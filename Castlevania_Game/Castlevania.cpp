#include "Castlevania.h"
#include "SceneManager.h"
#include "Map.h"
#include "EndGame.h"

SimonBelmont* player;
Camera* camera;
Castlevania::Castlevania() { }

Castlevania::~Castlevania() { }

void Castlevania::Init()
{
	Time::getInstance()->time = 400;
	Heart::getInstance()->heart = 0;
	ItemManager::getInstance()->Release();
	BloodManager::getInstance()->bloodEnemy = 16;
	BloodManager::getInstance()->bloodSimon = 16;
	bg = BackgroundLoader::getInstance();
	quad = Quadtree::getInstance()->getCurrentQuadtree();
	quad->getRoot(Stage::getInstance()->nextLevel);
	quad->restore();
	if (nowLevel == 1)
	{
		player = new SimonBelmont(1850, 860);//1850, 860
		player->setFlipX(false);
		M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\map1"));
		Camera::getInstance()->BossX = 256;
		Camera::getInstance()->BossY = 240;
	}
	if (nowLevel == 2)
	{
		player = new SimonBelmont(1317, 134);//680, 648
		player->setFlipX(true);
		M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\music\\map2"));
		Camera::getInstance()->BossX = 6912;
		Camera::getInstance()->BossY = 240;
	}

	Stage::getInstance()->prePointX = player->getPositionX();
	Stage::getInstance()->prePointY = player->getPositionY();
	Stage::getInstance()->flip = player->getFlipX();

#pragma region khởi tạo số tầng của camera
	string fileName;
	if (nowLevel == 1)
		fileName = "Map\\Level1\\camera.txt";
	if (nowLevel == 2)
		fileName = "Map\\Level2\\camera.txt";
	ifstream myfile(fileName, ios::in | ios::out);
	Camera::getInstance()->listFlat.clear();
	int x, y, width, height, id;
	string line;
	getline(myfile, line);
	while (!myfile.eof())
	{
		getline(myfile, line);
		getCamFlat(id,x,y,width,height,line);
		CameraFlat *temp = new CameraFlat(x, y, width, height);
		Camera::getInstance()->listFlat.push_back(temp);
	}
#pragma endregion

	Camera::getInstance()->setFlat((player->getPositionY() ) / 240);
	if (!player)
	{
		return ;
	}
	DoorManager::getInstance()->setListDoor(nowLevel);

	return ;
}

