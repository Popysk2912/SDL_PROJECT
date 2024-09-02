#version 330 core

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 UV;

out vec4 fragmentColor;

uniform float time;
uniform sampler2D mySampler;

void main()
{
    gl_Position = vec4(vertexPosition, 0.0, 1.0); // Преобразуем vec2 в vec4 и задаем позицию вершины

    vec4 textureColor = texture(mySampler, UV);

    fragmentColor = textureColor;
}
