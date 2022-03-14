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

#ifndef __SX_API_PORT_H__
#define __SX_API_PORT_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of PORT module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - Sets verbosity of API/MODULE/BOTH
 * @param[in] module_verbosity_level   - PORT module verbosity level
 * @param[in] api_verbosity_level      - PORT API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of PORT module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - Gets verbosity of API/MODULE/BOTH
 * @param[out] module_verbosity_level_p - PORT module verbosity level
 * @param[out] api_verbosity_level_p    - PORT API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API adds or deletes a device in the SDK.
 * port_attributes_list_p defines mapping of local ports to module identifier as and allows each port to be assigned with
 * a different width representing the number of lanes it is using, thus controlling port available rates.
 *
 * Device base MAC address given is used by hardware to assign MAC addresses to all physical ports incrementally from the
 * given address.
 *
 * On Spectrum-based devices, a given base MAC address should be aligned to 64 and in Spectrum-2 and Spectrum-3 devices,
 * the given base MAC address should be aligned to 128, according to the number of physical ports in the device.
 *
 * The SDK will map the device's local ports to unique logical ports (returned within port_attributes_list_p).
 * The logical ports represent SDK ports and used further in port APIs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                     - SX-API handle
 * @param[in] cmd                        - ADD/DELETE
 * @param[in] device_id                  - Device ID
 * @param[in] base_mac_addr_p            - Device base MAC address pointer
 * @param[in,out] port_attributes_list_p - [in] port_mode, port_mapping/[out] log_port
 * @param[in] port_cnt                   - port attributes lists length
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceed its range
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 *
 */
sx_status_t sx_api_port_device_set(const sx_api_handle_t handle,
                                   const sx_access_cmd_t cmd,
                                   const sx_device_id_t  device_id,
                                   const sx_mac_addr_t  *base_mac_addr_p,
                                   sx_port_attributes_t *port_attributes_list_p,
                                   const uint32_t        port_cnt);

/**
 * This API retrieves a device information (port lists) from the SDK.
 * If all optional output buffers are NULL, this API retrieves the number of ports.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] device_id               - Device ID
 * @param[in] swid                    - Switch ID (use SX_SWID_ID_DONTCARE to get all ports)
 * @param[out] port_attributes_list_p - port attributes list
 * @param[in,out] port_cnt_p          - [in] port attributes list length/[out] port attributes number
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceed its range
 */
sx_status_t sx_api_port_device_get(const sx_api_handle_t handle,
                                   const sx_device_id_t  device_id,
                                   const sx_swid_t       swid,
                                   sx_port_attributes_t *port_attributes_list_p,
                                   uint32_t             *port_cnt_p);

/**
 * This API retrieves a device base MAC from the SDK. The base MAC is used as a base address for the ports MAC.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] device_id        - Device ID
 * @param[out] base_mac_addr_p - Device base MAC
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STAUS_ERROR general error
 */
sx_status_t sx_api_port_device_base_mac_get(const sx_api_handle_t handle,
                                            const sx_device_id_t  device_id,
                                            sx_mac_addr_t        *base_mac_addr_p);
/**
 * This API sets ports mapping.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port_list_p       - List of local ports
 * @param[in] port_mapping_list_p   - Port mapping list
 * @param[in] port_cnt              - Number of ports
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceed its range
 */
sx_status_t sx_api_port_mapping_set(const sx_api_handle_t    handle,
                                    const sx_port_log_id_t  *log_port_list_p,
                                    const sx_port_mapping_t *port_mapping_list_p,
                                    const uint32_t           port_cnt);

/**
 * This API retrieves a logical port ID mapping from the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port_list_p       - List of local ports
 * @param[out] port_mapping_list_p  - Port mapping list
 * @param[in] port_cnt              - Number of ports
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceed its range
 */
sx_status_t sx_api_port_mapping_get(const sx_api_handle_t   handle,
                                    const sx_port_log_id_t *log_port_list_p,
                                    sx_port_mapping_t      *port_mapping_list_p,
                                    const uint32_t          port_cnt);


/**
 * This API retrieves the devices info list from the SDK.
 * If optional output buffer is NULL, this API retrieves the number of devices.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[out] device_info_list_p   - List of device info entries
 * @param[in,out] device_info_cnt_p - [in]input/[out]output list length
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceed its range
 */
sx_status_t sx_api_port_device_list_get(const sx_api_handle_t handle,
                                        sx_device_info_t     *device_info_list_p,
                                        uint32_t             *device_info_cnt_p);

/**
 * This API adds/deletes a SWID to/from the SDK.
 * A SWID which has ports bound to it cannot be deleted.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] cmd     - ADD/DELETE
 * @param[in] swid    - Switch ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if SWID exceeds its range or is undefined in profile
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 */
sx_status_t sx_api_port_swid_set(const sx_api_handle_t handle,
                                 const sx_access_cmd_t cmd,
                                 const sx_swid_t       swid);

/**
 * This API retrieves all SWIDs from the SDK. If optional output buffer is NULL, this API retrieves the number of SWIDs.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[out] swid_list_p   - Array of SWIDs
 * @param[in,out] swid_cnt_p - [in] array's length/[out] number of SWIDs
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if SWIDs list length is 0 (zero)
 */
sx_status_t sx_api_port_swid_list_get(const sx_api_handle_t handle,
                                      sx_swid_t            *swid_list_p,
                                      uint32_t             *swid_cnt_p);

/**
 * This API binds/unbinds a logical port to/from a SWID in the SDK.
 * To unbind a port from a SWID, the SWID field should be SX_SWID_ID_DISABLED.
 * Port attributes reset during an unbind operation (e.g., VLAN membership and QinQ).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[in] swid     - New switch partition ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if SWID is out of range
 */
sx_status_t sx_api_port_swid_bind_set(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      const sx_swid_t        swid);

/**
 * This API retrieves a logical port's bound SWID.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] log_port   - Logical Port ID
 * @param[out] swid_p    - The port's SWID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if SWID is out of range
 */
sx_status_t sx_api_port_swid_bind_get(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      sx_swid_t             *swid_p);

/**
 * This API retrieves the SwID's ports list. If optional output buffer is NULL, this API simply retrieves the number of ports.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] swid           - Switch ID
 * @param[out] log_port_list - Array of device's logical port IDs range
 * @param[in,out] port_cnt_p - [in] array's length/[out] number of ports in array
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if SWID is out of range
 */
sx_status_t sx_api_port_swid_port_list_get(const sx_api_handle_t handle,
                                           const sx_swid_t       swid,
                                           sx_port_log_id_t     *log_port_list_p,
                                           uint32_t             *port_cnt_p);

/**
 * This API sets the port's stacking mode in the SDK.
 *
 * Supported devices: SwitchX, SwitchX2.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[in] mode     - New port mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_mode_set(const sx_api_handle_t  handle,
                                 const sx_port_log_id_t log_port,
                                 const sx_port_mode_t   mode);

/**
 * This API retrieves the port's mode from the SDK.
 *
 * Supported devices: SwitchX, SwitchX2.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[out] mode_p  - current port mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_mode_get(const sx_api_handle_t  handle,
                                 const sx_port_log_id_t log_port,
                                 sx_port_mode_t        *mode_p);


/**
 * This API sets the port MTU size in the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[in] mtu_size - new MTU size. The MTU size is L2 frame size (payload size + L2 header size).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 */
sx_status_t sx_api_port_mtu_set(const sx_api_handle_t  handle,
                                const sx_port_log_id_t log_port,
                                const sx_port_mtu_t    mtu_size);


