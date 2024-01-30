/*
 * Copyright (C) 2014-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_TOPO_H__
#define __SX_API_TOPO_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_api_init.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of TOPOLOGY module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - TOPOLOGY module verbosity level
 * @param[in] api_verbosity_level      - TOPOLOGY API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_topo_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of TOPOLOGY module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - TOPOLOGY module verbosity level
 * @param[out] api_verbosity_level_p    - TOPOLOGY API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_topo_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API sets the devices. Each device that is introduced to the system must be configured through the topology library.
 * This API maintains a database that is used by other libraries to receive a device irrelevant for configuration.
 *
 * ADD adds a new device to topology library.
 * DELETE deletes the device from topology library.
 *      Note: The device should be removed from all forwarding trees associated with unicast/multicast/flood_tree_hndl_arr prior
 *      to that operation change.
 * READY device is declared ready when traffic can be routed from/to /via this device.
 *      Note:Trees (unicast/multicast/flood) must be configured with the new device.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE/READY
 * @param[in] dev_info  - Pointer to device information to set
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_PARAM_NULL if null pointer is given
 */
sx_status_t sx_api_topo_device_set(IN sx_api_handle_t         handle,
                                   IN sx_access_cmd_t         cmd,
                                   IN sx_topolib_dev_info_t * dev_info);

/**
 * This API prints device topology information into the debug output.
 *
 * GET_ALL dumps the topology tree.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - GET_ALL
 * @param[in] dump_info  - Pointer to dump information
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_PARAM_NULL if null parameter is given
 */
sx_status_t sx_api_topo_device_dump(sx_api_handle_t              handle,
                                    sx_access_cmd_t              cmd,
                                    sx_topo_lib_dump_db_info_t * dump_info);

/**
 * This API prints topology tree to the debug output.
 *
 * GET_ALL dumps the topology tree.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - GET_ALL
 * @param[in] dump_info  - Pointer to dump information
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_PARAM_NULL if null pointer is given
 */
sx_status_t sx_api_topo_tree_dump(sx_api_handle_t             handle,
                                  sx_access_cmd_t             cmd,
                                  sx_topo_lib_dump_db_info_t* dump_info);

/**
 * This API sets a forwarding tree.
 *
 * ADD adds a new tree.
 * EDIT adds leaf to an existing tree.
 * DELETE removes a tree.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle -  SX-API handle
 * @param[in] cmd - ADD/EDIT/DELETE
 * @param[in] sx_topo_lib_tree_t - Pointer to tree
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_CMD_UNSUPPORTED if invalid access command used
 * @return SX_STATUS_MEMORY_ERROR if there's not enough memory
 *  */
sx_status_t sx_api_topo_tree_set(IN sx_api_handle_t         handle,
                                 IN sx_access_cmd_t         cmd,
                                 INOUT sx_topo_lib_tree_t * tree);

/**
 * This API triggers load balance for unicast traffic.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] tree     - Specific tree handle/ALL_TREE
 * @param[in] log_port - Logical port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_topo_unicast_reload_balance(IN sx_api_handle_t  handle,
                                               IN sx_tree_hndl_t   tree,
                                               IN sx_port_log_id_t log_port);


/**
 * This API sets a multicast tree group. Multicast tree group is a group of devices that tag ingress packets with the same MID (multicast ID).
 *
 * CREATE creates a new multicast tree group
 * DELETE deletes a multicast tree group (the tree group should be empty before deletion).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle -   SX-API handle
 * @param[in] cmd - CREATE/DELETE
 * @param[out] mc_tree_group_id - [out] pointer to multicast group ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_topo_mc_tree_group_set(IN sx_api_handle_t            handle,
                                          IN sx_access_cmd_t            cmd,
                                          INOUT sx_mc_tree_group_id_t * mc_tree_group_id);


/**
 * This API adds/removes devices from a tree group. A tree group is a group of devices whose tag ingress packet
 * has the same MID (multicast ID).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE
 * @param[in] old_tree_group - Old tree groups
 * @param[in] new_tree_group - New tree groups
 * @param[in] dev_id - Dev ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_topo_mc_tree_group_dev_set(IN sx_api_handle_t         handle,
                                              IN sx_access_cmd_t         cmd,
                                              IN sx_mc_tree_group_hndl_t old_tree_group,
                                              IN sx_mc_tree_group_hndl_t new_tree_group,
                                              IN sx_dev_id_t             dev_id);


/**
 * This API add/remove forwarding tree form a multicast tree group.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE/DELETE
 * @param[in]  tree_group - Multicast tree group
 * @param[in]  tree - Forwarding tree
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_topo_mc_tree_group_tree_set(IN sx_api_handle_t         handle,
                                               IN sx_access_cmd_t         cmd,
                                               IN sx_mc_tree_group_hndl_t tree_group,
                                               IN sx_tree_hndl_t          tree);


/**
 * This API conducts a reload balance of multicast traffic.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle ([in] tree reload balances all multicast that forward traffic via mc_tree_group_id value)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_topo_mc_reload_balance(IN sx_api_handle_t         handle,
                                          IN sx_mc_tree_group_hndl_t mc_tree_group_id);


#endif /* __SX_API_TOPO_H__ */
