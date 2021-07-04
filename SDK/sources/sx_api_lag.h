/*
 * Copyright (C) 2014-2021 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_LAG_H__
#define __SX_API_LAG_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of a LAG module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - LAG module verbosity level
 * @param[in] api_verbosity_level      - LAG API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_lag_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of a LAG module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - LAG module verbosity level
 * @param[out] api_verbosity_level_p    - LAG API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_lag_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API creates/destroys a new/existing LAG's port group in the SDK. This API also adds/deletes ports to/from an existing LAG's
 * port group in the SDK.
 *
 * Note: All ports must be deleted from a LAG port groups before the group is destroyed.
 * Note: Creating a LAG group and adding ports to it in the same API call is not supported.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - CREATE/DESTROY/ADD/DELETE
 * @param[in] swid               - Switch (virtual partition) ID
 * @param[in,out] lag_log_port_p - [in] already-created LAG port's group ID/[out] newly-created LAG port's group ID
 * @param[in] log_port_list_p    - List of logical ports to ADD/DELETE to/from a LAG's port group
 * @param[in] log_port_cnt       - Number of logical ports to ADD/DELETE to/from a LAG's port group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in the database
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 * @return SX_STATUS_CMD_UNSUPPORTED if the provided command is unsupported
 * @return SX_STATUS_CMD_UNPERMITTED if ISSU is in progress
 * @return SX_STATUS_RESOURCE_IN_USE when reference count is non-zero during delete operation
 */
sx_status_t sx_api_lag_port_group_set(const sx_api_handle_t   handle,
                                      const sx_access_cmd_t   cmd,
                                      const sx_swid_t         swid,
                                      sx_port_log_id_t       *lag_log_port_p,
                                      const sx_port_log_id_t *log_port_list_p,
                                      const uint32_t          log_port_cnt);

/**
 * This API retrieves an existing LAG's port group from the SDK.
 *
 * Note: If the output ports list is NULL, only the number of ports in the LAG is retrieved.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] swid                  - Switch (virtual partition) ID
 * @param[in] lag_log_port          - LAG's port group ID
 * @param[in,out] log_port_list_p   - List of logical ports
 * @param[in,out] log_port_cnt_p    - [in] number of logical ports in list/[out] number of logical ports in a LAG
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in the database
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 */
sx_status_t sx_api_lag_port_group_get(const sx_api_handle_t  handle,
                                      const sx_swid_t        swid,
                                      const sx_port_log_id_t lag_log_port,
                                      sx_port_log_id_t      *log_port_list_p,
                                      uint32_t              *log_port_cnt_p);


