# PORT_CHANGES — ASL levelling chain DPE (ECO) → ILCU

Companion to `PORT_PLAN.md`. Lists every file added or modified, every stub (what is **not real yet**), and the verification evidence.
Paths are relative to `ILCU/Src/src_AL/app/swc_levelling/` unless stated. CddDcm lives in `ILCU/Src/src_AL/cdd/CddDcm/` (moved there after the port, §10).

## 1. Status at a glance

| Done-criterion | Status |
|---|---|
| **ILCU builds with the new files** | **UNVERIFIED.** The ILCU `Build/` tree and `Src_ThirdParty/` (TI MCAL, RTX) are not in this workspace, and Keil is Windows-only. Substitutes run here: host clang compile check with armclang-like flags (0 errors) and a native link at -O0/-O2. You run the real build (§8). |
| **No new warnings in the ported code** | **Met for all ILCU-introduced code** (adapter + every `ILCU_PORT` line: 0 warnings). **Knowingly not met for DPE-inherited code** (decision Q3): 20 `-Wall` warnings in unchanged DPE lines (§6). |
| **DPE untouched** | **Verified.** SHA-256 manifest of all 1712 DPE files identical before/after. |
| **Existing ILCU files untouched** | **Verified.** SHA-256 manifest: 0 of 670 pre-existing ILCU files changed. 35 new files: 27 in this folder, 8 in `src_AL/cdd/CddDcm/`. |
| **Chain behaviour (Init → Adj permanently, adjustment drives CtrlDcm → CddDcm)** | **Verified on host** (harness, §7). Real hardware: not run. |

**Accepted by the owner (2026-11-06), after both open criteria were raised again:**
- (1) The host compile check plus native link/harness is accepted **in place of the Keil build**. No `Build/` tree, TI MCAL or armclang exists on this machine; `~/Job/speech-creator/Algo/Src` is the same snapshot.
- (2) The 20 DPE-inherited warnings stay **as-is** (Q3 reconfirmed; the fix set in §6.3/§6.4 was offered and declined).
- Both "Done when" items therefore remain formally open; the real Keil build is still the outstanding confirmation.

## 2. Files added (all new; no existing ILCU file modified)

| File | Origin |
|---|---|
| `AvacStat1/` 11 files | copied from DPE `Cust/St/St126/App/Swc/AfsMaster/AvacStat1/`, then edited (§4) |
| `CtrlDcm/` 10 files (incl. `Api/CtrlDcm.h`) | copied from DPE `Cust/St/St126/App/Swc/Ctrl/Dcm/`, then edited (§4) |
| `src_AL/cdd/CddDcm/`: `Api/CddDcm.h`, `Gen/` 4 files, `Cfg/CddDcm_Cfg.h` | copied from DPE `Cdd/CddDcm/Gen/` and `Cust/St/St126/Cdd/CddDcm/`, then edited (§4); moved here from this folder (§10) |
| `ILCU_LevellingAdapter.h/.c` | new: the only ILCU ↔ chain integration point |
| `Make/IlcuLevelling_030_Flags.gmk`, `Make/IlcuLevelling_050_Files.gmk` | new: include paths / 11 sources (CddAsm330lhh pattern) |
| `src_AL/cdd/CddDcm/Make/CddDcm_030_Flags.gmk`, `CddDcm_050_Files.gmk` | new: CddDcm include paths (`Api`, `Gen`, `Cfg`) / 2 sources |
| `PORT_PLAN.md`, `PORT_CHANGES.md` | documentation |

