/*
 * Copyright (C) 2014-2022 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_COS_H__
#define __SX_API_COS_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_cos_redecn.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of COS module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - COS module verbosity level
 * @param[in] api_verbosity_level      - COS API verbosity level
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of COS module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - COS module verbosity level
 * @param[out] api_verbosity_level_p    - COS API verbosity level
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API sets the port default switch priority value. This default priority value is used in "trust port" configurations.
 * This default priority value is also used in cases when trust level is configured as L2 or L3 and the relevant packet
 * fields that determine the priority value are unavailable in the packet.
 *
 * Note: In Spectrum, the function sets the default switch priority.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] log_port     - Logical port ID
 * @param[in] priority     - Switch priority (0..cos_port_prio_max (see resource manager), default is 0)
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 * @return SX_STATUS_MEMORY_ERROR   Error handling memory
 */
sx_status_t sx_api_cos_port_default_prio_set(const sx_api_handle_t   handle,
                                             const sx_port_log_id_t  log_port,
                                             const sx_cos_priority_t priority);

/**
 * This API retrieves the default port switch priority value.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  log_port        - Logical port ID
 * @param[out] priority_p      - Switch priority (0..cos_port_prio_max (see resource manager), default is 0)
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_default_prio_get(const sx_api_handle_t  handle,
                                             const sx_port_log_id_t log_port,
                                             sx_cos_priority_t     *priority_p);

/**
 * This API adds or deletes a priority to/from a traffic class (TC). When a switch priority is added to a TC,
 * it is automatically re-mapped from its previous allocation. When a priority is deleted from a TC,
 * it is reallocated according to default settings.
 *
 * Each packet has an assigned priority. The priority of the packet is mapped to one of eight traffic classes (egress queues)
 * according to prio -> traffic class map. Each packet is dequeued on the egress port based on its traffic class.
 *
 * Note: Multiple priorities can be mapped to a single TC.
 * Note: Spectrum default settings:
 *         - i = [0,7]: switch priority i -> traffic class i
 *         - i = [8,14]: switch priority i -> traffic class 7
 *       Spectrum higher TC behavior:
 *         If a switch priority is mapped to a higher TC X [where 8 <= X <= 15],
 *         packets sent on TC X will still be counted against TC X-8.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - ADD/DELETE
 * @param[in] log_port      - Logical port ID (egress port)
 * @param[in] priority      - Priority
 * @param[in] traffic_class - Traffic class
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 * @return SX_STATUS_MEMORY_ERROR   Error handling memory
 * @return SX_STATUS_CMD_ERROR      Unsupported command
 */
sx_status_t sx_api_cos_port_tc_prio_map_set(const sx_api_handle_t        handle,
                                            const sx_access_cmd_t        cmd,
                                            const sx_port_log_id_t       log_port,
                                            const sx_cos_priority_t      priority,
                                            const sx_cos_traffic_class_t traffic_class);

/**
 * This API retrieves the traffic class of a specific switch priority.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  log_port        - Logical port ID
 * @param[in]  priority        - Priority
 * @param[out] traffic_class_p - Traffic class
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_tc_prio_map_get(const sx_api_handle_t   handle,
                                            const sx_port_log_id_t  log_port,
                                            const sx_cos_priority_t priority,
                                            sx_cos_traffic_class_t *traffic_class_p);

/**
 * This API sets the port trust level value.
 * User priority is assigned based on the following modes:
 *  -Trust port user priority - ignore packets priority and assign priority based on the port configuration.
 *  -Trust packet user priority/Trust L2 - tagged L2 packets are assigned with packets priority,
 *   untagged packets are assigned with port's priority.
 *  -Trust DSCP/Trust L3 - IP packets are assigned with a priority based on the DSCP to UP mapping.
 *   Non-IP packets are assigned with port's priority.
 *  -Trust both - IP packets are assigned with a priority based on the  DSCP to UP mapping.
 *   Otherwise, tagged L2 packets are assigned with packets priority, untagged packets are assigned with port's priority.
 *
 * Note: In Spectrum, for MPLS packets EXP field is used instead of DSCP.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - Logical port ID
 * @param[in] trust_level - Trust level [trust port user priority,trust L2, trust L3, trust both]
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 * @return SX_STATUS_MEMORY_ERROR   Error handling memory
 */
sx_status_t sx_api_cos_port_trust_set(const sx_api_handle_t      handle,
                                      const sx_port_log_id_t     log_port,
                                      const sx_cos_trust_level_t trust_level);

/**
 * This API retrieves the port trust level value.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle        - SX-API handle
 * @param[in]  log_port      - Logical port ID
 * @param[out] trust_level_p - Trust level [trust port user priority,trust L2, trust L3, trust both]
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_trust_get(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      sx_cos_trust_level_t  *trust_level_p);

/**
 * This API sets the port's priority to buffer map in the SDK.
 *
 * Note: Untagged frames must use a buffer used by one of the priorities.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - access command SX_ACCESS_CMD_SET
 * @param[in] log_port        - Logical port ID
 * @param[in] prio_to_buff_p  - Mapping of switch priorities to PG buffers
 *
 * @return SX_STATUS_SUCCESS         Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR     Input parameter is invalid
 * @return SX_STATUS_ERROR           General error
 * @return SX_STATUS_CMD_UNSUPPORTED Unsupported command
 */
sx_status_t sx_api_cos_port_prio_buff_map_set(const sx_api_handle_t    handle,
                                              const sx_access_cmd_t    cmd,
                                              const sx_port_log_id_t   log_port,
                                              sx_cos_port_prio_buff_t *prio_to_buff_p);

