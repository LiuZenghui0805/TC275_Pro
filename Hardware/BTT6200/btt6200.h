#ifndef __BTT6200_H
#define __BTT6200_H

#include "IfxPort.h"

#define OUT_EN      &MODULE_P20, 7
#define OUT_DS0     &MODULE_P14, 1
#define OUT_DS1     &MODULE_P20, 0

#define OUT01       &MODULE_P14, 8
#define OUT02       &MODULE_P20, 1
#define OUT03       &MODULE_P14, 0
#define OUT04       &MODULE_P20, 11

#define OUT05       &MODULE_P15, 8
#define OUT06       &MODULE_P21, 2
#define OUT07       &MODULE_P15, 7
#define OUT08       &MODULE_P21, 3

#define OUT09       &MODULE_P15, 2
#define OUT10       &MODULE_P21, 4
#define OUT11       &MODULE_P15, 6
#define OUT12       &MODULE_P21, 5

#define OUT13       &MODULE_P32, 4
#define OUT14       &MODULE_P33, 6
#define OUT15       &MODULE_P33, 13
#define OUT16       &MODULE_P33, 5

#define OUT17       &MODULE_P33, 12
#define OUT18       &MODULE_P33, 4
#define OUT19       &MODULE_P33, 11
#define OUT20       &MODULE_P33, 3

#define OUT21       &MODULE_P33, 10
#define OUT22       &MODULE_P33, 2
#define OUT23       &MODULE_P33, 1
#define OUT24       &MODULE_P33, 9


void btt6200_init(void);
void btt6200_all_close(void);
void btt6200_all_open(void);

#endif
