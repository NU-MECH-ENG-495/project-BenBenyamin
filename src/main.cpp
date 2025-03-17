/**
 * @file main.cpp
 * @brief This file contains the main function for rendering a 3D model using the Canvas and TriangleObject classes.
 * 
 * The program loads an STL file, processes the 3D model, and renders it onto a 2D canvas. It applies transformations
 * such as scaling, rotation, and translation to the model and generates multiple PPM images of the rendered model.
 * 
 * @author Ben Benyamin
 * @date March 2025
 */

 #include <iostream>
 #include <vector>
 #include <cmath>
 #include <filesystem>
 #include "canvas.h"
 #include "triangle.h"
 #include "stl.cpp"
 #include "triangle_object.h"
 
 /**
  * @brief The main function for rendering a 3D model.
  * 
  * This function initializes a canvas, loads a 3D model from an STL file, applies transformations to the model,
  * and renders it onto the canvas. It generates multiple PPM images of the rendered model with different rotations.
  * 
  * @return 0 on successful execution.
  */
 int main()
 {
     // Initialize canvas dimensions
     int width = 1000, height = 1000;
     Canvas canvas(height, width);
 
     // Set the camera normal vector
     std::vector<float> cameraNormal = {0.0f, 0.0f, 1.0f};
     canvas.setCameraNormal(cameraNormal);
 
     // Load the STL file
     std::string filename = "../example/ASCII.stl";
     TriangleObject triangleObject(filename); // Create TriangleObject and load the STL file
     std::cout << "Loaded " << triangleObject.size() << " triangles from " << filename << std::endl;
 
     // Define the rotation center for transformations
     std::vector<float> rotationCenter = {500.0f, 500.0f, 350.0f};
 
     // Apply transformations to the 3D model
     canvas.clear();
     triangleObject.scale(4.5); // Scale the model
     triangleObject.rotateAroundY(-90, rotationCenter); // Rotate around the Y-axis
     triangleObject.translate(-200, 0, 0); // Translate the model
     triangleObject.rotateAroundY(-15, rotationCenter); // Rotate around the Y-axis again
 
     // Render the model and generate PPM images
     for (int i = 0; i < 3; i++)
     {
         triangleObject.project(canvas); // Project the model onto the canvas
         triangleObject.rotateAroundX(6, rotationCenter); // Rotate around the X-axis
 
         // Save the rendered canvas as a PPM file
         std::string outFileName = "../output/MODEL_" + std::to_string(i) + ".ppm";
         canvas.writePPM(outFileName);
         canvas.clear(); // Clear the canvas for the next iteration
     }
 
     return 0; // Exit the program
 }