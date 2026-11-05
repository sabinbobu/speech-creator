# Al077a / ILCU Proto B0 - Distilled Schematic

Source: `docs/vsch_FEH0019576_variant.pdf` (9 pages), distilled so firmware work does not need to re-parse the PDF.

| Item | Value |
|---|---|
| Project | ALPRJ-26018363 – Stellantis Platform ECU ILCU |
| Function | ILCU schematic – Proto B0 |
| Variant / PCBA / PCBU / Schematic | FEH0019576 XX / FEH0019575 AA / EBD0011394 AA / 0000125680 AA |
| Date | 2026-07-23 (designer: Fardin Federico) |
| Sheets | 1 Block diagram & connector, 2 `15_SBC`, 3 `20_MCU`, 4 `25_MCU_ADC`, 5 `60_ACCELEROMETER`, 6 `80_SAVAC`, 7 Utilities, 8 BOM naming, 9 Revision table |

> Items marked **[verify]** are inferred from component datasheets, not from the schematic itself.

This note captures board-level schematic details. Firmware status below has been reconciled with the current Al077a integration; the schematic-derived electrical values remain subject to the stated verification notes.

## 1. Main components

| Ref | Part | Role |
|---|---|---|
| IC2000 | **MSPM0G3518QRGZRQ1** (TI, VQFN-48 RGZ, 256 KB flash) | MCU |
| IC1500 | **TLE9461ES V33** (Infineon Lite SBC) | Supplies (VCC1 3.3 V, VCC2 5 V), **CAN FD transceiver**, reset, watchdog; SPI-controlled |
| IC6000 | **ASM330LHH** (ST) | 6-axis IMU, SPI |
| IC8000 | NCV20071XV53T2G | Op-amp, LWR analog output stage |
| T8000 | BC807-40-Q (PNP) | LWR output enable |
| Q2000 | 16 MHz crystal (3225) | MCU HFXT |
| D1501 | PESD2CANFD24V-T | CAN ESD protection |
| L1504 | 51 µH CMC | CAN common-mode choke |

## 2. ECU connector X0001

| Pin | Net |
|---|---|
| 1 | KL15 (ignition) |
| 2 | n.c. |
| 3 | CAN_H |
| 4 | CAN_L |
| 5 | LWR_DC (headlamp-leveling analog output) |
| 6 | KL31 (GND) |
| 7, 8 | CPA (n.c.) |
| 9 / MP1, 10 / MP2 | KL31 |

VBAT_RPP = KL15 after reverse-polarity diode D1500 and filter (L1500/L1502).

## 3. MCU pin map (IC2000, VQFN-48)

