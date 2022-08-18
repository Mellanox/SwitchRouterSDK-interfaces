/*
 * Copyright (C) 2014-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_BRIDGE_H__
#define __SX_API_BRIDGE_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  Local Defines
 ***********************************************/

/************************************************
 *  Local Macros
 ***********************************************/

/************************************************
 *  Local Type definitions
 ***********************************************/

/************************************************
 *  Defines
 ***********************************************/

/************************************************
 *  Macros
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

/************************************************
 *  Global variables
 ***********************************************/

/************************************************
 *  Function declarations
 ***********************************************/

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of the BRIDGE module.
 *
 * Supported devices: Spectrum , Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - BRIDGE module verbosity level
 * @param[in] api_verbosity_level      - BRIDGE API verbosity level
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    An input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_bridge_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  const sx_verbosity_level_t      module_verbosity_level,
                                                  const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of the BRIDGE module.
 *
 * Supported devices: Spectrum , Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - BRIDGE module verbosity level
 * @param[out] api_verbosity_level_p    - BRIDGE API verbosity level
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_bridge_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  sx_verbosity_level_t           *module_verbosity_level_p,
                                                  sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This function is used to create/destroy a bridge.
 *
 * Note: This function is only supported in 802.1D mode.
 *
 * Supported devices: Spectrum , Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] cmd            - CREATE/DESTROY
 * @param[out] bridge_id_p   - Bridge ID
 */
sx_status_t sx_api_bridge_set(const sx_api_handle_t handle,
                              const sx_access_cmd_t cmd,
                              sx_bridge_id_t       *bridge_id_p);

/**
 *  This function retrieves a list of one or more Bridge IDs. This function is not supported in 802.1Q mode.
 *  The following use case scenarios apply with different input parameters X = don't-care
 *   - 1) cmd = SX_ACCESS_CMD_GET, bridge_id = X, bridge_id_list = X, bridge_id_cnt = 0:
 *        In this case the API will return the total number of bridge IDs in the internal DB.
 *
 *   - 2) cmd = SX_ACCESS_CMD_GET, bridge_id = valid/invalid, bridge_id_list = valid, bridge_id_cnt = 1:
 *        In this case the API will check if the specified bridge_id exists.
 *        If it does, the bridge ID will be returned in the bridge_id_list along with a bridge_id_cnt of 1.
 *        If the bridge ID does not exist, an empty list will be returned with bridge_id_cnt = 0.
 *        A non-NULL bridge_id_list pointer must be provided in this case.
 *
 *   - 3) cmd = SX_ACCESS_CMD_GET, bridge_id = valid/invalid, bridge_id_list = valid, bridge_id_cnt > 1:
 *        A bridge_id_cnt > 1 will be treated as a bridge_id_cnt of 1 and the behavior will be same as the earlier GET use cases.
 *
 *   - 4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, bridge_id = X, bridge_id_list = NULL, bridge_id_cnt = 0:
 *        A zero bridge_id_cnt and an empty bridge_id_list will be returned.
 *
 *   - 5) cmd = SX_ACCESS_CMD_GET_FIRST, bridge_id = X, bridge_id_list = valid, bridge_id_cnt > 0:
 *        In this case the API will return the first bridge_id_cnt bridge IDs starting from the head of the database.
 *        The total number of elements fetched will be returned as bridge_id_cnt. Note: returned bridge_id_cnt may
 *        be less than or equal to the requested bridge_id_cnt. The input bridge ID is ignored in this case.
 *        A non-NULL bridge_id_list pointer must be provided in this case.
 *
 *   - 6) cmd = SX_ACCESS_CMD_GETNEXT, bridge_id = valid/invalid, bridge_id_list = valid, bridge_id_cnt > 0:
 *        In this case the API will return the next set of bridge IDs starting from  the next bridge ID after
 *        the specified bridge ID. The total number of elements fetched will be returned as the bridge_id_cnt.
 *
 *        Note: returned bridge_id_cnt may be less than or equal to the requested bridge_id_cnt.
 *        If no valid next bridge ID exists in the db, an empty list will be returned.
 *        A non-NULL bridge_id_list pointer must be provided in this case.
 *
 *
 * Supported devices: Spectrum , Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle               - SX-API handle
 * @param [in] cmd                 - GET/GET_FIRST/GET_NEXT
 * @param[in] bridge_id            - Bridge ID
 * @param [in] filter_p            - Specify a filter parameter (not supported yet)
 * @param [out] bridge_id_list_p   - Return list of bridge IDs
 * @param [in,out] bridge_id_cnt_p - [in] number of bridge IDs to get/[out] number of bridge IDs returned
 *
 *
 * @return SX_STATUS_SUCCESS          Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE   NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED  Command is not supported
 * @return SX_STATUS_PARAM_NULL       Parameter is NULL
 * @return SX_STATUS_ERROR            General error
 */
sx_status_t sx_api_bridge_iter_get(const sx_api_handle_t     handle,
                                   const sx_access_cmd_t     cmd,
                                   const sx_bridge_id_t      bridge_id,
                                   const sx_bridge_filter_t *filter_p,
                                   sx_bridge_id_t           *bridge_id_list_p,
                                   uint32_t                 *bridge_id_cnt_p);

/**
 *
 *  This function is used to add/delete a virtual port to/from a bridge.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - ADD/DELETE/DELETE_ALL
 * @param[in] bridge_id   - Bridge ID
 * @param[in] log_port    - Logical virtual port ID
 *
 * @return SX_STATUS_SUCCESS           Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR       Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND   Bridge is not found in DB
 * @return SX_STATUS_ERROR             Unexpected behavior
 */
