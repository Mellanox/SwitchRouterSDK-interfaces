/*
 *  Copyright (C) 2014-2021. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

#ifndef __SX_BULK_COUNTER_H__
#define __SX_BULK_COUNTER_H__

#include <sx/sxd/kernel_user.h>
#include <sx/sdk/auto_headers/sx_port_id_auto.h>
#include <sx/sdk/auto_headers/sx_bulk_counter_auto.h>
#include <resource_manager/resource_manager.h>
#include <sx/sdk/sx_port.h>

typedef sxd_bulk_cntr_buffer_layout_common_t sx_bulk_cntr_buffer_layout_common_t;
typedef sxd_bulk_cntr_buffer_layout_flow_t sx_bulk_cntr_buffer_layout_flow_t;

typedef struct sx_bulk_cntr_read_key_port {
    sx_bulk_cntr_port_grp_e grp; /**< Counter-set of port counters */
    sx_port_log_id_t        log_port; /**< Port ID */
    union {
        sx_port_prio_id_t       prio_id; /**< Priority ID (in use only when grp is SX_BULK_PORT_CNTR_GRP_PRIO_E) */
        sx_port_tc_id_t         tc_id; /**< TC ID (in use only when grp is SX_BULK_PORT_CNTR_GRP_TC_E) */
        sx_cos_priority_group_t prio_group; /**< Priority group (in use only when grp is SX_BULK_PORT_CNTR_GRP_BUFF_E) */
    } grp_ex_param;
} sx_bulk_cntr_read_key_port_t;

typedef struct sx_bulk_cntr_read_key_flow {
    sx_flow_counter_id_t cntr_id; /**< Flow counter ID */
} sx_bulk_cntr_read_key_flow_t;

typedef struct sx_bulk_cntr_read_key {
    sx_bulk_cntr_key_type_e type; /**< Type of counter to get */
    union {
        sx_bulk_cntr_read_key_port_t port_key; /**< Port counter key */
        sx_bulk_cntr_read_key_flow_t flow_key; /**< Flow counter key */
    } key;
} sx_bulk_cntr_read_key_t;

typedef struct sx_bulk_cntr_data {
    union {
        union {
            const sx_port_cntr_ieee_802_dot_3_t          *port_cntr_ieee_802_p; /**< IEEE 802.3 counters entry */
            const sx_port_cntr_rfc_2863_t                *port_cntr_rfc_2863_p; /**< RFC 2863 counters entry */
            const sx_port_cntr_rfc_2819_t                *port_cntr_rfc_2819_p; /**< RFC 2819 counters entry */
            const sx_port_cntr_rfc_3635_t                *port_cntr_rfc_3635_p; /**< RFC 3635 counters entry */
            const sx_port_cntr_prio_t                    *port_cntr_prio_p; /**< Priority counters entry */
            const sx_port_traffic_cntr_t                 *port_cntr_tc_p; /**< Per TC counters */
            const sx_port_cntr_buff_t                    *port_cntr_buff_p; /**< Buffer counters entry */
            const sx_port_cntr_perf_t                    *port_cntr_perf_p; /**< Performance counters entry */
            const sx_port_cntr_discard_t                 *port_cntr_discard_p; /**< Discard counters entry */
            const sx_port_cntr_phy_layer_t               *port_cntr_phy_p; /**< Phy layer counters entry */
            const sx_port_cntr_phy_layer_statistics_t    *port_cntr_phy_stats_p; /**< Phy layer stats counters entry */
            const sx_port_cntr_phy_layer_internal_link_t *port_cntr_phy_int_link_p; /**< Phy layer internal link counters entry */
        } port_counters;
        union {
            const sx_flow_counter_set_t *flow_cntr_p; /**< Flow counter */
        } flow_counters;
    } data;
} sx_bulk_cntr_data_t;

#endif /* ifndef __SX_BULK_COUNTER_H__ */