| Pin | Port | Schematic net | Function | Direction / notes |
|---|---|---|---|---|
| 4 | NRST | IC2000_RESET | Reset from SBC RSTN via R2002 240 Ω; R2000 10 k pull-up, C2004 10 nF | in |
| 48 | VCORE | – | C2001 470 nF | – |
| 6 / 7 / 49 | VDD / VSS / EP | 3V3 / GND | 3V3 = SBC VCC1 | – |
| 8 | **PA2** | HW_IF_TIMG9_C1_CTRL_LWR | **TIMG9 CC1 PWM** → LWR setpoint | out |
| 9 | **PA3** | HW_IF_PA3_EN_LWR | **GPIO** LWR enable, active high (10 k pull-down on board) | out |
| 11 | **PA5** | HFXIN | 16 MHz crystal | analog |
| 12 | **PA6** | HFXOUT | 16 MHz crystal | analog |
| 13 | **PA7** | SPI0_POCI_uC / HW_IF_SPI0_POCI | **SPI0 POCI** (R2005 0 Ω, R2006 2.2 k pull-up to 3V3) | in |
| 14 | **PB2** | SPI0_PICO_uC / HW_IF_SPI0_PICO | **SPI0 PICO** (R2003 240 Ω + C2005 22 pF) | out |
| 15 | **PB3** | SPI0_SCK_uC / HW_IF_SPI0_SCK | **SPI0 SCK** (R2004 240 Ω + C2007 22 pF) | out |
| 16 | **PA8** | HW_IF_SPI0_CS0_SBC | **SPI0 CS0** → SBC CSN | out |
| 20 | **PB6** | HW_IF_SPI0_CS1_ACC | **SPI0 CS1** → IMU CS | out |
| 18 | PA10 | BSLTX | UART0 TX (BSL), TP2009 only | out |
| 19 | PA11 | BSLRX | UART0 RX (BSL), TP2008 only | in |
| 27 | **PA12** | HW_IF_CAN0_TX | **CANFD0 TX** → SBC TXDCAN | out |
| 28 | **PA13** | HW_IF_CAN0_RX | **CANFD0 RX** ← SBC RXDCAN | in |
| 30 | **PA15** | HW_IF_A0_1_FB_LWR | **ADC1 ch0** (net name says A0_1, but the TI pin DB maps PA15 to ADC1_0) – LWR output feedback (ADC.R_DC_OUT) | analog |
| 32 | **PA17** | HW_IF_A1_2_5V0 | **ADC1 ch2** – 5V0 (VCC2) monitor | analog |
| 33 | PA18 | BSL_invoke | BSL entry; R2009 10 k pull-down | in |
| 34 | PA19 | DEBUG_SWJ_SWDIO | SWD | – |
| 35 | PA20 | DEBUG_SWJ_SWCLK | SWD | – |
| 41 | **PB20** | HW_IF_A0_6_PCB_NTC | **ADC0 ch6** – PCB temperature NTC | analog |
| 42 | **PB24** | HW_IF_A0_5_KL15 | **ADC0 ch5** – KL15 / "ADC_VBAT" | analog |

**Unused (marked NC):** PA0 (1), PA1 (2), PA28 (3), PA31 (5), PA4 (10), PA9 (17), PB7 (21), PB8 (22), PB9 (23), PB14 (24), PB15 (25), PB16 (26), PA14 (29), PA16 (31), PB17 (36), PB18 (37), PB19 (38), PA21 (39), PA22 (40), PA23 (43), PA24 (44), PA25 (45), PA26 (46), PA27 (47).
Firmware should leave these pins in a safe state, either as GPIO outputs driven low or as inputs with pull-downs.

**Debug connector X2000 (DNS, 10-pin Cortex SWD):** pin 2 SWDIO (R2007 10 k pull-up), pin 4 SWCLK (R2008 10 k pull-down), pin 7 DEV_MODE, pin 10 DEBUG_RST → NRST via R2001 (DNS).

## 4. SPI0 bus

One SPI0 master on the MCU with two chip selects and shared SCK/PICO/POCI lines:

| CS | Pin | Device | SPI requirements **[verify]** |
|---|---|---|---|
| CS0 | PA8 | TLE9461ES V33 SBC | 16-bit frames, LSB first, CPOL=0 / CPHA=1, ≤ 4 MHz |
| CS1 | PB6 | ASM330LHH IMU | 8-bit addr + data, MSB first, SPI mode 3 (CPOL=1/CPHA=1), ≤ 10 MHz |

The two devices use different SPI modes and bit orders, so they need separate SPI external devices/jobs in the MCAL. IMU INT1/INT2 are routed only to test points TP6001/TP6002, not to the MCU, so IMU data must be polled. IMU SA0/SDO is connected to POCI, and the CS pull-up (R6001) is DNS.

## 5. SBC TLE9461ES V33 (IC1500)

| SBC pin | Connection |
|---|---|
| VS1/VS2 (15/16) | VBAT_RPP |
| VCC1 (13) | **3V3** – MCU supply (always on) |
| VCC2 (20) | **5V0 / 5V_VCC** – 5 V rail, also feeds **VCAN** and is measured by ADC1 ch2 |
| VCAN (1) | 5V_VCC (from VCC2), C1511 100 nF |
| VIO (12) | via L1503 (DNS); R1501 0 Ω → IC1500_BCKSW |
| CSN/CLK/SDI/SDO (7/4/5/6) | SPI0 CS0 / SCK / PICO / POCI |
| TXDCAN/RXDCAN (2/3) | PA12 / PA13 |
| CANH/CANL (23/24) | L1504 CMC → CAN_H/CAN_L, D1501 ESD, 68 pF to GND_EXT |
| RSTN (9) | → MCU NRST |
| INTN (8) | R1503 46.4 k to 3V3 (start-up configuration strap, not routed to the MCU) |
| TEST (10) | R1502 2.2 k → JP1500 "development mode" jumper to 3V3_VCC; optional DEV_MODE transistor circuit (DNS, "remove for series") |
| WK_VSENSE (18) | GND (wake input unused) |
| FO_GPIO (19) | n.c. |
| VCP (17) | C1512 1 nF |

