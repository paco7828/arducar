#include <mcp_can.h>
#include <SPI.h>

const int CAN_CS_PIN = 10; // CS pin for MCP2515
MCP_CAN CAN(CAN_CS_PIN);

void setup() {
  Serial.begin(115200);
  while (CAN.begin(MCP_ANY, 500000, MCP_8MHZ) != CAN_OK) { // 500 kbps, 8MHz oscillator
    Serial.println("CAN bus initialization failed!");
    delay(100);
  }
  Serial.println("CAN bus initialized.");
}

void loop() {
  long unsigned int id;
  unsigned char len;
  unsigned char buf[8];

  if (CAN.checkReceive() == CAN_MSGAVAIL) {
    CAN.readMsgBuf(&id, &len, buf);
    Serial.print("ID: ");
    Serial.println(id, HEX);
    for (int i = 0; i < len; i++) {
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
