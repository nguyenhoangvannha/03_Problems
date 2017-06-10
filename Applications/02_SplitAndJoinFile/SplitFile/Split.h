#pragma once
#include "string"
#include "fstream"
#include "iostream"

class Split
{
private:
	std::string link_;
	int number_ = 0;
	long size_in_ = 0; //byte
public:
	void setLink(std::string link);
	//std::string getLink();
	void setNumber(int number);
	//int getNumber();
	void setSizeIn(std::string link);
	long getSizeOut();
	std::string createFileOutName(std::string link, int i);
	bool cutFile(std::string link);
};