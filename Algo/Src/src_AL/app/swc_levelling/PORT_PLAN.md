# PORT_PLAN — ASL levelling chain DPE (ECO) → ILCU

Paths: DPE_ROOT = `/Users/bobus/Module_Porting/DPE/Src/Src_AL`, ILCU_ROOT = `/Users/bobus/Module_Porting/ILCU/Src`.
TARGET_FOLDER = `src_AL/app/swc_levelling/`. CddDcm: `src_AL/cdd/CddDcm/` (amended, see Q2).

**Decisions (from Q&A):**
- **Q1:** the phase is forced via adapter inputs; CtrlDcm is untouched.
- **Q2:** one folder, `src_AL/app/swc_levelling`. *Amended 2026-11-06 on request: CddDcm moved to ILCU's CDD folder `src_AL/cdd/CddDcm/` (`Api/`, `Gen/`, `Cfg/`, `Make/`); see PORT_CHANGES.md §10.*
- **Q3:** DPE logic is left as-is even where it warns; those warnings are reported as pre-existing, so "no new warnings" is knowingly not met for DPE-inherited code.
- **Q4:** snapshot only: host clang check + host harness here; you run the Keil build.

## 0. Context
ILCU is a levelling demo (MSPM0G3518, Keil armclang, hand-written RTE). Port AvacStat1 → CtrlDcm → CddDcm from DPE ECO. In ILCU an IMU replaces DPE's 2-height-sensor `Pitch`. This file is the Phase-1 deliverable; no code is written before approval.

## 1. Findings that change the brief (read first)

| # | Finding | Evidence | Consequence |
|---|---|---|---|
| F1 | **The Init/Adj/Fail phase machine is in CtrlDcm, not AvacStat1.** AvacStat1 only *reads* the phase to derive a "speed mode" output. | `CtrlDcmSm.c:140-216` (tables), `:552-651` (transitions), `:807-830` (StMch); AvacStat1 reads it at `AvacStat1Data.c:315-326`, `AvacStat1.c:901-931` | Contradiction resolved (Q1): CtrlDcm is unchanged and forced into Adj by adapter inputs (§4) |
| F2 | **ILCU cannot be built in this workspace.** No `Build/` tree (Make_000.gmk, CustVar_*.gmk, Build.bat), `Src_ThirdParty/` is empty (TI MCAL: Std_Types/Platform_Types/Compiler/Pwm/Dio/Adc; RTX), and Keil is Windows-only. | `src_ThirdParty/placeholder.txt` only; `BuildSystem.md:11-29`; no `Build` dir anywhere under `Module_Porting` | Done-criterion "ILCU builds" can only be confirmed by your Keil run; here: host clang check + harness (§10) |
| F3 | **CddDcm's output-stage maths is DPE hardware.** It drives LWR as a ‰ ratio of KL15 (150–850 ‰), with divisor 3.485 × 4970 mV. ILCU's stage gives ≈ D × 3.05 V absolute (RC 10/56.4 × gain 5.21). | `CddDcmHal.c:146-154`, `CddDcmCtrl.h:36-49`; `Al077HardwareSchematic.md:129-138` | It compiles and runs, but the commanded level will saturate on ILCU HW. Not changed (CddDcm logic is frozen) → listed as NOT REAL |
| F4 | **DPE coding defaults disable standstill levelling.** `ASL_FROZEN_VEH_SPEED = ASL_HIGH_FROZEN_VEH_SPEED = 0` → with speed 0 AvacStat1 sits in `Below_Min_Speed` and never adjusts. The production values (2 / 5 km/h) exist only as comments. | `CodM_Para_AvacStp.h:389-411`; `AvacStat1Data.h:80-81`; `AvacStat1.c:341-344` | Adapter coding stub uses 2 / 5 (from those comments) → stub |
| F5 | **An IMU SWC already exists.** `swc_imu` computes `Pitch_cdeg` (0.01°, accelerometer atan2) but publishes it only to CAN (no read-back port). | `src_AL/app/swc_imu/swc_imu.c:130-132`; `src_AL/rte/Rte.c:137-154` | Per brief: pitch is a stub in the adapter. Plug-in later = convert cdeg → 0.1 mrad (× 1.745) and check the sign (DPE: front up = positive) |
| F6 | **DPE snapshot lacks the ALUnit libs** (`UtilUtility.h`, `UtilMath.h`, `Util_Time.h`, `AL_Helper.h`) and `_NM_Types.h`. ILCU doesn't have them either. | `find` in both trees: absent | Minimal re-definitions in the adapter, semantics derived from usage → UNVERIFIED vs originals |
| F7 | **Al077a IoHwAb analog config disagrees with the schematic.** VBAT: ADC0 ch4 vs schematic KL15 on ADC0 ch5. LWR_FB scaling: 82.5k/21k vs schematic 82.5k/15k. | `config_AL/Al/Al077a/bsw/IoHwAb/IoHwAb_AnalogCfg.c:91-100,251-260`; `Al077HardwareSchematic.md:118-125` | If VBAT reads wrong, CddDcm locks the motor (window 8.59–17.69 V, `CddDcmCtrl.c:590`) → [verify on HW] |

