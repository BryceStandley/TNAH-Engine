#version 330 core
/*
// Uniform variables
uniform mat4 localToWorldMatrix;        // Local-space to world-space matrix
uniform mat4 worldToCameraMatrix;       // World-space to camera-space matrix
uniform mat4 projectionMatrix;          // Projection matrix
*/
uniform mat4 view;        // Local-space to world-space matrix // view
uniform mat4 model;       // World-space to camera-space matrix // model
uniform mat4 projection;          // Projection matrix


// In variables
layout (location = 0) in vec3 vPos;
layout (location = 1) in uint vertexColor;

// Out variables
out vec4 vertexColorOut;

void main() {

    // Compute the vertex position
    //vec4 positionCameraSpace = worldToCameraMatrix * localToWorldMatrix * vPos;

    // Compute the clip-space vertex coordinates
    //gl_Position = projectionMatrix * positionCameraSpace;
    //gl_Position = projectionMatrix * localToWorldMatrix * worldToCameraMatrix * vPos;
    gl_Position = projection * view * model * vec4(vPos.x, vPos.y, vPos.z, 1.0f);
    // Transfer the vertex color to the fragment shader
    vertexColorOut = vec4((vertexColor & 0xFF0000u) >> 16, (vertexColor & 0x00FF00u) >> 8, vertexColor & 0x0000FFu, 0xFF);
}
