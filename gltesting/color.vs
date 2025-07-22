#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos; //position of fragment
out vec3 normal;

void main()
{   
    fragPos = vec3(model * vec4(aPos, 1.0));

    normal = mat3(transpose(inverse(model))) * aNormal; //transposing as to gaurd against scaling errors

    gl_Position = projection * view * model * vec4(aPos, 1.0);
} 