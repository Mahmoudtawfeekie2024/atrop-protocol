#pragma once
#include <stdint.h>
#include <stddef.h>
#include "atrop_header.h"
#include "atrop_tlv.h"

int atrop_serialize_header(const atrop_header_t* header, uint8_t* buffer, size_t buf_len);
int atrop_deserialize_header(const uint8_t* buffer, size_t buf_len, atrop_header_t* header_out);

int atrop_serialize_tlv(const atrop_tlv_t* tlv, uint8_t* buffer, size_t buf_len);
int atrop_deserialize_tlv(const uint8_t* buffer, size_t buf_len, atrop_tlv_t* tlv_out);
