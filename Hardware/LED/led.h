#ifndef __LED_H
#define __LED_H

#include "IfxPort.h"

#define LED &MODULE_P33, 0

void led_init(void);
void led_on(void);
void led_off(void);
void led_toggled(void);

#endif