/**
 * This API retrieves the port MTU size from the SDK.
 *
 * Note: For Ethernet devices, maximum MTU and operational MTU are the same.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] log_port         - Logical Port ID
 * @param[out] max_mtu_size_p  - Maximum MTU supported on this port (L2 frame size)
 * @param[out] oper_mtu_size_p - Operational MTU configured on this port (L2 frame size)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_mtu_get(const sx_api_handle_t  handle,
                                const sx_port_log_id_t log_port,
                                sx_port_mtu_t         *max_mtu_size_p,
                                sx_port_mtu_t         *oper_mtu_size_p);

/**
 * This API controls enabling of the port ingress truncation mode and sets the truncation size of packets that ingress the port.
 * Note: - Ingress MTU discard is not functional on a Port with Ingress Truncation enabled.
 *       - Truncation size minimal value is 128B with granularity of 8 bytes.
 *       - The packets will be truncated to "size-4B" (4B for CRC).
 *       - The ingress MTU size will be minimum of [MTU, truncation size].
 *       - In case MTU size < truncation size, SDK will round up MTU value to a valid
 *         truncation size and will return the MTU to it's original value once truncation is disabled.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] cmd      - SET/UNSET
 * @param[in] log_port - Logical Port ID
 * @param[in] truncation_p - The truncation attributes configured on this port.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 */
sx_status_t sx_api_port_ingress_truncation_set(const sx_api_handle_t       handle,
                                               const sx_access_cmd_t       cmd,
                                               const sx_port_log_id_t      log_port,
                                               const sx_port_truncation_t *truncation_p);