/**
 * This API retrieves the port's priority to buffer mapping from the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - Logical port ID
 * @param[out] prio_to_buff_p - Mapping of switch priorities to PG buffers
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_prio_buff_map_get(const sx_api_handle_t    handle,
                                              const sx_port_log_id_t   log_port,
                                              sx_cos_port_prio_buff_t *prio_to_buff_p);

/**
 * This API sets the pool parameters. It is used to set shared buffer pools and shared headroom pools.
 *
 * Note: Shared headroom pools must have ingress direction and valid size. Infinite size is not allowed and the only
 *  supported mode is SX_COS_BUFFER_MAX_MODE_BUFFER_UNITS_E. Other attributes are ignored.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - CREATE/DESTROY/EDIT
 * @param[in] sx_cos_pool_attr    - Pool attributes pointer (Direction, Size (in Cells), Mode (dynamic/static))
 * @param[in/out] pool_id         - Pool ID pointer (use CMD SX_ACCESS_CMD_CREATE command will return the user pool_id)
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Any input parameters is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_shared_buff_pool_set(const sx_api_handle_t handle,
                                            const sx_access_cmd_t cmd,
                                            sx_cos_pool_attr_t   *sx_cos_pool_attr,
                                            uint32_t             *pool_id);

/**
 * This API gets the shared buffer pool attributes.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] pool_id             - Pool ID
 * @param[out] sx_cos_pool_attr_p - Pool attributes (Direction, Size, Shared size, Mode (dynamic/static))
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Any input parameters is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_shared_buff_pool_get(const sx_api_handle_t handle,
                                            const uint32_t        pool_id,
                                            sx_cos_pool_attr_t  * sx_cos_pool_attr_p);

/**
 * This API sets the port buffers size and threshold (Xon/Xoff) according to port buffer attribute type.
 * SET (and attribute size non-zero) allocates the specific port buffer with the attribute size (configures specific buffer entry).
 * SET (and attribute size zero), the API releases the size of specific port buffer (deletes specific buffer entry).
 * DELETE releases specific port buffers that were received on port_buffer_attr_list_p (sets size zero for those ports).
 * DELETE_ALL releases all the port buffers configured on specific logical port (deletes all buffer entries on logical port).
 * With logical port param, a validation is done to allocate MC buffer only if the  user sets log_port param with a single
 * reserved value of MC_LOG_ID as defined in sx_port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - SET/DELETE/DELETE_ALL
 * @param[in] log_port                  - Logical port ID
 * @param[in] port_buffer_attr_list_p   - Pointer to list of port buffers attributes
 * @param[in] port_buffer_attr_cnt      - Number of port buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Any input parameters is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_buff_type_set(const sx_api_handle_t            handle,
                                          const sx_access_cmd_t            cmd,
                                          const sx_port_log_id_t           log_port,
                                          const sx_cos_port_buffer_attr_t *port_buffer_attr_list_p,
                                          const uint32_t                   port_buffer_attr_cnt);

/**
 * This API gets the port buffers size and thresholds (Xon/Xoff) according to port buffer attribute type.
 * Port buffer thresholds can only be retrieved for a single buffer type.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                       - SX-API handle
 * @param[in] log_port                     - Logical port ID
 * @param[in/out] port_buffer_attr_list_p  - Pointer to list of port buffers attributes
 * @param[in/out] port_buffer_attr_cnt     - Number of port buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Any input parameters is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_buff_type_get(const sx_api_handle_t      handle,
                                          const sx_port_log_id_t     log_port,
                                          sx_cos_port_buffer_attr_t *port_buffer_attr_list_p,
                                          uint32_t                  *port_buffer_attr_cnt);

/**
 * This API sets the port shared buffers attributes according to port shared buffer attribute type.
 *
 * SET (and attribute max size/alpha non-zero) allocates the specific port shared buffer with attribute depending on the mode
 *  (configures specific buffer entry).
 * SET (and attribute max size/alpha zero) releases the size of specific port shared buffer (deletes specific buffer entry).
 * DELETE releases specific port buffers that received on port_shared_buffer_attr_list_p (sets max alpha/size zero for those ports).
 * DELETE_ALL releases all the port shared buffers configured on specific logical port (sets max alpha/size zero on all buffer entries on logical port).
 * With logical port param, a validation is done to allocate MC buffer only if the user sets log_port param with single
 * reserved value MC_LOG_ID as defined in sx_port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                            - SX-API handle
 * @param[in] cmd                               - SET/DELETE/DELETE_ALL
 * @param[in] log_port                          - Logical port ID
 * @param[in] port_shared_buffer_attr_list_p    - Pointer to list of port shared buffer attributes
 * @param[in] port_shared_buffer_attr_cnt       - Number of port shared buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Any input parameters is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_shared_buff_type_set(const sx_api_handle_t                   handle,
                                                 const sx_access_cmd_t                   cmd,
                                                 const sx_port_log_id_t                  log_port,
                                                 const sx_cos_port_shared_buffer_attr_t *port_shared_buffer_attr_list_p,
                                                 const uint32_t                          port_shared_buffer_attr_cnt);

/**
 * This API gets the port shared buffers attributes according to port shared buffer attribute type.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                               - SX-API handle
 * @param[in] log_port                             - Logical port ID
 * @param[in/out] port_shared_buffer_attr_list_p   - Pointer to list of port shared buffer attributes
 * @param[in/out] port_shared_buffer_attr_cnt      - Number of port shared buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Any input parameters is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_shared_buff_type_get(const sx_api_handle_t             handle,
                                                 const sx_port_log_id_t            log_port,
                                                 sx_cos_port_shared_buffer_attr_t *port_shared_buffer_attr_list_p,
                                                 uint32_t                         *port_shared_buffer_attr_cnt);

/**
 * This API gets the buffer status.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[out] status   - Buffer global status
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Any input parameters is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_buff_status_get(const sx_api_handle_t handle,
                                       sx_buffer_status_t   *status);

/**
 * This API returns the list of initialized pools.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in/out] pool_cnt   - Number of pools in the list
 * @param[out] pool_list_p   - List of pool IDs
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Any input parameters is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_pools_list_get(const sx_api_handle_t handle,
                                      uint32_t             *pool_cnt,
                                      sx_cos_pool_id_t     *pool_list_p);

/**
 * This API gets the port buffers occupancy parameters. This API input is a list of ports and requested port buffers
 * attributes and it returns usage items, which carry also identifying attributes, for all the requested attributes.
 *
 * Note: the order of returned items in usage_list_p may not be identical to input in statistic_param_list_p.
 * Note: This API allows getting multiple statistical elements per port.
 *  When the number of statistical elements exceed the API capability, the API will return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - READ/READ_CLEAR
 * @param[in] statistic_param_list_p - Pointer to a list of statistics input structure (Port, PG, Direction)
 * @param[in] statistic_cnt          - Number of input parameters in the list
 * @param[out] usage_list_p          - Pointer to a list of usage params
 * @param[in/out] usage_cnt          - Number of output parameters in the list (if zero, number of elements will be returned)
 *
 * @return SX_STATUS_SUCCESS                    Operation completed successfully
 * @return SX_STATUS_PARAM_NULL                 Any input parameter is NULL
 * @return SX_STATUS_PARAM_ERROR                Any input parameters is invalid
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT Too many statistical elements requested
 * @return SX_STATUS_ERROR                      General error
 */
