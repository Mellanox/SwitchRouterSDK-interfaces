/*
 *  Copyright (C) 2014-2020. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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


#ifndef __SX_API_ROUTER_H__
#define __SX_API_ROUTER_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of ROUTER MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - ROUTER module verbosity level
 * @param[in] api_verbosity_level      - ROUTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_router_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  const sx_verbosity_level_t      module_verbosity_level,
                                                  const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of ROUTER MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - ROUTER module verbosity level
 * @param[out] api_verbosity_level_p    - ROUTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_router_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  sx_verbosity_level_t           *module_verbosity_level_p,
                                                  sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This function sets the ECMP hash configuration parameters.
 * If ecmp_hash_params_p->symmetric_hash is TRUE, then hash(*,A) = hash(A,*)
 * This API will return error once the per port API
 * sx_api_router_ecmp_port_hash_params_set has been called.
 * This API cannot be used along with sx_api_router_ecmp_port_hash_params_set.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] ecmp_hash_param_p - ECMP hash configuration parameters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_ecmp_hash_params_set(const sx_api_handle_t               handle,
                                               const sx_router_ecmp_hash_params_t *ecmp_hash_params_p);

/**
 * This function sets the ECMP hash function configuration parameters on a per port basis.
 *
 * Each element in hash_field_enable_list_p enables a specific layer field to be
 * included in the hash calculation according to the de-facto fields of the
 * parsed packet.
 * Each element in hash_field_list_p represents a different field to
 * be included in the hash calculation, subject to the enables which are given in hash_field_enable_list_p.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                     - SX-API handle.
 * @param[in] cmd                        - SET/ ADD/ DELETE.
 * @param[in] log_port                   - log port ID
 * @param[in] ecmp_hash_params_p         - ECMP hash configuration parameters.
 * @param[in] hash_field_enable_list_p   - Array of enables to be included in the hash calculation (may be NULL if empty)
 * @param[in] hash_field_enable_list_cnt - Number of elements in hash_field_enable_list_p
 * @param[in] hash_field_list_p          - Array of fields to be included in the hash calculation (may be NULL if empty)
 * @param[in] hash_field_list_cnt        - Number of elements in hash_field_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if parameter is incorrectly NULL.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_ecmp_port_hash_params_set(const sx_api_handle_t                     handle,
                                                    const sx_access_cmd_t                     cmd,
                                                    const sx_port_log_id_t                    log_port,
                                                    const sx_router_ecmp_port_hash_params_t  *ecmp_hash_params_p,
                                                    const sx_router_ecmp_hash_field_enable_t *hash_field_enable_list_p,
                                                    const uint32_t                            hash_field_enable_list_cnt,
                                                    const sx_router_ecmp_hash_field_t        *hash_field_list_p,
                                                    const uint32_t                            hash_field_list_cnt);

/**
 *  This function gets the ECMP hash function configuration parameters.
 *  This API is disabled once sx_api_router_ecmp_port_hash_params_set is called.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[out] ecmp_hash_params_p - ECMP hash configuration parameters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_ecmp_hash_params_get(const sx_api_handle_t         handle,
                                               sx_router_ecmp_hash_params_t *ecmp_hash_params_p);

/**
 *  This function gets the ECMP hash function configuration parameters.
 *  if the given number of fields / fields enables is 0, the API will only return number of
 *  fields / enables.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                           - SX-API handle.
 * @param[in] log_port                         - local port
 * @param[out] ecmp_hash_params_p              - ECMP hash configuration parameters.
 * @param[out] hash_field_enable_list_p        - array of enables used in the hash calculation
 * @param[in/out] hash_field_enable_list_cnt_p - number of objects in hash_field_list_p
 * @param[out] hash_field_list_p               - array of fields used in the hash calculation
 * @param[in/out] hash_field_list_cnt_p        - number of objects in hash_field_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_ecmp_port_hash_params_get(const sx_api_handle_t               handle,
                                                    const sx_port_log_id_t              log_port,
                                                    sx_router_ecmp_port_hash_params_t  *ecmp_hash_params_p,
                                                    sx_router_ecmp_hash_field_enable_t *hash_field_enable_list_p,
                                                    uint32_t                           *hash_field_enable_list_cnt_p,
                                                    sx_router_ecmp_hash_field_t        *hash_field_list_p,
                                                    uint32_t                           *hash_field_list_cnt_p);

/**
 * This function Initiates the router module in SDK.
 * The parameter uc_params->ipv4_num requires a value larger than 30.
 * The parameter mc_params->mc_routes->ipv4_num requires a value larger than
 * 30 when the mc_router is enabled.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] general_params_p - general router parameters.
 * @param[in] router_resource_p- router resource parameter.
 *
 * @return SX_STATUS_SUCCESS - if operation completes
 *         successfully.
 * @return SX_STATUS_ALREADY_INITIALIZED - When router is
 *         already initialized.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - When calling with bad
 *         parameters.
 */
sx_status_t sx_api_router_init_set(const sx_api_handle_t              handle,
                                   const sx_router_general_param_t   *general_params_p,
                                   const sx_router_resources_param_t *router_resource_p);


/**
 *
 * This api deinitializes the router block in the sdk.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 *
 * @return SX_STATUS_SUCCESS if operation completes
 *         successfully.
 * @return SX_STATUS_RESOURCE_IN_USE When router is still
 *         active.
 */
sx_status_t sx_api_router_deinit_set(const sx_api_handle_t handle);

