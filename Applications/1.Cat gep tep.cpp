#define _CRT_SECURE_NO_WARNINGS
#include "iostream"
#include "fstream"
#include "string"
using namespace std;
void main();
void linkf(char link[])
{
	int i = 0;
	char n = ' ';
	//Lấy link của tệp góc
	cout << endl << "Nhap link file (them dau \\) : ";
	while (n != '\n')
	{
		n = getchar();
		link[i] = n;
		i++;
	}
	link[i - 1] = '\0';
	fstream f;
	f.open(link, ios_base::in | ios_base::binary);
	if (!f.is_open())
	{
		cout << endl << "Ban nhap link sai,file khong ton tai!";
		main();
	}
}
long sizef(char linkf[])
{
	fstream f;
	f.open(linkf, ios_base::in | ios_base::binary);
	f.seekg(0, ios::end);
	long sizef = f.tellg();
	f.close();
	return sizef;
}
void nhap( int &n)
{
	cout << endl << "So file ban muon tao ra tu file goc: ";
	cin >> n;
}
void tao_link_f_nho_thu_i(char linkfgoc[], char linkfnhothu_i[],int i)
{
	strcat(linkfnhothu_i, linkfgoc);
	strcat(linkfnhothu_i, ".");
	char duoi[100] = "";
	_itoa(i, duoi, 10);
	strcat(linkfnhothu_i, duoi);
}
void Cat()
{
	fstream fgoc , fnho;
	int sofnho;
	long sizefgoc, sizefnho;
	char linkfgoc[10000] = "";
	//khai bao
	linkf(linkfgoc);
	sizefgoc = sizef(linkfgoc);
	do
	{
		nhap(sofnho);
	}
	while (sofnho > sizefgoc);
	//lay link file can cat
	sizefnho = sizefgoc / (sofnho - 1);
	//Tinh size f goc va size file nho sau khi cat
	//Tao ra cac file nhỏ trống
	fgoc.open(linkfgoc, ios_base::in | ios_base::binary);
	int i;
	char *s1 = new char[sizefnho];
	for (i = 1; i < sofnho; i++)
	{
		char linkfnho[1000] = "";
		tao_link_f_nho_thu_i(linkfgoc, linkfnho, i);
		fnho.open(linkfnho, ios_base::out | ios_base::binary);
		fgoc.read(s1, sizefnho);
		fnho.write(s1, sizefnho);
		fnho.close();
	}
	delete[]s1;
	char linkfnho[1000] = "";
	tao_link_f_nho_thu_i(linkfgoc, linkfnho, i);
	fnho.open(linkfnho, ios_base::out | ios_base::binary);
	long sizefnhoconlai = sizefgoc - (sizefnho * (i - 1));
	char *s2 = new char[sizefnhoconlai];
	fgoc.read(s2, sizefnhoconlai);
	fnho.write(s2, sizefnhoconlai);
	fnho.close();
	fgoc.close();
	delete[]s2;
}
// Xong phần cắt tệp >> làm gép tệp
void tao_link_f_KQ(char link_f_KQ[10000], char linkfnguon[])
{
	//hàm này có mục đích là tạo ra link tệp gép lại nên không cần quan tâm
	// vd tệp nguồn (linkfnguon) là f:\file.txt.1 
	//thì tệp sau khi gép lại (link_f_KQ) có link l f:\new_file.txt
	char temp[1] = "";
	strcpy(link_f_KQ, temp);
	int i = strlen(linkfnguon) - 1;
	int j = 0;
	while (linkfnguon[i] != '\\') i--;
	char dau[1000] = "", cuoi[50] = "";
	for (int m = (i + 1); m < strlen(linkfnguon); m++)
	{
		cuoi[j] = linkfnguon[m];
		j++;
	}
	//asd.pdf.1234
	int k = strlen(cuoi) - 1;
	while (cuoi[k] != '.') k--;
	cuoi[k] = '\0';
	for (int k = 0; k <= i; k++)
	{
		dau[k] = linkfnguon[k];
	}
	strcat(dau, "new_");
	strcat(dau, cuoi);
	strcpy(link_f_KQ, dau);
}
void tao_link_f_nguon_thu_i(char linkfnguon[], int &i)
{
	int leng = strlen(linkfnguon);
	char duoi[100] = "";
	_itoa(i, duoi, 10);
	int j = leng - 1;
	while (linkfnguon[j] != '.') j--;
	linkfnguon[j + 1] = '\0';
	strcat(linkfnguon, duoi);
	i++;
}
void GepTep()
{
	int i = 1;
	int sotepcon = 0;
	long sizetepcon = 0;
	fstream tepgep, tepcon;
	char linkfnguon[1000] = "";
	char link_f_KQ[1000] = "";
	linkf(linkfnguon);
	tao_link_f_KQ(link_f_KQ, linkfnguon);
	tepcon.open(linkfnguon, ios_base::in | ios_base::binary);
	do
	{
		sotepcon++;
		tepcon.close();
		tao_link_f_nguon_thu_i(linkfnguon, i);
		sizetepcon = sizef(linkfnguon);
		tepcon.open(linkfnguon, ios_base::in | ios_base::binary);
		if (!tepcon.is_open()) continue;
		tepgep.open(link_f_KQ, ios_base::app | ios_base::binary);
		char *s = new char[sizetepcon];
		tepcon.read(s, sizetepcon);
		tepgep.write(s, sizetepcon);
		tepgep.close();
	} while (tepcon.is_open());
	//Xong gep tep >> xoa tep con theo yeu cau
	int chon = 0;
	do
	{
		cout << endl << "Ban co muon xoa cac file goc khong nhan 0 khong xoa nhan 1 de xoa: ";
		cin >> chon;
	} while (chon > 1 && chon < 0);
	if (chon == 1)
	{
		for (int i = 1; i <= sotepcon; i++)
		{
			tao_link_f_nguon_thu_i(linkfnguon, i);
			i--;
			remove(linkfnguon);
		}
	}
}
void main()
{
	int chon = 0;
menu:
	cout << endl << "-------------menu-------------" << endl << "1.Cat tep"
		<< endl << "2.Gep tep" << endl << "3.Thoat" << endl << "----------chon: ";
	cin >> chon;
	cin.ignore(1);
	switch (chon)
	{
	case 1: Cat(); break;
	case 2: GepTep(); break;
	case 3: exit(0);
	default: cout << endl << "Ban chon sai moi chon lai";
		goto menu;
	}
	goto menu;
}
//fb.co/nguyenhoangvannha