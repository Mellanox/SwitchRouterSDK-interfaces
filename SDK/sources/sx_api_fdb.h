/*
 * Copyright (C) 2014-2021 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_FDB_H__
#define __SX_API_FDB_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/***********************************************
*  API functions
***********************************************/

/**
 * This API sets the log verbosity level of FDB module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - FDB module verbosity level
 * @param[in] api_verbosity_level      - FDB API verbosity level
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of FDB module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - FDB module verbosity level
 * @param[out] api_verbosity_level_p    - FDB API verbosity level
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API sets the FDB age time in seconds. Age time is the time after which automatically learned addresses are deleted
 * from the FDB if they receive no traffic.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] swid       - Switch ID
 * @param[in] age_time   - Time in seconds
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_age_time_set(const sx_api_handle_t   handle,
                                    const sx_swid_t         swid,
                                    const sx_fdb_age_time_t age_time);

/**
 * This API retrieves the FDB age time in seconds. Age time is the time after which automatically-learned addresses are deleted
 * from the FDB if they receive no traffic.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] swid          - Switch ID
 * @param[out] age_time_p   - Time in seconds
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_age_time_get(const sx_api_handle_t handle,
                                    const sx_swid_t       swid,
                                    sx_fdb_age_time_t    *age_time_p);

/**
 * This API triggers an FDB poll for MAC-entry notifications.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] swid     - Virtual switch partition ID
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_NO_RESOURCES         No available resources in the jobs buffer
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_poll_set(const sx_api_handle_t handle,
                                const sx_swid_t       swid);

/**
 * This API sets the FDB polling interval at 0.1 second granularity.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] swid        - Virtual switch partition ID
 * @param[in] interval    - Polling interval in 0.1 seconds
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_polling_interval_set(const sx_api_handle_t           handle,
                                            const sx_swid_t                 swid,
                                            const sx_fdb_polling_interval_t interval);

/**
 * This API gets the FDB polling interval in 0.1 second granularity.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] swid        - Virtual switch partition ID
 * @param[in] interval    - Polling interval in 0.1 seconds
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ERROR                General error
 * @return SX_STATUS_PARAM_NULL           Parameter is NULL
 */
sx_status_t sx_api_fdb_polling_interval_get(const sx_api_handle_t      handle,
                                            const sx_swid_t            swid,
                                            sx_fdb_polling_interval_t* interval);


/**
 * This API adds/deletes UC MAC and UC LAG MAC entries to/from the FDB.
 * In case the operation fails on one or more entries, an error is returned and mac_list_p stores those entries and their
 * quantity is stored in data_cnt. Upon successful completion, SUCCESS is returned and data_cnt_p and mac_list_p are unchanged.
 *
 * Note: If sx_fdb_uc_mac_addr_params_t.dest_type is SX_FDB_UC_MAC_ADDR_DEST_TYPE_ECMP_NEXT_HOP_CONTAINER
 *       - sx_fdb_uc_mac_addr_params_t.entry_type cannot be SX_FDB_UC_AGEABLE
 *       - sx_fdb_uc_mac_addr_params_t.dest.ecmp should point to the ECMP that is one of the following types:
 *         SX_ECMP_CONTAINER_TYPE_NVE_FLOOD or SX_ECMP_CONTAINER_TYPE_NVE_MC
 *
 * Note: In Spectrum systems, when FDB learning is enabled, a packet with the SMAC=MAC1 triggers flushing of remote UC
 *  tunnel-ECMP FDB MAC1 entry from the FDB and a roaming MAC1 event is sent to the CPU, the next packets that have
 *  DMAC=MAC1 will be flooded.
 * Note: In 802.1D mode, instead of providing a VID (VLAN ID) or FID (filtering ID) in mac_list_p->fid_vid, provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - ADD/DELETE
 * @param[in] swid              - Virtual switch partition ID
 * @param[in,out] mac_list_p    - List of MAC record parameters (for deletion, entry_type is ignored)
 * @param[in,out] data_cnt_p    - Number of MAC records to ADD/DELETE
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_NO_RESOURCES         FDB hash bin is full
 * @return SX_STATUS_PARAM_NULL           Any of the parameters is NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_mac_addr_set(const sx_api_handle_t        handle,
                                       const sx_access_cmd_t        cmd,
                                       const sx_swid_t              swid,
                                       sx_fdb_uc_mac_addr_params_t *mac_list_p,
                                       uint32_t                    *data_cnt_p);

/**
 * This API reads MAC entries from the software FDB table which is an exact copy of the hardware database on any device.
 * The output supports up to SX_FDB_MAX_GET_ENTRIES entries which defaults to 64.
 *
 * The function can receive three types of input:
 *
 *   1) To get information for the supplied MAC + VLAN, insert MAC+VLAN data in the key variable.
 *        data_cnt_p should be equal to 1. cmd should be SX_ACCESS_CMD_GET.
 *
 *   2) To get a list of first n<=64 MACs, data_cnt_p should be equal to n. mac_type is the type that should be received.
 *      key_filter_p is the filter type(s) to filter the results by. cmd should be SX_ACCESS_CMD_GET_FIRST.
 *
 *   3) To get a list of n<=64 MACs which comes after a certain MAC record (that does not have to exist), insert
 *      MAC+VLAN data in the key variable. data_cnt_p should be equal to n. mac_type is the type that should be received.
 *      key_filter_p is the filter type(s) to filter the results by. cmd should be SX_ACCESS_CMD_GETNEXT.
 *
 * mac_list_p returns the records' information and their quantity in data_cnt_p for all types of requests.
 *
 * Note: In 802.1D mode, instead of providing a VID (VLAN ID) or FID (filtering ID) in key_p->fid_vid and a FID in
 *   key_filter_p->fid, provide a bridge_id.bridge_id's will be stored in mac_list_p->fid_vid.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] swid           - Virtual switch partition ID
 * @param[in] cmd            - GET/GETNEXT/GET_FIRST
 * @param[in] mac_type       - static/dynamic/all
 * @param[in] key_p          - MAC entry with information for search (MAC+FID)
 * @param[in] key_filter_p   - Filter types used on the mac_list_p (FID/MAC/logical port)
 * @param[out] mac_list_p    - Pointer to list
 * @param[in,out] data_cnt_p - [in] Number of entries to retrieve/[out] retrieved number of entries
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_mac_addr_get(const sx_api_handle_t              handle,
                                       const sx_swid_t                    swid,
                                       const sx_access_cmd_t              cmd,
                                       const sx_fdb_uc_mac_entry_type_t   mac_type,
                                       const sx_fdb_uc_mac_addr_params_t *key_p,
                                       const sx_fdb_uc_key_filter_t      *key_filter_p,
                                       sx_fdb_uc_mac_addr_params_t       *mac_list_p,
                                       uint32_t                          *data_cnt_p);

/**
 * This API counts all MAC entries in the software FDB table (static and dynamic).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] swid        - Virtual switch partition ID
 * @param[out] data_cnt_p - Retrieved number of entries
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  SWID is out of range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_count_get(const sx_api_handle_t handle,
                                    const sx_swid_t       swid,
                                    uint32_t             *data_cnt_p);

/**
 * This API retrieves the number of MACs learned on a port (static and dynamic).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] log_port     - Logical port ID
 * @param[out] data_cnt_p  - Retrieved number of entries
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       Invalid handle
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 *
 */
