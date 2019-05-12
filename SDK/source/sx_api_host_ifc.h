/*
 *  Copyright (C) 2014-2019. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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


#ifndef __SX_API_HOST_IFC_H__
#define __SX_API_HOST_IFC_H__

/*
 * Retry macro to be used with uninterruptible POSIX operations
 */
#define POSIX_EINTR_RETRY(ret_value, op) \
    do {                                 \
        ret_value = op;                  \
    } while (((ret_value) == -1) && (errno == EINTR))

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/**
 * This function sets the log verbosity level of HOST INTERFACE MODULE
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle                   - SX-API handle.
 * @param[in] verbosity_target         - Set verbosity of : API / MODULE / BOTH.
 * @param[in] module_verbosity_level   - HOST INTERFACE module verbosity level.
 * @param[in] api_verbosity_level      - HOST INTERFACE API verbosity level.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_host_ifc_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                    const sx_log_verbosity_target_t verbosity_target,
                                                    const sx_verbosity_level_t      module_verbosity_level,
                                                    const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of HOST INTERFACE MODULE
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]  handle                   - SX-API handle.
 * @param[in]  verbosity_target         - Get verbosity of : API / MODULE / BOTH.
 * @param[out] module_verbosity_level_p - HOST INTERFACE module verbosity level.
 * @param[out] api_verbosity_level_p    - HOST INTERFACE API verbosity level.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_host_ifc_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                    const sx_log_verbosity_target_t verbosity_target,
                                                    sx_verbosity_level_t           *module_verbosity_level_p,
                                                    sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This function retrieves the file descriptor of the current open channel
 * used for receiving a packet
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle          - SX-API handle.
 * @param[out]    fd_p            - File descriptor.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO error closing channel to the sx driver
 */
sx_status_t sx_api_host_ifc_open(const sx_api_handle_t handle,
                                 sx_fd_t              *fd_p);

/**
 * This function closes the file descriptor of the current open channel
 * used for receiving a packet
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]    handle         - SX-API handle.
 * @param[in]    fd_p           - File descriptor.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO error closing channel to the sx driver
 */
sx_status_t sx_api_host_ifc_close(const sx_api_handle_t handle,
                                  sx_fd_t              *fd_p);

