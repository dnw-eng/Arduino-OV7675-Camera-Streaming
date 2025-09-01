# Command Reference - Arduino OV7675 Camera Streaming

Complete reference for all available commands in the OV7675 Video Viewer system.

## 🎮 **Command Overview**

The system provides **10 interactive commands** for full camera control and diagnostics. All commands are sent via the Serial Monitor as **single characters**.

## 📱 **Camera Control Commands**

### **'c' - Capture Single Frame**
**Purpose:** Capture and stream one frame immediately
**Usage:** Send 'c' in Serial Monitor
**Response:** Complete frame data with metadata
**Example Output:**
```
Capturing single frame...
FRAME_START #15
FRAME_SIZE:38400
FRAME_WIDTH:160
FRAME_HEIGHT:120
FRAME_FORMAT:RGB565
FRAME_DATA:
[Hex data stream...]
FRAME_END
```

### **'p' - Start Continuous Streaming**
**Purpose:** Begin automatic frame streaming at 5 FPS
**Usage:** Send 'p' in Serial Monitor
**Response:** Confirmation and automatic frame delivery
**Example Output:**
```
Starting continuous streaming...
Streaming enabled at 5 FPS
[Automatic frame delivery begins]
```
**Visual Indicator:** Built-in LED blinks rapidly during streaming

### **'x' - Stop Continuous Streaming**
**Purpose:** Halt automatic frame streaming
**Usage:** Send 'x' in Serial Monitor
**Response:** Confirmation of streaming stop
**Example Output:**
```
Stopping continuous streaming...
Streaming disabled
```
**Visual Indicator:** Built-in LED stops blinking

### **'r' - Reset Camera**
**Purpose:** Reinitialize the camera system
**Usage:** Send 'r' in Serial Monitor
**Response:** Reset confirmation and reinitialization
**Example Output:**
```
Resetting camera...
Camera reset successful
```

## 📊 **Status & Information Commands**

### **'?' - Show Streaming Status**
**Purpose:** Display current system status and frame count
**Usage:** Send '?' in Serial Monitor
**Response:** Comprehensive status information
**Example Output:**
```
Streaming Status:
  Continuous streaming: ENABLED
  Total frames captured: 47
  Frame rate: 5 FPS
  Resolution: 160x120
  Format: RGB565
  Memory usage: ~38KB per frame
```

### **'d' - Display Camera Information**
**Purpose:** Show camera configuration and specifications
**Usage:** Send 'd' in Serial Monitor
**Response:** Camera technical details
**Example Output:**
```
Camera info:
  Resolution: 160x120
  Format: 16 bits per pixel
  Bytes per pixel: 2
  Total frame size: 38,400 bytes
  Target FPS: 5
  Camera type: OV7675
```

### **'z' - Reset Frame Counter**
**Purpose:** Reset the frame counter to zero
**Usage:** Send 'z' in Serial Monitor
**Response:** Counter reset confirmation
**Example Output:**
```
Resetting frame counter...
Frame counter reset to 0
```

## 🔧 **System Diagnostics Commands**

### **'i' - I2C Device Scan**
**Purpose:** Scan I2C bus for connected devices
**Usage:** Send 'i' in Serial Monitor
**Response:** List of detected I2C devices
**Example Output:**
```
Scanning I2C bus...
Scanning I2C bus (0x03-0x77)...
Device found at 0x21 (OV7675 alternate)
Device found at 0x6A (IMU LSM9DS1)
Device found at 0x5C (Barometric sensor)
Scan complete. Found 3 device(s).
```

### **'s' - Slow I2C Mode + Scan**
**Purpose:** Switch to slow I2C mode and rescan
**Usage:** Send 's' in Serial Monitor
**Response:** I2C speed change and detailed scan
**Example Output:**
```
Switching to slow I2C mode (10kHz)...
Rescanning I2C bus...
Scanning I2C bus (0x03-0x77)...
Device found at 0x21 (OV7675 alternate)
Scan complete. Found 1 device(s).
I2C bus is working - camera should be detected!
```

