#  minimum required cmake version: 3.1.15 support vs2019
cmake_minimum_required(VERSION 3.1.15)
project(OBViewer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)

set(OrbbecSDK_INCLUDE_DIRS "/Users/atharvp04/OrbbecSDK/include")
set(OrbbecSDK_LIBS "/Users/atharvp04/OrbbecSDK/lib/macOS/libOrbbecSDK.1.10.dylib")

add_executable(${PROJECT_NAME}
  src/DepthViewer.cpp
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
