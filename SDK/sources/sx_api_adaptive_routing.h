/*
 * Copyright (C) 2001-2021 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_ADAPTIVE_ROUTING_H__
#define __SX_API_ADAPTIVE_ROUTING_H__

#include <sx/sdk/sx_api.h>

/************************************************
 *  API Functions
 ***********************************************/
/**
 * This API Initiates the adaptive routing (AR) module in SDK.
 * This function should be called before any use of the library.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle.
 * @param[in] init_params_p - General AR parameters.
 *
 * @return SX_STATUS_SUCCESS - if operation completes
 *         successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if parameter is wrong.
 * @return SX_STATUS_ALREADY_INITIALIZED - When AR is
 *         already initialized.
 * @return SX_STATUS_MODULE_UNINITIALIZED – if router module isn’t initialized.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_ar_init_set(const sx_api_handle_t      handle,
                               const sx_ar_init_params_t *init_params_p);

/**
 * This API deinitializes the AR block in the SDK.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_ar_deinit_set(const sx_api_handle_t handle);

/**
 * This API sets the AR profile configuration parameters.
 * The user can configure only one of the profiles or both.
 *
 * Supported devices: Spectrum2, Spectrum3.
 * Note - Only CREATE and DESTROY access commands are supported.
 *
 * @param[in]  handle                       - SX-API handle
 * @param[in]  cmd                          - SX access command - SET
 * @param[in]  profile_key_p                - Profile id.
 * @param[in]  profile_attr_p               - profile attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_MODULE_UNINITIALIZED if AR module wasn't initialized.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input/output parameter is NULL.
 */
sx_status_t sx_api_ar_profile_set(const sx_api_handle_t       handle,
                                  const sx_access_cmd_t       cmd,
                                  const sx_ar_profile_key_t  *profile_key_p,
                                  const sx_ar_profile_attr_t *profile_attr_p);

/**
 *  This API gets AR profile configuration parameters.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle                         - SX-API handle
 * @param[in] profile_key_p                  - Profile key
 * @param[out] profile_attr_p                - Profile attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_ar_profile_get(const sx_api_handle_t      handle,
                                  const sx_ar_profile_key_t *profile_key_p,
                                  sx_ar_profile_attr_t      *profile_attr_p);

/**
 * This API sets the AR default classifier configuration parameters.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]  handle                       - SX-API handle
 * @param[in]  cmd                          - SET.
 * @param[in]  action_p                     - classifier action.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_MODULE_UNINITIALIZED if AR module wasn't initialized.
 * @return SX_STATUS_PARAM_NULL if any input/output parameter is NULL.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_ar_default_classification_set(const sx_api_handle_t            handle,
                                                 const sx_access_cmd_t            cmd,
                                                 const sx_ar_classifier_action_t *action_p);

/**
 * This API gets the AR default classification configuration.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]  handle                       - SX-API handle
 * @param[in]  action_p                     - default classifier action.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input/output parameter is NULL.
 */
sx_status_t sx_api_ar_default_classification_get(const sx_api_handle_t      handle,
                                                 sx_ar_classifier_action_t *action_p);

/**
 *  This API sets the AR classifier configuration parameters.
 * When multi-match then classifier with lower value wins.
 * When no match the default classifier wins.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] cmd               - SET.
 * @param[in] classifier_id     - Classifier ID
 * @param[in] attr_p            - Classifier configuration attributes.
 * @param[in] action_p          - Classifier action.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_ar_classifier_set(const sx_api_handle_t            handle,
                                     const sx_access_cmd_t            cmd,
                                     const sx_ar_classifier_id_e      classifier_id,
                                     const sx_ar_classifier_attr_t   *attr_p,
                                     const sx_ar_classifier_action_t *action_p);

/**
 *  This API gets AR classifier configuration parameters.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] classifier_id     - Classifier ID
 * @param[out] attr_p           - Classifier configuration attributes.
 * @param[out] action_p         - Classifier action.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if error in parameter.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_ar_classifier_get(const sx_api_handle_t       handle,
                                     const sx_ar_classifier_id_e classifier_id,
                                     sx_ar_classifier_attr_t    *attr_p,
                                     sx_ar_classifier_action_t  *action_p);

/**
 * This API sets the AR congestion threshold configuration.
 * This configuration will impact the port grade.
 * The grades are used by the AR engine to select the egress port.
 *
 * Buffer < thresh_lo  will get grade 0/1 depends on link utilization
 * thresh_lo  < Buffer < thresh_med will get grade 2
 * thresh_med < Buffer < thresh_hi  will get grade 3
 * thresh_hi  < Buffer              will get grade 4
 *
 * Note: min threshold = 0, max threshold = 2^24
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]  handle                       - SX-API handle
 * @param[in]  cmd                          - SET.
 * @param[in]  threshold_p                  - Congestion threshold.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input/output parameter is NULL.
 */
