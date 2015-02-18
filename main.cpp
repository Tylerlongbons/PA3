//Tyler Longbons
//Assignment: PA3


#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "image.h"	



	int main(int argc, char* argv[]){
		if(argc != 3)
		{
		return -1;	
		}
		

		if(strcmp(argv[1],argv[2]) == 0)
		{
			//std::cout<< "Args are the same"<<std::endl;
			return -1;
		}

		std::ifstream inFile(argv[1]);
		std::string fileType = getFileType(inFile);
		std::ifstream inFile2(argv[1]);


		if(fileType == "ascii")
		{
			
			if(readAsciiFile(inFile2) == -1)
			{
				//std::cout<< "Read File Failed"<<std::endl;
				return -1;
			}
			if(processAsciiFileData() == -1)
			{
				//std::cout<< "Process file failed"<<std::endl;
				return -1;
			}

			
			

		}else if(fileType == "binary")
		{
			
			std::ifstream binFile(argv[1]);
			//std::ifstream binFile(argv[2]);
			if(readBinaryFile(binFile) == -1)
			{
				//std::cout<<"BIN ERROR";
					return -1;
			}
			
		}else
		{
			return -1;
		}


		if(processHeaderData() == -1)
			{
				//std::cout << "Process Header Failed" << std::endl;
				return -1;
			}

		if(validatePixels() == -1)
			{
				//std::cout << "Bad Pixels" << std::endl;
				return -1;
			}
			findMin();
			findAverage();
			findMax();
		
			if(rescale() == -1)
			{
				//std::cout << "Failed to rescale" << std::endl;
				return -1;
			}
		
		std::string fullOutFileName = argv[2];
		std::string extension = getExtension(fullOutFileName);

		if(extension == ".pgma")
		{
			std::ofstream outFile(argv[2]);
				if(writeAsciiFile(outFile) == -1)
				{
					//std::cout<<"outFile failed" <<std::endl;
					return -1;
				}
		}else
		{
			std::ofstream outFile(argv[2], std::ios::binary | std::ios::out);
			if(writeBinaryFile(outFile) == -1)
			{
				//std::cout <<"outfile failed" << std::endl;
				return -1;
			}
		}
		



		
		
	return 0;


	}