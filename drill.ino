float reference_distance = 150.0;
int angle_drill_limit = 20;

int distance_0;
int distance_1;
int distance_2;
int angle_sensor_degree;

float distance_drill;
float depth;
bool is_angle_out_of_limit;
int angle_led;

void setup() {
  Serial.begin(9600);
}

void loop() {

  distance_0 = getDistance(0);
  distance_1 = getDistance(1);
  distance_2 = getDistance(2);

  angle_sensor_degree = getAngleOfSensor();

  distance_drill = calculateDistanceDrill();

  if (checkInput())
  {
    Serial.print("Signal arrived for storing reference\n");
    reference_distance = distance_drill;
  }

  depth = calculateDepth();

  is_angle_out_of_limit = calculateDrillAngle();

  if (is_angle_out_of_limit) {
    angle_led = calculateLedAngle();
  }
  else {
    angle_led = 0;
  }
  
  generateOutput();

  delay(2000);

}

#pragma region Read_Inputs

int getDistance(int pin) {
  
  // TODO Read sensor
  //digitalRead(pin),BIN

  return random(100, 150);
}

int getAngleOfSensor() {

  // TODO Read sensor
  return 25;
}

bool checkInput() {

  // TODO Read button
  return (Serial.read() != -1); // Can be triggered by any input like pushing "Enter"
}

#pragma endregion

#pragma region Process_Inputs

float calculateDistanceDrill() {
  float angle_sensor_radian = (angle_sensor_degree * 71.0) / 4068.0; // Degree to radian conversion
  return cos(angle_sensor_radian) * (distance_0 + distance_1 + distance_2) / 3.0;
}

float calculateDepth() {
  if (reference_distance > distance_drill) {
    return reference_distance - distance_drill;
  }
  else {
    return 0.0; // Do not want to show negative values.
  }
}

int calculateLedAngle() {
  int angle = 0;
  if (getMinDistance() == distance_0)
  {
    int d_1 = distance_1 - distance_0;
    int d_2 = distance_2 - distance_0;
    angle = ((d_1 * 120) + (d_2 * 240)) / (d_1 + d_2);
  }
  else if (getMinDistance() == distance_1)
  {
    int d_0 = distance_0 - distance_1;
    int d_2 = distance_2 - distance_1;
    angle = ((d_0 * 360) + (d_2 * 240)) / (d_0 + d_2);
  }
  else
  {
    int d_0 = distance_0 - distance_2;
    int d_1 = distance_1 - distance_2;
    angle = ((d_0 * 0) + (d_1 * 120)) / (d_0 + d_1);
  }

  angle = angle + 60; // Offset
  if (angle >= 360) {
    angle = angle - 360;
  }

  return 360 - angle; // Need to show exactly the other side.
}

int getMinDistance() {
  if (distance_0 <= distance_1 && distance_0 <= distance_2)
  {
    return distance_0;
  }
  else if (distance_1 <= distance_0 && distance_1 <= distance_2)
  {
    return distance_1;
  }
  else
  {
    return distance_2;
  }
}

int getMaxDistance() {
  if (distance_0 >= distance_1 && distance_0 >= distance_2)
  {
    return distance_0;
  }
  else if (distance_1 >= distance_0 && distance_1 >= distance_2)
  {
    return distance_1;
  }
  else
  {
    return distance_2;
  }
}

bool calculateDrillAngle() {
  return (getMaxDistance() - getMinDistance()) >= angle_drill_limit;
}

#pragma endregion

#pragma region Write_Outputs

void generateOutput() {

  // TODO Drive speaker and led-circle
  Serial.print("\n\n################################################\n");
  Serial.print("Reference_distance: ");
  Serial.print(reference_distance);
  Serial.print("  ---  ");
  Serial.print("distance_0: ");
  Serial.print(distance_0);
  Serial.print(",    ");
  Serial.print("distance_1: ");
  Serial.print(distance_1);
  Serial.print(",    ");
  Serial.print("distance_2: ");
  Serial.print(distance_2);
  Serial.print("    ##    ");
  Serial.print("Drill_distance: ");
  Serial.print(distance_drill);
  Serial.print(",    ");
  Serial.print("Depth: ");
  Serial.print(depth);
  Serial.print(",    ");
  Serial.print("Angle_led: ");
  Serial.print(angle_led);
  Serial.print("\n\n");

  if (is_angle_out_of_limit) {
    if (angle_led >= 345 || angle_led <= 15) {
      Serial.print("  O X O  \n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("  O O O  \n");
    }
    else if (angle_led >= 15 && angle_led <= 45) {
      Serial.print("  O O X  \n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("  O O O  \n");
    }
    else if (angle_led >= 45 && angle_led <= 75) {
      Serial.print("  O O O  \n");
      Serial.print("O       X\n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("  O O O  \n");
    }
    else if (angle_led >= 75 && angle_led <= 105) {
      Serial.print("  O O O  \n");
      Serial.print("O       O\n");
      Serial.print("O       X\n");
      Serial.print("O       O\n");
      Serial.print("  O O O  \n");
    }
    else if (angle_led >= 105 && angle_led <= 135) {
      Serial.print("  O O O  \n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("O       X\n");
      Serial.print("  O O O  \n");
    }
    else if (angle_led >= 135 && angle_led <= 165) {
      Serial.print("  O O O  \n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("  O O X  \n");
    }
    else if (angle_led >= 165 && angle_led <= 195) {
      Serial.print("  O O O  \n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("  O X O  \n");
    }
    else if (angle_led >= 195 && angle_led <= 225) {
      Serial.print("  O O O  \n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("  X O O  \n");
    }
    else if (angle_led >= 225 && angle_led <= 255) {
      Serial.print("  O O O  \n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("X       O\n");
      Serial.print("  O O O  \n");
    }
    else if (angle_led >= 255 && angle_led <= 285) {
      Serial.print("  O O O  \n");
      Serial.print("O       O\n");
      Serial.print("X       O\n");
      Serial.print("O       O\n");
      Serial.print("  O O O  \n");
    }
    else if (angle_led >= 285 && angle_led <= 315) {
      Serial.print("  O O O  \n");
      Serial.print("X       O\n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("  O O O  \n");
    }
    else if (angle_led >= 315 && angle_led <= 345) {
      Serial.print("  X O O  \n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("O       O\n");
      Serial.print("  O O O  \n");
    }
    Serial.print("\n\nBeeping: ON \n");
  }
  else {
    Serial.print("  O O O  \n");
    Serial.print("O       O\n");
    Serial.print("O       O\n");
    Serial.print("O       O\n");
    Serial.print("  O O O  \n");
    Serial.print("\n\nBeeping: OFF \n");
  }
}

#pragma endregion
