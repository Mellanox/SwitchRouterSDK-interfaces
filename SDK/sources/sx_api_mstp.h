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

#ifndef __SX_API_MSTP_H__
#define __SX_API_MSTP_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of MSTP module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - MSTP module verbosity level
 * @param[in] api_verbosity_level      - MSTP API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_mstp_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/**
 *  This API gets the log verbosity level of MSTP module.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] verbosity_target          - Get verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - MSTP module verbosity level
 * @param[out] api_verbosity_level_p    - MSTP API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_mstp_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API sets the switch STP activation mode (RSTP/MSTP/PVRST) on the SDK. As a result, the mapping between
 * instance(s) to VLAN(s) is deleted.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] swid    - Switch ID
 * @param[in] mode    - STP activation mode
 *                      Can take any of the following values:
 *                      SX_MSTP_MODE_MSTP (default)
 *                      SX_MSTP_MODE_RSTP
 *                      SX_MSTP_MODE_PVRST
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 */
sx_status_t sx_api_mstp_mode_set(const sx_api_handle_t handle,
                                 const sx_swid_t       swid,
                                 const sx_mstp_mode_t  mode);

/**
 * This API retrieves the switch STP activation state (RSTP/MSTP/PVRST) from the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] swid    - Switch ID
 * @param[out] mode_p - MSTP activation state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_mstp_mode_get(const sx_api_handle_t handle,
                                 const sx_swid_t       swid,
                                 sx_mstp_mode_t       *mode_p);

/**
 * This API adds/deletes an MSTP instance to/from the switch in the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] cmd     - ADD/DELETE
 * @param[in] swid    - Switch ID
 * @param[in] inst_id - MSTP instance ID to add/delete (range is <1- 1024>)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_CMD_UNPERMITTED if using it not in MSTP mode
 */
sx_status_t sx_api_mstp_inst_set(const sx_api_handle_t   handle,
                                 const sx_access_cmd_t   cmd,
                                 const sx_swid_t         swid,
                                 const sx_mstp_inst_id_t inst_id);

/**
 * This API gets a list of MSTP instances. If the command is GET and inst_list_p is NULL, this API will only return the count.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] cmd            - GET/GET_FIRST/GET_NEXT
 * @param[in] swid           - Switch ID
 * @param[in] inst_key       - MSTP instance ID, used only for GET_NEXT
 * @param[in] inst_filter_p  - Filter used on the list: VLAN-ID
 * @param[out] inst_list_p   - Pointer to list of instances
 * @param[in,out] inst_cnt_p - [in] number of instances to retrieve (max: 1024)/[out] number of instances retrieved successfully
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_CMD_UNPERMITTED if using it not in MSTP mode
 */
sx_status_t sx_api_mstp_inst_iter_get(const sx_api_handle_t        handle,
                                      const sx_access_cmd_t        cmd,
                                      const sx_swid_t              swid,
                                      const sx_mstp_inst_id_t      inst_key,
                                      const sx_mstp_inst_filter_t *inst_filter_p,
                                      sx_mstp_inst_id_t           *inst_list_p,
                                      uint32_t                    *inst_cnt_p);

/**
 * This API adds/deletes a mapping between a list of VLANs to/from the MSTP instance in the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - ADD/DELETE
 * @param[in] swid        - Switch ID
 * @param[in] inst_id     - MSTP instance ID (range is <1-1024>)
 * @param[in] vlan_list_p - List of VLANs to map/unmap
 * @param[in] vlan_cnt    - Number of VLANs to map/unmap (range is <1-4094>)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_CMD_UNPERMITTED if using it not in MSTP mode
 */
sx_status_t sx_api_mstp_inst_vlan_list_set(const sx_api_handle_t   handle,
                                           const sx_access_cmd_t   cmd,
                                           const sx_swid_t         swid,
                                           const sx_mstp_inst_id_t inst_id,
                                           const sx_vlan_id_t     *vlan_list_p,
                                           const uint32_t          vlan_cnt);

