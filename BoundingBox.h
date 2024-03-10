#pragma once
#include "Libraries/include/glm/glm.hpp"
#include <cmath>
#include "FileReadWrite.h" 
#include "Mesh.h" 
#include "VBO.h"

struct BoundingBox;
 
class IBounded
{
	virtual BoundingBox GetBoundingBox() = 0;
};


struct BoundingBox
{
	///Deafult values for Bounding Box
	glm::vec3 objCenter{ 0.0f,0.0f,0.0f };
	glm::vec3 objExtent{ 0.5f,0.5f,0.5f };
	std::vector<Vertex> getVertex;

	BoundingBox() = default;
	BoundingBox(const std::vector<Vertex>&, const glm::vec3& objCenter, const glm::vec3& objExtent) : getVertex(getVertex), objCenter(objCenter), objExtent(objExtent) {};

	bool IntersectAABB(const BoundingBox& otherObject, glm::vec3* MTV) const;
    std::shared_ptr<ReadWriteFiles> ReadWritePTR = std::make_shared<ReadWriteFiles>();
	//bool IntersectPlayer(std::vector<glm::vec3> &originPoint, std::vector<glm::vec3> hitRadius);  

	//bool IntersectObject(const std::pair<std::vector<Vertex>, std::vector<Vertex>> &getMesh, std::vector<glm::vec3> getVec3);





	/*void getOrigoVector (const std::pair<std::vector<Vertex>, std::vector<Vertex>>  &getMesh);
	std::vector<float> tempVecA;
	std::vector<float> tempVecB;

	float ObjectOrigoA = 0;
	float ObjectOrigoB = 0;

	float totVertPointsA = 0;
	float totVertPointsB = 0;*/
	
};

