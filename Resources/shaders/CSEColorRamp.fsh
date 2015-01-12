#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;
uniform sampler2D u_colorRampTexture;

void main()
{ vec4 normalColor = texture2D(u_texture, v_texCoord).rgba;

  float rampedR = texture2D(u_colorRampTexture, vec2(normalColor.r, 0)).r;
  float rampedG = texture2D(u_colorRampTexture, vec2(normalColor.g, 0)).g;
  float rampedB = texture2D(u_colorRampTexture, vec2(normalColor.b, 0)).b;
	
  gl_FragColor = vec4(rampedR, rampedG, rampedB, normalColor.a );
}