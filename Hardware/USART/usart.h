#ifndef __UART_H
#define __UART_H

#include <Ifx_Types.h>
#include <IfxAsclin.h>
#include <Ifx_Console.h>
#include <IfxCpu.h>
#include <Bsp.h>
// 通过包含该头文件 可以使用Asclin ASC模块的配置和设置函数 以及发送处理和接收数据等操作
#include "IfxAsclin_Asc.h"
// 通过包含该头文件 可以使用中断相关的函数和宏定义 以配置和管理中断
#include "IfxCpu_Irq.h"

// 发送最大的个数
#define UART_TX_BUFFER_SIZE     256
// 接收最大的个数
#define UART_RX_BUFFER_SIZE     256
// 发送的中断优先级
#define INTPRIO_ASCLIN2_TX      19
// 接收的中断优先级
#define INTPRIO_ASCLIN2_RX      18
// 定义发送和接收的引脚
#define UART_PIN_TX             IfxAsclin2_TX_P02_0_OUT
#define UART_PIN_RX             IfxAsclin2_RXB_P02_1_IN


extern IfxAsclin_Asc g_ascHandle;
extern char uart_finish;
extern uint16 g_rx_count;
extern uint8 rx_data[256];

typedef struct ASCLIN2_RX_Type {
        char rxbuf[8];
        char rx_sign;
        int rx_len;
} ASCLIN2_RX_Type;

extern ASCLIN2_RX_Type uart2_rx_message;

void Uart_Init(float32 baudrate);
void ASCLIN2_PutChar(char ch);
void ASCLIN2_PutStr(char *str);
void ASCLIN2_PutBuff(unsigned char *buff, int len);
uint8 ASCLIN2_GetCount(void);
char ASCLIN2_GetChar(void);
char ASCLIN2_GetBuff(unsigned char *data, int len);
void ASCLIN2_clearGetCount(void);
void my_printf(pchar format, ...);

#endif