sx_status_t sx_api_fdb_uc_port_count_get(const sx_api_handle_t  handle,
                                         const sx_port_log_id_t log_port,
                                         uint32_t              *data_cnt_p);

/**
 * This API retrieves the number of MACs learned on an FID (static and dynamic).
 *
 * Note: When in 802.1D mode, instead of providing a FID (filtering ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] swid         - Virtual switch partition ID
 * @param[in] fid          - Filtering database ID
 * @param[out] data_cnt_p  - Retrieved number of entries
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       Invalid handle
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  FID/SWID is out of range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_fid_count_get(const sx_api_handle_t handle,
                                        const sx_swid_t       swid,
                                        const sx_fid_t        fid,
                                        uint32_t             *data_cnt_p);

/**
 * This API sets/removes the limit on the amount of dynamic MACs learned on a port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] cmd        - SET/DELETE
 * @param[in] log_port   - Logical port ID
 * @param[in] limit      - When SET command is used, this is the new limit to set (between 0 and SX_FDB_MAX_ENTRIES)
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       Invalid handle
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Limit is out of range
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_limit_port_set(const sx_api_handle_t  handle,
                                         const sx_access_cmd_t  cmd,
                                         const sx_port_log_id_t log_port,
                                         const uint32_t         limit);

/**
 * This API retrieves the maximum amount of dynamic MACs that can be learned on a port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port  - Logical port ID
 * @param[out] limit_p  - Result limit (if no limit is set, SX_FDB_MAX_ENTRIES is returned)
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       Invalid handle
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_limit_port_get(const sx_api_handle_t  handle,
                                         const sx_port_log_id_t log_port,
                                         uint32_t              *limit_p);

/**
 * This API sets/removes the limit on the amount of dynamic MACs learned on FID (filtering ID).
 *
 * Note: When in 802.1D mode, instead of providing a FID, provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] cmd       - SET/DELETE
 * @param[in] swid      - Virtual switch partition ID
 * @param[in] fid       - Filtering database ID
 * @param[in] limit     - When using SET, this is the new limit to set (between 0 and SX_FDB_MAX_ENTRIES)
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       Invalid handle
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  SWID/FID/limit is out of range
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_limit_fid_set(const sx_api_handle_t handle,
                                        const sx_access_cmd_t cmd,
                                        const sx_swid_t       swid,
                                        const sx_fid_t        fid,
                                        const uint32_t        limit);

/**
 * This API retrieves the maximum amount of dynamic MACs that can be learned on an FID.
 *
 * Note: When in 802.1D mode, instead of providing a FID (filtering ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] swid      - Virtual switch partition ID
 * @param[in] fid       - Filtering database ID
 * @param[out] limit_p  - The result limit (if no limit is set, SX_FDB_MAX_ENTRIES is returned)
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       Invalid handle
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  FID/SWID is out of range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_limit_fid_get(const sx_api_handle_t handle,
                                        const sx_swid_t       swid,
                                        const sx_fid_t        fid,
                                        uint32_t             *limit_p);

/**
 * This API adds/deletes MC MAC entries from the FDB.
 *
 * ADD checks a MC group is already created and returns FAILURE if yes. It allocates and stores the MC group.
 * DELETE deletes MC FDB records, FDB MC ID records, SPGT records, MC group from MCDB, and returns PGI into the pool.
 * ADD_PORTS updates the MC database for adding logical ports and LAG ports for each leaf device:
 *   - Retrieves a list of LAG-member logical ports from LAGLib for all LAG logical ports which belong to this MC group
 *   - Updates the SPGT record for adding the spine, MC members, and the LAGs' member ports
 *   - Adds local ports to FDB MC ID records (if FDB look-up by MC ID is allowed on leaf devices)
 * DELETE_PORTS updates MC database for deleting logical ports and LAG ports for each leaf device:
 *   - Updates the SPGT record for deleting requested ports (if logical port is a LAG port, then all LAG-member logical ports are removed)
 *   - Removes local ports from FDB MC ID records (if FDB look up by MC ID is allowed on leaf devices)
 *
 * Note: MC entries cannot be created and associated with ports at the same time (i.e., create an MC entry before adding ports).
 * Note: The log_port_list_p list should not contain the logical port items which are specified as an Ethernet port and which
 *   are members of a LAG port at same time.
 * Note: When in 802.1D mode, instead of providing a VID (VLAN ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - ADD/DELETE/ADD_PORTS/DELETE_PORTS
 * @param[in] swid             - Virtual switch partition ID
 * @param[in] vid              - Filtering database ID
 * @param[in] group_addr       - MAC group address
 * @param[in] log_port_list_p  - Pointer to a port list
 * @param[in] port_cnt         - Size of port list
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_NO_MEMORY            Memory allocation failure
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS Already added group_addr
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_mac_addr_set(const sx_api_handle_t   handle,
                                       const sx_access_cmd_t   cmd,
                                       const sx_swid_t         swid,
                                       const sx_vid_t          vid,
                                       const sx_mac_addr_t     group_addr,
                                       const sx_port_log_id_t* log_port_list_p,
                                       const uint32_t          port_cnt);

/**
 * This API retrieves MC MAC entries data. User is responsible for memory management of retrieved list.
 * If the log_port_list_p is NULL or port_cnt is 0, the API retrieves the count of MC MAC entries for the VID.
 *
 * Note: If LAG ports are supplied, the log_port_list_p list should contain only LAG-port IDs and not LAG members logical-port IDs.
 * Note: In 802.1D mode, instead of providing a VID (VLAN ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] swid              - Virtual switch partition ID
 * @param[in] vid               - Filtering database ID
 * @param[in] group_addr        - MAC group address
 * @param[out] log_port_list_p  - Pointer to a port list
 * @param[in,out] port_cnt_p    - Size of port list
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_NO_MEMORY            Memory allocation failure
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_mac_addr_get(const sx_api_handle_t handle,
                                       const sx_swid_t       swid,
                                       const sx_vid_t        vid,
                                       const sx_mac_addr_t   group_addr,
                                       sx_port_log_id_t     *log_port_list_p,
                                       uint32_t             *port_cnt_p);

/**
 * This API retrieves a list of one or more MC MAC keys (VLAN ID + MC MAC address).
 *
 * Note: In 802.1D mode, instead of providing a VID (VLAN ID) in key_p->vid and filter_p->vid, provide a bridge_id.
 *  Returned bridge_id's will be stored in key_list_p->vid
 * Note: The following use case scenarios apply with different input parameters. X = don't-care.
 *   1) cmd = SX_ACCESS_CMD_GET, swid = valid, key = X, filter = valid/invalid, key_list = X key_cnt = 0:
 *        In this case the API will return the total number of MC MAC keys filtered by the filter parameter if present.
 *
 *   2) cmd = SX_ACCESS_CMD_GET, swid = valid, key = valid/invalid, filter = valid/invalid, key_list = valid, key_cnt = 1:
 *        A non-NULL key_list pointer must be provided in this case.
 *        The MC MAC key will be returned in the key_list along with a key_cnt of 1 in the following conditions:
 *            a) The key exists, a filter is provided, and the key matches the filter.
 *            b) The key exists and no filter is provided.
 *        An empty list will be returned with key_cnt = 0 in the following conditions:
 *            a) The key does not exist.
 *            b) The key exists, a filter is provided and the key does not match the filter.
 *
 *
 *   3) cmd = SX_ACCESS_CMD_GET, swid = valid, key = valid/invalid, filter = valid/invalid, key_list = valid, key_cnt > 1:
 *        An key_cnt > 1 will be treated as a key_cnt of 1 and the behavior will be same as the earlier GET use cases.
 *
 *   4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, swid = X, key = X, filter = X, key_list = NULL, key_cnt = 0:
 *        A zero key_cnt and an empty key_list will be returned.
 *
 *   5) cmd = SX_ACCESS_CMD_GET_FIRST, swid = valid, key = X, filter = valid/invalid, key_list = valid, key_cnt > 0:
 *        In this case, the API will return a list of MC MAC keys (max key_cnt) starting with first key of the internal database
 *        and matching the filter if present. The input MC MAC key is ignored in this case.
 *        A non-NULL key_list pointer must be provided in this case.
 *
 *   6) cmd = SX_ACCESS_CMD_GETNEXT, swid = valid, key = valid/invalid, filter = valid/invalid, key_list = valid, key_cnt > 0:
 *        In this case, the API will return a list of MC MAC keys (max key_cnt) starting with the next key after the input key
 *        and matching the filter, if present.
 *        A non-NULL key_list pointer must be provided in this case.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param [in] handle            - SX-API handle
 * @param [in] cmd               - GET/GET_FIRST/GET_NEXT
 * @param [in] swid              - Virtual switch partition ID
 * @param [in] key_p             - MC MAC key (VLAN ID + MC MAC address)
 * @param [in] filter_p          - Specify a filter parameter
 * @param [out] key_list_p       - Return list of MC MAC keys
 * @param [in,out] key_cnt_p     - [in] number of MC MAC keys to get/[out] number of MC MAC keys returned
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_mac_addr_iter_get(const sx_api_handle_t         handle,
                                            const sx_access_cmd_t         cmd,
                                            const sx_swid_t               swid,
                                            const sx_fdb_mc_mac_key_t    *key_p,
                                            const sx_fdb_mc_mac_filter_t *filter_p,
                                            sx_fdb_mc_mac_key_t          *key_list_p,
                                            uint32_t                     *key_cnt_p);


/**
 * This API adds/deletes FDB MC MAC entries from/to a multicast container (the MC container should have already been created).
 *
 * The MC container from the parameter "data" should be one of the following types:
 * SX_MC_CONTAINER_TYPE_BRIDGE_MC or SX_MC_CONTAINER_TYPE_VLAN_UNAWARE.
 * An FDB MC MAC entry can be created only if the FID from the parameter "group_key" is equal to the FID from the attributes
 * of the MC container.
 * For MC containers of the type SX_MC_CONTAINER_TYPE_VLAN_UNAWARE, the FID parity validation is skipped.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - ADD/DELETE
 * @param[in] group_key        - FID/MAC key for multicast
 * @param[in] data             - FDB data including action and MC container ID
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_NO_MEMORY            Memory allocation failure
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS Already added group_addr
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_mac_addr_group_set(const sx_api_handle_t     handle,
                                             const sx_access_cmd_t     cmd,
                                             const sx_fdb_mac_key_t  * group_key,
                                             const sx_fdb_mac_data_t * data);


/**
 * This API gets FDB MC MAC entries from a multicast container.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle             - SX-API handle
 * @param[in]  group_key          - FID/MAC key for multicast
 * @param[out] data               - FDB data including action and MC container ID
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_NO_MEMORY            Memory allocation failure
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS Already added group_addr
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_mac_addr_group_get(const sx_api_handle_t    handle,
                                             const sx_fdb_mac_key_t * group_key,
                                             sx_fdb_mac_data_t      * data_p);


/**
 * This API returns a list of one or more FDB MC keys (FID + MC MAC address).
 * The following use case scenarios apply with different input parameters. X = don't-care.
 *
 *   1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, key_list = X, Count =0:
 *        In this case, the API will return the total number of MACs in the Internal database.
 *
 *   2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, key_list = Valid, Count = 1:
 *        In this case the API will check if the specified key exists. If it does, the key will be returned in the key_list
 *        along with a count of 1. If the key does not exist, an empty list will be returned with count = 0.
 *
 *   3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = Valid, key_list = Valid, Count = 1:
 *        In this case, the API will check if the specified key exists. If it does, it will check it against the filter parameter.
 *        If the filter matches, the key will be returned in the key_list along with a count of 1.
 *        If the key does not exist or the filter does not match, an empty list will be returned with count = 0.
 *
 *   4) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = Valid/invalid, key_list is Valid, Count > 1:
 *        A count >1 will be treated as a count of 1 and the behavior will be same as earlier GET use cases.
 *
 *   5) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X, key_list = Null, Count =0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT a zero count  will return an empty list.
 *
 *   6) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = valid/invalid, key_list =  Valid, Count > 0:
 *        In this case, the API will return the first count MACs starting from the head of the database.
 *        The total elements fetched will be returned as the return count.
 *
 *        Note: return count may be less than or equal to the requested count. The key is don't-care.
 *        If a filter is specified, only those MACs that match the filter will be returned.
 *        A non-Null return key_list pointer must be provided.
 *
 *   - 7) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = valid/invalid, key_list = Valid, Count > 0:
 *        In this case the API will return the next set of MACs starting from the next valid MAC after the specified key.
 *        The total elements fetched will be returned as the return count.
 *        If a filter is specified, only those MACs that match the filter will be returned.
 *
 *        Note: return count may be less than or equal to the requested count.
 *        If no valid next MAC exists in the database (key = end of list, or invalid key specified, or key too large),
 *        an empty list will be returned.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3
 *
 * @param [in] cmd               - GET/GET_FIRST/GET_NEXT
 * @param [in] key_p             - MAC key
 * @param [in] filter_p          - Filter parameter
 * @param [out] key_list_p       - Return list of MAC keys
 * @param [in,out] data_cnt_p    - [in] number of MACs to get/[out] number of MACs returned
 *
 * @return SX_STATUS_SUCCESS               Operation completed successfully
 * @return SX_STATUS_PARAM_NULL            Unexpected NULL parameter was passed
 * @return SX_STATUS_PARAM_ERROR           Input parameter is invalid
 * @return SX_STATUS_ERROR                 General error
 * @return SX_STATUS_CMD_UNSUPPORTED       Invalid command
 * @return SX_STATUS_DB_NOT_INITIALIZED    Internal database is not initialized
 * @return SX_STATUS_NO_MEMORY             Memory allocation failure
 */
