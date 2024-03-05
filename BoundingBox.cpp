#include "BoundingBox.h"

bool BoundingBox::Intersect(const BoundingBox& b)
{
	///AABB --> Axis Align Collision
	auto& a = *this;
	if (abs(a.center.x - b.center.x) > (a.radius.x + b.radius.x)) return 0;
	if (abs(a.center.y - b.center.y) > (a.radius.y + b.radius.y)) return 0;
	if (abs(a.center.z - b.center.z) > (a.radius.z + b.radius.z)) return 0;

	return false;
}
