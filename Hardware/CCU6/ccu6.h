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
#define CCU6_TIMER_FREQ         IfxScuCcu_getSpbFrequency()                                       /* Timer module frequency in Hz         */
#define CCU6_ISR_FREQ           1                                          /* ISR frequency in Hz                  */
#define CCU6_TIMER_PERIOD       (CCU6_TIMER_FREQ / CCU6_ISR_FREQ) - 1       /* Timer module period in ticks         */

extern uint16 g_count;
extern uint16 g_rx_finsh;
extern IfxCcu6_Timer g_timer;

void ccu6_init(void);


#endif
