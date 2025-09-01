# Quick Start Guide - Arduino OV7675 Camera Streaming

Get your OV7675 camera streaming system up and running in **under 10 minutes** with this quick start guide.

## ⚡ **Super Quick Setup (5 minutes)**

### **1. Hardware Connection**
Connect your OV7675 camera to Arduino Nano 33 BLE:

| Pin | Connection |
|-----|------------|
| **VCC** | Arduino 3.3V |
| **GND** | Arduino GND |
| **SDA** | Arduino A4 |
| **SCL** | Arduino A5 |

*Note: Only 4 pins needed for basic I2C communication*

### **2. Software Setup**
1. **Install Arduino IDE** (latest version)
2. **Install Board Support**: Tools → Board → Boards Manager → Search "mbed nano" → Install "Arduino MBED OS Nano Boards" v2.3.1
3. **Install Library**: Tools → Manage Libraries → Search "Harvard_TinyMLx" → Install

### **3. Upload & Test**
1. **Open** `OV7675_Video_Viewer.ino` in Arduino IDE
2. **Select Board**: Tools → Board → Arduino Nano 33 BLE
3. **Upload** the sketch
4. **Open Serial Monitor** at 115200 baud
5. **Type 'c'** to capture your first frame!

## 🚀 **Detailed Quick Start (10 minutes)**

### **Step 1: Verify Hardware**
- ✅ Arduino Nano 33 BLE Sense connected via USB
- ✅ OV7675 camera module connected (4 pins minimum)
- ✅ Stable 3.3V power supply
- ✅ All connections secure

### **Step 2: Software Installation**
```bash
# Arduino IDE (if not installed)
# Download from: https://www.arduino.cc/en/software

# Required Libraries (via Library Manager)
- Harvard_TinyMLx (v1.1.0-Alpha)
- Arduino_LSM9DS1 (v1.1.0) 
- ArduinoBLE (v1.2.1)

# Board Support
- Arduino MBED OS Nano Boards (v2.3.1)
```

### **Step 3: Project Setup**
1. **Download** the project files
2. **Open** `OV7675_Video_Viewer.ino` in Arduino IDE
3. **Verify** all required libraries are installed
4. **Select** Arduino Nano 33 BLE as board
5. **Compile** to check for errors

### **Step 4: Upload & Test**
1. **Connect** Arduino to computer
2. **Select** correct USB port
3. **Upload** the sketch
4. **Open** Serial Monitor (115200 baud)
5. **Wait** for initialization messages

## 📱 **First Test Commands**

Once uploaded, try these commands in Serial Monitor:

| Command | Action | Expected Result |
|---------|--------|-----------------|
| **'c'** | Capture frame | Frame data appears |
| **'d'** | Camera info | Resolution, format, etc. |
| **'?'** | Status check | Streaming status |
| **'p'** | Start streaming | Continuous frames |
| **'x'** | Stop streaming | Streaming stops |

## 🎯 **Expected Output**

### **Successful Initialization:**
```
=== OV7675 Camera Video Viewer ===
Initializing camera system...
I2C initialized at 100kHz
[I2C scan results]
Initializing OV7675 camera... SUCCESS
Camera initialized: 160x120 @ 5 FPS
Format: 16 bits per pixel

=== Camera Ready for Streaming ===
Commands: [list of available commands]
```

### **First Frame Capture:**
```
Capturing single frame...
FRAME_START #1
FRAME_SIZE:38400
FRAME_WIDTH:160
FRAME_HEIGHT:120
FRAME_FORMAT:RGB565
FRAME_DATA:
[Camera data in hex format...]
FRAME_END
```

## 🚨 **Quick Troubleshooting**

### **If Camera Won't Initialize:**
1. **Check connections** - SDA→A4, SCL→A5, VCC→3.3V, GND→GND
2. **Verify power** - Camera needs stable 3.3V
3. **Check board selection** - Must be "Arduino Nano 33 BLE"
4. **Try 's' command** for slow I2C mode

### **If I2C Scan Shows No Devices:**
- **This is normal!** The working library uses its own I2C implementation
- **Camera will still work** if initialization succeeds
- **Use 's' command** for detailed I2C diagnostics

### **If Commands Don't Work:**
1. **Check serial monitor** is open at 115200 baud
2. **Send single characters** (not words)
3. **Wait for command prompt** before sending
4. **Use '?' command** to check system status

## 🎉 **Success Indicators**

You know it's working when:
- ✅ **Camera initializes** with "SUCCESS" message
- ✅ **Commands respond** immediately
- ✅ **Frame data appears** when using 'c' command
- ✅ **LED blinks** during continuous streaming
- ✅ **Frame counter increases** with each capture

## 📖 **Next Steps**

Once basic functionality is working:
1. **Try continuous streaming** with 'p' command
2. **Explore all commands** to learn full capabilities
3. **Check performance** with status commands
4. **Read detailed guides** for advanced features

## 🔗 **Related Documentation**

- **[Hardware Setup](hardware-setup.md)** - Complete wiring guide
- **[Main Project Guide](main-project-guide.md)** - Full feature documentation
- **[Troubleshooting Guide](troubleshooting.md)** - Common issues and solutions
- **[Command Reference](command-reference.md)** - All available commands

---

## ⚡ **You're Ready!**

Your OV7675 camera streaming system should now be working! If you encounter any issues, check the troubleshooting guide or use the built-in diagnostic commands.

**Status: ✅ QUICK START COMPLETE - Camera system operational**

---

*Part of the Arduino OV7675 Camera Streaming Project* 