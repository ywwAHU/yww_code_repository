cmake_minimum_required(VERSION 3.0.2)
project(getPng)


add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    cv_bridge
    image_transport
    geometry_msgs
    message_generation
)
find_package(OpenCV REQUIRED)




include_directories(
    ${catkin_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}

)


add_message_files(
  FILES
  ivsensorgps.msg
  ivsensorimu.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
)


add_executable(pub_png src/pub_png.cpp)
target_link_libraries(pub_png ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_executable(test_jpg src/test_jpg.cpp)
target_link_libraries(test_jpg ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_executable(pub_gps  src/get_gps.cpp)
target_link_libraries(pub_gps ${catkin_LIBRARIES} )
