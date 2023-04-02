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

#ifndef __SX_API_FLOW_COUNTER_H__
#define __SX_API_FLOW_COUNTER_H__sdk

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/**
 * This API sets the log verbosity level of FLOW COUNTER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Set verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - FLOW COUNTER module verbosity level
 * @param[in] api_verbosity_level      - FLOW COUNTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameter is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_flow_counter_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        const sx_verbosity_level_t      module_verbosity_level,
                                                        const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of FLOW COUNTER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Get verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - FLOW COUNTER module verbosity level
 * @param[out] api_verbosity_level_p    - FLOW COUNTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameter is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_flow_counter_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        sx_verbosity_level_t           *module_verbosity_level_p,
                                                        sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This API is used to create packets/bytes counter. For creation, use CREATE and supply counter_type.
 *  flow_counter_id is returned upon successful creation. To destroy a flow counter, the flow counter must not be bound
 *  to an ACL and the flow_counter_id should be provided.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - CREATE/DESTROY
 * @param[in] counter_type     - Counter type used
 * @param[in,out] counter_id_p - Flow counter ID, as described above
 *
 *  @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 *  @return SX_STATUS_NO_RESOURCES if no flow counter is available to create
 *  @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 *  @return SX_STATUS_INVALID_HANDLE if called Invalid Handle
 *  @return SX_STATUS_ENTRY_NOT_FOUND if called with DESTROY command and the counter does not exist
 */
sx_status_t sx_api_flow_counter_set(const sx_api_handle_t        handle,
                                    const sx_access_cmd_t        cmd,
                                    const sx_flow_counter_type_t counter_type,
                                    sx_flow_counter_id_t        *counter_id_p);

/**
 * This API is used to create a group of flow counters with consecutive counter IDs.
 * Counters can be of type packet, byte, both, or estimator.
 * CREATE creates a group of N counters of the given type using counter type and N=count. If the API is unable to create the
 *   given count of counters, then the API will return SX_STATUS_NO_RESOURCES error.
 * DESTROY destroys a counter's group using a base counter ID. When destroying counters, all counters must no longer be
 *   bound/in-use, otherwise the API will return SX_STATUS_RESOURCE_IN_USE error.
 *
 * Note: Using this API may cause fragmentation in flow counter resource.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - CREATE/DESTROY
 * @param[in] bulk_attr       - Counter type used and number of counters
 * @param[in,out] bulk_data_p - Flow counter base ID, as described above
 *
 *  @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_NULL if bulk_data_p is NULL
 *  @return SX_STATUS_RESOURCE_IN_USE if called with the cmd DESTROY and one or more flow counter ID in range is bound/in-use
 *  @return SX_STATUS_NO_RESOURCES if no continuous bulk of flow counter IDs is available to create
 *  @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 *  @return SX_STATUS_INVALID_HANDLE if called Invalid Handle
 *  @return SX_STATUS_ENTRY_NOT_FOUND if called with DESTROY command and counter does not exist
 *  @return SX_STATUS_UNSUPPORTED if counter type is not supported
 */
sx_status_t sx_api_flow_counter_bulk_set(const sx_api_handle_t             handle,
                                         const sx_access_cmd_t             cmd,
                                         const sx_flow_counter_bulk_attr_t bulk_attr,
                                         sx_flow_counter_bulk_data_t      *bulk_data_p);

/**
 * This API retrieves the Flow Counter.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] counter_id - Flow counter ID
 * @param[out] counter_val_p - Counter value
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if event mode is out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if there is a message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds the limit
 * @return SX_STATUS_COMM_ERROR Communication error (failure to send)
 * @return SX_STATUS_INVALID_HANDLE if called Invalid Handle
 */
sx_status_t sx_api_flow_counter_get(const sx_api_handle_t      handle,
                                    const sx_access_cmd_t      cmd,
                                    const sx_flow_counter_id_t counter_id,
                                    sx_flow_counter_set_t     *counter_set_p);

