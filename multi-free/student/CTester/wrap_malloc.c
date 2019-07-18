/* 
 * Wrapper for malloc, free and calloc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>
#include <stdlib.h>

#include  "wrap.h"

#include <libintl.h> 
#include <locale.h> 
#define _(STRING) gettext(STRING)

#include "gvc.h"

#define MSG_SIZE 1000
char msg[MSG_SIZE];


void * __real_malloc(size_t s);
void * __real_calloc(size_t nmemb, size_t s);
void __real_free(void *);
void * __real_realloc(void *ptr, size_t size);


extern bool wrap_monitoring;
extern struct wrap_stats_t stats;
extern struct wrap_monitor_t monitored;
extern struct wrap_fail_t failures;
extern struct wrap_log_t logs;

//
// keeps only MAX_LOG in memory
//
void log_malloc(void *ptr, size_t size) {
  
  if(ptr!=NULL && logs.malloc.n < MAX_LOG) {
    logs.malloc.log[logs.malloc.n].size=size;
    logs.malloc.log[logs.malloc.n].ptr=ptr;
    logs.malloc.n++;
  }
}

void update_realloc_block(void *ptr, size_t newsize) {
   for(int i=0;i<MAX_LOG;i++) {
     if(logs.malloc.log[i].ptr==ptr) {
      logs.malloc.log[i].size=newsize;
      return;
     } 
  }
   return ;
}

size_t find_size_malloc(void *ptr) {
  for(int i=0;i<MAX_LOG;i++) {
    if(logs.malloc.log[i].ptr==ptr) 
      return logs.malloc.log[i].size;
  }
  return -1;
}


void * __wrap_malloc(size_t size) {
  if(!wrap_monitoring || !monitored.malloc) {
    return __real_malloc(size);
  }
  stats.malloc.called++;
  stats.malloc.last_params.size=size;
  if(FAIL(failures.malloc)) {
    failures.malloc=NEXT(failures.malloc);
    return failures.malloc_ret;
  }
  stats.memory.used+=size;
  failures.malloc=NEXT(failures.malloc);    
  void *ptr=__real_malloc(size);
  stats.malloc.last_return=ptr;
  log_malloc(ptr,size);
  return ptr;
}

void * __wrap_realloc(void *ptr, size_t size) {
  if(!wrap_monitoring || !monitored.realloc) {
    return __real_realloc(ptr, size);
  }
  stats.realloc.called++;
  stats.realloc.last_params.size=size;
  if(FAIL(failures.realloc)) {
    failures.realloc=NEXT(failures.realloc);
    return failures.realloc_ret;
  }
  failures.realloc=NEXT(failures.realloc);    
  int old_size=find_size_malloc(ptr);
  void *r_ptr=__real_realloc(ptr,size);
  stats.realloc.last_return=r_ptr;
  if(ptr!=NULL) {
      stats.memory.used+=size-old_size;
      update_realloc_block(ptr,size);
  }
  return r_ptr;
}


void * __wrap_calloc(size_t nmemb, size_t size) {
  if(!wrap_monitoring || !monitored.calloc) {
    return __real_calloc(nmemb, size);
  }
  stats.calloc.called++;
  stats.calloc.last_params.size=size;
  stats.calloc.last_params.nmemb=nmemb;

  if(FAIL(failures.calloc)) {
    failures.calloc=NEXT(failures.calloc);
    return failures.calloc_ret;
  }
  stats.memory.used+=nmemb*size;
  failures.calloc=NEXT(failures.calloc);
    
  void *ptr=__real_calloc(nmemb,size);
  stats.calloc.last_return=ptr;
  log_malloc(ptr,nmemb*size);
  return ptr;
}

int malloc_free_ptr(void *ptr) {

  for(int i=0;i<MAX_LOG;i++) {
    if(logs.malloc.log[i].ptr==ptr) {
      int size=logs.malloc.log[i].size;
      logs.malloc.log[i].size=-1;
      logs.malloc.log[i].ptr=NULL;
      return size;
    }
  }
  return 0;
}

void __wrap_free(void *ptr) {
  if(!wrap_monitoring || !monitored.free) {
    return __real_free(ptr);
  }
  stats.free.called++;
  stats.free.last_params.ptr=ptr;
  if(ptr!=NULL) {
    stats.memory.used-=malloc_free_ptr(ptr);

    if (FAIL(failures.free))
      failures.free=NEXT(failures.free);
    else
      __real_free(ptr);
  }
}


/*
void * find_ptr_malloc(size_t size){
  for(int i=0;i<MAX_LOG;i++) {
    if(logs.malloc.log[i].size==size) 
      return logs.malloc.log[i].ptr;
  }
  return NULL;
}

void malloc_log_init(struct malloc_t *l) {
  for(int i=0;i<MAX_LOG;i++) {
    l->log[i].size=-1;
    l->log[i].ptr=NULL;
  }
  l->n=0;

}

*/
int  malloc_allocated() {
  int tot=0;
  for(int i=0;i<MAX_LOG;i++) {
    if(logs.malloc.log[i].ptr!=NULL) {
      tot+=(int) logs.malloc.log[i].size;
    }
  }
  return tot;
}

