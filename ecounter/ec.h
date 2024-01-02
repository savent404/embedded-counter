#pragma once

#include <stdint.h>
#include <stddef.h>

/**
 * @note: This is not thread-safe.
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ec_instance {
    struct ec_instance* next;
    const char *name;
    uint32_t item_size;
    uint32_t item_capacity;
    void* item_start;
    void* item_end;
    void* item_capacity_end;
    void* items;
} ec_inst_t;

void ec_inst_init_raw(ec_inst_t* inst, uint32_t item_size, void* pool, uint32_t pool_size);
void ec_inst_register(ec_inst_t* inst, const char *name);
void ec_inst_unregister(ec_inst_t* inst);
void ec_inst_deinit(ec_inst_t* inst);

void ec_inst_record(ec_inst_t* inst, const void* item);
void* ec_inst_record_nocopy(ec_inst_t* inst);

#define EC_INST(name) \
    (ec_inst_##name)

#define EC_INST_DEC(name) \
    extern ec_inst_t* const ec_inst_##name

#define EC_INST_DEF(name, item_size, item_count) \
    static uint8_t ec_inst_##name##_data[(item_size) * (item_count) + sizeof(ec_inst_t)] = { 0 }; \
    const uint8_t ec_inst_##name##_item_size = (item_size); \
    ec_inst_t* ec_inst_##name = (ec_inst_t*)ec_inst_##name##_data;

#define EC_INST_INIT(name) \
    ec_inst_init_raw(EC_INST(name), ec_inst_##name##_item_size, \
        ec_inst_##name##_data + sizeof(ec_inst_t), \
        sizeof(ec_inst_##name##_data) - sizeof(ec_inst_t))

#ifdef __cplusplus
}
#endif
