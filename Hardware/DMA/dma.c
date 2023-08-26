#include "dma.h"
#include "usart.h"

IfxDma_Dma_Channel g_chn_rx;
IfxDma_Dma_Channel g_chn_tx;

static int i = 0;

char send_buf[8] = {8, 7, 6, 5, 4, 3, 2, 1};

IFX_INTERRUPT(dma_rx_handler, 0, INTPRIO_DMA_RX);
void dma_rx_handler(void)
{
    // uart2_rx_message.rx_sign = 1;
    // IfxDma_setChannelDestinationAddress(&MODULE_DMA, (IfxDma_ChannelId)INTPRIO_ASCLIN2_RX, (void *) IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), &uart2_rx_message.rxbuf[0]));
}

IFX_INTERRUPT(dma_tx_handler, 0, INTPRIO_DMA_TX);
void dma_tx_handler(void)
{
    if(i >= 8) {
        i = 0;
    }
    // IfxDma_disableChannelTransaction(&MODULE_DMA, (IfxDma_ChannelId)INTPRIO_ASCLIN2_TX);
    IfxDma_setChannelSourceAddress(&MODULE_DMA, (IfxDma_ChannelId)INTPRIO_ASCLIN2_TX, (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), &send_buf[i]));
    i++;
}

void dma_rx_init(void) {
    IfxDma_Dma_Config dmaconfig;
    IfxDma_Dma_initModuleConfig(&dmaconfig, &MODULE_DMA);

    IfxDma_Dma dma;
    IfxDma_Dma_initModule(&dma, &dmaconfig);

    IfxDma_Dma_ChannelConfig cfg;
    IfxDma_Dma_initChannelConfig(&cfg, &dma);

    cfg.shadowAddress = 0;
    cfg.transferCount = 8;
    cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
    cfg.blockMode = IfxDma_ChannelMove_1;
    // cfg.requestMode = IfxDma_ChannelRequestMode_completeTransactionPerRequest;
    cfg.requestMode = IfxDma_ChannelRequestMode_oneTransferPerRequest;
    cfg.hardwareRequestEnabled = TRUE;
    cfg.operationMode = IfxDma_ChannelOperationMode_continuous;
    cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
    cfg.sourceCircularBufferEnabled = TRUE;
    // cfg.destinationAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
    // cfg.destinationCircularBufferEnabled = FALSE;
    cfg.channelId = (IfxDma_ChannelId)INTPRIO_ASCLIN2_RX;
    // cfg.sourceAddress = (uint32)&g_ascHandle.asclin->RXDATA.U;
    // cfg.destinationAddress = 0x90000000;
    // cfg.destinationAddress =  IFXCPU_GLB_ADDR_DSPR(IfxCpu_Id_0, uart2_rx_message.rxbuf);
    cfg.channelInterruptEnabled = TRUE;
    cfg.channelInterruptControl = IfxDma_ChannelInterruptControl_thresholdLimitMatch;
    cfg.channelInterruptPriority = INTPRIO_DMA_RX;
    cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;
    IfxDma_Dma_initChannel(&g_chn_rx, &cfg);
}

void dma_tx_init(void) {
    IfxDma_Dma_Config dmaconfig;
    IfxDma_Dma_initModuleConfig(&dmaconfig, &MODULE_DMA);

    IfxDma_Dma dma;
    IfxDma_Dma_initModule(&dma, &dmaconfig);

    IfxDma_Dma_ChannelConfig cfg;
    IfxDma_Dma_initChannelConfig(&cfg, &dma);

    cfg.shadowAddress = 0;
    cfg.transferCount = 1;
    cfg.moveSize = IfxDma_ChannelMoveSize_8bit;
    cfg.blockMode = IfxDma_ChannelMove_1;
    // cfg.requestMode = IfxDma_ChannelRequestMode_completeTransactionPerRequest;
    cfg.requestMode = IfxDma_ChannelRequestMode_oneTransferPerRequest;
    cfg.hardwareRequestEnabled = TRUE;
    cfg.operationMode = IfxDma_ChannelOperationMode_continuous;
    cfg.sourceAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
    cfg.sourceCircularBufferEnabled = TRUE;
    // cfg.destinationAddressCircularRange = IfxDma_ChannelIncrementCircular_none;
    // cfg.destinationCircularBufferEnabled = FALSE;
    cfg.channelId = (IfxDma_ChannelId)INTPRIO_ASCLIN2_TX;
    cfg.sourceAddress = IFXCPU_GLB_ADDR_DSPR(IfxCpu_Id_0, send_buf);
    // cfg.destinationAddress = 0x90000000;
    // cfg.destinationAddress = (uint32)&g_ascHandle.asclin->TXDATA.U;
    cfg.channelInterruptEnabled = TRUE;
    cfg.channelInterruptControl = IfxDma_ChannelInterruptControl_thresholdLimitMatch;
    cfg.channelInterruptPriority = INTPRIO_DMA_TX;
    cfg.channelInterruptTypeOfService = IfxSrc_Tos_cpu0;
    IfxDma_Dma_initChannel(&g_chn_tx, &cfg);
}
