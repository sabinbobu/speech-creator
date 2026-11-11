# ASL levelling port DPE → ILCU: review report

Date: 2026-11-11. Board config: `Al077a` (MSPM0G3518). Nothing here was built with Keil or run on the board; "verified" means the host checks in Appendix B.

**The demo does not run today, and the reasons that remain are outside `swc_levelling`.** Nothing calls the levelling chain, `swc_imu` drives the same LWR pins itself, and the IARA pitch is stuck at 0 because `swc_imu` consumes every IMU sample first. Inside `swc_levelling` every blocker I found is now closed and passes the host harness.

Two corrections to what you were told so far:

- **The modules are not unmodified.** 24 of 27 copied files differ from DPE. AvacStat1 lost one function and two data accessors; CddDcm had four PWM calls and one NvM call redirected. All edits are marked `ILCU_PORT`; I found no unmarked change (§2.1).
- **The output stage does not need a hardware change.** `Al077HardwareSchematic.md` and all three PDFs say the stage tops out at 3.05 V. The schematic photo shows R8004 is a pull-down on the PWM pin, not a divider. The stage gives D × 17.19 V, which is what CddDcm expects (§5.5).

Scope change: `Prompt.md` asked for analysis only. On 2026-11-10 you changed that: edit `swc_levelling` (your module), deliver patches for everything else. Six files under `swc_levelling` were edited (§2.2); no other source file was touched.

Path abbreviations used below:

| Prefix | Path |
|---|---|
| `LVL/` | `ILCU/Src/src_AL/app/swc_levelling/` |
| `APP/` | `ILCU/Src/src_AL/app/` |
| `CDD/` | `ILCU/Src/src_AL/cdd/` |
| `RTE/` | `ILCU/Src/src_AL/rte/` |
| `CFG/` | `ILCU/Src/config_AL/Al/Al077a/` |
| `DPE/` | `DPE/Src/Src_AL/Cust/St/St126/App/` |
| `SIB/` | `~/Job/speech-creator/Algo/Src/src_AL/ecu9_core_ptf/Src/Src_AL/` — platform core from an older (2026-11-06) copy of the ILCU tree, **outside the workspace**. The workspace has no platform core. |

## Documents

Recursive search for `*.html`, `*.htm`, `*.pdf` found 7 files. All were readable.

| Document | Read | Used for | Reliability |
|---|---|---|---|
| `ASL Levelling Port Report (DPE → ILCU)-2.pdf` (20 p) | fully | port history, decisions, interface map | Predates `swc_iara` and the motor output in `swc_imu`; its `Rte.c`/`swc_imu.c` line numbers are stale. Output-stage finding wrong. |
| `ASL Levelling Port Build Readiness and Build Guide-2.pdf` (13 p) | fully | build wiring, stack budget | Same age. Refers to a `Build/` tree that is not in the workspace. |
| `CddDcm on ILCU IoHwAb Change List.pdf` (7 p) | fully | IoHwAb/MCAL gaps | H1 (remove R8004) is wrong. I3 slope 42910 overflows `sint16 SlopeNum` (`SIB/bsw/IoHwAb/IoHwAb_Types.h:88`). |
| `ASL_Levelling_Fix_Guide.html` | fully | CAN signals available, stub list | Its work packages A to C are not implemented; not needed for a standstill demo. |
| `ASL_Levelling_Copilot_Roadmap.html` | fully | commit sequence | Process document; no new technical facts. |
| `DPE/graphify-out/graph.html` | opened | not used | Graph viewer (script plus node data), no prose. |
| `DPE/graphify-out-AvacStat1/graph.html` | opened | not used | Same. |

Also used: `LVL/PORT_PLAN.md`, `LVL/PORT_CHANGES.md`, `CFG/Al077HardwareSchematic.md`, `ILCU/copilot-instructions.md`, the two `CddAsm330lhh` text notes, and the schematic photos `IMG_3327.HEIC` (MCU page) and `IMG_3328.HEIC` (AVAC page).

---

## 1. Critical blockers (ranked)

Open blockers. None of these can be fixed from inside `swc_levelling`.

| # | Severity | Finding | Evidence | Fix | Owner |
|---|---|---|---|---|---|
| B1 | blocker | Nothing calls the chain. `Rte.c` has no adapter include, no `Init` in `Rte_Start`, no `MainFunction` in `BasicTask`. The linker drops all 13 objects. | `RTE/Rte.c:25-41`, `:102-111`, `:212-245` | Patch P1 (3 lines) | Integration |
| B2 | blocker | Two modules drive the LWR output. `swc_imu` writes the PWM duty `(pitch + 5000)/10` ‰ and sets EN_LWR high every 10 ms. CddDcm writes the same pins only on change, so `swc_imu` wins. | `APP/swc_imu/swc_imu.c:14-44`, `:134-138`, `:188`; `RTE/Rte.c:144-157` | Patch P2: remove the motor output from `swc_imu` | IMU |
| B3 | blocker | The IARA pitch never updates. All three CDD read functions clear `DataReady`. `swc_imu` runs first and takes the sample; `swc_iara` then gets `E_NOT_OK` and returns before `IARA_Main()`. `Rte_Iara_TargetPitch_cdeg` stays at the 0 written in `swc_iara_init`. UNVERIFIED by execution; follows from the code. | `CDD/CddAsm330lhh/Gen/CddAsm330lhh.c:1004,1070`; `RTE/Rte.c:122,164,227-228`; `APP/swc_imu/swc_imu.c:162`; `APP/swc_iara/swc_iara.c:83,98-101` | Patch P3: one fetch per cycle in `Rte.c`, both SWCs served from the copy | IMU |
| B4 | blocker | Make fragments are not included by any build file. UNVERIFIED: the workspace has no `Build/` tree. | `LVL/Make/*.gmk`, `CDD/CddDcm/Make/*.gmk`; no `Build` directory under `ILCU/` | Patch P9 | Build |

Closed inside `swc_levelling` on 2026-11-11 (were blockers):

| # | Finding | Evidence | What the adapter does now |
|---|---|---|---|
| C1 | KL15 read 0 mV, so CddDcm stayed locked. `IOHWAB_CHID_VBAT` is result slot 4 of ADC group 0; that group converts 2 channels. CddDcm enables the output only between 8.59 and 17.69 V. | `CFG/bsw/IoHwAb/IoHwAb_AnalogCfg.c:251-260`; `CFG/mcal/Adc_Cfg/src/Adc_PBcfg.c:113,121,133`; `CDD/CddDcm/Gen/CddDcmCtrl.c:584-593`, `:482-486`; `SIB/bsw/IoHwAb/internal/IoHwAb_Analog.c:171-181` | Reads raw counts of slot (0,0) and scales × 6.5 itself: `LVL/ILCU_LevellingAdapter.c:97-111`, `:383-393` |
| C2 | Nothing started an ADC conversion. Both groups are one-shot, software triggered; IoHwAb only copies result buffers. | `CFG/mcal/Adc_Cfg/src/Adc_PBcfg.c:100-102`; `SIB/bsw/IoHwAb/internal/IoHwAb_Analog.c:94-105`; only `swc_adc_test` and `swc_led` call `Adc_StartGroupConversion` | Starts both groups every 5 ms when not busy: `LVL/ILCU_LevellingAdapter.c:113-128`, `:262-264` |
| C3 | Pitch was a constant 0. | old stub, see `LVL/PORT_CHANGES.md` §5 S1 | Default source is the IARA pitch: `LVL/ILCU_LevellingAdapter.c:281-304`. Depends on B3. |
| C4 | One invalid pitch sample latched Fail until reset. `E_NOT_OK` became `SIG_INVALID`; CtrlDcm then sets "ignition needed", and the ignition stub never cycles. An IMU still initialising at power-on was enough. | `LVL/CtrlDcm/CtrlDcm_RteAccess.c:218-221`; `LVL/CtrlDcm/CtrlDcm.c:319-325`, `:255-259`, `:1110-1113`; `LVL/CtrlDcm/CtrlDcmSm.c:882-886`; `LVL/ILCU_LevellingAdapter.c:446-453` | Quality is `SIG_INIT` until the first usable sample, `SIG_INVALID` only after 5 s (start-up) or 500 ms (dropout): `LVL/ILCU_LevellingAdapter.c:130-202` |
| C5 | Output stage could be live at boot: PA3 initial level HIGH, PWM initial duty 50 %. CddDcm writes EN only when its enable state changes. | `CFG/mcal/Port_Cfg/src/Port_PBcfg.c:683`; `CFG/mcal/Pwm_Cfg/src/Pwm_PBcfg.c:111`; `CDD/CddDcm/Gen/CddDcmHal.c:418-451` | `Init` writes EN low and idles the PWM first: `LVL/ILCU_LevellingAdapter.c:209-212`. The window from `Port_Init` to `Rte_Start` remains; patch P6 closes it. |

