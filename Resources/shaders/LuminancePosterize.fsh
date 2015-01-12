#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;

//  toonify

// adapted from: http://www.lighthouse3d.com/tutorials/glsl-core-tutorial/glsl-core-tutorial-statements-and-functions/

vec4 toonify(in float intensity) {
    vec4 color;
    if (intensity > 0.85)
        color = vec4(1.0,1.0,1.0,1.0);
    else if (intensity > 0.5)
        color = vec4(0.5,0.5,0.5,1.0);
    else if (intensity > 0.15)
        color = vec4(0.25,0.25,0.25,1.0);
    else
        color = vec4(0.0,0.0,0.0,1.0);
    
    return(color);
}

void main()
{
    vec3 normalColor = texture2D( u_texture, v_texCoord ).rgb;
    
    float mono = 0.212655 * normalColor.r + 0.715158 * normalColor.g + 0.072187 * normalColor.b;
    
    gl_FragColor = toonify( mono );
}

