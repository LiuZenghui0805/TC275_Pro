#include "led.h"

void led_init(void) {
    IfxPort_setPinMode(LED,  IfxPort_Mode_outputPushPullGeneral);
}
void led_on(void) {
    IfxPort_setPinState(LED, IfxPort_State_high);
}
void led_off(void) {
    IfxPort_setPinState(LED, IfxPort_State_low);
}
void led_toggled(void) {
    IfxPort_setPinState(LED, IfxPort_State_toggled);
}
