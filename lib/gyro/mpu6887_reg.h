#ifndef _MPU6887_REG_H_
#define _MPU6887_REG_H_


#define MPU6887_DEFAULT_ADDRESS   (0x69) // 1101001 (AD = 1)
#define MPU6887_DEVICE_ID         (0x2E)


/********* REGISTERS ADDRESS *************/
#define XG_OFFS_TC_H        0x04
#define XG_OFFS_TC_L        0x05
#define YG_OFFS_TC_H        0x07
#define YG_OFFS_TC_L        0x08
#define ZG_OFFS_TC_H        0x0A
#define ZG_OFFS_TC_L        0x0B

#define SELF_TEST_X_ACCEL   0x0D
#define SELF_TEST_Y_ACCEL   0x0E
#define SELF_TEST_Z_ACCEL   0x0F

#define XG_OFFS_USRH        0x13
#define XG_OFFS_USRL        0x14
#define YG_OFFS_USRH        0x15
#define YG_OFFS_USRL        0x16
#define ZG_OFFS_USRH        0x17
#define ZG_OFFS_USRL        0x18

#define SMPLRT_DI           0x19

#define CONFIG              0x1A
#define GYRO_CONFIG         0x1B
#define ACCEL_CONFIG        0x1C
#define ACCEL_CONFIG_2      0x1D   
#define LP_MODE_CFG         0x1E

#define ACCEL_WOM_X_THR     0x20
#define ACCEL_WOM_Y_THR     0x21
#define ACCEL_WOM_Z_THR     0x22
#define FIFO_EN             0x23

#define FSYNC_INT           0x36
#define INT_PIN_CFG         0x37
#define INT_ENABLE          0x38
#define FIFO_WM_INT_STATUS  0x39
#define INTSTATU            0x3A

#define ACCEL_XOUT_H        0x3B
#define ACCEL_XOUT_L        0x3C
#define ACCEL_YOUT_H        0x3D
#define ACCEL_YOUT_L        0x3E
#define ACCEL_ZOUT_H        0x3F
#define ACCEL_ZOUT_L        0x40
#define TEMP_OUT_H          0x41
#define TEMP_OUT_L          0x42
#define GYRO_XOUT_H         0x43
#define GYRO_XOUT_L         0x44
#define GYRO_YOUT_H         0x45
#define GYRO_YOUT_L         0x46
#define GYRO_ZOUT_H         0x47
#define GYRO_ZOUT_L         0x48

#define SELF_TEST_X_GYRO    0x50
#define SELF_TEST_Y_GYRO    0x51
#define SELF_TEST_Z_GYRO    0x52
#define E_ID0               0x53
#define E_ID1               0x54
#define E_ID2               0x55
#define E_ID3               0x56
#define E_ID4               0x57
#define E_ID5               0x58
#define E_ID6               0x59
#define FIFO_WM_TH1         0x60
#define FIFO_WM_TH2         0x61

#define SIGNAL_PATH_RESET   0x68
#define ACCEL_INTEL_CTRL    0x69
#define USER_CTRL           0x6A
#define PWR_MGMT_1          0x6B
#define PWR_MGMT_2          0x6C

#define I2C_IF              0x70
#define FIFO_COUNTH         0x72
#define FIFO_COUNTL         0x73
#define FIFO_R_W            0x74
#define WHO_AM_I            0x75

#define XA_OFFSET_H         0x77
#define XA_OFFSET_L         0x78
#define YA_OFFSET_H         0x7A
#define YA_OFFSET_L         0x7B
#define ZA_OFFSET_H         0x7D
#define ZA_OFFSET_L         0x7E

#endif /* _MPU6887_REG_H_ */