sx_status_t sx_api_fdb_mc_mac_addr_group_iter_get(const sx_api_handle_t         handle,
                                                  const sx_access_cmd_t         cmd,
                                                  const sx_fdb_mac_key_t       *key_p,
                                                  const sx_fdb_mc_key_filter_t *filter_p,
                                                  sx_fdb_mac_key_t             *key_list_p,
                                                  uint32_t                     *key_cnt_p);
/**
 * This API deletes all learned (dynamic) FDB table entries on a switch partition.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] swid    - Virtual switch partition ID
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_flush_all_set(const sx_api_handle_t handle,
                                        const sx_swid_t       swid);

/**
 * This API deletes the FDB table entries that were learned on a port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port  - Logical port
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_flush_port_set(const sx_api_handle_t  handle,
                                         const sx_port_log_id_t log_port);

/**
 * This API deletes all FDB table entries that were learned on a FID.
 *
 * Note: In 802.1D mode, instead of providing a FID (filtering ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] swid    - Virtual switch partition ID
 * @param[in] fid     - Filtering database ID
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_flush_fid_set(const sx_api_handle_t handle,
                                        const sx_swid_t       swid,
                                        const sx_fid_t        fid);

/**
 * This API deletes all FDB table entries that were learned on the flushed FID and port.
 *
 * Note: When in 802.1D mode, instead of providing a FID (filtering ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port  - Logical port
 * @param[in] fid       - Filtering database ID
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_uc_flush_port_fid_set(const sx_api_handle_t  handle,
                                             const sx_port_log_id_t log_port,
                                             const sx_fid_t         fid);

/**
 * This API deletes all FDB MC tables on a switch partition.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] swid    - Virtual switch partition ID
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_flush_all_set(const sx_api_handle_t handle,
                                        const sx_swid_t       swid);

/**
 * This API deletes all FDB MC table entries that were learned on the flushed FID on a switch partition.
 *
 * Note: When in 802.1D mode, instead of providing a FID (filtering ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] swid    - Virtual switch partition ID
 * @param[in] fid     - Filtering database ID
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_flush_fid_set(const sx_api_handle_t handle,
                                        const sx_swid_t       swid,
                                        const sx_fid_t        fid);

/**
 * This API deletes dynamic FDB table entries according to the provided flush type and parameters.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] flush_data     - Struct including the type and parameters
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_ERROR          Parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_flush_by_type_set(const sx_api_handle_t  handle,
                                         const sx_flush_data_t *flush_data_p);


/**
 * \deprecated This API is deprecated and will be removed in the future.
 *
 * This API maps VLANs to filtering databases for shared VLAN learning (SVL) between VLANs.
 * If independent VLAN learning is desired, a single VLAN should be mapped to a single FID.
 *
 * ADD adds FID to VID mapping record to the selected SWID.
 * DELETE deletes FID to VID mapping record from the selected SWID.
 * DEF_FID value is added to the corresponding VLAN.
 *
 * Note: This API performs FDB flushing by FID before changing FID-to-VID mapping.
 * Note: Only independent learning is supported in the current release.
 * Note: This API is only valid in 802.1Q mode.
 *
 *
 * Supported devices: Not supported.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] cmd          - add/delete
 * @param[in] swid         - Virtual switch partition ID
 * @param[in] fid          - Filtering database ID
 * @param[in] vid          - VLAN ID
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_fid_vlan_member_set(const sx_api_handle_t handle,
                                           const sx_access_cmd_t cmd,
                                           const sx_swid_t       swid,
                                           const sx_fid_t        fid,
                                           const sx_vid_t        vid);

/**
 * This API sets the SWID's learning parameters into the system's database.
 *
 * Note: Only independent learning is supported in the current release.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] swid         - Virtual switch ID
 * @param[in] learn_ctrl   - Is independent/shared learning and is roaming enabled/disabled
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_global_params_set(const sx_api_handle_t     handle,
                                         const sx_swid_t           swid,
                                         const sx_fdb_learn_ctrl_t learn_ctrl);

/**
 *  This API retrieves the SWID's learning parameters from the system's database.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] swid            - Switch (virtual) ID (whose parameters to retrieve)
 * @param[out] learn_ctrl_p   - Is learning mode independent/shared and is roaming enabled/disabled
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_global_params_get(const sx_api_handle_t handle,
                                         const sx_swid_t       swid,
                                         sx_fdb_learn_ctrl_t  *learn_ctrl_p);

/**
 * This API sets the FDB learning mode per SWID affecting all ports and VLANs in the SWID.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] swid         - Virtual switch partition ID
 * @param[in] learn_mode   - New SWID's learn mode
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_learn_mode_set(const sx_api_handle_t     handle,
                                      const sx_swid_t           swid,
                                      const sx_fdb_learn_mode_t learn_mode);

/**
 * This API retrieves the FDB learning mode per SWID.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] swid          - Virtual switch partition ID
 * @param[out] learn_mode_p - SWID's learn mode
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_learn_mode_get(const sx_api_handle_t handle,
                                      const sx_swid_t       swid,
                                      sx_fdb_learn_mode_t  *learn_mode_p);

/**
 * This API sets a FID's learn mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] swid        - Switch ID
 * @param[in] fid         - Filtering identifier
 * @param[in] learn_mode  - FID's learn mode
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_fid_learn_mode_set(const sx_api_handle_t     handle,
                                          const sx_swid_t           swid,
                                          const sx_fid_t            fid,
                                          const sx_fdb_learn_mode_t learn_mode);

/**
 * This API gets a FID's learn mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] swid          - Switch ID
 * @param[in] fid           - Filtering identifier
 * @param[out] learn_mode_p - FID's learn mode
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_fid_learn_mode_get(const sx_api_handle_t handle,
                                          const sx_swid_t       swid,
                                          const sx_fid_t        fid,
                                          sx_fdb_learn_mode_t  *learn_mode_p);

/**
 * This API sets a port's learn mode.
 *
 * Note: The learn mode on the NVE port can be configured only when there is a connected NVE tunnel in the system.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - Logical port number
 * @param[in] learn_mode  - Port's learn mode
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_port_learn_mode_set(const sx_api_handle_t     handle,
                                           const sx_port_log_id_t    log_port,
                                           const sx_fdb_learn_mode_t learn_mode);

/**
 * This API gets a port's learn mode.
 *
 * Note: The API can retrieve the learn mode on the NVE port only when there is a connected NVE tunnel in the system.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical port number
 * @param[out] learn_mode_p - Port's learn mode
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_port_learn_mode_get(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t log_port,
                                           sx_fdb_learn_mode_t   *learn_mode_p);

/**
 * This API sets FDB notify parameters.
 *
 * Note: This API only takes effect when controlled learn mode is set.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] swid              - Virtual switch partition ID
 * @param[in] notify_params_p   - New notify parameters
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           Any parameters are NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_notify_params_set(const sx_api_handle_t         handle,
                                         const sx_swid_t               swid,
                                         const sx_fdb_notify_params_t *notify_params_p);

/**
 * This API gets FDB notify parameters.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] swid              - Virtual switch partition ID
 * @param[out] notify_params_p  - SWID's notify params
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           Any parameters are NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_notify_params_get(const sx_api_handle_t   handle,
                                         const sx_swid_t         swid,
                                         sx_fdb_notify_params_t *notify_params_p);

/**
 * This API is used to block ports from flooding a selected FID.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - ADD_PORTS/DELETE_PORTS/REPLACE_ALL_PORTS/ DELETE_ALL_PORTS
 * @param[in] swid        - Virtual switch partition ID
 * @param[in] fid         - VID/Bridge-ID to apply blocking list
 * @param[in] type        - Flood type to control
 * @param[in] ports_count - Number of items in ports_list array
 * @param[in] ports_list  - Array of logical ports
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_PARAM_NULL           ports_list is null and cmd is not DELETE_ALL_PORTS
 * @return SX_STATUS_UNSUPPORTED          Flood control is not supported in the switch
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_ERROR                General error
 *
 */