Not a blocker: the output stage (§5.5).

---

## 2. Current implementation state

### 2.1 Port review: diff against DPE

Method: `diff` of each ILCU file against its DPE source, then a scan of every added line for the `ILCU_PORT` marker.

| Module | Files | Byte-identical | Changed | Logic changes |
|---|---|---|---|---|
| AvacStat1 | 11 | `AvacStat1.h`, `ctaaAvacStat1.h` | 9 | `AvacStat1_SetSpeedMode()` removed with its call (`LVL/AvacStat1/AvacStat1.c:109,810,887-889`); `AvacStat1Data_WriteSpeedMode()`, `AvacStat1Data_ReadAslPhase()` and `teAvacStat1_LvlPhase` removed (`LVL/AvacStat1/AvacStat1Data.c:279-280`, `AvacStat1Data.h:43,59,61`); 30 accessors `INLINE` → `static INLINE`; `NvM_WriteBlock` → RAM stub (3 sites) |
| CtrlDcm | 10 | none | 10 | Includes only, until 2026-11-11. Now also 6 locals made `static` with an initial value (`LVL/CtrlDcm/CtrlDcmSm.c:866-867,1278`; `LVL/CtrlDcm/CtrlDcm_RteAccess.c:70,105,138`). |
| CddDcm | 6 | `CddDcm_Cfg.h` | 5 | `Pwm_SetDutyCycle` ×2, `Pwm_StartPwmChannel`, `Pwm_ClampPwmChannel` → adapter functions (`CDD/CddDcm/Gen/CddDcmHal.c:263,370,372,381`); `NvM_WriteBlock` → RAM stub (`CddDcmCtrl.c:209`) |

- Severity **major** (process, not function): the brief says "unmodified". It is not. The removed AvacStat1 code only mirrored CtrlDcm's phase into a signal nothing reads in the DPE ECO variant, so behaviour is unaffected, but anyone comparing against DPE must know.
- Unmarked changes: **none**. The 5 added lines without a marker are continuation lines of marked comments.
- Functional difference that is not a code edit: NvM is RAM only (`LVL/ILCU_LevellingAdapter.c:337-343`). Headlight angle, safety angle and motor position are lost at reset, so CddDcm starts every boot with "position unknown" and holds the output on for 21 s on the first move (`CDD/CddDcm/Gen/CddDcmCtrl.c:281-301`, `:714-721`).

### 2.2 What was edited on 2026-11-11

| File | Change |
|---|---|
| `LVL/ILCU_LevellingAdapter.h` | Configuration block `:49-101`; pitch API contract `:36-47` |
| `LVL/ILCU_LevellingAdapter.c` | Pitch source and conditioning, raw analog read, ADC start, safe start, demo timing (C1 to C5 above) |
| `LVL/CtrlDcm/CtrlDcmSm.c`, `LVL/CtrlDcm/CtrlDcm_RteAccess.c` | Six uninitialised "keep previous value" locals fixed |
| `LVL/Make/IlcuLevelling_030_Flags.gmk` | `src_AL/rte` include path |
| `LVL/PORT_CHANGES.md` | §11 change log and corrections |

Originals of the four source files are byte-identical in `~/Job/speech-creator/Algo/Src/src_AL/app/swc_levelling/` (checked before editing), so they are recoverable.

### 2.3 Adapter review

| Aspect | State | Evidence |
|---|---|---|
| Scheduling | `MainFunction` every 5 ms: CddDcm every call, AvacStat1 + CtrlDcm every 4th call. Matches DPE rates (AvacStat1/CtrlDcm 20 ms, CddDcm 5 ms). | `LVL/ILCU_LevellingAdapter.c:257-279`; `DPE/Rte/Eco/Rte_Cfg.c:103,105,108` |
| Call order | ILCU: pitch → AvacStat1 → CtrlDcm → CddDcm in one tick. DPE: AvacStat1, CddDcm, then CtrlDcm 2 ms later. ILCU has less latency; no dependency is inverted. **minor** | same |
| Init order | AvacStat1, CddDcm, CtrlDcm, as DPE. | `LVL/ILCU_LevellingAdapter.c:250-252`; `DPE/Rte/Eco/Rte_Cfg.c:65-68` |
| Task period | `BasicTask` every 5 OS ticks at 1 kHz. | `RTE/Rte.c:83`; `CFG/bsw/Os/FuSa-RTS/RTX_Config.h:42-43` |
| Units along the chain | 0.1 mrad → 0.01° (×180/314) → position ‰ (800 + 2 × Ver) → level ‰ (1000 − position) → PWM ‰. All integer, checked end to end in the harness. | `LVL/AvacStat1/AvacStat1Data.c:267-268`; `CDD/CddDcm/Gen/CddDcmCtrl.c:50-51,96,562`; `CDD/CddDcm/Gen/CddDcmHal.c:239` |
| PWM scaling | CddDcm ‰ → 0x8000 scale → adapter back to ‰ (rounded) → IoHwAb `(d × 33554) >> 10`. 1000 ‰ gives 0x7FFF, not 0x8000: one LSB short of 100 %. **minor** | `LVL/ILCU_LevellingAdapter.c:362-369`; `SIB/bsw/IoHwAb/internal/IoHwAb_Timing.c:36` |
| Invalid handling | Pitch: §1 C4. KL15/feedback read error → 0 mV → output locked. | `LVL/ILCU_LevellingAdapter.c:97-111` |
| Types | DPE type subsets copied by name. `tiu32Voltage_mV` is `unsigned long`: 32 bit on the target, 64 bit on a host. **minor**, host tests only. | `LVL/ILCU_LevellingAdapter.h:184` |
| Internal header | The adapter includes `IoHwAb_Internals.h` (no public wrapper for raw analog read or PWM idle). **minor**; goes away with patch P5. | `LVL/ILCU_LevellingAdapter.c:19` |

Symbols still stubbed (unchanged, acceptable for a standstill demo):

| Stub | Value | Evidence |
|---|---|---|
| Vehicle speed, pedal | 0, valid → AvacStat1 runs only its standstill regulation | `LVL/ILCU_LevellingAdapter.c:413-428` |
| Ignition, network state | ignition on, powertrain active | `:446-453` |
| Vehicle configuration, mounting side | customer mode, left (master) | `:439-444`, `:455-462` |
| Right-side ECU, UDS routine control, NM | healthy constants | `:483-559`, `:321-326` |
| Coding block | DPE defaults, standstill thresholds 2 / 5 km/h | `:230-236`, `:397-402` |
| NvM, Dem | RAM only | `:328-343` |
| Zero-level programming | reported as done (0xFF) | `:226` |

