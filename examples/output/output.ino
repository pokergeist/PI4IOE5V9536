#include <PI4IOE5V9536.h>

PI4IOE5V9536 ioex;

uint8_t status;

void setup() {
    Serial.begin(115200);
    while (not Serial and millis() < 5e3);

    if ( (status = ioex.begin(IOX_LOW_ALL, IOX_OUT_ALL, IOX_ORIGINAL_ALL)) ) {
      Serial.println("ERROR: IOEXP begin() fault " + status);
      while (1) {
        delay(5e3);
      }
    }
}

void loop() {
    for (uint8_t i = 0; i < 4; ++i) {
        Serial.print("set port high: ");
        Serial.println(i);

        ioex.write(i, IOX_HIGH);
        Serial.println(ioex.read(), BIN);
        delay(500);
    }

    for (uint8_t i = 0; i < 4; ++i) {
        Serial.print("set port low: ");
        Serial.println(i);

        ioex.write(i, IOX_LOW);
        Serial.println(ioex.read(), BIN);
        delay(500);
    }
}
