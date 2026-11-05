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
/// \file  CddEft.h
///
/// \brief  Access to EFT data
///
/// \author OTT, Peter ALDE-RT/EES6
//-----------------------------------------------------------------------------
#ifndef CDD_EFT_2021_07_02_H_
#define CDD_EFT_2021_07_02_H_



//=============================================================================
// includes
//=============================================================================
#include <AL_Helper.h>
#include <CddTps92520_Eft.h>
#include <CddNcv78702_Eft.h>


//=============================================================================
// defines
//=============================================================================

//#define EFT_CRC_SIZE         0x08
//#define EFT_CALIB_SIZE       0xF8
//#define EFT_HWDESC_SIZE      0x80
//#define EFT_ECUVARCFG_SIZE  0x180

//Start adressees for each block of memory
#define EFT_CRC_ST_ADRESS        0xA000U
#define EFT_CALIB_ST_ADRESS      0xA008U
#define EFT_HWDESC_ST_ADRESS     0xA100U
#define EFT_ECUVARCFG_ST_ADRESS  0xA180U
#define EFT_ECUVARCFG_MID_ADRESS 0xA280U  //EFT_ECUVARCFG have to be split afther 256bytes for read function
#define EFT_CFG_END_ADRESS       0xA2FFU  // end adress

// size of each block of memory
#define EFT_CRC_SIZE             (EFT_CALIB_ST_ADRESS       - EFT_CRC_ST_ADRESS )                      // size of EFT_CRC block                            8   bytes
#define EFT_CALIB_SIZE           (EFT_HWDESC_ST_ADRESS      - EFT_CALIB_ST_ADRESS)                     // size of  EFT_CALIB block                         256 bytes
#define EFT_HWDESC_SIZE          (EFT_ECUVARCFG_ST_ADRESS   - EFT_HWDESC_ST_ADRESS)                    // size of EFT_HWDESC bock                          127 bytes
#define EFT_ECUVARCFG_SIZE       (EFT_CFG_END_ADRESS + 0x01 - EFT_ECUVARCFG_ST_ADRESS)                 // size of  EFT_ECUVARCFG block                     384 bytes
#define EFT_ECUVARCFG_MH_SIZE    (EFT_ECUVARCFG_SIZE - 0x80)                                           // size of first 256bytes from EFT_ECUVARCFG block  256 bytes
#define EFT_ECUVARCFG_ML_SIZE    (EFT_ECUVARCFG_SIZE - 0x100)                                          // size of last  128bytes from EFT_ECUVARCFG block  128 bytes
#define EFT_CRC32_SIZE           4u			                                                           //CRC32 from EFT_CRC32                              4   bytes
#define EFT_DATA_SIZE            (EFT_CRC_SIZE + EFT_CALIB_SIZE + EFT_HWDESC_SIZE + EFT_ECUVARCFG_SIZE)//size of entire union                              768 bytes

#define EFT_CHECK_SIZE           (EFT_CRC_SIZE + EFT_CALIB_SIZE + EFT_HWDESC_SIZE + EFT_ECUVARCFG_SIZE - EFT_CRC32_SIZE )// second param for CRC32
#define EFT_CRC_START             0xFFFFFFFFuL // third param for CRC32, init value

#define EFT_START 0xA004U
#define EFT_END   0xA2FFU




//=============================================================================
// interface for EFT data users
//=============================================================================
#define EFT_CALIB_Ncv78702        EftData.Eft_Calib.Val.Ncv78702
#define EFT_CALIB_Tps92520        EftData.Eft_Calib.Val.Tps92520
#define EFT_CALIB_NxpAdc          EftData.Eft_Calib.Val.NxpAdc


#define EFT_ECUVARCFG_Ncv78702    EftData.Eft_EcuVarCfg.Val.Ncv78702
#define EFT_ECUVARCFG_Tps92520    EftData.Eft_EcuVarCfg.Val.Tps92520
#define EFT_ECUVARCFG_ADCFACTOR   EftData.Eft_EcuVarCfg.Val.AdcFactor 

#define EFT_ECUVARCFG_Vnd7140     EftData.Eft_EcuVarCfg.Val.aHss
#define EFT_ECUVARCFG_Vn7140      EftData.Eft_EcuVarCfg.Val.aHss
#define EFT_ECUVARCFG_HSS3        EftData.Eft_EcuVarCfg.Val.aHss[2].ucType

