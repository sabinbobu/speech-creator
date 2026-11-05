#ifndef DMA_2020_11_09_H_
  #define DMA_2020_11_09_H_

  #include <Std_Types.h>
  #include <Dma_TargetTypes.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef Dma_SpecificType Dma_ConfigType;

  extern const Dma_SpecificType Dma_Config;

  void Dma_Init(const Dma_ConfigType* ConfigPtr);
 

  #if defined(__cplusplus)
  }
  #endif

#endif // DMA_2020_11_09_H_
