/**************************************************************************************************\
 *** 
 *** Simulink model       : Adb_Mxb3_TL
 *** TargetLink subsystem : Adb_Mxb3_TL/ADBModel
 *** Codefile             : tl_dsfxp_limits.h
 *** Language             : C
 ***
 *** Generation date: 2025-06-30 23:08:39
 ***
 *** TargetLink version      : 23.1p2 from 23-May-2024
 *** Code generator version  : Build Id 23.1.0.24 from 2024-05-16 17:28:10
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
