#include "OctTree.h"

OctTree::OctTree(glm::vec3 c, glm::vec3 e)
{
	this->c = c;
	this->e = e;
	root = new OctNode(c, e);
}

void OctTree::print()
{
	std::cout << "Collider3D Oct Tree";
	if (root != nullptr) root->print();
}

bool OctTree::collidesWith(Collider3D * otherCollider3DPtr)
{
	return root->collidesWith(otherCollider3DPtr);
}

void OctTree::add(Collider3D * otherCollider3DPtr)
{
	root->add(otherCollider3DPtr);
}

OctTree::OctTree()
{
}

OctTree::~OctTree()
{
	if (root != nullptr) delete root;
}
