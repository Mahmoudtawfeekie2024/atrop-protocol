#pragma once
#include <stdint.h>

#define ATROP_VERSION 0x1

typedef struct {
    uint8_t version:4;
    uint8_t packet_type:4;

    uint8_t node_identity_vector[16];     // 128 bits
    uint8_t path_intelligence_vector[32]; // 256 bits
    uint8_t intent_descriptor[8];         // 64 bits
    uint8_t feedback_injection_field[8];  // 64 bits

    uint8_t security_flags;
    uint8_t header_length;
    uint8_t next_header;
} __attribute__((packed)) atrop_header_t;
