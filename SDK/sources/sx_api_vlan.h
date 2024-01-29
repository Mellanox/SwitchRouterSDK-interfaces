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

#ifndef __SX_API_VLAN_H__
#define __SX_API_VLAN_H__

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
 * This function sets the log verbosity level of VLAN module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - VLAN module verbosity level
 * @param[in] api_verbosity_level      - VLAN API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_vlan_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of VLAN module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - VLAN module verbosity level
 * @param[out] api_verbosity_level_p    - VLAN API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_vlan_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API sets VLAN member ports.
 *
 * When using ADD or DELETE command, vlan_port_list_p should be set with entries
 * of logical port number and the egress filter mode (tagged/untagged/priority tagged).
 * When using DELETE_ALL command, port_cnt = 0 and vlan_port_list_p = NULL are applicable.
 *
 * Note: This function is only valid when in 802.1Q bridge mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - ADD/DELETE/DELETE_ALL
 * @param[in] swid              - Virtual switch partition ID
 * @param[in] vid               - VLAN ID
 * @param[in] vlan_port_list_p  - An array of port list structure
 * @param[in] port_cnt          - Number of ports in a port list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occur
 * @return SX_STATUS_NO_RESOURCES if the pool cannot provide object
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_ports_set(const sx_api_handle_t  handle,
                                  const sx_access_cmd_t  cmd,
                                  const sx_swid_t        swid,
                                  const sx_vid_t         vid,
                                  const sx_vlan_ports_t *vlan_port_list_p,
                                  const uint32_t         port_cnt);

/**
 * This API retrieves the VLAN member ports.
 *
 * Note: If port_cnt_p is set as less than the actual number of ports, the first port_cnt_p elements in the array and a successful result
 *   are returned as the output.
 * Note: This function is only valid when in 802.1Q bridge mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] swid                 - Virtual switch partition ID
 * @param[in] vid                  - VLAN ID
 * @param[in,out] vlan_port_list_p - A pointer to array of VLAN port list structure. If it is NULL, the port_cnt_p variable is
 *                                   filled out with numbers of ports that could be retrieved. If the pointer is valid, VLAN ports
 *                                   are placed there and port_cnt_p takes actual number ports in array.
 * @param[in,out] port_cnt_p       - Number of ports in a list that you want to retrieve
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occur
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_CMD_UNSUPPORTED if 802.1D mode is enabled
 */
sx_status_t sx_api_vlan_ports_get(const sx_api_handle_t handle,
                                  const sx_swid_t       swid,
                                  const sx_vid_t        vid,
                                  sx_vlan_ports_t      *vlan_port_list_p,
                                  uint32_t             *port_cnt_p);

/**
 * This API sets the VLANs list to a port in a single command.
 *
 * ADD adds list of VLANs to port.
 * DELETE removes a list VLANs from port.
 *
 * Note: This function is only valid when in 802.1Q bridge mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] cmd            - ADD/DELETE
 * @param[in] log_port       - Logical port
 * @param[in] vlan_list_p    - Pointer to a VLANs list
 * @param[in] vlan_cnt       - Size of VLANs list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occur
 * @return SX_STATUS_NO_RESOURCES if the pool cannot provide object
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_multi_vlan_set(const sx_api_handle_t  handle,
                                            const sx_access_cmd_t  cmd,
                                            const sx_port_log_id_t log_port,
                                            const sx_port_vlans_t *vlan_list_p,
                                            const uint32_t         vlan_cnt);

/**
 * This API sets the priority tagged attribute per port.
 *
 * Note: This API supports port profile.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port              - Logical port
 * @param[in] untagged_prio_state   - Untagged packets are sent priority-tagged or not
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occur
 * @return SX_STATUS_NO_RESOURCES if the pool cannot provide object
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_prio_tagged_set(const sx_api_handle_t          handle,
                                             const sx_port_log_id_t         log_port,
                                             const sx_untagged_prio_state_t untagged_prio_state);

/**
 * This API retrieves the priority tagged attribute per port.
 *
 * Note: This API supports port profile.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] log_port                  - Logical port
 * @param[out] untagged_prio_state_p    - Untagged packets are sent priority-tagged or not
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_prio_tagged_get(const sx_api_handle_t     handle,
                                             const sx_port_log_id_t    log_port,
                                             sx_untagged_prio_state_t *untagged_prio_state_p);

/**
 * This API enables/disables ingress VLAN filtering on a port. The VLAN membership is defined in sx_vlan_ports_set API.
 *
 * This function is only valid when in 802.1Q bridge mode.
 *
 * Note: This API supports port profile.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 *  @param[in] handle              - SX-API handle
 *  @param[in] log_port            - Logical port number
 *  @param[in] ingress_filter_mode - Port ingress VLAN filter mode (enable/disable)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported access command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occur
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_ingr_filter_set(const sx_api_handle_t       handle,
                                             const sx_port_log_id_t      log_port,
                                             const sx_ingr_filter_mode_t ingress_filter_mode);

/**
 * This API retrieves ingress VLAN filtering on a port.
 *
 * Note: This function is only valid when in 802.1Q bridge mode.
 * Note: This API supports port profile.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 *  @param[in] handle                  - SX-API handle
 *  @param[in] log_port                - Logical port number
 *  @param[out] ingress_filter_state_p - Pointer to port ingress VLAN filter state (enable/disable)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_CMD_UNSUPPORTED if 802.1D mode is enabled
 */
