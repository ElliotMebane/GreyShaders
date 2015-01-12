#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;

uniform sampler2D u_texture;
uniform vec2 resolution;


void main()
{
    vec2 unit = 1.0 / resolution.xy;
    
    float tR = texture2D( u_texture, vec2(v_texCoord.x, v_texCoord.y ) ).r;
    float tG = texture2D( u_texture, vec2(v_texCoord.x + ( 20.0 * unit.x ), v_texCoord.y ) ).g;
    float tB = texture2D( u_texture, vec2(v_texCoord.x - ( 20.0 * unit.x ), v_texCoord.y ) ).b;

  	gl_FragColor = vec4( tR, tG, tB, 1.0 );
}