#include <Arduino.h>
// ---------- This is a testing code for MD02 temperature and humidity sensors, you may change the registers as per your need ------------
// In this example we use Serial2 ESP32, you may change to other serials or softwareserial
// UART pins
#define RS485_TX 17
#define RS485_RX 16
// MAX487 pins
#define DE 19
#define RE 18
// No.Parameters
#define PARAMS    2
#define REQ_FRAME 8
#define RES_FRAME 16
#define MODBUS_BAUD_RATE 9600

// Response bytes
uint8_t expectedBytes = 9; // 1(ID) + 1(Func) + 1(ByteCount) + 4(Data) + 2(CRC) = 9 bytes

// ---------- MAX487 MODES ----------
// Transmit mode
void enableTransmit()
{
  digitalWrite(RE, HIGH);
  digitalWrite(DE, HIGH);
}

// Receive mode
void enableReceive()
{
  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);
}

// Shutdown mode (LOW POWER)
void enableShutdown()
{
  digitalWrite(RE, HIGH);
  digitalWrite(DE, LOW);
}

// ---------- MODBUS CRC CALCULATION ----------
uint16_t calculateCRC(uint8_t *buffer, uint8_t length) 
{
  uint16_t crc = 0xFFFF;
  for (int pos = 0; pos < length; pos++) {
    crc ^= (uint16_t)buffer[pos];
    for (int i = 8; i != 0; i--) {
      if ((crc & 0x0001) != 0) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

void setup()
{
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  // Start in shutdown mode
  enableShutdown();

  Serial.begin(115200);
  Serial2.begin(MODBUS_BAUD_RATE, SERIAL_8N1, RS485_RX, RS485_TX);
}

void loop()
{
  uint16_t data[PARAMS];

  // Wake MAX487 before communication
  enableReceive();
  delay(5); // Stabilization time

  // ---------- CONSTRUCT MODBUS REQUEST ----------
  // Slave ID: 1, Function Code: 4 (Read Input Registers), Start Addr: 0x0001, Quantity: 2
  uint8_t requestFrame[REQ_FRAME] = {0x01, 0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00};
  
  // Calculate CRC for the first 6 bytes
  uint16_t crc = calculateCRC(requestFrame, 6);
  requestFrame[6] = crc & 0xFF;         // CRC Low Byte
  requestFrame[7] = (crc >> 8) & 0xFF;  // CRC High Byte

  // ---------- SEND REQUEST ----------
  enableTransmit();
  Serial2.write(requestFrame, 8);
  Serial2.flush(); // CRITICAL: Wait until all bytes are actually transmitted over UART
  enableReceive();

  // ---------- READ RESPONSE ----------
  uint8_t responseFrame[RES_FRAME];
  uint8_t bytesRead = 0;
  unsigned long startTime = millis();
  
  // Read with a timeout of 1000ms
  while ((millis() - startTime < 1000) && (bytesRead < expectedBytes)) {
    if (Serial2.available()) {
      responseFrame[bytesRead++] = Serial2.read();
    }
  }

  // ---------- PARSE AND VALIDATE ----------
  if (bytesRead == expectedBytes) 
  {
    // Verify CRC of the received frame (excluding the 2 CRC bytes at the end)
    uint16_t receivedCRC = responseFrame[7] | (responseFrame[8] << 8);
    uint16_t calculatedCRC = calculateCRC(responseFrame, 7);

    if (receivedCRC == calculatedCRC) 
    {
      // Verify Slave ID, Function Code, and Byte Count match expectations
      if (responseFrame[0] == 0x01 && responseFrame[1] == 0x04 && responseFrame[2] == 0x04) 
      {
        // Extract data (Modbus transmits High Byte first)
        data[0] = (responseFrame[3] << 8) | responseFrame[4];
        data[1] = (responseFrame[5] << 8) | responseFrame[6];
        
        Serial.println(data[0]);
        Serial.println(data[1]);
      } 
      else 
      {
        Serial.println("Modbus Error: Unexpected response format/error frame.");
      }
    } 
    else 
    {
      Serial.println("Modbus Error: CRC failed.");
    }
  } 
  else 
  {
    Serial.print("Modbus Error: Timeout or incomplete data. Bytes read: ");
    Serial.println(bytesRead);
  }

  // Enter shutdown mode after communication
  enableShutdown();
  delay(5000);
}