### 2.4 Remaining dependencies on the removed Pitch module

| Dependency | Consumer | Now | Severity |
|---|---|---|---|
| `Rte_Read_Pitch_Angle` (`tPitch0`: angle, height error, quality) | `LVL/AvacStat1/AvacStat1Data.c:209-220` | adapter, IARA pitch | closed |
| `Rte_Read_Pitch_PlausState` (sensor plausibility) | `LVL/CtrlDcm/CtrlDcm_RteAccess.c:258-282`; drives Init→Fail, Adj→Fail, Fail→Adj (`LVL/CtrlDcm/CtrlDcmSm.c:551-651`) | constant `eNO_FAILURE` (`LVL/ILCU_LevellingAdapter.c:476-481`) | **major**: IARA has a plausibility output (`APP/swc_iara/include/IARA_TL_Types.h:256`) that is not exported |
| `NvmBlockDeltaPwmPara.ucZeroLevProg` (written by the DPE zero-level routine) | `LVL/AvacStat1/AvacStat1.c:162`; `LVL/CtrlDcm/CtrlDcm.c:204` | forced 0xFF | minor (demo) |
| `NvmBlockDeltaPwmPara.eNVM_VAC_Input`, `.eASL_Present`, `.snVehicleAttitude` | `LVL/AvacStat1/AvacStat1.c:667,847-848`; `LVL/CtrlDcm/CtrlDcm_Data.c:52`; `LVL/CtrlDcm/CtrlDcm_RteAccess.c:274,546` | adapter RAM block | minor |
| `Rte_Read_CodM_Pitch_Para` (coding, named after Pitch) | `LVL/AvacStat1/AvacStat1Data.c:55`; `LVL/CtrlDcm/CtrlDcm_Data.c:72` | adapter stub | minor |
| DTC `ZERO_LVL_PROG` | `LVL/AvacStat1/AvacStat1.c:159-170` | Dem stub | minor |
| Height-sensor DTCs (supply, short, plausibility) | DPE Pitch only (`DPE/Swc/Pitch/Pitch.c`) | gone; no IMU fault DTC replaces them | **major** for a product, minor for the demo |
| Dead code: CAN pitch alternative | `LVL/AvacStat1/AvacStat1Data.c:212` (`sPitchAmvar`, unused) | unused | minor |

---

## 3. What is missing

| # | Severity | Finding | Evidence | Fix |
|---|---|---|---|---|
| M1 | major | No zero reference from a real calibration. The adapter takes the attitude 1 s after the first usable sample as zero (RAM, demo behaviour). IARA's mounting-orientation table is all zero. `swc_imu` has no offset. | `LVL/ILCU_LevellingAdapter.c:162-176`; `PIARA_SensorOrientationCalibration_deg` is in `.bss` of `APP/swc_iara/lib/libiara.a`; `APP/swc_iara/swc_iara.c:82` | Demo: keep the board still for 2 s after reset. Product: IMU owner sets the orientation calibration; zero stored in NvM. |
| M2 | major | Pitch sign and axis are not established anywhere. `swc_imu` uses `atan2(-Ax, …)`; IARA's convention is inside the library. AvacStat1 needs front-up positive. | `APP/swc_imu/swc_imu.c:168-170`; `LVL/AvacStat1/AvacStat1Types.h:39` | Bench check V2 (§4.6); flip `ILCU_LVLADP_PITCH_SIGN` if needed (`LVL/ILCU_LevellingAdapter.h:53-55`). |
| M3 | major | A stalled IARA cannot be detected. Validity is only "IMU initialised". | `LVL/ILCU_LevellingAdapter.c:281-304`; no counter or status in `RTE/Rte_Iara.h` | Patch P4: export a sample counter and the IARA plausibility. |
| M4 | major | Nose-down never moves the lamp. AvacStat1 clamps the vehicle angle to 0…875 (0…5°). ASL only lowers the beam. Not a defect, but a demo that tilts the wrong way shows nothing. | `LVL/AvacStat1/AvacStat1.c:88-89`, `:388-395`, `:880-881` | Demo script: tilt front-up. |
| M5 | major | After a real pitch fault the lamp stays stopped until reset: the "ignition needed" latch needs an ignition-off cycle and ignition is a constant. | `LVL/CtrlDcm/CtrlDcm.c:255-259`; `LVL/ILCU_LevellingAdapter.c:446-453` | Read `COM_SIGNAL_ID_IGNITION_STATUS` (`CFG/bsw/Com/src/Com_Cfg.c`, signal table) in the adapter. Not done: no CAN source is confirmed for the demo. |
| M6 | major | The SBC watchdog is never serviced. The schematic note says the SBC resets the MCU unless it is in development mode. UNVERIFIED: no register semantics in the workspace. | no watchdog write in `APP/swc_sbc_demo/swc_sbc_demo.c`; `CFG/Al077HardwareSchematic.md:113,116` | Hardware: confirm JP1500 development mode on the demo board. |
| M7 | major | `IoHwAb_PwmLEDCTRL1_SetDutyCycle` passes a pointer where `IoHwAb_TimingSetDutyCycle` takes a value. Current clang rejects it; older armclang warns. Not levelling code, but it is in the same build. | `CFG/bsw/IoHwAb/IoHwAb_Cfg.c:79-90` (line 87); `SIB/bsw/IoHwAb/internal/IoHwAb_Internals.h:70-74` | Patch P7 |
| M8 | minor | KL15 and LWR feedback are unfiltered. DPE filtered both. The 20 ms loop has a ±3 ‰ dead band (about 7 ADC counts at 12 V). | `DPE/Bsw/IoHwAb/IoHwAbUser.c:530`, `:1371`; `CDD/CddDcm/Gen/CddDcmHal.c:132,325` | Only if the PWM dithers on the bench: set a filter in the IoHwAb channel config. |
| M9 | minor | PWM runs at 4 kHz; the schematic note recommends ≥ 10 kHz. The two RC stages (343 Hz each) and the 193 Hz feedback pole leave roughly 20 mV ripple at 4 kHz (my estimate). | `CFG/mcal/Pwm_Cfg/src/Pwm_PBcfg.c:106,110`; `CFG/Al077HardwareSchematic.md:138` | Patch P6 |
| M10 | minor | Config headers say "Project: St133, generated by EB Tresos", while the schematic note says the Al077a config is hand-maintained. A regeneration would revert manual edits. | `CFG/mcal/Pwm_Cfg/src/Pwm_PBcfg.c:61-68`; `CFG/Al077HardwareSchematic.md:158-160` | BSW owner states which is the source of truth. |
| M11 | minor | DPE defects carried over: adjustment counter never increments; one error flag cleared twice instead of both. | `LVL/AvacStat1/AvacStat1.c:760-761`; `CDD/CddDcm/Gen/CddDcmCtrl.c:835-836` | Report to DPE owners. |
| M12 | minor | 13 compiler warnings remain in copied DPE code (unused variables and functions). | Appendix B | Left as is. |

---

## 4. IMU angle chain

### 4.1 How much of the IMU software is done

Estimates from reading the code. None of it was run.