sx_status_t sx_api_cos_port_buff_type_statistic_get(const sx_api_handle_t                   handle,
                                                    const sx_access_cmd_t                   cmd,
                                                    const sx_port_statistic_usage_params_t *statistic_param_list_p,
                                                    const uint32_t                          statistics_cnt,
                                                    sx_port_occupancy_statistics_t         *usage_list_p,
                                                    uint32_t                               *usage_cnt);

/**
 * This API gets pool occupancy statistics.
 *
 * Note: Shared headroom pools do not support watermark statistics.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - READ/READ_CLEAR
 * @param[in] pool_id_list_p     - Pointer to a list of Pool IDs (size - in units of cells)
 * @param[in] pool_id_cnt        - Number of parameters in the list
 * @param[out] usage_list_p      - Pointer to a list of usage params
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Any input parameters is invalid
 * @return SX_STATUS_PARAM_NULL     Any input parameter is NULL
 * @return SX_STATUS_NO_RESOURCES   Memory allocations have failed
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_pool_statistic_get(const sx_api_handle_t               handle,
                                          const sx_access_cmd_t               cmd,
                                          const sx_cos_pool_id_t             *pool_id_list_p,
                                          const uint32_t                      pool_id_cnt,
                                          sx_cos_pool_occupancy_statistics_t *usage_list_p);

/**
 * This API sets the default color value of a given port. Used for trust level "port" or for packets without the
 * relevant priority field for the configured trust level(L2/L3).
 *
 * Note: This API is not supported for VPORT.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - Logical port ID
 * @param[in] color       - Color
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_default_color_set(const sx_api_handle_t  handle,
                                              const sx_port_log_id_t log_port,
                                              const sx_cos_color_t   color);

/**
 * This API retrieves the default port color value.
 *
 * Note: This API is not supported for VPORT.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] log_port   - Logical port ID
 * @param[out] color_p   - Color
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_default_color_get(const sx_api_handle_t  handle,
                                              const sx_port_log_id_t log_port,
                                              sx_cos_color_t        *color_p);

/**
 * This API sets the default PCP,DEI field value for arriving untagged packets.
 *
 * Note: This API is not supported for VPORT. See sx_api_cos_port_default_prio_set.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - Logical port ID
 * @param[in] pcp_dei     - PCP,DEI
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_default_pcpdei_set(const sx_api_handle_t  handle,
                                               const sx_port_log_id_t log_port,
                                               const sx_cos_pcp_dei_t pcp_dei);

/**
 * This API retrieves the default PCP,DEI field value for arriving untagged packets.
 *
 * Note: This API is not supported for VPORT.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - Logical port ID
 * @param[out] pcp_dei_p  - PCP,DEI
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_default_pcpdei_get(const sx_api_handle_t  handle,
                                               const sx_port_log_id_t log_port,
                                               sx_cos_pcp_dei_t      *pcp_dei_p);

/**
 * This API sets the mapping between PCP, DEI and switch priority, color.
 * This table is used when the port trust mode is set to 'trust L2'.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port              - Logical port ID
 * @param[in] pcp_dei_p             - List of PCPs and DEIs
 * @param[in] switch_priority       - List of switch priorities
 * @param[in] element_cnt           - Number of elements in PCP, DEI and Switch Prio lists
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_pcpdei_to_prio_set(const sx_api_handle_t          handle,
                                               const sx_port_log_id_t         log_port,
                                               const sx_cos_pcp_dei_t        *pcp_dei_p,
                                               const sx_cos_priority_color_t *switch_priority_color_p,
                                               const uint32_t                 element_cnt);

/**
 * This API retrieves the mapping from PCP,DEI to switch priority and color.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] log_port                 - Logical port ID
 * @param[out] pcp_dei_p               - List of PCPs and DEIs
 * @param[out] switch_priority_color_p - List of switch priorities and colors
 * @param[in/out] element_cnt_p        - Number of elements in PCP, DEI and Switch Prio lists
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_pcpdei_to_prio_get(const sx_api_handle_t    handle,
                                               const sx_port_log_id_t   log_port,
                                               sx_cos_pcp_dei_t        *pcp_dei_p,
                                               sx_cos_priority_color_t *switch_priority_color_p,
                                               uint32_t                *element_cnt_p);

/**
 * This API sets the mapping from switch priority to IEEE priority. This IEEE priority value is used in the switch
 * for pause flow control. The device maps the switch priority into IEEE priority value using device global switch priority
 * to IEEE priority table (not done per port).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] switch_priority_p - List of switch priorities
 * @param[in] ieee_priority_p   - a list of IEEE priorities
 * @param[in] element_cnt       - Number of elements in switch priorities and IEEE priorities lists
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_prio_to_ieeeprio_set(const sx_api_handle_t     handle,
                                            const sx_cos_priority_t  *switch_priority_p,
                                            const sx_cos_ieee_prio_t *ieee_priority_p,
                                            const uint32_t            element_cnt);

/**
 * This API retrieves the mapping from switch priority to IEEE priority.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[out] switch_priority_p  - switch priorities list
 * @param[out] ieee_priority_p   - IEEE priorities list
 * @param[in/out] element_cnt_p   - Number of elements in switch priorities and IEEE priorities lists
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_prio_to_ieeeprio_get(const sx_api_handle_t handle,
                                            sx_cos_priority_t    *switch_priority_p,
                                            sx_cos_ieee_prio_t   *ieee_priority_p,
                                            uint32_t             *element_cnt_p);

/**
 * This API sets the mapping from EXP to switch priority, color, and ECN value.
 * This table is used for MPLS packets when the port trust mode is set to L3.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] log_port                - Logical port ID
 * @param[in] exp_p                   - List of EXPs
 * @param[in] switch_priority_color_p - List of switch priorities and colors
 * @param[in] ecn_p                   - List of ECNs
 * @param[in] element_cnt             - Number of elements in EXPs, ECNs, and switch priorities lists
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_exp_to_prio_set(const sx_api_handle_t          handle,
                                            const sx_port_log_id_t         log_port,
                                            const sx_cos_exp_t            *exp_p,
                                            const sx_cos_priority_color_t *switch_priority_color_p,
                                            const sx_cos_ecn_t            *ecn_p,
                                            const uint32_t                 element_cnt);

/**
 * This API retrieves the mapping from EXP to switch priority, color, and ECN value.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] log_port                 - Logical port ID
 * @param[out] exp_p                   - List of EXPs
 * @param[out] switch_priority_color_p - Switch priorities and colors
 * @param[out] ecn_p                   - List of ECNs
 * @param[in/out] element_cnt_p        - Number of elements in EXP and switch priority lists
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_exp_to_prio_get(const sx_api_handle_t    handle,
                                            const sx_port_log_id_t   log_port,
                                            sx_cos_exp_t            *exp_p,
                                            sx_cos_priority_color_t *switch_priority_color_p,
                                            sx_cos_ecn_t            *ecn_p,
                                            uint32_t                *element_cnt_p);

/**
 * This API sets the mapping from DSCP to switch priority and color.
 * This table is used when the port trust mode is set to L3.
 *
 * Note: The mapping from DSCP to switch priority is done per port and is applicable only in Spectrum.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port              - Logical port ID
 * @param[in] dscp_p                - List of DSCPs
 * @param[in] switch_priority_color - List of switch priorities and colors
 * @param[in] element_cnt           - Number of elements in EXP and switch priority lists
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_dscp_to_prio_set(const sx_api_handle_t          handle,
                                             const sx_port_log_id_t         log_port,
                                             const sx_cos_dscp_t           *dscp_p,
                                             const sx_cos_priority_color_t *switch_priority_color_p,
                                             const uint32_t                 element_cnt);

/**
 * This API retrieves the mapping from DSCP to switch priority and color.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                     - SX-API handle
 * @param[in] log_port                   - Logical port ID
 * @param[out] dscp_p                    - List of DSCPs
 * @param[out] switch_priority_color_p   - List of switch priorities and colors
 * @param[in/out] element_cnt_p          - Number of elements in DSCPs and switch priorities lists
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_dscp_to_prio_get(const sx_api_handle_t    handle,
                                             const sx_port_log_id_t   log_port,
                                             sx_cos_dscp_t           *dscp_p,
                                             sx_cos_priority_color_t *switch_priority_color_p,
                                             uint32_t                *element_cnt_p);

/**
 * This API defines rewrite-enable option setting of PCP, DEI, DSCP, and EXP bits in packet header.
 * The values of rewriting are defined by mapping in the following functions. The rewrite is defined on an ingress port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Ingress logical port ID
 * @param[in] rewrite  - Rewrite PCP/DEI, DSCP, EXP
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_rewrite_enable_set(const sx_api_handle_t         handle,
                                               const sx_port_log_id_t        log_port,
                                               const sx_cos_rewrite_enable_t rewrite);

/**
 * This API retrieves rewrite-enable option setting of PCP, DEI, DSCP, and EXP bits in packet header.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] log_port   - Ingress logical port ID
 * @param[out] rewrite_p - Rewrite PCP/DEI, DSCP, EXP
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_rewrite_enable_get(const sx_api_handle_t    handle,
                                               const sx_port_log_id_t   log_port,
                                               sx_cos_rewrite_enable_t *rewrite_p);

/**
 * This API defines the mapping from switch priority, color to PCP, DEI for PCP, and DEI rewrite in packet headers.
 * The mapping will change the PCP, DEI values only if PCP, DEI rewrite was enabled in sx_api_cos_port_rewrite_enable_set.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] log_port                  - Egress logical port ID
 * @param[in] switch_priority_color_p   - List of switch priorities and colors
 * @param[in] pcp_dei_p                 - List of PCPs and DEIs
 * @param[in] element_cnt               - Switch priorities and PCP, DEI list's element count
 *
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_prio_to_pcpdei_rewrite_set(const sx_api_handle_t          handle,
                                                       const sx_port_log_id_t         log_port,
                                                       const sx_cos_priority_color_t *switch_priority_color_p,
                                                       const sx_cos_pcp_dei_t        *pcp_dei_p,
                                                       const uint32_t                 element_cnt);


/**
 * This API retrieves the mapping from switch priority, color to PCP, DEI for PCP, and DEI rewrite in packet header.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] log_port                 - Egress logical port ID
 * @param[out] switch_priority_color_p - List of switch priorities and colors
 * @param[out] pcp_dei_p               - List of PCPs and DEIs
 * @param[in/out] element_cnt_p        - Switch priorities and DSCP list's element count
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_prio_to_pcpdei_rewrite_get(const sx_api_handle_t    handle,
                                                       const sx_port_log_id_t   log_port,
                                                       sx_cos_priority_color_t *switch_priority_color_p,
                                                       sx_cos_pcp_dei_t        *pcp_dei_p,
                                                       uint32_t                *element_cnt_p);

/**
 * This API defines the mapping from switch priority, color to DSCP, for DSCP rewrite, in packet header.
 * The mapping will change the DSCP values only if DSCP rewrite was enabled in sx_api_cos_port_rewrite_enable_set.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] log_port                 - Egress Logical port ID
 * @param[in] switch_priority_color_p  - List of switch priorities and colors
 * @param[in] dscp_p                   - List of DSCPs
 * @param[in] element_cnt              - Switch priorities and DSCP list's element count
 *
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_prio_to_dscp_rewrite_set(const sx_api_handle_t          handle,
                                                     const sx_port_log_id_t         log_port,
                                                     const sx_cos_priority_color_t *switch_priority_color_p,
                                                     const sx_cos_dscp_t           *dscp_p,
                                                     const uint32_t                 element_cnt);

/**
 * This API retrieves the mapping from switch priority, color to DSCP, for DSCP rewrite, in packet header.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] log_port                 - Egress Logical port ID
 * @param[out] switch_priority_color_p - List of switch priorities and colors
 * @param[out] dscp_p                  - List of DSCPs
 * @param[in/out] element_cnt_p        - Switch priorities and DSCP list's element count
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_prio_to_dscp_rewrite_get(const sx_api_handle_t    handle,
                                                     const sx_port_log_id_t   log_port,
                                                     sx_cos_priority_color_t *switch_priority_color_p,
                                                     sx_cos_dscp_t           *dscp_p,
                                                     uint32_t                *element_cnt_p);

/**
 * This API defines the mapping from switch priority, color and ECN to EXP for EXP rewrite in packet header.
 * The mapping will change the EXP values only if EXP rewrite was enabled in sx_api_cos_port_rewrite_enable_set.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] log_port                - Egress Logical port ID
 * @param[in] switch_priority_color_p - List of switch priorities, colors
 * @param[in] ecn_p                   - List of ECNs
 * @param[in] exp_p                   - List of EXPs
 * @param[in] element_cnt             - Switch priorities, EXPs, and ECNs list's element count
 *
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_prio_to_exp_rewrite_set(const sx_api_handle_t          handle,
                                                    const sx_port_log_id_t         log_port,
                                                    const sx_cos_priority_color_t *switch_priority_color_p,
                                                    const sx_cos_ecn_t            *ecn_p,
                                                    const sx_cos_exp_t            *exp_p,
                                                    const uint32_t                 element_cnt);

/**
 * This API retrieves rewriting of EXP bit's setting.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                       - SX-API handle
 * @param[in] log_port                     - Egress logical port ID
 * @param[out] switch_priority_color_ecn_p - List of switch priorities and colors
 * @param[out] ecn_p                       - List of ECNs
 * @param[out] exp_p                       - List of EXPs
 * @param[in/out] element_cnt_p            - Switch priorities (ECNs and EXPs list's element count)
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_prio_to_exp_rewrite_get(const sx_api_handle_t    handle,
                                                    const sx_port_log_id_t   log_port,
                                                    sx_cos_priority_color_t *switch_priority_color_p,
                                                    sx_cos_ecn_t            *ecn_p,
                                                    sx_cos_exp_t            *exp_p,
                                                    uint32_t                *element_cnt_p);
/**
 * This API sets PTP shaper parameters.
 *
 * SET sets new shaper parameters.
 * DELETE resets shaper parameters to default.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle                        - SX-API handle
 * @param[in] cmd                           - SET/DELETE
 * @param[in] port_speed                    - Link speed of the port
 * @param[in] shaper_params                 - PTP shaper parameters
 *
 * @return SX_STATUS_SUCCESS        If operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    If input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 * @return SX_STATUS_UNSUPPORTED    Unsupported device
 */
