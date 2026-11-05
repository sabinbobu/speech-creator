//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************

///----------------------------------------------------------------------------
/// \file   CddDcm_Cfg.h
///
/// \brief  Dcm Configuration
///         Create your own config in your project in /Cust/.../Cdd/Dcm/CddDcm_Cfg.h
///
/// \author Marco Paland (pm88rt)
///         mailto:marco.paland@external.al-lighting.com
///----------------------------------------------------------------------------
#ifndef CDD_DCM_CFG_2022_06_08_H_
#define CDD_DCM_CFG_2022_06_08_H_

#include <Std_Types.h>
//******************************************************************************
// G E N E R A L   O P T I O N S
//******************************************************************************

// defines the number of DCM channels (normally 1 or 2)
#define CDDDCM_CHANNELS             1U
#define HALDCM_NUMBER_OF_CHANNELS   1U

// Additional Debug Ctrl variables ard added to the Dcm driver.
#define HALDCM_DEBUG_OUTCTRL_WITH_RDM

//#define HALDCM_UDCM_AVERAGE_FILTER_VALUE     (4)
// Ubat Dcm Filter disabled, because lower level ADC modul is already
// filtering incomming the battery voltage.
#define HALDCM_UDCM_AVERAGE_FILTER_VALUE     (0)  // value 0 means filter disabled.


//******************************************************************************



// the cycle time of the Dcm task (calling CddDcm_Cycle) in [ms]
#define CDDDCM_CYCLETIME       20U

// the maximum output voltage in [mV] of the OP driver, when its PWM input has full 5V
#define CDDDCM_FULLRANGE    16000U      // full range of DCM output in [mV]

// PWM maximum duty cycle in [1/1000] (per mille)
#define CDDDCM_MAX_DUTY       975U

// PWM minimum duty cycle in [1/1000] 
#define CDDDCM_MIN_DUTY        25U

// maximum voltage change on output per cycle in [mV]
#define CDDDCM_ATTENUATION     50U      // max duty change per 20 ms 

// detection time in [ms] for a deviation error
// If it is not possible to adjust the output voltage within this time to the target level
// an error is detected
#define CDDDCM_ERROR_TIME    1000U



//******************************************************************************
// define this for debugging purpose
// #define CDDDCM_DEBUG

#endif /* CDD_DCM_CFG_2022_06_08_H_ */
