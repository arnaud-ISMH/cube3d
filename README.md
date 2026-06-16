*This project has been created as part of the 42 curriculum by lchapot and adeflers.*

# cub3D #

## Description

**cub3D** is a graphic design project inspired by *Wolfenstein 3D*. The goal is to create a simple 3D engine using the **raycasting** technique and the **MiniLibX** library.

The program parses a .cub file with the map, textures and colors, then renders a first-person view game.

This project focuses on:

* Raycasting basics
* Graphics programming
* Event handling
* File parsing and validation
* Memory management

### Bonus Features

The bonus part extends the mandatory project with additional gameplay and graphical features such as:

* Mouse-controlled camera rotation
* Animated doors
* Minimap
* Sprites and interactive elements
* Wall collisions

## Raycasting Overview

The rendering engine uses the raycasting algorithm:

1. A ray is projected for every vertical column of the screen.
2. The engine calculates the distance to the first wall hit.
3. The wall height is determined according to the distance.
4. The appropriate texture is applied.
5. The frame is displayed and refreshed continuously.

---

## Project Structure

cub3D/
├── includes/
├── srcs/
├── bonus/
├── textures/
├── maps/
├── libft/
├── minilibx-linux/
├── Makefile
└── README.md

---

## Instructions

### Compilation

make

### Execution

./cub3D maps/mapname.cub

### Controls

| Key   | Action                |
| ----- | --------------------- |
| W     | Move forward          |
| S     | Move backward         |
| A     | Move left             |
| D     | Move right            |
| ← / → | Rotate camera         |
| Mouse | Rotate camera (bonus) |
| ESC   | Exit game             |
| E     | Open door             |
| Space | Eat monster           |

---

## Example Map

```text
111111111111
100000000001
100011000001
1000N0000001
100000000001
111111111111
```

Legend:

* `1` → Wall
* `0` → Empty space
* `N`, `S`, `E`, `W` → Player starting position + orientation
* Bonus " `X` → Monster and `D` → door

## Resources

### Documentation

* MiniLibX Documentation
https://harm-smits.github.io/42docs/libs/minilibx

* cub3d basics
https://harm-smits.github.io/42docs/projects/cub3d?utm_source=chatgpt.com
https://42-fran-byte-f94097.gitlab.io/docs/cub3d/cub3d-approach-en/?utm_source=chatgpt.com#/

* Raycasting Tutorial
https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents
https://www.youtube.com/watch?v=gYRrGTC7GtA&list=PLCXqoZAc8-tyDSaO8jnabOEFhdTQfx77_

* Learn OpenGL (graphics concepts)
https://learnopengl.com

### AI Usage

Artificial Intelligence tools were used as learning assistants during the development of this project.

Tasks where AI assistance was used:

* Understanding raycasting concepts.
* Understanding the DDA algorithm.
* Debugging specific implementation issues.
* Drafting and proofreading this README.
