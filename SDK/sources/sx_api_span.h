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

#ifndef __SX_API_SPAN_H__
#define __SX_API_SPAN_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>
/************************************************
*  *  Local Defines
************************************************/
#define SPAN_PORT_ATTR_MAX_NUM 16

/************************************************
*  *  Local Macros
************************************************/


/************************************************
*  *  Local Type definitions
************************************************/

/************************************************
*  *  Defines
************************************************/


/************************************************
*  *  Macros
************************************************/

/************************************************
*  *  Type definitions
************************************************/

/************************************************
*  *  Global variables
************************************************/

/************************************************
*  *  Function declarations
************************************************/


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of SPAN module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - SPAN module verbosity level
 * @param[in] api_verbosity_level      - SPAN API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_span_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of SPAN module
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - SPAN module verbosity level
 * @param[out] api_verbosity_level_p    - SPAN API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_span_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API creates a SPAN session and allocates the session ID.
 *
 * EDIT modifies the SPAN session's attributes.
 * DESTROY deletes a SPAN session.
 *
 * Note: In Spectrum systems, the EDIT operation needs another session resource as interim session. As such, if all other
 *   session resources are already allocated, EDIT will fail due to resource unavailability.
 * Note: In case a packet with encapsulation header is mirrored to an analyzer port with size larger than analyzer port's MTU,
 *  truncation should be enabled to avoid packets being discarded. Set truncate size = MTU (encapsulation or smaller).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] access_cmd            - CREATE/EDIT/DESTROY
 * @param[in] span_session_params_p - Generic SPAN session params
 * @param[in,out] span_session_id_p - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if  pointer params is  NULL
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occurs
 * @return SX_STATUS_NO_RESOURCES if pool cannot provide object
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_session_set(const sx_api_handle_t           handle,
                                    const sx_access_cmd_t           cmd,
                                    const sx_span_session_params_t *span_session_params_p,
                                    sx_span_session_id_t           *span_session_id_p);

/**
 * This API gets SPAN session information.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] span_session_id - SPAN session ID
 * @param[out] span_session_params - Session parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_span_session_get(const sx_api_handle_t      handle,
                                    const sx_span_session_id_t span_session_id,
                                    sx_span_session_params_t  *span_session_params_p);

/**
 * This API gets SPAN session ID and returns its mirror agent trap ID.
 *
 * Supported devices: Spectrum2.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  span_session_id - SPAN session ID
 * @param[out] trap_id_p       - Corresponding Trap ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if trap_id_p is NULL
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_session_trap_id_get(const sx_api_handle_t      handle,
                                            const sx_span_session_id_t span_session_id,
                                            sx_trap_id_t              *trap_id_p);

/**
 * This API returns a list of one or more of the current SPAN sessions.
 *
 * The following use case scenarios apply with different input parameters. X = don't-care.
 * 1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, list = X, Count = 0:
 *        In this case, the API will return the total number of SPAN session count from the internal database.
 *
 * 2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, list = Valid, Count = 1:
 *        In this case, the API will check if the specified key exists. If it does, the key will be returned in the list along
 *        with a count of 1. If the key does not exist, an empty list will be returned with count = 0.
 *
 * 3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = X, list is Valid, Count > 1:
 *        A count >1 will be treated as a count of 1 and the behaviour will be same as earlier GET use cases.
 *
 * 4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X, list = Null, Count = 0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, a zero count will return an empty list.
 *
 * 5) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = X, list = Valid, Count > 0:
 *        In this case, the API will return the first SPAN session IDs starting from the head of the database. The total
 *        elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. The key is dont-care but a non-Null return
 *        list pointer must be provided.
 *
 * 6) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = X, list = Valid, Count > 0:
 *        In this case, the API will return the next set of IDs starting from the next valid SPAN session ID after the specified
 *        key. The total elements fetched will be returned as the return count.
 *
 *        Note: return count may be less than or equal to the requested count. If no valid next counter exists in the database
 *        (key = end of list, or invalid key specified, or key too large), an empty list will be returned.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] cmd                  - GET/GET_FIRST/GETNEXT
 * @param[in] span_session_key_p   - Reference SPAN session ID key
 * @param[in] filter_p             - Return only SPAN sessions that match this filter param, if enabled
 * @param[out] span_session_list_p - Return list of SPAN session IDs
 * @param[in,out] span_session_cnt - [in] number of sessions to get/[out] number of sessions retrieved
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_CMD_UNSUPPORTED if invalid cmd is passed
 * @return SX_STATUS_DB_NOT_INITIALIZED if internal database is not initialized
 *
 */

