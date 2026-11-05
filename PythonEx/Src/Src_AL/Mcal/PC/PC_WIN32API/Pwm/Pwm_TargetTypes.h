//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  Pwm_Types.h
///
/// \brief PWM - Types
///
/// \descr Here are defined the specific Types used in the PWM module
///
/// \author Alexandru Mertic (F98665C)
///         mailTo:alexandru-laurentiu.mertic(at)magnetimarelli.com
//-----------------------------------------------------------------------------
#ifndef PWM_TARGET_TYPES_H_
#define PWM_TARGET_TYPES_H_

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include <Cfg/Cfg.h>
#include <UtilUtility.h>
#include <Device_TargetTypes.h>

#if defined(__cplusplus)
extern "C"
{
#endif


//=============================================================================
//  defines
//=============================================================================

#define CFG_SENS_PWM0                     0u   // SensPwm0
#define CFG_SENS_PWM1                     1u   // SensPwm1


#define FTM_RMW_SC(base, mask, value)
#define FTM_RMW_CnSCV_REG(base, channel, mask, value)
#define FTM_RMW_DEADTIME(base, mask, value)
#define FTM_RMW_EXTTRIG_REG(base, mask, value)
#define FTM_RMW_FLTCTRL(base, mask, value)
#define FTM_RMW_MODE(base, mask, value)
#define FTM_RMW_FMS(base, mask, value)
#define FTM_RMW_SYNC(base, mask, value)
#define FTM_RMW_CNTIN(base, mask, value)
#define FTM_RMW_MOD(base, mask, value)
#define FTM_RMW_CNT(base, mask, value)

#define FTM_CNT_COUNT(x)                         (uint32_t)(((uint32_t)(x)))
#define FTM_MODE_WPDIS(x)                        (uint32_t)(((uint32_t)(x)))
#define FTM_CNTIN_INIT(x)                        (uint32_t)(((uint32_t)(x)))
#define FTM_MOD_MOD(x)                           (uint32_t)(((uint32_t)(x)))
#define FTM_MODE_FAULTIE(x)                      (uint32_t)(((uint32_t)(x)))
#define FTM_FMS_FAULTF(x)                        (uint32_t)(((uint32_t)(x)))
#define FTM_FMS_FAULTF0(x)                       (uint32_t)(((uint32_t)(x)))
#define FTM_FMS_FAULTF1(x)                       (uint32_t)(((uint32_t)(x)))
#define FTM_FMS_FAULTF2(x)                       (uint32_t)(((uint32_t)(x)))
#define FTM_FMS_FAULTF3(x)                       (uint32_t)(((uint32_t)(x)))
#define FTM_SC_CLKS(x)                           (uint32_t)(((uint32_t)(x)))
#define FTM_SYNC_CNTMIN(x)                       (uint32_t)(((uint32_t)(x)))
#define FTM_SYNC_CNTMAX(x)                       (uint32_t)(((uint32_t)(x)))
#define FTM_SYNC_REINIT(x)                       (uint32_t)(((uint32_t)(x)))
#define FTM_SYNC_SYNCHOM(x)                      (uint32_t)(((uint32_t)(x)))
#define FTM_SYNC_TRIG0(x)                        (uint32_t)(((uint32_t)(x)))
#define FTM_SYNC_TRIG1(x)                        (uint32_t)(((uint32_t)(x)))
#define FTM_SYNC_TRIG2(x)                        (uint32_t)(((uint32_t)(x)))
#define FTM_SYNC_SWSYNC(x)                       (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_DMA(x)                          (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_ICRST(x)                        (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_ELSA(x)                         (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_ELSB(x)                         (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_MSA(x)                          (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_MSB(x)                          (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_CHIE(x)                         (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_CHF(x)                          (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_TRIGMODE(x)                     (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_CHIS(x)                         (uint32_t)(((uint32_t)(x)))
#define FTM_CnSC_CHOV(x)                         (uint32_t)(((uint32_t)(x)))

#define FTM_MAX_DUTY_CYCLE                       (0x8000U)
#define FTM_DUTY_TO_TICKS_SHIFT                  (15U)
#define FTM_INSTANCE_COUNT                       (4u)
#define FTM_FEATURE_FAULT_CHANNELS               (4U)
#define FEATURE_FTM_CHANNEL_COUNT                (111U)
#define FTM_SYNC_SWSYNC_MASK                     0x80u
#define FTM_SC_CLKS_MASK                         0x18u
#define FTM_SC_PS_MASK                           0x7u
#define FTM_SC_PS_SHIFT                          0u
#define FTM_SC_TOIE_MASK                         0x100u
#define FTM_FEATURE_OUTPUT_CHANNEL_OFFSET       (16U)
#define FTM_SC_TOF_MASK                          0x200u
#define FTM_SC_TOIE_SHIFT                        8u
#define FTM_SC_TOF_SHIFT                         9u
#define FTM_SC_CPWMS_MASK                        0x200u
#define FTM_SC_CPWMS_SHIFT                       0u
#define FTM_SC_RIE_MASK                          0x40u
#define FTM_SC_RF_MASK                           0x80u
#define FTM_SC_RF_SHIFT                          7u
#define FTM_SC_RIE_SHIFT                         6u
#define FTM_SC_CLKS_SHIFT                        3u
#define FTM_CNT_COUNT_MASK                       0xFFFFu
#define FTM_CNT_COUNT_SHIFT                      0u
#define FTM_MOD_MOD_MASK                         0xFFFFu
#define FTM_MOD_MOD_SHIFT                        0u
#define FTM_CNTIN_INIT_MASK                      0xFFFFu
#define FTM_CNTIN_INIT_SHIFT                     0u
#define FTM_CnSC_MSA_MASK                        0x10u
#define FTM_CnSC_MSA_SHIFT                       4u
#define FTM_CnSC_MSB_MASK                        0x20u
#define FTM_CnSC_MSB_SHIFT                       5u
#define FTM_CnSC_ELSA_MASK                       0x4u
#define FTM_CnSC_ELSB_MASK                       0x8u
#define FTM_CnSC_CHIE_MASK                       0x40u
#define FTM_CnSC_CHF_MASK                        0x80u
#define FTM_CnSC_TRIGMODE_MASK                   0x100u
#define FTM_CnSC_CHIS_MASK                       0x200u
#define FTM_MODE_FAULTIE_MASK                    0x80u
#define FTM_MODE_FAULTIE_SHIFT                   7u
#define FTM_FMS_FAULTF0_MASK                     0x1u
#define FTM_FMS_FAULTF1_MASK                     0x1u
#define FTM_FMS_FAULTF2_MASK                     0x1u
#define FTM_FMS_FAULTF3_MASK                     0x1u
#define FTM_FMS_FAULTF_MASK                      0x80u
#define FTM_MODE_FAULTM_MASK                     0x60u
#define FTM_MODE_INIT_MASK                       0x2u
#define FTM_FMS_WPEN_MASK                        0x40u
#define FTM_MODE_WPDIS_MASK                      0x4u
#define FTM_MODE_FTMEN_MASK                      0x1u
#define FTM_MODE_PWMSYNC_MASK                    0x8u
#define FTM_SYNC_TRIG0_MASK                      0x10u
#define FTM_SYNC_SYNCHOM_MASK                    0x8u
#define FTM_SYNC_CNTMAX_MASK                     0x2u
#define FTM_SYNC_CNTMIN_MASK                     0x1u
#define FTM_COMBINE_MCOMBINE0_MASK               0x80u
#define FTM_FEATURE_COMBINE_CHAN_CTRL_WIDTH      1U
#define FTM_COMBINE_FAULTEN0_MASK                0x40u
#define FTM_COMBINE_SYNCEN0_MASK                 0x20u
#define FTM_COMBINE_DTEN0_MASK                   0x10u
#define FTM_COMBINE_DECAP0_MASK                  0x8u
#define FTM_COMBINE_DECAPEN0_MASK                0x4u
#define FTM_COMBINE_COMP0_MASK                   0x2u
#define FTM_COMBINE_COMBINE0_MASK                0xFFFFu
#define FTM_DEADTIME_DTVALEX_MASK                0xF0000u
#define FTM_DEADTIME_DTPS_MASK                   0xC0u
#define FTM_DEADTIME_DTVAL_MASK                  0x3Fu
#define FTM_EXTTRIG_INITTRIGEN_MASK              0x40u
#define FTM_EXTTRIG_CH1TRIG_MASK                 0x20u
#define FTM_EXTTRIG_TRIGF_MASK                   0x80u
#define FTM_EXTTRIG_INITTRIGEN_MASK              0x40u
#define FTM_QDCTRL_QUADEN_SHIFT                  0u
#define FTM_QDCTRL_PHAFLTREN_MASK                0x80u
#define FTM_QDCTRL_PHAFLTREN_SHIFT               7u
#define FTM_QDCTRL_PHAPOL_MASK                   0x20u
#define FTM_QDCTRL_PHBPOL_MASK                   0x10u
#define FTM_QDCTRL_QUADMODE_MASK                 0x8u
#define FTM_QDCTRL_QUADIR_MASK                   0x4u
#define FTM_QDCTRL_TOFDIR_MASK                   0x2u
#define FTM_QDCTRL_QUADEN_MASK                   0x1u
#define FTM_QDCTRL_PHBFLTREN_SHIFT               6u
#define FTM_FLTCTRL_FFVAL_MASK                   0xF00u
#define FTM_FLTCTRL_FFLTR0EN_SHIFT               4u
#define FTM_FLTCTRL_FSTATE_SHIFT                 15u
#define FTM_SWOCTRL_CH0OC_MASK                   0x1u
#define FTM_SWOCTRL_CH3OC_MASK                   0x1u
#define FTM_SWOCTRL_CH6OC_MASK                   0x1u
#define FTM_SWOCTRL_CH1OC_MASK                   0x1u
#define FTM_SWOCTRL_CH4OC_MASK                   0x1u
#define FTM_SWOCTRL_CH7OC_MASK                   0x1u
#define FTM_SWOCTRL_CH2OC_MASK                   0x1u
#define FTM_SWOCTRL_CH5OC_MASK                   0x1u
#define FTM_SWOCTRL_CH0OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH1OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH2OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH3OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH4OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH5OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH6OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH7OCV_MASK                  0x100u
#define FTM_SWOCTRL_CH0OCV_SHIFT                 8u
#define FTM_CONF_BDMMODE_MASK                    0xC0u
#define FTM_SYNCONF_HWSOC_MASK                   0x100000u
#define FTM_SYNCONF_HWINVC_MASK                  0x80000u
#define FTM_SYNCONF_HWOM_MASK                    0x40000u
#define FTM_SYNCONF_HWWRBUF_MASK                 0x20000u
#define FTM_SYNCONF_HWRSTCNT_MASK                0x10000u
#define FTM_SYNCONF_SWSOC_MASK                   0x1000u
#define FTM_SYNCONF_SWINVC_MASK                  0x800u
#define FTM_SYNCONF_SWOM_MASK                    0x400u
#define FTM_SYNCONF_SWWRBUF_MASK                 0x200u
#define FTM_SYNCONF_SWRSTCNT_MASK                0x100u
#define FTM_SYNCONF_SWOC_MASK                    0x20u
#define FTM_SYNCONF_INVC_MASK                    0x10u
#define FTM_SYNCONF_HWTRIGMODE_MASK              0x1u
#define FTM_SYNCONF_SYNCMODE_MASK                0x80u
#define FTM_SYNCONF_CNTINC_MASK                  0x4u


#define DEV_ASSERT(x) ((void)0)
#define PWM_PERIOD_INVALID 0xFFFFU

#ifdef LDMO_A0_SAMPLE 
#if defined (SAMPLE_FULL) || (UNIT_TEST)
  #define PWM_NUM_OF_CHANNELS 16U
#elif defined(SAMPLE_ECO)
  #define PWM_NUM_OF_CHANNELS 9U
 #endif
#elif defined(LDMO_B0_SAMPLE)
#if defined (SAMPLE_FULL) || defined(UNIT_TEST)
#define PWM_NUM_OF_CHANNELS 14U
#elif defined(SAMPLE_ECO)
  #define PWM_NUM_OF_CHANNELS 6U
#endif
#endif


//=============================================================================
//  types
//=============================================================================


/** FTM - Register Layout Typedef */
typedef struct
{
	uint32_t SC;                                /**< Status And Control, offset: 0x0 */
	//uint32_t CNT;                               /**< Counter, offset: 0x4 */
	//uint32_t MOD;                               /**< Modulo, offset: 0x8 */
	struct
	{                                         /* offset: 0xC, array step: 0x8 */
		uint32_t CnSC;                              /**< Channel (n) Status And Control, array offset: 0xC, array step: 0x8 */
		uint32_t CnV;                               /**< Channel (n) Value, array offset: 0x10, array step: 0x8 */
	} CONTROLS[8u];
	//uint32_t CNTIN;                             /**< Counter Initial Value, offset: 0x4C */
	//uint32_t STATUS;                            /**< Capture And Compare Status, offset: 0x50 */
	uint32_t MODE;                              /**< Features Mode Selection, offset: 0x54 */
	uint32_t SYNC;                              /**< Synchronization, offset: 0x58 */
	//uint32_t OUTINIT;                           /**< Initial State For Channels Output, offset: 0x5C */
	uint32_t OUTMASK;                           /**< Output Mask, offset: 0x60 */
	uint32_t COMBINE;                           /**< Function For Linked Channels, offset: 0x64 */
	//uint32_t DEADTIME;                          /**< Deadtime Configuration, offset: 0x68 */
	uint32_t EXTTRIG;                           /**< FTM External Trigger, offset: 0x6C */
	uint32_t POL;                               /**< Channels Polarity, offset: 0x70 */
	uint32_t FMS;                               /**< Fault Mode Status, offset: 0x74 */
	//uint32_t FILTER;                            /**< Input Capture Filter Control, offset: 0x78 */
	uint32_t FLTCTRL;                           /**< Fault Control, offset: 0x7C */
	uint32_t QDCTRL;                            /**< Quadrature Decoder Control And Status, offset: 0x80 */
	uint32_t CONF;                              /**< Configuration, offset: 0x84 */
	uint32_t FLTPOL;                            /**< FTM Fault Input Polarity, offset: 0x88 */
	uint32_t SYNCONF;                           /**< Synchronization Configuration, offset: 0x8C */
	uint32_t INVCTRL;                           /**< FTM Inverting Control, offset: 0x90 */
	uint32_t SWOCTRL;                           /**< FTM Software Output Control, offset: 0x94 */
	//uint32_t PWMLOAD;                           /**< FTM PWM Load, offset: 0x98 */
	uint32_t HCR;                               /**< Half Cycle Register, offset: 0x9C */
	//uint32_t PAIR0DEADTIME;                     /**< Pair 0 Deadtime Configuration, offset: 0xA0 */
	//uint8_t RESERVED_0[4];
	//uint32_t PAIR1DEADTIME;                     /**< Pair 1 Deadtime Configuration, offset: 0xA8 */
	//uint8_t RESERVED_1[4];
	//uint32_t PAIR2DEADTIME;                     /**< Pair 2 Deadtime Configuration, offset: 0xB0 */
	//uint8_t RESERVED_2[4];
	//uint32_t PAIR3DEADTIME;                     /**< Pair 3 Deadtime Configuration, offset: 0xB8 */
	//uint8_t RESERVED_3[324];
	//uint32_t MOD_MIRROR;                        /**< Mirror of Modulo Value, offset: 0x200 */
	//uint32_t CV_MIRROR[8u];    /**< Mirror of Channel (n) Match Value, array offset: 0x204, array step: 0x4 */
} FTM_Type;//, *FTM_MemMapPtr;

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

typedef enum
{
	FTM_SYSTEM_CLOCK = 0U,
	FTM_PWM_SYNC = 1U
} ftm_reg_update_t;

typedef enum
{
	FTM_WAIT_LOADING_POINTS = 0U,   /*!< FTM register is updated at first loading point */
	FTM_UPDATE_NOW = 1U    /*!< FTM register is updated immediately */
} ftm_pwm_sync_mode_t;

typedef enum
{
	FTM_BDM_MODE_00 = 0x00U,
	FTM_BDM_MODE_01 = 0x01U,
	FTM_BDM_MODE_10 = 0x02U,
	FTM_BDM_MODE_11 = 0x03U
} ftm_bdm_mode_t;

typedef enum
{
	FTM_CLOCK_DIVID_BY_1 = 0x00U,    /*!< Divide by 1   */
	FTM_CLOCK_DIVID_BY_2 = 0x01U,    /*!< Divide by 2   */
	FTM_CLOCK_DIVID_BY_4 = 0x02U,    /*!< Divide by 4   */
	FTM_CLOCK_DIVID_BY_8 = 0x03U,    /*!< Divide by 8   */
	FTM_CLOCK_DIVID_BY_16 = 0x04U,    /*!< Divide by 16  */
	FTM_CLOCK_DIVID_BY_32 = 0x05U,    /*!< Divide by 32  */
	FTM_CLOCK_DIVID_BY_64 = 0x06U,    /*!< Divide by 64  */
	FTM_CLOCK_DIVID_BY_128 = 0x07U     /*!< Divide by 128 */
} ftm_clock_ps_t;


typedef enum
{
	FTM_PWM_UPDATE_IN_DUTY_CYCLE = 0x00U,     /*!< The type of PWM update in the duty cycle/pulse or also use in frequency update */
	FTM_PWM_UPDATE_IN_TICKS = 0x01U      /*!< The type of PWM update in ticks */
} ftm_pwm_update_option_t;

typedef enum
{
	PWM_INST_TYPE_FTM = 0u,
} pwm_inst_type_t;

typedef struct
{
	pwm_inst_type_t instType;    /*!< Peripheral over which the PAL is used */
	uint32_t instIdx;            /*!< Instance index of the peripheral over which the PAL is used */
} pwm_instance_t;

typedef enum
{
	PWM_ACTIVE_HIGH = 0, /*!< Polarity is active high */
	PWM_ACTIVE_LOW = 1  /*!< Polarity is active low */
} pwm_polarity_t;

typedef enum
{
	PWM_DUPLICATED = 0,   /*!< Complementary channel is the same as main channel */
	PWM_INVERTED = 1    /*!< Complementary channel is inverted relative to main channel */
} pwm_complementarty_mode_t;

typedef enum
{
	PWM_EDGE_ALIGNED = 0, /*!< Counter used by this type of channel is in up counting mode and the edge is aligned to PWM period */
	PWM_CENTER_ALIGNED = 1, /*!< Counter used by this type of channel is in up-down counting mode and the duty is inserted in center of PWM period */
} pwm_channel_type_t;


typedef enum
{
	FTM_FAULT_CONTROL_DISABLED = 0x00U,    /*!< Fault control is disabled for all channels */
	FTM_FAULT_CONTROL_MAN_EVEN = 0x01U,
	FTM_FAULT_CONTROL_MAN_ALL = 0x02U,
	FTM_FAULT_CONTROL_AUTO_ALL = 0x03U
} ftm_fault_mode_t;

typedef enum
{
	FTM_MODE_NOT_INITIALIZED = 0x00U,    /*!< The driver is not initialized */
	FTM_MODE_INPUT_CAPTURE = 0x01U,    /*!< Input capture */
	FTM_MODE_OUTPUT_COMPARE = 0x02U,    /*!< Output compare */
	FTM_MODE_EDGE_ALIGNED_PWM = 0x03U,    /*!< Edge aligned PWM */
	FTM_MODE_CEN_ALIGNED_PWM = 0x04U,    /*!< Center aligned PWM */
	FTM_MODE_QUADRATURE_DECODER = 0x05U,    /*!< Quadrature decoder */
	FTM_MODE_UP_TIMER = 0x06U,    /*!< Timer with up counter */
	FTM_MODE_UP_DOWN_TIMER = 0x07U     /*!< timer with up-down counter */
} ftm_config_mode_t;


typedef enum
{
	FTM_DEADTIME_DIVID_BY_1 = 0x01U, /*!< Divide by 1   */
	FTM_DEADTIME_DIVID_BY_4 = 0x02U, /*!< Divide by 4   */
	FTM_DEADTIME_DIVID_BY_16 = 0x03U  /*!< Divide by 16  */
} ftm_deadtime_ps_t;

typedef enum
{
	FTM_POLARITY_LOW = 0x00U,  /*!< The channel polarity is active LOW which is defined again */
	FTM_POLARITY_HIGH = 0x01U   /*!< The channel polarity is active HIGH which is defined again */
} ftm_polarity_t;

typedef enum
{
	FTM_LOW_STATE = 0x00U,    /*!< When fault is detected PWM channel is low. */
	FTM_HIGH_STATE = 0x01U   /*!< When fault is detected PWM channel is high. */
} ftm_safe_state_polarity_t;

typedef enum
{
	FTM_MAIN_INVERTED = 0x01U,
	FTM_MAIN_DUPLICATED = 0x00U
} ftm_second_channel_polarity_t;

typedef enum
{
	FTM_CLOCK_SOURCE_NONE = 0x00U,    /*!< None use clock for FTM  */
	FTM_CLOCK_SOURCE_SYSTEMCLK = 0x01U,    /*!< System clock            */
	FTM_CLOCK_SOURCE_FIXEDCLK = 0x02U,    /*!< Fixed clock             */
	FTM_CLOCK_SOURCE_EXTERNALCLK = 0x03U     /*!< External clock          */
} ftm_clock_source_t;

typedef enum
{
	IC_EVENT_MEASUREMENT_COMPLETE = 0x00U    /*!< Capture input signal is completed */
} ic_event_t;

typedef struct
{
	uint8_t                     channel;                        /*!< Channel number */
	pwm_channel_type_t          channelType;                    /*!< Channel waveform type */
	uint32_t                    period;                         /*!< Period of the PWM signal in ticks */
	uint32_t                    duty;                           /*!< Duty cycle in ticks */
	pwm_polarity_t              polarity;                       /*!< Channel polarity */
	bool                        insertDeadtime;                 /*!< Enable/disable dead-time insertion. This  feature is available only if complementary mode is enabled */
	uint8_t                     deadtime;                       /*!< Dead-time value in ticks*/
	bool                        enableComplementaryChannel;     /*!< Enable a complementary channel. This option can take control over other channel than the channel configured in this structure. */
	pwm_complementarty_mode_t   complementaryChannelPolarity;   /*!< Configure the polarity of the complementary channel relative to the main channel */
	void*                       timebase;                       /*!< This field is platform specific and it's used to configure the clocking tree for different time-bases.
																	 If FTM is use this field must be filled by a pointer to pwm_ftm_timebase_t */
	uint32_t                    counterInitialValue;
} pwm_channel_t;

typedef struct
{
	pwm_channel_t*  pwmChannels;          /*!< Pointer to channels configurations */
	uint8_t         numberOfPwmChannels;  /*!< Number of channels which are configured */
} pwm_global_config_t;

typedef struct
{
	ftm_clock_source_t sourceClock;         /*!< Clock source for FTM timebase */
	ftm_clock_ps_t     prescaler;           /*!< Prescaler for FTM timebase */
	ftm_deadtime_ps_t  deadtimePrescaler;   /*!< Prescaler for FTM dead-time insertion */
} pwm_ftm_timebase_t;

extern FTM_Type * g_ftmBase[5u];

typedef struct
{
	void* icu_instance;
	void* icu_global_config;
	void* icu_info_config;
}tsIcu_ConfigInstanceMap;

typedef struct
{
	uint8                    ucCountOfIcuInstances;
	tsIcu_ConfigInstanceMap* sCfgCharacteristics;
}tsIcu_SpecificType;

typedef tsIcu_SpecificType sIcu_ConfigType;

extern CONST_AL tsIcu_SpecificType sIcu_Config;

typedef struct
{
	uint8_t hwChannelId;                                 /*!< Physical hardware channel ID */
	ftm_polarity_t polarity;                             /*!< Polarity of the PWM signal generated on MCU pin.*/
	uint16_t uDutyCyclePercent;
	bool enableExternalTrigger;
	ftm_safe_state_polarity_t safeState;
	bool enableSecondChannelOutput;                      /*!< Enable complementary mode on next channel */
	ftm_second_channel_polarity_t secondChannelPolarity; /*!< Polarity of the channel n+1 relative to channel n in the complementary mode*/
	bool deadTime;                                       /*!< Enable/disable dead time for channel */
} ftm_independent_ch_param_t;

typedef struct
{
	uint8_t hwChannelId;                                 /*!< Physical hardware channel ID for channel (n) */
	uint16_t firstEdge;
	uint16_t secondEdge;
	bool deadTime;                                       /*!< Enable/disable dead time for channel */
	bool enableModifiedCombine;                          /*!< Enable/disable the modified combine mode for channels (n) and (n+1) */
	ftm_polarity_t mainChannelPolarity;                  /*!< Polarity of the PWM signal generated on MCU pin for channel n.*/
	bool enableSecondChannelOutput;                      /*!< Select if channel (n+1)  output is enabled/disabled for the complementary mode */
	ftm_second_channel_polarity_t secondChannelPolarity; /*!< Select channel (n+1) polarity relative to channel (n) in the complementary mode */
	bool enableExternalTrigger;
	bool enableExternalTriggerOnNextChn;
	ftm_safe_state_polarity_t mainChannelSafeState;      /*!< The selection of the channel (n) state when fault is detected */
	ftm_safe_state_polarity_t secondChannelSafeState;
} ftm_combined_ch_param_t;

typedef struct
{
	bool faultChannelEnabled;                   /*!< Fault channel state */
	bool faultFilterEnabled;                    /*!< Fault channel filter state */
	ftm_polarity_t ftmFaultPinPolarity;         /*!< Channel output state on fault */
} ftm_pwm_ch_fault_param_t;

typedef struct
{
	bool pwmOutputStateOnFault;             /*!< Output pin state on fault (safe state or tri-state) */
	bool pwmFaultInterrupt;                 /*!< PWM fault interrupt state */
	uint8_t faultFilterValue;               /*!< Fault filter value */
	ftm_fault_mode_t faultMode;             /*!< Fault mode */
	ftm_pwm_ch_fault_param_t ftmFaultChannelParam[4u]; /*!< Fault channels configuration */
} ftm_pwm_fault_param_t;

typedef struct
{
	uint8_t nNumIndependentPwmChannels;                                     /*!< Number of independent PWM channels */
	uint8_t nNumCombinedPwmChannels;                                        /*!< Number of combined PWM channels */
	ftm_config_mode_t mode;                                                 /*!< FTM mode */
	uint8_t deadTimeValue;                                                  /*!< Dead time value in [ticks] */
	ftm_deadtime_ps_t deadTimePrescaler;                                    /*!< Dead time pre-scaler value[ticks] */
	uint32_t uFrequencyHZ;                                                  /*!< PWM period in Hz */
	ftm_independent_ch_param_t * pwmIndependentChannelConfig;               /*!< Configuration for independent PWM channels */
	ftm_combined_ch_param_t * pwmCombinedChannelConfig;                     /*!< Configuration for combined PWM channels */
	ftm_pwm_fault_param_t * faultConfig;                                    /*!< Configuration for PWM fault */
	uint32_t counterInitValue;                                              // value used for phase shifting
} ftm_pwm_param_t;

typedef void(*ic_callback_t)(ic_event_t event, void *userData);

typedef struct
{
	ftm_clock_source_t ftmClockSource;                             /*!< Clock source used by FTM counter */
	ftm_config_mode_t ftmMode;                                     /*!< Mode of operation for FTM */
	uint16_t ftmPeriod;                                            /*!< This field is used only in PWM mode to store signal period */
	uint32_t ftmSourceClockFrequency;                              /*!< The clock frequency is used for counting */
	uint16_t measurementResults[4u];        /*!< This field is used only in input capture mode to store edges time stamps */
	void * channelsCallbacksParams[4u];     /*!< The parameters of callback function for channels events */
	ic_callback_t channelsCallbacks[4u];    /*!< The callback function for channels events */
	bool enableNotification[4u];            /*!< To save channels enable the notification on the callback application */
} ftm_state_t;

typedef uint8 Port_ConfigSpecificType;
typedef Port_ConfigSpecificType Port_ConfigType;

extern ftm_state_t * ftmStatePtr[5u]; //= { NULL };
extern const Port_ConfigType Port_ConfigData;

status_t FTM_DRV_UpdatePwmChannel(uint32_t instance, uint8_t channel, ftm_pwm_update_option_t typeOfUpdate, uint16_t firstEdge, uint16_t secondEdge, bool softwareTrigger);
//#endif


  typedef uint8 Pwm_ChannelHandleType;

  typedef struct pwm_config_instance_map_t
  {
    void* pwm_instance;
    void* pwm_global_config;
  } pwm_config_instance_map_t;

  typedef struct Pwm_SpecificType
  {
    uint8 ucCountOfPwmInstances;
    pwm_config_instance_map_t* Pwm_Cfg_atyCharacteristics;
  } Pwm_SpecificType;

  typedef struct pwm_channel_to_config_map_t
  {
    uint8 channel;
    uint8 instance_map_index;
    uint8 instance_map_chann;
  } pwm_channel_to_config_map_t;

  typedef enum
  {
    PWM_LOW = 0,
    PWM_HIGH
  }tePwm_OutputState;

//=============================================================================
//  variables
//=============================================================================

  extern pwm_channel_to_config_map_t pwm_channel_to_config_map_lut[PWM_NUM_OF_CHANNELS];


#if defined(__cplusplus)
}
#endif

#endif // PWM_TARGET_TYPES_H_
