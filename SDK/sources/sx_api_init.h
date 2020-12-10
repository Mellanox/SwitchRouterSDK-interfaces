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

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

#ifndef __SX_API_INIT_H__
#define __SX_API_INIT_H__


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of all modules in SwitchX SDK
 * Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
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
 * This function gets the log verbosity level of all modules in SwitchX SDK
 * Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
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
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] attr_p      - target verbosity attributes such as verbosity target
 *                          API or MODULE and flag whether we want to enable/disable
 *                          function enter/leave logs for this target.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_system_log_enter_func_severity_set(const sx_api_handle_t                 handle,
                                                      const sx_log_verbosity_target_attr_t *attr_p);


/**
 * This API gets the configured state for the function enter/leave debugging log messages.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in,out] attr_p  - target verbosity attributes such as verbosity target
 *                          API or MODULE and flag which indicates whether function
 *                          enter/leave logs are enabled/disabled for this target.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_system_log_enter_func_severity_get(const sx_api_handle_t           handle,
                                                      sx_log_verbosity_target_attr_t *attr_p);

/**
 *  This function opens channel to SX-API operations.
 *  Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] logging_cb - optional log messages callback
 * @param[out] handle - handle that should be used in all
 *       further SX-API operations. Invalid handle (0) returned
 *       in case of an error.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_ERROR - Input parameters error
 * @return SX_STATUS_NO_MEMORY - Memory allocation failed
 * @return SX_STATUS_COMM_ERROR - client communication channel open failed
 * @return SX_STATUS_ERROR - open SX-API client mutex failed
 */
sx_status_t sx_api_open(sx_log_cb_t      logging_cb,
                        sx_api_handle_t *handle);

/**
 *  This function closes channel to SX-API operations.
 *  Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_ERROR - Input parameters error - NULL
 *         handle
 * @return SX_STATUS_COMM_ERROR - Input parameters error -
 *         Invalid handle
 */
sx_status_t sx_api_close(sx_api_handle_t *handle);

/**
 * This function initializes SwitchX SDK.
 * Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] sdk_init_params_p - SwitchX SDK init parameters.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE - Input parameters error - Invalid handle
 * @return SX_STATUS_COMM_ERROR - Communication channel message Send/Receive error
 * @return SX_STATUS_PARAM_ERROR - no SWID was defined
 */
sx_status_t sx_api_sdk_init_set(const sx_api_handle_t       handle,
                                const sx_api_sx_sdk_init_t *sdk_init_params_p);

/**
 * This function is used to get SDK init parameters.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[out] sdk_init_params_p - SDK init parameters.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE - if handle is invalid
 * @return SX_STATUS_PARAM_NULL - if parameter is NULL
 * @return SX_STATUS_ERROR - if unexpected behavior occurs
 */
sx_status_t sx_api_sdk_init_params_get(const sx_api_handle_t handle,
                                       sx_api_sx_sdk_init_t *sdk_init_params_p);

/**
 *  This function returns the versions of the various
 *  components of SwitchX SDK package.
 *  Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[out] versions_p - SwitchX SDK versions.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_ERROR - Input parameters error
 * @return SX_STATUS_COMM_ERROR - Communication channel message
 *         send/ Receive error
 */
sx_status_t sx_api_sx_sdk_version_get(const sx_api_handle_t     handle,
                                      sx_api_sx_sdk_versions_t *versions_p);

/**
 *  This function is used to enter/exit transaction burst mode.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ENABLE /DISABLE
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
 *  Supported devices: Spectrum, Spectrum-A1, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] object_id_p - Object ID
 * @param[out] refcount_p - reference count of object
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router object isn't found.
 * @return SX_STATUS_ERROR if a general error occurs.
 */
sx_status_t sx_api_object_refcount_get(const sx_api_handle_t handle,
                                       const sx_object_id_t *object_id_p,
                                       uint32_t             *refcount_p);

#endif /* __SX_API_INIT_H__ */