/**
 * This API gets a list of flow counters.
 *
 * Note:
 *  The API can return up to SX_FLOW_COUNTER_ITER_GET_MAX counters.
 *  To get all the counters in the system, the API can be called first with the SX_ACCESS_CMD_GET_FIRST command,
 *  and then, if needed, it can be called with the SX_ACCESS_CMD_GETNEXT command multiple times until
 *  an empty list is returned.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd   - GET/GET_NEXT/GET_FIRST
 * @param[in] counter_id_key - Flow counter ID to use and key
 * @param[in] counter_filter_p - Filter to use
 * @param[out] counter_id_list_p - Pointer to the list of flow counter IDs returned
 * @param[in,out] counter_id_cnt_p - [in] number of entries to retrieve/[out] retrieved number of entries.
 *
 * The following use case scenarios apply with different input parameters. X = don't-care.
 *   1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, list = X, Count =0:
 *        In this case, the API will return the total number of flow counters in the internal database.
 *
 *   2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, list = Valid, Count = 1:
 *        In this case, the API will check if the specified key exists. If it does, the key will be returned in the list
 *        along with a count of 1. If the key does not exist, an empty list will be returned with count = 0.
 *
 *   3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = X, list is Valid, Count > 1:
 *        A count >1 will be treated as a count of 1 and the behaviour will be same as earlier GET use cases.
 *
 *   4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X,
 *        hist_list = Null, Count =0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT a zero count
 *        will return an empty list.
 *
 *   5) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = X, list = Valid, Count > 0:
 *        In this case, the API will return the first flow counters starting from the head of the database. The total elements
 *        fetched will be returned as the return count.
 *       Note: The return count may be less than or equal to the requested count. The key is dont-care, but a non-Null return
 *        list pointer must be provided.
 *
 *   6) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = X, list = Valid, Count > 0:
 *        In this case, the API will return the next set of counters starting from the next valid counter after the specified
 *        key. The total elements fetched will be returned as the return count.
 *       Note: The return count may be less than or equal to the requested count. If no valid next counter exists in the database
 *        (key = end of list, invalid key specified, or key too large), an empty list will be returned.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range
 * @return SX_STATUS_PARAM_ERROR if parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_INVALID_HANDLE if handle in invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_flow_counter_iter_get(const sx_api_handle_t      handle,
                                         const sx_access_cmd_t      cmd,
                                         const sx_flow_counter_id_t counter_id_key,
                                         sx_flow_counter_filter_t  *counter_filter_p,
                                         sx_flow_counter_id_t      *counter_id_list_p,
                                         uint32_t                  *counter_id_cnt_p);


/**
 * This API clears a specific flow counter.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] counter_id - Flow counter ID to clear
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if event mode is out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if there is a message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds the limit
 * @return SX_STATUS_COMM_ERROR if there is a communication error (failure to send)
 * @return SX_STATUS_INVALID_HANDLE if called Invalid Handle
 * @return SX_STATUS_ENTRY_NOT_FOUND if an invalid counter was cleared
 */
sx_status_t sx_api_flow_counter_clear_set(const sx_api_handle_t      handle,
                                          const sx_flow_counter_id_t counter_id);

/**
 * This API retrieves the Flow Counter.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] cmd            - READ/READ_CLEAR
 * @param[in] counter_id     - Flow estimator counter ID
 * @param[out] counter_val_p - Counter value
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if invalid command is passed
 * @return SX_STATUS_ENTRY_NOT_FOUND if the counter does not exist
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if params are out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if there is a message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds the limit
 * @return SX_STATUS_COMM_ERROR Communication error (failure to send)
 * @return SX_STATUS_INVALID_HANDLE if called Invalid Handle
 * @return SX_STATUS_PARAM_ERROR if called Invalid Handle
 */
sx_status_t sx_api_flow_counter_estimator_get(const sx_api_handle_t            handle,
                                              const sx_access_cmd_t            cmd,
                                              const sx_flow_counter_id_t       counter_id,
                                              sx_flow_estimator_counter_set_t *counter_val_p);