sx_status_t sx_api_bridge_vport_set(const sx_api_handle_t  handle,
                                    const sx_access_cmd_t  cmd,
                                    const sx_bridge_id_t   bridge_id,
                                    const sx_port_log_id_t log_port);

/**
 *  This function is used to get a list of all virtual ports associated with a bridge.
 *  When bridge_vport_cnt_p == 0, the number of existing entries will be returned.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] bridge_id                - Bridge ID
 * @param[out] bridge_vport_list_p     - Pointer to a sx_port_log_id_t list
 * @param[in/out] bridge_vport_cnt_p   - Size of the bridge_vport_list
 *
 * @return SX_STATUS_SUCCESS          Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR      Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND  Bridge is not found in DB
 * @return SX_STATUS_ERROR            Unexpected behavior
 */
sx_status_t sx_api_bridge_vport_get(const sx_api_handle_t handle,
                                    const sx_bridge_id_t  bridge_id,
                                    sx_port_log_id_t     *bridge_vport_list_p,
                                    uint32_t             *bridge_vport_cnt_p);


/**
 * This function is used to add/delete virtual ports from log_port_list list to the corresponding bridge from bridge_id_list.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE/DELETE_ALL
 * @param[in] bridge_id_list - bridge_id list
 * @param[in] log_port_list - logical virtual port ID list
 * @param[in] list_cnt - list counter.
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR      Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND  Bridge is not found in DB
 * @return SX_STATUS_ERROR            Unexpected behavior
 */
sx_status_t sx_api_bridge_vport_multi_set(const sx_api_handle_t   handle,
                                          const sx_access_cmd_t   cmd,
                                          const sx_bridge_id_t   *bridge_id_list,
                                          const sx_port_log_id_t *log_port_list,
                                          uint32_t                list_cnt);

/**
 *
 *  This function is used to bind/unbind a flow counter to a bridge.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND/UNBIND
 * @param[in] bridge_id - bridge_id.
 * @param[in] flow_counter_id - flow counter id to bind
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR      Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND  Bridge is not found in DB
 * @return SX_STATUS_ERROR            Unexpected behavior
 */
sx_status_t sx_api_bridge_counter_bind_set(const sx_api_handle_t      handle,
                                           const sx_access_cmd_t      cmd,
                                           const sx_bridge_id_t       bridge_id,
                                           const sx_flow_counter_id_t flow_counter_id);

/**
 *
 * This function is used to get the flow counter bound to the bridge. If there is no counter bound to the bridge, the API
 * will return SX_STATUS_ENTRY_NOT_FOUND and  flow_counter_id_p will be set to SX_FLOW_COUNTER_ID_INVALID.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] bridge_id - bridge_id.
 * @param[out] flow_counter_id_p - bound counter id
 *
 * @return SX_STATUS_SUCCESS          Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR      Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND  Bridge is not found in DB or no counter is bound
 * @return SX_STATUS_ERROR            Unexpected behavior
 */
sx_status_t sx_api_bridge_counter_bind_get(const sx_api_handle_t handle,
                                           const sx_bridge_id_t  bridge_id,
                                           sx_flow_counter_id_t* flow_counter_id_p);

/**
 * This API binds/un-binds a counter to/from a tunnel mapped to the bridge.
 *
 * For ENCAP_UC and ENCAP_MC counters, this operation can be performed only when FDB does not contain any entries
 * for tunnel in fid.  When Lazy Delete mode is enabled, flow counters will be automatically unbounded once the deletion
 * of the related VNI mapping is completed and VNI mapping delete notification is sent.
 * Counters can be bound only if the bridge/VLAN to tunnel mapping is configured.
 * Note: Flex tunnels are not supported.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - SX_ACCESS_CMD_BIND/SX_ACCESS_CMD_UNBIND
 * @param[in] bridge_id         - bridge_id/vlan_id on which tunnel mapped
 * @param[in] attr_p            - Counter attributes (type, tunnel_id)
 * @param[in] counter_d         - Flow counter ID to be bound
 *
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Any input parameters is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED      Command unsupported in this API
 * @return SX_STATUS_ENTRY_NOT_FOUND      Tunnel or tunnel mapping does not exist
 * @return SX_STATUS_ENTRY_ALREADY_BOUND  Counter is already bound
 * @return SX_STATUS_ENTRY_NOT_BOUND      Counter is not bound
 *
 */
sx_status_t sx_api_bridge_tunnel_counter_bind_set(const sx_api_handle_t                  handle,
                                                  const sx_access_cmd_t                  cmd,
                                                  const sx_bridge_id_t                   bridge_id,
                                                  const sx_bridge_tunnel_counter_attr_t *counter_attr_p,
                                                  const sx_flow_counter_id_t             counter_id);

/**
 *
 *  This API gets the bound flow counter ID of the tunnel mapped to the bridge.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] bridge_id         - bridge_id/vlan_id on which tunnel is mapped
 * @param[in] attr_p            - Counter attributes (type, tunnel_id)
 * @param[out] counter_id_p     - Pointer to flow counter ID (returns bound counter_id)
 *
 * @return SX_STATUS_SUCCESS          Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR      Any input parameters is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND  Tunnel does not exist or mapping is not found
 * @return SX_STATUS_ENTRY_NOT_BOUND  Counter is not bound
 *
 */
sx_status_t sx_api_bridge_tunnel_counter_bind_get(const sx_api_handle_t                  handle,
                                                  const sx_bridge_id_t                   bridge_id,
                                                  const sx_bridge_tunnel_counter_attr_t *counter_attr_p,
                                                  sx_flow_counter_id_t                  *counter_id_p);

#endif /* __SX_API_BRIDGE_H__ */
