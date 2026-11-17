# cub3D - 42 Common Core

A 3D graphical raycasting game engine inspired by the classic **Wolfenstein 3D** (1992), developed as part of the 42 Common Core curriculum using C and MiniLibX.

---

## Table of Contents
- [About the Project](#about-the-project)
- [Features](#features)
- [Controls](#controls)
- [Map Format (.cub)](#map-format-cub)
- [Compilation & Execution](#compilation--execution)
- [Architecture & Algorithms](#architecture--algorithms)

---

## About the Project
`cub3D` explores realistic 3D raycasting in a first-person perspective. The raycaster operates in a 2D grid map and projects vertical slices of textured walls on screen according to the player's position and viewing angle.

---

## Features
### Mandatory
- **DDA Raycasting**: Digital Differential Analysis algorithm for fast, grid-based raycasting.
- **Fisheye Correction**: Perpendicular wall distance projection to eliminate fisheye distortion.
- **Directional Wall Textures**: Dynamic orientation detection displaying distinct textures for North (`NO`), South (`SO`), East (`EA`), and West (`WE`) walls.
- **Floor & Ceiling Colors**: Solid 24-bit RGB rendering for ceiling and floor planes.
- **Wall Collisions & Sliding**: Independent axis collision checking allowing smooth sliding along walls.
- **Clean Resource Management**: Zero memory leaks across all termination triggers (`ESC` key, window close button).

### Bonus (`cub3D_bonus`)
- **Minimap System**: Real-time 2D radar overlay with a circular field-of-view, displaying player position, walkable corridors, and surrounding walls.

---

## Controls

| Key | Action |
| :--- | :--- |
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` (Left Arrow) | Rotate camera left |
| `→` (Right Arrow) | Rotate camera right |
| `ESC` / `[X]` | Exit game cleanly |

---

## Map Format (.cub)
The map file must use the `.cub` extension and adhere to the following structure:

```cub
NO ./src/textures/xpm/mario_chest.xpm
SO ./src/textures/xpm/mario_lucky_block.xpm
WE ./src/textures/xpm/mario_star.xpm
EA ./src/textures/xpm/mario_mushroom.xpm

F 220,100,0
C 0,100,220

111111
100001
100N01
111111
```

- **Identifiers**:
  - `NO`, `SO`, `WE`, `EA`: Paths to `.xpm` textures for each wall face.
  - `F`, `C`: RGB color components in the range `[0, 255]`.
- **Map Characters**:
  - `0`: Empty walkable space.
  - `1`: Wall.
  - `N`, `S`, `E`, `W`: Player starting position and spawn orientation.
  - Space (` `): Unused exterior padding.
- **Rules**:
  - The map must be completely surrounded/enclosed by walls (`1`).
  - No empty lines are permitted inside the map.

---

## Compilation & Execution

### Prerequisites
- **Linux**: `make`, `gcc`, `libx11-dev`, `libxext-dev`, `libbsd-dev`
- **macOS**: `make`, `clang` with Cocoa & OpenGL frameworks (bundled by default)

### Build Commands

```bash
# Compile mandatory executable (cub3D)
make

# Compile bonus executable (cub3D_bonus)
make bonus

# Clean object files
make clean

# Full clean (removes executables and libraries)
make fclean

# Rebuild everything
make re
```

### Running the Game

```bash
# Mandatory
./cub3D maps/basic.cub

# Bonus (with Minimap)
./cub3D_bonus maps/basic.cub
```
