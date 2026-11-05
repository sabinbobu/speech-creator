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
/// \file  Icu_TargetTypes.h
///
/// \brief Here are defined the specific types used in the ICU module
///
/// \author Tanase Alexandru-Anton (F58375C)
///         mailTo:alexandru-anton.tanase[at]marelli.com
//-----------------------------------------------------------------------------
#ifndef ICU_TARGET_TYPES_H_
#define ICU_TARGET_TYPES_H_

//=============================================================================
// includes
//=============================================================================

#include <Std_Types.h>
#include <Cfg/Cfg.h>
#include <Device_TargetTypes.h>

//=============================================================================
// defines
//=============================================================================


//=============================================================================
// data types
//=============================================================================


#include <UtilUtility.h>


#define FTM_INSTANCE_COUNT         (4u)
#define FEATURE_FTM_CHANNEL_COUNT  (8U)
#define FTM_SC_PWMEN0_MASK  0x10000u
#define FTM_SC_PWMEN4_MASK  0x100000u
#define FTM_SC_PS_MASK      0x7u
#define DUMMYMAX 25000U

typedef enum
{
  IC_EVENT_MEASUREMENT_COMPLETE = 0x00U    /*!< Capture input signal is completed */
} ic_event_t;

typedef void(*ic_callback_t)(ic_event_t event, void* userData);

typedef enum
{
  FTM_NO_MEASUREMENT = 0x00U,    /*!< No measurement */
  FTM_RISING_EDGE_PERIOD_MEASUREMENT = 0x01U,    /*!< Period measurement between two consecutive rising edges */
  FTM_FALLING_EDGE_PERIOD_MEASUREMENT = 0x02U,    /*!< Period measurement between two consecutive falling edges */
  FTM_PERIOD_ON_MEASUREMENT = 0x03U,    /*!< The time measurement taken for the pulse to remain ON or HIGH state */
  FTM_PERIOD_OFF_MEASUREMENT = 0x04U     /*!< The time measurement taken for the pulse to remain OFF or LOW state */
} ftm_signal_measurement_mode_t;

typedef enum
{
  FTM_NO_PIN_CONTROL = 0x00U,       /*!< No trigger */
  FTM_RISING_EDGE = 0x01U,       /*!< Rising edge trigger */
  FTM_FALLING_EDGE = 0x02U,       /*!< Falling edge trigger */
  FTM_BOTH_EDGES = 0x03U        /*!< Rising and falling edge trigger */
} ftm_edge_alignment_mode_t;

typedef enum
{
  FTM_EDGE_DETECT = 0U,    /*!< FTM edge detect */
  FTM_SIGNAL_MEASUREMENT = 1U,    /*!< FTM signal measurement */
  FTM_NO_OPERATION = 2U     /*!< FTM no operation */
} ftm_input_op_mode_t;

typedef struct
{
  uint8_t hwChannelId;                                /*!< Physical hardware channel ID*/
  ftm_input_op_mode_t inputMode;                      /*!< FlexTimer module mode of operation  */
  ftm_edge_alignment_mode_t edgeAlignement;           /*!< Edge alignment Mode for signal measurement*/
  ftm_signal_measurement_mode_t measurementType;      /*!< Measurement Mode for signal measurement*/
  uint16_t filterValue;                               /*!< Filter Value */
  bool filterEn;                                      /*!< Input capture filter state */
  bool continuousModeEn;                              /*!< Continuous measurement state */
  void* channelsCallbacksParams;                     /*!< The parameters of callback functions for channels events */
  ic_callback_t channelsCallbacks;                    /*!< The callback function for channels events */
} ftm_input_ch_param_t;

typedef struct
{
  uint8_t nNumChannels;                    /*!< Number of input capture channel used */
  uint16_t nMaxCountValue;                 /*!< Maximum counter value. Minimum value is 0 for this mode */
  ftm_input_ch_param_t* inputChConfig;    /*!< Input capture channels configuration */
} ftm_input_param_t;

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

typedef struct
{
  bool softwareSync;                          /*!< True - enable software sync,
                                               *   False - disable software sync */
  bool hardwareSync0;                         /*!< True - enable hardware 0 sync,
                                               *   False - disable hardware 0 sync */
  bool hardwareSync1;                         /*!< True - enable hardware 1 sync,
                                               *   False - disable hardware 1 sync */
  bool hardwareSync2;                         /*!< True - enable hardware 2 sync,
                                               *   False - disable hardware 2 sync */
  bool maxLoadingPoint;                       /*!< True - enable maximum loading point,
                                               *   False - disable maximum loading point */
  bool minLoadingPoint;                       /*!< True - enable minimum loading point,
                                               *   False - disable minimum loading point */
  ftm_reg_update_t inverterSync;              /*!< Configures INVCTRL sync */
  ftm_reg_update_t outRegSync;                /*!< Configures SWOCTRL sync */
  ftm_reg_update_t maskRegSync;               /*!< Configures OUTMASK sync */
  ftm_reg_update_t initCounterSync;           /*!< Configures CNTIN sync */
  bool autoClearTrigger;                      /*!< Available only for hardware trigger */
  ftm_pwm_sync_mode_t syncPoint;              /*!< Configure synchronization method
                                               *   (waiting next loading point or immediate) */
} ftm_pwm_sync_t;

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
  FTM_CLOCK_SOURCE_NONE = 0x00U,    /*!< None use clock for FTM  */
  FTM_CLOCK_SOURCE_SYSTEMCLK = 0x01U,    /*!< System clock            */
  FTM_CLOCK_SOURCE_FIXEDCLK = 0x02U,    /*!< Fixed clock             */
  FTM_CLOCK_SOURCE_EXTERNALCLK = 0x03U     /*!< External clock          */
} ftm_clock_source_t;

