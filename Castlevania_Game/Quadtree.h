
#define QUADTREE_REF "quadtree.txt"
#define OBJECT_REF "ob.txt"

#include "LargeCandle.h"
#include "Rect.h"
#include "Brick.h"
#include "BlackKnight.h"
#include "Stairs.h"
#include "Door.h"
#include "Raven.h"
#include "MummyMan.h"
#include "AxeMan.h"
#include "TreasureChest.h"
#include "Moneybag1000.h"
#include "Medusa.h"
#include "Ghost.h"
#include "MovingPlatform.h"
#include "VampireBat.h"
#include "DragonSkull.h"
#include "QueenMedusa.h"
#include "Hunchback.h"
#include "WhiteSkeleton.h"
#include "Quadnode.h"
#include "CObject.h"
#include "Block.h"
#include "Thorns.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "SweptAABB.h"
#include  "DoorManager.h"
#include "Zombie.h"
typedef pair<int, string> NamePair;
typedef pair<int, vector<CObject*>> ListPair;
typedef pair<int, vector<QuadNode*>> NodePair;

class Quadnode;

class Quadtree : public SweptAABB
{
private:
	std::map<int, string> mapQuad;
	std::map<int, string> mapOb;
	static Quadtree* _instance;
	bool isExist(CObject* Ob, vector<CObject*> list);
	vector<CObject*> _listObject;
	std::map<int, vector<CObject*>> ObjectManager;
	std::map<int, vector<QuadNode*>> NodeManager;
	QuadNode* _root;
	list<Door*> listDoorTemp;
	static Quadtree* _currentQuadtree;
	void getInformationOb(int &ID, int &type, int &x, int &y, int &width, int &height, string information, int &item);
	void getInformationNode(int &ID, int &x, int &y, int &width, int &height, vector<CObject*> &listObject, string information,int level);
public:
	static Quadtree* getInstance();
	QuadNode* getRoot(int i) 
	{ 
		auto temp = NodeManager[i];
		auto temp2 = ObjectManager[i];
		list.clear();
		_listObject.clear();
		_listObject = temp2;
		list = temp;
		return temp[0]; 
	};
	Quadtree();
	vector<CObject*> _objectInView;
	vector<QuadNode*> list;
	void InsertObjectIntoView(RECT viewPort, QuadNode* node);
	~Quadtree();
	void Update(int Deltatime);
	void restore();
	void Draw();
	void updateQuadtree();
	int getIntLength(int number);
	void load();
	void loadObject(string file,int level);
	void updateCollis(CObject* Ob);
	Quadtree* getCurrentQuadtree();
};