### **'t' - Test I2C Bus Functionality**
**Purpose:** Comprehensive I2C bus diagnostic test
**Usage:** Send 't' in Serial Monitor
**Response:** Detailed I2C test results
**Example Output:**
```
=== I2C Bus Diagnostic Test ===
Test 1: Basic I2C communication
  SDA pin (A4) state: 1
  SCL pin (A5) state: 1
Test 2: I2C clock speed
  Current speed: 100kHz
Test 3: Pin states
  I2C pins are properly configured
Test 4: I2C speed test
  Bus communication: OK
```

## 📋 **Command Summary Table**

| Command | Category | Purpose | Response Time | Visual Feedback |
|---------|----------|---------|---------------|-----------------|
| **'c'** | Camera | Single frame capture | Immediate | None |
| **'p'** | Camera | Start streaming | Immediate | LED blinks |
| **'x'** | Camera | Stop streaming | Immediate | LED stops |
| **'r'** | Camera | Reset camera | ~2 seconds | None |
| **'?'** | Status | Show status | Immediate | None |
| **'d'** | Status | Camera info | Immediate | None |
| **'z'** | Status | Reset counter | Immediate | None |
| **'i'** | Diagnostic | I2C scan | ~1 second | None |
| **'s'** | Diagnostic | Slow I2C scan | ~2 seconds | None |
| **'t'** | Diagnostic | I2C test | ~3 seconds | None |

## 🎯 **Command Usage Patterns**

### **Basic Operation:**
1. **'c'** - Test single frame capture
2. **'p'** - Start continuous streaming
3. **'x'** - Stop streaming when done

### **System Check:**
1. **'?'** - Check current status
2. **'d'** - Verify camera configuration
3. **'i'** - Scan for connected devices

### **Troubleshooting:**
1. **'t'** - Run comprehensive I2C test
2. **'s'** - Try slow I2C mode
3. **'r'** - Reset camera if needed

### **Performance Monitoring:**
1. **'?'** - Monitor frame count and status
2. **'z'** - Reset counter for new session
3. **'d'** - Check camera specifications

## 🚨 **Command Error Handling**

### **Invalid Commands:**
- **Response:** "Unknown command: [character]"
- **Action:** Command ignored, system continues normal operation
- **Recovery:** Send valid command

### **System Errors:**
- **Response:** Error message with specific details
- **Action:** System attempts recovery automatically
- **Recovery:** Use 'r' command to reset if needed

### **Communication Errors:**
- **Response:** "Communication error" or similar
- **Action:** System retries operation
- **Recovery:** Check connections and try again

## 🔍 **Advanced Command Features**

### **Auto-Response:**
- Commands respond immediately (except 'r', 's', 't')
- System continues normal operation during commands
- No command queuing or blocking

### **State Persistence:**
- Streaming state maintained across commands
- Frame counter increments automatically
- Camera settings preserved during operation

### **Real-Time Updates:**
- Status commands show current real-time data
- Frame counter updates with each capture
- Streaming status reflects current state

## 📖 **Command Best Practices**

### **For New Users:**
1. **Start with 'c'** to test basic functionality
2. **Use '?' frequently** to check system status
3. **Try 'p' and 'x'** to test streaming control

### **For Troubleshooting:**
1. **Use 't' first** for comprehensive diagnostics
2. **Try 's'** if I2C issues suspected
3. **Use 'r'** as last resort for camera reset

### **For Performance:**
1. **Monitor with '?'** during streaming
2. **Check 'd'** for camera configuration
3. **Use 'z'** to reset counters between sessions

## 🔗 **Related Documentation**

- **[Quick Start Guide](quick-start.md)** - Get started with basic commands
- **[Troubleshooting Guide](troubleshooting.md)** - Solve command-related issues
- **[Main Project Guide](main-project-guide.md)** - Complete system documentation

---

## 🎉 **Command System Ready!**

Your OV7675 camera system provides a complete command interface for full control and monitoring. All commands are tested and working.

**Status: ✅ ALL COMMANDS OPERATIONAL - Full control system available**

---

*Part of the Arduino OV7675 Camera Streaming Project* 