sx_status_t sx_api_vlan_port_ingr_filter_get(const sx_api_handle_t  handle,
                                             const sx_port_log_id_t log_port,
                                             sx_ingr_filter_mode_t *ingress_filter_mode_p);

/**
 * This API sets a port's default VLAN ID. The PVID is set to untagged packets that ingress on the port.
 *
 * Note: When the PVID is deleted from the port, it is assigned with the default VLAN ID.
 * Note: This API supports port profile.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] cmd      - ADD/DELETE
 * @param[in] log_port - Logical port number
 * @param[in] pvid     - Port VLAN ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_pvid_set(const sx_api_handle_t  handle,
                                      const sx_access_cmd_t  cmd,
                                      const sx_port_log_id_t log_port,
                                      const sx_vid_t         pvid);

/**
 * This API retrieves a port's default VLAN ID.
 *
 * Note: This API supports port profile.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Logical port number
 * @param[out] pvid_p  - Port VLAN ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_pvid_get(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      sx_vid_t              *pvid_p);

/**
 * This API sets a port's accepted frame types.
 *
 * Note: By default, all ports are configured to accept all frame types.
 * Note: Priority tagged packets are considered as untagged packets.
 * Note: This API supports port profile.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] log_port           - Logical port number
 * @param[in] accptd_frm_types_p - A pointer to the following values: allow_tagged, allow_untagged, allow_prio_tagged
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_accptd_frm_types_set(const sx_api_handle_t        handle,
                                                  const sx_port_log_id_t       log_port,
                                                  const sx_vlan_frame_types_t *accptd_frm_types_p);

/**
 * This API retrieves a port's accepted frame types.
 *
 * Note: This API supports port profile.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] log_port            - Logical port number
 * @param[out] accptd_frm_types_p - A pointer the following values: allow_tagged, allow_untagged, allow_prio_tagged
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_accptd_frm_types_get(const sx_api_handle_t  handle,
                                                  const sx_port_log_id_t log_port,
                                                  sx_vlan_frame_types_t *accptd_frm_types_p);

/**
 * This API sets the virtual switch's default VLAN ID. This VID is set by default as the PVID of all switch ports. If not
 * called, the default VID for all virtual switches is 1.
 * Note: This API will not affect a PVID that was explicitly SET to a port (using "sx_api_vlan_port_pvid_set")
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid   - Virtual switch partition ID
 * @param[in] vid    - Switch default VLAN ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported access command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occur
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_default_vid_set(const sx_api_handle_t handle,
                                        const sx_swid_t       swid,
                                        const sx_vid_t        vid);

/**
 * This API gets the virtual switch's default VLAN ID. This VID is set by default as the PVID of all switch ports. If not
 * called, the default VID for all virtual switches is 1.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid   - Virtual switch partition ID
 * @param[out] vid    - Switch default VLAN ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter exceeds range
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occur
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 */
sx_status_t sx_api_vlan_default_vid_get(const sx_api_handle_t handle,
                                        const sx_swid_t       swid,
                                        sx_vid_t             *vid);


