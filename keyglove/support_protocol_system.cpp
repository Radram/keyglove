// Keyglove controller source code - KGAPI "system" protocol command parser implementation
// 2014-11-28 by Jeff Rowberg <jeff@rowberg.net>

/* ============================================
Controller code is placed under the MIT license
Copyright (c) 2014 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

/**
 * @file support_protocol_system.cpp
 * @brief KGAPI "system" protocol command parser implementation
 * @author Jeff Rowberg
 * @date 2014-11-28
 *
 * This file implements subsystem-specific command processing functions for the
 * "system" part of the KGAPI protocol.
 *
 * This file is autogenerated. Normally it is not necessary to edit this file.
 */

#include "keyglove.h"
#include "support_protocol.h"
//#include "support_protocol_system.h"

/**
 * @brief Command processing routine for "system" packet class
 * @param[in] rxPacket Incoming KGAPI packet buffer
 * @return Protocol error, if any (0 for success)
 * @see protocol_parse()
 * @see KGAPI command: kg_cmd_system_ping()
 * @see KGAPI command: kg_cmd_system_reset()
 * @see KGAPI command: kg_cmd_system_get_info()
 * @see KGAPI command: kg_cmd_system_get_memory()
 * @see KGAPI command: kg_cmd_system_set_timer()
 * @see KGAPI command: kg_cmd_system_get_battery_status()
 */
uint8_t process_protocol_command_system(uint8_t *rxPacket) {
    // check for valid command IDs
    uint8_t protocol_error = 0;
    switch (rxPacket[3]) {
        case KG_PACKET_ID_CMD_SYSTEM_PING: // 0x01
            // system_ping()(uint32_t uptime)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint32_t uptime;
                uint16_t result = kg_cmd_system_ping(&uptime);
        
                // build response
                uint8_t payload[4] = { uptime & 0xFF, (uptime >> 8) & 0xFF, (uptime >> 16) & 0xFF, (uptime >> 24) & 0xFF };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 4, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_RESET: // 0x02
            // system_reset(uint8_t type)(uint16_t result)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_system_reset(rxPacket[4]);
        
                // build and send response if needed
                if (result != 0xFFFF) {
                    // build response
                    uint8_t payload[2] = { result & 0xFF, (result >> 8) & 0xFF };
        
                    // send response
                    send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
                }
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_GET_INFO: // 0x03
            // system_get_info()(uint8_t major, uint8_t minor, uint8_t patch, uint32_t timestamp)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t major;
                uint8_t minor;
                uint8_t patch;
                uint32_t timestamp;
                uint16_t result = kg_cmd_system_get_info(&major, &minor, &patch, &timestamp);
        
                // build response
                uint8_t payload[7] = { major, minor, patch, timestamp & 0xFF, (timestamp >> 8) & 0xFF, (timestamp >> 16) & 0xFF, (timestamp >> 24) & 0xFF };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 7, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_GET_MEMORY: // 0x04
            // system_get_memory()(uint32_t free_ram, uint32_t total_ram)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint32_t free_ram;
                uint32_t total_ram;
                uint16_t result = kg_cmd_system_get_memory(&free_ram, &total_ram);
        
                // build response
                uint8_t payload[8] = { free_ram & 0xFF, (free_ram >> 8) & 0xFF, (free_ram >> 16) & 0xFF, (free_ram >> 24) & 0xFF, total_ram & 0xFF, (total_ram >> 8) & 0xFF, (total_ram >> 16) & 0xFF, (total_ram >> 24) & 0xFF };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 8, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_SET_TIMER: // 0x05
            // system_set_timer(uint8_t handle, uint16_t interval, uint8_t oneshot)(uint16_t result)
            // parameters = 4 bytes
            if (rxPacket[1] != 4) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_system_set_timer(rxPacket[4], rxPacket[5] | (rxPacket[6] << 8), rxPacket[7]);
        
                // build response
                uint8_t payload[2] = { result & 0xFF, (result >> 8) & 0xFF };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_GET_BATTERY_STATUS: // 0x06
            // system_get_battery_status()(uint8_t status, uint8_t level)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t status;
                uint8_t level;
                uint16_t result = kg_cmd_system_get_battery_status(&status, &level);
        
                // build response
                uint8_t payload[2] = { status, level };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        default:
            protocol_error = KG_PROTOCOL_ERROR_INVALID_COMMAND;
    }
    return protocol_error;
}

/* 0x01 */ uint8_t (*kg_evt_system_boot)(uint8_t major, uint8_t minor, uint8_t patch, uint32_t timestamp);
/* 0x02 */ uint8_t (*kg_evt_system_ready)();
/* 0x03 */ uint8_t (*kg_evt_system_error)(uint16_t code);
/* 0x04 */ uint8_t (*kg_evt_system_timer_tick)(uint8_t handle, uint32_t seconds, uint8_t subticks);
/* 0x05 */ uint8_t (*kg_evt_system_battery_status)(uint8_t status, uint8_t level);
