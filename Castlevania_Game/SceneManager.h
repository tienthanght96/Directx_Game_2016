#ifndef __SceneManager_H__
#define __SceneManager_H__

#include "m2dx.h"
#include <vector>

class SceneManager
{
private:

	SceneManager() {}

	~SceneManager() {}

	vector<M2DXBaseGameLayer*> m_ListGameScene;

	static SceneManager* s_Instance;

	LPDIRECT3DDEVICE9		m_lpDirectDevice;

public:

	static SceneManager* getInstance();

	void setDirectDevice(const LPDIRECT3DDEVICE9& lpDirectDevice);

	void Initialize();

	void HandleInput(BYTE keyState[]);

	void Update(int deltaTime);

	void Render();

	void AddElement(M2DXBaseGameLayer* GameScene);

	void ExitState();

	void ReplaceBy(M2DXBaseGameLayer* GameScene);

	void ClearAll();

	void onKeyDown(int keyCode);
};

#endif