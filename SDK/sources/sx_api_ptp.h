/*
 *  Copyright (C) 2014-2021. NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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
#ifndef __SX_API_PTP_H__
#define __SX_API_PTP_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_ptp.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of PTP module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - PTP module verbosity level
 * @param[in] api_verbosity_level      - PTP API verbosity level
 *
 * @return sx_status_t
 */

sx_status_t sx_api_ptp_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of PTP module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - PTP module verbosity level
 * @param[out] api_verbosity_level_p    - PTP API verbosity level
 *
 * @return sx_status_t
 */

sx_status_t sx_api_ptp_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API initializes the PTP module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] ptp_params - PTP parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_ERROR if a parameter is invalid
 * @return SX_STATUS_ALREADY_INITIALIZED if PTP module is already initialized
 * @return SX_STATUS_ERROR for a general error
 */

sx_status_t sx_api_ptp_init_set(const sx_api_handle_t  handle,
                                const sx_ptp_params_t *ptp_params);

/**
 * This API deinitializes the PTP module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_MODULE_UNINITIALIZED if PTP module is not initialized
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_ptp_deinit_set(const sx_api_handle_t handle);

#endif /* __SX_API_PTP_H__ */