/**
 *  This API retrieves a list of one or more LAG IDs.
 *  The following use case scenarios apply with different input parameters
 *  X = don't-care
 *   1) cmd = SX_ACCESS_CMD_GET, swid = valid, lag_id = X, lag_id_list = X, lag_id_cnt = 0:
 *        In this case, the API will return the total number of LAG IDs in the internal database.
 *
 *   2) cmd = SX_ACCESS_CMD_GET, swid = valid, lag_id = valid/invalid, lag_id_list = valid, lag_id_cnt = 1:
 *        In this case, the API will check if the specified LAG ID exists. If it does, the LAG ID will be returned in the
 *        lag_id_list along with a lag_id_cnt of 1.
 *        If the LAG ID does not exist, an empty list will be returned with lag_id_cnt = 0.
 *        A non-NULL lag_id_list pointer must be provided in this case.
 *
 *   3) cmd = SX_ACCESS_CMD_GET, swid = valid, lag_id = valid/invalid, lag_id_list = valid, lag_id_cnt > 1:
 *        A lag_id_cnt > 1 will be treated as a lag_id_cnt of 1 and the behavior will be the same as the earlier GET use cases.
 *
 *   4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, swid = X, lag_id = X, lag_id_list = NULL, lag_id_cnt = 0:
 *        A zero lag_id_cnt and an empty lag_id_list will be returned.
 *
 *   5) cmd = SX_ACCESS_CMD_GET_FIRST, swid = valid, lag_id = X, lag_id_list = valid, lag_id_cnt > 0:
 *        In this case, the API will return the first lag_id_cnt LAG IDs starting from the head of the database.
 *        The total number of elements fetched will be returned as lag_id_cnt.
 *
 *         Note: returned lag_id_cnt may be less than or equal to  the requested lag_id_cnt. The input LAG ID is ignored in this
 *        case and a non-NULL lag_id_list pointer must be provided.
 *
 *   6) cmd = SX_ACCESS_CMD_GETNEXT, swid = valid, lag_id = valid/invalid, lag_id_list = valid, lag_id_cnt > 0:
 *        In this case, the API will return the next set of LAG IDs starting from  the next LAG ID after the specified LAG ID.
 *        The total number of elements fetched will be returned as the lag_id_cnt.
 *
 *        Note: returned lag_id_cnt may be less than or equal to the requested lag_id_cnt. If no valid next LAG ID exists in
 *        the database, an empty list will be returned and a non-NULL lag_id_list pointer must be provided.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param [in] cmd                    - GET/GET_FIRST/GET_NEXT
 * @param[in] swid                    - Virtual switch partition ID
 * @param[in] lag_id                  - LAG ID
 * @param [in] filter_p               - Specify a filter parameter (not supported yet)
 * @param [out] lag_id_list_p         - Return list of LAG IDs
 * @param [in,out] lag_id_cnt_p       - [in] number of LAG IDs to get/[out] number of LAG IDs returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in the database
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_lag_port_group_iter_get(const sx_api_handle_t  handle,
                                           const sx_access_cmd_t  cmd,
                                           const sx_swid_t        swid,
                                           const sx_port_log_id_t lag_id,
                                           const sx_lag_filter_t *filter_p,
                                           sx_port_log_id_t      *lag_id_list_p,
                                           uint32_t              *lag_id_cnt_p);


/**
 * This API enables/disables collection on a specific LAG port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] lag_log_port   - Logical port number representing the LAG's port group
 * @param[in] log_port       - Logical port number
 * @param[in] collector_mode - Collector mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_NO_MEMORY if the system has no more available free memory
 */

sx_status_t sx_api_lag_port_collector_set(const sx_api_handle_t     handle,
                                          const sx_port_log_id_t    lag_log_port,
                                          const sx_port_log_id_t    log_port,
                                          const sx_collector_mode_t collector_mode);


/**
 * This API returns information whether collection is enabled or disabled on a specific port in a LAG port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] lag_log_port      - Logical port number representing the LAG's port group
 * @param[in] log_port          - Logical port number
 * @param[out] collector_mode_p - Collector mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 */

sx_status_t sx_api_lag_port_collector_get(const sx_api_handle_t  handle,
                                          const sx_port_log_id_t lag_log_port,
                                          const sx_port_log_id_t log_port,
                                          sx_collector_mode_t   *collector_mode_p);

/**
 * This API enables/disables distribution on a specific LAG port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] lag_log_port     - Logical port number representing the LAG's port group
 * @param[in] log_port         - Logical port number
 * @param[in] distributor_mode - Distributor mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if requested element already exists
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 */
sx_status_t sx_api_lag_port_distributor_set(const sx_api_handle_t       handle,
                                            const sx_port_log_id_t      lag_log_port,
                                            const sx_port_log_id_t      log_port,
                                            const sx_distributor_mode_t distributor_mode);


/**
 * This API returns information whether distribution is enabled or disabled on a specific port in a LAG port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] lag_log_port        - Logical port number representing the LAG's port group
 * @param[in] log_port            - Logical port number
 * @param[out] distributor_mode_p - Distributor mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 */

sx_status_t sx_api_lag_port_distributor_get(const sx_api_handle_t  handle,
                                            const sx_port_log_id_t lag_log_port,
                                            const sx_port_log_id_t log_port,
                                            sx_distributor_mode_t *distributor_mode_p);

/**
 * This API configures the flow indicators that impact the LAG hash distribution function.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 *  @param[in] handle               - SX-API handle
 *  @param[in] lag_hash_param_p     - Hash parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_NO_MEMORY if memory allocation fails
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 */
sx_status_t sx_api_lag_hash_flow_params_set(const sx_api_handle_t      handle,
                                            const sx_lag_hash_param_t *lag_hash_param_p);


