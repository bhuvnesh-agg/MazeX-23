# MazeX-22
Our final submission code for MazeX 2023 conducted by Robotics Club, IIT(BHU)

## Approach
We designed our robot with 5 IR sensors up front, facing downwards. Let's number these sensors from left to right as 1 to 5. Using this sensor design, we follow the following algorithm:
1. If only sensor 3 detects the line while the other four output 0, continue straight.
2. If any of the sensors 2 or 4 output 1, straighten the bot in the right or left directions respectively.
3. If either sensors (1,2) or sensors (4,5) return 1, then turn left or right respectively. Since the bot was Rear-Wheel Drive, with a castor up front, a little delay was added to ensure that the bot stays on track.
4. Stop if all sensors return 1.
5. Take a U-Turn if all sensors return 0.

## Maze-Solving
For solving the maze, we use a basic Left-Hand Algorithm. That is, if given a choice among going straight, taking a left and taking a right; the robot always turns left. This works in this case as the maze has no loops.

## Implementation
The two motors have been defined separately in the code, and turns are made through introducing speed differences in the two.
Following functions are used to perform different operations:
- read_sensors: runs digitalRead on all sensors and updates the corresponding variables
- set_speed: checks for negative speeds and analogWrites into the motors accordingly
Inside the loop, the bot continuously reads from the sensors, and assigns an error value according to the approach above. This error value is then used to calculate PID, which sets the wheel speed accordingly.
Turns, U-Turns and Stop are defined separately.

## Contributors
- Bhuvnesh Aggarwal
- Dushyant Agrawal
- Mayank Agrawal
- Nikita Gupta
