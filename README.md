# Cham City 3D

ChamCity3D is an open-source 3D simulation project designed to replicate the Cham City Center, a prominent mall located in Damascus, Syria. Built with modern OpenGL (core profile), the project is designed for immersive graphics programming and rendering.

## Features
- Accurate 3D representation of the Cham City Center.
- Custom shader pipeline for advanced rendering.
- Input handling with frame-independent processing.
- Extensible architecture for adding new features and components.
- Phong Lighting is used for lighting the scene.
- Reflections are used in the storefronts and the outside world like cars, ground, etc...
- Blending is used for drawing transparent objects.
- Instancing is used for increasing performance.
- MSAA (Multisample Anti-Aliasing) is used for a better 3D graphics experience.
- Cubemaps used for skybox and reflections.
- Depth testing to prevent objects from rendering in the front while they're supposed to be behind other objects.
- 3D audio using the irrKlang library for a better 3D experience.
- transformations for objects like an elevator, escalators, cars, etc...
- Day/night mode.
- A camera with two modes: Free Camera (First-Person View) and fly mode.
- And more...

## Prerequisites
Before building ChamCity3D, ensure you have the following installed on your system:

- A C++17-compatible compiler
- CMake (minimum version 3.0)
- git

## Building the Project

### Windows
1. Clone the repository:
   ```sh
   git clone https://github.com/Zaid-Al-Habbal/cham-city-3D.git
   cd cham-city-3D 
   ```
2. Create a `build` directory and run CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   ```
3. Open the generated Visual Studio solution and build the project.

### Linux
1. Clone the repository:
   ```sh
   git clone https://github.com/Zaid-Al-Habbal/cham-city-3D.git
   cd cham-city-3D
   ```
2. Create a `build` directory and run CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

### MacOS
1. Follow the Linux instructions, ensuring that your OpenGL framework is correctly linked.

## Usage
1. Run the generated executable from the `bin` directory:
   ```sh
   ./Cham-City-3D
   ```
2. Use the following controls to interact with the application:
   - **W/A/S/D**: Move the camera
   - **Mouse**: Look around
   - **LEFT_MOUSE_BOTTUN**: toggle light mode.
   - **RIGHT_MOUSE_BOTTUN**: toggle camera mode.
   - **KEY_0 & KEY_1 & KEY_2**: to use elevator between the ground, first and second floor. 
   - **ENTER**: to enter or get out of the Lamborghini.

## Project Structure
- **src/**: Contains the source code for the application
- **includes/**: Header files and third-party libraries
- **resources/**: Models, textures, and shaders used in the simulation
- **cmake/**: CMake modules for finding dependencies
- **bin/**: Compiled executables and resources

## Contribution
Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Submit a pull request detailing your changes.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

---

Enjoy exploring Cham City Center in 3D!