| Stage | Done | Evidence | Gap |
|---|---|---|---|
| Driver | 85 % | Init sequence WHO_AM_I → CTRL3 → CTRL1 → CTRL2, async state machine: `CDD/CddAsm330lhh/Gen/CddAsm330lhh.c:626`, `:739-843`; `Gen/CddAsm330lhh_Types.h:83-90` | No filter registers configured; self-test is a WHO_AM_I compare only. |
| Bus (SPI) | 90 % | Sequence 1, sequence-end callback wired: `CFG/mcal/Spi_Cfg/src/Spi_PBcfg.c:178`; routing `CFG/cdd/CddAsm330lhh/Cfg/CddAsm330lhh_RoutCfg.h:20-30` | UNVERIFIED on hardware. |
| Init | 90 % | `RTE/Rte.c:108`, status polled `:219-226` | — |
| Raw read | 85 % | 16-byte burst from STATUS_REG, decode: `CddAsm330lhh.c:813`, `:441-489` | Data-ready bits of the status byte are not checked. |
| Calibration | 5 % | Sensitivity constants only: `CddAsm330lhh.c:219-282` | No zero-g offset, no gyro bias, no mounting orientation. |
| Filtering | 15 % | None in `swc_imu`. IARA filters internally (complementary filter 0.2 Hz static / 2 Hz dynamic, read from the library data) but does not run (B3). | — |
| Fusion | 40 % | IARA library linked and called at 10 ms: `APP/swc_iara/swc_iara.c:86-119`. Model rate in the library is 100 Hz, which matches. | Starved of samples (B3). Wheel speeds, gear, brakes are constants: `swc_iara.c:69-82`. |
| Output signal | 35 % | `Rte_Iara_TargetPitch_cdeg` global and two CAN signals: `RTE/Rte.c:44,178-189` | No validity, no counter, no consumer until the adapter change. `swc_imu`'s pitch goes to CAN only (`RTE/Rte.c:191-210`). |
| Scheduling | 60 % | Both SWCs every 2nd 5 ms tick, same phase: `APP/swc_imu/swc_imu.c:150-155`; `APP/swc_iara/swc_iara.c:91-96` | Call order causes B3. `SamplePeriodMs` is hard-coded 10: `RTE/Rte.c:134`. |

Values read from `APP/swc_iara/lib/libiara.a` (`objdump -s`, little-endian, scaling from `APP/swc_iara/include/IARA_TL_Init.h:117,136,164,190` and `IARA_TL_Types.h`):

| Parameter | Raw | Value |
|---|---|---|
| `PIARA_ModelMainDatarate_Hz`, `PIARA_IMURawDatarate_Hz` | 0x6400 (2⁻⁸) | 100 Hz |
| `PIARA_PitchSaturationRange_rad` | 0x00D67750 (2⁻²⁸) | 0.05236 rad = 3.0° |
| `PIARA_FusionStaticCFFreq_Hz` / `Dynamic` | 0x00066666 / 0x00400000 (2⁻²¹) | 0.2 Hz / 2.0 Hz |
| `PIARA_SensorOrientationCalibration_deg[3]` | `.bss` | 0, 0, 0 |

### 4.2 What the IMU output physically is

| Signal | What it is | Suitable for static levelling |
|---|---|---|
| `swc_imu` `Pitch_cdeg` | Accelerometer tilt against gravity: `atan2(-Ax, sqrt(Ay² + Az²))`. No gyro, no filter. | Drift-free, so yes at standstill, but: it contains the road slope and the mounting tilt; the input is integer mg (`CddAsm330lhh.c:219-246`), so the angle moves in steps of about 1 mrad (5.7 cdeg), which is exactly AvacStat1's minimum-change threshold; and it is not readable by another SWC. **Not used.** |
| `swc_imu` `Yaw_cdeg` | Integrated gyro Z rate. Drifts. | Irrelevant. |
| `Rte_Iara_TargetPitch_cdeg` | IARA output `IARAPitch_rad` (Q28 rad) converted to 0.01°. Fused (accelerometer + gyro, complementary filter, gyro bias compensation, standstill algorithm), saturated at ±3°. | Intended replacement: its ±3° range equals DPE Pitch's ±524 (0.1 mrad) limits (`DPE/Swc/CodM/CodM_Para_AvacStp.h`, `NVMPARA_AVACSTP_PITCHDATA_INIT`). **Used by the adapter.** Whether it is body-to-road or body-to-gravity is inside the library: §8 Q1. |

Gyro drift: not an issue for the accelerometer tilt. For IARA it is handled inside the library (bias compensation parameters exist, `IARA_TL_Init.h:115-117`); UNVERIFIED. Mounting orientation: not handled anywhere (M1).

### 4.3 What AvacStat1 expects

| Property | Value | Evidence |
|---|---|---|
| Type | `sint16` in `tPitch0.nAngle` | `LVL/ILCU_LevellingAdapter.h` (`tPitch0`); `LVL/AvacStat1/AvacStat1Types.h:37-42` |
| Unit, resolution | 0.1 mrad per LSB (0.00573°) | `LVL/AvacStat1/AvacStat1Types.h:39`; `LVL/AvacStat1/AvacStat1Data.c:217` |
| Sign | front side up = positive | `LVL/AvacStat1/AvacStat1Types.h:39`; `DPE/Swc/Pitch/Pitch_Types.h:44` |
| Axis | vehicle pitch (rotation about the lateral axis); DPE computed it as (front − rear height) / wheelbase | `DPE/Swc/Pitch/Pitch.c:259-281` |
| Range delivered by DPE Pitch | ±524 (±3°) | `DPE/Swc/CodM/CodM_Para_AvacStp.h`, `NVMPARA_AVACSTP_PITCHDATA_INIT` |
| Range used | 0…875 (0…5°); negative clamps to 0 | `LVL/AvacStat1/AvacStat1.c:88-89,388-395` |
| Sampling | every 100 ms (5 × 20 ms); the instantaneous value is used, no averaging in standstill mode | `LVL/AvacStat1/AvacStat1.c:71,680-687,725` |
| Quality | `teRte_SigQty`: not VALID freezes regulation; INVALID outputs the safety angle and CtrlDcm fails | `LVL/AvacStat1/AvacStat1.c:721-724,806`; `LVL/CtrlDcm/CtrlDcm_RteAccess.c:213-225` |
| Minimum change | 10 (1 mrad), held for the load-change interval | `LVL/AvacStat1/AvacStat1Init.c:40`; `LVL/AvacStat1/AvacStat1.c:516-549` |
| DPE source | filtered displacement sensors, updated every 20 ms | `DPE/Swc/Pitch/Pitch.c:240`; `DPE/Rte/Eco/Rte_Cfg.c:103` |

### 4.4 Mismatch table

| Field | IMU side (`Rte_Iara_TargetPitch_cdeg`) | AvacStat1 side | Conversion | Where |
|---|---|---|---|---|
| Type | `volatile sint32` | `sint16` | clamp, cast | `LVL/ILCU_LevellingAdapter.c:287-301` |
| Unit | 0.01° | 0.1 mrad | × 349 / 200 (1.745; exact factor 1.74533, error 0.02 %) | `:301`, `:36-39` |
| Resolution | 0.01° = 0.175 mrad | 0.1 mrad | none needed; coarser than the LSB, finer than the 1 mrad threshold | — |
| Sign | unknown | front up positive | `ILCU_LVLADP_PITCH_SIGN` | `:145`; `LVL/ILCU_LevellingAdapter.h:53-55` |
| Axis | sensor X assumed longitudinal; mounting unknown | vehicle pitch | none in software; IMU owner | §8 Q2 |
| Range | ±300 (IARA saturation) | 0…875 used | none; AvacStat1 clamps | — |
| Rate | 10 ms | read every 100 ms | adapter samples at 20 ms and low-passes (320 ms) | `:148-160` |
| Zero | unknown reference, mounting tilt included | 0 = nominal attitude | zero taken at start or on request | `:162-176` |
| Validity | none | `teRte_SigQty` | INIT / VALID / INVALID with timeouts | `:178-201` |
| Freshness | none | implicit | **not solvable in the adapter** | patch P4 |

