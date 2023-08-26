#include "usart.h"
#include "ccu6.h"
#include "string.h"
#include "led.h"

// 结构体用来表示ASCLIN模块的句柄或句柄相关数据
IfxAsclin_Asc g_asc2Handle;
IfxAsclin_Asc g_asc3Handle;
IfxAsclin_Asc g_asc1Handle;
IfxStdIf_DPipe  g_asc2StandardInterface;
IfxStdIf_DPipe  g_asc3StandardInterface;
IfxStdIf_DPipe  g_asc1StandardInterface;


static uint8 g_asc2TxBuffer[UART_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 g_asc2RxBuffer[UART_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 g_asc3TxBuffer[UART_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 g_asc3RxBuffer[UART_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 g_asc1TxBuffer[UART_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 g_asc1RxBuffer[UART_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

IFX_INTERRUPT(asclin2TxISR, 0, INTPRIO_ASCLIN2_TX);
void asclin2TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_asc2Handle);
}

IFX_INTERRUPT(asclin2RxISR, 0, INTPRIO_ASCLIN2_RX);
void asclin2RxISR(void)
{
    IfxAsclin_Asc_isrReceive(&g_asc2Handle);
    IfxCcu6_setT12CounterValue(&MODULE_CCU60, 0);
    IfxCcu6_Timer_start(&g_rx2_timer);
}

IFX_INTERRUPT(asclin3TxISR, 0, INTPRIO_ASCLIN3_TX);
void asclin3TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_asc3Handle);
}

IFX_INTERRUPT(asclin3RxISR, 0, INTPRIO_ASCLIN3_RX);
void asclin3RxISR(void)
{
    IfxAsclin_Asc_isrReceive(&g_asc3Handle);
    IfxCcu6_setT13CounterValue(&MODULE_CCU60, 0);
    IfxCcu6_Timer_start(&g_rx3_timer);
}

IFX_INTERRUPT(asclin1TxISR, 0, INTPRIO_ASCLIN1_TX);
void asclin1TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_asc1Handle);
}

IFX_INTERRUPT(asclin1RxISR, 0, INTPRIO_ASCLIN1_RX);
void asclin1RxISR(void)
{
    IfxAsclin_Asc_isrReceive(&g_asc1Handle);
    IfxCcu6_setT12CounterValue(&MODULE_CCU61, 0);
    IfxCcu6_Timer_start(&g_rx1_timer);
}

void my_printf2(pchar format, ...) {
    IfxStdIf_DPipe_print(&g_asc2StandardInterface, format);
}

void my_printf3(pchar format, ...) {
    IfxStdIf_DPipe_print(&g_asc3StandardInterface, format);
}

void my_printf1(pchar format, ...) {
    IfxStdIf_DPipe_print(&g_asc1StandardInterface, format);
}

