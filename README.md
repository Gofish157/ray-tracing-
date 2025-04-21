# Raytrace SDL

A C++ program using SDL3 that demonstrates basic ray tracing from the mouse position and interaction with a moving circular obstacle.

## Description

- 150 rays are emitted from the mouse pointer at different angles.
- Rays are rendered until they either hit an obstacle or reach the screen bounds.
- There are two circles on the screen:
  - One follows the mouse.
  - The other moves horizontally and bounces off the window edges.
- Circle rendering and collision detection are implemented manually (no SDL primitives used for circles).
