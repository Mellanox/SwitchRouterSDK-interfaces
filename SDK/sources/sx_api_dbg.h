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

#ifndef __SX_API_DBG_H__
#define __SX_API_DBG_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_dbg.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of SX API DEBUG module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Set verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - SX API DEBUG module verbosity level
 * @param[in] api_verbosity_level      - SX API DEBUG API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE when parameter exceeds range
 */
sx_status_t sx_api_dbg_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of SX API DEBUG module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Get verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - SX API DEBUG module verbosity level
 * @param[out] api_verbosity_level_p    - SX API DEBUG API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE when parameter exceeds range
 */
sx_status_t sx_api_dbg_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API generates debug dump of all SDK modules, SX-core, and driver.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
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
 * This API generates debug dump extra information for modules monitored by the SDK
 * If a path is not provided, dump will be found in path /var/log.
 *
 * Supported dumps:
 * Name            Mandatory/Optional    File-Name(s)                    Description
 * -------------------------------------------------------------------------------------------------------------
 * CR-Space        Mandatory             'sdk_dump_ext_cr_*.udmp'         Device's configuration-space dump
 * Driver          Mandatory             'sdk_dump_ext_driver_dump_*.txt'             Driver-internals dump
 * iRISC core      Optional              'sdk_dump_ext_ir_core_dump_*.core'           FW core dump
 * FW-Trace        Optional              'sdk_dump_ext_fw_trace_dump_*.txt'           FW internal log
 * AMBER           Optional              'sdk_dump_ext_amber_dump_*.hex'              PHY layer information
 *
 * Supported devices:  Spectrum, Spectrum2, Spectrum3, Spectrum4, Quantum, Quantum2
 *
 * @param[in] handle       - SX-API handle
 * @param[in] dbg_params_p - Parameters of debug dump extraction
 *
 * @return SX_STATUS_SUCCESS              Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR          Any input parameters is invalid
 * @return SX_STATUS_PARAM_NULL           Parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE  Any parameter exceeds range limitation
 * @return SX_STATUS_TIMEOUT              Timeout in synchronous mode (if the call was asynchronous, this RC will be in the completion event)
 * @return SX_STATUS_ERROR                General error
 */
sx_status_t sx_api_dbg_generate_dump_extra(const sx_api_handle_t      handle,
                                           const sx_dbg_extra_info_t *dbg_params_p);


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
 * Supported devices: Spectrum, Spectrum2, Spectrum3, Spectrum4.
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
 * This API enable detection of SDK and FW failures (SDQ, RDQ, command interface,
 * User space error threads .kernel error threads).
 *
 * The mechanism will monitor and detect: SDK components health state, user
 * space modules, kernel space modules and HW interfaces that SDK uses to communicate
 * with HW, so if issue was found health event will be sent,
 * in parallel the mechanism inform via SysFs ("kernel_health") on the liveness of the system.
 *
 * IMPORTANT: this API and sx_api_fw_dbg_control_set() API are mutually exclusive! Only one can be used
 * in a single SDK life cycle.
 *
 * ENABLE trigger the health checks - it's not allowed to enable it during ISSU, during SDK
 * Initialization or during SDK shutdown in such case SDK will postpone automatically
 * the health monitoring.
 * DISABLE will cancel an active operation.
 *
 * Note:  Upon ISSU / SDK deinit, health monitor mechanism will be disabled.
 *
 * Note:  When command is ENABLE and health_sample_params_p is NULL SDK use default values,
 * see sx_dbg_health_sample_params_t description
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - ENABLE/DISABLE
 * @param[in] dbg_sample_params_p - Pointer to sample parameters
 *
 * @return SX_STATUS_SUCCESS               If operation completes successfully
 * @return SX_STATUS_PARAM_ERROR           If any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED       If cmd is different then ENABLE/DISABLE
 * @return SX_STATUS_SDK_NOT_INITIALIZED   In case API sent with ENABLE during init
 * @return SX_STATUS_ISSU_IN_PROGRESS      In case API sent with ENABLE during ISSU
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE   Any health sample parameter exceeds range limitation.
 *
 */
