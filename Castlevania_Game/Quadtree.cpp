#include "Quadtree.h"
Quadtree* Quadtree::_instance = 0;

Quadtree::Quadtree() 
{
	mapOb.insert(NamePair(1, "Map\\Level1\\ob.txt"));
	mapQuad.insert(NamePair(1, "Map\\Level1\\quadtree.txt"));
	mapOb.insert(NamePair(2, "Map\\Level2\\ob.txt"));
	mapQuad.insert(NamePair(2, "Map\\Level2\\quadtree.txt"));
}
Quadtree::~Quadtree() {}

void Quadtree::load() 
{
	int i = 1;
	while (i <= 2)
	{
		auto fileOb = mapOb[i];
		auto fileQuad = mapQuad[i];
		loadObject(fileOb,i);
		string line;
		ifstream myfile(fileQuad);
		while (!myfile.eof())
		{
			QuadNode* tamp = new QuadNode();
			getline(myfile, line);
			getInformationNode(tamp->id, tamp->bound->x, tamp->bound->y, tamp->bound->witdh, tamp->bound->height, tamp->listObject, line, i);
			list.push_back(tamp);
		}
		for (int i = 0;i < (int)list.size();i++)
		{
			if (list[i]->id == 0)
			{
				_root = list[i];
				continue;
			}
			int rootId = list[i]->id / 10;
			for (int j = 0; j < (int)list.size();j++)
			{
				if (list[j]->id == rootId)
				{
					switch (list[i]->id % 10)
					{
					case 1:
						list[j]->_nodeTL = list[i];
						break;
					case 2:
						list[j]->_nodeTR = list[i];
						break;
					case 3:
						list[j]->_nodeBL = list[i];
						break;
					case 4:
						list[j]->_nodeBR = list[i];
						break;
					}
					break;
				}
			}
		}
		NodeManager.insert(NodePair(i, list));
		list.clear();
		i++;
	}
}

bool Quadtree::isExist(CObject * Ob, vector<CObject*> list)
{
	if (!list.empty())
	{
		for (vector<CObject*>::iterator i = list.begin(); i != list.end();)
		{
			if ((*i) == Ob)
				return true;
			else
				i++;
		}
	}
	return false;
}

void Quadtree::getInformationOb(int &ID, int &type, int &x, int &y, int &width, int &height, string information, int &item)
{
	int count = 0;
	int temp = 0;
	for (int i = 0;i < information.length();i++)
	{
		if (information[i] != ' ')
		{
			temp = temp*10 + information[i] - 48;
		}
		else
			if(information[i] == ' ')
		{
				if (count == 0)
				{
					ID = temp;
					temp = 0;
					count++;
				}
				else
					if (count == 1)
					{
						type = temp;
						temp = 0;
						count++;
					}
					else
						if (count == 2)
						{
							x = temp;
							temp = 0;
							count++;
						}
						else
							if (count == 3)
							{
								y = temp;
								temp = 0;
								count++;
							}
							else
								if (count == 4)
								{
									width = temp;
									temp = 0;
									count++;
								}
								else
									if(count == 5)
									{
										height = temp;
										temp = 0;
										count++;
									}
									else
										if (count == 6)
										{
											item = temp;
											return;
										}
		}		
	}
}

void Quadtree::getInformationNode(int &ID, int &x, int &y, int &width, int &height, vector<CObject*> &listObjectt, string information,int level)
{
	auto listOb = ObjectManager[level];
	int count = 0;
	int temp = 0;
	for (int i = 0;i < information.length();i++)
	{
		if (count < 5)
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
						ID = temp;
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
										temp = 0;
										count++;
									}
				}
		}
		else
		{
			if (information[i] != ',')
			{
				temp = temp * 10 + information[i] - 48;
			}
			else
			{
				listObjectt.push_back(listOb[temp-1]);
				temp = 0;
			}
		}
	}
}

Quadtree * Quadtree::getInstance()
{
	if (!_instance)
	{
		_instance = new Quadtree();
	}
	return _instance;
}

