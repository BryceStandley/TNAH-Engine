find_library(LUA_LIBRARY
        NAMES liblua.a
        HINTS "${PROJECT_SOURCE_DIR}/lib/macLib/lua/5.4.3"
        PATHS ${PROJECT_SOURCE_DIR}/lib/macLib/lua/5.4.3
        PATH_SUFFIXES lib
        NO_DEFAULT_PATH
        )

if(LUA_LIBRARY)
    message("Library: LUA found! Located at: ${LUA_LIBRARY}")
else()
    message("Library: LUA NOT found! Located at: ${LUA_LIBRARY}")
endif(LUA_LIBRARY)