/**
 * Create / Edit a trap group
 *   Allows creating a new trap group with certain attributes,
 *   and editing an existing trap group with new attributes.
 *
 * On Edit :
 * Changing Monitor trap group (attribute is_monitor 1) to
 * regular trap group and vice versa are not allowed.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle                   - SX-API handle.
 * @param[in]     swid                     - Switch ID.
 * @param[in]     trap_group               - The trap group, must be between 0-63.
 * @param[in]     trap_group_attributes_p  - Trap group attributes.
 *
 * @return  SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t sx_api_host_ifc_trap_group_set(const sx_api_handle_t             handle,
                                           const sx_swid_id_t                swid,
                                           const sx_trap_group_t             trap_group,
                                           const sx_trap_group_attributes_t* trap_group_attributes_p);

/**
 * When cmd = SX_ACCESS_CMD_SET, create / edit a trap group, it works exactly the same with API sx_api_host_ifc_trap_group_set.
 *   Allows creating a new trap group with certain attributes,
 *   and editing an existing trap group with new attributes.
 *
 *   On Edit :
 *     Changing Monitor trap group (attribute is_monitor 1) to
 *     regular trap group and vice versa are not allowed.
 *
 * When cmd = SX_ACCESS_CMD_UNSET, unset a trap group and the trap_group_attributes_p parameter is ignored (can be NULL).
 *   1) If there are policers bound to the trap group, please unbind them first.
 *   2) If there are trap IDs configured to the trap group via API sx_api_host_ifc_trap_id_ext_set,
 *      please unset them first.
 *   3) If the trap group is monitor trap group, then the file descriptor associated with this trap
 *      group will be reverted back to non-monitor file descriptor.
 *
 * Note: The trap groups set by API sx_api_host_ifc_trap_group_set can be unset by sx_api_host_ifc_trap_group_ext_set.
 *   It is recommended to use sx_api_host_ifc_trap_group_ext_set to set/unset trap groups.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle                   - SX-API handle.
 * @param[in]     cmd                      - SX_ACCESS_CMD_SET / SX_ACCESS_CMD_UNSET
 * @param[in]     swid                     - Switch ID.
 * @param[in]     trap_group               - The trap group, must be between 0-63.
 * @param[in]     trap_group_attributes_p  - Trap group attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t sx_api_host_ifc_trap_group_ext_set(const sx_api_handle_t             handle,
                                               const sx_access_cmd_t             cmd,
                                               const sx_swid_id_t                swid,
                                               const sx_trap_group_t             trap_group,
                                               const sx_trap_group_attributes_t* trap_group_attributes_p);


/**
 * Get Trap group attributes:
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle                   - SX-API handle.
 * @param[in]     swid                     - Switch ID.
 * @param[in]     trap_group               - The trap group, must be between 0-63.
 * @param[out]    trap_group_attributes_p  - Trap group attributes.
 *
 * @return  SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t sx_api_host_ifc_trap_group_get(const sx_api_handle_t        handle,
                                           const sx_swid_id_t           swid,
                                           const sx_trap_group_t        trap_group,
                                           sx_trap_group_attributes_t * trap_group_attributes_p);

/**
 *  This function retrieves a list of one or more trap group IDs.
 *  The following use case scenarios apply with different input parameters
 *  X = don't-care
 *   - 1) cmd = SX_ACCESS_CMD_GET, swid = valid, trap_group_id = X,
 *        trap_group_id_list = X, trap_group_id_cnt = 0:
 *        In this case the API will return the total number of trap group IDs in the
 *        internal DB.
 *
 *   - 2) cmd = SX_ACCESS_CMD_GET, swid = valid, trap_group_id = valid/invalid,
 *        trap_group_id_list = valid, trap_group_id_cnt = 1:
 *        In this case the API will check if the specified trap_group_id exists.
 *        If it does, the trap group ID will be returned in the trap_group_id_list
 *        along with a trap_group_id_cnt of 1.
 *        If the trap group ID does not exist, an empty list will be returned with
 *        trap_group_id_cnt = 0.
 *        A non-NULL trap_group_id_list pointer must be provided in this case.
 *
 *   - 3) cmd = SX_ACCESS_CMD_GET, swid = valid, trap_group_id = valid/invalid,
 *        trap_group_id_list = valid, trap_group_id_cnt > 1:
 *        A trap_group_id_cnt > 1 will be treated as a trap_group_id_cnt of 1 and the
 *        behavior will be same as the earlier GET use cases.
 *
 *   - 4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, swid = X, trap_group_id = X,
 *        trap_group_id_list = NULL, trap_group_id_cnt = 0:
 *        A zero trap_group_id_cnt and an empty trap_group_id_list will be returned.
 *
 *   - 5) cmd = SX_ACCESS_CMD_GET_FIRST, swid = valid, trap_group_id = X,
 *        trap_group_id_list = valid, trap_group_id_cnt > 0:
 *        In this case the API will return the first trap_group_id_cnt trap group IDs
 *        starting from the head of the database. The total number of elements fetched
 *        will be returned as trap_group_id_cnt.
 *        Note: returned trap_group_id_cnt may be less than or equal to the requested
 *        trap_group_id_cnt. The input trap group ID is ignored in this case.
 *        A non-NULL trap_group_id_list pointer must be provided in this case.
 *
 *   - 6) cmd = SX_ACCESS_CMD_GETNEXT, swid = valid, trap_group_id = valid/invalid,
 *        trap_group_id_list = valid, trap_group_id_cnt > 0:
 *        In this case the API will return the next set of trap group IDs starting from
 *        the next trap group ID after the specified trap group ID. The total number of
 *        elements fetched will be returned as the trap_group_id_cnt.
 *        Note: returned trap_group_id_cnt may be less than or equal to the requested
 *        trap_group_id_cnt.
 *        If no valid next trap group ID exists in the db, an empty list will be returned.
 *        A non-NULL trap_group_id_list pointer must be provided in this case.
 *
 *
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param [in] handle                  - SX-API handle.
 * @param [in] cmd                     - GET/GET_FIRST/GET_NEXT.
 * @param [in] swid                    - Switch ID.
 * @param [in] trap_group_id           - Trap group ID.
 * @param [in] filter_p                - Specify a filter parameter (not supported yet).
 * @param [out] trap_group_id_list_p   - Return list of trap group IDs:
 * @param [in,out] trap_group_id_cnt_p - [in] number of trap group IDs to get.
 *                                     - [out] number of trap group IDs returned.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_host_ifc_trap_group_iter_get(const sx_api_handle_t         handle,
                                                const sx_access_cmd_t         cmd,
                                                const sx_swid_id_t            swid,
                                                const sx_trap_group_t         trap_group_id,
                                                const sx_trap_group_filter_t *filter_p,
                                                sx_trap_group_t              *trap_group_id_list_p,
                                                uint32_t                     *trap_group_id_cnt_p);


/**
 * Configure traps / event properties for each device in the system:
 *       Map Trap ID / Event ID to Priority group.
 *       Configure trap action (for traps only).
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle        - SX-API handle.
 * @param[in]     swid          - Switch ID.
 * @param[in]     trap_id       - Trap ID.
 * @param[in]     trap_group    - Trap group handle.
 * @param[in]     trap_action   - Trap action.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 *
 * Note: When configuring trap_id of SX_TRAP_ID_ETH_L2_PACKET_SAMPLING /SX_TRAP_ID_GENERAL_FDB /SX_TRAP_ID_ACL/SX_TRAP_ID_IPTRAP,
 *       trap_action field is ignored.
 *       Instead, the action should be configured in each module.
 */
