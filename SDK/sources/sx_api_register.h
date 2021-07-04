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

#ifndef __SX_API_REGISTER_H__
#define __SX_API_REGISTER_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of REGISTER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - REGISTER module verbosity level
 * @param[in] api_verbosity_level      - REGISTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_register_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                    const sx_log_verbosity_target_t verbosity_target,
                                                    const sx_verbosity_level_t      module_verbosity_level,
                                                    const sx_verbosity_level_t      api_verbosity_level);


/**
 * This API gets the log verbosity level of REGISTER module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Get verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - REGISTER module verbosity level
 * @param[out] api_verbosity_level_p    - REGISTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_NULL if an input parameter is invalid
 */
sx_status_t sx_api_register_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                    const sx_log_verbosity_target_t verbosity_target,
                                                    sx_verbosity_level_t           *module_verbosity_level_p,
                                                    sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API creates/destroys a register.
 * An extraction point can be set on the allocated register and use it as ACL key. In addition, user can use the register
 * for flex ACL ALU actions. When using cmd CREATE, the registers list must be provided. If any register in the list is already
 * allocated, the allocation will fail.
 * This API together with sx_api_flex_parser_reg_ext_point_set replace sx_api_acl_custom_bytes_set, where general purpose
 * register N represents a set of custom byte 2N and custom byte 2N+1.
 *
 * Note: This API is mutually exclusive with sx_api_acl_custom_bytes_set. As such, per single SDK life cycle, only one can be used.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param [in] handle         - SX-API handle
 * @param [in] cmd            - CREATE/DESTROY
 * @param [in] reg_key_list_p - List of registers
 * @param [in] reg_key_cnt_p  - Number of items in register_list_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_ERROR if register already allocated (CREATE) or register in use (DESTROY) or register does not exist
 * @return SX_STATUS_PARAM_NULL if reg_key_list_p or reg_key_cnt_p parameter is NULL
 */
sx_status_t sx_api_register_set(const sx_api_handle_t    handle,
                                const sx_access_cmd_t    cmd,
                                const sx_register_key_t *reg_key_list_p,
                                const uint32_t          *reg_key_cnt_p);

/**
 * This function retrieves a list of one or more registers. The following use case scenarios apply with different input
 * parameters.  X stands for don't-care.
 *
 *   1) cmd = SX_ACCESS_CMD_GET, reg_key = X, reg_key_list_p = X, reg_key_cnt_p = 0:
 *        In this case, the API will return the total number of registers that were set.
 *
 *   2) cmd = SX_ACCESS_CMD_GET, reg_key = X, reg_key_list_p = valid, reg_key_cnt_p > 0:
 *        In this case, the API will check if the specified reg_key exists.
 *        If it does, the reg_key will be returned in the reg_key_list_p along with a reg_key_cnt_p of 1.
 *        If reg_key does not exist, an empty list will be returned with reg_key_cnt_p = 0.
 *        A reg_key_cnt_p > 1 will be treated as a reg_key_cnt_p of 1. In this case, reg_key_list_p pointer must be valid.
 *
 *   3) cmd = SX_ACCESS_CMD_GET_FIRST, reg_key = X, reg_key_list_p = valid, reg_key_cnt_p = X:
 *        In this case, the API will return the first reg_key_cnt_p registers starting from the head of the database.
 *        The total number of elements fetched will not exceed the value provided in reg_key_cnt_p and will be returned to
 *        that pointer. The input reg_key is ignored in this case.
 *        For reg_key_cnt_p = 0 API will return success and an empty list. In this case, reg_key_list_p pointer must be valid.
 *
 *   4) cmd = SX_ACCESS_CMD_GETNEXT, reg_key = X, reg_key_list_p = valid, reg_key_cnt_p = X:
 *        In this case, the API will return the next set of register IDs starting from the next valid register ID that comes after
 *        the specified reg_key.  The total number of elements fetched will not exceed the value provided in reg_key_cnt_p and will
 *        be returned to that pointer.
 *
 *        Note: For reg_key_cnt_p = 0 API will return success and an empty list. If no valid next register exists in the database,
 *          an empty list will be returned. In this case, reg_key_list_p pointer must be valid.
 *
 *  Supported devices: Spectrum2, Spectrum3.
 *
 * @param [in] handle            - SX-API handle
 * @param [in] cmd               - GET/GET_FIRST/GET_NEXT
 * @param [in] reg_key           - Register key
 * @param [in] filter_p          - Specify a filter parameter (not supported yet)
 * @param [out] reg_key_list_p   - Return list of register keys
 * @param [in,out] reg_key_cnt_p - [in] number of registers to get/[out] number of registers returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_register_iter_get(const sx_api_handle_t       handle,
                                     const sx_access_cmd_t       cmd,
                                     const sx_register_key_t     reg_key,
                                     const sx_register_filter_t *filter_p,
                                     sx_register_key_t          *reg_key_list_p,
                                     uint32_t                   *reg_key_cnt_p);

#endif /* __SX_API_REGISTER_H__ */
