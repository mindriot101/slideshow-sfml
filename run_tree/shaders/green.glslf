uniform float t;
uniform sampler2D texture;

void main() {
    float green = abs(sin(t));
    vec4 color = vec4(0, green, 0, 1);
    vec4 pixel = color * texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = pixel;
}

// vim: ft=c
