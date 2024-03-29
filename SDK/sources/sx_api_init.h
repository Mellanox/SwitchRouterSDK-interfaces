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

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

#ifndef __SX_API_INIT_H__
#define __SX_API_INIT_H__


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of all modules in SwitchX SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - SwitchX SDK modules verbosity level
 * @param[in] api_verbosity_level      - SwitchX SDK API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_system_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  const sx_verbosity_level_t      module_verbosity_level,
                                                  const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of all modules in SwitchX SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - SwitchX SDK modules verbosity level
 * @param[out] api_verbosity_level_p    - SwitchX SDK API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_system_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  sx_verbosity_level_t           *module_verbosity_level_p,
                                                  sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API allows to enable/disable function enter/leave debugging log messages.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] attr_p      - Target verbosity attributes (e.g.,verbosity target API or MODULE)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_system_log_enter_func_severity_set(const sx_api_handle_t                 handle,
                                                      const sx_log_verbosity_target_attr_t *attr_p);


/**
 * This API gets the configured state of function level entry/exit logging.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle      - SX-API handle
 * @param[in,out] attr_p  - Target verbosity attributes (e.g.,verbosity target API or MODULE)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_system_log_enter_func_severity_get(const sx_api_handle_t           handle,
                                                      sx_log_verbosity_target_attr_t *attr_p);

/**
 * This API opens channel to SX-API operations.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] logging_cb - Optional log messages callback
 * @param[out] handle    - Handle that should be used in all further SX-API operations
 *                         Invalid handle (0) is returned, in case of an error
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_NO_MEMORY if memory allocation failed
 * @return SX_STATUS_COMM_ERROR if client communication channel failed
 * @return SX_STATUS_ERROR if open SX-API client mutex failed
 */
sx_status_t sx_api_open(sx_log_cb_t      logging_cb,
                        sx_api_handle_t *handle);

/**
 * This API closes channel to SX-API operations.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_COMM_ERROR if client communication channel failed
 */
sx_status_t sx_api_close(sx_api_handle_t *handle);

/**
 * This API gets device HW information.
 *
 * Notes:
 *   - In initialization flow, this API must be called prior to sx_api_sdk_init_set() or any access to the FW.
 *   - Returned chip-type is an aggregation of chip-type and revision. E.g.:
 *     SX_CHIP_TYPE_SPECTRUM for Spectrum-1 revision A0 and SX_CHIP_TYPE_SPECTRUM_A1 for Spectrum-1 revision A1.
 *   - On status SX_STATUS_FW_INIT_FAILURE or SX_STATUS_DEVICE_UNRECOVERABLE the returned chip-type is valid.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] dev_hw_info_p - Device HW information
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 * @return SX_STATUS_FW_INIT_FAILURE if secure firmware boot failure occurs. Need to actively start recovery
 *                                   flow process (conducting regular initialization will not address the issue).
 *                                   Contact NVIDIA Support for instructions.
 * @return SX_STATUS_DEVICE_UNRECOVERABLE if device is in an unrecoverable state.
 *                                        Contact NVIDIA Support to discuss further options.
 */

sx_status_t sx_api_device_hw_info_get(const sx_api_handle_t handle, sx_device_hw_info_t *dev_hw_info_p);

/**
 * This API initializes SwitchX SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] sdk_init_params_p - SwitchX SDK init parameters
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_COMM_ERROR if there is a communication error in channel message send/receive
 * @return SX_STATUS_PARAM_ERROR if no SWID was defined
 * @return SX_STATUS_FW_INIT_FAILURE if secure firmware boot failure occurs. Need to actively start recovery
 *                                   flow process (conducting regular initialization will not address the issue).
 *                                   Contact NVIDIA Support for instructions.
 * @return SX_STATUS_DEVICE_UNRECOVERABLE if device is in an unrecoverable state.
 *                                        Contact NVIDIA Support to discuss further options.
 */
sx_status_t sx_api_sdk_init_set(const sx_api_handle_t       handle,
                                const sx_api_sx_sdk_init_t *sdk_init_params_p);

/**
 * This API is used to get SDK initialization parameters.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle             - SX-API handle
 * @param[out] sdk_init_params_p - SDK init parameters
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameters is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_sdk_init_params_get(const sx_api_handle_t handle,
                                       sx_api_sx_sdk_init_t *sdk_init_params_p);

/**
 * This API returns the versions of the various components of SwitchX SDK package.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle      - SX-API handle
 * @param[out] versions_p - SwitchX SDK versions
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_COMM_ERROR if there is a communication error in channel message send/receive
 */
sx_status_t sx_api_sx_sdk_version_get(const sx_api_handle_t     handle,
                                      sx_api_sx_sdk_versions_t *versions_p);

/**
 * This API is used to enter/exit transaction burst mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd    - ENABLE/DISABLE
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behaviour occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_transaction_mode_set(const sx_api_handle_t handle,
                                        const sx_access_cmd_t cmd);

/**
 * This API is used to get the reference count of an SDK object.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] object_id_p - Object ID
 * @param[out] refcount_p - reference count of object
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if router object is not found
 * @return SX_STATUS_ERROR if a general error occurs
 */
sx_status_t sx_api_object_refcount_get(const sx_api_handle_t handle,
                                       const sx_object_id_t *object_id_p,
                                       uint32_t             *refcount_p);

#endif /* __SX_API_INIT_H__ */
