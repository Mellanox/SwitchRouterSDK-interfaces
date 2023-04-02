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

#ifndef __SX_API_STATEFUL_DB_H__
#define __SX_API_STATEFUL_DB_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/************************************************
*  API functions
************************************************/

/**
 * This API sets the log verbosity level of STATEFUL DB module.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - STATEFUL DB module verbosity level
 * @param[in] api_verbosity_level      - STATEFUL DB API verbosity level
 *
 * @return SX_STATUS_SUCCESS        if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR    if an input parameter is invalid
 * @return SX_STATUS_ERROR          for a general error
 * @return SX_STATUS_INVALID_HANDLE for invalid handle
 */
sx_status_t sx_api_stateful_db_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                       const sx_log_verbosity_target_t verbosity_target,
                                                       const sx_verbosity_level_t      module_verbosity_level,
                                                       const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of STATEFUL DB module.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Get verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - STATEFUL DB module verbosity level
 * @param[out] api_verbosity_level_p    - STATEFUL DB API verbosity level
 *
 * @return SX_STATUS_SUCCESS           if operation completes successfully
 * @return SX_STATUS_ERROR             for a general error
 * @return SX_STATUS_PARAM_ERROR       if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL        if an input parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE    for invalid handle
 */
sx_status_t sx_api_stateful_db_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                       const sx_log_verbosity_target_t verbosity_target,
                                                       sx_verbosity_level_t           *module_verbosity_level_p,
                                                       sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API initiates stateful DB module and its default parameters.
 *
 * Supported devices: Spectrum4
 *
 * @param[in] handle       - SX-API handle
 * @param[in] init_param_p - Stateful DB init params
 *
 * @return SX_STATUS_SUCCESS             if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR         if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL          if an input parameter is NULL
 * @return SX_STATUS_ERROR               for a general error
 * @return SX_STATUS_INVALID_HANDLE      for invalid handle
 * @return SX_STATUS_ALREADY_INITIALIZED if module already initialized
 */
sx_status_t sx_api_stateful_db_init_set(const sx_api_handle_t              handle,
                                        const sx_stateful_db_init_param_t *init_param_p);

/**
 * This API de-initiates stateful DB module.
 *
 * Note: All partition configurations must be cleared before deinit.
 *
 * Supported devices: Spectrum4
 *
 * @param[in] handle - SX-API handle
 *
 * @return SX_STATUS_SUCCESS              if operation completes successfully
 * @return SX_STATUS_ERROR                for a general error
 * @return SX_STATUS_INVALID_HANDLE       for invalid handle
 * @return SX_STATUS_DB_NOT_EMPTY         if DB was not cleared
 * @return SX_STATUS_MODULE_UNINITIALIZED if stateful DB module was not initialized
 *
 */
sx_status_t sx_api_stateful_db_deinit_set(const sx_api_handle_t handle);

/**
 * This API edits global attribute of stateful DB module.
 *
 * Note : Ordering configuration cannot be changed when stateful DB is active.
 *        Stateful DB is considered active when at least one ACL rule accesses stateful DB in its action.
 *        The GP register allocated for force ordering cannot be used for other purposes.
 *        Any attempt of another module to use this GP register will lead to a param error.
 *        Changing ordering register requires disabling ordering and then re-enabling it with a new GP register.
 *
 * Supported devices: Spectrum4
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd    - EDIT
 * @param[in] attr_p - Global attributes
 *
 * @return SX_STATUS_SUCCESS              if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR          if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL           if an input parameter is NULL
 * @return SX_STATUS_ERROR                for a general error
 * @return SX_STATUS_INVALID_HANDLE       for invalid handle
 * @return SX_STATUS_CMD_ERROR            for unsupported command
 * @return SX_STATUS_MODULE_UNINITIALIZED if stateful DB module was not initialized
 */
sx_status_t sx_api_stateful_db_attr_set(const sx_api_handle_t        handle,
                                        const sx_access_cmd_t        cmd,
                                        sx_stateful_db_attributes_t *attr_p);

