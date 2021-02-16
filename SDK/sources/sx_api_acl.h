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

#ifndef __SX_API_ACL_H__
#define __SX_API_ACL_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_acl.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of the ACL MODULE
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - ACL module verbosity level
 * @param[in] api_verbosity_level      - ACL API verbosity level
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_acl_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of the ACL MODULE
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - ACL module verbosity level
 * @param[out] api_verbosity_level_p    - ACL API verbosity level
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_acl_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This function is used to create an ACL Region (rules list).
 *  CREATE is used to create a new region and takes as input the key_type and region size. Region ID is returned
 *  on successful creation.
 *  DESTORY is used to destroy an existing region. It is required that the ACL region is not bound to any ACL rules.
 *  EDIT command is used for resizing an existing ACL region. acl_region_id and new size should be provided.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE / DESTROY / EDIT
 * @param[in] key_type - key type used in this ACL. Should be created using sx_api_acl_flex_key_set
 * @param[in] action_type - This parameter should be set to zero. Irrelevant for current ACL implementation.
 * @param[in] acl_size - maximum number of rules in this ACL
 * @param[in,out] region_id_p - ACL region ID as described above
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no resources are available to create the region
 * @return SX_STATUS_CMD_UNSUPPORTED if the supplied command is unsupported
 */
sx_status_t sx_api_acl_region_set(const sx_api_handle_t      handle,
                                  const sx_access_cmd_t      cmd,
                                  const sx_acl_key_type_t    key_type,
                                  const sx_acl_action_type_t action_type,
                                  const sx_acl_size_t        region_size,
                                  sx_acl_region_id_t        *region_id_p);

/**
 *  This function is used to get an ACL region's properties.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] region_id - ACL region ID
 * @param[out] key_type_p - key type used in this ACL region
 * @param[out] action_type_p - This parameter is ignored. will be set to 0.
 * @param[out] region_size_p - maximum number of rules in this
 *       ACL region
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is  not found in DB
 */
sx_status_t sx_api_acl_region_get(const sx_api_handle_t    handle,
                                  const sx_acl_region_id_t region_id,
                                  sx_acl_key_type_t       *key_type_p,
                                  sx_acl_action_type_t    *action_type_p,
                                  sx_acl_size_t           *region_size_p);

/**
 *
 *  This function is used to create a single region ACL.
 *  CREATE command is used for creating a new ACL, it will return an ACL ID on success.
 *  DESTROY command may be used to destroy the ACL when it is not bound to HW.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE / DESTROY
 * @param[in] acl_type - ACL type of this ACL (only AGNOSTIC type is currently supported)
 * @param[in] acl_direction - ACL direction (ingress or egress port or ingress or egress RIF ACL)
 * @param[in] acl_region_group_p - ACL region group matching ACL type
 * @param[in,out] acl_id_p - ACL ID as described above
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no HW resources are available to create the ACL
 * @return SX_STATUS_CMD_UNSUPPORTED if the supplied command is unsupported
 */
sx_status_t sx_api_acl_set(const sx_api_handle_t        handle,
                           const sx_access_cmd_t        cmd,
                           const sx_acl_type_t          acl_type,
                           const sx_acl_direction_t     acl_direction,
                           const sx_acl_region_group_t *acl_region_group_p,
                           sx_acl_id_t                 *acl_id_p);

/**
 *  This function is used to get an ACL's attributes. It takes as input
 *  an ACL ID and returns the attributes of that ACL i.e. type and a
 *  list of attached regions. The length of the regions list
 *  depends on the ACL type.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] acl_id - ACL ID
 * @param[out] acl_type_p - ACL type (packet agnostic or packet sensitive)
 * @param[out] acl_direction_p - ACL direction
 * @param[out] acl_region_group_p - ACL region group attached to the ACL
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 *  not found in DB
 */
sx_status_t sx_api_acl_get(const sx_api_handle_t  handle,
                           const sx_acl_id_t      acl_id,
                           sx_acl_type_t         *acl_type_p,
                           sx_acl_direction_t    *acl_direction_p,
                           sx_acl_region_group_t *acl_region_group_p);

/**
 *  This function gets a list of valid ACL IDs.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd    GET/GET_NEXT/GET_FIRST
 * @param[in] acl_id_key - ACL ID to use and key.
 * @param[in] acl_filter_p - Filter to use (not supported yet)
 * @param[out] acl_id_list_p - pointer to the list of ACL IDs returned.
 * @param[in,out] acl_id_cnt_p [in] number of entries to retrieve (max 400); [out] retrieved  number of entries.
 *
 * Input/Output types
 *      - Get first - Get a list of first n entries.  Cmd should be SX_ACCESS_CMD_GET_FIRST and
 *           count should be equal to n. key is irrelevant in this case. Returns number of
 *           entries retrieved as count
 *      -  Get next  - Get n entries after a specified key (it does not have to exist).
 *           Cmd should be SX_ACCESS_CMD_GETNEXT. count should be equal to n.
 *           Returns number of entries retrieved as count
 *      - Get - Gets a specific entry. Cmd should be SX_ACCESS_CMD_GET and count should be 1.
 *       If input count is 0, then returns a count of ACL Ids as output instead.
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any parameter is in error.
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_INVALID_HANDLE if handle in invalid
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_acl_iter_get(const sx_api_handle_t  handle,
                                const sx_access_cmd_t  cmd,
                                const sx_acl_id_t      acl_id_key,
                                const sx_acl_filter_t *acl_filter_p,
                                sx_acl_id_t           *acl_id_list_p,
                                uint32_t              *acl_id_cnt_p);
/**
 *
 *  This function is used to set the attributes of an ACL.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET
 * @param[in] acl_id - ACL ID
 * @param[in] acl_attributes - ACL attributes
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 */
sx_status_t sx_api_acl_attributes_set(const sx_api_handle_t     handle,
                                      const sx_access_cmd_t     cmd,
                                      const sx_acl_id_t         acl_id,
                                      const sx_acl_attributes_t acl_attributes);

/**
 *
 *  This function is used to retrieve the attributes of a given ACL.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] acl_id - ACL ID
 * @param[in,out] acl_attributes_p - returned ACL attributes.
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_NULL if any input parameter is invalid
 */
sx_status_t sx_api_acl_attributes_get(const sx_api_handle_t      handle,
                                      const sx_acl_id_t          acl_id,
                                      const sx_acl_attributes_t *acl_attributes_p);

