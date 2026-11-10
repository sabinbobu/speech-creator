#include "Rte_Imu.h"
#include "swc_imu.h"

static const sint16 SwcImu_AtanCdeg[15] =
{
    4500, 2657, 1404, 713, 358, 179, 90, 45, 22, 11, 6, 3, 1, 1, 0
};

static uint8 SwcImu_CycleCount;
static sint32 SwcImu_YawCdeg;
static sint32 SwcImu_YawRemainder;
static volatile Std_ReturnType SwcImu_MotorOutputStatus;

static uint16 SwcImu_PitchToDutyPermille(sint16 Pitch_cdeg)
{
    sint32 Pitch = Pitch_cdeg;

    if (Pitch <= -5000)
    {
        return 0u;
    }
    if (Pitch >= 5000)
    {
        return 1000u;
    }

    return (uint16)((Pitch + 5000) / 10);
}

static void SwcImu_UpdateMotorOutput(sint16 Pitch_cdeg)
{
    uint16 DutyPermille = SwcImu_PitchToDutyPermille(Pitch_cdeg);

    SwcImu_MotorOutputStatus = Rte_Call_ImuMotor_SetDutyPermille(DutyPermille);
    if (SwcImu_MotorOutputStatus == E_OK)
    {
        SwcImu_MotorOutputStatus = Rte_Call_ImuMotor_SetEnable(TRUE);
    }

    if (SwcImu_MotorOutputStatus != E_OK)
    {
        (void)Rte_Call_ImuMotor_SetEnable(FALSE);
    }
}

static uint32 SwcImu_IntegerSqrt(uint32 Value)
{
    uint32 Result = 0u;
    uint32 Bit = 1uL << 30u;

    while (Bit > Value)
    {
        Bit >>= 2u;
    }

    while (Bit != 0u)
    {
        if (Value >= (Result + Bit))
        {
            Value -= Result + Bit;
            Result = (Result >> 1u) + Bit;
        }
        else
        {
            Result >>= 1u;
        }
        Bit >>= 2u;
    }

    return Result;
}

static sint16 SwcImu_Atan2Cdeg(sint32 Y, sint32 X)
{
    sint32 Angle = 0;
    uint8 Index;

    if (X == 0)
    {
        if (Y > 0)
        {
            return 9000;
        }
        if (Y < 0)
        {
            return -9000;
        }
        return 0;
    }

    if (X < 0)
    {
        Angle = (Y >= 0) ? 18000 : -18000;
        X = -X;
        Y = -Y;
    }

    for (Index = 0u; Index < 15u; Index++)
    {
        sint32 YShift = Y / (sint32)(1uL << Index);
        sint32 OldX = X;

        if (Y > 0)
        {
            X += YShift;
            Y -= OldX / (sint32)(1uL << Index);
            Angle += SwcImu_AtanCdeg[Index];
        }
        else if (Y < 0)
        {
            X -= YShift;
            Y += OldX / (sint32)(1uL << Index);
            Angle -= SwcImu_AtanCdeg[Index];
        }
    }

    if (Angle > 18000)
    {
        Angle = 18000;
    }
    else if (Angle < -18000)
    {
        Angle = -18000;
    }

    return (sint16)Angle;
}

void swc_imu_init(void)
{
    SwcImu_CycleCount = 0u;
    SwcImu_YawCdeg = 0;
    SwcImu_YawRemainder = 0;
    SwcImu_MotorOutputStatus = Rte_Call_ImuMotor_SetEnable(FALSE);
    if (Rte_Call_ImuMotor_SetDutyPermille(0u) != E_OK)
    {
        SwcImu_MotorOutputStatus = E_NOT_OK;
    }
}

void swc_imu_MainFunction(void)
{
    Rte_ImuSampleType Sample;
    Rte_ImuAnglesType Angles;
    uint32 AccelY2;
    uint32 AccelZ2;
    uint32 HorizontalAcceleration;
    sint32 YawIncrement;

    SwcImu_CycleCount++;
    if (SwcImu_CycleCount < 2u)
    {
        return;
    }
    SwcImu_CycleCount = 0u;

    if (Rte_ImuInitResult != E_OK)
    {
        return;
    }

    if (Rte_Read_ImuSensor_Sample(&Sample) == E_OK)
    {
        AccelY2 = (uint32)(Sample.AccelY_mg * Sample.AccelY_mg);
        AccelZ2 = (uint32)(Sample.AccelZ_mg * Sample.AccelZ_mg);
        HorizontalAcceleration = SwcImu_IntegerSqrt(AccelY2 + AccelZ2);

        Angles.Roll_cdeg = SwcImu_Atan2Cdeg(Sample.AccelY_mg, Sample.AccelZ_mg);
        Angles.Pitch_cdeg = SwcImu_Atan2Cdeg(-Sample.AccelX_mg,
                                             (sint32)HorizontalAcceleration);

        SwcImu_YawRemainder += Sample.GyroZ_mdps * (sint32)Sample.SamplePeriodMs;
        YawIncrement = SwcImu_YawRemainder / 10000;
        SwcImu_YawRemainder %= 10000;
        SwcImu_YawCdeg += YawIncrement;

        while (SwcImu_YawCdeg > 18000)
        {
            SwcImu_YawCdeg -= 36000;
        }
        while (SwcImu_YawCdeg < -18000)
        {
            SwcImu_YawCdeg += 36000;
        }
        Angles.Yaw_cdeg = (sint16)SwcImu_YawCdeg;
        Angles.Temperature_cdeg = (sint16)Sample.Temp_cdeg;

        SwcImu_UpdateMotorOutput(Angles.Pitch_cdeg);
        (void)Rte_Write_ImuAngles_Values(&Angles);
    }

    (void)Rte_Call_ImuSensor_StartRead();
}
