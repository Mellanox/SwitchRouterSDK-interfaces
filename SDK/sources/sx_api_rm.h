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

#ifndef __SX_API_RM_H__
#define __SX_API_RM_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/***********************************************
*  API functions
***********************************************/

/**
 * \deprecated This API is deprecated and will be removed in the future.
 *  This API is not supported in the current release.
 *  This API set the lower and upper thresholds of an sdk resource.
 *
 * Supported devices: Not supported
 *
 * @param[in] cmd              -ADD/DELETE
 * @param[in] resource         - Resource type
 * @param[in] threshold_full   - Upper threshold value given in percentage
 * @param[in] threshold_empty  - Lower threshold value given in percentage
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if the command is not supported/thresholds are invalid
 */

sx_status_t sx_api_rm_sdk_table_thresholds_set(const sx_api_handle_t             handle,
                                               const sx_access_cmd_t             access_cmd,
                                               const rm_sdk_table_type_e         resource,
                                               const sx_notification_threshold_t threshold_full,
                                               const sx_notification_threshold_t threshold_empty);

/**
 * \deprecated This API is deprecated and will be removed in the future.
 * This API is not supported in the current release.
 *
 * This function gets the lower and upper thresholds of an SDK resource.
 *
 * Supported devices: Not supported.
 *
 * @param[in] resource         - Resource type
 * @param[out] threshold_full  - Upper threshold value given in percentage
 * @param[out] threshold_empty - Lower threshold value given in percentage
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if the command is not supported/thresholds are invalid
 */

sx_status_t sx_api_rm_sdk_table_thresholds_get(const sx_api_handle_t        handle,
                                               const rm_sdk_table_type_e    resource,
                                               sx_notification_threshold_t *threshold_full,
                                               sx_notification_threshold_t *threshold_empty);

/**
 * \deprecated This API is deprecated and will be removed in the future.
 * This API is not supported in the current release.
 *
 * This function sets the lower and upper thresholds of a hardware resource.
 *
 * Supported devices: Not supported
 *
 * @param[in] cmd             - ADD/DELETE
 * @param[in] resource        - Resource type
 * @param[in] threshold_full  - Upper threshold value given in percentage
 * @param[in] threshold_empty - Lower threshold value given in percentage
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if the command is not supported/thresholds are invalid
 */


sx_status_t sx_api_rm_hw_table_thresholds_set(const sx_api_handle_t             handle,
                                              const sx_access_cmd_t             access_cmd,
                                              const rm_hw_table_type_e          resource,
                                              const sx_notification_threshold_t threshold_full,
                                              const sx_notification_threshold_t threshold_empty);

/**
 * \deprecated This API is deprecated and will be removed in the future.
 * This API is not supported in the current release.
 *
 * This function get the lower and upper thresholds of a hardware resource.
 *
 * Supported devices: Not supported.
 *
 * @param[in] resource         - Resource type
 * @param[out] threshold_full  - Upper threshold value given in percentage
 * @param[out] threshold_empty - Lower threshold value given in percentage
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if the command is not supported/thresholds are invalid
 */

sx_status_t sx_api_rm_hw_table_thresholds_get(const sx_api_handle_t        handle,
                                              const rm_hw_table_type_e     resource,
                                              sx_notification_threshold_t *threshold_full,
                                              sx_notification_threshold_t *threshold_empty);

/**
 * This API allows to configure the number of times an entry should be replicated in the KVD Central/KVD Linear Database.
 * This replication provides an increase of the data access bandwidth and general performance of the database,
 * especially in cases when multiple requests want to get access to the same data entry.
 *
 * Note: Configuration is allowed at system init before any entries are added to the KVD.
 * Note: Not all entry types support duplication.
 * Note: RM_SDK_TABLE_TYPE_FIB_IPV6_UC_E, RM_SDK_TABLE_TYPE_FIB_IPV6_SHORT_UC_E and RM_SDK_TABLE_TYPE_FIB_IPV6_LONG_UC_E
 *       have the same replication settings. The configuration applied to one type will be automatically applied to the
 *       other two types as well.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] resource - Resource type
 * @param[in] param_p  - Structure to specify duplication parameter for the resource
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters are invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameters exceed valid range
 * @return SX_STATUS_UNSUPPORTED if API is not supported for this device
 * @return SX_STATUS_PARAM_NULL if param_p is NULL
 * @return SX_STATUS_ERROR general error
 *
 */
sx_status_t sx_api_rm_entries_duplication_set(const sx_api_handle_t                   handle,
                                              const sx_api_table_type_t               resource,
                                              const sx_sdk_table_duplication_param_t *param_p);

/**
 * This API gets the number of entry duplication per specified table type.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] resource    - Resource type
 * @param[in/out] param_p - Structure with retrieved duplication parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters are invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameters exceed valid range
 * @return SX_STATUS_UNSUPPORTED if API is not supported for this device
 * @return SX_STATUS_PARAM_NULL if param_p is NULL.
 * @return SX_STATUS_ERROR general error
 *
 */
sx_status_t sx_api_rm_entries_duplication_get(const sx_api_handle_t             handle,
                                              const sx_api_table_type_t         resource,
                                              sx_sdk_table_duplication_param_t *param_p);


