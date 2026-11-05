/**
 * @file       $RCSfile: tllimits.h $
 * @brief      Implementation of platform-dependent limit definitions for Renesas RH850 / Green Hills Compiler 
 * @author     Sebastian Hillebrand
 * @copyright  (c) 2016, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.1 $ $Date: 2016/08/10 11:00:04CEST $
 */

#ifndef TLLIMITS_H
#define TLLIMITS_H


#define LITTLE_ENDIAN
#define ALIGN 4
#define MCU_RH850
#define COMP_GHS


#define INT8MAX                 127
#define INT8MIN                 (-INT8MAX -1)
#define INT16MAX                32767
#define INT16MIN                (-INT16MAX -1)
#define INT32MAX                2147483647L
#define INT32MIN                (-INT32MAX -1L)

#define UINT8MAX                255U
#define UINT8MIN                0U
#define UINT16MAX               65535U
#define UINT16MIN               0U
#define UINT32MAX               4294967295UL
#define UINT32MIN               0U

#define FLOAT32MAX				3.40282347E+38F
#define FLOAT32MIN				-3.40282347E+38F
#define FLOAT64MAX				1.7976931348623157E+308
#define FLOAT64MIN				-1.7976931348623157E+308


#endif