sx_status_t sx_api_span_session_iter_get(const sx_api_handle_t       handle,
                                         const sx_access_cmd_t       cmd,
                                         const sx_span_session_id_t *span_session_key_p,
                                         const sx_span_filter_t     *filter_p,
                                         sx_span_session_id_t       *span_session_list_p,
                                         uint32_t                   *span_session_cnt_p);
/**
 * This API sets SPAN session admin state.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] span_session_id - SPAN session ID
 * @param[in] admin_state - SPAN session Admin state (Enable/Disable).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_session_state_set(const sx_api_handle_t      handle,
                                          const sx_span_session_id_t span_session_id,
                                          const boolean_t            admin_state);

/**
 * This API gets the SPAN session admin state.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] span_session_id - SPAN session ID
 * @param[out] admin_state_p - SPAN Admin state reference
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_span_session_state_get(const sx_api_handle_t      handle,
                                          const sx_span_session_id_t span_session_id,
                                          boolean_t                 *admin_state_p);

/**
 * This API gets the extended state of the SPAN session.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle - SX-API handle
 * @param[in]  span_session_id - SPAN session ID
 * @param[out] span_session_state_p - SPAN session state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_session_state_ext_get(const sx_api_handle_t        handle,
                                              const sx_span_session_id_t   span_session_id,
                                              sx_span_session_state_ext_t *span_session_state_p);

/**
 * This API gets the analyzer port assigned to the SPAN session.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] span_session_id - SPAN session ID
 * @param[out] analyzer_port - Analyzer port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_span_session_analyzer_get(const sx_api_handle_t      handle,
                                             const sx_span_session_id_t span_session_id,
                                             sx_port_log_id_t          *analyzer_port_p);

/**
 * This API gets the mirror ports assigned to the SPAN session.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] span_session_id - SPAN session ID
 * @param[out] mirror_ports_list_p - Array of mirror ports
 * @param[in,out] mirror_ports_cnt_p - Number of mirror ports
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_span_session_mirror_get(const sx_api_handle_t      handle,
                                           const sx_span_session_id_t span_session_id,
                                           sx_span_mirror_t          *mirror_ports_list_p,
                                           uint32_t                  *mirror_ports_cnt_p);

/**
 * This API sets the SPAN session ID using mirror port and direction as key.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE
 * @param[in] mirror_port - Mirror port
 * @param[in] mirror_direction - Mirror direction (ingress/egress)
 * @param[in] span_session_id - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_NO_RESOURCES if pool cannot provide object
 * @return SX_STATUS_ERROR if unexpected behavior occurs*
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_set(const sx_api_handle_t       handle,
                                   const sx_access_cmd_t       cmd,
                                   const sx_port_log_id_t      mirror_port,
                                   const sx_mirror_direction_t mirror_direction,
                                   const sx_span_session_id_t  span_session_id);

/**
 * This API gets the SPAN session ID using mirror port and direction as key.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] mirror_port - Mirror port
 * @param[in] mirror_direction - Mirror direction ingress/egress
 * @param[out] span_session_id_p - Reference to SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_get(const sx_api_handle_t       handle,
                                   const sx_port_log_id_t      mirror_port,
                                   const sx_mirror_direction_t mirror_direction,
                                   sx_span_session_id_t       *span_session_id_p);

/**
 * This API sets the SPAN mirror admin state using mirror_port and direction as key.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] mirror_port - Mirror port
 * @param[in] mirror_direction - Mirror direction (ingress/egress)
 * @param[in] admin_state - Admin state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_NO_RESOURCES if pool cannot provide object
 * @return SX_STATUS_ERROR if unexpected behavior occurs*
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_state_set(const sx_api_handle_t       handle,
                                         const sx_port_log_id_t      mirror_port,
                                         const sx_mirror_direction_t mirror_direction,
                                         const boolean_t             admin_state);

/**
 * This API gets the SPAN mirroring admin state using mirror port and direction as key.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] mirror_port - Mirror port
 * @param[in] mirror_direction - Mirror direction (ingress/egress)
 * @param[out] admin_state_p - Admin state reference
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_state_get(const sx_api_handle_t       handle,
                                         const sx_port_log_id_t      mirror_port,
                                         const sx_mirror_direction_t mirror_direction,
                                         boolean_t                  *admin_state_p);

/**
 * This API sets the SPAN session analyzer ports.
 *
 * Spectrum-2 and Spectrum-3 systems support CPU port as analyzer port.
 *
 * This API allows configuring a LAG as a SPAN session analyzer port. In this case the following
 * conditions apply:
 *   - If the provided LAG has one or more member ports, the SDK shall select one of the LAG member ports
 *     to be an analyzer port.
 *   - If the LAG has no ports then the following caveats apply:
 *           - The SPAN configuration is stored only in the SDK DB.
 *           - If the client tries to enable the SPAN session and the LAG has no members, the SDK will set
 *             the admin state of the SPAN session to true only in the SDK DB.
 *           - When the first port is added to the LAG, this port will be used as the analyzer port and
 *             the SDK will propagate the configuration to the firmware.
 *   - If a LAG member that was chosen by the SDK to be used as the analyzer port is being removed,
 *     the SDK will choose one of other LAG members and configure it as the new analyzer port.
 *   - When the last LAG member is removed, the SDK will disable the SPAN session in the firmware.
 *   - Fine grain LAGs are not supported.
 *   - Redirect LAGs are not supported.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE
 * @param[in] log_port - Analyzer port associated with SPAN
 * @param[in] port_params - Analyzer port parameters
 * @param[in] span_session_id - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_analyzer_set(const sx_api_handle_t                 handle,
                                     const sx_access_cmd_t                 cmd,
                                     const sx_port_log_id_t                log_port,
                                     const sx_span_analyzer_port_params_t *port_params_p,
                                     const sx_span_session_id_t            span_session_id);

/**
 * This API gets the SPAN session using analyzer ports as key.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Analyzer port associated with SPAN
 * @param[out] port_params_p - Analyzer port parameters
 * @param[out] span_session_id_list_p - SPAN session ID array
 * @param[in,out] span_session_cnt_p - SPAN sessions num
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_analyzer_get(const sx_api_handle_t           handle,
                                     const sx_port_log_id_t          log_port,
                                     sx_span_analyzer_port_params_t *port_params_p,
                                     sx_span_session_id_t           *span_session_id_list_p,
                                     uint32_t                       *span_sessions_cnt_p);

/**
 * This API initializes certain aspects of SPAN module behavior. Currently, the only data item controlled by this API
 * is the version of SPAN header attached to mirrored packets.
 * Mirroring resources may be allocated without calling this function using default settings.
 * The API may be called repeatedly to change configuration, but only if a call to sx_api_span_deinit_set intervenes.
 * The function fails if mirroring sessions are already allocated.
 *
 * Note: In Spectrum, calling this API is optional. If not called, the default module configuration is used.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] init_params_p     - Module configuration parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_ALREADY_INITIALIZED if any mirroring resources are already allocated
 * @return SX_STATUS_ALREADY_INITIALIZED if called twice without intervening a call to sx_api_span_deinit_set
 */