/**
 * This API gets the given port's ingress truncation mode state.
 * When enabled, the API will return the size to which ingress packets will be truncated to.
 * When disabled, the truncation size will be returned as 0.
 * Note: The packets are truncated to truncation size -4B for the CRC.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] cmd      - GET
 * @param[in] log_port - Logical Port ID
 * @param[out] truncation_p - Truncation attributes pointer.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_ingress_truncation_get(const sx_api_handle_t  handle,
                                               const sx_access_cmd_t  cmd,
                                               const sx_port_log_id_t log_port,
                                               sx_port_truncation_t  *truncation_p);

/**
 * This API sets the port type & speed. This API enables the application to set the port enabled mode(s).
 * When the link is up, the current active protocol is retrieved (after SET).
 * When the link is down, the supported protocols are retrieved (after SET).
 *
 * Note: Disabling auto-negotiation also disables auto FEC.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical Port ID
 * @param[in] admin_speed_p - New types and speeds (protocols) enabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_speed_admin_set(const sx_api_handle_t             handle,
                                        const sx_port_log_id_t            log_port,
                                        const sx_port_speed_capability_t *admin_speed_p);

/**
 * This API retrieves the port's admin and operational speed from the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - Logical Port ID
 * @param[out] admin_speed_p - Port administrative speed
 * @param[out] oper_speed_p  - Port Operational speed
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_speed_get(const sx_api_handle_t       handle,
                                  const sx_port_log_id_t      log_port,
                                  sx_port_speed_capability_t *admin_speed_p,
                                  sx_port_oper_speed_t       *oper_speed_p);

/**
 * This API retrieves the port's supported capabilities from the SDK. Hardware capabilities are not configurable.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical Port ID
 * @param[out] capability_p - Port capabilities
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_capability_get(const sx_api_handle_t  handle,
                                       const sx_port_log_id_t log_port,
                                       sx_port_capability_t  *capability_p);

/**
 * This API retrieves the port's supported FEC capabilities from the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] log_port                - Logical Port ID
 * @param[out] fec_capability_list_p  - List of capabilities and corresponding speeds
 * @param[in, out] fec_cnt_p          - [in] number of entries to get/[out] number of entries in returned list
 *                                      If fec_capability_list is NULL or fec_cnt is 0, Count is returned instead
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_fec_capability_get(const sx_api_handle_t     handle,
                                           const sx_port_log_id_t    log_port,
                                           sx_port_fec_capability_t *fec_capability_list_p,
                                           uint32_t                 *fec_cnt_p);


/**
 * This API retrieves the port's physical address (MAC) from the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] log_port         - Logical Port ID
 * @param[out] port_mac_addr_p - Current base MAC address
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_phys_addr_get(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      sx_mac_addr_t         *port_mac_addr_p);

/**
 * This API sets the port's physical address (MAC).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] log_port         - Logical Port ID
 * @param[out] port_mac_addr_p - New MAC address
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_phys_addr_set(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      const sx_mac_addr_t   *port_mac_addr_p);

/**
 * This API sets the port's physical loopback. LAG port cannot be loopback.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - Logical Port ID
 * @param[in] phys_loopback   - New physical loopback
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_phys_loopback_set(const sx_api_handle_t         handle,
                                          const sx_port_log_id_t        log_port,
                                          const sx_port_phys_loopback_t phys_loopback);

/**
 * This API retrieves the port's physical loopback (LAG port cannot be loopback).
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] log_port         - Logical Port ID
 * @param[out] phys_loopback_p - Current physical loopback
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_phys_loopback_get(const sx_api_handle_t    handle,
                                          const sx_port_log_id_t   log_port,
                                          sx_port_phys_loopback_t *phys_loopback_p);


/**
 * This API sets the port administrative state in the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - Logical Port ID
 * @param[in] admin_state - New administrative status
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_state_set(const sx_api_handle_t       handle,
                                  const sx_port_log_id_t      log_port,
                                  const sx_port_admin_state_t admin_state);

/**
 * This API retrieves the port's administrative, operational, and module state from the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - Logical Port ID
 * @param[out] oper_state_p   - Port operational state
 * @param[out] admin_state_p  - Port administrative state
 * @param[out] module_state_p - Module operational state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_state_get(const sx_api_handle_t   handle,
                                  const sx_port_log_id_t  log_port,
                                  sx_port_oper_state_t   *oper_state_p,
                                  sx_port_admin_state_t  *admin_state_p,
                                  sx_port_module_state_t *module_state_p);

/**
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID (whose flow control configuration to set)
 * @param[in] fc_mode  - Tx/Rx flow control state
 *
 * This API sets the port flow control pause configuration.
 * fc_mode sets the mode of both Rx and Tx with one of 4 possible EN/DIS combinations.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[in] fc_mode  - Tx/Rx flow control state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_global_fc_enable_set(const sx_api_handle_t          handle,
                                             const sx_port_log_id_t         log_port,
                                             const sx_port_flow_ctrl_mode_t fc_mode);

/**
 *
 * This API retrieves the port flow control pause configuration from the SDK.
 * fc_mode_p gets the mode of both Rx and Tx with one of 4 possible EN/DIS combinations.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] log_port   - Logical Port ID (whose flow control configuration to retrieve)
 * @param[out] fc_mode_p - Tx/Rx flow control state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_global_fc_enable_get(const sx_api_handle_t     handle,
                                             const sx_port_log_id_t    log_port,
                                             sx_port_flow_ctrl_mode_t *fc_mode_p);

/**
 *
 * This API sets the port priority flow control (PFC) configuration.
 * fc_mode sets the mode of both Rx and Tx with one of 4 possible EN/DIS combinations.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Port ID
 * @param[in] pfc_prio - PFC priority
 * @param[in] fc_mode  - Tx/Rx flow control state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_pfc_enable_set(const sx_api_handle_t          handle,
                                       const sx_port_log_id_t         log_port,
                                       const sx_port_flow_ctrl_prio_t pfc_prio,
                                       const sx_port_flow_ctrl_mode_t fc_mode);

/**
 * This API retrieves the port priority flow control (PFC) configuration from the SDK.
 * fc_mode_p gets the mode of both Rx and Tx with one of 4 possible EN/DIS combinations.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] log_port   - Port ID
 * @param[in] pfc_prio   - PFC priority
 * @param[out] fc_mode_p - Tx/Rx flow control state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_pfc_enable_get(const sx_api_handle_t          handle,
                                       const sx_port_log_id_t         log_port,
                                       const sx_port_flow_ctrl_prio_t pfc_prio,
                                       sx_port_flow_ctrl_mode_t      *fc_mode_p);

/**
 * This API retrieves the port IEEE 802.3 counters from the SDK.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - READ/READ_CLEAR
 * @param[in] log_port               - Logical Port ID
 * @param[out] cntr_ieee_802_dot_3_p - IEEE 802.3 counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_ieee_802_dot_3_get(const sx_api_handle_t          handle,
                                                   const sx_access_cmd_t          cmd,
                                                   const sx_port_log_id_t         log_port,
                                                   sx_port_cntr_ieee_802_dot_3_t *cntr_ieee_802_dot_3_p);

/**
 * This API retrieves the port RFC 2863 counters from the SDK.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - READ/READ_CLEAR
 * @param[in] log_port         - Logical Port ID
 * @param[out] cntr_rfc_2863_p - RFC 2863 counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_rfc_2863_get(const sx_api_handle_t    handle,
                                             const sx_access_cmd_t    cmd,
                                             const sx_port_log_id_t   log_port,
                                             sx_port_cntr_rfc_2863_t *cntr_rfc_2863_p);

/**
 * This API retrieves the port RFC 2819 counters from the SDK.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - READ/READ_CLEAR
 * @param[in] log_port         - Logical Port ID
 * @param[out] cntr_rfc_2819_p - RFC 2819 counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_rfc_2819_get(const sx_api_handle_t    handle,
                                             const sx_access_cmd_t    cmd,
                                             const sx_port_log_id_t   log_port,
                                             sx_port_cntr_rfc_2819_t *cntr_rfc_2819_p);

/**
 * This API retrieves the port RFC 3635 counters from the SDK.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - READ/READ_CLEAR
 * @param[in] log_port         - Logical Port ID
 * @param[out] cntr_rfc_3635_p - RFC 3635 counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_rfc_3635_get(const sx_api_handle_t    handle,
                                             const sx_access_cmd_t    cmd,
                                             const sx_port_log_id_t   log_port,
                                             sx_port_cntr_rfc_3635_t *cntr_rfc_3635_p);

/**
 * This API retrieves the port CLI counters from the SDK.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - READ/CLEAR
 * @param[in] log_port    - Logical Port ID
 * @param[out] cntr_cli_p - CLI counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_cli_get(const sx_api_handle_t  handle,
                                        const sx_access_cmd_t  cmd,
                                        const sx_port_log_id_t log_port,
                                        sx_port_cntr_cli_t    *cntr_cli_p);

/**
 * This API retrieves the port priority counters from the SDK.
 * When a LAG port is given, the result is the sum of all the LAG ports counters.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] cmd          - READ/READ_CLEAR
 * @param[in] log_port     - Logical Port ID
 * @param[in] prio_id      - Priority ID
 * @param[out] cntr_prio_p - Priority counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_prio_get(const sx_api_handle_t    handle,
                                         const sx_access_cmd_t    cmd,
                                         const sx_port_log_id_t   log_port,
                                         const sx_cos_ieee_prio_t prio_id,
                                         sx_port_cntr_prio_t     *cntr_prio_p);

/**
 * This API retrieves the port's traffic class counters.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Note: The API does not support LAG and VPort.
 * Note: For Spectrum devices, if a switch priority is mapped to any higher TC X [where 8 <= X <= 15], then tx_octet and
 *    tx_frames will be counted against TC [X - 8].
 * Note: For Spectrum devices, if the port is in MC Aware Mode, valid values of tc_id are [0-7].
 *
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - READ/READ_CLEAR
 * @param[in] log_port      - Logical Port ID
 * @param[in] tc_id         - Traffic class ID
 * @param[out] cntr_tc_p    - Per port per TC counters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_tc_get(const sx_api_handle_t   handle,
                                       const sx_access_cmd_t   cmd,
                                       const sx_port_log_id_t  log_port,
                                       const sx_port_tc_id_t   tc_id,
                                       sx_port_traffic_cntr_t *cntr_tc_p);

/**
 * This API retrieves the port buffer counters from the SDK.
 * When a LAG port is given, the result is the sum of all the LAG ports counters.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Note: In UC mode, Rx UC octets, Rx UC frames, and Rx discard counters are available only for buffer ID 0-7.
 * Note: On Spectrum devices, shared buffer discard counter is not supported.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle       - SX-API handle
 * @param[in]  cmd          - READ/READ_CLEAR
 * @param[in]  log_port     - Logical Port ID
 * @param[in]  buff_id      - Buffer ID
 * @param[out] cntr_buff_p  - Buffer counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_buff_get(const sx_api_handle_t         handle,
                                         const sx_access_cmd_t         cmd,
                                         const sx_port_log_id_t        log_port,
                                         const sx_cos_priority_group_t buff_id,
                                         sx_port_cntr_buff_t          *cntr_buff_p);

/**
 * This API retrieves the extended port counters from the SDK.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Note: This API does not support LAG.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] cmd          - READ/READ_CLEAR
 * @param[in] log_port     - Logical Port ID
 * @param[in] prio_id      - Counters priority ID (only in Spectrum devices, prio_id=0 is supported)
 * @param[out] cntr_perf_p - Performance counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_perf_get(const sx_api_handle_t   handle,
                                         const sx_access_cmd_t   cmd,
                                         const sx_port_log_id_t  log_port,
                                         const sx_port_prio_id_t prio_id,
                                         sx_port_cntr_perf_t    *cntr_perf_p);

/**
 * This API retrieves the port discard counters from the SDK.
 * The following options are available:
 *   1. Read the discard counters (set the cmd to SX_ACCESS_CMD_READ).
 *   2. Read and clear the discard counters (set the cmd to SX_ACCESS_CMD_READ_CLEAR).
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - READ/READ_CLEAR
 * @param[in] log_port        - Logical Port ID
 * @param[out] cntr_discard_p - Discard counters entry
 *
 * @return sx_status_t :
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_ERROR if a parameter is NULL or not supported
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in the DB
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_discard_get(const sx_api_handle_t   handle,
                                            const sx_access_cmd_t   cmd,
                                            const sx_port_log_id_t  log_port,
                                            sx_port_cntr_discard_t *cntr_discard_p);

/**
 * This API clears port counters.
 * The following options are available:
 *   1. Clear a specific port (set log_port field with the log port ID && all_ports = FALSE):
 *      Option a: Clear specific counter group (set the group in cntr_grp)
 *      Option b: Clear all counter groups (set cntr_grp = SX_PORT_CNTR_GRP_ALL)
 *
 *   2. Clear all ports (set all_ports = TRUE):
 *      Option a: Clear specific counter group (set the group in cntr_grp)
 *      Option b: Clear all counter groups (set cntr_grp = SX_PORT_CNTR_GRP_ALL)
 *
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - Logical Port ID.
 * @param[in] all_ports      - Clear all ports counters
 * @param[in] cntr_grp       - Performance counter group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_clear_set(const sx_api_handle_t    handle,
                                          const sx_port_log_id_t   log_port,
                                          const boolean_t          all_ports,
                                          const sx_port_cntr_grp_t cntr_grp);

/**
 * This API retrieves the port physical Layer counters from the SDK.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - READ/READ_CLEAR
 * @param[in] log_port          - Logical Port ID
 * @param[out] cntr_phy_layer_p - Physical Layer counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_phy_layer_get(const sx_api_handle_t     handle,
                                              const sx_access_cmd_t     cmd,
                                              const sx_port_log_id_t    log_port,
                                              sx_port_cntr_phy_layer_t *cntr_phy_layer_p);

/**
 * This API retrieves the port Physical Layer Statistic counters.
 *
 * Note:This API is capable of returning counters for 400GbE (8x lanes) ports.
 *  For non 400GbE ports (not 8x lanes), counters will be returned only for used lanes.
 * Note: When link_side is external, retrieved data will depend on the current FEC mode and the API's phy_raw_errors
 *   counters may represent counters for NO FEC, FC FEC, or RS FEC modes:
 *     NO FEC - edpl_bip_errors
 *     FC FEC - fc_fec_corrected_blocks
 *     RS FEc - rs_fec_corrected_symbols
 *  When link_side is Near or Far, retrieved data will represent corrected symbols for USR ZL FEC mode.
 * Note: It is not allowed to call this API when port bulk counter
 *  transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - READ/READ_CLEAR
 * @param[in] log_port    - Logical Port ID
 * @param[in] link_side   - The side of logical port to query
 * @param[out] cntr_p     - Physical Statistical Layer counters' entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_phy_layer_statistics_get(const sx_api_handle_t                handle,
                                                         const sx_access_cmd_t                cmd,
                                                         const sx_port_log_id_t               log_port,
                                                         const sx_port_phys_link_side_t       link_side,
                                                         sx_port_cntr_phy_layer_statistics_t *cntr_p);


/**
 * This API retrieves the port Physical Internal Link Layer counters.
 *
 * It is not allowed to call this API when port bulk counter
 * transaction (initiated by sx_api_bulk_counter_transaction_set API) is in progress.
 *
 * Supported devices: Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - READ/READ_CLEAR
 * @param[in] log_port    - Logical Port ID
 * @param[in] link_side   - The side of logical port to query (supported only Near or Far types)
 * @param[out] cntr_p     - Physical Internal Link Layer counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR if operation completes with failure
 * @return SX_STATUS_CMD_UNPERMITTED if port bulk counter transaction is in progress
 */
