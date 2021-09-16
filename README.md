# KMITL C Programming Project: 3D Projection Engine 

## Proposal Structure:
The proposal will include the following sections:
* Project Title: 3D Projection Engine 
* Description: This program (1.) projects a 3D illusion into a 2D plane (2.) by drawing inclined or declined lines from  coordinates or vertices in a certain angle from a perspective point (3.) to make a 3D object for detailed method please read the detail below.


## Detailed Description:
Please read the simplified description above first.
* Checkpoint (1.) \
We first need a console engine that creates a 'blank' window application from win32 api,directx or any other optional libary in order to show us the output/result and serve us as a GUI for example olcgameengine window which is made up of 6base number 6x6 array in which each array is translated from a coordinate(x,y) with the following formula: 
array[i] = y *(i in range (x,y)) + x 
* Checkpoint (2.)\
Next we need a base engine from any graphical libary composed of functions that has a mathematics formula that receives our parameter/input and logic to translate the variable and calculate the "object" and  "projection" output for us. For more detail about the method please read the documentation provided below.
* Checkpoint (3.)\
Finally we can observe the outcome from our designated "perspective", also we can make the object dynamic by constantly updating its position precisely using "matrix rotation" and mathematics.
* Room for improvement \
Additionally a camera can be made by constantly updating our "perspective" upon WASD input thus ray-casting and ray-tracing is possible to make up a viable first person game also we can add texture to the object or import a texture by reading a FILE which contains our desired parameter(input) in a specified format.



## Documentation:
* **ENGINE Example of a 2D Plane Window Application.** 
![](images/2dgameengineexample.png)
![](images/p2.png)
* **OBJECT 3D Projection method on a 2D plane.**
![](images/3dprojection.png)

![](images/perspective.png) \
P are vertices of the object
* **PERSPECTIVE Matrix relation with the object.**
![](images/objectandperspective%20relation.png)
*  **MATRIX ROTATION relation with object movement method.**
![](images/matrix%20rotation.jpg)



## Trivia,Reference and Requirements:
* C/C++ Optional Lbaries: \
-OpenGL \
-SFML \
-DirectX \
-olcgameengine https://www.youtube.com/watch?v=u5BhrA8ED0o&t=1080s&ab_channel=javidx9 \
-2DgameEngine Derived from Direct2D 
* Recommended IDE: \
Visual Studio IDE 

## Example of the finalized project.

![](images/image.png)
