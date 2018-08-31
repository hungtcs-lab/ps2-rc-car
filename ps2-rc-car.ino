#include <PS2X_lib.h>
#include "defines.h"

PS2X ps2x;

// 控制器震动强度
byte vibrate = 0;
// 运行状态
byte runningStatus = 0;
// 控制器类型
byte controllerType = 0;
// 控制器状态
byte controllerStatus = 0;

void setup() {
  Serial.begin(9600);

  // waiting for controller init
  delay(300);

  // read controller status
  controllerStatus = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, PRESSURES, RUMBLE);
  handleStatus(controllerStatus);

  // read controller type
  controllerType = ps2x.readType();
  printControllerType(controllerType);
}

void loop() {
  // no controller found
  if(controllerStatus == 1) {
    return;
  }

  ps2x.read_gamepad(false, vibrate);

  if(runningStatus == STATUS_STOPED) {
    // 按下R2前进
    if(ps2x.Button(PSB_R2)) {
      moveOn();
      runningStatus = STATUS_MOVE_ON;
      Serial.println("start move on");
    }
    // 按下L2倒车
    if(ps2x.Button(PSB_L2)) {
      backwards();
      runningStatus = STATUS_BACKWARDS;
      Serial.println("start backwards");
    }
  } else if(runningStatus == STATUS_MOVE_ON) {
    // 松开R2停止前进
    if(!ps2x.Button(PSB_R2)) {
      stop();
      runningStatus = STATUS_STOPED;
      Serial.println("stop move on");
    }
  } else if(runningStatus == STATUS_BACKWARDS) {
    // 松开L2停止倒车
    if(!ps2x.Button(PSB_L2)) {
      stop();
      runningStatus = STATUS_STOPED;
      Serial.println("stop backwards");
    }
  }

  // 转向按钮
  if(ps2x.ButtonPressed(PSB_CIRCLE)) {
    trunRight();
  } else if(ps2x.ButtonReleased(PSB_CIRCLE)) {
    trunStraight();
  } else if(ps2x.ButtonPressed(PSB_SQUARE)) {
    trunLeft();
  } else if(ps2x.ButtonReleased(PSB_SQUARE)) {
    trunStraight();
  }

  delay(50);
}

void handleStatus(int status) {
  if(status == 0) {
    Serial.println("found controller, configured successful");
  } else if(status == 1) {
     Serial.println("no controller found, check wiring");
  } else if(status == 2) {
    Serial.println("controller found but not accepting commands");
  } else if(status == 3) {
    Serial.println("controller refusing to enter pressures mode, may not support it");
  }
}

void printControllerType(byte type) {
  switch(type) {
    case 0: {
      Serial.print("Unknown Controller type found ");
      break;
    }
    case 1: {
      Serial.print("DualShock Controller found ");
      break;
    }
    case 2: {
      Serial.print("GuitarHero Controller found ");
      break;
    }
    case 3: {
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
    }
  }
}

void stop() {
  digitalWrite(MOTOR_1_I, HIGH);
  digitalWrite(MOTOR_1_O, HIGH);
}

void moveOn() {
  digitalWrite(MOTOR_1_I, LOW);
  digitalWrite(MOTOR_1_O, HIGH);
}

void backwards() {
  digitalWrite(MOTOR_1_I, HIGH);
  digitalWrite(MOTOR_1_O, LOW);
}

void trunStraight() {
  digitalWrite(MOTOR_2_I, LOW);
  digitalWrite(MOTOR_2_O, LOW);
}

void trunLeft() {
  digitalWrite(MOTOR_2_I, LOW);
  digitalWrite(MOTOR_2_O, HIGH);
}

void trunRight() {
  digitalWrite(MOTOR_2_I, HIGH);
  digitalWrite(MOTOR_2_O, LOW);
}
