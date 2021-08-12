/*
 * Copyright (C) 2010-2021 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 * FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 * See the Apache Version 2.0 License for specific language governing
 * permissions and limitations under the License.
 *
 */

/*
 * [[ WARNING | AUTOMATICALLY GENERATED FILE ]]
 * ------------------------------------------------------------------------
 * This file has been generated by the script:
 *     applibs/sx_api_utils/generator/sx_header_gen.py.
 *
 * You can manually modify this file ONLY for your testing needs.
 * In all other cases manual changes in this file must be removed
 * before committing. To modify content of this file in legal way
 * use applibs/include/adb/sx_flex_modifier.adb file.
 * ------------------------------------------------------------------------
 */

#ifndef __SX_FLEX_MODIFIER_AUTO_H__
#define __SX_FLEX_MODIFIER_AUTO_H__


/* Enum specific MACRO */
#define SX_GENERATE_ENUM(ENUM, STR)   ENUM,
#define SX_GENERATE_STRING(ENUM, STR) STR,

#define FOREACH_FLEX_MODIFIER_EMT_ID(F)    \
    F(SX_FLEX_MODIFIER_EMT0_E,     "EMT0") \
    F(SX_FLEX_MODIFIER_EMT1_E,     "EMT1") \
    F(SX_FLEX_MODIFIER_EMT2_E,     "EMT2") \
    F(SX_FLEX_MODIFIER_EMT3_E,     "EMT3") \
    F(SX_FLEX_MODIFIER_EMT4_E,     "EMT4") \
    F(SX_FLEX_MODIFIER_EMT5_E,     "EMT5") \
    F(SX_FLEX_MODIFIER_EMT6_E,     "EMT6") \
    F(SX_FLEX_MODIFIER_EMT7_E,     "EMT7") \
    F(SX_FLEX_MODIFIER_EMT_LAST_E, "")

typedef enum sx_flex_modifier_emt_id {
    FOREACH_FLEX_MODIFIER_EMT_ID(SX_GENERATE_ENUM)
} sx_flex_modifier_emt_id_e;

typedef struct sx_flex_modifier_emt_key {
    sx_flex_modifier_emt_id_e emt_id;
} sx_flex_modifier_emt_key_t;


#define FOREACH_FLEX_MODIFIER_EMT_UPDATE_FIELD(F)                                        \
    F(SX_FLEX_MODIFIER_EMT_UPDATE_FIELD_IPV4_LENGTH_E,        "Update IPv4 length")      \
    F(SX_FLEX_MODIFIER_EMT_UPDATE_FIELD_IPV6_LENGTH_E,        "Update IPv6 length")      \
    F(SX_FLEX_MODIFIER_EMT_UPDATE_FIELD_UDP_TCP_LENGTH_E,     "Update UDP/TCP length")   \
    F(SX_FLEX_MODIFIER_EMT_UPDATE_FIELD_GENEVE_LENGTH_E,      "Update GENEVE length")    \
    F(SX_FLEX_MODIFIER_EMT_UPDATE_FIELD_HBH_LENGTH_E,         "Update HBH length")       \
    F(SX_FLEX_MODIFIER_EMT_UPDATE_FIELD_UDP_TCP_CHECKSUM_E,   "Update UDP/TCP checksum") \
    F(SX_FLEX_MODIFIER_EMT_UPDATE_FIELD_CLEAR_UDP_CHECKSUM_E, "Clear UDP checksum")      \
    F(SX_FLEX_MODIFIER_EMT_UPDATE_FIELD_LAST_E,               "")

typedef enum sx_flex_modifier_emt_update_field {
    FOREACH_FLEX_MODIFIER_EMT_UPDATE_FIELD(SX_GENERATE_ENUM)
} sx_flex_modifier_emt_update_field_e;

#define FOREACH_FLEX_MODIFIER_EMT_COMMAND(F)                                                              \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_IMMEDIATE_E,                      "Immediate")                         \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_SPAN_MIRROR_INGRESS_PORT_LABEL_E, "Span mirror ingress port")          \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_SPAN_MIRROR_EGRESS_PORT_LABEL_E,  "Span mirror egress port")           \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_INGRESS_TIMESTAMP_SEC_MSB_E,      "Ingress timestamp seconds MSB")     \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_INGRESS_TIMESTAMP_SEC_LSB_E,      "Ingress timestamp seconds LSB")     \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_INGRESS_TIMESTAMP_NSEC_MSB_E,     "Ingress timestamp nanoseconds MSB") \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_INGRESS_TIMESTAMP_NSEC_LSB_E,     "Ingress timestamp nanoseconds LSB") \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_EGRESS_TIMESTAMP_SEC_MSB_E,       "Egress timestamp seconds MSB")      \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_EGRESS_TIMESTAMP_SEC_LSB_E,       "Egress timestamp seconds LSB")      \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_EGRESS_TIMESTAMP_NSEC_MSB_E,      "Egress timestamp nanoseconds MSB")  \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_EGRESS_TIMESTAMP_NSEC_LSB_E,      "Egress timestamp nanoseconds LSB")  \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_TCLASS_E,                         "Tclass")                            \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_EGRESS_BUFFER_FILL_LEVEL_MSB_E,   "Egress buffer fill level MSB")      \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_EGRESS_BUFFER_FILL_LEVEL_LSB_E,   "Egress buffer fill level LSB")      \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_LATENCY_MSB_E,                    "Latency MSB")                       \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_LATENCY_LSB_E,                    "Latency LSB")                       \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_GP_REGISTER_0_E,                  "GP register 0")                     \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_GP_REGISTER_1_E,                  "GP register 1")                     \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_GP_REGISTER_2_E,                  "GP register 2")                     \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_GP_REGISTER_3_E,                  "GP register 3")                     \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_GP_REGISTER_4_E,                  "GP register 4")                     \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_GP_REGISTER_5_E,                  "GP register 5")                     \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_GP_REGISTER_6_E,                  "GP register 6")                     \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_GP_REGISTER_7_E,                  "GP register 7")                     \
    F(SX_FLEX_MODIFIER_EMT_COMMAND_LAST_E,                           "")

typedef enum sx_flex_modifier_emt_command {
    FOREACH_FLEX_MODIFIER_EMT_COMMAND(SX_GENERATE_ENUM)
} sx_flex_modifier_emt_command_e;

typedef struct sx_flex_modifier_emt_data {
    sx_flex_modifier_emt_command_e cmd_id;
    uint16_t                       immediate_value; /**< Immediate value to set (immediate command only) */
    boolean_t                      skip;            /**< False: Set the value from this command, True: leave the original value (edit only) */
} sx_flex_modifier_emt_data_t;

#define FLEX_MODIFIER_MAX_EMT_CFG 32


typedef struct sx_flex_modifier_emt_cfg {
    sx_flex_modifier_emt_data_t         emt_data_list[FLEX_MODIFIER_MAX_EMT_CFG];                  /**< List of commands to perform in this EMT */
    uint32_t                            emt_data_cnt;
    sx_flex_modifier_emt_update_field_e emt_update_list[SX_FLEX_MODIFIER_EMT_UPDATE_FIELD_LAST_E]; /**< List of updates to perform in this EMT */
    uint32_t                            emt_update_cnt;
} sx_flex_modifier_emt_cfg_t;

#endif /* __SX_FLEX_MODIFIER_AUTO_H__ */