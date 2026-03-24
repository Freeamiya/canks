//
// Created by Free on 2026/3/18.
//

#ifndef CAN51_UART_H
#define CAN51_UART_H

#include "config.h"

void UART_Init(void);
void uart_printf(const char *format, ...);

#endif //CAN51_UART_H