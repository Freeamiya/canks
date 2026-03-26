//
// Created by Free on 2026/3/18.
//

#ifndef CAN51_GATEWAY_H
#define CAN51_GATEWAY_H

#include "config.h"
#include "uart.h"
#include "can.h"

extern uint8 tr_count;

void Gateway_Process(void);

#endif //CAN51_GATEWAY_H