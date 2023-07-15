#ifndef __STM_H
#define __STM_H


#include <Ifx_Types.h>
#include <IfxCpu.h>
#include <IfxCpu_IntrinsicsTasking.h>
#include <IfxCpu_Irq.h>
#include <IfxStm_cfg.h>
#include <IfxStm_reg.h>
#include <IfxStm_regdef.h>
#include <Bsp.h>

#define STM0_CH0_PRIORITY  21


void STM0_channel0_Init(uint32 us);
void STM_DelayUs(uint32 us);
void delayms(unsigned short stmms);


#endif

