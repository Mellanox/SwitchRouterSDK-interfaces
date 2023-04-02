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

#ifndef __SX_API_FLEX_PARSER_H__
#define __SX_API_FLEX_PARSER_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/
/**
 * This API sets the log verbosity level of FLEX_PARSER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Set verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - FLEX_PARSER module verbosity level
 * @param[in] api_verbosity_level      - FLEX_PARSER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */


sx_status_t sx_api_flex_parser_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                       const sx_log_verbosity_target_t verbosity_target,
                                                       const sx_verbosity_level_t      module_verbosity_level,
                                                       const sx_verbosity_level_t      api_verbosity_level);


/**
 * This API gets the log verbosity level of FLEX_PARSER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Get verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - FLEX_PARSER module verbosity level
 * @param[out] api_verbosity_level_p    - FLEX_PARSER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_NULL if an input parameter is invalid
 */

sx_status_t sx_api_flex_parser_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                       const sx_log_verbosity_target_t verbosity_target,
                                                       sx_verbosity_level_t           *module_verbosity_level_p,
                                                       sx_verbosity_level_t           *api_verbosity_level_p);


/**
 * This API initializes the flex parser module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * Parameters:
 * @param[in]    handle     - SX-API handle
 * @param[in]    params     - Configuration parameters for the initial state of the flex parser
 *                            (parameters for Spectrum is don't-care)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if the module is not supported by the platform
 * @return SX_STATUS_NO_RESOURCES if configuration fails due to a lack of hardware resources
 * @return SX_STATUS_ALREADY_INITIALIZED if module is already initialized.
 */

sx_status_t sx_api_flex_parser_init_set(const sx_api_handle_t         handle,
                                        const sx_flex_parser_param_t *params);


/**
 * This API de-initializes the flex parser module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * Parameters:
 * @param[in]    handle     - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MODULE_UNINITIALIZED if de-initialization is invoked without initialization
 * @return SX_STATUS_UNSUPPORTED if module is not supported by the platform
 */
sx_status_t sx_api_flex_parser_deinit_set(const sx_api_handle_t handle);


/**
 * This API enables/disables transition between two existing flex parser headers in the parse graph.
 * Caller must specify the header to enable the transition between "From" and "To" nodes.
 * Depending on the "To" (next protocol field) definition, the actual size of the value used may be less than 32 bits.
 *
 * Note: Some combination of flex parser headers may be unsupported and will return SX_STATUS_UNSUPPORTED.
 * Note: Spectrum systems only support the following:
 *  - Fixed header types
 *  - Transition from UDP to VxLAN with outer encapsulation level
 * Note: The API may impact the ISSU for Flex transition. To enable ISSU support user should use the new API (sx_api_flex_parser_flex_transition_set)
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * Parameters:
 * @param[in]    handle            - SX-API handle
 * @param[in]    cmd               - SX_ACCESS_CMD_SET/SX_ACCESS_CMD_UNSET
 * @param[in]    from              - Flex parser header to transition from (src)
 * @param[in]    to                - Flex parser next transition header information (dest)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_NO_RESOURCES if configuration fails due to a lack of hardware resources
 * @return SX_STATUS_MODULE_UNINITIALIZED if an API is called without initialization
 * @return SX_STATUS_CMD_UNSUPPORTED if invalid command is passed
 */

sx_status_t sx_api_flex_parser_transition_set(const sx_api_handle_t             handle,
                                              const sx_access_cmd_t             cmd,
                                              const sx_flex_parser_header_t     from,
                                              const sx_flex_parser_transition_t to);


