/*
 * Copyright (C) 2014-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_BFD_H__
#define __SX_API_BFD_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_bfd.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of BFD module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - BFD module verbosity level
 * @param[in] api_verbosity_level      - BFD API verbosity level
 *
 * @return SX_STATUS_SUCCESS         Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR     Input parameter is invalid
 * @return SX_STATUS_ERROR           General error
 */
sx_status_t sx_api_bfd_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);


/**
 * This API gets the log verbosity level of BFD module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - BFD module verbosity level
 * @param[out] api_verbosity_level_p    - BFD API verbosity level
 *
 * @return SX_STATUS_SUCCESS             Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR         An input parameter is invalid
 * @return SX_STATUS_ERROR               General error
 */
sx_status_t sx_api_bfd_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API is used to initialize BFD module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] params_p  - Pointer to init params structure
 *
 * @return SX_STATUS_SUCCESS          Operation completed successfully
 * @return SX_STATUS_NO_RESOURCES     Resource cannot be allocated
 * @return SX_STATUS_ERROR            General error
 */
sx_status_t sx_api_bfd_init_set(const sx_api_handle_t handle,
                                sx_bfd_init_params_t *params_p);

/**
 * This API is used to deinit BFD module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                - SX-API handle
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_bfd_deinit_set(const sx_api_handle_t handle);

/**
 * This API is used to create/edit/destroy BFD offload for a session.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] cmd                      - Command (CREATE/EDIT/DESTROY)
 * @param[in] session_params           - Parameters of the session
 * @param[in/out] session_id           - BFD session ID
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 *         SX_STATUS_ERROR                                                                General error
 */
sx_status_t sx_api_bfd_offload_set(const sx_api_handle_t          handle,
                                   const sx_access_cmd_t          cmd,
                                   const sx_bfd_session_params_t *session_params,
                                   sx_bfd_session_id_t           *session_id);


/**
 *  This function retrieves a list of BFD session IDs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - GET/GET_NEXT/GET_FIRST
 * @param[in] session_id_key        - BFD session ID to use as key
 * @param[in] session_filter_p      - Filter to use (not supported yet)
 * @param[out] session_id_list_p    - Pointer to the list of BFD session IDs returned
 * @param[in,out] session_id_cnt_p  - [in] number of entries to retrieve/[out] retrieved number of entries
 *
 * The following use case scenarios apply with different input parameters (X=don't care)
 *   - 1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, list = X, Count = 0:
 *        In this case the API will return the total number of BFD sessions in the
 *        internal db.
 *
 *   - 2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, list = Valid, Count = 1:
 *        In this case the API will check if the specified key exists. If it does,
 *        the key will be returned in the list along with a count of 1.
 *        If the key does not exist, an empty list will be returned with a count of 0.
 *
 *   - 3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = X, list = valid, Count > 1:
 *        A count > 1 will be treated as a count of 1 and the behaviour will be same as earlier GET use cases.
 *
 *   - 5) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X, list = Null, Count = 0:
 *        For either SX_ACCESS_CMD_GET_FIRST or SX_ACCESS_CMD_GETNEXT, a zero count will return an empty list.
 *
 *   - 6) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = X, list = Valid, Count > 0:
 *        In this case the API will return the first BFD session IDs starting from  the head of the database.
 *        The total elements fetched will be returned as the return count.
 *
 *        Note: return count may be less than or equal to the requested count.
 *        The key is dont-care, but a non-NULL return list pointer must be provided.
 *
 *   - 7) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = X, list = Valid, Count > 0:
 *        In this case, the API will return the next set of BFD session IDs starting from the next valid ID
 *        after the specified key. The total elements fetched will be returned as the return count.
 *
 *        Note: return count may be less than or equal to the requested count. If no valid next counter exists
 *        in the DB (key = end of list, or invalid key specified, or key too large), an empty list will be returned.
 *
 *
 * @return SX_STATUS_SUCCESS            Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR        Invalid parameter
 * @return SX_STATUS_CMD_UNSUPPORTED    Command is not supported
 * @return SX_STATUS_INVALID_HANDLE     Handle is invalid
 * @return SX_STATUS_ERROR              General error
 */
sx_status_t sx_api_bfd_session_iter_get(const sx_api_handle_t       handle,
                                        const sx_access_cmd_t       cmd,
                                        const sx_bfd_session_id_t   session_id_key,
                                        sx_bfd_session_id_filter_t *session_id_filter_p,
                                        sx_bfd_session_id_t        *session_id_list_p,
                                        uint32_t                   *session_id_cnt_p);


/**
 * This API is used to read/clear BFD offload statistics for a session.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] cmd                      - Command (READ/READ_CLEAR)
 * @param[in] session_type             - Command (SX_BFD_ASYNC_ACTIVE_RX/SX_BFD_ASYNC_ACTIVE_TX)
 * @param[in] session_id               - BFD session ID
 * @param[out] session_stats           - Statistics for the session
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 *         SX_STATUS_ERROR                                                                General error
 */
sx_status_t sx_api_bfd_offload_get_stats(const sx_api_handle_t       handle,
                                         const sx_access_cmd_t       cmd,
                                         const sx_bfd_session_type_t session_type,
                                         sx_bfd_session_id_t        *session_id,
                                         sx_bfd_offload_stats_t     *session_stats);


#endif /* ifndef __SX_API_BFD_H__ */
