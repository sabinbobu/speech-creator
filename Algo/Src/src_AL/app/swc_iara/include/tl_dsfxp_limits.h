/**************************************************************************************************\
 *** 
 *** Simulink model       : IMU_SDL_CodeGen_tl
 *** TargetLink subsystem : IMU_SDL_CodeGen_tl/IARA_TL
 *** Codefile             : tl_dsfxp_limits.h
 *** Language             : C
 ***
 *** Generation date: 2026-11-02 15:03:18
 ***
 *** TargetLink version      : 23.1p1 from 23-Jan-2024
 *** Code generator version  : Build Id 23.1.0.23 from 2023-10-18 12:33:41
\**************************************************************************************************/

#ifndef TL_DSFXP_LIMITS_H
#define TL_DSFXP_LIMITS_H

#include <float.h>

#define tl_dsfxp_LITTLE_ENDIAN
#define tl_dsfxp_FLOAT32MAX FLT_MAX /* Upper limit of tl_dsfxp_Float32 */
#define tl_dsfxp_FLOAT32NMIN (-FLT_MAX) /* Lower limit of tl_dsfxp_Float32 */
#define tl_dsfxp_FLOAT64MAX DBL_MAX /* Upper limit of tl_dsfxp_Float64 */
#define tl_dsfxp_FLOAT64NMIN (-DBL_MAX) /* Lower limit of tl_dsfxp_Float64 */
#define tl_dsfxp_INT16MAX 32767 /* Upper limit of tl_dsfxp_Int16 */
#define tl_dsfxp_INT16MIN (-tl_dsfxp_INT16MAX - 1) /* Lower limit of tl_dsfxp_Int16 */
#define tl_dsfxp_INT32MAX 2147483647L /* Upper limit of tl_dsfxp_Int32 */
#define tl_dsfxp_INT32MIN (-tl_dsfxp_INT32MAX - 1L) /* Lower limit of tl_dsfxp_Int32 */
#define tl_dsfxp_INT8MAX 127 /* Upper limit of tl_dsfxp_Int8 */
#define tl_dsfxp_INT8MIN (-tl_dsfxp_INT8MAX - 1) /* Lower limit of tl_dsfxp_Int8 */
#define tl_dsfxp_UINT16MAX 65535U /* Upper limit of tl_dsfxp_UInt16 */
#define tl_dsfxp_UINT16MIN 0U /* Lower limit of tl_dsfxp_UInt16 */
#define tl_dsfxp_UINT32MAX 4294967295UL /* Upper limit of tl_dsfxp_UInt32 */
#define tl_dsfxp_UINT32MIN 0UL /* Lower limit of tl_dsfxp_UInt32 */
#define tl_dsfxp_UINT8MAX 255U /* Upper limit of tl_dsfxp_UInt8 */
#define tl_dsfxp_UINT8MIN 0U /* Lower limit of tl_dsfxp_UInt8 */

#endif /* TL_DSFXP_LIMITS_H */
/*------------------------------------------------------------------------------------------------*\
  END OF FILE
\*------------------------------------------------------------------------------------------------*/
