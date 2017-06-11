#include "FileHandler.h"
#include <string>


std::vector<Blob*> FileHandler::readFromFile(const char* file)
{
	std::vector<Blob*> blobs;
	
	float lifeSpan;
	float moveSpeed;
	int redColor;
	int greenColor;
	int blueColor;
	float radius;
	float x;
	float y;
	std::string script;		

	std::ifstream in, count;	
	
	count.open(file);
	std::string str;
	int nrOfBlobs = 0;
	while (std::getline(count, str))
	{
		nrOfBlobs++;
	}
	count.close();
	in.open(file);
	for (int i = 0; i < nrOfBlobs; i++)
	{//lifespan,  movespeed, red, green, blue, radius, x, y, scrtipt
		in	>> lifeSpan 
			>> moveSpeed
			>> redColor 
			>> greenColor 
			>> blueColor
			>> radius
			>> x
			>> y;
		in.ignore();
		std::getline(in, script);

		Blob* blob = new Blob(lifeSpan, moveSpeed, redColor, greenColor, blueColor, radius, x, y, script);
		
		blobs.push_back(blob);
	}

	in.close();

	return blobs;
}

void FileHandler::writeToFile(const char* file, std::vector<Blob*> blobs)
{
	std::string str;

	std::ofstream myFile;
	myFile.open(file);

	for each (Blob* blob in blobs)
	{
		str = blob->toString();
		myFile << str << std::endl;
	}

	myFile.close();
}
