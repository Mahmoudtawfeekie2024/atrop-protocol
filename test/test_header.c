#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "C:\Users\mahmo\Desktop\atrop-protocol\specs\packet_format\atrop_packet.h"
#include "C:\Users\mahmo\Desktop\atrop-protocol\specs\packet_format\atrop_packet_type.h"

int main() {
    uint8_t buffer[512];

    // Step 1: Create a sample ATROP header
    atrop_header_t hdr = {0};
    hdr.version = ATROP_VERSION;
    hdr.packet_type = ATROP_PKT_DISCOVERY;  // Using the new enum
    hdr.header_length = sizeof(atrop_header_t);

    // Optional: Populate identity and telemetry fields (demo only)
    memcpy(hdr.node_identity_vector, "NODE1234567890ID", 16);
    memcpy(hdr.path_intelligence_vector, "LATENCYLATENCYLATENCYLATENCY...", 32);
    memcpy(hdr.intent_descriptor, "QOS1234", 7);
    memcpy(hdr.feedback_injection_field, "DELAY100", 8);

    printf("Creating ATROP header...\n");

    // Step 2: Serialize the header into the buffer
    int written = atrop_serialize_header(&hdr, buffer, sizeof(buffer));
    if (written < 0) {
        printf("Serialization failed!\n");
        return 1;
    }

    printf("Serialized header (%d bytes).\n", written);

    // Step 3: Deserialize the header back from buffer
    atrop_header_t parsed_hdr;
    int parsed = atrop_deserialize_header(buffer, written, &parsed_hdr);
    if (parsed < 0) {
        printf("Deserialization failed!\n");
        return 1;
    }

    // Step 4: Output results
    printf("Deserialized header:\n");
    printf("  Version      : %u\n", parsed_hdr.version);
    printf("  Packet Type  : %u\n", parsed_hdr.packet_type);
    printf("  Header Length: %u\n", parsed_hdr.header_length);

    // Optional: Debug contents of key fields
    printf("  Identity     : %.16s\n", parsed_hdr.node_identity_vector);
    printf("  Intent       : %.8s\n", parsed_hdr.intent_descriptor);
    printf("  Feedback     : %.8s\n", parsed_hdr.feedback_injection_field);

    return 0;
}
