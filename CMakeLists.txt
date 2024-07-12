cmake_minimum_required(VERSION 3.1.15)
project(OBRecorder)

# Set OpenCV directory
set(OpenCV_DIR /usr/lib/x86_64-linux-gnu/cmake/opencv4)

# Find OpenCV package
find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found. Please install OpenCV or specify OpenCV_DIR.")
endif()

# Find OrbbecSDK package
find_package(OrbbecSDK REQUIRED)
if(NOT OrbbecSDK_FOUND)
    message(FATAL_ERROR "OrbbecSDK not found. Please install OrbbecSDK or specify OrbbecSDK_DIR.")
endif()

add_executable(${PROJECT_NAME}
  main.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${OpenCV_LIBS}
  ${OrbbecSDK_LIBS}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${OpenCV_INCLUDE_DIRS}
  ${OrbbecSDK_INCLUDE_DIRS}
)

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)