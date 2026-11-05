
#if defined(CDDSPI_MAC_DECL_DEV_ENUM)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV                                                   typedef enum teCddSpiDev{
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)                               CDDSPI_CONCAT(CddSpi_eDev_,name),
#define END_CDDSPI_DEV                                                             CddSpi_eDev_Count}teCddSpiDev;

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP

#elif defined(CDDSPI_MAC_DECL_IFC_ENUM)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC                                                    typedef enum teCddSpiIfc{
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)                                                      CDDSPI_CONCAT(CddSpi_eIfc_,ifc),
#define END_CDDSPI_IFC                                                                               CddSpi_eIfc_Count}teCddSpiIfc;

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP

#elif defined(CDDSPI_MAC_DECL_IFCCFG)
#include "CddSpi_Mac_Prep.h"

#define BEGIN_CDDSPI_MAP
#define BEGIN_CDDSPI_IFC                                                       STATIC_AL  tsCddSpiIfcCfg  CddSpi_asIfcCfg[CddSpi_eIfc_Count] = {
#if ((CDDSPI_SINGLE_OPERATION == STD_ON) && (CDDSPI_CYCLIC_OPERATION == STD_ON))
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)                                                                                                { .eIfcSingleMode = (teCddSpiIfcSingleMode)hwmodesingle , \
                                                                                                                                                         .eIfcCyclicMode = (teCddSpiIfcCyclicMode)hwmodecyclic , \
                                                                                                                                                         .ucIfcMap       =                        ifc          },
#elif (CDDSPI_SINGLE_OPERATION == STD_ON)
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)                                                                                                { .eIfcSingleMode = (teCddSpiIfcSingleMode)hwmodesingle , \
                                                                                                                                                         .ucIfcMap       =                        ifc          },
#else
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)                                                                                                { .eIfcCyclicMode = (teCddSpiIfcCyclicMode)hwmodecyclic  ,\
                                                                                                                                                         .ucIfcMap       =                        ifc          },
#endif
#define END_CDDSPI_IFC                                                                                                                         };


#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par, ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP

#elif defined(CDDSPI_MAC_DECL_DEVHANDLE)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV                                                         STATIC_AL  tsCddSpiDevCfg CddSpi_asDeviceCfg[] = {
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par, ddcb)                                                              { .ucSpiIfc      = ifc,     \
                                                                                                                                         .ucCs          = cs,      \
                                                                                                                                         .ucDataLen     = len,     \
                                                                                                                                         .ucMaxElements = msg,     \
                                                                                                                                         .ucElements    = msg,     \
                                                                                                                                         .ucBrs         = brs,     \
                                                                                                                                         .ucCPol        = cpol,    \
                                                                                                                                         .ucCPha        = cpha,    \
                                                                                                                                         .ucDataDir     = msb },
  #define END_CDDSPI_DEV                                                                                                             };

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP

#elif defined(CDDSPI_MAC_DECL_DEVDYNCFG)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV                                                STATIC_AL CONST_AL tsCddSpiDevDynCfg CddSpi_asDevDynCfg[] = {
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)                                                                    {.fpDevDynCfgCb = ddcb},
#define END_CDDSPI_DEV                                                                                                               };

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP

#elif defined(CDDSPI_MAC_DECL_IFCSEQ_ENUM)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP                                                typedef enum teCddSpiIfcSeq{

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)                                                                           CDDSPI_CONCAT(CddSpi_eSeqIfc_,ifc),
#define BEGIN_CDDSPI_DEVCYC(name)
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP                                                                      CddSpi_eSeq_Count}teCddSpiIfcSeq;

#elif defined(CDDSPI_MAC_DECL_DEVFRM_ENUM)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV                                                                 typedef enum teCddSpiDevMaxElements{
#define CDDSPI_DEV_CFG(name,ifc,cs,len,frm,brs,cpol,cpha,msb,par,ddcb)                                                   CDDSPI_CONCAT(CddSpi_eDevMaxElements_,name) = (frm),
#define END_CDDSPI_DEV                                                                                              }teCddSpiDevMaxElements;

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP

#elif defined(CDDSPI_MAC_DECL_CBS)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)                                    void rxcb(uint16 unId, uint32 ulData); \
                                                                            uint32 txcb(uint16 unId);
#define CDDSPI_DEVCRC_CFG(crccheck)

#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP

#elif defined(CDDSPI_MAC_DECL_DEVCB)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)                                      STATIC_AL tsCddSpiCbData CDDSPI_CONCAT(CddSpi_asSpiDevCb_,name)[] = {
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)                                                                                                    { .unCbId  = cbid,                                        \
                                                                                                                                                  .sDevCb  = {(tfpCddSpiTxCb)txcb, (tfpCddSpiRxCb)rxcb}   \
                                                                                                                                                },
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC                                                                                                                   };

#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP


#elif defined(CDDSPI_MAC_DECL_DEVCB_ASSERT)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)                           CDDSPI_STATIC_ASSERT((sizeof(CDDSPI_CONCAT(CddSpi_asSpiDevCb_,name))/sizeof(tsCddSpiCbData)) == CDDSPI_CONCAT(CddSpi_eDevMaxElements_,name) ,"Number of CB elements does not match number of device element!");
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC 
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP


#elif defined(CDDSPI_MAC_DECL_TXBUFF)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)                 STATIC_AL  uint16 CDDSPI_CONCAT(CddSpi_aunTxBuff_,name)[CDDSPI_CONCAT(CddSpi_eDevMaxElements_,name)] = {0};
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP

#elif defined(CDDSPI_MAC_DECL_RXBUFF)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)                 STATIC_AL  uint16 CDDSPI_CONCAT(CddSpi_aunRxBuff_,name)[CDDSPI_CONCAT(CddSpi_eDevMaxElements_,name)] = {0};
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP

#elif defined(CDDSPI_MAC_DECL_SEQDATAIFC)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)                STATIC_AL tsCddSpiDevSeqData CDDSPI_CONCAT(CddSpi_asSeqDataIfc_,ifc)[]    = {
#define BEGIN_CDDSPI_DEVCYC(name)                                                                                                                {.eDev             = CDDSPI_CONCAT(CddSpi_eDev_,name),               \
                                                                                                                                                    .psCbData         = CDDSPI_CONCAT(CddSpi_asSpiDevCb_,name),         \
                                                                                                                                                    .punTxBuff        = CDDSPI_CONCAT(CddSpi_aunTxBuff_,name),          \
                                                                                                                                                    .punRxBuff        = CDDSPI_CONCAT(CddSpi_aunRxBuff_,name),
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define END_CDDSPI_DEVCYC                                                                                                                          },
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_SEQ                                                                                                                       };

#define END_CDDSPI_MAP

#elif defined(CDDSPI_MAC_DECL_SEQDATA)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP                                        STATIC_AL  tsCddSpiSeqData    CddSpi_asSeqData[]        = {

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)                                                                          {  .ucDeviceCount   = (sizeof(CDDSPI_CONCAT(CddSpi_asSeqDataIfc_,ifc))/sizeof(tsCddSpiDevSeqData))  ,    \
                                                                                                                                 .psDevData       = CDDSPI_CONCAT(CddSpi_asSeqDataIfc_,ifc)},
  #define BEGIN_CDDSPI_DEVCYC(name)
  #define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
  #define CDDSPI_DEVCRC_CFG(crccheck)
  #define END_CDDSPI_DEVCYC
  #define END_CDDSPI_SEQ

#define END_CDDSPI_MAP                                                                                                         };

#elif defined(CDDSPI_MAC_DECL_SEQHANDLE)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP                                                 STATIC_AL tsCddSpiSeqHandler  CddSpi_asSeqHandler[] = {

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle, hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)                                                                                             {.ucCycleCnt       = offs,                                                   \
                                                                                                                                                  .ucPrescaler      = pre,                                                    \
                                                                                                                                                  .ucTimeOutCnt  = waitcyclmax,                                            \
                                                                                                                                                  .ucTimeOutMax  = waitcyclmax,                                            \
                                                                                                                                                  .eSpiIfc          = CDDSPI_CONCAT(CddSpi_eIfc_,ifc)},
  #define BEGIN_CDDSPI_DEVCYC(name)
  #define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
  #define CDDSPI_DEVCRC_CFG(crccheck)
  #define END_CDDSPI_DEVCYC
  #define END_CDDSPI_SEQ

  #define END_CDDSPI_MAP                                                                                                                         };

#elif defined(CDDSPI_MAC_DECL_INTERLEAVE_DATA)
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP                                             STATIC_AL tsCddSpiTransferData CddSpi_msInterleaveData[CddSpi_eIfc_Count][10] = {

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle, hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)                                                                                             {
  #define BEGIN_CDDSPI_DEVCYC(name)
  #define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)                                                                                                    { .ulTCR_data = 0U,        \
                                                                                                                                                .ulTDR_data = 0U         \
                                                                                                                                              },
  #define CDDSPI_DEVCRC_CFG(crccheck)
  #define END_CDDSPI_DEVCYC
  #define END_CDDSPI_SEQ                                                                                                                        },

  #define END_CDDSPI_MAP                                                                                                                         };           \
                                                                                                                                STATIC_AL uint16 aunCddSpiReceiveData[CddSpi_eIfc_Count][10];

#else
#include "CddSpi_Mac_Prep.h"
#define BEGIN_CDDSPI_MAP

#define BEGIN_CDDSPI_IFC
#define CDDSPI_IFC(ifc,hwmodesingle, hwmodecyclic)
#define END_CDDSPI_IFC

#define BEGIN_CDDSPI_DEV
#define CDDSPI_DEV_CFG(name,ifc,cs,len,msg,brs,cpol,cpha,msb,par,ddcb)
#define END_CDDSPI_DEV

#define BEGIN_CDDSPI_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDSPI_DEVCYC(name)
#define CDDSPI_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDSPI_DEVCRC_CFG(crccheck)
#define END_CDDSPI_DEVCYC
#define END_CDDSPI_SEQ

#define END_CDDSPI_MAP
#endif