### 4.5 Conversion code

Implemented, not just proposed: `LVL/ILCU_LevellingAdapter.c:281-304` (source) and `:130-202` (conditioning). The core:

```c
sint32 Pitch_cdeg = Rte_Iara_TargetPitch_cdeg;            /* 0.01 deg */
/* clamp to +-18000, then */
*Pitch_0p1mrad = (sint16)((Pitch_cdeg * 349) / 200);      /* 0.1 mrad */
return (Rte_ImuInitResult == E_OK) ? E_OK : E_NOT_OK;
```

To take the pitch from another module instead, define `ILCU_LVLADP_EXTERNAL_PITCH_SOURCE` in the build and implement `ILCU_LevellingAdapter_GetPitchAngle` there. The conditioning stays in the adapter.

### 4.6 Validation

Host harness results (real chain, real Al077a IoHwAb config, model of the real stage, KL15 = 12.0 V). Each row was held 4 s:

| Pitch at the source | Adapter out (0.1 mrad) | AvacStat1 `Ver` (0.01°) | CtrlDcm target | CddDcm level | PWM duty | LWR_DC |
|---|---|---|---|---|---|---|
| 0° | 0 | 0 | 0 | 200 ‰ | 140 ‰ | 2406 mV |
| +1.00° | 174 | −100 | −100 | 400 ‰ | 278 ‰ | 4778 mV |
| +2.00° | 349 | −200 | −200 | 600 ‰ | 419 ‰ | 7202 mV |
| +3.00° | 523 | −300 | −300 | 800 ‰ | 559 ‰ | 9609 mV |
| +4.00° | 698 | −400 | −300 (clamped) | 800 ‰ | 559 ‰ | 9609 mV |
| −1.00° | −174 | 0 (clamped) | 0 | 200 ‰ | 140 ‰ | 2406 mV |

Rule: LWR_DC = level × KL15, level = 200 ‰ + 2 ‰ per 0.01° of lowering, limits 200…800 ‰.

Bench checks, in this order, actuator disconnected until V5 passes:

| # | Check | How | Pass |
|---|---|---|---|
| V1 | Chain alive | watch `ILCU_LvlAdp_TimeUs` | +5000 per 5 ms |
| V2 | Chain without the IMU | debugger: `ILCU_LvlAdp_BenchPitch_0p1mrad = 349`, `ILCU_LvlAdp_BenchPitchEnable = 1` | after about 2 s `ILCU_LvlAdp_AvacStat1Out.Position[0].Ver = -200`; DVM on LWR_DC = 0.600 × KL15 |
| V3 | KL15 reading | bench supply 13.50 V; watch the value `Rte_Read_IoHwAb_User_GetAdc_DIAG_VBAT` returns | 13.5 V ± 2 % (lower by one diode drop if the divider sits after D1500) |
| V4 | Pitch sign | bench override off; tilt the board front-up by a known angle | `ILCU_LvlAdp_PitchOut` positive, about 175 per degree |
| V5 | Ratiometric | repeat V2 at 11 V and 15 V | LWR_DC / KL15 = 0.600 ± 0.005 |
| V6 | Boot state | scope PA3, PA2, LWR_DC from power-on | LWR_DC stays 0 V until the first move |
| V7 | End of move | wait about 21 s after the first move starts | EN low, LWR_DC 0 V |

---

## 5. Hardware path per module

Path for all levelling signals: CddDcm → adapter → IoHwAb → MCAL → pin → AVAC stage → connector X0001 pin 5 (LWR_DC). There are no direction pins and no position sensor: the "DC motor" is a levelling actuator with its own position control, commanded by an analog voltage that is a ratio of KL15. The ADC "feedback" is a read-back of that command voltage, not of the lamp position.

### 5.1 Schematic against code

Checked against the two photos. Every levelling net matches the code's pin choice.

| Net (schematic) | MCU pin | Code | Verdict |
|---|---|---|---|
| `HW_IF_TIMG9_C1_CTRL_LWR` | PA2, pin 8 | Port mode `TIMG9_CCP1`, PINCM 7: `CFG/mcal/Port_Cfg/src/Port_PBcfg.c:735-763`; PWM channel 17, `gpioPin 2`: `CFG/mcal/Pwm_Cfg/src/Pwm_PBcfg.c:103-109` | match |
| `HW_IF_PA3_EN_LWR` | PA3, pin 9 | GPIO output, PINCM 8, Dio channel 3: `Port_PBcfg.c:679-707`; `CFG/mcal/Dio_Cfg/include/Dio_Cfg.h:186` | match; initial level wrong (§5.4) |
| `HW_IF_A0_1_FB_LWR` | PA15, pin 30 | Port mode `ADC1_0`: `Port_PBcfg.c:105-133`; ADC group 1, first channel 0: `CFG/mcal/Adc_Cfg/src/Adc_PBcfg.c:172` | match. The net name says "A0_1" but the generated pin mode is ADC1 channel 0; the name is misleading, the code is consistent. |
| `HW_IF_A0_5_KL15` | PB24, pin 42 | Port mode `ADC0_5`: `Port_PBcfg.c:192-220`; ADC group 0, first channel 5: `Adc_PBcfg.c:121` | match at MCAL level; IoHwAb mapping wrong (§5.2) |
| SPI0, CAN0, crystal, SWD, BSL | PA7, PB2, PB3, PA8, PB6, PA12, PA13, PA5, PA6, PA19, PA20, PA10, PA11 | all present in `Port_PBcfg.c` (pin names at `:272-647`) | match |

Minor: `Port_PinId` values (42, 43, 8, …) follow a 64-pin package numbering, not the 48-pin package on the schematic; PINCM numbers are what select the pad. PA18 (BSL_invoke) and the 24 not-connected pins have no Port entry, although `Al077HardwareSchematic.md:165` says all 44 pins are configured.

### 5.2 Adc

| Item | Value | Evidence |
|---|---|---|
| Groups | group 0 = ADC0 {ch5 KL15, ch6 NTC}; group 1 = ADC1 {ch0 LWR feedback, ch2 5V0} | `CFG/mcal/Adc_Cfg/src/Adc_PBcfg.c:92-193` |
| Mode | one-shot, software trigger, single access, 12 bit, VDDA reference, interrupt access | `:100-104`, `:112`, `:122`, `:201` |
| Interrupts | ADC0 and ADC1 enabled | `CFG/bsw/EcuM/EcuM_Interrupts.c:75-76` |
| Result buffers | registered by IoHwAb at init | `SIB/bsw/IoHwAb/internal/IoHwAb_Analog.c:83-92` |
| Scaling | 82.5k/15k divider, × 6.5, full scale 21.45 V, 5.24 mV per count | `CFG/Al077HardwareSchematic.md:122,124` (ADC page not in the photos: UNVERIFIED) |

| Severity | Problem | Fix |
|---|---|---|
| blocker, worked around | Nothing starts the groups (C2). | Adapter starts them. Clean fix: patch P5b. |
| minor | `ADC_BUSY` and restart from `ADC_STREAM_COMPLETED` are AUTOSAR behaviour; UNVERIFIED for the TI MCAL (no TI headers in any tree). `swc_adc_test` uses `ADC_STREAM_COMPLETED`, so the enum is the AUTOSAR one. | Check `Adc.h` when building. |

### 5.3 IoHwAb

