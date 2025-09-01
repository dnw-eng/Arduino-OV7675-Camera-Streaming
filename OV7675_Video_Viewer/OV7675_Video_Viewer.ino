/**
 * @file OV7675_Video_Viewer.ino
 * @brief OV7675 Camera Video Streaming for Arduino Nano 33 BLE Sense
 * 
 * This Arduino sketch captures and streams video from the OV7675 camera module
 * connected to the Arduino Nano 33 BLE Sense. Video data is streamed via 
 * serial port for viewing on a computer.
 * 
 * Hardware Requirements:
 * - Arduino Nano 33 BLE Sense
 * - OV7675 Camera Module
 * - Connection as per TinyML course documentation
 * 
 * Libraries Required:
 * - Wire (I2C communication)
 * - Arduino Nano 33 BLE board support
 * 
 * Author: Generated for TinyML Camera Streaming
 * Based on: Linux kernel OV7670 driver and TinyML course materials
 */

#include <Wire.h>
#include "Arduino_OV767X_TinyMLx.h"

// Global objects
OV767X camera;

// Configuration - using Arduino_OV767X_TinyMLx library format
const int TARGET_RESOLUTION = QQVGA;  // 160x120 for memory constraints
const int TARGET_FORMAT = RGB565;     // 16-bit color
const int TARGET_FPS = 5;            // Low frame rate for serial streaming
const int CAMERA_TYPE = OV7675;      // Camera model

// Status variables
bool cameraInitialized = false;
bool continuousStreaming = false;
unsigned long lastFrameTime = 0;
const unsigned long FRAME_INTERVAL = 1000 / TARGET_FPS;  // ms between frames
unsigned long frameCount = 0;  // Track total frames captured

void setup() {
  // Initialize serial communication for debugging and streaming
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  Serial.println("=== OV7675 Camera Video Viewer ===");
  Serial.println("Initializing camera system...");
  
  // Initialize I2C for camera communication
  Wire.begin();
  Wire.setClock(100000);  // 100kHz I2C clock for reliable communication
  
  Serial.println("I2C initialized at 100kHz");
  
  // Add pull-up resistors for I2C (some boards need this)
  pinMode(A4, INPUT_PULLUP);  // SDA
  pinMode(A5, INPUT_PULLUP);  // SCL
  
  // First, scan for I2C devices to verify connections
  Serial.println("Scanning for I2C devices...");
  scanI2CDevices();
  
  // Additional I2C debugging
  Serial.println("Additional I2C diagnostics:");
  Serial.print("SDA pin (A4) state: ");
  Serial.println(digitalRead(A4));
  Serial.print("SCL pin (A5) state: ");
  Serial.println(digitalRead(A5));
  
  // Test I2C bus with simple scan
  Serial.println("Quick I2C bus test:");
  bool i2c_working = false;
  for (uint8_t addr = 0x03; addr < 0x78; addr++) {
    Wire.beginTransmission(addr);
    uint8_t error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("  Found device at 0x");
      if (addr < 0x10) Serial.print("0");
      Serial.println(addr, HEX);
      i2c_working = true;
    }
  }
  
  if (!i2c_working) {
    Serial.println("  NO I2C devices found - bus not working!");
    Serial.println("  This indicates a fundamental I2C wiring issue");
  } else {
    Serial.println("  I2C bus is working - camera should be detected");
  }
  
  // Initialize camera using the working library
  Serial.print("Initializing OV7675 camera... ");
  if (camera.begin(TARGET_RESOLUTION, TARGET_FORMAT, TARGET_FPS, CAMERA_TYPE)) {
    Serial.println("SUCCESS");
    cameraInitialized = true;
    
    // Print camera information
    Serial.print("Camera initialized: ");
    Serial.print(camera.width());
    Serial.print("x");
    Serial.print(camera.height());
    Serial.print(" @ ");
    Serial.print(TARGET_FPS);
    Serial.println(" FPS");
    Serial.print("Format: ");
    Serial.print(camera.bitsPerPixel());
    Serial.println(" bits per pixel");
  } else {
    Serial.println("FAILED");
    Serial.println("ERROR: Camera initialization failed!");
    Serial.println("Check connections and power supply.");
    return;
  }
  
  Serial.println();
  Serial.println("=== Camera Ready for Streaming ===");
  Serial.println("Commands:");
  Serial.println("  'c' - Capture and stream one frame");
  Serial.println("  'p' - Start continuous streaming");
  Serial.println("  'x' - Stop continuous streaming");
  Serial.println("  '?' - Show streaming status");
  Serial.println("  'z' - Reset frame counter");
  Serial.println("  't' - Test I2C bus functionality");
  Serial.println("  'r' - Reset camera");
  Serial.println("  'd' - Show camera info");
  Serial.println("  'i' - I2C device scan (diagnostic)");
  Serial.println("  's' - Slow I2C mode + scan (troubleshooting)");
  Serial.println();
}

