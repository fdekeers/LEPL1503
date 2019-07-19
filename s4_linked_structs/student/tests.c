// CTester template

#include <stdlib.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"


/*
 * @return: number of times @value is contained in @array
 */
int containsArray(int* array, int size, int value){
    int count = 0;
    for(int i = 0; i < size; i++){
        if(array[i] == value)
            count++;
    }
    return count;
}

/*
 * @return: the first integer in @array that is not equal to @value. If every value of @array is equal to @value, 0 is returned
 */
int diffContains(int* array, int size, int value){
    for(int i = 0; i < size; i++){
        if(array[i] != value){
            return array[i];
        }
    }
    return 0;;
}

int nodeEquals(struct node *a, struct node *b){
    int sameName;
    if(a->name == NULL && b->name == NULL)
        sameName = 1;
    else{
        if(a->name == NULL || b->name == NULL){
            return 0;
        }
        else{
            sameName = !strcmp(a->name,b->name);
        }
    }
    int sameBuffer;
    if(a->buffer == NULL && b->buffer == NULL)
        sameBuffer = 1;
    else{
        if(a->buffer == NULL || b->buffer == NULL){
            return 0;
        }
        else{
            sameBuffer = !strcmp(a->buffer,b->buffer);
        }
    }
    int sameParent;
    if(a->parent == NULL && b->parent == NULL)
        sameParent = 1;
    else{
        if(a->parent == NULL || b->parent == NULL){
            return 0;
        }
        else{
            sameParent = a->parent == b->parent;
        }
    }
    int sameFifo;
    if(a->fifo == NULL && b->fifo == NULL)
        sameFifo = 1;
    else{
        if(a->fifo == NULL || b->fifo == NULL){
            return 0;
        }
        else{
            sameFifo = a->fifo == b->fifo;
        }
    }
    return ( a->hash==b->hash && a->id==b->id && sameName && sameBuffer && a->timestamp==b->timestamp && a->acl==b->acl && a->flow==b->flow && sameParent && sameFifo );


    //another solution, since the pointer is the first allocated thing in the node structure :
    /*
    return !memcmp((void*)(a+sizeof(struct node*)),(void*)(b+sizeof(struct node*)), sizeof(struct node) - sizeof(struct node*));
    // doesn't work.
    */
}

struct node *generate_list(){
    int len = sizeof(struct node);
    int i, j;

    struct node *head, *tmp, *act;
    char* tmp2;

    for (j = 0; j < 10; j++){
        tmp = (struct node*) malloc(len);
        //printf("tmp add = %p\n", tmp);
        tmp->next = NULL;
        tmp2 = (char*) tmp;

        for(i = sizeof(struct node*); i < len; i++){
            if (i%2)
                *(tmp2+i) = 0;
            else
                *(tmp2+i) = (j+1)%10;
            //printf("struct %i : byte %i = %i\n", j, i, *(tmp2+i));
            //printf("%i", *(tmp2+i));
        }

        if (j == 0){
            head = tmp;
        }
        else{
            (act)->next = tmp;
        }

        act = tmp;
    }

    act->next = NULL;

    /*struct node * run = head;
  while(run)
  {
    printf("run : %p\n", run);
    run = run->next;
  }*/

    return head;
}
int flag = 1;
void test_empty_list(){
    set_test_metadata("filter", _("Test the return value of the function when null pointer is given as arg"), 1);

    struct node* ret = (struct node*) 0x42;

    SANDBOX_BEGIN;
    ret = pair_filter(NULL);
    SANDBOX_END;

    CU_ASSERT_PTR_NULL(ret);
    if (ret){
	flag = 0;
	set_tag("wrong_args_handling");
        push_info_msg(_("Wrong returned value when passing NULL arg"));
    }
}

void test_one_elem(){
    set_test_metadata("filter", _("Test the return value of the function when the list is one element long"), 1);

    //TODO changed
    //struct node* ret = (struct node*) 0x42;
    struct node *ret;

    struct node* list = malloc(sizeof(struct node));
    list->next = NULL;
    /*list->fifo = NULL;
  list->parent = '\0';*/

    //to be able to know how many bytes the student malloced
    int begin = logs.malloc.n;
    monitored.malloc = true;

    SANDBOX_BEGIN;
    ret = pair_filter(list);
    SANDBOX_END;

    CU_ASSERT_PTR_NOT_NULL(ret);
    if (!ret){
	flag = 0;
	set_tag("not_expected_list");
        push_info_msg(_("NULL was returned for a one element list"));
        return;
    }

    int nbMalloc = stats.malloc.called;
    CU_ASSERT_EQUAL(nbMalloc, 1);
    if(nbMalloc != 1){
	flag = 0;
	set_tag("not_malloc_once");
        push_info_msg(_("You should use malloc once in this case."));
    }
    else{
        int size = logs.malloc.log[begin].size;
        if(size != sizeof(struct node)){
	    flag = 0;
            CU_FAIL();
            if(size == sizeof(struct node*)){
		set_tag("wrong_alloc_size");
                char error_msg[150];
                sprintf(error_msg, _("You allocated the space for a pointer, not for the struct node. You allocated %zd bytes instead of %zd"), sizeof(struct node*), sizeof(struct node));
                push_info_msg(error_msg);
            }
            else{
		set_tag("wrong_alloc_size");
                char error_msg[150];
                sprintf(error_msg, _("You allocated %d bytes but we expected %zd bytes"), size, sizeof(struct node));
                push_info_msg(error_msg);
            }
        }
    }

    CU_ASSERT_PTR_NULL(ret->next);
    if (memcmp(list, ret, sizeof(struct node))){
	flag = 0;
	set_tag("not_expected_list");
        CU_FAIL("The function produced a wrong list");
        push_info_msg(_("The function produced a wrong list"));
    }
}

