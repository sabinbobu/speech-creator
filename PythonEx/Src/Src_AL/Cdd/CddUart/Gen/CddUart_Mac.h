/* Do not create header for this file ! */

#if defined(CDDUART_MAC_DECL_DEV_ENUM)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV                                                   typedef enum teCddUartDev{
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb)                                CDDUART_CONCAT(CddUart_eDev_,name),
#define END_CDDUART_DEV                                                             CddUart_eDev_Count}teCddUartDev;

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDUART_DEVCYC(name)
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDUART_DEVCRC_CFG(crccheck)
#define END_CDDUART_DEVCYC
#define END_CDDUART_SEQ

#define END_CDDUART_MAP

#elif defined(CDDUART_MAC_DECL_IFC_ENUM)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP

#define BEGIN_CDDUART_IFC                                                    typedef enum teCddUartIfc{
#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)                                                      CDDUART_CONCAT(CddUart_eIfc_,ifc),
#define END_CDDUART_IFC                                                                               CddUart_eIfc_Count}teCddUartIfc;

#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDUART_DEVCYC(name)
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDUART_DEVCRC_CFG(crccheck)
#define END_CDDUART_DEVCYC
#define END_CDDUART_SEQ

#define END_CDDUART_MAP

#elif defined(CDDUART_MAC_DECL_IFCCFG)
#include "CddUart_Mac_Prep.h"

#define BEGIN_CDDUART_MAP
#define BEGIN_CDDUART_IFC                                                       STATIC_AL  tsCddUartIfcCfg  CddUart_asIfcCfg[CddUart_eIfc_Count] = {

#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)                                                                                                { .eIfcSingleMode = (teCddUartIfcSingleMode)hwmodesingle , \
                                                                                                                                                         .eIfcCyclicMode = (teCddUartIfcCyclicMode)hwmodecyclic , \
                                                                                                                                                         .ucIfcMap       =                        ifc          },

#define END_CDDUART_IFC                                                                                                                         };


#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit, ddcb)
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDUART_DEVCYC(name)
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDUART_DEVCRC_CFG(crccheck)
#define END_CDDUART_DEVCYC
#define END_CDDUART_SEQ

#define END_CDDUART_MAP

#elif defined(CDDUART_MAC_DECL_DEVHANDLE)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV                                                         STATIC_AL  tsCddUartDevCfg CddUart_asDeviceCfg[] = {
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit, ddcb)                                                              { .ucUartIfc     = ifc,     \
                                                                                                                                                .ucDataLen     = datalen, \
                                                                                                                                                .ulBaudRate    = brs,     \
                                                                                                                                                .ucDataDir     = msb,     \
                                                                                                                                                .ucParity      = par,     \
                                                                                                                                                .ucStopBits    = stopbit  },
  #define END_CDDUART_DEV                                                                                                                   };

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDUART_DEVCYC(name)
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDUART_DEVCRC_CFG(crccheck)
#define END_CDDUART_DEVCYC
#define END_CDDUART_SEQ

#define END_CDDUART_MAP

#elif defined(CDDUART_MAC_DECL_DEVDYNCFG)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV                                                STATIC_AL CONST_AL tsCddUartDevDynCfg CddUart_asDevDynCfg[] = {
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb)                                                                     {.fpDevDynCfgCb = ddcb},
#define END_CDDUART_DEV                                                                                                               };

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDUART_DEVCYC(name)
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDUART_DEVCRC_CFG(crccheck)
#define END_CDDUART_DEVCYC
#define END_CDDUART_SEQ

#define END_CDDUART_MAP

#elif defined(CDDUART_MAC_DECL_IFCSEQ_ENUM)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP                                                typedef enum teCddUartIfcSeq{

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)                                                                           CDDUART_CONCAT(CddUart_eSeqIfc_,ifc),
#define BEGIN_CDDUART_DEVCYC(name)
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDUART_DEVCRC_CFG(crccheck)
#define END_CDDUART_DEVCYC
#define END_CDDUART_SEQ

#define END_CDDUART_MAP                                                                      CddUart_eSeq_Count}teCddUartIfcSeq;

#elif defined(CDDUART_MAC_DECL_CBS)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDUART_DEVCYC(name)
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)                                    void rxcb(const uint8* pucRxData, boolean boRxStatus); \
                                                                             void txcb(tsCddUart_MessageEntryType *psTxCbData);
#define CDDUART_DEVCRC_CFG(crccheck)

#define END_CDDUART_DEVCYC
#define END_CDDUART_SEQ

#define END_CDDUART_MAP

#elif defined(CDDUART_MAC_DECL_DEVCB)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDUART_DEVCYC(name)                                      STATIC_AL tsCddUartCbData CDDUART_CONCAT(CddUart_asUartDevCb_,name)[] = {
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)                                                                                                  {      .unCbId  = cbid,                                        \
                                                                                                                                                  .sDevCb  = {(tfpCddUartTxCb)txcb, (tfpCddUartRxCb)rxcb} \
                                                                                                                                           },
