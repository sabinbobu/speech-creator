#ifndef RTE_IARA_H
#define RTE_IARA_H

#include "Std_Types.h"

typedef struct
{
    sint32 AccelX_mg;
    sint32 AccelY_mg;
    sint32 AccelZ_mg;
    sint32 GyroX_mdps;
    sint32 GyroY_mdps;
    sint32 GyroZ_mdps;
} Rte_IaraImuSampleType;

extern volatile sint32 Rte_Iara_TargetPitch_cdeg;

Std_ReturnType Rte_Read_Iara_ImuSample(Rte_IaraImuSampleType* SamplePtr);
Std_ReturnType Rte_Write_Iara_TargetPitch(sint32 TargetPitch_cdeg);
Std_ReturnType Rte_Write_Iara_FilteredPitch(sint16 FilteredPitch_cdeg);

#endif