**Bus termination:** the split-termination resistors R1506/R1507 and C1515 are DNS, so the board has no CAN termination.

**Firmware implications** **[verify against the TLE9461 datasheet]:**
1. The MCU muxing CANFD0 alone is not enough. The SBC CAN transceiver must be set to **Normal mode** over SPI through `BUS_CTRL_1`.
2. **VCC2 must be enabled** through SPI (`M_S_CTRL`) because VCAN and the 5V0 rail come from VCC2.
3. The **SBC watchdog** starts after reset with a long open window. Unless the board is in SBC development mode (TEST/JP1500), it must be configured and triggered periodically over SPI (`WD_CTRL`), or the SBC resets the MCU.
4. After initialization, switch the SBC to **Normal mode** and clear its status registers.

**Current Al077a firmware status:** `swc_sbc_demo` performs a nine-register SPI write/readback initialization and only requests CAN controller start after all readbacks pass. It is a bring-up demo, not a complete production SBC CDD; periodic watchdog servicing and the exact functional meaning of each configured register must be verified before production use.

## 6. Analog inputs (sheet 25_MCU_ADC)

| ADC channel | Pin | Signal | Circuit | Conversion |
|---|---|---|---|---|
| ADC0 ch5 | PB24 | KL15 ("ADC_VBAT") | R2505 82.5 k / R2506 15 k, C2502 10 nF | V_KL15 = V_adc × 6.5 (full scale at 3.3 V ≈ 21.45 V) |
| ADC1 ch2 | PA17 | 5V0 (VCC2) | R2507 19.6 k / R2508 19.6 k, C2503 100 nF | V_5V0 = V_adc × 2 |
| ADC1 ch0 | PA15 | LWR_DC feedback (R_DC_OUT) | R2509 82.5 k / R2510 15 k, C2504 100 nF | V_LWR = V_adc × 6.5 |
| ADC0 ch6 | PB20 | PCB temperature | R2500 4.64 k pull-up to 3V3, R2502 10 k NTC to GND, C2500 100 nF | R_NTC = 4.64 k × V_adc / (3.3 − V_adc); NTC placed near SBC |

ADC reference is assumed to be VDD = 3.3 V.

## 7. LWR analog output (sheet 80_SAVAC)

- **CTRL_LWR (PA2, TIMG9 CC1 PWM):** goes through a 2-stage RC filter (R8001 46.4 k with R8004 10 k to GND, C8001 10 nF; R8002 46.4 k, C8002 10 nF) into op-amp IN+. IN+ ≈ D × 3.3 V × 10/56.4 ≈ **D × 0.585 V**, where D is the PWM duty cycle.
- **Op-amp IC8000:** supplied from VBAT_RPP via R8000 100 Ω. It is a non-inverting stage with gain 1 + 82.5 k/19.6 k ≈ **5.21** (R8007 ∥ C8003 feedback, R8009 to GND). Output ≈ **D × 3.05 V** and drives LWR_DC (connector pin 5) through 2 × 3.01 k in parallel (≈ 1.5 k), with C8004 22 nF to GND_EXT.
- **EN_LWR (PA3, GPIO):** drives PNP T8000 through R8008 46.4 k, with R8010 10 k pull-down.
  - EN_LWR **low or floating:** T8000 is on, pulling IN− to 3.3 V, so the output is forced low (disabled).
  - EN_LWR **high:** T8000 is off and the output follows the PWM.
  - The enable is **active high**, and the default state is disabled.
- **Feedback:** LWR_DC is read back on ADC1 ch0 (PA15), see §6.
- **PWM frequency:** not specified on the schematic. The filter corner is about 300 Hz, so a PWM frequency of ≥ 10 kHz is recommended for low ripple.