| Channel | Config | Problem | Severity |
|---|---|---|---|
| `IOHWAB_CHID_VBAT` (KL15) | group 0, **slot 4**, slope 82.5k/21k | Slot never written: 0 mV. Slope would also be wrong (× 4.93 instead of × 6.5). `CFG/bsw/IoHwAb/IoHwAb_AnalogCfg.c:251-260` | blocker, worked around (C1) |
| `IOHWAB_CHID_ADIN_3` (LWR feedback) | group 1, slot 0, slope 82.5k/21k | Right slot, reads 24 % low (harness: 5457 mV for 7202 mV). `:91-100`, `:53-64` | major, worked around |
| `IOHWAB_CHID_HSS_SENSE_1_2` | group 0, slot 0, no conversion | This is where KL15's counts actually are. The adapter reads it raw. `:171-180` | — |
| `IOHWAB_CHID_CTRL_LWR` | PWM channel 17 | Correct. `CFG/bsw/IoHwAb/IoHwAb_TimingCfg.c:40-46` | — |
| `IOHWAB_CHID_EN_LWR` | Dio PA3, output | Correct. `CFG/bsw/IoHwAb/IoHwAb_DigitalCfg.c:39-46` | — |
| Other 17 analog and 9 timing entries | pins this board does not have | Table belongs to a larger board (comments name a 64-pin package). Harmless, except that it is why KL15 landed in slot 4. | minor |

Clean fix for the BSW owner: patch P5a. When it lands, change the two channel-ID macros in `LVL/ILCU_LevellingAdapter.h:77-82`. If the IDs are renamed the adapter stops compiling, which is intended.

### 5.4 PWM and Port

| Parameter | Current | Required | Evidence | Severity |
|---|---|---|---|---|
| PA3 initial level | HIGH (stage enabled) | LOW | `CFG/mcal/Port_Cfg/src/Port_PBcfg.c:683`; schematic: R8010 pull-down means "off by default" | major |
| PWM initial duty | 0x4000 (50 %) | 0 | `CFG/mcal/Pwm_Cfg/src/Pwm_PBcfg.c:111` | major |
| PWM period | 0x2710 = 10000 ticks → 4 kHz at 40 MHz | 2000 ticks → 20 kHz | `:106,110` | minor |
| Polarity / idle | high / low | as is | `:112-113` | — |
| Channel class | `PWM_VARIABLE_PERIOD` | as is. AUTOSAR lets `Pwm_SetDutyCycle` reactivate either class after `Pwm_SetOutputToIdle` (from memory of the specification; UNVERIFIED for the TI MCAL). The change list's M4 is not needed on that basis. | `:114` | open, §8 Q6 |
| TIMG9 clock | `BUSCLK`; PWM config assumes 40 MHz | measure | `CFG/mcal/Mcu_Cfg/src/Mcu_PBcfg.c:222-223` | open, §8 Q5 |

With PA3 high and 50 % duty, LWR_DC sits at about 8.6 V from `Port_Init`/`Pwm_Init` until `Rte_Start`. An actuator would move at every power-on. The adapter cannot close that window; patch P6 does.

Duty range used: 200…800 ‰ of KL15 on the output, which is 140…560 ‰ PWM duty at 12 V. CddDcm limits its set level to 80…920 ‰ and the PWM to 1000 ‰ (`CDD/CddDcm/Gen/CddDcmHal.c:114-120`).

### 5.5 AVAC output stage (from the schematic photo)

- CTRL_LWR → R8001 46.4 k → C8001 10 nF → R8002 46.4 k → C8002 10 nF → op-amp IN+. Two low-pass stages at about 343 Hz.
- **R8004 10 k goes from the CTRL_LWR node (before R8001) to ground.** It holds the pin low while the MCU pin is high-impedance. It does not divide the PWM.
- IC8000 (NCV20071), supplied from VBAT_RPP through R8000 100 Ω. Non-inverting: R8007 82.5 k ∥ C8003 10 nF feedback, R8009 19.6 k to ground. Gain 1 + 82.5/19.6 = **5.21**.
- T8000 (BC807, PNP): emitter 3.3 V, collector on the feedback node, base from EN_LWR through R8008 46.4 k, R8010 10 k pull-down. EN low → T8000 on → IN− at 3.3 V → output 0 V. EN high → off → stage follows the PWM. **Active high**, matches `LVL/ILCU_LevellingAdapter.c:348-351`.
- Output through R8003 ∥ R8005 (1.5 k), C8004 22 nF to GND_EXT → LWRDC.

Transfer: **LWR_DC = D × 3.3 V × 5.21 = D × 17.19 V**, limited by the supply (KL15 minus the reverse-polarity diode).

- Severity **major** (documentation): `CFG/Al077HardwareSchematic.md:131-132` states D × 3.05 V. That figure caused the hardware-change request in the PDFs. It is wrong. Fix: patch P8.
- CddDcm's constant is 17.32 V (`CDD/CddDcm/Gen/CddDcmHal.c:138-141`). Feed-forward is 0.75 % high; the 20 ms loop corrects it (`:316-344`). No code change.

### 5.6 Init order

`EcuM_AL_DriverInitOne`: `Port_Init` ×5 → `Spi_Init` → CAN stack → `Gpt_Init` → `Adc_Init` → `Pwm_Init` → `Icu_Init` → Fee/Fls/NvM → `IoHwAb_Init` → interrupts → SBC demo (`CFG/bsw/EcuM/EcuM_Callout_Stubs.c:170-204`). `Rte_Start` runs later, so the adapter's `Init` (after patch P1) finds IoHwAb ready. `MainFunction` is guarded against running before `Init` (`LVL/ILCU_LevellingAdapter.c:260`).

---

## 6. Configuration to change

Values already set in `swc_levelling` (yours; change by macro, no code edit):

| File | Parameter | Value | Reason / rule |
|---|---|---|---|
| `LVL/ILCU_LevellingAdapter.h:54` | `ILCU_LVLADP_PITCH_SIGN` | 1 | −1 if bench check V4 shows front-up negative |
| `:57` | `ILCU_LVLADP_PITCH_FILTER_SHIFT` | 4 (320 ms) | keeps the 1 mrad comparison stable; raise if the lamp hunts |
| `:60` | `ILCU_LVLADP_PITCH_STARTUP_TIMEOUT` | 250 (5 s) | longer than the IMU init |
| `:63` | `ILCU_LVLADP_PITCH_INVALID_DEBOUNCE` | 25 (500 ms) | a fault after this stops the lamp until reset |
| `:66`, `:69` | `ILCU_LVLADP_PITCH_AUTO_ZERO`, `_ZERO_SETTLE` | ON, 50 (1 s) | demo; OFF for an absolute pitch |
| `:78`, `:81` | `ILCU_LVLADP_KL15_RAW_CHID`, `_LWRFB_RAW_CHID` | `IOHWAB_CHID_HSS_SENSE_1_2`, `IOHWAB_CHID_ADIN_3` | follow the IoHwAb table |
| `:84` | `ILCU_LVLADP_ADC_FULLSCALE_MV` | 21450 | 3300 × (82.5 + 15) / 15; adjust after bench check V3 |
| `:90` | `ILCU_LVLADP_START_ADC_GROUPS` | ON | OFF once IoHwAb starts the groups |
| `:95` | `ILCU_LVLADP_LOAD_CHANGE_INTERVAL` | 20 (2 s) | DPE value 100 (10 s) |
| `LVL/ILCU_LevellingAdapter.c:235-236` | standstill speed thresholds | 2 / 5 km/h | DPE defaults 0 / 0 block standstill levelling |
| `LVL/AvacStat1/AvacStat1Init.c:40` | min change at power-on / light-on / load change | 30 / 10 / 10 (0.1 mrad) | DPE, unchanged |
| coding stub (`NVMPARA_AVACSTP_DCMOTORDATA_INIT`, `LVL/ILCU_LevellingAdapter.h`) | adjust range, safety position | −300…0, −32 (0.01°) | DPE, unchanged |
| `CDD/CddDcm/Gen/CddDcmCtrl.h:36-49` | position range, threshold, error time | 200…800 ‰, 5 ‰, 500 ms | DPE, unchanged |

