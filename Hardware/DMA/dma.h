#ifndef __DMA_H
#define __DMA_H

#include "Ifx_Types.h"
#include "IfxDma_Dma.h"

#define INTPRIO_DMA_RX       30
#define INTPRIO_DMA_TX       31

extern IfxDma_Dma_Channel    g_chn_rx;
extern IfxDma_Dma_Channel    g_chn_tx;


void dma_rx_init(void);
void dma_tx_init(void);


#endif
