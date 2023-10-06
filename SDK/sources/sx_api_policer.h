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

#ifndef __SX_API_POLICER_H__
#define __SX_API_POLICER_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of the POLICER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - POLICER module verbosity level
 * @param[in] api_verbosity_level      - POLICER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                   const sx_log_verbosity_target_t verbosity_target,
                                                   const sx_verbosity_level_t      module_verbosity_level,
                                                   const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of POLICER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - POLICER module verbosity level
 * @param[out] api_verbosity_level_p    - POLICER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                   const sx_log_verbosity_target_t verbosity_target,
                                                   sx_verbosity_level_t           *module_verbosity_level_p,
                                                   sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API creates/destroys/edits a policer in the system.
 *
 * CREATE creates a new policer and returns a policer ID in policer_id_p.
 * DESTROY destroys an existing policer (according to policer_id_p).
 * EDIT edits configuration parameters of an existing policer. Only CIR, EIR, EBS, CBS, yellow action and red action can be edited.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - CREATE/DESTROY/EDIT
 * @param[in] policer_attr_p   - Policer attributes (ignored when command is DESTROY)
 * @param[in,out] policer_id_p - Policer ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if supplied command is an unsupported one
 * @return SX_STATUS_PARAM_ERROR if any of the input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_NO_RESOURCES if there are no more resources
 * @return SX_STATUS_RESOURCE_IN_USE if trying to destroy a bound policer
 * @return SX_STATUS_WRONG_POLICER_TYPE if wrong policer_type was supplied
 */
sx_status_t sx_api_policer_set(const sx_api_handle_t          handle,
                               const sx_access_cmd_t          cmd,
                               const sx_policer_attributes_t *policer_attr_p,
                               sx_policer_id_t               *policer_id_p);

/**
 * This API gets the attributes of the given policer ID.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4
 *
 * @param[in] handle            - SX-API handle
 * @param[in] policer_id        - Policer ID
 * @param[out] policer_attr_p   - Pointer to policer attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested object is not found in database
 */
sx_status_t sx_api_policer_get(const sx_api_handle_t    handle,
                               const sx_policer_id_t    policer_id,
                               sx_policer_attributes_t *policer_attr_p);

/**
 * This API retrieves a list of Policer IDs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] cmd                  - GET/GET_NEXT/GET_FIRST
 * @param[in] policer_id_key       - Policer ID to use as key
 * @param[in] policer_filter_p     - Filter to use (not supported yet)
 * @param[out] policer_id_list_p   - Pointer to the list of Policer IDs returned
 * @param[in,out] policer_id_cnt_p - [in] number of entries to retrieve/[out] retrieved number of entries
 *
 * The following use case scenarios apply with different input parameters. X = don't-care.
 *   1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, list = X, Count = 0:
 *        In this case, the API will return the total number of policers in the internal database.
 *
 *   2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, list = Valid, Count = 1:
 *        In this case, the API will check if the specified key exists. If it does,  the key will be returned in the list
 *        along with a count of 1. If the key does not exist an empty list will be returned with count = 0.
 *
 *   3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = X, list is Valid, Count > 1:
 *        A count >1 will be treated as a count of 1 and the behaviour will be same as earlier GET use cases.
 *
 *   4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X, list = Null, Count = 0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT a zero count will return an empty list.
 *
 *   5) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = X, list = Valid, Count > 0:
 *        In this case, the API will return the first policer IDs starting from the head of the database.
 *        The total elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. The key is dont-care but a non-Null return
 *          list pointer must be provided.
 *
 *   6) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = X, list = Valid, Count > 0:
 *        In this case, the API will return the next set of IDs starting from  the next valid policer after the specified key.
 *        The total elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. If no valid next counter exists in the database
 *        (key = end of list, or invalid key specified, or key too large), an empty list will be returned.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_iter_get(const sx_api_handle_t   handle,
                                    const sx_access_cmd_t   cmd,
                                    const sx_policer_id_t   policer_id_key,
                                    sx_policer_id_filter_t *policer_id_filter_p,
                                    sx_policer_id_t        *policer_id_list_p,
                                    uint32_t               *policer_id_cnt_p);


/**
 * This API clears policer counters values.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] policer_id     - Policer ID
 * @param[in] clear_counters - Counters to be cleared
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_counters_clear_set(const sx_api_handle_t              handle,
                                              const sx_policer_id_t              policer_id,
                                              const sx_policer_counters_clear_t *clear_counters_p);

/**
 * This API retrieves policer counters values.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] policer_id          - Policer ID
 * @param[out] policer_counters_p - Pointer to a policer counter
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_counters_get(const sx_api_handle_t  handle,
                                        const sx_policer_id_t  policer_id,
                                        sx_policer_counters_t *policer_counters_p);

#endif /* __SX_API_POLICER_H__ */
