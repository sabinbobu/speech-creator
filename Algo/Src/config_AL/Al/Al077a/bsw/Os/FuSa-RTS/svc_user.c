/*
 * Copyright (c) 2013-2018 Arm Limited. All rights reserved.
 *
 * This Software is licensed under an Arm proprietary license.
 *
 * -----------------------------------------------------------------------------
 *
 * Project:     CMSIS-RTOS RTX
 * Title:       SVC User Table
 *              Original file: Src\Src_ThirdParty\OS\FuSa-RTS\FuSaRTS_V1.10\CortexM0+_Package\FSRTS-SW-00000-r1p1-00rel0\CMSIS\RTOS2\RTX\Template\svc_user.c
 *              Modified according to: Src/Src_ThirdParty/OS/FuSa-RTS/FuSaRTS_V1.10/CortexM0+_Package/FSRTS-SW-00000-r1p1-00rel0/CMSIS/Documentation/RTOS2/html/theory_of_operation.html
 *
 * -----------------------------------------------------------------------------
 */
#include "RTE_Components.h"
#include CMSIS_device_header

#define USER_SVC_COUNT  2       // Number of user SVC functions

void EnablePrivelegedMode(void);
void DisablePrivelegedMode(void);

extern void * const osRtxUserSVC[1+USER_SVC_COUNT];
       void * const osRtxUserSVC[1+USER_SVC_COUNT] = {
       (void *)USER_SVC_COUNT,
       (void *)EnablePrivelegedMode,
       (void *)DisablePrivelegedMode
// ...
};

void EnablePrivelegedMode(void){
  __set_CONTROL( __get_CONTROL( ) & ~CONTROL_nPRIV_Msk ) ;
}

void DisablePrivelegedMode(void){
  __set_CONTROL( __get_CONTROL( ) | CONTROL_nPRIV_Msk ) ;
}
