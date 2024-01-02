#include "ecounter/ec.h"
#include <assert.h>
#include <string.h>

static ec_inst_t* ec_head = NULL;

void ec_inst_init_raw(ec_inst_t* inst, uint32_t item_size, void* pool, uint32_t pool_size) {
    inst->item_size = item_size;
    inst->item_capacity = pool_size / item_size;
    inst->item_start = pool;
    inst->item_end = pool;
    inst->item_capacity_end = (uint8_t*)pool + inst->item_capacity * item_size;
    inst->items = pool;
    inst->mark = 0x175BB517;
}

void ec_inst_register(ec_inst_t* inst, const char *name) {
    ec_inst_t *ptr = ec_head, *prev = NULL;

    while (ptr) {
        if (ptr == inst) {
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }

    if (prev) {
        prev->next = inst;
    } else {
        ec_head = inst;
    }
    inst->name = name;
}

void ec_inst_unregister(ec_inst_t* inst) {
    ec_inst_t *ptr = ec_head, *prev = NULL;

    while (ptr) {
        if (ptr == inst) {
            if (prev) {
                prev->next = ptr->next;
            } else {
                ec_head = ptr->next;
            }
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
}

void ec_inst_deinit(ec_inst_t* inst) {
    ec_inst_unregister(inst);
}


// force inline
static inline void* _ec_inst_record_nocopy(ec_inst_t* inst)
{
    // NOTE: overwriting is default behavior
    uint32_t size= inst->item_size;
    uint32_t capacity = inst->item_capacity;
    void *end = inst->item_end, *retval = end;
    void *capacity_end = (uint8_t*)inst->item_start + size * capacity;

    end = (uint8_t*)end + size;
    if (end >= capacity_end) {
        end = inst->items;
    }
    inst->item_end = end;

    return retval;
}

void ec_inst_record(ec_inst_t* inst, const void* item)
{
    void* free_item = _ec_inst_record_nocopy(inst);
    memcpy(free_item, item, inst->item_size);
}

void* ec_inst_record_nocopy(ec_inst_t* inst)
{
    return _ec_inst_record_nocopy(inst);
}
