/*
*****************************************************************************
* (C) Automotive Lighting Italy S.r.l.
*     Venaria Reale (TO), Italy
*****************************************************************************
* File: CddAsm330lhh_RoutCfg.h
* Description:
*   Routing configuration macros that connect CDD services to platform services
*   (SPI, SchM, delay and DET).
*****************************************************************************
*/

#ifndef CDD_ASM330LHH_ROUTCFG_2026_07_07_H_
#define CDD_ASM330LHH_ROUTCFG_2026_07_07_H_

#include <Std_Types.h>
#include <Os.h>
#include <Spi_Cfg.h>

#ifndef CDDASM330LHH_SPI_JOB_ID
  #define CDDASM330LHH_SPI_JOB_ID  SpiConf_SpiJob_SpiJob_ACC
#endif

#ifndef CDDASM330LHH_SPI_SEQUENCE_ID
  #define CDDASM330LHH_SPI_SEQUENCE_ID  SpiConf_SpiSequence_SpiSequence_ACC
#endif

#ifndef CDDASM330LHH_SPI_CHANNEL_ID
  #define CDDASM330LHH_SPI_CHANNEL_ID  SpiConf_SpiChannel_SpiChannel_1
#endif

#include <Spi.h>

/*
*****************************************************************************
* Exclusive area routing
* Integration may map these macros to SchM_Enter/SchM_Exit APIs.
*****************************************************************************
*/
#ifndef CDDASM330LHH_ENTER_CRITICAL
  #define CDDASM330LHH_ENTER_CRITICAL() SuspendAllInterrupts()
#endif

#ifndef CDDASM330LHH_EXIT_CRITICAL
  #define CDDASM330LHH_EXIT_CRITICAL() ResumeAllInterrupts()
#endif

/*
*****************************************************************************
* Delay routing
* Integration may map this macro to a platform delay function.
*****************************************************************************
*/
#ifndef CDDASM330LHH_DELAY_US
  #define CDDASM330LHH_DELAY_US(DelayUs) do { (void)(DelayUs); } while (FALSE)
#endif

/*
*****************************************************************************
* DET routing
* Integration may map this macro to Det_ReportError.
*****************************************************************************
*/
#ifndef CDDASM330LHH_DET_REPORT_ERROR
  #define CDDASM330LHH_DET_REPORT_ERROR(ModuleId, InstanceId, ApiId, ErrorId) \
    do                                                                          \
    {                                                                           \
      (void)(ModuleId);                                                         \
      (void)(InstanceId);                                                       \
      (void)(ApiId);                                                            \
      (void)(ErrorId);                                                          \
    } while (FALSE)
#endif

#endif /* CDD_ASM330LHH_ROUTCFG_2026_07_07_H_ */
