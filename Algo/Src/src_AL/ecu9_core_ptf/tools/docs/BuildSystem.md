# LPTF Core Lean – Build System Guide

> **Audience:** developers and AI assistants (future prompts) that need to build this
> repository, add/remove source files, change compiler flags, or debug build failures.
> Read this document completely before touching anything under `Build\`.

---

## 1. TL;DR – How to build

```powershell
# Must be run from Build\VS (all makefile paths are relative to the current directory!)
cd D:\git\lptfcore_lean\Build\VS
..\Build.bat H00 MSPM0G_3519 ARM_KEIL CUnit GCOV M0P Al077 App default NonKey rebuild *> $env:TEMP\build.log
```

- A full `rebuild` takes several minutes (≈ 6–8 min on the reference machine). Use a long
  timeout and redirect output to a log file.
- **`Build.bat` always returns exit code 0, even when compilation/linking fails.** Every
  recipe is prefixed with `-` and make runs with `-k`. Success MUST be verified by:
  1. Searching the log for `error` (case-insensitive), e.g.
     `Select-String -Path $env:TEMP\build.log -Pattern 'error' -CaseSensitive:$false`
  2. Checking that `Build\Bin\H00Al077_App_default\H00Al077_App_default.hex` (and `.elf`)
     have a fresh timestamp.
- Outputs land in `Build\Bin\<TYP_NAME>\`; intermediates in `Build\Tmp\<TYP_NAME>\`.
- Use `all` instead of `rebuild` for an incremental build (no clean, uses `.d` dependency files).

The same command is wired to VS Code (`.vscode\tasks.json`, task *Rebuild* →
`Build\VS\runBuildSelector.bat "Al077 H00 Proto App"`).

---

## 2. Toolchain prerequisites

| Item | Location / value |
|---|---|
| `ToolsGeneric` root | `PATH_TOOLSGENERIC` env var; default = `Build\VS\..\..\..\ToolsGeneric` → **`D:\git\ToolsGeneric`** (sibling of the repo) |
| GNU make | `ToolsGeneric\Utilities\CommonDomain\make\make.exe` |
| Unix helpers (echo, rm, mkdir, sed, cat, mv, gawk) | `ToolsGeneric\Utilities\CommonDomain\<tool>\<tool>.exe` |
| Python | `ToolsGeneric\Utilities\CommonDomain\python\python383\python.exe` |
| Keil / ARM Compiler 6 (armclang, armlink, fromelf, armar) | `ToolsGeneric\Compilation\ArmGeneric\KEIL\arm\Keil_v5_v6.16\ARM\ARMCLANG\bin` |
| GNU objcopy/objdump (used with Keil) | `ToolsGeneric\Compilation\ArmGeneric\GCC\arm-none-eabi\9.2.1\bin` |
| AL tools (ALSize, ALHexManip, ALElfToRdm) | `ToolsGeneric\Utilities\AL\...` |
| Axivion (MISRA) | `ToolsGeneric\StaticCodeAnalysis\AXIVION\bauhaus-suite-7_8_1-x86_64-windows\bin` |
| Testwell CTC (coverage) | `ToolsGeneric\DynamicCodeAnalysis\Coverage\Testwell\CTC_9_1_4` |

Parallelism: `NUMBER_OF_PROCESSORS` jobs by default; override with env var `GNUMAKE_MAX_JOBS`.

---

## 3. Call chain

```
Build\VS\runBuildSelector.bat  (optional, VS Code task; maps a config name to Build.bat args)
        │
        ▼
Build\Build.bat  p01..p11      (stores args in %p01%..%p11%, prints help, sets up MSVC env for WIN_VC,
        │                       measures build time)
        ▼
Build\Make\Make.bat            (sets TYP_* variables, decides which phases to run, sets tool paths,
        │                       then invokes GNU make up to 4 times)
        ▼
