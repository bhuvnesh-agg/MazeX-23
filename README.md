# MazeX-22
Our final submission code for MazeX 2023 conducted by Robotics Club, IIT(BHU)

## Approach
We designed our robot with 5 IR sensors up front, facing downwards. Let's number these sensors from left to right as 1 to 5. Using this sensor design, we follow the following algorithm:
1. If only sensor 3 detects the line while the other four output 0, continue straight.
2. If any of the sensors 2 or 4 output 1, straighten the bot in the right or left directions respectively.
3. If either sensors (1,2) or sensors (4,5) return 1, then turn left or right respectively. Since the bot was rwd, with a castor up front, a little delay was added to ensure that the bot stays on track.
4. Stop if all sensors return 1.
5. Take a U-Turn if all sensors return 0.
