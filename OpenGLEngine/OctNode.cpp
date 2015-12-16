#include "OctNode.h"

OctNode::OctNode(glm::vec3 c, glm::vec3 e)
{
	binBox = Collider3D(c, e);
	colliderPtrs = std::vector<Collider3D*>(capacity);
	for each (Collider3D* colliderPtr in colliderPtrs) colliderPtr = nullptr;
}

void OctNode::print()
{
	std::cout << std::fixed << std::setprecision(2) << "OctNode: " << std::endl;
	std::cout << "binBox: ";
	binBox.print();
	std::cout << std::endl;

	std::cout << "Colliders: " << count << std::endl;
	for each (Collider3D* colliderPtr in colliderPtrs) if (colliderPtr != nullptr) colliderPtr->print();
	std::cout << std::endl;

	std::cout << "Children: " << std::endl;
	if (child1 == nullptr) std::cout << "child 1 = nullptr" << std::endl;
	else
	{
		std::cout << "child 1: ";
		child1->print();
	}
	if (child2 == nullptr) std::cout << "child 2 = nullptr" << std::endl;
	else
	{
		std::cout << "child 2: ";
		child2->print();
	}
	if (child3 == nullptr) std::cout << "child 3 = nullptr" << std::endl;
	else
	{
		std::cout << "child 3: ";
		child3->print();
	}
	if (child4 == nullptr) std::cout << "child 4 = nullptr" << std::endl;
	else
	{
		std::cout << "child 4: ";
		child4->print();
	}
	if (child5 == nullptr) std::cout << "child 5 = nullptr" << std::endl;
	else
	{
		std::cout << "child 5: ";
		child5->print();
	}
	if (child6 == nullptr) std::cout << "child 6 = nullptr" << std::endl;
	else
	{
		std::cout << "child 6: ";
		child6->print();
	}
	if (child7 == nullptr) std::cout << "child 7 = nullptr" << std::endl;
	else
	{
		std::cout << "child 7: ";
		child7->print();
	}
	if (child8 == nullptr) std::cout << "child 8 = nullptr" << std::endl;
	else
	{
		std::cout << "child 8: ";
		child8->print();
	}
	std::cout << std::endl;
}

OctNode::~OctNode()
{
	if (child1 != nullptr) delete child1;
	if (child2 != nullptr) delete child2;
	if (child3 != nullptr) delete child3;
	if (child4 != nullptr) delete child4;
	if (child5 != nullptr) delete child5;
	if (child6 != nullptr) delete child6;
	if (child7 != nullptr) delete child7;
	if (child8 != nullptr) delete child8;
}

bool OctNode::collidesWith(Collider3D* otherColliderPtr)
{
	//(Filter out colliders that don’t hit binBox
	if (!binBox.collidesWith(otherColliderPtr)) return false;

	//, then check collisions vs each collider (leaf)
	if (isLeaf)
		for each (Collider3D* colliderPtr in colliderPtrs)
		{
			if (colliderPtr != nullptr)
				if (colliderPtr->collidesWith(otherColliderPtr))
					return true;
		}

	//or child (not a leaf).)
	if (!isLeaf)
	{
		if (child1->collidesWith(otherColliderPtr)) return true;
		if (child2->collidesWith(otherColliderPtr)) return true;
		if (child3->collidesWith(otherColliderPtr)) return true;
		if (child4->collidesWith(otherColliderPtr)) return true;
		if (child5->collidesWith(otherColliderPtr)) return true;
		if (child6->collidesWith(otherColliderPtr)) return true;
		if (child7->collidesWith(otherColliderPtr)) return true;
		if (child8->collidesWith(otherColliderPtr)) return true;
	}

	// If no collisions, return false.
	return false;
}

void OctNode::add(Collider3D* otherColliderPtr)
{
	//(Filter out colliders that don’t hit binBox
	if (!binBox.collidesWith(otherColliderPtr))
		return;

	// Check if we have to branch
	if (count + 1 > capacity)
		branch();

	//, then add collider to this node (leaf) and increment count
	if (isLeaf)
		colliderPtrs[count++] = otherColliderPtr;

	//or add collider to its children (not a leaf).)
	if (!isLeaf)
	{
		child1->add(otherColliderPtr);
		child2->add(otherColliderPtr);
		child3->add(otherColliderPtr);
		child4->add(otherColliderPtr);
		child5->add(otherColliderPtr);
		child6->add(otherColliderPtr);
		child7->add(otherColliderPtr);
		child8->add(otherColliderPtr);
	}
}

void OctNode::branch()
{
	// Set leaf = false
	isLeaf = false;

	// Make child nodes
	glm::vec3 qWidth = glm::vec3(binBox.e.x * .5, binBox.e.y * .5, binBox.e.z * .5);

	child1 = new OctNode(binBox.c + glm::vec3(-1, -1, -1) * qWidth, qWidth);
	child2 = new OctNode(binBox.c + glm::vec3(-1, -1, 1) * qWidth, qWidth);
	child3 = new OctNode(binBox.c + glm::vec3(-1, 1, 1) * qWidth, qWidth);
	child4 = new OctNode(binBox.c + glm::vec3(1, 1, 1) * qWidth, qWidth);
	child5 = new OctNode(binBox.c + glm::vec3(1, 1, -1) * qWidth, qWidth);
	child6 = new OctNode(binBox.c + glm::vec3(1, -1, -1) * qWidth, qWidth);
	child7 = new OctNode(binBox.c + glm::vec3(-1, 1, -1) * qWidth, qWidth);
	child8 = new OctNode(binBox.c + glm::vec3(1, -1, 1) * qWidth, qWidth);

	// Add this node’s colliders to the children
	// Set this node’s collider pointers to nullptr
	for (int i = 0; i < count; i++)
	{
		child1->add(colliderPtrs[i]);
		child2->add(colliderPtrs[i]);
		child3->add(colliderPtrs[i]);
		child4->add(colliderPtrs[i]);
		child5->add(colliderPtrs[i]);
		child6->add(colliderPtrs[i]);
		child7->add(colliderPtrs[i]);
		child8->add(colliderPtrs[i]);
		colliderPtrs[i] = nullptr;
	}

	// Set count = 0.
	count = 0;
}