/**
 * This API gets global attribute of stateful DB module.
 *
 * Supported devices: Spectrum4
 *
 * @param[in]  handle - SX-API handle
 * @param[in]  cmd    - GET
 * @param[out] attr_p - Global attributes
 *
 * @return SX_STATUS_SUCCESS              if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR          if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL           if an input parameter is NULL
 * @return SX_STATUS_ERROR                for a general error
 * @return SX_STATUS_INVALID_HANDLE       for invalid handle
 * @return SX_STATUS_CMD_ERROR            for unsupported command
 * @return SX_STATUS_MODULE_UNINITIALIZED if stateful DB module was not initialized
 */
sx_status_t sx_api_stateful_db_attr_get(const sx_api_handle_t        handle,
                                        const sx_access_cmd_t        cmd,
                                        sx_stateful_db_attributes_t *attr_p);

/**
 * This API forces ordering of packets on a list of network ports.
 * When enabled, stateful DB is accessed by the same order as the packets ingress to the port.
 *
 * Note: Ordering must be enabled globally before forcing order on port (set force_ordering_enable to TRUE
 *         by sx_api_stateful_db_init or by sx_api_stateful_db_attr_set).
 *       Ordering is disabled by default.
 *       To change ordering configuration, port admin state must be down.
 *       This API supports network ports only. The network port can be a LAG member.
 *
 * Supported devices: Spectrum4
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - SET
 * @param[in] ordering_cfg_list_p - List of ports and the configuration for packet processing order
 * @param[in] list_cnt            - Number of ports in the list
 *
 * @return SX_STATUS_SUCCESS              if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR          if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL           if an input parameter is NULL
 * @return SX_STATUS_ERROR                for a general error
 * @return SX_STATUS_INVALID_HANDLE       for invalid handle
 * @return SX_STATUS_CMD_ERROR            for unsupported command
 * @return SX_STATUS_MODULE_UNINITIALIZED if stateful DB module was not initialized
 */
sx_status_t sx_api_stateful_db_ordering_set(const sx_api_handle_t          handle,
                                            const sx_access_cmd_t          cmd,
                                            sx_stateful_db_ordering_cfg_t *ordering_cfg_list_p,
                                            const uint32_t                 list_cnt);

/**
 * This API returns the ordering configuration for a list of ports.
 *
 * Supported devices: Spectrum4
 *
 * @param[in]     handle               - SX-API handle
 * @param[in]     cmd                  - GET
 * @param[in,out] ordering_cfg_list_p  - List of ports and their ordering configuration
 *                                       IN: List of log ports, OUT: Ports' ordering configuration
 * @param[in]     list_cnt             - Number of ports in the list
 *
 * @return SX_STATUS_SUCCESS              if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR          if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL           if an input parameter is NULL
 * @return SX_STATUS_ERROR                for a general error
 * @return SX_STATUS_INVALID_HANDLE       for invalid handle
 * @return SX_STATUS_CMD_ERROR            for unsupported command
 * @return SX_STATUS_MODULE_UNINITIALIZED if stateful DB module was not initialized
 */
sx_status_t sx_api_stateful_db_ordering_get(const sx_api_handle_t          handle,
                                            const sx_access_cmd_t          cmd,
                                            sx_stateful_db_ordering_cfg_t *ordering_cfg_list_p,
                                            const uint32_t                 list_cnt);

/**
 * This API configures a handler to be executed in case of failure.
 *
 * Note: The default handler is no operations.
 *       No handler can be programmed for success status.
 *
 * Supported devices: Spectrum4
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - SET/UNSET
 * @param[in] failure_type      - Failure type
 * @param[in] failure_handler_p - Failure handler
 *
 * @return SX_STATUS_SUCCESS              if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR          if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL           if an input parameter is NULL
 * @return SX_STATUS_ERROR                for a general error
 * @return SX_STATUS_INVALID_HANDLE       for invalid handle
 * @return SX_STATUS_CMD_ERROR            for unsupported command
 * @return SX_STATUS_MODULE_UNINITIALIZED if stateful DB module was not initialized
 */
sx_status_t sx_api_stateful_db_failure_handler_set(const sx_api_handle_t                 handle,
                                                   const sx_access_cmd_t                 cmd,
                                                   const sx_stateful_db_status_e         failure_type,
                                                   sx_stateful_db_failure_handler_cfg_t *failure_handler_p);

