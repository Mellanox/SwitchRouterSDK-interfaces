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
#ifndef __SX_API_MPLS_H__
#define __SX_API_MPLS_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_mpls.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of MPLS module.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - MPLS module verbosity level
 * @param[in] api_verbosity_level      - MPLS API verbosity level
 *
 * @return sx_status_t
 */

sx_status_t sx_api_mpls_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of MPLS module.
 *
 * Supported devices: Spectrum.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - MPLS module verbosity level
 * @param[out] api_verbosity_level_p    - MPLS API verbosity level
 *
 * @return sx_status_t
 */

sx_status_t sx_api_mpls_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API initiates the MPLS module in SDK. This API can be called only after the router module is initialized.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] general_params_p - MPLS general parameters
 *
 * @return sx_status_t
 */

sx_status_t sx_api_mpls_init_set(const sx_api_handle_t           handle,
                                 const sx_mpls_general_params_t *general_params);

/**
 * This API de-initializes the MPLS block in the SDK. This API must be called before the router module is de-initialized if
 * MPLS block was initialized previously.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle     - SX-API handle
 *
 * @return sx_status_t
 */

sx_status_t sx_api_mpls_deinit_set(const sx_api_handle_t handle);

/**
 * This API creates an ILM table.
 *
 * Note: ilm_table can only be an MPLS VRID.
 *       MPLS label space is a router VRID.
 *       Only a single VRID is supported.
 *       This VRID contains all MPLS RIFs.
 *       The VRID needs to be created before calling this API.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] cmd       - CREATE/ADD/DELETE/DESTROY
 * @param[in] ilm_table - MPLS ILM table ID
 *
 * @return sx_status_t
 */

sx_status_t sx_api_mpls_ilm_init_set(const sx_api_handle_t        handle,
                                     const sx_access_cmd_t        cmd,
                                     const sx_mpls_ilm_table_id_t ilm_table);

/**
 * This API sets an in-segment parameters.
 *
 * Note: ilm_table can only be an MPLS VRID.
 *       MPLS label space is a router VRID.
 *       Only a single VRID is supported.
 *       This VRID contains all MPLS RIFs.
 *       The VRID needs to be created before calling this API.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - CREATE/EDIT/DESTROY
 * @param[in] in_segment_key_p       - In-segment incoming label
 * @param[in] in_segment_params_p    - Parameters for in-segment
 *
 * @return sx_status_t
 */

sx_status_t sx_api_mpls_in_segment_set(const sx_api_handle_t              handle,
                                       const sx_access_cmd_t              cmd,
                                       const sx_mpls_in_segment_key_t    *in_segment_key_p,
                                       const sx_mpls_in_segment_params_t *in_segment_params_p);

/**
 * This API gets in-segment parameters.
 *
 * Note: In-segment filter is currently unsupported.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] in_segment_key_p       - Specify a in-segment key
 * @param[out] in_segment_params_p   - List of in-segment params
 *
 * @return sx_status_t
 */

sx_status_t sx_api_mpls_in_segment_get(const sx_api_handle_t           handle,
                                       const sx_mpls_in_segment_key_t *in_segment_key_p,
                                       sx_mpls_in_segment_params_t    *in_segment_params_p);

