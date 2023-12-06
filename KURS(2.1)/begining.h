#ifndef begining_h
#define begining_h
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h> 
#include <stdio.h>  
#include <share.h>  
#include <Windows.h>
#include <ctype.h>
#include <stdlib.h>
using namespace std;
// ��������� ��� ������
struct zags
{
	char date[11];
	int numberofzags;
	bool sost;
	char FIOh[50];
	char bh[11];
	char pasph[12];
	char FIOw[50];
	char bw[11];
	char paspw[12];

public:
	void printStr();//������� ��� ��������� ������ � �������
	friend istream& operator>>(istream&, zags&);// ���������� ������� ����� � ������
	friend ostream& operator<<(ostream&, const zags&);
	//char* getName() { return name; }// ������� ��� ������ �����
	//double getCost() { return avrcost; }
	//bool operator<(const kino& k1) { return avrcost < k1.avrcost; }// ���������� �������� ��������� (��� ������ ����������)
//	bool operator<(const int i) { return avrcost < double(i); }
	zags& operator=(const zags& k)//���������� ��������� ������������ (�� ������ ������)
	{
		for (int i = 0; i < strlen(date); i++)
		{
			date[i] = k.date[i];
		}
		for (int j = 0; j < strlen(FIOh); j++)
		{
			FIOh[j] = k.FIOh[j];
		}
		for (int j = 0; j < strlen(bh); j++)
		{
			bh[j] = k.bh[j];
		}
		for (int j = 0; j < strlen(pasph); j++)
		{
			pasph[j] = k.pasph[j];
		}
		for (int j = 0; j < strlen(FIOw); j++)
		{
			FIOw[j] = k.FIOw[j];
		}
		for (int j = 0; j < strlen(bw); j++)
		{
			bw[j] = k.bw[j];
		}
		for (int j = 0; j < strlen(paspw); j++)
		{
			paspw[j] = k.paspw[j];
		}
		//avrcost = k.avrcost;
		//zalperseats = k.zalperseats;
		numberofzags = k.numberofzags;
		sost = k.sost;
		return *this;
	}
}zg;//��������� � ���������
const int ZAGS_SIZE = sizeof(zags);//������ ����� ���������
int masSize = 0;//������ �������(��� ����������)
const char tableHead[][230] = {
	"|                                             �����                                               |",
	"|-------------------------------------------------------------------------------------------------|",
	"||����     | ����� |  ���  | ���� ����.| ����� �������� |  ���   | ���� ����.  |  ����� ��������  |",
	"||�����    | ����� |������ |  ������   |    ������      | �������|  �������    |   �������        |",
	"||(�������)|       |(����) |  (����)   |    (����)      | (����) |  (����)     |    (����)        |",
	"|-------------------------------------------------------------------------------------------------|",
};//����� ������� ��� ������
ifstream finb, finr;//������������ ��������� ������
ofstream foutb, foutr;
fstream fiob, fior;
void filtr(char* c)//������� ��� ������� ����
{
	int i;
	int sLeft = 0;
	int sRight = strlen(c) - 1;
	while (c[sLeft] == ' ') sLeft++;
	while (c[sRight] == ' ') sRight--;
	for (i = sLeft; i <= sRight; i++) c[i - sLeft] = c[i];
	c[i - sLeft] = '\0';
}

istream& operator>>(istream& in, zags& kin)
{
	char tempar[100];
	in >> kin.sost;
	in.getline(kin.date, 11); filtr(kin.date); in.clear();
	in >> kin.numberofzags;
	in.getline(kin.FIOh, 50); filtr(kin.FIOh); in.clear();
	in.getline(kin.bh, 11); filtr(kin.bh); in.clear();
	in.getline(kin.pasph, 12); filtr(kin.pasph); in.clear();
	in.getline(kin.FIOw, 50); filtr(kin.FIOh); in.clear();
	in.getline(kin.bw, 11); filtr(kin.bh); in.clear();
	in.getline(kin.paspw, 12); filtr(kin.pasph); in.clear();
	in.getline(tempar, 200);
	return in;
}
ostream& operator<<(ostream& out, const zags& kin)
{
	out.setf(ios::left);
	out << setw(11) << kin.date << setw(8) << kin.numberofzags << setw(8) << kin.FIOh << setw(8) << kin.bh << setw(8) << kin.pasph 
		<< setw(8) << kin.FIOw << setw(8) << kin.bw << setw(8) << kin.paspw << "\n";
	out.unsetf(ios::left);
	return out;
}
#endif