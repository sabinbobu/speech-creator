#define JENKINS_APP_INFO_SW_ID    G01St126temp_LDM
#define JENKINS_APP_INFO_APPL_ID  J8A2-14C084-AF
#define JENKINS_BUILD_DAY         0x00
#define JENKINS_BUILD_MONTH       0x00
#define JENKINS_BUILD_YEAR        0x00
#define JENKINS_FUNCTIONAL_PRODUCT_NUMBER {0x98, 0x58, 0x18, 0x00, 0x80}
#define JENKINS_FUNCTIONAL_PLAN_NUMBER {0x98, 0x50, 0x06, 0x63, 0x80}
#define JENKINS_SW_EVOLUTION_INDEX 0xFF
#define JENKINS_SW_INFO_VERSION     "SBJ0000991"
#define JENKINS_SW_INFO_PART_NUMBER "SBJ0000991AA"
#define JENKINS_SW_SAMPLE_VERSION 0x02u
#define JENKINS_SW_SERIES_VERSION 0x00u
 
 //=============================================================================
 //  Section for ulp and cal files!
 //=============================================================================
 // Application number from PSA
 #define CFG_ULP_CAL_SUPPLIER            0x2A   
 #define CFG_ULP_CAL_SYSTEM              0xF6
 #define CFG_ULP_CAL_APPLICATION         0x08       
 #define CFG_ULP_CAL_SOFTWARE_VERSION    0x00        // software version - from PSA   */ // do not used by PSA tool yet, fix 0x01
 #define CFG_ULP_CAL_SOFTWARE_EDITION    (uint16)(0x1300u)      // software edition - from PSA   */ // SW 0.8 = 0x0008; SW 0.10 = 0x000A; SW 1.0 = 0x0100
 #define CFG_ULP_CAL_CLEF                1           /* 0: no security access (CLEF = 0xFFFF) / 1: security acces active (CLEF active) */
 // The next three macros give the name of *.ulp and *.cal files. To be change only at Software Release when *.ulp/*.cal files are delivered
 #define CFG_ULP_CAL_FILE_NUMBER_1     0x99        // file number - from PSA
 #define CFG_ULP_CAL_FILE_NUMBER_2     0x83        // file number - from PSA
 #define CFG_ULP_CAL_FILE_NUMBER_3     0x44        // file number - from PSA