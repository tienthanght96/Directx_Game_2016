#include "SceneManager.h"

SceneManager* SceneManager::s_Instance = 0;

SceneManager* SceneManager::getInstance()
{
	if (!s_Instance)
	{
		s_Instance = new SceneManager();
	}
	return s_Instance;
}

void SceneManager::setDirectDevice(const LPDIRECT3DDEVICE9& _lpDirectDevice)
{
	this->m_lpDirectDevice = _lpDirectDevice;
}

void SceneManager::Initialize()
{
	if (!m_ListGameScene.empty())
	{
		m_ListGameScene.back()->Init();
	}
}

void SceneManager::AddElement(M2DXBaseGameLayer* GameScene)
{
	if (!m_ListGameScene.empty())
	{
		m_ListGameScene[m_ListGameScene.size() - 1]->Pause();
	}
	m_ListGameScene.push_back(GameScene);
	m_ListGameScene.back()->Init();
}

void SceneManager::HandleInput(BYTE keyState[])
{
	if (!m_ListGameScene.empty())
	{
		m_ListGameScene.back()->processInput(keyState);
	}
}

void SceneManager::Update(int deltaTime)
{
	if (!m_ListGameScene.empty())
	{
		m_ListGameScene.back()->update(deltaTime);
	}
}
void SceneManager::Render()
{
	if (!m_ListGameScene.empty())
	{
		m_ListGameScene.back()->render();
	}
}
void SceneManager::ExitState()
{
	if (!m_ListGameScene.empty())
	{
		m_ListGameScene.back()->release();
		m_ListGameScene.pop_back();
	}
}
void SceneManager::ReplaceBy(M2DXBaseGameLayer* GameScene)
{
	ExitState();
	AddElement(GameScene);
}
void SceneManager::ClearAll()
{
	while (!m_ListGameScene.empty())
	{
		ExitState();
	}
}

void SceneManager::onKeyDown(int keyCode)
{
	if (!m_ListGameScene.empty())
	{
		m_ListGameScene.back()->onKeyDown(keyCode);
	}
}

