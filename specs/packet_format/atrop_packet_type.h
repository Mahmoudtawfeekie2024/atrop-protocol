#pragma once

typedef enum {
    ATROP_PKT_DISCOVERY      = 0x01,  // Used for topology discovery and zone probing
    ATROP_PKT_ADVERTISEMENT  = 0x02,  // Node capability, metrics, role, learning scope
    ATROP_PKT_DECISION       = 0x03,  // AI-based path selection message
    ATROP_PKT_CORRECTION     = 0x04,  // Re-alignment due to feedback loop or anomaly
    ATROP_PKT_FEEDBACK       = 0x05,  // Real-time flow-level feedback (FIF-related)
    ATROP_PKT_INTENT_UPDATE  = 0x06,  // Business intent propagation or SLA redefinition
    ATROP_PKT_CONTROL        = 0x07,  // Used for FSM handshake and internal state sync
    ATROP_PKT_HEARTBEAT      = 0x08,  // Liveness probe inside ATZ
    ATROP_PKT_SECURITY       = 0x09,  // Trust signaling, SSIP identity, validation hops
    ATROP_PKT_VENDOR_EXT     = 0xFF   // Reserved for vendor-specific experimentation
} atrop_packet_type_t;
