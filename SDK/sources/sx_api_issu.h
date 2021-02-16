/*
 *  Copyright (C) 2014-2021. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_ISSU_H__
#define __SX_API_ISSU_H__

#include <sx/sdk/sx_api.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 *  This function sets the log verbosity level of ISSU MODULE.
 *  Supported devices: Spectrum, Spectrum 2, Spectrum 3
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - ISSU module verbosity level
 * @param[in] api_verbosity_level      - ISSU API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_issu_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);


/**
 *  This function gets the log verbosity level of ISSU MODULE.
 *  Supported devices: Spectrum, Spectrum 2, Spectrum 3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] verbosity_target          - set verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - ISSU module verbosity level
 * @param[out] api_verbosity_level_p    - ISSU API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_issu_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API is used to prepare the SDK for restart in "FAST-FAST Boot mode".
 * It triggers ISSU (In Service Software Upgrade) of the SDK & FW by shutting down SDK,
 * resetting the ASIC and switching to a new SDK/FW if available.
 * Supported devices: Spectrum, Spectrum 2, Spectrum 3.
 *
 * @param[in] handle                   - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_issu_start_set(const sx_api_handle_t handle);

/**
 * This API is used to notify the newly upgraded SDK in "FAST-FAST Boot Mode" that
 * the configuration stage of the ISSU (In Service Software Upgrade) process
 * has finished and to resume normal operations.
 * Supported devices: Spectrum, Spectrum 2, Spectrum 3.
 *
 * @param[in] handle                   - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_issu_end_set(const sx_api_handle_t handle);

/**
 * This API prepares the SDK for CRIU (checkpoint/restore in userspace) Hibernation.
 * The SDK configuration is written to persistent storage from where it can be restored.
 * This is also referred to as SDK "Warm Boot" Mode
 * Supported devices: Spectrum, Spectrum 2, Spectrum 3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] pause_params_p - pause params.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS          - Operation completes successfully
 * @return SX_STATUS_PARAM_ERROR      - Input parameters error - NULL handle
 * @return SX_STATUS_COMM_ERROR       - Input parameters error - Invalid handle
 * @return SX_STATUS_CMD_UNPERMITTED  - if SDK is already paused
 * @return SX_STATUS_ISSU_IN_PROGRESS - When ISSU is already in progress.
 * @return SX_STATUS_NO_MEMORY        - Out of Memory
 */
sx_status_t sx_api_issu_pause_set(const sx_api_handle_t  handle,
                                  const sx_issu_pause_t *pause_params_p);

/**
 * Used for "Warm" boot mode to "resume" the SDK from CRIU hibernation
 * This API restores the SDK from CRIU (checkpoint/restore in userspace) Hibernation.
 * This is also referred to as SDK "Warm Boot" Mode
 * Supported devices: Spectrum, Spectrum 2, Spectrum 3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] resume_params_p - resume params.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS         - Operation completes successfully
 * @return SX_STATUS_PARAM_ERROR     - Input parameters error - NULL handle
 * @return SX_STATUS_COMM_ERROR      - Input parameters error - Invalid handle
 * @return SX_STATUS_CMD_UNPERMITTED - If SDK is not paused
 * @return SX_STATUS_NO_MEMORY       - No more memory available
 */
sx_status_t sx_api_issu_resume_set(const sx_api_handle_t   handle,
                                   const sx_issu_resume_t *resume_params_p);

#endif /* __SX_API_ISSU_H__ */
