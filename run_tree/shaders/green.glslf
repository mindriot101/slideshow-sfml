uniform float t;
uniform sampler2D texture;
varying vec4 vert;

void main() {
    float green = abs(sin(t));
    vec4 color = vec4(vert.x * 255.0, green, vert.y * 255.0, 1);
    vec4 pixel = color * texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = pixel;
}

// vim: ft=c