sx_status_t sx_api_fdb_flood_control_set(const sx_api_handle_t          handle,
                                         const sx_access_cmd_t          cmd,
                                         const sx_swid_t                swid,
                                         const sx_fid_t                 fid,
                                         sx_flood_control_type_t        type,
                                         const uint16_t                 ports_count,
                                         const sx_port_log_id_t * const ports_list);

/**
 * This API is used to retrieve the list of ports on which flood control has been enabled.
 * ports_count will be updated with the number of blocked ports.
 * If ports_count is non-zero, user is responsible for memory management of ports_list.
 * Passing ports_count as 0 and ports_list NULL, will return a count of the number of ports.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] swid            - Virtual switch partition ID
 * @param[in] fid             - VID/Bridge-ID to apply blocking list
 * @param[in] type            - Flood type to control.
 * @param[in,out] ports_count - Number of items in ports_list array, returned as number of actual ports
 * @param[out] ports_list     - (Optional) Array to fill blocked logical ports.
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_UNSUPPORTED          Flood control is not supported in the switch.
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_PARAM_NULL           ports_list is null and ports_count is not 0.
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_flood_control_get(const sx_api_handle_t    handle,
                                         const sx_swid_t          swid,
                                         const sx_fid_t           fid,
                                         sx_flood_control_type_t  type,
                                         uint16_t * const         ports_count,
                                         sx_port_log_id_t * const ports_list);

/**
 * This API is used to manage flood control for tunnels.
 * Configuration from this API extends configuration from sx_api_fdb_flood_control_set for tunnel support.
 * For each tunnel, flooding for specified bridge can be added or removed.
 *
 * The MC container that is pointed by the parameter "flood_vector" should be one of the following types:
 * SX_MC_CONTAINER_TYPE_NVE_FLOOD, SX_MC_CONTAINER_TYPE_BRIDGE_MC, or SX_MC_CONTAINER_TYPE_VLAN_UNAWARE.
 * An MC container of the type SX_MC_CONTAINER_TYPE_NVE_FLOOD or SX_MC_CONTAINER_TYPE_BRIDGE_MC container can be bound to
 * a given FID only if the FID is equal to a FID from the attributes of the MC container.
 * On Spectrum, an MC container of the SX_MC_CONTAINER_TYPE_BRIDGE_MC type cannot be used as a tunnel flood vector if
 * sx_tunnel_nve_general_params_t.mc_ecmp_enabled != sx_tunnel_nve_general_params_t.flood_ecmp_enabled.
 * For MC containers of the type SX_MC_CONTAINER_TYPE_VLAN_UNAWARE, the FID parity validation is skipped.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] cmd			 - ADD/DELETE/SET
 * @param[in] swid           - Virtual switch partition ID
 * @param[in] fid            - FID
 * @param[in] flood_vector   - MC container which next-hops are used to flood through a tunnel
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND      Tunnel or fid doesn't exists
 * @return SX_STATUS_ENTRY_ALREADY_BOUND  FID already have flooding vector
 * @return SX_STATUS_UNSUPPORTED          API is not supported for this device
 * @return SX_STATUS_ERROR                General error
 * */