/**
 * This API retrieves the configured transition information between given nodes in the parse graph.
 * Caller can start at the root and iterate over the results to traverse the entire parse graph.
 *
 * Note: Spectrum systems only support UDP as current header.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * Parameters:
 * @param [in]  handle         - SX-API handle
 * @param [in]  curr_ph        - The current flex parser header to transition from.
 * @param [out] next_trans_p   - A pointer to array of node transition structure.
 *                               If it is NULL, the next_trans_cnt variable is filled out
 *                               with numbers of transitions that could be retrieved.
 *                               If the pointer is valid, node transition info is placed
 *                               and next_trans_cnt takes actual number ports in array.
 * @param [out] next_trans_cnt - Specifies the number of items in the next_trans_p array.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_NO_RESOURCES if configuration fails due to a lack of hardware resources
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization
 * @return SX_STATUS_PARAM_NULL if next_trans_cnt parameter is NULL
 */
sx_status_t sx_api_flex_parser_transition_get(const sx_api_handle_t         handle,
                                              const sx_flex_parser_header_t curr_ph,
                                              sx_flex_parser_transition_t  *next_trans_p,
                                              uint32_t                     *next_trans_cnt);

/**
 * This API configures (ADD/DELETE/DELETE_ALL) multiple transitions between existing parser headers in
 * the parse graph. For each transition the caller must specify the headers to enable
 * the transition between "From" and "To" nodes.
 * Note that this API only supports transitions that involve at least one flex header (FPP).
 * For setting a transition involving only hard headers please refer to sx_api_flex_parser_hard_graph_set.
 * Note that some combinations of parser headers may be unsupported and will return SX_STATUS_UNSUPPORTED.
 * Note that the API may impact the ISSU for Flex transition. To enable ISSU support user should use the new API (sx_api_flex_parser_flex_transition_set)
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in]    handle             - SX-API handle
 * @param[in]    cmd                - SX_ACCESS_CMD_ADD / SX_ACCESS_CMD_DELETE / SX_ACCESS_CMD_DELETE_ALL
 * @param[in]    actions_list_p     - Pointer to a list of transition actions to perform (ignored by DELETE_ALL command).
 * @param[in]    actions_list_cnt   - The number of actions in the list pointed by actions_list_p (ignored by DELETE_ALL command).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform.
 * @return SX_STATUS_NO_RESOURCES if configuration fails due to a lack of HW resources
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 * @return SX_STATUS_CMD_UNSUPPORTED - if invalid cmd is passed
 */
sx_status_t sx_api_flex_parser_flex_graph_set(const sx_api_handle_t                handle,
                                              const sx_access_cmd_t                cmd,
                                              const sx_flex_parser_graph_action_t *actions_list_p,
                                              const uint32_t                       actions_list_cnt);
/**
 * This API configures (SET/UNSET/DELETE_ALL) multiple transitions between existing hard headers (HPH) in
 * the parse graph. For each transition the caller must specify the headers to enable
 * the transition between "From" and "To" nodes.
 * Note that this API supports transitions that involve hard headers only (such as MAC, IP, TCP etc).
 * Note that some combinations of parser headers may be unsupported and will return SX_STATUS_UNSUPPORTED.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in]    handle             - SX-API handle
 * @param[in]    cmd                - SX_ACCESS_CMD_SET / SX_ACCESS_CMD_UNSET / SX_ACCESS_CMD_DELETE_ALL
 * @param[in]    actions_list_p     - Pointer to a list of transition actions to perform (ignored by DELETE_ALL command).
 * @param[in]    actions_list_cnt   - The number of actions in the list pointed by actions_list_p (ignored by DELETE_ALL command).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform.
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 * @return SX_STATUS_CMD_UNSUPPORTED - if invalid cmd is passed
 */

sx_status_t sx_api_flex_parser_hard_graph_set(const sx_api_handle_t                handle,
                                              const sx_access_cmd_t                cmd,
                                              const sx_flex_parser_graph_action_t *actions_list_p,
                                              const uint32_t                       actions_list_cnt);


