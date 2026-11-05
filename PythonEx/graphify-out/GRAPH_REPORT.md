# Graph Report - Swc  (2026-09-01)

## Corpus Check
- Large corpus: 353 files · ~537,895 words. Semantic extraction will be expensive (many Claude tokens). Consider running on a subfolder.

## Summary
- 3191 nodes · 7236 edges · 178 communities (176 shown, 2 thin omitted)
- Extraction: 81% EXTRACTED · 19% INFERRED · 0% AMBIGUOUS · INFERRED: 1342 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Community Hubs (Navigation)
- Adb module
- Pitch module
- Sigprep module
- Afsmaster module
- Dbl module
- Cpm module
- Ctrl module
- Ctrl module
- Rsens module
- Ctrl module
- Dbl module
- Sigprep module
- Ctrl module
- Sysmon module
- Fctr module
- Fctr module
- Adb module
- Sysmon module
- Dbl module
- Fctr module
- Ctrl module
- Sigprep module
- Ctrl module
- Sysmon module
- Adb module
- Ctrl module
- Ctrl module
- Ctrl module
- Ctrl module
- Sigprep module
- Ctrl module
- Ctrl module
- Sysmon module
- Adb module
- Ctrl module
- Sysmon module
- Ctrl module
- Adb module
- Adb module
- Ctrl module
- Sysvolt module
- Adb module
- Statm module
- Sysmon module
- Adb module
- Ctrl module
- Dbl module
- Fctr module
- Sigprep module
- Ctrl module
- Ctrl module
- Dbl module
- Diagcontrol module
- Adb module
- Adb module
- Ctrl module
- Afsmaster module
- Ctrl module
- Ctrl module
- Ctrl module
- Dbl module
- Afsmaster module
- Ctrl module
- Fctr module
- Sysmon module
- Adb module
- Adb module
- Afsmaster module
- Dbl module
- Ctrl module
- Sysmon module
- Sysmon module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Afsmaster module
- Sysmon module
- Sysmon module
- Adb module
- Adb module
- Ctrl module
- Ctrl module
- Sysmon module
- Adb module
- Ctrl module
- Ctrl module
- Ctrl module
- Dbl module
- Adb module
- Adb module
- Dbl module
- Dbl module
- Sysmon module
- Adb module
- Adb module
- Sysmon module
- Afsmaster module
- Codm module
- Ctrl module
- Dbl module
- Afsmaster module
- Ctrl module
- Sigprep module
- Adb module
- Adb module
- Appl module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Sigprep module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- Adb module
- LOCAL module

## God Nodes (most connected - your core abstractions)
1. `AdbMxb4_Cycle0()` - 38 edges
2. `AdbMxb3Main()` - 33 edges
3. `tagISV_SNoObjRst_TSAG_1_tp` - 31 edges
4. `AdbPxa3Main()` - 28 edges
5. `SigPrep_RxCallbacks_ConvertValueInt2Sint()` - 24 edges
6. `SysMonCheck_Cycle10ms_HandleLowBeamAndTurnIndicator()` - 24 edges
7. `AdbPxa3CalcIntensityAndAnimation()` - 23 edges
8. `AdbPxa3_Cycle0()` - 20 edges
9. `ADBModel()` - 20 edges
10. `tag_SIBFS_CalcAdbModeLogic_calcAdbMode__tp` - 20 edges

## Surprising Connections (you probably didn't know these)
- `rpAdbPxa3_Cycle0()` --calls--> `AdbPxa3_Cycle0()`  [INFERRED]
  Adb/ADBPXA3/ctaaAdbPxa3.c → Adb/ADBPXA3/AdbPxa3.c
- `rpMxb_Cycle0()` --calls--> `AdbMxb4_Cycle0()`  [INFERRED]
  Adb/Mxb/ctaaMxb.c → Adb/Mxb/AdbMxb4.c
- `Com_Loss_Callback()` --calls--> `SigPrepRx_ComM_EnableCallbacks()`  [INFERRED]
  ElecInt/ElecInt.c → SigPrep/SigPrepRx.c
- `Normal_Request_Callback()` --calls--> `SigPrepRx_ComM_EnableCallbacks()`  [INFERRED]
  ElecInt/ElecInt.c → SigPrep/SigPrepRx.c
- `Normal_Request_Callback()` --calls--> `SigPrepTx_ComM_ActivateTxBufer()`  [INFERRED]
  ElecInt/ElecInt.c → SigPrep/SigPrepTx.c

## Import Cycles
- None detected.

## Communities (178 total, 2 thin omitted)

### Community 0 - "Adb module"
Cohesion: 0.05
Nodes (107): ADBModel(), tAdbChannelX, tCamObjectTL, Get_Sa2_AdbChannel1_LeftHL(), Get_Sa2_AdbChannel1_RightHL(), Get_Sa2_AdbChannel2_LeftHL(), Get_Sa2_AdbChannel2_RightHL(), Get_Sa2_AdbChannel3_LeftHL() (+99 more)

### Community 1 - "Pitch module"
Cohesion: 0.05
Nodes (78): Pitch_CheckSensValue, Pitch_CheckVehSpeedData, CONST_AL, STATIC_AL, boolean, STATIC_AL, tNvmPara_CodingArea, tParaFct0_Cmd (+70 more)

### Community 2 - "Sigprep module"
Cohesion: 0.03
Nodes (10): CONST_AL, STATIC_AL, tParaFct0_Cmd, uint8, SigPrep_CodingDataValidation(), SigPrep_Data_ParaFct0(), SigPrep_SetCodingData(), SigPrepRx_Cycle0() (+2 more)

### Community 3 - "Afsmaster module"
Cohesion: 0.06
Nodes (72): AvacStat1_CheckZeroLvl(), AvacStat1_Cycle0(), AvacStat1_GetHeadlightAngle(), AvacStat1_Init(), AvacStat1_SetRegMode(), AvacStat1_SetSpeedMode(), AvacStat1_SetStaticFilterParameters(), sint16 (+64 more)

### Community 4 - "Dbl module"
Cohesion: 0.06
Nodes (67): _ClPolySolverCalcStartSlope(), LrRelation2(), CodAfsHld_CGCorrection(), CodAfsHld_HlaFilterSize(), CodAfsHld_HlaOutMaxStep(), CodAfsHld_HlaOutMinStep(), CodAfsHld_IdleRange(), CodAFSHldDev_OperatingMode() (+59 more)

