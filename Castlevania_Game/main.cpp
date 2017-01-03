#include "m2dx.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	auto baseGameLayer = new M2DXBaseGameLayer(hInstance);

	if (baseGameLayer->init())
	{
		baseGameLayer->start();
	}
}