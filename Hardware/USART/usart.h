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
#define UART_TX_BUFFER_SIZE     128
// 接收最大的个数
#define UART_RX_BUFFER_SIZE     128
// 发送的中断优先级
#define INTPRIO_ASCLIN2_TX      18
// 接收的中断优先级
#define INTPRIO_ASCLIN2_RX      19
// 发送的中断优先级
#define INTPRIO_ASCLIN3_TX      20
// 接收的中断优先级
#define INTPRIO_ASCLIN3_RX      21

// 定义发送和接收的引脚
#define UART2_PIN_TX             IfxAsclin2_TX_P02_0_OUT
#define UART2_PIN_RX             IfxAsclin2_RXB_P02_1_IN

// 定义发送和接收的引脚
#define UART3_PIN_TX             IfxAsclin3_TX_P32_3_OUT
#define UART3_PIN_RX             IfxAsclin3_RXD_P32_2_IN

extern IfxAsclin_Asc g_asc2Handle;
extern IfxAsclin_Asc g_asc3Handle;


void Uart2_Init(float32 baudrate);
void ASCLIN2_PutChar(char ch);
void ASCLIN2_PutStr(char *str);
void ASCLIN2_PutBuff(unsigned char *buff, int len);
uint16 ASCLIN2_GetCount(void);
char ASCLIN2_GetChar(void);
char ASCLIN2_GetBuff(unsigned char *data, int len);
void ASCLIN2_clearGetCount(void);
void my_printf2(pchar format, ...);


void Uart3_Init(float32 baudrate);
void ASCLIN3_PutChar(char ch);
void ASCLIN3_PutStr(char *str);
void ASCLIN3_PutBuff(unsigned char *buff, int len);
uint16 ASCLIN3_GetCount(void);
char ASCLIN3_GetChar(void);
char ASCLIN3_GetBuff(unsigned char *data, int len);
void ASCLIN3_clearGetCount(void);
void my_printf3(pchar format, ...);


#endif


