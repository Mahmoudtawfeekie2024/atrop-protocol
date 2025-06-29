#include <stdio.h>
#include "atrop_fsm.h"

void atrop_fsm_handle_packet(atrop_fsm_ctx_t* ctx, atrop_packet_type_t pkt_type) {
    switch (ctx->state) {
        case ATROP_STATE_INIT:
            if (pkt_type == ATROP_PKT_DISCOVERY) {
                ctx->state = ATROP_STATE_LEARNING;
                printf("[FSM] Transition: INIT → LEARNING\n");
            }
            break;

        case ATROP_STATE_LEARNING:
            if (pkt_type == ATROP_PKT_FEEDBACK) {
                ctx->learning_rounds += 1;
                printf("[FSM] Feedback received (learning_rounds=%d)\n", ctx->learning_rounds);
            } else if (pkt_type == ATROP_PKT_DECISION) {
                ctx->state = ATROP_STATE_DECISION;
                printf("[FSM] Transition: LEARNING → DECISION\n");
            }
            break;

        case ATROP_STATE_DECISION:
            if (pkt_type == ATROP_PKT_CORRECTION) {
                ctx->state = ATROP_STATE_CORRECTION;
                printf("[FSM] Transition: DECISION → CORRECTION\n");
            } else if (pkt_type == ATROP_PKT_ADVERTISEMENT) {
                ctx->state = ATROP_STATE_CONVERGED;
                printf("[FSM] Transition: DECISION → CONVERGED\n");
            }
            break;

        case ATROP_STATE_CONVERGED:
            if (pkt_type == ATROP_PKT_SECURITY) {
                ctx->state = ATROP_STATE_SECURE;
                ctx->trust_score = 100;
                printf("[FSM] Transition: CONVERGED → SECURE\n");
            }
            break;

        default:
            printf("[FSM] No transition defined for state %d and pkt %d\n", ctx->state, pkt_type);
            break;
    }
}
