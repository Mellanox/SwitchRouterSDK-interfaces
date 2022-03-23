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

#ifndef __SX_API_FLEX_MODIFIER_H__
#define __SX_API_FLEX_MODIFIER_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/
/**
 * This API sets the log verbosity level of FLEX_MODIFIER module.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Set verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - FLEX_MODIFIER module verbosity level
 * @param[in] api_verbosity_level      - FLEX_PMODIFIER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */


sx_status_t sx_api_flex_modifier_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                         const sx_log_verbosity_target_t verbosity_target,
                                                         const sx_verbosity_level_t      module_verbosity_level,
                                                         const sx_verbosity_level_t      api_verbosity_level);


/**
 * This API gets the log verbosity level of FLEX_MODIFIER module.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Get verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - FLEX_MODIFIER module verbosity level
 * @param[out] api_verbosity_level_p    - FLEX_MODIFIER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_NULL if an input parameter is invalid
 */

sx_status_t sx_api_flex_modifier_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                         const sx_log_verbosity_target_t verbosity_target,
                                                         sx_verbosity_level_t           *module_verbosity_level_p,
                                                         sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API configures (CREATE/SET/DESTROY) an egress modifier template (EMT).
 * An EMT is used to modify packets using ACL actions.
 * An EMT needs to be allocated first (CREATE cmd) before its parameters are set (SET cmd).
 * Note: an EMT used in an ACL action cannot be destroyed.
 * Supported devices: Spectrum2, Spectrum3.
 * Parameters:
 * @param[in] handle    - SX-API handle
 * @param[in] cmd       - CREATE / SET / DESTROY
 * @param[in] emt_id    - The egress modifier template to configure
 * @param[in] emt_cfg_p - Pointer to the configuration to apply to the EMT (ignored by CREATE & DESTROY commands).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if trying to create an EMT that already exists.
 * @return SX_STATUS_RESOURCE_IN_USE when trying to destroy an EMT used by an ACL action.
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform*
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_flex_modifier_set(const sx_api_handle_t             handle,
                                     const sx_access_cmd_t             cmd,
                                     const sx_flex_modifier_emt_key_t  emt_id,
                                     const sx_flex_modifier_emt_cfg_t *emt_cfg_p);

/**
 * This API retrieves the configuration of an egress modifier template (EMT).
 * Supported devices: Spectrum2, Spectrum3.
 * Parameters:
 * @param[in]  handle    - SX-API handle
 * @param[in]  cmd       - GET
 * @param[in]  emt_id    - The egress modifier template to retrieve.
 * @param[out] emt_cfg_p - Pointer to the configuration to filled by the API.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 */

sx_status_t sx_api_flex_modifier_get(const sx_api_handle_t            handle,
                                     const sx_access_cmd_t            cmd,
                                     const sx_flex_modifier_emt_key_t emt_id,
                                     sx_flex_modifier_emt_cfg_t      *emt_cfg_p);

#endif /* __SX_API_FLEX_MODIFIER_H__ */
