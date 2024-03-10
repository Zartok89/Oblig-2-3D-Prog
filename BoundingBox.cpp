#include "BoundingBox.h"

//bool BoundingBox::IntersectPlayer(std::vector<glm::vec3> &originPoint, std::vector<glm::vec3> hitRadius)
//{ 
//	/*std::vector<float> originPoint = ReadWritePTR->OrigoVector;*/ 
//	///AABB --> Axis Align Collision
//	for (auto points : originPoint) 
//	{
//		for (auto hr : hitRadius) 
//		{
//			/*if (abs(points.x - player.x) > (hr.x + player.radius.x)) return 0;
//			if (abs(points.y - player.y) > (hr.y + player.radius.y)) return 0;
//			if (abs(points.z - player.z) > (hr.z + player.radius.z)) return 0;*/
//		}
//	}
//	
//
//	return false;
//}
//
//bool BoundingBox::IntersectObject(const std::pair<std::vector<Vertex>, std::vector<Vertex>>& getMesh, std::vector<glm::vec3> getVec3)
//{
//	getOrigoVector(getMesh);
//	for (const Vertex& meshA : getMesh.first)
//	{
//		for (const Vertex& meshB : getMesh.second)    
//		{    
//			if (abs(meshA.position.x - meshB.position.x) > (ObjectOrigoA + ObjectOrigoB)) return 0;  
//			if (abs(meshA.position.y - meshB.position.y) > (ObjectOrigoA + ObjectOrigoB)) return 0; 
//			if (abs(meshA.position.z - meshB.position.z) > (ObjectOrigoA + ObjectOrigoB)) return 0;  
//		}
//	}
//}

//void BoundingBox::getOrigoVector(const std::pair<std::vector<Vertex>, std::vector<Vertex>> &getMesh)
//{
//	//Test: bru: -20
//	for (const Vertex& OmeshA : getMesh.first)
//	{
//		tempVecA.emplace_back(OmeshA.position.x);
//		tempVecA.emplace_back(OmeshA.position.y);
//		tempVecA.emplace_back(OmeshA.position.z);
//	}
//
//	for (auto abc : tempVecA)
//	{
//		totVertPointsA += abc;
//	}
//	ObjectOrigoA = totVertPointsA / tempVecA.size();  
//
//	//Test bakke: -28
//	for (const Vertex& OmeshB : getMesh.second) 
//	{
//		tempVecB.emplace_back(OmeshB.position.x);
//		tempVecB.emplace_back(OmeshB.position.y);
//		tempVecB.emplace_back(OmeshB.position.z);
//	}
//
//	for (auto abc : tempVecB)  
//	{
//		totVertPointsB += abc; 
//	}
//	ObjectOrigoB = totVertPointsB / tempVecB.size();
//}

bool BoundingBox::IntersectAABB(const BoundingBox& otherObject, glm::vec3* mtv) const
{
	glm::vec3 vecDiff = otherObject.objCenter - this->objCenter;
	glm::vec3 sumExtent = this->objExtent + otherObject.objExtent;

	///Checking collison for each axis: x, y & z.
	for (int axis = 0; axis < 3; ++axis)
	{
		///If distance is greater or equal to the sum of both AABB-extents, no collision is detected
		if (abs(vecDiff[axis] >= sumExtent[axis]))
		{
			return false;
		}
	}

	///MTV = minimum Translated Vector
	if (mtv)
	{
		glm::vec3 mtvValues;

	    ///MTV-values
		for (int axis = 0; axis < 3; ++axis) //axis and ++axis is incremented at the same time
		{
			mtvValues[axis] = sumExtent[axis] - abs(vecDiff[axis]);
		}

		///Minimum non-zero translation vector
		float nzTV = FLT_MAX;
		int minAxis = -1;

		for (int axis = 0; axis < 3; ++axis)
		{
			if (mtvValues[axis] < nzTV && mtvValues[axis] > 0)
			{
				nzTV = mtvValues[axis];
				minAxis = axis;
			}
		}

		if (minAxis != -1);
		{
			///Declaring new vec3 with x,y & z = 0
			glm::vec3 direction = glm::vec3(0);

			///direction at index "minAxis" is equal to 1 if "vecDiff" at index "minAxis"
			///-is greater than 0, else -1;
			direction[minAxis] = vecDiff[minAxis] > 0 ? 1 : -1;

			///Pointer to the vec3 "mtv" tat needs to be updated updating.
			*mtv = direction * nzTV;
		}

	}

	///The intersection is true, exists
	return true; 
}
