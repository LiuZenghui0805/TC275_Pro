#include "iso1i813t.h"

static void iso_delay (uint32 cnt)
{
    while (cnt --);
}

static void iso1i813t_io_set_out_mode (void) {
    /* 设置AD0~7对应的数据位的模式 */
    IfxPort_setGroupModeOutput(IN_AD0, 0xff, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
}

static void iso1i813t_io_set_in_mode (void) {
    /* 设置AD0~7对应的数据位的模式 */
    IfxPort_setGroupModeInput(IN_AD0, 0xff, IfxPort_InputMode_noPullDevice);
}

static void iso1i813t_parallel_data_set (uint8 data) {
    /* 设置AD0~7对应的数据位 */
    IfxPort_setGroupState(IN_AD0, 0xff, data);
}

static uint8 iso1i813t_parallel_data_get (void)
{
    uint8 data = 0;

    /* 读取AD0~7对应的数据位 */
    if (IfxPort_getPinState(IN_AD0) == TRUE) {
        data |= 1<<0;
    }
    if (IfxPort_getPinState(IN_AD1) == TRUE) {
        data |= 1<<1;
    }
    if (IfxPort_getPinState(IN_AD2) == TRUE) {
        data |= 1<<2;
    }
    if (IfxPort_getPinState(IN_AD3) == TRUE) {
        data |= 1<<3;
    }
    if (IfxPort_getPinState(IN_AD4) == TRUE) {
        data |= 1<<4;
    }
    if (IfxPort_getPinState(IN_AD5) == TRUE) {
        data |= 1<<5;
    }
    if (IfxPort_getPinState(IN_AD6) == TRUE) {
        data |= 1<<6;
    }
    if (IfxPort_getPinState(IN_AD7) == TRUE) {
        data |= 1<<7;
    }

    return data;
}

uint8 iso1i813t_01_data_read (uint8 addr, uint8 *data)
{
    uint8 err;

    /* 0. 读错误 */
    err = ISO_ERR0108_READ;

    /* 1. 拉低片选 */
    ISO_CS1_EN(0);

    iso_delay(5);

    /* 2. ALE拉高 */
    ISO_ALE_H;

    /* 3. 设置为输出模式 */
    iso1i813t_io_set_out_mode();

    /* 4. 设置读数据地址 */
    iso1i813t_parallel_data_set(addr);

    /* 5. ALE拉低 */
    ISO_ALE_L;

    iso_delay(8);

    /* 6. RD拉低 */
    ISO_RD_L;

    /* 7. 设置为输入模式 */
    iso1i813t_io_set_in_mode();

    /* 8. 读数据 */
    *data = iso1i813t_parallel_data_get();

    /* 9. RD拉高 */
    ISO_RD_H;

    /* 10. 拉高片选 */
    ISO_CS1_EN(1);

    return err;
}

uint8 iso1i813t_02_data_read (uint8 addr, uint8 *data)
{
    uint8 err;

    /* 0. 读错误 */
    err = ISO_ERR0916_READ;

    /* 1. 拉低片选 */
    ISO_CS2_EN(0);

    iso_delay(5);

    /* 2. ALE拉高 */
    ISO_ALE_H;

    /* 3. 设置为输出模式 */
    iso1i813t_io_set_out_mode();

    /* 4. 设置读数据地址 */
    iso1i813t_parallel_data_set(addr);

    /* 5. ALE拉低 */
    ISO_ALE_L;

    iso_delay(8);

    /* 6. RD拉低 */
    ISO_RD_L;

    /* 7. 设置为输入模式 */
    iso1i813t_io_set_in_mode();

    /* 8. 读数据 */
    *data = iso1i813t_parallel_data_get();

    /* 9. RD拉高 */
    ISO_RD_H;

    /* 10. 拉高片选 */
    ISO_CS2_EN(1);

    return err;
}

uint8 iso1i813t_03_data_read (uint8 addr, uint8 *data)
{
    uint8 err;

    /* 0. 读错误 */
    err = ISO_ERR1724_READ;

    /* 1. 拉低片选 */
    ISO_CS3_EN(0);

    iso_delay(5);

    /* 2. ALE拉高 */
    ISO_ALE_H;

    /* 3. 设置为输出模式 */
    iso1i813t_io_set_out_mode();

    /* 4. 设置读数据地址 */
    iso1i813t_parallel_data_set(addr);

    /* 5. ALE拉低 */
    ISO_ALE_L;

    iso_delay(8);

    /* 6. RD拉低 */
    ISO_RD_L;

    /* 7. 设置为输入模式 */
    iso1i813t_io_set_in_mode();

    /* 8. 读数据 */
    *data = iso1i813t_parallel_data_get();

    /* 9. RD拉高 */
    ISO_RD_H;

    /* 10. 拉高片选 */
    ISO_CS3_EN(1);

    return err;
}

uint8 iso1i813t_04_data_read (uint8 addr, uint8 *data)
{
    uint8 err;

    /* 0. 读错误 */
    err = ISO_ERR2532_READ;

    /* 1. 拉低片选 */
    ISO_CS4_EN(0);

    iso_delay(5);

    /* 2. ALE拉高 */
    ISO_ALE_H;

    /* 3. 设置为输出模式 */
    iso1i813t_io_set_out_mode();

    /* 4. 设置读数据地址 */
    iso1i813t_parallel_data_set(addr);

    /* 5. ALE拉低 */
    ISO_ALE_L;

    iso_delay(8);

    /* 6. RD拉低 */
    ISO_RD_L;

    /* 7. 设置为输入模式 */
    iso1i813t_io_set_in_mode();

    /* 8. 读数据 */
    *data = iso1i813t_parallel_data_get();

    /* 9. RD拉高 */
    ISO_RD_H;

    /* 10. 拉高片选 */
    ISO_CS4_EN(1);

    return err;
}

void iso1i813t_init(void)
{
    /* 0. 初始化SEL->并口与串口选择引脚, 0: 并行传输  1: 串行传输 */
    IfxPort_setPinMode(IN_SEL,  IfxPort_Mode_outputPushPullGeneral);

    /* 1. ERR初始化 */
    IfxPort_setPinMode(IN0108_ERR,  IfxPort_Mode_inputNoPullDevice);
    IfxPort_setPinMode(IN0916_ERR,  IfxPort_Mode_inputNoPullDevice);
    IfxPort_setPinMode(IN1724_ERR,  IfxPort_Mode_inputNoPullDevice);
    IfxPort_setPinMode(IN2532_ERR,  IfxPort_Mode_inputNoPullDevice);

    /* 2. 初始化CS->每一片ISO1I813T使能端子 */
    IfxPort_setPinMode(IN0108_CS,  IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(IN0916_CS,  IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(IN1724_CS,  IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(IN2532_CS,  IfxPort_Mode_outputPushPullGeneral);

    /* 3. 初始化RD/WR->读写控制引脚 */
    IfxPort_setPinMode(IN_RD,  IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinMode(IN_WR,  IfxPort_Mode_outputPushPullGeneral);

    /* 4. 初始化ALE->写地址和写数据选择引脚 */
    IfxPort_setPinMode(IN_ALE,  IfxPort_Mode_outputPushPullGeneral);

    /* 5. 初始化AD0~7->并行数据引脚 */
    IfxPort_setGroupModeOutput(&MODULE_P00, 0, 0xff, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    IfxPort_setPinState(IN0108_CS, IfxPort_State_high);
    IfxPort_setPinState(IN0916_CS, IfxPort_State_high);
    IfxPort_setPinState(IN1724_CS, IfxPort_State_high);
    IfxPort_setPinState(IN2532_CS, IfxPort_State_high);

    IfxPort_setPinState(IN_RD,  IfxPort_State_low);
    IfxPort_setPinState(IN_WR,  IfxPort_State_high);
    IfxPort_setPinState(IN_ALE, IfxPort_State_low);
    IfxPort_setPinState(IN_SEL, IfxPort_State_low);        /* 拉低设置为并行模式 */
}




