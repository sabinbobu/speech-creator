/**************************************************************************************************\
 *** 
 *** Simulink model       : CPM_TL
 *** TargetLink subsystem : CPM_TL/CPM_Gen
 *** Codefile             : tl_dsfxp_limits.h
 ***
 *** Generation date: 2023-01-10 07:30:59
 ***
 *** TargetLink version      : 5.1 from 28-Oct-2020
 *** Code generator version  : Build Id 5.1.0.29 from 2020-10-08 19:52:58
\**************************************************************************************************/

#ifndef TL_DSFXP_LIMITS_H
#define TL_DSFXP_LIMITS_H

#include <float.h>

#define LITTLE_ENDIAN
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
