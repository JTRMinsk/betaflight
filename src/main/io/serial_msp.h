/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// Each MSP port requires state and a receive buffer, revisit this default if someone needs more than 2 MSP ports.
#define MAX_MSP_PORT_COUNT 2

typedef enum {
    IDLE,
    HEADER_START,
    HEADER_M,
    HEADER_ARROW,
    HEADER_SIZE,
    HEADER_CMD,
    COMMAND_RECEIVED
} mspState_e;

#define MSP_PORT_INBUF_SIZE 64

struct serialPort_s;
typedef struct mspPort_s {
    struct serialPort_s *port; // null when port unused.
    uint8_t offset;
    uint8_t dataSize;
    uint8_t checksum;
    uint8_t indRX;
    uint8_t inBuf[MSP_PORT_INBUF_SIZE];
    mspState_e c_state;
    uint8_t cmdMSP;
} mspPort_t;


extern struct serialPort_s *mspSerialPort;
extern mspPort_t *currentPort;

struct bufWriter_s;
extern struct bufWriter_s *writer;

extern bool isRebootScheduled;


struct serialConfig_s;
void mspSerialInit(struct serialConfig_s *serialConfig);
void mspSerialProcess(void);
void mspSerialAllocatePorts(struct serialConfig_s *serialConfig);
void mspSerialReleasePortIfAllocated(struct serialPort_s *serialPort);