sx_status_t sx_api_fdb_flood_set(const sx_api_handle_t      handle,
                                 const sx_access_cmd_t      cmd,
                                 const sx_swid_t            swid,
                                 const sx_fid_t             fid,
                                 const sx_mc_container_id_t flood_vector);
/**
 * This API is used to get flood control settings for a tunnel.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle         - SX-API handle
 * @param[in]  swid           - Virtual switch partition ID
 * @param[in]  fid            - FID
 * @param[out] flood_vector   - MC container that contains a flooding vector as ECMP object
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND      Flooding vector not set
 * @return SX_STATUS_UNSUPPORTED          API is not supported for this device
 * @return SX_STATUS_ERROR                General error
 * */
sx_status_t sx_api_fdb_flood_get(const sx_api_handle_t  handle,
                                 const sx_swid_t        swid,
                                 const sx_fid_t         fid,
                                 sx_mc_container_id_t * flood_vector);

/**
 * \deprecated This API is deprecated and will be removed in the future.
 *
 * This API is used to retrieve flooding counters of the switch.
 *
 * Supported devices: N/A
 *
 * @param[in] handle    - SX-API handle
 * @param[in] cmd       - READ/READ_CLEAR
 * @param[in] swid      - Virtual switch partition ID
 * @param[out] counters - Counters struct to store retrieved information
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_UNSUPPORTED          Flooding counters are not supported on the switch
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_NULL           Counters are null
 * @return SX_STATUS_ERROR                General error
 */

