#ifndef WDG_2019_02_07_H_
  #define WDG_2019_02_07_H_

  #include <Std_Types.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef enum WdgIf_ModeType
  {
    WDGIF_OFF_MODE,
    WDGIF_SLOW_MODE,
    WDGIF_FAST_MODE
  }WdgIf_ModeType;

  typedef void Wdg_ConfigType;

  void           Wdg_Init   (const Wdg_ConfigType* ConfigPtr);
  void           Wdg_Trigger(void);
  Std_ReturnType Wdg_SetMode(WdgIf_ModeType Mode);

  #if defined(__cplusplus)
  }
  #endif

#endif // WDG_2019_02_07_H_
