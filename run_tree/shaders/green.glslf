uniform sampler2D texture;

void main() {
    vec4 color = vec4(0, 255, 0, 255);
    vec4 pixel = color * texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = pixel;
}
