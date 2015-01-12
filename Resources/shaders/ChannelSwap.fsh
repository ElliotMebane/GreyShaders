#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;

void main()
{ 
	vec4 normalColor = texture2D(CC_Texture0, v_texCoord).rgba;
	gl_FragColor = vec4( normalColor.g, normalColor.b, normalColor.r, normalColor.a );
  	
  	// The syntax below is called swizzling, and achieves the same results as the above.
  	// A channel swapping shader like this is a great candidate for swizzling 
  	// https://www.opengl.org/wiki/Data_Type_%28GLSL%29		
  	// gl_FragColor.rgba = texture2D(CC_Texture0, v_texCoord).gbra;
}