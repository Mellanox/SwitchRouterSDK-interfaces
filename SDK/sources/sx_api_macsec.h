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
#ifndef __SX_API_MACSEC_H__
#define __SX_API_MACSEC_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>
#include <sx/sdk/sx_macsec.h>

/**
 * This API sets the log verbosity level of SX MACSEC MODULE.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
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
sx_status_t sx_api_macsec_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  const sx_verbosity_level_t      module_verbosity_level,
                                                  const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of SX MACSEC MODULE.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
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
sx_status_t sx_api_macsec_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  sx_verbosity_level_t           *module_verbosity_level_p,
                                                  sx_verbosity_level_t           *api_verbosity_level_p);


/**
 * This API Initiates the MACSec module in SDK.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] macsec_init_params_p - MACsec init parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ALREADY_INITIALIZED if MACsec is already initialized.
 * @return SX_STATUS_ERROR in case of general error
 */

sx_status_t sx_api_macsec_init(const sx_api_handle_t handle, sx_macsec_init_params_t *macsec_init_params_p);


/**
 * This API deinitializes the MACSec module in SDK.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MODULE_UNINITIALIZED if MACSec is not initialized
 * @return SX_STATUS_RESOURCE_IN_USE if MACSec flow objects or associated SC/SA objects exist.
 * @return SX_STATUS_ERROR in case of general error
 */

sx_status_t sx_api_macsec_deinit(const sx_api_handle_t handle);

/**
 * This API retrieves MACSec module init params.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] macsec_init_params_p - MACsec init parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MODULE_UNINITIALIZED if MACSec module is not initialized.
 * @return SX_STATUS_ERROR in case of general error
 */

sx_status_t sx_api_macsec_init_params_get(const sx_api_handle_t handle, sx_macsec_init_params_t *macsec_init_params_p);

/**
 * This API enables MACsec on a logical port.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[in] cmd - SET/EDIT - SET sets the attributes and initializes MACSec/EDIT edits the MACsec attributes.
 * @param[in] macsec_port_init_attr_p - port MACsec attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 * @return SX_STATUS_COMM_ERROR if client communication fails.
 * @return SX_STATUS_CMD_UNSUPPORTED if a command is not supported.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_ERROR if MACSec global init is not done.
 * @return SX_STATUS_ERROR in case of general error.
 */

sx_status_t sx_api_macsec_port_init(const sx_api_handle_t            handle,
                                    const sx_port_log_id_t           log_port,
                                    const sx_access_cmd_t            cmd,
                                    sx_macsec_port_init_attribute_t *macsec_port_init_attr_p);

/**
 * This API disables MACsec on a logical port.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_COMM_ERROR if client communication fails.
 * @return SX_STATUS_CMD_UNSUPPORTED if a command is not supported.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_ERROR in case of general error
 * @return SX_STATUS_RESOURCE_IN_USE if there are flows associated to the port.
 */

sx_status_t sx_api_macsec_port_deinit(const sx_api_handle_t handle, const sx_port_log_id_t log_port);

/**
 * This API retrieves MACsec capability of a logical port.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[out] capability_p - MACSec port capability.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_COMM_ERROR if client communication fails.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_ERROR in case of general error
 */

sx_status_t sx_api_macsec_port_capability_get(const sx_api_handle_t        handle,
                                              const sx_port_log_id_t       log_port,
                                              sx_macsec_port_capability_t *capability_p);

/**
 * This API creates or deletes a MACsec flow object.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE/DELETE
 * @param[in] macsec_flow_attr_p - MACSec flow attributes.
 * @param[out] macsec_flow_obj_id_p- MACSec flow object identifier
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if attribute or obj is NULL.
 * @return SX_STATUS_COMM_ERROR if client communication fails.
 * @return SX_STATUS_CMD_UNSUPPORTED if a command is not supported.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_RESOURCE_IN_USE in case a DELETE cmd is invoked and flow obj associated SC objects exists or flow obj is in use by ACL.
 * @return SX_STATUS_ERROR in case of general error
 */

sx_status_t sx_api_macsec_flow_obj_set(const sx_api_handle_t       handle,
                                       const sx_access_cmd_t       cmd,
                                       sx_macsec_flow_attribute_t *macsec_flow_attr_p,
                                       sx_macsec_flow_obj_id_t    *macsec_flow_obj_id_p);


