//Tyler Longbons

#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <math.h>

#include "image.h"


int height;
int width;
int MAX_PIXEL_VAL;
int total_Num_Pixels;
int min;
int max;
double average;

//Where we are storing the file
std::vector < std::vector < std::string > > origFileData;
//std::vector <std::string> pixels;
std::vector <int> scaledPixels;
std::vector <int> pixels;


std::string getFileType(std::istream& inFile)
{
	if(!inFile)
	{
		return "invalid";
	}
	
	std::string line;
	getline(inFile, line);

	for(unsigned int i = 0; i < 3; i++)
	{
		char c = line[i];
		if(i == 0)
		{
			if(c != 'P')
			{
				return "invalid";
			}
		}
		else if(i == 1)
		{
			if(c != '2' && c != '5')
			{
				return "invalid";
			}
			if(c == '5')
			{
				return "binary";
			}
		}else
		{
			if(!isspace(c) && c != '\0' && c != '#')
			{
				return "invalid";
			}
		}
	}
		return "ascii";
}


//Use for Debugging
void printOrigFinalData()
{
		for(unsigned int i = 0; i < 10;i++)
		{
			std::cout<<"Line: " << i << std::endl;
				for(unsigned int j = 0; j < origFileData[i].size();j++)
				{

					std::cout<<"MyData: " << origFileData[i][j] <<std::endl;
				}
		}
}

//Use for debugging
void printPixels()
{
		for(unsigned int i = 0;i < 5;i++)
		{
			std::cout<<"Pixels: " << pixels[i] << std::endl;
		}
}


int getWidth()
{
	width = pixels[0];
	if(width <= 0)
	{
		return -1;
	}
	return 0;
}

int getHeight()
{
	height = pixels[1];
	if(height <= 0)
	{
		return -1;
	}
	return 0;
}
int getMaxPixelVal()
{
	MAX_PIXEL_VAL = pixels[2];
	if(MAX_PIXEL_VAL < 0  || MAX_PIXEL_VAL > 256)
	{
		return -1;
	}
	return 0;
}

int processHeaderData()
{
	if(getWidth() == -1)
	{
		return -1;
	}
	if(getHeight() == -1)
	{
		return -1;
	}
	if(getMaxPixelVal() == -1)
	{
		return -1;
	}


	return 0;
}



bool isTokenNumber(std::string token)
{
	bool isNumber = true;
	unsigned int i         = 0;
	while(isNumber && i < token.length())
	{
		char c 	  = token[i];
		if(isdigit(c) == 0)
		{
			isNumber = false;
		}
		i++;
	}
	return isNumber;
}

bool isTokenComment(std::string token)
{
	int found = token.find("#");
	if(found == -1)
	{
		return false;
	}else
	{
		return true;
	}
}

std::string getCommentNumber(std::string token)
{
		int found                = token.find("#");
		std::string commentVal   = "-1";
		if (found != -1)
		{
			if(found > 0)
			{
				commentVal       = token.substr(0, found);
			}
		}
	return commentVal;
}


int processAsciiFileData()
{


	for(unsigned int i = 0; i < origFileData.size();i++)
		{
				for(unsigned int j = 0; j < origFileData[i].size();j++)
				{
					if(i == 0 && j == 0)
					{	
						if(isTokenComment(origFileData[i][j]) == true)
						{
							if(origFileData.size() == 1)
							{
								return -1;
							}
						
						}

					}else
					{
						if(isTokenNumber(origFileData[i][j]) == true)
						{
							pixels.push_back(atoi(origFileData[i][j].c_str()));
						}else if(isTokenComment(origFileData[i][j]) == true)
						{
							std::string commentVal = getCommentNumber(origFileData[i][j]);
								if(commentVal != "-1")
								{
									pixels.push_back(atoi(commentVal.c_str()));
									break;
								}else
								{
									break;
								}
						}else
						{
							return -1;
						}
					}	
				}
		}


	return 0;
}



int readAsciiFile(std::istream& inFile)
{
	
	if(!inFile)
	{
		return -1;
	}
	//int lineCount = 0;
	std::string line;
	//Read each line primarily to make parsing comments easier
	
	while(getline(inFile, line))
	{
		std::vector<std::string> row;

		std::istringstream lineStream(line);
		std::string token;

		//break line into tokens to make sure we are 
		//getting valid entries 
		while(lineStream >> token)
		{
			row.push_back(token);
		}
		
		origFileData.push_back(row);
		//lineCount++;
	}
	

		return 0;
}



