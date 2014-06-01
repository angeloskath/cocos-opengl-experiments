
// the initial offset
uniform vec2 offset;
// the scale relative to the texture
uniform vec2 scale;

varying vec2 v_texCoord;

void main() {
    gl_FragColor = texture2D(CC_Texture0, offset + v_texCoord*scale);
}
