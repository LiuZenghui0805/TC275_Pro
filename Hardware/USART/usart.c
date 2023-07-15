#include "usart.h"

// 结构体用来表示ASCLIN模块的句柄或句柄相关数据
IfxAsclin_Asc g_ascHandle;

static uint8 g_ascTxBuffer[UART_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 g_ascRxBuffer[UART_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];


IFX_INTERRUPT(asclin2TxISR, 0, INTPRIO_ASCLIN2_TX);
void asclin2TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_ascHandle);
}


IFX_INTERRUPT(asclin2RxISR, 0, INTPRIO_ASCLIN2_RX);
void asclin2RxISR(void)
{
    IfxAsclin_Asc_isrReceive(&g_ascHandle);
}


void Uart_Init(float32 baudrate) {

    // 关闭CPU中断
    char interruptState = disableInterrupts();
    // 配置ASCLIN模块的结构体
    IfxAsclin_Asc_Config asc_Config;
    // 配置中断结构体

    // 使用默认值初始化配置结构体
    IfxAsclin_Asc_initModuleConfig(&asc_Config, UART_PIN_TX.module);
    IfxAsclin_Asc_initModuleConfig(&asc_Config, UART_PIN_RX.module);
    // 配置ASCLIN2模块
    asc_Config.baudrate.baudrate = baudrate;     // 设置波特率
    asc_Config.baudrate.prescaler = 4;            // 数据帧模式
    asc_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;   // 数据长度
    asc_Config.dataBufferMode = Ifx_DataBufferMode_normal;  // 普通接收模式

    asc_Config.interrupt.txPriority = INTPRIO_ASCLIN2_TX;   // 设置发送中断优先级
    asc_Config.interrupt.rxPriority = INTPRIO_ASCLIN2_RX;   // 设置接收中断优先级
    asc_Config.interrupt.typeOfService = IfxSrc_Tos_cpu0;   // 选择CPU0来处理ASCLIN模块的中断请求
    asc_Config.txBuffer = &g_ascTxBuffer;                   // 选择发送的缓冲区域
    asc_Config.txBufferSize = UART_TX_BUFFER_SIZE;          // 选择发送缓冲区域的内存大小
    asc_Config.rxBuffer = &g_ascRxBuffer;                   // 选择接收的缓冲区域
    asc_Config.rxBufferSize = UART_RX_BUFFER_SIZE;          // 选择接收缓冲区域的内存大小

    // 设置ASCLIN2的引脚结构体
    const IfxAsclin_Asc_Pins pins = {
        NULL_PTR,     IfxPort_InputMode_pullUp,            // 不使用RTS引脚
        &UART_PIN_RX, IfxPort_InputMode_pullUp,            // 设置RX引脚
        NULL_PTR,     IfxPort_OutputMode_pushPull,         // 不使用CTS引脚
        &UART_PIN_TX, IfxPort_OutputMode_pushPull,         // 设置TX引脚
        IfxPort_PadDriver_cmosAutomotiveSpeed1             // 引脚的驱动器模式
    };
    // 配置引脚结构体 因为是const类型 所以传指针
    asc_Config.pins = &pins;
    // 初始化ASCLIN2模块
    IfxAsclin_Asc_initModule(&g_ascHandle, &asc_Config);

    IfxCpu_Irq_installInterruptHandler((void*)asclin2TxISR, INTPRIO_ASCLIN2_TX);
    IfxCpu_Irq_installInterruptHandler((void*)asclin2RxISR, INTPRIO_ASCLIN2_RX);

    // 打开CPU中断
    restoreInterrupts(interruptState);
}

void ASCLIN2_PutChar(char ch) {
    IfxAsclin_Asc_blockingWrite(&g_ascHandle, ch);
}

void ASCLIN2_PutStr(char *str) {
   while(*str) {
       ASCLIN2_PutChar(*str++);
    }
}

void ASCLIN2_PutBuff(unsigned char *buff, int len) {
    while(len--) {
        ASCLIN2_PutChar(*buff);
        buff++;
    }
}

uint8 ASCLIN2_GetCount(void) {
    return (uint8)IfxAsclin_Asc_getReadCount(&g_ascHandle);
}

void ASCLIN2_clearGetCount(void) {
    IfxAsclin_Asc_clearRx(&g_ascHandle);
}

char ASCLIN2_GetChar(void) {
    uint8 data=0;
    Ifx_SizeT count = 1;
    /* 获取接收到的一个字节数据 注意如果没有接收到，会一直等待 */
    IfxAsclin_Asc_read(&g_ascHandle, &data, &count, TIME_INFINITE);
    return  data;
}

char ASCLIN2_GetBuff(unsigned char *data, int len) {
    Ifx_SizeT count = (Ifx_SizeT)len;

    if(ASCLIN2_GetCount() < len) {
        return 1;
    }

    IfxAsclin_Asc_read(&g_ascHandle, data, &count, TIME_INFINITE);
    return  0;
}


