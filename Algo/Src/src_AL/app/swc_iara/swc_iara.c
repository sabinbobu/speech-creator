#include "swc_iara.h"

#include "iara_lib.h"
#include "Rte_Iara.h"

#define SWC_IARA_ACCEL_Q22_NUMERATOR 411304L
#define SWC_IARA_ACCEL_Q22_DENOMINATOR 10L
#define SWC_IARA_GYRO_Q22_NUMERATOR 73256L
#define SWC_IARA_GYRO_Q22_DENOMINATOR 1000L
#define SWC_IARA_RAD_Q28_TO_CDEG_NUMERATOR 18000L
#define SWC_IARA_RAD_Q28_TO_CDEG_DENOMINATOR 843314857L
#define SWC_IARA_FILTERED_PITCH_MIN_CDEG (-18000L)
#define SWC_IARA_FILTERED_PITCH_MAX_CDEG 18000L

static uint8 SwcIara_CycleDivider;
static uint8 SwcIara_ImuSequenceCounter;
static boolean SwcIara_ResetNvmOnNextCycle;

static sint32 SwcIara_ConvertAccelMgToQ22(sint32 Accel_mg)
{
    return (sint32)(((sint64)Accel_mg * SWC_IARA_ACCEL_Q22_NUMERATOR) /
                    SWC_IARA_ACCEL_Q22_DENOMINATOR);
}

static sint32 SwcIara_ConvertGyroMdpsToQ22(sint32 Gyro_mdps)
{
    return (sint32)(((sint64)Gyro_mdps * SWC_IARA_GYRO_Q22_NUMERATOR) /
                    SWC_IARA_GYRO_Q22_DENOMINATOR);
}

static sint32 SwcIara_ConvertPitchRadQ28ToCdeg(sint32 Pitch_radQ28)
{
    sint64 ScaledPitch;

    ScaledPitch = (sint64)Pitch_radQ28 * SWC_IARA_RAD_Q28_TO_CDEG_NUMERATOR;
    if (ScaledPitch >= 0)
    {
        ScaledPitch += SWC_IARA_RAD_Q28_TO_CDEG_DENOMINATOR / 2L;
    }
    else
    {
        ScaledPitch -= SWC_IARA_RAD_Q28_TO_CDEG_DENOMINATOR / 2L;
    }

    return (sint32)(ScaledPitch / SWC_IARA_RAD_Q28_TO_CDEG_DENOMINATOR);
}

static sint16 SwcIara_ClampFilteredPitchCdeg(sint32 Pitch_cdeg)
{
    if (Pitch_cdeg > SWC_IARA_FILTERED_PITCH_MAX_CDEG)
    {
        return (sint16)SWC_IARA_FILTERED_PITCH_MAX_CDEG;
    }

    if (Pitch_cdeg < SWC_IARA_FILTERED_PITCH_MIN_CDEG)
    {
        return (sint16)SWC_IARA_FILTERED_PITCH_MIN_CDEG;
    }

    return (sint16)Pitch_cdeg;
}

void swc_iara_init(void)
{
    SwcIara_CycleDivider = 0u;
    SwcIara_ImuSequenceCounter = 0u;
    SwcIara_ResetNvmOnNextCycle = TRUE;

    IARA_TL_U.ActivateIARA_b = TRUE;
    IARA_TL_U.ResetNVMToDefault_b = FALSE;
    IARA_TL_U.RefAngularVelocityZ_rads = 0;
    IARA_TL_U.WhlSpeed_RearLeft_ms = 0;
    IARA_TL_U.WhlSpeed_RearRight_ms = 0;
    IARA_TL_U.IMUTemperature_C = 0;
    IARA_TL_U.AnyDoorOpen_b = FALSE;
    IARA_TL_U.GearState_en = Iara_GearForward;
    IARA_TL_U.BreakState_en = Iara_BrakeReleased;
    IARA_TL_U.ParkBreakState_en = Iara_BrakeReleased;
    IARA_TL_U.CANSignalsStatus_en = Iara_SignalValid;
    IARA_TL_U.IsMountingSideLeft_b = TRUE;
    IARA_TL_U.LearningActive_b = TRUE;
    IARA_TL_U.SelfCalibrationCommand_en = Iara_SelfCalibNoCommand;
    (void)Rte_Write_Iara_TargetPitch(0);
}

void swc_iara_MainFunction(void)
{
    Rte_IaraImuSampleType Sample;
    sint32 Pitch_cdeg;

    SwcIara_CycleDivider++;
    if (SwcIara_CycleDivider < 2u)
    {
        return;
    }
    SwcIara_CycleDivider = 0u;

    if (Rte_Read_Iara_ImuSample(&Sample) != E_OK)
    {
        return;
    }

    IARA_TL_U.ActivateIARA_b = TRUE;
    IARA_TL_U.ResetNVMToDefault_b = SwcIara_ResetNvmOnNextCycle;
    SwcIara_ResetNvmOnNextCycle = FALSE;
    IARA_TL_U.IMUAccelerometer_ms2[0] = SwcIara_ConvertAccelMgToQ22(Sample.AccelX_mg);
    IARA_TL_U.IMUAccelerometer_ms2[1] = SwcIara_ConvertAccelMgToQ22(Sample.AccelY_mg);
    IARA_TL_U.IMUAccelerometer_ms2[2] = SwcIara_ConvertAccelMgToQ22(Sample.AccelZ_mg);
    IARA_TL_U.IMUGyroscope_rads[0] = SwcIara_ConvertGyroMdpsToQ22(Sample.GyroX_mdps);
    IARA_TL_U.IMUGyroscope_rads[1] = SwcIara_ConvertGyroMdpsToQ22(Sample.GyroY_mdps);
    IARA_TL_U.IMUGyroscope_rads[2] = SwcIara_ConvertGyroMdpsToQ22(Sample.GyroZ_mdps);
    SwcIara_ImuSequenceCounter++;
    IARA_TL_U.IMUSequenceCounter = SwcIara_ImuSequenceCounter;

    IARA_Main();
    Pitch_cdeg = SwcIara_ConvertPitchRadQ28ToCdeg(IARA_TL_Y.IARAPitch_rad);
    (void)Rte_Write_Iara_TargetPitch(Pitch_cdeg);
    (void)Rte_Write_Iara_FilteredPitch(SwcIara_ClampFilteredPitchCdeg(Pitch_cdeg));
}
