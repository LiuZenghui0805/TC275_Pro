#ifndef __SWITCH_H
#define __SWITCH_H

#include "IfxPort.h"

#define SW1         &MODULE_P40, 2
#define SW2         &MODULE_P23, 2
#define SW3         &MODULE_P23, 1
#define SW4         &MODULE_P23, 0

void switch_init(void);
char switch_get_sw1_state(void);
char switch_get_sw2_state(void);
char switch_get_sw3_state(void);
char switch_get_sw4_state(void);



#endif