/**
 * This API returns the configured handler per failure type.
 *
 * Note: When the number of actions in an action set is zero means that there is no actions set for the failure type.
 *
 * Supported devices: Spectrum4
 *
 * @param[in]  handle            - SX-API handle
 * @param[in]  cmd               - GET
 * @param[in]  failure_type      - Failure type
 * @param[out] failure_handler_p - Failure handler
 *
 * @return SX_STATUS_SUCCESS              if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR          if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL           if an input parameter is NULL
 * @return SX_STATUS_ERROR                for a general error
 * @return SX_STATUS_INVALID_HANDLE       for invalid handle
 * @return SX_STATUS_CMD_ERROR            for unsupported command
 * @return SX_STATUS_MODULE_UNINITIALIZED if stateful DB module was not initialized
 */
sx_status_t sx_api_stateful_db_failure_handler_get(const sx_api_handle_t                 handle,
                                                   const sx_access_cmd_t                 cmd,
                                                   const sx_stateful_db_status_e         failure_type,
                                                   sx_stateful_db_failure_handler_cfg_t *failure_handler_p);

/**
 * This API creates a stateful DB key ID that represents the access key description to stateful DB.
 * Use this key ID in ACL action SX_FLEX_ACL_STATEFUL_DB or in sx_api_stateful_db_entry_set or sx_api_stateful_db_entry_meta_get API.
 * The API returns the key ID and number of KVD lines in key_desc_p->key_size.
 * To set partition with N entries using sx_api_stateful_db_partition_set API, allocate partition size: N*key_size.
 *
 * Note: It is not possible to DESTROY stateful DB key ID, if the key is used by the ACL action.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]     handle     - SX-API handle
 * @param[in]     cmd        - CREATE/DESTROY
 * @param[in,out] key_desc_p - Stateful key description (ignored when using DESTROY)
 * @param[in,out] key_id_p   - Stateful key ID
 *
 * @return SX_STATUS_SUCCESS                             if operation completes successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_ERROR if input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                     if stateful DB key is not found in the database
 * @return SX_STATUS_CMD_UNSUPPORTED                     for unsupported command
 * @return SX_STATUS_INVALID_HANDLE                      for invalid handle
 */
sx_status_t sx_api_stateful_db_key_set(const sx_api_handle_t    handle,
                                       const sx_access_cmd_t    cmd,
                                       sx_stateful_db_key_t    *key_desc_p,
                                       sx_stateful_db_key_id_t *key_id_p);

/**
 * This API returns the description of stateful DB key.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]  handle      - SX-API handle
 * @param[in]  cmd         - GET
 * @param[in]  key_id      - Stateful key ID
 * @param[out] key_desc_p  - Stateful key description
 *
 * @return SX_STATUS_SUCCESS           if operation completed successfully
 * @return SX_STATUS_PARAM_NULL        if input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND   if stateful DB key is not found in database
 * @return SX_STATUS_CMD_UNSUPPORTED   if supplied command is unsupported
 * @return SX_STATUS_INVALID_HANDLE    for invalid handle error
 */
sx_status_t sx_api_stateful_db_key_get(const sx_api_handle_t         handle,
                                       const sx_access_cmd_t         cmd,
                                       const sx_stateful_db_key_id_t key_id,
                                       sx_stateful_db_key_t         *key_desc_p);

/**
 * This API configures partition maximum size and warning threshold of a partition in stateful DB.
 *
 * Partition size is allocated with KVD line units.
 * In order to allocate partition with N entries, use the maximum size of N*key_size.
 * Key_size is the value return by sx_api_stateful_db_key_set API.
 * Max partition occupancy might exceed configured maximum threshold by rm_resource_global.stateful_db_partition_max_exceed_kvd.
 * Crossing maximum or warning thresholds will trigger SX_TRAP_ID_STATEFUL_DB_PARTITION_THRESHOLD_CROSSED event.
 * It is possible to register to receive this event, which informs of the current occupancy and the threshold crossed.
 * Crossing the maximum threshold results SX_STATEFUL_DB_STATUS_OVERFLOW_E failure, which triggers the execution
 *  of configured action set by sx_api_stateful_db_failure_handler_set API.
 *
 * Note: Changing partition configuration can be done only by destroying it and then creating it with a new configuration.
 *       Partition size is accounted in the system KVD.
 *
 * Supported devices: Spectrum4
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - CREATE/DESTROY
 * @param[in] partition_id    - Partition ID
 * @param[in] partition_cfg_p - Partition configuration
 *
 * @return SX_STATUS_SUCCESS          if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR      if input parameter is invalid
 * @return SX_STATUS_ERROR            for a general error
 * @return SX_STATUS_PARAM_NULL       if input parameter is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED  for unsupported command
 * @return SX_STATUS_INVALID_HANDLE   for invalid handle error
 */
