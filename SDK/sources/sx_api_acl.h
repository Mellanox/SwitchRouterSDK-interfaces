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

#ifndef __SX_API_ACL_H__
#define __SX_API_ACL_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_acl.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of the ACL module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - ACL module verbosity level
 * @param[in] api_verbosity_level      - ACL API verbosity level
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 *         SX_STATUS_ERROR                                                                General error
 */
sx_status_t sx_api_acl_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of the ACL module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - ACL module verbosity level
 * @param[out] api_verbosity_level_p    - ACL API verbosity level
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ERROR                                                                General error
 */
sx_status_t sx_api_acl_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API is used to create an ACL region (rules list).
 *
 * CREATE is used to create a new region and takes the key_type and region size as input. Region ID is returned
 * upon successful creation.
 * DESTORY is used to destroy an existing region. The ACL region must not be bound to any ACL rules.
 * EDIT is used for resizing an existing ACL region. acl_region_id and new size should be provided.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - CREATE/DESTROY/EDIT
 * @param[in] key_type        - Key type used in this ACL (should be created using sx_api_acl_flex_key_set)
 * @param[in] action_type     - This parameter should be set to zero (irrelevant for current ACL implementation)
 * @param[in] acl_size        - Maximum number of rules in this ACL
 * @param[in,out] region_id_p - ACL region ID, as described above
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                      Entry is not found in database
 * @return SX_STATUS_NO_RESOURCES                                                         No resources are available to create the region
 * @return SX_STATUS_CMD_UNSUPPORTED                                                      Command is unsupported
 */
sx_status_t sx_api_acl_region_set(const sx_api_handle_t      handle,
                                  const sx_access_cmd_t      cmd,
                                  const sx_acl_key_type_t    key_type,
                                  const sx_acl_action_type_t action_type,
                                  const sx_acl_size_t        region_size,
                                  sx_acl_region_id_t        *region_id_p);

/**
 * This API is used to get an ACL region's properties.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] region_id        - ACL region ID
 * @param[out] key_type_p      - Key type used in this ACL region
 * @param[out] action_type_p   - This parameter is ignored and will be set to 0
 * @param[out] region_size_p   - Maximum number of rules in this ACL region
 *
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                      Entry is not found in database
 */
sx_status_t sx_api_acl_region_get(const sx_api_handle_t    handle,
                                  const sx_acl_region_id_t region_id,
                                  sx_acl_key_type_t       *key_type_p,
                                  sx_acl_action_type_t    *action_type_p,
                                  sx_acl_size_t           *region_size_p);

/**
 * This API is used to create a single region ACL.
 *
 * CREATE is used for creating a new ACL. It will return an ACL ID upon successful creation.
 * DESTROY may be used to destroy the ACL when it is not bound to the hardware.
 *
 * Note: If an ACL is created with the SX_ACL_DIRECTION_MULTI_POINTS_E direction,
 * the user must set the ACL direction bitmap (acl_attributes.multi_direction.acl_direction_bitmap) of the desired directions
 * using the sx_api_acl_attributes_set API prior to any other API operations
 * (for example, setting it to an ACL group, adding rules to the bound ACL region).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - CREATE/DESTROY
 * @param[in] acl_type           - ACL type of this ACL (only AGNOSTIC type is currently supported)
 * @param[in] acl_direction      - ACL direction
 * @param[in] acl_region_group_p - ACL region group matching ACL type
 * @param[in,out] acl_id_p       - ACL ID, as described above
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     Entry is not found in database
 * @return SX_STATUS_NO_RESOURCES                                                        No hardware resources are available to create the ACL
 * @return SX_STATUS_CMD_UNSUPPORTED                                                     Command provided is unsupported
 */
sx_status_t sx_api_acl_set(const sx_api_handle_t        handle,
                           const sx_access_cmd_t        cmd,
                           const sx_acl_type_t          acl_type,
                           const sx_acl_direction_t     acl_direction,
                           const sx_acl_region_group_t *acl_region_group_p,
                           sx_acl_id_t                 *acl_id_p);

/**
 * This API is used to get an ACL's attributes. It takes an input of an ACL ID and returns the attributes of that ACL
 * (i.e., the ACL type and a list of attached regions). The length of the regions list depends on the ACL type.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] acl_id              - ACL ID
 * @param[out] acl_type_p         - ACL type (packet agnostic or packet sensitive)
 * @param[out] acl_direction_p    - ACL direction
 * @param[out] acl_region_group_p - ACL region group attached to the ACL
 *
 *
 * @return SX_STATUS_SUCCESS                                        Operation completed successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE    Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                Entry is not found in database
 */
sx_status_t sx_api_acl_get(const sx_api_handle_t  handle,
                           const sx_acl_id_t      acl_id,
                           sx_acl_type_t         *acl_type_p,
                           sx_acl_direction_t    *acl_direction_p,
                           sx_acl_region_group_t *acl_region_group_p);

/**
 * This API gets a list of valid ACL IDs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] cmd               - GET/GET_NEXT/GET_FIRST
 * @param[in] acl_id_key        - ACL ID to use and key
 * @param[in] acl_filter_p      - Filter to use (not supported yet)
 * @param[out] acl_id_list_p    - Pointer to the list of ACL IDs returned
 * @param[in,out] acl_id_cnt_p  - [in] number of entries to retrieve (max 400)/[out] number of entries retrieved
 *
 * Input/Output Types
 *      - Get first - Gets a list of first N entries. The command should be SX_ACCESS_CMD_GET_FIRST and
 *           count should be equal to N (acl_id_key is irrelevant in this case). Returns the number of
 *           entries retrieved via acl_id_cnt_p.
 *      - Get next - Gets N entries after a specified acl_id_key (it does not have to exist).
 *           The command should be SX_ACCESS_CMD_GETNEXT. The value of acl_id_cnt_p should be equal to N.
 *           Returns the number of entries retrieved via acl_id_cnt_p.
 *      - Get - Gets a specific entry. The command should be SX_ACCESS_CMD_GET and the value of acl_id_cnt_p should be 1.
 *       Setting the input value of acl_id_cnt_p is 0 returns the count of the ACL IDs available.
 *
 * @return SX_STATUS_SUCCESS                   Operation completed successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE       Parameters exceed range
 * @return SX_STATUS_PARAM_ERROR               Any parameter is in error
 * @return SX_STATUS_CMD_UNSUPPORTED           Command is not supported
 * @return SX_STATUS_INVALID_HANDLE            Handle in invalid
 * @return SX_STATUS_ERROR                     General error
 */

sx_status_t sx_api_acl_iter_get(const sx_api_handle_t  handle,
                                const sx_access_cmd_t  cmd,
                                const sx_acl_id_t      acl_id_key,
                                const sx_acl_filter_t *acl_filter_p,
                                sx_acl_id_t           *acl_id_list_p,
                                uint32_t              *acl_id_cnt_p);
/**
 *
 * This API is used to set the attributes of an ACL.
 *
 * Note: The ACL direction bitmap of an ACL can be set only once and cannot be changed.
 * To change other attributes, the user can pass an empty bitmap (bitmap = 0) or
 * exactly the same that has been set already.
 * Note: The ACL direction bitmap can contain any combinations of ACL directions
 * as long as each one of the used ACL keys is supported in all selected directions.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] cmd            - SET
 * @param[in] acl_id         - ACL ID
 * @param[in] acl_attributes - ACL attributes
 *
 * @return SX_STATUS_SUCCESS            Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR        Any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED    Command is unsupported
 */
sx_status_t sx_api_acl_attributes_set(const sx_api_handle_t     handle,
                                      const sx_access_cmd_t     cmd,
                                      const sx_acl_id_t         acl_id,
                                      const sx_acl_attributes_t acl_attributes);