sx_status_t sx_api_port_counter_phy_layer_internal_link_get(const sx_api_handle_t                   handle,
                                                            const sx_access_cmd_t                   cmd,
                                                            const sx_port_log_id_t                  log_port,
                                                            const sx_port_phys_link_side_t          link_side,
                                                            sx_port_cntr_phy_layer_internal_link_t *cntr_p);

/**
 * This API initializes the port in the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Logical Port ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_init_set(const sx_api_handle_t  handle,
                                 const sx_port_log_id_t log_port);

/**
 * This API de-initializes the port in the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Logical Port ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_deinit_set(const sx_api_handle_t  handle,
                                   const sx_port_log_id_t log_port);

/**
 * This API sets storm control parameters of the given port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - ADD/EDIT/DELETE
 * @param[in] log_port               - Logical Port ID
 * @param[in] storm_control_id       - Storm Control ID
 * @param[in] storm_control_param_p  - Storm Control parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if hardware fails
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_storm_control_set(const sx_api_handle_t                 handle,
                                          const sx_access_cmd_t                 cmd,
                                          const sx_port_log_id_t                log_port,
                                          const sx_port_storm_control_id_t      storm_control_id,
                                          const sx_port_storm_control_params_t *storm_control_params_p);

/**
 * This API retrieves storm control parameters of the given port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] log_port                - Logical Port ID
 * @param[in] storm_control_id        - Storm Control ID
 * @param[out] storm_control_param_p  - Storm Control parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_storm_control_get(const sx_api_handle_t            handle,
                                          const sx_port_log_id_t           log_port,
                                          const sx_port_storm_control_id_t storm_control_id,
                                          sx_port_storm_control_params_t  *storm_control_params_p);

/**
 * This API clears storm control counter values of the given port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] log_port          - Logical Port ID
 * @param[in] storm_control_id  - Storm Control ID
 * @param[in] clear_counters    - Counters to clear
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_port_storm_control_counters_clear_set(const sx_api_handle_t              handle,
                                                         const sx_port_log_id_t             log_port,
                                                         const sx_port_storm_control_id_t   storm_control_id,
                                                         const sx_policer_counters_clear_t *clear_counters_p);

/**
 * This API retrieves storm control counters values of the given port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] log_port            - Logical Port ID
 * @param[in] storm_control_id    - Storm Control ID
 * @param[out] policer_counters_p - Pointer to a policer counter
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_port_storm_control_counters_get(const sx_api_handle_t            handle,
                                                   const sx_port_log_id_t           log_port,
                                                   const sx_port_storm_control_id_t storm_control_id,
                                                   sx_policer_counters_t           *policer_counters_p);

/**
 * This API controls sFlow configuration. Using the access command ADD, an sFlow sampling is defined on port.
 * After the sFlow configuration is set, the user can EDIT the sFlow parameters of a configured port.
 * To remove sFlow sampling from the port, access command DELETE can be used.
 * The API returns the sFlow params configured in practice. Deviation is returned in percentage.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - Access command (ADD/DELETE/EDIT)
 * @param[in] log_port            - Logical Port ID
 * @param[in, out] sflow_params_p - sFlow related configuration params (Deviation>0; ignored when CMD=DESTROY)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified port does not exist in database or port not configured with sflow
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if sflow is requested for add on port already configured with sflow
 * @return SX_STATUS_NO_MEMORY if there is no free memory
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_sflow_set(const sx_api_handle_t   handle,
                                  const sx_access_cmd_t   cmd,
                                  const sx_port_log_id_t  log_port,
                                  sx_port_sflow_params_t *sflow_params_p);


/**
 * This API gets the ports sFlow configuration.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - Logical Port ID
 * @param[out] sflow_params_p - sFlow related configuration parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if sflow is requested for port not configured with sflow
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_sflow_get(const sx_api_handle_t   handle,
                                  const sx_port_log_id_t  log_port,
                                  sx_port_sflow_params_t *sflow_params_p);

/**
 * This API retrieves the a counter of dropped packets per logical port or LAG.
 * The dropped packets counter accumulates the following:
 *   - Packets dropped due to lack of host CPU Rx buffer resources
 *   - Packets dropped by host CPU policers
 * The following events are not counted:
 *   - Packets dropped due to lack of shared buffer resources on duplication
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - access command (READ/READ_CLEAR/CLEAR)
 * @param[in] log_port      - Logical Port ID
 * @param[out] sflow_stat_p - sFlow statistics related configuration parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_ENTRY_NOT_FOUND if sflow is requested for port not configured with sflow
 * @return SX_STATUS_NO_MEMORY if there is no free memory
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_sflow_statistics_get(const sx_api_handle_t       handle,
                                             const sx_access_cmd_t       cmd,
                                             const sx_port_log_id_t      log_port,
                                             sx_port_sflow_statistics_t *sflow_stat_p);

/**
 * This API controls loopback filter state of the port.
 *
 * Notes relevant to NVE port:
 *  On Spectrum systems, changing of the state of the loopback filter is not supported on Spectrum.
 *  Changing of the state affects only UC traffic (MC and flooding are always filtered).
 *  The state of the filter can be changed only when there is a connected NVE tunnel in the system.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[in] lbf_mode - Loopback filter mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_loopback_filter_set(const sx_api_handle_t                handle,
                                            const sx_port_log_id_t               log_port,
                                            const sx_port_loopback_filter_mode_t lbf_mode);

/**
 * This API retrieves the loopback filter state of the port.
 *
 * Note: On Spectrum-2 systems, the API can retrieve the state of the loopback filter on the NVE port. The API can retrieve
 *  the state of the loopback filter on the NVE port only when there is connected NVE tunnel in the system.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - Logical Port ID
 * @param[out] lbf_mode_p - Loopback filter mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_loopback_filter_get(const sx_api_handle_t           handle,
                                            const sx_port_log_id_t          log_port,
                                            sx_port_loopback_filter_mode_t *lbf_mode_p);

/**
 * This API sets the isolation group of the port (a list of ports from which traffic should not be transmitted to log_port).
 * Isolation is supported only between ports that are on the same device and on the same SWID.
 *
 * SET adds ports to isolation group (overwrites previous configuration).
 * ADD adds ports to isolation group (in addition to previous configuration).
 * DELETE removes ports from isolation group.
 * DELETE_ALL empties isolation group.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - SET/ADD/DELETE/DELETE_ALL
 * @param[in] log_port          - Logical Port ID
 * @param[in] log_port_list_p   - List of logical ports
 * @param[in] log_port_cnt      - Number of logical ports in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in the database
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 */
sx_status_t sx_api_port_isolate_set(const sx_api_handle_t   handle,
                                    const sx_access_cmd_t   cmd,
                                    const sx_port_log_id_t  log_port,
                                    const sx_port_log_id_t *log_port_list_p,
                                    const uint32_t          log_port_cnt);

