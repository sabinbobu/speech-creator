//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
//-----------------------------------------------------------------------------
/// \file  Test.c
///
/// \brief Unit Test Cases for the module CddSpi of St126 project
///
//-----------------------------------------------------------------------------

//=============================================================================
//  Includes
//=============================================================================
// Standard unit test header
#include <ALUnitTest_UserInterface.h>
#include <stdio.h>

// Stub headers
#include "Test_Stubs.h"

// Headers of the unit test module
#include "Test.h"

//=============================================================================
//  Helper functions
//=============================================================================
//-----------------------------------------------------------------------------
/// \brief Mt_CddSpi_SaveInitContext
///
/// \descr Helper function to save Initialization context of CddSpi driver
///
/// \param 
///
/// \return void
//-----------------------------------------------------------------------------
void Mt_CddSpi_SaveInitContext(void)
{
	Mt_CddSpi_ucState = CddSpi_ucState;
#if (CDDSPI_STATUS_FAULT == STD_ON)
	Mt_CddSpi_ucStatusFaultVal = CddSpi_ucStatusFaultVal;
#endif
	Mt_dummyPERI = dummyPERI;
	memcpy(Mt_CddSpi_asIfcCfg, CddSpi_asIfcCfg, sizeof(Mt_CddSpi_asIfcCfg));
#if (CDDSPI_DYNAMIC_CFG == STD_ON)
	memcpy(Mt_CddSpi_asDevDynCfg, CddSpi_asDevDynCfg, sizeof(Mt_CddSpi_asDevDynCfg));
#endif
#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
	memcpy(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, SBC), CDDSPI_CONCAT(CddSpi_asSpiDevCb_, SBC), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, SBC)));
	memcpy(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, BOOST), CDDSPI_CONCAT(CddSpi_asSpiDevCb_, BOOST), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, BOOST)));
	memcpy(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, STP), CDDSPI_CONCAT(CddSpi_asSpiDevCb_, STP), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, STP)));
	memcpy(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, BUCK_0_5), CDDSPI_CONCAT(CddSpi_asSpiDevCb_, BUCK_0_5), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, BUCK_0_5)));
	memcpy(CDDSPI_CONCAT(Mt_CddSpi_asSeqDataIfc_, CDDSPI_IFC0), CDDSPI_CONCAT(CddSpi_asSeqDataIfc_, CDDSPI_IFC0), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSeqDataIfc_, CDDSPI_IFC0)));
	memcpy(CDDSPI_CONCAT(Mt_CddSpi_asSeqDataIfc_, CDDSPI_IFC1), CDDSPI_CONCAT(CddSpi_asSeqDataIfc_, CDDSPI_IFC1), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSeqDataIfc_, CDDSPI_IFC1)));
	memcpy(Mt_CddSpi_asSeqData, CddSpi_asSeqData, sizeof(Mt_CddSpi_asSeqData));
	memcpy(Mt_CddSpi_asDeviceCfg, CddSpi_asDeviceCfg, sizeof(Mt_CddSpi_asDeviceCfg));
	memcpy(Mt_CddSpi_asSeqHandler, CddSpi_asSeqHandler, sizeof(Mt_CddSpi_asSeqHandler));
#endif
	#warning "to be used when RTE is implemented"
		//Mt_Rte_GstppCddSpiStatusFault0_sStatusFault_ctaaSysMon_sData = Rte_GstppCddSpiStatusFault0_sStatusFault_ctaaSysMon_sData;
}

//-----------------------------------------------------------------------------
/// \brief Mt_CddSpi_RestoreInitContext
///
/// \descr Helper function to restore Initialization context of CddSpi driver  for its use as pre-requisite 
///        in Unit Test Cases. Mt_CddSpi_SaveInitContext must be called first.
///
/// \param 
///
/// \return void
//-----------------------------------------------------------------------------
void Mt_CddSpi_RestoreInitContext(void)
{
	CddSpi_ucState = Mt_CddSpi_ucState;
#if (CDDSPI_STATUS_FAULT == STD_ON)
	CddSpi_ucStatusFaultVal = Mt_CddSpi_ucStatusFaultVal;
#endif
	dummyPERI = Mt_dummyPERI;
	memcpy(CddSpi_asIfcCfg, Mt_CddSpi_asIfcCfg, sizeof(Mt_CddSpi_asIfcCfg));
#if (CDDSPI_DYNAMIC_CFG == STD_ON)
	memcpy(CddSpi_asDevDynCfg, Mt_CddSpi_asDevDynCfg, sizeof(Mt_CddSpi_asDevDynCfg));
#endif

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
	memcpy(CDDSPI_CONCAT(CddSpi_asSpiDevCb_, SBC), CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, SBC), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, SBC)));
	memcpy(CDDSPI_CONCAT(CddSpi_asSpiDevCb_, BOOST), CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, BOOST), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, BOOST)));
	memcpy(CDDSPI_CONCAT(CddSpi_asSpiDevCb_, STP), CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, STP), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, STP)));
	memcpy(CDDSPI_CONCAT(CddSpi_asSpiDevCb_, BUCK_0_5), CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, BUCK_0_5), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSpiDevCb_, BUCK_0_5)));
	memcpy(CDDSPI_CONCAT(CddSpi_asSeqDataIfc_, CDDSPI_IFC0), CDDSPI_CONCAT(Mt_CddSpi_asSeqDataIfc_, CDDSPI_IFC0), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSeqDataIfc_, CDDSPI_IFC0)));
	memcpy(CDDSPI_CONCAT(CddSpi_asSeqDataIfc_, CDDSPI_IFC1), CDDSPI_CONCAT(Mt_CddSpi_asSeqDataIfc_, CDDSPI_IFC1), sizeof(CDDSPI_CONCAT(Mt_CddSpi_asSeqDataIfc_, CDDSPI_IFC1)));
	memcpy(CddSpi_asSeqData, Mt_CddSpi_asSeqData, sizeof(Mt_CddSpi_asSeqData));
	memcpy(CddSpi_asDeviceCfg, Mt_CddSpi_asDeviceCfg, sizeof(Mt_CddSpi_asDeviceCfg));
	memcpy(CddSpi_asSeqHandler, Mt_CddSpi_asSeqHandler, sizeof(Mt_CddSpi_asSeqHandler));
#endif
	#warning "to be used when RTE is implemented"
		//Rte_GstppCddSpiStatusFault0_sStatusFault_ctaaSysMon_sData = Mt_Rte_GstppCddSpiStatusFault0_sStatusFault_ctaaSysMon_sData;
}

//=============================================================================================================================================================
//
//  CddSpi Unit Test Cases 
//
//
//=============================================================================================================================================================
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_Init
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
/// 
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_Init sets the correct state of the spi driver depending on its previous value.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           -   CddSpi_ucState: Previous Spi driver state
///         - Expected results
///           -   CddSpi_ucState: Next Spi driver state set by the FUT
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions: 
///         - Driver internal variables shall have the init value set statically 
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_Init(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8 ucSpiState;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint8 ucSpiState;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		//           Inputs              ||            Outputs
		// Previous state                ||  expected State 
		{{CDDSPI_STATE_RESET           } , {CDDSPI_STATE_SINGLE_OPERATION} },
		{{CDDSPI_STATE_RESET           } , {CDDSPI_STATE_SINGLE_OPERATION} },
		{{CDDSPI_STATE_SINGLE_OPERATION} , {CDDSPI_STATE_SINGLE_OPERATION} },
		{{CDDSPI_STATE_SINGLE_OPERATION} , {CDDSPI_STATE_SINGLE_OPERATION} },
		{{CDDSPI_STATE_CYCLIC_OPERATION} , {CDDSPI_STATE_CYCLIC_OPERATION} },
		{{CDDSPI_STATE_CYCLIC_OPERATION} , {CDDSPI_STATE_CYCLIC_OPERATION} },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		CddSpi_ucState = asTestCaseData[ucIdx].sInputData.ucSpiState;

		//Step 3) Call the FUT
		CddSpi_Init();

		//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
		AL_UNITTEST_CHECK(CddSpi_ucState, asTestCaseData[ucIdx].sOutputData.ucSpiState, == );
	}

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_DeInit
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_DeInit sets the correct state of the spi driver depending on its previous value.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - Previous Spi driver state
///         - Expected results
///           - Next Spi driver state set by the FUT
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///           -Module internal variables shall contain its init value set statically 
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_DeInit(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8 ucSpiState;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint8 ucSpiState;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		// Input                            ||  Output
		// Previous state                   ||  expected State 
		{ { CDDSPI_STATE_RESET            }  , {CDDSPI_STATE_RESET } },
		{ { CDDSPI_STATE_RESET            }  , {CDDSPI_STATE_RESET } },
		{ { CDDSPI_STATE_SINGLE_OPERATION }  , {CDDSPI_STATE_RESET } },
		{ { CDDSPI_STATE_SINGLE_OPERATION }  , {CDDSPI_STATE_RESET } },
		{ { CDDSPI_STATE_CYCLIC_OPERATION }  , {CDDSPI_STATE_RESET } },
		{ { CDDSPI_STATE_CYCLIC_OPERATION }  , {CDDSPI_STATE_RESET } },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		CddSpi_ucState = asTestCaseData[ucIdx].sInputData.ucSpiState;

		//Step 3) Call the FUT
		CddSpi_DeInit();

		//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
		AL_UNITTEST_CHECK(CddSpi_ucState, asTestCaseData[ucIdx].sOutputData.ucSpiState, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_GetState
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_GetState returns the right value depending on the value of the internal variable CddSpi_ucState
///        which stores the state of the driver
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ucSpiState : Value of the internal variable CddSpi_ucState
///         - Expected results
///           - ucRetVal   : Return value by the FUT
///
///       For further information about specific input/outputs variables refer to the input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///           -Module internal variables shall contain its init value set statically
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_GetState(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8 ucSpiState;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint8 ucRetVal;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		// Input                            ||  Output
		// Previous state                   ||  expected State 
		{ { CDDSPI_STATE_RESET            }  , {CDDSPI_STATE_RESET              } },
		{ { CDDSPI_STATE_SINGLE_OPERATION }  , {CDDSPI_STATE_SINGLE_OPERATION   } },
		{ { CDDSPI_STATE_CYCLIC_OPERATION }  , {CDDSPI_STATE_CYCLIC_OPERATION   } },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		CddSpi_ucState = asTestCaseData[ucIdx].sInputData.ucSpiState;

		//Step 3) Call the FUT
		uint8 ucRetVal = CddSpi_GetState();

		//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
		AL_UNITTEST_CHECK(ucRetVal, asTestCaseData[ucIdx].sOutputData.ucRetVal, == );
	}
}

#if (CDDSPI_SINGLE_OPERATION == STD_ON)
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_TransferMsg
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// \Test Case Description
///    - Test subject: 
///        Check that the function CddSpi_TransferMsg returns the correct value depending on the value of the SPI module state , the 
///        Device Id which is passed to the function as parameter and if the time out for transmission is elepased or not.
///        Check if the Received HW Data is copied in the data parameter passed as parameter to the function.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ucDevice : Device Id passed to the function as parameter
///           - CddSpi_ucState: Current Spi driver state
///           - psPeri->unRDR.ulData : HW Buffer content
///           - Time Out Error Condition  (Estimulated by Error Injection)
///         - Expected results
///           - Return Value of the FUT
///           - pucData: Data copied in data argument address
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions: 
///           - Module internal variables shall contain its init value set statically
///           - Timeout error injection shall be simulated by using a dummy structure which emulates the real HW register set of the SPI level driver
//-----------------------------------------------------------------------------
void Mt_CddSpi_TransferMsg(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8         ucDevice;
		uint8         ucSpiState;
		uint16        unRxHwBuff;
		boolean       boTimeOut;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		boolean boRetVal;
		uint16  unSimReceivedData;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		//                                               Inputs                                                       ||                  Outputs
		// Device ID               | Current SPI state             | Rx Hw Buffer content     |  TimeOut  error       || FUT Return Value | Data copied in data argument address
		{ {CDDSPI_DEVICE(SBC)      , CDDSPI_STATE_RESET            , 0x00                      , FALSE               } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(SBC)      , CDDSPI_STATE_RESET            , 0x00                      , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(SBC)      , CDDSPI_STATE_RESET            , CDDSPI_UT_UINT16_PATTERN  , FALSE               } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(SBC)      , CDDSPI_STATE_RESET            , CDDSPI_UT_UINT16_PATTERN  , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(SBC)      , CDDSPI_STATE_SINGLE_OPERATION , 0x00                      , FALSE               } , {TRUE           , 0x00                     }},
		{ {CDDSPI_DEVICE(SBC)      , CDDSPI_STATE_SINGLE_OPERATION , 0x00                      , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(SBC)      , CDDSPI_STATE_SINGLE_OPERATION , CDDSPI_UT_UINT16_PATTERN  , FALSE               } , {TRUE           , CDDSPI_UT_UINT16_PATTERN }},
		{ {CDDSPI_DEVICE(SBC)      , CDDSPI_STATE_SINGLE_OPERATION , CDDSPI_UT_UINT16_PATTERN  , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BUCK_0_5) , CDDSPI_STATE_RESET            , 0x00                      , FALSE               } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BUCK_0_5) , CDDSPI_STATE_RESET            , 0x00                      , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BUCK_0_5) , CDDSPI_STATE_RESET            , CDDSPI_UT_UINT16_PATTERN  , FALSE               } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BUCK_0_5) , CDDSPI_STATE_RESET            , CDDSPI_UT_UINT16_PATTERN  , TRUE                } , {FALSE          , 0x00                     }},
		//--------------The bucks configuration is not used in single mode transfers
		{ {CDDSPI_DEVICE(BUCK_0_5) , CDDSPI_STATE_SINGLE_OPERATION , 0x00                      , FALSE               } , {TRUE           , 0x00                     }},
		{ {CDDSPI_DEVICE(BUCK_0_5) , CDDSPI_STATE_SINGLE_OPERATION , 0x00                      , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BUCK_0_5) , CDDSPI_STATE_SINGLE_OPERATION , CDDSPI_UT_UINT16_PATTERN  , FALSE               } , {TRUE           , CDDSPI_UT_UINT16_PATTERN }},
		{ {CDDSPI_DEVICE(BUCK_0_5) , CDDSPI_STATE_SINGLE_OPERATION , CDDSPI_UT_UINT16_PATTERN  , TRUE                } , {FALSE          , 0x00                     }},
		//---------------------------------
		{ {CDDSPI_DEVICE(STP)  , CDDSPI_STATE_RESET            , 0x00                      , FALSE               } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(STP)  , CDDSPI_STATE_RESET            , 0x00                      , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(STP)  , CDDSPI_STATE_RESET            , CDDSPI_UT_UINT16_PATTERN  , FALSE               } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(STP)  , CDDSPI_STATE_RESET            , CDDSPI_UT_UINT16_PATTERN  , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(STP)  , CDDSPI_STATE_SINGLE_OPERATION , 0x00                      , FALSE               } , {TRUE           , 0x00                     }},
		{ {CDDSPI_DEVICE(STP)  , CDDSPI_STATE_SINGLE_OPERATION , 0x00                      , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(STP)  , CDDSPI_STATE_SINGLE_OPERATION , CDDSPI_UT_UINT16_PATTERN  , FALSE               } , {TRUE           , CDDSPI_UT_UINT16_PATTERN }},
		{ {CDDSPI_DEVICE(STP)  , CDDSPI_STATE_SINGLE_OPERATION , CDDSPI_UT_UINT16_PATTERN  , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BOOST)    , CDDSPI_STATE_RESET            , 0x00                      , FALSE               } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BOOST)    , CDDSPI_STATE_RESET            , 0x00                      , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BOOST)    , CDDSPI_STATE_RESET            , CDDSPI_UT_UINT16_PATTERN  , FALSE               } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BOOST)    , CDDSPI_STATE_RESET            , CDDSPI_UT_UINT16_PATTERN  , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BOOST)    , CDDSPI_STATE_SINGLE_OPERATION , 0x00                      , FALSE               } , {TRUE           , 0x00                     }},
		{ {CDDSPI_DEVICE(BOOST)    , CDDSPI_STATE_SINGLE_OPERATION , 0x00                      , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(BOOST)    , CDDSPI_STATE_SINGLE_OPERATION , CDDSPI_UT_UINT16_PATTERN  , FALSE               } , {TRUE           , CDDSPI_UT_UINT16_PATTERN }},
		{ {CDDSPI_DEVICE(BOOST)    , CDDSPI_STATE_SINGLE_OPERATION , CDDSPI_UT_UINT16_PATTERN  , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(Count)    , CDDSPI_STATE_SINGLE_OPERATION , 0x00                      , FALSE               } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(Count)    , CDDSPI_STATE_CYCLIC_OPERATION , 0x00                      , TRUE                } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(Count)    , CDDSPI_STATE_SINGLE_OPERATION , CDDSPI_UT_UINT16_PATTERN  , FALSE               } , {FALSE          , 0x00                     }},
		{ {CDDSPI_DEVICE(Count)    , CDDSPI_STATE_CYCLIC_OPERATION , CDDSPI_UT_UINT16_PATTERN  , TRUE                } , {FALSE          , 0x00                     }},
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		teCddSpiDev eDevice = asTestCaseData[ucIdx].sInputData.ucDevice;
		uint16      unDummyBuff = 0;
		CddSpi_ucState = asTestCaseData[ucIdx].sInputData.ucSpiState;
		psPeri->unRDR.ulData = asTestCaseData[ucIdx].sInputData.unRxHwBuff;
		psPeri->unFSR.sBit.u3RXCOUNT |= (asTestCaseData[ucIdx].sInputData.boTimeOut == FALSE) ? (CDDSPI_S32K_14X_RX_FIFO_STATUS_MSK & CddSpi_asDeviceCfg[asTestCaseData[ucIdx].sInputData.ucDevice].ucElements) : 0x00U;

		//Step 3) Call the FUT
		boolean boRetVal = CddSpi_TransferMsg(eDevice, &unDummyBuff);

		//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
		AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.boRetVal, == );
		AL_UNITTEST_CHECK(unDummyBuff, asTestCaseData[ucIdx].sOutputData.unSimReceivedData, == );
	}
}
#endif


