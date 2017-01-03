#include"Rect.h"
#include"CObject.h"
#include <vector>
using namespace std;
class QuadNode {
private:

public:
	QuadNode* _nodeTL = NULL;
	QuadNode* _nodeTR = NULL;
	QuadNode* _nodeBL = NULL;
	QuadNode* _nodeBR = NULL;

	vector<CObject*> listObject;
	int id;
	Rect* bound;
	QuadNode();
	QuadNode(int ID, Rect* b, vector<CObject*> list)
	{
		id = ID;
		bound = b;
		listObject = list;
	};
	~QuadNode();
};