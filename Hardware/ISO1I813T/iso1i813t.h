#ifndef __ISO1I813T_H
#define __ISO1I813T_H

#include "IfxPort.h"

#define IN_SEL      &MODULE_P14, 10

#define IN0108_ERR  &MODULE_P13, 0
#define IN0916_ERR  &MODULE_P10, 8
#define IN1724_ERR  &MODULE_P13, 2
#define IN2532_ERR  &MODULE_P40, 4

#define IN0108_CS   &MODULE_P14, 9
#define IN0916_CS   &MODULE_P13, 1
#define IN1724_CS   &MODULE_P10, 7
#define IN2532_CS   &MODULE_P00, 12

#define IN_RD       &MODULE_P00, 8
#define IN_WR       &MODULE_P00, 10
#define IN_ALE      &MODULE_P00, 9

#define IN_AD0      &MODULE_P00, 0
#define IN_AD1      &MODULE_P00, 1
#define IN_AD2      &MODULE_P00, 2
#define IN_AD3      &MODULE_P00, 3
#define IN_AD4      &MODULE_P00, 4
#define IN_AD5      &MODULE_P00, 5
#define IN_AD6      &MODULE_P00, 6
#define IN_AD7      &MODULE_P00, 7

#define ISO_CS1_H           IfxPort_setPinState(IN0108_CS, IfxPort_State_high)
#define ISO_CS1_L           IfxPort_setPinState(IN0108_CS, IfxPort_State_low)
#define ISO_CS2_H           IfxPort_setPinState(IN0916_CS, IfxPort_State_high)
#define ISO_CS2_L           IfxPort_setPinState(IN0916_CS, IfxPort_State_low)
#define ISO_CS3_H           IfxPort_setPinState(IN1724_CS, IfxPort_State_high)
#define ISO_CS3_L           IfxPort_setPinState(IN1724_CS, IfxPort_State_low)
#define ISO_CS4_H           IfxPort_setPinState(IN2532_CS, IfxPort_State_high)
#define ISO_CS4_L           IfxPort_setPinState(IN2532_CS, IfxPort_State_low)

#define ISO_ALE_H           IfxPort_setPinState(IN_ALE, IfxPort_State_high)
#define ISO_ALE_L           IfxPort_setPinState(IN_ALE, IfxPort_State_low)

#define ISO_RD_H            IfxPort_setPinState(IN_RD, IfxPort_State_high)
#define ISO_RD_L            IfxPort_setPinState(IN_RD, IfxPort_State_low)

#define ISO_WR_H            IfxPort_setPinState(IN_WR, IfxPort_State_high)
#define ISO_WR_L            IfxPort_setPinState(IN_WR, IfxPort_State_low)

#define ISO_PARALLEL        IfxPort_setPinState(IN_SEL, IfxPort_State_low)
#define ISO_SERIAL          IfxPort_setPinState(IN_SEL, IfxPort_State_high)

#define ISO_ERR0108_READ    IfxPort_getPinState(IN0108_ERR)
#define ISO_ERR0916_READ    IfxPort_getPinState(IN0916_ERR)
#define ISO_ERR1724_READ    IfxPort_getPinState(IN1724_ERR)
#define ISO_ERR2532_READ    IfxPort_getPinState(IN2532_ERR)

#define ISO_CS1_EN(x)                                               \
{   if (x)  IfxPort_setPinState(IN0108_CS, IfxPort_State_high);     \
    else    IfxPort_setPinState(IN0108_CS, IfxPort_State_low );     \
    IfxPort_setPinState(IN0916_CS, IfxPort_State_high);             \
    IfxPort_setPinState(IN1724_CS, IfxPort_State_high);             \
    IfxPort_setPinState(IN2532_CS, IfxPort_State_high);             \
}

#define ISO_CS2_EN(x)                                               \
{   if (x)  IfxPort_setPinState(IN0916_CS, IfxPort_State_high);     \
    else    IfxPort_setPinState(IN0916_CS, IfxPort_State_low );     \
    IfxPort_setPinState(IN0108_CS, IfxPort_State_high);             \
    IfxPort_setPinState(IN1724_CS, IfxPort_State_high);             \
    IfxPort_setPinState(IN2532_CS, IfxPort_State_high);             \
}

#define ISO_CS3_EN(x)                                               \
{   if (x)  IfxPort_setPinState(IN1724_CS, IfxPort_State_high);     \
    else    IfxPort_setPinState(IN1724_CS, IfxPort_State_low );     \
    IfxPort_setPinState(IN0916_CS, IfxPort_State_high);             \
    IfxPort_setPinState(IN0108_CS, IfxPort_State_high);             \
    IfxPort_setPinState(IN2532_CS, IfxPort_State_high);             \
}

#define ISO_CS4_EN(x)                                               \
{   if (x)  IfxPort_setPinState(IN2532_CS, IfxPort_State_high);     \
    else    IfxPort_setPinState(IN2532_CS, IfxPort_State_low );     \
    IfxPort_setPinState(IN0916_CS, IfxPort_State_high);             \
    IfxPort_setPinState(IN1724_CS, IfxPort_State_high);             \
    IfxPort_setPinState(IN0108_CS, IfxPort_State_high);             \
}

void iso1i813t_init(void);
uint8 iso1i813t_01_data_read (uint8 addr, uint8 *data);
uint8 iso1i813t_02_data_read (uint8 addr, uint8 *data);
uint8 iso1i813t_03_data_read (uint8 addr, uint8 *data);
uint8 iso1i813t_04_data_read (uint8 addr, uint8 *data);


#endif