void Uart2_Init(float32 baudrate) {

    // 关闭CPU中断
    char interruptState = disableInterrupts();

    // 配置ASCLIN模块的结构体
    IfxAsclin_Asc_Config asc_Config;
    // 配置中断结构体
    // 使用默认值初始化配置结构体
    IfxAsclin_Asc_initModuleConfig(&asc_Config, UART2_PIN_TX.module);
    IfxAsclin_Asc_initModuleConfig(&asc_Config, UART2_PIN_RX.module);

    // 配置ASCLIN2模块
    asc_Config.baudrate.baudrate = baudrate;     // 设置波特率
    asc_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;   // 数据长度
    asc_Config.dataBufferMode = Ifx_DataBufferMode_normal;  // 普通接收模式

    asc_Config.interrupt.txPriority = INTPRIO_ASCLIN2_TX;   // 设置发送中断优先级
    asc_Config.interrupt.rxPriority = INTPRIO_ASCLIN2_RX;   // 设置接收中断优先级
    asc_Config.interrupt.typeOfService = IfxSrc_Tos_cpu0;   // 选择CPU0来处理ASCLIN模块的中断请求
    asc_Config.txBuffer = &g_asc2TxBuffer;                   // 选择发送的缓冲区域
    asc_Config.txBufferSize = UART_TX_BUFFER_SIZE;          // 选择发送缓冲区域的内存大小
    asc_Config.rxBuffer = &g_asc2RxBuffer;                   // 选择接收的缓冲区域
    asc_Config.rxBufferSize = UART_RX_BUFFER_SIZE;          // 选择接收缓冲区域的内存大小

    // 设置ASCLIN2的引脚结构体
    const IfxAsclin_Asc_Pins pins = {
        NULL_PTR,      IfxPort_InputMode_pullUp,            // 不使用RTS引脚
        &UART2_PIN_RX, IfxPort_InputMode_pullUp,            // 设置RX引脚
        NULL_PTR,      IfxPort_OutputMode_pushPull,         // 不使用CTS引脚
        &UART2_PIN_TX, IfxPort_OutputMode_pushPull,         // 设置TX引脚
        IfxPort_PadDriver_cmosAutomotiveSpeed1             // 引脚的驱动器模式
    };
    // 配置引脚结构体 因为是const类型 所以传指针
    asc_Config.pins = &pins;

    // 初始化ASCLIN2模块
    IfxAsclin_Asc_initModule(&g_asc2Handle, &asc_Config);

    IfxAsclin_setRxFifoInterruptLevel(g_asc2Handle.asclin, IfxAsclin_RxFifoInterruptLevel_4);

    IfxAsclin_Asc_stdIfDPipeInit(&g_asc2StandardInterface, &g_asc2Handle);
    Ifx_Console_init(&g_asc2StandardInterface);

    IfxCpu_Irq_installInterruptHandler((void*)asclin2TxISR, INTPRIO_ASCLIN2_TX);
    IfxCpu_Irq_installInterruptHandler((void*)asclin2RxISR, INTPRIO_ASCLIN2_RX);

    // 打开CPU中断
    restoreInterrupts(interruptState);
}