/*
 * returns true if the address has been managed by malloc, false
 * otherwise (also false if address has been freed)
 */
int malloced(void *addr) {
  for(int i=0;i<logs.malloc.n;i++) {
    if(logs.malloc.log[i].ptr<=addr && 
       (logs.malloc.log[i].ptr+ logs.malloc.log[i].size)>=addr) {
      return true;
    }
  }
  return false;

}

/*
 * returns true if the address has been allocated by malloc, false
 * otherwise
 */
int malloced_ptr(void *addr) {
  for(int i=0;i<logs.malloc.n;i++) {
    if(logs.malloc.log[i].ptr==addr) {
      return true;
    }
  }
  return false;

}

struct addr2node {
  Agnode_t *node;
  void * addr;
};


/*
 * graphical representation of the memory
 */
void plot_memory(char *filename){
    Agraph_t *g;
    printf("Memory allocated : %d bytes\n",malloc_allocated());
    GVC_t *gvc;
    // set up a graphviz context
    gvc = gvContext();
    // Create a simple digraph 
    g = agopen("g", Agdirected, 0);

    struct addr2node map[logs.malloc.n];
    for(int i=0;i<logs.malloc.n;i++) {
      map[i].node=NULL;
      map[i].addr=NULL;
    }
    // heuristic
    // if sizeof=sizeof(void *) then assume pointer, 
    // if sizeof>= assume struct that may contain pointers
    // otherwise char

    // nodes, one node per block of memory
    Agnode_t *total_mem ;
    char total_mem_str[100];
    snprintf(total_mem_str,100,_("Total memory: %d bytes in %d blocks \n"),malloc_allocated(),logs.malloc.n);
    total_mem = agnode(g, total_mem_str, 1);
    agsafeset(total_mem, "color", "white", "");
    agsafeset(total_mem, "shape", "oval", "");

    for(int i=0;i<logs.malloc.n;i++) {
      if(logs.malloc.log[i].size==sizeof(void *)) {
	char ptr_addr[20];
	snprintf(ptr_addr, 20, "[%d bytes] %p", (int) logs.malloc.log[i].size,logs.malloc.log[i].ptr);	  
	map[i].node = agnode(g, ptr_addr, 1);
	map[i].addr=logs.malloc.log[i].ptr;
	//printf("node %d for addr %p  (%zu bytes)\n",i,map[i].addr, logs.malloc.log[i].size);
	agsafeset(map[i].node, "color", "red", "");
	agsafeset(map[i].node, "shape", "oval", "");
      }
      else if (logs.malloc.log[i].size>sizeof(void *)) {
	char ptr_addr[20];
	snprintf(ptr_addr, 20, "[%d bytes] %p ", (int) logs.malloc.log[i].size,logs.malloc.log[i].ptr);	  
	map[i].node = agnode(g, ptr_addr, 1);
	map[i].addr=logs.malloc.log[i].ptr;
	//printf("node %d for addr %p (%zu bytes)\n\n",i,map[i].addr, logs.malloc.log[i].size);
	agsafeset(map[i].node, "color", "blue", "");
	agsafeset(map[i].node, "shape", "oval", "");
	
      }
      else {
	// assume char
	char str[logs.malloc.log[i].size+1];
	str[logs.malloc.log[i].size+1]=0;
	for(int j=0;j<logs.malloc.log[i].size+1;j++){
	    str[j]=*(((char *)logs.malloc.log[i].ptr)+j);
	}
	map[i].node = agnode(g, str, 1);
	map[i].addr=logs.malloc.log[i].ptr;
	//printf("node %d for addr %p (%zu bytes)\n\n",i,map[i].addr, logs.malloc.log[i].size);
	agsafeset(map[i].node, "color", "black", "");
	agsafeset(map[i].node, "shape", "rectangle", "");
	}
    }
    // edges

    for(int i=0;i<logs.malloc.n;i++) {
      //printf ("node %d size(%d)\n",i,(int) logs.malloc.log[i].size);
      // node i
      //printf(" size %zu\n",logs.malloc.log[i].size);
      unsigned long * ptr=(unsigned long *)logs.malloc.log[i].ptr;
      if(logs.malloc.log[i].size>=sizeof(void *)) {
        for(int j=0;j<(logs.malloc.log[i].size/sizeof(void *));j++) {
          if(malloced_ptr((void *)*ptr)) {
            for(int k=0;k<logs.malloc.n;k++){
	      //printf ("checking %p== %p \n",(void *) *ptr,map[k].addr);
	      if(map[k].addr== (void *) *ptr) {
                Agedge_t *e __attribute__((unused));
                e = agedge(g, map[i].node, map[k].node, 0, 1);
                //printf("edge added from %d to %d\n",k,i);
              }
            }
          }
          ptr++;
        }
      }
    }
    gvLayout(gvc, g, "dot");
    // save graph in png file for feedback

    gvRenderFilename(gvc, g, "png", filename);
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
}