**Build configuration changes NOT applied (the files are not in this workspace).** Add them where the ILCU `Build/` tree lives, next to the existing CddAsm330lhh wiring. Variable names follow the CddAsm330lhh fragments. UNVERIFIED:
```make
# Build/Make/Cust/Al/Al077/App/CustVar_030_Flags.gmk
include $(PATH_SRC_CDD_BASE)/../app/swc_levelling/Make/IlcuLevelling_030_Flags.gmk
include $(PATH_SRC_CDD_BASE)/CddDcm/Make/CddDcm_030_Flags.gmk
C_INCLUDES := $(C_INCLUDES_ILCULEVELLING) $(C_INCLUDES_CDDDCM) $(C_INCLUDES)

# Build/Make/Cust/Al/Al077/App/CustVar_050_Files.gmk
include $(PATH_SRC_CDD_BASE)/../app/swc_levelling/Make/IlcuLevelling_050_Files.gmk
include $(PATH_SRC_CDD_BASE)/CddDcm/Make/CddDcm_050_Files.gmk
FILES_SRC_CUST += $(FILES_SRC_ILCULEVELLING)
FILES_SRC_CDD  += $(FILES_SRC_CDDDCM)
```
- Wire both fragment pairs together. CddDcm includes `ILCU_LevellingAdapter.h`, while CtrlDcm and the adapter include `CddDcm.h`.
- `IlcuLevelling_030_Flags.gmk` also adds `$(PATH_SRC_BSW)/IoHwAb/internal`, because the adapter calls `IoHwAb_Internals.h`.
- If `PATH_SRC_CDD_BASE` does not resolve to `Src/src_AL/cdd`, set `PATH_SRC_ILCULEVELLING` to this folder before the include.

**Scheduling hook NOT applied** (`src_AL/rte/Rte.c` is an existing ILCU file). Until it is added, the linker (`--remove`, LTO) drops the whole chain. Three lines:
```c
#include "ILCU_LevellingAdapter.h"          /* top of Rte.c */
ILCU_LevellingAdapter_Init();               /* in Rte_Start(); IoHwAb_Init already ran in EcuM_AL_DriverInitOne */
ILCU_LevellingAdapter_MainFunction();       /* in TASK(BasicTask) (5 ms), right after IoHwAb_MainFunction() */
```

## 3. Adapter: what it provides

| Group | Implementation |
|---|---|
| Scheduling | `Init`: NvM RAM defaults, then `riAvacStat1_Init`, `riCddDcm_Init`, `riCtrlDcm_Init` (DPE order). `MainFunction` (5 ms): CddDcm every call, AvacStat1 + CtrlDcm every 4th call (20 ms), as in DPE `Rte_Cfg.c`. |
| Pitch input | `ILCU_LevellingAdapter_GetPitchAngle(sint16* Pitch_0p1mrad)`: 0.1 mrad, front up = positive; E_NOT_OK = invalid. IMU plug-in: define `ILCU_LVLADP_EXTERNAL_PITCH_SOURCE` and implement the function in the IMU module. Neither ported code nor adapter changes. |
| Chain-internal RTE ports | static buffers: AvacStat1→CtrlDcm (`ppsAvacStat1Out`), CtrlDcm→CddDcm (`ppCtrlDcmTarget0`), CddDcm→CtrlDcm (`CddDcm_ErrorStatus`, passed through), CtrlDcm status (`ILCU_LvlAdp_CtrlDcmStatus`, debug-visible ASL mode/phase), CddDcm blackboard (`DcmState0`, `DcmPos0`) |
| LWR output stage | `IoHwAb_User_SetDio_EN_DC` → `IoHwAb_DiscreteEN_LWR_Write` (PA3); `IoHwAbUser_GetAdc_VoltDC_OUT1` → `IoHwAb_AnalogReadConverted(IOHWAB_CHID_ADIN_3)` (ADC1 ch0); `Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT` → `IoHwAb_VoltageKL30_Read`; PWM → `IoHwAb_TimingSetDutyCycle/StopActuation(IOHWAB_CHID_CTRL_LWR)` (TIMG9 CC1, PA2), duty 0x8000-scale → ‰ (exact inverse with rounding) |
| Platform services | `TimerGetTick/TimerGetTimeSince` (µs counter, +5000 per MainFunction), `NM_GetMode`, `Rte_Call_DemPrj_ReportErrorStatus`, `ILCU_LvlAdp_NvM_WriteBlock` |
| DPE types/macros | field subsets of RteCommonTypes/CodM/NvM_Para types, same names and enumerator values; byte-exact copies of the `tDcmCtrlMsg`/`tDcmStateMsg` unions; `STATIC_AL`, `CONST_AL`, `STATIC_UT`, `UTIL_*`, `ORDER1_Filter`, `CFG_*` switches |