## 2. Files to copy (COPY only; DPE is read-only)

Target layout under `ILCU_ROOT/src_AL/app/swc_levelling/`, except CddDcm under `ILCU_ROOT/src_AL/cdd/CddDcm/` (amended, Q2). All basenames are unique in ILCU (checked):

| Module | DPE source → target subfolder | Files |
|---|---|---|
| AvacStat1 | `Cust/St/St126/App/Swc/AfsMaster/AvacStat1/` → `AvacStat1/` | AvacStat1.c/.h, AvacStat1Data.c/.h, AvacStat1Init.c/.h, AvacStat1Types.h, AvacStat1Util.c/.h, ctaaAvacStat1.c/.h (11) |
| CtrlDcm | `Cust/St/St126/App/Swc/Ctrl/Dcm/` → `CtrlDcm/` | Api/CtrlDcm.h, CtrlDcm.c, CtrlDcmSm.c/.h, CtrlDcm_Data.c/.h, CtrlDcm_RteAccess.c/.h, ctaaCtrlDcm.c/.h (10) |
| CddDcm | `Cdd/CddDcm/Gen/` → `src_AL/cdd/CddDcm/Api/` (CddDcm.h) and `Gen/` (the rest); `Cust/St/St126/Cdd/CddDcm/` → `src_AL/cdd/CddDcm/Cfg/` (amended, Q2) | CddDcm.h, CddDcmCtrl.c/.h, CddDcmHal.c/.h, Cfg/CddDcm_Cfg.h (6) |

**Not copied:**
- `CddDcm/S32K/*` and `CddDcm/PC/*`: empty S32K/PC stubs, and ILCU is MSPM0.
- `CddDcm/Stubs/CddDcm_Stubs.c`: 0 bytes.
- `CddDcm/Make/*.gmk`: DPE make layout.
- Unit tests `Test/Mt_AvacStat1`, `Mt_CtrlDcm`, `CddDcm/Test`: DPE test framework.
- `Pitch/*` and every other DPE module.

**New files:**
- `ILCU_LevellingAdapter.c/.h`
- `Make/IlcuLevelling_030_Flags.gmk` and `Make/IlcuLevelling_050_Files.gmk` (same pattern as `src_AL/cdd/CddAsm330lhh/Make/`)
- `PORT_PLAN.md` (this file)
- `PORT_CHANGES.md`

## 3. External dependencies and handling
Rule:
- Ported call sites keep their DPE names.
- The adapter implements every DPE-only symbol under its original name.
- Only names that collide with real ILCU/AUTOSAR symbols (`NvM_WriteBlock`, `Pwm_*`) are renamed at the call site to `ILCU_LvlAdp_*`.
- All DPE-only `#include`s are replaced by `#include "ILCU_LevellingAdapter.h"`. This is mandatory: on Windows `<Nvm.h>` would silently resolve to ILCU's `NvM.h`.

