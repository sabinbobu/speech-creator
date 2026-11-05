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
/// \file  CddDma_Mac_Prep.h
///
/// \brief
///
//-----------------------------------------------------------------------------
#ifndef CDDDMA_CONCAT2
#define CDDDMA_CONCAT2(x, y)  x ## y
#endif

#ifndef CDDDMA_CONCAT
#define CDDDMA_CONCAT(x, y) CDDDMA_CONCAT2(x, y)
#endif

// DMA0
#ifdef CDDDMA_CONFIG_MACRO__BEGIN
#undef CDDDMA_CONFIG_MACRO__BEGIN
#endif
#ifdef CDDDMA_CONIG_DMA_CHANNEL
#undef CDDDMA_CONIG_DMA_CHANNEL
#endif
#ifdef CDDDMA_CONFIG_MACRO__END
#undef CDDDMA_CONFIG_MACRO__END
#endif