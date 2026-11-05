/* Do not create header for this file ! */

#ifdef BEGIN_MLC_DEVICE_CONFIGURATION
#undef BEGIN_MLC_DEVICE_CONFIGURATION
#endif

#ifdef MLC_DEVICE_CONFIG
#undef MLC_DEVICE_CONFIG
#endif

#ifdef END_MLC_DEVICE_CONFIGURATION
#undef END_MLC_DEVICE_CONFIGURATION
#endif

#if defined(CDDMLC_DECL_DEV_ENUM)

  #define BEGIN_MLC_DEVICE_CONFIGURATION                            typedef enum{
  #define MLC_DEVICE_CONFIG(name, bus, init_func, cyclic_func)      eMlcDevice_##name,
  #define END_MLC_DEVICE_CONFIGURATION                              eMlcDeviceMax }teCddMlc_DeviceType;

  #define MLC_DEVICE(name)    eMlcDevice_##name

#elif defined(CDDMLC_DECL_IFCCFG)
  #define BEGIN_MLC_DEVICE_CONFIGURATION                            static tsCddMlc_DeviceAPIs CddMlc_sDeviceAPIs[eMlcDeviceMax] = {         
  #define MLC_DEVICE_CONFIG(name, bus, init_func, cyclic_func)      {init_func, cyclic_func },
  #define END_MLC_DEVICE_CONFIGURATION                              };

#else

  #define BEGIN_MLC_DEVICE_CONFIGURATION                      
  #define MLC_DEVICE_CONFIG(name, bus, init_func, cyclic_func)
  #define END_MLC_DEVICE_CONFIGURATION                        

#endif

#ifdef CDDMLC_DECL_DEV_ENUM
  #undef CDDMLC_DECL_DEV_ENUM
#endif

#ifdef CDDMLC_DECL_IFCCFG
  #undef CDDMLC_DECL_IFCCFG
#endif
  