/**
 * This API retrieves the attributes of a MACsec flow object.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - GET
 * @param[in] macsec_flow_obj_id - MACSec flow object identifier.
 * @param[out] macsec_flow_attr_p - MACSec flow attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if attribute or obj is NULL
 * @return SX_STATUS_COMM_ERROR if client communication fails.
 * @return SX_STATUS_CMD_UNSUPPORTED if a command is not supported.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_ERROR in case of general error
 */

sx_status_t sx_api_macsec_flow_obj_get(const sx_api_handle_t       handle,
                                       const sx_access_cmd_t       cmd,
                                       sx_macsec_flow_obj_id_t     macsec_flow_obj_id,
                                       sx_macsec_flow_attribute_t *macsec_flow_attr_p);


/**
 * This API returns a list of one or more MACsec flow objects.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param [in] handle - SX API handle
 * @param [in] cmd - GET/GET_FIRST/GET_NEXT
 * @param [in] macsec_flow_obj_id - MACSec flow obj Id
 * @param [in] filter_p - filter parameter
 * @param [out] macsec_flow_attr_list_p - List of MACsec flow object attributes
 * @param [in,out] macsec_flow_cnt_p - [in] number of MACsec flow objects to get, max 400/[out] number of MACsec flow objects returned.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range
 * @return SX_STATUS_PARAM_NULL if an unexpected NULL parameter was passed
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_CMD_UNSUPPORTED if invalid command is passed
 * @return SX_STATUS_MODULE_UNINITIALIZED if MACSec module is uninitialized
 * @return SX_STATUS_CMD_ERROR if internal RPC mechanism to SDK server fails
 * @return SX_STATUS_DB_NOT_INITIALIZED if internal MACSec database is not initialized
 */

sx_status_t sx_api_macsec_flow_obj_iter_get(const sx_api_handle_t          handle,
                                            const sx_access_cmd_t          cmd,
                                            const sx_macsec_flow_obj_id_t  macsec_flow_obj_id,
                                            const sx_macsec_flow_filter_t *filter_p,
                                            sx_macsec_flow_attribute_t    *macsec_flow_attr_list_p,
                                            uint32_t                      *macsec_flow_cnt_p);

/**
 * This API creates or deletes a MACsec SC object.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE/DELETE
 * @param[in] macsec_sc_attr_p - MACSec SC attributes.
 * @param[out] macsec_sc_obj_id_p- MACSec SC object identifier.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if attribute or obj is NULL
 * @return SX_STATUS_COMM_ERROR if client communication fails.
 * @return SX_STATUS_CMD_UNSUPPORTED if a command is not supported.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_RESOURCE_IN_USE in case of DELETE cmd, if associated SA objects exist.
 * @return SX_STATUS_ERROR in case of general error.
 */

sx_status_t sx_api_macsec_sc_obj_set(const sx_api_handle_t     handle,
                                     const sx_access_cmd_t     cmd,
                                     sx_macsec_sc_attribute_t *macsec_sc_attr_p,
                                     sx_macsec_sc_obj_id_t    *macsec_sc_obj_id_p);


/**
 * This API retrieves the attributes of a MACsec SC object.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - GET
 * @param[in] macsec_sc_obj_id - MACSec SC object identifier
 * @param[out] macsec_sc_attr_p - MACSec SC attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if attribute or obj is NULL
 * @return SX_STATUS_COMM_ERROR if client communication fails.
 * @return SX_STATUS_CMD_UNSUPPORTED if a command is not supported.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_ERROR in case of general error
 */

sx_status_t sx_api_macsec_sc_obj_get(const sx_api_handle_t     handle,
                                     const sx_access_cmd_t     cmd,
                                     sx_macsec_sc_obj_id_t     macsec_sc_obj_id,
                                     sx_macsec_sc_attribute_t *macsec_sc_attr_p);


/**
 * This API returns a list of one or more MACSec secure channel objects and its attributes.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param [in] handle - SX API handle
 * @param [in] cmd - GET/GET_FIRST/GET_NEXT
 * @param [in] macsec_sc_obj_id - MACSec SC obj id
 * @param [in] filter_p - filter parameter
 * @param [out] macsec_sc_attr_list_p - List of MACSec SC object attributes.
 * @param [in,out] macsec_sc_cnt_p - [in] number of MACSec SC objects to get. max 400/[out] number of MACSec SC objects returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range
 * @return SX_STATUS_PARAM_NULL if an unexpected NULL parameter was passed
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_CMD_UNSUPPORTED if invalid command is passed
 * @return SX_STATUS_MODULE_UNINITIALIZED if MACSec module is uninitialized
 * @return SX_STATUS_CMD_ERROR if internal RPC mechanism to SDK server fails
 * @return SX_STATUS_DB_NOT_INITIALIZED if internal MACSec database is not initialized
 */

