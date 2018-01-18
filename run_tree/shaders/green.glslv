uniform float t;
varying vec4 vert;

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    vert = gl_Position;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
}

// vim: ft=c
