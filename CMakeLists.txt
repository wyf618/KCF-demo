cmake_minimum_required( VERSION 2.8 )
project( Project )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread" )

#头文件目录
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include)

find_package( OpenCV 3.1 REQUIRED )

include_directories( 
    ${OpenCV_INCLUDE_DIRS} 
)

add_executable(Project src/detect.cpp  src/fhog.cpp  src/kcftracker.cpp  src/runtracker.cpp  )

target_link_libraries( Project ${OpenCV_LIBS} )



