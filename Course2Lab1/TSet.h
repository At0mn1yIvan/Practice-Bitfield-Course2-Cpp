#include "TBitField.h"
#pragma once
class TSet
{
private:
	TBitField BitField;
	int MaxPower;
public:
	TSet(int mp) : BitField(mp), MaxPower(mp) {};
	TSet(TSet& set) : BitField(set.BitField), MaxPower(set.MaxPower) {};
	TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength()) {};
	operator TBitField();
	int GetMaxPower() const;
	int IsMember(int el) const;
	void InsElem(int el);
	void DelElem(int el);
	TSet& operator=(const TSet& st);
	int operator==(const TSet& st) const;
	int operator!=(const TSet& st) const;
	TSet operator+(const TSet& st) const;
	TSet operator+(const int el) const;
	TSet operator-(const int el) const;
	TSet operator*(const TSet& st) const;
	TSet operator~();
	friend std::ostream& operator<<(std::ostream& out, const TSet& st);
};

