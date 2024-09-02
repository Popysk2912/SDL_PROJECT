#version 330 core

in vec4 fragmentColor; // Получаем цвет из вершинного шейдера
out vec4 FragColor;

void main()
{
    FragColor = fragmentColor; // Используем полученный цвет
}