/**
 * This API sets the ingress port configuration parameters of LAG hash. Once this API is called,
 * sx_api_lag_hash_flow_params_set is disabled.
 *
 * SET replaces existing hash parameters, enables field, and sets fields with new values.
 * ADD adds new fields and enables fields on top of the existing fields (hash parameters are ignored).
 * DELETE deletes specific fields and disable fields from the existing fields (hash parameters are ignored).
 *   Each element in hash_field_enable_list_p enables a specific layer field to be included in the hash calculation according to
 *   the de-facto fields of the parsed packet.
 *   Each element in hash_field_list_p represents a different field to be included in the hash calculation, subject to
 *   the enables which are given in hash_field_enable_list_p.
 *
 * Note: LAG hash parameters are configured per ingress port and impact egress LAG.
 * Note: In hash parameters, seed is global (i.e., the last configured seed will be used).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                     - SX-API handle
 * @param[in] cmd                        - SET/ADD/DELETE
 * @param[in] log_port                   - Log port ID of ingress port
 * @param[in] lag_hash_params_p          - LAG hash configuration parameters
 * @param[in] hash_field_enable_list_p   - Array of enables to be included in the hash calculation (may be NULL if empty)
 * @param[in] hash_field_enable_list_cnt - Number of elements in hash_field_enable_list_p
 * @param[in] hash_field_list_p          - Array of fields to be included in the hash calculation (may be NULL if empty)
 *                                         Note: on Spectrum devices, custom_bytes are not supported
 * @param[in] hash_field_list_cnt        - Number of elements in hash_field_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if parameter is incorrectly NULL
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_PARAM_ERROR if a parameter has an invalid value
 */

sx_status_t sx_api_lag_port_hash_flow_params_set(const sx_api_handle_t             handle,
                                                 const sx_access_cmd_t             cmd,
                                                 const sx_port_log_id_t            log_port,
                                                 const sx_lag_port_hash_params_t  *hash_params_p,
                                                 const sx_lag_hash_field_enable_t *hash_field_enable_list_p,
                                                 const uint32_t                    hash_field_enable_list_cnt,
                                                 const sx_lag_hash_field_t        *hash_field_list_p,
                                                 const uint32_t                    hash_field_list_cnt);


/**
 * This API retrieves the flow indicators that impact the LAG hash distribution function.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle               - SX-API handle
 * @param[out] lag_hash_param_p    - Hash parameters retrieved
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_UNSUPPORTED if per-port API has already been invoked
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_lag_hash_flow_params_get(const sx_api_handle_t handle,
                                            sx_lag_hash_param_t  *lag_hash_param_p);

/**
 * This API gets the given port's LAG hash function configuration parameters.
 * If the given number of fields / field enables is 0, the API will only return
 * the number of fields / field enables.
 * Once this API is called sx_api_lag_hash_flow_params_get is disabled
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]     handle                       - SX-API handle
 * @param[in]     log_port                     - Local port
 * @param[out]    lag_hash_params_p            - LAG hash configuration parameters
 * @param[out]    hash_field_enable_list_p     - Array of enables used in the hash calculation
 * @param[in/out] hash_field_enable_list_cnt_p - Number of objects in hash_field_list_p
 * @param[out]    hash_field_list_p            - Array of fields used in the hash calculation
 * @param[in/out] hash_field_list_cnt_p        - Number of objects in hash_field_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if any of the count parameters has an invalid value
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_ENTRY_NOT_FOUND if the LAG is not found
 */
sx_status_t sx_api_lag_port_hash_flow_params_get(const sx_api_handle_t       handle,
                                                 const sx_port_log_id_t      log_port,
                                                 sx_lag_port_hash_params_t  *lag_hash_params_p,
                                                 sx_lag_hash_field_enable_t *hash_field_enable_list_p,
                                                 uint32_t                   *hash_field_enable_list_cnt_p,
                                                 sx_lag_hash_field_t        *hash_field_list_p,
                                                 uint32_t                   *hash_field_list_cnt_p);

/**
 * This API creates/destroys a redirection between a LAG and a destination LAG. Redirection does not align LAG configuration,
 * only TX traffic.
 *
 * Note: Redirect operation is valid only between 2 LAGs. A chain of redirected LAGs cannot be created.
 * Note: Redirect is a L2 action and is not valid for router ports.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - CREATE/DESTROY
 * @param[in] lag_log_port          - LAG logical ID
 * @param[in] redirect_lag_log_port - LAG logical ID which lag_log_port now points to (ignored in DESTROY)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 */