/**
 * This API configures the transition between two flex transition headers in the parse graph. The API supports ISSU.
 * User should invoke the API first to create the requested transition index and later to set the transition.
 * User must specify the transition index to be created.
 *
 * Notes
 * transition_cfg is not used if cmd is CREATE, DESTROY, and UNSET.
 * An entry with a given pair of {from_hdr, transition_value} must not exist more than once in the flex table.
 * On-the-fly change allowed only for fields: to_hdr.
 * Some combinations of flex parser headers may be unsupported and will return SX_STATUS_UNSUPPORTED.
 * This API is for flex transitions only. For hard transitions, use sx_api_flex_parser_transition_set().
 * This API supports ISSU.
 * For flex transitions, user should not mix this API with the other APIs (sx_api_flex_parser_flex_graph_set or sx_api_flex_parser_transition_set)
 *
 * Supported devices:  Spectrum2, Spectrum3, Spectrum4.
 *
 * Parameters:
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SX_ACCESS_CMD_CREATE/SX_ACCESS_CMD_DESTROY/SX_ACCESS_CMD_SET/SX_ACCESS_CMD_UNSET
 * @param[in] transition_index - Flex parser transition index (0-15)
 * @param[in] transition_cfg_p - Flex transition between headers information
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if the configuration is not supported by the platform
 * @return SX_STATUS_NO_RESOURCES if configuration fails due to a lack of hardware resources
 * @return SX_STATUS_MODULE_UNINITIALIZED if an API is called without initialization
 * @return SX_STATUS_CMD_UNSUPPORTED if an invalid command is passed
 */
sx_status_t sx_api_flex_parser_flex_transition_set(const sx_api_handle_t               handle,
                                                   const sx_access_cmd_t               cmd,
                                                   sx_flex_parser_transition_index_t  *transition_index_p,
                                                   sx_flex_parser_transition_action_t *transition_cfg_p);

/**
 * This API retrieves the configured transition information between two flex transition headers in the parse graph given the transition index.
 *
 * Note:
 * If the transition index passed to the API has not been configured in the system, then the transition_en field in transition_cfg_p will be 0.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * Parameters:
 * @param[in] handle - SX-API handle
 * @param[in] transition_index - Flex parser transition index (0-15)
 * @param[out] transition_cfg_p - Flex transition between headers information
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization
 *
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 */
sx_status_t sx_api_flex_parser_flex_transition_get(const sx_api_handle_t                   handle,
                                                   const sx_flex_parser_transition_index_t transition_index,
                                                   sx_flex_parser_transition_action_t     *transition_cfg_p);

/**
 * This API configures (CREATE/SET/DESTROY) a flexible parsing program (FPP).
 * This API can configure a flex parsing header (FPH), an empty FPH or a TLV options parsing (FTLV).
 * An FPP needs to be allocated first (CREATE cmd) before its parameters are set (SET cmd).
 * Note: an FPP used in a transition cannot be modified or destroyed.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in] handle    - SX-API handle
 * @param[in] cmd       - SX_ACCESS_CMD_CREATE / SX_ACCESS_CMD_SET / SX_ACCESS_CMD_DESTROY
 * @param[in] fpp_id    - The flex parsing program to configure
 * @param[in] fpp_cfg_p - Pointer to the configuration to apply to the FPP (ignored by CREATE & DESTROY commands).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if trying to create an FPP that already exists.
 * @return SX_STATUS_RESOURCE_IN_USE when trying to set / destroy an FPP used by a transition / other FPP.
 * @return SX_STATUS_ERROR general error.
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform.
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 */
sx_status_t sx_api_flex_parser_fpp_set(const sx_api_handle_t       handle,
                                       const sx_access_cmd_t       cmd,
                                       sx_flex_parser_fpp_id_t    *fpp_id_p,
                                       const sx_flex_parser_fpp_t *fpp_cfg_p);

/**
 * This API retrieves the configuration of a flexible parsing program (FPP).
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in]  handle    - SX-API handle
 * @param[in]  cmd       - SX_ACCESS_CMD_GET
 * @param[in]  fpp_id    - The flex parsing program to retrieve.
 * @param[out] fpp_cfg_p - Pointer to the configuration to filled by the API.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 */