/**
 *
 * This API is used to retrieve the attributes of an ACL.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] acl_id                - ACL ID
 * @param[in,out] acl_attributes_p  - Returned ACL attributes
 *
 * @return SX_STATUS_SUCCESS                               Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_NULL   Any input parameter is invalid
 */
sx_status_t sx_api_acl_attributes_get(const sx_api_handle_t      handle,
                                      const sx_acl_id_t          acl_id,
                                      const sx_acl_attributes_t *acl_attributes_p);

/**
 *
 * This API is used to set certain global attributes of the ACL module.
 *
 * Note: Enabling certain functionality may require enabling both the global and individual attributes.
 * Use sx_api_acl_attributes_set to set individual attributes.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - SET
 * @param[in] global_acl_attributes - Global ACL attributes
 *
 * @return SX_STATUS_SUCCESS           Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR       Any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED   Command is unsupported
 */
sx_status_t sx_api_acl_global_attributes_set(const sx_api_handle_t            handle,
                                             const sx_access_cmd_t            cmd,
                                             const sx_acl_global_attributes_t global_acl_attributes);

/**
 *
 * This API is used to retrieve the global attributes of the ACL module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[out] global_acl_attributes_p  - Returned global ACL attributes
 *
 * @return SX_STATUS_SUCCESS                               Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_NULL   Any input parameter is invalid
 */
sx_status_t sx_api_acl_global_attributes_get(const sx_api_handle_t             handle,
                                             const sx_acl_global_attributes_t *global_acl_attributes_p);

/**
 *
 * This API is used for controlling ACL groups. Allows to create a liked list of ACL blocks up to the size of SX_ACL_MAX_ACL_GROUP_SIZE.
 *
 * CREATE is used to create a new group with a specified group direction and returns new group ID.
 * SET is used to add a list of ACLs to the group. The ACLs need to be in the same direction as the group.
 * DESTROY is used to destroy the ACL group. This can be done only if the ACL group is not bound to the hardware.
 *
 * Note: SX_ACL_DIRECTION_MULTI_POINTS_E ACL groups are not supported.
 * Note: An ACL that has the SX_ACL_DIRECTION_MULTI_POINTS_E direction cannot be added to an ACL group until the ACL direction bitmap is set.
 * Note: Every ACL that is being set to the group should either have the same direction as the group or if the ACL has MULTI-POINTS direction,
 * then ACL's direction bitmap should include the group's direction.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - CREATE/SET/DESTROY
 * @param[in] acl_direction - ACL group direction
 * @param[in] acl_id_list_p - Ordered list of ACL IDs (ignored when using the command CREATE or DESTROY)
 * @param[in] acl_id_cnt    - Number of elements in the list of ACL IDs (ignored when using the command CREATE or DESTROY)
 * @param[in,out] group_id  - ACL group ID
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     Entry is not found in database
 * @return SX_STATUS_NO_RESOURCES                                                        No resources are available to create the new group
 * @return SX_STATUS_CMD_UNSUPPORTED                                                     Command is unsupported
 */
sx_status_t sx_api_acl_group_set(const sx_api_handle_t    handle,
                                 const sx_access_cmd_t    cmd,
                                 const sx_acl_direction_t acl_direction,
                                 const sx_acl_id_t       *acl_id_list_p,
                                 const uint32_t           acl_id_cnt,
                                 sx_acl_id_t             *group_id_p);

/**
 *
 * This API is used to get the properties of a provided group ID.
 *
 * Note: If the supplied acl_id_count is 0, the command only retrieves a count of the ACLs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] group_id         - ACL group ID
 * @param[out] acl_direction   - ACL direction
 * @param[out] acl_id_list_p   - List of the group ACL IDs
 * @param[in,out] acl_id_cnt_p - [In] size of the ACL ID's array/[OUT] number of valid ACL IDs
 *
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     Entry is not found in database
 *
 */
sx_status_t sx_api_acl_group_get(const sx_api_handle_t handle,
                                 const sx_acl_id_t     group_id,
                                 sx_acl_direction_t   *acl_direction_p,
                                 sx_acl_id_t          *acl_id_list_p,
                                 uint32_t             *acl_id_cnt_p);

/**
 * This API gets a list of valid ACL group IDs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - GET/GET_NEXT/GET_FIRST
 * @param[in] group_id_key     - ACL group ID to use as group_id_key for GET and GET_NEXT commands
 * @param[in] acl_filter_p     - Filter to use (not supported yet)
 * @param[out] acl_id_list_p   - Pointer to the list of valid ACL Group IDs returned
 * @param[in,out] acl_id_cnt_p -[in] number of entries to retrieve (max 400)/[out] number of entries retrieved
 *
 * Input/Output Types
 *    - Get first - Gets a list of first N entries. The command should be SX_ACCESS_CMD_GET_FIRST and
 *      count should be equal to N (acl_id_key is irrelevant in this case). Returns the number of
 *      entries retrieved via acl_id_cnt_p.
 *    - Get next - Gets N entries after a specified acl_id_key (it does not have to exist).
 *      The command should be SX_ACCESS_CMD_GETNEXT. The value of acl_id_cnt_p should be equal to N.
 *      Returns the number of entries retrieved via acl_id_cnt_p.
 *    - Get - Gets a specific entry. The command should be SX_ACCESS_CMD_GET and the value of acl_id_cnt_p should be 1.
 *      Setting the input value of acl_id_cnt_p is 0 returns the count of the ACL IDs available.
 *
 * @return SX_STATUS_SUCCESS                Operation completed successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE    Parameters exceed the range
 * @return SX_STATUS_PARAM_ERROR            Any parameter is in error
 * @return SX_STATUS_CMD_UNSUPPORTED        Command is not supported
 * @return SX_STATUS_INVALID_HANDLE         Handle in invalid
 * @return SX_STATUS_ERROR                  General error
 */

sx_status_t sx_api_acl_group_iter_get(const sx_api_handle_t  handle,
                                      const sx_access_cmd_t  cmd,
                                      const sx_acl_id_t      group_id_key,
                                      const sx_acl_filter_t *acl_filter_p,
                                      sx_acl_id_t           *acl_id_list_p,
                                      uint32_t              *acl_id_cnt_p);

/**
 *
 * This API is used to set the attributes of an ACL group.
 * After the ACL group is created by sx_api_acl_group_set API, it is possible to set a priority to the ACL group.
 * The default group priority is FLEX_ACL_GROUP_PRIORITY_DEFAULT.
 * When binding multiple ACL groups to a port, the groups will be ordered according to their priority.
 * Setting priority of a group that is already bound does not take effect on previously bound groups.
 *
 * Note: Priority values range is FLEX_ACL_GROUP_PRIORITY_MIN to FLEX_ACL_GROUP_PRIORITY_MAX.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - SET
 * @param[in] acl_group_id          - ACL group ID
 * @param[in] acl_group_attr_p      - ACL group attributes pointer
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED      Command is unsupported
 * @return SX_STATUS_ERROR                General error
 *
 */
sx_status_t sx_api_acl_group_attributes_set(const sx_api_handle_t            handle,
                                            const sx_access_cmd_t            cmd,
                                            const sx_acl_id_t                acl_group_id,
                                            const sx_acl_group_attributes_t *acl_group_attr_p);

/**
 *
 * This API is used to get the attributes of a given ACL group.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] acl_group_id      - ACL group ID
 * @param[out] acl_group_attr_p - ACL group attributes
 *
 * @return SX_STATUS_SUCCESS                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR   Any input parameter is invalid
 * @return SX_STATUS_ERROR                               General error
 *
 */