sx_status_t sx_api_lag_redirect_set(const sx_api_handle_t  handle,
                                    const sx_access_cmd_t  cmd,
                                    const sx_port_log_id_t lag_log_port,
                                    const sx_port_log_id_t redirect_lag_log_port);

/**
 * This API returns information stating whether a given LAG is redirected. For a LAG that was redirected, the LAG logical ID
 * is returned.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                     - SX-API handle
 * @param[in] lag_log_port               - LAG logical ID
 * @param[out] is_redirected_p           - Is lag_port redirected
 * @param[out] redirected_lag_log_port_p - LAG logical ID which lag_log_port points to when the LAG is redirected
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 */
sx_status_t sx_api_lag_redirect_get(const sx_api_handle_t  handle,
                                    const sx_port_log_id_t lag_log_port,
                                    boolean_t             *is_redirected_p,
                                    sx_port_log_id_t      *redirected_lag_log_port_p);

/**
 * This API returns all the LAGs that are redirected to the given LAG.
 * Calling this API with lag_log_port_list_p=NULL will return the  number of LAGs redirected to lag_port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] lag_log_port              - LAG logical ID
 * @param[in,out] lag_log_port_list_p   - Pointer to array of LAG port lists
 * @param[in,out] lag_log_port_cnt_p    - Number of LAG ports in a list retrieve
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a lag_log_port_cnt_p is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 */
sx_status_t sx_api_lag_redirected_lags_get(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t lag_log_port,
                                           sx_port_log_id_t      *lag_log_port_list_p,
                                           uint32_t              *lag_log_port_cnt_p);

/**
 * This API sets/deletes a fine grained LAG distribution list.
 * LAG distribution will be according to the given port list with relative weight.
 *
 * SET sets a LAG distribution list according to port list with relative weight.
 * ADD adds ports to the existing LAG distribution list.
 * DELETE deletes ports from distribution list.
 * DELETE ALL returns to the default distribution function.
 *
 * Note: Setting the distribution list is optional and only affects unicast traffic.
 * Note: In case the distribution list is not set, the hash will be done according to the LAG member ports.
 * Note: A port does not have to be a LAG member.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] access_cmd   - SET/ADD/DELETE/DELETE_ALL
 *
 * @param[in] lag_log_port - logical port number representing the LAG
 * @param[in] params_p     - Fine grain LAG parameters (controls the resolution of the distribution list)
 *                           Note: valid for SET command only
 * @param[in] port_list_p  - List of ports to SET/ADD/DELETE distribution list with weights
 *                           Note: On ADD, the members should not exist in the LAG distribution list
 *                           Note: On DELETE, the members should exist in the LAG distribution list
 * @param[in] port_cnt     - Number of elements on port_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_PARAM_ERROR if a parameter is invalid
 * @return SX_STATUS_NO_RESOURCES if there are no more resources
 * @return SX_STATUS_CMD_UNSUPPORTED if the access Command is not supported
 */
sx_status_t sx_api_lag_distributer_list_set(const sx_api_handle_t             handle,
                                            const sx_access_cmd_t             access_cmd,
                                            const sx_port_log_id_t            lag_log_port,
                                            const sx_lag_fine_grain_params_t *params_p,
                                            const sx_lag_fine_grain_member_t *port_list_p,
                                            const uint32_t                    port_cnt);

/**
 * This API retrieves a fine grained LAG distribution list and the fine grain LAG parameters.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] lag_log_port       - logical port number representing the LAG
 * @param[out] params_p          - the fine grained lag parameters
 * @param[out] port_list_p       - list of ports and weights in the advance distribution port list
 * @param[in/out] port_cnt_p     - number of ports in the distribution list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_PARAM_ERROR if a parameter is invalid
 */
sx_status_t sx_api_lag_distributer_list_get(const sx_api_handle_t       handle,
                                            const sx_port_log_id_t      lag_log_port,
                                            sx_lag_fine_grain_params_t *params_p,
                                            sx_lag_fine_grain_member_t *port_list_p,
                                            uint32_t                   *port_cnt_p);


#endif /* __SX_API_LAG_H__ */
