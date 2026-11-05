//*****************************************************************************
// (C) Automotive Lighting Reutlingen GmbH
//     Tuebinger Strasse 123, 72762 Reutlingen, Germany
//
// Automotive Lighting Reutlingen GmbH owns all the rights to this work.
// This work shall not be copied, reproduced, used, modified, transferred
// or its information shall not be disclosed without the prior written
// authorization of Automotive Lighting Reutlingen GmbH.
//*****************************************************************************
/// ---------------------------------------------------------------------------
///
///  \file    ClLrRelation1.h
///
///  \author  Bernd Dreier  Bernd.Dreier@al-lighting.com
///           ported by     VORNICU Tony - EEG-PM4 (F63906B)
///                         mailTo:tony.vornicu@al-lighting.com
///
///  \owner   Bernd Dreier   Bernd.Dreier@al-lighting.com
///
///  \date    26.06.2003
///
///  \brief   left | right relation  
///
///  \descr   left | right relation 
///
/// ---------------------------------------------------------------------------
#ifndef CL_LR_RELATION_2021_11_02_H_
#define CL_LR_RELATION_2021_11_02_H_

//=============================================================================
// includes
//=============================================================================
#include "Dbl_Types.h"

  #if ( CFG_TYP_CL_LR06 != CFG_Cl_None )

    #if  ( CFG_OPT_CL & CFG_Cl_LR_RelationDev )
      /// depending on AFSHldDevParameter settings (EEPROM), the input swiveling angle is delegated to the left and right swiveling angles.
      void LrRelation( sint32, sint32*, sint32* );
      #define CL_LRRELATION(hla, pleft, pright )    LrRelation( hla, pleft, pright )

    #elif( CFG_OPT_CL & CFG_Cl_LR_Relation1 )
      /// alpha | alpha/2, linear 150 - 75 [0.1°]
      void LrRelation1( sint32, sint32*, sint32* );
      #ifndef CL_LRRELATION
        #define CL_LRRELATION(hla, pleft, pright )    LrRelation1( hla, pleft, pright )
      #endif
              
    #elif( CFG_OPT_CL & CFG_Cl_LR_Relation2 )
      /// alpha | alpha/2, adaptive 150 - 75 [0.1°]
      void LrRelation2( sint32, sint32*, sint32* );
      #ifndef CL_LRRELATION
        #define CL_LRRELATION(hla, pleft, pright )    LrRelation2( hla, pleft, pright )
      #endif

    #elif( CFG_OPT_CL & CFG_Cl_LR_Relation4 )
      /// alpha | alpha/3, adaptive 150 - 50 [0.1°]
      void LrRelation4( sint32, sint32*, sint32* );
      #ifndef CL_LRRELATION
        #define CL_LRRELATION(hla, pleft, pright )    LrRelation4( hla, pleft, pright )
      #endif

    #elif( CFG_OPT_CL & CFG_Cl_LR_Relation5 )
      /// alpha | alpha/3, linear 150 - 50 [0.1°]
      void LrRelation5( sint32, sint32*, sint32* );
      #ifndef CL_LRRELATION
        #define CL_LRRELATION(hla, pleft, pright )    LrRelation5( hla, pleft, pright )
      #endif

    #elif( CFG_OPT_CL & CFG_Cl_LR_Relation6 )
      /// alpha | 0, linear 150 - 75 [0.1°]
      void LrRelation6( sint32, sint32*, sint32* );
      #ifndef CL_LRRELATION
        #define CL_LRRELATION(hla, pleft, pright )    LrRelation6( hla, pleft, pright )
      #endif

    #elif ( CFG_OPT_CL & CFG_Cl_LR_RelationPrj )
      /// project dependent (implemented in project specific code parts)
      void LrRelationPrj( sint32, sint32*, sint32* );
      #ifndef CL_LRRELATION
        #define CL_LRRELATION(hla, pleft, pright )    LrRelationPrj( hla, pleft, pright )
      #endif

    #endif
  #endif // ( CFG_TYP_CL_LR06 != CFG_Cl_None )


#endif // CL_LR_RELATION_2021_11_02_H_
