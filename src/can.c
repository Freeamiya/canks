//
// Created by Free on 2026/3/18.
//

#include "can.h"
#include "uart.h"
#include "gateway.h"

uint8 node1_data = 0;
uint8 node2_data = 0;
bit rx_flag = 0;
uint8 RX_buffer[FrameNum];
uint8 TX_buffer[FrameNum];  //发送的数据

// ===== CAN初始化 =====
void CAN_Init(void)
{
    uint8 Status;

    // ===== SJA1000初始化 =====
    do
    {
        SJA_MOD = RM_BIT | AFM_BIT;
        Status = SJA_MOD;
    } while (!(Status & RM_BIT));

    SJA_CDR = CANMode_BIT | CLKOff_BIT;
    SJA_BTR0 = 0x02;   // BRP=3, SJW=1
    SJA_BTR1 = 0x3A;   // TSEG1=11, TSEG2=4 → 125kbps @12MHz

    SJA_IER = RIE_BIT;
    SJA_OCR = NormalMode | Tx0PullDn | OCPOL1_BIT | Tx1PullUp;
    SJA_CMR = RRB_BIT;

    SJA_AMR0 = 0xff;
    SJA_AMR1 = 0xff;
    SJA_AMR2 = 0xff;
    SJA_AMR3 = 0xff;

    do
    {   //确保进入自接收模式
		SJA_MOD   = STM_BIT;
		Status  = SJA_MOD;
    }
    while( !(Status & STM_BIT) );
}

// ===== CAN接收中断 =====
void Peli_RXD(void) interrupt 2
{
    uint8 Status;
    EA = 0; //关闭总中断
    Status = SJA_IR;
    if (Status & RI_BIT)
    {
        // 读取一帧
        RX_buffer[0] = SJA_RBSR0;
        RX_buffer[1] = SJA_RBSR1;
        RX_buffer[2] = SJA_RBSR2;
        RX_buffer[3] = SJA_RBSR3;
        RX_buffer[4] = SJA_RBSR4;
        RX_buffer[5] = SJA_RBSR5;
        RX_buffer[6] = SJA_RBSR6;
        RX_buffer[7] = SJA_RBSR7;
        RX_buffer[8] = SJA_RBSR8;
        RX_buffer[9] = SJA_RBSR9;
        RX_buffer[10] = SJA_RBSR10;
        RX_buffer[11] = SJA_RBSR11;
        RX_buffer[12] = SJA_RBSR12;

        //can_id = (RX_buffer[1] << 3) | (RX_buffer[2] >> 5);

        // ===== 数据区分 =====
        node1_data = RX_buffer[5];

        // 释放缓冲区
        SJA_CMR = RRB_BIT;
        Status = SJA_ALC;
        Status = SJA_ECC;
        rx_flag = 1;
    }

    SJA_IER = RIE_BIT;
    EA = 1; //打开总中断
}

void Peli_TXD(uint8 tx_data)
{
    uint8 Status;

    TX_buffer[0] = 0x88;//.7=0扩展帧；.6=0数据帧; .3=1数据长度
    TX_buffer[1] = 0x01;//本节点地址
    TX_buffer[2] = 0x02;//
    TX_buffer[3] = 0x03;//
    TX_buffer[4] = 0x04;//
    TX_buffer[5]  = tx_data;
    TX_buffer[6]  = 0x22;
    TX_buffer[7]  = 0x33;
    TX_buffer[8]  = 0x44;//
    TX_buffer[9]  = 0x55;//
    TX_buffer[10] = 0x66;//
    TX_buffer[11] = 0x77;//
    TX_buffer[12] = 0x88;//

    do
    {
        Status = SJA_SR;
    } while (Status & RS_BIT);

    do
    {
        Status = SJA_SR;
    } while (!(Status & TCS_BIT));

    do
    {
        Status = SJA_SR;
    } while (!(Status & TBS_BIT));

    SJA_TBSR0  = TX_buffer[0];
    SJA_TBSR1  = TX_buffer[1];
    SJA_TBSR2  = TX_buffer[2];
    SJA_TBSR3  = TX_buffer[3];
    SJA_TBSR4  = TX_buffer[4];
    SJA_TBSR5  = TX_buffer[5];
    SJA_TBSR6  = TX_buffer[6];
    SJA_TBSR7  = TX_buffer[7];
    SJA_TBSR8  = TX_buffer[8];
    SJA_TBSR9  = TX_buffer[9];
    SJA_TBSR10 = TX_buffer[10];
    SJA_TBSR11 = TX_buffer[11];
    SJA_TBSR12  = TX_buffer[12];

    SJA_CMR = SRR_BIT;
}