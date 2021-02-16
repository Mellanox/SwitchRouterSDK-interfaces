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

#ifndef __SX_API_COS_H__
#define __SX_API_COS_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_cos_redecn.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of COS MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - COS module verbosity level
 * @param[in] api_verbosity_level      - COS API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of COS MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - COS module verbosity level
 * @param[out] api_verbosity_level_p    - COS API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This function sets the port default switch priority value.
 * This default priority value is used in "trust port" configurations.
 * This default priority value is also used in cases when trust level is
 * configured as L2 or L3 and the relevant packet fields that determine the
 * priority value are unavailable in the packet.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 * In Spectrum the function sets the default switch-priority.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] log_port     - logical port ID
 * @param[in] priority     - switch priority [0..cos_port_prio_max
 *                              (see resource manager) , default is 0]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 */
sx_status_t sx_api_cos_port_default_prio_set(const sx_api_handle_t   handle,
                                             const sx_port_log_id_t  log_port,
                                             const sx_cos_priority_t priority);

/**
 * This function retrieves the default port switch priority value.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  log_port        - logical port ID
 * @param[out] priority_p      - switch priority [0..cos_port_prio_max
 *                              (see resource manager) , default is 0]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_default_prio_get(const sx_api_handle_t  handle,
                                             const sx_port_log_id_t log_port,
                                             sx_cos_priority_t     *priority_p);

/**
 *  This function adds or deletes a priority to/from a traffic
 *  class (TC). When a switch priority is added to a TC, it is
 *  automatically re-mapped from its previous allocation. When
 *  a priority is deleted from a TC, it is reallocated
 *  according to default settings.
 *
 *  Each packet has an assigned priority. The priority of the packet
 *  is mapped to one of eight traffic classes (egress queue)
 *  according to prio -> traffic class map.
 *  Each packet is dequeued on the egress port based on its
 *  traffic class.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 *  Note: Multiple priorities can be mapped to a single TC.
 *
 *  Spectrum:
 *      default settings:
 *          for i = [0,7]: switch priority i -> traffic class i.
 *          for i = [8,14]: switch priority i -> traffic class 7.
 *      Higher TC behavior:
 *          If a switch priority is mapped to a higher TC X [where 8 <= X <= 15],
 *          packets sent on TC X will still be counted against TC X-8
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - Add/Delete
 * @param[in] log_port      - logical port ID (egress port)
 * @param[in] priority      - priority
 * @param[in] traffic_class - traffic class
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_CMD_ERROR if an unsupported command is requested
 */
sx_status_t sx_api_cos_port_tc_prio_map_set(const sx_api_handle_t        handle,
                                            const sx_access_cmd_t        cmd,
                                            const sx_port_log_id_t       log_port,
                                            const sx_cos_priority_t      priority,
                                            const sx_cos_traffic_class_t traffic_class);

/**
 * This function retrieves the traffic class of a specific
 * switch priority.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  log_port        - logical port ID
 * @param[in]  priority        - priority
 * @param[out] traffic_class_p - traffic class
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_tc_prio_map_get(const sx_api_handle_t   handle,
                                            const sx_port_log_id_t  log_port,
                                            const sx_cos_priority_t priority,
                                            sx_cos_traffic_class_t *traffic_class_p);

/**
 * This function sets the port trust level value.
 * Assigns the user priority based on the following modes:
 * Trust port user priority - ignore packets priority and assign
 * priority based on the port configuration.
 * Trust packet user priority/Trust L2 - tagged L2 packets are assigned with
 * packets priority, untagged packets are assigned with port's priority.
 * Trust DSCP/Trust L3 - IP packets are assigned with a priority based on
 * the DSCP to UP mapping. Non-IP packets are assigned with
 * port's priority.
 * Trust both - IP packets are assigned with a priority based on the
 * DSCP to UP mapping. Else, tagged L2 packets are assigned with
 * packets priority, untagged packets are assigned with port's priority.
 * In Spectrum for MPLS packets EXP field is used instead of DSCP.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - logical port id
 * @param[in] trust_level - trust level  [trust port user priority,
 *                                        trust L2,
 *                                        trust L3,
 *                                        trust both]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 */
sx_status_t sx_api_cos_port_trust_set(const sx_api_handle_t      handle,
                                      const sx_port_log_id_t     log_port,
                                      const sx_cos_trust_level_t trust_level);

/**
 * This function retrieves the port trust level value.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle        - SX-API handle
 * @param[in]  log_port      - logical port id
 * @param[out] trust_level_p - trust level  [trust port,
 *                                           trust L2,
 *                                           trust L3,
 *                                           trust both]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_trust_get(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      sx_cos_trust_level_t  *trust_level_p);

/**
 * This API sets the port's priority to buffer map in the SDK.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * Note:
 * Untagged frames must use a buffer used by one of the priorities.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - access command SX_ACCESS_CMD_SET
 * @param[in] log_port        - logical port ID
 * @param[in] prio_to_buff_p  - mapping of switch priorities to PG buffers
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_CMD_UNSUPPORTED command is not supported
 */
