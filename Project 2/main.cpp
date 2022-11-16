#ifndef OURTYPE_INCLUDED
#define OURTYPE_INCLUDED

	struct OurType
{
	explicit OurType(int v = 0) : m_value(v) { m_count++; }
	OurType(const OurType& other) : m_value(other.m_value)
	{
		m_count++; m_asstcopycount++;
	}
	~OurType() { m_count--; }
	OurType& operator=(const OurType& rhs)
	{
		m_value = rhs.m_value; m_asstcopycount++; return *this;
	}

	int m_value;
	static int m_count;
	static int m_asstcopycount;
};

inline
bool operator==(const OurType & lhs, const OurType & rhs)
{
	return lhs.m_value == rhs.m_value;
}

inline
bool operator<(const OurType & lhs, const OurType & rhs)
{
	return lhs.m_value < rhs.m_value;
}

inline
bool operator!=(const OurType & lhs, const OurType & rhs)
{
	return !(lhs == rhs);
}

inline
bool operator<=(const OurType & lhs, const OurType & rhs)
{
	return !(rhs < lhs);
}

inline
bool operator>=(const OurType & lhs, const OurType & rhs)
{
	return !(lhs < rhs);
}

inline
bool operator>(const OurType & lhs, const OurType & rhs)
{
	return rhs < lhs;
}

inline
bool operator==(const OurType & lhs, int rhs)
{
	return lhs.m_value == rhs;
}

inline
bool operator!=(const OurType & lhs, int rhs)
{
	return !(lhs == rhs);
}

#include <iostream>

inline
std::ostream& operator<<(std::ostream & lhs, const OurType & rhs)
{
	return lhs << rhs.m_value;
}

#endif

#include "Sequence.h"
#include <iostream>
#include <cstdlib>
#include <type_traits>
#include <cassert>

using namespace std;

int OurType::m_count = 0;
int OurType::m_asstcopycount = 0;

inline int itemcount()
{
	return OurType::m_count;
}

inline int nasstcopys()
{
	return OurType::m_asstcopycount;
}

ItemType SOMEVAL = ItemType(123);
ItemType DEFAULT = ItemType(0);
ItemType ARRAY[6] = {
	ItemType(10), ItemType(20), ItemType(30),
	ItemType(40), ItemType(50), ItemType(60),
};