sx_status_t sx_api_acl_group_attributes_get(const sx_api_handle_t            handle,
                                            const sx_acl_id_t                group_id,
                                            const sx_acl_group_attributes_t *acl_group_attr_p);


/**
 * This API adds/edits/deletes a policy based switching (PBS) set. A PBS entry can be later bound to an ACL rule
 * in order to specify destination port/port group (multicast) or send the frame to the router block.
 *
 * ADD creates a PBS entry.
 *
 * Note: this operation may fail if no hardware resources are available. PBS entry can be created without ports
 *  in order to ensure future hardware resource availability. Use the commands ADD_PORTS and DELETE_PORTS to
 *  edit an existing PBS entry and to add or delete ports.
 * Note: A unicast entry can have only 1 port. Use the DELETE command to clear a PBS record (not allowed when
 *  this record is in use by ACL rules).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] cmd        - ADD/ADD_PORTS/DELETE_PORTS/DELETE
 * @param[in] pbs_entry  - PBS attributes
 * @param[in,out] pbs_id - PBS ID
 *
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                      Entry is not found in database
 * @return SX_STATUS_NO_RESOURCES                                                         No hardware resources for PBS creation
 * @return SX_STATUS_RESOURCE_IN_USE                                                      PBS record is in use
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                                                Hardware failure
 * @return SX_STATUS_PARAM_ERROR                                                          Any input parameters is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED                                                      Command is unsupported
 * @return SX_STATUS_INVALID_HANDLE                                                       Invalid handle error
 */
sx_status_t sx_api_acl_policy_based_switching_set(const sx_api_handle_t     handle,
                                                  const sx_access_cmd_t     cmd,
                                                  const sx_swid_t           swid,
                                                  const sx_acl_pbs_entry_t *pbs_entry_p,
                                                  sx_acl_pbs_id_t          *pbs_id_p);

/**
 * This API is used to get a PBS set or to get the number of ports in a PBS set.
 *
 * Note: For the GET command, the pbs_entry.log_ports should be pre-allocated and the pbs_entry.port_num should be
 * set to the maximum number of ports to be retrieved.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - COUNT/GET
 * @param[in] swid            - SWID of the PBS entry
 * @param[in] pbs_id          - PBS entry ID
 * @param[in,out] pbs_entry   - PBS entry attributes
 *                              ([IN]max port number to retrieve/[OUT] actual number of ports retrieved)
 *
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     ACL element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                                               Hardware failure
 * @return SX_STATUS_CMD_UNSUPPORTED                                                     Unsupported command
 * @return SX_STATUS_INVALID_HANDLE                                                      Invalid handle error
 */
sx_status_t sx_api_acl_policy_based_switching_get(const sx_api_handle_t handle,
                                                  const sx_access_cmd_t cmd,
                                                  const sx_swid_t       swid,
                                                  const sx_acl_pbs_id_t pbs_id,
                                                  sx_acl_pbs_entry_t   *pbs_entry_p);

/**
 * This API gets a list of one or more PBS set object IDs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - GET/GET_NEXT/GET_FIRST
 * @param[in] swid             - SWID of the PBS entry
 * @param[in] pbs_id_key       - PBS entry ID to use as pbs_id_key for GET and GET_NEXT commands
 * @param[in] pbs_id_filter_p  - Filter the entries retrieved based on entry type.
 * @param[out] pbs_id_list_p   - Pointer to the list of PBS IDs returned
 * @param[in,out] pbs_id_cnt_p  - [in] number of entries to retrieve /[out] number of entries retrieved.
 *
 * Input/Output Types
 *    - GET_FIRST - Gets a list of first N entries. The command should be SX_ACCESS_CMD_GET_FIRST and
 *      count should be equal to N (pbs_id_key is irrelevant in this case). Returns the number of
 *      entries retrieved via pbs_id_cnt_p.
 *    - GET_NEXT - Gets N entries after a specified pbs_id_key (it does not have to exist).
 *      The command should be SX_ACCESS_CMD_GETNEXT. The value of pbs_id_cnt_p should be equal to N.
 *      Returns the number of entries retrieved via pbs_id_cnt_p.
 *    - GET - Gets a specific entry. The command should be SX_ACCESS_CMD_GET and the value of pbs_id_cnt_p should be 1.
 *      Setting the input value of pbs_id_cnt_p is 0 returns the total count of the PBS IDs available.
 *    - filter -  If a valid filter value is provided, the above commands will return PBS IDs that match the filter only.
 *                If none match, the API will succeed with a return count of 0 and an empty list.
 *
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Any parameter is in error
 * @return SX_STATUS_CMD_UNSUPPORTED      Command is not supported
 * @return SX_STATUS_INVALID_HANDLE       Handle is invalid
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_acl_policy_based_switching_iter_get(const sx_api_handle_t      handle,
                                                       const sx_access_cmd_t      cmd,
                                                       const sx_swid_t            swid,
                                                       const sx_acl_pbs_id_t      pbs_id_key,
                                                       const sx_acl_pbs_filter_t *pbs_id_filter_p,
                                                       sx_acl_pbs_id_t           *pbs_id_list_p,
                                                       uint32_t                  *pbs_id_cnt_p);

/***
 * This API adds/edits/deletes a Layer 4 port range comparison set (up to SX_ACL_MAX_PORT_RANGES).
 *
 * ADD command is used to create a new range ID from the supplied port range.
 * EDIT command is used to update the port range of the supplied range ID.
 * DELETE command is used to clear the range configuration. This will fail if the range is being used by an ACL.
 *
 * Note: SX_ACL_PORT_RANGE_IP_HEADER_BOTH option for IP header type is not supported in Spectrum2 and Spectrum3 systems.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - ADD/EDIT/DELETE
 * @param[in] l4_port_range - Layer 4 port range comparison
 * @param[in, out] range_id - Port range comparison ID
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO                                                   Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT                                          Message size error
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     ACL element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                                               Hardware failure
 * @return SX_STATUS_CMD_UNSUPPORTED                                                     Command is unsupported
 * @return SX_STATUS_INVALID_HANDLE                                                      Invalid handle error
 */
sx_status_t sx_api_acl_l4_port_range_set(const sx_api_handle_t            handle,
                                         const sx_access_cmd_t            cmd,
                                         const sx_acl_port_range_entry_t *l4_port_range_p,
                                         sx_acl_port_range_id_t          *range_id_p);

/**
 * This API is used to get the properties of a L4 port range comparison set.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] range_id       - Port range comparison ID
 * @param[out] l4_port_range - L4 port range
 *
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO                                                    Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT                                           Message size error
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                      ACL element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                                                Hardware failure
 * @return SX_STATUS_INVALID_HANDLE                                                       Invalid handle error
 */

sx_status_t sx_api_acl_l4_port_range_get(const sx_api_handle_t        handle,
                                         const sx_acl_port_range_id_t range_id,
                                         sx_acl_port_range_entry_t   *l4_port_range_p);

