#ifndef TMC8462_REGISTER_H
#define TMC8462_REGISTER_H

	// ===== TMC8462 register set =====

	// SPI register addresses
	#define TMC8462_ENC_MODE                0x0000
	#define TMC8462_ENC_STATUS              0x0010
	#define TMC8462_ENC_X_W                 0x0020
	#define TMC8462_ENC_X_R                 0x0030
	#define TMC8462_ENC_CONST               0x0040
	#define TMC8462_ENC_LATCH               0x0050

	#define TMC8462_SPI_RX_DATA             0x0060
	#define TMC8462_SPI_TX_DATA             0x0070
	#define TMC8462_SPI_CONF                0x0080
	#define TMC8462_SPI_STATUS              0x0090
	#define TMC8462_SPI_LENGTH              0x00A0
	#define TMC8462_SPI_TIME                0x00B0

	#define TMC8462_IIC_TIMEBASE            0x00C0
	#define TMC8462_IIC_CONTROL             0x00D0
	#define TMC8462_IIC_STATUS              0x00E0
	#define TMC8462_IIC_ADDRESS             0x00F0
	#define TMC8462_IIC_DATA_R              0x0100
	#define TMC8462_IIC_DATA_W              0x0110

	#define TMC8462_SD_SR0                  0x0120
	#define TMC8462_SD_SR1                  0x0130
	#define TMC8462_SD_SR2                  0x0140
	#define TMC8462_SD_SC0                  0x0150
	#define TMC8462_SD_SC1                  0x0160
	#define TMC8462_SD_SC2                  0x0170
	#define TMC8462_SD_ST0                  0x0180
	#define TMC8462_SD_ST1                  0x0190
	#define TMC8462_SD_ST2                  0x01A0
	#define TMC8462_SD_CMP0                 0x01B0
	#define TMC8462_SD_CMP1                 0x01C0
	#define TMC8462_SD_CMP2                 0x01D0
	#define TMC8462_SD_NEXTSR0              0x01E0
	#define TMC8462_SD_NEXTSR1              0x01F0
	#define TMC8462_SD_NEXTSR2              0x0200
	#define TMC8462_SD_SL                   0x0210
	#define TMC8462_SD_DLY                  0x0220
	#define TMC8462_SD_CFG                  0x0230

	#define TMC8462_PWM_CFG                 0x0240
	#define TMC8462_PWM1                    0x0250
	#define TMC8462_PWM2                    0x0260
	#define TMC8462_PWM3                    0x0270
	#define TMC8462_PWM4                    0x0280
	#define TMC8462_PWM1_CNTRSHFT           0x0290
	#define TMC8462_PWM2_CNTRSHFT           0x02A0
	#define TMC8462_PWM3_CNTRSHFT           0x02B0
	#define TMC8462_PWM4_CNTRSHFT           0x02C0
	#define TMC8462_PULSE_B_PULSE_A         0x02D0
	#define TMC8462_PULSE_LENGTH            0x02E0

	#define TMC8462_GPO                     0x02F0
	#define TMC8462_GPI                     0x0300
	#define TMC8462_GPIO_CONFIG             0x0310

	#define TMC8462_DAC_VAL                 0x0320

	#define TMC8462_MFCIO_IRQ_CFG           0x0330
	#define TMC8462_MFCIO_IRQ_FLAGS         0x0340

	#define TMC8462_WD_TIME                 0x0350
	#define TMC8462_WD_CFG                  0x0360
	#define TMC8462_WD_OUT_MASK_POL         0x0370
	#define TMC8462_WD_OE_POL               0x0380
	#define TMC8462_WD_IN_MASK_POL          0x0390
	#define TMC8462_WD_MAX                  0x03A0

	#define TMC8462_HV_STATUS               0x03B0

	#define TMC8462_SYNC_EVT_COUNTER        0x03F0

	#define TMC8462_HVIO_CFG                0x0400
	#define TMC8462_SWREG_CONF              0x0410
	#define TMC8462_AL_OVERRIDE             0x0420
	#define TMC8462_TEST_BIST               0x03C0
	#define TMC8462_TEST_ON_CFG             0x03C0

    // ESC RAM-Addresses
	#define TMC8462_ESC_CFG_MFCIO_0         0x0580
	#define TMC8462_ESC_CFG_MFCIO_1         0x0581
	#define TMC8462_ESC_CFG_MFCIO_2         0x0582
	#define TMC8462_ESC_CFG_MFCIO_3         0x0583
	#define TMC8462_ESC_CFG_MFCIO_4         0x0584
	#define TMC8462_ESC_CFG_MFCIO_5         0x0585
	#define TMC8462_ESC_CFG_MFCIO_6         0x0586
	#define TMC8462_ESC_CFG_MFCIO_7         0x0587
	#define TMC8462_ESC_CFG_MFCIO_8         0x0588
	#define TMC8462_ESC_CFG_MFCIO_9         0x0589
	#define TMC8462_ESC_CFG_MFCIO_10        0x058A
	#define TMC8462_ESC_CFG_MFCIO_11        0x058B
	#define TMC8462_ESC_CFG_MFCIO_12        0x058C
	#define TMC8462_ESC_CFG_MFCIO_13        0x058D
	#define TMC8462_ESC_CFG_MFCIO_14        0x058E
	#define TMC8462_ESC_CFG_MFCIO_15        0x058F

	#define TMC8462_ESC_CFG_MFCIO_HV_0      0x0590
	#define TMC8462_ESC_CFG_MFCIO_HV_1      0x0591
	#define TMC8462_ESC_CFG_MFCIO_HV_2      0x0592
	#define TMC8462_ESC_CFG_MFCIO_HV_3      0x0593
	#define TMC8462_ESC_CFG_MFCIO_HV_4      0x0594
	#define TMC8462_ESC_CFG_MFCIO_HV_5      0x0595
	#define TMC8462_ESC_CFG_MFCIO_HV_6      0x0596
	#define TMC8462_ESC_CFG_MFCIO_HV_7      0x0597

	#define TMC8462_ESC_CFG_HVIO_SLOPE      0x0598
	#define TMC8462_ESC_CFG_HVIO_WEAK_H     0x0599
	#define TMC8462_ESC_CFG_HVIO_WEAK_L     0x059A
	#define TMC8462_ESC_CFG_HVIO_DIFF_EN    0x059B
	#define TMC8462_ESC_CFG_SWREG_33        0x059C
	#define TMC8462_ESC_CFG_SWREG_VOUT      0x059D

	#define TMC8462_ESC_CFG_MEM_BLOCK0      0x059E
	#define TMC8462_ESC_CFG_MEM_BLOCK1      0x05A0

	#define TMC8462_ESC_ENC_MODE            0x05A2
	#define TMC8462_ESC_ENC_STATUS          0x05A3
	#define TMC8462_ESC_ENC_X_W             0x05A4
	#define TMC8462_ESC_ENC_X_R             0x05A5
	#define TMC8462_ESC_ENC_CONST           0x05A6
	#define TMC8462_ESC_ENC_LATCH           0x05A7

	#define TMC8462_ESC_SPI_RX_DATA         0x05A8
	#define TMC8462_ESC_SPI_TX_DATA         0x05A9
	#define TMC8462_ESC_SPI_CONF            0x05AA
	#define TMC8462_ESC_SPI_STATUS          0x05AB
	#define TMC8462_ESC_SPI_LENGTH          0x05AC
	#define TMC8462_ESC_SPI_TIME            0x05AD

	#define TMC8462_ESC_IIC_TIMEBASE        0x05AE
	#define TMC8462_ESC_IIC_CONTROL         0x05AF
	#define TMC8462_ESC_IIC_STATUS          0x05B0
	#define TMC8462_ESC_IIC_ADDRESS         0x05B1
	#define TMC8462_ESC_IIC_DATA_R          0x05B2
	#define TMC8462_ESC_IIC_DATA_W          0x05B3

	#define TMC8462_ESC_SD_SR0              0x05B4
	#define TMC8462_ESC_SD_SR1              0x05B5
	#define TMC8462_ESC_SD_SR2              0x05B6
	#define TMC8462_ESC_SD_SC0              0x05B7
	#define TMC8462_ESC_SD_SC1              0x05B8
	#define TMC8462_ESC_SD_SC2              0x05B9
	#define TMC8462_ESC_SD_ST0              0x05BA
	#define TMC8462_ESC_SD_ST1              0x05BB
	#define TMC8462_ESC_SD_ST2              0x05BC
	#define TMC8462_ESC_SD_CMP0             0x05BD
	#define TMC8462_ESC_SD_CMP1             0x05BE
	#define TMC8462_ESC_SD_CMP2             0x05BF
	#define TMC8462_ESC_SD_NEXTSR0          0x05C0
	#define TMC8462_ESC_SD_NEXTSR1          0x05C1
	#define TMC8462_ESC_SD_NEXTSR2          0x05C2
	#define TMC8462_ESC_SD_SL               0x05C3
	#define TMC8462_ESC_SD_DLY              0x05C4
	#define TMC8462_ESC_SD_CFG              0x05C5

	#define TMC8462_ESC_PWM_CFG             0x05C6
	#define TMC8462_ESC_PWM1                0x05C7
	#define TMC8462_ESC_PWM2                0x05C8
	#define TMC8462_ESC_PWM3                0x05C9
	#define TMC8462_ESC_PWM4                0x05CA
	#define TMC8462_ESC_PWM1_CNTRSHFT       0x05CB
	#define TMC8462_ESC_PWM2_CNTRSHFT       0x05CC
	#define TMC8462_ESC_PWM3_CNTRSHFT       0x05CD
	#define TMC8462_ESC_PWM4_CNTRSHFT       0x05CE
	#define TMC8462_ESC_PULSE_B_PULSE_A     0x05CF
	#define TMC8462_ESC_PULSE_LENGTH        0x05D0

	#define TMC8462_GPO                     0x05D1
	#define TMC8462_GPI                     0x05D2
	#define TMC8462_GPIO_CONFIG             0x05D3

	#define TMC8462_DAC_VAL                 0x05D4

	#define TMC8462_MFCIO_IRQ_CFG           0x05D5
	#define TMC8462_MFCIO_IRQ_FLAGS         0x05D6

	#define TMC8462_WD_TIME                 0x05D7
	#define TMC8462_WD_CFG                  0x05D8
	#define TMC8462_WD_OUT_MASK_POL         0x05D9
	#define TMC8462_WD_OE_POL               0x05DA
	#define TMC8462_WD_IN_MASK_POL          0x05DB
	#define TMC8462_WD_MAX                  0x05DC

	#define TMC8462_HV_STATUS               0x05DD

	#define TMC8462_SYNC_EVT_COUNTER        0x05E1

	// Crossbar configuration
	#define TMC8462_MFCFG_INPUT             0
	#define TMC8462_MFCFG_LOW               1
	#define TMC8462_MFCFG_HIGH              2
	#define TMC8462_MFCFG_TRI               3
	#define TMC8462_MFCFG_ENCA_P            4
	#define TMC8462_MFCFG_ENCA_N            5
	#define TMC8462_MFCFG_ENCB_P            6
	#define TMC8462_MFCFG_ENCB_N            7
	#define TMC8462_MFCFG_ENCN_P            8
	#define TMC8462_MFCFG_ENCN_N            9
	#define TMC8462_MFCFG_SPI_SCK           10
	#define TMC8462_MFCFG_SPI_MOSI          11
	#define TMC8462_MFCFG_SPI_MISO          12
	#define TMC8462_MFCFG_SPI_CSN0          13
	#define TMC8462_MFCFG_SPI_CSN1          14
	#define TMC8462_MFCFG_SPI_CSN2          15
	#define TMC8462_MFCFG_SPI_CSN3          16
	#define TMC8462_MFCFG_IIC_SCL           17
	#define TMC8462_MFCFG_IIC_SDA           18
	#define TMC8462_MFCFG_SD_STEP0          19
	#define TMC8462_MFCFG_SD_DIR0           20
	#define TMC8462_MFCFG_SD_STEP1          21
	#define TMC8462_MFCFG_SD_DIR1           22
	#define TMC8462_MFCFG_SD_STEP2          23
	#define TMC8462_MFCFG_SD_DIR2           24
	#define TMC8462_MFCFG_SD_STEP0_N        25
	#define TMC8462_MFCFG_SD_DIR0_N         26
	#define TMC8462_MFCFG_SD_STEP1_N        27
	#define TMC8462_MFCFG_SD_DIR1_N         28
	#define TMC8462_MFCFG_SD_STEP2_N        29
	#define TMC8462_MFCFG_SD_DIR2_N         30
	#define TMC8462_MFCFG_PWM_HS0           31
	#define TMC8462_MFCFG_PWM_LS0           32
	#define TMC8462_MFCFG_PWM_HS1           33
	#define TMC8462_MFCFG_PWM_LS1           34
	#define TMC8462_MFCFG_PWM_HS2           35
	#define TMC8462_MFCFG_PWM_LS2           36
	#define TMC8462_MFCFG_PWM_HS3           37
	#define TMC8462_MFCFG_PWM_LS3           38
	#define TMC8462_MFCFG_GPI0              39
	#define TMC8462_MFCFG_GPI1              40
	#define TMC8462_MFCFG_GPI2              41
	#define TMC8462_MFCFG_GPI3              42
	#define TMC8462_MFCFG_GPI4              43
	#define TMC8462_MFCFG_GPI5              44
	#define TMC8462_MFCFG_GPI6              45
	#define TMC8462_MFCFG_GPI7              46
	#define TMC8462_MFCFG_GPI8              47
	#define TMC8462_MFCFG_GPI9              48
	#define TMC8462_MFCFG_GPI10             49
	#define TMC8462_MFCFG_GPI11             50
	#define TMC8462_MFCFG_GPI12             51
	#define TMC8462_MFCFG_GPI13             52
	#define TMC8462_MFCFG_GPI14             53
	#define TMC8462_MFCFG_GPI15             54
	#define TMC8462_MFCFG_GPO0              55
	#define TMC8462_MFCFG_GPO1              56
	#define TMC8462_MFCFG_GPO2              57
	#define TMC8462_MFCFG_GPO3              58
	#define TMC8462_MFCFG_GPO4              59
	#define TMC8462_MFCFG_GPO5              60
	#define TMC8462_MFCFG_GPO6              61
	#define TMC8462_MFCFG_GPO7              62
	#define TMC8462_MFCFG_GPO8              63
	#define TMC8462_MFCFG_GPO9              64
	#define TMC8462_MFCFG_GPO10             65
	#define TMC8462_MFCFG_GPO11             66
	#define TMC8462_MFCFG_GPO12             67
	#define TMC8462_MFCFG_GPO13             68
	#define TMC8462_MFCFG_GPO14             69
	#define TMC8462_MFCFG_GPO15             70
	#define TMC8462_MFCFG_DAC0              71
	#define TMC8462_MFCFG_PWM_PULSE_A       72
	#define TMC8462_MFCFG_PWM_PULSE_CENTER  73
	#define TMC8462_MFCFG_PWM_PULSE_B       74
	#define TMC8462_MFCFG_PWM_PULSE_AB      75
	#define TMC8462_MFCFG_PWM_PULSE_ZERO    76

#endif /* TMC8462_REGISTER_H */
