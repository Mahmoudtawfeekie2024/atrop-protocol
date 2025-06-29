#include <stdio.h>
#include "C:\Users\mahmo\Desktop\atrop-protocol\specs\state_machines\atrop_fsm.h"
#include "C:\Users\mahmo\Desktop\atrop-protocol\specs\packet_format\atrop_packet_type.h"

int main() {
    atrop_fsm_ctx_t fsm = {
        .state = ATROP_STATE_INIT,
        .trust_score = 0,
        .learning_rounds = 0
    };

    printf("Starting FSM Simulation...\n");

    // Simulate a discovery packet
    atrop_fsm_handle_packet(&fsm, ATROP_PKT_DISCOVERY);

    // Simulate feedback packets
    atrop_fsm_handle_packet(&fsm, ATROP_PKT_FEEDBACK);
    atrop_fsm_handle_packet(&fsm, ATROP_PKT_FEEDBACK);

    // Simulate decision packet
    atrop_fsm_handle_packet(&fsm, ATROP_PKT_DECISION);

    // Simulate correction
    atrop_fsm_handle_packet(&fsm, ATROP_PKT_CORRECTION);

    // Simulate advertisement (assume correction is complete)
    fsm.state = ATROP_STATE_DECISION;
    atrop_fsm_handle_packet(&fsm, ATROP_PKT_ADVERTISEMENT);

    // Simulate security handshake
    atrop_fsm_handle_packet(&fsm, ATROP_PKT_SECURITY);

    // Final state
    printf("FSM Final State: %d (trust_score: %d)\n", fsm.state, fsm.trust_score);

    return 0;
}
