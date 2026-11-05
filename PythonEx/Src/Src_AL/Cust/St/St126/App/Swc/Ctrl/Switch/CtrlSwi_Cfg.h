#ifndef CTRL_HSS_CFG_2019_12_17_H_
#define CTRL_HSS_CFG_2019_12_17_H_
#include <Std_Types.h>

//  maximum number of high side switches
#if defined (SAMPLE_FULL) || (UNIT_TEST)
#define CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS                   3u
#else
#define CFG_CTRLSWI_HSS_MAX_NO_OF_HSS_CHANNELS                   2u
#endif
#define HSS1                                                     0u
#define HSS2                                                     1u
#define HSS3                                                     2u

#define HSS_SM                                                   8u  //output function for SM from coding Led1 sheet (LedConfigDRV13.FUSA_DRV13_NAME)
#define HSS_DRL                                                  4u  //output function for DRL/POS from coding Led1 sheet (LedConfigDRV13.FUSA_DRV13_NAME)
#define HSS_RGB                                                  9u  //output function for RGB from coding Led1 sheet (LedConfigDRV13.FUSA_DRV13_NAME)

#define CFG_CTRLSWI_HSS1_ERROR_DEBOUNCE                         60u  // 60 * 10 ms cycle time
#define CFG_CTRLSWI_HSS2_ERROR_DEBOUNCE                         60u  // 60 * 10 ms cycle time
#define CFG_CTRLSWI_HSS3_ERROR_DEBOUNCE                         60u  // 60 * 10 ms cycle time

#define CFG_CTRLSWI_DIAGNOSE_CYCLE_60ms                          6u
#define CFG_CTRLSWI_DELAY_ERROR_DETECTION_1s                   100u   //    1s no error detection (switch from ON to OFF)
#define CFG_CTRLSWI_DELAY_ERROR_DETECTION_500ms                 50u   // 500ms no error detection (switch from OFF to ON)
#define CFG_CTRLSWI_SWITCH_ON_DELAY_HSS1                       300u   //    3s delay for switching from off to on
#define CFG_CTRLSWI_SWITCH_ON_DELAY_HSS2                       300u   // 100ms delay for switching from off to on
#define CFG_CTRLSWI_SWITCH_ON_DELAY_HSS3                        20u   // 200ms delay for switching from off to on

#define CFG_CTRLSWI_DIAG_SWITCH_ON_DELAY_HSS                    10u   // 100ms delay for switching from off to on in diagnose mode

#ifndef CTRLSWI_CFG_ERR_DISABLED
#define CTRLSWI_CFG_ERR_DISABLED        0xFF              // error detection permanently disabled
#endif /*ERR_DISABLED*/


#ifndef CTRLSWI_CFG_ERR_SNA
#define CTRLSWI_CFG_ERR_SNA 0U
#endif /*CTRLSWI_CFG_ERR_SNA*/

#ifndef CTRLSWI_CFG_ERR_NO
#define CTRLSWI_CFG_ERR_NO 2U
#endif /*CTRLSWI_CFG_ERR_NO*/

#ifndef CTRLSWI_CFG_ERR_YES
#define CTRLSWI_CFG_ERR_YES 1U
#endif /*CTRLSWI_CFG_ERR_YES*/

//error status initis 
#if defined (SAMPLE_FULL)
#define CTRLSWI_SERRSTATE_ERR_INIT  { CTRLSWI_CFG_ERR_SNA, CTRLSWI_CFG_ERR_SNA, CTRLSWI_CFG_ERR_SNA }
#define CTRLSWI_SERRSTATE_CNT_INIT  { 0U, 0U, 0U }
#else
#define CTRLSWI_SERRSTATE_ERR_INIT  { CTRLSWI_CFG_ERR_SNA }
#define CTRLSWI_SERRSTATE_CNT_INIT  { 0U }
#endif



#ifndef CTRLSWI_CFG_HSS_SNA
#define CTRLSWI_CFG_HSS_SNA 0U
#endif /*CTRLSWI_CFG_HSS_SNA*/

#ifndef CTRLSWI_CFG_HSS_NOEFT
#define CTRLSWI_CFG_HSS_NOEFT 1U
#endif /*CTRLSWI_CFG_HSS_NOEFT*/

#ifndef CTRLSWI_CFG_HSS_SUPPORT
#define CTRLSWI_CFG_HSS_SUPPORT 2U
#endif /*CTRLSWI_CFG_HSS_SUPPORT*/

#ifndef CTRLSWI_CFG_HSS_NOSUPPORT
#define CTRLSWI_CFG_HSS_NOSUPPORT 3U
#endif /*CTRLSWI_CFG_HSS_NOSUPPORT*/


#define ERRORTYPE_MAX         3              // Max. Nr of ErrorType

// Rename this according to coding standards
#ifndef SUPPORT_NO
#define SUPPORT_NO 255U
#endif /*SUPPORT_NO*/

#ifndef SUPPORT_SNA
#define SUPPORT_SNA 0U
#endif /*SUPPORT_SNA*/

#ifndef SUPPORT_UNKNOWN
#define SUPPORT_UNKNOWN 2U
#endif /*SUPPORT_UNKNOWN*/

#ifndef SUPPORT_YES
#define SUPPORT_YES 1U
#endif /*SUPPORT_YES*/

#ifndef NO_EFT_DATA
#define NO_EFT_DATA 3U
#endif /*NO_EFT_DATA*/

#ifndef INIT
#define INIT 0U
#endif /*INIT*/

#ifndef HW_NOT_SUPPORTED
#define HW_NOT_SUPPORTED 2U
#endif /*HW_NOT_SUPPORTED*/

#ifndef HW_SUPPORTED
#define HW_SUPPORTED 1U
#endif /*HW_SUPPORTED*/

#ifndef HSS_DISABLED
#define HSS_DISABLED 255U
#endif /*HSS_DISABLED*/

#ifndef HSS_SNA
#define HSS_SNA 0U
#endif /*HSS_SNA*/

#ifndef HSS_OFF
#define HSS_OFF 2U
#endif /*HSS_OFF*/

#ifndef HSS_ON
#define HSS_ON 1U
#endif /*HSS_ON*/

#if defined(SAMPLE_FULL) || defined(UNIT_TEST)
#define CTRLSWI_CFG_OUTPUTS_CNT             (3u)  // Number of Switch outputs
#elif defined(SAMPLE_ECO)
#define CTRLSWI_CFG_OUTPUTS_CNT             (1u)  // Number of Switch outputs
#endif


#endif /* CTRL_HSS_CFG_2019_12_17_H_ */
