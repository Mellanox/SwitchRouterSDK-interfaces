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

#ifndef __SX_API_DBG_H__
#define __SX_API_DBG_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_dbg.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API generates debug dump of all SDK modules, SX-core, and driver.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] dump_file_path      - Full path file name
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Path string length is greater than 256
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_dbg_generate_dump(const sx_api_handle_t handle,
                                     const char           *dump_file_path);


/**
 * This API should be used only for debug purposes. It is used to access internal commands for the ATcam (SPACE) module.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] sx_dbg_atcam_cmd_info_t   - Supported atcam module to execute directly
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Any input parameters is invalid
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_dbg_atcam(const sx_api_handle_t handle, sx_dbg_atcam_cmd_info_t* cmd_p);

/**
 * This API generates debug dump extra info for modules monitored by the SDK.
 * The file name is of the following format "sdkdump_ext_cr_<DEVICE_ID> - <timestamp>.udmp".
 * If a path is not provided, dump will be found in path /var/log.
 * Clear from the path any files with suffix "udmp.*.tmp" before rebooting after information collection.
 *
 * Supported devices:  Spectrum, Spectrum2, Spectrum3, Quantum, Quantum2
 *
 * @param[in] handle                         - SX-API handle
 * @param[in] sx_dbg_extra_info_t dbg_params - Parameters of debug dump extraction
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Any input parameters is invalid
 * @return SX_STATUS_PARAM_NULL           Parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Any parameter exceeds range limitation
 * @return SX_STATUS_TIMEOUT              Timeout in synchronous mode (if the call was asynchronous, this RC will be in the completion event)
 * @return SX_STATUS_ERROR                General error
 */

sx_status_t sx_api_dbg_generate_dump_extra(const sx_api_handle_t      handle,
                                           const sx_dbg_extra_info_t *dbg_params);


/**
 * This API generates debug dump of selected SDK modules, SX-core, and driver.
 * It also allows setting parameters to determine how the debug dump will be collected.
 *
 * Note: In case dump to plain text format and path is empty, SDK will use the default dump-file path '/var/log/sdkdump'.
 * In case dump to JSON format and path is empty, SDK will use the default dump-file path '/var/log/sdkdump.json'.
 * Hardware-Configuration fetch levels:
 *   - Basic: SDK will dump the basic hardware configuration data (e.g., flow/port counters, shared-buffers status). This
 *       is the default action and may be used in most cases.
 *   - None: SDK will not dump hardware configuration data at all. Use this option when only software databases are required
 *       or when a hardware problem is already observed before the dump.
 *   - Extended: SDK will get all available hardware configuration data. Use this option in cases when the basic hardware
 *       configuration data may not be sufficient for the analysis.
 *  The time it takes to dump all information depends on the requested hardware dump method.
 *  During the dump, SDK may fetch hardware configuration data, according to the requested dump method. In case SDK
 *       is unable to access hardware, it will skip fetching all remaining hardware configuration data.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] dump_info_p         - Dump parameters
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL           Parameter is NULL
 * @return SX_STATUS_PARAM_ERROR          Any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Any parameter exceeds range limitation
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_dbg_dump(const sx_api_handle_t     handle,
                            const sx_dbg_dump_info_t *dump_info_p);


/**
 * Sets Firmware Dump Me control parameters for firmware fatal event: enable and policy.
 * Once firmware fatal event mode is enabled, a trap will be asserted by firmware in case of fatal event.
 * On firmware fatal event occurrence, a firmware dump will be triggered either automatically or by calling the API,
 * as configured in policy.
 *
 * Note: After a successful firmware dump, the user must re-enable the firmware Fatal event using this API each time.
 *
 * Supported devices:  Spectrum, Spectrum2, Spectrum3, Quantum, Quantum2.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - * Currently, only SET is supported
 * @param[in] params              - Debug control parameters
 *
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Path string length is greater than sx_dbg_policy_e
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fw_dbg_control_set(const sx_api_handle_t          handle,
                                      const sx_access_cmd_t          cmd,
                                      const sx_dbg_control_params_t *params);


/**
 * Gets Firmware Dump Me control parameters for firmware fatal event: enable and policy.
 *
 * Supported devices:  Spectrum, Spectrum2, Spectrum3, Quantum, Quantum2
 *
 * @param[in] handle              - SX-API handle
 * @param[in] params              - Debug control parameters
 *
 * @return SX_STATUS_SUCCESS                Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR            Any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE    Path string length is greater than sx_dbg_policy_e
 * @return SX_STATUS_ERROR                  General error
 */
