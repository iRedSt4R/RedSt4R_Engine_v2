#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 ttexCoord;
  
out vec3 ourColor;
out vec2 texCoord;



void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    texCoord = vec2(ttexCoord.x, 1 - ttexCoord.y);
    //texCoord = ttexCoord;
}