sx_status_t sx_api_cos_ets_ptp_shaper_param_set(const sx_api_handle_t          handle,
                                                const sx_access_cmd_t          cmd,
                                                sx_cos_ets_ptp_port_speed_e    port_speed,
                                                sx_cos_ets_ptp_shaper_params_t shaper_params);

/**
 * This API retrieves PTP shaper parameters.
 *
 * GET retrieves current shaper parameters.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - GET
 * @param[in] port_speed            - Link speed of the port
 * @param[in] shaper_params         - PTP shaper parameters
 *
 * @return SX_STATUS_SUCCESS        If operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    If input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 * @return SX_STATUS_UNSUPPORTED    Unsupported device
 */
sx_status_t sx_api_cos_ets_ptp_shaper_param_get(const sx_api_handle_t           handle,
                                                const sx_access_cmd_t           cmd,
                                                sx_cos_ets_ptp_port_speed_e     port_speed,
                                                sx_cos_ets_ptp_shaper_params_t *shaper_params);

/**
 * This API binds a traffic class (TC) to a TC queue and group and sets shapers and rate-based ECN threshold.
 *
 * CREATE creates a queuing structure.
 * ADD adds an element to an existing queuing structure.
 * EDIT edits an element in an existing queuing structure.
 * DESTROY destroys the queuing structure (return to default).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - CREATE/ADD/EDIT/DESTROY
 * @param[in] log_port          - Egress port ID
 * @param[in] ets_element       - ETS element array
 * @param[in] ets_element_cnt   - Number of ETS elements
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_ets_element_set(const sx_api_handle_t              handle,
                                            const sx_access_cmd_t              cmd,
                                            const sx_port_log_id_t             log_port,
                                            const sx_cos_ets_element_config_t *ets_element_p,
                                            const uint32_t                     element_cnt);

/**
 * This API retrieves all elements of the queuing system.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle             - SX-API handle
 * @param[in]  log_port           - Egress port ID
 * @param[out]  ets_element       - ETS element array
 * @param[in/out] ets_element_cnt - Number of ETS elements
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_ets_element_get(const sx_api_handle_t        handle,
                                            const sx_port_log_id_t       log_port,
                                            sx_cos_ets_element_config_t *ets_element_p,
                                            uint32_t                    *element_cnt_p);

/**
 * This API sets the port MC awareness mode. If mc_aware==TRUE then the MC traffic will be mapped to the
 * higher TCs (8-15) and the UC traffic will be mapped to the lower TCs (0-7).
 * If there is a mapping configured to TC 8-15, the function will return SX_STATUS_ERROR.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - Egress port ID
 * @param[in] mc_aware       - MC awareness TC mode
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_tc_mcaware_set(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t log_port,
                                           const boolean_t        mc_aware);

/**
 * This API retrieves the port MC awareness mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - Egress port ID
 * @param[out] mc_aware   - MC awareness TC mode
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_port_tc_mcaware_get(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t log_port,
                                           boolean_t             *mc_aware_p);

/**
 * \deprecated This API is deprecated and will be removed in the future.
 * Use sx_api_cos_redecn_log_verbosity_level_set in its place.
 * This API sets the log verbosity level of REDECN module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - Module verbosity level
 * @param[in] api_verbosity_level      - API verbosity level
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_verbosity_level_set(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  const sx_verbosity_level_t      module_verbosity_level,
                                                  const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API sets the log verbosity level of REDECN module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - Module verbosity level
 * @param[in] api_verbosity_level      - API verbosity level
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                      const sx_log_verbosity_target_t verbosity_target,
                                                      const sx_verbosity_level_t      module_verbosity_level,
                                                      const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of REDECN module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - Module verbosity level
 * @param[out] api_verbosity_level_p    - API verbosity level
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                      const sx_log_verbosity_target_t verbosity_target,
                                                      sx_verbosity_level_t           *module_verbosity_level_p,
                                                      sx_verbosity_level_t           *api_verbosity_level_p);
/**
 * This API sets global configuration of ECN, RED and ECE.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] configuration_p   - Configuration parameters (see sx_cos_redecn_global_t)
 *
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 *
 */
