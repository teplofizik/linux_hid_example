cmake_minimum_required(VERSION 2.10) # �������� ������ CMake.
project(hid_example)

set (CMAKE_CXX_STANDARD 17)

add_executable(hid_example hid_example.cpp HidDevice.cpp)
target_link_libraries(hid_example pthread hidapi-hidraw)
