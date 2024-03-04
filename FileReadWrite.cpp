#include "FileReadWrite.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "VBO.h"

struct Face {
	std::vector<int> indices;
};

void ReadWriteFiles::ReadFromFileWriteIntoNewFile(std::string FileToRead, std::string NewDataFileVertices, std::string NewDataFileFaces)
{
	std::fstream MyFileRead;
	std::fstream MyFileVerts;
	std::fstream MyFileFaces;
	MyFileRead.open(FileToRead, std::ios::in);
	MyFileVerts.open(NewDataFileVertices, std::ios::out);
	if (MyFileRead.is_open() && MyFileVerts.is_open())
	{
		MyFileVerts << std::fixed << std::setprecision(2);
		std::cout << "Reading file: " << FileToRead << std::endl;
		std::cout << "Starting to write into new file: " << NewDataFileVertices << std::endl;
		std::string Line;
		// Skip the first line
		std::getline(MyFileRead, Line);
		while (std::getline(MyFileRead, Line))
		{
			std::istringstream iss(Line);
			std::string token;
			iss >> token;
			if (token == "v")
			{
				RemovingUnwantedChars(Line);

				// Tokenize the line based on spaces
				std::istringstream iss(Line);
				std::vector<float> floats;
				float Vertices;
				while (iss >> Vertices)
				{
					floats.push_back(Vertices);
				}

				// Write the code to floats to the output file
				for (float Number : floats)
				{
					MyFileVerts << Number << " ";
				}
				MyFileVerts << std::endl;
			}
		}
		MyFileRead.close();
		MyFileVerts.close();

		MyFileFaces.open(NewDataFileFaces, std::ios::out);
		MyFileRead.open(FileToRead, std::ios::in);
		std::string Line2;
		// Skip the first line
		std::getline(MyFileRead, Line2);
		while (std::getline(MyFileRead, Line2))
		{
			std::istringstream iss(Line2);
			std::string token;
			iss >> token;
			if (token == "f")
			{
				RemovingUnwantedChars(Line2);
				// Tokenize the line based on spaces
				std::istringstream iss(Line2);
				Face face;
				std::vector<float> floats;
				float Vertices;
				int index;
				char slash;  // to read the slashes

				while (iss >> index)
				{
					floats.push_back(index - 1);

					// Skip texture coordinates and normals
					iss >> std::ws;  // consume whitespace
					if (iss.peek() == '/')
					{
						iss.ignore();  // skip the slash
						while (iss.peek() != ' ' && iss.peek() != '\n' && iss.peek() != '\r' && iss.peek() != EOF)
						{
							iss.ignore();  // skip characters until the next whitespace or end of line
						}
					}
				}
				// Write the code to floats to the output file
				for (float Number : floats)
				{
					MyFileFaces << Number << " ";
				}
				MyFileFaces << std::endl;
			}
		}
		MyFileRead.close();
		MyFileFaces.close();
	}
	else
	{
		std::cerr << "Error opening files." << std::endl;
	}
}

void ReadWriteFiles::FromDataToVertexVector(std::string VertexDataFile, std::vector<Vertex>& VerticesVector)
{
	std::fstream MyFileVertices;
	MyFileVertices.open(VertexDataFile, std::ios::in); // Read mode
	if (MyFileVertices.is_open())
	{
		std::cout << VertexDataFile << " File has been opened correctly\n";
		std::string LineVert;
		while (std::getline(MyFileVertices, LineVert))
		{
			std::istringstream iss(LineVert);
			std::vector<float> floats;
			float Number;
			while (iss >> Number)
			{
				floats.push_back(Number);
			}
			float TempX = floats[0];
			float TempY = floats[1];
			float TempZ = floats[2];
			glm::vec3 position;
			VerticesVector.emplace_back(Vertex{ glm::vec3(TempX, TempY, TempZ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1, 1)});
		}

		//std::cout << "Amount of Vertexes added to the vector: " << VerticesVector.size() << std::endl;
		MyFileVertices.close();
	}
	else
	{
		std::cerr << "Error opening files." << std::endl;
	}
}

void ReadWriteFiles::FromDataToIndicesVector(std::string IndicesDataFile, std::vector<int>& IndicesVector)
{
	std::fstream MyFileIndices;
	MyFileIndices.open(IndicesDataFile, std::ios::in); // Read mode
	if (MyFileIndices.is_open())
	{
		std::cout << IndicesDataFile << " File has been opened correctly\n";
		std::string LineVert;
		while (std::getline(MyFileIndices, LineVert))
		{
			std::istringstream iss(LineVert);
			int Number;
			while (iss >> Number)
			{
				IndicesVector.push_back(Number);
			}
		}

		//std::cout << "Amount of Vertexes added to the vector: " << VerticesVector.size() << std::endl;
		MyFileIndices.close();
	}
	else
	{
		std::cerr << "Error opening files." << std::endl;
	}
}


void ReadWriteFiles::RemovingUnwantedChars(std::string& Line)
{
	// Symbols and lines to remove:
	Line.erase(std::remove(Line.begin(), Line.end(), 'x'), Line.end());
	Line.erase(std::remove(Line.begin(), Line.end(), 'y'), Line.end());
	Line.erase(std::remove(Line.begin(), Line.end(), 'z'), Line.end());
	Line.erase(std::remove(Line.begin(), Line.end(), 'r'), Line.end());
	Line.erase(std::remove(Line.begin(), Line.end(), 'g'), Line.end());
	Line.erase(std::remove(Line.begin(), Line.end(), 'b'), Line.end());
	Line.erase(std::remove(Line.begin(), Line.end(), 'u'), Line.end());
	Line.erase(std::remove(Line.begin(), Line.end(), 'v'), Line.end());
	Line.erase(std::remove(Line.begin(), Line.end(), ':'), Line.end());
	Line.erase(std::remove(Line.begin(), Line.end(), ','), Line.end());
	Line.erase(std::remove(Line.begin(), Line.end(), 'f'), Line.end());
}