/**
 * This API returns a list of one or more in-segment key identifiers.
 * The following use case scenarios apply with different input parameters
 * X = don't-care
 *   1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, in_segment_key_list = X, Count =0:
 *        In this case, the API will return the total number of in-segment keys in the ILM.
 *
 *   2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, in_segment_key_list = Valid, Count = 1:
 *        In this case, the API will check if the specified key exists. If it does, the key will be returned in the
 *        in_segment_key_list along with a count of 1. If the key does not exist, an empty list will be returned with count = 0
 *
 *   3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = X, in_segment_key_list is Valid, Count > 1:
 *        A count > 1 will be treated as a count of 1 and the behavior will be the same as earlier GET use cases.
 *
 *   4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X,  in_segment_key_list = Null, Count =0:
 *        For either SX_ACCESS_CMD_GET_FIRST or SX_ACCESS_CMD_GETNEXT, a zero count will return an empty list.
 *
 *   5) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = X, in_segment_key_list = Valid, Count > 0:
 *        In this case, the API will return the first count in-segments starting from the head of the database.
 *        The total elements fetched will be returned as the return count.
 *
 *         Note: Return count may be less than or equal to the requested count. The key is dont-care.
 *
 *   6) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = X, rif_list = Valid, Count > 0:
 *        In this case, the API will return the next set of in-segments starting from the next valid in segment k after the
 *        specified key. The total elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count.  If no valid next in-segment exists in the
 *         database (key = end of list, or invalid key specified, or key too large), an empty list will be returned. *
 *
 * Supported devices: Spectrum.
 *
 * @param [in] handle                           - SX API handle
 * @param [in] cmd                              - GET/GET_FIRST/GET_NEXT
 * @param [in] in_segment_key_p                 - Specify a in segment key
 * @param [in] filter                           - Specify a filter parameter
 * @param [out] in_segment_key_list_p           - Return list of in segment keys
 * @param [in,out] in_segment_get_entries_cnt_p - [in] number of in segments to get/[out] number of in segments returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range
 * @return SX_STATUS_PARAM_NULL if an unexpected NULL parameter was passed
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_CMD_UNSUPPORTED if invalid command is passed
 * @return SX_STATUS_MODULE_UNINITIALIZED  if a router module is uninitialized
 * @return SX_STATUS_CMD_ERROR if internal RPC mechanism to SDK server fails
 * @return SX_STATUS_DB_NOT_INITIALIZED if internal RIF database is not initialized
 */

sx_status_t sx_api_mpls_in_segment_iter_get(const sx_api_handle_t             handle,
                                            const sx_access_cmd_t             cmd,
                                            const sx_mpls_in_segment_key_t   *in_segment_key_p,
                                            const sx_in_segment_key_filter_t *filter_p,
                                            sx_mpls_in_segment_key_t         *in_segment_key_list_p,
                                            uint32_t                         *in_segment_get_entries_cnt_p);

/**
 * This API sets the MPLS attributes of the interface. It must be called to enable/disable MPLS on a router interface.
 *
 * Note: Only label space 0 is currently supported (ilm_table_id).
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] rif_p             - Router interface ID
 * @param[in] rif_mpls_attr_p   - MPLS attributes of the interface
 *
 * @return sx_status_t
 */

sx_status_t sx_api_mpls_router_interface_attributes_set(const sx_api_handle_t                 handle,
                                                        const sx_router_interface_t           rif,
                                                        const sx_mpls_router_interface_attr_t rif_mpls_attr);

/**
 * This API gets the MPLS attributes of the interface
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] rif_p            - Router interface ID
 * @param[out] rif_mpls_attr_p - MPLS attributes of the interface
 *
 * @return sx_status_t
 */

sx_status_t sx_api_mpls_router_interface_attributes_get(const sx_api_handle_t            handle,
                                                        const sx_router_interface_t      rif,
                                                        sx_mpls_router_interface_attr_t *rif_mpls_attr_p);

/**
 * This API binds or un-binds a flow counter to an existing ILM entry.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] cmd            - BIND/UNBIND
 * @param[in] in_segment_key - In-segment identification
 * @param[in] counter_id     - Flow counter identifier
 *
 * @return sx_status_t
 */
sx_status_t sx_api_mpls_ilm_counter_bind_set(const sx_api_handle_t           handle,
                                             const sx_access_cmd_t           cmd,
                                             const sx_mpls_in_segment_key_t *in_segment_key_p,
                                             const sx_flow_counter_id_t      counter_id);

/**
 * This API retrieves a flow counter identifier bounded to an existing ILM entry.
 *
 * Supported devices: Spectrum.
 *
 * @param[in]  handle           - SX-API handle
 * @param[in]  cmd              - GET
 * @param[in]  in_segment_key_p - In-segment identification
 * @param[out] counter_id_p     - A flow counter identifier
 *
 * @return sx_status_t
 */
sx_status_t sx_api_mpls_ilm_counter_bind_get(const sx_api_handle_t           handle,
                                             const sx_access_cmd_t           cmd,
                                             const sx_mpls_in_segment_key_t *in_segment_key_p,
                                             sx_flow_counter_id_t           *counter_id_p);

#endif /* __SX_API_MPLS_H__ */