sx_status_t sx_api_host_ifc_trap_id_set(const sx_api_handle_t  handle,
                                        const sx_swid_t        swid,
                                        const sx_trap_id_t     trap_id,
                                        const sx_trap_group_t  trap_group,
                                        const sx_trap_action_t trap_action);

/**
 * Configure traps / event properties for each device in the system:
 * Map Trap ID / Event ID to 1 of the 3 Priority groups: HIGH, MEDIUM, LOW.
 * Configure trap action (for traps only).
 * Please note that this API allows to bind the same trap id to regular and
 * monitor trap groups at the same time.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle        - SX-API handle.
 * @param[in]     cmd           - SX_ACCESS_CMD_SET / SX_ACCESS_CMD_UNSET
 * @param[in]     trap_key_p    - Trap key value (e.g. Trap ID)
 * @param[in]     trap_attr_p   - Trap attributes (e.g. trap group and trap action)
 *
 *    @return SX_STATUS_SUCCESS if operation completes successfully
 *    @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *    @return SX_STATUS_ERROR general error
 *
 * Note: when configuring trap_id of SX_TRAP_ID_ETH_L2_PACKET_SAMPLING/SX_TRAP_ID_GENERAL_FDB/SX_TRAP_ID_ACL/SX_TRAP_ID_IPTRAP,
 *       trap_action field is ignored.
 *       Instead, the action should be configured in each module.
 */
sx_status_t sx_api_host_ifc_trap_id_ext_set(const sx_api_handle_t          handle,
                                            const sx_access_cmd_t          cmd,
                                            const sx_host_ifc_trap_key_t  *trap_key_p,
                                            const sx_host_ifc_trap_attr_t *trap_attr_p);

/**
 * Get configured traps / event properties for each device in the system:
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle        - SX-API handle.
 * @param[in]     cmd           - SX_ACCESS_CMD_GET
 *
 * @param[in]     trap_key_p    - Trap key value (e.g. Trap ID).
 * @param[out]    trap_attr_p   - Trap attributes (e.g. trap group and trap action)
 * @param[out]    trap_cnt_p    - Number of the trap groups and relevant parameters
 *                                which bound to trap_id.
 *
 *    @return SX_STATUS_SUCCESS if operation completes successfully
 *    @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *    @return SX_STATUS_ERROR general error
 *
 * Note: when trap_attr_p is NULL only the number of bound trap groups
 *       will be returned in trap_cnt_p.
 */
sx_status_t sx_api_host_ifc_trap_id_ext_get(const sx_api_handle_t         handle,
                                            const sx_access_cmd_t         cmd,
                                            const sx_host_ifc_trap_key_t *trap_key_p,
                                            sx_host_ifc_trap_attr_t      *trap_attr_p,
                                            uint32_t                     *attr_cnt_p);

