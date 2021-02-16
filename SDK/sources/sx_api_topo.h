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

#ifndef __SX_API_TOPO_H__
#define __SX_API_TOPO_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_api_init.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of TOPOLOGY MODULE
 * Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
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
 * This function gets the log verbosity level of TOPOLOGY MODULE
 * Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
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
 *  This function sets the devices. Each device that is
 *  introduced to the system must be configured through the topology
 *  library. This API maintains a database that is used by other
 *  libraries to receive a device irrelevant for configuration
 *
 *  Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle -   SX-API handle
 * @param[in] cmd -
 *  SX_ACCESS_CMD_ADD - Adds new device to topo lib.
 *  SX_ACCESS_CMD_DELETE - Deletes the device from topo lib.
 *  Note that the device should be removed from all forwarding tree
 *  associated with unicast/multicast/flood_tree_hndl_arr prior to
 *  that operation change.
 *  SX_ACCESS_CMD_READY - device is made ready when traffic can be routed
 *  from/to /via this device.  please note that trees(unicast/multicast/flood_ must
 *  be configured with the new device
 * @param[in] dev_info  - pointer to device info to set
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
 *  This function prints device topology information into the
 *  debug output
 *  Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle -   SX-API handle
 * @param[in] cmd - GET_ALL - dump the topo tree
 * @param[in] dump_info  - pointer to dump info
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
 *  This function prints topology tree to the debug output
 *  Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle -   SX-API handle
 * @param[in] cmd - GET_ALL - dump the topo tree
 * @param[in] dump_info  - pointer to dump info
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
 *  This function sets forwarding tree.
 *  Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle -  SX-API handle
 * @param[in] cmd -
 * SX_ACCESS_CMD_ADD  - Adds a new tree
 * SX_ACCESS_CMD_EDIT - Add leaf to existing tree
 * SX_ACCESS_CMD_DELETE - Removes a  tree
 * @param[in] sx_topo_lib_tree_t - pointer to tree
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
 *  This function reload balance unicast traffic
 *  Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle - SX-API handle
 *  [in] tree - all ports that forward traffic via "tree" should
 *  replace (chose another tree) possible value specific tree
 *  handle/ALL_TREE
 *  [in] log_port- rebalance this port possible value
 *  port/ALL_PORT
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_topo_unicast_reload_balance(IN sx_api_handle_t  handle,
                                               IN sx_tree_hndl_t   tree,
                                               IN sx_port_log_id_t log_port);


/**
 * This function sets multicast tree group.
 * Multicast tree group is a group  of devices that tag ingress packet
 * with the  same MID (multicast ID)
 * Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle -   SX-API handle
 * @param[in] cmd -
 * SX_ACCESS_CMD_CREATE - create a new multicast tree group
 * SX_ACCESS_CMD_DELETE - delete multicast tree group. The tree group
 * should be empty before deletion.
 * @param[out] mc_tree_group_id -
 *                       Out: Pointer to multicast group id.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_topo_mc_tree_group_set(IN sx_api_handle_t            handle,
                                          IN sx_access_cmd_t            cmd,
                                          INOUT sx_mc_tree_group_id_t * mc_tree_group_id);


/**
 * This function  add/remove devices from  tree group.
 * Tree group is a group of devices that tag ingress packet
 * with the same MID (multicast ID)
 * Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle -   SX-API handle
 * @param[in] cmd -
 * @param[in] old_tree_group -
 * @param[in] new_tree_group -
 * @param[in] dev_id
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
 * This function add/remove forwarding tree form mc tree group
 * Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle -   SX-API handle
 * @param[in] cmd - SX_ACCESS_CMD_CREATE, SX_ACCESS_CMD_DELETE
 *
 * @param[in]  tree_group - multicast tree group
 * @param[in]  tree forwarding tree
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
 *  This function reload balance multicast  traffic
 *  Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle - SX-API handle
 *  [in] tree - reload balance all multicast that forward
 *  traffic via mc_tree_group_id value.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_topo_mc_reload_balance(IN sx_api_handle_t         handle,
                                          IN sx_mc_tree_group_hndl_t mc_tree_group_id);


#endif /* __SX_API_TOPO_H__ */