## 4. Modifications to the copied DPE files (each marked `/* ILCU_PORT: … */`)
Audit: every added line in the 27 copied files is either `ILCU_PORT`-marked, a continuation of a marked comment, or one of the 30 `static INLINE` lines under the single marker in `AvacStat1Data.h`. **0 unmarked changes.** `AvacStat1.h`, `ctaaAvacStat1.h` and `CddDcm_Cfg.h` are byte-identical to DPE.

| File | −/+ lines | Change |
|---|---|---|
| `AvacStat1/AvacStat1.c` | 50/8 | includes → adapter; `NvM_WriteBlock` → `ILCU_LvlAdp_NvM_WriteBlock` (×2, one in the compiled-out tester hook); **`AvacStat1_SetSpeedMode()` removed** (prototype, call, body) |
| `AvacStat1/AvacStat1Data.c` | 49/3 | includes → adapter; **`AvacStat1Data_WriteSpeedMode()` and `AvacStat1Data_ReadAslPhase()` removed** |
| `AvacStat1/AvacStat1Data.h` | 43/38 | includes → adapter; `teAvacStat1_LvlPhase` and the 2 prototypes removed; `NvM_WriteBlock` renamed; **`INLINE` → `static INLINE` (30 functions)** |
| `AvacStat1/AvacStat1Init.c/.h`, `AvacStat1Types.h`, `AvacStat1Util.c/.h` | 1/1 each | DPE-only include → adapter |
| `AvacStat1/ctaaAvacStat1.c` | 1/1 | include path flattened |
| `CtrlDcm/Api/CtrlDcm.h`, `CtrlDcmSm.h`, `CtrlDcm_Data.c/.h`, `CtrlDcm_RteAccess.c/.h`, `ctaaCtrlDcm.c/.h`, `CtrlDcm.c`, `CtrlDcmSm.c` | includes only | DPE-only includes → adapter; `<../App/Swc/Ctrl/Dcm/…>` paths flattened. **No logic change in CtrlDcm.** |
| `src_AL/cdd/CddDcm/Api/CddDcm.h`, `Gen/CddDcmCtrl.h`, `Gen/CddDcmHal.h` | 1/1 each | DPE-only include → adapter |
| `src_AL/cdd/CddDcm/Gen/CddDcmCtrl.c` | 8/2 | includes → adapter; `NvM_WriteBlock` → `ILCU_LvlAdp_NvM_WriteBlock` |
| `src_AL/cdd/CddDcm/Gen/CddDcmHal.c` | 12/5 | includes → adapter; `Pwm_SetDutyCycle` ×2 → `ILCU_LvlAdp_LwrPwmSetDuty`, `Pwm_StartPwmChannel` → `ILCU_LvlAdp_LwrPwmStart`, `Pwm_ClampPwmChannel(…, PWM_LOW)` → `ILCU_LvlAdp_LwrPwmToIdle`. **No logic change in CddDcm.** |

Why each class:
- **Includes.** The DPE headers do not exist in ILCU. On Windows, `<Nvm.h>` would otherwise silently resolve to ILCU's `NvM.h`.
- **Renames.** `NvM_WriteBlock` and `Pwm_*` collide with real ILCU/TI MCAL symbols.
- **AvacStat1 reduction (Q1).** AvacStat1 has no Init/Adj/Fail machine of its own. Its only phase code was this mirror of the CtrlDcm phase.
- **`static INLINE`.** Confirmed necessary: with the AUTOSAR `INLINE = inline`, an `-O0` link failed with undefined `_Cod_AvacStat1_*`. ILCU builds `FILES_DEBUG` at `-O0` (`BuildSystem.md` §6.2).

## 5. STUBS — what is NOT real yet