sx_status_t sx_api_fdb_flood_counter_get(const sx_api_handle_t       handle,
                                         const sx_access_cmd_t       cmd,
                                         const sx_swid_t             swid,
                                         sx_flood_counters_t * const counters);

/**
 * \deprecated This API is deprecated and will be removed in the future.
 *
 * This API is used to clear flooding counters of the switch.
 *
 * Supported devices: N/A
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid   - Virtual switch partition ID
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_UNSUPPORTED          Flooding counters are not supported on the switch
 */
sx_status_t sx_api_fdb_flood_counter_clear(const sx_api_handle_t handle,
                                           const sx_swid_t       swid);

/**
 * This API sets a port's FDB miss protect mode.
 * When enabled, the source MAC (SMAC) will not be learned and will be used for security lookup on the packet.
 *
 * Note: This API is not supported in 802.1D mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - Logical port number
 * @param[in] enable      - Enable/disable SMAC miss port protection
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 */
sx_status_t sx_api_fdb_src_miss_protect_set(const sx_api_handle_t  handle,
                                            const sx_port_log_id_t log_port,
                                            const boolean_t        enable);

/**
 * This API gets ports' FDB SMAC miss protect mode status.
 *
 * Note: This API is not supported in 802.1D mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical port number
 * @param[out] enable_p     - Port's FDB miss protection status
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 */
sx_status_t sx_api_fdb_src_miss_protect_get(const sx_api_handle_t  handle,
                                            const sx_port_log_id_t log_port,
                                            boolean_t             *enable_p);

/**
 * This API sets up FDB source miss protection drop counter.
 *
 * Note: This API is not supported in 802.1D mode
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - CREATE/DESTROY
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_ERROR                General error
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 */
sx_status_t sx_api_fdb_src_miss_protect_drop_cntr_set(const sx_api_handle_t handle,
                                                      const sx_access_cmd_t cmd);

/**
 * This API gets the FDB source miss protection drop counters.
 *
 * Note: This API is not supported in 802.1D mode
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - GET/GET_AND_CLEAR
 * @param[out] dropped_pkts_cntr_p - port's source miss protection packet counter
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_ERROR                General error
 * @return SX_STATUS_PARAM_NULL if dropped_pkts_cntr is null
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 */
sx_status_t sx_api_fdb_src_miss_protect_drop_cntr_get(const sx_api_handle_t handle,
                                                      const sx_access_cmd_t cmd,
                                                      uint64_t             *dropped_pkts_cntr_p);