/**
 * This API gets the utilization of a logical resource in the SDK. User is responsible for memory management of the retrieved
 * utilization list.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] resource_list  - List of resources
 * @param[in/out] list_count - [in] size of resource list/[out] size of returned list
 * @param[out] Utilization   - Utilization list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters are invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameters exceed valid range
 * @return SX_STATUS_UNSUPPORTED if API is not supported for this device
 * @return SX_STATUS_PARAM_NULL if any parameters are NULL
 * @return SX_STATUS_ERROR general error
 *
 */
sx_status_t sx_api_rm_sdk_table_utilization_get(const sx_api_handle_t          handle,
                                                sx_api_table_type_t           *resource_list_p,
                                                uint32_t                      *list_count_p,
                                                sx_api_rm_table_utilization_t *utilization_list_p);

/**
 * This API gets the utilization of a logical resource in the SDK and allows to filter or query using a key.
 *
 * Note: User is responsible for memory management of the retrieved utilization list.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] resource_list  - List of logical resource types and their optional keys (mandatory in some cases e.g macsec resources)
 * @param[in/out] list_count - [in] size of resource list/[out] size of returned list
 * @param[out] Utilization   - Utilization list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters are invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameters exceed valid range
 * @return SX_STATUS_UNSUPPORTED if API is not supported for this device
 * @return SX_STATUS_PARAM_NULL if any parameters are NULL
 * @return SX_STATUS_ERROR general error
 *
 */
sx_status_t sx_api_rm_sdk_table_utilization_ext_get(const sx_api_handle_t             handle,
                                                    sx_api_rm_sdk_logical_resource_t *resource_list_p,
                                                    uint32_t                         *list_count_p,
                                                    sx_api_rm_table_utilization_t    *utilization_list_p);
/**
 * This API retrieves the utilization of a hardware table in the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] hw_type      - Hardware table type
 * @param[out] utilization - Utilization in 10th of percentage
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters are invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameters exceed valid range
 * @return SX_STATUS_UNSUPPORTED if API is not supported for this device
 * @return SX_STATUS_PARAM_NULL if any parameters are NULL
 * @return SX_STATUS_ERROR general error
 *
 */
sx_status_t sx_api_rm_hw_utilization_get(const sx_api_handle_t  handle,
                                         sx_api_hw_table_type_t hw_type,
                                         uint32_t             * utilization_p);

/**
 * This API retrieves the utilization of a hardware table in the SDK.
 * This extended API allows to filter or query using a table type & key.
 *
 * Note: for RM_HW_TABLE_TYPE_MACSEC_UTCAM_E, in order to get the HW Utilization
 * of the entire table, please set rsrc_key.macsec_utcam.key_width = SX_ACL_FLEX_KEY_WIDTH_NONE_E
 * To get the HW Utilization for a specific key width please set
 * rsrc_key.macsec_utcam.key_width appropriately.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] hw_type      - Hardware table type + key
 * @param[out] utilization - Utilization in 10th of percentage
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters are invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameters exceed valid range
 * @return SX_STATUS_UNSUPPORTED if API is not supported for this device
 * @return SX_STATUS_PARAM_NULL if any parameters are NULL
 * @return SX_STATUS_ERROR general error
 *
 */
sx_status_t sx_api_rm_hw_utilization_ext_get(const sx_api_handle_t   handle,
                                             sx_api_rm_hw_resource_t hw_type,
                                             uint32_t               *utilization_p);

/**
 * This API retrieves the predicted number of resources that can be added assuming that no other objects are added which
 * may compete for the same hardware resource.
 *
 * Note: this number provides the maximum possible and there is no guarantee that this number will be achievable in practice.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] resource      - Logical resource
 * @param[out] free_count_p - Number of free entries of resource provided
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters are invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameters exceed valid range
 * @return SX_STATUS_UNSUPPORTED if API is not supported for this device
 * @return SX_STATUS_PARAM_NULL if any parameters are NULL
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_rm_free_entries_by_type_get(const sx_api_handle_t     handle,
                                               const sx_api_table_type_t resource,
                                               uint32_t                 *free_cnt_p);

/**
 * This API retrieves the predicted number of resources that can be added to the system.
 * For system-wide resources, it assumes that no other objects are added which
 *  may compete for the same hardware resource.
 * For port-specific resources, such as MACSEC, a key must be specified.
 *
 * Note: The number provided is the maximum possible number of resources and there is
 * no guarantee that this number will be achievable in practice.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] resource      - SDK logical resource
 * @param[out] free_count_p - Number of free entries of resource provided
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters are invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameters exceed valid range
 * @return SX_STATUS_UNSUPPORTED if API is not supported for this device
 * @return SX_STATUS_PARAM_NULL if any parameters are NULL
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_rm_free_entries_by_type_ext_get(const sx_api_handle_t            handle,
                                                   sx_api_rm_sdk_logical_resource_t resource,
                                                   uint32_t                        *free_cnt_p);

#endif /* __SX_API_RM_H__ */
