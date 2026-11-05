/**
 * @file       $RCSfile: NEG64s01.c $
 * @brief      This file contains function to negate 64 bit values.
 * @author     Klaus Goebel, Dagmar Andoleit
 * @copyright  (c) 2014, dSPACE GmbH, Paderborn, Germany
 * @version    $Revision: 1.5 $ $Date: 2014/12/18 08:25:11CET $
 */

#include "dsfxp.h"


void negate(UInt64s *x)
{
	x->lo = (UInt32)(-((Int32)x->lo));	/* complement */
	x->hi = ~x->hi;
	if(x->lo == 0U) {++x->hi;}
}