/**
 *
 *  This function is used to set certain global attributes of the ACL Module.
 *  Note that enabling certain functionality may require enabling both the global and individual
 *  attributes. Use sx_api_acl_attributes_set for setting individual attributes.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET
 * @param[in] global_acl_attributes - Global ACL attributes .
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 */
sx_status_t sx_api_acl_global_attributes_set(const sx_api_handle_t            handle,
                                             const sx_access_cmd_t            cmd,
                                             const sx_acl_global_attributes_t global_acl_attributes);

/**
 *
 *  This function is used to retrieve the global attributes of the ACL Module.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[out] global_acl_attributes_p - returned global ACL attributes.
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_NULL if any input parameter is invalid
 */
sx_status_t sx_api_acl_global_attributes_get(const sx_api_handle_t             handle,
                                             const sx_acl_global_attributes_t *global_acl_attributes_p);

/**
 *
 *  This function is used for controlling a group of ACLs or in
 *  other words cascaded ACL blocks up to the size of  SX_ACL_MAX_ACL_GROUP_SIZE.
 *  CREATE is used to create a new group with a specified group direction, returns new Group ID
 *  SET is used to add a list of ACLs to the group. The ACLs need to be in the same direction as the Group.
 *  DESTROY is used to destroy the ACL group. This can be done only if the ACL group is not bound to HW.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE / SET / DESTROY
 * @param[in] acl_direction - ACL group direction. All ACLs in this group must have the same direction
 * @param[in] acl_id_list_p - ordered list of ACL IDs. Ignored when CMD=CREATE or CMD=DESTROY.
 * @param[in] acl_id_cnt - number of elements in the list of ACL IDs. Ignored when CMD=CREATE or CMD=DESTROY.
 * @param[in,out] group_id - ACL group ID
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no resources are available to create the new Group
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 */
sx_status_t sx_api_acl_group_set(const sx_api_handle_t    handle,
                                 const sx_access_cmd_t    cmd,
                                 const sx_acl_direction_t acl_direction,
                                 const sx_acl_id_t       *acl_id_list_p,
                                 const uint32_t           acl_id_cnt,
                                 sx_acl_id_t             *group_id_p);

/**
 *
 *  This function is used to get the properties of a provided group id. If
 *  the supplied acl_id_count is 0, it just retrieves a count of the ACLs.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] group_id - ACL group ID
 * @param[out] acl_direction - ACL direction
 * @param[out] acl_id_list_p - list of the group ACL IDs.
 * @param[in,out] acl_id_cnt_p - In - size of the ACL IDs array, OUT - number of valid ACL IDs.
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 *
 */
sx_status_t sx_api_acl_group_get(const sx_api_handle_t handle,
                                 const sx_acl_id_t     group_id,
                                 sx_acl_direction_t   *acl_direction_p,
                                 sx_acl_id_t          *acl_id_list_p,
                                 uint32_t             *acl_id_cnt_p);

/**
 *  This function gets a list of valid ACL Group Ids.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd    GET/GET_NEXT/GET_FIRST
 * @param[in] group_id_key - ACL Group ID to use as Key for GET and GET_NEXT commands.
 * @param[in] acl_filter_p - Filter to use (not supported yet)
 * @param[out] acl_id_list_p - pointer to the list of valid ACL Group IDs returned.
 * @param[in,out] acl_id_cnt_p [in] number of entries to retrieve (max 400); [out] retrieved  number of entries.
 *
 * Input/Output types
 *      - Get first - Get a list of first n entries.  Cmd should be SX_ACCESS_CMD_GET_FIRST and
 *           count should be equal to n. key is irrelevant in this case. Returns number of
 *           entries retrieved as count
 *      -  Get next  - Get n entries after a specified key (it does not have to exist).
 *           Cmd should be SX_ACCESS_CMD_GETNEXT. count should be equal to n.
 *           Returns number of entries retrieved as count
 *      - Get - Gets a specific entry. Cmd should be SX_ACCESS_CMD_GET and count should be 1.
 *       If input count is 0, then returns a count of ACL Group Ids as output instead.
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any parameter is in error.
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_INVALID_HANDLE if handle in invalid
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_acl_group_iter_get(const sx_api_handle_t  handle,
                                      const sx_access_cmd_t  cmd,
                                      const sx_acl_id_t      group_id_key,
                                      const sx_acl_filter_t *acl_filter_p,
                                      sx_acl_id_t           *acl_id_list_p,
                                      uint32_t              *acl_id_cnt_p);

/**
 *
 *  This function is used to set the attributes of an ACL Group.
 *  After the ACL group is created by sx_api_acl_group_set API, it is possible to set
 *  a priority to the ACL group. The default group priority is FLEX_ACL_GROUP_PRIORITY_DEFAULT.
 *  When binding multiple ACL groups to a port, the groups will be ordered according to their priority.
 *  Setting priority to a group that is already bound does not take effect on previously
 *  bound groups.
 *
 *  Priority attribute limitations:
 *  Priority values range is FLEX_ACL_GROUP_PRIORITY_MIN to FLEX_ACL_GROUP_PRIORITY_MAX.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET
 * @param[in] acl_group_id - ACL Group ID
 * @param[in] acl_group_attr_p -  ACL group attributes pointer.
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 * @return SX_STATUS_ERROR general error
 *
 */
sx_status_t sx_api_acl_group_attributes_set(const sx_api_handle_t            handle,
                                            const sx_access_cmd_t            cmd,
                                            const sx_acl_id_t                acl_group_id,
                                            const sx_acl_group_attributes_t *acl_group_attr_p);

/**
 *
 *  This function is used to get the attributes of a given ACL Group
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] acl_group_id - ACL group ID
 * @param[out] acl_group_attr_p - ACL group attributes
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 *
 */
sx_status_t sx_api_acl_group_attributes_get(const sx_api_handle_t            handle,
                                            const sx_acl_id_t                group_id,
                                            const sx_acl_group_attributes_t *acl_group_attr_p);