### 3.1 Chain-internal RTE ports → adapter (static buffers = mini-RTE)
| Port | Producer → consumer | Handling |
|---|---|---|
| `Rte_Write/Read_ppsAvacStat1Out_Port` (tPositionOut) | AvacStat1 → CtrlDcm | adapter buffer |
| `Rte_Write/Read_ppCtrlDcmTarget0_DcmTargetValues` | CtrlDcm → CddDcm | adapter buffer |
| `Rte_Write/Read_CddDcm_ErrorStatus` | CddDcm → CtrlDcm | adapter buffer, passed through (real short-circuit detection stays live) |
| `Rte_Write/Read_CtrlDcm_StatusParameters_Port` | CtrlDcm → AvacStat1 (phase mirror) | adapter buffer; the AvacStat1 reader is removed (§4) |
| `Rte_Read/Write_DcmState0_Port`, `DcmPos0_Port` | CddDcm blackboard (read-modify-write) | adapter buffer |
| `Rte_Read/Write_CtrlDcm_MasterCommand`, `DrvLedDiag`, `DrvLedDiagR` | CtrlDcm → CAN (L/R ECU) | adapter buffer (no CAN in ILCU) |

### 3.2 Pitch-provided signals (Pitch NOT ported)
| Signal | Consumer | Handling |
|---|---|---|
| `Rte_Read_Pitch_Angle` (tPitch0: nAngle [0.1 mrad], nHeightErr, eSigQty) | AvacStat1 `AvacStat1Data.c:218` | adapter calls `ILCU_LevellingAdapter_GetPitchAngle(sint16*)`. **STUB**: returns E_OK + fixed `ILCU_LVLADP_STUB_PITCH_0P1MRAD` (0). E_OK→SIG_VALID, else SIG_INVALID; nHeightErr = 0 |
| `Rte_Read_Pitch_PlausState` (teRte_HlsSensorState) | CtrlDcm `CtrlDcm_RteAccess.c:263` | **STUB** eNO_FAILURE |
| `NvmBlockDeltaPwmPara` (Pitch/Diag-owned NvM: ucZeroLevProg, eNVM_VAC_Input, snVehicleAttitude, eASL_Present) | AvacStat1, CtrlDcm | adapter RAM block. **STUB** ucZeroLevProg = 0xFF ("zero-level programmed" → CtrlDcm TrainingState TRUE) |

### 3.3 Vehicle / environment signals (absent in ILCU) → adapter STUB constants
| Port | Stub value | Why this value |
|---|---|---|
| `Rte_Read_SysMon_VehicleSpeed` | speed 0, SpeedInfoAvailable, SIG_VALID | standstill; VALID avoids CtrlDcm func-fault (`CtrlDcm_RteAccess.c:75-83`) |
| `Rte_Read_SigPrep_DynamicSigs` | pedal/acc 0, SIG_VALID | no dynamics |
| `Rte_Read_SysMon_VehNetState` | VESState_Ignition, eTA_NOMINAL, SIG_VALID | ignition on + powertrain active |
| `Rte_Read_SigPrep_VehicleConfigSig` | eModeConfigVehicle_Client, SIG_VALID | Customer mode → ASL Available |
| `Rte_Read_IoHwAbUser_GetMountingSide` | eMountedLeft | single ECU = master; also `Position[0]` index |
| `Rte_Read_SigPrep_DcmDiagStatusR` | eDiagLvl_Ok, SIG_VALID | no right-side ECU |
| `Rte_Read_SigPrep_LevellingTgtPos` | SIG_VALID, 0 | slave-only path (unreachable) |
| `Rte_Read/Write_Dcm_RoutineControl` | buffer, boRequestStatus FALSE | no UDS routine → no takeover |
| `Rte_Read_CodM_Pitch_Para` (coding; provider is CodM) | {CodingDataValid, &const block} | see §3.6 |

