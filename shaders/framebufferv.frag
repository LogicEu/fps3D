layout (location = 0) in vec2 vertCoord;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(vertCoord.x, vertCoord.y, 0.0, 1.0); 
    TexCoords = (vertCoord + vec2(1.0)) * 0.5;
}