sx_status_t sx_api_cos_redecn_general_param_set(const sx_api_handle_t         handle,
                                                const sx_cos_redecn_global_t *configuration_p);


/**
 * This API gets global configuration of ECN, RED and ECE.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle            - SX-API handle
 * @param[out] configuration_p  - Configuration parameters (see sx_cos_redecn_global_t)
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 *
 */
sx_status_t sx_api_cos_redecn_general_param_get(const sx_api_handle_t   handle,
                                                sx_cos_redecn_global_t *configuration_p);


/**
 * This API creates a single RED/ECN profile.
 *
 * ADD create a new profile (profile_p is the output).
 * EDIT edits a profile.
 * DELETE deletes a profile (params_p is ignored).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - ADD/EDIT/DELETE
 * @param[in] params_p         - Parameter of redecn profile attributes
 * @param[in/out] profile_p    - Configured or profile to reconfigure/delete
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 * @return SX_STATUS_NO_RESOURCES   No resources available
 *
 */
sx_status_t sx_api_cos_redecn_profile_set(const sx_api_handle_t                     handle,
                                          const sx_access_cmd_t                     cmd,
                                          const sx_cos_redecn_profile_attributes_t *params_p,
                                          sx_cos_redecn_profile_t                  *profile_p);


/**
 * This API gets RED/ECN profile configuration for given profile.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]   handle     - SX-API handle
 * @param[in]   profile    - redecn profile to get
 * @param[out]  params_p   - Structure of retrieved profile attributes
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 *
 */
