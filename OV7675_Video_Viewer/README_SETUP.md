# OV7675 Camera Video Streaming Setup Guide

## ✅ **Current Status: FULLY WORKING**

This camera system is now **fully operational** and has been tested successfully. The setup guide below reflects the current working configuration.

## Hardware Requirements

✅ **Verified Components:**
- Arduino Nano 33 BLE Sense
- OV7675 Camera Module
- USB Cable (Type-A to Micro-B)
- Either: TinyML Shield (recommended) OR Breadboard with jumper wires

## Pin Connections (Updated & Verified)

| OV7675 Pin | Function | Arduino Pin | Physical Pin |
|------------|----------|-------------|--------------|
| 1 (VCC)    | Power 3.3V | 3.3V      | Top-left 2nd |
| 2 (GND)    | Ground   | GND         | Multiple     |
| 3 (SIOC)   | I2C Clock| A5 (SCL)    | Pin A5       |
| 4 (SIOD)   | I2C Data | A4 (SDA)    | Pin A4       |
| 5 (VSYNC)  | V-Sync   | D8          | Pin D8       |
| 6 (HREF)   | H-Ref    | A1          | Pin A1       |
| 7 (PCLK)   | Pixel Clk| A0          | Pin A0       |
| 8 (XCLK)   | Master Clk| D9         | Pin D9       |
| 9 (D7)     | Data 7   | D4          | Pin D4       |
| 10 (D6)    | Data 6   | D6          | Pin D6       |
| 11 (D5)    | Data 5   | D5          | Pin D5       |
| 12 (D4)    | Data 4   | D3          | Pin D3       |
| 13 (D3)    | Data 3   | D2          | Pin D2       |
| 14 (D2)    | Data 2   | D0/RX       | Pin D0       |
| 15 (D1)    | Data 1   | D1/TX       | Pin D1       |
| 16 (D0)    | Data 0   | D10         | Pin D10      |
| 17, 18     | NC       | --          | Not connected|
| 19 (RST)   | Reset    | A2          | Pin A2       |
| 20 (PWDN)  | Power Dwn| A3          | Pin A3       |

⚠️ **Critical:** Double-check all connections. Most camera issues stem from incorrect wiring.

## Software Setup (macOS)

### 1. Install Arduino IDE
```bash
# Download from: https://www.arduino.cc/en/software
# Or use Homebrew:
brew install arduino-ide
```

### 2. Install Board Support
1. Open Arduino IDE
2. Go to **Tools → Board → Boards Manager**
3. Search for "mbed nano"
4. Install **Arduino MBED OS Nano Boards** version **2.3.1**

### 3. Install Required Libraries
1. Go to **Tools → Manage Libraries**
2. Install these libraries:
   - **Harvard_TinyMLx** (version 1.1.0-Alpha) - **This includes the working camera library**
   - **Arduino_LSM9DS1** (version 1.1.0)
   - **ArduinoBLE** (version 1.2.1)

**Note:** The **Arduino_OV767X_TinyMLx** library is included with Harvard_TinyMLx and is what makes this project work.

### 4. Configure Board Settings
1. **Tools → Board** → Select **Arduino Nano 33 BLE**
2. **Tools → Port** → Select your board's port (typically `/dev/cu.usbmodem****`)

## Project Setup

### 1. Open the Project
1. Launch Arduino IDE
2. Open `OV7675_Video_Viewer.ino`
3. Verify the file loads without errors

### 2. Verify Compilation
1. Click the **✓ Verify** button
2. Wait for compilation (may take several minutes first time)
3. Check for any errors in the output panel

### 3. Upload to Board
1. Connect Arduino via USB
2. Select correct **Port** in Tools menu
3. Click **→ Upload** button
4. Wait for "Done uploading" message

## Testing & Usage

### 1. Open Serial Monitor
1. **Tools → Serial Monitor**
2. Set baud rate to **115200**
3. You should see initialization messages:
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

### 2. Test Commands
Send these single characters via Serial Monitor:
- **'c'** - Capture and stream one frame
- **'p'** - Start continuous streaming  
- **'x'** - Stop streaming
- **'?'** - Show streaming status
- **'r'** - Reset camera
- **'d'** - Show camera info
- **'i'** - I2C device scan
- **'s'** - Slow I2C mode + scan

### 3. Expected Output
For successful frame capture:
```
FRAME_START #1
FRAME_SIZE:38400
FRAME_WIDTH:160
FRAME_HEIGHT:120  
FRAME_FORMAT:RGB565
FRAME_DATA:
[Hex data stream...]
FRAME_END
```

## Current Working Features

✅ **Camera Initialization:** Automatic detection and setup
✅ **Frame Capture:** Single frame capture on demand
✅ **Continuous Streaming:** 5 FPS automatic streaming
✅ **Interactive Commands:** Full command set working
✅ **Status Monitoring:** Real-time status and frame counting
✅ **LED Indicators:** Visual feedback during streaming
✅ **Error Handling:** Robust error detection and recovery

## Troubleshooting (Updated)

### Camera Working but I2C Scan Shows No Devices
✅ **This is normal and expected!**
- The working library uses its own I2C implementation
- Camera will function perfectly even if manual I2C scan fails
- Use 's' command for detailed I2C diagnostics if needed

### Compilation Errors  
❌ **Symptoms:** Red error messages during verify/upload
✅ **Solutions:**
1. Ensure **Arduino MBED OS Nano Boards** v2.3.1 installed
2. Check **Harvard_TinyMLx** library is installed
3. Verify board selected as **Arduino Nano 33 BLE**
4. Close/reopen Arduino IDE and try again

### Upload Failures
❌ **Symptoms:** "Upload failed" or port not found
✅ **Solutions:**
1. Press reset button on Arduino, then immediately upload
2. Try different USB cable
3. Check port selection in Tools menu
4. On macOS, may need to approve security dialog

## Frame Data Format

The camera outputs RGB565 format:
- **Resolution:** 160x120 pixels (QQVGA)
- **Color Depth:** 16-bit (RGB565)  
- **Frame Size:** 38,400 bytes
- **Pixel Format:** RRRR RGGG GGGB BBBB (5-6-5 bits)
- **Frame Rate:** 5 FPS (configurable)

## Hardware Documentation References

📖 **Pin Mapping:** Verified working configuration above
📖 **Library:** Harvard_TinyMLx Arduino_OV767X_TinyMLx
📖 **nRF52840 Specs:** Nordic nRF52840 Product Specification v1.1
📖 **Arduino Support:** Arduino MBED OS Nano Boards documentation

## Next Steps

The camera system is now fully functional and ready for:
1. **Computer vision applications** using the streamed data
2. **TinyML integration** for machine learning projects
3. **Video monitoring systems** with real-time capture
4. **Image processing experiments** on the captured frames
5. **Integration with other Arduino projects**

## Support

If you encounter issues:
1. **Check hardware connections** first (use the table above)
2. **Verify software versions** match exactly
3. **Review serial monitor output** for specific messages
4. **Use diagnostic commands** ('s', 't', '?') for troubleshooting

---

**Status: ✅ FULLY WORKING - Camera streaming successfully implemented and tested**
**Last Updated:** Current session - All features operational