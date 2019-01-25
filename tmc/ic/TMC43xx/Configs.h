/*
 * Configs.h
 *
 *  Created on: 18.07.2017
 *      Author: LK
 */

#ifndef TMC_IC_TMC43XX_CONFIGS_H_
#define TMC_IC_TMC43XX_CONFIGS_H_

typedef struct
{
	uint8 IRun;
	uint8 IStandby;
	uint16 SettingDelay;
	uint8 BoostCurrent;
} TMotorConfig;

typedef struct
{
	uint8 ClosedLoopMode;
	uint32 GammaVMin;
	uint32 GammaVAdd;
	uint8 Gamma;
	uint16 Beta;
	uint32 Offset;
	uint8 CurrentScalerMinimum;
	uint8 CurrentScalerMaximum;
	uint8 CurrentScalerStartUp;
	uint32 UpscaleDelay;
	uint32 DownscaleDelay;
	uint32 CorrectionVelocityP;
	uint32 CorrectionVelocityI;
	uint32 CorrectionVelocityIClip;
	uint32 CorrectionVelocityDClk;
	uint32 CorrectionVelocityDClip;
	uint32 PositionCorrectionP;
	uint32 PositionCorrectionTolerance;
	uint32 PositionWindow;
	uint8 EncVMeanWait;
	uint8 EncVMeanFilter;
	uint32 EncVMeanInt;
	int8 EncoderCorrectionYOffset;
} TClosedLoopConfig;

#endif /* TMC_IC_TMC43XX_CONFIGS_H_ */