sx_status_t sx_api_macsec_sc_obj_iter_get(const sx_api_handle_t        handle,
                                          const sx_access_cmd_t        cmd,
                                          const sx_macsec_sc_obj_id_t  macsec_sc_obj_id,
                                          const sx_macsec_sc_filter_t *filter_p,
                                          sx_macsec_sc_attribute_t    *macsec_sc_attr_list_p,
                                          uint32_t                    *macsec_sc_cnt_p);

/**
 * This API creates or deletes a MACsec SA object.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE/DELETE
 * @param[in] macsec_sa_attr_p - MACSec SA attributes.
 * @param[out] macsec_sa_obj_id_p- MACSec SA object identifier.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if attribute or obj is NULL
 * @return SX_STATUS_COMM_ERROR if client communication fails.
 * @return SX_STATUS_CMD_UNSUPPORTED if a command is not supported.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_ERROR in case of general error
 */

sx_status_t sx_api_macsec_sa_obj_set(const sx_api_handle_t     handle,
                                     const sx_access_cmd_t     cmd,
                                     sx_macsec_sa_attribute_t *macsec_sa_attr_p,
                                     sx_macsec_sa_obj_id_t    *macsec_sa_obj_id_p);

/**
 * This API retrieves the attributes of a MACsec SA object.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - GET
 * @param[in] macsec_sa_obj_id - MACSec SA object identifier.
 * @param[out] macsec_sa_attr_p - MACSec SA attribute.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if attribute or obj is NULL
 * @return SX_STATUS_COMM_ERROR if client communication fails.
 * @return SX_STATUS_CMD_UNSUPPORTED if a command is not supported.
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_ERROR in case of general error
 */

sx_status_t sx_api_macsec_sa_obj_get(const sx_api_handle_t     handle,
                                     const sx_access_cmd_t     cmd,
                                     sx_macsec_sa_obj_id_t     macsec_sa_obj_id,
                                     sx_macsec_sa_attribute_t *macsec_sa_attr_p);

/**
 * This API returns a list of one or more macsec flow identifiers.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Note - Spectrum2 and Spectrum3 requires additional MACSec capable gearbox to support MACsec functionality.
 *
 * @param [in] handle - SX API handle
 * @param [in] cmd - GET/GET_FIRST/GET_NEXT
 * @param [in] macsec_sa_obj_id - MACSec SA obj Id.
 * @param [in] filter_p - filter parameter
 * @param [out] macsec_sa_attr_list_p - List of MACSec SA objects
 * @param [in,out] macsec_sa_cnt_p - [in] number of MACSec SA objects to get. max 400/[out] number of MACSec SA objects returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range
 * @return SX_STATUS_PARAM_NULL if an unexpected NULL parameter was passed
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_CMD_UNSUPPORTED if invalid command is passed
 * @return SX_STATUS_MODULE_UNINITIALIZED if MACSec module is uninitialized
 * @return SX_STATUS_CMD_ERROR if internal RPC mechanism to SDK server fails
 * @return SX_STATUS_DB_NOT_INITIALIZED if internal MACSec database is not initialized
 */

sx_status_t sx_api_macsec_sa_obj_iter_get(const sx_api_handle_t        handle,
                                          const sx_access_cmd_t        cmd,
                                          const sx_macsec_sa_obj_id_t  macsec_sa_obj_id,
                                          const sx_macsec_sa_filter_t *filter_p,
                                          sx_macsec_sa_attribute_t    *macsec_sa_attr_list_p,
                                          uint32_t                    *macsec_sa_cnt_p);

/**
 * This API retrieves the MACSec counter values.
 * Multiple counters of different types can be read simultaneously by providing a list of counter types
 * and the respective keys in the macsec_cntr_key_list_p array
 * Note: cntr_list_len cannot be 0
 *
 * Supported devices: Spectrum4, systems with MACSec capable gearbox
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - READ / READ_CLEAR
 * @param[in] macsec_cntr_key_list_p - list of macsec counter keys
 * @param[in] cntr_list_len - key & value array size [Valid range is [1-128]
 * @param[out] macsec_cntr_val_list_p - list of macsec counter values
 *
 *
 * @return SX_STATUS_SUCCESS:                                           Operation completed successfully
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT:	Too many counters requested
 * @return SX_STATUS_PARAM_NULL:                                        If any input parameter is NULL
 * @return SX_STATUS_PARAM_ERROR:                                       If any input parameter is invalid
 * @return SX_STATUS_ERROR:                         General error
 */