/**
 * Get trap group information such as total number of discarded
 * packets.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle        - SX-API handle.
 * @param[in]     cmd           - SX_ACCESS_CMD_READ, SX_ACCESS_CMD_READ_CLEAR
 *
 * @param[in]     group_key_p    - Trap group key value (e.g. Trap group ID).
 * @param[out]    group_stat_p   - Trap group statistic data (e.g. total number of discarded packets)
 *
 *    @return SX_STATUS_SUCCESS if operation completes successfully
 *    @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *    @return SX_STATUS_ERROR general error
 *
 */
sx_status_t sx_api_host_ifc_trap_group_stat_get(const sx_api_handle_t               handle,
                                                const sx_access_cmd_t               cmd,
                                                const sx_host_ifc_trap_group_key_t *group_key_p,
                                                sx_host_ifc_trap_group_stat_t      *group_stat_p);

/**
 * This API adds/deletes user defined trap ID's.
 * The trap ID created should be in the [SX_TRAP_ID_USER_BASE,SX_TRAP_ID_USER_MAX]
 * range.
 * For cmd == SX_ACCESS_CMD_DELETE, trap_attributes_p can be NULL.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle            - SX-API handle.
 * @param[in]     cmd               - ADD/DELETE.
 * @param[in]     swid              - Switch ID.
 * @param[in]     trap_id           - Trap ID.
 * @param[in]     trap_attributes_p - Traps attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ERROR general error.
 * @return SX_STATUS_MEMORY_ERROR error handling memory.
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS If trap ID is already configured.
 *
 */
sx_status_t sx_api_host_ifc_user_defined_trap_id_set(const sx_api_handle_t                 handle,
                                                     const sx_access_cmd_t                 cmd,
                                                     const sx_swid_t                       swid,
                                                     const sx_trap_id_t                    trap_id,
                                                     sx_trap_id_user_defined_attributes_t *trap_attributes_p);

/**
 * Register / DeRegister Traps (STP , LACP)  or Events (Port up /
 * down , Temperature event) in the driver. Configure the driver
 * to pass packets matching this trap ID / Event ID, criteria &
 * SWID to the client (according to user_channel).
 * The source_log_port parameter of the received L2 trap always relates
 * to the relevant physical port.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle          - SX-API handle.
 * @param[in]     cmd             - REGISTER/DEREGISTER.
 * @param[in]     trap_id         - Trap ID.
 * @param[in]     user_channel_p  - The channel for the packets to be trapped.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */

sx_status_t sx_api_host_ifc_trap_id_register_set(const sx_api_handle_t    handle,
                                                 const sx_access_cmd_t    cmd,
                                                 const sx_swid_t          swid,
                                                 const sx_trap_id_t       trap_id,
                                                 const sx_user_channel_t *user_channel_p);

/**
 * This function get the trap's user channel list according to the swid and trap_id.
 * The following use case scenarios apply with different input parameters.
 * 1) SX_ACCESS_CMD_GET
 *    When *user_channel_cnt_p is not 0, this function returns a list of user channels.
 *    The returned user_channel_cnt may be less or equal to the requested user_channel_cnt.
 *    When *user_channel_cnt_p is 0, this function returns the total number of user channels
 *    configured for the specified trap ID.
 *    The input user_channel is ignored in this case.
 *
 * 2) SX_ACCESS_CMD_GET_FIRST
 *    In this case the API will return the first set of user channels.
 *    The returned user_channel_cnt may be less or equal to the requested user_channel_cnt.
 *    The input user_channel is ignored int this case.
 *
 * 3) SX_ACCESS_CMD_GETNEXT
 *    In this case the API will return the next set of user channels starting from
 *    the next user channel after the specified user channel.
 *    The returned user_channel_cnt may be less or equal to the requested user_channel_cnt.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle                 - SX-API handle.
 * @param[in]     cmd                    - GET/GET_FIRST/GET_NEXT.
 * @param[in]     swid                   - Switch ID.
 * @param[in]     trap_id                - Trap ID.
 * @param[out]    user_channel           - User channel, as a key to get next entries.
 * @param[out]    user_channel_list_p    - List of user channels.
 * @param[in,out] user_channel_cnt_p     - as input: number of user channels requested.
 *                                         as output: number of user channels returned.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_host_ifc_trap_id_register_get(const sx_api_handle_t    handle,
                                                 const sx_access_cmd_t    cmd,
                                                 const sx_swid_t          swid,
                                                 const sx_trap_id_t       trap_id,
                                                 const sx_user_channel_t *user_channel,
                                                 sx_user_channel_t       *user_channel_list_p,
                                                 uint32_t                *user_channel_cnt_p);

/**
 * Register / DeRegister Traps (STP , LACP)  or Events (Port up /
 * down , Temperature event) in the driver. Configure the driver
 * to pass packets matching this trap ID / Event ID, port OR vlan &
 * SWID to the client (according to user_channel).
 * The source_log_port parameter of the received L2 trap always relates
 * to the relevant physical port.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle          - SX-API handle.
 * @param[in]     cmd             - REGISTER/DEREGISTER.
 * @param[in]     trap_id         - Trap ID.
 * @param[in]     register_key_p  - Port/FID/Global
 * @param[in]     user_channel_p  - The channel for the packets to be trapped.
 *
 * @return  SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */

