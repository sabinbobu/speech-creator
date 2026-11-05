//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written 
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
///----------------------------------------------------------------------------
/// \file   Dem_Mac.h
///
/// \brief  
///
/// \descr  X-Macros for building the DEM config tables
///
/// \author Vlad Sarghe (F09695C)
///         mailTo:adrian-vlad.sarghe[at]marelli.com
///----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Macro defines
//-----------------------------------------------------------------------------

#ifdef DEM_CONFIG_BEGIN
#undef DEM_CONFIG_BEGIN
#endif
#ifdef DEM_CONFIG_ENTRY
#undef DEM_CONFIG_ENTRY
#endif
#ifdef DEM_CONFIG_END
#undef DEM_CONFIG_END
#endif
#ifdef DEM_CONFIG_DECL_FLT_NOTIFY_FCT
#undef DEM_CONFIG_DECL_FLT_NOTIFY_FCT
#endif
#ifdef DEM_CONFIG_DECL_CONDITION_FCT
#undef DEM_CONFIG_DECL_CONDITION_FCT
#endif
#ifdef DEM_CONFIG_DECL_NOTIFY_FCT
#undef DEM_CONFIG_DECL_NOTIFY_FCT
#endif
#ifdef DEM_CONFIG_DECL_CUSTOM_FCT
#undef DEM_CONFIG_DECL_CUSTOM_FCT
#endif


//-----------------------------------------------------------------------------
// DEM function macros
//-----------------------------------------------------------------------------

#if defined(DEM_CONFIG_DECL_FCT)
#define DEM_CONFIG_DECL_FLT_NOTIFY_FCT(fct_name)  void fct_name(uint16 event_id);
#define DEM_CONFIG_DECL_CONDITION_FCT(fct_name)   boolean fct_name(uint16 event_id);
#define DEM_CONFIG_DECL_NOTIFY_FCT(fct_name)      void fct_name(uint16 unEventId, uint8 ucStatus);
#define DEM_CONFIG_DECL_CUSTOM_FCT(fct_name)      void fct_name(uint16 event_id, uint8 status);
#else
#define DEM_CONFIG_DECL_FLT_NOTIFY_FCT(fct_name)
#define DEM_CONFIG_DECL_CONDITION_FCT(fct_name)
#define DEM_CONFIG_DECL_NOTIFY_FCT(fct_name)
#define DEM_CONFIG_DECL_CUSTOM_FCT(fct_name)
#endif


//-----------------------------------------------------------------------------
// DEM table macros
//-----------------------------------------------------------------------------

#if defined(DEM_CONFIG_MAC_DEF_TABLE)
#define DEM_CONFIG_BEGIN                                              \
  STATIC_AL CONST_AL dem_config_type dem_config [] = {
#define DEM_CONFIG_ENTRY(event_id, debounce_time_failed, debounce_time_passed, debounce_cnt_failed, debounce_cnt_passed, debounce_cnt_max, debounce_cnt_min, jdd_reporter, condition_present, condition_confirmed_present, condition_absent, condition_confirmed_absent, notify_failed, notify_passed, callback_custom)   \
  { event_id, debounce_time_failed, debounce_time_passed, debounce_cnt_failed, debounce_cnt_passed, debounce_cnt_max, debounce_cnt_min,  jdd_reporter, condition_present, condition_confirmed_present, condition_absent, condition_confirmed_absent, notify_failed, notify_passed, callback_custom },
#define DEM_CONFIG_END                                                \
  { 0u, 0u, 0u, 0u, 0u, 0u, 0u, FALSE, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR } \
  };

#elif defined(DEM_CONFIG_MAC_DECL_ENUM)
#define DEM_CONFIG_BEGIN                                              \
  typedef enum enum_dem_config_enum_type {
#define DEM_CONFIG_ENTRY(event_id, debounce_time_failed, debounce_time_passed, debounce_cnt_failed, debounce_cnt_passed, debounce_cnt_max, debounce_cnt_min, jdd_reporter, condition_present, condition_confirmed_present, condition_absent, condition_confirmed_absent, notify_failed, notify_passed, callback_custom)   \
  dem_entry_##event_id,
#define DEM_CONFIG_END                                                \
  dem_entry_max                                                       \
  } dem_config_enum_type;
#define DEM_CONFIG_ENTRY_MAX  ((uint16)dem_entry_max)

#else
#define DEM_CONFIG_BEGIN
#define DEM_CONFIG_ENTRY(event_id, debounce_time_passed, debounce_time_failed, debounce_cnt_passed, debounce_cnt_failed, debounce_cnt_max, debounce_cnt_min, jdd_reporter, condition_present, condition_confirmed_present, condition_absent, condition_confirmed_absent, notify_failed, notify_passed, callback_custom)
#define DEM_CONFIG_END
#endif

// EOF