Values owned by others:

| File | Parameter | Current | Required | Reason |
|---|---|---|---|---|
| `CFG/mcal/Port_Cfg/src/Port_PBcfg.c:683` | PA3 `Port_PinLevelValue` | `PORT_PIN_LEVEL_HIGH` | `PORT_PIN_LEVEL_LOW` | stage off at boot |
| `CFG/mcal/Pwm_Cfg/src/Pwm_PBcfg.c:111` | `.dutyCycle` | `0x4000U` | `0x0000U` | no output before software decides |
| `CFG/mcal/Pwm_Cfg/src/Pwm_PBcfg.c:110` | `.hwPeriod` | `0x2710` | `2000U` (if TIMG9 runs at 40 MHz) | 20 kHz, less ripple |
| `CFG/bsw/IoHwAb/IoHwAb_AnalogCfg.c:255` | KL15 source | `IOHWAB_ADC_SOURCEID(0U, 4U)` | `(0U, 0U)` | the slot the ADC writes |
| `CFG/bsw/IoHwAb/IoHwAb_AnalogCfg.c:259`, `:99` | KL15 and LWR feedback slope | 32536 / 13 | 21455 / 12 | × 6.5 divider: 4095 counts → 21450 mV; fits `sint16` |
| `APP/swc_iara` (library coding) | sensor orientation calibration | 0, 0, 0 | measured mounting angles | pitch axis and zero |
| `RTE/Rte.c:134` | `SamplePeriodMs` | 10 (constant) | derived from the real period | yaw integration only; not levelling |

---

## 7. Ordered action plan

Smallest step first. Steps 1 to 4 need no hardware.

| # | Step | Owner | Done when |
|---|---|---|---|
| 1 | Copy the six edited files from `LVL/` into the real repository. | you | diff against this snapshot is empty |
| 2 | Add the CustVar lines (P9), rebuild. | build | 13 new objects; only the 13 known warnings in the port folders |
| 3 | Apply P7 if the build stops at `IoHwAb_Cfg.c:87`. | BSW | file compiles |
| 4 | Apply P1 (`Rte.c` hook) and P2 (remove the `swc_imu` motor output) together. | integration, IMU | map file contains `rpAvacStat1_Cycle0`; bench check V1 |
| 5 | Bench checks V2, V3, V5 with the debugger override, actuator disconnected. | you | LWR_DC = level × KL15 |
| 6 | Apply P6 (boot defaults). | BSW | bench check V6 |
| 7 | Apply P3 (IARA sample starvation). | IMU | `Rte_Iara_TargetPitch_cdeg` changes when the board is tilted |
| 8 | Bench check V4; set `ILCU_LVLADP_PITCH_SIGN`. | you, IMU | front-up gives a positive `ILCU_LvlAdp_PitchOut` |
| 9 | Connect the actuator. Demo: reset, keep still 2 s, tilt front-up 1 to 3°, hold 3 s. | you | beam lowers; returns when levelled |
| 10 | Apply P5 (IoHwAb table, ADC start) and switch the adapter macros back. | BSW, you | bench check V3 still passes with `ILCU_LVLADP_START_ADC_GROUPS` OFF |
| 11 | P4 (validity export), then real ignition and speed from CAN, then NvM. | IMU, you | after the demo |

---

## 8. Open questions

For the IMU integrator:

| # | Question | Why it matters |
|---|---|---|
| Q1 | Is `IARAPitch_rad` body-to-road or body-to-gravity, and what is its sign for front-up? What does it do when the board is tilted by hand at standstill with wheel speeds fixed at 0? | Decides whether the demo responds at all, and the sign macro. |
| Q2 | How is the ASM330LHH mounted: which sensor axis points forward, which up? Will `PIARA_SensorOrientationCalibration_deg` be set? | Pitch versus roll, sign, zero. |
| Q3 | Will `swc_imu` stop driving EN_LWR and the LWR PWM (P2)? | B2. |
| Q4 | Can a sample counter and `IARAPitchPlausibility_en` be exported next to the pitch (P4)? | Stale-data detection, sensor fault path. |
| Q5a | Are `APP/swc_iara/src/IARA_TL.c` and `IARA_TL_Data.c` in the build? They define `IARA_TL_U` / `IARA_TL_Y`, which `libiara.a` also defines, and include headers that are not in the workspace (`AL_Helper.h`, `IARA_TL_Data.h`). | Possible duplicate definitions; not levelling, but same image. |

For the hardware / BSW team:

| # | Question | Why it matters |
|---|---|---|
| Q5 | Is TIMG9 clocked at 40 MHz or 80 MHz? | PWM frequency is 4 or 8 kHz today; 20 or 40 kHz after P6. |
| Q6 | Does the TI `Pwm_SetDutyCycle` bring the channel back after `Pwm_SetOutputToIdle`? | CddDcm idles the PWM after every move. If not, the second move produces no output. |
| Q7 | ADC page: are the KL15 and LWR feedback dividers both 82.5k/15k, and does the KL15 divider sit before or after D1500? Where is the feedback tapped: at the op-amp output or after the 1.5 k series resistors? | Scale constant; a ratio error of one diode drop; load compensation. |
| Q8 | Which actuator is on LWR_DC, what is its input impedance, and does it hold position with 0 V on the control line after a move? | 1.5 k source resistance; CddDcm switches the output off after each move. |
| Q9 | Is the demo board in SBC development mode (JP1500), or must the watchdog be served? | A periodic reset would look like a levelling fault. |
| Q10 | Is the Al077a MCAL configuration generated or hand-edited? | Whether P6 survives a regeneration. |

Could not be determined from the workspace: anything about `Build/`, the TI MCAL sources, the full schematic PDF (`docs/vsch_FEH0019576_variant.pdf`, referenced but absent), and the inside of `libiara.a` beyond its data sections.

---

## Appendix A: patches for other owners

None of these was applied or compiled. All UNVERIFIED.

**P1 — `RTE/Rte.c`, integration.** Three lines.

```c
#include "IoHwAb_Cfg.h"
#include "ILCU_LevellingAdapter.h"                 /* add */

FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void)
{
  Std_ReturnType RetVal;

  ILCU_LevellingAdapter_Init();                    /* add: IoHwAb_Init already ran in EcuM_AL_DriverInitOne */
  swc_imu_init();

TASK(BasicTask)
{
  IoHwAb_MainFunction();
  ILCU_LevellingAdapter_MainFunction();            /* add: every 5 ms, after IoHwAb refreshed its inputs */
```

**P2 — `APP/swc_imu/swc_imu.c`, IMU.** Minimum: delete line 188 (`SwcImu_UpdateMotorOutput(Angles.Pitch_cdeg);`) and lines 134-138 (the two `Rte_Call_ImuMotor_*` calls in `swc_imu_init`). Clean: also remove `SwcImu_PitchToDutyPermille`, `SwcImu_UpdateMotorOutput`, `SwcImu_MotorOutputStatus` (`:12-44`), `Rte_Call_ImuMotor_SetEnable/SetDutyPermille` (`RTE/Rte.c:144-157`) and their prototypes (`RTE/Rte_Imu.h:30-31`).

**P3 — `RTE/Rte.c`, IMU.** One fetch, two consumers.

