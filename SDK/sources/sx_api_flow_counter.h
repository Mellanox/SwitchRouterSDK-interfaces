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

#ifndef __SX_API_FLOW_COUNTER_H__
#define __SX_API_FLOW_COUNTER_H__sdk

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/**
 * This API sets the log verbosity level of FLOW COUNTER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
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
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
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
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
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
 * Counters can be of type packet, byte, or both.
 * CREATE creates a group of N counters of the given type using counter type and N=count. If the API is unable to create the
 *   given count of counters, then the API will return SX_STATUS_NO_RESOURCES error.
 * DESTROY destroys a counter's group using a base counter ID. When destroying counters, all counters must no longer be
 *   bound/in-use, otherwise the API will return SX_STATUS_RESOURCE_IN_USE error.
 *
 * Note: Using this API may cause fragmentation in flow counter resource.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
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
 */
sx_status_t sx_api_flow_counter_bulk_set(const sx_api_handle_t             handle,
                                         const sx_access_cmd_t             cmd,
                                         const sx_flow_counter_bulk_attr_t bulk_attr,
                                         sx_flow_counter_bulk_data_t      *bulk_data_p);

/**
 * This API retrieves the Flow Counter.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
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
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd   - GET/GET_NEXT/GET_FIRST
 * @param[in] counter_id_key - Flow counter ID to use and key
 * @param[in] counter_filter_p - Filter to use (not supported yet)
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
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
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

#endif