sx_status_t sx_api_cos_port_prio_buff_map_set(const sx_api_handle_t    handle,
                                              const sx_access_cmd_t    cmd,
                                              const sx_port_log_id_t   log_port,
                                              sx_cos_port_prio_buff_t *prio_to_buff_p);

/**
 * This API retrieves the port's priority to buffer mapping from the SDK.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - logical port ID
 * @param[out] prio_to_buff_p - mapping of switch priorities to PG buffers
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_buff_map_get(const sx_api_handle_t    handle,
                                              const sx_port_log_id_t   log_port,
                                              sx_cos_port_prio_buff_t *prio_to_buff_p);

/**
 * This API sets the pool parameters.
 * It is used to set shared buffer pools and shared headroom pools.
 *
 * Note:
 * Shared headroom pools must have ingress direction and valid size.
 * Infinite size is not allowed and the only supported mode is
 * SX_COS_BUFFER_MAX_MODE_BUFFER_UNITS_E, Other attributes are ignored.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - CMD SX_ACCESS_CMD_CREATE /SX_ACCESS_CMD_DESTROY/ SX_ACCESS_CMD_EDIT
 * @param[in] sx_cos_pool_attr    - Pool attributes pointer (Direction, Size (in Cells), Mode (dynamic/static))
 * @param[in/out] pool_id         - Pool ID pointer - use CMD SX_ACCESS_CMD_CREATE command will return the user pool_id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_shared_buff_pool_set(const sx_api_handle_t handle,
                                            const sx_access_cmd_t cmd,
                                            sx_cos_pool_attr_t   *sx_cos_pool_attr,
                                            uint32_t             *pool_id);

/**
 * This API gets the shared buffer pool attributes.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] pool_id             - Pool ID
 * @param[out] sx_cos_pool_attr_p - Pool attributes (Direction, Size, Shared size, Mode (dynamic/static))
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_shared_buff_pool_get(const sx_api_handle_t handle,
                                            const uint32_t        pool_id,
                                            sx_cos_pool_attr_t  * sx_cos_pool_attr_p);

/**
 * This API sets the port buffers size and threshold (Xon/Xoff) according to
 * port buffer attribute type
 * With command SX_ACCESS_CMD_SET and attribute size non-zero, the API allocates
 * the specific port buffer with attribute size (configures specific buffer entry)
 * With command SX_ACCESS_CMD_SET and attribute size zero, the API releases the size
 * of specific port buffer (delete specific buffer entry)
 * With command SX_ACCESS_CMD_DELETE, the API releases specific port buffers that
 * were received on port_buffer_attr_list_p (set size zero for those ports)
 * With command SX_ACCESS_CMD_DELETE_ALL, the API releases all the port buffers
 * configured on specific logical port (deletes all buffer entries on logical port)
 * With logical port param, a validation is done to allocate mc buffer only if the
 * user sets log_port param with single reserved value MC_LOG_ID as defined in sx_port.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - CMD SX_ACCESS_CMD_SET/SX_ACCESS_CMD_DELETE/SX_ACCESS_CMD_DELETE_ALL
 * @param[in] log_port                  - logical port ID
 * @param[in] port_buffer_attr_list_p   - pointer to list of port buffers attributes
 * @param[in] port_buffer_attr_cnt      - Number of port buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_buff_type_set(const sx_api_handle_t            handle,
                                          const sx_access_cmd_t            cmd,
                                          const sx_port_log_id_t           log_port,
                                          const sx_cos_port_buffer_attr_t *port_buffer_attr_list_p,
                                          const uint32_t                   port_buffer_attr_cnt);

/**
 * This API gets the port buffers size and thresholds (Xon/Xoff) according to port buffer attribute type
 * Port buffer thresholds can only be retrieved for a single buffer type.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] log_port                  - logical port ID
 * @param[in/out] port_buffer_attr_list_p  - pointer to list of port buffers attributes
 * @param[in/out] port_buffer_attr_cnt  - Number of port buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_buff_type_get(const sx_api_handle_t      handle,
                                          const sx_port_log_id_t     log_port,
                                          sx_cos_port_buffer_attr_t *port_buffer_attr_list_p,
                                          uint32_t                  *port_buffer_attr_cnt);

/**
 * This API sets the port shared buffers attributes according to port shared buffer attribute type
 * With command SX_ACCESS_CMD_SET and attribute max size/alpha non-zero, the API allocates the
 * specific port shared buffer with attribute depending on the mode (configures specific buffer entry)
 * With command SX_ACCESS_CMD_SET and attribute max size/alpha zero, the API releases the size of
 * specific port shared buffer (delete specific buffer entry)
 * With command SX_ACCESS_CMD_DELETE, the API releases specific port buffers that received on
 * port_shared_buffer_attr_list_p (set max alpha/size zero for those ports)
 * With command SX_ACCESS_CMD_DELETE_ALL, the API releases all the port shared buffers configured
 * on specific logical port (set max alpha/size zero on all buffer entries on logical port)
 * With logical port param, a validation is done to allocate mc buffer only if the
 * user sets log_port param with single reserved value MC_LOG_ID as defined in sx_port.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                            - SX-API handle
 * @param[in] cmd                               - CMD SX_ACCESS_CMD_SET/SX_ACCESS_CMD_DELETE/SX_ACCESS_CMD_DELETE_ALL
 * @param[in] log_port                          - logical port ID
 * @param[in] port_shared_buffer_attr_list_p    - pointer to list of port shared buffer attributes
 * @param[in] port_shared_buffer_attr_cnt       - Number of port shared buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_shared_buff_type_set(const sx_api_handle_t                   handle,
                                                 const sx_access_cmd_t                   cmd,
                                                 const sx_port_log_id_t                  log_port,
                                                 const sx_cos_port_shared_buffer_attr_t *port_shared_buffer_attr_list_p,
                                                 const uint32_t                          port_shared_buffer_attr_cnt);

/**
 * This API gets the port shared buffers attributes according to port shared buffer attribute type
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                            - SX-API handle
 * @param[in] log_port                          - logical port ID
 * @param[in/out] port_shared_buffer_attr_list_p   - pointer to list of port shared buffer attributes
 * @param[in/out] port_shared_buffer_attr_cnt   - Number of port shared buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_shared_buff_type_get(const sx_api_handle_t             handle,
                                                 const sx_port_log_id_t            log_port,
                                                 sx_cos_port_shared_buffer_attr_t *port_shared_buffer_attr_list_p,
                                                 uint32_t                         *port_shared_buffer_attr_cnt);

/**
 * This API gets the buffer status.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[out] status   - the buffer global status
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_buff_status_get(const sx_api_handle_t handle,
                                       sx_buffer_status_t   *status);

/**
 * This API returns the list of initialized pools
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in/out] pool_cnt   - the number of pools in the list
 * @param[out] pool_list_p - list of pool ids
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_pools_list_get(const sx_api_handle_t handle,
                                      uint32_t             *pool_cnt,
                                      sx_cos_pool_id_t     *pool_list_p);

/**
 * This API gets the port buffers occupancy parameters.
 *
 * Note: This API allows getting multiple statistic elements per port.
 * When number of statistic elements exceed the API capability it will return
 * SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - CMD SX_ACCESS_CMD_READ /SX_ACCESS_CMD_READ_CLEAR
 * @param[in] statistic_param_list_p - Pointer to a list of statistics input structure (Port, PG, Direction)
 * @param[in] statistic_cnt          - Number of input parameters in the list
 * @param[out] usage_list_p          - Pointer to a list of usage params
 * @param[in/out] usage_cnt          - Number of output parameters in the list (if zero - number of elements will be returned)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT when too many statistic elements are requested
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_buff_type_statistic_get(const sx_api_handle_t                   handle,
                                                    const sx_access_cmd_t                   cmd,
                                                    const sx_port_statistic_usage_params_t *statistic_param_list_p,
                                                    const uint32_t                          statistics_cnt,
                                                    sx_port_occupancy_statistics_t         *usage_list_p,
                                                    uint32_t                               *usage_cnt);

/**
 * This API gets pool occupancy statistics.
 * Note: Shared headroom pools do not support watermark statistics.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - SX_ACCESS_CMD_READ /SX_ACCESS_CMD_READ_CLEAR
 * @param[in] pool_id_list_p     - Pointer to a list of Pool IDs (size - in units of cells)
 * @param[in] pool_id_cnt        - Number of parameters in the list
 * @param[out] usage_list_p      - Pointer to a list of usage params
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_NO_RESOURCES if memory allocations have failed
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_pool_statistic_get(const sx_api_handle_t               handle,
                                          const sx_access_cmd_t               cmd,
                                          const sx_cos_pool_id_t             *pool_id_list_p,
                                          const uint32_t                      pool_id_cnt,
                                          sx_cos_pool_occupancy_statistics_t *usage_list_p);

/**
 * This function sets the default color value of a given port. Used for trust level "port"
 * or for packets without the relevant priority field for the configured trust level(L2/L3)
 * This API is not supported for VPORT.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle      - SX-API handle
 * @param[in]  log_port    - logical port ID
 * @param[in]  color       - color
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_default_color_set(const sx_api_handle_t  handle,
                                              const sx_port_log_id_t log_port,
                                              const sx_cos_color_t   color);

/**
 * This function retrieves the default port color value.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 * This API is not supported for VPORT.
 *
 * @param[in]  handle     - SX-API handle
 * @param[in]  log_port   - logical port ID
 * @param[out] color_p    - color
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_default_color_get(const sx_api_handle_t  handle,
                                              const sx_port_log_id_t log_port,
                                              sx_cos_color_t        *color_p);

/**
 * This API sets the default PCP,DEI field value for arriving untagged packets.
 * This API is not supported for VPORT.
 * See sx_api_cos_port_default_prio_set.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle      - SX-API handle
 * @param[in]  log_port    - logical port ID
 * @param[in] pcp_dei      - PCP,DEI
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_default_pcpdei_set(const sx_api_handle_t  handle,
                                               const sx_port_log_id_t log_port,
                                               const sx_cos_pcp_dei_t pcp_dei);

/**
 * This function retrieves the default PCP,DEI field value for arriving untagged packets.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 * Not supported per VPORT.
 *
 * @param[in]  handle     - SX-API handle
 * @param[in]  log_port   - logical port ID
 * @param[out] pcp_dei_p  - PCP,DEI
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_default_pcpdei_get(const sx_api_handle_t  handle,
                                               const sx_port_log_id_t log_port,
                                               sx_cos_pcp_dei_t      *pcp_dei_p);

/**
 * This function sets the mapping between PCP, DEI and switch-priority, color.
 * This table is used when the port trust mode is set to 'trust L2'.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] pcp_dei_p  - a list of PCP's and DEI's
 * @param[in] switch_priority - a list of switch priorities
 * @param[in] element_cnt - num of elements in PCP, DEI and Switch Prio lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_pcpdei_to_prio_set(const sx_api_handle_t          handle,
                                               const sx_port_log_id_t         log_port,
                                               const sx_cos_pcp_dei_t        *pcp_dei_p,
                                               const sx_cos_priority_color_t *switch_priority_color_p,
                                               const uint32_t                 element_cnt);

/**
 * This function retrieves the mapping from PCP,DEI to switch-priority and color.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[out] pcp_dei_p  - a list of PCP's and DEI's
 * @param[out] switch_priority_color_p - a list of switch priorities and colors
 * @param[in/out] element_cnt_p - num of elements in PCP, DEI and Switch Prio lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_pcpdei_to_prio_get(const sx_api_handle_t    handle,
                                               const sx_port_log_id_t   log_port,
                                               sx_cos_pcp_dei_t        *pcp_dei_p,
                                               sx_cos_priority_color_t *switch_priority_color_p,
                                               uint32_t                *element_cnt_p);

/**
 * This function sets the mapping from switch-priority to IEEE priority.
 * This IEEE priority value is used in the switch for pause flow control
 * The device maps the switch-priority into IEEE priority value using
 * device global Switch Priority to IEEE Priority Table (not per port).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] switch_priority_p - a list of switch priorities
 * @param[in] ieee_priority_p   - a list of IEEE priorities
 * @param[in] element_cnt - num of elements in switch priorities and ieee priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_prio_to_ieeeprio_set(const sx_api_handle_t     handle,
                                            const sx_cos_priority_t  *switch_priority_p,
                                            const sx_cos_ieee_prio_t *ieee_priority_p,
                                            const uint32_t            element_cnt);

/**
 * This function retrieves the mapping from switch-priority to IEEE priority.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[out] switch_priority_p - switch priorities list
 * @param[out] ieee_priority_p   - IEEE priorities list
 * @param[in/out] element_cnt_p   - num of elements in switch priorities and ieee priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_prio_to_ieeeprio_get(const sx_api_handle_t handle,
                                            sx_cos_priority_t    *switch_priority_p,
                                            sx_cos_ieee_prio_t   *ieee_priority_p,
                                            uint32_t             *element_cnt_p);

/**
 * This function sets the mapping from EXP to switch-priority, color and ECN value.
 * This table is used for MPLS packets when the port trust mode is set to 'L3'
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] exp_p           - a list of EXP's
 * @param[in] switch_priority_color_p - a list of switch priorities and colors
 * @param[in] ecn_p    - a list of ECN's
 * @param[in] element_cnt - num of elements in EXP's, ECN's and switch priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_exp_to_prio_set(const sx_api_handle_t          handle,
                                            const sx_port_log_id_t         log_port,
                                            const sx_cos_exp_t            *exp_p,
                                            const sx_cos_priority_color_t *switch_priority_color_p,
                                            const sx_cos_ecn_t            *ecn_p,
                                            const uint32_t                 element_cnt);

/**
 * This function retrieves the mapping from EXP to switch-priority, color and ECN value.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[out] exp_p           - a list of EXP's
 * @param[out] switch_priority_color_p -  an array of switch priorities and colors
 * @param[out] ecn_p           - a list of ECN's
 * @param[in/out] element_cnt_p - num of elements in EXP's and switch priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_exp_to_prio_get(const sx_api_handle_t    handle,
                                            const sx_port_log_id_t   log_port,
                                            sx_cos_exp_t            *exp_p,
                                            sx_cos_priority_color_t *switch_priority_color_p,
                                            sx_cos_ecn_t            *ecn_p,
                                            uint32_t                *element_cnt_p);

/**
 * This function sets the mapping from DSCP to switch-priority and color.
 * This table is used when the port trust mode is set to 'L3'.
 * The mapping from DSCP to switch prio is on a per port basis and is applicable only in Spectrum.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port              - logical port ID
 * @param[in] dscp_p                - a list of DSCP's
 * @param[in] switch_priority_color - a list of switch priorities and colors
 * @param[in] element_cnt           - num of elements in DSCP's and switch priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_dscp_to_prio_set(const sx_api_handle_t          handle,
                                             const sx_port_log_id_t         log_port,
                                             const sx_cos_dscp_t           *dscp_p,
                                             const sx_cos_priority_color_t *switch_priority_color_p,
                                             const uint32_t                 element_cnt);

/**
 * This function retrieves the mapping from DSCP to switch-priority and color.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] log_port             - logical port ID
 * @param[out] dscp_p              - a list of DSCP's
 * @param[out] switch_priority_color_p   - a list of switch priorities and colors
 * @param[in/out] element_cnt_p  - num of elements in DSCP's and switch priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_dscp_to_prio_get(const sx_api_handle_t    handle,
                                             const sx_port_log_id_t   log_port,
                                             sx_cos_dscp_t           *dscp_p,
                                             sx_cos_priority_color_t *switch_priority_color_p,
                                             uint32_t                *element_cnt_p);

/**
 * This function defines rewrite enable option setting of PCP, DEI, DSCP and EXP
 * bits in packet header. The values of rewriting are defined by mapping
 * in the following functions.
 * The rewrite is defined on an ingress port.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] log_port - ingress logical port ID
 * @param[in] rewrite  - should rewrite PCP/DEI, DSCP, EXP
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_rewrite_enable_set(const sx_api_handle_t         handle,
                                               const sx_port_log_id_t        log_port,
                                               const sx_cos_rewrite_enable_t rewrite);

/**
 * This function retrieves rewrite enable option setting of PCP, DEI, DSCP and EXP
 * bits in packet header.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port   - ingress logical port ID
 * @param[out] rewrite_p - should rewrite PCP/DEI, DSCP, EXP
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_rewrite_enable_get(const sx_api_handle_t    handle,
                                               const sx_port_log_id_t   log_port,
                                               sx_cos_rewrite_enable_t *rewrite_p);

/**
 * This function defines the mapping from switch-priority, color to PCP, DEI for PCP and DEI rewrite,
 * in packet header.
 * The mapping will change the PCP, DEI values only if PCP, DEI rewrite was enabled in
 * sx_api_cos_port_rewrite_enable_set.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port - egress logical port ID
 * @param[in] switch_priority_color_p   - a list of switch priorities, and colors
 * @param[in] pcp_dei_p   - a list of PCP's and DEI's
 * @param[in] element_cnt - switch priorities and PCP's, DEI's lists elements count
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_pcpdei_rewrite_set(const sx_api_handle_t          handle,
                                                       const sx_port_log_id_t         log_port,
                                                       const sx_cos_priority_color_t *switch_priority_color_p,
                                                       const sx_cos_pcp_dei_t        *pcp_dei_p,
                                                       const uint32_t                 element_cnt);


/**
 * This function retrieves the mapping from switch-priority, color to PCP, DEI for PCP and DEI
 * rewrite, in packet header.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port   - egress logical port ID
 * @param[out] switch_priority_color_p - a list of switch priorities and colors
 * @param[out] pcp_dei_p      - a list of PCP's and DEI's
 * @param[in/out] element_cnt_p - switch priorities and DSCP lists elements count
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_pcpdei_rewrite_get(const sx_api_handle_t    handle,
                                                       const sx_port_log_id_t   log_port,
                                                       sx_cos_priority_color_t *switch_priority_color_p,
                                                       sx_cos_pcp_dei_t        *pcp_dei_p,
                                                       uint32_t                *element_cnt_p);

/**
 * This function defines the mapping from switch-priority, color to DSCP, for DSCP rewrite,
 * in packet header.
 * The mapping will change the DSCP values only if DSCP rewrite was enabled in
 * sx_api_cos_port_rewrite_enable_set
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port - egress logical port ID
 * @param[in] switch_priority_color_p   - list of switch priorities, and colors
 * @param[in] dscp_p   - a list of DSCP's
 * @param[in] element_cnt - switch priorities and DSCP's lists elements count
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_dscp_rewrite_set(const sx_api_handle_t          handle,
                                                     const sx_port_log_id_t         log_port,
                                                     const sx_cos_priority_color_t *switch_priority_color_p,
                                                     const sx_cos_dscp_t           *dscp_p,
                                                     const uint32_t                 element_cnt);

/**
 * This function retrieves the mapping from switch-priority, color to DSCP, for DSCP
 * rewrite, in packet header.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port   - egress logical port ID
 * @param[out] switch_priority_color_p - a list of switch priorities and colors
 * @param[out] dscp_p      - a list of DSCP's
 * @param[in/out] element_cnt_p - switch priorities and DSCP lists elements count
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_dscp_rewrite_get(const sx_api_handle_t    handle,
                                                     const sx_port_log_id_t   log_port,
                                                     sx_cos_priority_color_t *switch_priority_color_p,
                                                     sx_cos_dscp_t           *dscp_p,
                                                     uint32_t                *element_cnt_p);

/**
 * This function defines the mapping from switch-priority, color and ECN to EXP, for EXP rewrite,
 * in packet header.
 * The mapping will change the EXP values only if EXP rewrite was enabled in
 * sx_api_cos_port_rewrite_enable_set
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] log_port                - egress logical port ID
 * @param[in] switch_priority_color_p - list of switch priorities, colors
 * @param[in] ecn_p                   - list of ECN's
 * @param[in] exp_p                   - list of EXP's
 * @param[in] element_cnt             - switch priorities, EXP's and ECN's lists elements count
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_exp_rewrite_set(const sx_api_handle_t          handle,
                                                    const sx_port_log_id_t         log_port,
                                                    const sx_cos_priority_color_t *switch_priority_color_p,
                                                    const sx_cos_ecn_t            *ecn_p,
                                                    const sx_cos_exp_t            *exp_p,
                                                    const uint32_t                 element_cnt);

/**
 * This function retrieves rewriting of EXP bits setting.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                       - SX-API handle
 * @param[in] log_port                     - egress logical port ID
 * @param[out] switch_priority_color_ecn_p - a list of switch priorities, colors
 * @param[out] ecn_p                       - a list of ECN's
 * @param[out] exp_p                       - a list of EXP's
 * @param[in/out] element_cnt_p               - switch priorities, ECN's and EXP's lists elements count
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_exp_rewrite_get(const sx_api_handle_t    handle,
                                                    const sx_port_log_id_t   log_port,
                                                    sx_cos_priority_color_t *switch_priority_color_p,
                                                    sx_cos_ecn_t            *ecn_p,
                                                    sx_cos_exp_t            *exp_p,
                                                    uint32_t                *element_cnt_p);
/**
 * This function sets PTP shaper parameters
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                        - SX-API handle
 * @param[in] cmd                           - SX_ACCESS_CMD_SET : set new shaper parameters
 *                                            SX_ACCESS_CMD_DELETE : reset shaper parameters to default
 * @param[in] port_speed                    - The link speed of the port
 * @param[in] shaper_params                 - The ptp shaper parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_ets_ptp_shaper_param_set(const sx_api_handle_t          handle,
                                                const sx_access_cmd_t          cmd,
                                                sx_cos_ets_ptp_port_speed_e    port_speed,
                                                sx_cos_ets_ptp_shaper_params_t shaper_params);

/**
 * This function retrieves PTP shaper parameters
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                        - SX-API handle
 * @param[in] cmd                           - SX_ACCESS_CMD_GET : retrieve current shaper parameters
 * @param[in] port_speed                    - The link speed of the port
 * @param[in] shaper_params                 - The ptp shaper parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_ets_ptp_shaper_param_get(const sx_api_handle_t           handle,
                                                const sx_access_cmd_t           cmd,
                                                sx_cos_ets_ptp_port_speed_e     port_speed,
                                                sx_cos_ets_ptp_shaper_params_t *shaper_params);

/**
 * This function binds a traffic class (TC) to a TC queue and group,
 * and sets shapers and rate-based ECN threshold.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd - SX_ACCESS_CMD_CREATE: create a queuing structure
 *                  SX_ACCESS_CMD_ADD: add an element to an existing queuing structure
 *                  SX_ACCESS_CMD_EDIT: edit an element in an existing queuing structure
 *                  SX_ACCESS_CMD_DESTROY: destory the queuing structure (return to default)
 * @param[in] log_port          - egress port ID
 * @param[in] ets_element       - ETS element array
 * @param[in] ets_element_cnt - num of ETS elements
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_ets_element_set(const sx_api_handle_t              handle,
                                            const sx_access_cmd_t              cmd,
                                            const sx_port_log_id_t             log_port,
                                            const sx_cos_ets_element_config_t *ets_element_p,
                                            const uint32_t                     element_cnt);

/**
 * This function retrieves all elements of the queuing system.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle             - SX-API handle
 * @param[in]  log_port           - egress port ID
 * @param[out]  ets_element       - ETS element array
 * @param[in/out] ets_element_cnt - num of ETS elements
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_ets_element_get(const sx_api_handle_t        handle,
                                            const sx_port_log_id_t       log_port,
                                            sx_cos_ets_element_config_t *ets_element_p,
                                            uint32_t                    *element_cnt_p);

/**
 * This function sets the port MC awareness mode.
 * If mc_aware==TRUE then the MC traffic will be mapped to the higher TC's (8-15)
 * and the UC traffic will be mapped to the lower TC's (0-7).
 * If there is a mapping configured to TC 8-15 the function will return SX_STATUS_ERROR
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - egress port ID
 * @param[in] mc_aware - MC aware TC mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_tc_mcaware_set(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t log_port,
                                           const boolean_t        mc_aware);

/**
 * This function retrieves the port MC awareness mode.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port - egress port ID
 * @param[out] mc_aware   - MC aware TC mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_tc_mcaware_get(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t log_port,
                                           boolean_t             *mc_aware_p);

/**
 * \deprecated This API is deprecated and will be removed in the future.
 * Please use sx_api_cos_redecn_log_verbosity_level_set in its place.
 * This API sets the log verbosity level of REDECN MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - module verbosity level
 * @param[in] api_verbosity_level      - API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_verbosity_level_set(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  const sx_verbosity_level_t      module_verbosity_level,
                                                  const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API sets the log verbosity level of REDECN MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - module verbosity level
 * @param[in] api_verbosity_level      - API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                      const sx_log_verbosity_target_t verbosity_target,
                                                      const sx_verbosity_level_t      module_verbosity_level,
                                                      const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of REDECN MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - module verbosity level
 * @param[out] api_verbosity_level_p    - API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                      const sx_log_verbosity_target_t verbosity_target,
                                                      sx_verbosity_level_t           *module_verbosity_level_p,
                                                      sx_verbosity_level_t           *api_verbosity_level_p);
/**
 * This function sets global configuration of ECN and RED
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] configuration_p   - configuration parameters @see sx_cos_redecn_global_t
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 *
 */
