# Copilot instructions for this repository

## Build, test, and static-analysis commands

Use **Windows CMD/PowerShell** and run build commands from `Build\VS` (paths in makefiles are relative to that directory).

### Build Al077a application

```bat
cd Build\VS
..\Build.bat H00 MSPM0G_3518 ARM_KEIL CUnit GCOV M0P Al077a App default NonKey all
```

For a clean rebuild, replace the last argument with `rebuild`.

### Run all configured tests

```bat
cd Src\src_AL\ecu9_core_ptf\CI\Support
60_run_all_tests.bat
```

### Run a single test

```bat
cd Src\src_AL\ecu9_core_ptf\CI\Support
run_one_test.bat Mt_ApplBenchmark Unit CUnit
```

### Static analysis / lint-like checks

```bat
cd Src\src_AL\ecu9_core_ptf\CI\Support
50_run_qac.bat
51_run_axivion.bat
69_code_style_check_report.bat
```

## High-level architecture

- **Build system:** `Build\Build.bat` maps 11 positional parameters into `TYP_*` variables, then `Build\Make\Make.bat` expands `TYP_RULE` into `Clean/Prepare/Build/Finalize` phases and executes `make` on `Build\Make\Make_000.gmk`.
- **Source ownership split:**
  - Reusable platform/core code: `Src\src_AL\ecu9_core_ptf\Src\...`
  - Project application/CDD/RTE code: `Src\src_AL\app`, `Src\src_AL\cdd`, `Src\src_AL\rte`
  - Project-specific configuration: `Src\config_AL\Al\Al077a\...` (MCAL, BSW, CDD cfg, app entrypoint)
- **Runtime data flow:** `main()` (`config_AL\...\app\main.c`) starts EcuM/OS; `Rte.c` `BasicTask` orchestrates IoHwAb/Fee/NvM, SBC init (`swc_sbc_demo`), ASM330LHH CDD state machine, IMU SWC (`swc_imu`), COM TX, and CAN polling.
- **IMU path:** CDD (`CddAsm330lhh`) acquires/scales sensor data over SPI asynchronously, RTE adapts it via `Rte_Imu*`, and `swc_imu` computes roll/pitch/yaw then writes COM signals.

## Key repository conventions

- **Do project integration edits in variant makefiles first:** update `Build\Make\Cust\Al\Al077a\App\CustVar_030_Flags.gmk` (includes/defines) and `CustVar_050_Files.gmk` (source lists). This is where app, CDD, BSW, and MCAL pieces are selected for the Al077a variant.
- **Keep variability in `config_AL`:** Al077a-specific config and generated post-build artifacts live under `Src\config_AL\Al\Al077a`; keep reusable logic under `src_AL` / `ecu9_core_ptf`.
- **Follow asynchronous SPI integration pattern:** both SBC demo and ASM330LHH use `Spi_AsyncTransmit` + sequence-end callbacks (`swc_sbc_demo_SpiSequenceEndNotification`, `CddAsm330lhh_SequenceEndNotification`) and are progressed in periodic main functions/state machines.
- **Respect fixed-point units across layers:** IMU contracts use `mg`, `mdps`, and `cdeg` (`Rte_Imu.h`, `swc_imu.c`, `CddAsm330lhh` types); preserve these units and conversion boundaries when changing interfaces.
- **CAN start is gated by SBC readiness:** `swc_sbc_demo` validates SBC register write/readback before requesting `CAN_CS_STARTED`; this ordering is part of system bring-up behavior.
- **Avoid duplicate source basenames in build lists:** the make system flattens objects into one `Build\Tmp\<TYP_NAME>\obj` namespace, so identical filenames from different directories can collide.
- **Do not trust build exit code alone:** the build wrappers can still return success-shaped output after compile/link errors; verify artifacts in `Build\Bin\<TYP_NAME>\` and inspect logs.
