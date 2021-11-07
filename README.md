# Box2D Pinbal Project

A pinball game made with Box2D for physics class.

Link to the project: https://github.com/Alejandromo125/Box2D_GroupProject

## Members
* **Álvaro Milla: https://github.com/mrmile**
* **Alejandro Martin: https://github.com/Alejandromo125**
* **Gerard Martinez: https://github.com/GerardMartinez02**
* **Albert Ramisa: https://github.com/Taks7**
 
## Controls
### Gameplay Keys
Enter key: Start the game

Space Bar: Start the game but with...

Left Key: Move left stick

Right Key: Move right stick

Down Key: Activate spring

### Debugging Keys
F1: To view colliders

Mouse left click on the ball while in view colliders mode to drag the ball anywhere.

## Combos and exciting stuff
### Diamonds
The small ones makes you score 3 points and the big one 5.
### Holes
Adds 150 points to your score and the ball respawns on the spring.
### Ring Combo
You can score two times more points during 15 seconds.
### Multi Ball Ready Combo
It spawns golden balls on the scene that will make you score points.
### Egg Penalty
It makes you loose score points instead of wining them during 15 seconds.
### Extra stuff
Instead of having limited tries defined by lives, you can throw the ball as many times as you want until the time runs out wich makes the experience much more exciting and enjoyable.

If you enter the game pressing the Space Bar instead of the Enter key a motivating song will be played instead to cheer your mood up.

## Development
At first it wasn't easy to deal with Box2D and its functions, but after working with it we figured out the basic concepts and started working with it. The only but actually very problematic issue we've had is with eliminating the collision shapes from the world to avoid the objects colliding with them. Specially with the ones stored in lists where the program misteriously skips the instruction to iterate to the next element of the list.
