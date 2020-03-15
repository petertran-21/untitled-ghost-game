# untitled-ghost-game

## Instructions for using a Controller (Xbox / PS4)
Connect your controller to your computer via Bluetooth. There are good tutorials for this on YouTube. Next, run `./bin/myGame`. Note that the controller must be connected via Bluetooth to your computer before you run `./bin/myGame` for it to be recognized in the code! Look for `SDL_NumJoysticks() = 1` to be printed in the terminal.

## Demo for spritesheets and controllers
When the demo is started the characters idle animation will be played.

### Movement w/ Controller
Move your controller's **left analog stick** to move the character up, down, right, and left. The walking animation will be played when moving. Releasing the stick will stop the character and show the idle animation.

### Character Scaling w/ Controller
Pressing the **A button** increases the scale of the character. Pressing the **B button** decreases the scale of the character.