| # | Stub | Current value / behaviour | Consequence | Made real by |
|---|---|---|---|---|
| S1 | **Pitch angle** `ILCU_LevellingAdapter_GetPitchAngle` | fixed `ILCU_LVLADP_STUB_PITCH_0P1MRAD` = 0, always E_OK | headlamp stays at 0 after power-on | IMU module (swc_imu has `Pitch_cdeg` in 0.01°; × 1.745 → 0.1 mrad; verify sign) |
| S2 | Pitch plausibility `Rte_Read_Pitch_PlausState` | eNO_FAILURE | no sensor-plausibility fail path | IMU module, if wanted |
| S3 | Vehicle speed / dynamics | 0 km/h, pedal 0, SIG_VALID | AvacStat1 runs **only its Zero_Speed (standstill) regulation**: power-on/light-on adjustment, then load-change adjustment (Δ > 1 mrad held 10 s). Driving-mode filtering is unreachable. | a CAN speed signal |
| S4 | Vehicle network state | Ignition, eTA_NOMINAL, SIG_VALID | ignition never goes off → "ignition needed" latches never clear (§6.3) | real ignition/KL15 state |
| S5 | Vehicle configuration | eModeConfigVehicle_Client | CtrlDcm always in Customer mode; Assembly/Factory/Frozen unreachable | — |
| S6 | Mounting side | eMountedLeft (master) | slave (right-side) machine unreachable | — |
| S7 | Right-side ECU diag / target, master command, DrvLedDiag(R) | VALID/OK loop-back buffers | no L/R CAN exchange | — |
| S8 | UDS routine control (DD06) | no request | diag takeover unreachable | a Dcm/UDS integration |
| S9 | **Coding block** (`Rte_Read_CodM_Pitch_Para`) | DPE `NVMPARA_AVACSTP_DCMOTORDATA_INIT` (ASL enabled, Min/Max_ASL_Adjust_Left −300/0, safety −32) **except FROZEN = 2 and HIGH_FROZEN = 5** (DPE comment values; the DPE defaults are 0/0, which blocks standstill levelling) | real EOL coding not used | ILCU coding/NvM |
| S10 | **NvM** (5 blocks) | RAM only; `ILCU_LvlAdp_NvM_WriteBlock` returns E_OK and stores nothing | headlight angle, safety angle and LWR position are lost at reset; CddDcm starts every boot with "position unknown" | ILCU NvM blocks (requires editing ILCU NvM config) |
| S11 | `NvmBlockDeltaPwmPara.ucZeroLevProg` | 0xFF ("zero-level programming done") | CtrlDcm TrainingState TRUE; ZERO_LVL_PROG reported PASSED | EOL zero-level procedure |
| S12 | Dem | `Rte_Call_DemPrj_ReportErrorStatus` stores the last status per event in `ILCU_LvlAdp_DemStatus[]` | no DTC memory | an ILCU Dem |
| S13 | NM | never limp-home; `LIMP_HOME_MODE` = 0x02 is adapter-defined (DPE value unknown, only compared) | limp-home stop never triggers | — |
| S14 | Timer | 1 µs ticks from the 5 ms MainFunction count (5 ms resolution) | fine for CtrlDcm's 2 s fault timers | an OS tick if finer resolution is needed |
| S15 | `ILCU_LvlAdp_LwrPwmStart` | no-op (AUTOSAR: next SetDutyCycle re-activates an idle channel) | [verify with TI MCAL Pwm] | — |

## 6. Known issues carried over (not fixed, by decision or by rule)

### 6.1 Hardware / configuration — [verify on Al077a HW]
> **Superseded 2026-11-11, see §11.** F3 is wrong (the stage reaches about 17.2 V, no hardware change needed) and F7 is restated (KL15 reads 0 mV; worked around in the adapter).
- **F3, quantified: CddDcm's output stage is DPE hardware.**
  - CddDcm regulates LWR_DC as a ‰ ratio of KL15, with divisor 3.485 × 4970 mV (`CddDcmHal.c:146-154`).
  - The ILCU stage gives ≈ D × 3.05 V absolute (`Al077HardwareSchematic.md` §7).
  - Harness, ILCU-stage model, pitch 200: commanded **430 ‰** of KL15, reached **225 ‰** with PWM saturated at **1000 ‰**. No error is raised (225 ‰ is inside the 60–940 ‰ "OK" band), so the lamp silently ends up at the wrong position.
  - CddDcm logic stays unchanged per the brief, so this needs a hardware/product decision.
