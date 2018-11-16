Fast path finding algorithm for dynamic environments

<h2><i> Description </i></h2>

This algorithm is based on an ocrtree structure combined with an A star path algotithm.
It is designed to quickly find a path through a 3d point cloud.

<h2><i> Documentation </i></h2>

SDL is used for visualization purposes.
By default program is set to solve a task of finding a path in a 3d cube-like environment. X and Y coordinates of the start point can be set dynamically by aiming cursor on a preferable spot and pressing "s" button. Z coordinate is fixed on the bottom edge of the the cube and the goal point is set to the top right corner on the upper edge of the cube.
By pressing "a" you add 300 random obtacle points in the center part of the cube.
To add single point in a specific spot press "o"
