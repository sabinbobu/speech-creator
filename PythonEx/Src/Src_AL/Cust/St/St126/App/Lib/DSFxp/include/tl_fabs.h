/**
 * @file       $RCSfile: tl_fabs.h $
 * @brief      This file contains the TargetLink implementation of fabs from standard C
 *   		   header math.h for support ISO-C "conforming freestanding implementation".
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2017, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.4 $ $Date: 2017/02/22 15:10:32CET $
 */


#ifndef TL_FABS_H
#define TL_FABS_H

/* fabs */
#define fabs(x)\
    ( ((x) < 0.0) ? -(x) : (x) )

#endif /* #ifndef TL_FABS_H */