/**
 *  This function adds/deletes/edits a virtual router.
 *  The router ID is allocated and returned to the caller when
 *  cmd is ADD, otherwise it is given by the caller. All
 *  interfaces and routes associated with a router must be
 *  deleted before the router can be deleted as well.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE/EDIT.
 * @param[in] router_attr - Router attributes.
 * @param[in,out] vrid - Virtual router ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router was not added.
 * @return SX_STATUS_NO_RESOURCES if there are no resources to
 *         create another router
 * @return SX_STATUS_RESOURCE_IN_USE if router has interfaces or routes.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_set(const sx_api_handle_t         handle,
                              const sx_access_cmd_t         cmd,
                              const sx_router_attributes_t *router_attr,
                              sx_router_id_t               *vrid);

/**
 * This function gets a virtual router information.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] vrid - Virtual Router ID.
 * @param[out] router_attr - Router attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_get(const sx_api_handle_t   handle,
                              const sx_router_id_t    vrid,
                              sx_router_attributes_t *router_attr);

/**
 *  This function gets a list of valid VRIDs.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd    GET/GET_NEXT/GET_FIRST
 * @param[in] vrid_key - Virtual Router ID.
 * @param[in] vrid_filter_p - Filter to use (not supported yet)
 * @param[out] vrid_list_p - pointer to the list of valid VRIDs returned.
 * @param[in,out] vrid_cnt_p [in] number of entries to retrieve (max: 254).; [out] retrieved  number of entries.
 *
 * Input/Output types
 *      - Get first - Get a list of first n entries.  Cmd should be SX_ACCESS_CMD_GET_FIRST and
 *           vrid_cnt_p should be equal to n. key is irrelevant in this case. This cmd returns the
 *           number of entries retrieved as vrid_cnt_p
 *      - Get next - Get n entries after a specified vrid (vrid can be non-existent).
 *           Cmd should be SX_ACCESS_CMD_GETNEXT and vrid_cnt_p should be equal to n.
 *           This cmd returns number of entries retrieved as vrid_cnt_p
 *      - Get - Gets a specific entry. Cmd should be SX_ACCESS_CMD_GET and vrid_cnt_p should be 1.
 *          If the input vrid_cnt_p is 0, then this API returns a count of valid VRIDs as output.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_INVALID_HANDLE if handle in invalid
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_vrid_iter_get(const sx_api_handle_t   handle,
                                        const sx_access_cmd_t   cmd,
                                        const sx_router_id_t    vrid_key,
                                        const sx_vrid_filter_t *vrid_filter_p,
                                        sx_router_id_t         *vrid_list_p,
                                        uint32_t               *vrid_cnt_p);


/**
 *  This function adds/modifies/deletes/delete_all a router
 *  interface. A router interface is associated with L2
 *  interface.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 *  In 802.1D mode, if ifc_p needs to be configured as type=SX_L2_INTERFACE_TYPE_VLAN,
 *  then bridge_id needs to be provided instead of ifc.vlan.vlan.
 *
 *  On Spectrum/Spectrum2/Spectrum3 with command EDIT:
 *   - The only applicable RIF type that can be edited in ifc_p is
 *     SX_L2_INTERFACE_TYPE_PORT_VLAN and the only field that can be
 *     edited for the RIF type is the vlan field.
 *   - The only applicable fields in ifc_attr_p are mtu, multicast_ttl_threshold
 *     and loopback_enable. Other fields shall not  be edited.
 *
 *  On Spectrum/Spectrum2/Spectrum3 with command DELETE/DELETE_ALL:
 *   - All MACs assigned to a specific interface/interfaces will be deleted. This includes
 *      MACs configured by sx_api_router_interface_mac_set()
 *
 *  On Spectrum/Spectrum2/Spectrum3 the mac field in ifc_attr_p,
 *  is made from 38 bits of common base that is fixed and only
 *  the last 10 bits varies from one rif to another
 *
 *  On Spectrum/Spectrum2/Spectrum3 the qos_mode field in
 *  ifc_attr_p is redundant, the global router qos configuration
 *  shall be used instead. The rif must be aligned with the
 *  router global qos mode,that is configured using
 *  sx_api_router_cos_prio_update_enable_set, otherwise
 *  SX_ROUTER_QOS_MODE_NOP shall be set to use the router global
 *  configured qos mode.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/EDIT/DELETE/DELETE ALL.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] ifc_p -  Interface type and parameters .
 * @param[in] ifc_attr_p -Interface attributes.
 * @param[in,out] rif - Router Interface ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_NO_RESOURCES if no interface is available to create.
 * @return SX_STATUS_RESOURCE_IN_USE if router interface has routes.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_set(const sx_api_handle_t              handle,
                                        const sx_access_cmd_t              cmd,
                                        const sx_router_id_t               vrid,
                                        const sx_router_interface_param_t *ifc_p,
                                        const sx_interface_attributes_t   *ifc_attr_p,
                                        sx_router_interface_t             *rif_p);

/**
 * This function gets a router interface information.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 *  When in 802.1D mode, if ifc_p has type SX_L2_INTERFACE_TYPE_VLAN, then
 *  a bridge ID is returned instead of vlan ID in ifc.vlan.vlan.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] rif - Router Interface ID.
 * @param[out] vrid_p - Virtual Router ID.
 * @param[out] ifc_p -  Interface type and parameters .
 * @param[out] ifc_attr_p -Interface attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_get(const sx_api_handle_t        handle,
                                        const sx_router_interface_t  rif,
                                        sx_router_id_t              *vrid_p,
                                        sx_router_interface_param_t *ifc_p,
                                        sx_interface_attributes_t   *ifc_attr_p);
/**
 *  This function returns a list of one or more router interface identifiers.
 *  The following use case scenarios apply with different input parameters
 *  X = don't-care
 *   - 1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, Rif_list = X, Count=0:
 *        In this case the API will return the total number of RIFs in the
 *        Internal db
 *
 *   - 2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, Rif_list =
 *        Valid, Count = 1:
 *        In this case the API will check if the specified key exists. if it does
 *        the key will be returned in the rif_list along with a count of 1.
 *        If the key does not exist an empty list will be returned with count = 0
 *
 *   - 3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = Valid, Rif_list is Valid, Count=1:
 *        In this case the API will check if the specified key exists. if it does exist then,
 *        it will check it against the filter parameter. If the filter matches,
 *        then the key will be returned in the rif_list along with a count of 1.
 *        If the key does not exist or the filter does not match an empty list
 *        will be returned with count = 0
 *
 *   - 4) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = Valid/invalid,
 *        Rif_list is Valid, Count > 1:
 *        A count >1 will be treated as a count of 1 and the behavior will be same
 *        as earlier GET use cases.
 *
 *   - 5) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X,
 *        Rif_list = Null, Count =0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT a zero count
 *        will return an empty list.
 *
 *   - 6) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = valid/invalid, Rif_list =
 *        Valid, Count > 0:
 *        In this case the API will return the first count rifs starting from
 *        the head of the database. The total elements fetched will be returned
 *        as the return count.  Note: return count may be less than or equal to
 *        the requested count. The key is dont-care.
 *        If a filter is specified only those rifs that match the filter will
 *        be returned. A non-Null return rif_list pointer must be provided
 *
 *   - 7) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = valid/invalid,
 *        Rif_list = Valid, Count > 0:
 *        In this case the API will return the next set of rifs starting from
 *        the next valid rif after the specified key. The total elements fetched
 *        will be returned as the return count.  If a filter is specified, then only
 *        those rifs that match the filter will be returned.
 *        Note: return count may be less than or equal to the requested count.
 *        If no valid next rif exists in the db (key = end of list, or invalid
 *        key specified, or key too large), an empty list will be returned.
 *
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param [in] handle           : SX API handle
 * @param [in] cmd              : GET/GET_FIRST/GET_NEXT
 * @param [in] rif_key_p        : specify a rif key
 * @param [in] filter           : specify a filter parameter
 * @param [out] rif_list_p      : return list of rif ids
 * @param [in,out] rif_cnt_p    : [in] number of rifs to get. max 400
 *                              : [out] number of rifs returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if an unexpected NULL parameter was passed.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ERROR general error.
 * @return SX_STATUS_CMD_UNSUPPORTED - if invalid cmd is passed
 * @return SX_STATUS_MODULE_UNINITIALIZED - if router module is uninitialized
 * @return SX_STATUS_CMD_ERROR - if internal RPC mechanism to SDK server fails
 * @return SX_STATUS_DB_NOT_INITIALIZED - if internal RIF DB is not initialized
 */
sx_status_t sx_api_router_interface_iter_get(const sx_api_handle_t        handle,
                                             const sx_access_cmd_t        cmd,
                                             const sx_router_interface_t *rif_key_p,
                                             const sx_rif_filter_t       *filter_p,
                                             sx_router_interface_t       *rif_list_p,
                                             uint32_t                    *rif_cnt_p);