void ASCLIN2_PutChar(char ch) {
    IfxAsclin_Asc_blockingWrite(&g_asc2Handle, ch);
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

uint16 ASCLIN2_GetCount(void) {
    return (uint16)IfxAsclin_Asc_getReadCount(&g_asc2Handle);
}

void ASCLIN2_clearGetCount(void) {
    IfxAsclin_Asc_clearRx(&g_asc2Handle);
}

char ASCLIN2_GetChar(void) {
    uint8 data=0;
    Ifx_SizeT count = 1;
    /* 获取接收到的一个字节数据 注意如果没有接收到，会一直等待 */
    IfxAsclin_Asc_read(&g_asc2Handle, &data, &count, TIME_INFINITE);
    return  data;
}

char ASCLIN2_GetBuff(unsigned char *data, int len) {
    Ifx_SizeT count = (Ifx_SizeT)len;

    if(ASCLIN2_GetCount() < len) {
        return 1;
    }

    IfxAsclin_Asc_read(&g_asc2Handle, data, &count, TIME_INFINITE);
    return  0;
}


void Uart3_Init(float32 baudrate) {

    // 关闭CPU中断
    char interruptState = disableInterrupts();

    // 配置ASCLIN模块的结构体
    IfxAsclin_Asc_Config asc3_Config;
    // 配置中断结构体
    // 使用默认值初始化配置结构体
    IfxAsclin_Asc_initModuleConfig(&asc3_Config, UART3_PIN_TX.module);
    IfxAsclin_Asc_initModuleConfig(&asc3_Config, UART3_PIN_RX.module);

    // 配置ASCLIN3模块
    asc3_Config.clockSource = IfxAsclin_ClockSource_kernelClock;
    asc3_Config.baudrate.baudrate = baudrate;     // 设置波特率
    asc3_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;   // 数据长度
    asc3_Config.dataBufferMode = Ifx_DataBufferMode_normal;  // 普通接收模式

    asc3_Config.frame.stopBit = IfxAsclin_StopBit_1;

    asc3_Config.fifo.buffMode = IfxAsclin_ReceiveBufferMode_rxFifo;

    asc3_Config.interrupt.txPriority = INTPRIO_ASCLIN3_TX;   // 设置发送中断优先级
    asc3_Config.interrupt.rxPriority = INTPRIO_ASCLIN3_RX;   // 设置接收中断优先级
    asc3_Config.interrupt.typeOfService = IfxSrc_Tos_cpu0;   // 选择CPU0来处理ASCLIN模块的中断请求
    asc3_Config.txBuffer = &g_asc3TxBuffer;                   // 选择发送的缓冲区域
    asc3_Config.txBufferSize = UART_TX_BUFFER_SIZE;          // 选择发送缓冲区域的内存大小
    asc3_Config.rxBuffer = &g_asc3RxBuffer;                   // 选择接收的缓冲区域
    asc3_Config.rxBufferSize = UART_RX_BUFFER_SIZE;          // 选择接收缓冲区域的内存大小


    // 设置ASCLIN3的引脚结构体
    const IfxAsclin_Asc_Pins pins = {
        NULL_PTR,      IfxPort_InputMode_pullUp,            // 不使用RTS引脚
        &UART3_PIN_RX, IfxPort_InputMode_pullUp,            // 设置RX引脚
        NULL_PTR,      IfxPort_OutputMode_pushPull,         // 不使用CTS引脚
        &UART3_PIN_TX, IfxPort_OutputMode_pushPull,         // 设置TX引脚
        IfxPort_PadDriver_cmosAutomotiveSpeed1             // 引脚的驱动器模式
    };
    // 配置引脚结构体 因为是const类型 所以传指针
    asc3_Config.pins = &pins;

    // 初始化ASCLIN3模块
    IfxAsclin_Asc_initModule(&g_asc3Handle, &asc3_Config);

    IfxAsclin_setRxFifoInterruptLevel(g_asc3Handle.asclin, IfxAsclin_RxFifoInterruptLevel_4);

    IfxAsclin_Asc_stdIfDPipeInit(&g_asc3StandardInterface, &g_asc3Handle);
    Ifx_Console_init(&g_asc3StandardInterface);

    IfxCpu_Irq_installInterruptHandler((void*)asclin3TxISR, INTPRIO_ASCLIN3_TX);
    IfxCpu_Irq_installInterruptHandler((void*)asclin3RxISR, INTPRIO_ASCLIN3_RX);

    // 打开CPU中断
    restoreInterrupts(interruptState);
}

void ASCLIN3_PutChar(char ch) {
    IfxAsclin_Asc_blockingWrite(&g_asc3Handle, ch);
}

void ASCLIN3_PutStr(char *str) {
   while(*str) {
       ASCLIN3_PutChar(*str++);
    }
}

void ASCLIN3_PutBuff(unsigned char *buff, int len) {
    while(len--) {
        ASCLIN3_PutChar(*buff);
        buff++;
    }
}

uint16 ASCLIN3_GetCount(void) {
    return (uint16)IfxAsclin_Asc_getReadCount(&g_asc3Handle);
}

void ASCLIN3_clearGetCount(void) {
    IfxAsclin_Asc_clearRx(&g_asc3Handle);
}

char ASCLIN3_GetChar(void) {
    uint8 data=0;
    Ifx_SizeT count = 1;
    /* 获取接收到的一个字节数据 注意如果没有接收到，会一直等待 */
    IfxAsclin_Asc_read(&g_asc3Handle, &data, &count, TIME_INFINITE);
    return data;
}

char ASCLIN3_GetBuff(unsigned char *data, int len) {
    Ifx_SizeT count = (Ifx_SizeT)len;

    if(ASCLIN3_GetCount() < len) {
        return 1;
    }

    IfxAsclin_Asc_read(&g_asc3Handle, data, &count, TIME_INFINITE);
    return 0;
}


void Uart1_Init(float32 baudrate) {

    // 关闭CPU中断
    char interruptState = disableInterrupts();

    // 配置ASCLIN模块的结构体
    IfxAsclin_Asc_Config asc1_Config;
    // 配置中断结构体
    // 使用默认值初始化配置结构体
    IfxAsclin_Asc_initModuleConfig(&asc1_Config, UART1_PIN_TX.module);
    IfxAsclin_Asc_initModuleConfig(&asc1_Config, UART1_PIN_RX.module);

    // 配置ASCLIN3模块
    asc1_Config.clockSource = IfxAsclin_ClockSource_kernelClock;
    asc1_Config.baudrate.baudrate = baudrate;     // 设置波特率
    asc1_Config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;   // 数据长度
    asc1_Config.dataBufferMode = Ifx_DataBufferMode_normal;  // 普通接收模式

    asc1_Config.frame.stopBit = IfxAsclin_StopBit_1;

    asc1_Config.fifo.buffMode = IfxAsclin_ReceiveBufferMode_rxFifo;

    asc1_Config.interrupt.txPriority = INTPRIO_ASCLIN1_TX;   // 设置发送中断优先级
    asc1_Config.interrupt.rxPriority = INTPRIO_ASCLIN1_RX;   // 设置接收中断优先级
    asc1_Config.interrupt.typeOfService = IfxSrc_Tos_cpu0;   // 选择CPU0来处理ASCLIN模块的中断请求
    asc1_Config.txBuffer = &g_asc1TxBuffer;                   // 选择发送的缓冲区域
    asc1_Config.txBufferSize = UART_TX_BUFFER_SIZE;          // 选择发送缓冲区域的内存大小
    asc1_Config.rxBuffer = &g_asc1RxBuffer;                   // 选择接收的缓冲区域
    asc1_Config.rxBufferSize = UART_RX_BUFFER_SIZE;          // 选择接收缓冲区域的内存大小


    // 设置ASCLIN1的引脚结构体
    const IfxAsclin_Asc_Pins pins = {
        NULL_PTR,      IfxPort_InputMode_pullUp,            // 不使用RTS引脚
        &UART1_PIN_RX, IfxPort_InputMode_pullUp,            // 设置RX引脚
        NULL_PTR,      IfxPort_OutputMode_pushPull,         // 不使用CTS引脚
        &UART1_PIN_TX, IfxPort_OutputMode_pushPull,         // 设置TX引脚
        IfxPort_PadDriver_cmosAutomotiveSpeed1             // 引脚的驱动器模式
    };
    // 配置引脚结构体 因为是const类型 所以传指针
    asc1_Config.pins = &pins;

    // 初始化ASCLIN1模块
    IfxAsclin_Asc_initModule(&g_asc1Handle, &asc1_Config);

    IfxAsclin_setRxFifoInterruptLevel(g_asc1Handle.asclin, IfxAsclin_RxFifoInterruptLevel_4);

    IfxAsclin_Asc_stdIfDPipeInit(&g_asc1StandardInterface, &g_asc1Handle);
    Ifx_Console_init(&g_asc1StandardInterface);

    IfxCpu_Irq_installInterruptHandler((void*)asclin1TxISR, INTPRIO_ASCLIN1_TX);
    IfxCpu_Irq_installInterruptHandler((void*)asclin1RxISR, INTPRIO_ASCLIN1_RX);

    // 打开CPU中断
    restoreInterrupts(interruptState);
}

void ASCLIN1_PutChar(char ch) {
    IfxAsclin_Asc_blockingWrite(&g_asc1Handle, ch);
}

void ASCLIN1_PutStr(char *str) {
   while(*str) {
       ASCLIN1_PutChar(*str++);
    }
}

void ASCLIN1_PutBuff(unsigned char *buff, int len) {
    while(len--) {
        ASCLIN1_PutChar(*buff);
        buff++;
    }
}

uint16 ASCLIN1_GetCount(void) {
    return (uint16)IfxAsclin_Asc_getReadCount(&g_asc1Handle);
}

void ASCLIN1_clearGetCount(void) {
    IfxAsclin_Asc_clearRx(&g_asc1Handle);
}

char ASCLIN1_GetChar(void) {
    uint8 data=0;
    Ifx_SizeT count = 1;
    /* 获取接收到的一个字节数据 注意如果没有接收到，会一直等待 */
    IfxAsclin_Asc_read(&g_asc1Handle, &data, &count, TIME_INFINITE);
    return data;
}

char ASCLIN1_GetBuff(unsigned char *data, int len) {
    Ifx_SizeT count = (Ifx_SizeT)len;

    if(ASCLIN1_GetCount() < len) {
        return 1;
    }

    IfxAsclin_Asc_read(&g_asc1Handle, data, &count, TIME_INFINITE);
    return 0;
}