#if (CDDSPI_DYNAMIC_CFG == STD_ON)
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_SetDynamicCfg
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_SteDynamicCfg calculates the right number of active elements of the devices which
///      have an non NULL_PTR Dynamic Configuration Call Back, that is, CDDSPI_DEVICE(BUCK_0_6) and CDDSPI_DEVICE(STP)  and set its value 
///      in the internal variable CddSpi_asDeviceCfg accordingly
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///             -eDev : Device to be evaluated 
///             -unFootPrint: Value provided to the argument of the  Dynamic Configuration CallOut, used to calculate the number of active elemnts of a device
///             -fpDynCallOut : Dynamic Configuration Call Out, called by the function to get the footprint 
///             -boDynCallOutReturn: Return value of the Dynamic Configuration Call Out
///         - Expected results
///             -ucDevElemts: Number of active elements of the device, stored in an internal variable CddSpi_asDeviceCfg
///             -boRetVal: Return value of the FUT
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///           -Module internal variables shall contain its init value set statically
///
//------------------------------------------------------------------------------
void Mt_CddSpi_SetDynamicCfg(void)
{
  typedef struct tsTestCaseDataInput
  {
    teCddSpiDev        eDev;
    uint16             unFootPrint;
    tfpCddSpiDevDynCfg fpDynCallOut;
    boolean            boDynCallOutReturn;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint8   ucDevElemts;
    boolean boRetVal;
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;
  //CddTps92520_SpiGetConfig_boReturn = FALSE;
  tsTestCaseData asTestCaseData[] =
  {
    //           Inputs                                                                                                 ||                          Outputs
    //      Device              |FootPrint| Dynamic Configuration CallOut | Dynamic Configuration CallOut Return        || Device Elements                                                  | Return
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x0U    , NULL_PTR                      , FALSE                                      } , { CddSpi_asDeviceCfg[CDDSPI_DEVICE(BUCK_0_5)].ucMaxElements      , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x3FU   , NULL_PTR                      , FALSE                                      } , { CddSpi_asDeviceCfg[CDDSPI_DEVICE(BUCK_0_5)].ucMaxElements      , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x0U    , NULL_PTR                      , TRUE                                      } , { CddSpi_asDeviceCfg[CDDSPI_DEVICE(BUCK_0_5)].ucMaxElements      , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x3FU   , NULL_PTR                      , TRUE                                      } , { CddSpi_asDeviceCfg[CDDSPI_DEVICE(BUCK_0_5)].ucMaxElements      , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x0FU   , CddTps92520_SpiGetConfig          , FALSE                                      } , { CddSpi_asDeviceCfg[CDDSPI_DEVICE(BUCK_0_5)].ucMaxElements , FALSE }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x3FU   , CddTps92520_SpiGetConfig          , FALSE                                      } , { CddSpi_asDeviceCfg[CDDSPI_DEVICE(BUCK_0_5)].ucMaxElements , FALSE }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x00U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 0U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x01U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 1U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x02U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 1U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x03U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 2U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x04U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 1U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x05U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 2U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x06U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 2U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x07U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 3U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x08U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 1U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x09U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 2U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x0AU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 2U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x0BU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 3U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x0CU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 2U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x0DU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 3U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x0EU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 3U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x0FU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 4U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x10U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 1U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x11U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 2U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x12U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 2U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x13U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 3U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x14U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 2U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x15U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 3U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x16U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 3U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x17U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 4U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x18U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 2U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x19U   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 3U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x1AU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 3U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x1BU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 4U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x1CU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 3U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x1DU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 4U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x1EU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 4U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(BUCK_0_5)  , 0x1FU   , CddTps92520_SpiGetConfig          ,TRUE                                       } , { 5U                                                        , TRUE  }},
    { {CDDSPI_DEVICE(SBC)       , 0x1FU   , NULL_PTR                      , TRUE                                       } , { CddSpi_asDeviceCfg[CDDSPI_DEVICE(SBC)].ucMaxElements          , TRUE  }},
  };

  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
  {
    //Step 1: Set pre-conditions
    Mt_CddSpi_RestoreInitContext();

    //Step 2) Assign Input values
    CddTps92520_SpiGetConfig_unData = asTestCaseData[ucIdx].sInputData.unFootPrint;        //Mechanism to stimulate FootPrint Input
    CddTps92520_SpiGetConfig_boReturn = asTestCaseData[ucIdx].sInputData.boDynCallOutReturn; //Mechanism to Stimulate Call Out Return Input
    CddSpi_asDevDynCfg[asTestCaseData[ucIdx].sInputData.eDev].fpDevDynCfgCb = asTestCaseData[ucIdx].sInputData.fpDynCallOut;

    //Step 3) Call UUT
    boolean boRetVal = CddSpi_SetDynamicCfg(asTestCaseData[ucIdx].sInputData.eDev);

    //Step 4) Check expected output values
    AL_UNITTEST_CHECK(CddSpi_asDeviceCfg[asTestCaseData[ucIdx].sInputData.eDev].ucElements, asTestCaseData[ucIdx].sOutputData.ucDevElemts, == );
    AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.boRetVal, == );

  }
}
//-----------------------------------------------------------------------------
/// \Test Case :  Mt_CddSpi_UnSetDevCb
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_UnSetDevCb deactivate the Tx-RX Device (parameter) CallBack Id (parameter)
///      by setting it to NULL_PTR
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///           - eDev               : Device passed as argument to the FUT  to unset Tx-Rx Callbacks
///           - ucIfcDevIsAttached : Spi Interface that eDev is attached to
///           - ucSeqIfc           : Spi Interface of the sequence used for the Unit Test Case
///           - aboElementActive[] : Array which contains a set of CallBacks Ids to be (FALSE) or not(TRUE) deactivated
///         - Expected results
///           - asCb[]             : Array which contains device Callbacks
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///         - Initialize all Device Call Back to a non NULL_PTR value
///         - Set SeqIdx to a plausible value  , ucSeqIdx = 1U
///         - Set ucDevIdx to a plausible value, ucDevIdx = 0U
///
//------------------------------------------------------------------------------
void Mt_CddSpi_UnSetDevCb(void)
{
  tfpCddSpiTxCb fpTxDev = CddTps92520_SpiTx;
  tfpCddSpiRxCb fpRxDev = CddTps92520_SpiRx;
  uint8         ucSeqIdx = 1U;  //Seq Number configured in CddSpi_Cfg.h for ucDevName
  uint8         ucDevIdx = 0U;  //Dev Index in the sequence

  typedef struct tsTestCaseDataInput
  {
    teCddSpiDev  eDev;
    uint8        ucIfcDevIsAttached;
    uint8        ucSeqIfc;
    uint8        ucIfcMap;
    boolean      aboElementActive[10];
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    tsCddSpiDevCb asCb[10];
  }tsTestCaseDataOutput;

  typedef struct tsTestCaseData
  {
    tsTestCaseDataInput  sInputData;
    tsTestCaseDataOutput sOutputData;
  }tsTestCaseData;

  tsTestCaseData asTestCaseData[] =
  {
    //                              Inputs                                                                                                                                                  || Outputs
    //        Device           | IFc Device is attached | Sequence Interface                 | IFc Map  I       |   Array to  deactivate (FALSE)/ activate (TRUE) a callback I              ||                                                                               
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC0            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, FALSE, TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC0            , CDDSPI_IFC1                        ,  0U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  0U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  0U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  0U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE  } }                     , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  0U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE  } }                     , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, TRUE , FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, TRUE , FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, TRUE , TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, TRUE , TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, TRUE , FALSE, FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, TRUE , FALSE, FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, TRUE , FALSE, TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, TRUE , FALSE, TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, TRUE , TRUE , FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, TRUE , TRUE , FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, TRUE , TRUE , TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, TRUE , TRUE , TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , FALSE, FALSE, FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , FALSE, FALSE, FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , FALSE, FALSE, TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , FALSE, FALSE, TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , FALSE, TRUE , FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , FALSE, TRUE , FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , FALSE, TRUE , TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , FALSE, TRUE , TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , TRUE , FALSE, FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , TRUE , FALSE, FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , TRUE , FALSE, TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , TRUE , FALSE, TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , TRUE , TRUE , FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , TRUE , TRUE , FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , TRUE , TRUE , TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, TRUE , TRUE , TRUE , TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, FALSE, FALSE, FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, FALSE, FALSE, TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, FALSE, FALSE, TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, FALSE, TRUE , FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, FALSE, TRUE , FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, FALSE, TRUE , TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, FALSE, TRUE , TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, TRUE , FALSE, FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, TRUE , FALSE, FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, TRUE , FALSE, TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, TRUE , FALSE, TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, TRUE , TRUE , FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, TRUE , TRUE , FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, TRUE , TRUE , TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , FALSE, TRUE , TRUE , TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , FALSE, FALSE, FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , FALSE, FALSE, FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , FALSE, FALSE, TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , FALSE, FALSE, TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , FALSE, TRUE , FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , FALSE, TRUE , FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , FALSE, TRUE , TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , FALSE, TRUE , TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , TRUE , FALSE, FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , TRUE , FALSE, FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , TRUE , FALSE, TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , TRUE , FALSE, TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , TRUE , TRUE , FALSE, FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , TRUE , TRUE , FALSE, TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , TRUE , TRUE , TRUE , FALSE } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { FALSE, TRUE , TRUE , TRUE , TRUE , TRUE , TRUE  } }                      , { { { NULL_PTR , NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, FALSE, FALSE, TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, FALSE, FALSE, TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, FALSE, TRUE , FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, FALSE, TRUE , FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, FALSE, TRUE , TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, FALSE, TRUE , TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, TRUE , FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, TRUE , FALSE, FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, TRUE , FALSE, TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, TRUE , FALSE, TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, TRUE , TRUE , FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, TRUE , TRUE , FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, TRUE , TRUE , TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, FALSE, TRUE , TRUE , TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , FALSE, FALSE, FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , FALSE, FALSE, TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , FALSE, FALSE, TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , FALSE, TRUE , FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , FALSE, TRUE , FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , FALSE, TRUE , TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , FALSE, TRUE , TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , TRUE , FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , TRUE , FALSE, FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , TRUE , FALSE, TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , TRUE , FALSE, TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , TRUE , TRUE , FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , TRUE , TRUE , FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , TRUE , TRUE , TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , FALSE, TRUE , TRUE , TRUE , TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, FALSE, FALSE, FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, FALSE, FALSE, TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, FALSE, FALSE, TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, FALSE, TRUE , FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, FALSE, TRUE , FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, FALSE, TRUE , TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, FALSE, TRUE , TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, TRUE , FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, TRUE , FALSE, FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, TRUE , FALSE, TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, TRUE , FALSE, TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, TRUE , TRUE , FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, TRUE , TRUE , FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, TRUE , TRUE , TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , FALSE, TRUE , TRUE , TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , FALSE, FALSE, FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , FALSE, FALSE, TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , FALSE, FALSE, TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , FALSE, TRUE , FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , FALSE, TRUE , FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , FALSE, TRUE , TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , FALSE, TRUE , TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , TRUE , FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , TRUE , FALSE, FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , TRUE , FALSE, TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , TRUE , FALSE, TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , TRUE , TRUE , FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , TRUE , TRUE , FALSE, TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { NULL_PTR, NULL_PTR } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC1            , CDDSPI_IFC1                        ,  1U,             { TRUE , TRUE , TRUE , TRUE , TRUE , TRUE , TRUE  } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC0            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BUCK_0_5) ,CDDSPI_IFC0            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(STP)      ,CDDSPI_IFC0            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(SBC)      ,CDDSPI_IFC0            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },
    { { CDDSPI_DEVICE(BOOST)    ,CDDSPI_IFC0            , CDDSPI_IFC1                        ,  1U,             { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE } }                      , { { { fpTxDev , fpRxDev   }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  }, { fpTxDev , fpRxDev  } } } },

  };


  for (uint8 ucIdx = 0U; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
  {
    //Step 1: Set pre-conditions
    Mt_CddSpi_RestoreInitContext();
    uint8    ucMaxElemtsDev = CddSpi_asDeviceCfg[asTestCaseData[ucIdx].sInputData.eDev].ucMaxElements;

    for (uint8 ucElemts = 0U; ucElemts < ucMaxElemtsDev; ucElemts++)
    {
      CddSpi_asSeqData[ucSeqIdx].psDevData[ucDevIdx].psCbData[ucElemts].sDevCb.fpRx = fpRxDev;
      CddSpi_asSeqData[ucSeqIdx].psDevData[ucDevIdx].psCbData[ucElemts].sDevCb.fpTx = fpTxDev;
    }

    //Step 2) Assign Input values
    CddSpi_asDeviceCfg[asTestCaseData[ucIdx].sInputData.eDev].ucSpiIfc = asTestCaseData[ucIdx].sInputData.ucIfcDevIsAttached;
    CddSpi_asIfcCfg[CddSpi_asSeqHandler[ucSeqIdx].eSpiIfc].ucSeqMap = asTestCaseData[ucIdx].sInputData.ucSeqIfc;
    CddSpi_asIfcCfg[CddSpi_asSeqHandler[ucSeqIdx].eSpiIfc].ucIfcMap = asTestCaseData[ucIdx].sInputData.ucIfcMap;

    //Step 3) Call FUT
    for (uint8 ucElemts = 0U; ucElemts < ucMaxElemtsDev; ucElemts++)
    {
      if (asTestCaseData[ucIdx].sInputData.aboElementActive[ucElemts] == FALSE)
      {
        CddSpi_UnSetDevCb(asTestCaseData[ucIdx].sInputData.eDev, ucElemts);
      }
    }

    //Step 4) Check expected output values
    for (uint8 ucElemts = 0U; ucElemts < ucMaxElemtsDev; ucElemts++)
    {
      AL_UNITTEST_CHECK(CddSpi_asSeqData[ucSeqIdx].psDevData[ucDevIdx].psCbData[ucElemts].sDevCb.fpTx, asTestCaseData[ucIdx].sOutputData.asCb[ucElemts].fpTx, == );
      AL_UNITTEST_CHECK(CddSpi_asSeqData[ucSeqIdx].psDevData[ucDevIdx].psCbData[ucElemts].sDevCb.fpRx, asTestCaseData[ucIdx].sOutputData.asCb[ucElemts].fpRx, == );
    }
  }
}
#endif

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_Start
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_Start sets the right CddSpi_ucState value depening on its previous value and 
///      the timeout condition
///      Check that the correct Error Flag is set in internal variable to collect status fault, if EFT Data error is detected
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///             - ucSpiState     : Previous Spi driver state
///             - boTimeout      : TimeOut is  elpased (fault injection)
///
///         - Expected results
///             - ucSpiState     : Expected Spi driver state set by the FUT
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///         - Timeout error injection shall be simulated by using a dummy structure which emulates the real HW register set of the SPI level driver
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_Start(void)
{
  typedef struct tsTestCaseDataInput
  {
    uint8         ucSpiState;
    boolean       boDynamicCfgValid;
    boolean       boTimeOut;
  }tsTestCaseDataInput;

  typedef struct tsTestCaseDataOutput
  {
    uint8         ucSpiState;
    uint8         ucStatusFault;
  }tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;


  static tsTestCaseData asTestCaseData[] =
  {
    //                     Inputs                              ||             Outputs
    // Previous state                 | Dyn Valid | TimeOut    ||  expected State                SA Mask                     Dynamic Config Error Mask
    {{CDDSPI_STATE_RESET              , FALSE     , FALSE  }   , {CDDSPI_STATE_RESET           , 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_RESET              , FALSE     , TRUE   }   , {CDDSPI_STATE_RESET           , 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_RESET              , TRUE      , FALSE  }   , {CDDSPI_STATE_RESET           , 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_RESET              , TRUE      , TRUE   }   , {CDDSPI_STATE_RESET           , 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_SINGLE_OPERATION   , FALSE     , FALSE  }   , {CDDSPI_STATE_SINGLE_OPERATION, CDDSPI_STATUS_FAULT_SA_MSK | CDDSPI_STATUS_FAULT_DYNAMIC_CONFIG_ERROR_MSK } },
    {{CDDSPI_STATE_SINGLE_OPERATION   , FALSE     , TRUE   }   , {CDDSPI_STATE_SINGLE_OPERATION, CDDSPI_STATUS_FAULT_SA_MSK | CDDSPI_STATUS_FAULT_DYNAMIC_CONFIG_ERROR_MSK } },
    {{CDDSPI_STATE_SINGLE_OPERATION   , TRUE      , FALSE  }   , {CDDSPI_STATE_CYCLIC_OPERATION, CDDSPI_STATUS_FAULT_SA_MSK | 0x00                                         } },
    {{CDDSPI_STATE_SINGLE_OPERATION   , TRUE      , TRUE   }   , {CDDSPI_STATE_CYCLIC_OPERATION, CDDSPI_STATUS_FAULT_SA_MSK | 0x00                                         } },
    {{CDDSPI_STATE_CYCLIC_OPERATION   , FALSE     , FALSE  }   , {CDDSPI_STATE_CYCLIC_OPERATION, 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_CYCLIC_OPERATION   , FALSE     , TRUE   }   , {CDDSPI_STATE_CYCLIC_OPERATION, 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_CYCLIC_OPERATION   , TRUE      , FALSE  }   , {CDDSPI_STATE_CYCLIC_OPERATION, 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_CYCLIC_OPERATION   , TRUE      , TRUE   }   , {CDDSPI_STATE_CYCLIC_OPERATION, 0x00 | 0x00                                         } },
  };

	for (uint8 ucIdx = 0U; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		CddSpi_ucState = asTestCaseData[ucIdx].sInputData.ucSpiState;
    CddTps92520_SpiGetConfig_boReturn = asTestCaseData[ucIdx].sInputData.boDynamicCfgValid;  //Mechanism to stimulate return value of Dynami Configuration
		psPeri->unSR.sBit.u1MBF = asTestCaseData[ucIdx].sInputData.boTimeOut;                                     //Mechanism to stimulate time out condition

		//Step 3) Call the FUT
		CddSpi_Start();

		//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value
		AL_UNITTEST_CHECK(CddSpi_ucState, asTestCaseData[ucIdx].sOutputData.ucSpiState, == );
#if (CDDSPI_STATUS_FAULT == STD_ON)
    AL_UNITTEST_CHECK(CddSpi_ucStatusFaultVal, asTestCaseData[ucIdx].sOutputData.ucStatusFault, == );
#endif
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_Stop
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_Stop sets the correct CddSpi_ucState value depending on its previous state
///      Check that the internal variable  which collects status fault information is cleared (0x00)
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ucSpiState  : Previous Spi driver state
///           - eCyclicMode : Mode the sequence operates in Cyclic context
///           - boTimeOut   : TimeOut is  elpased (fault injection)
///         - Expected results
///           - ucSpiState    : Expected Spi driver state set by the FUT
///           - ucStatusFault : Expect value of internal variable which collecst all error flags
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically
///         - Timeout error injection shall be simulated by using a dummy structure which emulates the real HW register set of the SPI level driver
///         - CddSpi_ucStatusFault variable shall be set to an non zero value
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_Stop(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8                 ucSpiState;
		teCddSpiIfcCyclicMode eCyclicMode;
		boolean               boTimeOut;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint8         ucSpiState;
		uint8         ucStatusFault;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		// Input                                                                     ||  Output
		// Previous state                | CylicMode                      | Tiemout  ||  expected State               |Status Fault Value 
		{{CDDSPI_STATE_RESET             , CddSpi_eIfcCyclicMode_Polling  , FALSE } , {CDDSPI_STATE_RESET             , 0x00             } },
		{{CDDSPI_STATE_RESET             , CddSpi_eIfcCyclicMode_Polling  , TRUE  } , {CDDSPI_STATE_RESET             , 0x00             } },
		{{CDDSPI_STATE_RESET             , CddSpi_eIfcCyclicMode_Interrupt, FALSE } , {CDDSPI_STATE_RESET             , 0x00             } },
		{{CDDSPI_STATE_RESET             , CddSpi_eIfcCyclicMode_Interrupt, TRUE  } , {CDDSPI_STATE_RESET             , 0x00             } },
		{{CDDSPI_STATE_RESET             , CddSpi_eIfcCyclicMode_DMA      , FALSE } , {CDDSPI_STATE_RESET             , 0x00             } },
		{{CDDSPI_STATE_RESET             , CddSpi_eIfcCyclicMode_DMA      , TRUE  } , {CDDSPI_STATE_RESET             , 0x00             } },
		{{CDDSPI_STATE_CYCLIC_OPERATION  , CddSpi_eIfcCyclicMode_Polling  , FALSE } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_CYCLIC_OPERATION  , CddSpi_eIfcCyclicMode_Polling  , TRUE  } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_CYCLIC_OPERATION  , CddSpi_eIfcCyclicMode_Interrupt, FALSE } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_CYCLIC_OPERATION  , CddSpi_eIfcCyclicMode_Interrupt, TRUE  } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_CYCLIC_OPERATION  , CddSpi_eIfcCyclicMode_DMA      , FALSE } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_CYCLIC_OPERATION  , CddSpi_eIfcCyclicMode_DMA      , TRUE  } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_SINGLE_OPERATION  , CddSpi_eIfcCyclicMode_DMA      , FALSE } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_SINGLE_OPERATION  , CddSpi_eIfcCyclicMode_DMA      , TRUE  } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_SINGLE_OPERATION  , CddSpi_eIfcCyclicMode_Interrupt, FALSE } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_SINGLE_OPERATION  , CddSpi_eIfcCyclicMode_Interrupt, TRUE  } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_SINGLE_OPERATION  , CddSpi_eIfcCyclicMode_DMA      , FALSE } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
		{{CDDSPI_STATE_SINGLE_OPERATION  , CddSpi_eIfcCyclicMode_DMA      , TRUE  } , {CDDSPI_STATE_SINGLE_OPERATION  , 0x00             } },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;