/**
 *  This function sets admin state of a router interface. Admin state is set per
 *  IP protocol.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] rif - Router Interface ID.
 * @param[in] rif_state_p - Admin state for unicast routing and multicast routing.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_state_set(const sx_api_handle_t              handle,
                                              const sx_router_interface_t        rif,
                                              const sx_router_interface_state_t *rif_state_p);

/**
 * This function gets admin state of a router interface.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] rif - Router Interface ID.
 * @param[in] rif_state_p - Admin state for unicast routing and
 *                                            multicast routing.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_state_get(const sx_api_handle_t        handle,
                                              const sx_router_interface_t  rif,
                                              sx_router_interface_state_t *rif_state_p);

/**
 *  This function adds/deletes a MAC address from a router interface.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE/DELETE_ALL.
 * @param[in] rif - Router Interface ID.
 * @param[in] mac_addr_list_p - MAC addresses array.
 * @param[in] mac_addr_cnt - MAC addresses array size.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_mac_set(const sx_api_handle_t       handle,
                                            const sx_access_cmd_t       cmd,
                                            const sx_router_interface_t rif,
                                            const sx_mac_addr_t        *mac_addr_list_p,
                                            const uint32_t              mac_addr_cnt);

/**
 *  This function gets MAC address of a router interface.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] rif - Router Interface ID.
 * @param[out] mac_addr_list_p - MAC addresses array.
 * @param[in,out] mac_addr_cnt_p - MAC addresses array size.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_mac_get(const sx_api_handle_t       handle,
                                            const sx_router_interface_t rif,
                                            sx_mac_addr_t              *mac_addr_list_p,
                                            uint32_t                   *mac_addr_cnt_p);

/**
 *  This function adds/deletes/delete_all a neighbor
 *  information. The neighbor's information associates an IP
 *  address to a MAC address. The neighbor's IP addresses are
 *  learned via ARP/ND discovery at the control protocol layer.
 *  The interface that the neighbors are associated is
 *  derived from the IP interface configuration.
 *
 *  When cmd = DELETE_ALL, all neighbors which match the
 *  ip_addr_p->version and the rif, will be deleted.
 *  In case rif is rm_resource_global.router_rifs_dontcare, all neighbors,
 *  on all rifs, corresponding with the ip_addr_p->version will be deleted.
 *  If ip_addr_p->version = SX_IP_VERSION_NONE then only IPv4
 *  neighbors will be deleted.
 *
 *  In case the action is SX_ROUTER_ACTION_TRAP_FORWARD/SX_ROUTER_ACTION_TRAP,
 *  then trap ID will be set to SXD_TRAP_ID_RTR_EGRESS0 if trap priority is
 *  BEST EFFORT, LOW or MED, or to SXD_TRAP_ID_RTR_EGRESS1 for other priorities.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE/DELETE_ALL.
 * @param[in] rif - Router Interface Id
 * @param[in] ip_addr_p - IP address.
 * @param[in] neigh_data_p - Neighbors information.
 *
 * \deprecated In neigh_data_p, rif is deprecated and will be removed in the future.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if neighbor was not added.
 * @return SX_STATUS_NO_RESOURCES if no neighbor entry is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_neigh_set(const sx_api_handle_t       handle,
                                    const sx_access_cmd_t       cmd,
                                    const sx_router_interface_t rif,
                                    const sx_ip_addr_t         *ip_addr_p,
                                    const sx_neigh_data_t      *neigh_data_p);

/**
 *  This function gets the neighbor's information.
 *
 * The function can receive three types of input:
 *
 *   - 1) cmd SX_ACCESS_CMD_GET,
 *        gets the neighbor whose RIF and IP address match those given in rif and ip_addr_p.
 *        neigh_entry_cnt_p should be equal to 1.
 *
 *   - 2) cmd SX_ACCESS_CMD_GET_FIRST,
 *        get a list of first n<=20 neighbors whose IP version matches ip_addr_p->version.
 *        Entries can be filtered by the rif given in filter_p.
 *        If neigh_key_p->ip_addr.version == SX_IP_VERSION_NONE only IPv4 neighbors will be returned.
 *
 *   - 3) cmd SX_ACCESS_CMD_GETNEXT,
 *        get a list of n<=20 next neighbors after the key's IP address and RIF.
 *        The neighbor with the specific key doesn't have to exist.
 *        Entries can be filtered by the rif given in filter_p.
 *        If neigh_key_p->ip_addr.version == SX_IP_VERSION_NONE only IPv4 neighbors will be returned.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET/GET_FIRST/GET_NEXT.
 * @param[in] rif - Router Interface Id.
 * @param[in] neigh_key_p - neigh key.
 * @param[in] filter_p - neigh key_filter.
 * @param[out] neigh_entry_list_p  - found neigh entries arr
 * @param[in,out] neigh_entry_cnt_p - found neigh entries num
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if neighbor was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_neigh_get(const sx_api_handle_t       handle,
                                    const sx_access_cmd_t       cmd,
                                    const sx_router_interface_t rif,
                                    const sx_ip_addr_t         *neigh_key_p,
                                    const sx_neigh_filter_t    *filter_p,
                                    sx_neigh_get_entry_t       *neigh_entry_list_p,
                                    uint32_t                   *neigh_entry_cnt_p);

/**
 *  This function reads and cleans the neighbor's activity
 *  information.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - READ / READ_CLEAR
 * @param[in] rif - Router Interface Id.
 * @param[in] ip_addr_p - neigh IP address.
 * @param[out] activity_p - activity .
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if neighbor was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_neigh_activity_get(const sx_api_handle_t       handle,
                                             const sx_access_cmd_t       cmd,
                                             const sx_router_interface_t rif,
                                             const sx_ip_addr_t         *ip_addr_p,
                                             boolean_t                  *activity_p);

/**
 *  This function modifies unicast routes in the routing table.
 *  A route may have one of several types: IP2ME, LOCAL, or NEXT_HOP
 *  IP2ME routes trap traffic with the specified destination IP of the router host.
 *  Such traffic will have trap ID of IP2ME.
 *  Local routes allow IP forwarding to neighbors, and also trap traffic to
 *  unknown neighbors within the subnet. Such traffic will have trap ID of ARP-cache miss.
 *  Next-hop routes allow IP forwarding to next hop router(s)
 *  Next-hop routes must be defined with an ECMP container ID.
 *  ADD creates a new route and DELETE deletes an existing route.
 *  Command SET may be used to replace an existing route. This includes optionally
 *  changing its type. If a flow-counter is bound to the route, it stays bound.
 *  Command DELETE_ALL deletes all of the unicast routes of the specified virtual
 *  router, the specified route type in uc_route_data_p->type, and the IP protocol(s) in
 *  network_addr->version. If uc_route_data_p is NULL, then routes of type NEXT_HOP are
 *  deleted. If network_addr is NULL or network_addr->version is SX_IP_VERSION_NONE
 *  then all IPv4 routes of the specified type are deleted.
 *  For routes with action TRAP or TRAP_FORWARD, the trapped traffic will
 *  have Trap ID of SX_TRAP_ID_L3_UC_IP_BASE for trap priority BEST_EFFORT,
 *  LOW or MEDIUM, or (SX_TRAP_ID_L3_UC_IP_BASE+3) for higher trap priorities.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 * Note: This API supports Async Mode operation if the router is initialized
 * with Async support
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/SET/SOFT_ADD/DELETE/DELETE_ALL
 * @param[in] vrid - Virtual Router ID.
 * @param[in] network_addr_p - IP network address.
 * @param[in,out] uc_route_data_p - route data {ecmp id,action}
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_ACCEPTED if operation completes successfully in Async Mode.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if no routes is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_uc_route_set(const sx_api_handle_t handle,
                                       const sx_access_cmd_t cmd,
                                       const sx_router_id_t  vrid,
                                       const sx_ip_prefix_t *network_addr,
                                       sx_uc_route_data_t   *uc_route_data_p);

/**
 *  This function gets unicast route information from the routing table.
 *  The function can receive four types of input:
 *
 *   - 1) Get information for a specific IP address.
 *      Set the specific IP prefix in the network_addr parameter.
 *      uc_route_get_entries_cnt_p should be set to 1.
 *      cmd should be set to SX_ACCESS_CMD_GET.
 *
 *   - 2) Count the number of configured IPv4/6 UC routes,
 *      according to the network_addr->version parameter.
 *      uc_route_get_entries_cnt_p should be set to 0.
 *      cmd should be set to SX_ACCESS_CMD_GET.
 *
 *   - 3) Get a list of first n<=64 routes.
 *      Set IP prefix data in the network_addr parameter.
 *      uc_route_get_entries_cnt_p should be set to n.
 *      Set filter_p filter type(s) to filter the results by.
 *      cmd should be set to SX_ACCESS_CMD_GET_FIRST.
 *
 *   - 4) Get a list of n<=64 routes  which comes after specific
 *      IP prefix (not necessarily an existing one).  Set
 *      IP prefix address in the network_addr parameter.
 *      uc_route_get_entries_cnt_p should be set to n,
 *      filter_p is the filter type(s) you want to filter the
 *      results by. cmd should be SX_ACCESS_CMD_GETNEXT.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET /GET_FIRST/ GETNEXT.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] network_addr - IP network address
 * @param[in] filter_p - UC route key_filter.
 * @param[out]uc_route_get_entries_list_p - found uc route entries arr.
 * @param[in,out]uc_route_get_entries_cnt_p - found uc route entries num.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if UC route was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_uc_route_get(const sx_api_handle_t     handle,
                                       const sx_access_cmd_t     cmd,
                                       const sx_router_id_t      vrid,
                                       const sx_ip_prefix_t     *network_addr,
                                       sx_uc_route_key_filter_t *filter_p,
                                       sx_uc_route_get_entry_t  *uc_route_get_entries_list_p,
                                       uint32_t                 *uc_route_get_entries_cnt_p);

/**
 * \deprecated This API is deprecated and will be removed in the future. Use ECMP containers.
 * This function retrieves active unicast ECMP route information from the routing table.
 * When using oper_uc_route_entries_p->route_data.next_hop_cnt=0 only the number of next hops will be returned.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] network_addr - IP network address.
 * @param[out] oper_uc_route_entries_p - found uc route entry.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if ECMP UC route was not found.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_uc_route_operational_ecmp_get(const sx_api_handle_t    handle,
                                                        const sx_router_id_t     vrid,
                                                        const sx_ip_prefix_t    *network_addr_p,
                                                        sx_uc_route_get_entry_t *oper_uc_route_entries_p);

/**
 *  Binds or un-binds a flow counter to an existing unicast route
 *  Note: A route may be created via a call to sx_api_router_uc_route_set()
 *        A flow counter may be created via a call to sx_api_flow_counter_set()
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND/UNBIND
 * @param[in] vrid - Virtual Router ID
 * @param[in] network_addr_p - Network prefix of a unicast route
 * @param[in] counter_id - A flow counter identifier. Applicable only for command BIND
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if the specified route or flow counter was not found.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_uc_route_counter_bind_set(const sx_api_handle_t      handle,
                                                    const sx_access_cmd_t      cmd,
                                                    const sx_router_id_t       vrid,
                                                    const sx_ip_prefix_t      *network_addr_p,
                                                    const sx_flow_counter_id_t counter_id);

/**
 *  Retrieves the flow counter currently bound to a specified unicast route
 *  Notes: A flow counter may be bound to a route via a call to sx_api_router_uc_route_counter_bind_set()
 *         If no counter if bound to the specified route, this function returns SUCCESS, and
 *         sets *counter_id_p to SX_FLOW_COUNTER_ID_INVALID
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] vrid - Virtual Router ID
 * @param[in] network_addr_p - Network prefix of a unicast route
 * @param[out] counter_id_p - Returns the flow counter ID bound to the specified route
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if the specified route was not found.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_uc_route_counter_bind_get(const sx_api_handle_t handle,
                                                    const sx_router_id_t  vrid,
                                                    const sx_ip_prefix_t *network_addr_p,
                                                    sx_flow_counter_id_t *counter_id_p);

/**
 * This function creates/destroys a router counter. A router counter
 * should be bound later to a router interface.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/DESTROY.
 * @param[in,out] counter_p - Router counter ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_NO_RESOURCES if no counter is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_counter_set(const sx_api_handle_t   handle,
                                      const sx_access_cmd_t   cmd,
                                      sx_router_counter_id_t *counter_p);

/**
 *  This function creates/destroys a router counter by given type.
 *  A router counter should be bound later to a router interface.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/DESTROY.
 * @param[in] type - Router counter type.
 * @param[in,out] counter_p - Router counter ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_NO_RESOURCES if no counter is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_counter_extended_set(const sx_api_handle_t                handle,
                                               const sx_access_cmd_t                cmd,
                                               const sx_router_counter_attributes_t cntr_attributes,
                                               sx_router_counter_id_t              *counter_p);
/**
 * This function binds/unbinds a router counter to a router interface.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - BIND/UNBIND.
 * @param[in] counter - Router counter ID.
 * @param[in] rif - Router Interface ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_RESOURCE_IN_USE if interface is already bound.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_counter_bind_set(const sx_api_handle_t        handle,
                                                     const sx_access_cmd_t        cmd,
                                                     const sx_router_counter_id_t counter,
                                                     const sx_router_interface_t  rif);

/**
 * This function gets a router counter bind of a router interface.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] counter - Router counter ID.
 * @param[out] rif_p - Router Interface ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_ENTRY_NOT_BOUND if counter was not bound.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_counter_bind_get(const sx_api_handle_t        handle,
                                                     const sx_router_counter_id_t counter,
                                                     sx_router_interface_t       *rif_p);

/**
 * This function gets a router counter.
 * When using cmd=READ_CLEAR, the counters will be returned and cleared.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - READ/READ_CLEAR
 * @param[in] counter - Router counter ID.
 * @param[out] counter_set_p - Router counter set values.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_counter_get(const sx_api_handle_t        handle,
                                      const sx_access_cmd_t        cmd,
                                      const sx_router_counter_id_t counter,
                                      sx_router_counter_set_t     *counter_set_p);

/**
 *  This function gets a router counter by given type.
 *  When using cmd=READ_CLEAR, the counters will be returned and cleared.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - READ/READ_CLEAR
 * @param[in] counter - Router counter ID.
 * @param[out] counter_data_p - Router counter data values.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_counter_extended_get(const sx_api_handle_t             handle,
                                               const sx_access_cmd_t             cmd,
                                               const sx_router_counter_id_t      counter_id,
                                               sx_router_counter_set_extended_t *counter_data_p);
/**
 * This function clears router counter set of a router counter.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] counter - Router counter ID.
 * @param[in] all - Clear all Router counters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_counter_clear_set(const sx_api_handle_t        handle,
                                            const sx_router_counter_id_t counter,
                                            const boolean_t              all);

/**
 * This function adds/modifies/deletes a multicast route from the MC routing table.
 *
 * In case action is not SX_ROUTER_ACTION_FORWARD/SX_ROUTER_ACTION_DROP,
 * Trap ID will be set to SX_TRAP_ID_L3_MC_IP_BASE + trap priority.
 *
 * In case mc_router_attr_p->rpf_action is SX_ROUTER_RPF_ACTION_TRAP,
 * the caller should configure SX_TRAP_ID_ETH_L3_RPF trap first.
 *
 * In case the RPF action is SX_ROUTER_RPF_ACTION_TRAP or SX_ROUTER_RPF_ACTION_DROP,
 * the ingress RIF in the key should be the RPF RIF.
 * In case the RPF action is SX_ROUTER_RPF_ACTION_DIRECTIONAL, a valid ingress RIF
 * must be given.
 * egress_rif_cnt and egress_container_id are mutually exclusive and may not be both specified.
 * e.g. if egress_rif_cnt is nonzero then egress_container_id must be SX_MC_CONTAINER_ID_INVALID.
 * The DELETE_ALL command will delete all MC routes that match a given VRID and
 * IP version specified by source_addr.version. If the given IP version is SX_IP_VERSION_NONE,
 * then all MC routes on the given VRID will be deleted, regardless of the IP version.
 * the valid manual priority range is 1 - 32.
 * Router action SX_ROUTER_ACTION_SPAN is not supported on any device.
 * in case RPF actions is SX_ROUTER_RPF_ACTION_TRAP_LIST and SX_ROUTER_RPF_ACTION_DROP_LIST
 * then a valid RPF Group id must be given (that was previously created).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/EDIT/DELETE/DELETE_ALL
 * @param[in] vrid - Virtual Router ID.
 * @param[in] mc_route_key_p - mc route entry key
 *             {source IP prefix, group mask, ingress RIF}
 * @param[in] mc_router_attr_p - multicast route attributes
 *            (e.g. RPF mode, ttl, etc.)
 * @param[in] mc_route_data_p - route data (e.g. action, egress RIF list, etc.)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if no routes are available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_mc_route_set(const sx_api_handle_t            handle,
                                       const sx_access_cmd_t            cmd,
                                       const sx_router_id_t             vrid,
                                       const sx_mc_route_key_t        * mc_route_key_p,
                                       const sx_mc_route_attributes_t * mc_route_attr_p,
                                       const sx_mc_route_data_t       * mc_route_data_p);

/**
 * This function gets a multicast route or routes from the MC routing table,
 * based on a given key or criteria.
 * For GET_FIRST and GET_NEXT, the value of mc_route_get_entries_cnt_p must be
 * smaller or equal to SX_API_MC_ROUTE_GET_MAX_COUNT.
 * The ingress RIF is only considered part of the key for routes that have RPF
 * action SX_ROUTER_RPF_ACTION_DIRECTIONAL. Therefore, routes that were configured
 * with any other RPF action, and with an ingress RIF other than the "don't care"
 * RIF, will still be returned when filtering by the "don't care" ingress RIF. In
 * these cases, the configured ingress RIF can be found in the MC route data.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET - Get multicast route entry from DB.
 *                                      COUNT - Get number of MC entries from the DB that match the
 *                                                      criteria set by filter_p.
 *                                      GET_FIRST - Get first MC route entries from DB.
 *                                                      The maximum number of entries to be returned is
 *                                                      defined by mc_route_get_entries_cnt_p. The criteria
 *                                                      according to which entries will be returned is defined
 *                                                      by filter_p. The last route returned will be in
 *                                                      mc_route_key_p, and all routes returned will be in
 *                                                      mc_route_get_entries_list_p.
 *                                      GET_NEXT - Get next MC route entries from DB. The
 *                                                      maximum number of entries to be returned is defined
 *                                                      by mc_route_get_entries_cnt_p. The criteria according
 *                                                      to which entries will be returned is defined by filter_p.
 *                                                      The first entry returned will be the entry after that
 *                                                      given in mc_route_key_p, which should have been received
 *                                                      by a previous call to this API with GET_FIRST or GET_NEXT.
 *                                                      The last route returned will be in mc_route_key_p, and
 *                                                      all routes returned will be in mc_route_get_entries_list_p.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] mc_route_key_p - mc route entry key
 *                            {Source IP Address, group address, ingress rif}
 * @param[in] filter_p - filter according to which MC routes should be returned.
 *                       Relevant only for GET_FIRST and GET_NEXT commands.
 * @param[out] mc_route_get_entries_list_p - list of returned MC routes
 * @param[in,out] mc_route_get_entries_cnt_p - as input: number of entries in mc_route_get_entries_list_p
 *                                             as output: number of entries returned in mc_route_get_entries_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_NOT_FOUND if mc route is not found
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_mc_route_get(const sx_api_handle_t     handle,
                                       const sx_access_cmd_t     cmd,
                                       const sx_router_id_t      vrid,
                                       const sx_mc_route_key_t * mc_route_key_p,
                                       sx_mc_route_key_filter_t *filter_p,
                                       sx_mc_route_get_entry_t  *mc_route_get_entries_list_p,
                                       uint32_t                 *mc_route_get_entries_cnt_p);

/**
 * This function reads and clears multicast route activity.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - READ\READ_CLEAR
 * @param[in] vrid - Virtual Router ID.
 * @param[in] mc_route_key_p - mc route entry key
 *                             {Source IP Address, group address, ingress rif}
 * @param[out] activity_p - Route activity.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_NOT_FOUND if mc route is not found
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_router_mc_route_activity_get(const sx_api_handle_t    handle,
                                                const sx_access_cmd_t    cmd,
                                                const sx_router_id_t     vrid,
                                                const sx_mc_route_key_t *mc_route_key_p,
                                                boolean_t               *activity_p);
/**
 * This function initiates a notification regarding active mc routes in the system.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] cmd       - READ\READ_CLEAR
 * @param[in] filter_p  - activity notifier filter
 *
 * @return SX_STATUS_SUCCESS             if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR         if parameter is invalid.
 * @return SX_STATUS_RESOURCE_IN_USE     if a notification procedure is already running.
 * @return SX_STATUS_ERROR               general error.
 */