make.exe <TYP_*=...> SHELL=CMD -k -f Build\Make\Make_000.gmk <PhaseTarget>
```

### 3.1 Build.bat parameters → TYP_* variables

| # | Variable | Al077 value | Meaning / selects |
|---|---|---|---|
| p01 | `TYP_ECU` | `H00` | HAL/ECU variant → `Build\Make\Hal\<TYP_ECU>\` and `Src\Src_AL\Hal\<TYP_ECU>\` (H00 = target HW, W00 = Windows host) |
| p02 | `TYP_MCAL` | `MSPM0G_3519` | Split on `_` into `TYP_FAMILY=MSPM0G`, `TYP_DERIV=3519` → `Build\Make\Mcal\MSPM0G_3519\` |
| p03 | `TYP_CC` | `ARM_KEIL` | Toolchain → `Build\Make\Toolchain\CC\<TYP_CC>\` (ARM_KEIL, ARM_GCC, ARM_AXN, WIN_GCC, WIN_VC, UNIX_GCC) |
| p04 | `TYP_TEST` | `CUnit` | Test framework (only used by `Test` variant) |
| p05 | `TYP_COVER` | `GCOV` | Coverage tool → `Build\Make\Toolchain\Cover\<TYP_COVER>\` |
| p06 | `TYP_CORE` | `M0P` | CPU core flags inside `ToolChain_030_Flags.gmk` (M0P, M3, M4F, X64) |
| p07 | `TYP_PRJ` | `Al077` | Project. **`TYP_OEM` = first 2 chars of TYP_PRJ** (`Al`) |
| p08 | `TYP_VAR` | `App` | Variant → `Build\Make\Cust\<OEM>\<PRJ>\<VAR>\` (App, Test, …) |
| p09 | `TYP_BUILD` | `default` | Build type / module-test name (e.g. `Mt_ApplBenchmark` for Test, `AXIVION`) |
| p10 | `TYP_KEY` | `NonKey` | Security key type (informational) |
| p11 | `TYP_RULE` | `rebuild` | Which phases run (see §3.2) |

Derived: **`TYP_NAME = <ECU><PRJ>_<VAR>_<BUILD>`** → `H00Al077_App_default`. It names the
`Bin`/`Tmp` folders and all output files.

### 3.2 TYP_RULE → phases (Make.bat)

| TYP_RULE | Clean | Prepare | Build_C | Finalize |
|---|---|---|---|---|
| `all`, `all_developer` | – | ✔ | ✔ | ✔ |
| `rebuild`, `rebuild_developer`, `rebuild_delivery` | ✔ | ✔ | ✔ | ✔ |
| `clean` | ✔ | – | – | – |

Each phase is a separate `make` call against `Make_000.gmk`:

| Phase target | Jobs | Depends on (Make_000.gmk) |
|---|---|---|
| `SingleCore_Clean` | 1 | `CleanTmpDirectory` (wipe & recreate `Tmp\<NAME>\{err,lst,obj,qac}`) |
| `SingleCore_Prepare` | 1 | `CreateAndCleanBinDirectory` (wipes `Bin\<NAME>` except `*.log/*.csv/*Axivion.txt`), print version/flags/include paths, VS Code helper files, `DoMisraPrepare`, `PreBuild` |
| `MultiCore_Build_C` | N | `LinkObjectFiles` → depends on every object in `FILES_TMP_OBJ` (parallel compile) then links |
| `SingleCore_Finalize` | 1 | `HexManip`, `ALSize`, `PostBuild`, `DoMisraFinalize` |

---

## 4. Makefile architecture (`Build\Make`)

### 4.1 Numbered stage convention

Every layer contributes files named `<Layer>_<NNN>_<Stage>.gmk`. The number is the stage:

| NNN | Stage | Typical content |
|---|---|---|
| 005 | UserSettings | Optional local overrides (`-include`, may be missing) |
| 010 | Paths | `PATH_*` / `ENV_MAKE_*` variables |
| 020 | Tools | Executables (`CC`, `LD`, `SED`, …) and file suffixes |
| 030 | Flags | `C_INCLUDES`, `C_DEFINES`, `CFLAGS_*`, `LDFLAGS` |
| 050 | Files | Source lists `FILES_SRC_*` and per-file compile variants |
| 070 | Link | `FILES_LD` (linker script) and the `LinkObjectFiles` rule |
| 100 | HexManip | `HexManip` target (ALHexManip on the hex) |
| 110/120 | PCLint / Misra | Static analysis targets |
| 130 | Cover | Coverage targets (`PostBuildCover`) |
| 150 | Sizes | `ALSize` memory usage report |
| 180 | PreBuild | `PreBuild` target |
| 200 | PostBuild | `PostBuild` target |
| 500 | Rules | Pattern rules `%.o : %.c` and the toolchain command lines |

### 4.2 Layers and include hierarchy

`Make_000.gmk` includes `Make_0xx`…`Make_500` in stage order. Each top-level stage file
fans out to the layers. Simplified tree (Windows):

```
Make_000.gmk
├─ Make_005_UserSettings.gmk           (TYP_MISRA = AXIVION, output format)
├─ Make_010_Paths.gmk                  (all ENV_MAKE_*, PATH_SRC_*, PATH_TMP_*, PATH_BIN_*)
│   ├─ Bsw/Bsw_010_Paths.gmk           (FuSa-RTS path, Os/Osek path)
│   ├─ Lib/Lib_010_Paths.gmk
│   ├─ Hal/<ECU>/Hal_010_Paths.gmk ──► Toolchain/CC/<CC>/ToolChain_010_Paths.gmk (compiler dirs)
│   └─ Cust/<OEM>/<PRJ>/Cust_010_Paths.gmk
├─ Make_020_Tools.gmk                  (unix helper tools)
│   └─ Hal/<ECU>/Hal_020_Tools.gmk ──► ToolChain_020_Tools.gmk (armclang…) + Cust_020_Tools.gmk
├─ Make_030_Flags.gmk                  (resets C_DEFINES/C_INCLUDES, then:)
│   ├─ Gen/Gen_030_Flags.gmk
│   ├─ Bsw/Bsw_030_Flags.gmk           (OS, CMSIS, EcuM, IoHwAb includes)
│   ├─ Hal/<ECU>/Hal_030_Flags.gmk     (HAL dir + compiler std includes)
│   ├─ Lib/Lib_030_Flags.gmk
│   ├─ Toolchain/CC/<CC>/ToolChain_030_Flags.gmk  (CFLAGS_*, LDFLAGS, core flags)
│   └─ Cust/<OEM>/<PRJ>/Cust_030_Flags.gmk
│        └─ <VAR>/CustVar_030_Flags.gmk
│             └─ Mcal/<FAMILY>_<DERIV>/Mcal_030_Flags.gmk   (TI MCAL includes)
├─ Make_050_Files.gmk                  (resets FILES_* lists, then:)
│   ├─ Gen/Gen_050_Files.gmk
│   ├─ Bsw/Bsw_050_Files.gmk           (RTX kernel, Os wrapper, EcuM, IoHwAb)
│   ├─ Lib/Lib_050_Files.gmk           (AL_Filter)
│   ├─ Hal/<ECU>/Hal_050_Files.gmk     (startup_keil)
│   └─ Cust/<OEM>/<PRJ>/Cust_050_Files.gmk
│        └─ <VAR>/CustVar_050_Files.gmk
│             └─ Mcal/<FAMILY>_<DERIV>/Mcal_050_Files.gmk   (TI MCAL drivers)
├─ Make_070_Link.gmk ──► Hal_070_Link ──► Cust_070_Link ──► <VAR>/CustVar_070_Link.gmk
├─ Make_100_HexManip ──► Hal ──► Cust ──► CustVar_100_HexManip.gmk
├─ Make_120_Misra   ──► Toolchain/MISRA/<TYP_MISRA>/ToolChain_120_Misra.gmk
├─ Make_150_Sizes   ──► Hal ──► Cust ──► CustVar_150_Sizes.gmk
├─ Make_500_Rules   ──► Hal_500_Rules ──► ToolChain_500_Rules.gmk  (+ generic %.o rules)
├─ Make_130_Cover   ──► Toolchain/Cover/<TYP_COVER>/ToolChain_130_Cover.gmk
├─ Make_180_PreBuild (checks FuSa-RTS & TI MCAL dirs exist) ──► Hal ──► Cust ──► CustVar
└─ Make_200_PostBuild ──► Hal ──► Cust ──► CustVar
```

Pass-through pattern: `Make_* → Hal_* → Cust_* → CustVar_*`. Most Hal/Cust files only
`include` the next level. **Project-specific content lives in the `CustVar_*` files of the
variant** (`Build\Make\Cust\Al\Al077\App\`). For the `Test` variant there is one more level:
`CustVarBuild_*` under `Cust\Al\Al077\Test\<TYP_BUILD>\`.

> MCAL make files are **not** included by `Make_030/050` directly; they are pulled in from
> `CustVar_030_Flags.gmk` and `CustVar_050_Files.gmk` (`include $(ENV_MAKE_MCAL_FAMILY_DERIV)/Mcal_0x0_*.gmk`).
> `PATH_SRC_TI_MCAL_MCAL` is defined there.

### 4.3 Key path variables (Make_010_Paths.gmk)

`CURDIR` = `Build\VS` (where make is started).

| Variable | Resolves to |
|---|---|
| `PATH_BUILD` | `Build` |
| `ENV_MAKE` | `Build\Make` |
| `ENV_MAKE_HAL` | `Build\Make\Hal\$(TYP_ECU)` |
| `ENV_MAKE_CUST` | `Build\Make\Cust\$(TYP_OEM)\$(TYP_PRJ)` |
| `ENV_MAKE_CUST_VAR` | `…\Cust\Al\Al077\$(TYP_VAR)` |
| `ENV_MAKE_CUST_VAR_BUILD` | `…\Cust\Al\Al077\$(TYP_VAR)\$(TYP_BUILD)` |
| `ENV_MAKE_MCAL_FAMILY_DERIV` | `Build\Make\Mcal\MSPM0G_3519` |
| `PATH_SRC_BASE` | `Src` |
| `PATH_SRC_AL` | `Src\Src_AL` (generic, project-independent sources) |
| `PATH_SRC_BSW` | `Src\Src_AL\bsw` |
| `PATH_SRC_HAL` | `Src\Src_AL\Hal\$(TYP_ECU)` |
| `PATH_SRC_LIB` | `Src\Src_AL\lib` |
| `PATH_SRC_THIRD_PARTY` | `Src\Src_ThirdParty` (TI MCAL, FuSa-RTS, SDK) |
| **`PATH_SRC_CFG_CUST`** | **`Src\config_AL\Al\Al077`** – project config, app, SWCs, MCAL `*_Cfg` |
| `PATH_TMP_NAME` | `Build\Tmp\$(TYP_NAME)` with `obj`, `err`, `lst`, `qac` |
| `PATH_BIN_NAME` | `Build\Bin\$(TYP_NAME)` |

`PATH_SRC_CUST*` (`Src\Src_AL\Cust\...`) are legacy variables that point to a non-existent
folder; **use `PATH_SRC_CFG_CUST` for project files**.

Windows paths are case-insensitive, so mixed casing (`Hal` vs `hal`, `bsw` vs `Bsw`) works
on Windows but would break a Linux build.

---

## 5. Source tree mapping

```
Src\
├─ Src_AL\                     generic AL code (shared between projects)
│  ├─ bsw\                     EcuM, IoHwAb, Os\Osek (OS wrapper), …
│  ├─ Hal\H00\Sys\Start\       startup_keil.c (vector table, reset handler)
│  ├─ lib\Util\                AL_Filter, utilities
│  ├─ app, cdd, rte
├─ Src_ThirdParty\
│  ├─ mcal\Src_TI\TI_MCAL\MCAL_MSPM0_00.09.00.00\mcal\   TI AUTOSAR MCAL (drivers + include/hw)
│  ├─ mcal\Src_TI\mspm0_sdk_*                             TI SDK (reference only)
│  └─ OS\FuSa-RTS\FuSaRTS_V1.10\CortexM0+_Package\...     Keil RTX5 FuSa kernel + CMSIS
└─ config_AL\Al\Al077\        PROJECT-SPECIFIC (PATH_SRC_CFG_CUST)
   ├─ app\                    main.c, Rte.c, Rte_Main.h, SWCs (swc_*)
   ├─ bsw\                    EcuM / IoHwAb / Os configuration (Os_Cfg, RTX_Config, …)
   ├─ mcal\<Mod>_Cfg\{include,src}   hand-maintained MCAL configs (EB Tresos output style)
   ├─ cdd\, lib\
```

---

## 6. How source files are compiled

### 6.1 File lists

Sources are appended to one of these lists (all collected in `Make_050_Files.gmk`):
`FILES_SRC_GEN`, `FILES_SRC_BSW`, `FILES_SRC_HAL`, `FILES_SRC_LIB`, `FILES_SRC_CDD`,
`FILES_SRC_SWC`, `FILES_SRC_MCAL`, `FILES_SRC_CUST` → `FILES_SRC_ALL_FROM_MAKEFILES`.

**Entries are written WITHOUT extension**, e.g.

```make
FILES_SRC_CUST += $(PATH_SRC_CFG_CUST)/app/Rte
```

The build derives:
- `VPATH` = sorted list of the directories of all entries (so make can find `Rte.c` / `.cpp` / `.S`).
- `FILES_TMP_OBJ` = `Build/Tmp/<NAME>/obj/<basename>.o` for every entry.

Consequences:
- **Object files are flattened into one folder by basename.** Two sources with the same file
  name in different folders (e.g. two `Can_Cfg.c`) will collide; only one gets compiled/linked.
  Keep basenames unique.
- Because of `VPATH`, if a basename exists in multiple listed directories, make picks the
  first directory in the sorted `VPATH` – another reason to keep names unique.
- The source extension is resolved by the pattern rules: `.c`, `.cpp`, `.S`, `.arm`.

### 6.2 Compile variants (per-file flags)

`Make_500_Rules.gmk` chooses the compile command by basename membership:

| List | Command / flags (ARM_KEIL) |
|---|---|
| (default) | `CFLAGS_DEFAULT` = `-Os`, warnings enabled, `-flto` |
| `FILES_NOWARN_COMPILER` | `CFLAGS_NOWARN` (warnings off) |
| `FILES_DEBUG` | `CFLAGS_DEBUG` (`-O0`) – e.g. TI `Mcu_common` |
| `FILES_NOMISRA` | no-warn flags, excluded from MISRA batch |
| `FILES_COVER` | default flags + coverage tracking |

### 6.3 ARM_KEIL command line (ToolChain_030/500)

```
armclang -x c -std=gnu17 --target=arm-arm-none-eabi -g -ffunction-sections -fdata-sections
         -fshort-enums -flto -mcpu=cortex-m0plus -mthumb -Os -fno-inline-functions <-Wno-...>
         -D<C_DEFINES> -I<C_INCLUDES> -c <src> -o <obj> -MMD -MF <obj>.d  2> err/<name>.err
```

- Compiler stderr is redirected to `Build\Tmp\<NAME>\err\<file>.err` and then echoed into
  the log via `sed` (`file:line:` → `file(line) :`).
- `.d` dependency files are generated (`-MMD`) and included for non-`rebuild` builds.
- Global defines come from `ToolChain_030_Flags.gmk` (`__EVAL`, `AL_CONSTEXPR_OR_CONST`) and
  `CustVar_030_Flags.gmk` (`__MSPM0G351x__`, `BUILD_M0PLUS`, `AUTOSAR_440`, `DEBUG_BUILD`, …).
- Include order: layers **prepend** their paths (`C_INCLUDES := <mine> $(C_INCLUDES)`), so the
  last-included layer (Cust/Mcal) ends up with its paths first-ish. When two directories
  contain the same header name (e.g. `Os.h`, `Can_Cfg.h`), the first `-I` wins – check the
  `_compile_paths.txt` file (§8) when a wrong header is picked.

### 6.4 Linking (CustVar_070_Link.gmk)

- Linker script: `Build\Make\Cust\Al\Al077\App\Al077_App_<TYP_CC>_LinkerScript.<sct|ld>`
  → for Keil `Al077_App_ARM_KEIL_LinkerScript.sct`:
  - Flash `0x00000000`, 512 KB, `.intvecs` first.
  - SRAM `0x20200000`, 62 KB RW/ZI; RAM code `0x2020E000` (`.eraseLoadSram`, used by Fls).
  - Stack 2 KB at the top (`0x20210000`, growing down).
- `armlink --lto --strict --remove --symbols --info=... --xref --scatter <sct> --list <map>`
  → `<NAME>.elf`, `<NAME>.map`.
- `fromelf --i32combined` → `<NAME>.hex`; `arm-none-eabi-objdump -h` → `<NAME>_MemoryOD.map`.

### 6.5 Finalize

- **HexManip**: `ALHexManip.exe` with `Al077_App_HexManipScript.hxm` → `<NAME>_All.hex`.
- **ALSize**: memory report `<NAME>_Size.txt` (RAM `0x20200000/64K`, flash `0x0/512K`).
- **PostBuild**: no-op for App; for `Test` it runs the host executable + coverage (`PostBuildCover`).
- **MISRA** (Axivion): `DoMisraPrepare/Finalize`; active effectively only in the
  `ARM_AXN` / `AXIVION` configuration.

---

## 7. Common tasks (recipes)

### 7.1 Add a new project source file (SWC, config, BSW config)

1. Put the file under `Src\config_AL\Al\Al077\...` (project) or `Src\Src_AL\...` (generic).
2. Add it **without extension** to the right list:
   - Project/app/config → `Build\Make\Cust\Al\Al077\App\CustVar_050_Files.gmk`:
     `FILES_SRC_CUST += $(PATH_SRC_CFG_CUST)/app/swc_foo/swc_foo`
   - Generic BSW → `Build\Make\Bsw\Bsw_050_Files.gmk` (`FILES_SRC_BSW += $(PATH_SRC_BSW)/Foo/Foo`)
   - Library → `Build\Make\Lib\Lib_050_Files.gmk`
3. Add its header folder to `C_INCLUDES` in the matching `*_030_Flags.gmk`
   (`CustVar_030_Flags.gmk` for project folders, `Bsw_030_Flags.gmk` for BSW).
4. Make sure the basename is unique across the whole build.
5. Run a `rebuild` (new files are not picked up reliably by an incremental build).

### 7.2 Add/enable a TI MCAL driver (e.g. Can)

1. Driver sources → `Build\Make\Mcal\MSPM0G_3519\Mcal_050_Files.gmk`
   (`FILES_SRC_MCAL += $(PATH_SRC_TI_MCAL_MCAL)/Can/src/Can` and the `V0/...` private files).
2. Driver includes → `Build\Make\Mcal\MSPM0G_3519\Mcal_030_Flags.gmk`
   (`$(PATH_SRC_TI_MCAL_MCAL)/Can/include`, `.../Can/V0`).
3. Configuration sources → `CustVar_050_Files.gmk`
   (`$(PATH_SRC_CFG_CUST)/mcal/Can_Cfg/src/Can_Cfg`, `Can_PBcfg`).
4. Configuration includes → `CustVar_030_Flags.gmk` (`$(PATH_SRC_CFG_CUST)/mcal/Can_Cfg/include`).
5. Check for a basename clash with the TI `examples_config` folders: never add those to the lists.

### 7.3 Remove a module from the build

Delete its lines from `*_050_Files.gmk` **and** its include path from `*_030_Flags.gmk`
(otherwise stale headers can still be found). Remove call sites in `Rte.c` / `EcuM` callouts.

### 7.4 Add a global define / compiler option

- Project define → `C_DEFINES` in `CustVar_030_Flags.gmk`.
- Compiler/linker option for all Keil builds → `Toolchain\CC\ARM_KEIL\ToolChain_030_Flags.gmk`.
- Single file at `-O0` for debugging → add it to `FILES_DEBUG` (same no-extension form).

### 7.5 Change memory layout

Edit `Al077_App_ARM_KEIL_LinkerScript.sct` and keep `CustVar_150_Sizes.gmk` (ALSize
memory definition) consistent.

### 7.6 Add a new build configuration

- New variant: create `Build\Make\Cust\Al\Al077\<NewVar>\CustVar_0xx_*.gmk` (copy `App`), and a
  linker script `Al077_<NewVar>_<CC>_LinkerScript.*`.
- New project: create `Build\Make\Cust\<OEM>\<PRJ>\` (Cust_* + variant folders) and
  `Src\config_AL\<OEM>\<PRJ>\`. Remember `TYP_OEM` = first two letters of the project name.
- Add the configuration to `Build\VS\runBuildSelector.bat` and `.vscode\tasks.json`.

---

## 8. Debugging the build

| Artifact | Location | Use |
|---|---|---|
| Full log | wherever you redirected `Build.bat` output | grep `error`, `warning`, `+++ compile C:` |
| Per-file compiler output | `Build\Tmp\<NAME>\err\<file>.err` | exact diagnostics of one file |
| Include path list | `Build\Tmp\<NAME>\obj\_compile_paths.txt` | verify `-I` order |
| Object list | `Build\Tmp\<NAME>\obj\_object_files.txt` | verify what is linked |
| Dependency files | `Build\Tmp\<NAME>\obj\*.d` | header dependencies |
| Map file | `Build\Bin\<NAME>\<NAME>.map` | symbol placement, removed sections, sizes |
| Size report | `Build\Bin\<NAME>\<NAME>_Size.txt` | RAM/flash usage |

Typical issues:
- **“Build finished” but no fresh hex** → a compile or link error occurred; search for `error`
  in the log or look at non-empty `err\*.err` files.
- **Undefined symbol at link** → file missing from a `FILES_SRC_*` list, or basename collision.
- **Wrong header picked** → include order; check `_compile_paths.txt`.
- **`ToolsGeneric directory not found` / `make.exe not found`** → set `PATH_TOOLSGENERIC`.
- **`PATH_SRC_TI_MCAL_MCAL not found`** (PreBuild check) → MCAL folder moved/renamed; fix
  `Mcal_030/050` files.
- Make is run with `-k` (keep going), so the first real error may be far above the end of the log.
- `-flto` / `--lto` is enabled: some errors (e.g. duplicate symbols) only show up at link time,
  and the debugger may show inlined/merged functions.

---

## 9. Other configurations (reference)

| Config name (runBuildSelector) | Command |
|---|---|
| `Al077 H00 Proto App` | `H00 MSPM0G_3519 ARM_KEIL CUnit GCOV M0P Al077 App default NonKey <rule>` |
| `Al077 H00 Proto App AXIVION` | `H00 MSPM0G_3519 ARM_AXN CUnit GCOV M0P Al077 App AXIVION NonKey <rule>` (MISRA analysis, no hex) |
| `Al077 W00 Proto Mt_ApplBenchmark` | `W00 PC_WIN32API WIN_GCC CUnit GCOV X64 Al077 Test Mt_ApplBenchmark NonKey <rule>` (host module test + GCOV) |

A Linux entry point exists (`Build\VS\build.sh`, `Make_500_Rules_unix.gmk`,
`*_unix.gmk` cover files), but the reference flow is Windows + `Build.bat`.

---

## 10. Rules for future changes (checklist)

- [ ] Run `Build.bat` from `Build\VS`.
- [ ] Add sources without extension; keep basenames unique.
- [ ] Add both the source (050) and the include path (030) entry.
- [ ] Put project-specific files under `Src\config_AL\Al\Al077` and list them in the
      `App\CustVar_*` files; never list TI `examples_config` / `examples` files.
- [ ] Use `rebuild` after adding/removing files or changing flags.
- [ ] Verify success by grepping the log for errors **and** checking the hex timestamp; the
      exit code is meaningless.
