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
/// \file  EcuM_Mac.h
///
/// \brief Ecu Manager macros header file
///
/// \Project LDMO
///
/// \Author Stefan Tyirean (f75617c) mailto: stefan.tyirean[a]marelli.com
///
/// \Date September 2021
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// preprocessor definitions
//-----------------------------------------------------------------------------

#ifdef BEGIN_ECUM_INIT_SEQUENCE
  #undef BEGIN_ECUM_INIT_SEQUENCE
#endif

#ifdef END_ECUM_INIT_SEQUENCE
  #undef END_ECUM_INIT_SEQUENCE
#endif

#ifdef DRIVER_INIT_ZERO
  #undef DRIVER_INIT_ZERO
#endif

#ifdef DRIVER_INIT_ONE
  #undef DRIVER_INIT_ONE
#endif

#ifdef STARTUP_TWO_TRUSTED
  #undef STARTUP_TWO_TRUSTED
#endif

#ifdef STARTUP_TWO_NON_TRUSTED
  #undef STARTUP_TWO_NON_TRUSTED
#endif

#ifdef INTERRUPT_CFG
  #undef INTERRUPT_CFG
#endif

#ifdef INTERRUPT_ENABLE
#undef INTERRUPT_ENABLE
#endif

#ifdef INTERRUPT_DISABLE
#undef INTERRUPT_DISABLE
#endif

//-----------------------------------------------------------------------------
// config list definitions
//-----------------------------------------------------------------------------

#if defined(ECUM_MAC_DECL_INIT)
  #define BEGIN_ECUM_INIT_SEQUENCE
  #define DRIVER_INIT_ZERO(InitFunction)        extern void InitFunction(void);
  #define DRIVER_INIT_ONE(InitFunction)         extern void InitFunction(void);
  #define STARTUP_TWO_TRUSTED(InitFunction)     extern void InitFunction(void);
  #define STARTUP_TWO_NON_TRUSTED(InitFunction) extern void InitFunction(void);
  #define INTERRUPT_CFG(interrupt, priority)
  #define INTERRUPT_ENABLE(interrupt)
  #define INTERRUPT_DISABLE(interrupt)
  #define END_ECUM_INIT_SEQUENCE

#elif defined(ECUM_MAC_DRIVER_INIT_ZERO_FPTR_LIST)
  #define BEGIN_ECUM_INIT_SEQUENCE              STATIC_AL CONST_AL tpInitFunction EcuM_DriverInitZero_FunctionList[] = {
  #define DRIVER_INIT_ZERO(InitFunction)        InitFunction,
  #define DRIVER_INIT_ONE(InitFunction)
  #define STARTUP_TWO_TRUSTED(InitFunction)
  #define STARTUP_TWO_NON_TRUSTED(InitFunction)
  #define INTERRUPT_CFG(interrupt, priority)
  #define INTERRUPT_ENABLE(interrupt)
  #define INTERRUPT_DISABLE(interrupt)
  #define END_ECUM_INIT_SEQUENCE                (tpInitFunction)0 };

#elif defined(ECUM_MAC_DRIVER_INIT_ONE_FPTR_LIST)
  #define BEGIN_ECUM_INIT_SEQUENCE              STATIC_AL CONST_AL tpInitFunction EcuM_DriverInitOne_FunctionList[] = {
  #define DRIVER_INIT_ZERO(InitFunction)
  #define DRIVER_INIT_ONE(InitFunction)         InitFunction,
  #define STARTUP_TWO_TRUSTED(InitFunction)
  #define STARTUP_TWO_NON_TRUSTED(InitFunction)
  #define INTERRUPT_CFG(interrupt, priority)
  #define INTERRUPT_ENABLE(interrupt)
  #define INTERRUPT_DISABLE(interrupt)
  #define END_ECUM_INIT_SEQUENCE                (tpInitFunction)0 };

#elif defined(ECUM_MAC_STARTUP_TWO_TRUSTED_FPTR_LIST)
  #define BEGIN_ECUM_INIT_SEQUENCE              STATIC_AL CONST_AL tpInitFunction EcuM_StartupTwo_Trusted_FunctionList[] = {
  #define DRIVER_INIT_ZERO(InitFunction)
  #define DRIVER_INIT_ONE(InitFunction)
  #define STARTUP_TWO_TRUSTED(InitFunction)     InitFunction,
  #define STARTUP_TWO_NON_TRUSTED(InitFunction)
  #define INTERRUPT_CFG(interrupt, priority)
  #define INTERRUPT_ENABLE(interrupt)
  #define INTERRUPT_DISABLE(interrupt)
  #define END_ECUM_INIT_SEQUENCE                (tpInitFunction)0 };

