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


## Error Help

If you receive the `fatal error: 'SDL2/SDL_mixer.h' file not found` message upon running `make`, you can fix it by running the following command-line command...

- MacOS users
    - `$ brew install sdl2_mixer`
- Windows users
    - pretty sure this issue only exists for MacOS

## Connecting a Controller

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
- Press **IJKL** to move the camera.
- Press **ZX** to scale the camera.
- Press **E** to possess NPC. 
- Press **SPACE** to use ability of NPC.
- Press **P** to pause the game and open the menu.
- Press **M** to open the game map.

### Enemy Programming Demo
Implemented some NPC and object interactions. You can do the following with the NPCs present:
- All NPCs can collect item pouch object
- Pyromancer NPC can set fire to shrub (either on the shurb or next to shrub)
- Collectors will pick up a crab on collision, the crab then sticks to your position until you press space. Then the crab is placed at the adjacent tile (in the direction you are facing) and you have a about a second or so before you pick it up again
- Operators can turn on/off valves by standing next to them and pressing space. The corresponding water jets linked to the valve will turn on and create a stream of water. If an npc or crab steps into the water, they get pushed to the end of the stream. 
- Excavators can dig up rocks by standing next to them and pressing space. This will allow npcs to pass through that space



### Notes
- We connected the beach and forest areas directly for the sake of this demo.
- The forest area is currently not interactive, but you can navigate the area freely.
- The beach is mostly interactive but some of the object collisions may not be working.
