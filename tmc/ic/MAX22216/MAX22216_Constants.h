/*******************************************************************************
* Copyright © 2020 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_API_DEV_TMC_IC_MAX22216_MAX22216_CONSTANTS_H_
#define TMC_API_DEV_TMC_IC_MAX22216_MAX22216_CONSTANTS_H_

#define MAX22216_SYNC_BYTE       0x55
#define MAX22216_MASTER_ADDRESS  0xFF

// motion modes
#define MAX22216_MOTION_MODE_STOPPED    0
#define MAX22216_MOTION_MODE_TORQUE     1
#define MAX22216_MOTION_MODE_VELOCITY   2
#define MAX22216_MOTION_MODE_POSITION   3
#define MAX22216_MOTION_MODE_UQ_UD_EXT  8

// PHI_E selections
#define MAX22216_PHI_E_EXTERNAL   1
#define MAX22216_PHI_E_OPEN_LOOP  2
#define MAX22216_PHI_E_ABN        3
#define MAX22216_PHI_E_HALL       5
#define MAX22216_PHI_E_AENC       6
#define MAX22216_PHI_A_AENC       7

#define MAX22216_STATE_NOTHING_TO_DO    0
#define MAX22216_STATE_START_INIT       1
#define MAX22216_STATE_WAIT_INIT_TIME   2
#define MAX22216_STATE_ESTIMATE_OFFSET  3

#define MAX22216_CHIPINFO_ADDR_SI_TYPE     0
#define MAX22216_CHIPINFO_ADDR_SI_VERSION  1
#define MAX22216_CHIPINFO_ADDR_SI_DATE     2
#define MAX22216_CHIPINFO_ADDR_SI_TIME     3
#define MAX22216_CHIPINFO_ADDR_SI_VARIANT  4
#define MAX22216_CHIPINFO_ADDR_SI_BUILD    5

#endif /* TMC_API_DEV_TMC_IC_MAX22216_MAX22216_CONSTANTS_H_ */
