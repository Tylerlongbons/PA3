#ifndef IMAGE_H
#define IMAGE_H
//Tyler Longbons


int readAsciiFile(std::istream& inFile);
int findMax();
int findMin();
int findAverage();
int writeAsciiFile(std::ostream& outFile);
void resize();
void printOrigFinalData();
void printPixels();
bool isTokenNumber(std::string token);
bool isTokenComment(std::string token);
int processHeaderData();
int processAsciiFileData();
std::string getFileType(std::istream& inFile);
int getMaxPixelVal();
int getWidth();
int getHeight();
int validatePixels();
int rescale();
void printNewPixels();
int writeBinaryFile(std::ostream& outFile);
std::string getExtension(std::string& fileName);
int readBinaryFile(std::istream& inFile);




#endif