#if (CDDSPI_STATUS_FAULT == STD_ON)
		CddSpi_ucStatusFaultVal |= CDDSPI_STATUS_FAULT_SA_MSK;
#endif
		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		CddSpi_ucState = asTestCaseData[ucIdx].sInputData.ucSpiState;
		psPeri->unSR.sBit.u1MBF = asTestCaseData[ucIdx].sInputData.boTimeOut;

		for (uint8 ucIfcIdx = 0; ucIfcIdx < CddSpi_eIfc_Count; ucIfcIdx++)
		{
			CddSpi_asIfcCfg[ucIfcIdx].eIfcCyclicMode = asTestCaseData[ucIdx].sInputData.eCyclicMode;
		}

		//Step 3) Call the FUT
		CddSpi_Stop();

		//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
		AL_UNITTEST_CHECK(CddSpi_ucState, asTestCaseData[ucIdx].sOutputData.ucSpiState, == );
	}

}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_Cycle
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that no exception takes place
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_Cycle clears the internal variable for collecting error flags if the driver operates in CYCLIC Operation Mode
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ucSpiState   : Current Spi driver state
///         - Expected results
///           - ucStatusFault: Expect value of internal variable which collecst all error flags
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///         - CddSpi_ucStatusFault variable shall be set to an non zero value
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_Cycle(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8        ucSpiState;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint8 ucStatusFault;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput   sInputData;
		tsTestCaseDataOutput  sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		//             Inputs            ||  Outputs  
		// Operation mode                
		{{CDDSPI_STATE_RESET            } , {CDDSPI_UT_SF_EFT_SA_MASK  }},
		{{CDDSPI_STATE_CYCLIC_OPERATION } , {CDDSPI_UT_SF_EFT_SA_MASK  }},
		{{CDDSPI_STATE_SINGLE_OPERATION } , {CDDSPI_UT_SF_EFT_SA_MASK  }},
	};

	for (uint8 ucIdx = 0U; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();
#if (CDDSPI_STATUS_FAULT == STD_ON)
		CddSpi_ucStatusFaultVal |= CDDSPI_UT_SF_EFT_SA_MASK;
#endif
		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		CddSpi_ucState = asTestCaseData[ucIdx].sInputData.ucSpiState;

		//Step 3) Call the FUT
		rpCddSpi_Cycle();

		// Step 4) Check that no exception takes place
#if (CDDSPI_STATUS_FAULT == STD_ON)
		AL_UNITTEST_CHECK(CddSpi_ucStatusFaultVal & CDDSPI_UT_SF_EFT_SA_MASK, asTestCaseData[ucIdx].sOutputData.ucStatusFault & CDDSPI_UT_SF_EFT_SA_MASK, == );
#endif
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_ProcessSequence
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_ProcessSequence set the correct value of internal variables for handing the Tx and Rx data processing considering all the sequences, cyclic mode operation (interrupt/ polling)
///      prescaler value and cycle timeout configured in CddSpi_Cfg.h -> BEGIN_CDDSPI_SEQ(Ifc , cycle offset, cycle prescaler, max cycles to wait for a transfer to be completed),
///      as well as the transmission completion and initialization state of the sequence.
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set / changed by the FUT matchs the corresponding expected output value
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///            -ucSeqNum         : Sequence number
///            -eCyclicMode      : Cyclic mode of the sequence
///            -boTranferComplete: Transmission completion flag
///            -boInitialized    : Initialization flag of the sequence
///            -ucTimeOutMax     : Cycle Time Out
///            -ucTimeOut        : Cycle Time Out counter (fault injection)
///            -ucPrescaler      : Prescaler value (based on 1ms)
///            -ucCylcesCnt      : Internal cycles counter
///
///         - Expected results
///            -ucCycleCnt       : Expected value of Internal cycles counter
///            -ucTimeOutCnt     : Expected value of Cycle Time Out counter
///            -ucSeqContext     : Expected value of Internal variable for storing sequence context
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///         - Cycle Timeout error injection shall be simulated by estimulating internal transmision completion flag if sequence operates in IRQ Mode or by means of a 
///           structure which emulates the real HW register set of the SPI level driver, if driver operates in Polling Mode
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_ProcessSequence(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8                 ucSeqNum;
		teCddSpiIfcCyclicMode eCyclicMode;
		boolean               boTransferComplete;
		boolean               boInitialized;
		uint16                ucTimeOutMax;
		uint16                ucTimeOutCnt;
		uint16                ucPrescaler;
		uint16                unCyclesCnt;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint16  ucCycleCnt;
		uint16  ucTimeOutCnt;
		uint8   ucSeqContext;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		// Inputs                                                                                                          ||  Outputs
		// SeqNum |Cyclic mode                    | Transfer Compl| Initialized|Wait Max|WaitCnt| Prescaler | CycleCnt     ||  CycleCnt | WaitCnt |                 Sequence Context
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , FALSE      ,3        , 2        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , TRUE       ,3        , 2        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , FALSE      ,3        , 1        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , TRUE       ,3        , 1        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , FALSE      ,3        , 0        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , TRUE       ,3        , 0        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 1     , 0           }, { 1       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 1     , 0           }, { 1       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 2     , 0           }, { 2       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 2     , 0           }, { 2       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 3     , 3           }, { 2       , 3       , 0x00 | 0x00                              }},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 3     , 3           }, { 2       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 3     , 2           }, { 1       , 3       , 0x00 | 0x00                              }},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 3     , 2           }, { 1       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 3     , 1           }, { 0       , 3       , 0x00 | 0x00                              }},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 3     , 1           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , FALSE      ,3        , 2        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , TRUE       ,3        , 2        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , FALSE      ,3        , 1        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , TRUE       ,3        , 1        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , FALSE      ,3        , 0        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , TRUE       ,3        , 0        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 1     , 0           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 1     , 0           }, { 1       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 2     , 0           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 2     , 0           }, { 2       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 3     , 3           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 3     , 3           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 3     , 2           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 3     , 2           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 3     , 1           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 3     , 1           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , FALSE      ,3        , 2        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , TRUE       ,3        , 2        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , FALSE      ,3        , 1        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , TRUE       ,3        , 1        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , FALSE      ,3        , 0        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , TRUE       ,3        , 0        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 1     , 0           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 1     , 0           }, { 1       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 2     , 0           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 2     , 0           }, { 2       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 3     , 3           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 3     , 3           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 3     , 2           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 3     , 2           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 3     , 1           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 3     , 1           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 0      ,CddSpi_eIfcCyclicMode_DUMMY      , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , FALSE      ,3        , 2        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , TRUE       ,3        , 2        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , FALSE      ,3        , 1        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , TRUE       ,3        , 1        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , FALSE      ,3        , 0        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , FALSE       , TRUE       ,3        , 0        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 1     , 0           }, { 1       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 1     , 0           }, { 1       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 2     , 0           }, { 2       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 2     , 0           }, { 2       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 3     , 3           }, { 2       , 3       , 0x00 | 0x00                              }},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 3     , 3           }, { 2       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 3     , 2           }, { 1       , 3       , 0x00 | 0x00                              }},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 3     , 2           }, { 1       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 3     , 1           }, { 0       , 3       , 0x00 | 0x00                              }},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 3     , 1           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Polling    , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , FALSE      ,3        , 2        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , TRUE       ,3        , 2        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , FALSE      ,3        , 1        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , TRUE       ,3        , 1        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , FALSE      ,3        , 0        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , FALSE       , TRUE       ,3        , 0        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 1     , 0           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 1     , 0           }, { 1       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 2     , 0           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 2     , 0           }, { 2       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 3     , 3           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 3     , 3           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 3     , 2           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 3     , 2           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 3     , 1           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 3     , 1           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_Interrupt  , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , FALSE      ,3        , 2        , 0     , 0           }, { 0       , 2       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , TRUE       ,3        , 2        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , FALSE      ,3        , 1        , 0     , 0           }, { 0       , 1       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , TRUE       ,3        , 1        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , FALSE      ,3        , 0        , 0     , 0           }, { 0       , 0       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , FALSE       , TRUE       ,3        , 0        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 0     , 0           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 0     , 0           }, { 0       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 1     , 0           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 1     , 0           }, { 1       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 2     , 0           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 2     , 0           }, { 2       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 3     , 3           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 3     , 3           }, { 2       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 3     , 2           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 3     , 2           }, { 1       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 3     , 1           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | 0x00                              }},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 3     , 1           }, { 0       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , FALSE      ,3        , 3        , 3     , 0           }, { 3       , 3       , CDDSPI_SEQ_CONTEXT_COMPLETE_MSK | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DMA        , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
		{{ 1      ,CddSpi_eIfcCyclicMode_DUMMY      , TRUE        , TRUE       ,3        , 3        , 3     , 0           }, { 3       , 3       , 0x00 | CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK}},
	};

	for (uint8 ucIdx = 0U; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		tsCddSpiSeqHandler*           psSeqHandler = &CddSpi_asSeqHandler[asTestCaseData[ucIdx].sInputData.ucSeqNum];
		tsCddSpiSeqData*              psSeqData = &CddSpi_asSeqData[asTestCaseData[ucIdx].sInputData.ucSeqNum];
		tsCddSpiIfcCfg*               psIfcCfg = &CddSpi_asIfcCfg[CddSpi_asSeqHandler[asTestCaseData[ucIdx].sInputData.ucSeqNum].eSpiIfc];
		psSeqHandler->ucCycleCnt = asTestCaseData[ucIdx].sInputData.unCyclesCnt;
		psSeqHandler->ucPrescaler = asTestCaseData[ucIdx].sInputData.ucPrescaler;
		psSeqHandler->ucTimeOutMax = asTestCaseData[ucIdx].sInputData.ucTimeOutMax;
		psSeqHandler->ucTimeOutCnt = asTestCaseData[ucIdx].sInputData.ucTimeOutCnt;
		psIfcCfg->eIfcCyclicMode = asTestCaseData[ucIdx].sInputData.eCyclicMode;
		psSeqData->ucFramesCount = 4U; //HW limitation

		psSeqHandler->ucSeqContext |= (asTestCaseData[ucIdx].sInputData.boInitialized == TRUE) ? CDDSPI_SEQ_CONTEXT_INITIALIZED_MSK : 0U;

		if (CddSpi_asIfcCfg[CddSpi_asSeqHandler[asTestCaseData[ucIdx].sInputData.ucSeqNum].eSpiIfc].eIfcCyclicMode == CddSpi_eIfcCyclicMode_Polling)
		{
			psPeri->unFSR.sBit.u3RXCOUNT = (asTestCaseData[ucIdx].sInputData.boTransferComplete == TRUE) ? psSeqData->ucFramesCount : psSeqData->ucFramesCount - 1U;
		}
		else
		{
			psSeqHandler->ucSeqContext = (asTestCaseData[ucIdx].sInputData.boTransferComplete == TRUE) ? psSeqHandler->ucSeqContext | CDDSPI_SEQ_CONTEXT_COMPLETE_MSK :
				psSeqHandler->ucSeqContext & ~CDDSPI_SEQ_CONTEXT_COMPLETE_MSK;
			CddDma_IsJobCompleted_boReturn = asTestCaseData[ucIdx].sInputData.boTransferComplete;
		}


		//Step 3) Call the FUT
		CddSpi_ProcessSequence(asTestCaseData[ucIdx].sInputData.ucSeqNum);

		// Step 4) Check that the value of the output variables set / changed by the FUT matchs the corresponding expected output value
		AL_UNITTEST_CHECK(psSeqHandler->ucCycleCnt, asTestCaseData[ucIdx].sOutputData.ucCycleCnt, == );
		AL_UNITTEST_CHECK(psSeqHandler->ucTimeOutCnt, asTestCaseData[ucIdx].sOutputData.ucTimeOutCnt, == );
		AL_UNITTEST_CHECK(psSeqHandler->ucSeqContext, asTestCaseData[ucIdx].sOutputData.ucSeqContext, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_ProcessRxData
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// \Test Case Description
///    - Test subject:  Check that the function CddSpi_ProcessRxData gets the Rx data stored in the HW-Spi Buffer if sequence operates in Polling Mode, there 
///      is one single device attache to the sequence and Tx CRC Error has not been detected.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///             -ucSeqIdx           : Sequence Index
///             -eCyclicMode        : Sequence Cyclic Mode (Polling or Interrupt mode)
///             -ulRxFifoData       : Data stored in the HW-Spi Buffer
///             -ucDevicesInSeqCount: Number of devices attached to the sequence
///         - Expected results
///             -ulRxDeviceBuff     : Internal device buffer which collects Rx Data comming from Spi-Hw Buffer
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_ProcessRxData(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8                 ucSeqIdx;
		teCddSpiIfcCyclicMode eCyclicMode;
		uint32                ulRxFifoData;
		uint8                 ucDevicesInSeqCount;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint32                ulRxDeviceBuff;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput   sInputData;
		tsTestCaseDataOutput  sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		// Input                                                                    ||  Output
		//                                                                          ||
		{{ 0, CddSpi_eIfcCyclicMode_Polling    , CDDSPI_UT_UINT16_PATTERN, 0U }, {0x00U}                   },
		{{ 0, CddSpi_eIfcCyclicMode_Polling    , CDDSPI_UT_UINT16_PATTERN, 1U }, {CDDSPI_UT_UINT16_PATTERN}},
		{{ 0, CddSpi_eIfcCyclicMode_Polling    , CDDSPI_UT_UINT16_PATTERN, 2U }, {0x00U}                   },
		{{ 0, CddSpi_eIfcCyclicMode_Interrupt  , CDDSPI_UT_UINT32_PATTERN, 0U }, {0x00U}                   },
		{{ 0, CddSpi_eIfcCyclicMode_Interrupt  , CDDSPI_UT_UINT32_PATTERN, 1U }, {0x00U}                   },
		{{ 0, CddSpi_eIfcCyclicMode_Interrupt  , CDDSPI_UT_UINT32_PATTERN, 2U }, {0x00U}                   },
		{{ 0, CddSpi_eIfcCyclicMode_DMA        , CDDSPI_UT_UINT32_PATTERN, 0U }, {0x00U}                   },
		{{ 0, CddSpi_eIfcCyclicMode_DMA        , CDDSPI_UT_UINT32_PATTERN, 1U }, {CDDSPI_UT_UINT32_PATTERN}},
		{{ 0, CddSpi_eIfcCyclicMode_DMA        , CDDSPI_UT_UINT32_PATTERN, 2U }, {CDDSPI_UT_UINT32_PATTERN}},
		{{ 1, CddSpi_eIfcCyclicMode_Polling    , CDDSPI_UT_UINT32_PATTERN, 0U }, {0x00U}                   },
		{{ 1, CddSpi_eIfcCyclicMode_Polling    , CDDSPI_UT_UINT32_PATTERN, 1U }, {CDDSPI_UT_UINT32_PATTERN}},
		{{ 1, CddSpi_eIfcCyclicMode_Interrupt  , CDDSPI_UT_UINT32_PATTERN, 0U }, {0x00U}                   },
		{{ 1, CddSpi_eIfcCyclicMode_Interrupt  , CDDSPI_UT_UINT32_PATTERN, 1U }, {0x00U}                   },
		{{ 1, CddSpi_eIfcCyclicMode_DMA        , CDDSPI_UT_UINT32_PATTERN, 0U }, {0x00U}                   },
		{{ 1, CddSpi_eIfcCyclicMode_DMA        , CDDSPI_UT_UINT32_PATTERN, 1U }, {CDDSPI_UT_UINT32_PATTERN}},
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		CddSpi_asSeqData[asTestCaseData[ucIdx].sInputData.ucSeqIdx].ucDeviceCount = asTestCaseData[ucIdx].sInputData.ucDevicesInSeqCount;
		psPeri->unRDR.ulData = asTestCaseData[ucIdx].sInputData.ulRxFifoData;
		CddSpi_asIfcCfg[CddSpi_asSeqHandler[asTestCaseData[ucIdx].sInputData.ucSeqIdx].eSpiIfc].eIfcCyclicMode = asTestCaseData[ucIdx].sInputData.eCyclicMode;
		for (uint8 ucDevIdx = 0; ucDevIdx < CddSpi_asSeqData[asTestCaseData[ucIdx].sInputData.ucSeqIdx].ucDeviceCount; ucDevIdx++)
		{
			uint16* punDevRxBuff = CddSpi_asSeqData[asTestCaseData[ucIdx].sInputData.ucSeqIdx].psDevData[ucDevIdx].punRxBuff;
			uint8   ucElements = CddSpi_asDeviceCfg[CddSpi_asSeqData[asTestCaseData[ucIdx].sInputData.ucSeqIdx].psDevData[ucDevIdx].eDev].ucElements;
			for (uint8 ucBuffIdx = 0; ucBuffIdx < ucElements; ucBuffIdx++)
			{
				punDevRxBuff[ucBuffIdx] = 0x0000;
			}
		}
		for (uint8 ucBuffIdx = 0; ucBuffIdx < 10; ucBuffIdx++)
		{
			aunCddSpiReceiveData[CddSpi_asIfcCfg[CddSpi_asSeqHandler[asTestCaseData[ucIdx].sInputData.ucSeqIdx].eSpiIfc].ucIfcMap][ucBuffIdx] = asTestCaseData[ucIdx].sInputData.ulRxFifoData;
		}

		//Step 3) Call the FUT
		CddSpi_ProcessRxData(asTestCaseData[ucIdx].sInputData.ucSeqIdx);

		//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
		for (uint8 ucDevIdx = 0; ucDevIdx < CddSpi_asSeqData[asTestCaseData[ucIdx].sInputData.ucSeqIdx].ucDeviceCount; ucDevIdx++)
		{
			uint16* punDevRxBuff = CddSpi_asSeqData[asTestCaseData[ucIdx].sInputData.ucSeqIdx].psDevData[ucDevIdx].punRxBuff;
			uint8   ucElements = CddSpi_asDeviceCfg[CddSpi_asSeqData[asTestCaseData[ucIdx].sInputData.ucSeqIdx].psDevData[ucDevIdx].eDev].ucElements;
			for (uint8 ucBuffIdx = 0; ucBuffIdx < ucElements; ucBuffIdx++)
			{
				AL_UNITTEST_CHECK(punDevRxBuff[ucBuffIdx], (uint16)asTestCaseData[ucIdx].sOutputData.ulRxDeviceBuff, == );
			}
		}
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_ProcessTxData
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that no exception is executed if CddSpi_ProcessTxData is called, considering all possible execution branches
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///            - ucSeqIdx    : Sequence index
///            - eCyclicMode : Cyclic Mode of the sequence (Polling or Interrupt mode)
///
///         - Expected results
///            NA: If exception executed UT Result would not be available
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_ProcessTxData(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8                 ucSeqIdx;
		teCddSpiIfcCyclicMode eCyclicMode;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput   sInputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		// Input                              ||  Output
		//                                    ||
		{{ 0,  CddSpi_eIfcCyclicMode_Polling  }},
		{{ 0,  CddSpi_eIfcCyclicMode_Interrupt}},
		{{ 0,  CddSpi_eIfcCyclicMode_DMA      }},
		{{ 0,  CddSpi_eIfcCyclicMode_DUMMY    }},
		{{ 1,  CddSpi_eIfcCyclicMode_Polling  }},
		{{ 1,  CddSpi_eIfcCyclicMode_Interrupt}},
		{{ 1,  CddSpi_eIfcCyclicMode_DMA      }},
		{{ 1,  CddSpi_eIfcCyclicMode_DUMMY    }},
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		CddSpi_asIfcCfg[CddSpi_asSeqHandler[asTestCaseData[ucIdx].sInputData.ucSeqIdx].eSpiIfc].eIfcCyclicMode = asTestCaseData[ucIdx].sInputData.eCyclicMode;

		//Step 3) Call the FUT
		CddSpi_ProcessTxData(asTestCaseData[ucIdx].sInputData.ucSeqIdx);

		//Step 4) Check  that no excpetion is executed
		//NA
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_UpdateDevRxData
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_UpdateDevRxData provides the collected Rx Data (comming from Spi-HW buffer) to the device passed as parameter
///      Check that Rx Data is ignored if Device Callback is NULL_PTR
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///            - ulData : Data to be sent to device
///            - boDevTxIsActive: Device Callback is active (non NULL_PTR)
///         - Expected results
///            - aunCBData      : Data provided to the device by means of Rx- Callback
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///         - psDevSeqData must be set to plausible value
///         - psSeqData  must be set to a plausible value
///         - ucElemIDx must be set to a plausible value
///         - psDevSeqData->psCbData[ucElemIdx].sDevCb.fpRx  must be set to plausible value
///         - psDevSeqData->punRxBuff[ucElemIdx]  must be set to a known value
///
///      For further information about preconditions rerfer to step 1 of this Unit Test Case
///
///---------------------------------------------------------------------------------
void Mt_CddSpi_UpdateDevRxData(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint32  ulData;
		boolean boDevTxIsActive;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint32  aunCBData;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput   sInputData;
		tsTestCaseDataOutput  sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		// Input                                     ||           utput
		// Data                     | DeviceActive   ||    Return Data
		{{CDDSPI_UT_UINT16_PATTERN,   FALSE}          ,{ 0x00000000               }},
		{{CDDSPI_UT_UINT16_PATTERN,   TRUE }          ,{ CDDSPI_UT_UINT16_PATTERN }},
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();
		tsCddSpiDevSeqData* psDevSeqData = &CddSpi_asSeqDataIfc_1[0];
		tsCddSpiSeqData*    psSeqData = &CddSpi_asSeqData[1];
		uint8               ucElemIdx = 0;
		teCddSpiDev         eDev = CDDSPI_DEVICE(BUCK_0_5);
		psDevSeqData->psCbData[ucElemIdx].sDevCb.fpRx = CddTps92520_SpiRx;
		CddTps92520_SpiRx_ulData[CddSpi_asDeviceCfg[eDev].ucMaxElements - ucElemIdx - 1U] = 0x00000000;
		psDevSeqData->punRxBuff[ucElemIdx] = (uint16)asTestCaseData[ucIdx].sInputData.ulData;

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		if (asTestCaseData[ucIdx].sInputData.boDevTxIsActive != TRUE)
			psDevSeqData->psCbData[CddSpi_asDeviceCfg[eDev].ucMaxElements - ucElemIdx - 1U].sDevCb.fpRx = NULL_PTR;

		//Step 3) Call the FUT
		CddSpi_UpdateDevRxData(psDevSeqData);

		//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
		AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sOutputData.aunCBData, CddTps92520_SpiRx_ulData[CddSpi_asDeviceCfg[eDev].ucMaxElements - ucElemIdx - 1U], == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_UpdateDevTxData
///
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
///
/// \Test Case Description
///    - Test subject: Check that function CddSpi_UpdateDevTxData gets Tx data of the device passed as parameter for handling a HW transmission
///      Check that Tx Data is ignored if Device Callback is NULL_PTR
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///             -fpTxDev     : Array of Device Tx Callbacks
///
///         - Expected results
///             - unData       : Tx data stored in the internal device buffer to forward to Spi-HW Buffer
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///         - psDevSeqData must be set to plausible value
///         - psSeqData  must be set to a plausible value
///         - psDevSeqData->psCbData[ucElemIdx].sDevCb.fpTx  must be set to plausible value
///         - psDevSeqData->punRxBuff[ucElemIdx]  must be set to an known value
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_UpdateDevTxData(void)
{
	typedef struct tsTestCaseDataInput
	{
		tfpCddSpiTxCb  fpTxDev[6];
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint32   unData[6];
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput   sInputData;
		tsTestCaseDataOutput  sOutputData;
	}tsTestCaseData;

	teCddSpiDev         eDev = CDDSPI_DEVICE(BUCK_0_5);
	tsCddSpiDevSeqData* psDevSeqData = &CddSpi_asSeqDataIfc_1[0];
	tsCddSpiSeqData*    psSeqData = &CddSpi_asSeqData[1];
	const tfpCddSpiTxCb       fpTxDevCb = CddTps92520_SpiTx;

	static tsTestCaseData asTestCaseData[] =
	{
		// Input                                                                 ||                   Output
		//                   Device Callbacks                                    ||       Tx data stored in the internal device buffer to forward to Spi-HW Buffer
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR,  NULL_PTR }}  , { {0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR,  fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR }}  , { { 0x00                   , 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb,fpTxDevCb }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ { NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR , NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    , 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR , fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb, NULL_PTR }}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, 0x00                    }}},
		{{ {fpTxDevCb , fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb, fpTxDevCb}}  , { {CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN, CDDSPI_UT_UINT16_PATTERN}}},
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1.1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();

		for (uint8 ucElemIdx = 0U; ucElemIdx < CddSpi_asDeviceCfg[eDev].ucMaxElements; ucElemIdx++)
		{
			//Step 1.2) Set pre - conditions if needed
			uint8 CbIdx = CddSpi_asDeviceCfg[eDev].ucMaxElements - ucElemIdx - 1;
			CddTps92520_SpiTx_ulReturn[CbIdx] = (uint16)CDDSPI_UT_UINT16_PATTERN;
			psDevSeqData->punTxBuff[ucElemIdx] = 0x00U;

			//Step 2) Assign all input values to the corresponding input variables identified in the FUT
			psDevSeqData->psCbData[CbIdx].sDevCb.fpTx = asTestCaseData[ucIdx].sInputData.fpTxDev[ucElemIdx];
			CddTps92520_SpiTx_ulReturn[CbIdx] |= 0x14 << 16U;
		}

		//Step 3) Call the FUT
		CddSpi_UpdateDevTxData(psDevSeqData);

		//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value ;
		for (uint8 ucElemIdx = 0U; ucElemIdx < CddSpi_asDeviceCfg[eDev].ucMaxElements; ucElemIdx++)
		{
			AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sOutputData.unData[ucElemIdx], psDevSeqData->punTxBuff[ucElemIdx], == );
		}
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_CalculateIfcSeqMap
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_CalculateIfcSeqMap calculate the right value of the interface sequence passed as parameter
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///             -ucSeqIdx : Sequence Index
///
///         - Expected results
///             -ucIfcIdx : Interface Index the sequence operates on
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_CalculateIfcSeqMap(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8   ucSeqIdx;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint8   ucIfcIdx;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput   sInputData;
		tsTestCaseDataOutput  sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		//Input            || Output
		//SeqIdx           || IfcIdx
		{{0}               ,{ 0}},
		{{1}               ,{ 1}},
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		uint8 ucSeqIdx = asTestCaseData[ucIdx].sInputData.ucSeqIdx;

		//Step 3) Call the FUT
		CddSpi_CalculateIfcSeqMap(ucSeqIdx);

	}
	//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		AL_UNITTEST_CHECK(CddSpi_asIfcCfg[asTestCaseData[ucIdx].sOutputData.ucIfcIdx].ucSeqMap, asTestCaseData[ucIdx].sInputData.ucSeqIdx, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_ISRHandle
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_ISRHandler save the received Rx Data from Spi-Hw Buffer in the device internal buffer and set the correct values
///      of all internal flags for the Interrupt Service Routine Handling, and it triggers the transmission of the next device of the sequence in which a Tx Crc Error
///      has not been detected or it sets the completion flag and disables the Rx-Interrupts  if the current device is the last in sequence 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///             -ucIfcIdx           : Interface Index passed as parameter
///             -ucDeviceIdxPre     : Device Index previous to the function execution
///             -ucDeviceCount      : Number of devices attached to the sequence
///             -boIntEvenTriggered : Flag which indicates an Interrupt Trigger event has been set
///             -boTxCrcError       : TxCrcError has been detected
///         - Expected results
///             -boRxTriggerEventClearHwRegValuePost : Value of Trigger Event Flag post execution
///             -ulDeviceBuff                        : Data of internal device buffer
///             -ucDeviceIdxPost                     : Device Index post  to the function execution
///             -boXferCompletFlag                   : Transmission complet flag post to the function execution
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
//void Mt_CddSpi_ISRHandle()
//{
//  typedef struct tsTestCaseDataInput
//  {
//    uint8      ucIfcIdx;
//    uint8      ucDeviceIdxPre;
//    uint8      ucDeviceCount;
//    boolean    boIntEvenTriggered;
//    boolean    boTxCrcError;
//  }tsTestCaseDataInput;
//
//  typedef struct tsTestCaseDataOutput
//  {
//    boolean  boRxTriggerEventClearHwRegValuePost;
//    uint32   ulDeviceBuff;
//    uint8    ucDeviceIdxPost;
//    boolean  boXferCompletFlag;
//  }tsTestCaseDataOutput;
//
//  typedef struct tsTestCaseData
//  {
//    tsTestCaseDataInput  sInputData;
//    tsTestCaseDataOutput sOutputData;
//  }tsTestCaseData;
//
//  tsTestCaseData asTestCaseData[] =
//  {
//    //           Inputs                                                                      || Outputs
//    //  Interface Index |Device Index | Device Count  | Event Triggered       | TxCrc Error  || Hw Event Triggered Flag | Device Buffer           | Device Index after execution | Transfer complete Flag
//    { { 0               ,  0           , 1             , FALSE                , FALSE        },  { 0                    , 0x00U                   ,       0                      , FALSE}},
//    { { 0               ,  0           , 1             , FALSE                , TRUE         },  { 0                    , 0x00U                   ,       0                      , FALSE}},
//    { { 0               ,  0           , 1             , TRUE                 , FALSE        },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       1                      , TRUE}},
//    { { 0               ,  0           , 1             , TRUE                 , TRUE         },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       1                      , TRUE}},
//    { { 0               ,  1           , 1             , FALSE                , FALSE        },  { 0                    , 0x00U                   ,       1                      , FALSE}},
//    { { 0               ,  1           , 1             , FALSE                , TRUE         },  { 0                    , 0x00U                   ,       1                      , FALSE}},
//    { { 0               ,  1           , 1             , TRUE                 , FALSE        },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       2                      , TRUE}},
//    { { 0               ,  1           , 2             , TRUE                 , FALSE        },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       2                      , TRUE}},
//    { { 0               ,  0           , 2             , TRUE                 , TRUE         },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       2                      , TRUE}},
//    { { 0               ,  0           , 2             , TRUE                 , FALSE        },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       1                      , FALSE}},
//    { { 1               ,  0           , 1             , TRUE                 , FALSE        },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       1                      , TRUE}},
//    { { 1               ,  1           , 1             , FALSE                , FALSE        },  { 0                    , 0x00U                   ,       1                      , FALSE}},
//    { { 1               ,  1           , 1             , TRUE                 , FALSE        },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       2                      , TRUE}},
//  };
//
//
//  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
//  {
//    //Step 1: Set pre-conditions
//    Mt_CddSpi_RestoreInitContext();
//    volatile tsCddSpi_CYT2_B9_SCB* const psSCB = &dummySCBCtrl;
//
//    //Step 2) Assign Input values
//    uint8 ucIfcIdx = asTestCaseData[ucIdx].sInputData.ucIfcIdx;
//    tsCddSpiSeqHandler* const psSeqHandler = &CddSpi_asSeqHandler[CddSpi_asIfcCfg[ucIfcIdx].ucSeqMap];
//    tsCddSpiSeqData*          psSeqData = &CddSpi_asSeqData[CddSpi_asIfcCfg[ucIfcIdx].ucSeqMap];
//    tsCddSpiDevSeqData*       psDevData = &psSeqData->psDevData[psSeqHandler->ucIntDevIdx];
//
//    for (uint8 ucDevBuffIdx = 0U; ucDevBuffIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucElements; ucDevBuffIdx++)
//    {
//      psDevData->punRxBuff[ucDevBuffIdx] = 0;
//    }
//
//    //Initializle register to known value
//    psSCB->unINTR_RX.sBit.u1TRIGGER = (asTestCaseData[ucIdx].sInputData.boIntEvenTriggered == TRUE) ? 1 : 0;
//    psSCB->unRX_FIFO_RD.ulData = CDDSPI_UT_UINT16_PATTERN;
//    psSeqData->ucDeviceCount = asTestCaseData[ucIdx].sInputData.ucDeviceCount;
//
//    (psDevData + 1)->boTxCrcError = asTestCaseData[ucIdx].sInputData.boTxCrcError;
//    psSeqHandler->ucIntDevIdx = asTestCaseData[ucIdx].sInputData.ucDeviceIdxPre;
//
//    //Step 3) Call UUT for all sequences
//    CddSpi_ISRHandle(ucIfcIdx);
//
//    //Step 4) Check expected output values
//    AL_UNITTEST_CHECK(psSCB->unINTR_RX.sBit.u1TRIGGER, asTestCaseData[ucIdx].sOutputData.boRxTriggerEventClearHwRegValuePost, == );
//    AL_UNITTEST_CHECK(psSeqHandler->ucIntDevIdx, asTestCaseData[ucIdx].sOutputData.ucDeviceIdxPost, == );
//    AL_UNITTEST_CHECK(((psSeqHandler->ucSeqContext & CDDSPI_SEQ_CONTEXT_COMPLETE_MSK) >> CDDSPI_SEQ_CONTEXT_COMPLETE_POS), asTestCaseData[ucIdx].sOutputData.boXferCompletFlag, == );
//  }
//
//}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_InitIfc_Deriv
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_InitIfc_Deriv sets all needed SPI-HW registers as expected to enable a Master-Motorola SPI operation.
///
/// \Steps:
///         Step1: Set pre-conditions
///         Step2: Assign input values
///         Step3: Call the function
///         Step4: Check  the value of the output variables set/changed by the FUT matchs the corresponding expected output value
///                of the DT entry, as well as the output values which do not depend on any DT entry.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///           - unIfc: SPI driver Interface used and passed as parameter to the FUT.
///         - Expected results
///           -psPeri->unCFGR1.sBit.u1PCSCFG = 0u
///           -psPeri->unCFGR1.sBit.u1OUTCFG = 0u
///           -psPeri->unCFGR1.sBit.u1PCSCFG = 0u
///           -psPeri->unCFGR1.sBit.u4PCSPOL = 0u
///           -psPeri->unCCR.sBit.u8SCKPCS   = 0u
///           -psPeri->unCCR.sBit.u8PCSSCK   = 0u
///           -psPeri->unCCR.sBit.u8DBT      = 0u
///           -psPeri->unCCR.sBit.u8SCKDIV   = 0u
///           -psPeri->unCFGR1.sBit.u1SAMPLE = 1u
///           -psPeri->unCR.sBit.u1MEN       = 1u
///           -psPeri->unFCR.sBit.u2TXWATER  = 2u
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_InitIfc_Deriv(void)
{

	typedef struct tsTestCaseDataInput
	{
		uint16   unIfc;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		// Inputs          ||  Outputs
		// SPI Interface   || 
		 {{  CDDSPI_IFC0  } },
		 {{  CDDSPI_IFC1  } },
	};

	volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre-conditions
		Mt_CddSpi_RestoreInitContext();

		//Step 2) Assign input values
		uint8 ucIfc = asTestCaseData[ucIdx].sInputData.unIfc;

		//Step 3) Call FUT
		CddSpi_InitIfc_Deriv(ucIfc);

		//Step 4) Check  the value of the output variables set/changed by the FUT matchs the corresponding expected output value
		//of the DT entry, as well as the output values which do not depend on any DT entry.
		AL_UNITTEST_CHECK(psPeri->unCFGR1.sBit.u1PCSCFG, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unCFGR1.sBit.u1OUTCFG, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unCFGR1.sBit.u1PCSCFG, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unCFGR1.sBit.u4PCSPOL, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unCCR.sBit.u8SCKPCS, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unCCR.sBit.u8PCSSCK, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unCCR.sBit.u8DBT, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unCCR.sBit.u8SCKDIV, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unCFGR1.sBit.u1SAMPLE, 1U, == );
		AL_UNITTEST_CHECK(psPeri->unCR.sBit.u1MEN, 1U, == );
		AL_UNITTEST_CHECK(psPeri->unFCR.sBit.u2TXWATER, 2U, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_DeInitIfc_Deriv
///
/// \Functional Safety: ASIL B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_InitIfc_Deriv sets all needed SPI-HW registers as expected, which in turn depend on the SPI Interface 
///        passed as parameter, to enable a Master-Motorola SPI operation.
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///             - unIfc: SPI driver Interface used and passed as parameter to the FUT.
///         - Expected results
///             - boLPSPIEnable : HW-Spi Register value to enable / disable Spi Hardware Block
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_DeInitIfc_Deriv(void)
{

	typedef struct tsTestCaseDataInput
	{
		uint16   unIfc;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		boolean boLPSPIEnable;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		// Inputs          ||               Outputs
		// SPI Interface   ||     LPSPI Enabled
		 {{  CDDSPI_IFC0  } , {     FALSE          } },
		 {{  CDDSPI_IFC1  } , {     FALSE          } },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign input values
		uint8 ucIfc = asTestCaseData[ucIdx].sInputData.unIfc;

		//Step 3) Call FUT
		CddSpi_DeInitIfc_Deriv(ucIfc);

		//Step 4) Check  the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
		AL_UNITTEST_CHECK(psPeri->unCR.sBit.u1MEN, asTestCaseData[ucIdx].sOutputData.boLPSPIEnable, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_ConfigureTransfer
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_ConfigureTransfer_Deriv sets all needed SPI-HW registers as expected to configure an SPI transmission
///        depending on the passed parameter, tsCddSpiDevCfg psDevCfg.
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///           - Device Configuration:
///              - ucSpiIfc          : Spi interface that the device is attached to
///              - ucCs              : Chip Select number
///              - ucDataLen         : Data Length
///              - ucMsgs            : Number of frames
///              - ucBrs             : Bit Rate
///              - ucCPol            : Clock Polarity
///              - ucCPha            : Clock Phase
///              - ucDataDir         : Data direction: MSB or LSB
///         - Expected results
///              - ucPCS             : Value of the HW-SPI register  which selects the SS used
///              - ucFRAMESZ         : Value of the HW-SPI register  which sets the size transmission
///              - ucCONT            : Value of the HW-SPI register  which enables/disables continuous SS transfer 
///              - ucPRESCALE        : Value of the HW-SPI register  which sets the Clocl Prescale value
///              - ucCPOL            : Value of the HW-SPI register  which sets the Clock Polarity
///              - ucCPHA            : Value of the HW-SPI register  which sets the Clock Phase
///              - ucLSBF            : Value of the HW-SPI register  which enables/disables the MSB direction for transmission
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_ConfigureTransfer_Deriv(void)
{
	typedef struct tsTestCaseDataInput
	{
		const tsCddSpiDevCfg psDevCfg;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint8 ucPCS;
		uint8 ucFRAMESZ;
		uint8 ucCONT;
		uint8 ucPRESCALE;
		uint8 ucCPOL;
		uint8 ucCPHA;
		uint8 ucLSBF;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//                                            Inputs                                                                    ||                                          Outputs
		//    SPI Ifc   | CS | Length |Max Elems | Elems |  BRS           | Clock Polarity | Clock Phase | Bit Direction        ||  SSEL | FRAMESZ  | CONT | PRESCALE | CPOL | CPHA | LSBF
		{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST} }   , { 0U   , 15U      , 0U  , 4U        , 0U  , 0U    , 1U }},
		{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST} }   , { 0U   , 15U      , 0U  , 4U        , 0U  , 0U    , 0U }},
		{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_1, CDDSPI_LSB_FIRST} }   , { 0U   , 15U      , 0U  , 4U        , 0U  , 1U    , 1U }},
		{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_1, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST} }   , { 0U   , 15U      , 0U  , 4U        , 1U  , 0U    , 1U }},
		{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_1M  , CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST} }   , { 0U   , 15U      , 0U  , 3U        , 0U  , 0U    , 1U }},
		{ { {CDDSPI_IFC0, 0  , 32U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST} }   , { 0U   , 31U      , 0U  , 4U        , 0U  , 0U    , 0U }},
		{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 2U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST} }   , { 0U   , 15U      , 1U  , 4U        , 0U  , 0U    , 0U }},
		{ { {CDDSPI_IFC0, 1  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST} }   , { 1U   , 15U      , 0U  , 4U        , 0U  , 0U    , 0U }},
		{ { {CDDSPI_IFC0, 2  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST} }   , { 2U   , 15U      , 0U  , 4U        , 0U  , 0U    , 0U }},
		{ { {CDDSPI_IFC0, 3  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST} }   , { 3U   , 15U      , 0U  , 4U        , 0U  , 0U    , 0U }},
		{ { {CDDSPI_IFC1, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST} }   , { 0U   , 15U      , 0U  , 4U        , 0U  , 0U    , 1U }},
	};

	//Step 1: Set pre-conditions
	volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		Mt_CddSpi_RestoreInitContext();
		//Step 2) Assign Input values
		const tsCddSpiDevCfg psDevCfg = asTestCaseData[ucIdx].sInputData.psDevCfg;

		//Step 3) Call UUT
		CddSpi_ConfigureTransfer_Deriv(&psDevCfg);

		//Step 4) Check expected output values
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u12FRAMESZ, asTestCaseData[ucIdx].sOutputData.ucFRAMESZ, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u2WIDTH, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u1TXMSK, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u1RXMSK, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u1CONTC, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u1CONT, asTestCaseData[ucIdx].sOutputData.ucCONT, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u1BYSW, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u1LSBF, asTestCaseData[ucIdx].sOutputData.ucLSBF, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u2PCS, asTestCaseData[ucIdx].sOutputData.ucPCS, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u3PRESCALE, asTestCaseData[ucIdx].sOutputData.ucPRESCALE, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u1CPHA, asTestCaseData[ucIdx].sOutputData.ucCPHA, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.sBit.u1CPOL, asTestCaseData[ucIdx].sOutputData.ucCPOL, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_GetCommandWord_Deriv
///
/// \Functional Safety: QM
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_GetCommandWord_Deriv returns the correct word to set all needed SPI-HW registers as expected to configure an SPI transmission
///        depending on the passed parameter, tsCddSpiDevCfg psDevCfg.
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///           - Device Configuration:
///              - ucSpiIfc          : Spi interface that the device is attached to
///              - ucCs              : Chip Select number
///              - ucDataLen         : Data Length
///              - ucMsgs            : Number of frames
///              - ucBrs             : Bit Rate
///              - ucCPol            : Clock Polarity
///              - ucCPha            : Clock Phase
///              - ucDataDir         : Data direction: MSB or LSB
///         - Expected results
///              - ulData            : Value of the HW-SPI register 
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//-----------------------------------------------------------------------------
void Mt_CddSpi_GetCommandWord_Deriv(void)
{
	typedef struct tsTestCaseDataInput
	{
		const tsCddSpiDevCfg psDevCfg;
		uint8 ucIdx;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint32 ulData;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//                                            Inputs                                                                      ||      Outputs
		//    SPI Ifc   | CS | Length |Max Elems | Elems |  BRS           | Clock Polarity | Clock Phase | Bit Direction   | Idx  ||  Data  
		//{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/00/*LSBF*/0/*BYSW*/0/*CONT*/0/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 )}},
		  { { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0X2000000F}},
		  //{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_1, CDDSPI_LSB_FIRST},  0U}   ,   { 0b/*CPOL*/0/*CPHA*/1/*PRESCALE*/100/*Reserved*/0/*PCS*/00/*LSBF*/1/*BYSW*/0/*CONT*/0/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
			{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_1, CDDSPI_LSB_FIRST},  0U}   ,   { 0X6080000F}},
			//{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST},  0U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/00/*LSBF*/1/*BYSW*/0/*CONT*/0/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
			  { { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST},  0U}   ,   { 0X2080000F}},
			  //{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_1, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST},  0U}   ,   { 0b/*CPOL*/1/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/00/*LSBF*/1/*BYSW*/0/*CONT*/0/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
				{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_1, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST},  0U}   ,   { 0XA080000F}},
				//{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_1M  , CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST},  0U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/011/*Reserved*/0/*PCS*/00/*LSBF*/1/*BYSW*/0/*CONT*/0/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
				  { { {CDDSPI_IFC0, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_1M  , CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST},  0U}   ,   { 0X1880000F}},
				  //{ { {CDDSPI_IFC0, 0  , 32U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/00/*LSBF*/0/*BYSW*/0/*CONT*/0/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000011111 }},
					{ { {CDDSPI_IFC0, 0  , 32U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0X2000001F}},
					//{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 3U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/00/*LSBF*/0/*BYSW*/0/*CONT*/1/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
					  { { {CDDSPI_IFC0, 0  , 16U     , 1U        , 3U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0X2020000F}},
					  //{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 3U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  1U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/00/*LSBF*/0/*BYSW*/0/*CONT*/1/*CONTC*/1/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
						{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 3U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  1U}   ,   { 0X2030000F}},
						//{ { {CDDSPI_IFC0, 0  , 16U     , 1U        , 3U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  2U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/00/*LSBF*/0/*BYSW*/0/*CONT*/0/*CONTC*/1/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
						  { { {CDDSPI_IFC0, 0  , 16U     , 1U        , 3U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  2U}   ,   { 0X2010000F}},
						  //{ { {CDDSPI_IFC0, 1  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/01/*LSBF*/0/*BYSW*/0/*CONT*/0/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
							{ { {CDDSPI_IFC0, 1  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0X2100000F}},
							//{ { {CDDSPI_IFC0, 2  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/10/*LSBF*/0/*BYSW*/0/*CONT*/0/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
							  { { {CDDSPI_IFC0, 2  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0X2200000F}},
							  //{ { {CDDSPI_IFC0, 3  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/11/*LSBF*/0/*BYSW*/0/*CONT*/0/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
								{ { {CDDSPI_IFC0, 3  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_MSB_FIRST},  0U}   ,   { 0X2300000F}},
								//{ { {CDDSPI_IFC1, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST},  0U}   ,   { 0b/*CPOL*/0/*CPHA*/0/*PRESCALE*/100/*Reserved*/0/*PCS*/00/*LSBF*/1/*BYSW*/0/*CONT*/0/*CONTC*/0/*RXMSK*/0/*TXMSK*/0/*WIDTH*/00/*Reserved*/0000/*FRAMESZ*/000000001111 }},
								  { { {CDDSPI_IFC1, 0  , 16U     , 1U        , 1U  , CDDSPI_BRS_500K, CDDSPI_CPOL_0, CDDSPI_CPHA_0, CDDSPI_LSB_FIRST},  0U}   ,   { 0X2080000F}},
	};

	//Step 1: Set pre-conditions

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		Mt_CddSpi_RestoreInitContext();
		//Step 2) Assign Input values
		const tsCddSpiDevCfg psDevCfg = asTestCaseData[ucIdx].sInputData.psDevCfg;

		//Step 3) Call UUT
		uint32 ulReturnValue = CddSpi_GetCommandWord_Deriv(&psDevCfg, asTestCaseData[ucIdx].sInputData.ucIdx);

		//Step 4) Check expected output values
		AL_UNITTEST_CHECK(ulReturnValue, asTestCaseData[ucIdx].sOutputData.ulData, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_IfcIdle_Deriv
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_IdleIfc_Deriv returns the correct  state of the SPI Ifc (Idle or not Idle)
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///           - unIfc: SPI driver Interface used and passed as parameter to the FUT.
///           - ulSpiBusyFlag: Value of the SPI Busy flag
///         - Expected results
///           -boReturn: Return value of FUT
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_IfcIdle_Deriv(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8    ucSpiIfc;
		uint32   ulSpiBusyFlag;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		boolean boReturn;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//           Inputs              || Outputs
		// Spi Ifc      | Spi Busy Flag  || Return value
		{ {CDDSPI_IFC0  ,     0U          }  ,  { TRUE   } },
		{ {CDDSPI_IFC1  ,     0U          }  ,  { TRUE   } },
		{ {CDDSPI_IFC0  ,     1U          }  ,  { FALSE  } },
		{ {CDDSPI_IFC1  ,     1U          }  ,  { FALSE  } },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign Input values
		psPeri->unSR.sBit.u1MBF = asTestCaseData[ucIdx].sInputData.ulSpiBusyFlag;

		//Step 3) Call UUT
		boolean boRetVal = CddSpi_IfcIdle_Deriv(asTestCaseData[ucIdx].sInputData.ucSpiIfc);

		//Step 4) Check expected output values
		AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.boReturn, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_StartTransfer_Deriv
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_StartTransfer_Deriv sets all the register to start a transfer with DMA
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///           - unIfc: SPI driver Interface used and passed as parameter to the FUT.
///           - ulSpiBusyFlag: Value of the SPI Busy flag
///         - Expected results
///           -psPeri->unSR.ulData       = 0u
///           -psPeri->unTCR.ulData      = 0u
///           -psPeri->unDER.sBit.u1RDDE = 1u
///           -psPeri->unDER.sBit.u1TDDE = 1u
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_StartTransfer_Deriv(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8    ucSpiIfc;
		uint32*  pulTransferData;
		uint32*  pulReceiveData;
		uint16   unLen;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//           Inputs                                        || Outputs
		// Spi Ifc      |  TransferData   |  ReceiveData | unLen   || Return value
		{ {CDDSPI_IFC0  ,     NULL_PTR    ,    NULL_PTR   ,   0U  } },
		{ {CDDSPI_IFC1  ,     NULL_PTR    ,    NULL_PTR   ,   0U  } },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign Input values

		//Step 3) Call UUT
		CddSpi_StartTransfer_Deriv(asTestCaseData[ucIdx].sInputData.ucSpiIfc, asTestCaseData[ucIdx].sInputData.pulTransferData, asTestCaseData[ucIdx].sInputData.pulReceiveData, asTestCaseData[ucIdx].sInputData.unLen);

		//Step 4) Check expected output values
		AL_UNITTEST_CHECK(psPeri->unSR.ulData, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.ulData, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unDER.sBit.u1RDDE, 1U, == );
		AL_UNITTEST_CHECK(psPeri->unDER.sBit.u1TDDE, 1U, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_TransferComplete_Deriv
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_TransferComplete_Deriv returns the right value by checking the transfer completion considering
///        the size passed as parameter
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///             -ucSpiIfc            : Spi Interface
///             -unSize              : Size provided as parameter to check transfer completion
///             -unRxFifoHwDataCnt   : Size of received data in HW Buffer
///         - Expected results
///             - boReturn: return value of  FUT
///
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_TransferComplete_Deriv(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8    ucSpiIfc;
		uint16   unSize;
		uint16   unRxFifoHwDataCnt;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		boolean boReturn;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//           Inputs             || Outputs
		// Spi Ifc      | Size | HwData || Return value
		{ {CDDSPI_IFC0  ,  1U  , 1U   }  ,  { TRUE   } },
		{ {CDDSPI_IFC0  ,  1U  , 0U   }  ,  { FALSE  } },
		{ {CDDSPI_IFC1  ,  1U  , 1U   }  ,  { TRUE   } },
		{ {CDDSPI_IFC1  ,  1U  , 0U   }  ,  { FALSE  } },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign Input values
		psPeri->unFSR.sBit.u3RXCOUNT = asTestCaseData[ucIdx].sInputData.unRxFifoHwDataCnt;
		uint16 unSize = asTestCaseData[ucIdx].sInputData.unSize;

		//Step 3) Call UUT
		boolean boRetVal = CddSpi_TransferComplete_Deriv(asTestCaseData[ucIdx].sInputData.ucSpiIfc, unSize);

		//Step 4) Check expected output values
		AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.boReturn, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_TransferCompleteDMA_Deriv
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function CddSpi_TransferCompleteDMA_Deriv returns the right value by checking the transfer completion considering
///        the RX channel of interface
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///             -ucSpiIfc            : Spi Interface
///             -boChannelStatus     : Status that CddDma_IsJobCompleted should return
///         - Expected results
///             - boReturn: return value of  FUT
///
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_TransferCompleteDMA_Deriv(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8    ucSpiIfc;
		boolean  boChannelStatus;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		boolean boReturn;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//           Inputs            || Outputs
		// Spi Ifc    | Channel status || Return value
		{ {CDDSPI_IFC0, FALSE  }       ,  { FALSE  } },
		{ {CDDSPI_IFC0, TRUE   }       ,  { TRUE   } },
		{ {CDDSPI_IFC1, TRUE   }       ,  { TRUE   } },
		{ {CDDSPI_IFC1, FALSE  }       ,  { FALSE  } },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign Input values
		CddDma_IsJobCompleted_boReturn = asTestCaseData[ucIdx].sInputData.boChannelStatus;

		//Step 3) Call UUT
		boolean boRetVal = CddSpi_TransferCompleteDMA_Deriv(asTestCaseData[ucIdx].sInputData.ucSpiIfc);

		//Step 4) Check expected output values
		AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.boReturn, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_DmaStop_Deriv
///
/// \Functional Safety: QM
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: 
///        Check if the function Mt_CddSpi_DmaStop_Deriv sets the right values by checking the registers structure
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///             -ucSpiIfc            : Spi Interface
///         - Expected results
///             - psPeri registers value should be zero
///
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_DmaStop_Deriv(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8    ucSpiIfc;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//     Inputs    || Outputs
		// Spi Ifc       || Return value
		{ {CDDSPI_IFC0} },
		{ {CDDSPI_IFC0} },
		{ {CDDSPI_IFC1} },
		{ {CDDSPI_IFC1} },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign Input values

		//Step 3) Call UUT
		CddSpi_DmaStop_Deriv(asTestCaseData[ucIdx].sInputData.ucSpiIfc);

		//Step 4) Check expected output values
		AL_UNITTEST_CHECK(psPeri->unDER.sBit.u1RDDE, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unDER.sBit.u1TDDE, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unSR.ulData, 0U, == );
		AL_UNITTEST_CHECK(psPeri->unTCR.ulData, 0U, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_RxEventTriggered_Deriv
///
/// \Functional Safety: ASIL B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_RxEvenTriggered_Derive returns the right value by evaluating if the Rx Event has been set
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///            -ucSpiIfc: Spi Interface
///            -boRxEventTriggered: Spi-Hw Register value which provides information about Rx Event
///         - Expected results
///            -boRetVal: Return value of the FUT.
///
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_RxEventTriggered_Deriv(void)
{
	//  typedef struct tsTestCaseDataInput
	//  {
	//    uint8    ucSpiIfc;
	//    boolean  boRxEventTriggered;
	//  }tsTestCaseDataInput;
	//
	//  typedef struct tsTestCaseDataOutput
	//  {
	//    boolean   boRetVal;
	//  }tsTestCaseDataOutput;
	//
	//  typedef struct tsTestCaseData
	//  {
	//    tsTestCaseDataInput  sInputData;
	//    tsTestCaseDataOutput sOutputData;
	//  }tsTestCaseData;
	//
	//  tsTestCaseData asTestCaseData[] =
	//  {
	//    //           Inputs                        || Outputs
	//    // Spi Ifc      |boRxEventTriggered        ||  boRetVal
	//    { {CDDSPI_IFC0   , FALSE  }                 ,  { FALSE} },
	//    { {CDDSPI_IFC0   , TRUE   }                 ,  { TRUE } },
	//    { {CDDSPI_IFC1   , FALSE  }                 ,  { FALSE} },
	//    { {CDDSPI_IFC1   , TRUE   }                 ,  { TRUE } },
	//    { {CDDSPI_IFC2   , FALSE  }                 ,  { FALSE} },
	//    { {CDDSPI_IFC2   , TRUE   }                 ,  { TRUE } },
	//    { {CDDSPI_IFC3   , FALSE  }                 ,  { FALSE} },
	//    { {CDDSPI_IFC3   , TRUE   }                 ,  { TRUE } },
	//    { {CDDSPI_IFC4   , FALSE  }                 ,  { FALSE} },
	//    { {CDDSPI_IFC4   , TRUE   }                 ,  { TRUE } },
	//    { {CDDSPI_IFC5   , FALSE  }                 ,  { FALSE} },
	//    { {CDDSPI_IFC5   , TRUE   }                 ,  { TRUE } },
	//    { {CDDSPI_IFC6   , FALSE  }                 ,  { FALSE} },
	//    { {CDDSPI_IFC6   , TRUE   }                 ,  { TRUE } },
	//    { {CDDSPI_IFC7   , FALSE  }                 ,  { FALSE} },
	//    { {CDDSPI_IFC7   , TRUE   }                 ,  { TRUE } },
	//  };
	//
	//  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	//  {
	//    //Step 1: Set pre-conditions
	//    Mt_CddSpi_RestoreInitContext();
	//    volatile tsCddSpi_CYT2_B9_SCB* const psSCB = &dummySCBCtrl;
	//
	//    //Step 2) Assign Input values
	//    //Initializle register to known value
	//    psSCB->unINTR_RX.sBit.u1TRIGGER = (asTestCaseData[ucIdx].sInputData.boRxEventTriggered == TRUE) ? 1 : 0;
	//
	//    //Step 3) Call UUT
	//    boolean boRetVal = CddSpi_RxEventTriggered_Deriv(asTestCaseData[ucIdx].sInputData.ucSpiIfc);
	boolean boRetVal = CddSpi_RxEventTriggered_Deriv(0U);
	//
	//    //Step 4) Check expected output values
	//    AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.boRetVal, == );
	AL_UNITTEST_CHECK(boRetVal, FALSE, == );
	//
	//  }
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_RxIntDisableDeriv
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_RxIntDisableDeriv sets the rigth value to the Spi-Hw Register to disable Rx Interrupt
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///            -ucSpiIfc: Spi Interface
///            -boRxIntHwRegValuePre: Value of the Spi-Hw register previous to the function execution
///         - Expected results
///            -boRxIntHwRegValuePost: Value of the Spi-Hw register post to the function execution
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
//void Mt_CddSpi_RxIntDisable_Deriv(void)
//{
//  typedef struct tsTestCaseDataInput
//  {
//    uint8    ucSpiIfc;
//    boolean  boRxIntHwRegValuePre;
//  }tsTestCaseDataInput;
//
//  typedef struct tsTestCaseDataOutput
//  {
//    boolean  boRxIntHwRegValuePost;
//  }tsTestCaseDataOutput;
//
//  typedef struct tsTestCaseData
//  {
//    tsTestCaseDataInput  sInputData;
//    tsTestCaseDataOutput sOutputData;
//  }tsTestCaseData;
//
//  tsTestCaseData asTestCaseData[] =
//  {
//    //           Inputs     || Outputs
//    // Spi Ifc      |       || ucLevelHwRegValue
//    { {CDDSPI_IFC0, 0 }     ,  { 0} },
//    { {CDDSPI_IFC0, 1 }     ,  { 0} },
//    { {CDDSPI_IFC1, 0 }     ,  { 0} },
//    { {CDDSPI_IFC1, 1 }     ,  { 0} },
//    { {CDDSPI_IFC2, 0 }     ,  { 0} },
//    { {CDDSPI_IFC2, 1 }     ,  { 0} },
//    { {CDDSPI_IFC3, 0 }     ,  { 0} },
//    { {CDDSPI_IFC3, 1 }     ,  { 0} },
//    { {CDDSPI_IFC4, 0 }     ,  { 0} },
//    { {CDDSPI_IFC4, 1 }     ,  { 0} },
//    { {CDDSPI_IFC5, 0 }     ,  { 0} },
//    { {CDDSPI_IFC5, 1 }     ,  { 0} },
//    { {CDDSPI_IFC6, 0 }     ,  { 0} },
//    { {CDDSPI_IFC6, 1 }     ,  { 0} },
//    { {CDDSPI_IFC7, 0 }     ,  { 0} },
//    { {CDDSPI_IFC7, 1 }     ,  { 0} },
//  };
//
//  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
//  {
//    //Step 1: Set pre-conditions
//    Mt_CddSpi_RestoreInitContext();
//    volatile tsCddSpi_CYT2_B9_SCB* const psSCB = &dummySCBCtrl;
//
//    //Step 2) Assign Input values
//    psSCB->unINTR_RX_MASK.sBit.u1TRIGGER = asTestCaseData[ucIdx].sInputData.boRxIntHwRegValuePre;
//
//    //Step 3) Call UUT
//    CddSpi_RxIntDisable_Deriv(asTestCaseData[ucIdx].sInputData.ucSpiIfc);
//
//    //Step 4) Check expected output values
//    AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sOutputData.boRxIntHwRegValuePost, asTestCaseData[ucIdx].sOutputData.boRxIntHwRegValuePost, == );
//
//  }
//}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_RxTriggerEventClear_Deriv
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that the function CddSpi_RxTriggerEventClear_Deriv sets the right value of the Spi-Hw register to clear the Rx Trigger event
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///            -ucSpiIfc: Spi Interface
///             -boRxTriggerEventClearHwRegValuePre: Value of Spi-Hw register previous to FUT execution
///         - Expected results
///             -boRxTriggerEventClearHwRegValuePost: Value of Spi-Hw register post to FUT execution
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_RxTriggerEventClear_Deriv(void)
{
	//  typedef struct tsTestCaseDataInput
	//  {
	//    uint8    ucSpiIfc;
	//    boolean  boRxTriggerEventClearHwRegValuePre;
	//  }tsTestCaseDataInput;
	//
	//  typedef struct tsTestCaseDataOutput
	//  {
	//    boolean  boRxTriggerEventClearHwRegValuePost;
	//  }tsTestCaseDataOutput;
	//
	//  typedef struct tsTestCaseData
	//  {
	//    tsTestCaseDataInput  sInputData;
	//    tsTestCaseDataOutput sOutputData;
	//  }tsTestCaseData;
	//
	//  tsTestCaseData asTestCaseData[] =
	//  {
	//    //           Inputs                                       || Outputs
	//    // Spi Ifc      | boRxTriggerEventClearHwRegValuePre      || boRxTriggerEventClearHwRegValuePost
	//    { {CDDSPI_IFC0   , 0                                }     ,  { 1} },
	//    { {CDDSPI_IFC0   , 1                                }     ,  { 1} },
	//    { {CDDSPI_IFC1   , 0                                }     ,  { 1} },
	//    { {CDDSPI_IFC1   , 1                                }     ,  { 1} },
	//    { {CDDSPI_IFC2   , 0                                }     ,  { 1} },
	//    { {CDDSPI_IFC2   , 1                                }     ,  { 1} },
	//    { {CDDSPI_IFC3   , 0                                }     ,  { 1} },
	//    { {CDDSPI_IFC3   , 1                                }     ,  { 1} },
	//    { {CDDSPI_IFC4   , 0                                }     ,  { 1} },
	//    { {CDDSPI_IFC4   , 1                                }     ,  { 1} },
	//    { {CDDSPI_IFC5   , 0                                }     ,  { 1} },
	//    { {CDDSPI_IFC5   , 1                                }     ,  { 1} },
	//    { {CDDSPI_IFC6   , 0                                }     ,  { 1} },
	//    { {CDDSPI_IFC6   , 1                                }     ,  { 1} },
	//    { {CDDSPI_IFC7   , 0                                }     ,  { 1} },
	//    { {CDDSPI_IFC7   , 1                                }     ,  { 1} },
	//  };
	//
	//  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	//  {
	//    //Step 1: Set pre-conditions
	//    Mt_CddSpi_RestoreInitContext();
	//    volatile tsCddSpi_CYT2_B9_SCB* const psSCB = &dummySCBCtrl;
	//    //Step 2) Assign Input values
	//    //Initializle register to known value
	//    psSCB->unINTR_RX.sBit.u1TRIGGER = asTestCaseData[ucIdx].sInputData.boRxTriggerEventClearHwRegValuePre;
	//
	//    //Step 3) Call UUT
	//    CddSpi_RxTriggerEventClear_Deriv(asTestCaseData[ucIdx].sInputData.ucSpiIfc);
	CddSpi_RxTriggerEventClear_Deriv(0U);
	//
	//    //Step 4) Check expected output values
	//    AL_UNITTEST_CHECK(psSCB->unINTR_RX.sBit.u1TRIGGER, asTestCaseData[ucIdx].sOutputData.boRxTriggerEventClearHwRegValuePost, == );
	//
	//  }
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_TxFifoPut_Deriv
///
/// \Functional Safety:  ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that the function CddSpi_TxFifoPut_Deriv writes data in the Fifo-HW Buffer
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///            -ucSpiIfc : Spi Interface
///            -punBuff  : Buffer passed to the FUT
///            -unData   : Data content of the buffer passed to the FUT
///            -unLength : Length of the buffer passed to the FUT
///         - Expected results
///             -unHwBuffData:  Data content of the Fifo-HW BUffer
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_TxFifoPut_Deriv(void)
{

	typedef struct tsTestCaseDataInput
	{
		uint8   ucSpiIfc;
		uint16* punBuff;
		uint16  unData;
		uint16  unLength;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint16  unHwBuffData;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	uint16 punDataBuff[CDDSPI_UT_BUFF_MAX_LENGTH] = { 0x0000U };

	tsTestCaseData asTestCaseData[] =
	{
		//           Inputs                                                         ||  Outputs
		// Spi Ifc     | Buffer      | Data Buffer                 | Length         ||  Data Hw Buffer
		{ {CDDSPI_IFC0 ,punDataBuff  , CDDSPI_UT_UINT16_PATTERN     , 0           } ,  {0x0                      } },
		{ {CDDSPI_IFC0 ,punDataBuff  , CDDSPI_UT_UINT16_PATTERN     , 1           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC0 ,punDataBuff  , CDDSPI_UT_UINT16_PATTERN     , 2           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC0 ,punDataBuff  , CDDSPI_UT_UINT16_PATTERN     , 3           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC0 ,NULL_PTR     , CDDSPI_UT_UINT16_PATTERN     , 3           } ,  {0x00                     } },
		{ {CDDSPI_IFC1 ,punDataBuff  , CDDSPI_UT_UINT16_PATTERN     , 0           } ,  {0x0                      } },
		{ {CDDSPI_IFC1 ,punDataBuff  , CDDSPI_UT_UINT16_PATTERN     , 1           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC1 ,punDataBuff  , CDDSPI_UT_UINT16_PATTERN     , 2           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC1 ,punDataBuff  , CDDSPI_UT_UINT16_PATTERN     , 3           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC1 ,punDataBuff  , CDDSPI_UT_UINT16_PATTERN     , 4           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC1 ,NULL_PTR     , CDDSPI_UT_UINT16_PATTERN     , 3           } ,  {0x00                     } },
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign Input values
		if (asTestCaseData[ucIdx].sInputData.punBuff != NULL_PTR)
		{
			psPeri->unFSR.sBit.u3TXCOUNT = asTestCaseData[ucIdx].sInputData.unLength;
			for (uint8 ucBuffIdx = 0U; ucBuffIdx < asTestCaseData[ucIdx].sInputData.unLength; ucBuffIdx++)
			{
				asTestCaseData[ucIdx].sInputData.punBuff[ucBuffIdx] = asTestCaseData[ucIdx].sInputData.unData;
			}
		}

		//Step 3) Call UUT
		CddSpi_TxFifoPut_Deriv(asTestCaseData[ucIdx].sInputData.ucSpiIfc,
			asTestCaseData[ucIdx].sInputData.punBuff,
			asTestCaseData[ucIdx].sInputData.unLength);

		//Step 4) Check expected output values
		for (uint8 ucBuffIdx = 0U; ucBuffIdx < asTestCaseData[ucIdx].sInputData.unLength; ucBuffIdx++)
		{
			AL_UNITTEST_CHECK(psPeri->unTDR.ulData, asTestCaseData[ucIdx].sOutputData.unHwBuffData, == );
		}
	}
}
//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_RxFifoGet_Deriv
///
/// \Functional Safety:  ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Test Case Description
///    - Test subject:  Check that the function CddSpi_RxFifoGet_Deriv gets the data from Fifo-HW Buffer  and copy to the buffer passed as parameter
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///            -ucSpiIfc      : Spi Interface
///            -unHwBuffData  :  Data content of the Fifo-HW BUffer
///            -unLength      : Length of the buffer passed to the FUT
///         - Expected results
///            -unData  :  Data content of the buffer passed to the FUT
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_RxFifoGet_Deriv(void)
{

	typedef struct tsTestCaseDataInput
	{
		uint8   ucSpiIfc;
		uint16* punBuff;
		uint16  unHwBuffData;
		uint16  unLength;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint16  unData;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	uint16 punDataBuff[CDDSPI_UT_BUFF_MAX_LENGTH] = { 0 };
	tsTestCaseData asTestCaseData[] =
	{
		//           Inputs                                            ||  Outputs
		// Spi Ifc    |Data Buffer  | Data Hw Buffer               | Length        ||  Data Hw buffer
		{ {CDDSPI_IFC0 , punDataBuff   , 0                            , 0           } ,  {0                        } },
		{ {CDDSPI_IFC0 , punDataBuff   , CDDSPI_UT_UINT16_PATTERN     , 0           } ,  {0                        } },
		{ {CDDSPI_IFC0 , punDataBuff   , CDDSPI_UT_UINT16_PATTERN     , 1           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC0 , punDataBuff   , CDDSPI_UT_UINT16_PATTERN     , 2           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC0 , punDataBuff   , CDDSPI_UT_UINT16_PATTERN     , 3           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC0 , NULL_PTR      , CDDSPI_UT_UINT16_PATTERN     , 3           } ,  {0                        } },
		#if 1
		{ {CDDSPI_IFC1 , punDataBuff   , 0                            , 0           } ,  {0                        } },
		{ {CDDSPI_IFC1 , punDataBuff   , CDDSPI_UT_UINT16_PATTERN     , 0           } ,  {0                        } },
		{ {CDDSPI_IFC1 , punDataBuff   , CDDSPI_UT_UINT16_PATTERN     , 1           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC1 , punDataBuff   , CDDSPI_UT_UINT16_PATTERN     , 2           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC1 , punDataBuff   , CDDSPI_UT_UINT16_PATTERN     , 3           } ,  {CDDSPI_UT_UINT16_PATTERN } },
		{ {CDDSPI_IFC1 , NULL_PTR      , CDDSPI_UT_UINT16_PATTERN     , 3           } ,  {0                        } },
		#endif
	};

	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;
		for (uint8 ucBuffIdx = 0U; ucBuffIdx < CDDSPI_UT_BUFF_MAX_LENGTH; ucBuffIdx++)
		{
			punDataBuff[ucBuffIdx] = 0x0000U;
		}

		//Step 2) Assign Input values
		psPeri->unRDR.ulData = asTestCaseData[ucIdx].sInputData.unHwBuffData;

		//Step 3) Call UUT
		CddSpi_RxFifoGet_Deriv(asTestCaseData[ucIdx].sInputData.ucSpiIfc,
			asTestCaseData[ucIdx].sInputData.punBuff,
			asTestCaseData[ucIdx].sInputData.unLength);

		//Step 4) Check expected output values
		if (asTestCaseData[ucIdx].sInputData.punBuff != NULL_PTR)
		{
			for (uint8 ucBuffIdx = 0U; ucBuffIdx < CDDSPI_UT_BUFF_MAX_LENGTH; ucBuffIdx++)
			{
				if (ucBuffIdx < asTestCaseData[ucIdx].sInputData.unLength)
				{
					AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sInputData.punBuff[ucBuffIdx], asTestCaseData[ucIdx].sOutputData.unData, == );
				}
				else
				{
					AL_UNITTEST_CHECK(asTestCaseData[ucIdx].sInputData.punBuff[ucBuffIdx], 0, == );
				}
			}
		}

	}
}


//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_GetEFTData
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_GetEFTData provides a pointer to the EFT Data structure and returns the right value depending on the
///      EFT data validity
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///            - boEFTDataValid = EFT Data validity
///         - Expected results
///            - sEFTDataPtr = Pointer to sEFTData structure
///            - unReturnVal = Return value of FUT
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - EFT data must be emulated
///
//------------------------------------------------------------------------------
void Mt_CddSpi_GetEFTData(void)
{
	typedef struct tsTestCaseDataInput
	{
		boolean        boEFTDataValid;
		tieEftDataPtr  sEFTDataPtr;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		tieEftDataPtr  psEFTData;
		boolean         unReturnVal;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//           Inputs              || Outputs
		// EFTDataValid                  ||  Data           | Return Val
		{ { FALSE , NULL_PTR  }           , {NULL_PTR      , FALSE } },
		{ { TRUE  , NULL_PTR  }           , {NULL_PTR      , FALSE } },
		{ { FALSE , &Stub_sEftInitVal  }  , {NULL_PTR      , FALSE } },
		{ { TRUE  , &Stub_sEftInitVal  }  , {Stub_psEftAddr, TRUE  } },

	};

	volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;
	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		tieEftDataPtr psEFTDAta = NULL_PTR;
		uint16 unEFT = 0;

		//Step 2) Assign Input values
		Rte_Read_ctacCddSpi_ppCodMEftCrcStatus0_sVal_eData = asTestCaseData[ucIdx].sInputData.boEFTDataValid;
		Stub_psEftAddr = asTestCaseData[ucIdx].sInputData.sEFTDataPtr;

		//Step 3) Call UUT
		boolean boRetVal = CddSpi_GetEFTData(&psEFTDAta);

		//Step 4) Check expected output values
		AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.unReturnVal, == );
		AL_UNITTEST_CHECK(psEFTDAta, asTestCaseData[ucIdx].sOutputData.psEFTData, == );

	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_GetStpConfig
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Test Case Description
///    - Test subject: Check if the function CddSpi_GetStpConfig provides the right footprint value and return value depending of the
///      EFT data validity and EFT content concerning steppers population
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///             -boEFTDataValid: EFT Data validity (fault injection)
///         - Expected results
///             -boStp0Mounted: Emulate Stp0 population
///             -boStp1Mounted: Emulate Stp1 population
///             -boStp2Mounted: Emulate Stp2 population
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_GetStpConfig(void)
{
	typedef struct tsTestCaseDataInput
	{
		boolean  boEFTDataValid;
		boolean  boStp0Mounted;
		boolean  boStp1Mounted;
		boolean  boStp2Mounted;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint16     unData;
		boolean    unReturnVal;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//           Inputs                                            || Outputs
		// EFTDataValid| Stp0 Mounted |Stp1 Mounted | Stp2 Mounted     || Data           | Return Val
		{ { FALSE      , FALSE        , FALSE       , FALSE }          ,  {0             , FALSE } },
		{ { FALSE      , FALSE        , FALSE       , TRUE  }          ,  {0             , FALSE } },
		{ { FALSE      , FALSE        , TRUE        , FALSE }          ,  {0             , FALSE } },
		{ { FALSE      , FALSE        , TRUE        , TRUE  }          ,  {0             , FALSE } },
		{ { FALSE      , TRUE         , FALSE       , FALSE }          ,  {0             , FALSE } },
		{ { FALSE      , TRUE         , FALSE       , TRUE  }          ,  {0             , FALSE } },
		{ { FALSE      , TRUE         , TRUE        , FALSE }          ,  {0             , FALSE } },
		{ { FALSE      , TRUE         , TRUE        , TRUE  }          ,  {0             , FALSE } },
		{ { TRUE       , FALSE        , FALSE       , FALSE }          ,  {0x00          , TRUE  } },
		{ { TRUE       , FALSE        , FALSE       , TRUE  }          ,  {0x01          , TRUE  } },
		{ { TRUE       , FALSE        , TRUE        , FALSE }          ,  {0x01          , TRUE  } },
		{ { TRUE       , FALSE        , TRUE        , TRUE  }          ,  {0x07          , TRUE  } },
		{ { TRUE       , TRUE         , FALSE       , FALSE }          ,  {0x01          , TRUE  } },
		{ { TRUE       , TRUE         , FALSE       , TRUE  }          ,  {0x07          , TRUE  } },
		{ { TRUE       , TRUE         , TRUE        , FALSE }          ,  {0x07          , TRUE  } },
		{ { TRUE       , TRUE         , TRUE        , TRUE  }          ,  {0x0F          , TRUE  } },

	};

	volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;
	for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		uint16 unStpConfig = 0;

		Stub_psEftAddr->EFT_ECUVARCFG_STEPPER[0] = (asTestCaseData[ucIdx].sInputData.boStp0Mounted == TRUE) ? 1U : 0U;
		Stub_psEftAddr->EFT_ECUVARCFG_STEPPER[2] = (asTestCaseData[ucIdx].sInputData.boStp1Mounted == TRUE) ? 1U : 0U;
		Stub_psEftAddr->EFT_ECUVARCFG_STEPPER[4] = (asTestCaseData[ucIdx].sInputData.boStp2Mounted == TRUE) ? 1U : 0U;


		//Step 2) Assign Input values
		Rte_Read_ctacCddSpi_ppCodMEftCrcStatus0_sVal_eData = asTestCaseData[ucIdx].sInputData.boEFTDataValid;

		//Step 3) Call UUT
		boolean boRetVal = CddSpi_GetStpConfig(&unStpConfig);

		//Step 4) Check expected output values
		AL_UNITTEST_CHECK(boRetVal, asTestCaseData[ucIdx].sOutputData.unReturnVal, == );
		AL_UNITTEST_CHECK(unStpConfig, asTestCaseData[ucIdx].sOutputData.unData, == );

	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_HandleTransmissionInCyclicPollingMode
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_HandleTransmisisonInCyclicPollingMode handles the SPI-Hw buffering properly according to 
///      the number of devices attached to the sequence. If more than one device is attached, check that it waits for Device transmission completion
///      and stored the received Rx Data in internal Device Rx Buffer.
///      If device CRC Check is enabled, and TX -CRC error has been detected, check that it ignores the SPI-HW bufferinig of the device
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///            -ucSeqIdx     : Sequence Index
///            -boCrcTxError : Tx Crc Error has been detected (fault injection)
///            -ucDeviceCount: Number of devices attached to the sequence
///            -ucTimeOut    : TimeOut condition for transmission completion
///         - Expected results
///            -ucFramesCount: Remaining frames in Spi-Hw buffer
///            -ucHwTxBuff   : Value of Spi-Hw Buffer
///
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_HandleTransmissionInCyclicPollingMode(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8   ucSeqIdx;
		uint8   ucDeviceCount;
		boolean boTimeOut;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint8  ucFramesCount;
		uint16 ucHwTxBuff;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//           Inputs                            ||         Outputs
		//  Seq Index | Seq Device Count | TimeOut     ||  Seq Frames Count | Device Tx Buff 
		{{  0U        ,   1U             , FALSE      } , {1U                , CDDSPI_UT_UINT16_PATTERN }},
		{{  0U        ,   1U             , TRUE       } , {1U                , CDDSPI_UT_UINT16_PATTERN }},
		{{  0U        ,   2U             , TRUE       } , {0U                , CDDSPI_UT_UINT16_PATTERN }},
		{{  0U        ,   3U             , TRUE       } , {0U                , CDDSPI_UT_UINT16_PATTERN }},
		{{  1U        ,   1U             , FALSE      } , {6U                , CDDSPI_UT_UINT16_PATTERN }},
		{{  1U        ,   1U             , TRUE       } , {6U                , CDDSPI_UT_UINT16_PATTERN }},

	};

	for (uint8 ucIdx = 0U; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;
		tsCddSpiSeqHandler*            const psSeqHandler = &CddSpi_asSeqHandler[asTestCaseData[ucIdx].sInputData.ucSeqIdx];
		tsCddSpiSeqData*               const psSeqData = &CddSpi_asSeqData[asTestCaseData[ucIdx].sInputData.ucSeqIdx];

		//Step 2) Assign Input values
		psSeqData->ucDeviceCount = asTestCaseData[ucIdx].sInputData.ucDeviceCount;
		for (uint8 ucDevIdx = 0U; ucDevIdx < psSeqData->ucDeviceCount; ucDevIdx++)
		{
			tsCddSpiDevSeqData* psDevSeqData = &(psSeqData->psDevData[ucDevIdx]);
			//psDevSeqData->boTxCrcError = asTestCaseData[ucIdx].sInputData.boCrcTxError;
			psPeri->unFSR.sBit.u3RXCOUNT |= (asTestCaseData[ucIdx].sInputData.boTimeOut == FALSE) ? (CDDSPI_S32K_14X_RX_FIFO_STATUS_MSK & CddSpi_asDeviceCfg[psDevSeqData->eDev].ucElements) : 0x00U;
			for (uint8 ucElemIdx = 0U; ucElemIdx < CddSpi_asDeviceCfg[psDevSeqData->eDev].ucElements; ucElemIdx++)
			{
				psDevSeqData->punTxBuff[ucElemIdx] = CDDSPI_UT_UINT16_PATTERN;
				//printf("\n data ", psDevSeqData->punTxBuff[ucElemIdx]);
			}
		}

		//Step 3) Call UUT
		CddSpi_HandleTransmissionInCyclicPollingMode(asTestCaseData[ucIdx].sInputData.ucSeqIdx);

		//Step 4) Check expected output values
		AL_UNITTEST_CHECK(psSeqData->ucFramesCount, asTestCaseData[ucIdx].sOutputData.ucFramesCount, == );
		for (uint8 ucDevIdx = 0U; ucDevIdx < psSeqData->ucDeviceCount; ucDevIdx++)
		{
			tsCddSpiDevSeqData* psDevSeqData = &(psSeqData->psDevData[ucDevIdx]);
			for (uint8 ucElemIdx = 0U; ucElemIdx < CddSpi_asDeviceCfg[psDevSeqData->eDev].ucElements; ucElemIdx++)
			{
				//printf("\n data ", psDevSeqData->punTxBuff[ucElemIdx]);
				AL_UNITTEST_CHECK(psPeri->unTDR.ulData, asTestCaseData[ucIdx].sOutputData.ucHwTxBuff, == );
			}
		}

	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_CddSpi_HandleTransmissionInCyclicDMAMode
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Test Case Description
///    - Test subject: Check that the function CddSpi_HandleTransmisisonInCyclicDMAMode handles the SPI-Hw buffering properly according to 
///      the number of devices attached to the sequence. If more than one device is attached, check that it waits for Device transmission completion
///      and stored the received Rx Data in internal Device Rx Buffer.
///      If device CRC Check is enabled, and TX -CRC error has been detected, check that it ignores the SPI-HW bufferinig of the device
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs:
///            -ucSeqIdx     : Sequence Index
///            -boCrcTxError : Tx Crc Error has been detected (fault injection)
///            -ucDeviceCount: Number of devices attached to the sequence
///            -ucTimeOut    : TimeOut condition for transmission completion
///         - Expected results
///            -ucFramesCount: Remaining frames in Spi-Hw buffer
///            -ucHwTxBuff   : Value of Spi-Hw Buffer
///
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
void Mt_CddSpi_HandleTransmissionInCyclicDMAMode(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8   ucSeqIdx;
		uint16  ulData;
		uint8   ucDeviceCount;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint32  TCR_Data[7];
		uint16 ucHwTxBuff;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	tsTestCaseData asTestCaseData[] =
	{
		//           Inputs                                   ||         Outputs
		//  Seq Index | TransferData             | DevicesNo  ||  TCR_Data                                                                | Device Tx Buff 
		{{  0U        , 0x0 , 6U }        , {{0x6080000f, 0x2100000f, 0x6300000f, 0x0,		  0x0,		  0x0		}, 0x0 }},
		{{  0U        , 0x0 , 6U }        , {{0x6080000f, 0x2100000f, 0x6300000f, 0x0,		  0x0,		  0x0		}, 0x0 }},
		{{  1U        , 0x0 , 6U }        , {{0x2020000f, 0x2030000f, 0x2030000f, 0x2030000f, 0x2030000f, 0x2010000f}, 0x0 }},
		{{  1U        , 0x0 , 6U }        , {{0x2020000f, 0x2030000f, 0x2030000f, 0x2030000f, 0x2030000f, 0x2010000f}, 0x0 }},
	};

	for (uint8 ucIdx = 0U; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1: Set pre-conditions
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;
		tsCddSpiSeqHandler*				  const psSeqHandler = &CddSpi_asSeqHandler[asTestCaseData[ucIdx].sInputData.ucSeqIdx];
		tsCddSpiSeqData*				  const psSeqData = &CddSpi_asSeqData[asTestCaseData[ucIdx].sInputData.ucSeqIdx];
		uint8 ucInterfaceIdx = CddSpi_asIfcCfg[psSeqHandler->eSpiIfc].ucIfcMap;

		//Step 2) Assign Input values
		for (uint8 ucDevIdx = 0U; ucDevIdx < psSeqData->ucDeviceCount; ucDevIdx++)
		{
			tsCddSpiDevSeqData* psDevSeqData = &(psSeqData->psDevData[ucDevIdx]);

			for (uint8 ucElemIdx = 0U; ucElemIdx < CddSpi_asDeviceCfg[psDevSeqData->eDev].ucElements; ucElemIdx++)
			{
				psDevSeqData->punTxBuff[ucElemIdx] = (uint32)asTestCaseData[ucIdx].sInputData.ulData;
			}
		}

		//Step 3) Call FUT
		CddSpi_HandleTransmissionInCyclicDMAMode(asTestCaseData[ucIdx].sInputData.ucSeqIdx);

		//Step 4) Check expected output values
		for (uint8 ucElemIdx = 0U; ucElemIdx < asTestCaseData[ucIdx].sInputData.ucDeviceCount; ucElemIdx++)
		{
			AL_UNITTEST_CHECK(CddSpi_msInterleaveData[ucInterfaceIdx][ucElemIdx].ulTCR_data, asTestCaseData[ucIdx].sOutputData.TCR_Data[ucElemIdx], == );
			AL_UNITTEST_CHECK(CddSpi_msInterleaveData[ucInterfaceIdx][ucElemIdx].ulTDR_data, asTestCaseData[ucIdx].sOutputData.ucHwTxBuff, == );
		}
	}
}

//-----------------------------------------------------------------------------
/// \Test Cased : Mt_riCddSpiInit
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
///
/// \Test Case Description
///    - Test subject: Check correct execution of function riCddSpiInit. As content of the function is a single function call to CddSpi_Start
///      the same UT check  procedure has been applied as in its related UT  Mt_CddSpi_Start
///
///      - DT-Info:
///         - Inputs:
///             - ucSpiState     : Previous Spi driver state
///             - boTimeout      : TimeOut is  elpased (fault injection)
///
///         - Expected results
///             - ucSpiState     : Expected Spi driver state set by the FUT
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///         - Timeout error injection shall be simulated by using a dummy structure which emulates the real HW register set of the SPI level driver
//-----------------------------------------------------------------------------
void Mt_riCddSpiInit(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8         ucSpiState;
		boolean       boDynamicCfgValid;
		boolean       boTimeOut;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint8         ucSpiState;
		uint8         ucStatusFault;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput  sInputData;
		tsTestCaseDataOutput sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		//                     Inputs                 ||       Outputs
		// Previous state                | TimeOut    ||  expected State
    {{CDDSPI_STATE_RESET              , FALSE     , FALSE  }   , {CDDSPI_STATE_RESET           , 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_RESET              , FALSE     , TRUE   }   , {CDDSPI_STATE_RESET           , 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_RESET              , TRUE      , FALSE  }   , {CDDSPI_STATE_RESET           , 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_RESET              , TRUE      , TRUE   }   , {CDDSPI_STATE_RESET           , 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_SINGLE_OPERATION   , FALSE     , FALSE  }   , {CDDSPI_STATE_SINGLE_OPERATION, CDDSPI_STATUS_FAULT_SA_MSK | CDDSPI_STATUS_FAULT_DYNAMIC_CONFIG_ERROR_MSK } },
    {{CDDSPI_STATE_SINGLE_OPERATION   , FALSE     , TRUE   }   , {CDDSPI_STATE_SINGLE_OPERATION, CDDSPI_STATUS_FAULT_SA_MSK | CDDSPI_STATUS_FAULT_DYNAMIC_CONFIG_ERROR_MSK } },
    {{CDDSPI_STATE_SINGLE_OPERATION   , TRUE      , FALSE  }   , {CDDSPI_STATE_CYCLIC_OPERATION, CDDSPI_STATUS_FAULT_SA_MSK | 0x00                                         } },
    {{CDDSPI_STATE_SINGLE_OPERATION   , TRUE      , TRUE   }   , {CDDSPI_STATE_CYCLIC_OPERATION, CDDSPI_STATUS_FAULT_SA_MSK | 0x00                                         } },
    {{CDDSPI_STATE_CYCLIC_OPERATION   , FALSE     , FALSE  }   , {CDDSPI_STATE_CYCLIC_OPERATION, 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_CYCLIC_OPERATION   , FALSE     , TRUE   }   , {CDDSPI_STATE_CYCLIC_OPERATION, 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_CYCLIC_OPERATION   , TRUE      , FALSE  }   , {CDDSPI_STATE_CYCLIC_OPERATION, 0x00 | 0x00                                         } },
    {{CDDSPI_STATE_CYCLIC_OPERATION   , TRUE      , TRUE   }   , {CDDSPI_STATE_CYCLIC_OPERATION, 0x00 | 0x00                                         } },
	};

	for (uint8 ucIdx = 0U; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();
		volatile tsCddSpi_S32K146_PERI*   const psPeri = &dummyPERI;

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		CddSpi_ucState = asTestCaseData[ucIdx].sInputData.ucSpiState;
		psPeri->unSR.sBit.u1MBF = asTestCaseData[ucIdx].sInputData.boTimeOut;                                     //Mechanism to stimulate time out condition
    CddTps92520_SpiGetConfig_boReturn = asTestCaseData[ucIdx].sInputData.boDynamicCfgValid;  //Mechanism to stimulate return value of Dynami Configuration

		//Step 3) Call the FUT
		riCddSpiInit();

		//Step 4) Check that the value of the output variables set/changed by the FUT matchs the corresponding expected output value 
		AL_UNITTEST_CHECK(CddSpi_ucState, asTestCaseData[ucIdx].sOutputData.ucSpiState, == );
	}
}

//-----------------------------------------------------------------------------
/// \Test Cased : Mt_rpCddSpi_Cycle
///
/// \Functional Safety: ASIL-B
///
/// \Test methods: 
///        - Requirements-based test
///
/// \Steps:
///         Step1: Set pre - conditions if needed
///         Step2: Assign all input values to the corresponding input variables identified in the FUT
///         Step3: Call the FUT
///         Step4: Check that no exception takes place
///
/// \Test Case Description
///    - Test subject: Check that the function Mt_rpCddSpi_Cycle clears the internal variable for collecting error flags if the driver operates in CYCLIC Operation Mode
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. Every DT-entry represents a different Test Case interaction.
///      - DT-Info:
///         - Inputs:
///           - ucSpiState   : Current Spi driver state
///         - Expected results
///           - ucStatusFault: Expect value of internal variable which collecst all error flags
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions:
///         - Module internal variables shall contain its init value set statically 
///         - CddSpi_ucStatusFault variable shall be set to an non zero value
///
//-----------------------------------------------------------------------------
void Mt_rpCddSpi_Cycle(void)
{
	typedef struct tsTestCaseDataInput
	{
		uint8        ucSpiState;
	}tsTestCaseDataInput;

	typedef struct tsTestCaseDataOutput
	{
		uint8 ucStatusFault;
	}tsTestCaseDataOutput;

	typedef struct tsTestCaseData
	{
		tsTestCaseDataInput   sInputData;
		tsTestCaseDataOutput  sOutputData;
	}tsTestCaseData;

	static tsTestCaseData asTestCaseData[] =
	{
		//             Inputs            ||  Outputs  
		// Operation mode                ||
		{{CDDSPI_STATE_RESET            } , {CDDSPI_UT_SF_EFT_SA_MASK  }},
		{{CDDSPI_STATE_CYCLIC_OPERATION } , {CDDSPI_UT_SF_EFT_SA_MASK  }},
		{{CDDSPI_STATE_SINGLE_OPERATION } , {CDDSPI_UT_SF_EFT_SA_MASK  }},
	};

	for (uint8 ucIdx = 0U; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
	{
		//Step 1) Set pre - conditions if needed
		Mt_CddSpi_RestoreInitContext();
#if (CDDSPI_STATUS_FAULT == STD_ON)
		CddSpi_ucStatusFaultVal |= CDDSPI_UT_SF_EFT_SA_MASK;
#endif

		//Step 2) Assign all input values to the corresponding input variables identified in the FUT
		CddSpi_ucState = asTestCaseData[ucIdx].sInputData.ucSpiState;

		//Step 3) Call the FUT
		rpCddSpi_Cycle();

		// Step 4) Check that no exception takes place
#if (CDDSPI_STATUS_FAULT == STD_ON)
		AL_UNITTEST_CHECK(CddSpi_ucStatusFaultVal & CDDSPI_UT_SF_EFT_SA_MASK, asTestCaseData[ucIdx].sOutputData.ucStatusFault & CDDSPI_UT_SF_EFT_SA_MASK, == );
#endif
	}
}

//-----------------------------------------------------------------------------
/// \Test Case : Mt_ISR_CddSpiIRQ4
///
/// \Functional Safety: NA
///
/// \Test methods: 
///        - Requirements-based test
///        - Fault injection
///
/// \Test Case Description
///    - Test subject: Check the correct execution of function ISR_CddSpiIRQ4. It consist of a single function call of CddSpi_ISRHandler, providing a fixed function argument value equal to 0.
///      For that reason the same DT has been used as in Mt_CddSpi_ISRHandler limiting the value of this argument  to 0 (unIfcIdx)
///      As in Mt_CddSpi_ISRHandler, the UT check if the FUT saves the received Rx Data from Spi-Hw Buffer in the device internal buffer and set the correct values
///      of all internal flags for the Interrupt Service Routine Handling, and it triggers the transmission of the next device of the sequence in which a Tx Crc Error
///      has not been detected or it sets the completion flag and disables the Rx-Interrupts  if the current device is the last in sequence 
///
///    - Test Design Technique: DT (Decision Table)
///        The Decision Table asTestCaseData[] is used in this test case. This DT contains all possible values of all inputs
///        which are taken into account by the algorithm of the FUT, as well as the expected values of all outputs which are
///        set by the FUT. 
///      - DT-Info:
///         - Inputs: 
///             -ucIfcIdx           : Spi Interface index
///             -ucDeviceIdxPre     : Device Index previous to the function execution
///             -ucDeviceCount      : Number of devices attached to the sequence
///             -boIntEvenTriggered : Flag which indicates an Interrupt Trigger event has been set
///             -boTxCrcError       : TxCrcError has been detected (fault injection)
///         - Expected results
///             -boRxTriggerEventClearHwRegValuePost : Value of Trigger Event Flag post execution
///             -ulDeviceBuff                        : Data of internal device buffer
///             -ucDeviceIdxPost                     : Device Index post  to the function execution
///             -boXferCompletFlag                   : Transmission complet flag post to the function execution
///
///       For further information about specific input/outputs variables refer to the  input assignament (step 2) and output value check (step 4) of this Unit Test Case
///
///    - Preconditions: 
///         - Module internal variables shall contain its init value set statically 
///         - All related SPI-HW registers which are used must be emulated by the Test Case.
///
//------------------------------------------------------------------------------
//void Mt_ISR_CddSpiIRQ4(void)
//{
//  typedef struct tsTestCaseDataInput
//  {
//    uint8      ucIfcIdx;
//    uint8      ucDeviceIdxPre;
//    uint8      ucDeviceCount;
//    boolean    boIntEvenTriggered;
//    boolean    boTxCrcError;
//  }tsTestCaseDataInput;
//
//  typedef struct tsTestCaseDataOutput
//  {
//    boolean  boRxTriggerEventClearHwRegValuePost;
//    uint32   ulDeviceBuff;
//    uint8    ucDeviceIdxPost;
//    boolean  boXferCompletFlag;
//  }tsTestCaseDataOutput;
//
//  typedef struct tsTestCaseData
//  {
//    tsTestCaseDataInput  sInputData;
//    tsTestCaseDataOutput sOutputData;
//  }tsTestCaseData;
//
//  tsTestCaseData asTestCaseData[] =
//  {
//    //           Inputs                                                                      || Outputs
//    //  Interface Index |Device Index | Device Count  | Event Triggered       | TxCrc Error  || Hw Event Triggered Flag | Device Buffer           | Device Index after execution | Transfer complete Flag
//    { { 0               ,  0           , 1             , FALSE                , FALSE        },  { 0                    , 0x00U                   ,       0                      , FALSE}},
//    { { 0               ,  0           , 1             , FALSE                , TRUE         },  { 0                    , 0x00U                   ,       0                      , FALSE}},
//    { { 0               ,  0           , 1             , TRUE                 , FALSE        },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       1                      , TRUE}},
//    { { 0               ,  0           , 1             , TRUE                 , TRUE         },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       1                      , TRUE}},
//    { { 0               ,  1           , 1             , FALSE                , FALSE        },  { 0                    , 0x00U                   ,       1                      , FALSE}},
//    { { 0               ,  1           , 1             , FALSE                , TRUE         },  { 0                    , 0x00U                   ,       1                      , FALSE}},
//    { { 0               ,  1           , 1             , TRUE                 , FALSE        },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       2                      , TRUE}},
//    { { 0               ,  1           , 2             , TRUE                 , FALSE        },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       2                      , TRUE}},
//    { { 0               ,  0           , 2             , TRUE                 , TRUE         },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       2                      , TRUE}},
//    { { 0               ,  0           , 2             , TRUE                 , FALSE        },  { 1                    ,CDDSPI_UT_UINT16_PATTERN ,       1                      , FALSE}},
//  };
//
//
//  for (uint8 ucIdx = 0; ucIdx < sizeof(asTestCaseData) / sizeof(tsTestCaseData); ucIdx++)
//  {
//    //Step 1: Set pre-conditions
//    Mt_CddSpi_RestoreInitContext();
//    volatile tsCddSpi_CYT2_B9_SCB* const psSCB = &dummySCBCtrl;
//
//    //Step 2) Assign Input values
//    uint8 ucIfcIdx = asTestCaseData[ucIdx].sInputData.ucIfcIdx;
//    tsCddSpiSeqHandler* const psSeqHandler = &CddSpi_asSeqHandler[CddSpi_asIfcCfg[ucIfcIdx].ucSeqMap];
//    tsCddSpiSeqData*          psSeqData = &CddSpi_asSeqData[CddSpi_asIfcCfg[ucIfcIdx].ucSeqMap];
//    tsCddSpiDevSeqData*       psDevData = &psSeqData->psDevData[psSeqHandler->ucIntDevIdx];
//
//    for (uint8 ucDevBuffIdx = 0U; ucDevBuffIdx < CddSpi_asDeviceCfg[psDevData->eDev].ucElements; ucDevBuffIdx++)
//    {
//      psDevData->punRxBuff[ucDevBuffIdx] = 0;
//    }
//
//    //Initializle register to known value
//    psSCB->unINTR_RX.sBit.u1TRIGGER = (asTestCaseData[ucIdx].sInputData.boIntEvenTriggered == TRUE) ? 1 : 0;
//    psSCB->unRX_FIFO_RD.ulData = CDDSPI_UT_UINT16_PATTERN;
//    psSeqData->ucDeviceCount = asTestCaseData[ucIdx].sInputData.ucDeviceCount;
//
//    (psDevData + 1)->boTxCrcError = asTestCaseData[ucIdx].sInputData.boTxCrcError;
//    psSeqHandler->ucIntDevIdx = asTestCaseData[ucIdx].sInputData.ucDeviceIdxPre;
//
//    //Step 3) Call FUT 
//    ISR_CddSpi_IRQ4();
//
//    //Step 4) Check expected output values
//    AL_UNITTEST_CHECK(psSCB->unINTR_RX.sBit.u1TRIGGER, asTestCaseData[ucIdx].sOutputData.boRxTriggerEventClearHwRegValuePost, == );
//    AL_UNITTEST_CHECK(psSeqHandler->ucIntDevIdx, asTestCaseData[ucIdx].sOutputData.ucDeviceIdxPost, == );
//    AL_UNITTEST_CHECK(((psSeqHandler->ucSeqContext & CDDSPI_SEQ_CONTEXT_COMPLETE_MSK) >> CDDSPI_SEQ_CONTEXT_COMPLETE_POS), asTestCaseData[ucIdx].sOutputData.boXferCompletFlag, == );
//  }
//}


//temporary unit test
//void Mt_TaskTest(void)
//{
//	TaskCddSpi_Cyclic_Init();
//	TaskCddSpi_Cyclic_Func();
//	TaskCddSpi_Cyclic_Func();
//}

// ----------------------------------------------------------------------------
// Test Cases
//-----------------------------------------------------------------------------
#define CDDSPI_UT_ISOLATE 1U
void ALUnitTest_AddTests(void)
{
	Mt_CddSpi_SaveInitContext();


#if (CDDSPI_UT_ISOLATE == 0U)
	ALUnitTest_AddFunction("Mt_riCddSpi1ms", Mt_rpCddSpi_Cycle);
#else

	ALUnitTest_AddFunction("Mt_CddSpi_Init", Mt_CddSpi_Init);
	ALUnitTest_AddFunction("Mt_CddSpi_DeInit", Mt_CddSpi_DeInit);
	ALUnitTest_AddFunction("Mt_CddSpi_GetState", Mt_CddSpi_GetState);
#if (CDDSPI_SINGLE_OPERATION == STD_ON)
	ALUnitTest_AddFunction("Mt_CddSpi_TransferMsg", Mt_CddSpi_TransferMsg);
#endif

#if (CDDSPI_DYNAMIC_CFG == STD_ON)
	ALUnitTest_AddFunction("Mt_CddSpi_SetDynamicCfg", Mt_CddSpi_SetDynamicCfg);
	ALUnitTest_AddFunction("Mt_CddSpi_UnSetDevCb", Mt_CddSpi_UnSetDevCb);
#endif
	ALUnitTest_AddFunction("Mt_CddSpi_GetEFTData", Mt_CddSpi_GetEFTData);
	ALUnitTest_AddFunction("Mt_CddSpi_GetStpConfig", Mt_CddSpi_GetStpConfig);

#if (CDDSPI_CYCLIC_OPERATION == STD_ON)
	ALUnitTest_AddFunction("Mt_CddSpi_Start", Mt_CddSpi_Start);
	ALUnitTest_AddFunction("Mt_CddSpi_Stop", Mt_CddSpi_Stop);
	ALUnitTest_AddFunction("Mt_CddSpi_Cycle", Mt_CddSpi_Cycle);
	ALUnitTest_AddFunction("Mt_CddSpi_ProcessSequence", Mt_CddSpi_ProcessSequence);
	ALUnitTest_AddFunction("Mt_CddSpi_ProcessRxData", Mt_CddSpi_ProcessRxData);
	ALUnitTest_AddFunction("Mt_CddSpi_ProcessTxData", Mt_CddSpi_ProcessTxData);
	ALUnitTest_AddFunction("Mt_CddSpi_UpdateDevRxData", Mt_CddSpi_UpdateDevRxData);
	ALUnitTest_AddFunction("Mt_CddSpi_UpdateDevTxData", Mt_CddSpi_UpdateDevTxData);
	ALUnitTest_AddFunction("Mt_CddSpi_HandleTransmissionInCyclicPollingMode", Mt_CddSpi_HandleTransmissionInCyclicPollingMode);
	ALUnitTest_AddFunction("Mt_CddSpi_HandleTransmissionInCyclicDMAMode", Mt_CddSpi_HandleTransmissionInCyclicDMAMode);
	ALUnitTest_AddFunction("Mt_CddSpi_CalculateIfcSeqMap", Mt_CddSpi_CalculateIfcSeqMap);
	ALUnitTest_AddFunction("Mt_riCddSpiInit", Mt_riCddSpiInit);
	ALUnitTest_AddFunction("Mt_rpCddSpi_Cycle", Mt_rpCddSpi_Cycle);
#endif
	ALUnitTest_AddFunction("Mt_CddSpi_InitIfc_Deriv", Mt_CddSpi_InitIfc_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_DeInitIfc_Deriv", Mt_CddSpi_DeInitIfc_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_ConfigureTransfer_Deriv", Mt_CddSpi_ConfigureTransfer_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_IfcIdle_Deriv", Mt_CddSpi_IfcIdle_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_TransferComplete_Deriv", Mt_CddSpi_TransferComplete_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_TransferCompleteDMA_Deriv", Mt_CddSpi_TransferCompleteDMA_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_DmaStop_Deriv", Mt_CddSpi_DmaStop_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_GetCommandWord_Deriv", Mt_CddSpi_GetCommandWord_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_StartTransfer_Deriv", Mt_CddSpi_StartTransfer_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_RxEventTriggered_Deriv", Mt_CddSpi_RxEventTriggered_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_RxTriggerEventClear_Deriv", Mt_CddSpi_RxTriggerEventClear_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_TxFifoPut_Deriv", Mt_CddSpi_TxFifoPut_Deriv);
	ALUnitTest_AddFunction("Mt_CddSpi_RxFifoGet_Deriv", Mt_CddSpi_RxFifoGet_Deriv);

#if (CDDSPI_STATUS_FAULT == STD_ON)
	//ALUnitTest_AddFunction("Mt_CddSpi_StatusFault", Mt_CddSpi_StatusFault);
#endif
#endif
}