void Castlevania::update(int deltaTime)
{
	if (bossDead == true)
		setCam(deltaTime);
	updateTime(deltaTime);	
	if (endMap == false)
	{
#pragma region cài đặt và update simon
		// cài đặt không cho Simon đi ra ngoài màn hình
		player->setLockLeft(Camera::getInstance()->cameraX - Camera::getInstance()->width / 2);
		player->setLockRight(Camera::getInstance()->cameraX + Camera::getInstance()->width / 2);
		//update simon
		player->update(deltaTime);
#pragma endregion


#pragma region update cổng chuyển state
		//update cauwr chuyển state
		CObject* tempSimon = (CObject*)player;
		DoorManager::getInstance()->Update(deltaTime);
		DoorManager::getInstance()->UpdateCollision(tempSimon);
		DoorManager::getInstance()->updateCamera(player);
#pragma endregion

		int dem = 0;
		//nếu không chuyển state
		if (Camera::getInstance()->changeState == false)
		{
#pragma region cập nhật các hoạt động trong 1 state
			CObject* temp = (CObject*)player;
#pragma region cập nhật va chạm của roi, rìu, bomerang, ... 
			WeponManager::getInstance()->Update(deltaTime, temp);
#pragma endregion

			//chèn object vào trong camera
			quad->InsertObjectIntoView(Camera::getInstance()->getBound(), quad->getRoot(nowLevel));

			for (vector<CObject*>::iterator i = quad->_objectInView.begin(); i != quad->_objectInView.end();i++)
			{
				if ((*i)->_x > player->getPositionX() * 2)
					(*i)->setAD(CObject::AttackDirection::Left);
				else
					(*i)->setAD(CObject::AttackDirection::Right);
				(*i)->getSimonPoint(player->getPositionX(), player->getPositionY());
			}
			quad->Update(deltaTime);

			BulletManager::getInstance()->Update(deltaTime);
			BulletManager::getInstance()->UpdateCollision(temp);

#pragma region cập nhật va chạm của simon với object

			if (player->getActionState() == SimonBelmont::ActionState::Walking || player->getActionState() == SimonBelmont::ActionState::Standing)
			{
				player->setactionState(SimonBelmont::ActionState::Jumping);
				player->reset();
			}
			for (vector<CObject*>::iterator i = quad->_objectInView.begin(); i != quad->_objectInView.end();i++)
			{
				if (player->updateCollis(*i))
					dem++;
			}
#pragma endregion

#pragma region cập nhật và xét va chạm của các Item, Object
			ItemManager::getInstance()->Update(deltaTime);
			for (vector<CObject*>::iterator i = quad->_objectInView.begin(); i != quad->_objectInView.end();i++)
			{
				(*i)->isFall = true;
				quad->updateCollis(*i);
				WeponManager::getInstance()->updateCollis(*i);
				ItemManager::getInstance()->UpdateCollision(*i);
				BulletManager::getInstance()->UpdateCollision(*i);
			}
			ItemManager::getInstance()->UpdateCollision(temp);
			for (list<CObject*>::iterator i = ItemManager::getInstance()->m_ListItem.begin(); i != ItemManager::getInstance()->m_ListItem.end();i++)
			{
				if ((*i)->_type == 25 && (*i)->isDead == true)
					bossDead = true;
				if ((*i)->_type == 48 && (*i)->isDead == true)
				{
					bg->setColor = true;
					clearAll();
				}
			}

#pragma endregion

#pragma endregion
		}
		this->deltatime = deltaTime;
	}
	Camera::getInstance()->Follow(player);
	Camera::getInstance()->Update();
	ScoreManager::getInstance()->Update();
}

void Castlevania::render()
{
	//M2DXDirect3D::getInstance()->getD3DDeviceInterface()->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF000000, 0, 0);
	G_Device->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF000000, 0, 0);
	auto d3dxSpriteInterface = M2DXD3DX::getInstance()->getD3DXSpriteInterface();
	d3dxSpriteInterface->Begin(D3DXSPRITE_ALPHABLEND);
	Camera::getInstance()->SetTransform(G_Device);
	D3DXMATRIX newTransformMatrix;
	D3DXMATRIX oldTransformMatrix;
	d3dxSpriteInterface->GetTransform(&oldTransformMatrix);
	D3DXVECTOR2 scaling = D3DXVECTOR2(SCALE_FACTOR, SCALE_FACTOR);
	D3DXMatrixTransformation2D(&newTransformMatrix, NULL, 0.0f, &scaling, NULL, 0.0f, NULL);
	newTransformMatrix *= oldTransformMatrix;
	d3dxSpriteInterface->SetTransform(&newTransformMatrix);
	bg->UpdateRender(nowLevel, deltatime);
	DoorManager::getInstance()->Render();
	quad->Draw();
	player->draw();
	WeponManager::getInstance()->Render();
	ItemManager::getInstance()->Render();
	BulletManager::getInstance()->Render();
	ScoreManager::getInstance()->Render();
	d3dxSpriteInterface->SetTransform(&oldTransformMatrix);
	d3dxSpriteInterface->End();
}

