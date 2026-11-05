#ifndef STD_TYPES_2019_02_07_H_
  #define STD_TYPES_2019_02_07_H_

  typedef unsigned char      uint8;
  typedef unsigned short int uint16;
  typedef unsigned long int  uint32;
  typedef unsigned long long uint64;

  typedef   signed char      sint8;
  typedef   signed short int sint16;
  typedef   signed long int  sint32;
  typedef   signed long long sint64;

  typedef uint32 uint8_least;
  typedef uint32 uint16_least;
  typedef uint32 uint32_least;
  typedef uint64 uint64_least;

  typedef uint32 uint8_fast;
  typedef uint32 uint16_fast;
  typedef uint32 uint32_fast;
  typedef uint64 uint64_fast;

  typedef sint32 sint8_least;
  typedef sint32 sint16_least;
  typedef sint32 sint32_least;
  typedef sint64 sint64_least;

  typedef sint32 sint8_fast;
  typedef sint32 sint16_fast;
  typedef sint32 sint32_fast;
  typedef sint64 sint64_fast;

  typedef uint8 boolean;

  typedef uint8 Std_ReturnType;
  typedef uint8 StatusType;



// volatile uint32 type for Hw registers access
typedef volatile uint32 vuint32;

  #if defined(TRUE)
  #undef TRUE
  #endif

  #if defined(FALSE)
  #undef FALSE
  #endif

  #define FALSE ((boolean) 0U)
  #define TRUE  ((boolean) 1U)

  #if defined(NULL_PTR)
  #undef NULL_PTR
  #endif

  #if defined(__cplusplus)
  #define NULL_PTR nullptr
  #else
  #define NULL_PTR ((void*) 0U)
  #endif

  #if defined(E_OK)
  #undef E_OK
  #endif

  #if defined(E_NOT_OK)
  #undef E_NOT_OK
  #endif

  #define E_OK     ((Std_ReturnType) 0U)
  #define E_NOT_OK ((Std_ReturnType) 1U)

  // [SWS_Std_00007]
  #define STD_LOW  ((StatusType) 0U)
  #define STD_HIGH ((StatusType) 1U)

  // [SWS_Std_00010]
  #define STD_ON   0x01U
  #define STD_OFF  0x00U

  // [SWS_Std_00013]
  #define STD_ACTIVE  0x01U
  #define STD_IDLE    0x00U

  // [SWS_Std_00015]
  typedef struct {
    uint16 vendorID;
    uint16 moduleID;
    uint8  sw_major_version;
    uint8  sw_minor_version;
    uint8  sw_patch_version;
  } Std_VersionInfoType;

  #include <Compiler.h>

#endif // STD_TYPES_2019_02_07_H_
