#include <string.h>
#include <stdlib.h>
#include "atrop_header.h"
#include "atrop_tlv.h"

#define ATROP_SUCCESS 0
#define ATROP_ERROR_INVALID_LENGTH -1

// Serialize ATROP header to a byte buffer
int atrop_serialize_header(const atrop_header_t* header, uint8_t* buffer, size_t buf_len) {
    if (buf_len < sizeof(atrop_header_t)) return ATROP_ERROR_INVALID_LENGTH;
    memcpy(buffer, header, sizeof(atrop_header_t));
    return sizeof(atrop_header_t);
}

// Deserialize ATROP header from a byte buffer
int atrop_deserialize_header(const uint8_t* buffer, size_t buf_len, atrop_header_t* header_out) {
    if (buf_len < sizeof(atrop_header_t)) return ATROP_ERROR_INVALID_LENGTH;
    memcpy(header_out, buffer, sizeof(atrop_header_t));
    return sizeof(atrop_header_t);
}

// Serialize a TLV field
int atrop_serialize_tlv(const atrop_tlv_t* tlv, uint8_t* buffer, size_t buf_len) {
    if (buf_len < (2 + tlv->length)) return ATROP_ERROR_INVALID_LENGTH;
    buffer[0] = tlv->type;
    buffer[1] = tlv->length;
    memcpy(&buffer[2], tlv->value, tlv->length);
    return 2 + tlv->length;
}

// Deserialize a TLV field
int atrop_deserialize_tlv(const uint8_t* buffer, size_t buf_len, atrop_tlv_t* tlv_out) {
    if (buf_len < 2) return ATROP_ERROR_INVALID_LENGTH;
    tlv_out->type = buffer[0];
    tlv_out->length = buffer[1];
    if (tlv_out->length > MAX_TLV_SIZE || (2 + tlv_out->length) > buf_len)
        return ATROP_ERROR_INVALID_LENGTH;

    memcpy(tlv_out->value, &buffer[2], tlv_out->length);
    return 2 + tlv_out->length;
}