sx_status_t sx_api_macsec_counters_get(const sx_api_handle_t          handle,
                                       const sx_access_cmd_t          cmd,
                                       const sx_macsec_counter_key_t *macsec_cntr_key_list_p,
                                       uint32_t                       cntr_list_len,
                                       sx_macsec_counter_t           *macsec_cntr_val_list_p);


/**
 * This API configures MACSEC events operation.
 * Events configured with Trap operation will be reported as part of SX_TRAP_ID_UTFD event.
 * Supported devices: Spectrum4, systems with MACSEC capable gearbox
 *
 * @param[in] handle - SX-API handle
 * @param[in] macsec_event_list_len - MACsec event list length
 * @param[in] macsec_event_key_list_p - MACsec event keys list
 * @param[in] macsec_event_attr_list_p - MACsec event attributes list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR in case of general error
 */
sx_status_t sx_api_macsec_events_set(const sx_api_handle_t         handle,
                                     const uint32_t                macsec_event_list_len,
                                     const sx_macsec_event_key_t  *macsec_event_key_list_p,
                                     const sx_macsec_event_attr_t *macsec_event_attr_list_p);

/**
 * This API retrieves the MACSEC events configuration.
 * Supported devices: Spectrum4, systems with MACSEC capable gearbox
 *
 * @param[in] handle - SX-API handle
 * @param[in] macsec_event_list_len - MACsec event list length
 * @param[in] macsec_event_key_list_p - MACsec event keys list
 * @param[out] macsec_event_attr_list_p - MACsec event attributes list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR in case of general error
 */
sx_status_t sx_api_macsec_events_get(const sx_api_handle_t        handle,
                                     const uint32_t               macsec_event_list_len,
                                     const sx_macsec_event_key_t *macsec_event_key_list_p,
                                     sx_macsec_event_attr_t      *macsec_event_attr_list_p);


/**
 * This API is used to create/destroy MACSEC ACL counter that can be used with MACSEC ACL rules and SA.
 * MACSEC ACL counters is per PORT + DIRECTION , so this params should be provided during creation
 * macsec_acl_counter_id is returned upon successful creation.
 * To destroy a MACSEC ACL counter, the counter must not be bound to an ACL and the
 * macsec_acl_counter_id should be provided.
 *
 * Supported devices: Spectrum4, systems with MACSEC capable gearbox
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE/DESTROY
 * @param[in] log_port - logical port (reserved when cmd is DESTROY)
 * @param[in] direction - direction (reserved when cmd is DESTROY)
 * @param[in,out] macsec_acl_counter_id_p - MACSEC ACL counter ID, as described above
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_NO_RESOURCES if no counter is available to create
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_INVALID_HANDLE if called Invalid Handle
 * @return SX_STATUS_ENTRY_NOT_FOUND if called with DESTROY command and the counter does not exist
 */
sx_status_t sx_api_macsec_acl_counter_set(const sx_api_handle_t       handle,
                                          const sx_access_cmd_t       cmd,
                                          const sx_port_log_id_t      log_port,
                                          const sx_macsec_direction_e direction,
                                          sx_macsec_acl_counter_id_t *macsec_acl_counter_id_p);


/**
 * This API retrieves the MACSEC ACL Counter values.
 *
 * Supported devices: Spectrum4, systems with MACSEC capable gearbox
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - READ/READ_CLEAR
 * @param[in] macsec_acl_counter_id_list - MACSEC ACL counter ID list
 * @param[out] macsec_acl_counter_set_list - counter value list
 * @param[out] counter_list_len - counter list len
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if event mode is out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if there is a message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds the limit
 * @return SX_STATUS_COMM_ERROR Communication error (failure to send)
 * @return SX_STATUS_INVALID_HANDLE if called Invalid Handle
 */
sx_status_t sx_api_macsec_acl_counter_get(const sx_api_handle_t             handle,
                                          const sx_access_cmd_t             cmd,
                                          const sx_macsec_acl_counter_id_t *macsec_acl_counter_id_list,
                                          sx_macsec_acl_counter_set_t      *macsec_acl_counter_set_list,
                                          uint32_t                          counter_list_len);
#endif /* __SX_API_MACSEC_H__*/
