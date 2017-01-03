#include "ListChunk.h"

ListChunk::ListChunk(int X, int Y)
{
	m_ListChunk.push_back(new Chunk(X, Y, CHUNK_X, -CHUNK_Y));
	m_ListChunk.push_back(new Chunk(X, Y , CHUNK_X, 0));
	m_ListChunk.push_back(new Chunk(X ,Y, -CHUNK_X, -CHUNK_Y));
	m_ListChunk.push_back(new Chunk(X ,Y, -CHUNK_X, 0));
}

void ListChunk::Update(int deltaTime)
{
	for (list<Chunk*>::iterator i = m_ListChunk.begin(); i != m_ListChunk.end();)
	{
		(*i)->Update(deltaTime);
		i++;
	}
}

void ListChunk::Render()
{
	for (list<Chunk*>::iterator i = m_ListChunk.begin(); i != m_ListChunk.end();)
	{
		(*i)->Draw();
		i++;
	}
}

void ListChunk::Release()
{
	for (list<Chunk*>::iterator i = m_ListChunk.begin(); i != m_ListChunk.end();)
	{
		SAFE_DELETE(*i);
	}
	m_ListChunk.clear();
}