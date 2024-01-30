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

#ifndef __SX_API_FLEX_PM_H__
#define __SX_API_FLEX_PM_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of FLEX_PM module.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Set verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - FLEX_PM module verbosity level
 * @param[in] api_verbosity_level      - FLEX_PM API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_flex_pm_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                   const sx_log_verbosity_target_t verbosity_target,
                                                   const sx_verbosity_level_t      module_verbosity_level,
                                                   const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of FLEX_PM module.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Get verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - FLEX_PM module verbosity level
 * @param[out] api_verbosity_level_p    - FLEX_PM API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_NULL if an input parameter is invalid
 */
sx_status_t sx_api_flex_pm_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                   const sx_log_verbosity_target_t verbosity_target,
                                                   sx_verbosity_level_t           *module_verbosity_level_p,
                                                   sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API configures (CREATE/EDIT/DESTROY) an application.
 * This sets the application's attributes.
 *
 * Can not edit or destroy a running application.
 * Can not destroy an application that still has contexts added to it.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] cmd          - CREATE/EDIT/DESTROY
 * @param[in/out] key_p    - The application's key. Output on CREATE, input on EDIT/DESTROY
 * @param[in] attr_p       - The attributes to set to the application. Ignored on DESTROY
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a NULL is given
 * @return SX_STATUS_PARAM_ERROR if a parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter is not in the expected range
 * @return SX_STATUS_ENTRY_NOT_FOUND if an entity can't be retrieved
 * @return SX_STATUS_RESOURCE_IN_USE if EDIT/DESTROY is executed on a running application
 * @return SX_STATUS_NO_MEMORY if memory allocation failed
 * @return SX_STATUS_CMD_UNSUPPORTED if the given command is not supported
 * @return SX_STATUS_ERROR on general error
 */
sx_status_t sx_api_flex_pm_app_set(const sx_api_handle_t        handle,
                                   const sx_access_cmd_t        cmd,
                                   sx_flex_pm_app_key_t        *key_p,
                                   const sx_flex_pm_app_attr_t *attr_p);

/**
 * This API retrieves the attributes of a configured application.
 *
 * Note: attr_p contains the two fields: resources_list and resources_list_cnt.
 *       If resources_list is not NULL, it will be filled with a resources_list_cnt
 *       resources configured. Neither the picking nor the order of the resources
 *       retrieved is defined. Note: if resources_list_cnt is larger than the
 *       number of all the configured resources, then all the resources will
 *       be retrieved and resources_list_cnt will be updated to their number.
 *       If resources_list is NULL, resources_list_cnt will be updated to the
 *       number of all the configured resources.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4
 *
 * @param[in] handle     - SX-API handle
 * @param[in] cmd        - GET
 * @param[in] key        - The key to the application to retrieve
 * @param[out] attr_p    - The attributes to be filled by the API
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a NULL is given
 * @return SX_STATUS_PARAM_ERROR if a parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if an entity can't be retrieved
 * @return SX_STATUS_NO_MEMORY if memory allocation failed
 * @return SX_STATUS_CMD_UNSUPPORTED if the given command is not supported
 * @return SX_STATUS_ERROR on general error
 */
sx_status_t sx_api_flex_pm_app_get(const sx_api_handle_t      handle,
                                   const sx_access_cmd_t      cmd,
                                   const sx_flex_pm_app_key_t key,
                                   sx_flex_pm_app_attr_t     *attr_p);

/**
 * This API sets the state of a configured application.
 *
 * Note: can not set the application's state to 'run' if it has no program set.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] cmd          - SET
 * @param[in] key_p        - The key to the application to set its state
 * @param[in] attr_p       - The state's attributes to set to the application
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a NULL is given
 * @return SX_STATUS_PARAM_ERROR if a parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if an entity can't be retrieved
 * @return SX_STATUS_CMD_UNSUPPORTED if the given command is not supported
 * @return SX_STATUS_ERROR on general error
 */
sx_status_t sx_api_flex_pm_app_state_set(const sx_api_handle_t              handle,
                                         const sx_access_cmd_t              cmd,
                                         const sx_flex_pm_app_key_t        *key_p,
                                         const sx_flex_pm_app_state_attr_t *attr_p);

/**
 * This API ADD/DELETE/DELETE ALL context(s).
 *
 * ADD/DELETE adds/deletes all the given contexts. DELETE_ALL deletes all
 * the contexts in the system.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] cmd          - ADD/DELETE/DELETE_ALL
 * @param[in] key_list     - Contexts keys. Valid on ADD/DELETE commands
 * @param[in] config_list  - Contexts configurations. Valid only on ADD command.
 *                           Note: configuration at element i in this list
 *                           corresponds to the key at element i in key_list
 * @param[in] context_cnt  - The number of elements in each of key_list
 *                           and config_list (when valid) lists. Valid
 *                           on ADD/DELETE commands
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a NULL is given
 * @return SX_STATUS_PARAM_ERROR if a parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if an entity can't be retrieved
 * @return SX_STATUS_NO_MEMORY if memory allocation failed
 * @return SX_STATUS_CMD_UNSUPPORTED if the given command is not supported
 * @return SX_STATUS_ERROR on general error
 */
sx_status_t sx_api_flex_pm_app_program_context_set(const sx_api_handle_t                          handle,
                                                   const sx_access_cmd_t                          cmd,
                                                   const sx_flex_pm_app_program_context_key_t    *key_list,
                                                   const sx_flex_pm_app_program_context_config_t *config_list,
                                                   const uint32_t                                 context_cnt);

/**
 * This API sets a program and adds it to the given application
 * (application key is created by sx_api_flex_pm_app_set).
 * Each application can have only one program added to it.
 * In order to set a program, the application should not be running.
 * Maximum number of commands in a program is SX_FLEX_PM_PROGRAM_CMD_MAX.
 *
 * Supported devices:  Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] cmd     - SX_ACCESS_CMD_ADD/SX_ACCESS_CMD_EDIT/SX_ACCESS_CMD_DELETE
 * @param[in] key     - The application key to set the program for
 * @param[in] attr_p  - The program attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_RESOURSE_IN_USE if EDIT/DELETE command is executed on running application
 * @return SX_STATUS_ENTRY_ALREADY_BOUND if a program is added to an already bound application
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_flex_pm_app_program_set(const sx_api_handle_t                handle,
                                           const sx_access_cmd_t                cmd,
                                           const sx_flex_pm_app_key_t           key,
                                           const sx_flex_pm_app_program_attr_t *attr_p);

/**
 * This API gets the program attributes set for the given application.
 *
 * Supported devices:  Spectrum2, Spectrum3, Spectrum4
 *
 * @param[in] handle  - SX-API handle
 * @param[in] cmd     - SX_ACCESS_CMD_GET
 * @param[in] key     - The application key to get the program for
 * @param[out] attr_p - The program attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_flex_pm_app_program_get(const sx_api_handle_t          handle,
                                           const sx_access_cmd_t          cmd,
                                           const sx_flex_pm_app_key_t     key,
                                           sx_flex_pm_app_program_attr_t *attr_p);

#endif /* __SX_API_FLEX_PM_H__ */