sx_status_t sx_api_stateful_db_partition_set(const sx_api_handle_t           handle,
                                             const sx_access_cmd_t           cmd,
                                             sx_stateful_db_partition_id_e   partition_id,
                                             sx_stateful_db_partition_cfg_t *partition_cfg_p);

/**
 * This API return the stateful DB partition configuration and current occupancy in hardware.
 *
 * Supported devices: Spectrum4
 *
 * @param[in]  handle             - SX-API handle
 * @param[in]  cmd                - GET
 * @param[in]  partition_id       - Partition ID
 * @param[out] partition_status_p - Configuration and occupancy
 *
 * @return SX_STATUS_SUCCESS           if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR       if input parameter is invalid
 * @return SX_STATUS_ERROR             for a general error
 * @return SX_STATUS_PARAM_NULL        if input parameter is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED   if applied command is unsupported
 * @return SX_STATUS_INVALID_HANDLE    for invalid handle error
 * @return SX_STATUS_RESOURCE_IN_USE   if trying to destroy partition while in use
 */
sx_status_t sx_api_stateful_db_partition_get(const sx_api_handle_t              handle,
                                             const sx_access_cmd_t              cmd,
                                             sx_stateful_db_partition_id_e      partition_id,
                                             sx_stateful_db_partition_status_t *partition_status_p);

/**
 * This API performs software access to stateful DB: read, write or remove entry.
 * The software entry key contains the key data, the operations and the partition ID to access.
 * The access returns the status of the operation.
 * If the operation failed, failure type will return.
 * If the operation was successful, the DB entry data will return.
 *
 * Note: New DB entry will be created when:
 *       1. db_op NOP sem_op LOCK --> Create new entry with value 0.
 *       2. db_op READ sem_op LOCK --> Create new entry with value 0, db_entry_value is 0.
 *       3. db_op WRITE --> Create new entry with value db_entry_value.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]     handle        - SX-API handle
 * @param[in]     cmd           - SET
 * @param[in]     access_key_p  - Stateful key data, access operations, and partition ID
 * @param[in,out] access_data_p - Returns status of DB operation, found indication, and entry data
 *
 * @return SX_STATUS_SUCCESS           if operation completes successfully
 * @return SX_STATUS_PARAM_NULL        if input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED   for unsupported command
 * @return SX_STATUS_INVALID_HANDLE    for invalid handle error
 */
sx_status_t sx_api_stateful_db_entry_set(const sx_api_handle_t            handle,
                                         const sx_access_cmd_t            cmd,
                                         sx_stateful_db_sw_access_key_t  *access_key_p,
                                         sx_stateful_db_sw_access_data_t *access_data_p);

/**
 * This API returns data and metadata of stateful DB entry.
 * This API does not change DB data or metadata, and does not impact entry activity.
 * The software entry key contains the key data and the partition ID to access.
 *
 * Note: db_op and sem_op are ignored.
 *       The access returns the status of the operation, found indication, value in hardware,
 *       and entry metadata: activity and semaphore information.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in]  handle         - SX-API handle
 * @param[in]  cmd            - GET
 * @param[in]  access_key_p   - Stateful key data and partition ID.
 * @param[out] access_data_p  - Return status of DB operation, found indication and entry data.
 * @param[out] access_meta_p  - Entry metadata, valid if entry was found in DB.
 *
 * @return SX_STATUS_SUCCESS          if operation completes successfully
 * @return SX_STATUS_PARAM_NULL       if input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND  if stateful DB key is not found in the database
 * @return SX_STATUS_CMD_UNSUPPORTED  for unsupported command
 * @return SX_STATUS_INVALID_HANDLE   for invalid handle
 */
sx_status_t sx_api_stateful_db_entry_meta_get(const sx_api_handle_t            handle,
                                              const sx_access_cmd_t            cmd,
                                              sx_stateful_db_sw_access_key_t  *access_key_p,
                                              sx_stateful_db_sw_access_data_t *access_data_p,
                                              sx_stateful_db_entry_meta_t     *access_meta_p);

#endif /* __SX_API_STATEFUL_DB_H__ */