sx_status_t sx_api_router_mc_route_activity_notify(const sx_api_handle_t                       handle,
                                                   const sx_access_cmd_t                       cmd,
                                                   const sx_mc_route_activity_notify_filter_t *filter_p);
/**
 * This function adds/sets/deletes/deletes-all egress RIFs to/from a previously
 * configured MC route.
 * Only routes configured with egress_rif_cnt and egress_rif_list_p are supported by this
 * function. Routes configured with egress_container_id are not supported.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE/DELETE_ALL/SET
 *                 SET command replaces the entire list of existing egress RIFs
 *                 with the given list.
 *                 DELETE_ALL command deletes all egress router interfaces
 *                 associated with multicast group.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] mc_route_key_p - mc route entry key
 *                             {Source IP Address, group address, ingress rif}
 * @param[in] egress_rif_list_p - Egress Router Interface array.
 * @param[in] egress_rif_cnt - Egress Router Interface array num.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if no more RIFs can be set.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_mc_egress_rif_set(const sx_api_handle_t        handle,
                                            const sx_access_cmd_t        cmd,
                                            const sx_router_id_t         vrid,
                                            const sx_mc_route_key_t     *mc_route_key_p,
                                            const sx_router_interface_t *egress_rif_list_p,
                                            const uint32_t               egress_rif_cnt);

/**
 *  This function gets the list of egress RIFs associated with the given multicast
 *  route. When egress_rif_num is 0 or egress_rif_arr == NULL, the function will
 *  return the number of egress RIFs, and egress_rif_arr will remain empty.
 *  Only routes configured with egress_rif_cnt and egress_rif_list_p are supported by this
 *  function. Routes configured with egress_container_id are not.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] mc_route_key_p - mc route entry key
 *                             {Source IP Address, group address, ingress rif}
 * @param[out] egress_rif_list_p - Egress Router Interface array.
 * @param[in,out] egress_rif_cnt_p - as input: number of entries in egress_rif_list_p
 *                                                                       as output: number of egress RIFs returned in egress_rif_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_mc_egress_rif_get(const sx_api_handle_t    handle,
                                            const sx_router_id_t     vrid,
                                            const sx_mc_route_key_t *mc_route_key_p,
                                            sx_router_interface_t   *egress_rif_list_p,
                                            uint32_t                *egress_rif_cnt);

/**
 * This function enables in-router rewriting of PCP, DEI rewriting bits.
 * The configuration is per IP router.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] rewrite_pcp_dei        - enable the option to rewrite PCP and DEI fields
 *                                     at the egress port (preserve from the ingress,
 *                                     disable rewrite, enable rewrite).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_router_cos_rewrite_pcpdei_enable_set(const sx_api_handle_t          handle,
                                                        const sx_cos_pcp_dei_rewrite_e rewrite_pcp_dei);

/**
 * This function retrieves in-router rewriting of PCP, DEI rewriting bits.
 * The configuration is per IP router.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param[out] rewrite_pcp_dei        - enable the option to rewrite PCP and DEI fields
 *                                      at the egress port (preserve from the ingress,
 *                                      disable rewrite, enable rewrite).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_router_cos_rewrite_pcpdei_enable_get(const sx_api_handle_t     handle,
                                                        sx_cos_pcp_dei_rewrite_e *rewrite_pcp_dei_p);

/**
 * This function enables in-router updating of switch-priority and color. The updated
 * mapping is defined using sx_api_router_cos_dscp_to_prio_set.
 * The configuration is per IP router.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] update_priority_color - enable updates the switch priority and color
 *                   by the DSCP map defined using sx_api_router_cos_dscp_to_prio_set.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_router_cos_prio_update_enable_set(const sx_api_handle_t handle,
                                                     const boolean_t       update_priority_color);

/**
 * This function retrieves in-router updating of switch-priority and color. The updated
 * mapping is defined using sx_api_router_cos_dscp_to_prio_set.
 * The configuration is per IP router.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[out] update_priority_color_p - enable updates the switch priority and color
 *                   by the DSCP map described in sx_api_router_cos_dscp_to_prio_set
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_router_cos_prio_update_enable_get(const sx_api_handle_t handle,
                                                     boolean_t            *update_priority_color_p);

/**
 * This function sets the mapping from DSCP to switch-priority and color
 * for in-router rewrite.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 * The mapping is used only if enabled in sx_api_router_cos_prio_update_enable_set.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] dscp                  - a list of DSCP's
 * @param[in] switch_priority_color - a list of switch priorities and color
 * @param[in] element_cnt           - num of elements in switch priorities and DSCP's lists
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_router_cos_dscp_to_prio_set(const sx_api_handle_t          handle,
                                               const sx_cos_dscp_t           *dscp_p,
                                               const sx_cos_priority_color_t *priority_color_p,
                                               const uint32_t                 element_cnt);

/**
 * This function retrieves the mapping from DSCP to switch-priority and color for in-router rewrite.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] dscp                    - a list of DSCP's
 * @param[in] switch_priority_color_p - a list of switch priorities and color
 * @param[in] element_cnt_p           - num of elements in switch priorities and DSCP's lists
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 */
sx_status_t sx_api_router_cos_dscp_to_prio_get(const sx_api_handle_t    handle,
                                               sx_cos_dscp_t           *dscp_p,
                                               sx_cos_priority_color_t *priority_color_p,
                                               uint32_t                *element_cnt_p);

