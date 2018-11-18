<h2><i> Description </i></h2>

Fast path finding algorithm for dynamic environments.

This algorithm is based on an ocrtree structure combined with an A star path algotithm.
It is designed to quickly find a path through a 3d point cloud.

<h2><i> Quick start </i></h2>

<ul>
  <li><i>Debug/ConsoleApplicationTree.exe</i> is the working winows application</li>
  <li><i>ConsoleApplicationTree/ConsoleApplicationTree.cpp</i> is the main source code file</li>
  <li><i>ConsoleApplicationTree/Window.cpp</i> is the code for displaying graphics</li>
</ul>

It is a <b>Visual studio</b> project written in <b>C++</b>

SDL library is already included in <b>externals</b> folder

Tutorial of how to add SDL lib to <b>vs</b> project can be found here <i>https://www.wikihow.com/Set-Up-SDL-with-Visual-Studio-2017</i> (from part 4)

<h2><i> Documentation </i></h2>

SDL is used for visualization purposes.
By default program is set to solve a task of finding a path in a 3d cube-like environment. X and Y coordinates of the start point can be set dynamically by aiming cursor on a preferable spot and pressing "s" button. Z coordinate is fixed on the upper edge of the the cube and the goal point is set to the top right corner on the bottom edge of the cube.
By pressing "a" you add 300 random obtacle points in the center part of the cube.
To add single point in a specific spot press "o", default z will be set to 10

Class "manager" recieves 1 integer (<b>depth</b>, default 6) that means how many times you can divide the environment in half, increasing the accuracy of its construction.
Class "AStar" receives the root node, minimum precision of search (integer = depth) and maximum precision of search (integer from 1 to depth)

Resulting path is saved to <b>pathset</b> array in AStar class.
<br></br>
<p align="center"><b>2D version</b></p>

In order to use algorithm in <b>2D</b> spaces, replace <i>ConsoleApplicationTree/ConsoleApplicationTree.cpp</i> file with <i>ConsoleApplicationTree2D.cpp</i> file from the root directory
<br></br>
Blue dots are path vectors, right crosses show occupied space, green crosses show free space.

<p align="center"><b> 2D variant representation, depth = 4 </b></p>
<p align="center">
  <image src="https://user-images.githubusercontent.com/29633052/48675325-811ba980-eb68-11e8-83a0-7f54ebbfaa3e.png" height="480"></image>
</p>

<p align="center"><b> 2D variant representation, depth = 6 </b></p>
<p align="center">
  <image src="https://user-images.githubusercontent.com/29633052/48675479-4f0b4700-eb6a-11e8-9333-860ef51dc11d.png" height="480"></image>
</p>