sx_status_t sx_api_cos_redecn_profile_get(const sx_api_handle_t               handle,
                                          const sx_cos_redecn_profile_t       profile,
                                          sx_cos_redecn_profile_attributes_t *params_p);


/**
 * This API enables/disables RED, ECN and ECE for traffic classes.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] log_port                - Egress port to set
 * @param[in] traffic_classes_p       - List of traffic classes this configuration applies to
 * @param[in] traffic_classes_cnt     - Number of traffic classes
 * @param[in] params_p                - Enables parameters
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_tc_enable_set(const sx_api_handle_t                handle,
                                            const sx_port_log_id_t               log_port,
                                            const sx_cos_traffic_class_t        *traffic_classes_p,
                                            const uint8_t                        traffic_classes_cnt,
                                            const sx_cos_redecn_enable_params_t *params_p);


/**
 * This API gets RED, ECN and ECE enabled parameters of a traffic class.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Egress port to query
 * @param[in] traffic_class - Traffic class to get
 * @param[out] params_p     - Enables parameters
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_tc_enable_get(const sx_api_handle_t          handle,
                                            const sx_port_log_id_t         log_port,
                                            const sx_cos_traffic_class_t   traffic_class,
                                            sx_cos_redecn_enable_params_t *params_p);


/**
 * This API binds RED, ECN and ECE profiles to the traffic class and traffic type (TCP/non-TCP, color).
 *
 * BIND binds a port+TC+flow to a profile.
 * UNBIND unbinds a port+TC+flow from a profile.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] log_port            - Egress port to bind/unbind
 * @param[in] cmd                 - BIND/UNBIND
 * @param[in] traffic_classes_p   - Traffic classes affected by this command
 * @param[in] traffic_classes_cnt - Number of traffic classes in the above array
 * @param[in] flow_type           - Flow type to bind/unbind
 * @param[in] params_p            - Profile to bind to this flow type
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_profile_tc_bind_set(const sx_api_handle_t              handle,
                                                  const sx_port_log_id_t             log_port,
                                                  const sx_access_cmd_t              cmd,
                                                  const sx_cos_traffic_class_t      *traffic_classes_p,
                                                  const uint8_t                      traffic_classes_cnt,
                                                  const sx_cos_redecn_flow_type_e    flow_type,
                                                  const sx_cos_redecn_bind_params_t *params_p);


/**
 * This API retrieves the binding of RED/ECN/ECE profiles configuration for a given egress port and traffic class.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle        - SX-API handle
 * @param[in]  log_port      - Egress port to query
 * @param[in]  traffic_class - Traffic class to retrieve
 * @param[in]  flow_type     - Flow type to bind/unbind
 * @param[out] params_p      - Profile to bind to this flow type
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 *
 */
sx_status_t sx_api_cos_redecn_profile_tc_bind_get(const sx_api_handle_t           handle,
                                                  const sx_port_log_id_t          log_port,
                                                  const sx_cos_traffic_class_t    traffic_class,
                                                  const sx_cos_redecn_flow_type_e flow_type,
                                                  sx_cos_redecn_bind_params_t    *params_p);


/**
 * \deprecated This API is deprecated and will be removed in the future.
 * This API sets the rate based configuration for RED/ECN.
 *
 * Supported devices: Currently this API is not supported.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] enabled   - Enable/disable
 * @param[in] log_port  - Egress port to configure
 * @param[in] params_p  - Parameters (used only when enabling)
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_rate_based_set(const sx_api_handle_t              handle,
                                             const boolean_t                    enabled,
                                             const sx_port_log_id_t             log_port,
                                             sx_cos_redecn_rate_based_params_t *params_p);

/**
 * \deprecated This API is deprecated and will be removed in the future.
 * This API gets the rate based configuration for RED/ECN.
 *
 * Supported devices: Currently this API is not supported.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Egress port to configure
 * @param[out] params_p     - Configured parameters
 * @param[out] enabled_p    - Shows if rate based enabled
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_rate_based_get(const sx_api_handle_t              handle,
                                             const sx_port_log_id_t             log_port,
                                             sx_cos_redecn_rate_based_params_t *params_p,
                                             boolean_t                         *enabled_p);


/**
 * This API sets the mirroring binding for packets that are discarded (due to RED) in the ingress port.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - ADD/DELETE
 * @param[in] ingress_port     - Port to mirror to
 * @param[in] span_session_id  - Session ID to use
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_mirroring_set(const sx_api_handle_t      handle,
                                            const sx_access_cmd_t      cmd,
                                            const sx_port_log_id_t     ingress_port,
                                            const sx_span_session_id_t span_session_id);


/**
 * This API gets the mirroring binding for packets that are discarded (due to RED) in the ingress port.
 *
 * Supported devices: Spectrum.
 *
 * @param[in]   handle            - SX-API handle
 * @param[out]  ingress_port_p    - Port to test
 * @param[out]  enabled_p         - Enabled/disabled for the port
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_mirroring_get(const sx_api_handle_t  handle,
                                            const sx_port_log_id_t ingress_port,
                                            boolean_t             *enabled_p);

/**
 * This API gets the RED/ECN counter for a specific egress_port.
 *
 * Note: tc_ecn_marked_packet is supported in Spectrum3 and above.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - READ/READ_CLEAR
 * @param[in] log_port      - Egress port to query
 * @param[out] counters_p   - Counters structure
 *
 * @return SX_STATUS_SUCCESS        If operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    If input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_counters_get(const sx_api_handle_t          handle,
                                           const sx_access_cmd_t          cmd,
                                           const sx_port_log_id_t         log_port,
                                           sx_cos_redecn_port_counters_t *counters_p);


/**
 * This API reads the RED drop counter for one or more user-provided traffic classes for a specific given egress port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - READ/READ_CLEAR
 * @param[in] log_port          - Logical egress port to query
 * @param[in] tc_list_p         - List of traffic classes on the specified port
 * @param[in] tc_list_cnt       - Number of traffic classes
 * @param[out] red_counter_p    - Counters indexed in same order as tc_list_p
 *
 * @return SX_STATUS_SUCCESS         Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR     Input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED Unsupported command
 * @return SX_STATUS_ERROR           General error
 */
