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


#ifndef __SX_API_TELE_H__
#define __SX_API_TELE_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * Sets the log verbosity level of TELEMETRY MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
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
 * Gets the log verbosity level of TELEMETRY MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
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
 * This API is used to initialize telemetry module.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] params_p - pointer to init params structure.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_NO_RESOURCES if cannot allocate resources for telemetry.
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tele_init_set(const sx_api_handle_t  handle,
                                 sx_tele_init_params_t *params_p);

/**
 * This API is used to deinit telemetry module.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tele_deinit_set(const sx_api_handle_t handle);

/**
 * Sets the Histogram attributes.
 * Command SET sets the histogram attributes described on key to attributes_data
 *
 * Note:
 * For Spectrum: sample time is global, last configured sample time is applied
 *     to all histograms.
 * For latency histograms (supported on Spectrum2 and Spectrum3):
 *      1. Histogram attributes must be identical for all TCs of the same port.
 *      2. Edit command is not supported.
 *         (Destroy all latency histograms on port, than set new configuration).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - SET/EDIT/DESTROY.
 * @param[in] attributes_key - Histogram key.
 * @param[in] attributes_data - Histogram attributes data.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation.
 * @return SX_STAUS_ERROR on internal error.
 */
sx_status_t sx_api_tele_histogram_set(const sx_api_handle_t                     handle,
                                      const sx_access_cmd_t                     cmd,
                                      const sx_tele_histogram_key_t             key,
                                      const sx_tele_histogram_attributes_data_t data);

/**
 *  Retrieves the histogram attributes data that match the key.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET
 * @param[in] key -  Histogram key.
 * @param[out] data_p - Histogram attributes data pointer.
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STAUS_ERROR general error.
 */
sx_status_t sx_api_tele_histogram_get(const sx_api_handle_t                handle,
                                      const sx_access_cmd_t                cmd,
                                      const sx_tele_histogram_key_t        key,
                                      sx_tele_histogram_attributes_data_t *data_p);

/**
 *  This function returns a list of one or more histogram keys.
 *  The following use case scenarios apply with different input parameters
 *  X = don't-care
 *   - 1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, hist_list = X, Count =0:
 *        In this case the API will return the total number of histograms in the
 *        Internal db
 *
 *   - 2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, hist_list =
 *        Valid, Count = 1:
 *        In this case the API will check if the specified key exists. if it does
 *        the key will be returned in the hist_list along with a count of 1.
 *        If the key does not exist an empty list will be returned with count = 0
 *
 *   - 3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = Valid, hist_list is Valid, Count =1:
 *        In this case the API will check if the specified key exists. if it does
 *        it will check it against the filter parameter. If the filter matches,
 *        the key will be returned in the hist_list along with a count of 1.
 *        If the key does not exist or the filter does not match an empty list
 *        will be returned with count = 0
 *
 *   - 4) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = Valid/invalid,
 *        hist_list is Valid, Count > 1:
 *        A count >1 will be treated as a count of 1 and the behavior will be same
 *        as earlier GET use cases.
 *
 *   - 5) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X,
 *        hist_list = Null, Count =0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT a zero count
 *        will return an empty list.
 *
 *   - 6) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = valid/invalid, hist_list =
 *        Valid, Count > 0:
 *        In this case the API will return the first count histograms starting from
 *        the head of the database. The total elements fetched will be returned
 *        as the return count.  Note: return count may be less than or equal to
 *        the requested count. The key is dont-care.
 *        If a filter is specified only those histograms that match the filter will
 *        be returned. a non-Null return hist_list pointer must be provided
 *
 *   - 7) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = valid/invalid,
 *        hist_list = Valid, Count > 0:
 *        In this case the API will return the next set of histograms starting from
 *        the next valid histogram after the specified key. The total elements fetched
 *        will be returned as the return count.  If a filter is specified only
 *        those histograms that match the filter will be returned.
 *        Note: return count may be less than or equal to the requested count.
 *        If no valid next histogram exists in the db (key = end of list, or invalid
 *        key specified, or key too large), an empty list will be returned.
 *
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param [in] handle           : SX API handle
 * @param [in] cmd              : GET/GET_FIRST/GET_NEXT
 * @param [in] hist_key_p       :specify a histogram key
 * @param [in] filter           : specify a filter parameter
 * @param [out] hist_list_p      : return list of histogram keys
 * @param [in,out] hist_cnt_p    : [in] number of histograms to get. max 20
 *                              : [out] number of histograms returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ERROR general error.
 * @return SX_STATUS_CMD_UNSUPPORTED - if invalid cmd is passed
 * @return SX_STATUS_MODULE_UNINITIALIZED - if router module is uninitialized
 * @return SX_STATUS_CMD_ERROR - if internal RPC mechanism to SDK server fails
 * @return SX_STATUS_DB_NOT_INITIALIZED - if internal RIF DB is not initialized
 */
