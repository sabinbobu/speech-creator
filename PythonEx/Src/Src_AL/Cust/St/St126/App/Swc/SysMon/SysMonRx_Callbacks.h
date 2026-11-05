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
/// \file   SysMonRx_Callbacks.h
///
/// \brief  
///
/// \descr  Input Rx Frame Callbacks Header file
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef __SYS_MON_RX_CALLBACKS_H__
#define __SYS_MON_RX_CALLBACKS_H__

//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include <SysMon_Types.h>

//-----------------------------------------------------------------------------
//  defines
//-----------------------------------------------------------------------------
#define SYSMON_RX_ZERO_VALUE                                 0u
#define SYSMON_RX_TI_ON_VALUE                              0x1u
#define SYSMON_RX_INVALID_VITESSE_VEHICULE_ROUES          (uint16)0xFFFF       //  VITESSE_VEHICULE_ROUES  invalid value
#define SYSMON_RX_5KMH_THRESHOLD                          (uint16)500u         //  VITESSE_VEHICULE_ROUES 5 km/h value

#define SYSMONRX_CALLBACKS_INVALID_CHKSUM_NBFRAMES_PASSED    50U
#define SYSMONRX_CALLBACKS_INVALID_PROCCNT_NBFRAMES_PASSED   50U
#define SYSMONRX_CALLBACKS_INVALID_SPEED_NBFRAMES_PASSED     50U

// Defines used for Etat Clignotants
#define SYSMON_RX_ETAT_CLIGNO_RIGHT_IND_ACTIVE              1u    // Right Turn Indicator Active
#define SYSMON_RX_ETAT_CLIGNO_LEFT_IND_ACTIVE               2u    // Left Turn Indiator Active
#define SYSMON_RX_ETAT_CLIGNO_LEFT_AND_RIGHT_IND_ACTIVE     3u    // Left And Right Turn Indicator Active

// Defines used for Parking Light State
#define SYSMON_RX_ETAT_FEUX_STAT_DEACTIVATED                0u    // Deactivated
#define SYSMON_RX_ETAT_FEUX_STAT_LEFT_SIDE                  1u    // Left Side
#define SYSMON_RX_ETAT_FEUX_STAT_RIGHT_SIDE                 2u    // Right Side

// Defines used for Vehicle Configuration
#define SYSMON_RX_VEHICLE_CONFIG_FITTING                    0u    // Fitting
#define SYSMON_RX_VEHICLE_CONFIG_PLANT                      1u    // Plant
#define SYSMON_RX_VEHICLE_CONFIG_CHECK                      2u    // Check
#define SYSMON_RX_VEHICLE_CONFIG_STORAGE                    3u    // Storage
#define SYSMON_RX_VEHICLE_CONFIG_CLIENT                     4u    // Client
#define SYSMON_RX_VEHICLE_CONFIG_SHOWROOM                   5u    // Showroom
#define SYSMON_RX_VEHICLE_CONFIG_APV                        6u    // APV

// Defines used for Eletrical Network State
#define SYSMON_RX_ETAT_RESEAU_ELEC_TI_NOMINAL               0u    // TI_NOMINAL
#define SYSMON_RX_ETAT_RESEAU_ELEC_TI_DEGRADE               1u    // TI_DEGRADE
#define SYSMON_RX_ETAT_RESEAU_ELEC_TI_DISPO_DEM             2u    // TI_DISPO_DEM
#define SYSMON_RX_ETAT_RESEAU_ELEC_DEMARRAGE                3u    // DEMARRAGE
#define SYSMON_RX_ETAT_RESEAU_ELEC_REDEMARRAGE              4u    // REDEMARRAGE
#define SYSMON_RX_ETAT_RESEAU_ELEC_TA_NOMINAL               5u    // TA_NOMINAL
#define SYSMON_RX_ETAT_RESEAU_ELEC_TA_DEGRADE               6u    // DEGRADE
#define SYSMON_RX_ETAT_RESEAU_ELEC_TA_SECU                  7u    // TA_SECU

// Defines used for Life Phases
#define SYSMON_RX_PHASE_VIE_STANDBY                         0u    // Standby
#define SYSMON_RX_PHASE_VIE_NORMAL_MODE                     1u    // Normal Mode
#define SYSMON_RX_PHASE_VIE_SWITCH_TO_STANDBY               2u    // Switch To Standby
#define SYSMON_RX_PHASE_VIE_WAKE_UP                         3u    // Wake Uo
#define SYSMON_RX_PHASE_VIE_COM_OFF                         4u    // Com Off

// Defines used for ETAT Princip SEV
#define SYSMON_RX_ETAT_PRINCIP_SEV_STOP                     0u    // Stop
#define SYSMON_RX_ETAT_PRINCIP_SEV_IGNITION                 1u    // Contact/Ignition
#define SYSMON_RX_ETAT_PRINCIP_SEV_START                    2u    // Start

// Defines used for Vehicle Speed Unavailability
#define SYSMON_RX_VVH_INDISP_AVAILABLE                      1u    // Vehicle Speed Available
#define SYSMON_RX_VVH_INDISP_UNAVAILABLE                    2u    // Vehicle Speed Unavailable

// Defines used for Turn Indicator Value
#define SYSMON_RX_TURN_INDICATOR_ON                         1u    // TI On
#define SYSMON_RX_TURN_INDICATOR_OFF                        2u    // TI Off