- **F7.** Al077a IoHwAb analog config vs schematic:
  - VBAT is read from ADC0 ch4 (`IoHwAb_AnalogCfg.c:251-260`); the schematic has KL15 on ADC0 ch5.
  - LWR feedback is scaled 82.5k/21k; the schematic has 82.5k/15k.
  - If VBAT reads outside 8.59–17.69 V, CddDcm locks the output permanently (`CddDcmCtrl.c` VoltChange).

### 6.2 DPE defects (logic left unchanged)
- `AvacStat1.c` `NvmSet_AvacStat1_AdjCounter(unCnt++)` passes the old value, so the adjustment counter never increments.
- `CddDcmCtrl.c` (DoErrorDetection, "both absent" branch) writes `boElecGND = FALSE` twice; `boElecBAT` is not cleared there.
- `CtrlDcm_RteAccess.c` `WriteCtrlDcm_MasterCommand_Port` writes `eRCmdRefLvl`/`eSigQty` from an uninitialised local. Harmless with a single (master) ECU.

### 6.3 Undefined behaviour observed in the harness (DPE code, Q3 = left as-is)
- `CtrlDcmSm.c` `CtrlDcm_HandleFailState` reads the uninitialised locals `eFailStateLeft/Right` when Fail is active but no fault is present (the recovery cycle).
- Harness scenario 2 (pitch invalid → valid): on that cycle, **`-O0` stops the output, `-O2` drives it (duty 206 ‰)**. This is the only `-O0`/`-O2` transcript difference.
- After recovery, CtrlDcm returns to **Adj** but `boStop` stays TRUE ("ignition needed" latch). With stub S4, the lamp stays frozen until reboot.
- **Recommendation:** revisit Q3 for these lines. Initialising the two locals to `CtrlDcm_eFreeze` changes nothing on any defined path.

### 6.4 DPE-inherited compiler warnings (verbatim; clang `-Wall`, thumbv6m, armclang-like flags)
```
AvacStat1/AvacStat1Data.c:212:36: warning: unused variable 'sPitchAmvar' [-Wunused-variable]
CtrlDcm/CtrlDcm.c:124:20: warning: unused function 'CtrlDcm_SetDiagRequest' [-Wunused-function]
CtrlDcm/CtrlDcm.c:126:20: warning: unused function 'CtrlDcm_WriteValidationFrames' [-Wunused-function]
CtrlDcm/CtrlDcm.c:127:51: warning: unused function 'CtrlDcm_DiagSequenceMachine' [-Wunused-function]
CtrlDcm/CtrlDcm.c:195:10: warning: unused variable 'nPosReq' [-Wunused-variable]
CtrlDcm/CtrlDcm.c:218:10: warning: unused variable 'nPosReq' [-Wunused-variable]
CtrlDcm/CtrlDcm.c:306:92: warning: unused variable 'boSTTPhaseInvalid' [-Wunused-variable]
CtrlDcm/CtrlDcm.c:59:30: warning: unused variable 'CtrlDcm_ulDiagSequenceTimer' [-Wunused-variable]
CtrlDcm/CtrlDcm.c:67:59: warning: unused variable 'CtrlDcm_eCurrentDiagState' [-Wunused-variable]
CtrlDcm/CtrlDcm.c:69:59: warning: unused variable 'CtrlDcm_aeDiagSequence1' [-Wunused-const-variable]
CtrlDcm/CtrlDcm.c:71:59: warning: unused variable 'CtrlDcm_aeDiagSequence2' [-Wunused-const-variable]
CtrlDcm/CtrlDcm.c:97:32: warning: unused variable 'CtrlDcm_DiagStatus' [-Wunused-variable]
CtrlDcm/CtrlDcmSm.c:1293:14: warning: variable 'eFailState' is used uninitialized whenever 'if' condition is false [-Wsometimes-uninitialized]
CtrlDcm/CtrlDcmSm.c:902:14: warning: variable 'eFailStateLeft' is used uninitialized whenever 'if' condition is false [-Wsometimes-uninitialized]
CtrlDcm/CtrlDcmSm.c:902:14: warning: variable 'eFailStateRight' is used uninitialized whenever 'if' condition is false [-Wsometimes-uninitialized]
CtrlDcm/CtrlDcm_Data.c:40:44: warning: unused variable 'CtrlDcm_sDCMotorData' [-Wunused-variable]
CtrlDcm/CtrlDcm_RteAccess.c:114:12: warning: variable 'ucCtrlDcmVechElectricState' is used uninitialized whenever 'if' condition is false [-Wsometimes-uninitialized]
CtrlDcm/CtrlDcm_RteAccess.c:151:12: warning: variable 'ucCtrlDcmVESMainState' is used uninitialized whenever 'if' condition is false [-Wsometimes-uninitialized]
CtrlDcm/CtrlDcm_RteAccess.c:75:7: warning: variable 'unCtrlDcmSpeed' is used uninitialized whenever '&&' condition is false [-Wsometimes-uninitialized]
CtrlDcm/CtrlDcm_RteAccess.c:75:7: warning: variable 'unCtrlDcmSpeed' is used uninitialized whenever 'if' condition is false [-Wsometimes-uninitialized]
```
`-Wextra` adds one more, also in DPE code: `CtrlDcm/CtrlDcm_RteAccess.c` `-Wmissing-field-initializers`. Line numbers refer to the ILCU copies.