/**
 *  This function adds/edits/deletes a policy based switching
 *  (PBS) set . Policy based switching entry can be later bound
 *  to an ACL rule in order to specify destination port/port
 *  group (multicast) or send the frame to the router block. Use
 *  ADD command to create a PBS entry. Note that this operation
 *  may fail if no HW resources are available. PBS entry can be
 *  created without ports in order to ensure future HW resource
 *  availability. Use ADD_PORTS and DELETE_PORTS to edit an existing
 *  PBS entry and add or delete ports. Note that an unicast
 *  entry can have only 1 port. Use DELETE command to clear a PBS
 *  record (not allowed when this record is in use by ACL rules)
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD / ADD_PORTS / DELETE_PORTS / DELETE
 * @param[in] pbs_entry - struct for PBS attributes
 * @param[in,out] pbs_id - PBS ID
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if element is not found in DB
 * @return  SX_STATUS_NO_RESOURCES if there are no HW resources for PBS creation
 * @return SX_STATUS_RESOURCE_IN_USE if the PBS record is in use
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_policy_based_switching_set(const sx_api_handle_t     handle,
                                                  const sx_access_cmd_t     cmd,
                                                  const sx_swid_t           swid,
                                                  const sx_acl_pbs_entry_t *pbs_entry_p,
                                                  sx_acl_pbs_id_t          *pbs_id_p);

/**
 *  This function is used to get a PBS set or to count the number
 *  of ports in a PBS set. Note that for GET command the pbs_entry.log_ports
 *  should be pre-allocated and the pbs_entry.port_num should be
 *  set to the maximum number of ports to retrieve.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - COUNT / GET
 * @param[in] swid - SWID of the PBS entry
 * @param[in] pbs_id - Port based switching entry ID
 * @param[in,out] pbs_entry - struct for Policy based switching
 *       entry attributes. IN - max port number to retrieve. OUT
 *       - actual number of ports retrieved.
 *
 * @return SX_STATUS_SUCCESS if the operation completes
 *          successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *         requested
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_policy_based_switching_get(const sx_api_handle_t handle,
                                                  const sx_access_cmd_t cmd,
                                                  const sx_swid_t       swid,
                                                  const sx_acl_pbs_id_t pbs_id,
                                                  sx_acl_pbs_entry_t   *pbs_entry_p);

/**
 *  This function adds/edits/deletes a Layer 4 port range comparison set (up to SX_ACL_MAX_PORT_RANGES).
 *  Note: SX_ACL_PORT_RANGE_IP_HEADER_BOTH option for IP header type is not supported by Spectrum2, Spectrum3.
 *  ADD command is used to create a new range ID from the supplied port range.
 *  EDIT command is used to update the port range of the supplied range ID
 *  DELETE command is used to clear the range configuration. This will fail
 *  if the range is being used by an ACL.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD / EDIT / DELETE
 * @param[in] l4_port_range - struct for Layer 4 port range comparison
 * @param[in, out] range_id - Port range comparison ID
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if the supplied command is unsupported
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_l4_port_range_set(const sx_api_handle_t            handle,
                                         const sx_access_cmd_t            cmd,
                                         const sx_acl_port_range_entry_t *l4_port_range_p,
                                         sx_acl_port_range_id_t          *range_id_p);

/**
 *  This function is used to get the properties of a Layer 4 port range comparison set.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] range_id - Port range comparison ID
 * @param[out] l4_port_range - struct for Layer 4 port range comparison
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */

sx_status_t sx_api_acl_l4_port_range_get(const sx_api_handle_t        handle,
                                         const sx_acl_port_range_id_t range_id,
                                         sx_acl_port_range_entry_t   *l4_port_range_p);

/**
 *  This function gets a list of ACL L4 Port Range IDs
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 * @param[in] handle - SX-API handle.
 * @param[in] cmd    GET/GET_NEXT/GET_FIRST
 * @param[in] range_id_key -Range ID to use as Key for GET and GET_NEXT commands.
 * @param[in] range_id_filter_p - Filter to use (not supported yet)
 * @param[out] range_id_list_p - pointer to the list of Range IDs returned.
 * @param[in,out] range_id_cnt_p [in] number of entries to retrieve (max 16); [out] retrieved  number of entries.
 *
 * Input/Output types
 *      - Get first - Get a list of first n entries.  Cmd should be SX_ACCESS_CMD_GET_FIRST and
 *           count should be equal to n. key is irrelevant in this case. Returns number of
 *           entries retrieved as count
 *      -  Get next  - Get n entries after a specified key (it does not have to exist).
 *           Cmd should be SX_ACCESS_CMD_GETNEXT. count should be equal to n.
 *           Returns number of entries retrieved as count
 *      - Get - Gets a specific entry. Cmd should be SX_ACCESS_CMD_GET and count should be 1.
 *       If input count is 0, then returns a count of Range Ids as output instead.
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any parameter is in error.
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_INVALID_HANDLE if handle in invalid
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_acl_l4_port_range_iter_get(const sx_api_handle_t             handle,
                                              const sx_access_cmd_t             cmd,
                                              const sx_acl_port_range_id_t      range_id_key,
                                              const sx_acl_port_range_filter_t *range_id_filter_p,
                                              sx_acl_port_range_id_t           *range_id_list_p,
                                              uint32_t                         *range_id_cnt_p);

/**
 *  This function adds/edits/deletes a range comparison set (up to SX_ACL_MAX_PORT_RANGES).
 *  Supported devices: Spectrum2, Spectrum3.
 *  Supported range comparisons: L4 Port, IP length, TTL, Custom Bytes and UTC.
 *  Note: SX_ACL_PORT_RANGE_IP_HEADER_BOTH option for IP header type is not supported by Spectrum2, Spectrum3.
 *  Note: At a given time no more than 2 Custom Bytes ranges can be used.
 *  When ADD command is used the given ranges are written into a group and its ID is returned.
 *  When EDIT command is used the given range is written into a group of range_index.
 *  When DELETE command is used the given range_index configuration is cleared.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD / EDIT / DELETE
 * @param[in] range_entry_p - struct for range comparison
 * @param[in, out] range_id - range comparison ID
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation
 * @return SX_STATUS_RESOURCE_IN_USE if range is in use and cannot be deleted
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_range_set(const sx_api_handle_t       handle,
                                 const sx_access_cmd_t       cmd,
                                 const sx_acl_range_entry_t *range_entry_p,
                                 sx_acl_port_range_id_t     *range_id_p);

/**
 *  This function is used to get a range comparison set.
 *  Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] range_id - range comparison ID
 * @param[out] range_entry_p - struct for range comparison
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_range_get(const sx_api_handle_t        handle,
                                 const sx_acl_port_range_id_t range_id,
                                 sx_acl_range_entry_t        *range_entry_p);

/**
 *  \deprecated This API is deprecated and will be removed in the future. Please use sx_api_acl_flex_rules_set in its place.
 *
 *  This function is used for inserting rules into an ACL
 *  region. Inserting rules is allowed before and after bind
 *  operation. Rule is inserted to an explicit offset,
 *  overriding existing rule on that offset. Rules must have the
 *  same key type as the ACL region.
 *  Supported devices: SwitchX, SwitchX2.
 *
 *  When in 802.1D mode, instead of providing a vid(Vlan ID) in
 *  rules[].key.fields.key_type.vid (if present in the key_type) and
 *  rules[].mask.fields.key_type.vid (if present) and
 *  rules[].action.basic_action.vid (if present),
 *  you should provide a bridge_id.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET / DELETE
 * @param[in] region_id - ACL region ID
 * @param[in] rules_p - array of structs representing rule
 *       content. should be in size of num_of_rules
 * @param[in] num_of_rules - number of rules to configure
 *       (number of elements in the array)
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if there is no more space for rules
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 */
sx_status_t sx_api_acl_rules_set(const sx_api_handle_t    handle,
                                 const sx_access_cmd_t    cmd,
                                 const sx_acl_region_id_t region_id,
                                 const sx_acl_rule_t     *rules_list_p,
                                 const uint32_t           rules_cnt);

