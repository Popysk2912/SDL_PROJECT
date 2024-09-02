#version 330 core

in vec2 vertexPosition;
in vec4 vertexColor;

out vec4 fragmentColor;

uniform float time;

void main()
{
    gl_Position = vec4(vertexPosition, 0.0, 1.0); // Преобразуем vec2 в vec4 и задаем позицию вершины
    fragmentColor = vertexColor +  vec4(cos(time) * 0.5, cos(time+1.0) * 0.5, cos(time+3.0) * 0.5, 255); // Pass vertex color to the fragment shader
}