## 7. Verification evidence (host, this workspace)
1. **Compile check.**
   - Setup: Apple clang 21, `--target=thumbv6m-none-eabi -mcpu=cortex-m0plus -std=gnu17 -fshort-enums -ffreestanding -Os -Wall -fsyntax-only` on all 13 sources. Real ILCU IoHwAb/AL_Filter/MemMap headers; scratchpad-only shims for the missing TI MCAL `Std_Types/Platform_Types/Compiler/Adc/Dio/Pwm/Icu` and libc `stdlib.h`.
   - Result: **0 errors; 0 diagnostics in the adapter or on ILCU_PORT lines**; 20 DPE-inherited warnings (§6.4).
   - This is not armclang and not the real TI headers.
2. **Native link.** The whole chain links at `-O0` and `-O2` after the `static INLINE` fix (before it, `-O0` failed with undefined `_Cod_AvacStat1_*`).
3. **Behaviour harness** (chain + adapter + IoHwAb fakes, 5 ms ticks): all 4 scenarios PASS at `-O0` and `-O2`.
   - Healthy: CtrlDcm phase **Adj at 20 ms** (first CtrlDcm cycle) and still Adj after 45 s. Target tracks pitch 200 → −115 (0.01°). The load change to 400 is held 10 s, then target −229. EN_LWR and PWM are driven; the move completes after the adjusting time.
   - Pitch invalid: Fail, target = coded safety position −32.
   - LWR output shorted to GND: DCMotor_SC_GND after about 0.5 s → `boElecGND` → Fail at 2.56 s.
   - ILCU output-stage model: F3 confirmed (§6.1).
4. **Manifests:** DPE 1712/1712 files identical; ILCU 0/670 pre-existing files changed.
5. **Re-run after the CddDcm move (§10):** 0 compile errors and the identical 20-warning set. Harness: 4 of 4 scenarios PASS, with transcripts byte-identical to the pre-move runs at -O0 and -O2.

## 8. What you need to run
1. Apply the CustVar lines (§2), then:
   `Build\VS> ..\Build.bat H00 MSPM0G_3519 ARM_KEIL CUnit GCOV M0P Al077 App default NonKey rebuild > build.log`
   Grep `build.log` for `error`/`warning` in `swc_levelling` and check the hex timestamp. The exit code is meaningless (`BuildSystem.md` §1).
2. Add the 3 hook lines in `Rte.c` (§2) only when the chain should actually run.
3. Decide F3 (output-stage scaling) and F7 (IoHwAb analog mapping) before connecting a real LWR actuator.

## 9. Corrections to PORT_PLAN.md
- **I was wrong about the SpeedMode consumer.** PORT_PLAN §4.5 says SpeedMode's "only consumer is Pitch". In fact `Rte_Read_AvacStat1_SpeedMode` has **no reader** in the DPE snapshot: only its RTE definition exists, `Rte/Eco/Rte_Cfg.c:2609`. Pitch reads the CtrlDcm *phase*, not SpeedMode. The removal stands, with a stronger justification.
- **Predicted `-Wbraced-scalar-init` at `CtrlDcm.c:781` did not occur** (clang warns about it only in C++).
- **Four warnings I had not predicted:** 3× `-Wunused-function` (static prototypes for `#if 0` functions) and unused `boSTTPhaseInvalid`.
- **E4 was conditional in the plan.** The host link confirmed the hazard, so it was applied.