sx_status_t sx_api_span_init_set(sx_api_handle_t        handle,
                                 sx_span_init_params_t *init_params_p);

/**
 * This API resets the SPAN init parameters to the default setting. Calls to this API require a prior call to
 * sx_api_span_init_set. The API fails if any mirroring sessions are already allocated when it is called.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_RESOURCE_IN_USE if any mirroring resources are already allocated
 * @return SX_STATUS_DB_NOT_INITIALIZED if called without prior call to sx_api_span_init_set
 */
sx_status_t sx_api_span_deinit_set(sx_api_handle_t handle);

/**
 * This API retrieves or clears dropped packet counters for a mirroring session.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - READ/READ_CLEAR
 * @param[in] span_session_id - SPAN session ID
 * @param[out] counter_set_p - Set of counter values
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_UNSUPPORTED if not supported on this device
 * @return SX_STATUS_CMD_UNSUPPORTED if cmd parameter is invalid
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_session_counter_get(const sx_api_handle_t      handle,
                                            const sx_access_cmd_t      cmd,
                                            const sx_span_session_id_t span_session_id,
                                            sx_span_counter_set_t     *counter_set_p);


/**
 * This API enables or disables mirroring for modules whose own API does not refer to an explicit mirroring session.
 * When enabled, it associates the predefined trap group associated with MIRROR trap ID with the given mirroring session.
 * When disabled, the association between the trap group and the mirroring session is removed. It is possible to call the
 * API repeatedly to replace one mirroring session with another.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE
 * @param[in] span_session_id - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if not supported on this device
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_tables_set(const sx_api_handle_t      handle,
                                          const sx_access_cmd_t      cmd,
                                          const sx_span_session_id_t span_session_id);

/**
 * This API retrieves the mirroring session that was configured using the trap group associated with the MIRROR trap ID for
 * modules whose own API does not refer to an explicit mirroring session.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[out] span_session_id_p - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if not supported on this device
 * @return SX_STATUS_ENTRY_NOT_FOUND if no mirroring session exists
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_tables_get(const sx_api_handle_t handle,
                                          sx_span_session_id_t *span_session_id_p);

/**
 * This API configures mirroring to a SPAN session of dropped packets.
 *
 * SET sets the SPAN session to the new settings, overriding the current configuration.
 * ADD adds more Drop Reasons to the existing configuration.
 * DELETE removes Drop Reasons from existing configuration.
 * DELETE_ALL removes all Drop Reasons from existing configuration.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET/ADD/DELETE/DELETE_ALL
 * @param[in] span_session_id - SPAN session ID
 * @param[in] drop_mirroring_attr_p - Drop Mirroring configuration (only valid or SET)
 * @param[in] drop_reason_list_p - List of Drop Reasons (ignored for DELETE_ALL)
 * @param[in] drop_reason_cnt - Count of Drop Reasons (ignored for DELETE_ALL)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if not supported on this device
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_drop_mirror_set(const sx_api_handle_t                handle,
                                        const sx_access_cmd_t                cmd,
                                        const sx_span_session_id_t           span_session_id,
                                        const sx_span_drop_mirroring_attr_t *drop_mirroring_attr_p,
                                        const sx_span_drop_reason_t         *drop_reason_list_p,
                                        const uint32_t                       drop_reason_cnt);

/**
 * This API retrieves the mirroring session drop reasons configured for router-drop mirroring via the trap IDs for router drops.
 * If drop_reason_list is NULL, the number of drop reasons will be returned in drop_reason_cnt.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] span_session_id - SPAN session ID
 * @param[out] drop_mirroring_attr_p - Drop Mirroring configuration
 * @param[out] drop_reason_list_p - List of Drop Reasons
 * @param[out] drop_reason_cnt_p - Count of Drop Reasons
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if not supported on this device
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_drop_mirror_get(const sx_api_handle_t          handle,
                                        const sx_span_session_id_t     span_session_id,
                                        sx_span_drop_mirroring_attr_t *drop_mirroring_attr_p,
                                        sx_span_drop_reason_t         *drop_reason_list_p,
                                        uint32_t                      *drop_reason_cnt_p);

/**
 * This API binds the mirror binding point to SPAN session with sampling rate.
 *
 * Note: The behavior of Mirror-Latency will be undefined, if CRC parameters on at least one port are
 *       configured in the following way:
 *           - Egress as SX_PORT_CRC_EGRESS_RECALC_MODE_PREVENT (using sx_api_port_crc_params_set API)
 *               AND
 *           - Ingress as SX_TS_OVER_CRC_INGRESS_MODE_ENABLE_E (using sx_api_tele_attributes_set API)
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] cmd      - Bind/UNBIND
 * @param[in] key      - Bind key
 * @param[in] attr     - Bind attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_ALREADY_BOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */

