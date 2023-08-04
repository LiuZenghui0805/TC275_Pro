#include "ccu6.h"

uint16 g_count = 0;
uint16 g_rx_finsh = 0;
IfxCcu6_Timer g_timer;

IFX_INTERRUPT(isrCCU6Timer, 0, ISR_PRIORITY_CCU6_INT1);
void isrCCU6Timer(void)
{
    g_rx_finsh = 1; /* Increase value of the counter each time the ISR is called */
    IfxCcu6_clearInterruptStatusFlag(&MODULE_CCU60, IfxCcu6_InterruptSource_t12PeriodMatch);
    IfxCcu6_Timer_stop(&g_timer);
    IfxCcu6_setT12CounterValue(&MODULE_CCU60, 0);
    g_count++;
}

void ccu6_init(void)
{
    IfxCcu6_Timer_Config timerConfig;                   /* Structure for timer configuration                        */
    IfxCcu6_Timer_initModuleConfig(&timerConfig, &MODULE_CCU60); /* Initialize the timer module structure with default values*/
    uint8 i = 0;
    uint32 period = 0;
    uint64 clk = 0;
    clk = IfxScuCcu_getSpbFrequency();
    uint16 us = 5000;
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

    timerConfig.clock.t12countingInputMode = IfxCcu6_CountingInputMode_internal;
    timerConfig.timer12.counterValue = 0;
    timerConfig.interrupt1.serviceRequest = IfxCcu6_ServiceRequest_1;
    timerConfig.base.t12Frequency = (float)clk;                /* Configure the frequency of the timer module */
    timerConfig.base.t12Period = period;                 /* Configure the period of the timer (16-bit)  */
    timerConfig.timer = IfxCcu6_TimerId_t12;                        /* Select the timer to be started              */
    timerConfig.interrupt1.source = IfxCcu6_InterruptSource_t12PeriodMatch; /* Set interrupt source                */
    timerConfig.interrupt1.priority = ISR_PRIORITY_CCU6_INT1;       /* Set the priority of the ISR                 */
    timerConfig.interrupt1.typeOfService = IfxSrc_Tos_cpu0;         /* Set the type of service for the interrupt   */
    timerConfig.trigger.t13InSyncWithT12 = FALSE;                   /* Configure timers synchronization            */

    IfxCcu6_Timer_initModule(&g_timer, &timerConfig);               /* Initialize the CCU6 module                  */


}

