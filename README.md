## Part 1: Textured Triangles

An extension of the classic OpenGL texture mapping demo. A 2×2 red/yellow checkered pattern is mapped onto three triangles with different UV coordinate mappings, producing visually distinct results from the same texture.

### Features Added
- Continuous 360° spin via timer callback
- **P** — pause spinning
- **C** — continue spinning
- **U / D** — move up / down
- **L / R** — move left / right
- **+ / -** — zoom in / out

### Screenshot
![Textured Triangles](screenshots/checkered.png)

---

## Part 2: Color Cube Flyby

An extension of the RGB colour cube flyby. The camera orbits the cube along a parametric curve. Three extra cubes with different colours and brightness levels bounce between two vertical wall planes.

### Features Added
- **R** — toggle Y-axis rotation of the whole scene
- **S** — stop flyby animation
- **C** — continue flyby animation
- **U / D** — move scene up / down (while stopped)
- **+ / -** — zoom in / out
- Three extra cubes: cyan (full brightness), magenta (60% brightness), orange (120% brightness)
- Two vertical wall planes (cyan-tinted left, magenta-tinted right)
- Cubes bounce between the walls

### Screenshot
![Color Cube Flyby](screenshots/colorcube.png)

---

## Build Instructions

```bash
# Install freeglut via vcpkg
cd C:\Users\kianj\vcpkg
.\vcpkg install freeglut

# Open folder in Visual Studio 2022 — detects CMakePresets.json automatically
# Build -> Build All
```

---

## AI Assistance Disclosure

Portions of this project were developed with the assistance of an AI tool (Claude by Anthropic). The feature implementations and understanding of the OpenGL/GLUT pipeline are the author's own. AI assistance was used to help structure and extend the provided starter code.
