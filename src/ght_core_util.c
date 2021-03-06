/** 
 *  @file   ght_core_util.c
 *  @brief  Utility function definitions for Hash Table Library
 *
 *  This contains the Utility function definitions for Hash Table Library
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2020 Tony Josi
 *  @bug            No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

#include "../inc/generic_hash_table.h"
#include "../inc/legacy_macros.h"
#include "../inc/generic_hash_table_ds.h"
#include "../inc/generic_hash_table_core_util.h"



static unsigned long    hash_func_1(const unsigned long, const unsigned long);
static unsigned long    hash_func_2(const unsigned long);
static unsigned int     check_if_prime(unsigned int);



ght_ret_status_t 
__ght_core_util_item_init(
    ght_item_t *item, 
    unsigned long key, 
    void *val, 
    size_t size) {

    item->is_active = true;
    item->key = key;

    if(!memcpy(item->val_ptr, val, size)) {
        perror("    ERR: __ght_core_util_item_init(): memcpy()");
        return GHT_FAIL;
    }

    return GHT_SUCCESS;
}



ght_ret_status_t 
__ght_core_util_item_deinit(
    ght_item_t *item) {
    
    item->is_active = false;

    return GHT_SUCCESS;
}



unsigned long 
hash_func_1(
    const unsigned long key, 
    const unsigned long m) {

    return (key % m);

}



unsigned long 
hash_func_2(
    const unsigned long key) {
    
    unsigned long x = (HASH_FUNC_2_PRIME - (key % HASH_FUNC_2_PRIME));
    return x;

}



unsigned long 
__ght_core_util_get_hash(
    const unsigned long key, 
    const unsigned long capacity, 
    unsigned int chain_degreee) {

    UNUSED(hash_func_1);
    UNUSED(hash_func_2);
    UNUSED(chain_degreee);
    return (key % capacity);

}



unsigned int 
check_if_prime(
    unsigned int num) {

    if(num < 2)
        return 1;
    if(num < 4)
        return 0;
    if((num % 2) == 0)
        return 1;

    for(unsigned int itr = 3; itr <= floor(sqrt((double) num)); itr += 2)
        if((num % itr) == 0)
            return 1;
    return 0;
}



unsigned int     
get_next_prime(unsigned int base) {

    while(check_if_prime(base) != 0)
        ++base;

    return base;
}



ght_ret_status_t 
__ght_core_util_resize(
    g_hash_table_t *ht, 
    size_t size_estimate) {

    if(size_estimate < (ht->base_capacity))
        return GHT_SUCCESS;

    ght_ret_status_t ret_code;
    g_hash_table_t new_ht;
    size_t new_size = get_next_prime(size_estimate);

    new_ht.base_capacity = ht->base_capacity;
    new_ht.capacity = new_size;
    new_ht.item_size = ht->item_size;
    new_ht.scaling_factor = ht->scaling_factor;
    new_ht.count = 0;
    if((new_ht.items = \
    (ght_item_t *) calloc(new_ht.capacity, sizeof(ght_item_t)))  == NULL)
        return GHT_FAIL;

    uint8_t *alloc_mem = NULL;
    if((alloc_mem = malloc(new_ht.item_size * new_ht.capacity)) == NULL)
        return GHT_FAIL;

    for(unsigned int itr = 0; itr < new_ht.capacity; ++itr) {
        new_ht.items[itr].is_active = false;
        new_ht.items[itr].val_ptr = \
        (void *) (alloc_mem + (new_ht.item_size * itr)); 
    }

    if(ht->items) {
        for(size_t i = 0; i < ht->capacity; i++) 
            if(ht->items[i].is_active == true) {
                if((ret_code = ght_insert(&new_ht, ht->items[i].key, \
                ht->items[i].val_ptr)) != GHT_SUCCESS)
                    return GHT_FAIL;
            }
    }

    if(ght_deinit(ht) != GHT_SUCCESS)
        return GHT_FAIL;
        
    *ht = new_ht;
    //memcpy(ht, &new_ht, sizeof(g_hash_table_t));
    return GHT_SUCCESS;
}



ght_ret_status_t 
__ght_core_util_scale_up(
    g_hash_table_t *ht) {
    
    if(__ght_core_util_resize(ht, (size_t)(ht->capacity * 2)) != GHT_SUCCESS)
        return GHT_FAIL;
    
    return GHT_SUCCESS;
}


ght_ret_status_t 
__ght_core_util_scale_down(
    g_hash_table_t *ht) {

    if(__ght_core_util_resize(ht, (size_t)(ht->capacity / 2)) != GHT_SUCCESS) 
        return GHT_FAIL;

    return GHT_SUCCESS;
}



unsigned long 
get_time_in_nanosec(
    void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (unsigned long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