/**
 * This API sets the IGMPv3 state.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - SET
 * @param[in] fid                       - FID
 * @param[in] fdb_igmpv3_snooping_state - Enable/ Disable
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_NO_MEMORY            Memory allocation failure
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS If snooping is already enabled
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_igmpv3_state_set(const sx_api_handle_t       handle,
                                        const sx_access_cmd_t       cmd,
                                        const sx_fid_t              fid,
                                        const sx_fdb_igmpv3_state_t fdb_igmpv3_snooping_state);

/**
 * This API gets the IGMPv3 state.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - GET
 * @param[in] fid                       - FID
 * @param[out] fdb_igmpv3_snooping_state- Pointer to the IGMP v3 state
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_igmpv3_state_get(const sx_api_handle_t  handle,
                                        const sx_access_cmd_t  cmd,
                                        const sx_fid_t         fid,
                                        sx_fdb_igmpv3_state_t* fdb_igmpv3_snooping_state);

/**
 * This API sets MC IP entries using a multicast container as the destination.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - ADD/DELETE/DELETE_ALL
 * @param[in] mc_fdb_mc_ip_key - Structure containing the FID/SIP/DIP of the MC group
 * @param[in] fdb_mc_ip_action - Structure containing Action/Container ID/Trap
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_NO_MEMORY            Memory allocation failure
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS group_addr is already added
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_ip_addr_group_set(const sx_api_handle_t        handle,
                                            const sx_access_cmd_t        cmd,
                                            const sx_fdb_mc_ip_key_t   * mc_fdb_mc_ip_key,
                                            const sx_fdb_mc_ip_action_t* fdb_mc_ip_action);

/**
 * This API gets MC IP entries using a multicast container as destination.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] mc_fdb_mc_ip_key  - Structure containing the FID/SIP/DIP of the MC group
 * @param[out] fdb_mc_ip_action - Pointer to a Structure containing Action/Container ID/Trap
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_NO_MEMORY            Memory allocation failure
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_ip_addr_group_get(const sx_api_handle_t     handle,
                                            const sx_fdb_mc_ip_key_t* mc_fdb_mc_ip_key,
                                            sx_fdb_mc_ip_action_t   * fdb_mc_ip_action_p);

/**
 * This API binds a flow counter to a MC IP Entry.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] key_p            - Structure containing the FID/SIP/DIP of the MC group
 * @param[in] cmd              - Command: SX_ACCESS_CMD_ADD/SX_ACCESS_CMD_DELETE
 * @param[in] counter_id       - Counter ID for adding/deleting from rule
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_NO_MEMORY            Memory allocation failure
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS Counter is already added
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_ip_addr_group_counter_bind_set(const sx_api_handle_t      handle,
                                                         const sx_access_cmd_t      cmd,
                                                         const sx_fdb_mc_ip_key_t  *key_p,
                                                         const sx_flow_counter_id_t counter_id);

/**
 * This API gets the flow counter bound to a MC IP entry.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] key_p            - Structure containing the FID/SIP/DIP of the MC group
 * @param[out] counter_id      - Pointer to counter
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_INVALID_HANDLE       NULL handle received
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameter exceeds the range
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_NO_MEMORY            Memory allocation failure
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_ip_addr_group_counter_bind_get(const sx_api_handle_t     handle,
                                                         const sx_fdb_mc_ip_key_t *key_p,
                                                         sx_flow_counter_id_t     *counter_id_p);

/**
 * This API sets the unregistered MC flood mode.
 *
 * Note: When in 802.1D mode, instead of providing a VID (VLAN ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] swid              - Virtual switch partition ID
 * @param[in] vid               - VLAN ID
 * @param[in] urmc_flood_mode   - Unregistered MC flood mode: FLOOD/PRUNE
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_unreg_mc_flood_mode_set(const sx_api_handle_t           handle,
                                               const sx_swid_t                 swid,
                                               const sx_vid_t                  vid,
                                               const sx_fdb_unreg_flood_mode_t urmc_flood_mode);

/**
 * This API retrieves the unregistered MC flood mode.
 *
 * Note: When in 802.1D mode, instead of providing a VID (VLAN ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] swid                   - Virtual switch partition ID
 * @param[in] vid                    - VLAN ID
 * @param[out] urmc_flood_mode_p     - Unregister MC flood mode: FLOOD/PRUNE
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_unreg_mc_flood_mode_get(const sx_api_handle_t      handle,
                                               const sx_swid_t            swid,
                                               const sx_vid_t             vid,
                                               sx_fdb_unreg_flood_mode_t *urmc_flood_mode_p);

/**
 * This API sets unregistered MC flood ports.
 *
 * Note: When in 802.1D mode, instead of providing a VID (VLAN ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] swid              - Virtual switch partition ID
 * @param[in] vid               - VLAN ID
 * @param[in] log_port_list_p   - Pointer to a port list, port may be a LAG or physical port
 * @param[in] port_cnt          - Size of port list
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_unreg_mc_flood_ports_set(const sx_api_handle_t   handle,
                                                const sx_swid_t         swid,
                                                const sx_vid_t          vid,
                                                const sx_port_log_id_t *log_port_list_p,
                                                const uint32_t          port_cnt);

/**
 * This API retrieves unregistered MC flood ports.
 *
 * Note: When in 802.1D mode, instead of providing a VID (VLAN ID), provide a bridge_id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] swid              - Virtual switch partition ID
 * @param[in] vid               - VLAN ID
 * @param[out] log_port_list_p  - Pointer to a port list, port can be LAG or physical port
 * @param[in,out] port_cnt_p    - Size of port list
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND      Requested element is not found in the database
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_unreg_mc_flood_ports_get(const sx_api_handle_t handle,
                                                const sx_swid_t       swid,
                                                const sx_vid_t        vid,
                                                sx_port_log_id_t     *log_port_list_p,
                                                uint32_t             *port_cnt_p);

/**
 * This API is used to set the flooding mode and vector for unregistered IPv4 and IPv6 MC traffic.
 *
 * Flooding mode includes FLOOD/PRUNE:
 * PRUNE provides the MC container with a list of ports.
 * FLOOD means the flood_vector is N/A. SDK will set the flooding vector to be all VLAN members.
 *
 * SET configures URMC according flood_attr.
 * UNSET configures URMC mode to be FLOOD to release MC container.
 *
 * Note: In order to have a separate vector for unregistered IPv6 MC traffic, the following flag should be enabled
 * sdk_init_params.fdb_params.unreg_mc_ipv6_flood_en as part of SDK init. If it is not enabled, the broadcast vector
 * will apply for unregistered IPv6 MC traffic.
 *
 * Note: This API is mutually exclusive and supersedes the following APIs below which will be deprecated:
 *    -sx_api_fdb_unreg_mc_flood_mode_set(..)
 *    -sx_api_fdb_unreg_mc_flood_ports_set(..)
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] access_cmd            - SET/UNSET
 * @param[in] flood_key_p           - Flood key
 * @param[in] flood_attr_p          - Flood attributes
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_ERROR                General error
 *
 */