void loop() {
  if (!cameraInitialized) {
    // Camera failed to initialize, just blink LED to indicate error
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(900);
    return;
  }
  
  // Handle serial commands
  if (Serial.available()) {
    char command = Serial.read();
    handleSerialCommand(command);
  }
  
  // Continuous streaming logic
  if (continuousStreaming) {
    unsigned long currentTime = millis();
    if (currentTime - lastFrameTime >= FRAME_INTERVAL) {
      captureAndStreamFrame();
      lastFrameTime = currentTime;
      
      // Add small delay to prevent overwhelming serial output
      delay(10);
    }
    
    // Blink LED rapidly to indicate streaming is active
    static bool ledState = false;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  } else {
    // Keep LED off when not streaming
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  // Small delay to prevent overwhelming the system
  delay(10);
}

/**
 * Handle commands received via serial port
 */
void handleSerialCommand(char command) {
  switch (command) {
    case 'c':
    case 'C':
      Serial.println("Capturing single frame...");
      captureAndStreamFrame();
      break;
      
    case 'p':
    case 'P':
      Serial.println("Starting continuous streaming...");
      continuousStreaming = true;
      lastFrameTime = millis();
      Serial.println("Continuous streaming ENABLED - frames will stream automatically");
      break;
      
    case 'x':
    case 'X':
      Serial.println("Stopping continuous streaming...");
      continuousStreaming = false;
      Serial.println("Continuous streaming DISABLED");
      break;
      
    case 'r':
    case 'R':
      Serial.println("Resetting camera...");
      resetCamera();
      break;
      
    case 'd':
    case 'D':
      Serial.println("Camera info:");
      Serial.print("  Resolution: ");
      Serial.print(camera.width());
      Serial.print("x");
      Serial.println(camera.height());
      Serial.print("  Format: ");
      Serial.print(camera.bitsPerPixel());
      Serial.println(" bits per pixel");
      Serial.print("  Bytes per pixel: ");
      Serial.println(camera.bytesPerPixel());
      break;
      
    case 'i':
    case 'I':
      Serial.println("Scanning I2C bus...");
      scanI2CDevices();
      break;
      
    case 's':
    case 'S':
      Serial.println("Switching to slow I2C mode (10kHz)...");
      Wire.setClock(10000);
      Serial.println("Rescanning I2C bus...");
      scanI2CDevices();
      break;
      
    case 't':
    case 'T':
      Serial.println("Testing I2C bus functionality...");
      testI2CBus();
      break;
      
    case '?':
      Serial.println("Streaming Status:");
      Serial.print("  Continuous streaming: ");
      Serial.println(continuousStreaming ? "ENABLED" : "DISABLED");
      Serial.print("  Total frames captured: ");
      Serial.println(frameCount);
      if (continuousStreaming) {
        Serial.print("  Frame rate: ");
        Serial.print(TARGET_FPS);
        Serial.println(" FPS");
        Serial.print("  Resolution: ");
        Serial.print(camera.width());
        Serial.print("x");
        Serial.println(camera.height());
      }
      break;
      
    case 'z':
    case 'Z':
      Serial.println("Resetting frame counter...");
      frameCount = 0;
      Serial.println("Frame counter reset to 0");
      break;
      
    default:
      Serial.print("Unknown command: ");
      Serial.println(command);
      break;
  }
}

/**
 * Capture a frame and stream it via serial port
 */
void captureAndStreamFrame() {
  frameCount++;  // Increment frame counter
  Serial.print("FRAME_START #");
  Serial.println(frameCount);
  
  // Calculate frame buffer size
  int frameWidth = camera.width();
  int frameHeight = camera.height();
  int bytesPerPixel = camera.bytesPerPixel();
  size_t bufferSize = frameWidth * frameHeight * bytesPerPixel;
  
  // Allocate buffer for frame data
  uint8_t* frameBuffer = (uint8_t*)malloc(bufferSize);
  if (!frameBuffer) {
    Serial.println("ERROR: Failed to allocate frame buffer");
    return;
  }
  
  // Send frame header
  Serial.print("FRAME_SIZE:");
  Serial.println(bufferSize);
  Serial.print("FRAME_WIDTH:");
  Serial.println(frameWidth);
  Serial.print("FRAME_HEIGHT:");
  Serial.println(frameHeight);
  Serial.print("FRAME_FORMAT:");
  Serial.println(bytesPerPixel == 2 ? "RGB565" : "Unknown");
  
  // Capture frame from camera
  Serial.println("FRAME_DATA:");
  camera.readFrame(frameBuffer);
  
  // Send frame data as hex bytes
  for (size_t i = 0; i < bufferSize; i++) {
    if (frameBuffer[i] < 0x10) Serial.print("0");
    Serial.print(frameBuffer[i], HEX);
    
    if (i % 32 == 31) Serial.println();  // New line every 32 bytes
  }
  
  // Clean up
  free(frameBuffer);
  
  Serial.println();
  Serial.println("FRAME_END");
}

/**
 * Reset and reinitialize the camera
 */
void resetCamera() {
  Serial.println("Resetting camera...");
  camera.end();
  delay(100);
  
  if (camera.begin(TARGET_RESOLUTION, TARGET_FORMAT, TARGET_FPS, CAMERA_TYPE)) {
    Serial.println("Camera reset successful");
  } else {
    Serial.println("Camera reset failed");
  }
}

/**
 * Scan I2C bus for connected devices
 */
void scanI2CDevices() {
  Serial.println("Scanning I2C bus (0x03-0x77)...");
  int deviceCount = 0;
  
  for (uint8_t addr = 0x03; addr < 0x78; addr++) {
    Wire.beginTransmission(addr);
    uint8_t error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("Device found at 0x");
      if (addr < 0x10) Serial.print("0");
      Serial.print(addr, HEX);
      
      // Identify known devices
      if (addr == 0x42) Serial.print(" (OV7675 camera - expected)");
      else if (addr == 0x21) Serial.print(" (OV7675 alternate)");
      else if (addr == 0x30) Serial.print(" (OV7675 possible)");
      else if (addr == 0x60 || addr == 0x61) Serial.print(" (OV camera possible)");
      else if (addr == 0x6A || addr == 0x6B) Serial.print(" (IMU LSM9DS1)");
      else if (addr == 0x5C || addr == 0x5D) Serial.print(" (Barometric sensor)");
      else if (addr == 0x1C || addr == 0x1D) Serial.print(" (Accelerometer)");
      else if (addr == 0x44 || addr == 0x45) Serial.print(" (Temp/Humidity sensor)");
      else Serial.print(" (unknown device)");
      
      Serial.println();
      deviceCount++;
    } else if (error == 4) {
      // Bus error - indicates wiring issue
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
    Serial.println("  6. Try slower I2C speed (type 's' for slow mode)");
  } else {
    Serial.println("I2C bus is working - camera should be detected!");
  }
}

/**
 * Test I2C bus functionality with detailed diagnostics
 */
void testI2CBus() {
  Serial.println("=== I2C Bus Diagnostic Test ===");
  
  // Test 1: Basic I2C communication
  Serial.println("Test 1: Basic I2C communication");
  Wire.beginTransmission(0x42);
  uint8_t error = Wire.endTransmission();
  Serial.print("  Test to 0x42: ");
  if (error == 0) {
    Serial.println("SUCCESS");
  } else {
    Serial.print("FAILED (error ");
    Serial.print(error);
    Serial.println(")");
  }
  
  // Test 2: I2C clock speed
  Serial.println("Test 2: I2C clock speed");
  Serial.println("  Current speed: 100000 Hz (set during initialization)");
  
  // Test 3: Pin states
  Serial.println("Test 3: Pin states");
  Serial.print("  SDA (A4): ");
  Serial.println(digitalRead(A4));
  Serial.print("  SCL (A5): ");
  Serial.println(digitalRead(A5));
  
  // Test 4: Try different I2C speeds
  Serial.println("Test 4: I2C speed test");
  uint32_t speeds[] = {100000, 50000, 10000};
  for (int i = 0; i < 3; i++) {
    Wire.setClock(speeds[i]);
    Serial.print("  Testing at ");
    Serial.print(speeds[i]);
    Serial.print(" Hz: ");
    
    Wire.beginTransmission(0x42);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.println("SUCCESS");
    } else {
      Serial.print("FAILED (error ");
      Serial.print(error);
      Serial.println(")");
    }
  }
  
  // Reset to original speed
  Wire.setClock(100000);
  
  Serial.println("=== I2C Test Complete ===");
}