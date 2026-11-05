// TBD insert correct header

#ifndef __NVM_ID_H__
  #define __NVM_ID_H__

  //lint -e451 Header file repeatedly included but does not have a standard include guard
  #include <Std_Types.h>
  //lint +e451 Header file repeatedly included but does not have a standard include guard
  #include <Nvm_Types.h>
  #include <MemIf.h>
  #include <Cfg/CfgId.h>
//lint -e451 Header file repeatedly included but does not have a standard include guard
  #include "string.h"
//lint +e451 Header file repeatedly included but does not have a standard include guard



  typedef struct structNvMConfigBlock
  {
    char strVersion[sizeof(CFG_InfoVersion)];     // 10+1=11 ASCII chars plus end of string terminator
    uint8 reserved;                               // padding
    uint8 aucKeyBytes[4];
  }
  tNvMConfigBlock;



Std_ReturnType NvmCheckConfigBlock(void);
void Nvm_InitConfigBlock(void);

#endif
