#include "TBitField.h"

int TBitField::GetMemIndex(const int n) const
{
	return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const
{
	return 1 << (n & 31); // n % 32 то же самое  
												
}

TBitField::TBitField(int len) : BitLen(len){
	if (BitLen < 1) throw BitLen;
	if (BitLen < 32) {
		MemLen = (BitLen + 31) >> 5;
	}
	else 
		MemLen = ((len - 1) >> 5) + 1;
	pMem = new TELEM[MemLen];
	if (pMem != nullptr) {
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	
}

TBitField::TBitField(const TBitField& bf)
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	if (pMem != nullptr) {
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetLength() const
{
	return BitLen;
}

void TBitField::SetBit(const int n)
{
	if (n >= BitLen || n < 0)
		throw n;
	if (n < BitLen && n > -1)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
	if (n >= BitLen || n < 0)
		throw n;
	if (n < BitLen && n > -1)
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
	if (n >= BitLen || n < 0)
		throw n;
	if (n < BitLen && n > -1)
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	return 0;
}

int TBitField::operator==(const TBitField& bf) const
{
	if (BitLen != bf.BitLen)
		return false;
	
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return false;
	
	return true;

	
}

int TBitField::operator!=(const TBitField& bf) const
{
	return !(this == &bf);
}

TBitField& TBitField::operator=(const TBitField& bf)
{
	if (this == &bf)
		return *this;
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
		MemLen = bf.MemLen;
	if (pMem != nullptr)
		delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

TBitField& TBitField::operator|(const TBitField& bf) const
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField& TBitField::operator&(const TBitField& bf) const
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField& TBitField::operator~()
{
	int B = BitLen;
	TBitField temp(B);
	
	for (size_t i = 0; i < MemLen; i++){
		temp.pMem[i] = ~pMem[i];
	}
	return temp;
}

std::istream& operator>>(std::istream& in, TBitField& bf)
{
	for (int i = 0; i < bf.BitLen; i++) {
		int b;
		in >> b;
		if (b == 1)
			bf.SetBit(i);
	}
	return in;

}

std::ostream& operator<<(std::ostream& out, const TBitField& bf)
{
	int len = bf.GetLength();
	for (size_t i = 0; i < len; i++) {
		out << (bf.GetBit(i) > 0 ? 1 : 0);
	}
	return out;
}