sx_status_t sx_api_fdb_unreg_mc_flood_mode_ext_set(const sx_api_handle_t               handle,
                                                   const sx_access_cmd_t               access_cmd,
                                                   const sx_fdb_unreg_mc_flood_key_t * flood_key_p,
                                                   const sx_fdb_unreg_mc_flood_attr_t* flood_attr_p);


/**
 * This API is used to get the flooding mode and vector for unregistered IPv4 and IPv6 MC traffic.
 * Only one type can be provided at time.
 *
 * Flooding mode includes FLOOD/PRUNE
 * PRUNE means flood_attr flood_vector will contains MC container with log_ports.
 * FLOOD means flood_vector will return SX_MC_CONTAINER_ID_INVALID.
 *
 * Note: In order to have separate vector for unregistered IPv6 MC traffic the following flag should be enabled:
 * sdk_init_params.fdb_params.unreg_mc_ipv6_flood_en as part of SDK init.
 * If it is not enabled, the broadcast vector will apply for unregistered IPv6 MC traffic.
 *
 * This API is mutually exclusive and supersedes the following APIs below which will be deprecated:
 *      - sx_api_fdb_unreg_mc_flood_mode_get(..)
 *      - sx_api_fdb_unreg_mc_flood_ports_get(..)
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] flood_key_p      - Flood key
 * @param[out] flood_attr_p    - Flood attributes
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_UNSUPPORTED          Flood control is not supported in the switch
 * @return SX_STATUS_PARAM_ERROR          Input parameter is invalid
 * @return SX_STATUS_PARAM_NULL           ports_list is null and ports_count is not 0
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_unreg_mc_flood_mode_ext_get(const sx_api_handle_t               handle,
                                                   const sx_fdb_unreg_mc_flood_key_t * flood_key_p,
                                                   sx_fdb_unreg_mc_flood_attr_t* const flood_attr_p);


/**
 * This API reads and/or clears activity on a specified multicast IP Entry.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle.
 * @param[in] cmd           - READ\READ_CLEAR
 * @param[in] fdb_mc_key_p  - MC entry key (FID, source IP address, group address)
 * @param[out] activity_p   - Activity state
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Key parameters exceed allowed range
 * @return SX_STATUS_CMD_UNSUPPORTED      Unsupported command
 * @return SX_STATUS_ENTRY_NOT_FOUND      MC route is not found
 * @return SX_STATUS_PARAM_NULL           A parameter is NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fdb_mc_ip_addr_group_activity_get(const sx_api_handle_t     handle,
                                                     const sx_access_cmd_t     cmd,
                                                     const sx_fdb_mc_ip_key_t *key_p,
                                                     boolean_t                *activity_p);

/**
 * This API initiates a notification regarding active MC FDB entries in the system.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle    - SX-API handle
 * @param[in] cmd	    - READ/READ_CLEAR
 * @param[in] filter_p  - Activity-notifier filter
 *
 * @return SX_STATUS_SUCCESS             Operation completed successfully
 * @return SX_STATUS_CMD_UNSUPPORTED     Unsupported command
 * @return SX_STATUS_PARAM_ERROR         Parameter is invalid
 * @return SX_STATUS_RESOURCE_IN_USE     Notification procedure is already running
 * @return SX_STATUS_ERROR               General error
 */
sx_status_t sx_api_fdb_mc_ip_addr_group_activity_notify(const sx_api_handle_t        handle,
                                                        const sx_access_cmd_t        cmd,
                                                        const sx_fdb_mc_ip_filter_t *filter_p);

/**
 *  This API protects user traffic from logical port failures.
 *
 *  When a logical port goes DOWN, the API can redirect UC traffic from this logical port to a tunnel,
 *  and once the port is UP again, the API can redirect UC traffic back to this port.
 *
 *  The redirection is done by changing the destination according to protection_data of all UC FDB
 *  entries that match with protection_key.
 *
 *  Redirecting FDB entries to/from a port updates the number of FDB entries on that port,
 *  but the limit of FDB entries is not enforced, so it may cause a state where the limit is exceeded.
 *
 *  The API does not affect learnt FDB entries that were not processed before calling this API.
 *  In the CONTROL learn mode, the user should process notifications about each learnt FDB entry using
 *  sx_api_fdb_uc_mac_addr_set by himself.
 *  In the AUTO learn mode, SDK configures each learnt FDB entries according to the learning source (a
 *  port or a tunnel).
 *
 *  Notes:
 *    The API should not be called during the ISSU process or during the FAST boot.
 *
 *  Notes for Spectrum:
 *    The redirection from a logical port to a tunnel using a tunnel next-hop is the only supported
 *    redirection.
 *    In other words, the only valid combination of destinations is:
 *    protection_key.protection_object.dest_type == SX_FDB_UC_MAC_ADDR_DEST_TYPE_LOGICAL_PORT and
 *    protection_data.protection_object.dest_type == SX_FDB_UC_MAC_ADDR_DEST_TYPE_NEXT_HOP.
 *
 *  Notes for Spectrum2, Spectrum3:
 *    Only the following redirection options are supported:
 *      - From a logical port to a tunnel using a tunnel next-hop.
 *      - From a logical port to a tunnel using an ECMP NVE container - this is the recommended way.
 *      - From an ECMP NVE container to a logical port.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] protection_key_p  - criteria for selecting UC FDB entries that will be redirected
 * @param[in] protection_data_p - a new destination for redirected entries
 *
 * @return SX_STATUS_SUCCESS            if the operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE     if a NULL handle is received
 * @return SX_STATUS_ENTRY_NOT_FOUND    if a given parameter contains invalid data,
 *                                      e.g. a FID that does not exist
 * @return SX_STATUS_PARAM_NULL         if a parameter is NULL
 * @return SX_STATUS_ERROR              for a general error
 */
sx_status_t sx_api_fdb_uc_local_protect_set(const sx_api_handle_t                  handle,
                                            const sx_api_fdb_uc_protection_key_t  *protection_key_p,
                                            const sx_api_fdb_uc_protection_data_t *protection_data_p);

#endif /* __SX_API_FDB_H__ */