/**
 * This function creates/modifies/destroys an ECMP container, according to cmd.
 *
 * SX_ACCESS_CMD_CREATE - by providing a next hops list, the command creates an
 * ECMP container. Container content is formed as a subset of the resolved next
 * hops. Returned Next hops weights are adjusted to the proper weights as
 * written on HW.
 * This command returns the containers next hops as written on HW, list count
 * and new container ID.
 * SX_ACCESS_CMD_SET - Modifies the contents of an existing ECMP container,
 * specified by *ecmp_id_p. If *next_hop_cnt_p is zero, SET cmd empties the container.
 * SX_ACCESS_CMD_DESTROY - by providing a container ID, the command removes
 * all next hops from the existing given container, destroying the container as well.
 * The container ID is invalid until reassigned on container creation. This command
 * returns list count 0
 * Weights will be modified on runtime according to next hops resolution changes.
 * Clearing(set with an empty next hops list), is not allowed in
 * case container is in use by UC route(s).
 *
 * Note for ECMP containers of types SX_ECMP_CONTAINER_TYPE_NVE_FLOOD and SX_ECMP_CONTAINER_TYPE_NVE_MC:
 *   1. The max size of ECMP NVE container is determined:
 *      - by sx_tunnel_nve_general_params_t.ecmp_max_size value on Spectrum;
 *      - by min{rm_resources_t.tunnel_nve_group_size_flood_max;sx_router_resources_param_t.max_ecmp_block_size}
 *        for ECMP NVE FLOOD containers on Spectrum2 and higher;
 *      - by min{rm_resources_t.tunnel_nve_group_size_mc_max;sx_router_resources_param_t.max_ecmp_block_size}
 *        for ECMP NVE MC containers on Spectrum2 and higher;
 *   2. ECMP NVE containers can contain next hops only of the type SX_NEXT_HOP_TYPE_TUNNEL_ENCAP.
 *   3. To create an ECMP container of the type SX_ECMP_CONTAINER_TYPE_NVE_FLOOD
 *      or SX_ECMP_CONTAINER_TYPE_NVE_MC, do the following steps:
 *         3.1. Create an empty ECMP container using sx_api_router_ecmp_set;
 *         3.2. Change the type of this ECMP container using sx_api_router_ecmp_attributes_set;
 *         3.3. Set next hopes to this ECMP container using sx_api_router_ecmp_set;
 *   4. On Spectrum, all ECMP NVE containers have the same size in HW,
 *      if an ECMP NVE container has next hops with the total weight less than
 *      the configured global size (sx_tunnel_nve_general_params_t.ecmp_max_size),
 *      then next hops will be configured to HW using weighted round robin algorithm.
 *      For example if the size is configured to be four, and an ECMP NVE container has two following next hops:
 *        - next hop #A with weight of 1;
 *        - next hop #B with weight of 2;
 *      you will get unbalanced ECMP container.
 *      In the HW, this ECMP container will have three next hops with total weight of four: nh #A, nh #B, nh #A.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - action to perform: CREATE, DESTROY, SET,
 * @param[in,out] ecmp_id            - id of ECMP container
 * @param[in,out] next_hop_list_p    - a given list of next hops
 * @param[in,out] next_hop_cnt_p     - amount of next hops
 *
 * @return SX_STATUS_SUCCESS             if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR         if parameter is NULL or exceeds range.
 * @return SX_STATUS_UNSUPPORTED         if invalid cmd.
 * @return SX_STATUS_NO_RESOURCES        if no space for ECMP container allocation.
 * @return SX_STATUS_RESOURCE_IN_USE     if trying to destroy ECMP an container
 *                                       in use.
 * @return SX_STATUS_ENTRY_NOT_FOUND     if ecmp_id not found.
 * @return SX_STATUS_ERROR               general error.
 */