sx_status_t sx_api_host_ifc_port_vlan_trap_id_register_set(const sx_api_handle_t             handle,
                                                           const sx_access_cmd_t             cmd,
                                                           const sx_swid_t                   swid,
                                                           const sx_trap_id_t                trap_id,
                                                           const sx_host_ifc_register_key_t *register_key_p,
                                                           const sx_user_channel_t          *user_channel_p);

/**
 * This function get the trap's register entry (register key and user channel) list according to the swid and trap_id.
 * The following use case scenarios apply with different input parameters.
 * 1) SX_ACCESS_CMD_GET
 *    When *register_entry_cnt_p is not 0, this function returns a list of register entries.
 *    The returned register_entry_cnt_p may be less or equal to the requested register_entry_cnt_p.
 *    When *register_entry_cnt_p is 0, this function returns the total number of register entries
 *    configured for the specified trap ID.
 *    The input register entry is ignored in this case.
 *
 * 2) SX_ACCESS_CMD_GET_FIRST
 *    In this case the API will return the first set of register entries.
 *    The returned register_entry_cnt may be less or equal to the requested register_entry_cnt.
 *    The input register entry is ignored int this case.
 *
 * 3) SX_ACCESS_CMD_GETNEXT
 *    In this case the API will return the next set of register entries starting from
 *    the next register entry after the specified register entry.
 *    The returned register_entry_cnt may be less or equal to the requested register_entry_cnt.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle                 - SX-API handle.
 * @param[in]     cmd                    - GET/GET_FIRST/GET_NEXT
 * @param[in]     swid                   - Switch ID.
 * @param[in]     trap_id                - Trap ID.
 * @param[out]    register_entry         - Register entry, as a key to get next entries.
 * @param[out]    register_entry_list_p  - List of register entries.
 * @param[in,out] register_entry_cnt_p   - [in]: number of register entries requested.
 *                                         [out]: number of register entries returned.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_host_ifc_port_vlan_trap_id_register_get(const sx_api_handle_t                   handle,
                                                           const sx_access_cmd_t                   cmd,
                                                           const sx_swid_t                         swid,
                                                           const sx_trap_id_t                      trap_id,
                                                           const sx_host_ifc_register_get_entry_t *register_entry,
                                                           sx_host_ifc_register_get_entry_t       *register_entry_list_p,
                                                           uint32_t                               *register_entry_cnt_p);

/**
 * This function configures the switch to filter packets received from certain ports/LAGs.
 * If cmd is ADD, the given ports are added to the filter list.
 * If the cmd is DELETE the given ports are removed from the trap filter list.
 * If the cmd is DELETE_ALL all ports and LAGs which were previously added to the filter
 * are removed. In this case log_port_num and log_port_list parameters are ignored.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] cmd               - ADD / DELETE /DELETE_ALL
 * @param[in] swid              - Switch ID.
 * @param[in] trap_id           - Trap ID to filter on.
 * @param[in,out] log_port_list - List of Logical Ports to ADD/DELETE to/from the trap's filter list.
 *               If the API returns an error the list will contain the ports/LAGs which were
 *               not added successfully to the filter list.
 * @param[in,out] log_port_num  - Number of Logical Ports to ADD/DELETE to/from the trap's filter list.
 *               If the API returns and error it will hold the number of ports/LAGs which were
 *               not added successfully to the filter list.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if the command is not supported
 * @return SX_STATUS_ERROR if a general error has occurred
 */
