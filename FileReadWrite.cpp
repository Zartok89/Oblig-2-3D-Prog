#include "FileReadWrite.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "VBO.h"


void ReadWriteFiles::ReadFromFileWriteIntoNewFile(std::string FileToRead, std::string NewDataFile)
{
	std::fstream MyFileRead;
	std::fstream MyFileWrite;
	MyFileRead.open(FileToRead, std::ios::in);
	MyFileWrite.open(NewDataFile, std::ios::out);

	if (MyFileRead.is_open() && MyFileWrite.is_open())
	{
		MyFileWrite << std::fixed << std::setprecision(2);
		std::cout << "Reading file: " << FileToRead << std::endl;
		std::cout << "Starting to write into new file: " << NewDataFile << std::endl;
		std::string Line;
		// Skip the first line
		std::getline(MyFileRead, Line);
		while (std::getline(MyFileRead, Line))
		{
			if (Line == "v")
			{
				RemovingUnwantedChars(Line);

				// Tokenize the line based on spaces
				std::istringstream iss(Line);
				std::vector<float> floats;
				float Number;
				while (iss >> Number)
				{
					floats.push_back(Number);
				}

				// Write the code to floats to the output file
				for (float Number : floats)
				{
					MyFileWrite << Number << " ";
				}
				MyFileWrite << std::endl;
			}
		}
		MyFileRead.close();
		MyFileWrite.close();
		std::cout << "Characters removed" << std::endl;
	}
	else
	{
		std::cerr << "Error opening files." << std::endl;
	}
}

//void ReadWriteFiles::FromDataToVertexVector(std::string DataFileToVertexVector, std::vector<Vertex>& VerticesVector)
//{
//	std::fstream MyFile;
//	MyFile.open(DataFileToVertexVector, std::ios::in); // Read mode
//	if (MyFile.is_open())
//	{
//		std::cout << DataFileToVertexVector << " File has been opened correctly\n";
//		std::string Line;
//		while (std::getline(MyFile, Line))
//		{
//			std::istringstream iss(Line);
//			std::vector<float> floats;
//			float Number;
//			while (iss >> Number)
//			{
//				floats.push_back(Number);
//			}
//			float TempX = floats[0];
//			float TempY = floats[1];
//			float TempZ = floats[2];
//			float TempR = floats[3];
//			float TempG = floats[4];
//			float TempB = floats[5];
//			float TempU = floats[6];
//			float TempV = floats[7];
//			VerticesVector.emplace_back(Vertex{ TempX, TempY, TempZ, TempR});
//		}
//
//		//std::cout << "Amount of Vertexes added to the vector: " << VerticesVector.size() << std::endl;
//		MyFile.close();
//	}
//	else
//	{
//		std::cerr << "Error opening files." << std::endl;
//	}
//}
//
//void ReadWriteFiles::SubdivideData(std::vector<Vertex>& VerticesVector, std::vector<Vertex>& NewSubdividedDataVector)
//{
//	float opplosning = 9;
//	NewSubdividedDataVector.emplace_back(VerticesVector[0].x, VerticesVector[0].y, 0, 0, 0, 0, 0, 0);
//
//	for (float i = 0; i < VerticesVector.size() - 1; i++)
//	{
//		float TempN = (VerticesVector[i + 1].x - VerticesVector[i].x);
//		float TempNY = (VerticesVector[i + 1].y - VerticesVector[i].y);
//		float TempX = VerticesVector[i].x;
//		float TempY = VerticesVector[i].y;
//		float hX = TempN / opplosning;
//		float hY = TempNY / opplosning;
//		for (float j = hX; j <= TempN; j += hX)
//		{
//			float newX = TempX + j;
//			float newY = TempY += hY;
//			NewSubdividedDataVector.emplace_back(newX, newY, 1, 1, 1, 0, 0, 0);
//		}
//	}
//	for (Vertex tempvert : NewSubdividedDataVector)
//	{
//		std::cout << "x: " << tempvert.x << ", ";
//		std::cout << "y: " << tempvert.y << "\n";
//	}
//}

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