/*
 * This API supports to CREATE/SET/DESTROY a profile with specific params.
 * For CREATE:
 *  Create a profile with specific hash params and bin group size. If the profile key exists, API will fail and return
 *  "SX_STATUS_ENTRY_ALREADY_EXISTS".
 *  1) "hash_params" contains various flow estimator profile hash params.
 *      - If "hash_params" is not NULL, those hash params will overwrite the profile's current params;
 *      - if it is NULL, default hash params (with only SIP/DIP/SPort/DPort/Protocol fields be enabled) will be set.
 *  2) bin_group_size specifies the number of flow estimator bins (buckets) for flow cardinality calculations.
 *      - The bin_group_size should only be set with values of 16, 32, 64, 128, 256, 512, other values are
 *        invalid and would be refused with "SX_STATUS_PARAM_EXCEEDS_RANGE"
 *      - bin_group_size also determines counter_num of flow counter to be allocated (via sx_api_flow_counter_bulk_set)
 *        and bound with the profile in an ACL action, i.e.,
 *             counter_num = bin_group_size / FLOW_ESTIMATOR_BINS_PER_FLOW_COUNTER
 *        where FLOW_ESTIMATOR_BINS_PER_FLOW_COUNTER is a macro 4.
 *     Example:
 *         - Users call this API to create a profile with bin_group_size = 64.
 *         - Users should calculate the required counter_num, which should be 16 (=64/4),
 *         - Users call sx_api_flow_counter_bulk_set() to create the specific flow counters,
 *           with counter_num = 16, type = SX_FLOW_COUNTER_TYPE_ESTIMATOR.
 *
 * For SET:
 *  Set a profile with specific hash params and bin group size. If the profile key is not created, fails with
 *  "SX_STATUS_ENTRY_NOT_FOUND".
 *  1) "hash_params" contains profile hash params.
 *      - If "hash_params" is not NULL, those hash params will overwrite the profile's current params;
 *      - If it is NULL, default hash params (with only SIP/DIP/SPort/DPort/Protocol fields be enabled) will be set.
 *  2) bin_group_size specifies the number of flow estimator bins (buckets) for cardinality calculations.
 *      - If the profile is in use, its bin_group_size cannot be changed. In that case, the input value
 *        should be equivalent to the profile's existing value. Otherwise, it fails with "SX_STATUS_RESOURCE_IN_USE".
 *      - Other description please see bin_group_size above in "CREATE".
 *
 * For DESTROY:
 *  Un-allocate the specific profile key. If the profile key is not created, fails with "SX_STATUS_ENTRY_NOT_FOUND".
 *  If the profile key is still used in some ACL actions, fails with "SX_STATUS_RESOURCE_IN_USE".
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                     - SX-API handle
 * @param[in] cmd                        - CREATE/SET/DESTROY
 * @param[in] profile_key                - flow estimator profile key
 * @param[in] profile_cfg_p              - flow estimator profile parameters. Ignored and can be NULL for cmd = DESTROY
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE or SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_NO_MEMORY if no memory is available
 * @return SX_STATUS_CMD_ERROR if invalid command is passed or internal RPC mechanism to SDK server fails
 * @return SX_STATUS_INVALID_HANDLE if called Invalid Handle
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS  fails because the profile key has been already created.
 * @return SX_STATUS_RESOURCE_IN_USE   fails because of the profile being bound to some ACL actions. Details see SET/DESTROY descriptions.
 * @return SX_STATUS_ENTRY_NOT_FOUND   fails because of the profile is not created. Details see SET/DESTROY descriptions.
 */
sx_status_t sx_api_flow_estimator_profile_set(const sx_api_handle_t                  handle,
                                              const sx_access_cmd_t                  cmd,
                                              const sx_flow_estimator_profile_key_t  profile_key,
                                              const sx_flow_estimator_profile_cfg_t *profile_cfg_p);