sx_status_t sx_api_host_ifc_trap_filter_set(const sx_api_handle_t handle,
                                            const sx_access_cmd_t cmd,
                                            const sx_swid_t       swid,
                                            const sx_trap_id_t    trap_id,
                                            sx_port_log_id_t     *log_port_list_p,
                                            uint32_t             *log_port_cnt_p);

/**
 * This function get the trap's filter list according to the swid and trap_id.
 * The following use case scenarios apply with different input parameters.
 * 1) SX_ACCESS_CMD_GET
 *    When *log_port_cnt_p is not 0, this function returns a list of logical port IDs.
 *    The returned log_port_cnt may be less or equal to the requested log_port_cnt.
 *    When *log_port_cnt_p is 0, this function returns the the total number of ports/LAGs
 *    configured for the specified trap ID.
 *    The input log_port_id is ignored in this case.
 *
 * 2) SX_ACCESS_CMD_GET_FIRST
 *    In this case the API will return the first set of logical port IDs.
 *    The returned log_port_cnt may be less or equal to the requested log_port_cnt.
 *    The input log_port_id is ignored int this case.
 *
 * 3) SX_ACCESS_CMD_GETNEXT
 *    In this case the API will return the next set of logical port IDs starting from
 *    the next logical port ID after the specified logical port ID.
 *    The returned log_port_cnt may be less or equal to the requested log_port_cnt.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] cmd               - GET/GET_FIRST/GET_NEXT.
 * @param[in] swid              - Switch ID.
 * @param[in] trap_id           - Trap ID.
 * @param[in] log_port_id       - Logical port ID, as a key to get next entries.
 * @param[out] log_port_list    - List of logical ports.
 * @param[in,out] log_port_num  - as input: number of logical ports requested.
 *                                as output: number of logical ports returned.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR if a general error has occurred
 */
sx_status_t sx_api_host_ifc_trap_filter_get(const sx_api_handle_t  handle,
                                            const sx_access_cmd_t  cmd,
                                            const sx_swid_t        swid,
                                            const sx_trap_id_t     trap_id,
                                            const sx_port_log_id_t log_port_id,
                                            sx_port_log_id_t      *log_port_list_p,
                                            uint32_t              *log_port_cnt_p);

/**
 *  This function binds/unbinds a policer to a trap priority.
 *  The policer type must be a global slow policer.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle           - SX-API handle.
 * @param[in] cmd              - BIND/UNBIND.
 * @param[in] swid             - Switch ID.
 * @param[in] trap_group       - Trap group.
 * @param[in] policer_id       - Policer ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t sx_api_host_ifc_policer_bind_set(const sx_api_handle_t handle,
                                             const sx_access_cmd_t cmd,
                                             const sx_swid_t       swid,
                                             const sx_trap_group_t trap_group,
                                             const sx_policer_id_t policer_id);

/**
 * Get policer ID per trap group.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle         - SX-API handle.
 * @param[in]     swid           - Switch ID.
 * @param[in]     trap_group     - The trap group, must be between 0-63.
 * @param[out]    policer_id     - Policer ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if no policer is bound to trap_group
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_host_ifc_policer_bind_get(const sx_api_handle_t handle,
                                             const sx_swid_t       swid,
                                             const sx_trap_group_t trap_group,
                                             sx_policer_id_t      *policer_id);

/**
 * Get host interface counters.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     handle         - SX-API handle.
 * @param[in]     cmd            - READ/READ_CLEAR.
 * @param[in]     filter_p       - Filter to determine which counters to get.
 * @param[out]    host_ifc_cnt_p - Host interface counters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_host_ifc_counters_get(const sx_api_handle_t                handle,
                                         const sx_access_cmd_t                cmd,
                                         const sx_host_ifc_counters_filter_t *filter_p,
                                         sx_host_ifc_counters_t              *host_ifc_cnt_p);

#endif /* __SX_API_HOST_IFC_H__ */