/**
 * This API retrieves the isolation group of the port (a list of ports from which traffic should not be transmitted to log_port).
 * Use log_port_cnt_p=0 to retrieve only the size of the isolation group.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] log_port            - Logical Port ID
 * @param[in,out] log_port_list_p - list of logical ports
 * @param[in,out] log_port_cnt_p  - [in] Number of logical ports in list/[out]Number of logical ports in LAG
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in the database
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 */
sx_status_t sx_api_port_isolate_get(const sx_api_handle_t  handle,
                                    const sx_port_log_id_t log_port,
                                    sx_port_log_id_t      *log_port_list_p,
                                    uint32_t              *log_port_cnt_p);

/**
 * This API defines port isolation mode: whether pass or filter frames, which went through the router.
 * This API is added for backward compatibility and for performance considerations.
 * If pass_routed_frames is True, frame performance penalty is possible. pass_routed_frames=True relates to the physical ports
 * and not to the internal tunnel ports.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] port_isolate_mode_p - Port isolate mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_ERROR if requested element is not found in the database
 * @return SX_STATUS_PARAM_ERROR if a parameters exceeds its range
 */
sx_status_t sx_api_port_isolate_mode_set(const sx_api_handle_t         handle,
                                         const sx_port_isolate_mode_t *port_isolate_mode_p);


/**
 * This API retrieves port isolation mode.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle               - SX-API handle
 * @param[out] port_isolate_mode_p - Port isolate mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */

sx_status_t sx_api_port_isolate_mode_get(const sx_api_handle_t   handle,
                                         sx_port_isolate_mode_t *port_isolate_mode_p);

/**
 * This API returns the SWID type as it was configured in the profile at the time of SDK initialization.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param swid          - Switch partition ID
 * @param swid_type_p   - DISABLED/ETHERNET/INFINIBAND
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 */
sx_status_t sx_api_port_swid_type_get(const sx_api_handle_t handle,
                                      const sx_swid_t       swid,
                                      sx_swid_type_t       *swid_type_p);

/**
 * This API creates a virtual port for port log_port and VLAN ID.
 *
 * ADD creates a VPort for the given logical port and VLAN.
 * DELETE deletes the given VPort.
 * DELETE_ALL deletes all VPorts from the given logical port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - ADD/DELETE/DELETE_ALL
 * @param[in] log_port          - Port or LAG
 * @param[in] vlan_id           - VLAN ID
 * @param[in,out] log_vport     - Logical port representing the virtual port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if command is unsupported in this API
 * @return SX_STATUS_ENTRY_NOT_FOUND if port does not exist OR VPort for delete command
 * @return SX_STATUS_PARAM_ERROR if vlan_id is not in the range or log_port type is invalid
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if virtual port already exists
 * @return SX_STATUS_NO_RESOURCES if there is no more room for VPorts to be added
 *
 */
sx_status_t sx_api_port_vport_set(const sx_api_handle_t  handle,
                                  const sx_access_cmd_t  cmd,
                                  const sx_port_log_id_t log_port,
                                  const sx_vlan_id_t     vlan_id,
                                  sx_port_log_id_t      *log_vport_p);

/**
 * This API returns the VPort VLANs created over the port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port              - Port or LAG
 * @param[out] vlan_id_p            - A list of all VLANs created on the port
 * @param[in,out] vport_vlan_cnt_p  - The number of vport_vlans to return (if vport_vlan_cnt_p==0, Only the number of vport_vlans
 *                                     will be returned and the list will remain empty)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if log_port does not exist
 * @return SX_STATUS_PARAM_ERROR if vlan_list_p is NULL
 *
 */
sx_status_t sx_api_port_vport_get(const sx_api_handle_t  handle,
                                  const sx_port_log_id_t log_port,
                                  sx_vlan_id_t          *vlan_id_list_p,
                                  uint32_t              *vport_vlan_cnt_p);

/**
 * This API returns the base port and VLAN properties for a given VPort.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] vport         - VPort logical ID
 * @param[out] vlan_id_p    - VLAN
 * @param[out] log_port_p   - Base port logical ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if VPort does not exist
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 *
 */
sx_status_t sx_api_port_vport_base_get(const sx_api_handle_t  handle,
                                       const sx_port_log_id_t vport,
                                       sx_vlan_id_t          *vlan_id_p,
                                       sx_port_log_id_t      *log_port_p);

/**
 * This API binds a flow counter to a virtual port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - BIND/UNBIND
 * @param[in] virtual_port      - Logical port representing the virtual port
 * @param[in] flow_counter_id   - The flow counter ID to be bound to the virtual port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if the command is unsupported in this API
 * @return SX_STATUS_ENTRY_NOT_FOUND if VPort or flow counter do not exist
 * @return SX_STATUS_ENTRY_ALREADY_BOUND if virtual port already has a counter
 *
 */
sx_status_t sx_api_port_vport_counter_bind_set(const sx_api_handle_t      handle,
                                               const sx_access_cmd_t      cmd,
                                               const sx_port_log_id_t     virtual_port,
                                               const sx_flow_counter_id_t flow_counter_id);

/**
 * This API retrieves the flow counter bound to the virtual port.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] virtual_port          - Logical port representing the virtual port
 * @param[out] flow_counter_id_p    - The flow counter ID bound to the virtual port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if VPort or flow counter do not exist
 *
 */
sx_status_t sx_api_port_vport_counter_bind_get(const sx_api_handle_t  handle,
                                               const sx_port_log_id_t virtual_port,
                                               sx_flow_counter_id_t  *flow_counter_id_p);

/**
 * This API sets the port's PHY mode in the SDK.
 *
 * Note: 1. Changing the FEC mode of 25GbE speed also sets 50GbE speed mode and vice versa.
 *       2. When changing FEC mode, the new setting will only apply after link training has succeeded.
 *          This can be achieved by toggling the port admin state (down-up).
 *       3. It is recommended to query the supported FEC capabilities before attempting to set a new mode.
 *          Attempting to set an unsupported FEC mode will be ignored, and the API will return a success.
 *
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] log_port          - Logical Port ID
 * @param[in] speed             - PHY Speed
 * @param[in] admin_mode    - New PHY admin mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 *
 */
