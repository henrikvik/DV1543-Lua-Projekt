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
	static void writeToFile(const char* file, std::vector<Blob*> blobs);

private:


};