void test_two_elem(){
    set_test_metadata("filter", _("Test the return value of the function when the list is two element long"), 1);

    //TODO changed
    //struct node* ret = (struct node*) 0x42;
    struct node *ret;

    struct node* list = malloc(sizeof(struct node));
    list->fifo = NULL;
    list->parent = '\0';

    list->next = malloc(sizeof(struct node));
    list->next->next = NULL;
    list->next->fifo = NULL;
    list->next->parent = '\0';

    //to be able to know how many bytes the student malloced
    int begin = logs.malloc.n;

    monitored.malloc = true;
    SANDBOX_BEGIN;
    ret = pair_filter(list);
    SANDBOX_END;

    int nbMalloc = stats.malloc.called;
    CU_ASSERT_EQUAL(nbMalloc, 1);
    if(nbMalloc != 1){
	flag = 0;
	set_tag("not_malloc_once");
        push_info_msg(_("You should use malloc once in this case."));
    }
    else{
        int size = logs.malloc.log[begin].size;
        if(size != sizeof(struct node)){
	    flag = 0;
            CU_FAIL();
            if(size == sizeof(struct node*)){
		set_tag("wrong_alloc_size");
                char error_msg[150];
                sprintf(error_msg, _("You allocated the space for a pointer, not for the struct node. You allocated %zd bytes instead of %zd"), sizeof(struct node*), sizeof(struct node));
                push_info_msg(error_msg);
            }
            else{
		set_tag("wrong_alloc_size");
                char error_msg[150];
                sprintf(error_msg, _("You allocated %d bytes but we expected %zd bytes"), size, sizeof(struct node));
                push_info_msg(error_msg);
            }
        }
    }

    CU_ASSERT_PTR_NOT_NULL(ret);
    if (!ret){
	set_tag("not_expected_list");
	flag = 0;
        push_info_msg(_("NULL was returned for a two element list"));
        return;
    }

    CU_ASSERT_PTR_NULL(ret->next);
    list->next = NULL;
    if (memcmp(list, ret, sizeof(struct node))){
	flag = 0;
	set_tag("not_expected_list");
        CU_FAIL("The function produced a wrong list");
        push_info_msg(_("The function produced a wrong list"));
    }
    if(flag){
	set_tag("q1");
    }
}

void test_pair_filter(){
    set_test_metadata("filter", _("Test if the function returns a valid linked list in normal case"), 1);
    int len = sizeof(struct node);

    struct node* head = generate_list(), *ret;
    //printf("%p\n", (head));

    //to be able to know how many bytes the student malloced
    int begin = logs.malloc.n;

    monitored.malloc = true;
    SANDBOX_BEGIN;
    ret = pair_filter(head);
    SANDBOX_END;

    int nbMalloc = stats.malloc.called;
    CU_ASSERT_EQUAL(nbMalloc, 5);
    if(nbMalloc != 5){
	flag = 0;
        push_info_msg(_("You should use malloc 5 times in this case."));
    }
    else{
        int size[1];
        size[0] = logs.malloc.log[begin].size;
        int firstDiff = diffContains(size, 5, len);
        if(firstDiff){
	    flag = 0;
            CU_FAIL();
            int size[5];
            size[0] = logs.malloc.log[begin].size;
            size[1] = logs.malloc.log[begin+1].size;
            size[2] = logs.malloc.log[begin+2].size;
            size[3] = logs.malloc.log[begin+3].size;
            size[4] = logs.malloc.log[begin+4].size;
            if(containsArray(size, 5, sizeof(struct node*))){
		set_tag("wrong_alloc_size");
                char error_msg[150];
                sprintf(error_msg, _("For at least one of the nodes, you allocated the space for a pointer, not for the struct node. You allocated %zd bytes instead of %zd"), sizeof(struct node*), sizeof(struct node));
                push_info_msg(error_msg);
            }
            else{
		set_tag("wrong_alloc_size");
                char error_msg[150];
                sprintf(error_msg, _("You allocated %d bytes but we expected %zd bytes"), firstDiff, sizeof(struct node));
                push_info_msg(error_msg);
            }
        }
    }

    if (!ret){
	flag = 0;
	set_tag("error_normal_case");
        CU_FAIL("NULL returned value");
        push_info_msg(_("NULL returned value"));
        return;
    }

    //printf("ret %p\n", ret);

    struct node *run1 = ret, *run2 = head;
    int equals;

    //------
    int count = 0;
    //------
    while(run2){
        //------
        count++;
        //------
        if(!run1){
	    flag= 0 ;
	    set_tag("not_expected_list");
            CU_FAIL("The function produced a wrong list");
            push_info_msg(_("The function produced a wrong list. Your list is shorter than expected."));
            return;
        }

        equals = nodeEquals(run1,run2);
        if (!equals){
	    flag = 0;
            CU_FAIL("The function produced a wrong list");
            char errmsg[50];
            sprintf(errmsg, _("The function produced a wrong list. Error at node : %d, counting from 1."), count);
            CU_FAIL("The function produced a wrong list");
            push_info_msg(errmsg);
            return;
        }

        run1 = run1->next;
        run2 = run2->next;
        if (!run2->next)
            break;
        run2 = run2->next;
    }
    //------
    char error_msg[30];
    sprintf(error_msg, _("Number of nodes : %d"), count);
    push_info_msg(error_msg);
    //------

    CU_PASS("The produced list match");
}


int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test_pair_filter, test_empty_list, test_one_elem, test_two_elem);
}

