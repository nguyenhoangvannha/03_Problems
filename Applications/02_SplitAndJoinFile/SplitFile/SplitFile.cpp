#include "Split.h"
std::string nhapLink()
{
	std::string link;
	std::cout << "Nhap link file can cat: ";
	std::cin >> link;
	return link;
}
int main()
{
	Split file;
	file.setNumber(4);
	file.cutFile("tdb.pdf");
	return 0;
}