### Community 5 - "Cpm module"
Cohesion: 0.05
Nodes (43): CONST_AL, STATIC_AL, tsRte_PcbTemperatureMsg, Cpm_CodingValidCycle(), Cpm_Cycle20ms(), CPM_Data_DriverMap(), Cpm_Init(), Cpm_MapParams() (+35 more)

### Community 6 - "Ctrl module"
Cohesion: 0.07
Nodes (57): boolean, CONST_AL, teCtrlStp_MountingSide, tsCtrlStp_ValidationParameters, uint8_least, CtrlStp_CondEnabled(), CtrlStp_CondIsOn(), CtrlStp_CondIsReady() (+49 more)

### Community 7 - "Ctrl module"
Cohesion: 0.11
Nodes (58): STATIC_AL, teCtrlStp_SensorState, CtrlStp_DetectElecTransition(), CtrlStp_RefRequest(), CtrlStp_RetPowerTrainActive(), CtrlStp_ReturnboExtTakeOver(), CtrlStp_ReturnboLvlAdjFuncFault(), CtrlStp_ReturnboSlaveLvlAdjFuncFault() (+50 more)

### Community 8 - "Rsens module"
Cohesion: 0.08
Nodes (52): NtcTables, rpRSens_Cycle0(), boolean, sint16, STATIC_AL, tNvmPara_CodingArea, tParaFct0_Cmd, uint16 (+44 more)

### Community 9 - "Ctrl module"
Cohesion: 0.13
Nodes (54): AnimMa_AllocateBlockContext(), AnimMa_BitTest(), AnimMa_CeilU8(), AnimMa_Cod_GetBlockSpecific(), AnimMa_copyKernel(), AnimMa_DeleteBlockContext(), AnimMa_DeleteBlocks(), AnimMa_EnableInitContext() (+46 more)

### Community 10 - "Dbl module"
Cohesion: 0.10
Nodes (52): ClHlaAttenuationFactor(), ClResetSpeedFilter(), teTraffic, uint32, Dbl_RteAccess_ReadDblCmd(), Dbl_RteAccess_ReadDblTrafficSide(), Dbl_RteAccess_ReadEnvCondition(), Dbl_RteAccess_ReadSpeed() (+44 more)

### Community 11 - "Sigprep module"
Cohesion: 0.06
Nodes (28): Com_Loss_Callback(), Com_Off_Request_Callback(), ElecInt_Cycle(), ElecInt_EnterEIMMode(), ElecInt_ExitEIMMode(), Normal_Request_Callback(), Sleep_Callback(), Sleep_Request_Callback() (+20 more)

### Community 12 - "Ctrl module"
Cohesion: 0.09
Nodes (46): riCtrlSwiDeInit(), riCtrlSwiInit(), rpCtrlSwiCycle0(), boolean, sint8, STATIC_AL, TIMER, tNvmPara_CodingArea (+38 more)

### Community 13 - "Sysmon module"
Cohesion: 0.11
Nodes (50): SysMon_EnumLifePhaseState, STATIC_AL, SysMonRx_ASIL_Compute_LB_PhaseVieState(), SysMonRx_ASIL_Compute_TI_PhaseVieState(), SysMonRx_ASIL_EmergencyOperation(), SysMonRx_ASIL_EmergencyOperation_ActivateLowBeam(), SysMonRx_ASIL_EmergencyOperation_ClearDiagLowBeam(), SysMonRx_ASIL_EmergencyOperation_ClearDiagTurnIndicator() (+42 more)

### Community 14 - "Fctr module"
Cohesion: 0.07
Nodes (47): FctR_eAimingType, boolean, STATIC_AL, Std_ReturnType, teFctR_AfsMode, teFctR_EcuOperationgMode, tsFctR_StdLgtFctsReq, tsFctR_TgtLgtReq (+39 more)

### Community 15 - "Fctr module"
Cohesion: 0.11
Nodes (46): boolean, FctR_Cod_Valid(), boolean, sint8, STATIC_AL, tAppLightFunction, tAppLogLamp, TIMER (+38 more)

### Community 16 - "Adb module"
Cohesion: 0.11
Nodes (45): AdbMxb3Alg(), sint16, tCamObjArray, CalcChannelOutput_Motorway(), calcDrivingMode(), CalcSafetyDynOffset(), AdbMxb4Data_GetCodingValid(), Cod_aCamDistanceFilter_Indexed() (+37 more)

### Community 17 - "Sysmon module"
Cohesion: 0.12
Nodes (42): teRte_MountingSide, CONST_AL, STATIC_AL, teRte_SigQty, uint8, SysMon_RxCallbacks_HS6_COMMANDES_VSM_036(), SysMon_RxCallbacks_HS6_DAT_BSI_432(), SysMon_RxCallbacks_HS6_DAT_VSM_2AE() (+34 more)

### Community 18 - "Dbl module"
Cohesion: 0.08
Nodes (41): boolean, teDbl_MountingSide, uint8, Dbl_Read_PhaseVie(), Dbl_RteAccess_Read_EcuSide(), Dbl_RteAccess_ReadDblOutput(), Dbl_RteAccess_ReadDynBendingBeamFaultL(), Dbl_RteAccess_ReadDynBendingBeamFaultR() (+33 more)

### Community 19 - "Fctr module"
Cohesion: 0.12
Nodes (40): FctR_RteAccess_Write_TiWarningMode(), boolean, STATIC_AL, teFctR_AfsMode, teFctR_EcuOperationgMode, tsFctR_StdLgtFctsReq, tsFctR_TgtLgtReq, tsFctR_TiReq (+32 more)

### Community 20 - "Ctrl module"
Cohesion: 0.09
Nodes (39): boolean, uint16, CtrlStp_GetContinMove(), CtrlStp_GetOffset(), CtrlStp_SetDiagPos(), CtrlStp_TempCheck(), CtrlStp_HandleDiagLvl(), boolean (+31 more)

### Community 21 - "Sigprep module"
Cohesion: 0.16
Nodes (38): tsRte_SigPrep_ClusterSigGroup2_sVal, tsRte_SigPrep_PerceiveSigGroup2_sVal, uint32, uint8, SigPrep_RxCallbacks_Compute_ClusterSubType(), SigPrep_RxCallbacks_Compute_ClusterType(), SigPrep_RxCallbacks_Compute_TrafficDetected(), SigPrep_RxCallbacks_ConfigDetection() (+30 more)

