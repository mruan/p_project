cmake_minimum_required (VERSION 2.7)
project (paillier_project)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#find_package(GMP REQUIRED)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_BUILD_TYPE DEBUG)

include_directories(include /usr/local/include/)
link_directories(/usr/local/lib/)

# Find all source files
#file(GLOB SOURCES "src/*.cpp")

add_library(agent src/agent.cpp)
target_link_libraries(agent paillier gmp)

#add_executable(test01 ${SOURCES})
#target_link_libraries(test01 agent)

#if (GMP_FOUND)
#  include_directories(${BZIP_INCLUDE_DIRS})
#  target_link_libraries(test_01 paillier ${GMP_LIBRARY})
#endif (GMP_FOUND)