/**
 * \deprecated This API is deprecated and will be removed in the future. Please use sx_api_acl_flex_rules_get in its place.
 *
 *  This function is used for getting rules of an ACL block.
 *
 *  When in 802.1D mode, instead of receiving a vid(Vlan ID),
 *  on rules[].key.fields.key_type.vid, rules[].mask.fields.key_type.vid and
 *  rules[].action.basic_action.vid, a bridge_id's are provided.
 *  Supported devices: SwitchX, SwitchX2.
 *
 * @param[in] handle - SX-API handle
 * @param[in] region_id - ACL region ID
 * @param[in] start_offset - Start offset within the region
 * @param[out] rules_p - pointer to array of structs
 *       representing rule content. should be in size of
 *       num_of_rules.
 * @param[in,out] num_of_rules - IN - number of rules to
 *       get (number of elements in the array), OUT - number of
 *       rules that were actually read from ACL table
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure requested
 */
sx_status_t sx_api_acl_rules_get(const sx_api_handle_t      handle,
                                 const sx_acl_region_id_t   region_id,
                                 const sx_acl_rule_offset_t start_offset,
                                 sx_acl_rule_t             *rules_list_p,
                                 uint32_t                  *rules_cnt_p);

/**
 *  This function is used for getting and/or clearing the activity of a specific rule.
 *  If the region is not bound, activity_p is invalid.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - READ / READ_CLEAR
 * @param[in] region_id - ACL region ID
 * @param[in] rule_offset - ACL Rule offset within the region
 * @param[out] activity_p - ACL Rule activity
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 */
sx_status_t sx_api_acl_rule_activity_get(const sx_api_handle_t      handle,
                                         const sx_access_cmd_t      cmd,
                                         const sx_acl_region_id_t   region_id,
                                         const sx_acl_rule_offset_t rule_offset,
                                         boolean_t                 *activity_p);

/**
 *  This function is used for moving a block of rules within an
 *  ACL region. Moving is allowed before and after ACL bind.
 *  Moving a block does not affect search hits, but may override
 *  existing rules if such exist on the new block location.
 *  Non-valid rules within the block are moved as well.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] region_id - ACL region ID
 * @param[in] block_start - Rules block start offset within the
 *       ACL block
 * @param[in] block_size - Number of rules to move within the
 *       block
 * @param[in] new_block_start - New offset of the first rule of
 *       the given rules block
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 */
sx_status_t sx_api_acl_rule_block_move_set(const sx_api_handle_t      handle,
                                           const sx_acl_region_id_t   region_id,
                                           const sx_acl_rule_offset_t block_start,
                                           const sx_acl_size_t        block_size,
                                           const sx_acl_rule_offset_t new_block_start);

/**
 *  This function is used to bind/unbind an ACL or an ACL group to a
 *  port (or LAG). Binding more than one ACL to port may be achieved by using
 *  ACL groups.
 *  BIND command is used for binding a single ACL or a single ACL group to a port.
 *  UNBIND command will clear port binding, even if there are multiple ACL groups
 *  which are bound to the port.
 *  ADD command can be used to bind additional ACL groups (not ACLs) to the port. In this case
 *  the order of group execution is determined by the group priority,
 *  set by sx_api_acl_group_attributes_set API.
 *  DELETE command can be used to remove an ACL group from multiple ACL groups
 *  bound to the port/LAG.
 *
 *  Binding to L2 tunnel ports is supported in this API as well.
 *  Spectrum supports NVE port binding by providing the NVE logical port.
 *  Spectrum support is a virtual binding to the NVE decap table, where ADD and DELETE commands are not supported.
 *  Spectrum2 support for L2 tunnel port binding has API support like any other port binding.
 *  In order to bind L2 tunnel port, the appropriate logical port and an ACL group with one of the directions
 *  SX_ACL_DIRECTION_TPORT_INGRESS or SX_ACL_DIRECTION_TPORT_EGRESS should be provided.
 *
 *  Note: ADD and DELETE commands support binding of ACL groups only.
 *        Binding or adding groups may fail if there are insufficient resources in HW.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND / UNBIND / ADD / DELETE
 * @param[in] log_port - logical port ID to bind
 * @param[in] acl_id - ACL ID given for ACL or ACL group
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no resources are available for the operation.
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 */
sx_status_t sx_api_acl_port_bind_set(const sx_api_handle_t  handle,
                                     const sx_access_cmd_t  cmd,
                                     const sx_port_log_id_t log_port,
                                     const sx_acl_id_t      acl_id);

/**
 *  This function is used to get the ACL ID of an ACL table or
 *  ACL group which is bound to a specific port
 *  When multiple groups are bound to a port, this API will return the highest
 *  priority group. To retrieve multiple bindings it is suggested to use the
 *  sx_api_acl_port_bindings_get API instead.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] acl_direction - ingress or egress ACL
 * @param[out] acl_id_p - ACL ID of an ACL or ACL group
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if port is not bound
 */
sx_status_t sx_api_acl_port_bind_get(const sx_api_handle_t    handle,
                                     const sx_port_log_id_t   log_port,
                                     const sx_acl_direction_t acl_direction,
                                     sx_acl_id_t             *acl_id_p);

