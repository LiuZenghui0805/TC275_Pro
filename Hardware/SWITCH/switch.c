#include "switch.h"


void switch_init(void) {
    IfxPort_setPinMode(SW1, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(SW2, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(SW3, IfxPort_Mode_inputPullUp);
    IfxPort_setPinMode(SW4, IfxPort_Mode_inputPullUp);
}

char switch_get_sw1_state(void) {
    return (char)IfxPort_getPinState(SW1);
}

char switch_get_sw2_state(void) {
    return (char)IfxPort_getPinState(SW2);
}

char switch_get_sw3_state(void) {
    return (char)IfxPort_getPinState(SW3);
}

char switch_get_sw4_state(void) {
    return (char)IfxPort_getPinState(SW4);
}