### Community 22 - "Ctrl module"
Cohesion: 0.10
Nodes (33): Anima_CheckInputs, Anima_Cycle10(), Anima_DoRamps(), Anima_GetInputs(), Anima_Init(), Anima_Percent8_to_Percent16(), Anima_ReadFrontTurnIndicatorCmd(), Anima_StartStopAnimation() (+25 more)

### Community 23 - "Sysmon module"
Cohesion: 0.07
Nodes (26): EECO_TEP_ProfileOneChunkStatusPtr, riSysMon_E2EInit(), rpSysMon_E2ECycle10ms(), rcSysMon_Cycle1ms(), riSysMon_Init(), riSysMonCheckInit(), rpSysMonCheck_Cycle(), riSysMonRxInit() (+18 more)

### Community 24 - "Adb module"
Cohesion: 0.11
Nodes (14): ISV_SNoObjRst_GFHB_1_tp, ISV_SNoObjRst_TSAG_1_tp, tagISV_SChOutput_GFHB_1_tp, pISV_SNoObjRst_GFHB_1_tp, tagISV_SChOutput_TSAG_1_tp, pISV_SNoObjRst_TSAG_1_tp, tAdbChannelX, tagISV_SNoObjRst_GFHB_1_1_tp (+6 more)

### Community 25 - "Ctrl module"
Cohesion: 0.15
Nodes (34): CtrlLed_Data_AnimationMapping(), CtrlLed_Data_Get_ConfigLedHssName(), CtrlLed_Data_Get_ConfigLedName(), CtrlLed_Data_Get_DriverMap(), CtrlLed_Data_Get_PxlMap(), CtrlLed_Data_Get_Size_PxlMap(), CtrlLed_Data_Led_CurBinSel_Ch1(), CtrlLed_Data_Led_CurBinSel_Ch10() (+26 more)

### Community 26 - "Ctrl module"
Cohesion: 0.12
Nodes (30): AnimMa_ActiveSeqNr(), AnimMa_clearSequence(), AnimMa_Cod_GetSequenceIdx(), AnimMa_FindSequence(), AnimMa_getElapsedTime(), AnimMa_getMountSide(), AnimMa_GetPxlNr(), AnimMa_isCodingValid() (+22 more)

### Community 27 - "Ctrl module"
Cohesion: 0.10
Nodes (31): boolean, STATIC_AL, tuCtrlPxl_bErr, uint16, uint8, CtrlPxl_RteAccess_Get_Coding(), CtrlPxl_RteAccess_Get_ECU_Side(), CtrlPxl_RteAccess_Get_Intensities_CPM() (+23 more)

### Community 28 - "Ctrl module"
Cohesion: 0.10
Nodes (33): CtrlStp_ReadMasterSignals(), CtrlStp_ReadSlaveSignals(), CtrlStp_WriteMasterSignals(), CtrlStp_WriteSlaveSignals(), void(), Cod_LwrMaxRefSpeed(), boolean, sint16 (+25 more)

### Community 29 - "Sigprep module"
Cohesion: 0.08
Nodes (34): sint16, STATIC_AL, uint16, SigPrep_RxCallbacks_Compute_ExtLightingAnimationReq(), SigPrep_RxCallbacks_HS6_DAT2_DRVLED_R_4D7_RX(), SigPrep_RxCallbacks_HS6_DAT4_V2_BSI_552(), SigPrep_RxCallbacks_HS6_DAT_DRVLED_R_297_RX(), SigPrep_RxCallbacks_HS6_DAT_VSM_36E() (+26 more)

### Community 30 - "Ctrl module"
Cohesion: 0.16
Nodes (32): AM_INLINE, AnimMa_AllocateBlocks(), AnimMa_PiecewiseLinear_InitRamp(), AnimMa_StopBlocksNr(), tBlockSpecificPiecewiseLinear, Ramp_Phys2HighRes(), AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoint_Intensity(), AnimMa_Cod_Get_BlockSpecificPiecewiseLinear_FunctionPoint_Time() (+24 more)

### Community 31 - "Ctrl module"
Cohesion: 0.09
Nodes (32): teCtrlDcm_MountingSide, CtrlDcm_GetDiagLvl(), CtrlDcm_ReadSlaveSignals(), CtrlDcm_ReturnSide(), CtrlDcm_WriteMasterSignals(), CtrlDcm_WriteSlaveSignals(), CtrlDcm_WriteValidationFrames(), teCtrlDcm_MountingSide (+24 more)

### Community 32 - "Sysmon module"
Cohesion: 0.14
Nodes (32): boolean, sint8, STATIC_AL, TIMER, uint8, SysMonCheck_Data_AreFuSaParamValid(), SysMonCheck_Data_GetaLEDChParamPtr(), SysMonCheck_LedDiag_Init() (+24 more)

### Community 33 - "Adb module"
Cohesion: 0.08
Nodes (28): tAdbChannelX, CreateChannelOutputs(), tAdbChannelX, ParallaxCorrection(), sint16, tAdbChannelX, tieAdbHeadlampSide, tieAdbMode (+20 more)

### Community 34 - "Ctrl module"
Cohesion: 0.14
Nodes (32): CtrlDcm_ReturnboTrainingState(), CtrlDcm_RetVehIgnition(), CtrlDcm_SetDiagLvl(), CtrlDcm_SetFailIgnitionNeeded(), CtrlDcm_SetSignalMode(), CtrlDcm_SetSlaveSafetyPosition(), CtrlDcm_SetSlaveStopRequest(), CtrlDcm_RteAccess_ReadVehicleModeConfig() (+24 more)

### Community 35 - "Sysmon module"
Cohesion: 0.16
Nodes (31): STATIC_AL, uint8, SysMonCheck_Data_AreAllLedChSupportedByHw(), SysMonCheck_Data_CalcComputedFuSaParamCrc32(), SysMonCheck_Data_CheckCrcForFuSaParameters(), SysMonCheck_Data_CheckEFT_ECUVARCFG_LED(), SysMonCheck_Data_ComputeFuSaParam(), SysMonCheck_Data_Cycle10ms_FuSaMonitoring() (+23 more)

### Community 36 - "Ctrl module"
Cohesion: 0.11
Nodes (30): boolean, STATIC_AL, tsRte_Binning0, uint16, uint8, uint8_fast, CtrlLed_Rte_Get_BinningClass(), CtrlLed_Rte_ReadTgtBinningVal() (+22 more)

### Community 38 - "Adb module"
Cohesion: 0.12
Nodes (29): AdbPxa3CalcCurtainAnimSeq(), tAdbActualShadowTL, tAdbChannelTL, tieAdbLightDist84Pxl, Get_AdbPxa3_ActualLightDist(), Get_AdbPxa3_ActualShadowCh1_Addr(), Get_AdbPxa3_ActualShadowCh2_Addr(), Get_AdbPxa3_ActualShadowCh3_Addr() (+21 more)

