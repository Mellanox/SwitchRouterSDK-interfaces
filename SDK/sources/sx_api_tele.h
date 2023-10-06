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


#ifndef __SX_API_TELE_H__
#define __SX_API_TELE_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of TELEMETRY module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - TELEMETRY module verbosity level
 * @param[in] api_verbosity_level      - TELEMETRY API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_tele_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/**
 * Gets the log verbosity level of TELEMETRY module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - TELEMETRY module verbosity level
 * @param[out] api_verbosity_level_p    - TELEMETRY API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_tele_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API is used to initialize the TELEMETRY module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] params_p - Pointer to initialization parameters structure
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_NO_RESOURCES if cannot allocate resources for telemetry
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tele_init_set(const sx_api_handle_t  handle,
                                 sx_tele_init_params_t *params_p);

/**
 * This API is used to deinitialize the TELEMETRY module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle   - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tele_deinit_set(const sx_api_handle_t handle);

/**
 * This API sets the histogram attributes.
 *
 * SET sets the histogram attributes described on key to attributes_data.
 *
 * Note: On Spectrum devices, sample time is global. The last configured sample time is applied to all histograms.
 * Note: For latency histograms (supported on Spectrum-2 and above) the following is true:
 *      1. Histogram attributes must be identical for all TCs of the same port.
 *      2. Edit command is not supported (To edit, destroy all latency histograms on a port and then set a new configuration).
 *      3. The behavior of Latency-Histograms will be undefined, if CRC parameters on at least one port are configured in
 *         the following way:
 *             - Egress as SX_PORT_CRC_EGRESS_RECALC_MODE_PREVENT (using sx_api_port_crc_params_set API)
 *                 AND
 *             - Ingress as SX_TS_OVER_CRC_INGRESS_MODE_ENABLE_E (using sx_api_tele_attributes_set API)
 * Note: For counter histograms we support two histograms per port and every histogram can be configured on any counter.
 * Note: For port profile cmd=EDIT/DESTROY is not supported.
 * Note: sx_api_tele_histogram_set doesn't support port profile on SPC1.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET/EDIT/DESTROY
 * @param[in] attributes_key - Histogram key
 * @param[in] attributes_data - Histogram attributes data
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation
 * @return SX_STAUS_ERROR on internal error
 */
sx_status_t sx_api_tele_histogram_set(const sx_api_handle_t                     handle,
                                      const sx_access_cmd_t                     cmd,
                                      const sx_tele_histogram_key_t             key,
                                      const sx_tele_histogram_attributes_data_t data);

/**
 * This API retrieves the histogram attributes data that match the key.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - GET
 * @param[in] key -  Histogram key
 * @param[out] data_p - Histogram attributes data pointer
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported
 * @return SX_STAUS_ERROR general error
 */
sx_status_t sx_api_tele_histogram_get(const sx_api_handle_t                handle,
                                      const sx_access_cmd_t                cmd,
                                      const sx_tele_histogram_key_t        key,
                                      sx_tele_histogram_attributes_data_t *data_p);

/**
 *  This API returns a list of one or more histogram keys.
 *  The following use case scenarios apply with different input parameters. X = don't-care.
 *   - 1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, hist_list = X, Count =0:
 *        In this case, the API will return the total number of histograms in the internal database.
 *
 *   - 2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, hist_list = Valid, Count = 1:
 *        In this case, the API will check if the specified key exists. If it does, the key will be returned in the hist_list
 *        along with a count of 1. If the key does not exist an empty list will be returned with count = 0.
 *
 *   - 3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = Valid, hist_list is Valid, Count =1:
 *        In this case, the API will check if the specified key exists. If it does, it will check it against the filter parameter.
 *        If the filter matches, the key will be returned in the hist_list along with a count of 1. If the key does not exist or
 *        the filter does not match an empty list will be returned with count = 0.
 *
 *   - 4) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = Valid/invalid, hist_list is Valid, Count > 1:
 *        A count >1 will be treated as a count of 1 and the behavior will be same as earlier GET use cases.
 *
 *   - 5) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X, hist_list = Null, Count =0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, a zero count will return an empty list.
 *
 *   - 6) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = valid/invalid, hist_list = Valid, Count > 0:
 *        In this case, the API will return the first count histograms starting from the head of the database. The total
 *        elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. The key is dont-care.  If a filter is specified
 *        only those histograms that match the filter will be returned. A non-Null return hist_list pointer must be provided.
 *
 *   - 7) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = valid/invalid, hist_list = Valid, Count > 0:
 *        In this case, the API will return the next set of histograms starting from the next valid histogram after the specified
 *        key. The total elements fetched will be returned as the return count.  If a filter is specified, only those histograms
 *        that match the filter will be returned.
 *
 *        Note: Return count may be less than or equal to the requested count. If no valid next histogram exists in the database
 *        (key = end of list, or invalid key specified, or key too large), an empty list will be returned.
 *
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param [in] handle           - SX API handle
 * @param [in] cmd              - GET/GET_FIRST/GET_NEXT
 * @param [in] hist_key_p       -Specify a histogram key
 * @param [in] filter           - specify a filter parameter
 * @param [out] hist_list_p      - Return list of histogram keys
 * @param [in,out] hist_cnt_p    - [in] number of histograms to get. max 20/[out] number of histograms returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_CMD_UNSUPPORTED if invalid command is passed
 * @return SX_STATUS_MODULE_UNINITIALIZED if router module is uninitialized
 * @return SX_STATUS_CMD_ERROR if internal RPC mechanism to SDK server fails
 * @return SX_STATUS_DB_NOT_INITIALIZED if internal RIF database is not initialized
 */