### 3.4 BSW / platform
| DPE dependency | ILCU status | Handling |
|---|---|---|
| NvM: 5 blocks + `NvM_WriteBlock` at `AvacStat1.c:831,854`, `AvacStat1Data.h:111`, `CddDcmCtrl.c:215` | NvM exists, but adding blocks means editing ILCU NvM config (forbidden) | **STUB**: RAM blocks initialised from DPE defaults (`AvacStat1Init.c:32-50`, `CddDcmCtrl.c:60`); call sites renamed to `ILCU_LvlAdp_NvM_WriteBlock` (returns E_OK, no persistence) |
| Dem: `Rte_Call_DemPrj_ReportErrorStatus` (ZERO_LVL_PROG `AvacStat1.c:169,173`; DCMotor_SC_GND/BAT `CddDcmCtrl.c:816-908`) | no Dem in ILCU | **STUB**: stores last status per event (debug visible), returns E_OK |
| Det | not used by the 3 modules | — |
| PWM: `Pwm_SetDutyCycle` ×2, `Pwm_StartPwmChannel`, `Pwm_ClampPwmChannel` (`CddDcmHal.c:270,377,379,388`), ch 5 | TI MCAL; LWR = `PWM_TIMG_CHANNEL17` via `IOHWAB_CHID_CTRL_LWR` | **ADAPTER**: rename sites → `ILCU_LvlAdp_LwrPwm*`, which call `IoHwAb_TimingSetDutyCycle/StopActuation(IOHWAB_CHID_CTRL_LWR)`. Converts 0x8000-scale → 0..1000 ‰ with rounding (lossless; `IoHwAb_Timing.c:34-36`) |
| `IoHwAb_User_SetDio_EN_DC` (`CddDcmHal.c:204`) | `IoHwAb_DiscreteEN_LWR_Write` (PA3) | **ADAPTER** (same DPE name) |
| `IoHwAbUser_GetAdc_VoltDC_OUT1` (`CddDcmHal.c:215`) | `IoHwAb_AnalogReadConverted(IOHWAB_CHID_ADIN_3)` (ADC1 ch0 = LWR_FB) | **ADAPTER** [verify scaling, F7] |
| `Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT` (`CddDcmHal.c:227`, `CddDcmCtrl.c:588`) | `IoHwAb_VoltageKL30_Read` | **ADAPTER** [verify channel, F7] |
| `NM_GetMode`, `NM_ModeType`, `LIMP_HOME_MODE` (`CtrlDcm.c:781-798`) | no NM | **STUB**: never limp-home; `LIMP_HOME_MODE` value adapter-defined (DPE value unknown, only compared) |
| `TIMER`, `TimerGetTick`, `TimerGetTimeSince`, `UTILTIME_MSEC` (`CtrlDcm.c:373-457`) | absent | **ADAPTER**: µs counter advanced 5000 per 5 ms MainFunction call |
| `SysLoad.h` (`ctaaCtrlDcm.c:18`) | absent | include replaced; `SYS_LOAD_RUNNABLE` undefined → compiled out |

### 3.5 Includes and shared types → COPY (subset) into the adapter header
- **Headers replaced by the adapter:** `Rte.h`, `RteCommonTypes.h`, `Cfg/Cfg.h`, `Nvm.h`, `Bsw/NvM/NvM_Para.h`, `Swc/CodM/CodM.h`, `CodM_Para.h`, `CodM_Para_AvacStp.h`, `UtilUtility.h`, `UtilMath.h`, `Util_Time.h`, `AL_Helper.h`, `_NM_Types.h`, `IoHwAbUser.h`, `Pwm.h`, `Bsw/Sys/Load/SysLoad.h`.
- **Kept as-is:** `Std_Types.h` (ILCU/TI MCAL), `stdlib.h`, `stdbool.h` (DPE uses `bool/true/false`).
- **Types (copied into the adapter):** exact field subsets, with enums copied verbatim so numeric semantics are preserved.
  - teRte_SigQty, tPitch0, tsRte_SysMon_VehicleSpeed (+tsVitesseVehiculesRoues, teVvhIndisp), tsRte_SigPrep_DynamicSigs (+tsRte_EfcmntPdleAccel), tPositionOut (+tAfsAngle), teRte_DcmSpeedMode, tsRte_CtrlDcmStatusParams (+eDcmMode/eDcmPhase), tsRteCodingParameters, tParaFct0_Cmd, teRte_MountingSide, tsRte_SysMon_VehNetState (+VESState_*, eTA_*/eDEMARRAGE/eInvalid), tsRte_SigPrep_VehicleConfigSig (+eModeConfigVehicle_*, teRte_EtatMar), teRte_HlsSensorState, tsRte_DcmStatusError, tsRte_LevellingTgtPos (+sign, ref and position types), DrvLed 457/477, tsRte_DcmDiagStatusR, teDiagLvl, tsRte_CtrlDcmTarget, tsRte_DcMotorRoutineControl (+4 enums), tiu32Voltage_mV.
  - **Copied byte-exact** because the code writes `.Bit` and reads `.Val` through a union (`CddDcmCtrl.c:568,506`): the unions `tDcmStateMsg` and `tDcmCtrlMsg`, plus their bitfield structs.
  - **NvM types:** tisStatAvacPrj1Para, tisStatAvac1Para, tisStatAvacOp1Data, tDcMotorDataStruct, tDcMotorCharacteristicStruct, tisNvmDeltaPwmPara (reduced to the 4 used fields), teVacInput, teAslInput.
  - **Coding types:** tNvmPara_AvacStp_DCMotorData (verbatim), tNvmPara_AvacStpBlock (reduced: DCMotorData only; PitchData belongs to Pitch), tNvmPara_CodingArea (reduced: AvacStp only), NVMPARA_AVACSTPBLOCK_INIT.