void Quadtree::loadObject(string file,int i) {
	string line;
	ifstream myfile(file);
	try
	{
		while(!myfile.eof())
		{
			getline(myfile, line);
			int id,x, y, width, height, type = 0, item;
			getInformationOb(id, type, x, y, width, height, line, item);
			switch(type)
			{
				case 2:
				{
					_listObject.push_back(new Brick(x,G_MapHeight[i-1] - y , width, height, item));
				}
				break;
				case 14:
				{
					_listObject.push_back(new Stairs(type, x - width/2, G_MapHeight[i-1] - y, item));
				}
				break;
				case 16:
				{
					_listObject.push_back(new Stairs(type, x + width / 2, G_MapHeight[i-1] - y  , item));
				}
				break;
				case 15:
				{
					_listObject.push_back(new Stairs(type, x + width/2, G_MapHeight[i-1] - (y + height/2) ,item));
				}
				break;
				case 17:
				{
					_listObject.push_back(new Stairs(type, x - width / 2, G_MapHeight[i-1] - (y + height / 2), item));
				}
				break;
				case 12:
				{
					_listObject.push_back(new Candle(x, G_MapHeight[i-1] - y , item));
				}
				break;
				case 10:
				{
					listDoorTemp.push_back(new Door(x, G_MapHeight[i-1] - y,item));
					_listObject.push_back(new Door(x, G_MapHeight[i-1] - y, item));
				}
				break;
				case 5:
				{
					_listObject.push_back(new Zombie(x, G_MapHeight[i-1] - y,item));
				}
				break;
				case 9:
				{
					_listObject.push_back(new BlackKnight(x, G_MapHeight[i-1] - y, item));
				}
				break;
				case 8:
				{
					_listObject.push_back(new AxeMan(x, G_MapHeight[i-1] - y, item));
				}
				break;
				case 7:
				{
					_listObject.push_back(new Medusa(x, G_MapHeight[i-1] - y, item));
				}
				break;
				case 6:
				{
					_listObject.push_back(new Ghost(x, G_MapHeight[i-1] - y, item));
				}
				break;
				case 4:
				{
					_listObject.push_back(new VampireBat(x, G_MapHeight[i-1] - y, item));
				}
				break;
				case 11:
				{
					_listObject.push_back(new DragonSkull(x, G_MapHeight[i-1] - y, item));
				}
				break;
				case 13:
				{
					_listObject.push_back(new QueenMedusa(x, G_MapHeight[i-1] - y, item));
				}
				break;
				case 18:
				{
					_listObject.push_back(new MovingPlatform(x, G_MapHeight[i-1] - y, item));
				}
				break;
				case 21:
				{
					_listObject.push_back(new Hunchback(x, G_MapHeight[i - 1] - y, item));
				}
				break;
				case 22:
				{
					_listObject.push_back(new WhiteSkeleton(x, G_MapHeight[i - 1] - y, item));
				}
				break;
				case 23:
				{
					_listObject.push_back(new Raven(x, G_MapHeight[i - 1] - y, item));
				}
				break;
				case 24:
				{
					_listObject.push_back(new MummyMan(x, G_MapHeight[i - 1] - y, item));
				}
				break;
				case 37:
				{
					_listObject.push_back(new Block(x, G_MapHeight[i - 1] - y, item));
				}
				break;
				case 46:
				{
					_listObject.push_back(new TreasureChest(x, G_MapHeight[i - 1] - y));
				}
				break;
				case 35:
				{
					_listObject.push_back(new MoneyBag1000(x, G_MapHeight[i - 1] - y));
				}
				break;
				case 47:
				{
					_listObject.push_back(new Thorns(x, G_MapHeight[i - 1] - y));
				}
				break;
			}
		}
		ObjectManager.insert(ListPair(i, _listObject));
		DoorManager::getInstance()->AddElement(i,listDoorTemp);
		listDoorTemp.clear();
		_listObject.clear();
	}
	catch (exception ex)
	{}
}

void Quadtree::updateCollis(CObject * Ob)
{
	for (int i = 0;i < (int)_objectInView.size(); i++)
	{
		if (_objectInView[i]->_type != 10)
			_objectInView[i]->updateCollis(Ob);
	}
}

Quadtree * Quadtree::getCurrentQuadtree()
{
	return _instance;
}

void Quadtree::InsertObjectIntoView(RECT viewPort, QuadNode* node)
{
	Box View(viewPort.left/2, viewPort.top/2, (viewPort.right - viewPort.left)/2, (viewPort.bottom - viewPort.top)/2);
	Box Node(node->bound->x, node->bound->y, node->bound->witdh,node->bound->height);
	if (AABBCheck(View,Node))
	{
		int i = 0;
		for (vector<CObject*>::iterator i = node->listObject.begin(); i != node->listObject.end();)
		{
			if ((*i)->isDead == false)
			{
				_objectInView.push_back((*i));
				if ((*i)->isMovement == true)
				{
					i = node->listObject.erase(i);
				}
				else
					i++;
			}
			else
			i++;
		}
		if (node->_nodeBL != NULL)
			InsertObjectIntoView(viewPort, node->_nodeBL);
		if (node->_nodeBR != NULL)
			InsertObjectIntoView(viewPort, node->_nodeBR);
		if (node->_nodeTL != NULL)
			InsertObjectIntoView(viewPort, node->_nodeTL);
		if (node->_nodeTR != NULL)
			InsertObjectIntoView(viewPort, node->_nodeTR);
	}
}


void Quadtree::Draw()
{
	if (!_objectInView.empty())
	{
		for (vector<CObject*>::iterator i = _objectInView.begin(); i != _objectInView.end();)
		{
			if ((*i)->_type != 10)
			{
				(*i)->Draw();
				i = _objectInView.erase(i);
			}
			else
			i++;
		}
	}
	_objectInView.clear();
}


void Quadtree::updateQuadtree()
{
	int temp = getIntLength(list[list.size() - 1]->id);
	for (vector<QuadNode*>::iterator i = list.begin(); i != list.end();)
	{
		if (getIntLength((*i)->id) == temp)
		{
			for (vector<CObject*>::iterator j = _objectInView.begin(); j != _objectInView.end();j++)
			{
				Box node((*i)->bound->x * 2 , (*i)->bound->y * 2 , (*i)->bound->witdh * 2, (*i)->bound->height * 2 );
				if ((*j)->isMovement == true && AABBCheck(node, (*j)->_box)
					&& !isExist((*j),(*i)->listObject))
					(*i)->listObject.push_back((*j));
			}
		}
		i++;
	}
}

int Quadtree::getIntLength(int number)
{
	int dem = 0;
	while (number != 0)
	{
		dem++;
		number = number / 10;
	}
	return dem;
}

void Quadtree::Update(int Deltatime)
{
	for (vector<CObject*>::iterator i = _objectInView.begin(); i != _objectInView.end();i++)
	{
		if ((*i)->_type != 10)
			if (!(Stage::getInstance()->pauseGame && (*i)->getCurrentState() == CObject::State::alive))
		(*i)->Update(Deltatime);
	}
	updateQuadtree();
}

void Quadtree::restore()
{
	for (vector<CObject*>::iterator i = _listObject.begin(); i != _listObject.end();i++)
	{
		if ((*i)->isDead == true)
		{
			(*i)->isDead = false;
			(*i)->setState(CObject::State::alive);
		}
		(*i)->Restore();
	}
}
