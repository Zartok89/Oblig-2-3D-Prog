#pragma once
#include <string>
#include <vector>

#include "VBO.h"

class ReadWriteFiles
{
public:

	ReadWriteFiles() = default;
	void WriteToFile(std::string Filepath, std::vector<Vertex>& VertexVector);
	void AppendToFile(std::string Filepath);
	void ReadFromFile(std::string FileToRead);
	void ReadFromFileWriteIntoNewFile(std::string FileToRead, std::string NewDataFileVertices, std::string NewDataFileIndices);
	void FromDataToVertexVector(std::string VertexDataFile, std::vector<Vertex>& VerticesVector);
	void FromDataToIndicesVector(std::string IndicesDataFile, std::vector<int>& IndicesVector);
	void SubdivideData(std::vector<Vertex>& VerticesVector, std::vector<Vertex>& NewSubdividedDataFile);
	void RemovingUnwantedChars(std::string& Line);
};
