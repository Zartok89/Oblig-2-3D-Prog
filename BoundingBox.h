#pragma once
#include "Libraries/include/glm/glm.hpp"
#include <cmath>

struct BoundingBox;


class IBounded
{
	virtual BoundingBox& GetBoundingBox() = 0;
};


struct BoundingBox
{
	glm::vec3 center{ 0.f };
	glm::vec3 radius{ 1.f };

	bool Intersect(const BoundingBox& b); 
};

