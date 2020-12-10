/*
 *  Copyright (C) 2014-2020. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_DBG_H__
#define __SX_API_DBG_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_dbg.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API generates debug dump of all SDK modules, SX-core and driver.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle.
 * @param[in] dump_file_path      - Full path file name.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if the path string length is greater than 256
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_dbg_generate_dump(const sx_api_handle_t handle,
                                     const char           *dump_file_path);


/**
 * This API should be used only for debug purposes.
 * It is used to access internal commands for the ATcam (SPACE) module.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] sx_dbg_atcam_cmd_info_t   - One of the supported within atcam module to execute directly
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_dbg_atcam(const sx_api_handle_t handle, sx_dbg_atcam_cmd_info_t* cmd_p);

/**
 * This API generates debug dump extra info, for modules monitored by the SDK
 * The file name is of the following format "sdkdump_ext_cr_<DEVICE_ID> - <timestamp>.udmp"
 * If path is not provided dump will be found in path /var/log.
 * User should clear from path any files with suffix "udmp.*.tmp" before rebooting after information collection
 *
 * Supported devices:  Spectrum, Spectrum2, Spectrum3, Quantum, Quantum2
 *
 * @param[in] handle              - SX-API handle.
 * @param[in] sx_dbg_extra_info_t dbg_params - parameters of debug dump extraction
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any parameter exceeds range limitation
 * @return SX_STATUS_TIMEOUT in case of a timeout in synchronous mode. if the call was asynchronous this RC will be in the completion event
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_dbg_generate_dump_extra(const sx_api_handle_t      handle,
                                           const sx_dbg_extra_info_t *dbg_params);


/**
 * Sets FW Dump Me control parameters for FW fatal event: enable and policy.
 * Once FW fatal event mode is enabled, a trap will be asserted by FW in case of fatal event.
 * On FW fatal event occurrence a FW dump will be triggered either automatically or by calling
 * the API, as configured in policy.
 * Note: After a successful FW dump, the user must re-enable the FW Fatal event using this API each time.
 *
 * Supported devices:  Spectrum, Spectrum2, Spectrum3, Quantum, Quantum2
 *
 * @param[in] handle              - SX-API handle.
 *
 * @param[in] cmd                 - currently only SET is supported *
 * @param[in] params              - debug control parameters
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if the path string length is greater than sx_dbg_policy_e
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_fw_dbg_control_set(const sx_api_handle_t          handle,
                                      const sx_access_cmd_t          cmd,
                                      const sx_dbg_control_params_t *params);


/**
 * Gets FW Dump Me control parameters for FW fatal event: enable and policy
 *
 *
 * Supported devices:  Spectrum, Spectrum2, Spectrum3, Quantum, Quantum2
 *
 * @param[in] handle              - SX-API handle.
 *
 * @param[in] params              - debug control parameters
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if the path string length is greater than sx_dbg_policy_e
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_fw_dbg_control_get(const sx_api_handle_t handle, sx_dbg_control_params_t *params);

/**
 * Triggers the assertion of FW fatal event for testing purposes
 * After triggering test the fw fatal event mode in FW should be re-enabled
 *
 *
 *
 * Supported devices:  Spectrum, Spectrum2, Spectrum3, Quantum, Quantum2
 *
 * @param[in] handle              - SX-API handle.
 *
 * @param[in] params              - test control parameters
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if the path string length is greater than sx_dbg_policy_e
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_fw_dbg_test(const sx_api_handle_t handle, const sx_dbg_test_params_t *params);


/**
 * This API configures API logger parameters.
 * To change parameters of active API logger, the user must first disable it and then
 * enable it again with new parameters.
 *
 * Disabled mode is not supported by this API. The API can disable the API logger using the DISABLE command.
 * Disabled mode can be returned by sx_api_dbg_api_logger_get if the API logger is inactive.
 *
 * Linear mode writes logs to one file. The writing can be stopped manually or when out of free space.
 *
 * Cyclic mode writes logs in cycle. When a log file reaches max file size, SDK generates an
 * SX_TRAP_ID_API_LOGGER_EVENT event with the path to the filled log file and starts to write a next log file.
 * When a number of log files reaches sx_dbg_api_logger_params_t.cyclic_params.log_file_num, SDK overwrites
 * the oldest log file.
 * The name of the file in cyclic mode is built using the following scheme: path/file_name_N.pcap
 * where N = [0, SX_DBG_API_LOG_UNIQUE_SUFFIXES_NUM-1].
 * When the file with N=(SX_DBG_API_LOG_UNIQUE_SUFFIXES_NUM-1) is finished, the next one will use N=0.
 * While SDK tries to keep unique names for log files using unique suffixes, at the given moment of time,
 * there can be up to sx_dbg_api_logger_params_t.cyclic_params.log_file_num log files on a disk.
 * Example:
 * sx_dbg_api_logger_params_t.cyclic_params.max_log_size = 5242880; / 5 Mb /
 * sx_dbg_api_logger_params_t.cyclic_params.log_file_num = 3;
 * sx_dbg_api_logger_params_t.log_file_path[0] = '\0';   / log_file_path is empty, so the default path is used /
 * SDK starts with the file /tmp/sx_sdk_0.pcap. Once it has the size of 5 Mb, SDK will generate an
 * SX_TRAP_ID_API_LOGGER_EVENT event with the path /tmp/sx_sdk_0.pcap and it will start the second out of 3 files
 * using the name /tmp/sx_sdk_1.pcap. Once the second file has the size of 5 Mb, SDK will generate another event and
 * start the third file using the name /tmp/sx_sdk_2.pcap. And once the third file has the size of 5 Mb, SDK will generate
 * another event again and it will rewrite the content of the first file and change the name from /tmp/sx_sdk_0.pcap to
 * /tmp/sx_sdk_3.pcap, and continue to work in this manner.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle.
 * @param[in] cmd      - ENABLE/DISABLE
 * @param[in] params_p - API logger parameters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed allowed range
 * @return SX_STATUS_PARAM_NULL if params_p is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_dbg_api_logger_set(const sx_api_handle_t             handle,
                                      const sx_access_cmd_t             cmd,
                                      const sx_dbg_api_logger_params_t *params_p);

/**
 * This API returns API logger parameters if enabled.
 * Otherwise returns SX_DBG_API_LOGGER_DISABLED_MODE.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle   - SX-API handle.
 * @param[out] params_p - API logger parameters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if params_p is NULL
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_dbg_api_logger_get(const sx_api_handle_t       handle,
                                      sx_dbg_api_logger_params_t *params_p);

#endif /* __SX_API_DBG_H__ */