sx_status_t sx_api_cos_redecn_general_param_set(const sx_api_handle_t         handle,
                                                const sx_cos_redecn_global_t *configuration_p);


/**
 * This function gets global configuration of ECN and RED
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[out] configuration_p  - configuration parameters @see sx_cos_redecn_global_t
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 *
 */
sx_status_t sx_api_cos_redecn_general_param_get(const sx_api_handle_t   handle,
                                                sx_cos_redecn_global_t *configuration_p);


/**
 * This function creates a single RED/ECN profile
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]       handle -            SX-API handle
 * @param[in]       cmd -                       SX_ACCESS_CMD_ADD - create a new profile - profile_p is the output
 *                                                                      SX_ACCESS_CMD_EDIT - edit a profile
 *                                                                      SX_ACCESS_CMD_DELETE - delete a profile (params_p is ignored)
 * @param[in]       params_p -          parameter of redecn profile attributes
 * @param[in/out]   profile_p -     configured or profile to reconfigure/delete
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_NO_RESOURCES no available
 *
 */
sx_status_t sx_api_cos_redecn_profile_set(const sx_api_handle_t                     handle,
                                          const sx_access_cmd_t                     cmd,
                                          const sx_cos_redecn_profile_attributes_t *params_p,
                                          sx_cos_redecn_profile_t                  *profile_p);


