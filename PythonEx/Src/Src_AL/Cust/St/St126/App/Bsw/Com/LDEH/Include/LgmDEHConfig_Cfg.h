/******************************************************************************
 *  The software belongs to the LGM INGENIERIE company, member of LGM Group.  *
 *  The software cannot be used or modified without the authorization of      *
 *  LGM INGENIERIE.                                                           *
 *  The software cannot be share with other parts without the LGM INGENIERIE  *
 *  agreement.                                                                *
 *                                                                            *
 ******************************************************************************
 * Software name: LgmStack                                                    *
 * File name: LgmDEHConfig_Cfg.h                                              *
 *                                                                            *
 ******************************************************************************/
#ifndef LGM_DEH_CONFIG_CFG_H
#define LGM_DEH_CONFIG_CFG_H
/*============================================================================*/
/*                                  Includes                                  */
/*============================================================================*/
/* #start of automatic include section                                        */
/* #end of automatic include section                                          */

/* #start of manual include section                                           */
#include "LgmDEHMainAPI.h"
/* #end of manual include section                                             */

/* PRQA S 0841 EOF #Justification: This is a configuration file that defined configuration macro, so #undef usage is allowed */

/*============================================================================*/
/*                               Public macros                                */
/*============================================================================*/
/* #start of automatic public macros section                                  */
/* #end of automatic public macros section                                    */

/* #start of manual public macro section                                      */

/****** Set user function call ******/
/* Use to send 8 byte frames */
#define LDEH_DF_SEND_FRAMES         APPLI_Send_Defaut

/* Use to store DE in NVM if needed */
#define LDEH_DF_STR_NVM             APPLI_StoreInNVM

/* Use to update DE date in NVM */
#define LDEH_DF_DATE_UPDATE_NVM     APPLI_DateUpdateNVM

/* Use to remove a DE from the NVM that has been sent */
#define LDEH_DF_DE_ACK              APPLI_DEAck

/* Use to remove a DE from the NVM that has not been sent
 * because of an acknowledgment error */
#define LDEH_DF_DE_NOT_ACK          APPLI_DENotAck

/* Use to remove DE from NVM that are no longer up to date */
#undef LDEH_DF_REMOVE_DTC_NVM

/* Use to remove all DE from NVM */
#define LDEH_DF_CLEAR_ALL_DTC       APPLI_RemoveAllDTC

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
/* User function prototype */
/* Send frames prototype function */
extern LDEH_TE_ErrVal APPLI_Send_Defaut( const Tu8P_Int PIu8P_ByteToSend );

/* NVM DE storage prototype function */
extern void APPLI_StoreInNVM( LDEH_TS_DECtxt const * const PISP_DE );

/* Update NVM DE date prototype function */
extern void APPLI_DateUpdateNVM( LDEH_TS_DECtxt const * const PISP_DE );

/* DE send acknowledgment prototype function */
extern void APPLI_DEAck( LDEH_TS_DECtxt const * const PISP_DE );

/* DE send non-acknowledgment prototype function */
extern void APPLI_DENotAck( LDEH_TS_DECtxt const * const PISP_DE );

/* Remove all DEs prototype function */
extern void APPLI_RemoveAllDTC( void );
/* #end of automatic public function section                                  */

#endif /* LGM_DEH_CONFIG_CFG_H */
/*============================================================================*/
/*                                End of file                                 */
/*============================================================================*/
