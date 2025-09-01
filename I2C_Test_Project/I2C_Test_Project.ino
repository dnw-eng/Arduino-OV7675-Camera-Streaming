/**
 * I2C Test Sketch for OV7675 Camera
 * 
 * This simple sketch tests I2C communication to help debug
 * camera connection issues before running the full video viewer.
 * 
 * IMPORTANT: This should be uploaded as a separate Arduino project,
 * not as part of the OV7675_Video_Viewer project.
 */

#include <Wire.h>

// OV7675 possible I2C addresses
const uint8_t OV7675_ADDRESSES[] = {0x42, 0x21, 0x30, 0x60, 0x61};
const int NUM_ADDRESSES = 5;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  Serial.println("=== OV7675 I2C Test ===");
  
  // Initialize I2C
  Wire.begin();
  Wire.setClock(100000);  // 100kHz for reliability
  
  // Add pull-up resistors
  pinMode(A4, INPUT_PULLUP);  // SDA
  pinMode(A5, INPUT_PULLUP);  // SCL
  
  Serial.println("I2C initialized at 100kHz");
  Serial.println("Testing I2C communication...");
  Serial.println();
}

void loop() {
  // Scan for I2C devices
  Serial.println("Scanning I2C bus...");
  int deviceCount = 0;
  
  for (uint8_t addr = 0x03; addr < 0x78; addr++) {
    Wire.beginTransmission(addr);
    uint8_t error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("Device found at 0x");
      if (addr < 0x10) Serial.print("0");
      Serial.print(addr, HEX);
      
      // Check if it's one of our expected addresses
      bool isExpected = false;
      for (int i = 0; i < NUM_ADDRESSES; i++) {
        if (addr == OV7675_ADDRESSES[i]) {
          isExpected = true;
          break;
        }
      }
      
      if (isExpected) {
        Serial.print(" (OV7675 camera - EXPECTED!)");
      } else if (addr == 0x6A || addr == 0x6B) {
        Serial.print(" (IMU LSM9DS1)");
      } else if (addr == 0x5C || addr == 0x5D) {
        Serial.print(" (Barometric sensor)");
      } else if (addr == 0x1C || addr == 0x1D) {
        Serial.print(" (Accelerometer)");
      } else if (addr == 0x44 || addr == 0x45) {
        Serial.print(" (Temp/Humidity sensor)");
      } else {
        Serial.print(" (unknown device)");
      }
      
      Serial.println();
      deviceCount++;
    } else if (error == 4) {
      Serial.print("Bus error at 0x");
      if (addr < 0x10) Serial.print("0");
      Serial.print(addr, HEX);
      Serial.println(" - check wiring!");
    }
  }
  
  Serial.print("Scan complete. Found ");
  Serial.print(deviceCount);
  Serial.println(" device(s).");
  
  if (deviceCount == 0) {
    Serial.println("No I2C devices found! Troubleshooting:");
    Serial.println("  1. Check SDA connection: Camera Pin 4 → Arduino A4");
    Serial.println("  2. Check SCL connection: Camera Pin 3 → Arduino A5");
    Serial.println("  3. Check 3.3V power: Camera Pin 1 → Arduino 3.3V");
    Serial.println("  4. Check ground: Camera Pin 2 → Arduino GND");
    Serial.println("  5. Verify camera module pins (Pin 1 = VCC)");
    Serial.println("  6. Try different I2C speed");
  } else {
    Serial.println("I2C bus is working!");
    
    // Test specific OV7675 addresses
    Serial.println();
    Serial.println("Testing OV7675 addresses specifically:");
    for (int i = 0; i < NUM_ADDRESSES; i++) {
      uint8_t addr = OV7675_ADDRESSES[i];
      Serial.print("  0x");
      if (addr < 0x10) Serial.print("0");
      Serial.print(addr, HEX);
      Serial.print(": ");
      
      Wire.beginTransmission(addr);
      uint8_t error = Wire.endTransmission();
      
      if (error == 0) {
        Serial.println("RESPONDING ✓");
      } else {
        Serial.print("No response (error ");
        Serial.print(error);
        Serial.println(")");
      }
    }
  }
  
  Serial.println();
  Serial.println("Press any key to rescan...");
  while (!Serial.available()) {
    delay(100);
  }
  Serial.read(); // Clear the input
  Serial.println();
} 