sx_status_t sx_api_span_mirror_bind_set(const sx_api_handle_t             handle,
                                        const sx_access_cmd_t             cmd,
                                        const sx_span_mirror_bind_key_t  *key_p,
                                        const sx_span_mirror_bind_attr_t *attr_p);

/**
 * This API gets the mirror binding attribute.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] key_p     - Bind key
 * @param[out] attr_p   - Bind attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_BOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_bind_get(const sx_api_handle_t            handle,
                                        const sx_span_mirror_bind_key_t *key_p,
                                        sx_span_mirror_bind_attr_t      *attr_p);

/**
 * This API gets the mirror type bound to the SPAN session.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] span_session_id           - SPAN session ID
 * @param[out] mirror_bind_key_list_p   - Array of mirror bind keys
 * @param[in,out] mirror_bind_key_cnt_p - Number of mirror bind keys
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_span_session_mirror_bound_get(const sx_api_handle_t      handle,
                                                 const sx_span_session_id_t span_session_id,
                                                 sx_span_mirror_bind_key_t *mirror_bind_key_list_p,
                                                 uint32_t                  *mirror_bind_key_cnt_p);

/**
 * This API enables mirroring on a mirror object. This configuration is supported on a per port TC, port PG, or a port basis
 * depending on the mirror enable type.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] cmd      - SET/DELETE
 * @param[in] object_p - Mirror enable object
 * @param[in] attr_p   - Mirror enable attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_enable_set(const sx_api_handle_t                 handle,
                                          const sx_access_cmd_t                 cmd,
                                          const sx_span_mirror_enable_object_t *object_p,
                                          const sx_span_mirror_enable_attr_t   *attr_p);

/**
 * This API gets the enable attribute for mirror object
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle     - SX-API handle
 * @param[in]  object_p   - Mirror enable object
 * @param[out] attr_p     - Mirror enable attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if input object is not found
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_enable_get(const sx_api_handle_t                 handle,
                                          const sx_span_mirror_enable_object_t *object_p,
                                          sx_span_mirror_enable_attr_t         *attr_p);

/**
 * This API returns the a list of span objects as per object type.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - supported commands:GET/GET_FIRST/GETNEXT
 * @param[in] object_key_p      - A reference mirror enable object key
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
 *        In this case, the API will return the total number of mirror enabled object count from internal database.
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
 *        In this case, the API will return the first mirror enabled object starting from the head of the database. The total
 *        elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. The key must have type the rest is dont-care but
 *        a non-NULL return list pointer must be provided.
 *
 * - 6) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/(type,port=X,tc_pg=X), filter = X, list = valid, count > 0:
 *        In this case, the API will return the next set of mirror enabled objects starting from the next valid mirror enabled
 *        object after the specified key. The total elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. If no valid next counter exists in the database
 *        (key = end of list, or invalid key specified, or key too large), an empty list will be returned.
 */
