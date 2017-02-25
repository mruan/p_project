cmake_minimum_required (VERSION 2.7)
project (paillier_project)

include_directories(include /usr/local/include/)
link_directories(/usr/local/lib/)

# Find all source files
file(GLOB SOURCES "src/*.cpp")

add_executable(test01 ${SOURCES})
target_link_libraries(test01 paillier gmp)

#if (GMP_FOUND)
#  include_directories(${BZIP_INCLUDE_DIRS})
#  target_link_libraries(test_01 paillier ${GMP_LIBRARY})
#endif (GMP_FOUND)
