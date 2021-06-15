IF(WIN32)
    find_library(REACT_LIBRARY
            NAMES libreactphysics3d.dll
            HINTS "${PROJECT_SOURCE_DIR}"
            PATHS ${PROJECT_SOURCE_DIR}
            PATH_SUFFIXES lib
            NO_DEFAULT_PATH
            )
ELSE()
    find_library(REACT_LIBRARY
            NAMES libreactphysics3d.a
            HINTS "${PROJECT_SOURCE_DIR}/lib/macLib/react/0.8"
            PATHS ${PROJECT_SOURCE_DIR}/lib/macLib/react/0.8
            PATH_SUFFIXES lib
            NO_DEFAULT_PATH
            )
    include_directories(${PROJECT_SOURCE_DIR}/lib/macLib/react/0.8/include)
ENDIF(WIN32)

if(REACT_LIBRARY)
    message("Library: REACT found! Located at: ${REACT_LIBRARY}")
else()
    message("Library: REACT NOT found! Located at: ${REACT_LIBRARY}")
endif(REACT_LIBRARY)