#version 330 core

// Uniform variables
uniform bool isGlobalVertexColorEnabled;          // True if we need to use the global vertex color
uniform vec4 globalVertexColor;                   // Vertex color

// In variables
in vec4 vertexColorOut;

// Out variables
out vec4 color;                        // Output color

void main() {

    // Compute the final color
    if (isGlobalVertexColorEnabled) {
        color = globalVertexColor;
    }
    else {
        color = vertexColorOut;
    }
}