sx_status_t sx_api_flex_parser_fpp_get(const sx_api_handle_t         handle,
                                       const sx_access_cmd_t         cmd,
                                       const sx_flex_parser_fpp_id_t fpp_id,
                                       sx_flex_parser_fpp_t         *fpp_cfg_p);
/**
 * This API configures (SET/UNSET) the root of a parsing graph for the specified logical ports.
 * By default, each port is configured with start of parsing (SOP) from the MAC header.
 * This API can change the root parsing header to be a specified FPP.
 * Note: FTLV cannot be set as a root parsing header.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in]  handle          - SX-API handle
 * @param[in]  cmd             - SX_ACCESS_CMD_SET / SX_ACCESS_CMD_UNSET
 * @param[in]  root_cfg_list_p - Pointer to a list of ports & FPP for which to set/unset the parsing root.
 * @param[in]  root_cfg_cnt    - Number of elements in the list.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 */
sx_status_t sx_api_flex_parser_root_set(const sx_api_handle_t                handle,
                                        const sx_access_cmd_t                cmd,
                                        const sx_flex_parser_root_sop_cfg_t *root_cfg_list_p,
                                        const uint32_t                       root_cfg_cnt);

/**
 * This API retrieves the configured root parsing header for the specified logical port.
 * If this API is called with root_sop_cfg_list_p parameter set to NULL or *root_sop_cfg_cnt_p set to 0,
 * it will return the actual number of root parsing configurations that exist.
 * For GET command, the parsing header associated with the logical port will be returned.
 * For GET_FIRST command, the first logical port in the DB with an associated parsing header will be retrieved.
 * For GETNEXT command, the next port after logical port in the DB with an associated parsing header will be retrieved.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in]     handle              - SX-API handle
 * @param[in]     cmd                 - SX_ACCESS_CMD_GET / SX_ACCESS_CMD_GET_FIRST / SX_ACCESS_CMD_GETNEXT
 * @param[in]     logical_port        - The logical port for which to retrieve the root SOP -
 *                                      relevant only for SX_ACCESS_CMD_GET & SX_ACCESS_CMD_GETNEXT cmd.
 * @param[in/out] root_sop_cfg_list_p - Pointer to a list SOP entries to be retrieved.
 * @param[in/out] root_sop_cfg_cnt_p  - IN - Specifies the size of the list to be retrieved.
 *                                      OUT - The number of entries that were actually retrieved.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 */
sx_status_t sx_api_flex_parser_root_get(const sx_api_handle_t          handle,
                                        const sx_access_cmd_t          cmd,
                                        const sx_port_log_id_t         log_port,
                                        sx_flex_parser_root_sop_cfg_t *root_sop_cfg_list_p,
                                        uint32_t                      *root_sop_cfg_cnt_p);

/**
 * This API sets the configuration for the specified hard parser header (HPH).
 * Currently this supports setting a FTLV options parsing only.
 * Note: not all HPH supports FTLV configuration, SX_STATUS_UNSUPPORTED will be returned in such a case.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in]  handle    - SX-API handle
 * @param[in]  cmd       - SX_ACCESS_CMD_SET / SX_ACCESS_CMD_UNSET
 * @param[in]  hph_id    - The hard parsing header to configure.
 * @param[in]  hph_cfg_p - Pointer to the configuration to apply to this header (relevant only for SX_ACCESS_CMD_SET cmd).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 */

sx_status_t sx_api_flex_parser_hph_set(const sx_api_handle_t         handle,
                                       const sx_access_cmd_t         cmd,
                                       const sx_flex_parser_hph_id_t hph_id,
                                       const sx_flex_parser_hph_t   *hph_cfg_p);

/**
 * This API retrieves the configuration of a hard parsing header (HPH).
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in]  handle    - SX-API handle
 * @param[in]  cmd       - SX_ACCESS_CMD_GET
 * @param[in]  hph_id    - The hard header to retrieve.
 * @param[out] hph_cfg_p - Pointer to the configuration to filled by the API.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 */

