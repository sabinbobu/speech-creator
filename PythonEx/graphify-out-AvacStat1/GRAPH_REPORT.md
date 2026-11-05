# Graph Report - AvacStat1  (2026-09-24)

## Corpus Check
- Corpus is ~5,133 words - fits in a single context window. You may not need a graph.

## Summary
- 93 nodes · 212 edges · 9 communities (8 shown, 1 thin omitted)
- Extraction: 73% EXTRACTED · 27% INFERRED · 0% AMBIGUOUS · INFERRED: 57 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Community Hubs (Navigation)
- Cyclic Runnable + Pitch/Output NVM Access
- Core Module (AvacStat1) + Filter Utility & Shared Includes
- Coding Parameter Validation (Rte-fed)
- Init + CodM Coding Module Access
- Speed Mode & Level Phase Logic
- Headlight Angle & Timing Coding Params
- Regulation Mode & Dynamic Speed-Limit Coding Params
- Static Filter Parameter Coding Params
- AvacStat1Init + NvM Driver Dependency

## God Nodes (most connected - your core abstractions)
1. `AvacStat1_Cycle0()` - 20 edges
2. `AvacStat1_GetHeadlightAngle()` - 18 edges
3. `AvacStat1_SetRegMode()` - 15 edges
4. `AvacStat1_Init()` - 11 edges
5. `AvacStat1_SetStaticFilterParameters()` - 7 edges
6. `AvacStat1_SetSpeedMode()` - 7 edges
7. `Std_Types (AUTOSAR Standard Types)` - 7 edges
8. `AvacStat1Data_CodingDataValidation()` - 6 edges
9. `Cod_AvacStat1_SampleTimeShort()` - 6 edges
10. `AvacStat1Util_Order1Filter()` - 6 edges

## Surprising Connections (you probably didn't know these)
- `riAvacStat1_Init()` --calls--> `AvacStat1_Init()`  [INFERRED]
  ctaaAvacStat1.c → AvacStat1.c
- `AvacStat1_SetRegMode()` --calls--> `Cod_AvacStat1_LoadChangeInterval()`  [INFERRED]
  AvacStat1.c → AvacStat1Data.h
- `AvacStat1_SetRegMode()` --calls--> `Cod_AvacStat1_SampleTimeLong()`  [INFERRED]
  AvacStat1.c → AvacStat1Data.h
- `AvacStat1_SetRegMode()` --calls--> `Cod_AvacStat1_SampleTimeShort()`  [INFERRED]
  AvacStat1.c → AvacStat1Data.h
- `AvacStat1_SetRegMode()` --calls--> `AvacStat1Util_Order1Filter()`  [INFERRED]
  AvacStat1.c → AvacStat1Util.c

## Import Cycles
- None detected.

## Communities (9 total, 1 thin omitted)

### Community 0 - "Cyclic Runnable + Pitch/Output NVM Access"
Cohesion: 0.11
Nodes (17): AvacStat1_Cycle0(), AvacStat1Data_ReadPitch(), AvacStat1Data_WriteAvacOut(), Cod_AvacSafetyAngle(), Cod_AvacStat1_FilterCoefToUnlock(), sint16, uint16, NvmGet_AvacStat1_AdjCounter() (+9 more)

### Community 1 - "Core Module (AvacStat1) + Filter Utility & Shared Includes"
Cohesion: 0.21
Nodes (11): AvacStat1Util_Order1Filter(), AvacStat1Util_Order1FilterInit(), AvacStat1Util_Order1FilterValue(), sint16, uint16, ORDER1_Filter, Cfg.h (App Configuration Header), RteCommonTypes.h (Shared RTE Type Definitions) (+3 more)

### Community 2 - "Coding Parameter Validation (Rte-fed)"
Cohesion: 0.20
Nodes (12): AvacStat1Data_CodingDataValidation(), AvacStat1Data_Get_CodingPara(), AvacStat1Data_GetAvacS_En(), AvacStat1Data_GetAvacS_Ok(), AvacStat1Data_GetLowBeamOn(), AvacStat1Data_ParaFct0(), STATIC_AL, boolean (+4 more)

### Community 3 - "Init + CodM Coding Module Access"
Cohesion: 0.29
Nodes (9): AvacStat1_Init(), Cod_AvacStat1_DynamicMinChange(), Cod_AvacStat1_LoadChangeInterval(), Cod_AvacStat1_SafetyAngle(), Cod_AvacStat1_SampleTimeLong(), Cod_AvacStat1_StaticFilterCoefAtZeroSpeed(), NvmGet_AvacStat1_HeadlightAngle(), CodM (Coding Module SWC) (+1 more)

### Community 4 - "Speed Mode & Level Phase Logic"
Cohesion: 0.22
Nodes (9): AvacStat1_CheckZeroLvl(), AvacStat1_SetSpeedMode(), STATIC_AL, AvacStat1Data_ReadAslPhase(), AvacStat1Data_ReadSpeed(), AvacStat1Data_WriteSpeedMode(), tAvacStat_Speed, teAvacStat1_LvlPhase (+1 more)

