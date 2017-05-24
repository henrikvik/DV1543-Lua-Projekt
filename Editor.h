#include <iostream>
#include <fstream>
#include <vector>
#include "Source\Blob.h"



class Editor
{
public:

	std::vector<Blob*> readFromFile();
	void writeToFile(float hm, float growthRate, float redColor, float greenColor, float blueColor, const char name, const char script);

private:


};