/**
 * This API gets a list of ACL L4 port range IDs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle.
 * @param[in] cmd                - GET/GET_NEXT/GET_FIRST
 * @param[in] range_id_key       - Range ID to use as range_id_key for GET and GET_NEXT commands
 * @param[in] range_id_filter_p  - Filter to use (not supported yet)
 * @param[out] range_id_list_p   - Pointer to the list of range IDs returned
 * @param[in,out] range_id_cnt_p - [in] number of entries to retrieve (max 16)/[out] number of entries retrieved
 *
 * Input/Output Types
 *    - Get first - Gets a list of first N entries. The command should be SX_ACCESS_CMD_GET_FIRST and
 *      count should be equal to N (acl_id_key is irrelevant in this case). Returns the number of
 *      entries retrieved via acl_id_cnt_p.
 *    - Get next - Gets N entries after a specified acl_id_key (it does not have to exist).
 *      The command should be SX_ACCESS_CMD_GETNEXT. The value of acl_id_cnt_p should be equal to N.
 *      Returns the number of entries retrieved via acl_id_cnt_p.
 *    - Get - Gets a specific entry. The command should be SX_ACCESS_CMD_GET and the value of acl_id_cnt_p should be 1.
 *      Setting the input value of acl_id_cnt_p is 0 returns the count of the ACL IDs available.
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameters exceed range
 * @return SX_STATUS_PARAM_ERROR          Any parameter is in error
 * @return SX_STATUS_CMD_UNSUPPORTED      Command is not supported
 * @return SX_STATUS_INVALID_HANDLE       Handle in invalid
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_acl_l4_port_range_iter_get(const sx_api_handle_t             handle,
                                              const sx_access_cmd_t             cmd,
                                              const sx_acl_port_range_id_t      range_id_key,
                                              const sx_acl_port_range_filter_t *range_id_filter_p,
                                              sx_acl_port_range_id_t           *range_id_list_p,
                                              uint32_t                         *range_id_cnt_p);

/**
 * This API adds/edits/deletes a range comparison set (up to SX_ACL_MAX_PORT_RANGES).
 * Supported range comparisons: L4 Port, IP length, TTL, Custom Bytes, and UTC.
 *
 * ADD command is used to write given range into a group and have their IDs returned.
 * EDIT command is used to set the given range into a given range ID.
 * DELETE command is used to clear the configuration of a given range ID.
 *
 * Note: SX_ACL_PORT_RANGE_IP_HEADER_BOTH option for IP header type is not supported on Spectrum2 and Spectrum3 systems.
 * Note: At a given time, no more than 2 Custom Bytes ranges can be used.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - ADD/EDIT/DELETE
 * @param[in] range_entry_p - Range comparison
 * @param[in, out] range_id - Range comparison ID
 *
 * @return SX_STATUS_SUCCESS                                        Operation completed successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO                              Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT                     Message size error
 * @return SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                ACL element is not found in database
 * @return SX_STATUS_NO_RESOURCES                                   No resources for the operation
 * @return SX_STATUS_RESOURCE_IN_USE                                Range is in use and cannot be deleted
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                          Hardware failure
 * @return SX_STATUS_CMD_UNSUPPORTED                                Command is unsupported
 * @return SX_STATUS_INVALID_HANDLE                                 Invalid handle error
 */
sx_status_t sx_api_acl_range_set(const sx_api_handle_t       handle,
                                 const sx_access_cmd_t       cmd,
                                 const sx_acl_range_entry_t *range_entry_p,
                                 sx_acl_port_range_id_t     *range_id_p);

/**
 * This API is used to get a range comparison set.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] range_id       - Range comparison ID
 * @param[out] range_entry_p - Struct for range comparison
 *
 *
 * @return SX_STATUS_SUCCESS                                        Operation completed successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO                              Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT                     Message size error
 * @return SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                ACL element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                          Hardware failure
 * @return SX_STATUS_INVALID_HANDLE                                 Invalid handle error
 */
sx_status_t sx_api_acl_range_get(const sx_api_handle_t        handle,
                                 const sx_acl_port_range_id_t range_id,
                                 sx_acl_range_entry_t        *range_entry_p);

/**
 * This API is used for getting and/or clearing the activity of a specific rule.
 *
 * Note: If the region is not bound, activity_p is invalid.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - READ/READ_CLEAR
 * @param[in] region_id   - ACL region ID
 * @param[in] rule_offset - ACL rule offset within the region
 * @param[out] activity_p - ACL rule activity
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     ACL element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                                               Hardware failure
 */
sx_status_t sx_api_acl_rule_activity_get(const sx_api_handle_t      handle,
                                         const sx_access_cmd_t      cmd,
                                         const sx_acl_region_id_t   region_id,
                                         const sx_acl_rule_offset_t rule_offset,
                                         boolean_t                 *activity_p);

/**
 * This API is used for moving a block of rules within an ACL region.
 * Moving is allowed before and after ACL bind. Moving a block does not affect search hits,
 * but may override existing rules if such exist on the new block location.
 * Non-valid rules within the block are moved as well.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] region_id       - ACL region ID
 * @param[in] block_start     - Rules block start offset within the ACL block
 * @param[in] block_size      - Number of rules to move within the block
 * @param[in] new_block_start - New offset of the first rule of the given rules block
 *
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     ACL element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                                               Hardware failure
 */
sx_status_t sx_api_acl_rule_block_move_set(const sx_api_handle_t      handle,
                                           const sx_acl_region_id_t   region_id,
                                           const sx_acl_rule_offset_t block_start,
                                           const sx_acl_size_t        block_size,
                                           const sx_acl_rule_offset_t new_block_start);

/**
 * This API is used to bind/unbind an ACL or an ACL group to a port (or LAG).
 * Binding more than one ACL to port may be achieved by using ACL groups.
 *
 * BIND command is used for binding a single ACL or a single ACL group to a port.
 * UNBIND command will clear port binding, even if there are multiple ACL groups which are bound to the port.
 * ADD command can be used to bind additional ACL groups (not ACLs) to the port. In this case,
 * the order of group execution is determined by the group priority, set by sx_api_acl_group_attributes_set API.
 * DELETE command can be used to remove an ACL group from multiple ACL groups bound to the port/LAG.
 *
 *
 * Binding to L2 tunnel ports is supported in this API as well.
 * Spectrum systems support NVE port binding by providing the NVE logical port.
 * Spectrum support is a virtual binding to the NVE decap table, where ADD and DELETE commands are not supported.
 * Spectrum2 support for L2 tunnel port binding has API support like any other port binding.
 * In order to bind L2 tunnel port, the appropriate logical port and an ACL group with one of the directions
 * SX_ACL_DIRECTION_TPORT_INGRESS or SX_ACL_DIRECTION_TPORT_EGRESS should be provided.
 *
 * Note: ADD and DELETE commands support binding of ACL groups only.
 * Note: Binding or adding groups may fail if there are insufficient resources in hardware.
 * Note: An ACL that has the SX_ACL_DIRECTION_MULTI_POINTS_E direction cannot be bound to a port directly,
 * instead the user has to create an ACL group, add the ACL into it, and then bind this ACL group to a port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] cmd      - BIND/UNBIND/ADD/DELETE
 * @param[in] log_port - Logical port ID to bind
 * @param[in] acl_id   - ACL ID given for ACL or ACL group
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     ACL element is not found in database
 * @return SX_STATUS_NO_RESOURCES                                                        No resources are available for the operation
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                                               Hardware failure
 * @return SX_STATUS_CMD_UNSUPPORTED                                                     Command is unsupported
 */
sx_status_t sx_api_acl_port_bind_set(const sx_api_handle_t  handle,
                                     const sx_access_cmd_t  cmd,
                                     const sx_port_log_id_t log_port,
                                     const sx_acl_id_t      acl_id);

/**
 * This API is used to get the ACL ID of an ACL table or ACL group which is bound to a specific port.
 * When multiple groups are bound to a port, this API will return the highest priority group.
 * To retrieve multiple bindings, it is recommended to use the sx_api_acl_port_bindings_get API.
 *
 * Note: The acl_direction cannot be set to the SX_ACL_DIRECTION_MULTI_POINTS_E direction.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical port ID
 * @param[in] acl_direction - Ingress or egress ACL
 * @param[out] acl_id_p     - ACL ID of an ACL or ACL group
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     Port is not bound
 */
sx_status_t sx_api_acl_port_bind_get(const sx_api_handle_t    handle,
                                     const sx_port_log_id_t   log_port,
                                     const sx_acl_direction_t acl_direction,
                                     sx_acl_id_t             *acl_id_p);

