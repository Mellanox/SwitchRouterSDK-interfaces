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


#ifndef __SX_API_MC_CONTAINER_H__
#define __SX_API_MC_CONTAINER_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of MC_CONTAINER module.
 *
 * Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - MC_CONTAINER module verbosity level
 * @param[in] api_verbosity_level      - MC_CONTAINER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_mc_container_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        const sx_verbosity_level_t      module_verbosity_level,
                                                        const sx_verbosity_level_t      api_verbosity_level);

/**
 * Gets the log verbosity level of MC_CONTAINER module.
 *
 * Supported devices: SwitchX, SwitchX2, Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - MC_CONTAINER module verbosity level
 * @param[out] api_verbosity_level_p    - MC_CONTAINER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_mc_container_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        sx_verbosity_level_t           *module_verbosity_level_p,
                                                        sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API allows to manipulate a multicast container.
 *
 * CREATE creates a new container with the specified list of next_hops_cnt, next hops in next_hop_list_p,
 *   and returns its new container ID in container_id_p.
 * ADD/DELETE adds or deletes the next hops specified by next_hop_list_p and next_hop_cnt to/from an existing container
 *   specified by container_id_p.
 * SET replaces the contents of an existing container specified by container_id_p, with the specified list of next hops
 *   in next_hop_list_p.
 * DESTROY deletes an existing container specified by container_id_p.
 * DELETE_ALL deletes all existing containers.
 *
 * Note: A container in use (e.g. by a multicast route or ACL) cannot be destroyed.
 * Note: A container may contain, at most, RM_API_ROUTER_RIFS_MAX next hops.
 * Note: An MC container of the SX_MC_CONTAINER_TYPE_BRIDGE_MC type can contain multiple next hops of the SX_MC_NEXT_HOP_TYPE_LOG_PORT type
 *   and either multiple next hops of the SX_MC_NEXT_HOP_TYPE_TUNNEL_ENCAP_IP type or one next hop of the SX_MC_NEXT_HOP_TYPE_ECMP type.
 *   A next hop of the SX_MC_NEXT_HOP_TYPE_ECMP type can point to an ECMP container of the SX_ECMP_CONTAINER_TYPE_NVE_MC type only.
 * Note: An MC container of the SX_MC_CONTAINER_TYPE_NVE_FLOOD type can contain either multiple next hops of
 *   the SX_MC_NEXT_HOP_TYPE_TUNNEL_ENCAP_IP type or one next hop of the SX_MC_NEXT_HOP_TYPE_ECMP type.
 *   A next hop of the SX_MC_NEXT_HOP_TYPE_ECMP type can point to an ECMP container of the SX_ECMP_CONTAINER_TYPE_NVE_FLOOD type only.
 * Note: An MC container of the SX_MC_CONTAINER_TYPE_VLAN_UNAWARE type can contain either multiple next hops of
 *   the SX_MC_NEXT_HOP_TYPE_TUNNEL_ENCAP_IP type or one next hop of the SX_MC_NEXT_HOP_TYPE_ECMP type.
 *   A next hop of the SX_MC_NEXT_HOP_TYPE_ECMP type can point to an ECMP container of the following types:
 *   SX_ECMP_CONTAINER_TYPE_NVE_FLOOD or SX_ECMP_CONTAINER_TYPE_NVE_MC.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - CREATE/ADD/DELETE/SET/DESTROY/DELETE_ALL
 * @param[in,out] container_id_p  - Specifies or returns the container ID
 * @param[in] next_hop_list_p     - List of next hops for the container
 * @param[in] next_hop_cnt        - Amount of next hops in next_hop_list_p
 * @param[in] container_attr_p    - Container attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is a NULL pointer
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container ID does not exist
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation
 * @return SX_STATUS_RESOURCE_IN_USE if group is in use and cannot be destroyed
 */
