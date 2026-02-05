# ONGEKI Mini Controller

**Language / 语言:** [中文](./README.md)

This is the (not-so-)mini controller designed for SEGA's arcade rhythm game ONGEKI.

This repository is a heavily modified build based on [Lee65535/Minigeki](https://github.com/Lee65535/Minigeki) and [HanasakiMana/Minigeki](https://github.com/HanasakiMana/Minigeki)

Finished product photos:

![Finished](./img/top.jpg)
![Side view](./img/side.jpg)

## Overview

The overall structure follows Lee's five-layer design and Hanasaki's enlarged PCB layout.

- Overall size: approximately 250 mm × 200 mm × 13.3 mm
- Bottom: a 1.6 mm base plate with feet
- Lower spacer: 5 mm acrylic plate
- Middle: PCB (designed by Hanasaki), 1.6 mm
- Upper spacer: 3.5 mm acrylic plate
- Top: 1.6 mm front panel (also serves as a positioning plate)

All layers are fastened by six sets of M3 × 18 socket-head screws and cap nuts. The screws pass from bottom to top, and each screw is wrapped with a silicone flat-head sleeve that acts as a foot pad.

To save time, the top and bottom spacer plates use the same outline (only thickness differs).

## Assembly / Parts

Required parts:

- 1 × SparkFun Pro Micro (or compatible clone)
- 10 × mechanical switches and keycaps. For the two side keys, consider 1.75U or 2U keycaps
- 10 × hot-swap switch sockets
- 10 × WS2812B LEDs (optional — LEDs are difficult to solder and can be omitted)
- 1 × 75 mm dual linear slider potentiometer, type `B10K` (used as a fader)
  - Type explanation: the first letter denotes taper (A = audio/logarithmic, B = linear). The number is the max resistance (e.g., 10K = 10 kilo-ohm)
  - I used an ALPS RS60112A6A0C to replace the original NOBLE XJV60GPV15C-15A20K because the latter was logarithmic and unsuitable
  - A 3D-printed imitation factory-style knob can be added on top (designed by the original project)

Manufacturing notes:

- Order the PCB from a board house using the PCB files
- For the spacer plates, provide the flat drawings to a shop; I used black acrylic but you can try POM or EVA foam
- Top and bottom plates can be aluminum or FR4 — in this build I used empty FR4 boards as top/bottom
- Use an online 3D/model viewer to inspect the files in this repository

Fasteners and accessories:

- 6 × M3 × 18 socket-head screws
- 6 × M3 cap nuts
- 6 × silicone flat-head sleeves (as feet). Recommended inner diameter: 5.1 mm, inner height: 3.5 mm

## Firmware

I experienced unstable joystick and key behavior when flashing the original `mu3controller` firmware, so I modified Lee's keyboard/mouse firmware instead.

- Build and flash the firmware in the `firmware-B` folder with PlatformIO
- If you happen to have the Type-A potentiometer, try `firmware-A`, which includes adjustments for the pot curve

### Why I modified it

The original mouse implementation used relative movement with acceleration and cumulative error, which caused drift. I changed the slider to map directly to absolute mouse coordinates to eliminate drift.

## Repository Structure

- `Minigeki keyboard firmware-*`: firmware source code
- `img/`: images
- `model/`: model files
  - `top_pcb/`: top empty PCB
  - `above_PCB.step`: upper spacer
  - `under_PCB.step`: lower spacer
  - `layer.dxf`: spacer outline
  - `top.step`: top panel
  - `bottom.step`: bottom panel
  - `mini knob.STL`: slider knob

## License

MIT