#define EFT_ECUVARCFG_ADCFACTOR               EftData.Eft_EcuVarCfg.Val.AdcFactor

#define EFT_HWDESC_ECUPARTNUMBER(index)       EftData.Eft_HwDesc.Val.Al.aucECUPartnumber[index]
#define EFT_HWDESC_ECRNUMBER(index)           EftData.Eft_HwDesc.Val.Al.aucAL_ECR_Number[index]

#define EFT_ADC_CALIBRATION_BASE(instance)    EftData.Eft_Calib.Val.NxpAdc[instance]

#define EFT_MANUFACTURING_DATE_YEAR(index)    EftData.Eft_HwDesc.Val.Al.sECUManufacturingDate.aucYear[index]
#define EFT_MANUFACTURING_DATE_MONTH(index)   EftData.Eft_HwDesc.Val.Al.sECUManufacturingDate.aucMonth[index]
#define EFT_MANUFACTURING_DATE_DAY(index)     EftData.Eft_HwDesc.Val.Al.sECUManufacturingDate.aucDay[index]

#define EFT_HWDESC_ECUDYNSN_LINE              EftData.Eft_HwDesc.Val.Al.sECUDynSN.aucLine
#define EFT_HWDESC_ECUDYNSN_EOL               EftData.Eft_HwDesc.Val.Al.sECUDynSN.aucEOL
#define EFT_HWDESC_ECUDYNSN_COUNTER(index)    EftData.Eft_HwDesc.Val.Al.sECUDynSN.aucCounter[index]

#define EFT_ECU_HWID_APPLICATION(index)       EftData.Eft_HwDesc.Val.Cust.aucHW_Perf_Application[index]
#define EFT_ECU_HWID_EMC(index)               EftData.Eft_HwDesc.Val.Cust.aucECU_EMC_TypeApproval[index]


#define EFT_ECU_EFT_DOC_VERSION               EftData.Eft_Crc.Vers.ucVersion


#define EFT_DATA_VALID_STATUS                 CddEft_DataValid()

//=============================================================================
// type definitions
//=============================================================================


//-----------------------------------------------------------------------------
// Structure tEft_Crc: CRC32 on tEft_Calib/tEft_HwDesc/tEft_EcuVarCfg
//-----------------------------------------------------------------------------
typedef struct
{
  uint32  ulCrc;
} tEft_Crc32;

typedef struct
{
  uint8   ucVersion;
  uint8   ucReserved1;
  uint8   ucReserved2;
  uint8   ucReserved3;
} tEft_DocVers;

typedef struct
{
  tEft_Crc32    Crc32;
  tEft_DocVers  Vers;
} tEft_Crc;


//-----------------------------------------------------------------------------
// Structure tEft_Calib: ECU calibration
//-----------------------------------------------------------------------------
typedef struct
{
  char  acText[4];   // string "CALI"
} tEft_Calib_Text;

typedef struct
{
  uint8  ucType;       // EftCalib structure type
  uint8  ucReserved1;
  uint8  ucReserved2;
  uint8  ucReserved3;
} tEft_Calib_Type;

typedef struct
{
  uint16  unReserved;
  uint16  unBASE_OFS;
  uint16  unOFS;
  uint16  unUSR_OFS;
  uint16  unXOFS;
  uint16  unYOFS;
  uint16  unG;
  uint16  unUG;
  uint16  unCLPS;
  uint16  unCLP3;
  uint16  unCLP2;
  uint16  unCLP1;
  uint16  unCLP0;
  uint16  unCLPX;
  uint16  unCLP9;
  uint16  unCLPS_OFS;
  uint16  unCLP3_OFS;
  uint16  unCLP2_OFS;
  uint16  unCLP1_OFS;
  uint16  unCLP0_OFS;
  uint16  unCLPX_OFS;
  uint16  unCLP9_OFS;
} tEft_Calib_NxpAdc;