int validatePixels()
{
	total_Num_Pixels    = width * height;
	int actualNumPixels = 0;
	if(MAX_PIXEL_VAL == 256)
	{
		MAX_PIXEL_VAL = 255;
	}

	for(unsigned int i = 3; i < pixels.size(); i++)
	{
		int pixel = pixels[i]; 
		if(pixel <= MAX_PIXEL_VAL && pixel >= 0)
		{
			actualNumPixels++;
		}else
		{
			return -1;
		}
	}

		if(total_Num_Pixels != actualNumPixels)
		{
			return -1;
		}

		return 0;
}



int findMax()
{
	max = 0;

	for(unsigned int i = 3; i < pixels.size(); i++)
	{
		int pixel = pixels[i]; 
		if(pixel > max)
		{
			max = pixel;
		}
	}
	return 0;
}



int findMin()
{
	min = 255;

	for(unsigned int i = 3; i < pixels.size(); i++)
	{
		int pixel = pixels[i]; 
		if(pixel < min)
		{
			min = pixel;
		}
	}
	return 0;

}


int findAverage()
{
	average = 0;

	for(unsigned int i = 3; i < pixels.size(); i++)
	{
		int pixel = pixels[i]; 
		average += pixel;
	}
	average /= (total_Num_Pixels);
	return 0;
}


//Used for Debugging;
void printNewPixels()
{
	for(unsigned int i = 0; i < scaledPixels.size();i++)
	{
		std::cout<< "Pixel: " << scaledPixels[i] <<std::endl;
	}
}

int rescale()
{

for(unsigned int i = 3; i < pixels.size(); i++)
{
	int pixel  = pixels[i];
	double pix = pixel - min;
	double den = max   - min;
	if(den == 0)
	{
		return -1;
	}
	double newPix = (255.0 * pix) / den;
	int newPixel  = round(newPix);
	
	scaledPixels.push_back(newPixel);
}

return 0;

}


int writeAsciiFile(std::ostream& outFile)
{
	if(!outFile)
	{
		return -1;
	}

	outFile << "P2" <<std::endl;
	outFile << width << " " << height <<std::endl;
	outFile << "255" << std::endl;
	
	int colCount = 0;
	for(unsigned int i = 0; i < scaledPixels.size(); i++)
	{
		if(colCount == 19)
		{
			colCount = 0;
			outFile << scaledPixels[i] << std::endl;
		}else
		{
			outFile << scaledPixels[i] << " " ;
			colCount++;
		}
		
	}
	
	return 0;
}

int writeBinaryFile(std::ostream& outFile)
{
	int newMaxVal = 255;
	
	if(!outFile)
	{
		return -1;
	}
		outFile << "P5";
		outFile.write((char*)&width,         sizeof(int));
		outFile.write((char*)&height,        sizeof(int));
		outFile.write((char*)&newMaxVal,     sizeof(int));

		for(unsigned int i = 0; i < scaledPixels.size(); i++)
	{
			outFile.write((char*)&scaledPixels[i], sizeof(unsigned char));
	}
	
return 0;


}


std::string getExtension(std::string& fileName)
{
	std::string extension = fileName.substr(fileName.find("."), fileName.length());
	return extension;
}


int readBinaryFile(std::istream& inFile)
{

  //std::vector <int> binaryValues;
  while(!inFile.eof())
  {
  	
    unsigned c = inFile.get();
    pixels.push_back(c);
  }
  pixels.erase(pixels.begin() + pixels.size() - 1);

  pixels.erase(pixels.begin(),     pixels.begin() + 2);
  pixels[0] = pixels[0]|pixels[1]<<8|pixels[2]<<16|pixels[3]<<24;	
  pixels.erase(pixels.begin() + 1, pixels.begin() + 4);
  pixels[1] = pixels[1]|pixels[2]<<8|pixels[3]<<16|pixels[4]<<24;	
  pixels.erase(pixels.begin() + 2, pixels.begin() + 5);
  pixels[2] = pixels[2]|pixels[3]<<8|pixels[4]<<16|pixels[5]<<24;	
  pixels.erase(pixels.begin() + 3, pixels.begin() + 6);


return 0;
}