## 10. Change log

### 2026-11-06 — CddDcm moved to the Cdd folder (on request)
CddDcm now sits in ILCU's CDD folder with the same layout as `src_AL/cdd/CddAsm330lhh`. It is a pure move: the 6 files are byte-identical before and after (SHA-256), and no source line changed. The sources include each other and the adapter by bare file name, so only include paths moved.

| File | Was | Now |
|---|---|---|
| `CddDcm.h` (interface header) | `app/swc_levelling/CddDcm/` | `cdd/CddDcm/Api/` |
| `CddDcmCtrl.c/.h`, `CddDcmHal.c/.h` | `app/swc_levelling/CddDcm/` | `cdd/CddDcm/Gen/` |
| `CddDcm_Cfg.h` | `app/swc_levelling/CddDcm/Cfg/` | `cdd/CddDcm/Cfg/` |
| make fragments | CddDcm entries in `IlcuLevelling_030/050` | new `cdd/CddDcm/Make/CddDcm_030_Flags.gmk`, `CddDcm_050_Files.gmk` |

- `CddDcm_030_Flags.gmk` adds `Api`, `Gen` and `Cfg` (CddAsm330lhh adds only `Api`). `CddDcmHal.c` includes its own headers with angle brackets, which never search the source's folder.
- A per-project copy of `CddDcm_Cfg.h` could later go to `config_AL/Al/Al077a/cdd/CddDcm/Cfg/`, as CddAsm330lhh does. It is not needed now.
- Verification re-run: §7 item 5.

### 2026-11-11 — §11 Adapter made demo-ready; findings corrected against the schematic

Scope: only files under `swc_levelling/`. `Rte.c`, `swc_imu`, `swc_iara`, IoHwAb and MCAL configuration are unchanged; what they need is listed as patches in `LEVELLING_PORT_REPORT.md` (project root).

**Corrections to earlier sections**

| Earlier statement | Correct |
|---|---|
| §6.1 F3: the ILCU stage gives D × 3.05 V, hardware change needed | **Wrong.** On schematic sheet 80_SAVAC, R8004 (10 k) sits on the CTRL_LWR pin, before R8001: a pull-down, not a divider. IN+ = D × 3.3 V, gain 1 + 82.5k/19.6k = 5.21, so LWR_DC = D × 17.19 V. CddDcm assumes 17.32 V; its 20 ms loop removes the 0.75 % gap. No hardware change. |
| §6.1 F7: VBAT read from "ADC0 ch4" | `IOHWAB_CHID_VBAT` reads result slot 4 of ADC group 0, which converts 2 channels. The value is always 0 mV, so CddDcm stays locked. Nothing starts the ADC groups either. |
| §5 S1: pitch is a fixed 0 | Replaced, see below. |
| §6.3: recommendation to initialise the CtrlDcm locals | Done, see below. |

**Changes**

| File | Change |
|---|---|
| `ILCU_LevellingAdapter.h` | New section 1a: `#ifndef` configuration macros (pitch sign, filter, timeouts, auto-zero, analog channel IDs and scale, ADC start, demo load-change interval) and three debugger hooks. `ILCU_LVLADP_STUB_PITCH_0P1MRAD` removed. |
| `ILCU_LevellingAdapter.c` | (1) Default pitch source reads `Rte_Iara_TargetPitch_cdeg`, × 349/200 to 0.1 mrad, usable once `Rte_ImuInitResult == E_OK`. (2) `ILCU_LvlAdp_PitchCycle()` every 20 ms: sign, low pass, zero reference, quality `SIG_INIT` → `SIG_VALID`, `SIG_INVALID` only after 5 s without a first sample or 500 ms of dropout. (3) KL15 and LWR feedback read with `IoHwAb_AnalogReadRaw` and scaled × 6.5 in the adapter. (4) Both ADC groups started every 5 ms when not busy. (5) `Init` drives EN_LWR low and idles the PWM first; `MainFunction` returns until `Init` ran. (6) Load-change interval set to 2 s after the DPE defaults load. |
| `CtrlDcm/CtrlDcmSm.c` | `eFailStateLeft`, `eFailStateRight` (HandleFailState) and `eFailState` (HandleFailState_Slave) are `static`, initialised to `CtrlDcm_eFreeze`. Reverses Q3 for these lines. |
| `CtrlDcm/CtrlDcm_RteAccess.c` | `unCtrlDcmSpeed`, `ucCtrlDcmVechElectricState`, `ucCtrlDcmVESMainState` are `static` with a safe initial value. |
| `Make/IlcuLevelling_030_Flags.gmk` | `src_AL/rte` added to the include paths (`Rte_Imu.h`, `Rte_Iara.h`). |

