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

#ifndef __SX_API_MGMT_H__
#define __SX_API_MGMT_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>
#include <sx/sdk/sx_mgmt.h>

/**
 * This API sets the log verbosity level of SX MGMT MODULE.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - SX MGMT module verbosity level
 * @param[in] api_verbosity_level      - SX MGMT API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_mgmt_log_verbosity_level_set(const sx_api_handle_t           handle,
                                            const sx_log_verbosity_target_t verbosity_target,
                                            const sx_verbosity_level_t      module_verbosity_level,
                                            const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of SX MGMT MODULE.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - SX MGMT module verbosity level
 * @param[out] api_verbosity_level_p    - SX MGMT API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_mgmt_log_verbosity_level_get(const sx_api_handle_t           handle,
                                            const sx_log_verbosity_target_t verbosity_target,
                                            sx_verbosity_level_t           *module_verbosity_level_p,
                                            sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API retrieves the slot information based on the slot ID.
 * Note - Pre-allocated memory needs to be provided for the slot info list
 * so that the SDK can fill in the details. When memory for slot id list or slot info list
 * is not allocated, SDK will return the number of slots in system.
 *
 * @param[in]  handle            - SX-API handle.
 * @param[in]  slot_id_list_p    - list of slot Ids.
 * @param[out] slot_info_list_p  - slot information list.
 * @param[in,out]  slot_list_size_p    - size of slot info and slot ID list.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if the input parameter(any slot ID in list) is invalid.
 * @return SX_STATUS_PARAM_NULL if slot_list_size_p is NULL.
 * @return SX_STATUS_ERROR if the slot attribute retrieval fails.
 */
sx_status_t sx_mgmt_slot_info_get(const sx_api_handle_t handle,
                                  const sx_slot_id_t   *slot_id_list_p,
                                  sx_mgmt_slot_info_t  *slot_info_list_p,
                                  uint32_t             *slot_list_size_p);

/**
 * This API performs the provisioning operation for a given slot.
 * Note - Currently, this API supports applying and deleting the initialization config file for a slot.
 * Deleting(RESET) the initialization file can only be executed after all the port associated with slot are deleted.
 * If RESET is executed on a non initialized slot, then list of ports that underwent mapping changes will be empty.
 * APPLY operation is an asynchronous operation. Once the INI APPLY is finished, BCTOE trap id would be sent with
 * the current state(valid/non-valid) of INI and the INI operational status.
 *
 * @param[in]   handle              - SX-API handle
 * @param[in]   slot_id             - slot ID
 * @param[in]   operation           - INI operation to be performed.
 * @param[out]  ini_operation_result_p   - list of ports created or deleted along with its mapping as
 *                                    a result of provisioning operation.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if the slot parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL.
 * @return SX_STATUS_ERROR if the provisioning operation failed.
 */
sx_status_t sx_mgmt_slot_ini_operation_set(const sx_api_handle_t                handle,
                                           const sx_slot_id_t                   slot_id,
                                           const sx_mgmt_slot_ini_operation_e   operation,
                                           sx_mgmt_slot_ini_operation_result_t *ini_operation_result_p);


/**
 *  This API transfers the initialization config data for a given slot.
 *
 * @param[in] handle                     - SX-API handle
 * @param[in] slot_id                    - slot ID
 * @param[in] data_p                 - initialization config data
 * @param[out]  ini_transfer_result_p    - INI transfer result
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if the slot parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL.
 * @return SX_STATUS_ERROR if the init config file data transfer fails.
 *
 */
sx_status_t sx_mgmt_slot_ini_data_set(const sx_api_handle_t               handle,
                                      const sx_slot_id_t                  slot_id,
                                      const sx_mgmt_slot_ini_data_t      *data_p,
                                      sx_mgmt_slot_ini_transfer_result_t *ini_transfer_result_p);


/**
 * This API retrieves the slot state information based on the slot ID.
 * Note - Pre-allocated memory needs to be provided for slot state info list
 * for the SDK to fill in the details. When memory for slot id list or slot state info list
 * is not allocated, SDK will return the number of slots in system.
 *
 * @param[in]  handle              - SX-API handle
 * @param[in]  slot_id_list_p     - list of slot Ids.
 * @param[out] slot_state_list_p  - slot state information list.
 * @param[in,out]  slot_list_size_p   - in: size of slot state and slot ID list.
 *                                    - out: number of slots or size of slot state info list size.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if the input parameter(any slot ID in list) is invalid.
 * @return SX_STATUS_PARAM_NULL if slot_list_size_p is NULL.
 * @return SX_STATUS_ERROR if the slot state retrieval fails.
 */
sx_status_t sx_mgmt_slot_state_info_get(const sx_api_handle_t      handle,
                                        const sx_slot_id_t        *slot_id_list_p,
                                        sx_mgmt_slot_state_info_t *slot_state_info_list_p,
                                        uint32_t                  *slot_list_size_p);


/**
 * This API sets the slot control information based on slot ID.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] slot_id                   - slot ID
 * @param[in] slot_control_info_p      - slot control information.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if the slot parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL.
 * @return SX_STATUS_ERROR if the slot control information set fails.
 */
