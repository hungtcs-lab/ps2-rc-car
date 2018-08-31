#ifndef __DEFINES_H__
#define __DEFINES_H__

#define PS2_DAT        13
#define PS2_CMD        11
#define PS2_SEL        10
#define PS2_CLK        12

#define MOTOR_1_I      5
#define MOTOR_1_O      6
#define MOTOR_2_I      5
#define MOTOR_2_O      6
#define MOTOR_3_I      5
#define MOTOR_3_O      6

// 电机震动
#define RUMBLE         true
// 是否读取模拟量
#define PRESSURES      false

// 停止状态
#define STATUS_STOPED         0
// 前进状态
#define STATUS_MOVE_ON        1
// 倒车状态
#define STATUS_BACKWARDS      2


#endif
