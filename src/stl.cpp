/**
 * @file stl.cpp
 * @brief This file contains functions for reading and processing STL files.
 * 
 * The file includes functions to generate random colors and read triangle data from an STL file.
 * The triangles are stored in a shared pointer to a vector of TriangleSurface objects, and each
 * triangle is assigned a color for rendering purposes.
 * 
 * @author Ben Benyamin
 * @date March 2025
 */

 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <vector>
 #include <cstdlib>
 #include <ctime>
 #include <memory> // for std::shared_ptr
 #include "triangle.h"
 #include "canvas.h"
 
 /**
  * @brief Generates a random color as a vector of three floats (RGB).
  * 
  * Each component of the color (red, green, blue) is a random value between 0.0 and 1.0.
  * 
  * @return A vector containing three floats representing the RGB color.
  */
 std::vector<float> getRandomColor() {
     return {static_cast<float>(rand()) / RAND_MAX, 
             static_cast<float>(rand()) / RAND_MAX, 
             static_cast<float>(rand()) / RAND_MAX};
 }
 
 /**
  * @brief Reads triangle data from an STL file and stores it in a vector of TriangleSurface objects.
  * 
  * This function reads an ASCII STL file, extracts vertex data for each triangle, and assigns a color
  * to the triangle. The triangles are stored in a shared pointer to a vector of TriangleSurface objects.
  * 
  * @param filename The path to the STL file.
  * @param triangles A shared pointer to a vector of TriangleSurface objects where the triangle data will be stored.
  */
 void readSTL(const std::string &filename, std::shared_ptr<std::vector<TriangleSurface>> triangles)
 {
     srand(0); // Set the seed for random color generation
     std::ifstream file(filename);
 
     // Check if the file was successfully opened
     if (!file.is_open())
     {
         std::cerr << "Error: Unable to open STL file " << filename << std::endl;
         return;
     }
 
     std::string line;
     std::vector<float> A(3), B(3), C(3); // Vectors to store vertex coordinates
     std::vector<float> color = {0.0f, 1.0f, 1.0f}; // Default color (cyan)
 
     int faceCounter = 0; // Counter to track face pairs
 
     // Read the file line by line
     while (std::getline(file, line))
     {
         std::istringstream iss(line);
         std::string keyword;
         iss >> keyword;
 
         // Check if the line contains vertex data
         if (keyword == "vertex")
         {
             // Read the coordinates of the first vertex
             if (!(iss >> A[0] >> A[1] >> A[2]))
                 continue;
 
             // Read the coordinates of the second vertex
             std::getline(file, line);
             std::istringstream issB(line);
             issB >> keyword >> B[0] >> B[1] >> B[2];
 
             // Read the coordinates of the third vertex
             std::getline(file, line);
             std::istringstream issC(line);
             issC >> keyword >> C[0] >> C[1] >> C[2];
 
             // Assign a random color to every 1000th face
             if (faceCounter % 1000 == 0)
             {
                 color = getRandomColor(); // Generate random color
             }
 
             // Add the triangle to the vector
             triangles->emplace_back(A, B, C, color);
 
             faceCounter++; // Increment the face counter
         }
     }
 
     file.close(); // Close the file
 }