# PID Motor Control for JGA25-370

This Arduino sketch implements PID (Proportional-Integral-Derivative) control for the JGA25-370 DC geared motor with integrated magnetic hall encoder.

## Features

- ✅ Real-time speed control in RPM
- ✅ Encoder-based feedback for precision
- ✅ Serial interface for tuning and monitoring
- ✅ Anti-windup protection
- ✅ Runtime PID parameter adjustment

## Hardware Requirements

### Components
- **Motor**: JGA25-370 DC motor with encoder (6V version recommended)
- **Motor Driver**: L298N, TB6612FNG, or similar H-bridge driver
- **Controller**: Arduino Nano, Uno, or Mega
- **Power Supply**: 6V for motor (separate from Arduino if high current)

### Wiring Diagram

```
Arduino          Motor Driver        JGA25-370 Motor
-------          ------------        ---------------
Pin 9 (PWM) ---> ENA/PWMA            
Pin 8       ---> IN1             
Pin 7       ---> IN2             
                 OUT1 ------------> Motor +
                 OUT2 ------------> Motor -
                 
Pin 2 (INT) <--- Encoder A (Yellow)
Pin 3 (INT) <--- Encoder B (White)
GND         <--- Encoder GND (Black)
5V          <--- Encoder VCC (Red)
```

### Notes on Wiring
- Connect encoder to 5V (not motor voltage!)
- Use interrupt-capable pins for encoder (pins 2 & 3 on Arduino Uno/Nano)
- Ensure common ground between Arduino and motor driver
- Add 100nF capacitor across motor terminals to reduce noise

## Software Setup

1. **Install Arduino IDE** (1.8.x or 2.x)

2. **Open the sketch**
   ```
   File > Open > pid_control/pid_control.ino
   ```

3. **Configure pins** (if different from defaults)
   ```cpp
   const int MOTOR_PWM = 9;
   const int MOTOR_DIR1 = 8;
   const int MOTOR_DIR2 = 7;
   const int ENCODER_A = 2;
   const int ENCODER_B = 3;
   ```

4. **Set motor parameters**
   ```cpp
   const int ENCODER_PPR = 12;        // Pulses per revolution
   const float GEAR_RATIO = 46.8;     // Check your motor specs!
   ```

5. **Upload to Arduino**
   - Select your board: `Tools > Board > Arduino Nano/Uno`
   - Select port: `Tools > Port > /dev/ttyUSB0` (or COM port on Windows)
   - Click Upload

## Usage

### Serial Monitor

Open Serial Monitor at **115200 baud**

### Commands

| Command | Description | Example |
|---------|-------------|---------|
| `S<rpm>` | Set target speed in RPM | `S100` - Set 100 RPM |
| `P<value>` | Set Kp (proportional gain) | `P2.5` |
| `I<value>` | Set Ki (integral gain) | `I5.0` |
| `D<value>` | Set Kd (derivative gain) | `D1.2` |
| `X` | Stop motor | `X` |
| `?` | Show help | `?` |

### Example Session

```
JGA25-370 PID Control Initialized
Commands: S<rpm> - Set speed, P<val> I<val> D<val> - Tune PID

> S50
Setpoint: 50.00 RPM

Setpoint: 50.00 | Speed: 12.45 | Error: 37.55 | Output: 75 | Count: 142
Setpoint: 50.00 | Speed: 34.21 | Error: 15.79 | Output: 68 | Count: 387
Setpoint: 50.00 | Speed: 48.92 | Error: 1.08 | Output: 52 | Count: 621
Setpoint: 50.00 | Speed: 50.15 | Error: -0.15 | Output: 50 | Count: 845

> S0
Setpoint: 0.00 RPM

> X
Motor stopped
```

## PID Tuning

### Default Parameters
```cpp
Kp = 2.0;   // Proportional gain
Ki = 5.0;   // Integral gain  
Kd = 1.0;   // Derivative gain
```

These values are based on research for the JGA25-370 motor and should provide a good starting point.

### Tuning Process

1. **Start with defaults**
   - Upload sketch and set a moderate speed (e.g., S50)
   - Observe behavior in Serial Monitor

2. **If motor oscillates** (speed bounces up and down)
   - Reduce Kp: `P1.5`
   - Or reduce Ki: `I3.0`

3. **If motor is sluggish** (slow to reach target)
   - Increase Kp: `P3.0`
   - Check for mechanical resistance

4. **If steady-state error** (doesn't quite reach target)
   - Increase Ki: `I7.0`
   - Be careful of integral windup

5. **To reduce overshoot**
   - Increase Kd: `D2.0`
   - Or reduce Kp slightly

### Ziegler-Nichols Method (Advanced)

1. Set Ki and Kd to 0: `I0`, `D0`
2. Gradually increase Kp until oscillations occur
3. Note the critical gain (Ku) and oscillation period (Tu)
4. Calculate:
   - Kp = 0.6 * Ku
   - Ki = 1.2 * Ku / Tu
   - Kd = 0.075 * Ku * Tu

## Troubleshooting

### Motor doesn't move
- ✓ Check wiring connections
- ✓ Verify motor driver power supply
- ✓ Check direction pins are correctly connected
- ✓ Try higher PWM values directly

### Encoder count not changing
- ✓ Check encoder wiring (especially VCC and GND)
- ✓ Verify encoder channels on interrupt pins
- ✓ Check for loose connections
- ✓ Test encoder signals with oscilloscope/multimeter

### Speed reading is wrong
- ✓ Verify ENCODER_PPR and GEAR_RATIO constants
- ✓ Check encoder connections
- ✓ Ensure SAMPLE_TIME is appropriate (100ms default)
- ✓ Look for electrical noise (add capacitors)

### Motor oscillates wildly
- ✓ Reduce Kp gain
- ✓ Reduce Ki gain
- ✓ Check for mechanical binding
- ✓ Verify PWM frequency is appropriate

### Encoder noise
- ✓ Add 100nF capacitor across motor terminals
- ✓ Use shielded cables for encoder wires
- ✓ Keep encoder wires away from motor wires
- ✓ Consider adding a Kalman filter (see docs)

## Performance Expectations

With proper tuning, you should achieve:
- **Accuracy**: ±2% of target speed
- **Rise time**: 1-2 seconds to target speed
- **Overshoot**: <10%
- **Steady-state error**: <1 RPM

## Advanced Features (TODO)

- [ ] Kalman filter for noise reduction
- [ ] Multiple motor coordination
- [ ] Position control mode
- [ ] Velocity profiling (acceleration/deceleration curves)
- [ ] EEPROM storage of PID parameters
- [ ] Auto-tuning algorithm

## References

- [JGA25-370 Motor Specifications](../../../parts/25GA370_dc_geared_motor/)
- [PID Control Theory](../../../docs/jga25-370_pid_control.md)
- [L298N Motor Driver Guide](../../../parts/L298N_motor_driver/)

## Contributing

Found a bug or have an improvement? Please open an issue or submit a pull request!

## License

MIT License - see [LICENSE](../../../LICENSE) for details