- **Macros (re-defined from usage, UNVERIFIED vs AL_Helper/Util originals):**
  - `STATIC_AL` → static, `CONST_AL` → const, `STATIC_UT(t,n,i)` → `static t n = i`
  - `UTIL_ABS/MIN/MAX/COUNTOF`; `ORDER1_Filter` → sint32 (as in DPE test stubs `Mt_Avac/Test_Stubs.h:34`)
  - `CFG_DEV_HOOK_EN 0u`, `CFG_VARIANT_ECO`, `CFG_OPT_ENVCOND 0U`, `CFG_EnvCond_SuppLoBmOnRq`

### 3.6 Calibration parameters
| Group | Source | Handling |
|---|---|---|
| AvacStat1 NvM "Para" blocks (filter coefs, sample times, min-change thresholds, LoadChangeInterval = 100 × 100 ms, MaxSpeed …) | DPE NvM defaults `AvacStat1Init.c:32-50` (ported file) | copied with the module; adapter RAM blocks initialised from them |
| Coding `DCMotorData` (ucAsl_Enable = 1, Min/Max_ASL_Adjust_Left −300/0, Safety_Position_Left −32 …) | `NVMPARA_AVACSTP_DCMOTORDATA_INIT` | **STUB** const block in the adapter, verbatim **except** FROZEN = 2, HIGH_FROZEN = 5 (F4) |
| AvacStat1 constants (AVAC_SAFETY_POS −54, ControlFilterCoeff 123, angle clamp 0..875) | AvacStat1 sources | copied unchanged |
| CddDcm constants (pos range 150–850 ‰, min/max pos 200/800, threshold 5, hysteresis 30, error time 500 ms, VBAT window, HALDCM_DIV_VALUE, reverse polarity) | `CddDcmCtrl.h/.c`, `CddDcmHal.c`, `CddDcm_Cfg.h` | copied unchanged; DPE-HW-specific (F3) |

## 4. State machines: what exists, what is removed

**AvacStat1 contains no Init/Adj/Fail machine.** Its runtime structure:
1. **Coding gate.** Cycle0 does nothing until coding is valid (`AvacStat1.c:649,820`). The adapter coding is always valid, so it passes at Init.
2. **Downsampling.** 20 ms → 100 ms (`:685-692`).
3. **Input-quality request.** Normal / Freeze / NoDynamic, based on speed and pitch signal quality and AvacS_En/Ok (`:704-739`).
4. **Regulation-mode machine** `byLwrRegulationMode` (`SetRegMode :329-360`). Initial state is Zero_Speed.
   - Zero_Speed → Vehicle_Start: Speed > 100·Frozen
   - → Zero_Speed: Speed < 100·Frozen ∧ Transient = 0
   - → Transient_State: Speed < 100·Frozen ∧ Transient ≠ 0
   - → Below_Min_Speed: Speed ≤ 100·HighFrozen
   - → Acceleration: |Acc| ≥ 2·HighDynLimit
   - → Constant_Speed: |Acc| ≤ 2·HighDynLimit ∧ Transient = 0
   - → Transient_State: |Acc| ≤ 2·HighDynLimit ∧ Transient ≠ 0
   - The state actions in `GetHeadlightAngle :380-643` **are the adjustment algorithm, so all are kept verbatim.** With speed stub 0 and Frozen = 2, only **Zero_Speed** runs: power-on/light-on adjustment, then load-change adjustment when |Δpitch| > 1 mrad for 10 s.