sx_status_t sx_api_router_ecmp_set(const sx_api_handle_t handle,
                                   const sx_access_cmd_t cmd,
                                   sx_ecmp_id_t         *ecmp_id_p,
                                   sx_next_hop_t        *next_hop_list_p,
                                   uint32_t             *next_hop_cnt_p);

/**
 * This function retrieves an ECMP container content, as defined by the user.
 * Note:
 *     This function returns next hops for a given ECMP ID even if this ECMP is redirected.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] ecmp_id            - id of an ECMP container
 * @param[out] next_hop_list_p   - a given list of next hops
 * @param[out] next_hop_cnt_p    - amount of next hops
 *
 * @return SX_STATUS_SUCCESS             if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR         if parameter is NULL or exceeds range.
 * @return SX_STATUS_ENTRY_NOT_FOUND     if ecmp_id not found.
 * @return SX_STATUS_ERROR               general error.
 */
sx_status_t sx_api_router_ecmp_get(const sx_api_handle_t handle,
                                   const sx_ecmp_id_t    ecmp_id,
                                   sx_next_hop_t        *next_hop_list_p,
                                   uint32_t             *next_hop_cnt_p);

/**
 *  This function returns a list of one or more ECMP container identifiers.
 *  The following use case scenarios apply with different input parameters
 *  X = don't-care
 *   - 1) cmd = SX_ACCESS_CMD_GET, ecmp_id = X, ecmp_list = X, ecmp_cnt = 0:
 *        In this case the API will return the total number of ECMP containers in the
 *        Internal db.
 *
 *   - 2) cmd = SX_ACCESS_CMD_GET, ecmp_id = valid/invalid, ecmp_list = valid,
 *        ecmp_cnt = 1:
 *        In this case the API will check if the specified ECMP container ID exists.
 *        If it does, the ECMP container ID will be returned in the ecmp_list along with
 *        a ecmp_cnt of 1.
 *        If the key does not exist, an empty list will be returned with ecmp_cnt = 0.
 *        A non-NULL ecmp_list pointer must be provided in this case.
 *
 *   - 3) cmd = SX_ACCESS_CMD_GET, ecmp_id = valid/invalid, ecmp_list = valid,
 *        ecmp_cnt > 1:
 *        An ecmp_cnt > 1 will be treated as a ecmp_cnt of 1 and the behavior will be same
 *        as the earlier GET use cases.
 *
 *   - 4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, ecmp_id = X
 *        ecmp_list = NULL, ecmp_cnt = 0:
 *        A zero ecmp_cnt and an empty ecmp_list will be returned.
 *
 *   - 5) cmd = SX_ACCESS_CMD_GET_FIRST, ecmp_id = X, ecmp_list = valid, ecmp_cnt > 0:
 *        In this case the API will return the first ecmp_cnt ECMP container IDs starting
 *        from the head of the database. The total number of elements fetched will be returned
 *        as ecmp_cnt.  Note: returned ecmp_cnt may be less than or equal to
 *        the requested ecmp_cnt. The key is ignored in this case.
 *        A non-NULL ecmp_list pointer must be provided in this case.
 *
 *   - 6) cmd = SX_ACCESS_CMD_GETNEXT, ecmp_id = valid/invalid, ecmp_list = valid,
 *        ecmp_cnt > 0:
 *        In this case the API will return the next set of ECMP container IDs starting from
 *        the next valid ECMP container ID after the specified ECMP container ID. The total
 *        number of elements fetched will be returned as the ecmp_cnt.
 *        Note: returned ecmp_cnt may be less than or equal to the requested ecmp_cnt.
 *        If no valid next ECMP container ID exists in the db, an empty list will be returned.
 *        A non-NULL ecmp_list pointer must be provided in this case.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param [in] handle           : SX API handle
 * @param [in] cmd              : GET/GET_FIRST/GET_NEXT
 * @param [in] ecmp_id          : specify an ECMP container ID
 * @param [in] filter           : specify a filter parameter (not supported yet)
 * @param [out] ecmp_list_p     : return list of ECMP container IDs
 * @param [in,out] ecmp_cnt_p   : [in] number of ECMP container IDs to get
 *                              : [out] number of ECMP container IDs returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if an unexpected NULL parameter was passed.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ERROR general error.
 * @return SX_STATUS_CMD_UNSUPPORTED - if invalid cmd is passed
 * @return SX_STATUS_MODULE_UNINITIALIZED - if router module is uninitialized
 * @return SX_STATUS_CMD_ERROR - if internal RPC mechanism to SDK server fails
 * @return SX_STATUS_DB_NOT_INITIALIZED - if internal ECMP DB is not initialized
 */
