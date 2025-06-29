#pragma once
#include "C:\Users\mahmo\Desktop\atrop-protocol\specs\packet_format\atrop_packet_type.h"

// ATROP FSM States
typedef enum {
    ATROP_STATE_INIT,           // Waiting for discovery
    ATROP_STATE_LEARNING,       // Observing flows, gathering intelligence
    ATROP_STATE_DECISION,       // AI makes a path choice
    ATROP_STATE_CORRECTION,     // Adjusting based on feedback
    ATROP_STATE_CONVERGED,      // Stable routing mode
    ATROP_STATE_SECURE,         // Validated and encrypted session
    ATROP_STATE_VENDOR_EXT      // Vendor-defined state hook
} atrop_state_t;

// FSM Context (one per ATZ node)
typedef struct {
    atrop_state_t state;
    int trust_score;
    int learning_rounds;
} atrop_fsm_ctx_t;

// FSM transition handler
void atrop_fsm_handle_packet(atrop_fsm_ctx_t* ctx, atrop_packet_type_t pkt_type);