sx_status_t sx_api_cos_redecn_red_counter_per_port_tc_get(const sx_api_handle_t         handle,
                                                          const sx_access_cmd_t         cmd,
                                                          const sx_port_log_id_t        log_port,
                                                          const sx_cos_traffic_class_t *tc_list_p,
                                                          const uint8_t                 tc_list_cnt,
                                                          sx_port_cntr_t               *red_counter_p);
/**
 * This API reads the ECN counter for a user-specified egress port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - READ/READ_CLEAR
 * @param[in] log_port          - Logical egress port to query
 * @param[out] ecn_counters_p   - Return counter of number of ECN packets sent on this port
 *
 * @return SX_STATUS_SUCCESS         Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR     Input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED Unsupported command
 * @return SX_STATUS_ERROR           General error
 */
sx_status_t sx_api_cos_redecn_ecn_counter_per_port_get(const sx_api_handle_t  handle,
                                                       const sx_access_cmd_t  cmd,
                                                       const sx_port_log_id_t log_port,
                                                       sx_port_cntr_t        *ecn_counters_p);

/**
 * This API is used to configure whether ECN marking should be counted.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      -SX-API handle
 * @param[in] enabled     -True for counting/false to not count
 *
 * @return SX_STATUS_SUCCESS         Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR     Input parameter is invalid
 * @return SX_STATUS_ERROR           General error
 * @return SX_STATUS_CMD_UNSUPPORTED Function is being called in an unsupported chip
 */
sx_status_t sx_api_cos_redecn_counters_count_marked_set(const sx_api_handle_t handle,
                                                        const boolean_t       enabled);

/**
 * This API is used to retrieve if the SDK counts ECN marked packets or not.
 *
 * Supported devices: Spectrum
 *
 * @param[in] handle      - SX-API handle
 * @param[in] enabled_p   - True for counting/false to not count
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_redecn_counters_count_marked_get(const sx_api_handle_t handle,
                                                        const boolean_t      *enabled_p);


/**
 * This API is used to get buffer consumption.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] buff_consumption_p  - Pointer to buffer consumption
 *
 * @return SX_STATUS_SUCCESS        Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ERROR          General error
 */
sx_status_t sx_api_cos_buff_consumption_get(const sx_api_handle_t      handle,
                                            sx_cos_buff_consumption_t *buff_consumption_p);


/**
 * This function sets global configuration for the detection of elephant flows.
 * Note: configuration change will override and reset all previously detected flows.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] config_attribs_p - a pointer to configuration attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a null pointer was passed as input
 * @return SX_STATUS_RESOURCE_IN_USE if an asynchronous read transaction
 * (streaming) is in progress
 * @return SX_STATUS_ERROR in case of other general error
 */
sx_status_t sx_api_cos_elephant_detection_config_set(const sx_api_handle_t                   handle,
                                                     const sx_cos_elephant_config_attribs_t *config_attribs_p);


/**
 * This function gets the global configuration for the detection of elephant flows.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]  handle           - SX-API handle
 * @param[out] config_attribs_p - a pointer to configuration attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a null pointer was passed as input
 * @return SX_STATUS_MODULE_UNINITIALIZED if no configuration was previously set
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_elephant_detection_config_get(const sx_api_handle_t             handle,
                                                     sx_cos_elephant_config_attribs_t *config_attribs_p);


/**
 * This function set the switch elephant flow detection state on given physical ports.
 * Set command enables detection and unset command disables it.
 * Detection can't be enabled without providing initial configuration first, using sx_api_cos_elephant_config_set().
 * State is disabled by default for all ports
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - access command - SX_ACCESS_CMD_SET, SX_ACCESS_CMD_UNSET
 * @param[in] log_ports_list_p  -  a pointer to a list of logical port IDs (ingress ports)
 * @param[in] log_ports_cnt     -  count of logical port IDs  in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a null pointer was passed as input
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_elephant_detection_port_state_set(const sx_api_handle_t   handle,
                                                         const sx_access_cmd_t   cmd,
                                                         const sx_port_log_id_t *log_ports_list_p,
                                                         const uint32_t          log_ports_cnt);


/**
 * This function gets the switch elephant detection state on the given physical port.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID (ingress port)
 * @param[out] state_p - a pointer to the detection state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a null pointer was passed as input
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_elephant_detection_port_state_get(const sx_api_handle_t              handle,
                                                         const sx_port_log_id_t             log_port,
                                                         sx_cos_elephant_detection_state_e *state_p);


/**
 * This function gets a list of elephant detected flow IDs on the given physical port, or
 * clears them.
 * Clear command clears all detected flows.
 * Please note that the detection, and hence the list, are subject to change according
 * to traffic conditions.
 * For controlled management of the detected IDs (meaning that ID is valid until cleared manually),
 * use AUTOMATIC_CLEAR_DISABLE method when setting configuration
 * (see sx_cos_elephant_detection_config_set() description).
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]     handle            - SX-API handle
 * @param[in]     log_port          - logical port ID
 * @param[in]     cmd               - access commands: SX_ACCESS_CMD_READ, SX_ACCESS_CMD_CLEAR
 * @param[out]    flow_ids_list_p   - a pointer to a list of the detected flow IDs to be returned.
 *                                    Reserved when command is SX_ACCESS_CMD_CLEAR
 * @param[in/out] flow_ids_cnt_p    - [in] a pointer to the number of IDs to get.
 *                                    if 0 is passed then the function refers to all detected flows.
 *                                    Maximum number of flow IDs is SX_COS_ELEPHANT_FLOW_ID_NUM_MAX.
 *                                    [out] a pointer to the number of IDs managed to get.
 *                                    Reserved when command is SX_ACCESS_CMD_CLEAR
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a null pointer was passed as input
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_elephant_detection_port_flows_get(const sx_api_handle_t      handle,
                                                         const sx_access_cmd_t      cmd,
                                                         const sx_port_log_id_t     log_port,
                                                         sx_cos_elephant_flow_id_t *flow_ids_list_p,
                                                         uint32_t                  *flow_ids_cnt_p);


/**
 * This function reads flow data for the given flow IDs on the given physical port.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]  handle            - SX-API handle
 * @param[in]  cmd               - access commands: SX_ACCESS_CMD_READ , SX_ACCESS_READ_CLEAR
 * @param[in]  log_port          - logical port ID
 * @param[in]  flow_ids_list_p   - a pointer to a list of flow IDs
 * @param[out] flow_data_list_p  - a pointer to a list of the flow data requested for the given flow IDs
 * @param[in/out] list_cnt_p     - [in] a pointer to the count of flow IDs list
 *                                 [out] a pointer to the count of flow data entries returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a null pointer was passed as input
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_elephant_detection_port_flows_data_get(const sx_api_handle_t            handle,
                                                              const sx_access_cmd_t            cmd,
                                                              const sx_port_log_id_t           log_port,
                                                              const sx_cos_elephant_flow_id_t *flow_ids_list_p,
                                                              sx_cos_elephant_flow_data_t     *flow_data_list_p,
                                                              uint32_t                        *list_cnt_p);

/**
 * This function sets one kind of Tunnel QoS Profile data type at a time: TTL, QoS or ECN.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]  handle            - SX-API handle
 * @param[in]  cmd               - access commands: SX_ACCESS_CMD_SET
 * @param[in]  profile_key_p     - a pointer. specifies which profile to set
 * @param[in]  params_data_p     - a pointer to one of the three TQ profile data types and its selector
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a null pointer was passed as input
 * @return SX_STATUS_UNSUPPORTED if an unsupported profile key was passed an input
 */