/**
 *  This API is used to retrieve the ACL IDs/groups bound to a specific port.
 *  Since multiple groups may bound to a port, the caller of this API
 *  is responsible of providing an allocated array for getting the ACL IDs.
 *
 *  If the API is called with acl_id_p parameter set to NULL or *acl_cnt_p set to 0, it
 *  will return the actual number of ACL IDs bound to this port.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] acl_direction - ACL direction
 * @param[in,out] acl_id_p - An array of ACL IDs, should be allocated by the caller.
 * @param[in,out] acl_cnt_p - Specifies the maximum amount of ACL IDs to retrieve,
 *                            and returns the actual number of ACL IDs retrieved.
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if port is not bound
 */
sx_status_t sx_api_acl_port_bindings_get(const sx_api_handle_t    handle,
                                         const sx_port_log_id_t   log_port,
                                         const sx_acl_direction_t acl_direction,
                                         sx_acl_id_t             *acl_id_p,
                                         uint32_t                *acl_cnt_p);

/**
 *  This function is used for controlling mapping of vlans into
 *  vlan groups for ACL binding.
 *  CREATE command used for creating a new group, will return a
 *  free group ID
 *  ADD / DELETE commands are used to control mapping of SWID,VID to an existing vlan group
 *  DESTROY command is used to free a vlan group resource
 *
 *  Note: This function is only valid when in 802.1Q mode.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE / ADD / DELETE / DESTROY
 * @param[in] swid - SWID (used only with ADD/DELETE)
 * @param[in,out] group_id - vlan group ID
 * @param[in] vlan_list - a list of vlans to attach to this  group
 * @param[in] vlan_num - number of elements in the vlan list
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no resources are available
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 */
sx_status_t sx_api_acl_vlan_group_map_set(const sx_api_handle_t handle,
                                          const sx_access_cmd_t cmd,
                                          const sx_swid_id_t    swid,
                                          const sx_vlan_id_t   *vlan_list_p,
                                          const uint32_t        vlan_cnt,
                                          sx_acl_vlan_group_t  *group_id_p);

/**
 *  This function is used for getting the current mapping of
 *  vlans into vlan groups for ACL binding.
 *  the vlan_list parameter are arrays at the size of
 *  vlan_num which is filled by this function. the actual
 *  size is then returned as output.
 *
 *  This function is only valid when in 802.1Q mode.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - SWID
 * @param[in] group_id - vlan group ID
 * @param[out] vlan_list - list of vlans which are members in
 *       this vlan group (in the given SWID)
 * @param[in,out] vlan_num - IN - number of elements allocated
 *       in the mapping entries arrays, OUT - number of actual
 *       elements found
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_CMD_UNSUPPORTED if 802.1D mode is enabled
 */
sx_status_t sx_api_acl_vlan_group_map_get(const sx_api_handle_t     handle,
                                          const sx_swid_id_t        swid,
                                          const sx_acl_vlan_group_t group_id,
                                          sx_vlan_id_t             *vlan_list_p,
                                          uint32_t                 *vlan_cnt_p);

/**
 *  This function is used to bind/unbind an ACL or an ACL group to a VLAN group.
 *  Binding more than one ACL to the VLAN group may be achieved by using ACL groups.
 *  BIND command is used for binding a single ACL or a single ACL group to a VLAN group.
 *  UNBIND command will clear the VLAN group binding, even if there are multiple ACL groups
 *  which are bound to the VLAN group.
 *  ADD command can be used to bind multiple ACL groups to the VLAN group.
 *  In this case the order of group execution is determined by the group priority,
 *  set by sx_api_acl_group_attributes_set API.
 *  DELETE command can similarly be used to remove an ACL group from multiple ACL groups
 *  bound to a VLAN group.
 *
 *  Note: ADD and DELETE commands support binding of ACL groups only.
 *        Binding or adding groups may fail if there are insufficient resources in HW.
 *
 *  When in 802.1D mode instead of providing a VLAN group, a bridge_id should be used.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND / UNBIND / ADD / DELETE
 * @param[in] vlan_group - Vlan Group ID to bind
 * @param[in] acl_id - ACL ID of an ACL or ACL Group
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no ACL is available to create
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 */
sx_status_t sx_api_acl_vlan_group_bind_set(const sx_api_handle_t     handle,
                                           const sx_access_cmd_t     cmd,
                                           const sx_acl_vlan_group_t vlan_group,
                                           const sx_acl_id_t         acl_id);

/**
 *  This function is used to get the ACL ID of an ACL table or
 *  an ACL group which is bound to a specific VLAN group.
 *  When multiple ACLs are bound to the VLAN group, this API will only return the one
 *  carrying the highest priority. To retrieve multiple bindings it is suggested to use
 *  sx_api_acl_vlan_group_bindings_get
 *
 *  When in 802.1D mode, instead of providing a VLAN group, a bridge_id should be used.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] vlan_group - VLAN Group ID
 * @param[in] acl_direction - ingress or egress ACL
 * @param[out] acl_id_p - ACL ID of an ACL or ACL Group
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if VLAN group is not bound
 */
sx_status_t sx_api_acl_vlan_group_bind_get(const sx_api_handle_t     handle,
                                           const sx_acl_vlan_group_t vlan_group,
                                           const sx_acl_direction_t  acl_direction,
                                           sx_acl_id_t              *acl_id_p);

/**
 *  This API allows getting ACL IDs bound to a specific VLAN group.
 *  Since multiple groups may bound to a VLAN group, the caller of this API
 *  is responsible of providing an allocated array for getting the ACL IDs.
 *
 *  If this API is called with acl_id_p parameter set to NULL or *acl_cnt_p set to 0, it
 *  will return the actual number of ACL IDs bound to this VLAN group.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] vlan_group - VLAN group ID
 * @param[in] acl_direction - ACL direction
 * @param[in,out] acl_id_p - An array of ACL IDs, should be allocated by the caller.
 * @param[in,out] acl_cnt_p - Specifies the maximum amount of ACL IDs to retrieve,
 *                            and returns the actual number of ACL IDs retrieved.
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if port is not bound
 */
sx_status_t sx_api_acl_vlan_group_bindings_get(const sx_api_handle_t     handle,
                                               const sx_acl_vlan_group_t vlan_group,
                                               const sx_acl_direction_t  acl_direction,
                                               sx_acl_id_t              *acl_id_p,
                                               uint32_t                 *acl_cnt_p);