void Castlevania::processInput(BYTE keyState[])
{
	if (endMap == false)
	{
		SimonBelmont::SimonArrowsCommand arrowsCommand;
		arrowsCommand.leftArrow = isKeyDown(DIK_LEFTARROW, keyState);
		arrowsCommand.rightArrow = isKeyDown(DIK_RIGHTARROW, keyState);
		arrowsCommand.downArrow = isKeyDown(DIK_DOWNARROW, keyState);
		arrowsCommand.upArrow = isKeyDown(DIK_UPARROW, keyState);
		isUpArrow = arrowsCommand.upArrow;
		if (Camera::getInstance()->changeState == false)
			player->command(arrowsCommand);
	}
}

void Castlevania::onKeyDown(int keyCode)
{
	if (Camera::getInstance()->changeState == false && endMap == false)
	{
		switch (keyCode)
		{
		case JUMP_KEY_CODE:
			player->command(keyCode, false);
		case ATTACK_KEY_CODE:
			player->command(keyCode, isUpArrow);
		case CHANGE_WEPON_KEY_CODE:
			player->command(keyCode, false);
		default:
			break;
		}
	}
}

void Castlevania::clearAll()
{
	RECT viewPort(Camera::getInstance()->getBound());
	Box boxCam(viewPort.left, viewPort.top, (viewPort.right - viewPort.left), (viewPort.bottom - viewPort.top));
	for (vector<CObject*>::iterator i = quad->_objectInView.begin(); i != quad->_objectInView.end();i++)
	{
		if (swept.AABBCheck((*i)->_box, boxCam))
		{
			if ((*i)->isMovement == true && (*i)->_type != 18)
			{
				(*i)->setState(CObject::State::before_dead);
			}
		}
	}
}

void Castlevania::setCam(int deltaTime)
{
	remainingChangeState -= deltaTime;
	if (remainingChangeState <= 0)
		endMap = true;
}

void Castlevania::updateTime(int deltaTime)
{
	if (endMap == false)
	{
		if (Camera::getInstance()->changeState == false)
		{
			remainingTime -= 1;
			if (remainingTime <= 0)
			{
				Time::getInstance()->time -= 1;
				remainingTime = 30;
			}
		}
	}
	else
	{
		remainingTime -= 1;
		if (remainingTime <= 0)
		{
			if (Time::getInstance()->time > 0)
			{
				Time::getInstance()->time -= 1;
				M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\getscoretimer"));
			}
			if (Time::getInstance()->time <= 0 && Heart::getInstance()->heart > 0)
			{
				M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\getscoretimer"));
				Heart::getInstance()->heart -= 1;
				M2DXDSound::getInstance()->loop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\getscoreweapon"));
			}
			Score::getInstance()->score += 100;
			if (Time::getInstance()->time <= 0 && Heart::getInstance()->heart <= 0)
			{
				Stage::getInstance()->nextLevel += 1;
				M2DXDSound::getInstance()->stop(M2DXResourceManager::getInstance()->getSoundByName("Sound\\sound\\getscoreweapon"));
				if (Stage::getInstance()->nextLevel <= 2)
					SceneManager::getInstance()->ReplaceBy(new Map(Stage::getInstance()->nextLevel));
				else
					SceneManager::getInstance()->ReplaceBy(new EndGame());
			}
			remainingTime = 2;
		}
	}
}

void Castlevania::getCamFlat(int &id, int &x, int &y, int &width, int &height, string information)
{
	int count = 0;
	int temp = 0;
	for (int i = 0;i < information.length();i++)
	{
		if (information[i] != ' ')
		{
			temp = temp * 10 + information[i] - 48;
		}
		else
			if (information[i] == ' ')
			{
				if (count == 0)
				{
					id = temp;
					temp = 0;
					count++;
				}
					else
						if (count == 1)
						{
							x = temp;
							temp = 0;
							count++;
						}
						else
							if (count == 2)
							{
								y = temp;
								temp = 0;
								count++;
							}
							else
								if (count == 3)
								{
									width = temp;
									temp = 0;
									count++;
								}
								else
									if (count == 4)
									{
										height = temp;
										return;
									}
			}
	}
}