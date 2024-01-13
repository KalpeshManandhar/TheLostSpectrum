# TheLostSpectrum
<div align ="center">
Demons have stolen the colors of land of Chrometerra!.

The land needs your help to restore its colors back.

Written in modern C++ , **using Raylib**

<div align ="left">

**Made as a game developement project**




## Table of contents
- [Introduction](#introduction)
- [Technical Specifications](#specifications)
- [Game Overview](#game-overview)
- [Game Design](#game-design)
- [Technical Architecture](#technical-architecture)
- [Art and Animation](#art-and-animation)
- [Testing](#testing)
- [Team](#development-team)

### Introduction
*The lost spectrum* is a single player 2D top down adventure game. The game was developed as a project in a game developement competition in two days.

It aims to include:
- visual story telling
- never before seen concept of narration
- interactive riddles

**Help the land of Chrometerra regain its vibrant colours now**

### Specifications
- The game is written in C++ with Raylib as graphics library.
- Full support for both Windows and linux. 
- Works fine in low spec systems.

### Game Overview
The game is can be enjoyed by all age groups and genders. It will particularly be enjoyable for gamers who like:
- Visual story telling
- Narrative driven game
- Old school 2D games
- Indie games

### Game Design
The game is set on a land of colors (Chromaterra), which has lost its colors due to damage to its heartstone, i.e. the Chromastone. The protagonist must go on a quest to collect all the stone fragments and restore the balance of colors in the land of Chrometerra.

**Game Mechanics**
- Use W, A, S, D to move.
- Use E to strike.
- Enter the riddle inputs via keyboard and press enter.

### Technical architecture
The game is made using the Concept of Object Oriented Programming in C++. Hence, it contains classes of various aspects needed to make the game, like:
- Entity class => To make player entity and enemy entity
- Game class => Control the flow of the game
- Animation class => Contains methods and attributes to animate player and enemy sprites
- Camera class=> Controls the camera movement in the game. Here it follows the protagonist, i.e the player.
- Dialogue class => Manages all the ingame dialogues with NPC and other interactibles.
- Interactible class => Tracks the interactables in the game including items, NPC and bosses
- Levelmap class => Handles the loading and updating of tileset in game.
- Lexer class => Parses the tileset ingame.
- Riddle class => Manages in game riddles.
- SplashScreen class => Used for naration and cut scenes in game.

All of these classes interact with each other to make the game alive.

### Art and Animation
The game uses all the free spritesheet and art availabe online. 

**Asset credits:**

- <a href ="https://cainos.itch.io/pixel-art-top-down-basic">Tileset</a>
- <a href ="https://rvros.itch.io/pixel-art-animated-slime">Slime</a>
- <a href ="https://www.pinterest.com/pin/405394403971243041/">Static boat</a>
- <a href ="https://www.pinterest.com/pin/726135139937622101/" > Boat </a>
- <a href ="https://www.pinterest.com/pin/726135139937622101/" > Player  </a>
- <a href ="https://luizmelo.itch.io/monsters-creatures-fantasy/download/eyJleHBpcmVzIjoxNzA1MDQwNzYwLCJpZCI6NTY0Njk1fQ%3d%3d.DU8kcPPALMSXLSjDIHgEQvSCN%2fY%3d"> Evil wizard</a>

### Testing
The game is still in its developmental phase- so hasn't been rigoursly tested.

### Development Team
- [Mamata]((https://github.com/Mamata-Maharjan))
- [Kalpesh](https://github.com/KalpeshManandhar)
- [Ishwor](https://github.com/optimistic-ish)