```c
static Rte_ImuSampleType Rte_ImuSample;      /* last sample taken from the CDD */
static uint8             Rte_ImuSampleNew;   /* bit 0: not yet read by swc_imu, bit 1: by swc_iara */

static void Rte_ImuSample_Fetch(void)
{
  CddAsm330lhh_ScaledDataType SensorData;

  if (CddAsm330lhh_GetLatestSample(&SensorData) == E_OK)
  {
    Rte_ImuSample.AccelX_mg  = SensorData.Ax_mg;
    Rte_ImuSample.AccelY_mg  = SensorData.Ay_mg;
    Rte_ImuSample.AccelZ_mg  = SensorData.Az_mg;
    Rte_ImuSample.GyroX_mdps = SensorData.Gx_mdps;
    Rte_ImuSample.GyroY_mdps = SensorData.Gy_mdps;
    Rte_ImuSample.GyroZ_mdps = SensorData.Gz_mdps;
    Rte_ImuSample.Temp_cdeg  = SensorData.Temp_cdeg;
    Rte_ImuSample.SamplePeriodMs = 10u;
    Rte_ImuSampleNew = 0x03u;
  }
}

Std_ReturnType Rte_Read_ImuSensor_Sample(Rte_ImuSampleType* SamplePtr)
{
  Std_ReturnType RetVal = E_NOT_OK;

  if (SamplePtr != NULL_PTR)
  {
    Rte_ImuSample_Fetch();
    if ((Rte_ImuSampleNew & 0x01u) != 0u)
    {
      *SamplePtr = Rte_ImuSample;
      Rte_ImuSampleNew &= (uint8)~0x01u;
      RetVal = E_OK;
    }
  }
  return RetVal;
}
/* Rte_Read_Iara_ImuSample: same, with bit 0x02u, copying the six accel/gyro fields */
```

**P4 — `RTE/Rte.c`, `RTE/Rte_Iara.h`, `APP/swc_iara/swc_iara.c`, IMU.** Next to `Rte_Iara_TargetPitch_cdeg`, export `volatile uint8 Rte_Iara_PitchCounter` (incremented in `Rte_Write_Iara_TargetPitch`) and `volatile uint8 Rte_Iara_PitchPlausible` (from `IARA_TL_Y.IARAPitchPlausibility_en == Iara_SignalValid`). The adapter can then return `E_NOT_OK` when the counter stops, and feed `Rte_Read_Pitch_PlausState`.

**P5a — `CFG/bsw/IoHwAb/IoHwAb_AnalogCfg.c`, BSW.**

```c
/* 82.5k/15k divider, 3V3 reference: 4095 counts = 21450 mV; raw * 21455 >> 12 */
STATIC CONST(IoHwAb_AnalogLinearConvParamsType, IOHWAB_CONST) IoHwAb_ConvParam_Linear_x6p5 = { 0, 21455, 12 };

/* KL15 (IOHWAB_CHID_VBAT):       IOHWAB_ADC_SOURCEID(0U, 0U), &IoHwAb_ConvParam_Linear_x6p5 */
/* LWR feedback (IOHWAB_CHID_ADIN_3): IOHWAB_ADC_SOURCEID(1U, 0U), &IoHwAb_ConvParam_Linear_x6p5 */
```

Do not use 42910 / 13 from the earlier change list: `SlopeNum` is `sint16`.

**P5b — platform `IoHwAb_Analog.c`, BSW.** In `IoHwAb_AnalogMainFunction`, after the copy loop, restart each configured ADC group that is not busy. Then set `ILCU_LVLADP_START_ADC_GROUPS` to `STD_OFF`.

**P6 — MCAL config, BSW.** `Port_PBcfg.c:683` → `PORT_PIN_LEVEL_LOW`. `Pwm_PBcfg.c:111` → `0x0000U`; `:110` → `2000U`.

**P7 — `CFG/bsw/IoHwAb/IoHwAb_Cfg.c:87`, BSW.** `IoHwAb_TimingSetDutyCycle(IOHWAB_CHID_LEDCTRL1, *DutyCycle);` or change the wrapper to take the value, as `IoHwAb_PwmCTRL_LWR_SetDutyCycle` does (`:71-77`).

**P8 — `CFG/Al077HardwareSchematic.md`, docs.** §7: R8004 is a pull-down on CTRL_LWR; IN+ = D × 3.3 V; output = D × 17.19 V. §10: align the Pwm/IoHwAb/Port rows with the checked-in configuration (period 10000, duty 50 %, IoHwAb table of 20 channels, 19 pins configured).

**P9 — build tree.** As in `LVL/PORT_CHANGES.md` §2, in `Build/Make/Cust/Al/Al077a/App/CustVar_030_Flags.gmk` and `CustVar_050_Files.gmk`: include both fragment pairs (`IlcuLevelling_030/050`, `CddDcm_030/050`), prepend their include lists, append their file lists.

## Appendix B: verification evidence

All on the host (Apple clang, macOS), 2026-11-11.

1. **Warning check.** 13 chain sources, `--target=thumbv6m-none-eabi -mcpu=cortex-m0plus -std=gnu17 -fshort-enums -ffreestanding -Os -fno-inline-functions -Wall -fsyntax-only`, stand-in headers for `Std_Types.h`, `Adc.h`, `Dio.h`, `Pwm.h`, `Icu.h`, `AL_Filter.h`, `stdlib.h`; real `IoHwAb` headers and Al077a config. Result: **0 errors, 13 warnings, 0 in the adapter.** `-Wextra` adds 1, in DPE code. Before the CtrlDcm fix the count was 20; the 7 `-Wsometimes-uninitialized` warnings are gone.
2. **Behaviour harness.** Compiled natively: the 13 chain sources, the adapter, `SIB/bsw/IoHwAb/*.c` (4 files) and `CFG/bsw/IoHwAb/*.c` (4 files). Faked: MCAL calls and the two RTE globals. Hardware model: D × 17190 mV limited to KL15 − 0.7 V, EN gating, × 6.5 dividers, ADC results only when a conversion is started. Tick order: `IoHwAb_MainFunction()`, `ILCU_LevellingAdapter_MainFunction()`.

| Scenario | Result (identical at `-O0` and `-O2`) |
|---|---|
| S1 validation table | table in §4.6; after the move: EN low, duty 0, 0 V |
| S2 IMU ready after 3 s | `SIG_INIT`, phase Adj, target not stopped; afterwards Ver −200, 7202 mV |
| S3 IMU never ready | INIT until 5 s; then INVALID, phase Fail, target −32, lamp at 3162 mV |
| S4 KL15 7 V then 15 V | output off; then 9007 mV = 600 ‰ of 15 V |
| S5 dropout 300 ms, then 1 s | held VALID; then INVALID and Fail; after recovery phase Adj, target stopped |
| S6 IoHwAb path vs adapter | `IoHwAb_VoltageKL30_Read` 0 mV, adapter 11995 mV; IoHwAb feedback 5457 mV, adapter 7197 mV, pin 7202 mV |
| S7 debugger override 349 | Ver −200, 7202 mV |
| S8 LWR_DC short to ground | `DCMotor_SC_GND` FAILED, phase Fail, output off |

3. **Controls.** With `ILCU_LVLADP_START_ADC_GROUPS=STD_OFF`: KL15 reads 0 mV, output never enables (S7 fails), as expected. With the original CtrlDcm files, S5 gave the same transcript at `-O0` and `-O2` on this compiler, so the fix removes undefined behaviour and warnings but I could not show a behaviour difference.
4. **Not covered.** armclang, the TI MCAL, RTX, interrupt timing, the board, the actuator. The harness build needed `-Wno-int-conversion` because of M7.
