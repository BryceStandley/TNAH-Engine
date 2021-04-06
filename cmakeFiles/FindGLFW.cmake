find_library(GLFW_LIBRARY
        NAMES libglfw.3.3.dylib
        HINTS "${PROJECT_SOURCE_DIR}/lib/macLib/glfw/3.3.3"
        PATHS ${PROJECT_SOURCE_DIR}/lib/macLib/glfw/3.3.3
        PATH_SUFFIXES lib
        NO_DEFAULT_PATH
        )

if(GLFW_LIBRARY)
    message("Library: GLFW found! Located at: ${GLFW_LIBRARY}")
else()
    message("Library: GLFW NOT found! Located at: ${GLFW_LIBRARY}")
endif(GLFW_LIBRARY)