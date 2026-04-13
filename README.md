# Arkanoid (C++ / Chili DirectX Framework)

A classic **Arkanoid / Breakout-style game** implemented in C++ using the *Chili DirectX Framework*.  
This project focuses on low-level game logic, custom mechanics, and programmatic level generation.

## 🎮 Features

- Classic Arkanoid gameplay (paddle, ball, bricks)
- Multiple brick types with unique effects:
  - Indestructible bricks
  - Multi-hit bricks
  - Speed modifiers
  - Extra life
  - Power-ups (multi-ball, catcher, larger paddle, etc.)
- Meter system with abilities:
  - 🔵 Slow down ball (hold CTRL)
  - 🟢 Weapon system (press TAB)
  - 🔴 Extra life (automatic when full)
- Player choice mechanics:
  - Select a meter after early levels
  - Later choose a penalty (faster ball or smaller paddle)
- Multi-ball support
- Programmatically generated levels (grid-based system)

## 🧠 Technical Highlights

- Written in **C++**
- Uses **custom game loop and rendering via Chili DirectX Framework**
- Levels are generated using a **grid-based mathematical system**
- Manual control over:
  - Collision detection
  - Game state handling
  - Object management
- No external game engine (Unity/Unreal) — fully code-driven

## 🕹 Controls

| Action | Key |
|------|-----|
| Move paddle | Arrow keys |
| Slow ball (blue meter) | Hold CTRL |
| Shoot (green meter) | TAB |
| Menu / back | ESC |
| Choice screens | B / G / R |

## 🧩 Game Mechanics

### Bricks
Different colored bricks have different effects:
- Orange → Indestructible  
- Gray → Two-hit  
- Magenta → +1 Life  
- Yellow → Speed up ball  
- Blue / Red / Green → Meter boost  
- Scarlet → Larger paddle  
- Dark blue → Multiple balls  
- Light green → Catcher  
- Purple → Fill meter  

### Meters
- Blue meter → slows the ball (manual activation)
- Green meter → enables shooting
- Red meter → grants extra life when full

### Choice System
- Early game: choose a meter
- Later: choose a penalty (adds difficulty)

## 🛠 Build & Run

This project uses the **Chili DirectX Framework**, so make sure:

- You are on **Windows**
- You have **Visual Studio** installed
- The framework is properly set up

Steps:
1. Open the solution in Visual Studio
2. Build the project
3. Run the game

## 📸 Screenshots

(Add your screenshots here)

## 📜 License

This project is based on the **Chili DirectX Framework**.

Original framework:
- Copyright © PlanetChili

This project is licensed under:

> **GNU General Public License v3.0 or later**

See `License.txt` for full details.

## 🙋 About

This project was created as a **learning project** to practice:
- C++ programming
- Game logic and architecture
- Low-level graphics and input handling

---
