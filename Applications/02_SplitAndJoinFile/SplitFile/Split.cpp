#define _CRT_SECURE_NO_WARNINGS
#include "Split.h"
void Split::setLink(std::string link)
{
	link_ = link;
}
//std::string Split::getLink()
//{
//	return link_;
//}
void Split::setNumber(int number)
{
	number_ = number;
}
//int Split::getNumber()
//{
//	return number_;
//}
void Split::setSizeIn(std::string link)
{
	std::fstream f;
	f.open(link, std::ios_base::in | std::ios_base::binary);
	f.seekg(0, std::ios::end);
	size_in_ = f.tellg();
	f.close();
}
long Split::getSizeOut()
{
	return (size_in_ / number_);
}
std::string Split::createFileOutName(std::string link, int i)
{
	char c;
	_itoa(i, &c, 10);
	return link + c;
}
bool Split::cutFile(std::string link)
{
	setLink(link);
	std::fstream f,g;
	f.open(link, std::ios_base::in | std::ios_base::binary);
	//da co so luong file con
	setSizeIn(link);
	std::cout << "Size file: " << size_in_ << std::endl;
	std::cout << "Size file nho: " << getSizeOut() << std::endl;
	char * c = new char[getSizeOut()];
	for (int i = 1; i < number_; i++)
	{
		g.open(createFileOutName(link, i), std::ios_base::out | std::ios_base::binary);
		f.read(c, getSizeOut());
		g.write(c, getSizeOut());
		std::cout << "File member " << i << " size= " << g.tellg() << std::endl;
		g.close();
	}
	f.close();
	return true;
}