/**
 * This function gets RED/ECN profile configuration for given profile
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]   handle -        SX-API handle
 * @param[in]   profile -       redecn profile to get
 * @param[out]  params_p -      structure of retrieved profile attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 *
 */
sx_status_t sx_api_cos_redecn_profile_get(const sx_api_handle_t               handle,
                                          const sx_cos_redecn_profile_t       profile,
                                          sx_cos_redecn_profile_attributes_t *params_p);


/**
 * This function enables/disables RED and ECN for traffic classes
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle -                  SX-API handle
 * @param[in] log_port -                egress port to set
 * @param[in] traffic_classes_p -       list of traffic classes this configuration applies to
 * @param[in] traffic_classes_cnt -     num of traffic classes
 * @param[in] params_p -                enable parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_tc_enable_set(const sx_api_handle_t                handle,
                                            const sx_port_log_id_t               log_port,
                                            const sx_cos_traffic_class_t        *traffic_classes_p,
                                            const uint8_t                        traffic_classes_cnt,
                                            const sx_cos_redecn_enable_params_t *params_p);


/**
 * This function gets RED and ECN enabled parameters of a traffic class
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - egress port to query
 * @param[in] traffic_class - traffic class to get
 * @param[out] params_p - enable parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_tc_enable_get(const sx_api_handle_t          handle,
                                            const sx_port_log_id_t         log_port,
                                            const sx_cos_traffic_class_t   traffic_class,
                                            sx_cos_redecn_enable_params_t *params_p);


/**
 * This function binds RED and ECN profiles to the traffic class and traffic type (TCP/non-TCP, color).
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - egress port to bind/unbind
 * @param[in] cmd - SX_ACCESS_CMD_BIND - bind a port+tc+flow to a profile
 *                                      SX_ACCESS_CMD_UNBIND - unbind a port+tc+flow from a profile
 * @param[in] traffic_classes_p - traffic classes affected by this command
 * @param[in] traffic_classes_cnt - number of traffic classes in the above array
 * @param[in] flow_type - flow type to bind/unbind
 * @param[in] params_p - profile to bind to this flow type
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_profile_tc_bind_set(const sx_api_handle_t              handle,
                                                  const sx_port_log_id_t             log_port,
                                                  const sx_access_cmd_t              cmd,
                                                  const sx_cos_traffic_class_t      *traffic_classes_p,
                                                  const uint8_t                      traffic_classes_cnt,
                                                  const sx_cos_redecn_flow_type_e    flow_type,
                                                  const sx_cos_redecn_bind_params_t *params_p);


/**
 * This function retrieves the binding of RED/ECN profiles configuration for given egress port and traffic class.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle - SX-API handle
 * @param[in]  log_port - egress port to query
 * @param[in]  traffic_class - traffic class to retrieve
 * @param[in]  flow_type - flow type to bind/unbind
 * @param[out] params_p - profile to bind to this flow type
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 *
 */
