/*
  Copyright (c) 2016 Engimusing LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#if !defined(EFM32ZG108)
#error Incorrect Board Selected! Please select Engimusing EFM32ZG108 from the Tools->Board: menu. Or adjust the pins below to work with another DF11 engiumsing board.
#endif

#include "Arduino.h"

#define MLX92212_PIN    7
#define POWER_PIN       8

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(MLX92212_PIN, INPUT_PULLUP);

  delay(1000);
  Serial.printf("MLX92212 Example = %d\r\n",digitalRead(MLX92212_PIN));
  Serial1.printf("MLX92212 Example = %d\r\n",digitalRead(MLX92212_PIN));
}

void loop()
{
  static int on = HIGH;
  static int mlx = 1;

  digitalWrite(LED_BUILTIN, on);

  //Serial.printf("MLX = %d\r\n",digitalRead(MLX92212_PIN));

  if ((digitalRead(MLX92212_PIN) == 0) && (mlx == 1)) {
    mlx = 0;
    Serial.println("MLX92212 on");
    Serial1.println("MLX92212 on");
  } else if((digitalRead(MLX92212_PIN) == 1) && (mlx == 0)) {
    Serial.println("MLX92212 off");
    Serial1.println("MLX92212 off");
    mlx = 1;
  } 

  delay(200);
  on = (on) ? LOW : HIGH;  // on alternates between LOW and HIGH
}