#elif defined(ECUM_MAC_STARTUP_TWO_NON_TRUSTED_FPTR_LIST)
  #define BEGIN_ECUM_INIT_SEQUENCE              STATIC_AL CONST_AL tpInitFunction EcuM_StartupTwo_NonTrusted_FunctionList[] = {
  #define DRIVER_INIT_ZERO(InitFunction)
  #define DRIVER_INIT_ONE(InitFunction)
  #define STARTUP_TWO_TRUSTED(InitFunction)
  #define STARTUP_TWO_NON_TRUSTED(InitFunction) InitFunction,
  #define INTERRUPT_CFG(interrupt, priority)
  #define INTERRUPT_ENABLE(interrupt)
  #define INTERRUPT_DISABLE(interrupt)
  #define END_ECUM_INIT_SEQUENCE                (tpInitFunction)0 };

#elif defined(ECUM_MAC_DRIVER_INIT_ZERO_ID)
  #define BEGIN_ECUM_INIT_SEQUENCE              typedef enum  {
  #define DRIVER_INIT_ZERO(InitFunction)        EcuM_DriverInitZero_##InitFunction##_Id,
  #define DRIVER_INIT_ONE(InitFunction)
  #define STARTUP_TWO_TRUSTED(InitFunction)
  #define STARTUP_TWO_NON_TRUSTED(InitFunction)
  #define INTERRUPT_CFG(interrupt, priority)
  #define INTERRUPT_ENABLE(interrupt)
  #define INTERRUPT_DISABLE(interrupt)
  #define END_ECUM_INIT_SEQUENCE                EcuM_DriverInitZero_Id_Count }EcuM_DriverInitZero_Id_List;

#elif defined(ECUM_MAC_DRIVER_INIT_ONE_ID)
  #define BEGIN_ECUM_INIT_SEQUENCE              typedef enum  {
  #define DRIVER_INIT_ZERO(InitFunction)
  #define DRIVER_INIT_ONE(InitFunction)         EcuM_DriverInitOne_##InitFunction##_Id,
  #define STARTUP_TWO_TRUSTED(InitFunction)
  #define STARTUP_TWO_NON_TRUSTED(InitFunction)
  #define INTERRUPT_CFG(interrupt, priority)
  #define INTERRUPT_ENABLE(interrupt)
  #define INTERRUPT_DISABLE(interrupt)
  #define END_ECUM_INIT_SEQUENCE                EcuM_DriverInitOne_Id_Count }EcuM_DriverInitOne_Id_List;

#elif defined(ECUM_MAC_STARTUP_TWO_TRUSTED_ID)
  #define BEGIN_ECUM_INIT_SEQUENCE              typedef enum {
  #define DRIVER_INIT_ZERO(InitFunction)
  #define DRIVER_INIT_ONE(InitFunction)
  #define STARTUP_TWO_TRUSTED(InitFunction)     EcuM_Startup_Two_Trusted_##InitFunction##_Id,
  #define STARTUP_TWO_NON_TRUSTED(InitFunction)
  #define INTERRUPT_CFG(interrupt, priority)
  #define INTERRUPT_ENABLE(interrupt)
  #define INTERRUPT_DISABLE(interrupt)
  #define END_ECUM_INIT_SEQUENCE                EcuM_Startup_Two_Trusted_Id_Count }EcuM_Startup_Two_Trusted_Id_List ;

#elif defined(ECUM_MAC_STARTUP_TWO_NON_TRUSTED_ID)
  #define BEGIN_ECUM_INIT_SEQUENCE              typedef enum {
  #define DRIVER_INIT_ZERO(InitFunction)
  #define DRIVER_INIT_ONE(InitFunction)
  #define STARTUP_TWO_TRUSTED(InitFunction)
  #define STARTUP_TWO_NON_TRUSTED(InitFunction) EcuM_Startup_Two_NonTrusted_##InitFunction##_Id,
  #define INTERRUPT_CFG(interrupt, priority)
  #define INTERRUPT_ENABLE(interrupt)
  #define INTERRUPT_DISABLE(interrupt)
  #define END_ECUM_INIT_SEQUENCE                EcuM_Startup_Two_NonTrusted_Id_Count }EcuM_Startup_Two_NonTrusted_Id_List ;


#elif defined(ECUM_MAC_STARTUP_INT_CFG)