void testone(int n)
{
	Sequence s;
	switch (n)
	{
	default: {
		cout << "Bad argument" << endl;
	} break; case  1: {
		assert((is_same<decltype(&Sequence::empty), bool (Sequence::*)() const>::value));
	} break; case  2: {
		assert((is_same<decltype(&Sequence::size), int (Sequence::*)() const>::value));
	} break; case  3: {
		assert((is_same<decltype(&Sequence::get), bool (Sequence::*)(int, ItemType&) const>::value));
	} break; case  4: {
		assert((is_same<decltype(&Sequence::find), int (Sequence::*)(const ItemType&) const>::value));
	} break; case  5: {
		assert(s.empty());
	} break; case  6: {
		assert(s.size() == 0);
	} break; case  7: {
		assert(!s.erase(0) && s.size() == 0);
	} break; case  8: {
		assert(s.remove(DEFAULT) == 0 && s.size() == 0);
	} break; case  9: {
		ItemType x = SOMEVAL;
		assert(!s.get(0, x));
	} break; case 10: {
		ItemType x = SOMEVAL;
		s.get(0, x);
		assert(x == SOMEVAL);
	} break; case 11: {
		assert(!s.set(0, SOMEVAL) && s.size() == 0);
	} break; case 12: {
		assert(s.find(DEFAULT) == -1);
	} break; case 13: {
		assert(s.insert(0, SOMEVAL) == 0);
	} break; case 14: {
		s.insert(0, SOMEVAL);
		assert(!s.empty());
	} break; case 15: {
		s.insert(0, SOMEVAL);
		assert(s.size() == 1);
	} break; case 16: {
		s.insert(0, SOMEVAL);
		assert(s.find(SOMEVAL) == 0);
	} break; case 17: {
		s.insert(0, SOMEVAL);
		ItemType x = DEFAULT;
		assert(s.get(0, x));
	} break; case 18: {
		s.insert(0, SOMEVAL);
		ItemType x = DEFAULT;
		s.get(0, x);
		assert(x == SOMEVAL);
	} break; case 19: {
		s.insert(0, SOMEVAL);
		assert(s.set(0, DEFAULT));
	} break; case 20: {
		s.insert(0, SOMEVAL);
		s.set(0, DEFAULT);
		assert(s.size() == 1);
		ItemType x = SOMEVAL;
		s.get(0, x);
		assert(x == DEFAULT);
	} break; case 21: {
		s.insert(0, DEFAULT);
		s.set(0, SOMEVAL);
		assert(s.size() == 1);
		ItemType x = DEFAULT;
		s.get(0, x);
		assert(x == SOMEVAL);
	} break; case 22: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		assert(!s.empty() && s.size() == 2);
	} break; case 23: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		ItemType x = SOMEVAL;
		s.get(0, x);
		assert(x == ARRAY[0]);
	} break; case 24: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		ItemType x = SOMEVAL;
		s.get(1, x);
		assert(x == ARRAY[1]);
	} break; case 25: {
		s.insert(0, ARRAY[0]);
		s.insert(0, ARRAY[1]);
		assert(s.size() == 2);
	} break; case 26: {
		s.insert(0, ARRAY[0]);
		s.insert(0, ARRAY[1]);
		ItemType x = SOMEVAL;
		s.get(0, x);
		assert(x == ARRAY[1]);
	} break; case 27: {
		s.insert(0, ARRAY[0]);
		s.insert(0, ARRAY[1]);
		ItemType x = SOMEVAL;
		s.get(1, x);
		assert(x == ARRAY[0]);
	} break; case 28: {
		s.insert(0, ARRAY[3]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[0]);
		s.insert(0, ARRAY[4]);
		s.insert(2, ARRAY[2]);
		assert(s.size() == 5);
	} break; case 29: {
		s.insert(0, ARRAY[3]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[0]);
		s.insert(0, ARRAY[4]);
		s.insert(2, ARRAY[2]);
		for (size_t k = 0; k < 5; k++)
		{
			ItemType x = SOMEVAL;
			s.get(k, x);
			assert(x == ARRAY[5 - 1 - k]);
		}
	} break; case 30: {
		s.insert(0, ARRAY[3]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[0]);
		s.insert(3, ARRAY[4]);
		s.insert(4, ARRAY[2]);
		for (size_t k = 0; k < 5; k++)
			s.set(k, ARRAY[k]);
		assert(s.size() == 5);
		for (size_t k = 0; k < 5; k++)
		{
			ItemType x = SOMEVAL;
			s.get(k, x);
			assert(x == ARRAY[k]);
		}
	} break; case 31: {
		assert(s.insert(SOMEVAL) == 0);
	} break; case 32: {
		s.insert(SOMEVAL);
		assert(!s.empty());
	} break; case 33: {
		s.insert(SOMEVAL);
		assert(s.size() == 1);
	} break; case 34: {
		s.insert(SOMEVAL);
		assert(s.find(SOMEVAL) == 0);
	} break; case 35: {
		s.insert(ARRAY[0]);
		s.insert(ARRAY[1]);
		assert(!s.empty() && s.size() == 2);
	} break; case 36: {
		s.insert(SOMEVAL);
		ItemType x = DEFAULT;
		assert(s.get(0, x));
	} break; case 37: {
		s.insert(SOMEVAL);
		ItemType x = DEFAULT;
		s.get(0, x);
		assert(x == SOMEVAL);
	} break; case 38: {
		s.insert(ARRAY[0]);
		s.insert(ARRAY[1]);
		ItemType x = SOMEVAL;
		s.get(0, x);
		assert(x == ARRAY[0]);
	} break; case 39: {
		s.insert(ARRAY[0]);
		s.insert(ARRAY[1]);
		ItemType x = SOMEVAL;
		s.get(1, x);
		assert(x == ARRAY[1]);
	} break; case 40: {
		s.insert(ARRAY[1]);
		s.insert(ARRAY[0]);
		ItemType x = SOMEVAL;
		s.get(0, x);
		assert(x == ARRAY[0]);
	} break; case 41: {
		s.insert(ARRAY[1]);
		s.insert(ARRAY[0]);
		ItemType x = SOMEVAL;
		s.get(1, x);
		assert(x == ARRAY[1]);
	} break; case 42: {
		assert(s.insert(ARRAY[3]) == 0);
		assert(s.insert(ARRAY[1]) == 0);
		assert(s.insert(ARRAY[0]) == 0);
		assert(s.insert(ARRAY[4]) == 3);
		assert(s.insert(ARRAY[2]) == 2);
		assert(s.size() == 5);
	} break; case 43: {
		s.insert(ARRAY[3]);
		s.insert(ARRAY[1]);
		s.insert(ARRAY[0]);
		s.insert(ARRAY[4]);
		s.insert(ARRAY[2]);
		for (size_t k = 0; k < 5; k++)
		{
			ItemType x = SOMEVAL;
			s.get(k, x);
			assert(x == ARRAY[k]);
		}
	} break; case 44: {
		assert(s.insert(ARRAY[2]) == 0);
		assert(s.insert(ARRAY[1]) == 0);
		assert(s.insert(ARRAY[0]) == 0);
		assert(s.insert(ARRAY[1]) == 1);
		assert(s.insert(ARRAY[1]) == 1);
		assert(s.size() == 5);
		ItemType x = SOMEVAL;
		s.get(0, x);
		assert(x == ARRAY[0]);
		s.get(4, x);
		assert(x == ARRAY[2]);
		for (size_t k = 1; k < 4; k++)
		{
			x = SOMEVAL;
			s.get(k, x);
			assert(x == ARRAY[1]);
		}
	} break; case 45: {
		assert(s.insert(1, SOMEVAL) == -1 && s.size() == 0);
	} break; case 46: {
		assert(s.insert(-1, SOMEVAL) == -1 && s.size() == 0);
	} break; case 47: {
		s.insert(0, SOMEVAL);
		assert(s.insert(2, SOMEVAL) == -1 && s.size() == 1);
	} break; case 48: {
		s.insert(0, SOMEVAL);
		assert(!s.erase(1) && s.size() == 1);
	} break; case 49: {
		s.insert(0, SOMEVAL);
		assert(s.erase(0) && s.size() == 0);
	} break; case 50: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[3]);
		s.insert(4, ARRAY[4]);
		assert(s.erase(4) && s.size() == 4);
	} break; case 51: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[3]);
		s.insert(4, ARRAY[4]);
		s.erase(4);
		ItemType x;
		s.get(3, x);
		assert(x == ARRAY[3]);
	} break; case 52: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[3]);
		s.insert(4, ARRAY[4]);
		assert(s.erase(1) && s.size() == 4);
	} break; case 53: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[3]);
		s.insert(4, ARRAY[4]);
		s.erase(1);
		ItemType x;
		s.get(0, x);
		assert(x == ARRAY[0]);
		for (size_t k = 1; k < 4; k++)
		{
			s.get(k, x);
			assert(x == ARRAY[k + 1]);
		}
	} break; case 54: {
		s.insert(0, SOMEVAL);
		assert(s.remove(SOMEVAL) == 1);
	} break; case 55: {
		s.insert(0, SOMEVAL);
		s.remove(SOMEVAL);
		assert(s.size() == 0);
	} break; case 56: {
		s.insert(0, ARRAY[0]);
		assert(s.remove(ARRAY[1]) == 0);
	} break; case 57: {
		s.insert(0, ARRAY[0]);
		s.remove(ARRAY[1]);
		assert(s.size() == 1);
	} break; case 58: {
		s.insert(0, ARRAY[4]);
		s.insert(1, ARRAY[3]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[1]);
		s.insert(4, ARRAY[0]);
		s.remove(ARRAY[2]);
		ItemType x;
		for (size_t k = 0; k < 2; k++)
		{
			s.get(k, x);
			assert(x == ARRAY[5 - 1 - k]);
		}
		for (size_t k = 2; k < 4; k++)
		{
			s.get(k, x);
			assert(x == ARRAY[5 - 2 - k]);
		}
	} break; case 59: {
		s.insert(0, ARRAY[4]);
		s.insert(1, ARRAY[2]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[4]);
		s.insert(4, ARRAY[2]);
		s.insert(5, ARRAY[2]);
		assert(s.remove(ARRAY[2]) == 4);
	} break; case 60: {
		s.insert(0, ARRAY[4]);
		s.insert(1, ARRAY[2]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[4]);
		s.insert(4, ARRAY[2]);
		s.insert(5, ARRAY[2]);
		s.remove(ARRAY[2]);
		assert(s.size() == 2);
	} break; case 61: {
		s.insert(0, ARRAY[4]);
		s.insert(1, ARRAY[2]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[4]);
		s.insert(4, ARRAY[2]);
		s.insert(5, ARRAY[2]);
		s.remove(ARRAY[2]);
		ItemType x;
		for (size_t k = 0; k < 2; k++)
		{
			x = ARRAY[0];
			s.get(k, x);
			assert(x == ARRAY[4]);
		}
	} break; case 62: {
		s.insert(0, ARRAY[2]);
		s.insert(1, ARRAY[2]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[2]);
		s.insert(4, ARRAY[2]);
		s.remove(ARRAY[2]);
		assert(s.size() == 0);
	} break; case 63: {
		s.insert(0, SOMEVAL);
		s.insert(1, SOMEVAL);
		s.insert(2, SOMEVAL);
		ItemType x;
		assert(!s.get(-1, x));
	} break; case 64: {
		s.insert(0, SOMEVAL);
		s.insert(1, SOMEVAL);
		s.insert(2, SOMEVAL);
		ItemType x = ARRAY[1];
		s.get(-1, x);
		assert(x == ARRAY[1]);
	} break; case 65: {
		s.insert(0, SOMEVAL);
		s.insert(1, SOMEVAL);
		s.insert(2, SOMEVAL);
		ItemType x;
		assert(!s.get(3, x));
	} break; case 66: {
		s.insert(0, SOMEVAL);
		s.insert(1, SOMEVAL);
		s.insert(2, SOMEVAL);
		ItemType x = ARRAY[1];
		s.get(3, x);
		assert(x == ARRAY[1]);
	} break; case 67: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		assert(!s.set(-1, ARRAY[3]));
	} break; case 68: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		s.set(-1, ARRAY[3]);
		assert(s.size() == 3);
		for (size_t k = 0; k < 3; k++)
		{
			ItemType x = SOMEVAL;
			assert(s.get(k, x) && x == ARRAY[k]);
		}
	} break; case 69: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		assert(!s.set(3, ARRAY[3]));
	} break; case 70: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		s.set(-1, ARRAY[3]);
		assert(s.size() == 3);
		for (size_t k = 0; k < 3; k++)
		{
			ItemType x = SOMEVAL;
			assert(s.get(k, x) && x == ARRAY[k]);
		}
	} break; case 71: {
		s.insert(SOMEVAL);
		assert(s.find(DEFAULT) == -1);
	} break; case 72: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[4]);
		assert(s.find(ARRAY[4]) == 1);
	} break; case 73: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[4]);
		assert(s.find(ARRAY[3]) == -1);
	} break; case 74: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		{
			Sequence s2;
			s2.insert(0, ARRAY[3]);
			s2.insert(1, ARRAY[4]);
			s.swap(s2);
			assert(s.size() == 2 && s2.size() == 3);
		}
	} break; case 75: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		{
			Sequence s2;
			s2.insert(0, ARRAY[3]);
			s2.insert(1, ARRAY[4]);
			s.swap(s2);
			ItemType x;
			assert(s.get(0, x) && x == ARRAY[3]);
			assert(s.get(1, x) && x == ARRAY[4]);
			assert(s2.get(0, x) && x == ARRAY[0]);
			assert(s2.get(1, x) && x == ARRAY[1]);
			assert(s2.get(2, x) && x == ARRAY[2]);
		}
	} break; case 76: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		s.insert(3, ARRAY[3]);
		s.insert(4, ARRAY[4]);
		{
			Sequence s2;
			s2.insert(0, ARRAY[3]);
			s2.insert(1, ARRAY[4]);
			s2.insert(2, ARRAY[0]);
			int n = nasstcopys();
			s.swap(s2);
			int n2 = nasstcopys();
			assert(n2 >= n && n2 <= n + 3);  // swapping head nodes OK
		}
	} break; case 77: {
		const size_t NITEMS = 600;
		for (size_t k = 0; k < NITEMS; k++)
			assert(s.insert(SOMEVAL) != -1);
		assert(s.size() == NITEMS);
		for (size_t k = 0; k < NITEMS; k++)
		{
			ItemType x = DEFAULT;
			s.get(k, x);
			assert(x == SOMEVAL);
		}
	} break; case 78: {
		int before = itemcount();
		{
			Sequence s2;
			s2.insert(0, SOMEVAL);
			assert(itemcount() > before);
		}
		assert(itemcount() == before);
	} break; case 79: {
		{
			Sequence s2;
			s2.insert(0, ARRAY[1]);
			s2.insert(0, ARRAY[2]);
			s2.insert(2, ARRAY[3]);
			s2.insert(1, ARRAY[2]);
			s2.erase(0);
			s2.remove(ARRAY[2]);
			s2.insert(0, ARRAY[4]);
			s2.insert(s2.size(), ARRAY[4]);
			s2.remove(ARRAY[4]);
		}
		assert(true);  // no corruption so bad that destruction failed
	} break; case 80: {
		{
			Sequence s2;
			s2.insert(0, ARRAY[1]);
			s2.insert(0, ARRAY[2]);
			s2.insert(2, ARRAY[3]);
			s2.insert(1, ARRAY[2]);
			Sequence s3(s2);
			s3.insert(0, ARRAY[1]);
			s3.insert(0, ARRAY[2]);
			s3.insert(2, ARRAY[3]);
			s3.insert(1, ARRAY[2]);
			s3.erase(0);
			s3.remove(ARRAY[2]);
			s3.insert(0, ARRAY[4]);
			s3.insert(s3.size(), ARRAY[4]);
			s3.remove(ARRAY[4]);
		}
		assert(true);  // no corruption so bad that destruction failed
	} break; case 81: {
		int before = itemcount();
		{
			Sequence s2;
			s2.insert(0, ARRAY[1]);
			s2.insert(1, ARRAY[3]);
			s2.insert(2, ARRAY[2]);
			int mid = itemcount();
			Sequence s3(s2);
			assert(s3.size() == 3);
			assert(itemcount() - mid == mid - before);
		}
		assert(itemcount() == before);
	} break; case 82: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		{
			Sequence s2(s);
			s2.insert(3, ARRAY[3]);
			assert(s2.size() == s.size() + 1);
		}
	} break; case 83: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		{
			Sequence s2(s);
			s2.insert(0, ARRAY[3]);
			ItemType x;
			assert(s2.get(0, x) && x == ARRAY[3]);
			assert(s2.get(1, x) && x == ARRAY[0]);
			assert(s2.get(2, x) && x == ARRAY[1]);
			assert(s2.get(3, x) && x == ARRAY[2]);
		}
	} break; case 84: {
		s.insert(0, ARRAY[0]);
		s.insert(1, ARRAY[1]);
		s.insert(2, ARRAY[2]);
		{
			Sequence s2(s);
			s2.insert(0, ARRAY[3]);
			ItemType x;
			assert(s.get(0, x) && x == ARRAY[0]);
			assert(s.get(1, x) && x == ARRAY[1]);
			assert(s.get(2, x) && x == ARRAY[2]);
		}
	} break; case 85: {
		{
			Sequence s2;
			Sequence s3(s2);
			s2.insert(0, ARRAY[0]);
			s3.insert(0, ARRAY[1]);
			assert(s2.size() == 1 && s3.size() == 1);
			ItemType x;
			s2.get(0, x);
			assert(x == ARRAY[0]);
			s3.get(0, x);
			assert(x == ARRAY[1]);
		}
		assert(true);  // no corruption so bad that destruction failed
	} break; case 86: {
		{
			Sequence s2;
			s2.insert(0, ARRAY[1]);
			s2.insert(0, ARRAY[2]);
			s2.insert(2, ARRAY[3]);
			Sequence s3;
			s3.insert(0, ARRAY[5]);
			s3.insert(0, ARRAY[4]);
			s3 = s2;
			s3.insert(1, ARRAY[2]);
			s3.erase(0);
			s3.remove(ARRAY[2]);
			s3.insert(0, ARRAY[4]);
			s3.insert(s3.size(), ARRAY[4]);
			s3.remove(ARRAY[4]);
		}
		assert(true);  // no corruption so bad that destruction failed
	} break; case 87: {
		int before = itemcount();
		{
			Sequence s2;
			Sequence s3;
			int mid = itemcount();
			s3.insert(0, ARRAY[0]);
			s3.insert(1, ARRAY[1]);
			assert(s3.size() == 2);
			s3 = s2;
			assert(itemcount() == mid);
			s2.insert(0, ARRAY[2]);
			s3.insert(0, ARRAY[3]);
			assert(s2.size() == 1 && s3.size() == 1);
			ItemType x;
			s2.get(0, x);
			assert(x == ARRAY[2]);
			s3.get(0, x);
			assert(x == ARRAY[3]);
		}
		assert(itemcount() == before);
	} break; case 88: {
		int before = itemcount();
		{
			Sequence s2;
			Sequence s3;
			s3.insert(0, ARRAY[0]);
			s3.insert(1, ARRAY[1]);
			s2 = s3;
			s2.insert(2, ARRAY[2]);
			s3.insert(2, ARRAY[3]);
			assert(s2.size() == 3 && s3.size() == 3);
			ItemType x;
			for (size_t k = 0; k < 2; k++)
			{
				s2.get(k, x);
				assert(x == ARRAY[k]);
				s3.get(k, x);
				assert(x == ARRAY[k]);
			}
			s2.get(2, x);
			assert(x == ARRAY[2]);
			s3.get(2, x);
			assert(x == ARRAY[3]);
		}
		assert(itemcount() == before);
	} break; case 89: {
		int before = itemcount();
		{
			Sequence s2;
			s2.insert(0, ARRAY[1]);
			s2.insert(1, ARRAY[3]);
			s2.insert(2, ARRAY[2]);
			int mid = itemcount();
			Sequence s3;
			s3.insert(0, ARRAY[5]);
			s3.insert(0, ARRAY[4]);
			s3 = s2;
			assert(itemcount() - mid == mid - before);
		}
	} break; case 90: {
		{
			Sequence s2;
			s2.insert(0, ARRAY[1]);
			s2.insert(1, ARRAY[3]);
			s2.insert(2, ARRAY[2]);
			Sequence s3;
			s3.insert(0, ARRAY[5]);
			s3.insert(0, ARRAY[4]);
			s3 = s2;
			s3.insert(3, ARRAY[3]);
			assert(s3.size() == s2.size() + 1);
			for (int k = 0; k < s2.size(); k++)
			{
				ItemType x2 = SOMEVAL;
				ItemType x3 = DEFAULT;
				s2.get(k, x2);
				s3.get(k, x3);
				assert(x2 == x3);
			}
		}
	} break; case 91: {
		int before = itemcount();
		{
			Sequence s2;
			s2.insert(0, ARRAY[1]);
			s2.insert(1, ARRAY[3]);
			s2.insert(2, ARRAY[2]);
			Sequence s3;
			s3.insert(0, ARRAY[5]);
			s3.insert(0, ARRAY[4]);
			s2 = s3;
			assert(s2.size() == s3.size());
			ItemType x;
			assert(!s2.get(2, x));
			s2.insert(0, ARRAY[3]);
			assert(s2.size() == s3.size() + 1);
			assert(s2.get(0, x) && x == ARRAY[3]);
			assert(s2.get(1, x) && x == ARRAY[4]);
			assert(s2.get(2, x) && x == ARRAY[5]);
		}
		assert(itemcount() == before);
	} break; case 92: {
		{
			Sequence s2;
			s2.insert(0, ARRAY[1]);
			s2.insert(1, ARRAY[3]);
			s2.insert(2, ARRAY[2]);
			int n2 = itemcount();
			s2 = s2;
			assert(itemcount() == n2);
		}
		assert(true);  // no corruption so bad that destruction failed
	} break; case 93: {
		{
			Sequence s2;
			s2.insert(0, ARRAY[1]);
			s2.insert(1, ARRAY[3]);
			s2.insert(2, ARRAY[2]);
			s2 = s2;
			s2.insert(3, ARRAY[4]);
			ItemType x = SOMEVAL;
			s2.get(0, x); assert(x == ARRAY[1]);
			s2.get(1, x); assert(x == ARRAY[3]);
			s2.get(2, x); assert(x == ARRAY[2]);
			s2.get(3, x); assert(x == ARRAY[4]);
		}
	} break; case 94: {
		Sequence s2;
		assert(subsequence(s2, s) == -1);
	} break; case 95: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[3]);
		s.insert(2, ARRAY[2]);
		Sequence s2;
		assert(subsequence(s2, s) == -1);
	} break; case 96: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[3]);
		s.insert(2, ARRAY[2]);
		Sequence s2;
		assert(subsequence(s, s2) == -1);
	} break; case 97: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[3]);
		s.insert(2, ARRAY[2]);
		assert(subsequence(s, s) == 0);
	} break; case 98: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		s.insert(3, ARRAY[0]);
		s.insert(4, ARRAY[2]);
		Sequence s2;
		s2.insert(0, ARRAY[3]);
		s2.insert(1, ARRAY[0]);
		assert(subsequence(s, s2) == 2);
	} break; case 99: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		s.insert(3, ARRAY[0]);
		s.insert(4, ARRAY[2]);
		Sequence s2;
		s2.insert(0, ARRAY[0]);
		s2.insert(1, ARRAY[3]);
		assert(subsequence(s, s2) == -1);
	} break; case 100: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		s.insert(3, ARRAY[0]);
		s.insert(4, ARRAY[2]);
		Sequence s2;
		s2.insert(0, ARRAY[3]);
		s2.insert(1, ARRAY[2]);
		assert(subsequence(s, s2) == -1);
	} break; case 101: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[3]);
		s.insert(2, ARRAY[3]);
		s.insert(3, ARRAY[0]);
		s.insert(4, ARRAY[2]);
		Sequence s2;
		s2.insert(0, ARRAY[3]);
		s2.insert(1, ARRAY[0]);
		assert(subsequence(s, s2) == 2);
	} break; case 102: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		s.insert(3, ARRAY[0]);
		s.insert(4, ARRAY[2]);
		Sequence s2;
		s2.insert(0, ARRAY[0]);
		s2.insert(1, ARRAY[2]);
		assert(subsequence(s, s2) == 3);
	} break; case 103: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		s.insert(3, ARRAY[0]);
		s.insert(4, ARRAY[2]);
		Sequence s2;
		s2.insert(0, ARRAY[0]);
		s2.insert(1, ARRAY[2]);
		s2.insert(1, ARRAY[3]);
		assert(subsequence(s, s2) == -1);
	} break; case 104: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		Sequence s2;
		Sequence s3;
		interleave(s, s2, s3);
		assert(s3.size() == s.size());
		for (int k = 0; k < s.size(); k++)
		{
			ItemType x = SOMEVAL;
			ItemType x3 = SOMEVAL;
			s.get(k, x);
			s3.get(k, x3);
			assert(x == x3);
		}
	} break; case 105: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		Sequence s2;
		Sequence s3;
		interleave(s2, s, s3);
		assert(s3.size() == s.size());
		for (int k = 0; k < s.size(); k++)
		{
			ItemType x = SOMEVAL;
			ItemType x3 = SOMEVAL;
			s.get(k, x);
			s3.get(k, x3);
			assert(x == x3);
		}
	} break; case 106: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		Sequence s2;
		s2.insert(0, ARRAY[2]);
		s2.insert(1, ARRAY[0]);
		s2.insert(2, ARRAY[4]);
		Sequence s3;
		interleave(s, s2, s3);
		assert(s3.size() == s.size() + s2.size());
		for (int k = 0; k < s3.size(); k++)
		{
			ItemType x = SOMEVAL;
			ItemType x3 = SOMEVAL;
			if (k % 2 == 0)
				s.get(k / 2, x);
			else
				s2.get(k / 2, x);
			s3.get(k, x3);
			assert(x == x3);
		}
	} break; case 107: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		s.insert(3, ARRAY[0]);
		s.insert(4, ARRAY[2]);
		Sequence s2;
		s2.insert(0, ARRAY[2]);
		s2.insert(1, ARRAY[0]);
		s2.insert(2, ARRAY[4]);
		Sequence s3;
		interleave(s, s2, s3);
		assert(s3.size() == s.size() + s2.size());
		for (int k = 0; k < s3.size(); k++)
		{
			ItemType x = SOMEVAL;
			ItemType x3 = SOMEVAL;
			if (k >= 2 * s2.size())
				s.get(k - s2.size(), x);
			else if (k % 2 == 0)
				s.get(k / 2, x);
			else
				s2.get(k / 2, x);
			s3.get(k, x3);
			assert(x == x3);
		}
	} break; case 108: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		Sequence s2;
		s2.insert(0, ARRAY[2]);
		s2.insert(1, ARRAY[0]);
		s2.insert(2, ARRAY[4]);
		s2.insert(3, ARRAY[1]);
		s2.insert(4, ARRAY[3]);
		Sequence s3;
		interleave(s, s2, s3);
		assert(s3.size() == s.size() + s2.size());
		for (int k = 0; k < s3.size(); k++)
		{
			ItemType x = SOMEVAL;
			ItemType x3 = SOMEVAL;
			if (k >= 2 * s.size())
				s2.get(k - s.size(), x);
			else if (k % 2 == 0)
				s.get(k / 2, x);
			else
				s2.get(k / 2, x);
			s3.get(k, x3);
			assert(x == x3);
		}
	} break; case 109: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		s.insert(2, ARRAY[3]);
		Sequence s2;
		s2.insert(0, ARRAY[2]);
		s2.insert(1, ARRAY[0]);
		s2.insert(2, ARRAY[4]);
		Sequence s3;
		s3.insert(0, ARRAY[3]);
		s3.insert(1, ARRAY[2]);
		s3.insert(2, ARRAY[1]);
		interleave(s, s2, s3);
		assert(s3.size() == s.size() + s2.size());
		for (int k = 0; k < s3.size(); k++)
		{
			ItemType x = SOMEVAL;
			ItemType x3 = SOMEVAL;
			if (k % 2 == 0)
				s.get(k / 2, x);
			else
				s2.get(k / 2, x);
			s3.get(k, x3);
			assert(x == x3);
		}
	} break; case 110: { //fk up
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		Sequence s2;
		s2.insert(0, ARRAY[3]);
		s2.insert(1, ARRAY[2]);
		s2.insert(2, ARRAY[0]);
		interleave(s, s2, s);
		assert(s.size() == 5);
		ItemType x = SOMEVAL;
		s.get(0, x); assert(x == ARRAY[1]);
		s.get(1, x); assert(x == ARRAY[3]);
		s.get(2, x); assert(x == ARRAY[4]);
		s.get(3, x); assert(x == ARRAY[2]);
		s.get(4, x); assert(x == ARRAY[0]);
		s2.get(0, x); assert(x == ARRAY[3]);
		s2.get(1, x); assert(x == ARRAY[2]);
		s2.get(2, x); assert(x == ARRAY[0]);
	} break; case 111: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		Sequence s2;
		s2.insert(0, ARRAY[3]);
		s2.insert(1, ARRAY[2]);
		s2.insert(2, ARRAY[0]);
		interleave(s, s2, s2);
		assert(s2.size() == 5);
		ItemType x = SOMEVAL;
		s2.get(0, x); assert(x == ARRAY[1]);
		s2.get(1, x); assert(x == ARRAY[3]);
		s2.get(2, x); assert(x == ARRAY[4]);
		s2.get(3, x); assert(x == ARRAY[2]);
		s2.get(4, x); assert(x == ARRAY[0]);
		s.get(0, x); assert(x == ARRAY[1]);
		s.get(1, x); assert(x == ARRAY[4]);
	} break; case 112: {
		s.insert(0, ARRAY[1]);
		s.insert(1, ARRAY[4]);
		interleave(s, s, s);
		assert(s.size() == 4);
		ItemType x = SOMEVAL;
		s.get(0, x); assert(x == ARRAY[1]);
		s.get(1, x); assert(x == ARRAY[1]);
		s.get(2, x); assert(x == ARRAY[4]);
		s.get(3, x); assert(x == ARRAY[4]);
	} break; case 113: {
		const int NITEMS = 1000;
		for (size_t k = 0; k < NITEMS; k++)
			assert(s.insert(0, ARRAY[k % 4]) == 0);
		assert(s.size() == NITEMS);
		for (size_t k = NITEMS; k > 0; )
		{
			k--;
			ItemType x;
			s.get(0, x);
			assert(x == ARRAY[k % 4]);
			s.erase(0);
		}
		assert(s.size() == 0);
	}
	}
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testone(n);
	cout << "Passed" << endl;
}

