// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) : BitLen(len)
{
	if (len>=0)
	{
	MemLen=(len+15)>>4;
	pMem=new TELEM[MemLen];
	if (pMem!=NULL)
		for (int i=0; i<MemLen; i++)
			pMem[i]=0;
	}
	else
	{
		throw 1;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen=bf.MemLen;
	BitLen=bf.BitLen;
	pMem=new TELEM[MemLen];
	if (pMem!=NULL)
	for (int i=0;i<MemLen;i++)
	{
		pMem[i]=bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete pMem;
	pMem=NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if(n>=0)
	{
	return n>>4;
	}
	else 
		throw 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1<<(n&15);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n>-1) && (n<BitLen))
		pMem[GetMemIndex(n)]|=GetMemMask(n);
	else throw 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n>-1) && (n<BitLen))
		pMem[GetMemIndex(n)]&=~GetMemMask(n);
	else throw 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n>-1) && (n<BitLen))
		if(pMem[GetMemIndex(n)]&GetMemMask(n))
		{
			return 1;
		}
		else 
			return 0;
	else 
		throw 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen!=bf.BitLen)
	{
		MemLen=bf.MemLen;
		BitLen=bf.BitLen; 
		delete [] pMem;
		pMem=new TELEM[MemLen];
	}
	for (int i=0;i<MemLen;i++)
	{
		pMem[i]=bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  int res=1;
  if (BitLen!=bf.BitLen)
	  res=0;
  else
	  for (int i=0;i<MemLen;i++)
		  if (pMem[i]!=bf.pMem[i])
		  {
			  res=0;
			  break;
		  }
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
 int res=0;
  if (BitLen!=bf.BitLen)
	  res=1;
  else
	  for (int i=0;i<MemLen;i++)
		  if (pMem[i]!=bf.pMem[i])
		  {
			  res=1;
			  break;
		  }
  return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len;
	TBitField temp(0);
	if(BitLen>=bf.BitLen)
	{
		len=bf.MemLen;
		temp=*this;
	}
	else
	{
		len=MemLen;
		temp=bf;
	}
	for(int i=0;i<len;i++)
	{
		temp.pMem[i]=pMem[i]|bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len;
	TBitField temp(0);
	if(BitLen>=bf.BitLen)
	{
		len=bf.MemLen;
		temp=*this;
	}
	else
	{
		len=MemLen;
		temp=bf;
	}
	for(int i=0;i<len;i++)
	{
		temp.pMem[i]=pMem[i]&bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp=(*this);
	for (int i=0;i<BitLen;i++)
		if(temp.GetBit(i)) 
			temp.ClrBit(i);
		else 
			temp.SetBit(i);
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i=0;
	char ch;
	do 
	{
		istr>>ch;
	}
	while  (ch!=' ');
	while (1)
	{
		istr>>ch;
		if (ch=='0')
			bf.ClrBit(i++);
		else
			if (ch=='1')
				bf.SetBit(i++);
			else
				break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len=bf.GetLength();
	for (int i=0;i<len;i++)
		if (bf.GetBit(i))
			ostr<<'1';
		else
			ostr<<'0';
	return ostr;
}
