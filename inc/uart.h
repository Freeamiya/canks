//
// Created by Free on 2026/3/18.
//

#ifndef CAN51_UART_H
#define CAN51_UART_H

#include "config.h"

extern uint8 uart_rx_data;
extern bit uart_rx_flag;

void UART_Init(void);
void UART_SendByte(uint8 dat);
void UART_SendStr(char *s);
void UART_SendHex(uint8 dat);
void UART_ISR(void) interrupt 4;

#endif //CAN51_UART_H