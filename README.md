# Table of Contents
- [Table of Contents](#table-of-contents)
- [PenguinGame](#penguingame)
  - [General Rules](#general-rules)
  - [Initialization Stage](#initialization-stage)
  - [Placement Stage](#placement-stage)
  - [Movement Stage](#movement-stage)
  - [Determining Winner](#determining-winner)
  - [Run the application](#run-the-application)
# PenguinGame
"Penguin Game" is a university team project that transforms the board game "Hey, That's My Fish!" into a digital rendition. The project features a Graphical User Interface (GUI) built using fundamental WinAPI capabilities.
## General Rules
"Hey, That's My Fish!" is a strategy board game where players control penguins on a grid with ice and fish. Players take turns moving their penguins in straight lines, collecting fish from the tiles they move over. As penguins move, the tiles they leave behind are removed, creating a shifting game board where players aim to collect the most fish by the end to win.
## Initialization Stage
![](https://github.com/TheBestChelik/PenguinGame/blob/master/img/Initialization.png?raw=true)
![]()

To set up the game, follow these steps during the initialization stage:

1. Determine the board's dimensions in cells (recommended: 20x20).
2. Choose the size of each cell (recommended: 25 pixels).
3. Specify the number of players and the quantity of penguins per player.
4. Players should input their names and select colors for their penguins.


## Placement Stage
![](https://github.com/TheBestChelik/PenguinGame/blob/master/img/PlacementFinished.png?raw=true)

During the placement phase of "Hey, That's My Fish!," players take turns placing their penguins on unoccupied tiles of the game board. Each player's penguins must be placed on a tile with only one fish, and once placed, they cannot be moved until the main gameplay starts (Movement Stage). To place the penguin layer has to click on the chosen cell. Players strategically position their penguins to maximize their fish collection potential and establish a strong starting position for the subsequent movement phase.

Placement info
## Movement Stage
In the movement stage of "Hey, That's My Fish!," players take turns moving their penguins in straight lines to adjacent tiles with fish. Collected fish are tallied. Tiles vacated by penguins are removed, altering the board's layout. The movement phase ends when no valid moves remain, and players aim to gather the highest fish count to win.

To initiate a penguin's movement, a player selects their desired penguin and then clicks on the target cell where they intend to relocate the penguin.

## Determining Winner
The winner of "Hey, That's My Fish!" is the player with the highest accumulated fish count collected by their penguins on the game board when the movement stage concludes. The player with the most fish wins the game.
## Run the application
   Clone repository
   ```bat 
   gh repo clone TheBestChelik/PenguinGame
   ```
   Compile project
   ```bat
   cd PenguinGame
   make 
   ```