sx_status_t sx_api_cos_redecn_profile_tc_bind_get(const sx_api_handle_t           handle,
                                                  const sx_port_log_id_t          log_port,
                                                  const sx_cos_traffic_class_t    traffic_class,
                                                  const sx_cos_redecn_flow_type_e flow_type,
                                                  sx_cos_redecn_bind_params_t    *params_p);


/**
 * \deprecated This API is deprecated and will be removed in the future.
 * This function sets the rate based configuration for RED/ECN
 * Supported devices: Currently this API is not supported.
 *
 * @param[in] handle        -  SX-API handle
 * @param[in] enabled        - enable/disable
 * @param[in] log_port  - egress port to configure
 * @param[in] params_p      - parameters - used only when enabling
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_rate_based_set(const sx_api_handle_t              handle,
                                             const boolean_t                    enabled,
                                             const sx_port_log_id_t             log_port,
                                             sx_cos_redecn_rate_based_params_t *params_p);

/**
 * \deprecated This API is deprecated and will be removed in the future.
 * This function gets the rate based configuration for RED/ECN
 * Supported devices: Currently this API is not supported.
 *
 * @param[in] handle        -  SX-API handle
 * @param[in] log_port  - egress port to configure
 * @param[out] params_p     - configured parameters
 * @param[out] enabled_p        - is rate based enabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_rate_based_get(const sx_api_handle_t              handle,
                                             const sx_port_log_id_t             log_port,
                                             sx_cos_redecn_rate_based_params_t *params_p,
                                             boolean_t                         *enabled_p);


/**
 * This function sets the mirroring binding for packets that are discarded (due to tail drop or RED) in the egress port.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    -  SX-API handle
 * @param[in] cmd   - SX_ACCESS_CMD_ADD or SX_ACCESS_CMD_DELETE
 * @param[in] ingress_port - port to mirror to
 * @param[in] span_session_id - session id to use
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_mirroring_set(const sx_api_handle_t      handle,
                                            const sx_access_cmd_t      cmd,
                                            const sx_port_log_id_t     ingress_port,
                                            const sx_span_session_id_t span_session_id);


/**
 * This function gets the mirroring binding for packets that are discarded (due to tail drop or RED) in the egress port.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]   handle                  - SX-API handle
 * @param[out]  ingress_port_p  -               port to test
 * @param[out]  enabled_p           - enabled/disabled for the port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_mirroring_get(const sx_api_handle_t  handle,
                                            const sx_port_log_id_t ingress_port,
                                            boolean_t             *enabled_p);

/**
 *  This function get the RED/ECN counter for a specific egress_port
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        -  SX-API handle
 * @param[in] cmd           - SX_ACCESS_CMD_READ or SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port  -       egress port to query
 * @param[out] counters_p       - counters structure
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_counters_get(const sx_api_handle_t          handle,
                                           const sx_access_cmd_t          cmd,
                                           const sx_port_log_id_t         log_port,
                                           sx_cos_redecn_port_counters_t *counters_p);


/**
 * This function reads the RED drop counter for one or more user provided
 * traffic Classes for a given specific egress_port
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - SX_ACCESS_CMD_READ or SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port          - logical egress port to query
 * @param[in] tc_list_p         - list of traffic classes on the specified port
 * @param[in] tc_list_cnt       - num of traffic classes
 * @param[out] red_counter_p    - array of counters indexed in same order as tc_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if input cmd is not supported
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_red_counter_per_port_tc_get(const sx_api_handle_t         handle,
                                                          const sx_access_cmd_t         cmd,
                                                          const sx_port_log_id_t        log_port,
                                                          const sx_cos_traffic_class_t *tc_list_p,
                                                          const uint8_t                 tc_list_cnt,
                                                          sx_port_cntr_t               *red_counter_p);
/**
 * This function reads the ECN counter for a user specified egress_port
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - SX_ACCESS_CMD_READ or SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port          - logical egress port to query
 * @param[out] ecn_counters_p   - return counter of number of ecn packets sent on this port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if input cmd is not supported
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_ecn_counter_per_port_get(const sx_api_handle_t  handle,
                                                       const sx_access_cmd_t  cmd,
                                                       const sx_port_log_id_t log_port,
                                                       sx_port_cntr_t        *ecn_counters_p);

/**
 * This function is used to configure whether ecn marking should be counted
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle SX-API handle
 * @param[in] enabled true for counting, false to not count
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_CMD_UNSUPPORTED if the function is being called in an unsupported chip
 */
sx_status_t sx_api_cos_redecn_counters_count_marked_set(const sx_api_handle_t handle,
                                                        const boolean_t       enabled);

/**
 * This function is used to retrieve if the SDK counts ECN marked packets or not.
 * Supported devices: Spectrum
 *
 * @param[in] handle SX-API handle
 * @param[in] enabled_p true for counting, false to not count
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_counters_count_marked_get(const sx_api_handle_t handle,
                                                        const boolean_t      *enabled_p);


/**
 * This function is used to get buffer consumption
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle SX-API handle
 * @param[in] buff_consumption_p a pointer to buffer consumption struct
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */

sx_status_t sx_api_cos_buff_consumption_get(const sx_api_handle_t      handle,
                                            sx_cos_buff_consumption_t *buff_consumption_p);
#endif /* __SX_API_COS_H__ */