sx_status_t sx_api_flex_parser_hph_get(const sx_api_handle_t         handle,
                                       const sx_access_cmd_t         cmd,
                                       const sx_flex_parser_hph_id_t hph_id,
                                       sx_flex_parser_hph_t         *hph_cfg_p);

/**
 * This API is used to create / destroy flexible extraction points (FEXP)
 * to be used as part of FPPs.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in]  handle    - SX-API handle
 * @param[in]  cmd       - SX_ACCESS_CMD_CREATE / SX_ACCESS_CMD_DESTROY
 * @param[in]  fexp_id_p - The flexible extraction point to allocate.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if trying to create an FEXP that already exists.
 * @return SX_STATUS_RESOURCE_IN_USE when trying to destroy an FEXP used by an FPP.
 * @return SX_STATUS_ERROR general error.
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform.
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 */

sx_status_t sx_api_flex_parser_fexp_set(const sx_api_handle_t     handle,
                                        const sx_access_cmd_t     cmd,
                                        sx_flex_parser_fexp_id_t *fexp_id_p);

/**
 * This API retrieves the current resources use of the flex parser.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in]  handle                  - SX-API handle
 * @param[in]  cmd                     - SX_ACCESS_CMD_GET
 * @param[out] flex_parser_resources_p - Pointer to the resource information to be retrieved.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 */

sx_status_t sx_api_flex_parser_resources_get(const sx_api_handle_t       handle,
                                             const sx_access_cmd_t       cmd,
                                             sx_flex_parser_resources_t *flex_parser_resources_p);

/**
 * This API sets/un-sets list of extraction points for a given register key.
 * The register can have up to 4 extraction points. When extracting, the last extraction point will be taken.
 * This API, together with sx_api_register_set, replaces sx_api_acl_custom_bytes_set, where general purpose register N
 * represents a set of custom byte 2N and custom byte 2N+1.
 *
 * Note: This API, together with sx_api_register_set, is mutually exclusive with sx_api_acl_custom_bytes_set.
 * As such, in a single SDK life cycle, only one of them can be used.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param [in] handle           - SX-API handle
 * @param [in] cmd              - SET/UNSET
 * @param [in] reg_key          - Register key
 * @param [in] ext_point_list_p - List of extraction points
 * @param [in] ext_point_cnt_p  - Number of items in ext_point_list_p (max 4)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_PARAM_ERROR if reg_key is not allocated or extraction point is not valid
 * @return SX_STATUS_PARAM_NULL if ext_point_cnt_p or ext_point_list_p is NULL
 */
sx_status_t sx_api_flex_parser_reg_ext_point_set(const sx_api_handle_t        handle,
                                                 const sx_access_cmd_t        cmd,
                                                 const sx_register_key_t      reg_key,
                                                 const sx_extraction_point_t *ext_point_list_p,
                                                 const uint32_t              *ext_point_cnt_p);

/**
 * This API returns the first ext_point_cnt_p extraction points of a given register key.
 * Returned ext_point_cnt_p may be less than or equal to the requested ext_point_cnt_p.
 * When ext_point_list_p is NULL, ext_point_cnt_p will be set with a number of extraction points.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param [in] handle               - SX-API handle
 * @param [in] reg_key              - Register key
 * @param [in,out] ext_point_list_p - [in] If NULL, set ext_point_cnt_p with number of extraction points
 *                                    [out] list of extraction points
 * @param [in,out] ext_point_cnt_p  - [in]  Number of extraction points to get
 *                                     [out] number of extraction points returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_PARAM_ERROR if reg_key is not allocated or does not exist
 * @return SX_STATUS_PARAM_NULL if extraction_point_cnt_p parameter is NULL
 */
sx_status_t sx_api_flex_parser_reg_ext_point_get(const sx_api_handle_t   handle,
                                                 const sx_register_key_t reg_key,
                                                 sx_extraction_point_t  *ext_point_list_p,
                                                 uint32_t               *ext_point_cnt_p);

#endif /* __SX_API_FLEX_PARSER_H__ */
