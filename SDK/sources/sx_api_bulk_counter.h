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

#ifndef __SX_API_BULK_COUNTER_H__
#define __SX_API_BULK_COUNTER_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>
#include <sx/sdk/sx_bulk_counter.h>

/**
 * This function sets the log verbosity level of BULK COUNTER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API/MODULE/BOTH
 * @param[in] module_verbosity_level   - BULK COUNTER module verbosity level
 * @param[in] api_verbosity_level      - BULK COUNTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS                          Operation completed successfully
 *         SX_STATUS_PARAM_ERROR                      Any input parameters is invalid
 *         SX_STATUS_ERROR                            General error
 */
sx_status_t sx_api_bulk_counter_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        const sx_verbosity_level_t      module_verbosity_level,
                                                        const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of BULK COUNTER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - BULK COUNTER module verbosity level
 * @param[out] api_verbosity_level_p    - BULK COUNTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS                          Operation completed successfully
 *         SX_STATUS_PARAM_ERROR                      Any input parameters is invalid
 *         SX_STATUS_ERROR                            General error
 */
sx_status_t sx_api_bulk_counter_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        sx_verbosity_level_t           *module_verbosity_level_p,
                                                        sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API allocates or frees a buffer of an asynchronous bulk-counter-read operation.
 * Notes:
 *   1. Buffer is bound to key. An operation with a different key requires a new buffer.
 *   2. Buffer may be reused on multiple operations of sx_api_bulk_counter_transaction_set().
 *   3. Buffer operation must be completed or canceled before this function is called with SX_ACCESS_CMD_DESTROY command.
 *   4. A user cookie can be provided in buffer_p, so it can be used later to identify the event. So that the bulk counter
 *      done event can be registered and received in different process from the process where bulk counter buffer was created.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      -  SX-API handle
 * @param[in] cmd         -  CREATE to allocate buffer
 *                           DESTROY to free buffer
 * @param[in] key_p       -  Bulk-counter desired counters:
 *                           For port counters: list of logical port ID, list of priority IDs,
 *                                              list of TC IDs, list of priority groups.
 *                           For flow counters: range of flow counter IDs.
 *                           For elephant detected flows: a list of logical port IDs.
 *                           When cmd is DESTROY, key is ignored and can be NULL.
 * @param[in,out] buffer_p - On CREATE, returned allocated buffer to be used by other APIs.
 *                           On DESTROY, the buffer to deallocate.
 *
 * @return SX_STATUS_SUCCESS             Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE      NULL handle is received
 * @return SX_STATUS_PARAM_NULL          Parameter is NULL
 * @return SX_STATUS_PARAM_ERROR         Parameter error
 * @return SX_STATUS_CMD_UNSUPPORTED     Invalid command
 * @return SX_STATUS_NO_MEMORY           No free memory
 * @return SX_STATUS_RESOURCE_IN_USE     Buffer operation is running
 * @return SX_STATUS_ERROR               Operation failed
 */
sx_status_t sx_api_bulk_counter_buffer_set(const sx_api_handle_t            handle,
                                           const sx_access_cmd_t            cmd,
                                           const sx_bulk_cntr_buffer_key_t *key_p,
                                           sx_bulk_cntr_buffer_t           *buffer_p);

/**
 * This API initiates or cancels an asynchronous bulk-counter-read operation.
 *
 * READ reads a set of counters.
 * READ_CLEAR reads and clears a set of counters. Not supported for shared buffer type snapshot counter.
 * READ_FLUSH flushes and reads a set of counters (supported only for SX_BULK_CNTR_KEY_TYPE_FLOW_E).
 * READ_CLEAR_FLUSH flushes, reads, and clears a set of counters (supported only for SX_BULK_CNTR_KEY_TYPE_FLOW_E).
 * DISABLE cancels an active operation.
 *
 * Note: In "Normal" operation the SDK reads immediate value of the counter that can be different from its final value.
 *       "Flush" operation ensures that all device subsystems clear their cached values and final counter value is updated.
 * Note: After initiating the operation, an SX_BULK_READ_DONE event is sent and then API sx_api_bulk_counter_transaction_get()
 *  should be used. Until SX_BULK_READ_DONE event is received, buffer cannot be used with API sx_api_bulk_counter_transaction_get().
 *  And to identify the event is what's expected by user, user should compare the buffer id in event info with the one in buffer_p,
 *  cookie should be compared too if user provided it in API sx_api_bulk_counter_buffer_set().
 * Note: When initiating LAG port bulk-counter-read, its members are determined on operation initiation.
 *  Any change to the LAG port or to its members during the operation will not be reflected when reading the LAG counters
 *  upon operation completion.
 * Note: elephant-detected-flow-read does not support LAG ports.
 * Note: shared buffer key with type SX_BULK_CNTR_SHARED_BUFFER_SNAPSHOT_E should be used after calling
 * the API sx_api_cos_sb_snapshot_action_set with action SX_SB_SNAPSHOT_ACTION_TAKE_E.
 * Note: Upon disable, the buffer cannot be used on another operation or freed until the SW_BULK_READ_DONE event is received.
 * Note: Up to two transactions are allowed in parallel by the system:
 *           a. 2 x Port_Counters.
 *           b. Any combination of two different bulk counter types.
 *           c. The refresh transaction (consumed by calling sx_api_bulk_counter_refresh_set) and any of the bulk counter types.
 *           d. 2 x SX_BULK_CNTR_KEY_TYPE_FLOW_E only if one of transactions is started for
 *              accumulated (SX_FLOW_COUNTER_TYPE_ACCUMULATED) counters and the second one for any other type of flow counters.
 * Note: When port bulk counter transaction is in progress, it is not allowed to call any synchronous port counter API
 * (sx_api_port_counter_xxx).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - READ/READ_CLEAR/READ_FLUSH/READ_CLEAR_FLUSH/DISABLE
 * @param[in] buffer_p    - Valid buffer which was allocated by sx_api_bulk_buffer_set().
 *
 * @return SX_STATUS_SUCCESS             Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if cmd value is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if cmd is not valid
 * @return SX_STATUS_RESOURCE_IN_USE if there is another operation with same type in-flight
 * @return SX_STATUS_ERROR if operation completes with failure
 */