#define BEGIN_ECUM_INIT_SEQUENCE              STATIC_AL CONST_AL tsEcuM_InterruptCfg EcuM_InterruptCfg_List[] = {
#define DRIVER_INIT_ZERO(InitFunction)
#define DRIVER_INIT_ONE(InitFunction)
#define STARTUP_TWO_TRUSTED(InitFunction)
#define STARTUP_TWO_NON_TRUSTED(InitFunction)
#define INTERRUPT_CFG(interrupt, priority)  {interrupt, priority },
#define INTERRUPT_ENABLE(interrupt)
#define INTERRUPT_DISABLE(interrupt)
#define END_ECUM_INIT_SEQUENCE                (tsEcuM_InterruptCfg){0u, 0u}};

#elif defined(ECUM_MAC_STARTUP_INT_ENBL)

#define BEGIN_ECUM_INIT_SEQUENCE              STATIC_AL CONST_AL uint8 EcuM_InterruptEnbl_List[] = {
#define DRIVER_INIT_ZERO(InitFunction)
#define DRIVER_INIT_ONE(InitFunction)
#define STARTUP_TWO_TRUSTED(InitFunction)
#define STARTUP_TWO_NON_TRUSTED(InitFunction)
#define INTERRUPT_CFG(interrupt, priority)
#define INTERRUPT_ENABLE(interrupt)         interrupt,
#define INTERRUPT_DISABLE(interrupt)
#define END_ECUM_INIT_SEQUENCE                (uint8)0u };

#elif defined(ECUM_MAC_STARTUP_INT_DISABLE)

#define BEGIN_ECUM_INIT_SEQUENCE              STATIC_AL CONST_AL uint8 EcuM_InterruptDis_List[] = {
#define DRIVER_INIT_ZERO(InitFunction)
#define DRIVER_INIT_ONE(InitFunction)
#define STARTUP_TWO_TRUSTED(InitFunction)
#define STARTUP_TWO_NON_TRUSTED(InitFunction)
#define INTERRUPT_CFG(interrupt, priority)
#define INTERRUPT_ENABLE(interrupt)
#define INTERRUPT_DISABLE(interrupt)        interrupt,
#define END_ECUM_INIT_SEQUENCE                (uint8)0u };

#elif defined(ECUM_MAC_STARTUP_INT_ENBL_ID)

#define BEGIN_ECUM_INIT_SEQUENCE              typedef enum  {
#define DRIVER_INIT_ZERO(InitFunction)
#define DRIVER_INIT_ONE(InitFunction)
#define STARTUP_TWO_TRUSTED(InitFunction)
#define STARTUP_TWO_NON_TRUSTED(InitFunction)
#define INTERRUPT_CFG(interrupt, priority)
#define INTERRUPT_ENABLE(interrupt)         EcuM_Startup_Interrupt_##interrupt##_Enable_Id,
#define INTERRUPT_DISABLE(interrupt)
#define END_ECUM_INIT_SEQUENCE                EcuM_Startup_Interrupt_Enable_Id_Count }EcuM_Startup_Interrupt_Enable_Id_List;


#elif defined(ECUM_MAC_STARTUP_INT_CFG_ID)

#define BEGIN_ECUM_INIT_SEQUENCE              typedef enum  {
#define DRIVER_INIT_ZERO(InitFunction)
#define DRIVER_INIT_ONE(InitFunction)
#define STARTUP_TWO_TRUSTED(InitFunction)
#define STARTUP_TWO_NON_TRUSTED(InitFunction)
#define INTERRUPT_CFG(interrupt, priority)      EcuM_Startup_Interrupt_##interrupt##_Cfg_Id,
#define INTERRUPT_ENABLE(interrupt)
#define INTERRUPT_DISABLE(interrupt)
#define END_ECUM_INIT_SEQUENCE                EcuM_Startup_Interrupt_Cfg_Id_Count }EcuM_Startup_Interrupt_Cfg_Id_List;

#elif defined(ECUM_MAC_STARTUP_INT_DISABLE_ID)

#define BEGIN_ECUM_INIT_SEQUENCE              typedef enum  {
#define DRIVER_INIT_ZERO(InitFunction)
#define DRIVER_INIT_ONE(InitFunction)
#define STARTUP_TWO_TRUSTED(InitFunction)
#define STARTUP_TWO_NON_TRUSTED(InitFunction)
#define INTERRUPT_CFG(interrupt, priority)
#define INTERRUPT_ENABLE(interrupt)
#define INTERRUPT_DISABLE(interrupt)          EcuM_Startup_Interrupt_##interrupt##_Disable_Id,
#define END_ECUM_INIT_SEQUENCE                EcuM_Startup_Interrupt_Disable_Id_Count }EcuM_Startup_Interrupt_Disable_Id_List;

#else
#error No generation macro was defined before including EcuM_Cfg.h
#endif

// EOF