/**
 * This API sets Q-in-Q mode of port.
 *
 * Note: This function is only valid when in 802.1Q bridge mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port  - Logical port ID
 * @param[in] qinq_mode - Q-in-Q/802.1Q/802.1AD
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_CMD_UNSUPPORTED if 802.1D mode is enabled
 */
sx_status_t sx_api_vlan_port_qinq_mode_set(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t log_port,
                                           const sx_qinq_mode_t   qinq_mode);

/**
 * This API retrieves Q-in-Q mode of a port.
 *
 * Note: This function is only valid when in 802.1Q bridge mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical port ID
 * @param[out] qinq_mode_p  - Retrieved mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_CMD_UNSUPPORTED if 802.1D mode is enabled
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_qinq_mode_get(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t log_port,
                                           sx_qinq_mode_t        *qinq_mode_p);

/**
 * The API sets which priority should be taken for the outer tag when Q-in-Q is enabled (the port's default priority or the
 * inner tag's priority).
 *
 * Note: This function is only valid when in 802.1Q bridge mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port  - Logical port ID
 * @param[in] prio_mode - Default/inner priority
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_CMD_UNSUPPORTED if 802.1D mode is enabled
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_qinq_outer_prio_mode_set(const sx_api_handle_t           handle,
                                                      const sx_port_log_id_t          log_port,
                                                      const sx_qinq_outer_prio_mode_t prio_mode);

/**
 * This API retrieves port's Q-in-Q outer tag priority mode.
 *
 * Note: This function is only valid when in 802.1Q bridge mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] log_port     - Logical port ID
 * @param[out] prio_mode_p - Retrieved mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_CMD_UNSUPPORTED if 802.1D mode is enabled
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_vlan_port_qinq_outer_prio_mode_get(const sx_api_handle_t      handle,
                                                      const sx_port_log_id_t     log_port,
                                                      sx_qinq_outer_prio_mode_t *prio_mode_p);

/**
 * This API creates .1Q VLANs. If NO_RESOURCES status is returned then the vlan_list_p will contain the VLANs which were not
 * added (number of which is donated by vlan_cnt_p).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - ADD/DELETE
 * @param[in] swid          - Switch partition ID
 * @param[in] vlan_list_p   - A list of .1Q VLANs to add
 * @param[in] vlan_cnt_p    - The size of vlan_list_p array
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if cmd is unsupported in this API
 * @return SX_STATUS_NO_RESOURCES if all the .1Q VLANs have been set
 * @return SX_STATUS_PARAM_ERROR if vlan_list_p is NULL
 */
sx_status_t sx_api_vlan_set(const sx_api_handle_t handle,
                            const sx_access_cmd_t cmd,
                            const sx_swid_t       swid,
                            sx_vlan_id_t         *vlan_list_p,
                            uint32_t             *vlan_cnt_p);

/**
 * This API returns the list of .1Q VLANs added to the SWID.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] swid            - switch partition ID
 * @param[out] vlan_list_p    - A list of .1Q VLANs to add
 * @param[in,out] vlan_cnt_p  - The number of VLANs to return (if vlan_cnt_p==0, only the number of VLANs will be returned
 *                              and the list will remain empty)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if vlan_list_p is NULL
 */
sx_status_t sx_api_vlan_get(const sx_api_handle_t handle,
                            const sx_swid_t       swid,
                            sx_vlan_id_t         *vlan_list_p,
                            uint32_t             *vlan_cnt_p);

/**
 * This API sets FID attributes.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] vid             - VLAN/FID to set
 * @param[in] vlan_attrib_p   - Structure containing the attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if vlan_attrib_p is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND if VLAN does not exist
 */
sx_status_t sx_api_vlan_attrib_set(const sx_api_handle_t   handle,
                                   sx_vlan_id_t            vid,
                                   const sx_vlan_attrib_t *vlan_attrib_p);


/**
 * This API returns FID attributes.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] vid            - VLAN/FID to get
 * @param[in] vlan_attrib_p  - Structure containing the returned attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if vlan_attrib_p is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND if VLAN does not exist
 */
sx_status_t sx_api_vlan_attrib_get(const sx_api_handle_t handle,
                                   sx_vlan_id_t          vid,
                                   sx_vlan_attrib_t     *vlan_attrib_p);


#endif /* __SX_API_VLAN_H__ */
