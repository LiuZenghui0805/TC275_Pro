#ifndef __CCU6_H
#define __CCU6_H

#include <IfxCcu6.h>
#include <IfxCcu6_cfg.h>
#include <IfxCcu6_reg.h>
#include <IfxCcu6_regdef.h>
#include <IfxCcu6_Timer.h>
#include <IfxCpu.h>
#include <IfxCpu_Irq.h>
#include <IfxScuCcu.h>

#define ISR_PRIORITY_CCU6_INT1  40

#define ISR_PRIORITY_CCU61_INT1  50


extern uint16 g_rx2_finsh;
extern uint16 g_rx3_finsh;
extern IfxCcu6_Timer g_rx2_timer;
extern IfxCcu6_Timer g_rx3_timer;

void ccu6_init(void);
void ccu61_init(void);

#endif
