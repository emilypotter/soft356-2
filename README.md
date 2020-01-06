# SOFT356 Coursework 2

To open and control the software download the zip and unzip it. Open the open Load_3D_model_2.sln in visual studio and rebuild the project. Run the code and follow the on screen instrustions on how to interact with the program.

The program code runs from a main game loop which updates the game area, plays the background music and renders the game. The rendering of the game consists of setting up the cameras (which is mainly done is the camera.h header file), the lighting and draws the characters. The characters are drawn using the model.cpp file which handles the animation and the mesh.cpp file which contains all the vertex, index and other information needed to render. The background is then drawn as a skybox so the user can move the camera around and look around the game environment.

I started with a project I found on GitHub which was based around using skeletons in assimp to animate characters. I changed this by allowing the user to move the characters around and allowing them to change the environment the characters are in by changing the skybox.

Video report link: https://youtu.be/ePePqRR2nBs