//#include "Sequence.h"
//#include <iostream>
//#include <cassert>
//#include <type_traits>
//
//#define CHECKTYPE(c, f, r, a)  \
//		{  \
//		 static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
//		     "You did not declare " #c "::" #f " as the Project 2 spec does");  \
//		 auto p = static_cast<r (c::*)a>(&c::f);  \
//		 (void) p;  \
//		}
//#define CHECKTYPENONMEMBER(f, r, a)  \
//		{  \
//		 static_assert(std::is_same<decltype(&f), r (*)a>::value, \
//		     "You did not declare " #f " as the Project 2 spec does");  \
//		 auto p = static_cast<r (*)a>(f);  \
//		 (void) p;  \
//		}
//
//static_assert(std::is_default_constructible<Sequence>::value,
//    "Sequence must be default-constructible.");
//static_assert(std::is_copy_constructible<Sequence>::value,
//    "Sequence must be copy-constructible.");
//static_assert(std::is_copy_assignable<Sequence>::value,
//    "Sequence must be assignable.");
//
//void thisFunctionWillNeverBeCalled()
//{
//    CHECKTYPE(Sequence, empty, bool, () const);
//    CHECKTYPE(Sequence, size, int, () const);
//    CHECKTYPE(Sequence, erase, bool, (int));
//    CHECKTYPE(Sequence, remove, int, (const ItemType&));
//    CHECKTYPE(Sequence, get, bool, (int, ItemType&) const);
//    CHECKTYPE(Sequence, set, bool, (int, const ItemType&));
//    CHECKTYPE(Sequence, find, int, (const ItemType&) const);
//    CHECKTYPE(Sequence, swap, void, (Sequence&));
//    CHECKTYPENONMEMBER(subsequence, int, (const Sequence&, const Sequence&));
//    CHECKTYPENONMEMBER(interleave, void, (const Sequence&, const Sequence&, Sequence&));
//    { auto p = static_cast<int (Sequence::*)(int, const ItemType&)>(&Sequence::insert); (void)p; }
//    { auto p = static_cast<int (Sequence::*)(const ItemType&)>(&Sequence::insert); (void)p; }
//}
//
//int main()
//{
//    const int maxFill = 20;
//
//    // Default constructor
//    {
//        Sequence test;
//        assert(test.empty() == true);
//        assert(test.size() == 0);
//    }
//    // Copy constructor
//    {
//        Sequence base;
//        for (int i = 0; i < maxFill; i++) 
//            assert(base.insert(i) == i);
//        Sequence test = base;
//        assert(base.find(0) == 0);
//        assert(base.find(1) == 1);
//        for (int i = 0; i < maxFill; i++)
//            assert(test.find(i) == i);
//        base.erase(maxFill - 1);
//        test.erase(0);
//        for (int i = 0; i < maxFill - 1; i++)
//        {
//            assert(base.find(i) == i);
//            assert(test.find(i + 1) == i);
//        }
//    }
//    // Assignment operator
//    {
//        Sequence base, test;
//        // Create different Sequences
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(base.insert(i) == i);
//            assert(test.insert(i + maxFill) == i);
//        }
//        // Validate different Sequences
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(base.find(i) == i);
//            assert(test.find(i + maxFill) == i);
//        }
//        // Check if Sequences are the same after assignment
//        test = base;
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(base.find(i) == i);
//            assert(test.find(i) == i);
//        }
//        // Check if modifying one does not modify the other
//        base.erase(maxFill - 1);
//        test.erase(0);
//        for (int i = 0; i < maxFill - 1; i++)
//        {
//            assert(base.find(i) == i);
//            assert(test.find(i + 1) == i);
//        }
//
//        // Assign to empty
//        Sequence testFull, testEmpty;
//        for (int i = 0; i < maxFill; i++)
//            assert(testFull.insert(i) == i);
//        for (int i = 0; i < maxFill; i++)
//            assert(testFull.find(i) == i);
//        testFull = testEmpty;
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(testFull.find(i) == -1);
//            assert(testEmpty.find(i) == -1);
//        }
//
//        // Aliasing
//        Sequence testAlias;
//        for (int i = 0; i < maxFill; i++)
//            assert(testAlias.insert(i) == i);
//        for (int i = 0; i < maxFill; i++)
//            assert(testAlias.find(i) == i);
//        testAlias = testAlias;
//        for (int i = 0; i < maxFill; i++)
//            assert(testAlias.find(i) == i);
//    }
//    // empty(), size()
//    {
//        Sequence test;
//        assert(test.empty());
//        assert(test.size() == 0);
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(test.insert(i) == i);
//            assert(test.empty() == false);
//            assert(test.size() == i + 1);
//        }
//    }
//    // insert(pos, value)
//    {
//        Sequence test;
//        int mid = 0;
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(test.insert(mid, i) == mid);
//            assert(test.size() == i + 1);
//            mid = test.size() / 2;
//        }
//        for (int i = 0; i < mid; i++)
//        {
//            assert(test.find(2 * i + 1) == i);
//            assert(test.find(2 * i) == maxFill - 1 - i);
//        }
//    }
//    // insert(value)
//    {
//        Sequence test1, test2;
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(test1.insert(i) == i);
//            assert(test2.insert(maxFill - i - 1) == 0);
//            assert(test1.size() == i + 1);
//            assert(test2.size() == i + 1);
//        }
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(test1.find(i) == i);
//            assert(test2.find(i) == i);
//        }
//    }
//    // erase(pos)
//    {
//        Sequence test;
//
//        // Remove from end
//        for (int i = 0; i < maxFill; i++)
//            assert(test.insert(i) == i);
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(test.erase(test.size() - 1));
//            assert(test.size() == maxFill - 1 - i);
//            for (int j = 0; j < test.size(); j++)
//                assert(test.find(j) == j);
//        }
//
//        // Remove from front
//        for (int i = 0; i < maxFill; i++)
//            assert(test.insert(i) == i);
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(test.erase(0));
//            assert(test.size() == maxFill - 1 - i);
//            for (int j = 0; j < test.size(); j++)
//                assert(test.find(j + i + 1) == j);
//        }
//    }
//    // remove(value)
//    {
//        Sequence test;
//        ItemType arr[] = { 0, 7, 1, 7, 2, 7, 3, 7, 4, 7 };
//        for (int i = 0; i < 10; i++)
//            assert(test.insert(i, arr[i]) == i);
//        assert(test.remove(7) == 5);
//        for (int i = 0; i < 5; i++)
//            assert(test.find(i) == i);
//        assert(test.remove(7) == 0);
//    }
//    // get(pos, value)
//    {
//        Sequence test;
//        ItemType IT;
//        for (int i = 0; i < maxFill; i++)
//            assert(test.insert(i) == i);
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(test.get(i, IT));
//            assert(IT == i);
//        }
//        assert(test.get(-1, IT) == false);
//        assert(test.get(test.size(), IT) == false);
//    }
//    // set(pos, value)
//    {
//        Sequence test;
//        for (int i = 0; i < maxFill; i++)
//            assert(test.insert(i) == i);
//        for (int i = 0; i < maxFill; i++)
//            assert(test.find(i) == i);
//        for (int i = 0; i < maxFill; i++)
//            assert(test.set(i, i + maxFill));
//        assert(test.set(-1, 1) == false);
//        assert(test.set(test.size(), 1) == false);
//        for (int i = 0; i < maxFill; i++)
//            assert(test.find(i + maxFill) == i);
//    }
//    // swap(Seq1, Seq2)
//    {
//        Sequence test1, test2;
//        for (int i = 0; i < maxFill; i++)
//            assert(test1.insert(i) == i);
//        for (int i = 0; i < 2 * maxFill; i++)
//            assert(test2.insert(i + maxFill) == i);
//        assert(test1.size() == maxFill);
//        assert(test2.size() == maxFill * 2);
//
//        for (int i = 0; i < maxFill; i++)
//            assert(test1.find(i) == i);
//        for (int i = 0; i < 2 * maxFill; i++)
//            assert(test2.find(i + maxFill) == i);
//
//        test1.swap(test2);
//        assert(test1.size() == maxFill * 2);
//        assert(test2.size() == maxFill);
//        for (int i = 0; i < maxFill; i++)
//            assert(test2.find(i) == i);
//        for (int i = 0; i < 2 * maxFill; i++)
//            assert(test1.find(i + maxFill) == i);
//
//        // Empty swap
//        Sequence testFull, testEmpty;
//        for (int i = 0; i < maxFill; i++)
//            assert(testFull.insert(i) == i);
//        for (int i = 0; i < maxFill; i++)
//            assert(testFull.find(i) == i);
//        assert(testFull.size() == maxFill);
//        assert(testEmpty.empty());
//
//        testFull.swap(testEmpty);
//        assert(testFull.empty());
//        assert(testEmpty.size() == maxFill);
//        for (int i = 0; i < maxFill; i++)
//        {
//            assert(testFull.find(i) == -1);
//            assert(testEmpty.find(i) == i);
//        }
//
//        // Aliasing
//        Sequence testAlias;
//        for (int i = 0; i < maxFill; i++)
//            assert(testAlias.insert(i) == i);
//        testAlias.swap(testAlias);
//        for (int i = 0; i < maxFill; i++)
//            assert(testAlias.find(i) == i);
//    }
//    // subsequence
//    {
//        Sequence t01, t02;
//        ItemType t01a[] = { 1, 2, 2, 3, 2, 3, 4, 5 };
//        ItemType t02a[] = { 2, 3, 4, 5 };
//        for (int i = 0; i < 8; i++)
//            t01.insert(i, t01a[i]);
//        for (int i = 0; i < 4; i++)
//            t02.insert(i, t02a[i]);
//        assert(subsequence(t01, t02) == 4);
//
//        Sequence t11, t12;
//        ItemType t11a[] = { 1, 2, 2, 3, 2, 3, 4, 5 };
//        ItemType t12a[] = { 2, 3, 4 };
//        for (int i = 0; i < 8; i++)
//            t11.insert(i, t11a[i]);
//        for (int i = 0; i < 3; i++)
//            t12.insert(i, t12a[i]);
//        assert(subsequence(t11, t12) == 4);
//
//        Sequence t21, t22;
//        ItemType t21a[] = { 1, 2, 2, 3, 5 };
//        ItemType t22a[] = { 2, 3, 4, 5 };
//        for (int i = 0; i < 5; i++)
//            t21.insert(i, t21a[i]);
//        for (int i = 0; i < 4; i++)
//            t22.insert(i, t22a[i]);
//        assert(subsequence(t21, t22) == -1);
//
//        Sequence t31, t32;
//        ItemType t31a[] = { 1, 2, 2, 3, 5 };
//        for (int i = 0; i < 5; i++)
//            t31.insert(i, t31a[i]);
//        assert(subsequence(t31, t32) == -1);
//
//        Sequence t41, t42;
//        ItemType t42a[] = { 2, 3, 4, 5 };
//        for (int i = 0; i < 4; i++)
//            t42.insert(i, t42a[i]);
//        assert(subsequence(t41, t42) == -1);
//    }
//    // interleave
//    {
//        Sequence t01, t02, t03;
//        for (int i = 0; i < 5; i++)
//        {
//            t01.insert(2 * i);
//            t02.insert(2 * i + 1);
//            t03.insert(-1);
//        }
//        interleave(t01, t02, t03);
//        assert(t03.size() == 10);
//        for (int i = 0; i < 10; i++)
//            assert(t03.find(i) == i);
//
//        Sequence t11, t12, t13;
//        ItemType t11a[] = { 1, 2, 3, 4, 5 };
//        ItemType t12a[] = { 6, 7, 8 };
//        ItemType t13a[] = { 1, 6, 2, 7, 3, 8, 4, 5 };
//        for (ItemType elem : t11a)
//            t11.insert(elem);
//        for (ItemType elem : t12a)
//            t12.insert(elem);
//        interleave(t11, t12, t13);
//        assert(t13.size() == 8);
//        int i1 = 0;
//        for (ItemType elem : t13a)
//        {
//            ItemType temp;
//            t13.get(i1, temp);
//            assert(temp == elem);
//            i1++;
//        }
//
//        Sequence t21, t22, t23;
//        ItemType t21a[] = { 6, 7, 8 };
//        ItemType t22a[] = { 1, 2, 3, 4, 5 };
//        ItemType t23a[] = { 6, 1, 7, 2, 8, 3, 4, 5 };
//        for (ItemType elem : t21a)
//            t21.insert(elem);
//        for (ItemType elem : t22a)
//            t22.insert(elem);
//        interleave(t21, t22, t23);
//        assert(t23.size() == 8);
//        int i2 = 0;
//        for (ItemType elem : t23a)
//        {
//            ItemType temp;
//            t23.get(i2, temp);
//            assert(temp == elem);
//            i2++;
//        }
//
//        Sequence t31, t32, t33;
//        ItemType t31a[] = { 1, 2, 3, 4, 5 };
//        for (ItemType elem : t31a)
//            t31.insert(elem);
//        interleave(t31, t32, t33);
//        assert(t33.size() == 5);
//        int i3 = 0;
//        for (ItemType elem : t31a)
//        {
//            ItemType temp;
//            t33.get(i3, temp);
//            assert(temp == elem);
//            i3++;
//        }
//
//        Sequence t41, t42, t43;
//        ItemType t42a[] = { 1, 2, 3, 4, 5 };
//        for (ItemType elem : t42a)
//            t42.insert(elem);
//        interleave(t41, t42, t43);
//        assert(t33.size() == 5);
//        int i4 = 0;
//        for (ItemType elem : t42a)
//        {
//            ItemType temp;
//            t43.get(i4, temp);
//            assert(temp == elem);
//            i4++;
//        }
//
//        Sequence t51, t52, t53;
//        interleave(t51, t52, t53);
//        assert(t53.size() == 0);
//    }
//    std::cerr << "           ',\n        .-`-,\\__\n          .\"`   `,\n        .'_.  ._  `;.\n    __ / `      `  `.\\ .--.\n   /--,| 0)   0)     )`_.-,)\n  |    ;.-----.__ _-');   /\n   '--./         `.`/  `\"`\n      :   '`      |.\n      | \     /  //\n       \\ '---'  /'\n        `------' \\\n         _/       `--..." << std::endl;
//}