sx_status_t sx_api_tele_histogram_iter_get(const sx_api_handle_t            handle,
                                           const sx_access_cmd_t            cmd,
                                           const sx_tele_histogram_key_t   *hist_key_p,
                                           const sx_tele_histogram_filter_t filter,
                                           sx_tele_histogram_key_t         *hist_list_p,
                                           uint32_t                        *hist_cnt_p);


/**
 * This API retrieves the histogram data. Where histogram is created, histogram data is being sampled.
 * The occupancy is being sampled according to the attributes configured in sx_api_tele_histogram_set.
 * The relevant bin is increased according to the current sample occupancy.
 *
 * Note: On Spectrum devices, bin sampling stops when one of the bins reaches max value by bits according to resource manager
 *   variable tele_histogram_data_bin_bits_max.
 *
 * Note: counter histograms support start/stop mechanism and use is capable to run/stop histograms or run it a number of repetition.
 *               Useful in case when user wants to get a coherent value of histograms.
 *               Reading a histogram values when histogram is running can give non consistent values.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - READ/CLEAR
 * @param[in] key - Histogram key
 * @param[out] histogram_p - Histogram data ([out] number of bins and bins content)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported
 * @return SX_STAUS_ERROR general error
 */
sx_status_t sx_api_tele_histogram_data_get(const sx_api_handle_t         handle,
                                           const sx_access_cmd_t         cmd,
                                           const sx_tele_histogram_key_t key,
                                           sx_tele_histogram_data_t     *histogram_p);

/**
 * This API sets the congestion threshold for a specific port and enables a specific TC (in addition to enabled ones).
 * For port-related threshold types, network and LAG ports are supported.
 *
 * Note: On spectrum devices, the last threshold that was set on a port will apply to all TC's in the port.
 * Note: SET cannot be called on an existing entry. To modify, use EDIT.
 * Note: Number of latency thresholds is limited to rm_resource_global.tele_threshold_latency_table_size.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET/EDIT/DESTROY
 * @param[in] key - Threshold key
 * @param[in] data - Threshold data
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation
 * @return SX_STAUS_ERROR on internal error
 */
sx_status_t sx_api_tele_threshold_set(const sx_api_handle_t          handle,
                                      const sx_access_cmd_t          cmd,
                                      const sx_tele_threshold_key_t  key,
                                      const sx_tele_threshold_data_t data);

/**
 * This API retrieves the congestion threshold for a specific port and the TC's the threshold is configured to.
 * For port-related threshold types, network and LAG ports are supported.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - GET
 * @param[in] key - Threshold attributes key
 * @param[in,out] data - Threshold attributes data
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation
 * @return SX_STAUS_ERROR on internal error
 */
sx_status_t sx_api_tele_threshold_get(const sx_api_handle_t         handle,
                                      const sx_access_cmd_t         cmd,
                                      const sx_tele_threshold_key_t key,
                                      sx_tele_threshold_data_t     *data_p);

/**
 * This API retrieves the current threshold congestion state (below/above threshold) for a list of keys.
 * For port related threshold types, only network ports are supported.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle - SX-API handle
 * @param[in]  cmd - GET
 * @param[in]  key_p - List of threshold key
 * @param[out] crossed_data_p - List of threshold crossed data
 * @param[in]  key_cnt - Number of elements in key list and crossed data list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation
 * @return SX_STAUS_ERROR on internal error
 */
sx_status_t sx_api_tele_threshold_crossed_data_get(const sx_api_handle_t             handle,
                                                   const sx_access_cmd_t             cmd,
                                                   const sx_tele_threshold_key_t    *key_p,
                                                   sx_tele_threshold_crossed_data_t *crossed_data_p,
                                                   const uint32_t                    key_cnt);