sx_status_t sx_api_ar_congestion_threshold_set(const sx_api_handle_t                    handle,
                                               const sx_access_cmd_t                    cmd,
                                               const sx_ar_congestion_threshold_attr_t *threshold_p);

/**
 * This API gets the AR congestion threshold configuration.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]  handle                       - SX-API handle
 * @param[out]  threshold_p                 - Congestion threshold pointer.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input/output parameter is NULL.
 */
sx_status_t sx_api_ar_congestion_threshold_get(const sx_api_handle_t              handle,
                                               sx_ar_congestion_threshold_attr_t *threshold_p);

/**
 *  This API sets the AR link utilization configuration parameters.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle                     - SX-API handle.
 * @param[in] cmd                        - SET.
 * @param[in] log_port                   - SDK logical port
 * @param[in] link_util_attr             - Link utilization configuration attributes.
 *  [ND] link_util_attr_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if parameter is wrong.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 *  [ND] PARAM NULL
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_ar_link_utilization_threshold_set(const sx_api_handle_t                handle,
                                                     const sx_access_cmd_t                cmd,
                                                     const sx_port_log_id_t               log_port,
                                                     const sx_ar_link_utilization_attr_t *link_util_attr_p);

/**
 *  This API gets the AR link utilization configuration parameters.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle                           - SX-API handle.
 * @param[in] log_port                         - SDK logical port
 * @param[out] link_util_attr_p                - Link utilization configuration attributes.
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if parameter is wrong.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_ar_link_utilization_threshold_get(const sx_api_handle_t          handle,
                                                     const sx_port_log_id_t         log_port,
                                                     sx_ar_link_utilization_attr_t *link_util_attr_p);

/*
 * This API sets the AR shaper rate configuration parameters.
 * To prevent moving a large amount of flows moving from one output
 * to another output in a short period of time
 * two types of shapers per port are used:
 *
 * A shaper per output port for the number of flows that changed their destination to the output port
 * A shaper per output port for the number of flows that changed their destination from the output port
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] cmd               - SET.
 * @param[in] shaper_attr_p     - Shaper configuration attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_MODULE_UNINITIALIZED if AR module wasn't initialized.
 * @return SX_STATUS_PARAM_ERROR if parameter there is a bad parameter.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_ar_shaper_rate_set(const sx_api_handle_t      handle,
                                      const sx_access_cmd_t      cmd,
                                      const sx_ar_shaper_attr_t *shaper_attr_p);

/*
 *  This API gets AR shaper rate configuration parameters.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle.
 * @param[out] shaper_attr_p            - Shaper configuration attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_MODULE_UNINITIALIZED if AR module wasn't initialized.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_ar_shaper_rate_get(const sx_api_handle_t handle,
                                      sx_ar_shaper_attr_t  *shaper_attr_p);

/*
 * This API retrieves adaptive routing global counters values.
 *
 * Supported devices: Spectrum2, Spectrum3
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - READ/READ_CLEAR
 * @param[out] ar_counters_p    - Pointer to an AR global counter
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_ar_counters_get(const sx_api_handle_t    handle,
                                   const sx_access_cmd_t    cmd,
                                   sx_ar_global_counters_t *ar_counters_p);

#endif /* ifndef __SX_API_ADAPTIVE_ROUTING_H__ */
