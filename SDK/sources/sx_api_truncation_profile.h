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

#ifndef __SX_API_TRUNCATION_PROFILE_H__
#define __SX_API_TRUNCATION_PROFILE_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of TRUNCATION_PROFILE module.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Set verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - TRUNCATION_PROFILE module verbosity level
 * @param[in] api_verbosity_level      - TRUNCATION_PROFILE API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_truncation_profile_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                              const sx_log_verbosity_target_t verbosity_target,
                                                              const sx_verbosity_level_t      module_verbosity_level,
                                                              const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of TRUNCATION_PROFILE module.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Get verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - TRUNCATION_PROFILE module verbosity level
 * @param[out] api_verbosity_level_p    - TRUNCATION_PROFILE API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_NULL if an input parameter is invalid
 */
sx_status_t sx_api_truncation_profile_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                              const sx_log_verbosity_target_t verbosity_target,
                                                              sx_verbosity_level_t           *module_verbosity_level_p,
                                                              sx_verbosity_level_t           *api_verbosity_level_p);


/**
 * This API creates/destroys SPAN iMirror parsing base Masking & ACL Truncation profile.
 *
 * CREATE configures and enables truncation profile.
 * DESTROY disables the truncation of this profile.
 *
 * Truncation profile supports the following configuration:
 * - Truncation (fixed-offset): Ingress Mirror, Egress Mirror, ACL
 * - Parsing-Base Masking: Ingress Mirror
 *
 * Notes:
 *  - No changes can be made to a Truncation profile that binds to an active SPAN session or that is used by ACL.
 *  - Timestamp over CRC is not supported.
 *
 * Truncation (fixed-offset):
 * - Granularity of 4 bytes | Minimum value: 64 bytes
 * - In order to support Parsing-Base Masking, the API must be set to TRUNCATION_PROFILE_PARSING_BASED_MASKING_OFFSET_MAX
 *
 * Parsing-Based Masking:
 * - Size shall be < TRUNCATION_PROFILE_PARSING_BASED_MASKING_OFFSET_MAX
 * - Supported for iMirror (not eMirror or ACL)
 * - Only 'Zero'(= 0x00) is supported in Parsing-Base Masking
 *
 * The Lazy delete feature is supported for ACL Truncation profile mapping.
 *  - If Lazy Delete feature is disabled:
 *       If the reference counter of the Truncation Profile is 0, then the API call with command DESTROY deletes a Truncation Profile.
 *       Otherwise, the SDK returns SX_STATUS_RESOURCE_IN_USE.
 *
 *  - If Lazy Delete feature is enabled:
 *       If the reference counter of the Truncation Profile is not 0, then the API call with command DESTROY marks a Truncation Profile as deleted, and SDK returns SX_STATUS_SUCCESS.
 *       Once the reference counter of the Truncation Profile becomes 0, SDK will delete the Trunc Profile and will generate a notification with the trap ID (SX_TRAP_ID_OBJECT_DELETED_EVENT).
 *        The NOS should monitor delete notification events in order to delete the counter resource.
 *       When trying to recreate a Truncation Profile before a notification is received, the SDK returns the error SX_STATUS_RESOURCE_IN_USE.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] access_cmd            - CREATE/DESTROY
 * @param[in] trunc_profile_key_p   - Pointer to truncation profile key
 * @param[in] trunc_profile_cfg_p   - Pointer to truncation profile configuration
 *
 * @return SX_STATUS_SUCCESS                  if operation completes successfully
 * @return SX_STATUS_PARAM_NULL               if  pointer params is  NULL
 * @return SX_STATUS_PARAM_ERROR              if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED   if unsupported command is requested
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO    if SXD driver function returns fail
 * @return SX_STATUS_RESOURCE_IN_USE          if element is in use and cannot be released
 * @return SX_STATUS_ERROR                    if unexpected behavior occurs
 */
sx_status_t sx_api_truncation_profile_set(const sx_api_handle_t              handle,
                                          const sx_access_cmd_t              cmd,
                                          const sx_truncation_profile_key_t *trunc_profile_key_p,
                                          sx_truncation_profile_cfg_t       *trunc_profile_cfg_p);


/**
 * This API gets the Truncation profile.
 *
 * Note: In case the 'truncation' was enabled from the 'sx_api_span_session_set()' API then 'get Truncation profile'
 * also works without performing the 'set Truncation profile' API.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] trunc_profile_key_p    - Pointer to truncation profile key
 * @param[out] trunc_profile_cfg_p   - Pointer to truncation profile configuration
 *
 * @return SX_STATUS_SUCCESS                   if operation completes successfully
 * @return SX_STATUS_PARAM_NULL                if  pointer params is  NULL
 * @return SX_STATUS_PARAM_ERROR               if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED    if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND           if requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO     if SXD driver function returns fail
 * @return SX_STATUS_ERROR                     if unexpected behavior occurs
 */
sx_status_t sx_api_truncation_profile_get(const sx_api_handle_t              handle,
                                          const sx_truncation_profile_key_t *trunc_profile_key_p,
                                          sx_truncation_profile_cfg_t       *trunc_profile_cfg_p);
#endif /* __SX_API_TRUNCATION_PROFILE_H__ */
