#include "stm.h"

IfxStm_CompareConfig g_stmCompareConfig;

IFX_INTERRUPT(STM0_CH0_IRQHandler, 0, STM0_CH0_PRIORITY);
void STM0_CH0_IRQHandler() {
    IfxCpu_enableInterrupts();
    IfxStm_clearCompareFlag(&MODULE_STM0, g_stmCompareConfig.comparator);
    IfxStm_increaseCompare(&MODULE_STM0, g_stmCompareConfig.comparator, g_stmCompareConfig.ticks);
}


void STM0_channel0_Init(uint32 us) {
    char interruptState = disableInterrupts();

    Ifx_STM *STM = &MODULE_STM0;

    IfxStm_CompareConfig stmCompareConfig = g_stmCompareConfig;

    IfxStm_initCompareConfig(&stmCompareConfig);

    //挂起
    IfxStm_enableOcdsSuspend(STM);

    //获取STM模块的微秒计时 tick 数值
    sint32 ticks = IfxStm_getTicksFromMicroseconds(STM, us);

    stmCompareConfig.ticks = ticks;
    stmCompareConfig.comparator = IfxStm_Comparator_0;
    stmCompareConfig.comparatorInterrupt = IfxStm_ComparatorInterrupt_ir0;
    stmCompareConfig.triggerPriority = STM0_CH0_PRIORITY;
    stmCompareConfig.typeOfService = IfxSrc_Tos_cpu0;

    IfxStm_initCompare(STM, &stmCompareConfig);
    IfxCpu_Irq_installInterruptHandler((void*)STM0_CH0_IRQHandler, STM0_CH0_PRIORITY);

    restoreInterrupts(interruptState);
}


void STM_DelayUs(uint32 us) {
    Ifx_STM * STM = &MODULE_STM0;
    uint32 tick = IfxStm_getTicksFromMicroseconds(STM, us);
    IfxStm_waitTicks(STM, tick);
}

void delayms(unsigned short stmms) {
    while(stmms--) {
         STM_DelayUs(1000);
    }
}