typedef struct
{
  tEft_Calib_Text         Text;                                   // string "CALI"
  tEft_Calib_Type         Type;                                   // EftCalib structure type
  tCddTps92520_Eft_Calib  Tps92520[CDDTPS92520_Cfg_NbOfDevices];  // LED driver
  tCddNcv78702_Eft_Calib  Ncv78702[CDDNCV78702_Cfg_NbOfDevices];  // booster driver
  tEft_Calib_NxpAdc       NxpAdc[2];                              // naming TBD
} tEft_Calib_Val;

typedef union
{
  tEft_Calib_Val  Val;
  uint8           aucFill[EFT_CALIB_SIZE];
} tEft_Calib;


//-----------------------------------------------------------------------------
// Structure tEft_HwDesc: ECU identification
//-----------------------------------------------------------------------------
typedef struct
{
  char  acText[4];   // string "HWID"
} tEft_HwDesc_Text;

typedef struct
{
  uint8  ucTypeAl;     // Type AL
  uint8  ucTypeCust;   // Type Customer
  uint8  ucReserved1;
  uint8  ucReserved2;
} tEft_HwDesc_Type;

typedef struct
{
  uint8  aucYear [4];
  uint8  aucMonth[2];
  uint8  aucDay  [2];
} tECUManufacturingDate;

typedef struct
{
  uint8  aucLine;
  uint8  aucEOL;
  uint8  ucReserved1;
  uint8  ucReserved2;
  uint8  aucCounter[4];
} tECUDynSN;

typedef struct
{
  uint8                 aucECUPartnumber[12];
  tECUManufacturingDate sECUManufacturingDate;
  tECUDynSN             sECUDynSN;
  uint8                 aucAL_ECR_Number[11];
  uint8                 ucReserved;
  uint8                 aucReserved[16];
} tEft_HwId_AL;

typedef struct
{
  uint8  aucHWCust_TEXT[4];   // string "CUST"
  uint8  aucHWEL_Version[19];
  uint8  aucHW_Perf_Application[12];
  uint8  aucECU_EMC_TypeApproval[5];
  uint8  aucECU_CustomerSerialNumber[10];
  uint8  aucReserved[14];
} tEft_HwId_Cust;

typedef struct
{
  tEft_HwDesc_Text  Text;   // string "HWID"
  tEft_HwDesc_Type  Type;   // HwDesc structure type
  tEft_HwId_AL      Al;     // Identification AL
  tEft_HwId_Cust    Cust;   // Identification Customer
} tEft_HwDesc_Val;

typedef union
{
  tEft_HwDesc_Val  Val;
  uint8            aucFill[EFT_HWDESC_SIZE];
} tEft_HwDesc;


//-----------------------------------------------------------------------------
// Structure tEft_EcuVarCfg: characterizing ECU variant
//-----------------------------------------------------------------------------
typedef struct
{
  char  acText[4];   // string "VCFG"
} tEft_EcuVarCfg_Text;

typedef struct
{
  uint8  ucType;       // EcuVarCfg structure type
  uint8  ucReserved1;
  uint8  ucVariant;    // HW design variant
  uint8  ucReserved2;
} tEft_EcuVarCfg_Type;

// preliminary typedefs for ECUVARCFG structures
typedef struct
{
  uint16 unFitting;    // Fitting of NTC inputs
  uint16 unReserved;
} tEft_EcuVarCfg_NTC;  // naming TBD

typedef struct
{
  uint16 unG_Pullup;      // conductance of R_Pullup
  uint16 unG_UpperLower;  // conductance of R_Upper + R_Lower
} tEft_EcuVarCfg_ADC_IN;  // naming TBD

typedef struct
{
  uint8  ucType;          // assembly
  uint8  ucReserved;
} tEft_EcuVarCfg_Stp;     // naming TBD

typedef struct
{
  uint8  ucType;          // assembly
  uint8  ucReserved;
} tEft_EcuVarCfg_DcOut;   // naming TBD

typedef struct
{
  uint8  ucType;            // assembly
  uint8  ucReserved;
} tEft_EcuVarCfg_ExtSupply; // naming TBD

typedef struct
{
  uint8  unFitting;           // assembly
  uint8  ucReserved;
} tEft_EcuVarCfg_SwitchArray; // naming TBD

typedef struct
{
  uint8  ucType;          // assembly
  uint8  ucReserved;
} tEft_EcuVarCfg_Hss;     // naming TBD

typedef struct
{
  uint8  ucType;          // assembly
  uint8  ucReserved;
} tEft_EcuVarCfg_Can;     // naming TBD