/**
 * This API sets the attributes of TELEMETRY module.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] attributes - Telemetry module attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_tele_attributes_set(const sx_api_handle_t  handle,
                                       const sx_tele_attrib_t attributes);

/**
 * This API retrieves the attributes of TELEMETRY module.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[out] attributes_p - Telemetry module attributes pointer
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_tele_attributes_get(const sx_api_handle_t handle,
                                       sx_tele_attrib_t     *attributes_p);


/**
 * This API sets the hash signature default profile configuration.
 * There are User and Default profiles for HASH Signature calculation
 * Each profile defines the fields that will be used for hash signature calculation.
 * There is a classifier for each profile that determines the profile to be used for
 * hash calculation of incoming packets.
 * The default profile classifier is predefined to catch any packet and can't be changed.
 * The rule for choosing hash profile is as follow :
 * - If packet hit User profile classifiers then User profile profile
 *      will be used for hash signature calculation
 * - Else Default profile will be used for hash signature calculation
 *
 * Each element in hash_field_enable_list_p enables a specific layer field to be included
 * in the hash calculation according to the de facto fields of the parsed packet.
 * Each element in hash_field_list_p represents a different field to be included in
 * the hash calculation which is subject to the enables which are given in
 * hash_field_enable_list_p.
 *
 * SET replaces existing hash parameters, enables field, and sets fields with new values.
 * ADD adds new fields and enables fields on top of the existing fields (hash parameters are ignored).
 * DELETE deletes specific fields and disable fields from the existing fields (hash parameters are ignored).
 *
 * Supported devices: Spectrum4.
 *
 * @param[in] handle                     - SX-API handle
 * @param[in] cmd                        - SET/ADD/DELETE
 * @param[in] hash_params_p              - hash sig configuration parameters
 * @param[in] hash_field_enable_list_p   - Array of enables to be included in the hash calculation (may be NULL, if empty)
 * @param[in] hash_field_enable_list_cnt - Number of elements in hash_field_enable_list_p
 * @param[in] hash_field_list_p          - Array of fields to be included in the hash calculation (may be NULL, if empty)
 * @param[in] hash_field_list_cnt        - Number of elements in hash_field_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if parameter is incorrectly NULL
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tele_hash_sig_default_prof_set(const sx_api_handle_t                  handle,
                                                  const sx_access_cmd_t                  cmd,
                                                  const sx_tele_hash_sig_params_t       *hash_params_p,
                                                  const sx_tele_hash_sig_field_enable_t *hash_field_enable_list_p,
                                                  const uint32_t                         hash_field_enable_list_cnt,
                                                  const sx_tele_hash_sig_field_t        *hash_field_list_p,
                                                  const uint32_t                         hash_field_list_cnt);

/**
 * This API gets the hash signature default profile configuration parameters.
 * If the given number of fields/fields enables is 0, the API
 * will only return number of fields/enables.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in] handle                           - SX-API handle
 * @param[out] hash_params_p                   - hash sig configuration parameters
 * @param[out] hash_field_enable_list_p        - Array of enables used in the hash calculation
 * @param[in/out] hash_field_enable_list_cnt_p - Number of objects in hash_field_list_p
 * @param[out] hash_field_list_p               - Array of fields used in the hash calculation
 * @param[in/out] hash_field_list_cnt_p        - Number of objects in hash_field_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tele_hash_sig_default_prof_get(const sx_api_handle_t            handle,
                                                  sx_tele_hash_sig_params_t       *hash_params_p,
                                                  sx_tele_hash_sig_field_enable_t *hash_field_enable_list_p,
                                                  uint32_t                        *hash_field_enable_list_cnt_p,
                                                  sx_tele_hash_sig_field_t        *hash_field_list_p,
                                                  uint32_t                        *hash_field_list_cnt_p);


/**
 * This API sets hash-sig user profile configuration.
 * There are User and Default profiles for HASH Signature calculation
 * Each profile defines the fields that will be used for hash signature calculation.
 * There is a classifier for each profile that determines the profile to be
 * used for hash calculation of incoming packets.
 * The default profile classifier is predefined to catch any packet and can't be changed.
 * The rule for choosing hash profile is as follow :
 * - If packet hit User profile classifiers then User profile profile
 *      will be used for hash signature calculation
 * - Else Default profile will be used for hash signature calculation
 *
 * Each element in hash_field_enable_list_p enables a specific layer
 * field to be included in the hash calculation according to the de facto
 * fields of the parsed packet.
 * Each element in hash_field_list_p represents a different field to be
 * included in the hash calculation which is subject to the
 * enables which are given in hash_field_enable_list_p.
 *
 * SET    replaces existing hash parameters, enables field, and sets fields with new values.
 * ADD    adds new fields and enables fields on top of the existing fields
 *        (hash_sig_prof_class_p and hash_params_p parameters are ignored).
 * DELETE deletes specific fields and disable fields from the existing fields
 *        (hash_sig_prof_class_p and hash_params_p parameters are ignored).
 *
 * Supported devices: Spectrum4.
 *
 * @param [in] handle - SX-API handle
 * @param [in] cmd - SET/ADD/DELETE
 * @param [in] hash_sig_prof_idx_p        - hash_sig profile index
 * @param [in] hash_sig_prof_class_p      - hash_sig classifier attributes
 * @param [in] hash_params_p              - hash sig configuration parameters
 * @param [in] hash_field_enable_list_p   - Array of enables to be included in the hash calculation (may be NULL, if empty)
 * @param [in] hash_field_enable_list_cnt - Number of elements in hash_field_enable_list_p
 * @param [in] hash_field_list_p          - Array of fields to be included in the hash calculation (may be NULL, if empty)
 * @param [in] hash_field_list_cnt        - Number of elements in hash_field_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_PARAM_NULL if hash_sig_prof_cfg_p or hash_sig_prof_class_p is NULL
 */
