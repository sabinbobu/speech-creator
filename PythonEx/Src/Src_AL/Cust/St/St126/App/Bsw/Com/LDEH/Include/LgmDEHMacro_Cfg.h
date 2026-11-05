/******************************************************************************
 *  The software belongs to the LGM INGENIERIE company, member of LGM Group.  *
 *  The software cannot be used or modified without the authorization of      *
 *  LGM INGENIERIE.                                                           *
 *  The software cannot be share with other parts without the LGM INGENIERIE  *
 *  agreement.                                                                *
 *                                                                            *
 ******************************************************************************
 * Software name: LgmStack                                                    *
 * File name: LgmDEHMacro_Cfg.h                                              *
 *                                                                            *
 ******************************************************************************/
#ifndef LGM_DEH_MACRO_CFG_H
#define LGM_DEH_MACRO_CFG_H
/*============================================================================*/
/*                                  Includes                                  */
/*============================================================================*/
/* #start of automatic include section                                        */
/* #end of automatic include section                                          */

/* #start of manual include section                                           */
#include "CommonTypes.h"
/* #end of manual include section                                             */

/* PRQA S 0841 EOF #Justification: This is a configuration file that defined configuration macro, so #undef usage is allowed */

/*============================================================================*/
/*                               Public macros                                */
/*============================================================================*/
/* #start of automatic public macros section                                  */
/* #end of automatic public macros section                                    */

/* #start of manual public macro section                                      */

/****** Set DTC number ******/
#define LDEH_D_DTC_NB   DF_TO_UINT16(40)

/****** Set ECU code ******/
#define LDEH_D_ECU_CODE DF_TO_UINT8(0xA7)

/****** Set Main Schedule call timer period ******/
#define LDEH_D_SCHEDULE_PERIOD  DF_TO_UINT32(5)

/****** Set third frame option ******/
#undef LDEH_D_THIRD_FRAME
/* #end of manual public macro section                                        */

/*============================================================================*/
/*                                Public types                                */
/*============================================================================*/
/* #start of automatic public type section                                    */
/* #end of automatic public type section                                      */

/* #start of manual public type section                                       */
/* #end of manual public type section                                         */

/*============================================================================*/
/*                              Public constants                              */
/*============================================================================*/
/* #start of automatic public constant section                                */
/* #end of automatic public constant section                                  */

/* #start of manual public constant section                                   */
/* #end of manual public constant section                                     */

/*============================================================================*/
/*                              Public variables                              */
/*============================================================================*/
/* #start of automatic public variable section                                */
/* #end of automatic public variable section                                  */

/* #start of manual public variable section                                   */
/* #end of manual public variable section                                     */

/*============================================================================*/
/*                              Public functions                              */
/*============================================================================*/
/* #start of automatic public function section                                */
/* #end of automatic public function section                                  */

#endif /* LGM_DEH_MACRO_CFG_H */
/*============================================================================*/
/*                                End of file                                 */
/*============================================================================*/
