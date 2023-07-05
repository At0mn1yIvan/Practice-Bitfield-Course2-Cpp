#include "TSet.h"

TSet::operator TBitField()
{
	return TBitField(BitField);
}

int TSet::GetMaxPower() const
{
	return MaxPower;
}

int TSet::IsMember(int el) const
{
	return BitField.GetBit(el);
}

void TSet::InsElem(int el)
{
	BitField.SetBit(el);
}

void TSet::DelElem(int el)
{
	BitField.ClrBit(el);
}

TSet& TSet::operator=(const TSet& st)
{
	MaxPower = st.MaxPower;
	BitField = st.BitField;
	return *this;
}

int TSet::operator==(const TSet& st) const
{
	return BitField == st.BitField;
}

int TSet::operator!=(const TSet& st) const
{
	return BitField != st.BitField;
}

TSet TSet::operator+(const TSet& st) const
{
	return TSet(BitField | st.BitField);
}

TSet TSet::operator+(const int el) const
{
	TSet temp(BitField);
	temp.InsElem(el);
	return temp;
}

TSet TSet::operator-(const int el) const
{
	TSet temp(BitField);
	temp.DelElem(el);
	return temp;
}

TSet TSet::operator*(const TSet& st) const
{
	return TSet(BitField & st.BitField);
}

TSet TSet::operator~()
{
	return TSet(~BitField);
}

std::ostream& operator<<(std::ostream& out, const TSet& st)
{
	out << "{";
	int n = st.GetMaxPower();
	for (int i = 0; i < n; i++) {
		if (st.IsMember(i))
			out << i << (i < n) ? ", " : "";
	}
	out << "}";
	return out;
}
