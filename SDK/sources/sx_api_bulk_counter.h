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

#ifndef __SX_API_BULK_COUNTER_H__
#define __SX_API_BULK_COUNTER_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>
#include <sx/sdk/sx_bulk_counter.h>

/**
 * This function sets the log verbosity level of BULK COUNTER MODULE
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - BULK COUNTER module verbosity level
 * @param[in] api_verbosity_level      - BULK COUNTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_bulk_counter_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        const sx_verbosity_level_t      module_verbosity_level,
                                                        const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of BULK COUNTER MODULE
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - BULK COUNTER module verbosity level
 * @param[out] api_verbosity_level_p    - BULK COUNTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_bulk_counter_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        sx_verbosity_level_t           *module_verbosity_level_p,
                                                        sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This API allocates or frees a buffer of an asynchronous bulk-counter-read operation.
 *  Notes:
 *        1. Buffer is bound to key. An operation with a different key requires a new buffer.
 *        2. Buffer may be reused on multiple operations of sx_api_bulk_counter_transaction_set().
 *        3. Buffer operation must be completed or canceled before this function is called with
 *           SX_ACCESS_CMD_DESTROY command.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      -  SX-API handle
 * @param[in] cmd         -  SX_ACCESS_CMD_CREATE to allocate buffer
 *                           SX_ACCESS_CMD_DESTROY to free buffer
 * @param[in] key_p       -  Bulk-counter desired counters:
 *                           For port counters: list of logical port ID, list of counter groups,
 *                                              list of TCs, list of priorities.
 *                           For flow counters: range of flow counter IDs.
 *                           When cmd is SX_ACCESS_CMD_DESTROY, key should be NULL.
 * @param[in,out] buffer_p - On SX_ACCESS_CMD_CREATE, returned allocated buffer to be used by other APIs.
 *                           On SX_ACCESS_CMD_DESTROY, the buffer to deallocate.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if there is a parameter error
 * @return SX_STATUS_CMD_UNSUPPORTED if cmd is not valid
 * @return SX_STATUS_NO_MEMORY if there is no free memory
 * @return SX_STATUS_RESOURCE_IN_USE if buffer operation is running
 * @return SX_STATUS_ERROR if operation completes with failure
 */
sx_status_t sx_api_bulk_counter_buffer_set(const sx_api_handle_t            handle,
                                           const sx_access_cmd_t            cmd,
                                           const sx_bulk_cntr_buffer_key_t *key_p,
                                           sx_bulk_cntr_buffer_t           *buffer_p);

/**
 *  This API initiates or cancels an asynchronous bulk-counter-read operation.
 *  Notes:
 *        1. After initiating the operation, user is expected to get SX_BULK_READ_DONE event and then use
 *           sx_api_bulk_counter_transaction_get(). Until SX_BULK_READ_DONE event is received by the user,
 *           buffer cannot be used with sx_api_bulk_counter_transaction_get().
 *        2. When initiating LAG port bulk-counter-read, its members are determined on operation
 *           initiation. Any change to the LAG port or to its members during the operation will
 *           not be reflected when reading the LAG counters upon operation completion.
 *        3. On disable, the buffer cannot be used on another operation or freed until the SW_BULK_READ_DONE
 *           event is received.
 *        4. Up to two transactions are allowed in parallel by the system:
 *           a. 2 x Port_Counters
 *           b. Any combination of two different bulk counter types
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - SX_ACCESS_CMD_READ to read a set of counters
 *                          SX_ACCESS_CMD_READ_CLEAR to read and clear a set of counters
 *                          SX_ACCESS_CMD_DISABLE to cancel an active operation
 * @param[in] buffer_p    - Valid buffer which was allocated by sx_api_bulk_buffer_set().
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
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
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] key_p           - For port counter: Logical port ID, counter group,
 *                                                TC (optional), priority (optional),
 *                                                priority-group (optional).
 *                              For flow counter: Counter ID.
 * @param[in] buffer_p        - Valid buffer which was allocated by sx_api_bulk_buffer_set().
 * @param[out] counter_data_p - Requested counter data.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARTIALLY_COMPLETE if transaction is in progress
 * @return SX_STATUS_ERROR if operation completes with failure
 */
sx_status_t sx_api_bulk_counter_transaction_get(const sx_api_handle_t          handle,
                                                const sx_bulk_cntr_read_key_t *key_p,
                                                const sx_bulk_cntr_buffer_t   *buffer_p,
                                                sx_bulk_cntr_data_t           *counter_data_p);

#endif
