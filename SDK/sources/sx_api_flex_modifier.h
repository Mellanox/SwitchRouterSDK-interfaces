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

#ifndef __SX_API_FLEX_MODIFIER_H__
#define __SX_API_FLEX_MODIFIER_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/
/**
 * This API sets the log verbosity level of FLEX_MODIFIER module.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Set verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - FLEX_MODIFIER module verbosity level
 * @param[in] api_verbosity_level      - FLEX_PMODIFIER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */


sx_status_t sx_api_flex_modifier_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                         const sx_log_verbosity_target_t verbosity_target,
                                                         const sx_verbosity_level_t      module_verbosity_level,
                                                         const sx_verbosity_level_t      api_verbosity_level);


/**
 * This API gets the log verbosity level of FLEX_MODIFIER module.
 *
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Get verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - FLEX_MODIFIER module verbosity level
 * @param[out] api_verbosity_level_p    - FLEX_MODIFIER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_NULL if an input parameter is invalid
 */

sx_status_t sx_api_flex_modifier_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                         const sx_log_verbosity_target_t verbosity_target,
                                                         sx_verbosity_level_t           *module_verbosity_level_p,
                                                         sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API configures (CREATE/SET/DESTROY) an egress modifier template (EMT).
 * An EMT is used to modify packets using ACL actions.
 * An EMT needs to be allocated first (CREATE cmd) before its parameters are set (SET cmd).
 * Note: an EMT used in an ACL action cannot be destroyed.
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in] handle    - SX-API handle
 * @param[in] cmd       - CREATE / SET / DESTROY
 * @param[in] emt_id    - The egress modifier template to configure
 * @param[in] emt_cfg_p - Pointer to the configuration to apply to the EMT (ignored by CREATE & DESTROY commands).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if trying to create an EMT that already exists.
 * @return SX_STATUS_RESOURCE_IN_USE when trying to destroy an EMT used by an ACL action.
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform*
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_flex_modifier_set(const sx_api_handle_t             handle,
                                     const sx_access_cmd_t             cmd,
                                     const sx_flex_modifier_emt_key_t  emt_id,
                                     const sx_flex_modifier_emt_cfg_t *emt_cfg_p);

/**
 * This API retrieves the configuration of an egress modifier template (EMT).
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * Parameters:
 * @param[in]  handle    - SX-API handle
 * @param[in]  cmd       - GET
 * @param[in]  emt_id    - The egress modifier template to retrieve.
 * @param[out] emt_cfg_p - Pointer to the configuration to filled by the API.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 */

sx_status_t sx_api_flex_modifier_get(const sx_api_handle_t            handle,
                                     const sx_access_cmd_t            cmd,
                                     const sx_flex_modifier_emt_key_t emt_id,
                                     sx_flex_modifier_emt_cfg_t      *emt_cfg_p);

