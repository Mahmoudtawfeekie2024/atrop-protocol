#include <stdio.h>
#include <string.h>
#include "C:\Users\mahmo\Desktop\atrop-protocol\specs\packet_format\atrop_packet.h"

int main() {
    uint8_t buffer[128];

    // Step 1: Create TLV field
    atrop_tlv_t original_tlv;
    original_tlv.type = 0xA1;  // example type
    original_tlv.length = 5;
    memcpy(original_tlv.value, "ATROP", original_tlv.length);

    printf("Original TLV:\n");
    printf("  Type: 0x%X\n", original_tlv.type);
    printf("  Length: %d\n", original_tlv.length);
    printf("  Value: %.*s\n", original_tlv.length, original_tlv.value);

    // Step 2: Serialize
    int written = atrop_serialize_tlv(&original_tlv, buffer, sizeof(buffer));
    if (written < 0) {
        printf("TLV serialization failed.\n");
        return 1;
    }

    // Step 3: Deserialize
    atrop_tlv_t parsed_tlv;
    int parsed = atrop_deserialize_tlv(buffer, written, &parsed_tlv);
    if (parsed < 0) {
        printf("TLV deserialization failed.\n");
        return 1;
    }

    // Step 4: Print parsed TLV
    printf("\nParsed TLV:\n");
    printf("  Type: 0x%X\n", parsed_tlv.type);
    printf("  Length: %d\n", parsed_tlv.length);
    printf("  Value: %.*s\n", parsed_tlv.length, parsed_tlv.value);

    return 0;
}
