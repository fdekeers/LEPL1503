#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student_code.h"
#include "CTester/CTester.h"

product_t *init_product(char* name, double price){
    product_t *ret = malloc(sizeof(product_t));
    if(!ret)
        return NULL;
    ret->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    if(ret->name){
        free(ret);
        return NULL;
    }
    strcpy(ret->name,name);
    ret->price = price;
    return ret;
}

int structEquals(product_t prod, char* name, double price){
    if(!(prod.name))
        return 0;
    if(strcmp(prod.name,name))
        return 0;
    if(prod.price != price)
        return 0;
    return 1;
}

void test_ptr_price(){
    set_test_metadata("getPtrPrice", _("Testing in a normal case"),1);
    product_t prod = { .name = "0.5L Water", .price = 1.0};
    double retPrice;
    monitored.malloc = true;
    monitored.free = true;

    SANDBOX_BEGIN;
    retPrice = getPtrPrice(&prod);
    SANDBOX_END;

    if(stats.malloc.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use malloc"));
    }

    if(stats.free.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use free"));
    }

    if(retPrice != 1.00){
        CU_FAIL();
        push_info_msg(_("Wrong return value"));
    }
    if(!structEquals(prod, "0.5L Water", 1.0)){
        CU_FAIL();
        push_info_msg(_("You are not allowed to change the structure ?"));
    }
}

void test_price(){
    set_test_metadata("getPrice", _("Testing in a normal case"),1);
    product_t prod = { .name = "0.5L Water", .price = 1.0};
    double retPrice;
    monitored.malloc = true;
    monitored.free = true;

    SANDBOX_BEGIN;
    retPrice = getPrice(prod);
    SANDBOX_END;

    if(stats.malloc.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use malloc"));
    }

    if(stats.free.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use free"));
    }

    if(retPrice != 1.00){
        CU_FAIL();
        push_info_msg(_("Wrong return value"));
    }
    if(!structEquals(prod, "0.5L Water", 1.0)){ //TODO he can change the string right ?
        CU_FAIL();
        push_info_msg(_("You are not allowed to change the structure ?"));
    }
}

void test_ptr_name(){
    set_test_metadata("getPtrName", _("Testing in a normal case"),1);
    product_t prod = { .name = "0.5L Water", .price = 1.0};
    char* retName;
    monitored.malloc = true;
    monitored.free = true;
    int begin = logs.malloc.n;

    SANDBOX_BEGIN;
    retName = getPtrName(&prod);
    SANDBOX_END;

    if(stats.malloc.called != 1){
        CU_FAIL();
        push_info_msg(_("You should use malloc once"));
    }
    else{
        int size = logs.malloc.log[begin].size;
        if(size != strlen("0.5L Water")+1){
            CU_FAIL();
            set_tag("wrong_alloc_size");
            if(size == 8){
                push_info_msg(_("It seems like you allocated the size for a pointer ! You have to malloc the space for each character of the string"));
            }
            else{
                push_info_msg(_("You allocated the wrong size of memory ! Maybe you forgot the \\\\0 character ?"));
            }
        }
    }
    if(stats.free.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use free"));
    }

    if(strcmp("0.5L Water", retName)){
        CU_FAIL();
        push_info_msg(_("You didn't return the right name"));
    }
    if(retName == prod.name){
        CU_FAIL();
        push_info_msg(_("You have to return a copy of the string and not the reference to the name in the structure !"));
    }
    if(!structEquals(prod, "0.5L Water", 1.0)){
        CU_FAIL();
        push_info_msg(_("You are not allowed to change the structure ?"));
    }

}

void test_ptr_name_malloc_fails(){
    set_test_metadata("getPtrName", _("Testing when malloc fails"),1);
    product_t prod = { .name = "0.5L Water", .price = 1.0};
    char* retName;
    monitored.malloc = true;
    monitored.free = true;
    failures.malloc = FAIL_FIRST;

    SANDBOX_BEGIN;
    retName = getPtrName(&prod);
    SANDBOX_END;

    if(stats.malloc.called != 1){
        CU_FAIL();
        set_tag("malloc_fail");
        push_info_msg(_("You should use malloc once"));
    }
    if(stats.free.called){
        CU_FAIL();
        set_tag("malloc_fail");
        push_info_msg(_("You are not allowed to use free"));
    }
    if(retName){
        CU_FAIL();
        set_tag("malloc_fail");
        push_info_msg(_("You should return NULL in this case"));
    }
    if(!structEquals(prod, "0.5L Water", 1.0)){
        CU_FAIL();
        set_tag("malloc_fail");
        push_info_msg(_("You are not allowed to change the structure ?"));
    }

}

void test_name(){
    set_test_metadata("getName", _("Testing in a normal case"),1);
    product_t prod = { .name = "0.5L Water", .price = 1.0};
    char* retName;
    monitored.malloc = true;
    monitored.free = true;
    int begin = logs.malloc.n;

    SANDBOX_BEGIN;
    retName = getPtrName(&prod);
    SANDBOX_END;

    if(stats.malloc.called != 1){
        CU_FAIL();
        push_info_msg(_("You should use malloc once"));
    }
    else{
        int size = logs.malloc.log[begin].size;
        if(size != strlen("0.5L Water")+1){
            CU_FAIL();
            set_tag("wrong_alloc_size");
            if(size == 8){
                push_info_msg(_("It seems like you allocated the size for a pointer ! You have to malloc the space for each character of the string"));
            }
            else{
                push_info_msg(_("You allocated the wrong size of memory ! Maybe you forgot the \\\\0 character ?"));
            }
        }
    }
    if(stats.free.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use free"));
    }

    if(strcmp("0.5L Water", retName)){
        CU_FAIL();
        push_info_msg(_("You didn't return the right name"));
    }
    if(retName == prod.name){
        CU_FAIL();
        push_info_msg(_("You have to return a copy of the string and not the reference to the name in the structure !"));
    }
    if(!structEquals(prod, "0.5L Water", 1.0)){ //TODO he can change the string right ?
        CU_FAIL();
        push_info_msg(_("You are not allowed to change the structure ?"));
    }

}