sx_status_t sx_api_dbg_fatal_failure_detection_set(const sx_api_handle_t                handle,
                                                   const sx_access_cmd_t                cmd,
                                                   const sx_dbg_health_sample_params_t *health_sample_params_p);
/**
 * This API returns if the health check mechanism is enabled/disabled .
 * If the health check is enabled, then this API returns the currently configured
 * parameters for the health check feature in sx_dbg_health_sample_params_t.
 * If the health check is disabled, then the is_enable_p pointer value will be
 * False and the sx_dbg_health_sample_params_t values can be ignored
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 *
 * @param[in] handle               - SX-API handle.
 * @param[out] is_enable_p         - Indicate if health check mechanism is enabled.
 * @param[out] dbg_sample_params_p - Pointer to sample parameters.
 *
 * @return SX_STATUS_SUCCESS               If operation completes successfully
 * @return SX_STATUS_PARAM_ERROR           If any input parameter is invalid
 *
 */
sx_status_t sx_api_dbg_fatal_failure_detection_get(const sx_api_handle_t          handle,
                                                   boolean_t                     *is_enable_p,
                                                   sx_dbg_health_sample_params_t *health_sample_params_p);


/**
 * Generate dump file name with correct time.
 *
 * Supported devices:  Spectrum, Spectrum2, Spectrum3, Quantum, Quantum2
 *
 * @param[in] path              - Where to locate the dump file
 * @param[in] dev_id            - Device id
 * @param[in] dump_type_str     - The Dump file type
 * @param[out] dump_full_name   - Dump file name
 *
 * @return SX_STATUS_SUCCESS                Operation completed successfully
 * @return SX_STATUS_PARAM_ERROR            Any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE    Path string length is greater than sx_dbg_policy_e
 * @return SX_STATUS_ERROR                  General error
 */
sx_status_t generate_dump_file_name(const char       *path,
                                    const sx_dev_id_t dev_id,
                                    const char       *dump_prefix,
                                    const char       *dump_suffix,
                                    char             *dump_name);

/**
 * This API configures API logger parameters.
 * To change parameters of active API logger, the user must first disable it and then enable it again with new parameters.
 *
 * Disabled mode is not supported by this API. The API can disable the API logger using the DISABLE command.
 * Linear mode writes logs to one file. The writing can be stopped manually or when out of free space.
 *
 * Cyclic mode writes logs in cycle. When a log file reaches max file size, SDK will start to write the next log file.
 * When a number of log files reaches sx_dbg_api_logger_params_t.cyclic_params.log_file_num, SDK overwrites the 2nd log file.
 * The 1st log file will never be overwritten.
 * The name of the file in cyclic mode is built using the following scheme: path/file_name_timestamp_N.pcap
 * where N = [0, log_file_num-1].
 * When the file with N=(log_file_num-1) is finished, the next one will use N=1.
 * While SDK tries to keep unique names for log files using unique suffixes, at the given moment in time there can be up to
 * sx_dbg_api_logger_params_t.cyclic_params.log_file_num log files on a disk.
 * In cyclic mode, during start sdk will delete all other api logs except the latest log_file_num logs.
 * Example:
 * sx_dbg_api_logger_params_t.cyclic_params.max_log_size = 5242880; / 5 Mb /
 * sx_dbg_api_logger_params_t.cyclic_params.log_file_num = 3;
 * sx_dbg_api_logger_params_t.log_file_path[0] = '/tmp/sx_sdk.pcap';
 * SDK starts with the file /tmp/sx_sdk_0.pcap. Once it has the size of 5 Mb, SDK will start using the name /tmp/sx_sdk_1.pcap, then
 * /tmp/sx_sdk_2.pcap. Once /tmp/sx_sdk_2.pcap has the size of 5 Mb, SDK will start writing to /tmp/sx_sdk_1.pcap(not sx_sdk_0.pcap)
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
