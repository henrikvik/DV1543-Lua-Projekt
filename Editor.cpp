#include "Editor.h"

std::vector<Blob*> Editor::readFromFile(const char* file, int nrOfBlobs)
{
	std::vector<Blob*> blobs;
	
	float lifeSpan;
	float growthRate;
	float moveSpeed;
	int redColor;
	int greenColor;
	int blueColor;
	char name;			//Blob will ha in std::string
	char script;		//          --||--

	std::ifstream in;	
	in.open(file);

	for (int i = 0; i < nrOfBlobs; i++)
	{
		in	>> lifeSpan 
			>> growthRate 
			>> moveSpeed
			>> redColor 
			>> greenColor 
			>> blueColor 
			>> name 
			>> script;

		Blob* blob = new Blob(lifeSpan, growthRate, moveSpeed, redColor, greenColor, blueColor, name, script);
		
		blobs.push_back(blob);
	}

	in.close();

	return blobs;
}

void Editor::writeToFile(const char* file, float lifeSpan, float growthRate, float moveSpeed, int redColor, int greenColor, int blueColor, const char* name, const char* script)
{
	std::ofstream myFile;
	myFile.open(file);

	myFile	<< lifeSpan << " " 
			<< growthRate << " " 
			<< redColor << " " 
			<< greenColor << " " 
			<< blueColor << " " 
			<< name << " " 
			<< script 
			<< std::endl;

	myFile.close();
}