// Defines used for Advanced Frontlight System
#define SYSMON_RX_CTRL_AFS_AFS_OFF                          0u    // Afs Off
#define SYSMON_RX_CTRL_AFS_COUNTRY                          1u    // Country
#define SYSMON_RX_CTRL_AFS_MOTORWAY                         2u    // Motorway
#define SYSMON_RX_CTRL_AFS_TOWN                             3u    // Town
#define SYSMON_RX_CTRL_AFS_BAD_WEATHER_LHD                  4u    // Bad Weather Left Hand Driving
#define SYSMON_RX_CTRL_AFS_BAD_WEATHER_RHD                  5u    // Bad Weather Right Hand Driving
#define SYSMON_RX_CTRL_AFS_FOGGY_LHD                        6u    // Foggy Left Hand Driving
#define SYSMON_RX_CTRL_AFS_FOGGY_RHD                        7u    // Foggy Right Hand Driving

// Defines used for Glare Free High Beam
#define SYSMON_RX_GFHB_CURTAIN_ACTIVATION                   1u    // Curtain Activation
#define SYSMON_RX_GFHB_ON                                   2u    // On
#define SYSMON_RX_GFHB_CURTAIN_DEACTIVATION                 3u    // Curtain Deactivation

// Defines used for Checksum and Process Counter calculation of frame 0x38D
#define SYSMONRX_CALLBACKS_NIBBLELGTH          4u 
#define SYSMONRX_CALLBACKS_CHKINI_38D          0x08u
#define SYSMONRX_CALLBACKS_CHKOK               0x0Fu
#define SYSMONRX_CALLBACKS_LOWNIBBLE           0x0Fu
#define SYSMONRX_CALLBACKS_LENGTH_38D          8u
#define SYSMONRX_CALLBACKS_38D_RAW_FIRST       0u
#define SYSMONRX_CALLBACKS_38D_RAW_SECOND      1u
#define SYSMONRX_CALLBACKS_38D_RAW_THIRD       2u
#define SYSMONRX_CALLBACKS_38D_RAW_FOURTH      3u
#define SYSMONRX_CALLBACKS_38D_RAW_FIFTH       4u
#define SYSMONRX_CALLBACKS_38D_RAW_SIXTH       5u
#define SYSMONRX_CALLBACKS_38D_RAW_SEVENTH     6u
#define SYSMONRX_CALLBACKS_38D_RAW_EIGTH       7u

// Defines used for CRC/ALIVEERR and VEHICLE SPEED/SPEED DISPO debounce
#define SYSMONRX_CALLBACKS_CRCERR_TIMEOUT                2000u
#define SYSMONRX_CALLBACKS_ALIVEERR_TIMEOUT              2000u
#define SYSMONRX_CALLBACKS_SPEED_INVALID                 2000u
#define SYSMONRX_CALLBACKS_CRCERR_TIMER                     0u
#define SYSMONRX_CALLBACKS_ALIVEERR_TIMER                   1u
#define SYSMONRX_CALLBACKS_VEH_SPEED_TIMER                  2u
#define SYSMONRX_CALLBACKS_VVH_DISP_TIMER                   3u
#define SYSMONRX_CALLBACKS_NUMBER_OF_TIMERS                 4u

//-----------------------------------------------------------------------------
//  Data type definitions
//-----------------------------------------------------------------------------
typedef struct
{
    //input
    boolean boReq_Input;
    TIMER ulTimeMs_Input;
    //internal
    TIMER ulCommandStart;
    boolean boStartStopTimer;
    boolean boTimeOut;
}tsSysMonRx_TimerCfg;

//-----------------------------------------------------------------------------
//  function prototypes
//-----------------------------------------------------------------------------
void  SysMon_RxCallbacks_HS6_DAT_VSM_2AE       (teSysMon_RxFrameState eSysMonRxState);
void  SysMon_RxCallbacks_HS6_DAT_VSM_34E       (teSysMon_RxFrameState eSysMonRxState);
void  SysMon_RxCallbacks_HS6_COMMANDES_VSM_036 (teSysMon_RxFrameState eSysMonRxState);
void  SysMon_RxCallbacks_HS6_DAT_BSI_432       (teSysMon_RxFrameState eSysMonRxState);
void  SysMon_RxCallbacks_HS6_DYN_ABR_38D       (teSysMon_RxFrameState eSysMonRxState);

// Public interfaces for Emergency Operation Mode table
void  SysMonRx_Callbacks_GetLowBeamSignal          (uint8 *pucValue, teRte_SigQty *peSigQty);
void  SysMonRx_Callbacks_GetLifePhaseSignal        (teRte_PhaseVie *peValue, teRte_SigQty *peSigQty);
void  SysMonRx_Callbacks_GetSpeedSignal            (uint16 *punSpeedValue, teRte_SigQty *peSigQty);
void  SysMonRx_Callbacks_GetVESMainStateSignal     (teRte_SigQty *peSigQty);
void  SysMonRx_Callbacks_GetTurnIndicatorSignal    (uint8 *pucValue, teRte_SigQty *peSigQty);
void  SysMonRx_Callbacks_GetDiagMuxState           (boolean *pboValue);
void  SysMonRx_Callbacks_UpdateDeactivationStatus  (boolean boDeactStatus);

void SysMonRx_Callbacks_ResetSigQty(void);

teSysMon_WarningMode SysMonRx_Callbacks_Get_AutonomMode(void);

#endif // __SIG_PREP_RX_CALLBACKS_H__

// EOF