#define CDDUART_DEVCRC_CFG(crccheck)
#define END_CDDUART_DEVCYC                                                                                                                   };

#define END_CDDUART_SEQ

#define END_CDDUART_MAP

#elif defined(CDDUART_MAC_DECL_DEVCB_ASSERT)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDUART_DEVCYC(name)                           CDDUART_STATIC_ASSERT((sizeof(CDDUART_CONCAT(CddUart_asUartDevCb_,name))/sizeof(tsCddUartCbData)) == CDDUART_CONCAT(CddUart_eDevMaxElements_,name) ,"Number of CB elements does not match number of device element!");
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDUART_DEVCRC_CFG(crccheck)
#define END_CDDUART_DEVCYC 
#define END_CDDUART_SEQ

#define END_CDDUART_MAP

#elif defined(CDDUART_MAC_DECL_SEQDATAIFC)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)                STATIC_AL tsCddUartDevSeqData CDDUART_CONCAT(CddUart_asSeqDataIfc_,ifc)[]    = {
#define BEGIN_CDDUART_DEVCYC(name)                                                                                                                { .eDev      = CDDUART_CONCAT(CddUart_eDev_,name),               \
                                                                                                                                                    .psCbData  = CDDUART_CONCAT(CddUart_asUartDevCb_,name),          \
                                                                                                                                                    .ucCbCount = (sizeof(CDDUART_CONCAT(CddUart_asUartDevCb_,name)) / sizeof(tsCddUartCbData))
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
#define END_CDDUART_DEVCYC                                                                                                                          },
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_SEQ                                                                                                                       };

#define END_CDDUART_MAP

#elif defined(CDDUART_MAC_DECL_SEQDATA)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP                                        STATIC_AL tsCddUartSeqData    CddUart_asSeqData[]        = {

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle,hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)                                                                          {  .psDevData       = CDDUART_CONCAT(CddUart_asSeqDataIfc_,ifc)},
  #define BEGIN_CDDUART_DEVCYC(name)
  #define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
  #define CDDUART_DEVCRC_CFG(crccheck)
  #define END_CDDUART_DEVCYC
  #define END_CDDUART_SEQ

#define END_CDDUART_MAP                                                                                                         };

#elif defined(CDDUART_MAC_DECL_SEQHANDLE)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP                                                 STATIC_AL tsCddUartSeqHandler  CddUart_asSeqHandler[] = {

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle, hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)                                                                                             {.ucCycleCnt       = offs,                                                   \
                                                                                                                                                  .ucPrescaler      = pre,                                                    \
                                                                                                                                                  .ucTimeOutCnt  = waitcyclmax,                                            \
                                                                                                                                                  .ucTimeOutMax  = waitcyclmax,                                            \
                                                                                                                                                  .eUartIfc          = CDDUART_CONCAT(CddUart_eIfc_,ifc)},
  #define BEGIN_CDDUART_DEVCYC(name)
  #define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
  #define CDDUART_DEVCRC_CFG(crccheck)
  #define END_CDDUART_DEVCYC
  #define END_CDDUART_SEQ

  #define END_CDDUART_MAP                                                                                                                         };

#elif defined(CDDUART_MAC_DECL_INTERLEAVE_DATA)
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP                                             STATIC_AL uint8 CddUart_msInterleaveData[CddUart_eIfc_Count][10] = {

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle, hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)                                                                                             {
  #define BEGIN_CDDUART_DEVCYC(name)
  #define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)                                                                                                    { .ulTCR_data = 0U,        \
                                                                                                                                                .ulTDR_data = 0U         \
                                                                                                                                              },
  #define CDDUART_DEVCRC_CFG(crccheck)
  #define END_CDDUART_DEVCYC
  #define END_CDDUART_SEQ                                                                                                                        },

  #define END_CDDUART_MAP                                                                                                                         };           \
                                                                                                                                STATIC_AL uint8 aunCddUartReceiveData[CddUart_eIfc_Count][10];

#else
#include "CddUart_Mac_Prep.h"
#define BEGIN_CDDUART_MAP

#define BEGIN_CDDUART_IFC
#define CDDUART_IFC(ifc,hwmodesingle, hwmodecyclic)
#define END_CDDUART_IFC

#define BEGIN_CDDUART_DEV
#define CDDUART_DEV_CFG(name,ifc,datalen,brs,msb,par,stopbit,ddcb) 
#define END_CDDUART_DEV

#define BEGIN_CDDUART_SEQ(ifc,offs,pre,waitcyclmax)
#define BEGIN_CDDUART_DEVCYC(name)
#define CDDUART_DEVCB_CFG(cbid,txcb,rxcb)
#define CDDUART_DEVCRC_CFG(crccheck)
#define END_CDDUART_DEVCYC
#define END_CDDUART_SEQ

#define END_CDDUART_MAP
#endif
