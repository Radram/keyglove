// Keyglove controller source code - KGAPI "touch" protocol command parser declarations
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
 * @file support_protocol_touch.h
 * @brief KGAPI "touch" protocol command parser declarations
 * @author Jeff Rowberg
 * @date 2014-11-28
 *
 * This file implements subsystem-specific command processing functions for the
 * "touch" part of the KGAPI protocol.
 *
 * This file is autogenerated. Normally it is not necessary to edit this file.
 */

#ifndef _SUPPORT_PROTOCOL_TOUCH_H_
#define _SUPPORT_PROTOCOL_TOUCH_H_

/* =========================== */
/* KGAPI CONSTANT DECLARATIONS */
/* =========================== */

#define KG_PACKET_ID_CMD_TOUCH_GET_MODE                     0x01
#define KG_PACKET_ID_CMD_TOUCH_SET_MODE                     0x02
// -- command/event split --
#define KG_PACKET_ID_EVT_TOUCH_MODE                         0x01
#define KG_PACKET_ID_EVT_TOUCH_STATUS                       0x02

/* ================================ */
/* KGAPI COMMAND/EVENT DECLARATIONS */
/* ================================ */

/* 0x01 */ uint16_t kg_cmd_touch_get_mode(uint8_t *mode);
/* 0x02 */ uint16_t kg_cmd_touch_set_mode(uint8_t mode);
// -- command/event split --
/* 0x01 */ extern uint8_t (*kg_evt_touch_mode)(uint8_t mode);
/* 0x02 */ extern uint8_t (*kg_evt_touch_status)(uint8_t status_len, uint8_t *status_data);

uint8_t process_protocol_command_touch(uint8_t *rxPacket);

#endif // _SUPPORT_PROTOCOL_TOUCH_H_
