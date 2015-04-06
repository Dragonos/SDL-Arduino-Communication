
/*

	The MIT License (MIT)

	Copyright (c) 2015 Amine Ben Hassouna (https://github.com/Dragonos)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.

*/

#define BUTTON_UP     2
#define BUTTON_DOWN   3
#define BUTTON_RIGHT  4
#define BUTTON_LEFT   5

void setup() {                
    Serial.begin(9600);
    for(int i=2; i<6; i++)
      pinMode(i, INPUT);
}


void loop() {
  
  if(digitalRead(BUTTON_UP) == HIGH)
    Serial.print("up");
  else if(digitalRead(BUTTON_DOWN) == HIGH)
    Serial.print("down");
  else if(digitalRead(BUTTON_RIGHT) == HIGH)
    Serial.print("right");
  else if(digitalRead(BUTTON_LEFT) == HIGH)
    Serial.print("left");
  
  delay(10);
}