sx_status_t sx_api_span_mirror_enable_iter_get(const sx_api_handle_t                handle,
                                               const sx_access_cmd_t                cmd,
                                               sx_span_mirror_enable_object_t      *object_key_p,
                                               sx_span_mirror_enable_iter_filter_t *filter_p,
                                               sx_span_mirror_enable_object_t      *object_list_p,
                                               uint32_t                            *object_cnt_p);

/**
 * This API sets the current UTC time in the device that is used to update timestamp in SPAN headers.
 *
 * Note: This API should not be used when PTP protocol is active and running.
 * Note: UTC is also used for updating time stamp for ingress/egress packets to/from CPU.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - SET
 * @param[in] span_ts     - Current UTC time configuration
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if input parameter is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_span_header_time_stamp_set(const sx_api_handle_t   handle,
                                              const sx_access_cmd_t   cmd,
                                              sx_span_hdr_ts_config_t span_ts);

/**
 * This API binds a policer to a SPAN session. The policer must be defined as a SPAN session policer.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND/UNBIND
 * @param[in] span_session_id - SPAN session ID
 * @param[in] policer_id - Policer ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if access command is not supported
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_ENTRY_ALREADY_BOUND if SPAN session already has a policer
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_session_policer_bind_set(const sx_api_handle_t      handle,
                                                 const sx_access_cmd_t      cmd,
                                                 const sx_span_session_id_t span_session_id,
                                                 const sx_policer_id_t      policer_id);

/**
 * This API returns the policer ID bound to the provided SPAN session ID. When no policer is bound, the API will return
 * SX_STATUS_ENTRY_NOT_FOUND and policer_id_p will be set to SX_POLICER_ID_INVALID.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle - SX-API handle
 * @param[in]  span_session_id - SPAN session ID
 * @param[out] policer_id - Policer ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in database
 * @return SX_STATUS_PARAM_NULL if policer_id_p is NULL
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_session_policer_bind_get(const sx_api_handle_t      handle,
                                                 const sx_span_session_id_t span_session_id,
                                                 sx_policer_id_t           *policer_id_p);

/**
 * This API gets the SPAN attributes.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle - SX-API handle
 * @param[out] span_attrs_p - SPAN attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_UNSUPPORTED if the API is not supported for this device
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_attributes_get(const sx_api_handle_t handle,
                                       sx_span_attrs_t      *span_attrs_p);

/**
 * This API sets the port label that appears in mirror header for a port.
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] log_port                  - logical port.
 * @param[in] span_port_attr_list_p     - span port attribute list.
 * @param[in] span_port_attr_list_size  - span port attribute list size.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_ERROR if the API fails to set the port label.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL.
 * Note - currently, only mirror header port label attribute is supported.
 */