### Community 39 - "Ctrl module"
Cohesion: 0.11
Nodes (30): sint16, STATIC_AL, uint8, CtrlStp_ApplyOffset(), CtrlStp_CheckFrame350Recovery(), CtrlStp_DetectAfsOffsetCurtainActivation(), CtrlStp_DetectAfsOffsetCurtainDeactivation(), CtrlStp_DetectOffset() (+22 more)

### Community 40 - "Sysvolt module"
Cohesion: 0.10
Nodes (23): boolean, STATIC_AL, teSysVolt_VoltRanges, Std_ReturnType, teSysVolt_VoltRanges, uint16, SysVolt_RteAccess_Read_Vbat(), SysVolt_RteAccess_ReadElectricalSuppState() (+15 more)

### Community 41 - "Adb module"
Cohesion: 0.07
Nodes (27): tagISV_SNoObjRst_TSAG_1_tp, CNoObjRst_TSAG_1_Hold, CNoObjRst_TSAG_1_HoldOff1_ctr, CNoObjRst_TSAG_2_Hold_, CNoObjRst_TSAG_3_On, CNoObjRst_TSAG_4_Off, pISV_SNoObjRst_TSAG_1_1_tp, X_SNoObjRst_TSAG_10_Unit_Delay (+19 more)

### Community 42 - "Statm module"
Cohesion: 0.14
Nodes (22): reStatM_ResetStatistics(), boolean, STATIC_AL, tsRte_PcbTemperatureMsg, uint32, uint8, StatM__boCheckPatern(), StatM_Cycle0() (+14 more)

### Community 43 - "Sysmon module"
Cohesion: 0.11
Nodes (21): reSysMonRx_EnableCallbacks(), SysMonRx_ASIL_Get_boEmergencyOperation_FinalTurnIndicatorStatus(), SysMonRx_ASIL_InitLowBeamAndTurnIndicatorInterfaces(), STATIC_AL, uint8, boolean, SysMonRx_Callbacks_GetDiagMuxState(), SysMonRx_Callbacks_ResetSigQty() (+13 more)

### Community 44 - "Adb module"
Cohesion: 0.14
Nodes (25): AdbPxa3CalcIntensityAndAnimation(), boolean, tAdbAngleTL_deg, tAdbBrightnessTL_pct, tAdbChannelTL, tieAdbPxaMode, CAdbPxa3_12_ACTIVE_NO_OBJECT_en(), CAdbPxa3_16_AnimationMode_node_fcn1() (+17 more)

### Community 45 - "Ctrl module"
Cohesion: 0.23
Nodes (25): CtrlLed_pfInternalHandling(), boolean, CONST_AL, STATIC_AL, uint16, uint8, uint8_fast, CtrlLed_Diag_Check_MtxVccx_Eeprom_Fault() (+17 more)

### Community 46 - "Dbl module"
Cohesion: 0.15
Nodes (24): sint16, sint32, STATIC_AL, teDir, ClHlaIdlePosition(), ClPoly3(), ClPolySolver(), _ClPolySolverCalcEndC() (+16 more)

### Community 47 - "Fctr module"
Cohesion: 0.23
Nodes (25): Cod_ActiveB(), Cod_AfsTransitionDim(), Cod_ErrorImpactB(), Cod_IntensityB(), Cod_PriorityB(), Cod_RampTypeB(), Cod_TimeOffB(), Cod_TimeOnB() (+17 more)

### Community 48 - "Sigprep module"
Cohesion: 0.13
Nodes (18): reSigPrepTx_SendFrame457(), reSigPrepTx_SendFrame477(), boolean, SigPrep_RxCallbacks_HS6_DAT7_BSI_612(), SigPrep_RxCallbacks_HS6_DYN_VSM_28E(), Cod_Asl_Enable(), Cod_AvacStp_Enable(), Cod_CurtainEffect_Enable() (+10 more)

### Community 49 - "Ctrl module"
Cohesion: 0.24
Nodes (24): Anima_Tgt(), CONST_AL, STATIC_AL, uint16, uint32, uint8, uint8_fast, CtrlLed_Buck_Handling() (+16 more)

### Community 50 - "Ctrl module"
Cohesion: 0.23
Nodes (24): CtrlLed_Init(), boolean, CONST_AL, STATIC_AL, tParaFct0_Cmd, tsCtrlled_CodingData, uint16, uint8 (+16 more)

### Community 51 - "Dbl module"
Cohesion: 0.12
Nodes (23): Dbl_Init(), DblCrvCalc_Get_CurvatureCodingParameters(), DblCrvCalc_Get_WfCodingParameters(), DblCrState_Init(), Dbl_Get_Calculated_Curvature_Coding_Parameters(), DblcSm_Init(), DblcSm_ParaFct0(), CodDblCurvatureCalculation_Crc_Steering_Ratio() (+15 more)

### Community 52 - "Diagcontrol module"
Cohesion: 0.12
Nodes (13): CONST_AL, STATIC_AL, uint8_least, DiagControl_AfsTakeOver(), DiagControl_Cycle0(), DiagControl_ProgramingSession_TakeOver(), DiagControl_SequenceMachine(), boolean (+5 more)

### Community 53 - "Adb module"
Cohesion: 0.19
Nodes (23): AdbPxa3_Cycle0(), AdbPxa3Data_GetCodingValid(), LOCAL_INLINE, AdbPxa3_Rte_Read_AdbChannel01(), AdbPxa3_Rte_Read_AdbChannel02(), AdbPxa3_Rte_Read_AdbChannel03(), AdbPxa3_Rte_Read_AdbChannel04(), AdbPxa3_Rte_Read_AdbChannel05() (+15 more)

### Community 54 - "Adb module"
Cohesion: 0.12
Nodes (22): sint32, tAdbAngleTL_deg, tAdbBrightnessTL_pct, uint16, uint32, uint8, Tab1DIntp2I1T133_AdbPxa3_(), Tab1DIntp2I3T68_AdbPxa3_() (+14 more)

### Community 55 - "Ctrl module"
Cohesion: 0.24
Nodes (22): boolean, teCtrlDcm_SensorState, CtrlDcm_CondEnabled(), CtrlDcm_RetPowerTrainActive(), CtrlDcm_ReturnboLvlAdjFuncFault(), CtrlDcm_ReturnboLvlAdjHeadlampFault(), CtrlDcm_ReturnboLvlAdjHeadlampFault_R(), CtrlDcm_ReturnboSlaveLvlAdjFuncFault() (+14 more)

