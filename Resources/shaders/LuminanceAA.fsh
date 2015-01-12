#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;

// http://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color

void main()
{
    vec3 normalColor = texture2D( u_texture, v_texCoord ).rgb;
    
    float mono = 0.299 * normalColor.r + 0.587 * normalColor.g + 0.114 * normalColor.b;
    
    gl_FragColor.rgb = vec3( mono );
	gl_FragColor.a = 1.0;
}