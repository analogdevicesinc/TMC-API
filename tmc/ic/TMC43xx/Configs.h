/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC43XX_CONFIGS_H_
#define TMC_IC_TMC43XX_CONFIGS_H_

typedef struct
{
	uint8_t IRun;
	uint8_t IStandby;
	uint16_t SettingDelay;
	uint8_t BoostCurrent;
} TMotorConfig;

typedef struct
{
	uint8_t ClosedLoopMode;
	uint32_t GammaVMin;
	uint32_t GammaVAdd;
	uint8_t Gamma;
	uint16_t Beta;
	uint32_t Offset;
	uint8_t CurrentScalerMinimum;
	uint8_t CurrentScalerMaximum;
	uint8_t CurrentScalerStartUp;
	uint32_t UpscaleDelay;
	uint32_t DownscaleDelay;
	uint32_t CorrectionVelocityP;
	uint32_t CorrectionVelocityI;
	uint32_t CorrectionVelocityIClip;
	uint32_t CorrectionVelocityDClk;
	uint32_t CorrectionVelocityDClip;
	uint32_t PositionCorrectionP;
	uint32_t PositionCorrectionTolerance;
	uint32_t PositionWindow;
	uint8_t EncVMeanWait;
	uint8_t EncVMeanFilter;
	uint32_t EncVMeanInt;
	int8_t EncoderCorrectionYOffset;
} TClosedLoopConfig;

#endif /* TMC_IC_TMC43XX_CONFIGS_H_ */
