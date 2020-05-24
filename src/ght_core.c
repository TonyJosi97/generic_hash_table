#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../inc/generic_hash_table.h"
#include "../inc/generic_hash_table_core_util.h"

ght_ret_status_t ght_init(g_hash_table_t *ht, size_t base, size_t item_sz) {

    ht->base_capacity = base;
    ht->capacity = ht->base_capacity;
    ht->item_size = item_sz;
    ht->count = 0;
    if((ht->items = (ght_item_t **) calloc(ht->capacity, sizeof(ght_item_t *)))  == NULL)
        return GHT_FAIL;

    return GHT_SUCCESS;

}

ght_ret_status_t ght_insert(g_hash_table_t *ht, unsigned long key, void *val) {

    unsigned int chain_len = 0;
    size_t index = (size_t) get_hash(key, (unsigned long) ht->capacity, chain_len);
    while((ht->items[index]) != NULL) {
        ++chain_len;
        index = (size_t) get_hash(key, (unsigned long) ht->capacity, chain_len);
    }
    printf("Hash: %ld\n", index);
    if(__ght_core_util_item_init(&(ht->items[index]), key, val, ht->item_size) != GHT_SUCCESS)
        return GHT_FAIL;

    return GHT_SUCCESS;

}

ght_ret_status_t ght_search(g_hash_table_t *ht, unsigned long key, void *ret_ptr) {

    unsigned int chain_len = 0;
    size_t index = (size_t) get_hash(key, (unsigned long) ht->capacity, chain_len);

    while(((*ht->items[index]).key) != key) {

        if(++chain_len < ht->capacity)
            return GHT_FAIL;

        index = (size_t) get_hash(key, (unsigned long) ht->capacity, chain_len);
    }

    if(ht->items[index] != NULL) {
        memcpy(ret_ptr, (*(ht->items[index])).val_ptr, ht->item_size);
        return GHT_SUCCESS;
    }

    return GHT_FAIL;

}

ght_ret_status_t ght_deinit(g_hash_table_t *ht) {

    if(ht->items) {
        for(size_t i = 0; i < ht->capacity; i++) {
            if(ht->items[i] != NULL) {
                printf("_____________Deinit: %ld\n", i);
                if(__ght_core_util_item_deinit(ht->items[i]) != GHT_SUCCESS)
                    return GHT_FAIL;
            }
        }
    
        free(ht->items);
        return GHT_SUCCESS;
    }

    return GHT_FAIL;

}