/**
 * @file
 * Abstract Syntax Notation One (ISO 8824, 8825) codec.
 */

/*
 * Copyright (c) 2006 Axon Digital Design B.V., The Netherlands.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * Author: Christiaan Simons <christiaan.simons@axon.tv>
 */

#ifndef LWIP_HDR_APPS_SNMP_ASN1_H
#define LWIP_HDR_APPS_SNMP_ASN1_H

#include "lwip/apps/snmp_opts.h"
#include "lwip/err.h"
#include "lwip/pbuf.h"
#include "lwip/apps/snmp.h"

#if LWIP_SNMP

#ifdef __cplusplus
extern "C" {
#endif

#define SNMP_ASN1_UNIV   (0)    /* (!0x80 | !0x40) */
#define SNMP_ASN1_APPLIC (0x40) /* (!0x80 |  0x40) */
#define SNMP_ASN1_CONTXT (0x80) /* ( 0x80 | !0x40) */

#define SNMP_ASN1_CONSTR (0x20) /* ( 0x20) */
#define SNMP_ASN1_PRIMIT (0)    /* (!0x20) */

/* universal tags (from ASN.1 spec.) */
#define SNMP_ASN1_INTEG  2
#define SNMP_ASN1_OC_STR 4
#define SNMP_ASN1_NUL    5
#define SNMP_ASN1_OBJ_ID 6
#define SNMP_ASN1_SEQ    16

/* application specific (SNMP) tags (from SNMPv2-SMI) */
#define SNMP_ASN1_IPADDR    0  /* [APPLICATION 0] IMPLICIT OCTET STRING (SIZE (4)) */
#define SNMP_ASN1_COUNTER   1  /* [APPLICATION 1] IMPLICIT INTEGER (0..4294967295) => u32_t */
#define SNMP_ASN1_GAUGE     2  /* [APPLICATION 2] IMPLICIT INTEGER (0..4294967295) => u32_t */
#define SNMP_ASN1_TIMETICKS 3  /* [APPLICATION 3] IMPLICIT INTEGER (0..4294967295) => u32_t */
#define SNMP_ASN1_OPAQUE    4  /* [APPLICATION 4] IMPLICIT OCTET STRING */
#define SNMP_ASN1_COUNTER64 6  /* [APPLICATION 6] IMPLICIT INTEGER (0..18446744073709551615) */

/* context specific (SNMP) tags (from SNMP spec. RFC1157) */
#define SNMP_ASN1_PDU_GET_REQ      0
#define SNMP_ASN1_PDU_GET_NEXT_REQ 1
#define SNMP_ASN1_PDU_GET_RESP     2
#define SNMP_ASN1_PDU_SET_REQ      3
#define SNMP_ASN1_PDU_TRAP         4

err_t snmp_asn1_dec_type(struct pbuf *p, u16_t ofs, u8_t *type);
err_t snmp_asn1_dec_length(struct pbuf *p, u16_t ofs, u8_t *octets_used, u16_t *length);
err_t snmp_asn1_dec_u32t(struct pbuf *p, u16_t ofs, u16_t len, u32_t *value);
err_t snmp_asn1_dec_s32t(struct pbuf *p, u16_t ofs, u16_t len, s32_t *value);
err_t snmp_asn1_dec_oid(struct pbuf *p, u16_t ofs, u16_t len, struct snmp_obj_id *oid);
err_t snmp_asn1_dec_raw(struct pbuf *p, u16_t ofs, u16_t len, u16_t raw_len, u8_t *raw);

void snmp_asn1_enc_length_cnt(u16_t length, u8_t *octets_needed);
void snmp_asn1_enc_u32t_cnt(u32_t value, u16_t *octets_needed);
void snmp_asn1_enc_s32t_cnt(s32_t value, u16_t *octets_needed);
void snmp_asn1_enc_oid_cnt(u16_t ident_len, const s32_t *ident, u16_t *octets_needed);
err_t snmp_asn1_enc_type(struct pbuf *p, u16_t ofs, u8_t type);
err_t snmp_asn1_enc_length(struct pbuf *p, u16_t ofs, u16_t length);
err_t snmp_asn1_enc_u32t(struct pbuf *p, u16_t ofs, u16_t octets_needed, u32_t value);
err_t snmp_asn1_enc_s32t(struct pbuf *p, u16_t ofs, u16_t octets_needed, s32_t value);
err_t snmp_asn1_enc_oid(struct pbuf *p, u16_t ofs, u16_t ident_len, const s32_t *ident);
err_t snmp_asn1_enc_raw(struct pbuf *p, u16_t ofs, u16_t raw_len, const u8_t *raw);

err_t snmp_asn1_dec_bits(const u8_t *buf, u32_t buf_len, u32_t *bit_value);
u8_t  snmp_asn1_enc_bits(u8_t *buf, u32_t buf_len, u32_t bit_value);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_SNMP */

#endif /* LWIP_HDR_APPS_SNMP_ASN1_H */
