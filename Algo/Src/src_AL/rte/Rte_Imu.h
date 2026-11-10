#ifndef RTE_IMU_H
#define RTE_IMU_H

#include "Std_Types.h"

typedef struct
{
    sint32 AccelX_mg;
    sint32 AccelY_mg;
    sint32 AccelZ_mg;
    sint32 GyroX_mdps;
    sint32 GyroY_mdps;
    sint32 GyroZ_mdps;
    sint32 Temp_cdeg; /* Temperature in 0.01 degC units. */
    uint16 SamplePeriodMs;
} Rte_ImuSampleType;

typedef struct
{
    sint16 Roll_cdeg;
    sint16 Pitch_cdeg;
    sint16 Yaw_cdeg;
    sint16 Temperature_cdeg;
} Rte_ImuAnglesType;

extern volatile Std_ReturnType Rte_ImuInitResult;

Std_ReturnType Rte_Read_ImuSensor_Sample(Rte_ImuSampleType* SamplePtr);
Std_ReturnType Rte_Call_ImuSensor_StartRead(void);
Std_ReturnType Rte_Call_ImuMotor_SetEnable(boolean Enable);
Std_ReturnType Rte_Call_ImuMotor_SetDutyPermille(uint16 DutyPermille);
Std_ReturnType Rte_Write_ImuAngles_Values(const Rte_ImuAnglesType* AnglesPtr);

#endif