### Community 56 - "Afsmaster module"
Cohesion: 0.13
Nodes (21): AvacAlg_Main(), STATIC_AL, CreateOutputSignal_(), GetAutoAngle_(), SetDynamicIndex_(), AvacData_GetAvacD_En(), AvacData_GetAvacD_Ok(), AvacData_GetAvacS_En() (+13 more)

### Community 57 - "Ctrl module"
Cohesion: 0.19
Nodes (21): CONST_AL, sint16, STATIC_AL, uint16, uint8_least, CtrlDcm_CheckLvlAdjHeadlampFaultRecovery(), CtrlDcm_CheckLvlAdjHeadlampFaultRecovery_R(), CtrlDcm_DiagDcmTakeOver() (+13 more)

### Community 58 - "Ctrl module"
Cohesion: 0.18
Nodes (21): STATIC_AL, uint16, CtrlPxl_Cycle0(), CtrlPxl_GetInternalHandlingStruct(), CtrlPxl_ProcessIntensities(), STATIC_AL, uint8, CtrlPxl_AccessCalibDataAndCopy() (+13 more)

### Community 59 - "Ctrl module"
Cohesion: 0.19
Nodes (21): CtrlStp_DoNorm(), CtrlStp_GetTgtPos(), CtrlStp_isSafetyPosReached(), CtrlStp_SetTgtTmin(), CtrlStp_StartRef(), CtrlStp_WriteValidationFrames(), Cod_LwrAnschlagMi(), Cod_LwrHsGrad() (+13 more)

### Community 60 - "Dbl module"
Cohesion: 0.18
Nodes (20): Dbl_RteAccess_ReadEtatReseauElec(), Dbl_RteAccess_ReadSteeringWheelAngle(), Dbl_RteAccess_ReadVehicleSpeed(), Dbl_RteAccess_ReadYawSpeed(), CONST_AL, sint32, STATIC_AL, DblCrState_HandleDelayStatus() (+12 more)

### Community 61 - "Afsmaster module"
Cohesion: 0.21
Nodes (20): SetFilterTimeConstants_(), AvacData_GetPitchConfigValid(), Cod_AvacAccelPreDetectThresholdDown(), Cod_AvacAccelPreDetectThresholdUp(), Cod_AvacBadStreetTolerance(), Cod_AvacBrakePreDetectThresholdDown(), Cod_AvacBrakePreDetectThresholdUp(), Cod_AvacFilterDownMax() (+12 more)

### Community 62 - "Ctrl module"
Cohesion: 0.14
Nodes (15): CtrlDcm_GetTgtPos(), boolean, sint16, sint8, uint8, Cod_DcmEnable(), Cod_DcmFrozenVehSpeedASL(), Cod_DcmMaxAdjASL() (+7 more)

### Community 63 - "Fctr module"
Cohesion: 0.12
Nodes (10): CONST_AL, tParaFct0_Cmd, FctR_GetDelayTiNotRequested(), uint16, FctR_Cycle(), FctR_Init(), FctR_MapParams(), FctR_ParaFct0() (+2 more)

### Community 64 - "Sysmon module"
Cohesion: 0.10
Nodes (11): boolean, uint8, uint8_fast, SysMonCheck_RteAccess_Get_ChannelState(), SysMonCheck_RteAccess_Get_ElecSupState(), SysMonCheck_RteAccess_Get_TiFailureStatus(), SysMonCheck_RteAccess_Get_VoltageRange(), SysMonCheck_RteAccess_Set_ChannelState() (+3 more)

### Community 65 - "Adb module"
Cohesion: 0.10
Nodes (20): tag_SIBFS_CalcAdbModeLogic_calcAdbMode__tp, CcalcAdbMode_10_GFHB, CcalcAdbMode_11_OFF, CcalcAdbMode_12_Mode_CurtainOFF, CcalcAdbMode_13_CurtainON, CcalcAdbMode_15_GFHB_AfterSales_Mode, CcalcAdbMode_16_AftersalesMode_OFF, CcalcAdbMode_17_AftersalesMode_ON (+12 more)

### Community 67 - "Adb module"
Cohesion: 0.16
Nodes (18): tAdbChannelX, tAdbSpeedTL_kph, tieAdbDrivingMode, CalcChannelOutput_GFHB(), CalcChannelOutput_TSAG(), ISV_SNoObjRst_GFHB_1_tp, ISV_SNoObjRst_TSAG_1_tp, tAdbSpeedTL_kph (+10 more)

### Community 68 - "Afsmaster module"
Cohesion: 0.14
Nodes (12): Avac_CheckZeroLvl(), Avac_Cycle0(), Avac_Init(), Avac_ParaChanged(), STATIC_AL, AvacAlg_Add_Main(), AvacData_GetCodingValid(), AvacData_Init() (+4 more)

### Community 69 - "Dbl module"
Cohesion: 0.18
Nodes (12): Dbl_RteAccess_ReadSwimRate(), Dbl_RteAccess_WriteSwimRate(), CodAfsSwiRateLim_CGCorrection(), sint16, sint32, STATIC_AL, uint8, Dblc_Convert_Deg_mRad() (+4 more)

### Community 70 - "Ctrl module"
Cohesion: 0.19
Nodes (16): CtrlPxl_Init(), boolean, CONST_AL, STATIC_AL, tParaFct0_Cmd, uint8, CtrlPxl_CodingDataValidation(), CtrlPxl_Data_DriverMap() (+8 more)

### Community 71 - "Sysmon module"
Cohesion: 0.22
Nodes (16): tSysMon_FuSaChannelsStatusReaction, boolean, STATIC_AL, tSysMon_FuSaChannelsStatusReaction, uint8, uint8_fast, SysMonCheck_LedDiag_Cycle(), SysMonCheck_LedDiag_ErrorDebounce() (+8 more)

### Community 72 - "Sysmon module"
Cohesion: 0.15
Nodes (17): boolean, CONST_AL, tParaFct0_Cmd, uint16, SysMonCheck_Data_CheckAndSetCodingData(), SysMonCheck_Data_CodingDataValidation(), SysMonCheck_Data_Get_Crc32RamFailure(), SysMonCheck_Data_Get_Crc32RomFailure() (+9 more)