sx_status_t sx_api_port_phy_mode_set(const sx_api_handle_t     handle,
                                     const sx_port_log_id_t    log_port,
                                     const sx_port_phy_speed_t speed,
                                     const sx_port_phy_mode_t  admin_mode);

/**
 * This API retrieves the port's phy mode from the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - Logical Port ID
 * @param[in] speed          - Phy Speed
 * @param[out] admin_mode_p  - Current port's admin phy mode (admin phy mode is per speed so speed is required for the admin value)
 * @param[out] oper_mode_p   - Current port's operational phy mode (operational phy mode is global and not per speed so that
 *                             speed is don't care for the operational value)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 *
 */
sx_status_t sx_api_port_phy_mode_get(const sx_api_handle_t handle,
                                     const sx_port_log_id_t log_port, const sx_port_phy_speed_t speed,
                                     sx_port_phy_mode_t* admin_mode_p, sx_port_phy_mode_t* oper_mode_p);

/**
 * This API enables to read/clear discard reason.
 *
 * Note: This release does not support the following causes.
 *  ip_discard:
 *   sx_port_cause_t packet_to_router_is_not_ip
 *   sx_port_cause_t dip_is_loopback
 *   sx_port_cause_t sip_is_in_class
 *   sx_port_cause_t sip is loopback
 *   sx_port_cause_t ip header not okay
 *   sx_port_cause_t ipv4 sip is limited broadcast
 *   sx_port_cause_t lpm ipv6 miss
 *   sx_port_cause_t IPv4 dip is limited broadcast
 *   sx_port_cause_t IPv4 dip is local
 *   sx_port_cause_t  NVE packet to overlay router
 *
 *  MPLS_discard:
 *   sx_port_cause_t outer_label_is_not_valid
 *   sx_port_cause_t no_IP_after_decap
 *   sx_port_cause_t expected_Bos_but_pop_did_not_expose_BoS;
 *   sx_port_cause_t php_decap_and_no_ip_header_or_ip_header_is_not_okay
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - READ/READ_CLEAR
 * @param[in,out] discard_reason_list_p - Array of discard reason
 * @param[in] list_count                - Array's length
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * O/W, the appropriate error code it returned.
 */
sx_status_t sx_api_port_discard_reason_get(const sx_api_handle_t     handle,
                                           const sx_access_cmd_t     cmd,
                                           sx_port_discard_reason_t *discard_reason_list_p,
                                           const uint32_t            list_count);

/**
 * This API sets the port's forwarding mode (cut-through vs. store-and-forward) in the SDK.
 *
 * Note: Port operational forwarding mode will be updated only after port toggling.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - Logical Port ID
 * @param[in] admin_fwd_mode - New administrative forwarding mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_forwarding_mode_set(const sx_api_handle_t           handle,
                                            const sx_port_log_id_t          log_port,
                                            const sx_port_forwarding_mode_t admin_fwd_mode);

/**
 * This API retrieves the port's forwarding mode (cut-through vs. store-and-forward) from the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] log_port          - Logical Port ID
 * @param[out] admin_fwd_mode_p - Administrative forwarding mode configured on this port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_forwarding_mode_get(const sx_api_handle_t      handle,
                                            const sx_port_log_id_t     log_port,
                                            sx_port_forwarding_mode_t *admin_fwd_mode_p);

/**
 * This API set the chip parsing depth in bytes.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] parsing_depth     - Parsing depth in bytes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_parsing_depth_set(const sx_api_handle_t handle,
                                          const uint16_t        parsing_depth);

/**
 * This API retrieves the chip parsing depth.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[out] parsing_depth_p - Return parsing depth in bytes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_parsing_depth_get(const sx_api_handle_t handle,
                                          uint16_t             *parsing_depth_p);


/**
 * This API is used to set Ethertypes globally. This API allows the user to configure additional Ethertypes per function.
 *
 * Note: Ethertype 0x8100 will always be configured by default.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - ADD/DELETE
 * @param[in] ether_types_p     - Pointer to struct holding a list of ether_types
 * @param[in] ether_type_count  - Number of Ethertypes being configured (in Spectrum systems, Max is 1)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any of the parameters are in error
 * @return SX_STATUS_NO_RESOURCES if no resources are available
 * @return SX_STATUS_ENTRY_NOT_FOUND if a DELETE is called on a non-existent Ethertype
 * @return SX_STATUS_RESOURCE_IN_USE if a DELETE is called while a resource is in use
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_vlan_ethertype_set(const sx_api_handle_t handle,
                                           const sx_access_cmd_t cmd,
                                           sx_vlan_ethertype_t  *ether_types_list_p,
                                           uint32_t              ether_type_count);

/**
 * This API gets a list of user configured Ethertypes.
 *
 * Note that 0x8100 is always configured and will not be retrieved.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle
 * @param[out] ether_types_p        - Pointer to struct to hold the retrieved list
 * @param[in, out] ether_type_count - Number of Ethertypes being retrieved (if ether_type_count==0, count is returns instead)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any of the parameters are in error
 * @return SX_STATUS_ERROR for a general error
 */

sx_status_t sx_api_port_vlan_ethertype_get(const sx_api_handle_t handle,
                                           sx_vlan_ethertype_t  *ether_types_list_p,
                                           uint32_t             *ether_type_count_p);