/**
 * This API retrieves a list of VLANs in the MSTP instance from the SDK.
 * If the output list (array) is NULL, only the number of VLANs is retrieved.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] swid           - Switch ID
 * @param[in] inst_id        - MSTP instance ID (range is <1-1024>)
 * @param[out] vlan_list_p   - VLANs array
 * @param[in,out] vlan_cnt_p - [in] size of VLANs array (range is <1-4094>)/[out] number of VLANs retrieved successfully
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_CMD_UNPERMITTED if using it not in MSTP mode
 */
sx_status_t sx_api_mstp_inst_vlan_list_get(const sx_api_handle_t   handle,
                                           const sx_swid_t         swid,
                                           const sx_mstp_inst_id_t inst_id,
                                           sx_vlan_id_t           *vlan_list_p,
                                           uint32_t               *vlan_cnt_p);

/**
 * This API sets the MSTP port state for a given instance in the SDK.
 * In PVRST mode, instance ID equals to VLAN ID. (In .1D mode instance ID equals to bridge ID.)
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] swid       - Switch ID
 * @param[in] inst_id    - MSTP Instance ID (range is <1-1024>)
 * @param[in] log_port   - Logical Port ID (whose STP state to set)
 * @param[in] port_state - MSTP Port State
 *                         Can take any of the following values:
 *                         SX_MSTP_INST_PORT_STATE_DISCARDING
 *                         SX_MSTP_INST_PORT_STATE_LEARNING
 *                         SX_MSTP_INST_PORT_STATE_FORWARDING
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 */
sx_status_t sx_api_mstp_inst_port_state_set(const sx_api_handle_t           handle,
                                            const sx_swid_t                 swid,
                                            const sx_mstp_inst_id_t         inst_id,
                                            const sx_port_log_id_t          log_port,
                                            const sx_mstp_inst_port_state_t port_state);

/**
 * This API retrieves the MSTP port state for a given instance from the SDK.
 * In PVRST mode, instance ID equals to VLAN ID. (In .1D mode instance ID equals to bridge ID.)
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] swid          - Switch ID
 * @param[in] inst_id       - MSTP instance ID (range is <1-1024>)
 * @param[in] log_port      - Logical port ID (whose STP state to retrieve)
 * @param[out] port_state_p - MSTP port state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_mstp_inst_port_state_get(const sx_api_handle_t      handle,
                                            const sx_swid_t            swid,
                                            const sx_mstp_inst_id_t    inst_id,
                                            const sx_port_log_id_t     log_port,
                                            sx_mstp_inst_port_state_t *port_state_p);

/**
 * This API sets the RSTP port state in the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] log_port   - Logical port ID
 * @param[in] port_state - MSTP Port state
 *                         Can take any of the following values:
 *                         SX_MSTP_INST_PORT_STATE_DISCARDING
 *                         SX_MSTP_INST_PORT_STATE_LEARNING,
 *                         SX_MSTP_INST_PORT_STATE_FORWARDING
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 */
sx_status_t sx_api_rstp_port_state_set(const sx_api_handle_t           handle,
                                       const sx_port_log_id_t          log_port,
                                       const sx_mstp_inst_port_state_t port_state);

/**
 * This API retrieves the RSTP port state from the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical Port ID
 * @param[out] port_state_p - MSTP Port State
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_rstp_port_state_get(const sx_api_handle_t      handle,
                                       const sx_port_log_id_t     log_port,
                                       sx_mstp_inst_port_state_t *port_state_p);

/**
 * This API excludes a port from STP and sets forwarding state to all of its VLANs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical Port ID
 * @param[in] state         - Excluded state (NORMAL/FORWARD)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_mstp_exclude_port_state_set(const sx_api_handle_t              handle,
                                               const sx_port_log_id_t             log_port,
                                               const sx_mstp_exclude_port_state_t port_state);

/**
 * This API retrieves exclude state for a port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical Port ID
 * @param[out] state_p      - Excluded state (NORMAL/FORWARD)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_mstp_exclude_port_state_get(const sx_api_handle_t         handle,
                                               const sx_port_log_id_t        log_port,
                                               sx_mstp_exclude_port_state_t *port_state_p);

#endif /* __SX_API_MSTP_H__ */
