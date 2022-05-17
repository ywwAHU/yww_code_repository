cmake_minimum_required(VERSION 3.0.2)
project(getPng)

find_package(catkin REQUIRED COMPONENTS  
    roscpp
    std_msgs
    cv_bridge
    image_transport
)

catkin_package(


)

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIR}
)

add_executable(test src/test_jpg.cpp)
target_link_libraries(test ${catkin_LIBRARIES} ${OpenCV_LIBS})