void test_name_malloc_fails(){
    set_test_metadata("getName", _("Testing when malloc fails"),1);
    product_t prod = { .name = "0.5L Water", .price = 1.0};
    char* retName;
    monitored.malloc = true;
    monitored.free = true;
    failures.malloc = FAIL_FIRST;

    SANDBOX_BEGIN;
    retName = getName(prod);
    SANDBOX_END;

    if(stats.malloc.called != 1){
        CU_FAIL();
        set_tag("malloc_fail");
        push_info_msg(_("You should use malloc once"));
    }
    if(stats.free.called){
        CU_FAIL();
        set_tag("malloc_fail");
        push_info_msg(_("You are not allowed to use free"));
    }
    if(retName){
        CU_FAIL();
        set_tag("malloc_fail");
        push_info_msg(_("You should return NULL in this case"));
    }
    if(!structEquals(prod, "0.5L Water", 1.0)){ //TODO he can change the string right ?
        CU_FAIL();
        set_tag("malloc_fail");
        push_info_msg(_("You are not allowed to change the structure ?"));
    }

}

void test_equals_normal_case(){
    set_test_metadata("prodEquals", _("Test when the content of the structures is the same"),1);
    char str[11] = "0.5L Water";
    char str2[11] = "0.5L Water";
    product_t prod = { .name = str, .price = 0.5};
    product_t prod2 = { .name = str2, .price = 0.5};
    int ret;
    
    monitored.malloc = true;
    monitored.free = true;

    SANDBOX_BEGIN;
    ret = prodEquals(&prod,prod2);
    SANDBOX_END;

    if(stats.malloc.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use malloc"));
    }
    if(stats.free.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use free"));
    }
    if(ret != 1){
        CU_FAIL();
        push_info_msg(_("You didn't return the good value !"));
    }
    if(!structEquals(prod, "0.5L Water", 0.5) || !structEquals(prod2, "0.5L Water", 0.5)){ //TODO concerning prod2, he can change prod2->name right ?
        CU_FAIL();
        push_info_msg(_("You are not allowed to change the structure ?"));
    }
}

void test_equals_diff_name(){
    set_test_metadata("prodEquals", _("Test when the name is different"),1);
    product_t prod = { .name = "0.5L Water", .price = 1.0};
    product_t prod2 = { .name = "0.5L Coke", .price = 1.0};
    int ret;
    
    monitored.malloc = true;
    monitored.free = true;

    SANDBOX_BEGIN;
    ret = prodEquals(&prod,prod2);
    SANDBOX_END;

    if(stats.malloc.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use malloc"));
    }
    if(stats.free.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use free"));
    }
    if(ret){
        CU_FAIL();
        push_info_msg(_("You didn't return the good value !"));
    }
    if(!structEquals(prod, "0.5L Water", 1.0) || !structEquals(prod2, "0.5L Coke", 1.0)){ //TODO concerning prod2, he can change prod2->name right ?
        CU_FAIL();
        push_info_msg(_("You are not allowed to change the structure ?"));
    }
}

void test_equals_diff_price(){
    set_test_metadata("prodEquals", _("Test when the price is different"),1);
    product_t prod = { .name = "0.5L Water", .price = 0.5};
    product_t prod2 = { .name = "0.5L Water", .price = 0.65};
    int ret;
    
    monitored.malloc = true;
    monitored.free = true;

    SANDBOX_BEGIN;
    ret = prodEquals(&prod,prod2);
    SANDBOX_END;

    if(stats.malloc.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use malloc"));
    }
    if(stats.free.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use free"));
    }
    if(ret){
        CU_FAIL();
        push_info_msg(_("You didn't return the good value !"));
    }
    if(!structEquals(prod, "0.5L Water", 0.5) || !structEquals(prod2, "0.5L Water", 0.65)){ //TODO concerning prod2, he can change prod2->name right ?
        CU_FAIL();
        push_info_msg(_("You are not allowed to change the structure ?"));
    }
}

void test_equals_diff_both(){
    set_test_metadata("prodEquals", _("Test when both the name and the price are different"),1);
    product_t prod = { .name = "0.5L Water", .price = 0.5};
    product_t prod2 = { .name = "1L Water", .price = 1.0};
    int ret;
    
    monitored.malloc = true;
    monitored.free = true;

    SANDBOX_BEGIN;
    ret = prodEquals(&prod,prod2);
    SANDBOX_END;

    if(stats.malloc.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use malloc"));
    }
    if(stats.free.called){
        CU_FAIL();
        push_info_msg(_("You are not allowed to use free"));
    }
    if(ret){
        CU_FAIL();
        push_info_msg(_("You didn't return the good value !"));
    }
    if(!structEquals(prod, "0.5L Water", 0.5) || !structEquals(prod2, "1L Water", 1.0)){ //TODO concerning prod2, he can change prod2->name right ?
        CU_FAIL();
        push_info_msg(_("You are not allowed to change the structure ?"));
    }
}

int main(int argc,char** argv)
{
    BAN_FUNCS(calloc);
    RUN(test_ptr_price, test_price, test_ptr_name, test_ptr_name_malloc_fails, test_name, test_name_malloc_fails, test_equals_normal_case, test_equals_diff_name, test_equals_diff_price, test_equals_diff_both);
}