sx_status_t sx_api_bulk_counter_transaction_set(const sx_api_handle_t        handle,
                                                const sx_access_cmd_t        cmd,
                                                const sx_bulk_cntr_buffer_t *buffer_p);

/**
 *  This API reads a single counter from a bulk-counter-read buffer.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] key_p           - For port counter: Logical port ID, counter group, TC (optional), priority (optional),
 *                                                priority-group (optional)
 *                              For flow counter: Counter ID
 *                              For elephant detected flows: Logical port ID, flow ID (optional).
 * @param[in] buffer_p        - Valid buffer which was allocated by API sx_api_bulk_buffer_set()
 * @param[out] counter_data_p - Requested counter data
 *
 * @return SX_STATUS_SUCCESS             Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE      NULL handle is received
 * @return SX_STATUS_PARAM_NULL          Parameter is NULL
 * @return SX_STATUS_PARTIALLY_COMPLETE  Transaction is in progress
 * @return SX_STATUS_ERROR               Operation failure
 */
sx_status_t sx_api_bulk_counter_transaction_get(const sx_api_handle_t          handle,
                                                const sx_bulk_cntr_read_key_t *key_p,
                                                const sx_bulk_cntr_buffer_t   *buffer_p,
                                                sx_bulk_cntr_data_t           *counter_data_p);

/**
 * This API triggers the refresh of all accumulated (SX_FLOW_COUNTER_TYPE_ACCUMULATED) counters.
 *
 * Note:
 *  While the refreshing is not mandatory to read the values of accumulated counters,
 *  but if the up-to-date values are needed, then the refresh API should be called before reading.
 *  The refresh is an asynchronous operation. Once the refresh is done, SDK will generate an
 *  SX_TRAP_ID_BULK_REFRESH_COUNTER_DONE_EVENT event with a copy of attributes passed to the refresh API.
 *  Once the event is received, the user can read and get fresh values of accumulated counters.
 *
 *  A user cookie can be provided as a part of the refresh attributes, later it can be used to
 *  identify the refresh done event. So that the refresh done event can be registered and received in
 *  a different process from the process where the refresh API was called.
 *
 *  Only one refresh can be active. Until a REFRESH_COUNTER_DONE_EVENT event is received,
 *  the user should not start another refresh, otherwise, SDK will return an error.
 *
 *  The refresh also requires a free bulk counter transaction.
 *  For more details about transactions, please see the description of sx_api_bulk_counter_transaction_set.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET
 * @param[in] counter_refresh_attr_p - Refresh attributes
 *
 * @return SX_STATUS_SUCCESS             Operation completes successfully
 * @return SX_STATUS_PARAM_NULL          Refresh attributes pointer is not initialized
 * @return SX_STATUS_RESOURCE_IN_USE     Either the refresh is already in progress or
 *                                       there is no available bulk counter transaction.
 * @return SX_STATUS_CMD_UNSUPPORTED     Command is not supported
 * @return SX_STATUS_INVALID_HANDLE      Called invalid handle
 * @return SX_STATUS_ERROR               General error happened
 */
sx_status_t sx_api_bulk_counter_refresh_set(const sx_api_handle_t               handle,
                                            const sx_access_cmd_t               cmd,
                                            const sx_bulk_cntr_refresh_attr_t * counter_refresh_attr_p);

#endif /* ifndef __SX_API_BULK_COUNTER_H__ */