### Community 5 - "Headlight Angle & Timing Coding Params"
Cohesion: 0.33
Nodes (9): AvacStat1_GetHeadlightAngle(), AvacStat1Data_GetCodingValid(), Cod_AvacLoadChangeInterval(), Cod_AvacStat1_InterStopMinChange(), Cod_AvacStat1_PowerOnMinChange(), Cod_AvacStat1_StaticFilterCoefAtInterStop(), Cod_AvacStat1_StaticMinChange(), Cod_AvacStat1_TransientStatePeriod() (+1 more)

### Community 6 - "Regulation Mode & Dynamic Speed-Limit Coding Params"
Cohesion: 0.25
Nodes (8): AvacStat1_SetRegMode(), sint16, Cod_AvacStat1_AccFilterCoeff(), Cod_AvacStat1_FrozenVehSpeed(), Cod_AvacStat1_HighDynamicLimit(), Cod_AvacStat1_HighFrozenVehSpeed(), Cod_AvacStat1_MaxSpeed(), uint8

### Community 7 - "Static Filter Parameter Coding Params"
Cohesion: 0.40
Nodes (5): AvacStat1_SetStaticFilterParameters(), Cod_AvacStat1_ConstantSpeedInterval(), Cod_AvacStat1_FilterCoefInc(), Cod_AvacStat1_SampleTimeShort(), Cod_AvacStat1_StaticFilterCoefAtConstSpeed()

## Knowledge Gaps
- **5 isolated node(s):** `Cfg.h (App Configuration Header)`, `RteCommonTypes.h (Shared RTE Type Definitions)`, `CodM (Coding Module SWC)`, `CodM_Para (Coding Parameter Table)`, `UtilUtility (ALUnit Lib - General Utility Functions)`
  These have ≤1 connection - possible missing edges or undocumented components.
- **1 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `AvacStat1_Cycle0()` connect `Cyclic Runnable + Pitch/Output NVM Access` to `Core Module (AvacStat1) + Filter Utility & Shared Includes`, `Coding Parameter Validation (Rte-fed)`, `Init + CodM Coding Module Access`, `Speed Mode & Level Phase Logic`, `Headlight Angle & Timing Coding Params`, `Regulation Mode & Dynamic Speed-Limit Coding Params`?**
  _High betweenness centrality (0.197) - this node is a cross-community bridge._
- **Why does `AvacStat1_GetHeadlightAngle()` connect `Headlight Angle & Timing Coding Params` to `Cyclic Runnable + Pitch/Output NVM Access`, `Core Module (AvacStat1) + Filter Utility & Shared Includes`, `Coding Parameter Validation (Rte-fed)`, `Init + CodM Coding Module Access`, `Speed Mode & Level Phase Logic`, `Static Filter Parameter Coding Params`?**
  _High betweenness centrality (0.108) - this node is a cross-community bridge._
- **Why does `AvacStat1_SetRegMode()` connect `Regulation Mode & Dynamic Speed-Limit Coding Params` to `Cyclic Runnable + Pitch/Output NVM Access`, `Core Module (AvacStat1) + Filter Utility & Shared Includes`, `Init + CodM Coding Module Access`, `Speed Mode & Level Phase Logic`, `Static Filter Parameter Coding Params`?**
  _High betweenness centrality (0.105) - this node is a cross-community bridge._
- **Are the 15 inferred relationships involving `AvacStat1_Cycle0()` (e.g. with `AvacStat1Data_CodingDataValidation()` and `AvacStat1Data_GetAvacS_En()`) actually correct?**
  _`AvacStat1_Cycle0()` has 15 INFERRED edges - model-reasoned connections that need verification._
- **Are the 14 inferred relationships involving `AvacStat1_GetHeadlightAngle()` (e.g. with `AvacStat1Data_GetLowBeamOn()` and `Cod_AvacStat1_ConstantSpeedInterval()`) actually correct?**
  _`AvacStat1_GetHeadlightAngle()` has 14 INFERRED edges - model-reasoned connections that need verification._
- **Are the 10 inferred relationships involving `AvacStat1_SetRegMode()` (e.g. with `Cod_AvacStat1_AccFilterCoeff()` and `Cod_AvacStat1_FrozenVehSpeed()`) actually correct?**
  _`AvacStat1_SetRegMode()` has 10 INFERRED edges - model-reasoned connections that need verification._
- **Are the 10 inferred relationships involving `AvacStat1_Init()` (e.g. with `AvacStat1Data_CodingDataValidation()` and `Cod_AvacStat1_ConstantSpeedInterval()`) actually correct?**
  _`AvacStat1_Init()` has 10 INFERRED edges - model-reasoned connections that need verification._