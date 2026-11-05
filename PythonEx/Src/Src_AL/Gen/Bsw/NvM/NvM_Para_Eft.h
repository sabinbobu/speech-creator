#ifndef _NVM_PARA_EFT_H_
  #define _NVM_PARA_EFT_H_


#define NVM_PARA_SIZE_SYSTEM_EFT         64


typedef struct
{
  uint8  aucProductDate[6];
  uint8  aucPartNumber[12];
  uint8  aucRunningNumber[6];
}
tNvmPara_ALTraceability;


typedef struct
{
  uint8  aucData[40];
}
tNvmPara_SupplierTraceability;


typedef struct
{
  tNvmPara_ALTraceability        ALTraceability;        //  24 bytes
  tNvmPara_SupplierTraceability  SupplierTraceability;  //  40 bytes
}                                                       // ---------
tNvmPara_EftBlock;                                      //  64 bytes



#endif // _NVM_PARA_EFT_H_