sx_status_t sx_api_router_ecmp_iter_get(const sx_api_handle_t   handle,
                                        const sx_access_cmd_t   cmd,
                                        const sx_ecmp_id_t      ecmp_id,
                                        const sx_ecmp_filter_t *filter_p,
                                        sx_ecmp_id_t           *ecmp_list_p,
                                        uint32_t               *ecmp_cnt_p);

/**
 *  This function retrieves the ECMP container content, as written to HW(only
 *  resolved next hops are written to HW).
 *  Note:
 *      This function will return next hops for a given ECMP ID if this ECMP isn't redirected,
 *      if the ECMP is redirected, it will return next hops from the destination ECMP.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] ecmp_id            - id of an ECMP container
 * @param[out] next_hop_list_p   - a given list of next hops
 * @param[out] next_hop_cnt_p    - amount of next hops
 *
 * @return SX_STATUS_SUCCESS             if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR         if parameter is NULL or exceeds range.
 * @return SX_STATUS_ENTRY_NOT_FOUND     if ecmp_id not found.
 * @return SX_STATUS_ERROR               general error.
 */
sx_status_t sx_api_router_operational_ecmp_get(const sx_api_handle_t handle,
                                               const sx_ecmp_id_t    ecmp_id,
                                               sx_next_hop_t        *next_hop_list_p,
                                               uint32_t             *next_hop_cnt_p);


/**
 *  This function binds/unbinds a router counter to a list of next hops for a
 *  given container.
 *  In case of INVALID_NEXT_HOP_OFFSET counter will be bound to all next hops in
 *  given ECMP container.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] cmd               - BIND/UNBIND.
 * @param[in] ecmp_id           - id of an ECMP container
 * @param[in] counter_id_list_p - list of counter IDs to bind to matching offsets.
 * @param[in] offset_list_p     - list of next hop entries offset in configured next hops list to.
 * @param[in] elements_cnt      - amount of next hops offsets.
 *
 *
 * @return SX_STATUS_SUCCESS            if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED    if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR        if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND    if counter was not added.
 * @return SX_STATUS_RESOURCE_IN_USE    if interface is already bound.
 * @return SX_STATUS_ERROR              general error.
 */
sx_status_t sx_api_router_ecmp_counter_bind_set(const sx_api_handle_t       handle,
                                                const sx_access_cmd_t       cmd,
                                                const sx_ecmp_id_t          ecmp_id,
                                                const sx_flow_counter_id_t *counter_id_list_p,
                                                const uint32_t             *offset_list_p,
                                                const uint32_t              elements_cnt);

/**
 *  This function binds/unbinds a router counter to a list of indices in a
 *  container active set.
 *  This API should be used for containers that are not static containers.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] cmd               - BIND/UNBIND.
 * @param[in] ecmp_id           - ID of a non static ECMP container
 * @param[in] counter_id        - ID of a counter to bind to the given offsets.
 * @param[in] offset_list_p     - list of entry offsets in configured ECMP container.
 * @param[in] elements_cnt      - amount of entry offsets.
 *
 *
 * @return SX_STATUS_SUCCESS            if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED    if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR        if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND    if counter was not added.
 * @return SX_STATUS_RESOURCE_IN_USE    if interface is already bound.
 * @return SX_STATUS_ERROR              general error.
 */
sx_status_t sx_api_router_ecmp_fine_grain_counter_bind_set(const sx_api_handle_t      handle,
                                                           const sx_access_cmd_t      cmd,
                                                           const sx_ecmp_id_t         ecmp_id,
                                                           const sx_flow_counter_id_t counter_id,
                                                           const uint32_t            *offset_list_p,
                                                           const uint32_t             elements_cnt);


/**
 * This function initiates a notification regarding active neighbors in the system.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] cmd       - READ\READ_CLEAR
 * @param[in] filter_p  - neigh activity notifier filter
 *
 * @return SX_STATUS_SUCCESS             if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR         if parameter is invalid.
 * @return SX_STATUS_RESOURCE_IN_USE     if a notification procedure is already running.
 * @return SX_STATUS_ERROR               general error.
 */
sx_status_t sx_api_router_neigh_activity_notify(const sx_api_handle_t                    handle,
                                                const sx_access_cmd_t                    cmd,
                                                const sx_router_neigh_activity_filter_t *filter_p);

/**
 *
 * This function sets an ECMP container's attributes.
 * Using this API is not mandatory for ECMP hashing (default value is SX_ECMP_TYPE_STATIC_E)
 * To use this API one should create an empty ECMP container, set the container
 * attributes and add next hops.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] ecmp_id     - an ID of an ECMP container
 * @param[in] attr_p      - ECMP container attributes
 *
 * @return SX_STATUS_SUCCESS              if operation completes successfully.
 * @return SX_STATUS_ERROR                general error
 * @return SX_STATUS_PARAM_ERROR          if parameter is NULL or exceeds range.
 * @return SX_STATUS_ENTRY_NOT_FOUND      if ecmp_id not found.
 */
sx_status_t sx_api_router_ecmp_attributes_set(const sx_api_handle_t       handle,
                                              const sx_ecmp_id_t          ecmp_id,
                                              const sx_ecmp_attributes_t *attr_p);

/**
 * This function retrieves an ECMP container's attributes.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle.
 * @param[in] ecmp_id     - id of ECMP container.
 * @param[out] attr_p     - ECMP container attributes
 *
 * @return SX_STATUS_SUCCESS           if operation completes successfully.
 * @return SX_STATUS_ERROR             general error
 * @return SX_STATUS_PARAM_ERROR       if parameter is NULL or exceeds range.
 * @return SX_STATUS_ENTRY_NOT_FOUND   if ecmp_id not found.
 */
sx_status_t sx_api_router_ecmp_attributes_get(const sx_api_handle_t handle,
                                              const sx_ecmp_id_t    ecmp_id,
                                              sx_ecmp_attributes_t *attr_p);

/**
 * This function clones an ECMP container.
 * Note:
 *    ECMP redirect doesn't affect the cloning process - newly cloned container won't be
 *    redirected even if the original one is redirected.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] old_ecmp_id            - Old ID of ECMP container
 * @param[out] new_ecmp_id_p         - New ID of ECMP
 *                                     container pointer return
 *                                     with pointer that
 *                                     contains the new created
 *                                     container ID
 *
 * @return SX_STATUS_SUCCESS             if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR         if parameter is NULL or exceeds range.
 * @return SX_STATUS_NO_RESOURCES        if no space for ECMP container allocation.
 * @return SX_STATUS_ENTRY_NOT_FOUND     if ecmp_id not found.
 * @return SX_STATUS_ERROR               general error.
 */
