#ifndef __CTAA_CTRL_FAN_H__
#define __CTAA_CTRL_FAN_H__

//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************

//-----------------------------------------------------------------------------
/// \file  ctaaCtrlSwi.c
///
/// \brief
///
/// \descr  These files is the interface with the RTE. CtrlFan must receive information
///         from the other modules like SysVolt, Thermo Management and CddHss.
///         Also it contains module API functions which are called by the RTE/OS in
///         order to integrate the module into the arhitecture and for the module's
///         functionality to be used by other SWCs.
///
/// \author Cretu Vladut-Ioan (F78845C)
///         mailTo:vladut-ioan.cretu[at]marelli.com
//-----------------------------------------------------------------------------

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

/******************************************************************************/
/* Prototypes                                                                 */
/******************************************************************************/

void riCtrlSwiInit(void);
void rpCtrlSwiCycle0(void);
//void roCtrlFan_ParaFct0(const tParaFct0_Cmd eCmd, const tNvmPara_CodingArea* const pData) TBD

#endif // __CTAA_CTRL_FAN_H__
//EOF