5. **Phase mirror** `SetSpeedMode` (`:901-931`). It reads CtrlDcm Init/Adj/Fail → SpeedMode, whose only consumer is Pitch. → **REMOVED**, together with `AvacStat1Data_ReadAslPhase/WriteSpeedMode` and `teAvacStat1_LvlPhase`. This is the entire "AvacStat1 reduction".
6. **Kept:** the ZLP DTC check via the Dem stub, and the tester hook (compiled out, `CFG_DEV_HOOK_EN 0`).

**The real phase machine is in CtrlDcm** (`CtrlDcmSm.c`):
- Main mode: Assembly / Customer.
- ASL sub-mode: Unavailable / Available / Frozen / Factory.
- Phase (only when Available): Init → Adj, Init → Fail, Adj → Fail, Fail → Adj. Master and slave tables.
- Diag takeover.

**Chosen (Q1).** CtrlDcm is unchanged. The adapter's constant inputs (§3.3) make it go Customer → Available → Init → Adj on CtrlDcm cycles 1–3 (60 ms) and stay in Adj. Fail is reachable only by two genuine faults:
- (a) the pitch source returns E_NOT_OK, so AvacStat1 output is INVALID → CtrlDcm goes to safety position (latched, "ignition needed");
- (b) CddDcm detects the LWR output shorted to GND/BAT for ≥ 2 s.

Assembly/Factory/Frozen, the slave machine and diag takeover stay in the code, unreachable.

## 5. Edits to copied files (each marked `/* ILCU_PORT: <reason> */`)
- **E1 Includes.** DPE-only headers → `"ILCU_LevellingAdapter.h"`; `<../App/Swc/Ctrl/Dcm/Api/CtrlDcm.h>`-style paths → flat names.
- **E2 Name collisions.** `NvM_WriteBlock` ×4 → `ILCU_LvlAdp_NvM_WriteBlock`; `Pwm_*` ×4 in CddDcmHal.c → `ILCU_LvlAdp_LwrPwmSetDuty/Start/ToIdle`.
- **E3 AvacStat1 reduction (§4.5).** Delete SetSpeedMode + its call (`AvacStat1.c:114,815,892-931`), `AvacStat1Data.c:282-326`, `AvacStat1Data.h:46-51,67,69`.
- **E4 Toolchain (build correctness, not a warning fix).** `AvacStat1Data.h` `INLINE` → `STATIC INLINE`.
  - ILCU's INLINE is non-static: `Os_Wrapper.c:134` writes `STATIC INLINE`, which would not compile if INLINE already contained static.
  - Non-static inline functions defined in a header have no external definition, so with `-fno-inline-functions` they can cause link errors.
  - Applied only if the compile check confirms the hazard (otherwise skipped and noted).
- **No E5 (Q3).** DPE-inherited warnings are left in the code and listed in PORT_CHANGES.md as pre-existing (§8).
- CtrlDcm/CddDcm logic: **no change** beyond E1/E2.

