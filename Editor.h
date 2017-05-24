#include <iostream>
#include <fstream>
#include <vector>
#include "Source\Blob.h"



class Editor
{
public:

	std::vector<Blob*> readFromFile(const char* file, int nrOfBlobs);
	void writeToFile(const char* file, float lifeSpan, float growthRate, float moveSpeed, int redColor, int greenColor, int blueColor, const char* name, const char* script);

private:


};