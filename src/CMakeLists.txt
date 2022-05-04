cmake_minimum_required(VERSION 3.22)

project(
    opencv_notes
    VERSION 1.0.0
    LANGUAGES CXX)

# set OpenCV_DIR variable equal to the path to the cmake
# files within the previously installed opencv program

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

# tell the build to include the headers from OpenCV
include_directories( ${OpenCV_INCLUDE_DIRS} )

# specify the executable target to be built
add_executable(opencv_notes test.cpp)

# tell it to link the executable target against OpenCV
target_link_libraries(opencv_notes ${OpenCV_LIBS} )