/**
 * This API is used to retrieve the ACL IDs/groups bound to a specific port.
 * Since multiple groups may be bound to a port, the caller of this API is responsible of providing
 * an allocated array for getting the ACL IDs.
 *
 * If the API is called with acl_id_p parameter set to NULL or *acl_cnt_p set to 0,
 * it will return the actual number of ACL IDs bound to this port.
 *
 * Note: The acl_direction cannot be set to the SX_ACL_DIRECTION_MULTI_POINTS_E direction.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical port ID
 * @param[in] acl_direction - ACL direction
 * @param[in,out] acl_id_p  - An array of ACL IDs, should be allocated by the caller
 * @param[in,out] acl_cnt_p - Specifies the maximum amount of ACL IDs to retrieve and returns the actual number of ACL IDs retrieved.
 *
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                      Port is not bound
 */
sx_status_t sx_api_acl_port_bindings_get(const sx_api_handle_t    handle,
                                         const sx_port_log_id_t   log_port,
                                         const sx_acl_direction_t acl_direction,
                                         sx_acl_id_t             *acl_id_p,
                                         uint32_t                *acl_cnt_p);

/**
 * This API is used for controlling mapping of VLANs into VLAN groups for ACL binding.
 *
 * CREATE command is used for creating a new group, will return a free group ID
 * ADD/DELETE commands are used to control mapping of SWID and VID to an existing VLAN group
 * DESTROY command is used to free a VLAN group resource
 *
 * Note: This API is only valid when in 802.1Q mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle.
 * @param[in] cmd          - CREATE/ADD/DELETE/DESTROY
 * @param[in] swid         - SWID (used only with ADD/DELETE)
 * @param[in,out] group_id - VLAN group ID
 * @param[in] vlan_list    - A list of VLANs to attach to this group
 * @param[in] vlan_num     - Number of elements in the VLAN list
 *
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                      Entry not found in database
 * @return SX_STATUS_NO_RESOURCES                                                         No resources available for operation
 * @return SX_STATUS_CMD_UNSUPPORTED                                                      Command is unsupported
 */
sx_status_t sx_api_acl_vlan_group_map_set(const sx_api_handle_t handle,
                                          const sx_access_cmd_t cmd,
                                          const sx_swid_id_t    swid,
                                          const sx_vlan_id_t   *vlan_list_p,
                                          const uint32_t        vlan_cnt,
                                          sx_acl_vlan_group_t  *group_id_p);

/**
 * This API is used for getting the current mapping of VLANs into VLAN groups for ACL binding.
 * The vlan_list parameter are arrays at the size of vlan_num which is filled by this.
 * The actual size is then returned as output.
 *
 * Note: This API is only valid when in 802.1Q mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] swid         - SWID
 * @param[in] group_id     - VLAN group ID
 * @param[out] vlan_list   - List of VLANs which are members in this VLAN group (in the given SWID)
 * @param[in,out] vlan_num - [IN] number of elements allocated in the mapping entries arrays/
 *                           [OUT] number of actual elements found
 *
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     Entry not found in database
 * @return SX_STATUS_CMD_UNSUPPORTED                                                     802.1D mode is enabled
 */
sx_status_t sx_api_acl_vlan_group_map_get(const sx_api_handle_t     handle,
                                          const sx_swid_id_t        swid,
                                          const sx_acl_vlan_group_t group_id,
                                          sx_vlan_id_t             *vlan_list_p,
                                          uint32_t                 *vlan_cnt_p);

/**
 * This API is used to bind/unbind an ACL or an ACL group to a VLAN group.
 * Binding more than one ACL to the VLAN group may be achieved by using ACL groups.
 *
 * BIND command is used for binding a single ACL or a single ACL group to a VLAN group.
 * UNBIND command will clear the VLAN group binding, even if there are multiple ACL groups which are bound to the VLAN group.
 * ADD command can be used to bind multiple ACL groups to the VLAN group.
 * In this case, the order of group execution is determined by the group priority, set by sx_api_acl_group_attributes_set API.
 * DELETE command can similarly be used to remove an ACL group from multiple ACL groups bound to a VLAN group.
 *
 * Note: ADD and DELETE commands support binding of ACL groups only.
 * Note: Binding or adding groups may fail if there are insufficient resources in hardware.
 * Note: When in 802.1D mode instead of providing a VLAN group, a bridge_id should be used.
 * Note: An ACL that has the SX_ACL_DIRECTION_MULTI_POINTS_E direction cannot be bound to a VLAN group directly,
 * instead the user has to create an ACL group, add the ACL into it, and then bind this ACL group to a VLAN group.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] cmd        - BIND/UNBIND/ADD/DELETE
 * @param[in] vlan_group - VLAN group ID to bind
 * @param[in] acl_id     - ACL ID of an ACL or ACL group
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     ACL element is not found in database
 * @return SX_STATUS_NO_RESOURCES                                                        No ACL is available to create
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                                               Hardware failure
 * @return SX_STATUS_CMD_UNSUPPORTED                                                     Command is unsupported
 */
sx_status_t sx_api_acl_vlan_group_bind_set(const sx_api_handle_t     handle,
                                           const sx_access_cmd_t     cmd,
                                           const sx_acl_vlan_group_t vlan_group,
                                           const sx_acl_id_t         acl_id);

/**
 * This API is used to get the ACL ID of an ACL table or an ACL group which is bound to a specific VLAN group.
 * When multiple ACLs are bound to the VLAN group, this API will only return the one carrying the highest priority.
 * To retrieve multiple bindings, use sx_api_acl_vlan_group_bindings_get.
 *
 * Note: When in 802.1D mode, instead of providing a VLAN group, a bridge_id should be used.
 * Note: The acl_direction cannot be set to the SX_ACL_DIRECTION_MULTI_POINTS_E direction.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] vlan_group    - VLAN group ID
 * @param[in] acl_direction - Ingress or egress ACL
 * @param[out] acl_id_p     - ACL ID of an ACL or ACL group
 *
 * @return SX_STATUS_SUCCESS                                        Operation completed successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE    Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                VLAN group is not bound
 */
sx_status_t sx_api_acl_vlan_group_bind_get(const sx_api_handle_t     handle,
                                           const sx_acl_vlan_group_t vlan_group,
                                           const sx_acl_direction_t  acl_direction,
                                           sx_acl_id_t              *acl_id_p);

/**
 * This API allows getting ACL IDs bound to a specific VLAN group. Since multiple groups may be bound to a VLAN group,
 * the caller of this API is responsible of providing an allocated array for getting the ACL IDs.
 *
 * If this API is called with acl_id_p parameter set to NULL or *acl_cnt_p set to 0, it will return the actual number
 * of ACL IDs bound to this VLAN group.
 *
 * Note: The acl_direction cannot be set to the SX_ACL_DIRECTION_MULTI_POINTS_E direction.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] vlan_group    - VLAN group ID
 * @param[in] acl_direction - ACL direction
 * @param[in,out] acl_id_p  - An array of ACL IDs (should be allocated by the caller)
 * @param[in,out] acl_cnt_p - Specifies the maximum number of ACL IDs to retrieve
 *                            and returns the actual number of ACL IDs retrieved
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                      Port is not bound
 */
sx_status_t sx_api_acl_vlan_group_bindings_get(const sx_api_handle_t     handle,
                                               const sx_acl_vlan_group_t vlan_group,
                                               const sx_acl_direction_t  acl_direction,
                                               sx_acl_id_t              *acl_id_p,
                                               uint32_t                 *acl_cnt_p);

