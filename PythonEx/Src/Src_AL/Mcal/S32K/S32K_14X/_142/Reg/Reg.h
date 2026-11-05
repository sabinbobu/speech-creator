#ifndef REG_2020_07_01_H_
  #define REG_2020_07_01_H_

  #if defined(__cplusplus)
  #include <cstdint>
  #else
  #include <stdint.h>
  #endif

  #include <S32K142.h>


  #if defined(__cplusplus)
  namespace mcal
  {
    namespace reg
    {
      constexpr std::uint32_t scs_base        = UINT32_C(0xE000E000);
      constexpr std::uint32_t sys_tick_base   = scs_base + UINT32_C(0x00000010);
      constexpr std::uint32_t nvic_base       = scs_base + UINT32_C(0x00000100);

      constexpr std::uint32_t sys_tick_ctrl   = sys_tick_base + UINT32_C(0x00);
      constexpr std::uint32_t sys_tick_load   = sys_tick_base + UINT32_C(0x04);
      constexpr std::uint32_t sys_tick_val    = sys_tick_base + UINT32_C(0x08);

      // Global base addresses.

      // System SCB registers.

      constexpr std::uint32_t scb_base             = UINT32_C(0xE000E000);
      constexpr std::uint32_t scb_reserved_0_8     = UINT32_C(0xE000E000); // reserved_bytes[8]
      constexpr std::uint32_t scb_actlr            = UINT32_C(0xE000E008);
      constexpr std::uint32_t scb_reserved_1_3316  = UINT32_C(0xE000E00C); // reserved_bytes[3316]
      constexpr std::uint32_t scb_cpuid            = UINT32_C(0xE000ED00);
      constexpr std::uint32_t scb_icsr             = UINT32_C(0xE000ED04);
      constexpr std::uint32_t scb_vtor             = UINT32_C(0xE000ED08);
      constexpr std::uint32_t scb_aircr            = UINT32_C(0xE000ED0C);
      constexpr std::uint32_t scb_scr              = UINT32_C(0xE000ED10);
      constexpr std::uint32_t scb_ccr              = UINT32_C(0xE000ED14);
      constexpr std::uint32_t scb_shpr1            = UINT32_C(0xE000ED18);
      constexpr std::uint32_t scb_shpr2            = UINT32_C(0xE000ED1C);
      constexpr std::uint32_t scb_shpr3            = UINT32_C(0xE000ED20);
      constexpr std::uint32_t scb_shcsr            = UINT32_C(0xE000ED24);
      constexpr std::uint32_t scb_cfsr             = UINT32_C(0xE000ED28);
      constexpr std::uint32_t scb_hfsr             = UINT32_C(0xE000ED2C);
      constexpr std::uint32_t scb_dfsr             = UINT32_C(0xE000ED30);
      constexpr std::uint32_t scb_mmfar            = UINT32_C(0xE000ED34);
      constexpr std::uint32_t scb_bfar             = UINT32_C(0xE000ED38);
      constexpr std::uint32_t scb_afsr             = UINT32_C(0xE000ED3C);
      constexpr std::uint32_t scb_reserved_2_72    = UINT32_C(0xE000ED40); // reserved_bytes[72]
      constexpr std::uint32_t scb_cpacr            = UINT32_C(0xE000ED88);
      constexpr std::uint32_t scb_reserved_2_424   = UINT32_C(0xE000ED8C); // reserved_bytes[424]
      constexpr std::uint32_t scb_fpccr            = UINT32_C(0xE000EF34);
      constexpr std::uint32_t scb_fpcar            = UINT32_C(0xE000EF38);
      constexpr std::uint32_t scb_fpdscr           = UINT32_C(0xE000EF3C);

      constexpr std::uint32_t scg_base             = UINT32_C(0x40064000);
      constexpr std::uint32_t scg_verid            = UINT32_C(0x40064004);
      constexpr std::uint32_t scg_param            = UINT32_C(0x40064008);
      constexpr std::uint32_t scg_reserved_0_8     = UINT32_C(0x40064008); // reserved_bytes[8]
      constexpr std::uint32_t scg_csr              = UINT32_C(0x40064010);
      constexpr std::uint32_t scg_rccr             = UINT32_C(0x40064014);
      constexpr std::uint32_t scg_vccr             = UINT32_C(0x40064018);
      constexpr std::uint32_t scg_hccr             = UINT32_C(0x4006401C);
      constexpr std::uint32_t scg_clkoutcnfg       = UINT32_C(0x40064020);
      constexpr std::uint32_t scg_reserved_1_220   = UINT32_C(0x40064024); // reserved_bytes[220]
      constexpr std::uint32_t scg_sosccsr          = UINT32_C(0x40064100);
      constexpr std::uint32_t scg_soscdiv          = UINT32_C(0x40064104);
      constexpr std::uint32_t scg_sosccfg          = UINT32_C(0x40064108);
      constexpr std::uint32_t scg_reserved_2_244   = UINT32_C(0x4006410C); // reserved_bytes[244]
      constexpr std::uint32_t scg_sirccsr          = UINT32_C(0x40064200);
      constexpr std::uint32_t scg_sircdiv          = UINT32_C(0x40064204);
      constexpr std::uint32_t scg_sirccfg          = UINT32_C(0x40064208);
      constexpr std::uint32_t scg_reserved_3_244   = UINT32_C(0x4006420C); // reserved_bytes[244]
      constexpr std::uint32_t scg_firccsr          = UINT32_C(0x40064300);
      constexpr std::uint32_t scg_fircdiv          = UINT32_C(0x40064304);
      constexpr std::uint32_t scg_firccfg          = UINT32_C(0x40064308);
      constexpr std::uint32_t scg_reserved_4_756   = UINT32_C(0x4006430C); // reserved_bytes[756]
      constexpr std::uint32_t scg_spllcsr          = UINT32_C(0x40064600);
      constexpr std::uint32_t scg_splldiv          = UINT32_C(0x40064604);
      constexpr std::uint32_t scg_spllcfg          = UINT32_C(0x40064608);

      // Port registers.

      constexpr std::uint32_t porta_base           = UINT32_C(0x400FF000);
      constexpr std::uint32_t porta_pdor           = UINT32_C(0x400FF000);
      constexpr std::uint32_t porta_psor           = UINT32_C(0x400FF004);
      constexpr std::uint32_t porta_pcor           = UINT32_C(0x400FF008);
      constexpr std::uint32_t porta_ptor           = UINT32_C(0x400FF00C);
      constexpr std::uint32_t porta_dir            = UINT32_C(0x400FF010);
      constexpr std::uint32_t porta_ddr            = UINT32_C(0x400FF014);
      constexpr std::uint32_t porta_idr            = UINT32_C(0x400FF018);

      constexpr std::uint32_t portb_base           = UINT32_C(0x400FF040);
      constexpr std::uint32_t portb_pdor           = UINT32_C(0x400FF040);
      constexpr std::uint32_t portb_psor           = UINT32_C(0x400FF044);
      constexpr std::uint32_t portb_pcor           = UINT32_C(0x400FF048);
      constexpr std::uint32_t portb_ptor           = UINT32_C(0x400FF04C);
      constexpr std::uint32_t portb_dir            = UINT32_C(0x400FF050);
      constexpr std::uint32_t portb_ddr            = UINT32_C(0x400FF054);
      constexpr std::uint32_t portb_idr            = UINT32_C(0x400FF058);

      constexpr std::uint32_t portc_base           = UINT32_C(0x400FF080);
      constexpr std::uint32_t portc_pdor           = UINT32_C(0x400FF080);
      constexpr std::uint32_t portc_psor           = UINT32_C(0x400FF084);
      constexpr std::uint32_t portc_pcor           = UINT32_C(0x400FF088);
      constexpr std::uint32_t portc_ptor           = UINT32_C(0x400FF08C);
      constexpr std::uint32_t portc_dir            = UINT32_C(0x400FF090);
      constexpr std::uint32_t portc_ddr            = UINT32_C(0x400FF094);
      constexpr std::uint32_t portc_idr            = UINT32_C(0x400FF098);

      constexpr std::uint32_t portd_base           = UINT32_C(0x400FF0C0);
      constexpr std::uint32_t portd_pdor           = UINT32_C(0x400FF0C0);
      constexpr std::uint32_t portd_psor           = UINT32_C(0x400FF0C4);
      constexpr std::uint32_t portd_pcor           = UINT32_C(0x400FF0C8);
      constexpr std::uint32_t portd_ptor           = UINT32_C(0x400FF0CC);
      constexpr std::uint32_t portd_dir            = UINT32_C(0x400FF0D0);
      constexpr std::uint32_t portd_ddr            = UINT32_C(0x400FF0D4);
      constexpr std::uint32_t portd_idr            = UINT32_C(0x400FF0D8);

      constexpr std::uint32_t porte_base           = UINT32_C(0x400FF1C0);
      constexpr std::uint32_t porte_pdor           = UINT32_C(0x400FF1C0);
      constexpr std::uint32_t porte_psor           = UINT32_C(0x400FF1C4);
      constexpr std::uint32_t porte_pcor           = UINT32_C(0x400FF1C8);
      constexpr std::uint32_t porte_ptor           = UINT32_C(0x400FF1CC);
      constexpr std::uint32_t porte_dir            = UINT32_C(0x400FF1D0);
      constexpr std::uint32_t porte_ddr            = UINT32_C(0x400FF1D4);
      constexpr std::uint32_t porte_idr            = UINT32_C(0x400FF1D8);
    }
  }
  #endif

#endif // REG_2020_07_01_H_
