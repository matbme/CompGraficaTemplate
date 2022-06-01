#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 ScaledNormal;
out vec3 FragPos;
out vec2 TexCoords;
flat out int Highlight;
flat out int IsTextured;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int texHighlight;
uniform int isTextured;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    ScaledNormal = aNormal;
    FragPos = vec3(model * vec4(position, 1.0f));
    TexCoords = aTexCoord;
    Highlight = texHighlight;
    IsTextured = isTextured;
}
