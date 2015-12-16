#ifndef OCTNODE_H
#define OCTNODE_H

#include "Collider3D.h"
#include <vector>
class OctNode
{
public:
	Collider3D binBox;

	int count = 0;
	const int capacity = 8;
	std::vector<Collider3D*> colliderPtrs;	// Array would be faster...

	bool isLeaf = true;
	OctNode* child1 = nullptr;
	OctNode* child2 = nullptr;
	OctNode* child3 = nullptr;
	OctNode* child4 = nullptr;
	OctNode* child5 = nullptr;
	OctNode* child6 = nullptr;
	OctNode* child7 = nullptr;
	OctNode* child8 = nullptr;

	OctNode(glm::vec3 c, glm::vec3 e);
	void print();
	~OctNode();
	bool collidesWith(Collider3D* colliderPtr);
	void add(Collider3D* colliderPtr);
	void branch();
};

#endif