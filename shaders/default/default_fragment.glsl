#version 430 core

out vec4 FragColor;
in vec3 outColor;

void main()
{
    FragColor = vec4(outColor, 1.0);  // This will show the normalized color
}