sx_status_t sx_mgmt_slot_control_set(const sx_api_handle_t              handle,
                                     const sx_slot_id_t                 slot_id,
                                     const sx_mgmt_slot_control_info_t *slot_control_info_p);


/**
 * This API retrieves the possible module split information based on slot ID & module ID.
 *
 * @param[in] handle                        - SX-API handle
 * @param[in] module_id_info_p              - module slot identifier
 * @param[in] split_params_p                - split parameters.
 * @param[out] split_info_p                 - split information.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if the slot, module parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL.
 * @return SX_STATUS_ERROR if split information retrieval fails.
 */
sx_status_t sx_mgmt_phy_module_split_get(const sx_api_handle_t                    handle,
                                         const sx_mgmt_module_id_info_t          *module_id_info_p,
                                         const sx_mgmt_phy_module_split_params_t *split_params_p,
                                         sx_mgmt_phy_module_split_info_t         *split_info_p);


/**
 * This API retrieves the module information based on the slot ID & module ID.
 * Note - Pre-allocated memory needs to be provided for module_info_list_p with module_list_size entities
 * for SDK to fill in the details.
 *
 * @param[in] handle                        - SX-API handle
 * @param[in] module_id_info_list_p         - list of module slot identifiers
 * @param[in] list_size                     - size of module id and module info list size
 * @param[out] module_info_list_p           - list of module information.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if any of the slot, module parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL.
 * @return SX_STATUS_ERROR if split information retrieval fails.
 */
sx_status_t sx_mgmt_phy_module_info_get(const sx_api_handle_t           handle,
                                        const sx_mgmt_module_id_info_t *module_id_info_list_p,
                                        const uint32_t                  list_size,
                                        sx_mgmt_phy_module_info_t      *module_info_list_p);

/**
 * This API retrieves the slot, module and label port information for a given logical port.
 * Note - Pre-allocated memory needs to be provided for port_info_list_p with list_size entities
 * for SDK to fill in the details.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port_list_p       - list of logical port ID
 * @param[in] list_size             - size of log port and info list.
 * @param[out] port_info_list_p     - list of port information.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any of the logical port in the list is invalid.
 * @return SX_STATUS_ERROR if logical port information retrieval fails.
 */
sx_status_t sx_mgmt_port_info_get(const sx_api_handle_t   handle,
                                  const sx_port_log_id_t *log_port_list_p,
                                  const uint8_t           list_size,
                                  sx_mgmt_port_info_t    *port_info_list_p);


/**
 * This API retrieves information regarding the system components.
 *
 * @param[in] handle                - SX-API handle
 * @param[out] system_info_p        - system information.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if input parameter is NULL.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_ERROR if the system information retrieval fails.
 */

sx_status_t sx_mgmt_system_info_get(const sx_api_handle_t       handle,
                                    sx_mgmt_slot_system_info_t *system_info_p);


/**
 * This API set the temperature events configuration
 * based on the slot ID and sensor ID.
 * Note: list of sensor IDs can be obtained by using sx_mgmt_slot_info_get API.
 *
 * @param[in]    handle                          - SX-API handle.
 * @param[in]    cmd                             - SET/UNSET.
 * @param[in]    slot_id                         - slot id.
 * @param[in]    sensor_id_list_p                - sensor id list.
 * @param[in]    sensor_list_size                - size of "sensor id" and "sensor temperature control info" list.
 * @param[in]    temp_sensor_ctrl_info_list_p    - sensor temperature control information list.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if the input parameter(any slot ID of sensor ID in the list) is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL.
 * @return SX_STATUS_ERROR if the slot attribute retrieval fails.
 */
sx_status_t sx_mgmt_temp_sensor_set(const sx_api_handle_t handle,
                                    const sx_access_cmd_t cmd,
                                    const sx_slot_id_t    slot_id,
                                    const sx_sensor_id_t *sensor_id_list_p,
                                    const uint32_t        sensor_list_size,
                                    const sx_mgmt_temp_sensor_ctrl_info_t
                                                         *temp_sensor_ctrl_info_list_p);


/**
 * This API retrieves the temperature measurements and events configuration
 * based on the slot ID and sensor ID.
 * READ_CLEAR command will read and clear max_temp.
 * Note: list of sensor IDs can be obtained by using sx_mgmt_slot_info_get API.
 *
 * @param[in]    handle                 - SX-API handle.
 * @param[in]    cmd                    - READ/READ_CLEAR.
 * @param[in]    slot_id                - slot Id.
 * @param[in]    sensor_id_list         - sensor id list.
 * @param[in]    sensor_list_size       - size of "sensor id" and "sensor temperature information" list.
 * @param[out]   temp_sensor_info_p     - sensor temperature information.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if the input parameter(any slot ID or sensor ID in the list) is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL.
 * @return SX_STATUS_ERROR if the slot attribute retrieval fails.
 */
