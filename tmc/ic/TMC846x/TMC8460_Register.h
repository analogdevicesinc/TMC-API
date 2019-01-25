#ifndef TMC8460_REGISTER_H
#define TMC8460_REGISTER_H

	// ===== TMC8460 register set =====

	#define TMC8460_ENC_MODE                      0x0000
	#define TMC8460_ENC_STATUS                    0x0010
	#define TMC8460_ENC_X_W                       0x0020
	#define TMC8460_ENC_X_R                       0x0030
	#define TMC8460_ENC_CONST                     0x0040
	#define TMC8460_ENC_LATCH                     0x0050

	#define TMC8460_SPI_RX_DATA                   0x0060
	#define TMC8460_SPI_TX_DATA                   0x0070
	#define TMC8460_SPI_CONF                      0x0080
	#define TMC8460_SPI_STATUS                    0x0090
	#define TMC8460_SPI_LENGTH                    0x00A0
	#define TMC8460_SPI_TIME                      0x00B0

	#define TMC8460_SD_SR0                        0x00C0
	#define TMC8460_SD_SC0                        0x00D0
	#define TMC8460_SD_ST0                        0x00E0
	#define TMC8460_SD_SL0                        0x00F0
	#define TMC8460_SD_DLY0                       0x0100
	#define TMC8460_SD_CFG0                       0x0110

	#define TMC8460_PWM_MAXCNT                    0x0120
	#define TMC8460_PWM_CHOPMODE                  0x0130
	#define TMC8460_PWM_ALIGNMENT                 0x0140
	#define TMC8460_PWM_POLARITIES                0x0150
	#define TMC8460_PWM1                          0x0160
	#define TMC8460_PWM2                          0x0170
	#define TMC8460_PWM3                          0x0180
	#define TMC8460_PWM1_CNTRSHFT                 0x0190
	#define TMC8460_PWM2_CNTRSHFT                 0x01A0
	#define TMC8460_PWM3_CNTRSHFT                 0x01B0
	#define TMC8460_PULSE_A                       0x01C0
	#define TMC8460_PULSE_B                       0x01D0
	#define TMC8460_PULSE_LENGTH                  0x01E0
	#define TMC8460_BBM_H                         0x01F0
	#define TMC8460_BBM_L                         0x0200

	#define TMC8460_GPO_OUT_VAL                   0x0210
	#define TMC8460_GPI_IN_VAL                    0x0220
	#define TMC8460_GPIO_CONFIG                   0x0230

	#define TMC8460_MFCIO_IRQ_CFG                 0x0240
	#define TMC8460_MFCIO_IRQ_FLAGS               0x0250

	#define TMC8460_WD_TIME                       0x0260
	#define TMC8460_WD_CFG                        0x0270
	#define TMC8460_WD_OUT_MASK_POL               0x0280
	#define TMC8460_WD_OE_POL                     0x0290
	#define TMC8460_WD_IN_MASK_POL                0x02A0
	#define TMC8460_WD_MAX                        0x02B0

	#define TMC8460_AL_STATE_OVERRIDE             0x02C0

	#define TMC8460_MAPCFG_ENC_MODE               0x0580
	#define TMC8460_MAPCFG_ENC_STATUS             0x0581
	#define TMC8460_MAPCFG_ENC_X_W                0x0582
	#define TMC8460_MAPCFG_ENC_X_R                0x0583
	#define TMC8460_MAPCFG_ENC_CONST              0x0584
	#define TMC8460_MAPCFG_ENC_LATCH              0x0585
	#define TMC8460_MAPCFG_SPI_RX_DATA            0x0586
	#define TMC8460_MAPCFG_SPI_TX_DATA            0x0587
	#define TMC8460_MAPCFG_SPI_CONF               0x0588
	#define TMC8460_MAPCFG_SPI_STATUS             0x0589
	#define TMC8460_MAPCFG_SPI_LENGTH             0x058A
	#define TMC8460_MAPCFG_SPI_TIME               0x058B
	#define TMC8460_MAPCFG_SD_SR                  0x058C
	#define TMC8460_MAPCFG_SD_SC                  0x058D
	#define TMC8460_MAPCFG_SD_ST                  0x058E
	#define TMC8460_MAPCFG_SD_SL                  0x058F
	#define TMC8460_MAPCFG_SD_DLY                 0x0590
	#define TMC8460_MAPCFG_SD_CFG                 0x0591
	#define TMC8460_MAPCFG_PWM_MAXCNT             0x0592
	#define TMC8460_MAPCFG_PWM_CHOPMODE           0x0593
	#define TMC8460_MAPCFG_PWM_ALIGNMENT          0x0594
	#define TMC8460_MAPCFG_PWM_POLARITIES         0x0595
	#define TMC8460_MAPCFG_PWM_VALUE_1            0x0596
	#define TMC8460_MAPCFG_PWM_VALUE_2            0x0597
	#define TMC8460_MAPCFG_PWM_VALUE_3            0x0598
	#define TMC8460_MAPCFG_PWM_CNTRSHIFT_1        0x0599
	#define TMC8460_MAPCFG_PWM_CNTRSHIFT_2        0x059A
	#define TMC8460_MAPCFG_PWM_CNTRSHIFT_3        0x059B
	#define TMC8460_MAPCFG_PWM_PULSE_A            0x059C
	#define TMC8460_MAPCFG_PWM_PULSE_B            0x059D
	#define TMC8460_MAPCFG_PWM_PULSE_LENGTH       0x059E
	#define TMC8460_MAPCFG_PWM_BBM_H              0x059F
	#define TMC8460_MAPCFG_PWM_BBM_L              0x05A0
	#define TMC8460_MAPCFG_GPO_OUT_VAL            0x05A1
	#define TMC8460_MAPCFG_GPI_IN_VAL             0x05A2
	#define TMC8460_MAPCFG_GPIO_CONFIG            0x05A3
	#define TMC8460_MAPCFG_IRQ_CFG                0x05A4
	#define TMC8460_MAPCFG_IRQ_FLAGS              0x05A5
	#define TMC8460_MAPCFG_WD_TIME                0x05A6
	#define TMC8460_MAPCFG_WD_CFG                 0x05A7
	#define TMC8460_MAPCFG_WD_OUT_MASK_POL        0x05A8
	#define TMC8460_MAPCFG_WD_OE_POL              0x05A9
	#define TMC8460_MAPCFG_WD_IN_MASK_POL         0x05AA
	#define TMC8460_MAPCFG_WD_MAX                 0x05AB

	#define TMC8460_MAPCFG_ECAT_WRITE             0x80
	#define TMC8460_MAPCFG_TRIGGER_ALWAYS         0x0F
	#define TMC8460_MAPCFG_TRIGGER_SYNC0          0x01
	#define TMC8460_MAPCFG_TRIGGER_SYNC1          0x02
	#define TMC8460_MAPCFG_TRIGGER_LATCH0         0x03
	#define TMC8460_MAPCFG_TRIGGER_LATCH1         0x04
	#define TMC8460_MAPCFG_TRIGGER_SOF            0x05
	#define TMC8460_MAPCFG_TRIGGER_EOF            0x06
	#define TMC8460_MAPCFG_TRIGGER_PDI_CHIPSEL    0x07
	#define TMC8460_MAPCFG_TRIGGER_PDI_CHIPDESEL  0x08
	#define TMC8460_MAPCFG_TRIGGER_MFC_CHIPSEL    0x09
	#define TMC8460_MAPCFG_TRIGGER_MFC_CHIPDESEL  0x0A
	#define TMC8460_MAPCFG_TRIGGER_BEFORE         0x0B
	#define TMC8460_MAPCFG_TRIGGER_AFTER          0x0C
	#define TMC8460_MAPCFG_TRIGGER_PWM_ZERO       0x0D
	#define TMC8460_MAPCFG_TRIGGER_DATA_CHANGE    0x0E
	#define TMC8460_MAPCFG_TRIGGER_IMMEDIATELY    0x0F

	#define TMC8460_MEMADDR_ENC_MODE              0x4000
	#define TMC8460_MEMADDR_ENC_X_W               0x4004
	#define TMC8460_MEMADDR_ENC_CONST             0x4008
	#define TMC8460_MEMADDR_SPI_TX_DATA           0x400C
	#define TMC8460_MEMADDR_SPI_CONF              0x4014
	#define TMC8460_MEMADDR_SPI_LENGTH            0x4016
	#define TMC8460_MEMADDR_SPI_TIME              0x4017
	#define TMC8460_MEMADDR_SD_SR                 0x4018
	#define TMC8460_MEMADDR_SD_ST                 0x401C
	#define TMC8460_MEMADDR_SD_SL                 0x4020
	#define TMC8460_MEMADDR_SD_DLY                0x4022
	#define TMC8460_MEMADDR_SD_CFG                0x4024
	#define TMC8460_MEMADDR_PWM_MAXCNT            0x4026
	#define TMC8460_MEMADDR_PWM_CHOPMODE          0x4028
	#define TMC8460_MEMADDR_PWM_ALIGNMENT         0x402A
	#define TMC8460_MEMADDR_PWM_POLARITIES        0x402B
	#define TMC8460_MEMADDR_PWM_VALUE_1           0x402C
	#define TMC8460_MEMADDR_PWM_VALUE_2           0x402E
	#define TMC8460_MEMADDR_PWM_VALUE_3           0x4030
	#define TMC8460_MEMADDR_PWM_CNTRSHIFT_1       0x4032
	#define TMC8460_MEMADDR_PWM_CNTRSHIFT_2       0x4034
	#define TMC8460_MEMADDR_PWM_CNTRSHIFT_3       0x4036
	#define TMC8460_MEMADDR_PWM_PULSE_A           0x4038
	#define TMC8460_MEMADDR_PWM_PULSE_B           0x403A
	#define TMC8460_MEMADDR_PWM_PULSE_LENGTH      0x403C
	#define TMC8460_MEMADDR_PWM_BBM_H             0x403D
	#define TMC8460_MEMADDR_PWM_BBM_L             0x403E
	#define TMC8460_MEMADDR_GPO_OUT_VAL           0x4040
	#define TMC8460_MEMADDR_GPIO_CONFIG           0x4042
	#define TMC8460_MEMADDR_IRQ_CFG               0x4044
	#define TMC8460_MEMADDR_WD_TIME               0x4048
	#define TMC8460_MEMADDR_WD_CFG                0x404C
	#define TMC8460_MEMADDR_WD_OUT_MASK_POL       0x4050
	#define TMC8460_MEMADDR_WD_OE_POL             0x4058
	#define TMC8460_MEMADDR_WD_IN_MASK_POL        0x405C

	#define TMC8460_MEMADDR_ENC_STATUS            0x4800
	#define TMC8460_MEMADDR_ENC_X_R               0x4804
	#define TMC8460_MEMADDR_ENC_LATCH             0x4808
	#define TMC8460_MEMADDR_SPI_RX_DATA           0x480C
	#define TMC8460_MEMADDR_SPI_STATUS            0x4814
	#define TMC8460_MEMADDR_SD_SC                 0x4818
	#define TMC8460_MEMADDR_GPI_IN_VAL            0x481C
	#define TMC8460_MEMADDR_IRQ_FLAGS             0x481E
	#define TMC8460_MEMADDR_WD_MAX                0x4820

	#define TMC8460_SDCFG_DISABLE                 1
	#define TMC8460_SDCFG_CONTINOUS               2
	#define TMC8460_SDCFG_STEP_POL                4
	#define TMC8460_SDCFG_DIR_POL                 8
	#define TMC8460_SDCFG_COUNT_CLEAR             16
	#define TMC8460_SDCFG_TOGGLE                  32

	#define TMC8460_AL_OVR                        1

#endif /* TMC8460_REGISTER_H */
