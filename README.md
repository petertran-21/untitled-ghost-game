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

# Installation
- Unzip the `untitled-ghost-game.zip` folder
- Open a terminal
- Run `cd untitled-ghost-game/`
- Run `cd resources/`
- Run `python resetScenes.py`
- Run `cd ..`
- Run `make`
- Run `./bin/myGame`
- Hit the right arrow key to progress through tutorial!

**NOTE!!!** The first scene has a slight bug with the camera. To fix it, move the Ghost down, then up!

## Resetting the game
If you want to reset the game, run the following commands...
- Run `cd resources/`
- Run `python resetScenes.py`
- Run `cd ..`
- Run `make`
- Run `./bin/myGame`

## Error Help

If you receive the `fatal error: 'SDL2/SDL_mixer.h' file not found` message upon running `make`, you can fix it by running the following command-line command...

- MacOS users
    - `$ brew install sdl2_mixer`
- Windows users
    - pretty sure this issue only exists for MacOS

## Connecting a Controller

Connect your controller to your computer via Bluetooth. There are good tutorials for this on YouTube. Next, run `./bin/myGame`. Note that the controller must be connected via Bluetooth to your computer before you run `./bin/myGame` for it to be recognized in the code! Look for `SDL_NumJoysticks() = 1` to be printed in the terminal.

### Movement w/ Controller
Move your controller's **left analog stick** to move the character up, down, right, and left. Diagonal movement for ghost is also supported but not for NPC.
For PS4 controller:
- Press **square button** to possess an NPC.
- Press **triangle button** to make boo noise. 
- Press **circle button** to use NPC's ability (only can do this if already possessing NPC).

(Tested on Xbox One and PS4 controllers)

### Movement w/ Keyboard
- Press **WASD** to move character up, left, down, and right. Diagnoal movmeent for ghost is also supported but not for NPC. 
- Press **E** to possess NPC. 
- Press **SPACE** to use ability of NPC.
- Press **P** to pause the game and open the menu.
- Press **M** to open the game map.
- Press **F** to boo.

### Notes
- We didn't have time for music, so we added start music but that's it!
