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
    uint8 shi = num / 10;
    uint8 ge  = num % 10;

    // ===== 显示十位 =====
    DIG1 = 1;
    DIG2 = 0;
    P1 = SegCode[shi];
    MDELAY(2);

    // ===== 显示个位 =====
    DIG1 = 0;
    DIG2 = 1;
    P1 = SegCode[ge];
    MDELAY(2);
}