**Stub table (§5) after this change**

| # | Was | Now |
|---|---|---|
| S1 | pitch fixed 0 | IARA pitch by default; `ILCU_LvlAdp_BenchPitchEnable` / `ILCU_LvlAdp_BenchPitch_0p1mrad` feed a value from the debugger; `ILCU_LVLADP_EXTERNAL_PITCH_SOURCE` still replaces the source. Reads 0 until the IMU owner fixes the sample starvation of `swc_iara`. |
| S16 (new) | — | Zero reference is RAM only: taken 1 s after the first usable sample (`ILCU_LVLADP_PITCH_AUTO_ZERO`) or on `ILCU_LvlAdp_CalibRequest = 1`. Demo behaviour, not a vehicle calibration. |
| S17 (new) | — | The adapter starts the ADC groups and scales raw counts itself. Remove (`ILCU_LVLADP_START_ADC_GROUPS STD_OFF`, channel ID macros) once IoHwAb does both. |
| S4 | ignition always on | unchanged: after a real pitch fault the lamp stays stopped until reset. |

**Verification (host, 2026-11-11)**

- Warning check, clang `--target=thumbv6m-none-eabi -mcpu=cortex-m0plus -std=gnu17 -fshort-enums -ffreestanding -Os -fno-inline-functions -Wall -fsyntax-only`, 13 sources, stand-in headers for the TI MCAL: 0 errors, 13 warnings, none in the adapter. The 7 uninitialised-variable warnings of §6.4 are gone; the 13 left are the unused-code warnings of §6.4.
- Behaviour harness: the chain, the adapter, the real Al077a IoHwAb configuration and the platform IoHwAb core (copy of 2026-11-06), with a model of the real stage (D × 17.19 V, × 6.5 dividers). 8 scenarios pass at `-O0` and `-O2` with identical transcripts:

| Scenario | Result |
|---|---|
| Pitch 0 / +1° / +2° / +3° / +4° / −1° at 12 V | Ver 0 / −100 / −200 / −300 / −400 / 0; target clamps at −300; LWR_DC 2406 / 4778 / 7202 / 9609 / 9609 / 2406 mV |
| IMU ready after 3 s | quality `SIG_INIT`, phase Adj, no Fail latch; levels normally afterwards |
| IMU never ready | `SIG_INVALID` after 5 s, phase Fail, target −32, lamp at 3162 mV |
| KL15 7 V, then 15 V | output off; back at 9007 mV (600 ‰ of 15 V) |
| Dropout 300 ms, then 1 s | held; then Fail; after recovery Adj with the target stopped |
| IoHwAb path vs adapter | `IoHwAb_VoltageKL30_Read` = 0 mV, adapter 11995 mV; IoHwAb feedback 5457 mV for 7202 mV at the pin, adapter 7197 mV |
| Bench override 349 | Ver −200, 7202 mV |
| LWR_DC shorted to ground | `DCMotor_SC_GND` FAILED, phase Fail, output off |

- Control: with `ILCU_LVLADP_START_ADC_GROUPS STD_OFF` KL15 reads 0 mV and the output never enables.
- Not run: Keil/armclang build, TI MCAL, the board. `ADC_BUSY` and the PWM restart after `Pwm_SetOutputToIdle` are UNVERIFIED against the TI MCAL.