### Community 73 - "Adb module"
Cohesion: 0.13
Nodes (15): AdbPxa3CalcPixelOffsetMatrix(), sint16, tAdbBrightnessTL_pct, AdbPxa3SelectLightDistribution(), boolean, tAdbBrightnessTL_pct, tAdbIntensityTL_pct, tieAdbLightDist84Pxl (+7 more)

### Community 74 - "Adb module"
Cohesion: 0.12
Nodes (16): tagISV_SCrCamObj_1_tp, CCrCamObj_1__index, CCrCamObj_1_State, CCrCamObj_2_ON, CCrCamObj_3_INIT, CCrCamObj_4_OFF, FilterValue, FilterValue_a (+8 more)

### Community 75 - "Adb module"
Cohesion: 0.12
Nodes (16): tagISV_SNoObjRst_GFHB_1_tp, CNoObjRst_GFHB_1_Hold, CNoObjRst_GFHB_1_HoldOff2_ctr, CNoObjRst_GFHB_2_Hold_, CNoObjRst_GFHB_3_On, CNoObjRst_GFHB_4_Off, pISV_SNoObjRst_GFHB_1_1_tp, X_SNoObjRst_GFHB_1_Unit_Delay (+8 more)

### Community 76 - "Adb module"
Cohesion: 0.23
Nodes (13): boolean, ISV_SLutDyn_1_tp, sint16, sint32, FIR_Filter(), Hysteresis(), LookUpTableDyn(), TrackingFilter() (+5 more)

### Community 77 - "Adb module"
Cohesion: 0.13
Nodes (15): tAdbIntensityTL_pct, tAdbTimeTL_s, tieAdbPxaMode, tagISV_SPxlActMat_1_tp, CPxlActMat_1_DimTimeDown, CPxlActMat_1_DimTimeUp, CPxlActMat_1_PixelBrightness, pISV_SPxlActMat_1_0_tp (+7 more)

### Community 78 - "Afsmaster module"
Cohesion: 0.27
Nodes (14): DoStaticRegulation_(), AvacVddGetAccIndex_(), AvacVddGetBadStreetIndex_(), AvacVddGetDynState_(), AvacVddGetDynState_ConstSpeed_(), AvacVddGetDynState_HighAccel_(), AvacVddGetDynState_Invalid_(), AvacVddGetDynState_ZeroSpeed_() (+6 more)

### Community 79 - "Sysmon module"
Cohesion: 0.15
Nodes (15): NM_ModeType, SysMon_EnumTurnIndicatorState, SysMon_EnumVESMainState, SysMonRx_ASIL_Check_TI_Scrolling(), SysMonRx_ASIL_Compute_TurnIndicatorState(), SysMonRx_ASIL_Compute_VESMainState(), SysMonRx_ASIL_EmergencyOperation_TurnIndicator_Refresh(), SysMonRx_ASIL_GetTurnIndicatorState() (+7 more)

### Community 80 - "Sysmon module"
Cohesion: 0.19
Nodes (14): SysMonCheck_Data_AreFuSaParam_Invalid(), boolean, STATIC_AL, SysMonCheck_InternalCom_Cycle(), SysMonCheck_InternalCom_Init(), SysMonCheck_InternalCom_IsComErrActive(), SysMonCheck_InternalCom_LedState_CheckCrc(), SysMonCheck_InternalCom_SetInternalComErrActive() (+6 more)

### Community 81 - "Adb module"
Cohesion: 0.15
Nodes (13): boolean, tieAdbMode, uint8, tagISV_SResetCh_1_tp, CResetCh_1_Chart_ctr, CResetCh_1_Chart_FirstRun, CResetCh_1_Ctrl, CResetCh_2_INIT (+5 more)

### Community 82 - "Adb module"
Cohesion: 0.15
Nodes (13): tagISV_SHoRateLim_1_tp, firstRun, firstRun_a, firstRun_b, firstRun_c, pre, pre_a, preFilter (+5 more)

### Community 83 - "Ctrl module"
Cohesion: 0.17
Nodes (9): rpCtrlDcm_Cycle(), CtrlDcm_ReadMasterSignals(), CtrlDcm_ReturnboExtTakeOver(), teCtrlDcm_SensorState, CtrlDcm_RteAccess_Read_DrvLedDiagR_Port(), CtrlDcm_RteAccess_ReadSensorStatus(), CtrlDcm_Master_Cycle20ms(), CtrlDcm_Slave_Cycle20ms() (+1 more)

### Community 84 - "Ctrl module"
Cohesion: 0.18
Nodes (8): Anima_MapParams(), Anima_ParaFct0(), CONST_AL, teRte_ExtLightingAnimationReq, CodPrj_GetAnimMaSequenceId(), tNvmPara_CodingArea, tParaFct0_Cmd, roAnima_ParaFct0()

### Community 85 - "Sysmon module"
Cohesion: 0.18
Nodes (13): SysMon_EnumLowBeamState, SysMon_EnumSpeedState, SysMonRx_ASIL_Compute_LowBeamState(), SysMonRx_ASIL_Compute_SpeedState(), SysMonRx_ASIL_EmergencyOperation_LowBeam_Refresh(), SysMonRx_ASIL_GetLowBeamState(), SysMonRx_ASIL_GetSpeedState(), SysMonRx_ASIL_SetLowBeamState() (+5 more)

### Community 86 - "Adb module"
Cohesion: 0.21
Nodes (9): AdbPxa3_Init(), AdbPxa3Data_Init(), AdbPxa3Data_MapParams(), AdbPxa3Data_ParaFct0(), CONST_AL, CONST_AL, riAdbPxa3_Init(), roAdbPxa3_ParaFct0() (+1 more)

### Community 87 - "Ctrl module"
Cohesion: 0.30
Nodes (3): tuCtrlPxl_bErr, uint8_fast, CtrlPxl_GetMtxFaults()

### Community 88 - "Ctrl module"
Cohesion: 0.23
Nodes (12): STATIC_AL, uint8, CtrlPxl_Diag_ErrorDetected(), CtrlPxl_Diag_Handle_VCCx(), CtrlPxl_Diag_HandleMlcComFault(), CtrlPxl_Diag_HandleMlcCrcFault(), CtrlPxl_Diag_HandleMlcPxlFault(), CtrlPxl_Special_UT_Instrumentation_Force_DefaultVccxState() (+4 more)

### Community 89 - "Ctrl module"
Cohesion: 0.18
Nodes (12): CtrlStp_DetectSide(), CtrlStp_EntryInit(), CtrlStp_ReadParam(), CtrlStp_Init(), tNvmPara_CodingArea, tParaFct0_Cmd, CtrlStp_ParaFct0(), riCtrlStpInit() (+4 more)

