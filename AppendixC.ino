#include "IRremote.h"
#define POWER 0xa90
#define AIWA_RC_T501

IRsend irsend;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Ready");
}

void loop() {
    irsend.sendSony(POWER, 12); // Sony TV power code
}
