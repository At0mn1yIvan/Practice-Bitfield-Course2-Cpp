#pragma once
#include <iostream>

typedef unsigned int TELEM;
class TBitField
{
private:
	TELEM* pMem;
	int MemLen;// длина массива uint (по 32 бита)
	int BitLen; // длина битов
	int GetMemIndex(const int n) const;
	TELEM GetMemMask(const int n) const;
public:
	TBitField(int len);
	TBitField(const TBitField& bf);
	~TBitField();
	int GetLength() const;
	void SetBit(const int n);
	void ClrBit(const int n);
	int GetBit(const int n) const;
	int operator==(const TBitField& bf) const;
	int operator!=(const TBitField& bf) const;
	TBitField& operator=(const TBitField& bf);
	TBitField& operator|(const TBitField& bf) const;
	TBitField& operator&(const TBitField& bf) const;
	TBitField& operator~();
	friend std::istream& operator>>(std::istream& in, TBitField& bf) ;
	friend std::ostream& operator<<(std::ostream& out,const TBitField& bf);

};

