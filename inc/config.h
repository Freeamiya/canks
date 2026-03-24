//
// Created by Free on 2026/3/18.
//

#ifndef CAN51_CONFIG_H
#define CAN51_CONFIG_H

#include <reg52.h>

#include <stdio.h>

#define Fclk      11059200UL
#define BAUD      9600UL

typedef unsigned char uint8;
typedef unsigned short int uint16;

#define XBYTE(addr) (*((volatile unsigned char xdata *)(addr)))

#define MDELAY(ms)                         \
    do {                                   \
        uint16 _i = (ms);                  \
        while(_i--)                        \
        {                                  \
            uint8 _j = 244;                \
            while(--_j);                   \
        }                                  \
    } while(0)

#endif //CAN51_CONFIG_H