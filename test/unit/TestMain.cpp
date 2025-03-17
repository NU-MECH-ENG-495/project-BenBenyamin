/**
 * @file TestMain.cpp
 * @brief This file contains the main function for running unit tests using the Google Test framework.
 * 
 * The main function initializes and runs all unit tests defined in the project. This file is conditionally
 * compiled only when the `UNIT_TEST` macro is defined, allowing it to be excluded from production builds.
 * 
 * @author Ben Benyamin
 * @date March 2025
 */

 #ifdef UNIT_TEST // Conditionally compile this file only if UNIT_TEST is defined

 #include <gtest/gtest.h> // Google Test framework
 
 /**
  * @brief The main function for running unit tests.
  * 
  * This function initializes the Google Test framework, parses command-line arguments, and runs all
  * registered unit tests. It returns the result of the test execution, which can be used to determine
  * the success or failure of the test suite.
  * 
  * @param argc The number of command-line arguments.
  * @param argv An array of command-line arguments.
  * @return An integer representing the result of the test execution (0 for success, non-zero for failure).
  */
 int main(int argc, char **argv)
 {
     // Initialize the Google Test framework
     ::testing::InitGoogleTest(&argc, argv);
 
     // Run all registered unit tests and return the result
     return RUN_ALL_TESTS();
 }
 
 #endif // UNIT_TEST