## 6. Adapter API (ILCU-facing)
```c
void           ILCU_LevellingAdapter_Init(void);          /* after IoHwAb_Init; NvM RAM defaults, then riAvacStat1_Init, riCddDcm_Init, riCtrlDcm_Init (DPE order) */
void           ILCU_LevellingAdapter_MainFunction(void);  /* every 5 ms: timer +5000 us; every 4th call AvacStat1 + CtrlDcm (20 ms); every call CddDcm (5 ms, DPE Rte_Cfg.c slots) */
Std_ReturnType ILCU_LevellingAdapter_GetPitchAngle(sint16* Pitch_0p1mrad); /* STUB: IMU plug-in point; front up = positive */
```
**Not hooked into `src_AL/rte/Rte.c`** (hard boundary #3: existing ILCU file). Until it is hooked, the linker (`--remove`, LTO) drops the chain. PORT_CHANGES.md will give the exact 2 lines: Init in `Rte_Start()` and MainFunction after `IoHwAb_MainFunction()` in `TASK(BasicTask)`, which runs at 5 ms (`Rte.c:79` + `RTX_Config.h:43`).

## 7. Build configuration
- **New** `Make/IlcuLevelling_030_Flags.gmk` (`C_INCLUDES_ILCULEVELLING`: target folder, AvacStat1, CtrlDcm, CtrlDcm/Api, IoHwAb `internal/`) and `Make/IlcuLevelling_050_Files.gmk` (`FILES_SRC_ILCULEVELLING`: 11 sources without extension).
- **New (amended, Q2)** `src_AL/cdd/CddDcm/Make/CddDcm_030_Flags.gmk` (`C_INCLUDES_CDDDCM`: Api, Gen, Cfg) and `CddDcm_050_Files.gmk` (`FILES_SRC_CDDDCM`: 2 sources). Both fragment pairs are wired together.
- **Existing ILCU build files:** none in this workspace (`Build/` absent). PORT_CHANGES.md lists the exact `include` + list-append lines for `CustVar_030_Flags.gmk` and `CustVar_050_Files.gmk`, mirroring how CddAsm330lhh is wired. UNVERIFIED until you apply and build.

## 8. DPE defects carried over unchanged (reported, not fixed)
- `AvacStat1.c:765-766` `NvmSet_AvacStat1_AdjCounter(unCnt++)` passes the old value, so the adjustment counter never increments.
- `CddDcmCtrl.c:841-842` sets `boElecGND = FALSE` twice; `boElecBAT` is not cleared in that branch.
- `CtrlDcm_RteAccess.c:67-161` ReadSpeed/ReadVehicleElectricState/ReadVESMainState, and `CtrlDcmSm.c:865-916,1277-1304` HandleFailState(_Slave): "keep previous value" on non-static locals → undefined behaviour on non-VALID/no-fault paths. These paths are unreachable with the adapter's VALID stubs, except HandleFailState after fault recovery.
- **Warnings these files are predicted to raise under clang -Wall (left as-is, Q3):**
  - unused locals `CtrlDcm.c:200,223`, `AvacStat1Data.c:215`;
  - statics used only by `#if 0` code `CtrlDcm.c:64,72,74,76,102`, `CtrlDcm_Data.c:40`;
  - `-Wsometimes-uninitialized` in the functions above;
  - `-Wbraced-scalar-init` at `CtrlDcm.c:781`.
  - The exact list comes from the compile check and goes verbatim into PORT_CHANGES.md.

## 9. Execution order (after approval)
0. Write SHA manifests of DPE and ILCU (scratchpad) → proves DPE untouched and no existing ILCU file changed.
1. Write `PORT_PLAN.md` (this file) into the target folder.
2. `cp` the 27 files.
3. Write the adapter .h/.c.
4. Apply E1–E5.
5. Write the gmk fragments.
6. Verify (§10).
7. Write `PORT_CHANGES.md`: every added file, every modified line group, every stub/NOT-REAL item, the open [verify] items F3/F7, and the CustVar + Rte.c hook lines.

## 10. Verification
1. **Host compile check (scratchpad only, nothing added to ILCU).** Apple clang `--target=thumbv6m-none-eabi -mcpu=cortex-m0plus -std=gnu17 -fshort-enums -ffreestanding -Os -Wall -fsyntax-only` on all 13 .c files.
   - Uses the real ILCU IoHwAb/Pwm_Cfg/Dio_Cfg headers, with minimal shims only for the absent TI MCAL headers.
   - Gate: 0 warnings in `ILCU_LevellingAdapter.c/.h` and on every `ILCU_PORT`-edited line. DPE-inherited warnings are captured verbatim and reported (Q3). `-Wextra` findings are reported as information.
   - armclang is LLVM-based, but this is NOT the Keil build.
2. **Host behaviour harness (scratchpad).**
   - Build the chain natively with IoHwAb fakes and run 30 s of simulated 5 ms ticks.
   - Assert CtrlDcm phase = Adj within ≤ 3 CtrlDcm cycles and never leaves it with healthy stubs.
   - Assert the CtrlDcm target follows the stub angle, and EN_LWR/PWM get driven.
   - Assert that a pitch E_NOT_OK drives Fail → safety position.
3. **Manifest diff.** DPE unchanged; ILCU: only new files.
4. **Real build (you):** `Build.bat H00 MSPM0G_3519 ARM_KEIL … Al077 App default NonKey rebuild`, then grep the log for `error|warning` in `swc_levelling` and check the hex timestamp (`BuildSystem.md:19-24`).