/**
 * This API is used to set values to the different Bit Error Rate (BER) profiles.
 *
 * Min/max values:
 * |--------------------------------|
 * |    Monitor     |  Min  |  Max  |
 * |--------------------------------|
 * |RS-FEC Pre-FEC  | 1e-9  | 1e-4  |
 * |--------------------------------|
 * |FC-FEC PRE-FEC  | 1e-11 | 1e-4  |
 * |--------------------------------|
 * |NO-FEC/Post-FEC | 1e-14 | 1e-8  |
 * |--------------------------------|
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - Network port only
 * @param[in] fec_profile    - The FEC profile to be used (RS/FC/NO)
 * @param[in] threshold_data - Threshold values to set (values of fraction of errors; final BER monitor threshold should be between 0 and 1)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_port_ber_threshold_set(const sx_api_handle_t                          handle,
                                          const sx_port_log_id_t                         log_port,
                                          const sx_port_ber_fec_profile_e                fec_profile,
                                          const sx_port_ber_fec_profile_threshold_data_t threshold_data);

/**
 * This API is used to retrieve values of the different Bit Error Rate (BER) profiles.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] log_port          - Network port only
 * @param[in] fec_profile       - The FEC profile to retrieve (RS/FC/NO)
 * @param[out] threshold_data_p - Threshold values
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_port_ber_threshold_get(const sx_api_handle_t                     handle,
                                          const sx_port_log_id_t                    log_port,
                                          const sx_port_ber_fec_profile_e           fec_profile,
                                          sx_port_ber_fec_profile_threshold_data_t *threshold_data_p);

/**
 * This API is used to configure the Bit Error Rate (BER) Monitor.
 * It is recommended to use sx_api_port_ber_monitor_operational_get after configuring this API to retrieve the FEC status
 * that is configured. This API is orthogonal to the port FEC configuration.
 * It is recommended to first register to SX_TRAP_ID_BER_MONITOR and to then set the monitor data so the first event will
 * be the current status.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] log_port     - The port to which to set the monitor (only network ports are supported)
 * @param[in] monitor_data - The monitor attributes to configure
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_port_ber_monitor_set(const sx_api_handle_t            handle,
                                        const sx_port_log_id_t           log_port,
                                        const sx_port_ber_monitor_data_t monitor_data);

/**
 * This API is used to retrieve values configured to the Bit Error Rate (BER) Monitor.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - The port to which the monitor is configured (only network ports are supported)
 * @param[out] monitor_data_p - Structure to hold the desired data
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_port_ber_monitor_get(const sx_api_handle_t       handle,
                                        const sx_port_log_id_t      log_port,
                                        sx_port_ber_monitor_data_t *monitor_data_p);

/**
 * This API is used to retrieve the current state of the Bit Error Rate (BER) Monitor.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] log_port             - The port to which the monitor is configured (only network ports are supported)
 * @param[out] monitor_oper_data_p - Structure to hold the desired data
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_NO_RESOURCES if cannot allocate resources
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_port_ber_monitor_operational_get(const sx_api_handle_t            handle,
                                                    const sx_port_log_id_t           log_port,
                                                    sx_port_ber_monitor_oper_data_t *monitor_oper_data_p);

/**
 * This API SETs the sll_max_time in microseconds.
 * SLL is the max lifetime of a frame within the switch. The packet is discarded after SLL time.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] sll_max_time - The SLL duration in micro seconds
 *                           Min value = 32usec and Max value = 4398046511 usec (or 4398sec)
 *                           Any value greater than max implies NO SLL (i.e., packets are never aged & discarded)
 *                           SDK will round the SLL duration to (the lowest power of 2 >= sll) * 4.096 (e.g., 500000 is rounded up to 536871)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behaviour occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_port_sll_set(const sx_api_handle_t handle,
                                const uint64_t        sll_max_time);

/**
 * This API GETs the system sll_max_time in microseconds.
 *
 * SLL is the max lifetime of a frame within the switch. The packet is discarded after SLL time.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[out] sll_max_time_p - The SLL duration in micro seconds
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behaviour occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_port_sll_get(const sx_api_handle_t handle,
                                uint64_t             *sll_max_time_p);
/**
 * This API SETs hll_max_time and the hll_stall_cnt for a given port
 *
 * HLL is a mechanism that discards packets that are awaiting transmission at the head of a scheduling group queue.
 * The max duration that a packet can wait in the queue is configurable after a certain number of packets are discarded.
 * This scheduling group may enter the STALL state if enabled.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Local port (only physical ports and LAG Ports are allowed)
 * @param[in] hll_max_time  - The HLL duration in micro seconds.
 *                            Min val = 4usec. Max val = 2147483usec (or 2sec)
 *                            Any value greater than max implies infinite HLL (or No HLL)
 *                            SDK will round the HLL time to (the lowest power of 2 >= hll) * 4.096 (e.g. 10000 will be rounded up to 16777)
 * @param[in] hll_stall_cnt - Number of packets that need to be discarded after which the queue enters stall state.
 *                            Valid range [0-7]; Default = 7; 0 = Stall Disabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_port_hll_set(const sx_api_handle_t  handle,
                                const sx_port_log_id_t log_port,
                                const uint32_t         hll_max_time,
                                const uint32_t         hll_stall_cnt);

/**
 * This API GETs hll_max_time and the hll_stall_cnt for a given port.
 *
 * HLL is a mechanism that discards packets that are awaiting transmission at the head of a scheduling group queue.
 * The max duration that a packet can wait in the queue is configurable. After a certain number of packets are discarded.
 * This scheduling group may enter the STALL state if enabled.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] log_port         - the local port (only Physical ports and LAG Ports are allowed)
 * @param[out] hll_max_time_p  - The HLL duration in micro seconds rounded up to (nearest power of 2) * 4.096
 * @param[out] hll_stall_cnt_p - Number of packets that need to be discarded after which the queue enters stall state
 *                               Valid range [0-7]; 0 = Stall Disabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_port_hll_get(const sx_api_handle_t  handle,
                                const sx_port_log_id_t log_port,
                                uint32_t              *hll_max_time_p,
                                uint32_t              *hll_stall_cnt_p);

/**
 * This API sets the options for how the port handles CRCs in the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - Logical Port ID
 * @param[in] crc_params     - CRC handling options
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_crc_params_set(const sx_api_handle_t       handle,
                                       const sx_port_log_id_t      log_port,
                                       const sx_port_crc_params_t *crc_params_p);

/**
 * This API gets the current options for how the port handles CRCs in the SDK.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - Logical Port ID
 * @param[out] crc_params    - CRC handling options
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_crc_params_get(const sx_api_handle_t  handle,
                                       const sx_port_log_id_t log_port,
                                       sx_port_crc_params_t  *crc_params_p);

/**
 * This API sets PTP port parameters.
 *
 * EDIT changes grand master port
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle                        - SX-API handle
 * @param[in] cmd                           - EDIT
 * @param[in] log_port                      - Log port to set
 * @param[in] port_ptp_params               - PTP port parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_ptp_params_set(const sx_api_handle_t       handle,
                                       const sx_access_cmd_t       cmd,
                                       const sx_port_log_id_t      log_port,
                                       const sx_port_ptp_params_t *port_ptp_params);

/**
 * This API gets PTP port role.
 *
 * GET changes grand master port
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - GET
 * @param[in] log_port               - Log port to query
 * @param[out] port_ptp_params       - PTP port parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_ptp_params_get(const sx_api_handle_t  handle,
                                       const sx_access_cmd_t  cmd,
                                       const sx_port_log_id_t log_port,
                                       sx_port_ptp_params_t  *port_ptp_params_p);


/**
 * This API sets the port rate values bitmask only (speed value and not physical connector type).
 *
 * This API is mutually exclusive with sx_api_port_speed_admin_set, so, per single SDK life cycle, only one of them can be used.
 *
 * Note: Disabling auto-negotiation also disables Auto FEC.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[in] rate_p   - Bitmask of new rates to enabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_rate_set(const sx_api_handle_t         handle,
                                 const sx_port_log_id_t        log_port,
                                 const sx_port_rate_bitmask_t *rate_p);

/**
 * This API gets the port operation rate value only.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical Port ID
 * @param[out] oper_rate_p  - Operational rate value
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_rate_get(const sx_api_handle_t  handle,
                                 const sx_port_log_id_t log_port,
                                 sx_port_rate_e        *oper_rate_p);

/**
 * This API gets bitmask of configured port rates values and is supported by ASIC bitmasks of rates and module types.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] log_port     - Logical port ID
 * @param[out]admin_rate_p - Configured by user rate values
 * @param[out]capab_rate_p - Supported rates on ASIC
 * @param[out]capab_type_p - Supported PMD module types on ASIC
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_rate_capability_get(const sx_api_handle_t              handle,
                                            const sx_port_log_id_t             log_port,
                                            sx_port_rate_bitmask_t            *admin_rate_p,
                                            sx_port_rate_bitmask_t            *capab_rate_p,
                                            sx_port_phy_module_type_bitmask_t *capab_type_p);

/**
 * This API sets the Physical Medium Depended (PMD) port type.
 * By default, all types are enabled. As such, this API allows to reduce the set of allowed port types.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * \deprecated This API is deprecated and will be removed in the future.
 * Please use sx_mgmt_phy_module_admin_type_set in its place.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] module_id - Module ID
 * @param[in] types_p   - New types enabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_phy_module_type_set(const sx_api_handle_t                    handle,
                                            const sx_port_mod_id_t                   module_id,
                                            const sx_port_phy_module_type_bitmask_t *types_p);
/**
 * This API gets the operational Physical Medium Dependent port type.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * \deprecated This API is deprecated and will be removed in the future.
 * Please use sx_mgmt_phy_module_oper_type_get in its place.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] module_id    - Module ID
 * @param[out] oper_type_p - Operational types
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_phy_module_type_get(const sx_api_handle_t      handle,
                                            const sx_port_mod_id_t     module_id,
                                            sx_port_phy_module_type_e *oper_type_p);

/**
 * This API gets the electrical interface types which are supported by module.
 *
 * \deprecated This API is deprecated and will be removed in the future.
 * Please use sx_mgmt_phy_module_capability_get in its place.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] module_id          - Module ID
 * @param[out] capab_port_rate_p - Supported by module rate values
 * @param[out] admin_types_p     - Configured by user port types to enable
 * @param[out] capab_types_p     - Supported by module electrical interfaces
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_phy_module_capability_get(const sx_api_handle_t              handle,
                                                  const sx_port_mod_id_t             module_id,
                                                  sx_port_rate_bitmask_t            *capab_port_rate_p,
                                                  sx_port_phy_module_type_bitmask_t *admin_types_p,
                                                  sx_port_phy_module_type_bitmask_t *capab_types_p);

/**
 * This API gets port physical information. It returns the port's current operational state and states how many times
 * the operational state has changed. It also returns the possible reasons a port is down.
 * READ_CLEAR, clears the port state change count after reading the count, but does not clear the port down reason.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle     - SX-API handle
 * @param[in]  cmd        - READ/READ_CLEAR
 * @param[in]  log_port   - Logical Port ID
 * @param[out] phy_stat_p - Port physical information
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_phy_info_get(const sx_api_handle_t  handle,
                                     const sx_access_cmd_t  cmd,
                                     const sx_port_log_id_t log_port,
                                     sx_port_phy_stat_t    *phy_stat_p);

/**
 * This API sets a port's user memory to any (8-bit) value specified by the user.
 * This API supports Network and CPU ports only.
 *
 * SET sets the ports in the list provided.
 * SET_ALL sets all ports to the parameters specified in the first list entry.
 *
 * Note: The value of the port user memory might be changed via ACLs asynchronously with this API call.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - SET/SET_ALL
 * @param[in] port_params_list_p - List of ports user memory parameters to set
 * @param[in] port_cnt           - Number of ports in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if the port list pointer is NULL
 * @return SX_STATUS_NO_MEMORY if failed to allocate memory for the port list
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_user_memory_set(const sx_api_handle_t               handle,
                                        const sx_access_cmd_t               cmd,
                                        const sx_port_user_memory_params_t *port_params_list_p,
                                        const uint32_t                      port_cnt);

/**
 * This API retrieves port's user memory value from the SDK. This API supports Network and CPU ports only.
 * The value of the port user memory might be changed via ACLs asynchronously with this API call.
 *
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in]     handle             - SX-API handle
 * @param[in,out] port_params_list_p - [in] list of ports for which to retrieve user memory parameters
 *                                     [out] a list port user memory for the specified ports
 * @param[in]     port_cnt           - Number of ports in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if the port list pointer is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_NO_MEMORY if failed to allocate memory for the port list
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_user_memory_get(const sx_api_handle_t         handle,
                                        sx_port_user_memory_params_t *port_params_list_p,
                                        const uint32_t                port_cnt);

/**
 * This API sets the power Mode of a module. This API internally disables and then enables the module with desired power
 * mode setting. This disable and enable will result in additional PMAOS events.
 *
 * \deprecated This API is deprecated and will be removed in the future. Please use sx_mgmt_phy_module_pwr_attr_set in its place.
 *
 * Note: By default, modules are initialized in low power mode and the module power mode is set as per EEPROM data in the
 * initialization process. SX_MGT_PHY_MOD_PWR_MODE_AUTO_E mode is used to reset power mode to default value.
 * Changing module power mode to SX_MGT_PHY_MOD_PWR_MODE_HIGH_E is not allowed.
 * Note: This API supports only power attribute SX_MGMT_PHY_MOD_PWR_ATTR_PWR_MODE_E.
 * Note: This API does not support changing the power attributes of backplane module.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] cmd        - SET
 * @param[in] module_id  - Module ID
 * @param[in] pwr_attr   - Power attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_ERROR if a module parameter is invalid or module type is backplane
 * @return SX_STATUS_ERROR if the power attribute setting fails
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not SET
 */