### Community 90 - "Dbl module"
Cohesion: 0.35
Nodes (11): sint16, sint32, STATIC_AL, uint16, uint32, DblCrvCalc_FindWfZone(), DblCrvCalc_getCurvatureValue(), DblCrvCalc_getLinearInterpolatedValue() (+3 more)

### Community 91 - "Adb module"
Cohesion: 0.29
Nodes (10): AdbPxa3CalcPixelActivityMatrix(), AdbPxa3PxlActMat(), boolean, tAdbActualShadowTL, tAdbAngleTL_deg, tAdbBrightnessTL_pct, tAdbChannelTL, tAdbTimeTL_s (+2 more)

### Community 92 - "Adb module"
Cohesion: 0.33
Nodes (10): boolean, tieAdbMode, uint8, calcAdbMode(), CcalcAdbMode_10_GFHB_ex(), CcalcAdbMode_19_AfterSales_Regulation_ex(), CcalcAdbMode_3_GFHB_Customer_Mode_ex(), CcalcAdbMode_4_Manual_HB_ex() (+2 more)

### Community 93 - "Dbl module"
Cohesion: 0.20
Nodes (11): Dbl_Curvature_SigQty, sint32, teRte_SigQty, Dbl_RteAccess_ReadCurvature(), CONST_AL, Dbl_Curvature_SigQty_INV(), Dbl_HandleDelayStatus(), Dbl_Timeout() (+3 more)

### Community 94 - "Dbl module"
Cohesion: 0.35
Nodes (10): sint32, STATIC_AL, teDir, uint32, uint8, CalcIdleRange(), ClIdleRange(), ClIdleSignal() (+2 more)

### Community 95 - "Sysmon module"
Cohesion: 0.24
Nodes (10): SysMonCheck_Data_IsCodingDataValid(), SysMonCheck_Data_IsTurnIndicatorFuSa(), CONST_AL, STATIC_AL, SysMonCheck_LedCtrl_Cycle(), SysMonCheck_LedCtrl_EvaluateLightSourceReq(), SysMonCheck_LedCtrl_Init(), SysMonCheck_LedCtrl_TargetLedDefaultValues() (+2 more)

### Community 96 - "Adb module"
Cohesion: 0.20
Nodes (10): sint32, tCamObjArray, tCamObjectTL, uint8, PrepCamObjects(), sint32, tCamObjectTL, CreateCamObject() (+2 more)

### Community 97 - "Adb module"
Cohesion: 0.20
Nodes (10): sint16, sint32, uint16, tagISV_SPowFact_1_tp, SRateLimDy_1_Ts, X_SPowFact_2_Unit_Delay1, X_SPowFact_2_Unit_Delay2, X_SRateLimDy_1_Delay_Input2 (+2 more)

### Community 98 - "Sysmon module"
Cohesion: 0.29
Nodes (8): SysMonCheck_TI_Diag_Status(), boolean, SysMonRx_ASIL_Get_boDiagLowBeamStatus(), SysMonRx_ASIL_Get_boDiagTurnIndicatorStatus(), SysMonRx_ASIL_Get_boEmergencyOperation_FinalLowBeamStatus(), SysMonRx_ASIL_Get_SysMonRx_ASIL_boEmergencyOperationLowBeam(), SysMon_TxCallbacks_CyclicFrame_457(), SysMon_TxCallbacks_CyclicFrame_477()

### Community 100 - "Codm module"
Cohesion: 0.28
Nodes (4): STATIC_AL, tParaFct0_Cmd, CodM_Init(), CodM_InitModules()

### Community 101 - "Ctrl module"
Cohesion: 0.25
Nodes (9): CtrlDcm_DetectSide(), tNvmPara_CodingArea, tParaFct0_Cmd, CtrlDcm_ParaFct0(), Std_ReturnType, teCtrlDcm_MountingSide, CtrlDcm_RteAccess_MapParams(), CtrlDcm_RteAccess_Read_EcuSide() (+1 more)

### Community 102 - "Dbl module"
Cohesion: 0.47
Nodes (8): sint32, STATIC_AL, Dbl_SmoothTransition(), LrRelation(), LrRelation1(), LrRelation4(), LrRelation5(), LrRelation6()

### Community 103 - "Afsmaster module"
Cohesion: 0.39
Nodes (7): DoDynamicRegulation_(), AvacUtil_Order1FilterByRelTime(), AvacUtil_RateLimiter(), AvacUtil_SignalLimiter(), ORDER1_Filter, sint16, uint16

### Community 104 - "Ctrl module"
Cohesion: 0.43
Nodes (7): tsCtrlled_CodingData, CtrlLed_pfCodingData(), Cod_IluminantType(), Cod_LedBinningCurrent(), Cod_LedChannelType(), Cod_LedName(), uint8_fast

### Community 105 - "Sigprep module"
Cohesion: 0.43
Nodes (7): teRte_MountingSide, boolean, SigPrep_RxCallback_SideCheck_297_RX(), SigPrep_RxCallback_SideCheck_2B7_RX(), SigPrep_RxCallback_SideCheck_477_RX(), SigPrep_RxCallback_SideCheck_4D7_RX(), SigPrepRx_GetMountingSide()

### Community 106 - "Adb module"
Cohesion: 0.33
Nodes (6): tag_SIBFS_AnimationMode_AdbPxa3__tp, Aux_CAdbPxa3_16_sflag1, CAdbPxa3_17_ON, CAdbPxa3_18_switchingOFF, CAdbPxa3_19_switchingON, CAdbPxa3_20_OFF

### Community 107 - "Adb module"
Cohesion: 0.33
Nodes (6): ISV_SLutDyn_1_tp, tagISV_SSafetyOff_1_tp, pISV_SLutDyn_1_tp, pISV_SLutDyn_1_tp_a, pISV_SLutDyn_1_tp_b, pISV_SLutDyn_1_tp_c

### Community 108 - "Appl module"
Cohesion: 0.47
Nodes (3): APPLI_Run(), APPLI_SelectCANID(), APPLI_SelectVehicleArchiVariant()

### Community 109 - "Adb module"
Cohesion: 0.40
Nodes (5): sint32, tagISV_SRateLimIL_1_tp, X_SRateLimIL_1_Delay_Input2, tagISV_SRateLimPx_1_tp, X_SRateLimPx_1_Delay_Input2

