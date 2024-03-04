#pragma once
#include <string>
#include <vector>

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z, float r, float b, float g, float u, float v);
	float x, y, z, r, b, g, u, v;
};

class ReadWriteFiles
{
public:

	ReadWriteFiles();
	void WriteToFile(std::string Filepath, std::vector<Vertex>& VertexVector);
	void AppendToFile(std::string Filepath);
	void ReadFromFile(std::string FileToRead);
	void ReadFromFileWriteIntoNewFile(std::string FileToRead, std::string NewDataFile);
	void FromDataToVertexVector(std::string DataFileToVertexVector, std::vector<Vertex>& VerticesVector);
	void SubdivideData(std::vector<Vertex>& VerticesVector, std::vector<Vertex>& NewSubdividedDataFile);
	void RemovingUnwantedChars(std::string& Line);
};