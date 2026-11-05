#ifndef DIO_2019_02_08_H_
  #define DIO_2019_02_08_H_

  #include <Std_Types.h>
  #include <UtilUtility.h>
  #include <Dio_TargetTypes.h>


  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef void   Dio_ConfigType;
  typedef uint32 Dio_ChannelType;
  typedef uint8  Dio_LevelType;

#ifdef UNIT_TEST

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef struct {
  uint32_t PDOR;                              /**< Port Data Output Register, offset: 0x0 */
  uint32_t PSOR;                              /**< Port Set Output Register, offset: 0x4 */
  uint32_t PCOR;                              /**< Port Clear Output Register, offset: 0x8 */
  uint32_t PTOR;                              /**< Port Toggle Output Register, offset: 0xC */
  uint32_t PDIR;                              /**< Port Data Input Register, offset: 0x10 */
  uint32_t PDDR;                              /**< Port Data Direction Register, offset: 0x14 */
  uint32_t PIDR;                              /**< Port Input Disable Register, offset: 0x18 */
} GPIO_Type, *GPIO_MemMapPtr;

volatile GPIO_Type                dummyDioPTA;
volatile GPIO_Type                dummyDioPTB;
volatile GPIO_Type                dummyDioPTC;
volatile GPIO_Type                dummyDioPTD;
volatile GPIO_Type                dummyDioPTE;

/* GPIO - Peripheral instance base addresses */
/** Peripheral PTA base address */
#define PTA_BASE                                 (&dummyDioPTA)
/** Peripheral PTA base pointer */
#define PTA                                      ((GPIO_Type *)PTA_BASE)
/** Peripheral PTB base address */
#define PTB_BASE                                 (&dummyDioPTB)
/** Peripheral PTB base pointer */
#define PTB                                      ((GPIO_Type *)PTB_BASE)
/** Peripheral PTC base address */
#define PTC_BASE                                 (&dummyDioPTC)
/** Peripheral PTC base pointer */
#define PTC                                      ((GPIO_Type *)PTC_BASE)
/** Peripheral PTD base address */
#define PTD_BASE                                 (&dummyDioPTD)
/** Peripheral PTD base pointer */
#define PTD                                      ((GPIO_Type *)PTD_BASE)
/** Peripheral PTE base address */
#define PTE_BASE                                 (&dummyDioPTE)
/** Peripheral PTE base pointer */
#define PTE                                      ((GPIO_Type *)PTE_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                          { PTA_BASE, PTB_BASE, PTC_BASE, PTD_BASE, PTE_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { PTA, PTB, PTC, PTD, PTE }

#endif

  void          Dio_Init        (const Dio_ConfigType* ConfigPtr);
  void          Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
  Dio_LevelType Dio_ReadChannel (Dio_ChannelType ChannelId);

  #if defined(__cplusplus)
  }
  #endif

#endif // DIO_2019_02_08_H_
