out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

vec4 gray_color(sampler2D tex, vec2 texCoord)
{
    vec4 ret = texture(tex, texCoord);
    float average = (ret.r + ret.g + ret.b) / 3.0;
    return vec4(average, average, average, ret.w);
}

vec4 inverse_color(sampler2D tex, vec2 texCoord)
{
    return vec4(vec3(1.0 - texture(tex, texCoord)), 1.0);
}

vec4 blur_image(sampler2D tex, vec2 texCoord)
{
    const float offset = 1.0 / 300.0; 

    vec2 offsets[9] = vec2[] (
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    float kernel[9] = float[] (
        1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0,
        2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0,
        1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0  
    );
    
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++) {
        col += vec3(texture(tex, texCoord.st + offsets[i])) * kernel[i];
    }
    return vec4(col, 1.0);
}

vec4 image_pixelate(sampler2D tex, vec2 texCoord)
{
    float p = 64.0;
    float d = (1.0 / p);
    vec2 col = vec2(d * floor(texCoord.x / d), d * floor(texCoord.y / d));
    return texture(tex, col);
}  

void main()
{ 
    //FragColor = blur_image(screenTexture, TexCoords);
    //FragColor = gray_color(screenTexture, TexCoords);
    //FragColor = inverse_color(screenTexture, TexCoords);
    //FragColor = image_pixelate(screenTexture, TexCoords);
    FragColor = texture(screenTexture, TexCoords);
}