/**
 *  This function returns attributes of the flexible ACL key.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] key_handle            - The handle to flexible key
 * @param[out] key_attr_p          - Key Attributes
 *
 * @return SX_STATUS_SUCCESS            operation completes successfully
 * @return SX_STATUS_PARAM_ERROR        any input parameters is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND    the key handle is wrong
 */
sx_status_t sx_api_acl_flex_key_attr_get(const sx_api_handle_t    handle,
                                         const sx_acl_key_type_t  key_handle,
                                         sx_acl_flex_key_attr_t * key_attr_p);

/**
 * This API is used to create/delete a FLexible ACL Key. A Flex ACL Key is a combination of (maximum 6) predefined 9B Key blocks.
 * The Key Blocks themselves are composed of several filters and the smallest possible set of Key blocks
 * will be chosen by the SCP algorithm that encompasses all the Keys specified by the API.
 * Key creation is pure DB operation. The maximum number of keys is equal to the maximum number of regions.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - The access cmd CREATE/DELETE
 * @param[in] key_list_p                - Array of basic key ID's
 * @param[in] key_cnt                   - Number of elements in basic key array
 * @param[out] key_handle_p             - The handle to created flexible key
 *
 * @return  SX_STATUS_SUCCESS       operation completes successfully
 * @return  SX_STATUS_PARAM_ERROR   any input parameters is invalid
 * @return  SX_STATUS_UNSUPPORTED   the command is unsupported
 * @return  SX_STATUS_ERROR         general error
 */
sx_status_t sx_api_acl_flex_key_set(const sx_api_handle_t handle,
                                    const sx_access_cmd_t cmd,
                                    const sx_acl_key_t  * key_list_p,
                                    const uint32_t        key_count,
                                    sx_acl_key_type_t   * key_handle_p);

/**
 *  This function returns the list of filters included in the flexible key.
 *  The user is responsible for a memory management of the filters list.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] key_handle            - The handle to flexible key
 * @param[out] key_list_p           - Array of basic key ID's
 * @param[in, out] key_count_p      - Number of elements in basic key array
 *                                    on return will contain the actual number
 *                                    of elements copied to the array.
 *
 * @return SX_STATUS_SUCCESS            operation completes successfully
 * @return SX_STATUS_PARAM_ERROR        any input parameters are invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND    the key handle is not found in the DB
 */
sx_status_t sx_api_acl_flex_key_get(const sx_api_handle_t   handle,
                                    const sx_acl_key_type_t key_handle,
                                    sx_acl_key_t           *key_list_p,
                                    uint32_t               *key_count_p);


/**
 * This API is used to added or remove an ACL rule from an ACL region. The user is responsible for memory management -
 * it is necessary to initialize each member of rules_list_p using call to sx_lib_flex_acl_rule_init before calling this API
 * and de-initialize using call to sx_lib_flex_acl_rule_deinit after calling this API.
 * This operation configures the HW if the ACL is bound to a device.
 * The configured rule will override the existing rule if present at the given offset with the new rule.
 * The Keys specified in the rules_list must be a subset of the keys which were used to create the region.
 * The user can also define a custom set of actions for each rule.
 * If an offset in the offsets array crosses the boundaries of the region the function will return an error.
 * Only one of each of the following types of actions will be allowed within the same rule :
 *      - SX_FLEX_ACL_ACTION_FORWARD
 *      - SX_FLEX_ACL_ACTION_EGRESS_MIRROR or SX_FLEX_ACL_ACTION_MIRROR
 *      - SX_FLEX_ACL_ACTION_TRAP or SX_FLEX_ACL_ACTION_TRAP_W_USER_ID
 * Multiple Forward or Multiple Mirror or a combination where there is more than one of any of the above will return PARAM_ERROR
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - The access command SET/DELETE
 * @param[in] region_id             - ACL region ID received during region creation
 * @param[in] offsets_list_p        - Array of rule offsets into region directly associated with the appropriate item in the array of rules
 * @param[in] rules_list_p          - Array of structures describing the flexible rule content
 * @param[in] rules_cnt             - Number of elements in array of flexible rule descriptors
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
 *  @return SX_STATUS_CMD_UNSUPPORTED   The sent command is unsupported
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 *  @return SX_STATUS_ENTRY_NOT_FOUND   Wrong region ID
 *  @return SX_STATUS_NO_RESOURCES      No more space for rules. Cannot allocate space for all actions
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
 * This function returns a list of rules associated with particular region. The user is responsible for memory management -
 * it is necessary to initialize each member of rules_list_p using call to sx_lib_flex_acl_rule_init before calling this API and
 * de-initialize using call to sx_lib_flex_acl_rule_deinit after calling this API.
 *
 *  If the function is called with rules_list_p parameter set to NULL or *rules_cnt_p set to 0, it
 * will return the actual number of rules set to the region.
 *
 *  If the function is called with key_desc_list_p and action_list_p parameter of each of the rules in rules_list_p set
 * to NULL and offset_list_p array filled with zeroes - it will return the actual number of keys and actions for each valid rule
 * starting from offset 0, as well as the rule's offset in offset list for this rule.
 *
 *  If the function is called with key_desc_list_p and action_list_p parameter of each of the rules in rules_list_p set
 * to NULL, but offset_list_p array is filled with non-zero values - it will return the actual number of keys and actions for each valid rule
 * according to the offset, which is defined in the offset list. In this case the offset list should be filled with offsets of the rules,
 * which are valid.
 *
 *  If the function is called with key_desc_list_p and action_list_p parameter of each of the rules in rules_list_p set
 * to non-NULL, it is assumed that rule structures are allocated for all rules in the list. It also assumed that the offset list
 * is filled with real offsets of the rules in the same order as in the rules list.
 *
 * When calling the API, the key_desc_count and action_count of each sx_flex_acl_flex_rule_t should contain number of allocated
 * items, on API return these parameters will contain actual number of items. The offset list should contain offsets of valid rules only.
 *
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] region_id             - ACL region ID received during region creation
 * @param[in, out] offsets_list_p   - Array of rule offsets in the region directly associated with the appropriate item in the array of rules
 * @param[out] rules_list_p         - Array of structures describing the flexible rule content
 * @param[in, out] rules_cnt        - Desirable number of elements in array of flexible rule descriptors. Function returns actual count.
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
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
 *  This function is used to bind/unbind an ACL or an ACL group to a RIF.
 *  Binding more than one ACL to a RIF may be achieved by using ACL groups.
 *  BIND command is used for binding a single ACL or a single ACL group to a RIF.
 *  UNBIND command will clear RIF binding, even if there are multiple ACL groups
 *  which are bound to the RIF.
 *  ADD command can be used to bind additional groups to the RIF. In this case
 *  the order of group execution is determined by the group priority, asset by
 *  the sx_api_acl_group_attributes_set API. Similarly it is possible to remove
 *  an ACL group from multiple ACL groups bound RIF, using the DELETE command.
 *
 *  Note: ADD and DELETE commands support binding of ACL groups only.
 *        Binding or adding groups may fail if there are insufficient resources in HW.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - BIND/UNBIND/ADD/DELETE
 * @param[in] rif_id                - RIF ID
 * @param[in] acl_id                - ACL or ACL group ID
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID or RIF ID not found in DB
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 *  @return SX_STATUS_CMD_UNSUPPORTED   the given command is unsupported
 *  @return SX_STATUS_ERROR             The operation cannot be completed
 */