/**
 * This API configures the below egress modifier attributes according to the attr_type of the listed objects (att_cfg_list_p):
 *
 * a. port attributes (attr_type=TYPE_PORT_E):
 *    payload_offset_shift- By default the flex packet modification is supported up to the byte where the actual packet header parsing stops
 *    (actual parsing offset). also the actual parsing offset is less or equal to the configure parsing depth.
 *    the offset configuration enables to extend the actual parsing offset in order to apply either payload modification (EDIT)
 *    or additional header information element to the packet (PUSH) by the flex egress modifier.
 *    E.g :
 *    [------default valid for flex modification----]
 *    [------default actual parsing offset+---------]---------------------------------------------------+
 *    |Ethernet [18B]   |  ipv4[20B]      | udp[8B] |                      Payload                      |
 *    +-----------------+-----------------+---------+---------------------------------------------------+
 *
 *    configuring payload_offset_shift of 8 bytes:
 *
 *    [------------------valid range for flex modification---------------------]
 *    [------default actual parsing offset+---------]----------------------Payload----------------------+
 *    |Ethernet [18B]   |  ipv4[20B]      | udp[8B] | payload_offset_shift[8B] |                        |
 *    +-----------------+-----------------+---------+---------------------------------------------------+
 *
 *      Notes:
 *      - The configured offset is limited by up to 512B (in 2B granularity).
 *      - The default configuration of the payload_offset_shift is - 0 (the payload starts at the end of the actual parsing).
 *      - payload_offset_shift configuration is per port (physical ports only), split ports will not inherit the configuration from the original split port.
 *      - in case of LAG membership, all port members should be configured with the same payload_offset_shift.
 *      - Supported devices: Spectrum2, Spectrum3, Spectrum4.
 *
 * Parameters:
 * @param[in] handle                     - SX-API handle.
 * @param[in] cmd                        - SX_ACCESS_CMD_ADD / SX_ACCESS_CMD_DELETE.
 * @param[in] *attr_cfg_list_p           - pointer to a list of port/common attributes to set/unset
 * @param[in] attr_cfg_cnt               - number of elements in the list.
 *
 * @return SX_STATUS_SUCCESS             - operation completes successfully.
 * @return SX_STATUS_PARAM_NULL          - referenced inputs are NULL.
 * @return SX_STATUS_CMD_UNSUPPORTED     - CMD is not supported.
 * @return SX_STATUS_CMD_ERROR           - received struct is not the expected
 * @return SX_STATUS_PARAM_ERROR         - input parameter is invalid.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - input parameter is not in the expected range.
 * @return SX_STATUS_ENTRY_NOT_FOUND     - data base call back if entry can't be retrieved.
 * @return SX_STATUS_NO_MEMORY           - data base call back in case of memory allocation error.
 * @return SX_STATUS_NO_RESOURCES        - memory allocation failure.
 * @return SX_STATUS_UNSUPPORTED         - configuration is not supported by the platform.
 * @return SX_STATUS_MODULE_UNINITIALIZED- data base initialization failure.
 * @return SX_STATUS_ERROR               - general error.
 */

sx_status_t sx_api_flex_modifier_attr_set(const sx_api_handle_t                handle,
                                          const sx_access_cmd_t                cmd,
                                          const sx_flex_modifier_attributes_t *attr_cfg_list_p,
                                          const uint32_t                       attr_cfg_cnt);

/**
 * This API retrieves the egress modifier attributes from the requested data base.
 * The retrieved attributes depends on the requested attr_type of the provided list objects (attr_cfg_list_p).
 * Supported devices: Spectrum2, Spectrum3, Spectrum4.
 * ts
 * Parameters:
 * @param[in]  handle                    - SX-API handle
 * @param[in]  cmd                        - SX_ACCESS_CMD_GET / SX_ACCESS_CMD_GET_ALL.
 * @param[in]  *attr_cfg_list_p          - pointer to a list of port/common attributes to be retrieved.
 *                                         If it is NULL, the attr_cfg_cnt variable is filled out
 *                                         with numbers of attributes entries that could be retrieved.
 *                                         If the pointer is valid, attributes info is placed
 *                                         according to the requested log_port in the list set by the user,
 *                                         and attr_cfg_cnt updated with the actual number of requested entries in the list.
 *
 * @param[in][out] *attr_cfg_cnt         - pointer to the number of elements in the list to be retrieved.
 *                                         returns the actual number of successfully retrieved elements.
 *
 * @return SX_STATUS_SUCCESS             - operation completes successfully.
 * @return SX_STATUS_PARAM_NULL          - referenced inputs are NULL.
 * @return SX_STATUS_PARAM_ERROR         - input parameter is invalid.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - input parameter is not in the expected range.
 * @return SX_STATUS_NO_RESOURCES        - memory allocation failure.
 * @return SX_STATUS_ENTRY_NOT_FOUND     - data base call back if entry can't be retrieved.
 * @return SX_STATUS_MODULE_UNINITIALIZED- data base initialization failure.
 * @return SX_STATUS_UNSUPPORTED         - configuration is not supported by the platform.
 * @return SX_STATUS_ERROR               - general error.
 */

sx_status_t sx_api_flex_modifier_attr_get(const sx_api_handle_t          handle,
                                          const sx_access_cmd_t          cmd,
                                          sx_flex_modifier_attributes_t *attr_cfg_list_p,
                                          uint32_t                      *attr_cfg_cnt_p);
#endif /* __SX_API_FLEX_MODIFIER_H__ */