typedef struct
{
  uint8  ucType;          // assembly
  uint8  ucReserved;
} tEft_EcuVarCfg_Lin;     // naming TBD

typedef struct
{
  uint8  ucType;           // assembly
  uint8  ucReserved;
} tEft_EcuVarCfg_Gpio_Sbc; // naming TBD

typedef struct
{
  uint8  ucType;           // assembly
  uint8  ucReserved;
} tEft_EcuVarCfg_Wk_Sense; // naming TBD

typedef struct
{
  uint8  ucType;          // assembly
  uint8  ucReserved;
} tEft_EcuVarCfg_In;      // naming TBD



typedef struct
{
  uint16 unFactor_PcbTemp;                      // naming TBD
  uint16 unFactor_Ntc[14];                      // naming TBD
  uint16 unFactor_Vbat;                         // naming TBD
  uint16 unFactor_LrDetect;                     // naming TBD
  uint16 unFactor_HssSense_1_2;                 // naming TBD
  uint16 unFactor_HssSense_3;                   // naming TBD
  uint16 unFactor_PosSensor;                    // naming TBD
  uint16 unFactor_Vccx[3];                      // naming TBD
  uint16 unFactor_In[4];                        // naming TBD
  uint16 unFactor_OutFct;                       // naming TBD
  uint16 unFactor_Vboost;                       // naming TBD
  uint16 unFactor_DcOut;                        // naming TBD
} tEft_EcuVarCfg_AdcFactor; // naming TBD

typedef struct
{
  tEft_EcuVarCfg_Text  Text;                                          // string "VCFG"
  tEft_EcuVarCfg_Type  Type;                                          // EcuVarCfg structure type
  tCddTps92520_Eft_EcuVarCfg  Tps92520[CDDTPS92520_Cfg_NbOfDevices];  // LED driver
  tCddNcv78702_Eft_EcuVarCfg  Ncv78702[CDDNCV78702_Cfg_NbOfDevices];  // Booster driver
  tEft_EcuVarCfg_NTC          Ntc;                                    // naming TBD
  tEft_EcuVarCfg_ADC_IN       AdcIn;                                  // naming TBD
  tEft_EcuVarCfg_Stp          Stp[2];                                 // naming TBD
  tEft_EcuVarCfg_DcOut        DcOut;                                  // naming TBD
  tEft_EcuVarCfg_ExtSupply    ExtSupply2;                             // naming TBD
  tEft_EcuVarCfg_ExtSupply    ExtSupply3;                             // naming TBD
  tEft_EcuVarCfg_SwitchArray  SwitchArray;                            // naming TBD
  tEft_EcuVarCfg_Hss          aHss[4];                                // naming TBD
  tEft_EcuVarCfg_Can          Can2;                                   // naming TBD
  tEft_EcuVarCfg_Can          Can3;                                   // naming TBD
  tEft_EcuVarCfg_Lin          Lin;                                    // naming TBD
  tEft_EcuVarCfg_Gpio_Sbc     GpioSbc;                                // naming TBD
  tEft_EcuVarCfg_Wk_Sense     WkSense;                                // naming TBD
  tEft_EcuVarCfg_In           aIn[4];                                 // naming TBD
  tEft_EcuVarCfg_AdcFactor    AdcFactor;                              // naming TBD
} tEft_EcuVarCfg_Val;

typedef union
{
  tEft_EcuVarCfg_Val  Val;
  uint8               aucFill[EFT_ECUVARCFG_SIZE];
} tEft_EcuVarCfg;


//-----------------------------------------------------------------------------
// Structure tEftData: characterizing ECU variant
//-----------------------------------------------------------------------------

// EFT data struct
typedef struct
{
  tEft_Crc       Eft_Crc;
  tEft_Calib     Eft_Calib;
  tEft_HwDesc    Eft_HwDesc;
  tEft_EcuVarCfg Eft_EcuVarCfg;
}
tEftData;


//=============================================================================
// prototypes
//=============================================================================
void    CddEft_Init(void);
boolean CddEft_DataValid(void);

void riCddEftInit(void);

//=============================================================================
// externals
//=============================================================================
extern CONST_AL tEftData  EftData;

#endif // CDD_EFT_2021_07_02_H_
