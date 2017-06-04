#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Blob.h"



class FileHandler
{
public:

	static std::vector<Blob*> readFromFile(const char* file);
	static void writeToFile(const char* file, float lifeSpan, float growthRate, float moveSpeed, int redColor, int greenColor, int blueColor, float radius, float x, float y, const char* script);

private:


};