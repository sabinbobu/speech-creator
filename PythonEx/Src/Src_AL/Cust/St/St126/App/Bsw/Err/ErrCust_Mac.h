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
/// \file   ErrCust_Mac.h
///
/// \brief  DTC handling
///
/// \descr  X-Macros for building the ErrCust config tables
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// group definitions
//-----------------------------------------------------------------------------

// |  15  14    |  13 - 0     |
// | code class | code number |
// - (B) pour Body et sera codé 10.
// - (C) signifiera Chassis et sera codé 01.
// - (P) pour Power train et sera codé à 00.
// - (U) pour Network sera codé à 11.

// Powertrain group, 0u << 22u
#define ERRCUST_GRP_P (uint32)0x000000
// Chassis group, 1u << 22u
#define ERRCUST_GRP_C (uint32)0x400000
// Body group, 2u << 22u
#define ERRCUST_GRP_B (uint32)0x800000
// Network communication group, 3u << 22u
#define ERRCUST_GRP_U (uint32)0xC00000

//-----------------------------------------------------------------------------
// preprocessor definitions
//-----------------------------------------------------------------------------
#undef ERRCUST_CUSTOMER_CODE_BEGIN
#undef ERRCUST_CUSTOMER_CODE_ENTRY
#undef ERRCUST_CUSTOMER_CODE_END

#undef ERRCUST_CONFIG_BEGIN
#undef ERRCUST_CONFIG_ENTRY
#undef ERRCUST_CONFIG_END

#undef ERRCUST_NO_JDD_BEGIN
#undef ERRCUST_NO_JDD_ENTRY
#undef ERRCUST_NO_JDD_END

//-----------------------------------------------------------------------------
// ErrCust function macros
//-----------------------------------------------------------------------------
#if defined(ERRCUST_CONFIG_DECL)
#define ERRCUST_CUSTOMER_CODE_BEGIN                     \
  typedef enum tag_tErrCust_IxPsError {                 \
    ERRCUST_IxPsError_NONE = 0,            
#define ERRCUST_CUSTOMER_CODE_ENTRY(group, code)        \
    ERRCUST_IxPsError_ ## group ## code,
#define ERRCUST_CUSTOMER_CODE_END                       \
    ERRCUST_IxPsErrorMax                              \
  } teErrCust_IxPsError;
#define ERRCUST_NO_JDD_BEGIN
#define ERRCUST_NO_JDD_ENTRY(code)
#define ERRCUST_NO_JDD_END

#elif defined(ERRCUST_CONFIG_DEF)
#define ERRCUST_CUSTOMER_CODE_BEGIN                     \
  static const tsErrCust_PsDtcs ErrCust_aPsDtcs[] = {             \
    0x000000U, 0U,
#define ERRCUST_CUSTOMER_CODE_ENTRY(group, code)        \
    ERRCUST_GRP_ ## group | 0x ## code, 0U,
#define ERRCUST_CUSTOMER_CODE_END                       \
    0x000000U, 0U                                       \
  };
#define ERRCUST_NO_JDD_BEGIN                            \
  static const uint16 ErrCust_NoJDD[] = {
#define ERRCUST_NO_JDD_ENTRY(code)                      \
    code,
#define ERRCUST_NO_JDD_END                              \
    0U                                                  \
  };

#else
#define ERRCUST_CUSTOMER_CODE_BEGIN
#define ERRCUST_CUSTOMER_CODE_ENTRY(group, code)
#define ERRCUST_CUSTOMER_CODE_END
#define ERRCUST_NO_JDD_BEGIN
#define ERRCUST_NO_JDD_ENTRY(code)
#define ERRCUST_NO_JDD_END
#endif

//-----------------------------------------------------------------------------
// ErrCust config macros
//-----------------------------------------------------------------------------
#if defined(ERRCUST_CONFIG_ASSIGN)
#define ERRCUST_CONFIG_BEGIN
#define ERRCUST_CONFIG_ENTRY(event_id, error_code)            \
  peRefList[ event_id ] = ERRCUST_IxPsError_ ## error_code;
#define ERRCUST_CONFIG_END

#else
#define ERRCUST_CONFIG_BEGIN
#define ERRCUST_CONFIG_ENTRY(event_id, error_code)
#define ERRCUST_CONFIG_END
#endif


//EOF