/**
 * This API returns attributes of the flexible ACL key.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] key_handle           - Handle to flexible key
 * @param[out] key_attr_p          - Key attributes
 *
 * @return SX_STATUS_SUCCESS            Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR        Input parameters is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND    Key handle is wrong
 */
sx_status_t sx_api_acl_flex_key_attr_get(const sx_api_handle_t    handle,
                                         const sx_acl_key_type_t  key_handle,
                                         sx_acl_flex_key_attr_t * key_attr_p);

/**
 * This API is used to create/delete a flexible ACL key.
 * A flexible ACL key is a combination of hardware predefined key blocks.
 * The key blocks themselves are composed of several filters and the smallest possible set of key blocks
 * will be chosen by the SCP algorithm that encompasses all the keys specified by the API.
 * Key creation is a pure database operation. The maximum number of keys is equal to the maximum number of regions.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] cmd                  - The access cmd CREATE/DELETE
 * @param[in] key_list_p           - Array of basic key IDs
 * @param[in] key_cnt              - Number of elements in basic key array
 * @param[out] key_handle_p        - Handle of the created flexible key
 *
 * @return  SX_STATUS_SUCCESS       Operation completed successfully
 * @return  SX_STATUS_PARAM_ERROR   Any input parameter is invalid
 * @return  SX_STATUS_UNSUPPORTED   Unsupported command
 * @return  SX_STATUS_ERROR         General error
 */
sx_status_t sx_api_acl_flex_key_set(const sx_api_handle_t handle,
                                    const sx_access_cmd_t cmd,
                                    const sx_acl_key_t  * key_list_p,
                                    const uint32_t        key_count,
                                    sx_acl_key_type_t   * key_handle_p);

/**
 * This API returns the list of filters included in the flexible key.
 * The user is responsible for a memory management of the filters list.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] key_handle            - Handle of flexible key
 * @param[out] key_list_p           - Array of basic key IDs
 * @param[in, out] key_count_p      - Number of elements in basic key array
 *                                    upon return will contain the actual number
 *                                    of elements copied to the array.
 *
 * @return SX_STATUS_SUCCESS            Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR        Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND    Key handle is not found in the database
 */
sx_status_t sx_api_acl_flex_key_get(const sx_api_handle_t   handle,
                                    const sx_acl_key_type_t key_handle,
                                    sx_acl_key_t           *key_list_p,
                                    uint32_t               *key_count_p);


/**
 * This API is used to add or remove an ACL rule from an ACL region. The user is responsible for memory management.
 * As such, it is necessary to initialize each member of rules_list_p using call to sx_lib_flex_acl_rule_init before
 * calling this API and de-initialize using call to sx_lib_flex_acl_rule_deinit after calling this API.
 * This operation configures the hardware if the ACL is bound to a device.
 * The configured rule will override the existing rule if present at the given offset with the new rule.
 * The keys specified in the rules_list must be a subset of the keys which were used to create the region.
 * A custom set of actions for each rule can also be defined.
 * If an offset in the offsets' array crosses the boundaries of the region, the API will return an error.
 * Only one of each of the following types of actions will be allowed within the same rule:
 *      - SX_FLEX_ACL_ACTION_FORWARD
 *      - SX_FLEX_ACL_ACTION_EGRESS_MIRROR or SX_FLEX_ACL_ACTION_MIRROR
 *      - SX_FLEX_ACL_ACTION_TRAP or SX_FLEX_ACL_ACTION_TRAP_W_USER_ID
 * Using multiple FORWARD or multiple MIRROR commands, or a combination where there is more than one of
 * any of the above will return PARAM_ERROR.
 *
 * Note: Rules cannot be added to an ACL region, if the ACL region is bound to an ACL that has
 * the SX_ACL_DIRECTION_MULTI_POINTS_E direction and the the ACL direction bitmap is not set.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - The access command SET/DELETE
 * @param[in] region_id             - ACL region ID received during region creation
 * @param[in] offsets_list_p        - Array of rule offsets
 * @param[in] rules_list_p          - Flexible rule content description
 * @param[in] rules_cnt             - Number of elements in array of flexible rule descriptors
 *
 *  @return SX_STATUS_SUCCESS           Operation completed successfully
 *  @return SX_STATUS_CMD_UNSUPPORTED   Sent command is unsupported
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 *  @return SX_STATUS_ENTRY_NOT_FOUND   Wrong region ID
 *  @return SX_STATUS_NO_RESOURCES      No more space for rules; cannot allocate space for all actions
 *
 */
sx_status_t sx_api_acl_flex_rules_set(const sx_api_handle_t          handle,
                                      const sx_access_cmd_t          cmd,
                                      const sx_acl_region_id_t       region_id,
                                      sx_acl_rule_offset_t          *offsets_list_p,
                                      const sx_flex_acl_flex_rule_t *rules_list_p,
                                      const uint32_t                 rules_cnt);


/**
 *
 * This API returns a list of rules associated with a particular region. The user is responsible for memory management.
 * As such, it is necessary to initialize each member of rules_list_p using call to sx_lib_flex_acl_rule_init before
 * calling this API and de-initialize using call to sx_lib_flex_acl_rule_deinit after calling this API.
 *
 * If the API is called with rules_list_p parameter set to NULL or *rules_cnt_p set to 0, it will return the actual number
 * of rules set to the region.
 *
 * If the API is called with key_desc_list_p and action_list_p parameter of each of the rules in rules_list_p set to NULL
 * and offset_list_p array filled with zeroes, it will return the actual number of keys and actions for each valid rule
 * starting from offset 0, as well as the rule's offset in offset_list_p for this rule.
 *
 * If the API is called with key_desc_list_p and action_list_p parameter of each of the rules in rules_list_p set to NULL,
 * but offset_list_p array is filled with non-zero values, it will return the actual number of keys and actions for each
 * valid rule according to the offset, which is defined in offset_list_p. In this case the offset list should be filled
 * with offsets of the rules which are valid.
 *
 * If the API is called with key_desc_list_p and action_list_p parameter of each of the rules in rules_list_p set to non-NULL,
 * it is assumed that rule structs are allocated for all rules in the list. It is also assumed that offset_list_p is filled
 * with real offsets of the rules in the same order as in the rules list.
 *
 * When calling the API, the key_desc_count and action_count of each sx_flex_acl_flex_rule_t should contain number of allocated
 * items. Upon API return, these parameters will contain actual number of items. The offset list should contain offsets of
 * valid rules only.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] region_id             - ACL region ID received during region creation
 * @param[in, out] offsets_list_p   - Array of rule offsets
 * @param[out] rules_list_p         - Flexible rule content description
 * @param[in, out] rules_cnt        - Desirable number of elements in array of flexible rule descriptors (API returns actual count)
 *
 *  @return SX_STATUS_SUCCESS           Operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   Wrong region ID
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 *
 */
sx_status_t sx_api_acl_flex_rules_get(const sx_api_handle_t    handle,
                                      const sx_acl_region_id_t region_id,
                                      sx_acl_rule_offset_t    *offsets_list_p,
                                      sx_flex_acl_flex_rule_t *rules_list_p,
                                      uint32_t               * rules_cnt_p);


