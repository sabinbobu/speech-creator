/**************************************************************************************************\
 *** 
 *** Simulink model       : IMU_SDL_CodeGen_tl
 *** TargetLink subsystem : IMU_SDL_CodeGen_tl/IARA_TL
 *** Codefile             : tl_defines_IARA.h
 *** Language             : C
 ***
 *** Generation date: 2026-11-02 15:03:09
 ***
 *** TargetLink version      : 23.1p1 from 23-Jan-2024
 *** Code generator version  : Build Id 23.1.0.23 from 2023-10-18 12:33:41
\**************************************************************************************************/

#ifndef TL_DEFINES_IARA_H
#define TL_DEFINES_IARA_H

#ifdef TL_FRAME
#include "IARA_TL_frm.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************************\
   TL_CG_MACROCL_GLOBAL: Default macro class for macros with module extent
\**************************************************************************************************/
#define IARA_CodingDataAddressVariableClass 
#define IARA_CodingDataVariableClass 
#define IARA_NvmDataAddressVariableClass 
#define IARA_NvmDataVariableClass 

#ifndef TL_FRAME

#ifndef LOG_VAR
#define LOG_VAR(param_0, param_1, param_2)
#endif /* LOG_VAR */

#endif /* TL_FRAME */

#ifdef __cplusplus
}
#endif

#endif /* TL_DEFINES_IARA_H */
/*------------------------------------------------------------------------------------------------*\
  END OF FILE
\*------------------------------------------------------------------------------------------------*/
