/**************************************************************************************************\
 *** 
 *** Simulink model       : Adb_Mxb3_TL
 *** TargetLink subsystem : Adb_Mxb3_TL/ADBModel
 *** Codefile             : udt_a.h
 *** Language             : C
 ***
 *** Generation date: 2025-06-30 23:08:35
 ***
 *** TargetLink version      : 23.1p2 from 23-May-2024
 *** Code generator version  : Build Id 23.1.0.24 from 2024-05-16 17:28:10
\**************************************************************************************************/

#ifndef UDT_A_H
#define UDT_A_H

typedef enum eCamObjectType_tag {
   ECAMOBJECTTYPE_OT_NO_OBJECT = 0, 
   ECAMOBJECTTYPE_OT_ONCOMING = 1, 
   ECAMOBJECTTYPE_OT_PRECEDING = 2, 
   ECAMOBJECTTYPE_OT_TRAFFIC_SIGN = 3, 
   ECAMOBJECTTYPE_OT_STREET_LIGHT = 4, 
   ECAMOBJECTTYPE_OT_UNKNOWN = 15 
} eCamObjectType; /* Description: Enumeration type derived from Simulink type eCamObjectType */

#endif /* UDT_A_H */
/*------------------------------------------------------------------------------------------------*\
  END OF FILE
\*------------------------------------------------------------------------------------------------*/