sx_status_t sx_api_mc_container_set(const sx_api_handle_t               handle,
                                    const sx_access_cmd_t               cmd,
                                    sx_mc_container_id_t               *container_id_p,
                                    const sx_mc_next_hop_t             *next_hop_list_p,
                                    const uint32_t                      next_hop_cnt,
                                    const sx_mc_container_attributes_t* container_attr_p);

/**
 * This API retrieves information about a multicast container.
 *
 * GET retrieves information about the container specified by container_id_p.
 * GET_FIRST retrieves the first container, its ID, next hops, and attributes.
 * GET_NEXT retrieves the next container after container_id_p, its ID, next hops, and attributes.
 * COUNT returns the number of existing containers in *next_hop_cnt.
 *
 * Note: *next_hop_cnt should contain the maximum amount of next hops to retrieve.
 * Note: If next_hop_list_p is NULL, then next hops are not retrieved at all.
 *        If *next_hop_cnt is 0, or if next_hop_list_p is NULL, then the amount of next hops is returned in *next_hop_cnt.
 *       If container_attr is NULL, then attributes are not retrieved.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - GET/GET_FIRST/GET_NEXT/COUNT
 * @param[in] container_id        - Container ID whose attributes needs to be retrieved
 * @param[out] next_hop_list_p    - List of next hops in the container
 * @param[in,out] next_hop_cnt_p  - [in] maximum amount of next hops to retrieve/[out]returns the amount of next hops retrieved
 * @param[out] container_attr_p   - Returns the container attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if access command is not supported
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container does not exist or no more containers are found
 */
sx_status_t sx_api_mc_container_get(const sx_api_handle_t         handle,
                                    const sx_access_cmd_t         cmd,
                                    sx_mc_container_id_t          container_id,
                                    sx_mc_next_hop_t             *next_hop_list_p,
                                    uint32_t                     *next_hop_cnt_p,
                                    sx_mc_container_attributes_t *container_attr_p);

/**
 * This API retrieves a list of multicast Containers.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - GET/GET_NEXT/GET_FIRST
 * @param[in] container_id_key       - Container ID to use as key
 * @param[in] container_filter_p     - Filter to use (not supported yet)
 * @param[out] container_id_list_p   - Pointer to the list of Container IDs returned
 * @param[in,out] container_id_cnt_p - [in] number of entries to retrieve/[out] retrieved  number of entries
 *
 * The following use case scenarios apply with different input parameters X = don't-care
 *   1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, list = X, Count = 0:
 *        In this case, the API will return the total number of containers in the internal database.
 *
 *   2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, list = Valid, Count = 1:
 *        In this case, the API will check if the specified key exists. If it does, the key will be returned in the list
 *        along with a count of 1. If the key does not exist, an empty list will be returned with count = 0.
 *
 *   3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = X, list is Valid, Count > 1:
 *        A count > 1 will be treated as a count of 1 and the behavior will be same as earlier GET use cases.
 *
 *   5) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X, list = Null, Count = 0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, a zero count will return an empty list.
 *
 *   6) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = X, list = Valid, Count > 0:
 *        In this case, the API will return the first Container IDs starting from the head of the database.
 *        The total elements fetched will be returned as the return count.
 *
 *         Note: Return count may be less than or equal to the requested count. The key is dont-care, but a non-null return
 *          list pointer must be provided.
 *
 *    7) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = X, list = Valid, Count > 0:
 *        In this case, the API will return the next set of IDs starting from the next valid container after the specified key.
 *        The total elements fetched will be returned as the return count.
 *
 *        Note: Return count may be less than or equal to the requested count. If no valid next counter exists in the database
 *        (key = end of list, invalid key specified, or key too large), an empty list will be returned.
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if parameter is invalid.
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported.
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_mc_container_iter_get(const sx_api_handle_t        handle,
                                         const sx_access_cmd_t        cmd,
                                         const sx_mc_container_id_t   container_id_key,
                                         sx_mc_container_id_filter_t *container_id_filter_p,
                                         sx_mc_container_id_t        *container_id_list_p,
                                         uint32_t                    *container_id_cnt_p);


#endif /* __SX_API_MC_CONTAINER_H__ */