sx_status_t sx_api_acl_rif_bind_set(const sx_api_handle_t handle,
                                    const sx_access_cmd_t cmd,
                                    const sx_rif_id_t     rif_id,
                                    const sx_acl_id_t     acl_id);

/**
 *  This function is used to get the ACL or ACL group ID that is bound to the RIF.
 *  When multiple ACLs are bound to the RIF, this API will only return the one
 *  carrying the highest priority. To retrieve multiple bindings it is suggested to use
 *  the sx_api_acl_rif_bindings_get API instead.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] rif_id                  - RIF ID
 * @param[in] acl_direction           - The direction of ACL(ingress/egress)
 * @param[out] acl_id_p               - ACL or ACL group ID that is bound to RIF
 *
 *  @return SX_STATUS_SUCCESS   The operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID or RIF ID not found in DB
 *  @return SX_STATUS_PARAM_ERROR   Invalid parameter
 */
sx_status_t sx_api_acl_rif_bind_get(const sx_api_handle_t    handle,
                                    const sx_rif_id_t        rif_id,
                                    const sx_acl_direction_t acl_direction,
                                    sx_acl_id_t             *acl_id_p);

/**
 *  This API allows getting ACL IDs bound to a specific RIF.
 *  Since multiple groups may bound to a RIF, the caller of this API
 *  is responsible of providing a pre-allocated array for getting the ACL IDs.
 *  priority group.
 *  If the API is called with acl_id_p parameter set to NULL or *acl_cnt_p set to 0, it
 *  will return the actual number of ACL IDs bound to this RIF.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] rif_id - RIF ID
 * @param[in] acl_direction - ACL direction
 * @param[in,out] acl_id_p - An array of ACL IDs, should be allocated by the caller.
 * @param[in,out] acl_cnt_p - Specifies the maximum amount of ACL IDs to retrieve,
 *                            and returns the actual number of ACL IDs retrieved.
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if RIF is not bound
 */
sx_status_t sx_api_acl_rif_bindings_get(const sx_api_handle_t    handle,
                                        const sx_rif_id_t        rif_id,
                                        const sx_acl_direction_t acl_direction,
                                        sx_acl_id_t             *acl_id_p,
                                        uint32_t                *acl_cnt_p);

/**
 * On ACL module initialization the user can choose the parallel ACL search type. This function is used to support this feature.
 *  It links one ACL group to another. Their relation could be described as "one directional linked list" where the second group is
 *  next to the first one. Only the head of the list of groups is allowed to be bound to port/VLAN/RIF.
 *  The other linked groups will be bound automatically. An attempt to bind explicitly any group but the head will cause an error.
 *  In Parallel operation, the action of the ACL do not apply immediately so each ACL rule will act on the original packet.
 *
 *	Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - The command BIND/UNBIND
 * @param[in] parent_group_id           - The first, parent ACL or ACL group ID that second one will be bound to
 * @param[in] group_id                  - The second ACL or ACL group ID that will be bound to the first one
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID not found in DB
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 */
sx_status_t sx_api_acl_group_bind_set(sx_api_handle_t       handle,
                                      const sx_access_cmd_t cmd,
                                      sx_acl_id_t           group_id,
                                      sx_acl_id_t           next_group_id);

/**
 *  This function returns the next ACL group bound to the given one.
 *  Used when the ACL module has been initialized in parallel mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] group_id               - The first, parent ACL or ACL group ID that second one was be bound to
 * @param[out] group_id_p            - The ACL or ACL group ID that bound to the parent. In case no such binding
 *                                      exists to the parent, an invalid ACL ID will be returned
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID not found in DB
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 */
sx_status_t sx_api_acl_group_bind_get(sx_api_handle_t handle,
                                      sx_acl_id_t     group_id,
                                      sx_acl_id_t   * group_id_p);

/**
 * The function is used to manipulate a port list container
 * Command CREATE creates a new container with the specified list of logical ports
 * and returns its new container ID in port_list_id_p.
 * Command SET replaces the contents of an existing container specified by
 * port_list_id_p, with the specified list of logical ports in port_list_p.
 * Command DESTROY deletes an existing container specified by port_list_id_p.
 * Notes: A port list in use (e.g. by an ACL key) cannot be destroyed or modified
 *        A container may contain at most RM_API_ACL_PORT_LIST_MAX logical ports
 *        A container may contain only Ethernet logical ports and not LAG ports
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/SET/DESTROY.
 * @param[in] port_list_p - Specifies or returns the container ID
 * @param[in] port_list_cnt - Specifies the list of logical ports for the container
 * @param[in/out] port_list_id_p - specifies the id of the port list created/to change
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully.
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container ID does not exist.
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation.
 * @return SX_STATUS_RESOURCE_IN_USE if group is in use and cannot be destroyed.
 */
sx_status_t sx_api_acl_port_list_set(const sx_api_handle_t     handle,
                                     const sx_access_cmd_t     cmd,
                                     sx_acl_port_list_entry_t *port_list_p,
                                     const uint32_t            port_list_cnt,
                                     sx_acl_port_list_id_t    *port_list_id_p);

/**
 * Retrieve information about a port list container specified by port_list_id.
 * Notes: *port_list_cnt should contain the maximum amount of logical ports to retrieve.
 *        If port_list_p is NULL, then port_list_p are not retrieved at all. In this case port_list_cnt
 *        will contain the actual number if ports in the port list
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] port_list_id - specifies the id of the port list to retrieve
 * @param[out] port_list_p -	array of ports to copy into
 * @param[in,out] port_list_cnt_p - Specifies the maximum amount of logical ports to retrieve,
 *                               and returns the amount logical ports retrieved
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container does not exist, or no more containers.
 */