sx_status_t sx_api_cos_tq_profile_set(const sx_api_handle_t           handle,
                                      const sx_access_cmd_t           cmd,
                                      const sx_cos_tq_profile_key_t  *profile_key_p,
                                      const sx_cos_tq_profile_data_t *params_data_p);

/**
 * This function populate the out argument with a full TQ profile description: TTL, QoS and ECN.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]  handle            - SX-API handle
 * @param[in]  profile_key_p     - a pointer. specifies which profile to set
 * @param[out] params_data_p     - a pointer to a concrete profile entry to be populated
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a null pointer was passed as input
 * @return SX_STATUS_UNSUPPORTED if an unsupported profile key was passed an input
 */
sx_status_t sx_api_cos_tq_profile_get(const sx_api_handle_t           handle,
                                      const sx_cos_tq_profile_key_t  *profile_key_p,
                                      sx_cos_tq_profile_entry_type_t *profile_entry_p);

/**
 * This API configures snapshot trigger on a snapshot object. This configuration can be applied on a per port TC, port PG, or a port basis
 * depending on the snapshot trigger type.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] cmd      - SET/DELETE
 * @param[in] object_p - Snapshot trigger enable object
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_cos_sb_snapshot_trigger_set(const sx_api_handle_t                         handle,
                                               const sx_access_cmd_t                         cmd,
                                               const sx_sb_snapshot_trigger_enable_object_t *object_p);


/**
 * This API returns a list of snapshot objects as per object type.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - supported commands:GET/GET_FIRST/GETNEXT
 * @param[in] object_key_p      - A reference snapshot trigger enable object key
 * @param[in] filter_p          - Return only enabled object that match this filter param if valid
 * @param[out] object_list_p    - return list of objects
 * @param[in,out] object_cnt_p  - [in] number of objects to get (when object_cnt_p=0 will get number of all valid objects per type)
 *                                [out] number of objects retrieved
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_CMD_UNSUPPORTED if invalid cmd is passed
 * @return SX_STATUS_DB_NOT_INITIALIZED if internal database is not initialized
 *
 *
 * The following use case scenarios apply with different input parameters. X = don't-care.
 * - 1) cmd = SX_ACCESS_CMD_GET, key = (type,port=X,tc_pg=X), filter = X, list = X, count = 0:
 *        In this case, the API will return the total number of snapshot enabled object count from internal database.
 *
 * - 2) cmd = SX_ACCESS_CMD_GET, key = valid/(type,port=X,tc_pg=X), filter = X, list = Valid, count = 1:
 *        In this case, the API will check if the specified key exists. If it does, the key will be returned in the list along
 *        with a count of 1. If the key does not exist, an empty list will be returned with count = 0.
 *
 * - 3) cmd = SX_ACCESS_CMD_GET, key = valid, filter = X, list = valid, count > 1:
 *        A count > 1 will be treated as a count of 1 and the behaviour will be the same as earlier GET use cases.
 *
 * - 4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = (type,port=X,tc_pg=X), filter = X, list = NULL, count = 0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT,a zero count will return an empty list.
 *
 * - 5) cmd = SX_ACCESS_CMD_GET_FIRST, key = (type,port=X,tc_pg=X), filter = X, list = valid, count > 0:
 *        In this case, the API will return the first snapshot enabled object starting from the head of the database. The total
 *        elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. The key must have type the rest is dont-care but
 *        a non-NULL return list pointer must be provided.
 *
 * - 6) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/(type,port=X,tc_pg=X), filter = X, list = valid, count > 0:
 *        In this case, the API will return the next set of snapshot enabled objects starting from the next valid snapshot enabled
 *        object after the specified key. The total elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. If no valid next counter exists in the database
 *        (key = end of list, or invalid key specified, or key too large), an empty list will be returned.
 */
sx_status_t sx_api_cos_sb_snapshot_trigger_iter_get(const sx_api_handle_t                        handle,
                                                    const sx_access_cmd_t                        cmd,
                                                    sx_sb_snapshot_trigger_enable_object_t      *object_key_p,
                                                    sx_sb_snapshot_trigger_enable_iter_filter_t *filter_p,
                                                    sx_sb_snapshot_trigger_enable_object_t      *object_list_p,
                                                    uint32_t                                    *object_cnt_p);


/**
 * This API enables to take SW snapshot action which change the snapshot state to taken and the buffer counters to stop updating.
 * In this state the following can be done:
 *  1. Configure HW triggers.
 *  2. Read snapshot information and statistics.
 * Snapshot action release will release the lock and the counters will resume updating again.
 *
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] action   - Snapshot action
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_CMD_UNPERMITTED if shared buffer bulk counter transaction is in progress
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_cos_sb_snapshot_action_set(const sx_api_handle_t         handle,
                                              const sx_sb_snapshot_action_e action);


/**
 * This API gets the snapshot status and information related to the latest snapshot.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[out] snapshot_info_p    - return snapshot information(status, latest trigger and timestamp)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_cos_sb_snapshot_info_get(const sx_api_handle_t         handle,
                                            sx_sb_snapshot_information_t *snapshot_info_p);

#endif /* __SX_API_COS_H__ */