sx_status_t sx_api_tele_hash_sig_prof_set(const sx_api_handle_t                     handle,
                                          const sx_access_cmd_t                     cmd,
                                          const sx_tele_hash_sig_prof_t            *hash_sig_prof_idx_p,
                                          const sx_tele_hash_sig_classifier_attr_t *hash_sig_prof_class_p,
                                          const sx_tele_hash_sig_params_t          *hash_params_p,
                                          const sx_tele_hash_sig_field_enable_t    *hash_field_enable_list_p,
                                          const uint32_t                            hash_field_enable_list_cnt,
                                          const sx_tele_hash_sig_field_t           *hash_field_list_p,
                                          const uint32_t                            hash_field_list_cnt);


/**
 * This API gets hash-sig user profile configuration.
 * If the given number of fields/fields enables is 0, the API
 * will only return number of fields/enables.
 *
 * Supported devices: Spectrum4.
 *
 * @param [in] handle                       - SX-API handle
 * @param [in] hash_sig_prof_idx_p          - hash_sig profile index
 * @param [out] hash_sig_prof_class_p       - hash_sig classifier attributes
 * @param[out] hash_params_p                - hash sig configuration parameters
 * @param[out] hash_field_enable_list_p     - Array of enables to be included in the hash calculation (may be NULL, if empty)
 * @param[inout] hash_field_enable_list_cnt - Number of elements in hash_field_enable_list_p
 * @param[out] hash_field_list_p            - Array of fields to be included in the hash calculation (may be NULL, if empty)
 * @param[inout] hash_field_list_cnt        - Number of elements in hash_field_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_PARAM_NULL if hash_sig_prof_cfg_p or hash_sig_prof_class_p is NULL
 */
sx_status_t sx_api_tele_hash_sig_prof_get(const sx_api_handle_t               handle,
                                          const sx_tele_hash_sig_prof_t      *hash_sig_prof_idx_p,
                                          sx_tele_hash_sig_classifier_attr_t *hash_sig_prof_class_p,
                                          sx_tele_hash_sig_params_t          *hash_params_p,
                                          sx_tele_hash_sig_field_enable_t    *hash_field_enable_list_p,
                                          uint32_t                           *hash_field_enable_list_cnt_p,
                                          sx_tele_hash_sig_field_t           *hash_field_list_p,
                                          uint32_t                           *hash_field_list_cnt_p);

/**
 * This API sets the trap_group to use the TAC.
 *
 * The trap group must be between 0-63.
 * Requirements:
 * - TAC should be enabled in telemetry module attributes ( sx_api_tele_attributes_set )
 * - The trap group should be marked as TAC capable ( sx_api_host_ifc_trap_group_set / ext_set )
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]handle             - SX-API handle
 * @param[in]cmd                - SET / UNSET
 * @param[in]trap_group         - The trap group (must be between 0-63)
 * @param[in]tac_cfg_p	        - trap group TAC configuration
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error or if requirements isn't meet
 */
sx_status_t sx_api_tele_tac_set(const sx_api_handle_t handle,
                                const sx_access_cmd_t cmd,
                                const sx_trap_group_t trap_group,
                                sx_tele_tac_cfg_t    *tac_cfg_p);

