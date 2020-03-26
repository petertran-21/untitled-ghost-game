# Untitled Ghost Game

Untitled Ghost Game (lovingly shortened to UGG) is a 2D Exploratory Puzzle Game for CS 4730 at the University of Virginia Spring 2020 semester. The team that worked on it is as follows:
- Design
    - Josh Santana
    - Jennifer Liao
    - John Perez
- Engine
    - Austin Bunting
    - Brad Knaysi
    - Michelle Lovering
- SFX
    - Peter Tran
    - William Wong
    - Joseph Kim


## Installation
Connect your controller to your computer via Bluetooth. There are good tutorials for this on YouTube. Next, run `./bin/myGame`. Note that the controller must be connected via Bluetooth to your computer before you run `./bin/myGame` for it to be recognized in the code! Look for `SDL_NumJoysticks() = 1` to be printed in the terminal.

## Demo for character programming 
When the demo is started, the beach hub room is shown. Several characters will show up on the screen: ghost, pyromancer, and another NPC.

The following functionalities were implemented for this character:
 - movement of ghost
 - possession of pyromancer NPC by ghost
 - state ability of NPC
 - movement of NPC in cardinal directions (N,E,S,W) when possessed

 NPC Possession Instructions:
 - Uncomment line 69 and comment line 72 in MyGame.cpp in order to possess pyromancer NPC. 
 - Comment line 69 and uncomment line 72 in MyGame.cpp in order to possess archer NPC. 

### Movement w/ Controller
Move your controller's **left analog stick** to move the character up, down, right, and left. Diagonal movement for ghost is also supported but not for NPC.
For PS4 controller:
- Press **square button** to possess an NPC.
- Press **triangle button** to make boo noise. 
- Press **circle button** to use NPC's ability (only can do this if already possessing NPC).

(Did not test xBox controller, but PS4 controller was tested.)

### Movement w/ Keyboard
- Press **WASD** to move character up, left, down, and right. Diagnoal movmeent for ghost is also supported but not for NPC. 
- Press **E** to possess NPC. 
- Press **SPACE** to use ability of NPC.


### Comment on Collision Detection from Design Team
We have integrated a simple collision detection from the engine team, but have not yet integrated the fully functioning collision detection and resolution system due to time constraints across teams. We have designed two of our NPCs to be in collision with each other via the format provided by engine team so that we can just switch out the class functions for a fully working collision system. 

Following limitations:
- Current collision system detects collisions via x-axis only. 
- We have to hardcode the specific objects' ids into collisionSystem.cpp. 
- Collision resolution resolves to the same point when x-axis collision is detected.
- Collision system does not return which specific objects have collided.

### General Comments from Design Team
For character programming assignment, we inmplemented two NPC's abilities and the ghost character's possession as the main components of our main character. 