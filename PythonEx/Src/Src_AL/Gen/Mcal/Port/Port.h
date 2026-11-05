#ifndef PORT_2019_02_08_H_
  #define PORT_2019_02_08_H_

  #include <Std_Types.h>
  #include <Port_TargetTypes.h>


  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef Port_ConfigSpecificType Port_ConfigType;

  typedef uint32 Port_ChannelType;
  typedef uint32 Port_PinType;

  typedef enum Port_PinDirectionType
  {
    PORT_PIN_IN,
    PORT_PIN_OUT
  } Port_PinDirectionType;

#ifdef UNIT_TEST
  typedef enum
  {
    GPIO_INPUT_DIRECTION = 0x0U,  /*!< General purpose input direction.       */
    GPIO_OUTPUT_DIRECTION = 0x1U,  /*!< General purpose output direction.      */
    GPIO_UNSPECIFIED_DIRECTION = 0x2U   /*!< General purpose unspecified direction. */
  } port_data_direction_t;

  typedef enum
  {
    PORT_PIN_DISABLED = 0U,  /*!< corresponding pin is disabled, but is used as an analog pin       */
    PORT_MUX_AS_GPIO = 1U,  /*!< corresponding pin is configured as GPIO                           */
    PORT_MUX_ALT2 = 2U,  /*!< chip-specific                                                     */
    PORT_MUX_ALT3 = 3U,  /*!< chip-specific                                                     */
    PORT_MUX_ALT4 = 4U,  /*!< chip-specific                                                     */
    PORT_MUX_ALT5 = 5U,  /*!< chip-specific                                                     */
    PORT_MUX_ALT6 = 6U,  /*!< chip-specific                                                     */
    PORT_MUX_ALT7 = 7U,  /*!< chip-specific                                                     */
    PORT_MUX_ADC_INTERLEAVE = 8U   /*!< when selected, ADC Interleaved channel is connected to current pin
                                         *   and disconnected to opposed pin
                                         * ADC1_SE14-PTB15 | ADC1_SE15-PTB16 | ADC0_SE8-PTC0  | ADC0_SE9-PTC1
                                         * ADC1_SE14-PTB0  | ADC1_SE15-PTB1  | ADC0_SE8-PTB13 | ADC0_SE9-PTB14 */
  } port_mux_t;

  typedef enum
  {
    PORT_LOW_DRIVE_STRENGTH = 0U,    /*!< low drive strength is configured. @internal gui name="Low"  */
    PORT_HIGH_DRIVE_STRENGTH = 1U     /*!< high drive strength is configured. @internal gui name="High"*/
  } port_drive_strength_t;

  typedef enum
  {
    PORT_INTERNAL_PULL_NOT_ENABLED = 0U,  /*!< internal pull-down or pull-up resistor is not enabled.           */
    PORT_INTERNAL_PULL_DOWN_ENABLED = 1U,  /*!< internal pull-down resistor is enabled. @internal gui name="Down"*/
    PORT_INTERNAL_PULL_UP_ENABLED = 2U   /*!< internal pull-up resistor is enabled. @internal gui name="Up"    */
  } port_pull_config_t;

  typedef unsigned char      uint8_t;
  typedef unsigned short     uint16_t;
  typedef unsigned int       uint32_t;
  typedef unsigned long long uint64_t;

  typedef uint32_t pins_channel_type_t;
  typedef uint8_t pins_level_type_t;

  typedef struct {
    uint32_t PDOR;                              /**< Port Data Output Register, offset: 0x0 */
    uint32_t PSOR;                              /**< Port Set Output Register, offset: 0x4 */
    uint32_t PCOR;                              /**< Port Clear Output Register, offset: 0x8 */
    uint32_t PTOR;                              /**< Port Toggle Output Register, offset: 0xC */
    uint32_t PDIR;                              /**< Port Data Input Register, offset: 0x10 */
    uint32_t PDDR;                              /**< Port Data Direction Register, offset: 0x14 */
    uint32_t PIDR;                              /**< Port Input Disable Register, offset: 0x18 */
  } GPIO_Type, *GPIO_MemMapPtr;
  
  #define PORT_PCR_COUNT                           32u

  typedef struct {
    uint32_t PCR[PORT_PCR_COUNT];               /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
    uint32_t GPCLR;                             /**< Global Pin Control Low Register, offset: 0x80 */
    uint32_t GPCHR;                             /**< Global Pin Control High Register, offset: 0x84 */
    uint32_t GICLR;                             /**< Global Interrupt Control Low Register, offset: 0x88 */
    uint32_t GICHR;                             /**< Global Interrupt Control High Register, offset: 0x8C */
    uint8_t RESERVED_0[16];
    uint32_t ISFR;                              /**< Interrupt Status Flag Register, offset: 0xA0 */
    uint8_t RESERVED_1[28];
    uint32_t DFER;                              /**< Digital Filter Enable Register, offset: 0xC0 */
    uint32_t DFCR;                              /**< Digital Filter Clock Register, offset: 0xC4 */
    uint32_t DFWR;                              /**< Digital Filter Width Register, offset: 0xC8 */
  } PORT_Type, *PORT_MemMapPtr;

  volatile PORT_Type                dummyPortA;
  volatile PORT_Type                dummyPortB;
  volatile PORT_Type                dummyPortC;
  volatile PORT_Type                dummyPortD;
  volatile PORT_Type                dummyPortE;
  #define PORTA_BASE                                    (&dummyPortA)
  #define PORTB_BASE                                    (&dummyPortB)
  #define PORTC_BASE                                    (&dummyPortC)
  #define PORTD_BASE                                    (&dummyPortD)
  #define PORTE_BASE                                    (&dummyPortE)  
  #define PORTA                                         ((PORT_Type *)&dummyPortA)
  #define PORTB                                         ((PORT_Type *)&dummyPortB)
  #define PORTC                                         ((PORT_Type *)&dummyPortC)
  #define PORTD                                         ((PORT_Type *)&dummyPortD)
  #define PORTE                                         ((PORT_Type *)&dummyPortE)

  volatile GPIO_Type                dummyPTA;
  volatile GPIO_Type                dummyPTB;
  volatile GPIO_Type                dummyPTC;
  volatile GPIO_Type                dummyPTD;
  volatile GPIO_Type                dummyPTE;
  #define PTA_BASE                                 (&dummyPTA)
  #define PTA                                      ((GPIO_Type *)PTA_BASE)
  #define PTB_BASE                                 (&dummyPTB)
  #define PTB                                      ((GPIO_Type *)PTB_BASE)
  #define PTC_BASE                                 (&dummyPTC)
  #define PTC                                      ((GPIO_Type *)PTC_BASE)
  #define PTD_BASE                                 (&dummyPTD)
  #define PTD                                      ((GPIO_Type *)PTD_BASE)
  #define PTE_BASE                                 (&dummyPTE)
  #define PTE                                      ((GPIO_Type *)PTE_BASE)

  /* PCR Bit Fields */
  #define PORT_PCR_PS_MASK                         0x1u
  #define PORT_PCR_PS_SHIFT                        0u
  #define PORT_PCR_PS_WIDTH                        1u
  #define PORT_PCR_PS(x)                           (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PS_SHIFT))&PORT_PCR_PS_MASK)
  #define PORT_PCR_PE_MASK                         0x2u
  #define PORT_PCR_PE_SHIFT                        1u
  #define PORT_PCR_PE_WIDTH                        1u
  #define PORT_PCR_PE(x)                           (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PE_SHIFT))&PORT_PCR_PE_MASK)
  #define PORT_PCR_PFE_MASK                        0x10u
  #define PORT_PCR_PFE_SHIFT                       4u
  #define PORT_PCR_PFE_WIDTH                       1u
  #define PORT_PCR_PFE(x)                          (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PFE_SHIFT))&PORT_PCR_PFE_MASK)
  #define PORT_PCR_DSE_MASK                        0x40u
  #define PORT_PCR_DSE_SHIFT                       6u
  #define PORT_PCR_DSE_WIDTH                       1u
  #define PORT_PCR_DSE(x)                          (((uint32_t)(((uint32_t)(x))<<PORT_PCR_DSE_SHIFT))&PORT_PCR_DSE_MASK)
  #define PORT_PCR_MUX_MASK                        0x700u
  #define PORT_PCR_MUX_SHIFT                       8u
  #define PORT_PCR_MUX_WIDTH                       3u
  #define PORT_PCR_MUX(x)                          (((uint32_t)(((uint32_t)(x))<<PORT_PCR_MUX_SHIFT))&PORT_PCR_MUX_MASK)
  #define PORT_PCR_LK_MASK                         0x8000u
  #define PORT_PCR_LK_SHIFT                        15u
  #define PORT_PCR_LK_WIDTH                        1u
  #define PORT_PCR_LK(x)                           (((uint32_t)(((uint32_t)(x))<<PORT_PCR_LK_SHIFT))&PORT_PCR_LK_MASK)
  #define PORT_PCR_IRQC_MASK                       0xF0000u
  #define PORT_PCR_IRQC_SHIFT                      16u
  #define PORT_PCR_IRQC_WIDTH                      4u
  #define PORT_PCR_IRQC(x)                         (((uint32_t)(((uint32_t)(x))<<PORT_PCR_IRQC_SHIFT))&PORT_PCR_IRQC_MASK)
  #define PORT_PCR_ISF_MASK                        0x1000000u
  #define PORT_PCR_ISF_SHIFT                       24u
  #define PORT_PCR_ISF_WIDTH                       1u
  #define PORT_PCR_ISF(x)                          (((uint32_t)(((uint32_t)(x))<<PORT_PCR_ISF_SHIFT))&PORT_PCR_ISF_MASK)

  typedef struct {
    uint8_t RESERVED_0[4];
    uint32_t CHIPCTL;                           /**< Chip Control register, offset: 0x4 */
    uint8_t RESERVED_1[4];
    uint32_t FTMOPT0;                           /**< FTM Option Register 0, offset: 0xC */
    uint32_t LPOCLKS;                           /**< LPO Clock Select Register, offset: 0x10 */
    uint8_t RESERVED_2[4];
    uint32_t ADCOPT;                            /**< ADC Options Register, offset: 0x18 */
    uint32_t FTMOPT1;                           /**< FTM Option Register 1, offset: 0x1C */
    uint32_t MISCTRL0;                          /**< Miscellaneous control register 0, offset: 0x20 */
    uint32_t SDID;                              /**< System Device Identification Register, offset: 0x24 */
    uint8_t RESERVED_3[24];
    uint32_t PLATCGC;                           /**< Platform Clock Gating Control Register, offset: 0x40 */
    uint8_t RESERVED_4[8];
    uint32_t FCFG1;                             /**< Flash Configuration Register 1, offset: 0x4C */
    uint8_t RESERVED_5[4];
    uint32_t UIDH;                              /**< Unique Identification Register High, offset: 0x54 */
    uint32_t UIDMH;                             /**< Unique Identification Register Mid-High, offset: 0x58 */
    uint32_t UIDML;                             /**< Unique Identification Register Mid Low, offset: 0x5C */
    uint32_t UIDL;                              /**< Unique Identification Register Low, offset: 0x60 */
    uint8_t RESERVED_6[4];
    uint32_t CLKDIV4;                           /**< System Clock Divider Register 4, offset: 0x68 */
    uint32_t MISCTRL1;                          /**< Miscellaneous Control register 1, offset: 0x6C */
  } SIM_Type, *SIM_MemMapPtr;

  volatile SIM_Type dummySIM;

  /** Number of instances of the SIM module. */
  #define SIM_INSTANCE_COUNT                       (1u)
  
  
  /* SIM - Peripheral instance base addresses */
  /** Peripheral SIM base address */
  #define SIM_BASE                                 (&dummySIM)
  /** Peripheral SIM base pointer */
  #define SIM                                      ((SIM_Type *)SIM_BASE)

  #define SIM_CHIPCTL_ADC_INTERLEAVE_EN_MASK       0xFu
  #define SIM_CHIPCTL_ADC_INTERLEAVE_EN_SHIFT      0u
  #define SIM_CHIPCTL_ADC_INTERLEAVE_EN_WIDTH      4u
  #define SIM_CHIPCTL_ADC_INTERLEAVE_EN(x)         (((uint32_t)(((uint32_t)(x))<<SIM_CHIPCTL_ADC_INTERLEAVE_EN_SHIFT))&SIM_CHIPCTL_ADC_INTERLEAVE_EN_MASK)

  #define GPIO_PDDR_PDD_MASK                       0xFFFFFFFFu
  #define GPIO_PDDR_PDD_SHIFT                      0u
  #define GPIO_PDDR_PDD_WIDTH                      32u
  #define GPIO_PDDR_PDD(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDDR_PDD_SHIFT))&GPIO_PDDR_PDD_MASK)

  /* PDOR Bit Fields */
  #define GPIO_PDOR_PDO_MASK                       0xFFFFFFFFu
  #define GPIO_PDOR_PDO_SHIFT                      0u
  #define GPIO_PDOR_PDO_WIDTH                      32u
  #define GPIO_PDOR_PDO(x)                         (((uint32_t)(((uint32_t)(x))<<GPIO_PDOR_PDO_SHIFT))&GPIO_PDOR_PDO_MASK)


  #define FEATURE_PINS_DRIVER_USING_PORT (1)

#endif

  extern const Port_ConfigType Port_ConfigData;
  void Port_Init(const Port_ConfigType* ConfigPtr);
  Std_ReturnType Port_Read(uint32 portNb, uint32 pinNb, uint8 *result);
  Std_ReturnType Port_Write(uint32 portNb, uint32 pinNb, uint8 value);

  #if defined(__cplusplus)
  }
  #endif

#endif // DIO_2019_02_08_H_