sx_status_t sx_api_fw_dbg_control_get(const sx_api_handle_t handle, sx_dbg_control_params_t *params);

/**
 * Triggers the assertion of firmware fatal event for testing purposes.
 * After triggering test the firmware fatal event mode, firmware should be re-enabled.
 *
 * Supported devices:  Spectrum, Spectrum2, Spectrum3, Quantum, Quantum2
 *
 * @param[in] handle              - SX-API handle
 * @param[in] params              - Test control parameters
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Path string length is greater than sx_dbg_policy_e
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_fw_dbg_test(const sx_api_handle_t handle, const sx_dbg_test_params_t *params);


/**
 * This API configures API logger parameters.
 * To change parameters of active API logger, the user must first disable it and then enable it again with new parameters.
 *
 * Disabled mode is not supported by this API. The API can disable the API logger using the DISABLE command.
 * Disabled mode can be returned by sx_api_dbg_api_logger_get if the API logger is inactive.
 *
 * Linear mode writes logs to one file. The writing can be stopped manually or when out of free space.
 *
 * Cyclic mode writes logs in cycle. When a log file reaches max file size, SDK generates an SX_TRAP_ID_API_LOGGER_EVENT
 * event with the path to the filled log file and starts to write a next log file.
 * When a number of log files reaches sx_dbg_api_logger_params_t.cyclic_params.log_file_num, SDK overwrites the oldest log file.
 * The name of the file in cyclic mode is built using the following scheme: path/file_name_N.pcap
 * where N = [0, SX_DBG_API_LOG_UNIQUE_SUFFIXES_NUM-1].
 * When the file with N=(SX_DBG_API_LOG_UNIQUE_SUFFIXES_NUM-1) is finished, the next one will use N=0.
 * While SDK tries to keep unique names for log files using unique suffixes, at the given moment of time there can be up to
 * sx_dbg_api_logger_params_t.cyclic_params.log_file_num log files on a disk.
 *
 * Example:
 * sx_dbg_api_logger_params_t.cyclic_params.max_log_size = 5242880; / 5 Mb /
 * sx_dbg_api_logger_params_t.cyclic_params.log_file_num = 3;
 * sx_dbg_api_logger_params_t.log_file_path[0] = '\0'; / log_file_path is empty, so the default path is used /
 * SDK starts with the file /tmp/sx_sdk_0.pcap. Once it has the size of 5 Mb, SDK will generate an
 * SX_TRAP_ID_API_LOGGER_EVENT event with the path /tmp/sx_sdk_0.pcap and it will start the second out of 3 files
 * using the name /tmp/sx_sdk_1.pcap. Once the second file has the size of 5 Mb, SDK will generate another event and
 * start the third file using the name /tmp/sx_sdk_2.pcap. And once the third file has the size of 5 Mb, SDK will generate
 * another event again and it will rewrite the content of the first file and change the name from /tmp/sx_sdk_0.pcap to
 * /tmp/sx_sdk_3.pcap, and continue to work in this manner.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] cmd      - ENABLE/DISABLE
 * @param[in] params_p - API logger parameters
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Parameters exceed allowed range
 * @return SX_STATUS_PARAM_NULL           params_p is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED      Command is not supported
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_dbg_api_logger_set(const sx_api_handle_t             handle,
                                      const sx_access_cmd_t             cmd,
                                      const sx_dbg_api_logger_params_t *params_p);

/**
 * This API returns API logger parameters if enabled.
 * If it is disabled, the API returns SX_DBG_API_LOGGER_DISABLED_MODE.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle   - SX-API handle
 * @param[out] params_p - API logger parameters
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_NULL           params_p is NULL
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_dbg_api_logger_get(const sx_api_handle_t       handle,
                                      sx_dbg_api_logger_params_t *params_p);

#endif /* __SX_API_DBG_H__ */
