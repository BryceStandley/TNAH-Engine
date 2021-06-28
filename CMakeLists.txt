# Set cmake minimum version.
cmake_minimum_required(VERSION 3.15)

# Set the project details.
set(PROJECT_NAME TNAH-Project)
project(${PROJECT_NAME} LANGUAGES CXX)

# Setting Find cmake files path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmakeFiles)

# Define the executable.
add_executable(${PROJECT_NAME})

# Setting C++14
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

# Unsetting old cache var's
unset(${GLAD_LIBRARY} CACHE)
unset(${ASSIMP_LIBRARY} CACHE)
unset(${GLFW_LIBRARY} CACHE)
unset(${LUA_LIBRARY} CACHE)
unset(${REACT_LIBRARY} CACHE)

# Finding required lib's using FindXXX.cmake files in /cmakeFiles
message("")
#find_package(OpenGL REQUIRED)
find_package(GLAD REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(GLFW REQUIRED)
find_package(LUA REQUIRED)
find_package(ReactPhysics3D REQUIRED)
message("")

# Adding Source Directory
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

# Linking lib files to compiler
if(WIN32)
    target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARY} ${GLFW_LIBRARY} ${LUA_LIBRARY} )
ELSE(APPLE)
    target_link_libraries(${PROJECT_NAME}  ${ASSIMP_LIBRARY} ${GLFW_LIBRARY} ${LUA_LIBRARY} ${GLAD_LIBRARY} ${REACT_LIBRARY}  )
ENDIF()




# Copy resource files
if(!WIN32)
#file(COPY ${PROJECT_SOURCE_DIR}/src/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${PROJECT_SOURCE_DIR}/src/res ${CMAKE_CURRENT_BINARY_DIR}/res )
ENDIF(!WIN32)