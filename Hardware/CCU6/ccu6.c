#include "ccu6.h"
#include "led.h"


uint16 g_rx2_finsh = 0;
uint16 g_rx3_finsh = 0;
uint16 g_rx1_finsh = 0;

IfxCcu6_Timer g_rx2_timer;
IfxCcu6_Timer g_rx3_timer;
IfxCcu6_Timer g_rx1_timer;

IFX_INTERRUPT(isrCCU6Timer, 0, ISR_PRIORITY_CCU6_INT1);
void isrCCU6Timer(void)
{
    g_rx2_finsh = 1; /* Increase value of the counter each time the ISR is called */
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU60, IfxCcu6_InterruptSource_t12PeriodMatch);
    IfxCcu6_Timer_stop(&g_rx2_timer);
    IfxCcu6_setT12CounterValue(&MODULE_CCU60, 0);
}

IFX_INTERRUPT(isrCCU61Timer, 0, ISR_PRIORITY_CCU61_INT1);
void isrCCU61Timer(void)
{
    g_rx3_finsh = 1; /* Increase value of the counter each time the ISR is called */
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU60, IfxCcu6_InterruptSource_t13PeriodMatch);
    IfxCcu6_Timer_stop(&g_rx3_timer);
    IfxCcu6_setT13CounterValue(&MODULE_CCU60, 0);
}

IFX_INTERRUPT(isrCCU62Timer, 0, ISR_PRIORITY_CCU62_INT1);
void isrCCU62Timer(void)
{
    g_rx1_finsh = 1;
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU61, IfxCcu6_InterruptSource_t12PeriodMatch);
    IfxCcu6_Timer_stop(&g_rx1_timer);
    IfxCcu6_setT12CounterValue(&MODULE_CCU61, 0);
}

void ccu6_init(void)
{
    IfxCcu6_Timer_Config timerConfig;
    /**
     * 可以通过该注释了解计时器模块结构的默认配置 初始化计时器模块结构是为了在配置计时器模块之前
     * 确保所有的配置选项都有合理的默认值 这有助于简化配置流程 并且可以只更改需要自定义的配置选项
     */
    IfxCcu6_Timer_initModuleConfig(&timerConfig, &MODULE_CCU60); // 使用默认值初始化计时器模块结构
    uint8 i = 0;
    uint32 period = 0;
    uint64 clk = 0;
    clk = IfxScuCcu_getSpbFrequency();
    uint16 us = 50000;
    while (i++ < 16)
    {
        period = (uint32) (clk * us / 1000000);
        if (period < 0xffff)
        {
            break;
        }
        else
        {
            clk = clk / 2;
        }
    }

    timerConfig.clock.t12countingInputMode = IfxCcu6_CountingInputMode_internal;    // 定时器的计数输入模式为内部时钟作为计数输入
    timerConfig.timer12.counterValue = 0;               // 将定时器的初始值设置为0
    timerConfig.interrupt1.serviceRequest = IfxCcu6_ServiceRequest_1;  // 设置中断定时器中断请求号
    timerConfig.base.t12Frequency = (float)clk;           // 配置定时器的频率为clk 这是在初始化时钟的定时器频率
    timerConfig.base.t12Period = period;          // 配置定时器周期为period 定时器会在period个时钟周期后产生溢出中断
    timerConfig.timer = IfxCcu6_TimerId_t12;           // 选择定时器为t12
    timerConfig.interrupt1.source = IfxCcu6_InterruptSource_t12PeriodMatch;  // 设置中断源为T12周期匹配中断 即当定时器T12溢出时产生中断
    timerConfig.interrupt1.priority = ISR_PRIORITY_CCU6_INT1;   // 设置中断的优先级
    timerConfig.interrupt1.typeOfService = IfxSrc_Tos_cpu0;   // 设置中断在CPU0上运行
    timerConfig.trigger.t13InSyncWithT12 = FALSE;        // 禁用定时器T13和T12同步

    IfxCcu6_Timer_initModule(&g_rx2_timer, &timerConfig);         // 初始化定时器
}