sx_status_t sx_mgmt_temp_sensor_get(const sx_api_handle_t       handle,
                                    const sx_access_cmd_t       cmd,
                                    const sx_slot_id_t          slot_id,
                                    const sx_sensor_id_t       *sensor_id_list_p,
                                    const uint32_t              sensor_list_size,
                                    sx_mgmt_temp_sensor_info_t *temp_sensor_info_list_p);


/**
 *  This API returns Physical Medium Depended (PMD) types which are enabled by user and
 *  all the PMD types which are supported by module
 *  Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] module_id_info_p - module ID info
 * @param[out] capab_port_rate_p - supported by module rate values
 * @param[out] admin_types_p   - PMD types which are enabled by user
 * @param[out] capab_types_p   - all PMD types which are supported by module
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_mgmt_phy_module_capability_get(const sx_api_handle_t                 handle,
                                              const sx_mgmt_module_id_info_t       *module_id_info_p,
                                              sx_port_rate_bitmask_t               *capab_port_rate_p,
                                              sx_port_phy_module_type_capability_t *admin_types_p,
                                              sx_port_phy_module_type_capability_t *capab_types_p);


/**
 *  This API sets the Physical Medium Depended (PMD) type.
 *  By default all types are enabled, hence this API allows user to
 *  limit the set of supported module types.
 *  Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] module_id_info_p - module ID info
 * @param[in] types_p          - PMD types to be enabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_mgmt_phy_module_admin_type_set(const sx_api_handle_t                       handle,
                                              const sx_mgmt_module_id_info_t             *module_id_info_p,
                                              const sx_port_phy_module_type_capability_t *types_p);

/**
 *  This API gets the operational Physical Medium Dependent (PMD) type.
 *  Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] module_id_info_p   - module ID info
 * @param[out] oper_type_p       - operational type
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_mgmt_phy_module_oper_type_get(const sx_api_handle_t           handle,
                                             const sx_mgmt_module_id_info_t *module_id_info_p,
                                             sx_port_phy_module_type_e      *oper_type_p);


/**
 *  This API sets the power mode attributes of a module
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *  Supported commands: SX_ACCESS_CMD_SET
 *
 *  Note - By default, modules are initialized in low power mode and the module
 *  power mode is set as per EEPROM data in the initialization process.
 *  SX_MGT_PHY_MOD_PWR_MODE_AUTO_E mode is used to reset power mode to default value.
 *  Changing module power mode to SX_MGT_PHY_MOD_PWR_MODE_HIGH_E is not allowed.
 *  This API internally disables and then enables the module with desired power
 *  mode setting. This disable and enable will result in additional PMAOS events.
 *  This API supports only power attribute SX_MGMT_PHY_MOD_PWR_ATTR_PWR_MODE_E.
 *  All ports associated with the module should be admin disabled before changing power
 *  attributes.
 *  This API does not support changing the power attributes of backplane module.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] cmd        - command.
 * param[in] module_id_info_p - module ID Information
 * @param[in] pwr_attr_p   - power attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if a module parameter is invalid or module type is backplane.
 * @return SX_STATUS_ERROR if the power attribute setting fails.
 * @return SX_STATUS_PARAM_NULL if a module info parameter is NULL.
 * @return SX_STATUS_CMD_UNSUPPORTED if cmd is not SET.
 */
sx_status_t sx_mgmt_phy_module_pwr_attr_set(const sx_api_handle_t             handle,
                                            const sx_access_cmd_t             cmd,
                                            const sx_mgmt_module_id_info_t   *module_id_info_p,
                                            const sx_mgmt_phy_mod_pwr_attr_t *pwr_attr_p);


/**
 *  This API gets the module power attributes.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 *  Note - When module is not plugged in, this API returns the operational power mode and admin power mode
 *  as SX_MGMT_PHY_MOD_PWR_MODE_INVALID_E.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] module_id_info_p  - module info
 * @param[in/out] pwr_attr_p - power_attr_type (in) and pwr_mode_attr as (out).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL.
 * @return SX_STATUS_ERROR if the power attribute retrieval fails.
 * @return SX_STATUS_PARAM_ERROR if a module parameter is invalid.
 */
sx_status_t sx_mgmt_phy_module_pwr_attr_get(const sx_api_handle_t           handle,
                                            const sx_mgmt_module_id_info_t *module_id_info_p,
                                            sx_mgmt_phy_mod_pwr_attr_t     *pwr_attr_p);

/**
 *  This API resets the phy module.
 *  Resetting the module might result in link flaps.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 *  Note - PMAOS events would be generated during reset functionality.
 *  Module reset can only be executed on plugged and enabled modules. Modules
 *  are enabled by default or internally enabled by SDK when associated port admin
 *  is enabled.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] module_id_info_p - module ID Information
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_ERROR if reset cannot be executed.
 * @return SX_STATUS_PARAM_ERROR if a module info parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if a module info parameter is NULL.
 */
sx_status_t sx_mgmt_phy_module_reset(const sx_api_handle_t           handle,
                                     const sx_mgmt_module_id_info_t *module_id_info_p);
#endif /* __SX_API_MGMT_H__ */
