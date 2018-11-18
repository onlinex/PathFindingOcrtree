<h2><i> Description </i></h2>

Fast path finding algorithm for dynamic environments.

This algorithm is based on an ocrtree structure combined with an A star path algotithm.
It is designed to quickly find a path through a 3d point cloud.

<h2><i> Documentation </i></h2>

SDL is used for visualization purposes.
By default program is set to solve a task of finding a path in a 3d cube-like environment. X and Y coordinates of the start point can be set dynamically by aiming cursor on a preferable spot and pressing "s" button. Z coordinate is fixed on the upper edge of the the cube and the goal point is set to the top right corner on the bottom edge of the cube.
By pressing "a" you add 300 random obtacle points in the center part of the cube.
To add single point in a specific spot press "o"

Debug/ConsoleApplicationTree.exe contains the working winows application
ConsoleApplicationTree/ConsoleApplicationTree.cpp contains the main source code file
ConsoleApplicationTree/Window.cpp contains the code for displaying graphics

Class "manager" recieves 1 integer (<b>depth</b>, default 10) that means how many times you can divide the environment in half, increasing the accuracy of its construction.
Class "AStar" receives the root node, minimum precision of search (integer = depth) and maximum precision of search (integer from 1 to depth)

Resulting path is saved to <b>pathset</b> array in AStar class.

<br>
In order to use algorithm in 2D spaces, replace ConsoleApplicationTree/ConsoleApplicationTree.cpp file with ConsoleApplicationTree2D.cpp file from the root directory
<p align="center"><b> 2D variant representation, depth = 4 </b></p>
Blue dots are path vectors, right crosses show occupied space, green crosses show free space.
<p align="center">
  <image src="https://user-images.githubusercontent.com/29633052/48675325-811ba980-eb68-11e8-83a0-7f54ebbfaa3e.png" height="480"></image>
</p>

<p align="center"><b> 2D variant representation, depth = 6 </b></p>
<p align="center">
  <image src="https://user-images.githubusercontent.com/29633052/48675479-4f0b4700-eb6a-11e8-9333-860ef51dc11d.png" height="480"></image>
</p>