/**
 * This API is used to bind/unbind an ACL or an ACL group to a RIF.
 * Binding more than one ACL to a RIF may be achieved by using ACL groups.
 *
 * BIND command is used for binding a single ACL or a single ACL group to a RIF.
 * UNBIND command clears RIF binding, even if there are multiple ACL groups bound to the RIF.
 * ADD command can be used to bind additional groups to the RIF. In this case, the order of group execution is determined
 * by the group priority, as set by sx_api_acl_group_attributes_set API.
 * DELETE command can be used to remove an ACL group from multiple ACL groups bound RIF.
 *
 * Note: ADD and DELETE commands support binding of ACL groups only.
 * Note: Binding or adding groups may fail if there are insufficient resources in hardware.
 * Note: An ACL that has the SX_ACL_DIRECTION_MULTI_POINTS_E direction cannot be bound to a RIF directly,
 * instead the user has to create an ACL group, add the ACL into it, and then bind this ACL group to a RIF.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - BIND/UNBIND/ADD/DELETE
 * @param[in] rif_id                - RIF ID
 * @param[in] acl_id                - ACL or ACL group ID
 *
 *  @return SX_STATUS_SUCCESS           Operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID or RIF ID not found in database
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 *  @return SX_STATUS_CMD_UNSUPPORTED   Given command is unsupported
 *  @return SX_STATUS_ERROR             Operation cannot be completed
 */
sx_status_t sx_api_acl_rif_bind_set(const sx_api_handle_t handle,
                                    const sx_access_cmd_t cmd,
                                    const sx_rif_id_t     rif_id,
                                    const sx_acl_id_t     acl_id);

/**
 * This API is used to get the ACL or ACL group ID that is bound to the RIF. When multiple ACLs are bound to the RIF,
 * this API will only return the one carrying the highest priority. To retrieve multiple bindings, it is recommended
 * to use the sx_api_acl_rif_bindings_get API instead.
 *
 * Note: The acl_direction cannot be set to the SX_ACL_DIRECTION_MULTI_POINTS_E direction.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] rif_id                  - RIF ID
 * @param[in] acl_direction           - The direction of ACL (ingress/egress)
 * @param[out] acl_id_p               - ACL or ACL group ID that is bound to RIF
 *
 *  @return SX_STATUS_SUCCESS               Operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND       ACL ID or RIF ID not found in database
 *  @return SX_STATUS_PARAM_ERROR           Invalid parameter
 */
sx_status_t sx_api_acl_rif_bind_get(const sx_api_handle_t    handle,
                                    const sx_rif_id_t        rif_id,
                                    const sx_acl_direction_t acl_direction,
                                    sx_acl_id_t             *acl_id_p);

/**
 * This API allows getting ACL IDs bound to a specific RIF. Since multiple groups may be bound to a RIF, the caller of
 * this API is responsible of providing a pre-allocated array for getting the ACL IDs and priority group.
 * If the API is called with acl_id_p parameter set to NULL or *acl_cnt_p set to 0, it will return the actual number
 * of ACL IDs bound to this RIF.
 *
 * Note: The acl_direction cannot be set to the SX_ACL_DIRECTION_MULTI_POINTS_E direction.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] rif_id         - RIF ID
 * @param[in] acl_direction  - ACL direction
 * @param[in,out] acl_id_p   - An array of ACL IDs (should be allocated by the caller)
 * @param[in,out] acl_cnt_p  - Specifies the maximum number of ACL IDs to retrieve
 *                             and returns the actual number of ACL IDs retrieved
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     RIF is not bound
 */
sx_status_t sx_api_acl_rif_bindings_get(const sx_api_handle_t    handle,
                                        const sx_rif_id_t        rif_id,
                                        const sx_acl_direction_t acl_direction,
                                        sx_acl_id_t             *acl_id_p,
                                        uint32_t                *acl_cnt_p);

/**
 * Upon ACL module initialization, the parallel ACL search type can be chosen. This API is used to support this feature by
 * linking one ACL group to another. Their relation could be described as "one directional linked list" where the second
 * group is next to the first one. Only the head of the list of groups is allowed to be bound to port/VLAN/RIF.
 * The other linked groups will be bound automatically. An attempt to bind explicitly any group besides the head will cause
 * an error. In parallel operation, the actions of the ACL are not applied immediately, so each ACL rule will act upon the
 * original packet.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - The command BIND/UNBIND
 * @param[in] parent_group_id           - The first, parent ACL or ACL group ID that second one will be bound to
 * @param[in] group_id                  - The second ACL or ACL group ID that will be bound to the first one
 *
 *  @return SX_STATUS_SUCCESS           Operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID not found in database
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 */
sx_status_t sx_api_acl_group_bind_set(sx_api_handle_t       handle,
                                      const sx_access_cmd_t cmd,
                                      sx_acl_id_t           group_id,
                                      sx_acl_id_t           next_group_id);

/**
 * This API returns the next ACL group bound to the given group.
 * This API is usually to be used when the ACL module was initialized to work in parallel mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] group_id               - The first, parent ACL or ACL group ID that second one was be bound to
 * @param[out] group_id_p            - The ACL or ACL group ID that bound to the parent. In case no such binding
 *                                      exists to the parent, an invalid ACL ID will be returned
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID not found in database
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 */
sx_status_t sx_api_acl_group_bind_get(sx_api_handle_t handle,
                                      sx_acl_id_t     group_id,
                                      sx_acl_id_t   * group_id_p);

/**
 * The API is used to manipulate a port list container.
 *
 * CREATE creates a new container with the specified list of logical/tunnel ports and returns its new container ID in port_list_id_p.
 * SET replaces the contents of an existing container specified by port_list_id_p with the specified list of logical/tunnel ports
 * in port_list_p.
 * DESTROY deletes an existing container specified by port_list_id_p.
 *
 * Note: A port list in use (e.g., by an ACL key) cannot be destroyed or modified.
 * Note: A container may contain, at most, RM_API_ACL_PORT_LIST_MAX logical ports.
 * Note: A container may contain either Ethernet logical ports or Tunnel logical ports but not both. LAG ports are not supported.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - CREATE/SET/DESTROY
 * @param[in] port_list_p        - Specifies or returns the container ID
 * @param[in] port_list_cnt      - Specifies the list of logical ports for the container
 * @param[in/out] port_list_id_p - specifies the ID of the port list created/to change
 *
 * @return SX_STATUS_SUCCESS                                                             Operation completed successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE  Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                     Specified container ID does not exist
 * @return SX_STATUS_NO_RESOURCES                                                        There are no resources for the operation
 * @return SX_STATUS_RESOURCE_IN_USE                                                     Group is in use and cannot be destroyed
 */
sx_status_t sx_api_acl_port_list_set(const sx_api_handle_t     handle,
                                     const sx_access_cmd_t     cmd,
                                     sx_acl_port_list_entry_t *port_list_p,
                                     const uint32_t            port_list_cnt,
                                     sx_acl_port_list_id_t    *port_list_id_p);

/**
 * Retrieve information about a port list container specified by port_list_id.
 *
 * Note: *port_list_cnt should contain the maximum amount of logical ports to retrieve.
 * Note: If port_list_p is NULL, then port_list_p are not retrieved at all.
 *       In this case, port_list_cnt  will contain the actual number if ports in the port list.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] port_list_id         - Specifies the ID of the port list to retrieve
 * @param[out] port_list_p         - Array of ports to copy into
 * @param[in,out] port_list_cnt_p  - Specifies the maximum amount of logical ports to retrieve and returns the amount logical ports retrieved
 *
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_CMD_UNSUPPORTED                                                      Access command is not supported
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                      Specified container does not exist or
 *                                                                                        there are no more containers
 */
sx_status_t sx_api_acl_port_list_get(const sx_api_handle_t       handle,
                                     const sx_acl_port_list_id_t port_list_id,
                                     sx_acl_port_list_entry_t   *port_list_p,
                                     uint32_t                   *port_list_cnt_p);


/**
 * This API is used to get ACL region hardware size.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] region_id       - ACL region ID
 * @param[out] region_size_p  - The actual region hardware size
 *
 *
 * @return SX_STATUS_SUCCESS                                                              Operation completed successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND                                                      Entry is not found in database
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE   Any input parameter is invalid
 *
 */
