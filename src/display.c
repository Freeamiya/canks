//
// Created by Free on 2026/3/26.
//

#include "display.h"

uint8 code SegCode[] = {
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
    0x07, //7
    0x7F, //8
    0x6F  //9
};

void get_digits(uint8 num, uint8 *digits)
{
    digits[1] = num / 10;   // 十位
    digits[0] = num % 10;   // 个位

    if(num < 10)
    {
        digits[1] = 0;
    }
}

void SEG_Display(uint8 num)
{
    uint8 display[2];

    get_digits(num, display);

    for (uint8 j = 0; j < 20; j++)
    {
        for (uint8 i = 0; i < 2; i++)
        {
            P0 = 0xFF;
            P2 |= 0x03;     // P2.0 P2.1 = 1
            P1 = SegCode[display[i]];
            switch(i)
            {
                case 0: P2 &= ~0x01; break; // 第1位
                case 1: P2 &= ~0x02; break; // 第2位
            }
            MDELAY(1);
        }
    }
}