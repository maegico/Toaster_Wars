#include "Collider3D.h"

void Collider3D::print()
{
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Collider: c.x = " << c.x << "c.y = " << c.y << "c.z = " << c.z << ",   e.x = " << e.x << "e.y = " << e.y << "e.z = " << e.z << std::endl;
}

bool Collider3D::collidesWith(Collider3D* colliderPtr)
{
	float ra, rb;
	glm::mat3 r, absR;

	//compute roation matrix epressing colliderPtr in a's coordinate frame
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			r[i][j] = dot(u[i], colliderPtr->u[j]);
		}
	}

	//Compute translation vector t
	glm::vec3 t = colliderPtr->c - c;
	//bring translation into a's coordinate frame
	t = glm::vec3(dot(t, u[0]), dot(t, u[1]), dot(t, u[2]));

	//Compute common subexpressions-> Add in an epsilon term to
	//counteract arithmetic errors when two edges are parallel and
	//their cross product is (near) null
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//took out the "+ EPSILON"
			absR[i][j] = abs(r[i][j]) + FLT_EPSILON;
		}
	}

	//Test axes L = A0, L = A1, L = A2
	for (int i = 0; i < 3; i++)
	{
		ra = e[i];
		rb = colliderPtr->e[0] * absR[i][0] + colliderPtr->e[1] * absR[i][1] + colliderPtr->e[2] * absR[i][2];
		if (abs(t[i]) > ra + rb) return false;
	}

	//Test axes L = B0, L = B1, L = B2
	for (int i = 0; i < 3; i++)
	{
		ra = e[0] * absR[0][i] + e[1] * absR[1][i] + e[2] * absR[2][i];
		rb = colliderPtr->e[i];
		if (abs(t[0] * r[0][i] + t[1] * r[1][i] + t[2] * r[2][i]) > ra + rb) return false;
	}

	//Test axis l = A0 x B0
	ra = e[1] * absR[2][0] + e[2] * absR[1][0];
	rb = colliderPtr->e[1] * absR[0][2] + colliderPtr->e[2] * absR[0][1];
	if (abs(t[2] * r[1][0] - t[1] * r[2][0]) > ra + rb) return false;

	//Test axis L = A0 x B1
	ra = e[1] * absR[2][1] + e[2] * absR[1][1];
	rb = colliderPtr->e[0] * absR[0][2] + colliderPtr->e[2] * absR[0][0];
	if (abs(t[2] * r[1][1] - t[1] * r[2][1]) > ra + rb) return false;

	//Test axis L = A0 x B2
	ra = e[1] * absR[2][2] + e[2] * absR[1][2];
	rb = colliderPtr->e[0] * absR[0][1] + colliderPtr->e[1] * absR[0][0];
	if (abs(t[2] * r[1][2] - t[1] * r[2][2]) > ra + rb) return false;

	//Test axis L = A1 x B0
	ra = e[0] * absR[2][0] + e[2] * absR[0][0];
	rb = colliderPtr->e[1] * absR[1][2] + colliderPtr->e[2] * absR[1][1];
	if (abs(t[0] * r[2][0] - t[2] * r[0][0]) > ra + rb) return false;

	//Test axis L = A1 x B1
	ra = e[0] * absR[2][1] + e[2] * absR[0][1];
	rb = colliderPtr->e[0] * absR[1][2] + colliderPtr->e[2] * absR[1][0];
	if (abs(t[0] * r[2][1] - t[2] * r[0][1]) > ra + rb) return false;

	//Test axis L = A1 x B2
	ra = e[0] * absR[2][2] + e[2] * absR[0][2];
	rb = colliderPtr->e[0] * absR[1][1] + colliderPtr->e[1] * absR[1][0];
	if (abs(t[0] * r[2][2] - t[2] * r[0][2]) > ra + rb) return false;

	//Test axis L = A2 x B0
	ra = e[0] * absR[1][0] + e[1] * absR[0][0];
	rb = colliderPtr->e[1] * absR[2][2] + colliderPtr->e[2] * absR[2][1];
	if (abs(t[1] * r[0][0] - t[0] * r[1][0]) > ra + rb) return false;

	//Test axis L = A2 x B1
	ra = e[0] * absR[1][1] + e[1] * absR[0][1];
	rb = colliderPtr->e[0] * absR[2][2] + colliderPtr->e[2] * absR[2][0];
	if (abs(t[1] * r[0][1] - t[0] * r[1][1]) > ra + rb) return false;

	//Test axis L = A2 x B2
	ra = e[0] * absR[1][2] + e[1] * absR[0][2];
	rb = colliderPtr->e[0] * absR[2][1] + colliderPtr->e[1] * absR[2][0];
	if (abs(t[1] * r[0][2] - t[0] * r[1][2]) > ra + rb) return false;

	//since no separating axis is found, the OBBs must be intersecting
	return true;
}

Collider3D::Collider3D(glm::vec3 c, glm::vec3 e)
{
	this->c = c;
	this->e = e;
	u[0] = glm::vec3(1, 0, 0);
	u[1] = glm::vec3(0, 1, 0);
	u[2] = glm::vec3(0, 0, 1);
}

Collider3D::Collider3D()
{
}


Collider3D::~Collider3D()
{
}