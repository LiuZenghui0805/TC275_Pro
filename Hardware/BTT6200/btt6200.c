#include "btt6200.h"


void btt6200_init(void) {
    IfxPort_setPinMode(OUT01,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH1 */
    IfxPort_setPinMode(OUT02,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH2 */
    IfxPort_setPinMode(OUT03,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH3 */
    IfxPort_setPinMode(OUT04,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH4 */

    IfxPort_setPinMode(OUT05,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH5 */
    IfxPort_setPinMode(OUT06,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH6 */
    IfxPort_setPinMode(OUT07,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH7 */
    IfxPort_setPinMode(OUT08,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH8 */

    IfxPort_setPinMode(OUT09,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH9 */
    IfxPort_setPinMode(OUT10,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH10 */
    IfxPort_setPinMode(OUT11,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH11 */      /* todo: 固态预留 */
    IfxPort_setPinMode(OUT12,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH12 */

    IfxPort_setPinMode(OUT13,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH13 */      /* todo: 加热预留 */
    IfxPort_setPinMode(OUT14,  IfxPort_Mode_outputPushPullGeneral);      /* 输出IO CH14 */
    IfxPort_setPinMode(OUT15,  IfxPort_Mode_outputPushPullGeneral);      /* 输出IO CH15 */
    IfxPort_setPinMode(OUT16,  IfxPort_Mode_outputPushPullGeneral);      /* 输出IO CH16 */

    IfxPort_setPinMode(OUT17,  IfxPort_Mode_outputPushPullGeneral);      /* 输出IO CH17 */
    IfxPort_setPinMode(OUT18,  IfxPort_Mode_outputPushPullGeneral);      /* 输出IO CH18 */
    IfxPort_setPinMode(OUT19,  IfxPort_Mode_outputPushPullGeneral);      /* 输出IO CH19 */
    IfxPort_setPinMode(OUT20,  IfxPort_Mode_outputOpenDrainGeneral);     /* 输出IO CH20 */

    IfxPort_setPinMode(OUT21,  IfxPort_Mode_outputPushPullGeneral);    /* 输出IO CH21 */       /* todo: 电机脉冲 */
    IfxPort_setPinMode(OUT22,  IfxPort_Mode_outputPushPullGeneral);      /* 输出IO CH22 */
    IfxPort_setPinMode(OUT23,  IfxPort_Mode_outputPushPullGeneral);      /* 输出IO CH23 */
    IfxPort_setPinMode(OUT24,  IfxPort_Mode_outputPushPullGeneral);      /* 输出IO CH24 */
}
void btt6200_all_close(void) {
    IfxPort_setPinState(OUT01, IfxPort_State_low);          /* CH1  红灯 */
    IfxPort_setPinState(OUT02, IfxPort_State_high);
    IfxPort_setPinState(OUT03, IfxPort_State_high);
    IfxPort_setPinState(OUT04, IfxPort_State_high);

    IfxPort_setPinState(OUT05, IfxPort_State_high);
    IfxPort_setPinState(OUT06, IfxPort_State_high);
    IfxPort_setPinState(OUT07, IfxPort_State_high);
    IfxPort_setPinState(OUT08, IfxPort_State_high);

    IfxPort_setPinState(OUT09, IfxPort_State_high);
    IfxPort_setPinState(OUT10, IfxPort_State_high);
    IfxPort_setPinState(OUT11, IfxPort_State_high);
    IfxPort_setPinState(OUT12, IfxPort_State_high);

    IfxPort_setPinState(OUT13, IfxPort_State_high);
    IfxPort_setPinState(OUT14, IfxPort_State_low);          /* CH14  循环风道 */
    IfxPort_setPinState(OUT15, IfxPort_State_high);
    IfxPort_setPinState(OUT16, IfxPort_State_high);

    IfxPort_setPinState(OUT17, IfxPort_State_low);          /* CH17  蜂鸣器 */
    IfxPort_setPinState(OUT18, IfxPort_State_high);
    IfxPort_setPinState(OUT19, IfxPort_State_high);
    IfxPort_setPinState(OUT20, IfxPort_State_low);          /* CH20  门锁 */

    IfxPort_setPinState(OUT21, IfxPort_State_high);
    IfxPort_setPinState(OUT22, IfxPort_State_high);
    IfxPort_setPinState(OUT23, IfxPort_State_high);
    IfxPort_setPinState(OUT24, IfxPort_State_high);
}
void btt6200_all_open(void) {
    IfxPort_setPinState(OUT01, IfxPort_State_high);         /* CH1  红灯 */
    IfxPort_setPinState(OUT02, IfxPort_State_low);
    IfxPort_setPinState(OUT03, IfxPort_State_low);
    IfxPort_setPinState(OUT04, IfxPort_State_low);

    IfxPort_setPinState(OUT05, IfxPort_State_low);
    IfxPort_setPinState(OUT06, IfxPort_State_low);
    IfxPort_setPinState(OUT07, IfxPort_State_low);
    IfxPort_setPinState(OUT08, IfxPort_State_low);

    IfxPort_setPinState(OUT09, IfxPort_State_low);
    IfxPort_setPinState(OUT10, IfxPort_State_low);
    IfxPort_setPinState(OUT11, IfxPort_State_low);
    IfxPort_setPinState(OUT12, IfxPort_State_low);

    IfxPort_setPinState(OUT13, IfxPort_State_low);
    IfxPort_setPinState(OUT14, IfxPort_State_high);         /* CH14  循环风道 */
    IfxPort_setPinState(OUT15, IfxPort_State_low);
    IfxPort_setPinState(OUT16, IfxPort_State_low);

    IfxPort_setPinState(OUT17, IfxPort_State_high);         /* CH17  蜂鸣器 */
    IfxPort_setPinState(OUT18, IfxPort_State_low);
    IfxPort_setPinState(OUT19, IfxPort_State_low);
    IfxPort_setPinState(OUT20, IfxPort_State_high);         /* CH20  门锁 */

    IfxPort_setPinState(OUT21, IfxPort_State_low);
    IfxPort_setPinState(OUT22, IfxPort_State_low);
    IfxPort_setPinState(OUT23, IfxPort_State_low);
    IfxPort_setPinState(OUT24, IfxPort_State_low);
}