sx_status_t sx_api_tele_histogram_iter_get(const sx_api_handle_t            handle,
                                           const sx_access_cmd_t            cmd,
                                           const sx_tele_histogram_key_t   *hist_key_p,
                                           const sx_tele_histogram_filter_t filter,
                                           sx_tele_histogram_key_t         *hist_list_p,
                                           uint32_t                        *hist_cnt_p);


/**
 * Retrieves the histogram data.
 * Where histogram is created, histogram data is being sampled.
 * The occupancy is being sampled according to the attributes configured in sx_api_tele_histogram_set.
 * The relevant bin is being increased according to the current sample occupancy.
 *
 * For Spectrum: Bin sampling stop when one of the bins reaches max value by bits according to resource manager variable tele_histogram_data_bin_bits_max.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - SX_ACCESS_CMD_READ | SX_ACCESS_CMD_READ_CLEAR
 * @param[in] key - Histogram key.
 * @param[out] histogram_p - Histogram data.
 *                              out - num of bins and bins content.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STAUS_ERROR general error.
 */
sx_status_t sx_api_tele_histogram_data_get(const sx_api_handle_t         handle,
                                           const sx_access_cmd_t         cmd,
                                           const sx_tele_histogram_key_t key,
                                           sx_tele_histogram_data_t     *histogram_p);

/**
 * Sets the congestion threshold for a specific port and enables a specific TC (in addition to
 * enabled ones).
 * Note:
 * SET command cannot be called on an existing entry. in order to modify, use EDIT.
 * For port related thresholds: 1. network and LAG ports are supported.
 * 2. On spectrum, the last threshold that was set on a port will apply to all TC's in the port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - SET/EDIT/DESTROY.
 * @param[in] key - threshold key.
 * @param[in] data - threshold data.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation.
 * @return SX_STAUS_ERROR on internal error.
 */
sx_status_t sx_api_tele_threshold_set(const sx_api_handle_t          handle,
                                      const sx_access_cmd_t          cmd,
                                      const sx_tele_threshold_key_t  key,
                                      const sx_tele_threshold_data_t data);

/**
 * Retrieves the congestion threshold for a specific port and the TC's the threshold is configured to.
 * For port related threshold types, network and LAG ports are supported.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET.
 * @param[in] key - threshold attributes key.
 * @param[in,out] data - threshold attributes data.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation.
 * @return SX_STAUS_ERROR on internal error.
 */
sx_status_t sx_api_tele_threshold_get(const sx_api_handle_t         handle,
                                      const sx_access_cmd_t         cmd,
                                      const sx_tele_threshold_key_t key,
                                      sx_tele_threshold_data_t     *data_p);

/**
 * Retrieves the current threshold congestion state (below / above threshold) for a list of keys.
 * For port related threshold types, only network ports are supported.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle - SX-API handle.
 * @param[in]  cmd - GET.
 * @param[in]  key_p - list of threshold key.
 * @param[out] crossed_data_p - list of threshold crossed data.
 * @param[in]  key_cnt - number of elements in key list and crossed data list.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation.
 * @return SX_STAUS_ERROR on internal error.
 */
sx_status_t sx_api_tele_threshold_crossed_data_get(const sx_api_handle_t             handle,
                                                   const sx_access_cmd_t             cmd,
                                                   const sx_tele_threshold_key_t    *key_p,
                                                   sx_tele_threshold_crossed_data_t *crossed_data_p,
                                                   const uint32_t                    key_cnt);

/**
 * Sets the attributes of telemetry module.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle -      SX-API handle
 * @param[in] attributes -  Telemetry module attributes struct
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_tele_attributes_set(const sx_api_handle_t  handle,
                                       const sx_tele_attrib_t attributes);

/**
 * Retrieves the attributes of telemetry module.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle -      SX-API handle
 * @param[out] attributes_p -  Telemetry module attributes pointer
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_tele_attributes_get(const sx_api_handle_t handle,
                                       sx_tele_attrib_t     *attributes_p);

#endif /* __SX_API_TELE_H__ */
