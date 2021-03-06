#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;

// http://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color

void main()
{
    vec3 normalColor = texture2D( u_texture, v_texCoord ).rgb;
    
    float mono = dot( normalColor, vec3( 0.333, 0.333, 0.333 ) );
    
    gl_FragColor.rgb = vec3( mono );
	gl_FragColor.a = 1.0;
}