typedef enum
{
  FTM_BDM_MODE_00 = 0x00U,    /*!< FTM counter stopped, CH(n)F bit can be set, FTM channels */
  FTM_BDM_MODE_01 = 0x01U,    /*!< FTM counter stopped, CH(n)F bit is not set, FTM channels*/
  FTM_BDM_MODE_10 = 0x02U,    /*!< FTM counter stopped, CH(n)F bit is not set, FTM channels*/
  FTM_BDM_MODE_11 = 0x03U     /*!< FTM counter in functional mode, CH(n)F bit can be set */
} ftm_bdm_mode_t;

typedef struct
{
  ftm_pwm_sync_t syncMethod;              /*!< Register sync options available in the
                                           *   ftm_sync_method_t enumeration  */
  ftm_config_mode_t ftmMode;              /*!< Mode of operation for FTM */
  ftm_clock_ps_t ftmPrescaler;            /*!< Register pre-scaler options available in the
                                           *   ftm_clock_ps_t enumeration  */
  ftm_clock_source_t ftmClockSource;      /*!< Select clock source for FTM */
  ftm_bdm_mode_t BDMMode;                 /*!< Select FTM behavior in BDM mode */
  bool isTofIsrEnabled;                   /*!< true: enable interrupt,
                                           *   false: write interrupt is disabled */
  bool enableInitializationTrigger;       /*!< true: enable the generation of initialization trigger
                                           *   false: disable the generation of initialization trigger */
} ftm_user_config_t;

typedef struct
{
  ftm_clock_source_t ftmClockSource;                             /*!< Clock source used by FTM counter */
  ftm_config_mode_t ftmMode;                                     /*!< Mode of operation for FTM */
  uint16_t ftmPeriod;                                            /*!< This field is used only in PWM mode to store signal period */
  uint32_t ftmSourceClockFrequency;                              /*!< The clock frequency is used for counting */
  uint16_t measurementResults[FEATURE_FTM_CHANNEL_COUNT];        /*!< This field is used only in input capture mode to store edges time stamps */
  void* channelsCallbacksParams[FEATURE_FTM_CHANNEL_COUNT];     /*!< The parameters of callback function for channels events */
  ic_callback_t channelsCallbacks[FEATURE_FTM_CHANNEL_COUNT];    /*!< The callback function for channels events */
  bool enableNotification[FEATURE_FTM_CHANNEL_COUNT];            /*!< To save channels enable the notification on the callback application */
} ftm_state_t;

typedef struct
{
  uint32_t POL;                               /**< Channels Polarity, offset: 0x70 */
  uint32_t CONF;                              /**< Configuration, offset: 0x84 */
  uint32_t SWOCTRL;                           /**< FTM Software Output Control, offset: 0x94 */
} FTM_Type;//, *FTM_MemMapPtr;

typedef enum
{
  FTM_DISABLE_OPERATION = 0x00U, /*!< Have no operation */
  FTM_TIMESTAMP_RISING_EDGE = 0x01U, /*!< Rising edge trigger */
  FTM_TIMESTAMP_FALLING_EDGE = 0x02U, /*!< Falling edge trigger */
  FTM_TIMESTAMP_BOTH_EDGES = 0x03U, /*!< Rising and falling edge trigger */
  FTM_MEASURE_RISING_EDGE_PERIOD = 0x04U, /*!< Period measurement between two consecutive rising edges */
  FTM_MEASURE_FALLING_EDGE_PERIOD = 0x05U, /*!< Period measurement between two consecutive falling edges */
  FTM_MEASURE_PULSE_HIGH = 0x06U, /*!< The time measurement taken for the pulse to remain ON or HIGH state */
  FTM_MEASURE_PULSE_LOW = 0x07U  /*!< The time measurement taken for the pulse to remain OFF or LOW state */
} ftm_ic_op_mode_t;

extern ftm_state_t* ftmStatePtr[FTM_INSTANCE_COUNT];
extern FTM_Type* g_ftmBase[4u];





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

typedef struct
{
  uint8 ucChannel;
  uint8 ucInstanceMapIdx;
  uint8 ucInstanceMapCh;
}tsIcu_ChannelMap;

#endif // ICU_TARGET_TYPES_H_