/**
 * This API gets the trap group TAC configuration.
 *
 * The trap group must be between 0-63.
 * Requirements:
 * - TAC should be enabled in telemetry module attributes
 * - The trap group should be marked as TAC trap group
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]handle             - SX-API handle
 * @param[in]cmd                - GET
 * @param[in]trap_group         - The trap group (must be between 0-63)
 * @param[out]tac_cfg_p	        - trap group TAC configuration
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_ENTRY_NOT_FOUND if TAC wasn't set on this trap group
 */
sx_status_t sx_api_tele_tac_get(const sx_api_handle_t handle,
                                const sx_access_cmd_t cmd,
                                const sx_trap_group_t trap_group,
                                sx_tele_tac_cfg_t    *tac_cfg_p);

/**
 * This API scan all/filter TAC cache and run tac action.
 *
 * The application/user can listen for the SX_TRAP_ID_TAC_ACTION_DONE event to know that the action is done and new action can start.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]handle              - SX-API handle
 * @param[in]cmd                 - SET
 * @param[in]tac_action_filter_p - TAC action filter
 * @param[in]tac_action_p        - TAC action
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_RESOURCE_IN_USE in case previous command is still in progress
 */
sx_status_t sx_api_tele_tac_action_set(const sx_api_handle_t        handle,
                                       const sx_access_cmd_t        cmd,
                                       sx_tele_tac_action_filter_t *tac_action_filter_p,
                                       sx_tele_tac_action_info_t   *tac_action_info_p);

/**
 * This API get the status of the TAC action block.
 * TAC can execute single action at a time.
 *
 * The action status explanation :
 * SX_TAC_ACTION_STATUS_BUSY_E - Previous TAC action is still in progress
 * SX_TAC_ACTION_STATUS_FREE_E - TAC is free to execute new TAC action
 *
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]handle               - SX-API handle
 * @param[in]cmd                  - GET
 * @param[out]tac_action_status_p - TAC action status
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_tele_tac_action_status_get(const sx_api_handle_t        handle,
                                              const sx_access_cmd_t        cmd,
                                              sx_tele_tac_action_status_t *tac_action_status_p);

/**
 * This API get TAC statistics.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]handle      - SX-API handle
 * @param[in]cmd         - READ / READ_CLEAR
 * @param[out]tac_stat_p - TAC statistics
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_tele_tac_statistics_get(const sx_api_handle_t     handle,
                                           const sx_access_cmd_t     cmd,
                                           sx_tele_tac_statistics_t *tac_stat_p);

/**
 * This API Sets the BW gauge configuration.
 * there are two params that affect the calculation of the BW: log_time_interval, alpha_factor .
 * log_time_interval: This field determine the time between measurements T. T = (2^log_time_interval) * 64uSec.
 *                                        Range 0...12, Default is 7, means that T = (2^7) * 64uSec = 8mSec.
 *
 * alpha_factor: Alpha for the exponential moving average formula. Alpha = 1/(2^alpha_factor)
 *                               Range 0...7, Default is 2.
 *                               new_average_bw = alpha*current_bw + (1-alpha)*previous_bw
 *
 * Note: gauge is running permanently with default configuration defined above. User can read gauge data event without set it.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]  handle - SX-API handle
 * @param[in]  cmd - GET
 * @param[in]  gauge_config - gauge configuration params
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STAUS_ERROR on internal error
 */
sx_status_t sx_api_tele_port_bw_gauge_set(const sx_api_handle_t   handle,
                                          const sx_access_cmd_t   cmd,
                                          sx_tele_gauge_config_t *gauge_config_p);


/**
 * This API retrieves the BW gauge configuration.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]  handle - SX-API handle
 * @param[in]  cmd - GET
 * @param[out]  gauge_config - gauge configuration params
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STAUS_ERROR on internal error
 */
sx_status_t sx_api_tele_port_bw_gauge_get(const sx_api_handle_t   handle,
                                          const sx_access_cmd_t   cmd,
                                          sx_tele_gauge_config_t *gauge_config_p);


/**
 * This API retrieves the BW gauge data (RX and TX BW) of the given  ports.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]  handle - SX-API handle
 * @param[in]  cmd - GET
 * @param[in]  gauge_key - Provided list of ports to get its BW
 * @param[out] gauge_data - RX and TX BW of the ports
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STAUS_ERROR on internal error
 */
sx_status_t sx_api_tele_port_bw_gauge_data_get(const sx_api_handle_t handle,
                                               const sx_access_cmd_t cmd,
                                               sx_tele_gauge_key_t  *gauge_key_p,
                                               sx_tele_gauge_data_t *gauge_data_p);

#endif /* __SX_API_TELE_H__ */
