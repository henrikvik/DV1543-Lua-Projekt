#include "Editor.h"

std::vector<Blob*> Editor::readFromFile()
{
	std::vector<Blob*> blobs;
	
	float radius;
	float growthRate;



	return blobs;
}

void Editor::writeToFile(float hm, float growthRate, float redColor, float greenColor, float blueColor, const char name, const char script)
{
	std::ofstream myFile;
	myFile.open("Editor.txt");

	myFile	<< hm << " " 
			<< growthRate << " " 
			<< redColor << " " 
			<< greenColor << " " 
			<< blueColor << " " 
			<< name << " " 
			<< script 
			<< std::endl;

	myFile.close();
}
