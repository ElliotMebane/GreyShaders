#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;

// adapted from: http://stackoverflow.com/a/13558570/1647217

// Inverse of sRGB "gamma" function. (approx 2.2)
float inv_gam_sRGB( in int ic) {
    float c = float( ic )/255.0;
    if ( c <= 0.04045 )
        return c/12.92;
    else
        return pow(((c+0.055)/(1.055)),2.4);
}

// sRGB "gamma" function (approx 2.2)
int gam_sRGB( in float v) {
    if(v<=0.0031308)
        v *= 12.92;
    else
        v = 1.055*pow(v,1.0/2.4)-0.055;
    return int(v*255.0+.5);
}

void main()
{
    vec3 normalColor = texture2D( u_texture, v_texCoord ).rgb;
    
    // sRGB luminance(Y) values
    float rY = 0.299;
    float gY = 0.587;
    float bY = 0.114;
    
    ivec3 normalColorInts = ivec3( normalColor * 255.0 );
    
    // GRAY VALUE ("brightness")
    int mono = gam_sRGB( rY*inv_gam_sRGB( normalColorInts.r ) +
                    gY*inv_gam_sRGB( normalColorInts.g ) +
                    bY*inv_gam_sRGB( normalColorInts.b  )
                    );
    
    gl_FragColor.rgb = vec3( float( mono ) / 255.0 );
    gl_FragColor.a = 1.0;
}


