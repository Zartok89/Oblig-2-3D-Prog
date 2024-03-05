#pragma once
#include "Libraries/include/glm/glm.hpp"
#include <cmath>
#include "FileReadWrite.h" 
#include "Mesh.h" 

struct BoundingBox;
 
class IBounded
{
	virtual BoundingBox& GetBoundingBox() = 0;
};


struct BoundingBox
{
    std::shared_ptr<ReadWriteFiles> ReadWritePTR = std::make_shared<ReadWriteFiles>();
	bool Intersect(std::vector<float> OrigoPoints);  
};