sx_status_t sx_api_acl_port_list_get(const sx_api_handle_t       handle,
                                     const sx_acl_port_list_id_t port_list_id,
                                     sx_acl_port_list_entry_t   *port_list_p,
                                     uint32_t                   *port_list_cnt_p);


/**
 *  This function is used to get ACL region HW size .
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] region_id - ACL region ID
 * @param[out] region_size_p - The region actual hw size
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 *
 */
sx_status_t sx_api_acl_region_hw_size_get(const sx_api_handle_t    handle,
                                          const sx_acl_region_id_t region_id,
                                          sx_acl_size_t           *region_size_p);


/**
 * This API creates and deletes a Custom Bytes Set. Currently only 4-bytes sets are supported.
 * Returned value is a set of key Ids from sx_acl_key_t space.
 * Each byte in the custom bytes set is accessed as a separate ACL key in the
 * FLEX_ACL_CUSTOM_BYTES_START to FLEX_ACL_CYSTOM_BYTE_LAST range.
 * The Custom Bytes extraction points are a predefined set of extraction points
 * based on the protocol of interest. The key ids returned by this API can
 * then be used to create a Flex ACL key.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/DESTROY/EDIT.
 * @param[in] custom_bytes_set_attributes - Specifies extraction points data.
 * @param[in/out] custom_bytes_set_key_id_p - Specifies an array of the custom bytes keys id.
 *  For CREATE an array of SDK key ids should be provided. For destroy only the first key is used to identify the destroyed set.
 *  For CREATE, if the first key id in list is zero (FLEX_ACL_KEY_INVALID) or any other value not in the interval
 *  [FLEX_ACL_KEY_CUSTOM_BYTES_START .. FLEX_ACL_KEY_CUSTOM_BYTES_LAST], the custom bytes set is allocated by SW
 *  as the first free one. If the first key id in the list belongs to interval
 *  [FLEX_ACL_KEY_CUSTOM_BYTES_START .. FLEX_ACL_KEY_CUSTOM_BYTES_LAST], it identifies the custom bytes set to be
 *  allocated. If the custom bytes set is already allocated, SW allocates first free set.
 *  As an example, key ids, which were allocated once and destroyed after that, may be submitted to the CREATE
 *  operation in order to get the same key ids, in case they are still free.
 * @param[in/out] custom_bytes_set_key_id_cnt_p - Specifies how many custom bytes are expected by the user.
 *  The counter is updated with the smaller of the available number of bytes in allocated set & Requested number of bytes
 *
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container ID does not exist.
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation.
 * @return SX_STATUS_RESOURCE_IN_USE if group is in use and cannot be destroyed.
 */
sx_status_t sx_api_acl_custom_bytes_set(sx_api_handle_t                             handle,
                                        sx_access_cmd_t                             cmd,
                                        const sx_acl_custom_bytes_set_attributes_t *custom_bytes_set_attributes,
                                        sx_acl_key_t                               *custom_bytes_set_key_id_p,
                                        uint32_t                                   *custom_bytes_set_key_id_cnt_p);

/**
 *
 * This API returns extraction point parameters of the existing Custom Bytes Set
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] custom_bytes_set_key_id_p - Specifies an array of the custom bytes keys id. Only first item
 *                                        in array is provided.
 * @param[out] custom_bytes_key_extraction_point_list_p - Specifies extraction points fetched data.
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container does not exist, or no more containers.
 */
sx_status_t sx_api_acl_custom_bytes_get(sx_api_handle_t                       handle,
                                        sx_acl_key_t                         *custom_bytes_set_key_id_p,
                                        sx_acl_custom_bytes_set_attributes_t *custom_bytes_set_attributes_p);

/**
 *  This function adds/edits/deletes a policy based ILM (PBILM).
 *  Policy based ILM entry can be later bound to an ACL rule
 *  in order to specify a mpls ecmp that will encapsulate the packet
 *  with mpls labels and send it to RIF. It can also send the frame
 *  to IP or ILM lookup.
 *  Use CREATE to create a PBILM entry, which can be changed when
 *  needed by SET. Note that these operations may fail if no HW
 *  resources are available. Use DESTROY to remove the PBILM.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE / SET / DESTROY
 * @param[in] pbilm_entry - struct for PBILM attributes
 * @param[in,out] pbilm_id - Port range comparison ID
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if there are no HW resources for PBILM creation
 * @return SX_STATUS_RESOURCE_IN_USE if the PBILM record is in use
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_policy_based_ilm_set(const sx_api_handle_t       handle,
                                            const sx_access_cmd_t       cmd,
                                            const sx_acl_pbilm_entry_t *pbilm_entry_p,
                                            sx_acl_pbilm_id_t          *pbilm_id_p);

/**
 *  This function is used to get a PBILM set or to count ports of
 *  a PBILM set. The user should ensure that the pbilm_entry
 *  is preallocated with the maximum number of ports to be retrieved.
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] pbilm_id - Policy based ILM entry ID
 * @param[out] pbilm_entry - struct for Policy ILM
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_CMD_UNSUPPORTED if if the supplied command is unsupported
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_policy_based_ilm_get(const sx_api_handle_t   handle,
                                            const sx_acl_pbilm_id_t pbilm_id,
                                            sx_acl_pbilm_entry_t   *pbilm_entry_p);

/**
 *  This function is used for updating a set of priorities, in the range [min_priority, max_priority]
 *  to priority + priority_change.
 *  Limitation: The priority can be changed only if there is no other rules between min priority + change  to
 *  max priority + change (and the opposite if the priority_change < 0 )
 *  Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle - SX-API handle
 * @param[in] region_id - ACL region ID
 * @param[in] min_priority - Minimum priority in the range
 * @param[in] max_priority - - Maximum priority in the range
 * @param[in] priority_change - The offset by which the priority should be changed (can be positive/negative)
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 */
sx_status_t sx_api_acl_flex_rules_priority_set(const sx_api_handle_t             handle,
                                               const sx_acl_region_id_t          region_id,
                                               const sx_flex_acl_rule_priority_t min_priority,
                                               const sx_flex_acl_rule_priority_t max_priority,
                                               const int32_t                     priority_change);


#endif /* ifndef __SX_API_ACL_H__ */