## 8. Clock

- 16 MHz crystal Q2000 on PA5/PA6 (C2006/C2008 10 pF). The MCU should use HFXT 16 MHz as its clock source, and the MCAN functional clock should be derived from it or the SYSPLL.

## 9. MCAL configuration checklist derived from this schematic

| Module | Required configuration |
|---|---|
| Mcu | HFXT 16 MHz on PA5/PA6; MCAN clock source |
| Port | Configure the pins in §3: PA2 TIMG9_CCP1, PA3 GPIO out low, PA5/PA6 HFXT, PA7/PB2/PB3 SPI0, PA8/PB6 SPI0 CS0/CS1 (or GPIO CS), PA12/PA13 CANFD0, PA15/PA17/PB20/PB24 analog, PA18 input, PA19/PA20 SWD, PA10/PA11 UART0 (optional). Set unused pins to a safe state. |
| Dio | Channel EN_LWR (PA3) |
| Pwm | TIMG9 channel 1 on PA2 (CTRL_LWR), idle state low |
| Adc | ADC0 group 0: ch5 (KL15), ch6 (NTC); ADC1 group 1: ch0 (LWR feedback), ch2 (5V0) |
| Spi | SPI0 master with 2 external devices: SBC (CS0, 16-bit, LSB first) and IMU (CS1, mode 3, MSB first) |
| Can | CANFD0 controller; bus rate per network specification; no on-board termination |
| SBC driver (CDD) | Enable VCC2, set CAN Normal mode, configure and trigger the watchdog, set SBC Normal mode |
| Icu / Gpt | No schematic input requires Icu. Gpt is only needed for scheduling. |

## 10. MCAL hand configuration (EB Tresos no longer used)

The active Al077a MCAL config sources are under `Src\config_AL\Al\Al077a\mcal\`. Treat the checked-in configuration as the build source of truth; do not regenerate it from an unverified Tresos project.

| Module | Implemented configuration |
|---|---|
| Mcu | HFXT 16 MHz (range 8–16 MHz), SYSPLL 16 × (9+1) = 160 MHz VCO → MCLK 80 MHz, MCAN 40 MHz (same CAN bit timing as before). TIMG9 clocked from BUSCLK. |
| Port | Single board-wide `Port_Config` with all 44 pins of §3. Unused/NC pins are GPIO outputs driven low. PA10/PA11 are GPIO inputs with pull-down. Generated with session helper script `gen_port.py` (pin mux checked against the TI pin DB). |
| Dio | `DioConf_DioChannel_PA3_EN_LWR` (output), `DioConf_DioChannel_PA18_BSL_INVOKE` (input) |
| Pwm | One channel `PWM_TIMG_CHANNEL17` = TIMG9 CC1 on PA2, period 2000 counts, initial duty 0 |
| Adc | Group 0 = ADC0 {ch5, ch6}; group 1 = ADC1 {ch0, ch2}; SW trigger, one-shot |
| IoHwAb | KL15 (×6.5), PCB_TEMP (raw), LWR_FB (×6.5), 5V0 (×2) |
| Spi | SPI0, 1 Mbit/s. Channel 0/job 0/seq 0 = SBC (CS0, 16-bit, LSB first, mode 1); channel 1/job 1/seq 1 = IMU (CS1, 8-bit, MSB first, mode 3) |
| Fls | MSPM0G3518: 256 KB main flash (256 sectors × 1 KB, 2 banks). The Keil scatter file is limited to 0x40000. |
| Icu | Config retained but not initialized (no schematic input) |

**Open points [verify on hardware]:**
- TIMG9 power domain/bus clock (40 MHz or 80 MHz). PWM frequency is 20 kHz if 40 MHz, 40 kHz if 80 MHz.
- Confirm the SBC register meanings and watchdog requirements against the exact TLE9461 variant/datasheet. The integrated SPI framing is operational, but the demo does not provide production watchdog supervision.
- The AL077a build target is `MSPM0G_3518`; the shared MCAL family implementation uses the MSPM0G351x peripheral definitions.