sx_status_t sx_api_acl_region_hw_size_get(const sx_api_handle_t    handle,
                                          const sx_acl_region_id_t region_id,
                                          sx_acl_size_t           *region_size_p);


/**
 * This API creates and deletes a Custom Bytes Set. Currently only 4-bytes sets are supported.
 * Returned value is a set of key IDs from sx_acl_key_t space.
 * Each byte in the custom bytes set is accessed as a separate ACL key in the FLEX_ACL_CUSTOM_BYTES_START
 * to FLEX_ACL_CYSTOM_BYTE_LAST range.
 * The custom bytes extraction points are a predefined set of extraction points based on the protocol of interest.
 * The key IDs returned by this API can then be used to create a Flex ACL key.
 *
 * CREATE should have an array of SDK key IDs provided. If the first key ID in the list is zero (FLEX_ACL_KEY_INVALID)
 *  or any other value not in the range FLEX_ACL_KEY_CUSTOM_BYTES_START to FLEX_ACL_KEY_CUSTOM_BYTES_LAST,
 *  the custom bytes set is allocated by the software as the first free one. If the first key ID in the list belongs to
 *  the range FLEX_ACL_KEY_CUSTOM_BYTES_START to FLEX_ACL_KEY_CUSTOM_BYTES_LAST, it identifies the custom bytes that were
 *  set to be allocated. If the custom bytes set is already allocated, the software allocates the first free set.
 *  For example, key IDs which were allocated once and destroyed afterwards may be submitted to the CREATE operation in order
 *  to get the same key IDs in case they are still free.
 * DESTROY only uses the first key to identify the destroyed set.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                            - SX-API handle
 * @param[in] cmd                               - CREATE/DESTROY/EDIT
 * @param[in] custom_bytes_set_attributes       - Specifies extraction points data
 * @param[in/out] custom_bytes_set_key_id_p     - Specifies an array of the custom bytes key ID
 * @param[in/out] custom_bytes_set_key_id_cnt_p - Specifies how many custom bytes are expected by the user.
 *                                                The counter is updated with the smaller of the available
 *                                                number of bytes in allocated set and requested number of bytes.
 *
 * @return SX_STATUS_SUCCESS             Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR         Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND     Specified container ID does not exist
 * @return SX_STATUS_NO_RESOURCES        No resources for the operation
 * @return SX_STATUS_RESOURCE_IN_USE     Group is in use and cannot be destroyed
 */
sx_status_t sx_api_acl_custom_bytes_set(sx_api_handle_t                             handle,
                                        sx_access_cmd_t                             cmd,
                                        const sx_acl_custom_bytes_set_attributes_t *custom_bytes_set_attributes,
                                        sx_acl_key_t                               *custom_bytes_set_key_id_p,
                                        uint32_t                                   *custom_bytes_set_key_id_cnt_p);

/**
 *
 * This API returns extraction point parameters of the existing custom bytes set.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                                     - SX-API handle
 * @param[in] custom_bytes_set_key_id_p                  - Specifies an array of the custom bytes key's ID (only the first item in the array is provided)
 * @param[out] custom_bytes_key_extraction_point_list_p  - Specifies extraction points of fetched data
 *
 * @return SX_STATUS_SUCCESS                Operation completed successfully
 * @return SX_STATUS_CMD_UNSUPPORTED        Access command is not supported
 * @return SX_STATUS_PARAM_ERROR            Any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND        Specified container does not exist or there are no more containers
 */
sx_status_t sx_api_acl_custom_bytes_get(sx_api_handle_t                       handle,
                                        sx_acl_key_t                         *custom_bytes_set_key_id_p,
                                        sx_acl_custom_bytes_set_attributes_t *custom_bytes_set_attributes_p);

/**
 * This API adds/edits/deletes a policy based ILM (PBILM). PBILM entry can be later bound to an ACL rule in order to specify
 * an MPLS ECMP that will encapsulate the packet with MPLS labels and send it to RIF. It can also send the frame to IP
 * or ILM lookup.
 *
 * CREATE is used to create a PBILM entry which can be changed when needed by SET (operation may fail if no hardware resources are available).
 * DESTROY is used to remove the PBILM.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - CREATE/SET/DESTROY
 * @param[in] pbilm_entry           - PBILM attributes
 * @param[in,out] pbilm_id          - Port range comparison ID
 *
 * @return SX_STATUS_SUCCESS                                  Operation completed successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_ERROR      Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                          Element is not found in database
 * @return SX_STATUS_NO_RESOURCES                             No hardware resources for PBILM creation
 * @return SX_STATUS_RESOURCE_IN_USE                          The PBILM record is in use
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO                    Hardware failure
 * @return SX_STATUS_CMD_UNSUPPORTED                          Command is unsupported
 * @return SX_STATUS_INVALID_HANDLE                           Invalid handle error
 */
sx_status_t sx_api_acl_policy_based_ilm_set(const sx_api_handle_t       handle,
                                            const sx_access_cmd_t       cmd,
                                            const sx_acl_pbilm_entry_t *pbilm_entry_p,
                                            sx_acl_pbilm_id_t          *pbilm_id_p);

/**
 * This API is used to get a PBILM set or to count ports of a PBILM set. Ensure that the pbilm_entry is preallocated with the
 * maximum number of ports to be retrieved.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] pbilm_id          - PBILM entry ID
 * @param[out] pbilm_entry      - PBILM attributes
 *
 * @return SX_STATUS_SUCCESS                                Operation completed successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_ERROR    Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                        ACL element is not found in database
 * @return SX_STATUS_CMD_UNSUPPORTED                        Supplied command is unsupported
 * @return SX_STATUS_INVALID_HANDLE                         Invalid handle error
 */
sx_status_t sx_api_acl_policy_based_ilm_get(const sx_api_handle_t   handle,
                                            const sx_acl_pbilm_id_t pbilm_id,
                                            sx_acl_pbilm_entry_t   *pbilm_entry_p);

/**
 * This API is used for updating a set of priorities in the range (min_priority to max_priority) to priority + priority_change.
 *
 * Note:The priority can be changed only if there is no other rules between min priority + change to max priority + change
 * (and the opposite if the priority_change < 0 ).
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] region_id        - ACL region ID
 * @param[in] min_priority     - Minimum priority in the range
 * @param[in] max_priority     - Maximum priority in the range
 * @param[in] priority_change  - The offset by which the priority should be changed (can be positive/negative)
 *
 * @return SX_STATUS_SUCCESS                                            Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE       Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND                                    ACL element is not found in database
 */
sx_status_t sx_api_acl_flex_rules_priority_set(const sx_api_handle_t             handle,
                                               const sx_acl_region_id_t          region_id,
                                               const sx_flex_acl_rule_priority_t min_priority,
                                               const sx_flex_acl_rule_priority_t max_priority,
                                               const int32_t                     priority_change);

/**
 * This API triggers a notification of ACL rules activity.
 * The application can listen for the SX_TRAP_ID_ACL_ACTIVITY Trap to get the data.
 * The application can get multiple trap events per a notification procedure.
 * If entry_cnt in trap event is 0, means it's the end of this notification procedure.
 * If DDD is enabled, region id filtering is not allowed. In this case,
 * will return SX_STATUS_PARAM_ERROR if filter_by_region_id is valid in activity_attr_p.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - READ/READ_CLEAR
 * @param[in] activity_attr     - Activity notifier attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if parameter is invalid
 * @return SX_STATUS_RESOURCE_IN_USE if a notification procedure is already running.
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_acl_activity_notify(const sx_api_handle_t                     handle,
                                       const sx_access_cmd_t                     cmd,
                                       const sx_flex_acl_activity_notify_attr_t *activity_attr_p);

#endif /* ifndef __SX_API_ACL_H__ */