### Community 110 - "Adb module"
Cohesion: 0.40
Nodes (5): tagISV_SLutDynG_1_tp, pISV_SLutDynG_1_0_tp, pISV_SLutDynG_1_1_tp, ISV_SLutDynG_1_0_tp, ISV_SLutDynG_1_1_tp

### Community 111 - "Adb module"
Cohesion: 0.40
Nodes (5): tag_SIBFS_Scheduler_a_tp, Ca3_Slot1, Ca4_Slot2, Ca5_Slot3, Ca6_Slot4

### Community 112 - "Adb module"
Cohesion: 0.40
Nodes (3): AdbMxb4_Init(), riMxb_Init(), rpMxb_Cycle0()

### Community 113 - "Adb module"
Cohesion: 0.40
Nodes (5): tagISV_SLutDyn_1_tp, pISV_SLutDyn_1_0_tp, pISV_SLutDyn_1_1_tp, ISV_SLutDyn_1_0_tp, ISV_SLutDyn_1_1_tp

### Community 117 - "Adb module"
Cohesion: 0.50
Nodes (4): tag_SIBFS_PixelAnimationSequence__switching_animated_OFF_1_AdbPxa3__tp, CAdbPxa3_26_hold, CAdbPxa3_27_switchOff, CAdbPxa3_28_on

### Community 118 - "Adb module"
Cohesion: 0.50
Nodes (4): tag_SIBFS_PixelAnimationSequence__switching_animated_OFF_2_AdbPxa3__tp, CAdbPxa3_30_hold, CAdbPxa3_31_switchOff, CAdbPxa3_32_on

### Community 119 - "Adb module"
Cohesion: 0.50
Nodes (4): tag_SIBFS_PixelAnimationSequence__switching_animated_OFF__AdbPxa3__tp, CAdbPxa3_22_hold, CAdbPxa3_23_switchOff, CAdbPxa3_24_on

### Community 120 - "Adb module"
Cohesion: 0.50
Nodes (4): tag_SIBFS_PixelAnimationSequence__switching_animted_ON1_AdbPxa3__tp, CAdbPxa3_38_switch, CAdbPxa3_39_on, CAdbPxa3_40_hold

### Community 121 - "Adb module"
Cohesion: 0.50
Nodes (4): tag_SIBFS_PixelAnimationSequence__switching_animted_ON2_AdbPxa3__tp, CAdbPxa3_42_switch, CAdbPxa3_43_on, CAdbPxa3_44_hold

### Community 122 - "Adb module"
Cohesion: 0.50
Nodes (4): tag_SIBFS_PixelAnimationSequence__switching_animted_ON_AdbPxa3__tp, CAdbPxa3_34_switch, CAdbPxa3_35_on, CAdbPxa3_36_hold

### Community 123 - "Adb module"
Cohesion: 0.50
Nodes (4): sint32, tagISV_SLutDynG_1_0_tp, SLutDynG_1_BreakPoints, SLutDynG_1_Table

### Community 124 - "Adb module"
Cohesion: 0.50
Nodes (4): sint32, tagISV_SLutDyn_1_0_tp, SLutDyn_1_BreakPoints, SLutDyn_1_Table

### Community 127 - "Sigprep module"
Cohesion: 0.50
Nodes (4): uint16, SigPrep_RxCallbacks_HS6_DYN3_CMM_468(), SigPrep_RxCallbacks_STTConfigDetection(), SigPrepRx_GetConfigTime()

### Community 128 - "Adb module"
Cohesion: 0.67
Nodes (3): tag_SIBFS_ChartGetAnimationConfig3_AdbPxa3__tp, CAdbPxa3_8_ChartGetAnimationConfig3_ns, CAdbPxa3_8_glflag

### Community 129 - "Adb module"
Cohesion: 0.67
Nodes (3): tAdbActualShadowTL, tagISV_SPxlActMat_1_0_tp, CPxlActMat_1_ActualShadow

### Community 130 - "Adb module"
Cohesion: 0.67
Nodes (3): ISV_SIPI1_tp, tagISV_SPBI_1_tp, pISV_SIPI1_tp

### Community 131 - "Adb module"
Cohesion: 0.67
Nodes (3): uint8, tagISV_SIPI1_0_tp, SIPI1_Prelookup_NumAxisPts

### Community 132 - "Adb module"
Cohesion: 0.67
Nodes (3): tagISV_SIPI1_tp, pISV_SIPI1_0_tp, ISV_SIPI1_0_tp

### Community 133 - "Adb module"
Cohesion: 0.67
Nodes (3): uint8, tagISV_SLutDynG_1_1_tp, SLutDynG_1_Prelookup_NumAxisPts

### Community 135 - "LOCAL module"
Cohesion: 0.67
Nodes (3): LOCAL_INLINE, sint8, SigPrep_RxCallbacks_RangeCheck_PerceiveAzimuthRate()

## Knowledge Gaps
- **163 isolated node(s):** `Aux_CAdbPxa3_16_sflag1`, `CAdbPxa3_17_ON`, `CAdbPxa3_18_switchingOFF`, `CAdbPxa3_19_switchingON`, `CAdbPxa3_20_OFF` (+158 more)
  These have ≤1 connection - possible missing edges or undocumented components.
- **2 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `tagISV_SNoObjRst_TSAG_1_tp` connect `Adb module` to `Adb module`, `Adb module`, `Adb module`?**
  _High betweenness centrality (0.036) - this node is a cross-community bridge._
- **Why does `AdbPxa3Main()` connect `Adb module` to `Adb module`, `Adb module`, `Adb module`, `Adb module`, `Adb module`, `Adb module`?**
  _High betweenness centrality (0.026) - this node is a cross-community bridge._
- **Why does `AdbMxb4_Cycle0()` connect `Adb module` to `Adb module`, `Adb module`, `Adb module`?**
  _High betweenness centrality (0.024) - this node is a cross-community bridge._
- **What connects `Aux_CAdbPxa3_16_sflag1`, `CAdbPxa3_17_ON`, `CAdbPxa3_18_switchingOFF` to the rest of the system?**
  _163 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Adb module` be split into smaller, more focused modules?**
  _Cohesion score 0.052497451580020386 - nodes in this community are weakly interconnected._
- **Should `Pitch module` be split into smaller, more focused modules?**
  _Cohesion score 0.0522466039707419 - nodes in this community are weakly interconnected._
- **Should `Sigprep module` be split into smaller, more focused modules?**
  _Cohesion score 0.025490196078431372 - nodes in this community are weakly interconnected._