IF(!WIN32)
    find_library(GLAD_LIBRARY
            NAMES libglad.a
            PATHS
                ${PROJECT_SOURCE_DIR}/lib/macLib/glad
                /usr/local/Cellar
                /usr/local
            PATH_SUFFIXES lib src
            NO_DEFAULT_PATH
            )
ENDIF(!WIN32)


if(GLAD_LIBRARY)
    message("Library: GLAD found! Located at: ${GLAD_LIBRARY}")
else()
    message("Library: GLAD NOT found! Located at: ${GLAD_LIBRARY}")
endif(GLAD_LIBRARY)