sx_status_t sx_api_span_port_attr_set(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      sx_span_port_attr_t   *span_port_attr_list_p,
                                      uint32_t               span_port_attr_list_size);


/**
 * This API gets the port label that appears in mirror header for a port.
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 * Note - Only GET access command is supported.
 *
 * @param[in]  handle                       - SX-API handle
 * @param[in]  log_port                     - logical port.
 * @param[in]  attr_type                    - span port attribute type.
 * @param[out] span_port_attr_p             - span port attribute.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_ERROR if the API fails to get the port label.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input/output parameter is NULL.
 * Note - currently, only mirror header port label attribute is supported.
 */

sx_status_t sx_api_span_port_attr_get(const sx_api_handle_t    handle,
                                      const sx_port_log_id_t   log_port,
                                      sx_span_port_attr_type_e attr_type,
                                      sx_span_port_attr_t     *span_port_attr_p);

/**
 * This API configures conditional mirroring on a number of ports. This configuration is supported on a per mirror trigger on
 * either elephant or none-elephant flow, per port basis.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - SET/UNSET: per mirror trigger on either elephant or non-elephant flow, UNSET would remove the previous user settings.
 * @param[in] mirror_enable_cfg_list_p  - conditional mirroring configurations of the specific port(s)
 * @param[in] mirror_enable_cnt_p       - number of specific ports to be configured
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_enable_port_set(const sx_api_handle_t             handle,
                                               const sx_access_cmd_t             cmd,
                                               sx_span_mirror_enable_port_set_t *mirror_enable_cfg_list_p,
                                               const uint32_t                    mirror_enable_cnt);

/**
 * This API returns the a list of configurations of mirror triggers on either elephant or non-elephant flow, on specific or serials of ports configured by users.
 *
 * Supported devices: Spectrum4.
 *
 * @param[in] handle                        - SX-API handle
 * @param[in] cmd                           - supported commands:GET/GET_FIRST/GETNEXT
 * @param[in] log_port                      - the specific logical port to be fetched as a key
 * @param[in] filter_p                      - reserved
 * @param[out] mirror_enable_cfg_list_p     - return list of objects
 * @param[in,out] mirror_enable_cnt_p       - [in] number of objects to get (when object_cnt_p=0 will get number of all valid objects per type)
 *                                            [out] number of objects retrieved
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
 * - 1) cmd = SX_ACCESS_CMD_GET, key = log_port, filter = X, list = X, count = 0:
 *        In this case, the API will return the total number of mirror enabled object count from internal database.
 *
 * - 2) cmd = SX_ACCESS_CMD_GET, key = log_port, filter = X, list = Valid, count = 1:
 *        In this case, the API will check if the specified key exists. If it does, the key will be returned in the list along
 *        with a count of 1. If the key does not exist, an empty list will be returned with count = 0.
 *
 * - 3) cmd = SX_ACCESS_CMD_GET, key = log_port, filter = X, list = valid, count > 1:
 *        A count > 1 will be treated as a count of 1 and the behaviour will be the same as earlier GET use cases.
 *
 * - 4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = log_port, filter = X, list = NULL, count = 0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT,a zero count will return an empty list.
 *
 * - 5) cmd = SX_ACCESS_CMD_GET_FIRST, key = log_port, filter = X, list = valid, count > 0:
 *        In this case, the API will return the first mirror enabled object starting from the head of the database. The total
 *        elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. The key must have type the rest is dont-care but
 *        a non-NULL return list pointer must be provided.
 *
 * - 6) cmd = SX_ACCESS_CMD_GETNEXT, key = log_port, filter = X, list = valid, count > 0:
 *        In this case, the API will return the next set of conditional mirror configurations starting from the next valid log port
 *        after the specified key. The total elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. If no valid next counter exists in the database
 *        (key = end of list, or invalid key specified, or key too large), an empty list will be returned (returned count is zero).
 */
sx_status_t sx_api_span_mirror_enable_port_iter_get(const sx_api_handle_t                           handle,
                                                    const sx_access_cmd_t                           cmd,
                                                    const sx_port_log_id_t                          log_port,
                                                    const sx_span_mirror_enable_port_iter_filter_t *filter_p,
                                                    sx_span_mirror_enable_port_set_t               *mirror_enable_cfg_list_p,
                                                    uint32_t                                       *mirror_enable_cnt_p);

#endif /* __SX_API_SPAN_H__ */