void ccu61_init(void)
{
    IfxCcu6_Timer_Config timerConfig;
    /**
     * 可以通过该注释了解计时器模块结构的默认配置 初始化计时器模块结构是为了在配置计时器模块之前
     * 确保所有的配置选项都有合理的默认值 这有助于简化配置流程 并且可以只更改需要自定义的配置选项
     */
    IfxCcu6_Timer_initModuleConfig(&timerConfig, &MODULE_CCU60); // 使用默认值初始化计时器模块结构
    uint8 i = 0;
    uint32 period = 0;
    uint64 clk = 0;
    clk = IfxScuCcu_getSpbFrequency();
    uint32 us = 50000;
    while (i++ < 16)
    {
        period = (uint32) (clk * us / 1000000);
        if (period < 0xffff)
        {
            break;
        }
        else
        {
            clk = clk / 2;
        }
    }

    timerConfig.clock.t13countingInputMode = IfxCcu6_CountingInputMode_internal;    // 定时器的计数输入模式为内部时钟作为计数输入
    timerConfig.timer13.counterValue = 0;               // 将定时器的初始值设置为0
    timerConfig.interrupt1.serviceRequest = IfxCcu6_ServiceRequest_2;  // 设置中断定时器中断请求号
    timerConfig.base.t13Frequency = (float)clk;           // 配置定时器的频率为clk 这是在初始化时钟的定时器频率
    timerConfig.base.t13Period = period;          // 配置定时器周期为period 定时器会在period个时钟周期后产生溢出中断
    timerConfig.timer = IfxCcu6_TimerId_t13;           // 选择定时器为t13
    timerConfig.interrupt1.source = IfxCcu6_InterruptSource_t13PeriodMatch;  // 设置中断源为T12周期匹配中断 即当定时器T12溢出时产生中断
    timerConfig.interrupt1.priority = ISR_PRIORITY_CCU61_INT1;   // 设置中断的优先级
    timerConfig.interrupt1.typeOfService = IfxSrc_Tos_cpu0;   // 设置中断在CPU0上运行
    timerConfig.trigger.t13InSyncWithT12 = FALSE;        // 禁用定时器T13和T12同步

    IfxCcu6_Timer_initModule(&g_rx3_timer, &timerConfig);         // 初始化定时器
}

void ccu62_init(void)
{
    IfxCcu6_Timer_Config timerConfig;
    /**
     * 可以通过该注释了解计时器模块结构的默认配置 初始化计时器模块结构是为了在配置计时器模块之前
     * 确保所有的配置选项都有合理的默认值 这有助于简化配置流程 并且可以只更改需要自定义的配置选项
     */
    IfxCcu6_Timer_initModuleConfig(&timerConfig, &MODULE_CCU61); // 使用默认值初始化计时器模块结构
    uint8 i = 0;
    uint32 period = 0;
    uint64 clk = 0;
    clk = IfxScuCcu_getSpbFrequency();
    uint32 us = 50000;
    while (i++ < 16)
    {
        period = (uint32) (clk * us / 1000000);
        if (period < 0xffff)
        {
            break;
        }
        else
        {
            clk = clk / 2;
        }
    }

    timerConfig.clock.t12countingInputMode = IfxCcu6_CountingInputMode_internal;    // 定时器的计数输入模式为内部时钟作为计数输入
    timerConfig.timer12.counterValue = 0;               // 将定时器的初始值设置为0
    timerConfig.interrupt1.serviceRequest = IfxCcu6_ServiceRequest_1;  // 设置中断定时器中断请求号
    timerConfig.base.t12Frequency = (float)clk;           // 配置定时器的频率为clk 这是在初始化时钟的定时器频率
    timerConfig.base.t12Period = period;          // 配置定时器周期为period 定时器会在period个时钟周期后产生溢出中断
    timerConfig.timer = IfxCcu6_TimerId_t12;           // 选择定时器为t12
    timerConfig.interrupt1.source = IfxCcu6_InterruptSource_t12PeriodMatch;  // 设置中断源为T12周期匹配中断 即当定时器T12溢出时产生中断
    timerConfig.interrupt1.priority = ISR_PRIORITY_CCU62_INT1;   // 设置中断的优先级
    timerConfig.interrupt1.typeOfService = IfxSrc_Tos_cpu0;   // 设置中断在CPU0上运行
    timerConfig.trigger.t13InSyncWithT12 = FALSE;        // 禁用定时器T13和T12同步

    IfxCcu6_Timer_initModule(&g_rx1_timer, &timerConfig);         // 初始化定时器
}

