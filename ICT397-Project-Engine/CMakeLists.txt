target_sources(${PROJECT_NAME} PRIVATE
        application.cpp
        BoundingBox.cpp
        Callbacks.cpp
        camera.h
        Debugger.cpp
        Enemy.cpp
        Engine.cpp
        ExitScreen.cpp
        GameAssetFactory.cpp
        GameObject.cpp
        GameObjects.cpp
        glad.c
        GlfwWindow.cpp
        GUI.cpp
        Input.cpp
        luaManager.cpp
        Mesh.cpp
        Model.cpp
        OpenGL.cpp
        Player.cpp
        Renderer.cpp
        Water.cpp
        Scene.cpp
        Shader.cpp
        Skybox.cpp
        stb.cpp
        Static.cpp
        Terrain.cpp
        TextureLoader.cpp
        Time.cpp
        Token.cpp
        View.cpp
        Window.cpp
        Fbx.cpp
        Buffer.cpp
        enemyStates.cpp
        Md2.cpp
        Md2State.cpp
        singleton.h
        state.h
        stateMachine.h
        )

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

#imgui includes
target_sources(${PROJECT_NAME} PRIVATE
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_impl_glfw.cpp
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        )