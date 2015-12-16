#ifndef OCTTREE_H
#define OCTTREE_H

#include "OctNode.h"
class OctTree
{
public:
	glm::vec3 c, e;

	OctNode* root = nullptr;

	OctTree(glm::vec3 c, glm::vec3 e);
	void print();
	bool collidesWith(Collider3D* otherCollider3DPtr);
	void add(Collider3D* otherCollider3DPtr);


	OctTree();
	~OctTree();
};

#endif