/*
 * This API retrieves a flow estimator profile's configuration.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                     - SX-API handle
 * @param[in] profile_key                - flow estimator profile key
 * @param[out] profile_p                 - flow estimator profile attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if parameter is NULL or exceeds range
 * @return SX_STATUS_ENTRY_NOT_FOUND if the profile_key is not found
 * @return SX_STATUS_CMD_ERROR if invalid command is passed or internal RPC mechanism to SDK server fails
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_flow_estimator_profile_get(const sx_api_handle_t                 handle,
                                              const sx_flow_estimator_profile_key_t profile_key,
                                              sx_flow_estimator_profile_attr_t     *profile_attr_p);

/**
 * This API returns a list of one or more flow estimator profile keys.
 *  The following use case scenarios apply with different input parameters. X = don't-care.
 *   1) cmd = SX_ACCESS_CMD_GET, profile_key = X, profile_list = X, profile_cnt = 0:
 *        In this case, the API will return the total number of profile containers in the internal database.
 *
 *   2) cmd = SX_ACCESS_CMD_GET, profile_key = valid/invalid, profile_list = valid, profile_cnt = 1:
 *        In this case, the API will check if the specified profile key exists.  If it does, the profile key will
 *        be returned in the profile_list along with a profile_cnt of 1.
 *        If the key does not exist, an empty list will be returned with profile_cnt = 0. In this case, a non-NULL profile_list
 *        pointer must be provided.
 *
 *   3) cmd = SX_ACCESS_CMD_GET, profile_key = valid/invalid, profile_key_list = valid, profile_cnt > 1:
 *        An profile_cnt > 1 will be treated as a profile_cnt of 1 and the behavior will be same as the earlier GET use cases.
 *
 *   4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, profile_key = X, profile_key_list = NULL, profile_key_cnt = 0:
 *        A zero profile_key_cnt and an empty profile_key_list will be returned.
 *
 *   5) cmd = SX_ACCESS_CMD_GET_FIRST, profile_key = X, profile_list = valid, profile_cnt > 0:
 *        In this case, the API will return the first profile_cnt profile keys starting from the head of the database.
 *        The total number of elements fetched will be returned as profile_cnt.
 *
 *        Note: Returned profile_cnt may be less than or equal to the requested profile_cnt. The key is ignored in this case.
 *        A non-NULL profile_list pointer must be provided in this case.
 *
 *   6) cmd = SX_ACCESS_CMD_GETNEXT, profile_key = valid/invalid, profile_list = valid, profile_cnt > 0:
 *        In this case, the API will return the next set of profile keys starting from the next valid profile key
 *        after the specified profile key. The total number of elements fetched will be returned as the profile_cnt.
 *
 *        Note: returned profile_cnt may be less than or equal to the requested profile_cnt.
 *        If no valid next profile key exists in the database, an empty list will be returned.
 *        A non-NULL profile_list pointer must be provided in this case.
 *
 *  Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param [in] handle              - SX API handle
 * @param [in] cmd                 - GET/GET_FIRST/GET_NEXT
 * @param [in] profile_key         - Specify an profile key
 * @param [in] filter              - Specify a filter parameter (not supported yet)
 * @param [out] profile_list_p     - return list of profile keys
 * @param [in,out] profile_cnt_p   - [in] number of profile keys to get
 *                                 - [out] number of profile keys returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range
 * @return SX_STATUS_PARAM_NULL if an unexpected NULL parameter was passed
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_CMD_ERROR if invalid command is passed or internal RPC mechanism to SDK server fails
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_UNSUPPORTED if flow estimator profile is not supported
 * @return SX_STATUS_DB_NOT_INITIALIZED if internal profile database is not initialized
 */
sx_status_t sx_api_flow_estimator_profile_iter_get(const sx_api_handle_t                 handle,
                                                   const sx_access_cmd_t                 cmd,
                                                   const sx_flow_estimator_profile_key_t profile_key_key,
                                                   sx_flow_estimator_profile_filter_t   *profile_filter_p,
                                                   sx_flow_estimator_profile_key_t      *profile_key_list_p,
                                                   uint32_t                             *profile_key_cnt_p);

#endif /* ifndef __SX_API_FLOW_COUNTER_H__ */
