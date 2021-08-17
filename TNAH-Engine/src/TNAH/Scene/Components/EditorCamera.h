#pragma once

#include "TNAH/Scene/SceneCamera.h"

namespace tnah {
    struct EditorCameraComponent
    {
        SceneCamera EditorCamera;
        bool Editor = true;

        EditorCameraComponent() = default;
        EditorCameraComponent(const EditorCameraComponent& other) = default;

        operator SceneCamera& () { return EditorCamera; }
        operator const SceneCamera& () const { return EditorCamera; }
    };
}
