#include "Sprite.h"

Sprite::Sprite()
{
	_vboID = 0;
}

Sprite::~Sprite()
{
	if(_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}

}

void Sprite::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	Vertex vertexData[6] = {};

	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(0, 0);

	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0, 1);

	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0, 0);

	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0, 0);

	vertexData[4].setPosition(x + width, y);
	vertexData[4].setUV(1, 0);

	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1, 1);

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255,255,0,255);
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
