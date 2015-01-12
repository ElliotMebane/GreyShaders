#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_textureMask;
// uniform float u_interpolate;

void main() {
    vec4 color1 = texture2D(CC_Texture0, v_texCoord);
    vec4 color2 = texture2D(u_textureMask, v_texCoord);
    // using just the red channel of the mask image as the alpha channel of the final image
    gl_FragColor.rgba = vec4( color1.r, color1.g, color1.b, color2.r );
}