sx_status_t sx_api_router_ecmp_clone_set(const sx_api_handle_t handle,
                                         const sx_ecmp_id_t    old_ecmp_id,
                                         sx_ecmp_id_t         *new_ecmp_id_p);

/** Manipulate a multicast router Reverse-Path Forwarding group
 * Command CREATE creates a new RPF group which contains the specified list of
 * ingress RIFs in rpf_rif_list_p, and returns its new group ID in rpf_group_id_p.
 * Command SET replaces the contents of an existing RPF group specified by
 * rpf_group_id_p, with the specified list of ingress RIFs in rpf_rif_list_p.
 * Command DESTROY deletes the existing RPF group specified by rpf_group_id_p
 * Command DELETE_ALL deletes all existing RPF groups.
 * Notes: An RPF group in use by a multicast route cannot be destroyed
 *        An RPF group may contain only ingress RIFs which belong to the same virtual router
 *        An RPF group must contain at least one ingress RIF
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/SET/DESTROY/DELETE_ALL.
 * @param[in,out] rpf_group_id_p - Specifies or returns the group ID
 * @param[in] rpf_rif_list_p - Specifies the list of ingress RIFs in a group
 * @param[in] rpf_rif_cnt - Specifies the amount of ingress RIFs in rpf_rif_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified group ID does not exist.
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation.
 * @return SX_STATUS_RESOURCE_IN_USE if group is in use and cannot be destroyed.
 */
sx_status_t sx_api_router_mc_rpf_group_set(const sx_api_handle_t   handle,
                                           const sx_access_cmd_t   cmd,
                                           sx_rpf_group_id_t      *rpf_group_id_p,
                                           sx_router_vinterface_t *rpf_vif_list_p,
                                           uint32_t                rpf_vif_cnt);

/**
 * Retrieve information about a multicast router Reverse-Path Forwarding group
 * Command GET retrieves information about an RPF group specified by rpf_group_id_p
 * Command GETFIRST retrieves the first existing RPF group, its ID and contents
 * Command GETNEXT retrieves the next existing RPF group, its ID and contents
 * Notes: In order to enumerate all existing RPF groups, a client application may
 *        call GETFIRST once, and then repeatedly call GETNEXT until all groups are
 *        retrieved.
 *        If *rpf_rif_cnt_p is 0, then rpf_rif_list_p may be NULL, and only the
 *        amount of RIFs is returned without the list of RIFs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET/GETFIRST/GETNEXT
 * @param[in,out] rpf_group_id_p - Specifies a previous group ID or returns a group ID
 * @param[out] rpf_rif_list_p - Returns a list of ingress RIFs in the group
 * @param[in,out] rpf_rif_cnt - Specifies the size of rpf_rif_list_p, and returns the amount
 *                              of ingress RIFs in rpf_rif_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified group ID does not exist, or no more groups.
 */

sx_status_t sx_api_router_mc_rpf_group_get(const sx_api_handle_t   handle,
                                           const sx_access_cmd_t   cmd,
                                           sx_rpf_group_id_t      *rpf_group_id_p,
                                           sx_router_vinterface_t *rpf_vif_list_p,
                                           uint32_t               *rpf_vif_cnt_p);

/**
 *  Binds or un-binds a flow counter to an existing multicast route
 *  Note: A route may be created via a call to sx_api_router_mc_route_set()
 *        A flow counter may be created via a call to sx_api_flow_counter_set()
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND/UNBIND
 * @param[in] vrid - Virtual Router ID
 * @param[in] mc_route_key_p - MC route key
 * @param[in] counter_id - A flow counter identifier. Applicable only for command BIND
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is null.
 * @return SX_STATUS_ENTRY_NOT_FOUND if the specified route or flow counter was not found.
 * @return SX_STATUS_ENTRY_ALREADY_BOUND if mc route already bounded.
 * @return SX_STATUS_ENTRY_NOT_BOUND if counter was not bound.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_mc_route_counter_bind_set(const sx_api_handle_t      handle,
                                                    const sx_access_cmd_t      cmd,
                                                    const sx_router_id_t       vrid,
                                                    const sx_mc_route_key_t   *mc_route_key_p,
                                                    const sx_flow_counter_id_t counter_id);

/**
 *  Retrieves the flow counter currently bound to a specified multicast route
 *  Notes: A flow counter may be bound to a route via a call to sx_api_router_mc_route_counter_bind_set()
 *         If no counter is bound to the specified route, this function returns SUCCESS, and
 *         sets *counter_id_p to SX_FLOW_COUNTER_ID_INVALID
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] vrid - Virtual Router ID
 * @param[in] mc_route_key_p - MC route key
 * @param[out] counter_id_p - Returns the flow counter ID bound to the specified route
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is null.
 * @return SX_STATUS_ENTRY_NOT_FOUND if the specified route was not found.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_mc_route_counter_bind_get(const sx_api_handle_t    handle,
                                                    const sx_router_id_t     vrid,
                                                    const sx_mc_route_key_t *mc_route_key_p,
                                                    sx_flow_counter_id_t    *counter_id_p);

/**
 *  This API CREATEs/DESTROYs redirection between an ECMP(“ecmp”) and a
 *  destination ECMP(“redirect_ecmp”).
 *
 *  Note:
 *  Only ECMP NVE containers can be redirected;
 *  ECMP container “ecmp” can be redirected to an ECMP container “redirect_ecmp” only if:
 *      1. ECMP container “redirect_ecmp” is not in use (the reference counter of ECMP container is equal 0):
 *         1.1 ex.: there are no FDB entries that point to “redirect_ecmp”;
 *      2. “redirect_ecmp” is not redirected to any other ECMP and no other container is already redirected to  “redirect_ecmp”.
 *  Once ECMP container “redirect_ecmp” becomes the master, the user cannot create objects that point to the container “redirect_ecmp” directly.
 *  ECMP container “redirect_ecmp” cannot be destroyed until redirection stops.
 *  ECMP container “ecmp” cannot be destroyed until redirection stops.
 *  Only 1:1 redirection is supported:
 *      1. Redirection chains are not supported: “A” -> “B” -> “C”;
 *      2. N:1 redirection is not supported: “A” -> “C” | “B” -> “C”;
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - CREATE/DESTROY
 * @param[in] ecmp                  - ECMP ID
 * @param[in] redirect_ecmp         - ECMP ID which ecmp now
 *                                    points to. Ignored in DESTROY command.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 */
sx_status_t sx_api_router_ecmp_redirect_set(const sx_api_handle_t handle,
                                            const sx_access_cmd_t cmd,
                                            const sx_ecmp_id_t    ecmp,
                                            const sx_ecmp_id_t    redirect_ecmp);

/**
 *  This API returns information whether given ECMP is redirected.
 *  If given ECMP is redirected, the redirected ECMP ID is returned.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                     - SX-API handle.
 * @param[in] ecmp                       - ECMP ID.
 * @param[out] is_redirected_p           - is ECMP_port redirected.
 * @param[out] redirected_ecmp_p         - the ECMP ID to point to when the ECMP is redirected.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 */
sx_status_t sx_api_router_ecmp_redirect_get(const sx_api_handle_t handle,
                                            const sx_ecmp_id_t    ecmp,
                                            boolean_t            *is_redirected_p,
                                            sx_ecmp_id_t         *redirected_ecmp_p);


/**
 *
 *  This API gets the completion info for the last successfully configured route in Hardware.
 *  The completion Info will contain the user cookie provided when the route was configured.
 *   Note: This API is relevant if the Router has been initialized in Async mode only.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[out] completion_info_p – Completion Info Parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_req_completion_info_get(const sx_api_handle_t                      handle,
                                                  sx_router_req_completion_info_get_entry_t* completion_info_p);

#endif /* __SX_API_ROUTER_H__ */
