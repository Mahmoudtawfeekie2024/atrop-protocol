#pragma once
#include <stdint.h>

#define MAX_TLV_SIZE 64

typedef struct {
    uint8_t type;
    uint8_t length;
    uint8_t value[MAX_TLV_SIZE];
} __attribute__((packed)) atrop_tlv_t;