sx_status_t sx_mgmt_phy_mod_pwr_attr_set(const sx_api_handle_t             handle,
                                         const sx_access_cmd_t             cmd,
                                         const sx_port_mod_id_t            module_id,
                                         const sx_mgmt_phy_mod_pwr_attr_t *pwr_attr_p);

/**
 * This API gets the module power status.
 *
 * \deprecated This API is deprecated and will be removed in the future. Please use sx_mgmt_phy_module_pwr_attr_get in its place.
 * Note: This API returns the operational power mode and admin power mode as SX_MGMT_PHY_MOD_PWR_MODE_INVALID_E
 *   when the module is not plugged in.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] module_id      - Module ID
 * @param[in/out] pwr_attr_p - Phy module power attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR if the power attribute retrieval fails
 * @return SX_STATUS_PARAM_ERROR if a module parameter is invalid
 */
sx_status_t sx_mgmt_phy_mod_pwr_attr_get(const sx_api_handle_t       handle,
                                         const sx_port_mod_id_t      module_id,
                                         sx_mgmt_phy_mod_pwr_attr_t *pwr_attr_p);

/**
 * This API resets the phy module.
 *
 * \deprecated This API is deprecated and will be removed in the future. Please use sx_mgmt_phy_module_reset in its place.
 *
 * Note: Resetting the module might result in link flaps.
 * Note: PMAOS events are generated during reset functionality.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] module_id - module ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_ERROR if reset cannot be executed
 * @return SX_STATUS_PARAM_ERROR if a module parameter is invalid
 */

sx_status_t sx_mgmt_phy_mod_reset(const sx_api_handle_t  handle,
                                  const sx_port_mod_id_t module_id);


/**
 * This API retrieves the mapping attributes of all ports that have a
 * valid lane mapping between local port to module in a device.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 * Note - when port_attributes_list_p is NULL, port_cnt returns the count of ports
 * with valid mapping.
 *
 * @param[in]  handle                            - SX-API handle
 * @param[in]  device_id                         - Device ID
 * @param[out] port_attributes_list_p            - port mapping attributes list.
 * @param[in, out]  port_attributes_list_size_p  - port attribute list size(in).
 *                                               - count of port attribute entries returned(out).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STAUS_INVALID_HANDLE if a NULL handle is received.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL.
 * @return SX_STATUS_ERROR if the port mapping attribute retrieval failed.
 */

sx_status_t sx_api_port_device_mapping_get(const sx_api_handle_t handle,
                                           const sx_device_id_t  device_id,
                                           sx_port_attributes_t *port_attributes_list_p,
                                           uint32_t             *port_attributes_list_size_p);

/**
 * This API retrieves port connector type.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle            - SX-API handle
 * @param[in] log_port          - Logical Port ID
 * @param[out] connector_type_p - Pointer to a port connector type
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_port_connector_type_get(const sx_api_handle_t            handle,
                                           const sx_port_log_id_t           log_port,
                                           sx_port_connector_type_params_t *connector_type_p);

/**
 * This API retrieves remote port capability.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] log_port                  - Logical Port ID
 * @param[out] remote_port_capability_p - Pointer to remote port capability
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_port_remote_capability_get(const sx_api_handle_t             handle,
                                              const sx_port_log_id_t            log_port,
                                              sx_port_remote_port_capability_t *remote_port_capability_p);

/**
 * This API retrieves the port's enhanced state from the SDK.
 * This API replaces sx_api_port_state_get.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - Logical Port ID
 * @param[out] port_state_p - Port enhanced state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_state_ext_get(const sx_api_handle_t     handle,
                                      const sx_port_log_id_t    log_port,
                                      sx_port_ext_port_state_t *port_state_p);

#endif /* __SX_API_PORT_H__ */
