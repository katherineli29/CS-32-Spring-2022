#include <stdlib.h>
#include "NewSequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence() {    // Create an empty sequence (i.e., one whose size() is 0).
	vsize = 0;
	vmax = DEFAULT_MAX_ITEMS;
	arr = new ItemType[vmax];
}

Sequence::Sequence(int amt) {    // Create a sequence that can hold at most amt ItemTypes
	if (amt <= 0) {
		exit(1);
	}
	vsize = 0;
	vmax = amt;
	arr = new ItemType[vmax];
}

Sequence::Sequence(const Sequence& seq) {
	vsize = seq.size();
	vmax = seq.vmax;
	arr = new ItemType[vmax];
	for (int i = 0; i < vsize; i++) {
		arr[i] = seq.arr[i];
	}
}

Sequence& Sequence::operator=(const Sequence& other)
{
	if (this == &other) {
		return *this;
	}
	Sequence temp = other;
	swap(temp);
	return *this;
}

Sequence::~Sequence() {
	delete[] arr;
}

bool Sequence::empty() const {  // Return true if the sequence is empty, otherwise false.
	return (vsize == 0);
}

int Sequence::size() const {    // Return the number of items in the sequence.
	return vsize;
}

int Sequence::insert(int pos, const ItemType& value) {
	// Insert value into the sequence so that it becomes the item at
	// position pos.  The original item at position pos and those that
	// follow it end up at positions one greater than they were at before.
	// Return pos if 0 <= pos <= size() and the value could be
	// inserted.  (It might not be, if the sequence has a fixed capacity,
	// e.g., because it's implemented using a fixed-size array.)  Otherwise,
	// leave the sequence unchanged and return -1.  Notice that
	// if pos is equal to size(), the value is inserted at the end.
	if (!(0 <= pos && pos <= size() && ((vsize + 1) <= DEFAULT_MAX_ITEMS))) { //is it possible
		return -1;
	}
	if (pos == size()) { //add in at end
		arr[vsize] = value;
		vsize++;
	}
	else { //shift right
		for (int i = size() - 1; i >= pos; i--) {
			arr[i + 1] = arr[i];
		}
		arr[pos] = value;
		vsize++;
	}
	return pos;
}

int Sequence::insert(const ItemType& value) {
	// Let p be the smallest integer such that value <= the item at
	// position p in the sequence; if no such item exists (i.e.,
	// value > all items in the sequence), let p be size().  Insert
	// value into the sequence so that it becomes the item in position
	// p.  The original item at position p and those that follow it end
	// up at positions one greater than before.  Return p if the value
	// was actually inserted.  Return -1 if the value was not inserted
	// (perhaps because the sequence has a fixed capacity and is full).
	if (size() + 1 > DEFAULT_MAX_ITEMS) { //returns -1 if full
		return -1;
	}

	int p = size();
	for (int i = 0; i < size(); i++) { //if there is value smaller than value, p is initalized to that pos
		if (value <= arr[i]) {
			p = i;
			break;
		}
	}

	insert(p, value);

	return p;
}

bool Sequence::erase(int pos) {
	// If 0 <= pos < size(), remove the item at position pos from
	// the sequence (so that all items that followed that item end up at
	// positions one lower than they were at before), and return true.
	// Otherwise, leave the sequence unchanged and return false.
	if (!(0 <= pos && pos < size())) { //return false
		return false;
	}

	for (int i = pos; i <= size() - 2; i++) { //shift everything
		arr[i] = arr[i + 1];
	}

	vsize--;

	return true;
}

int Sequence::remove(const ItemType& value) {
	// Erase all items from the sequence that == value.  Return the
	// number of items removed (which will be 0 if no item == value).
	int num = 0;
	for (int i = 0; i < size(); i++) {
		if (arr[i] == value) { //erase all items that equal value
			erase(i);
			num++;
			i--;
		}
	}

	return num;
}

bool Sequence::get(int pos, ItemType& value) const {
	// If 0 <= pos < size(), copy into value the item at position pos
	// of the sequence and return true.  Otherwise, leave value unchanged
	// and return false.
	if (!(0 <= pos && pos < size())) { //return false if 0 <= pos < size()
		return false;
	}

	value = arr[pos];

	return true;
}

bool Sequence::set(int pos, const ItemType& value) {
	// If 0 <= pos < size(), replace the item at position pos in the
	// sequence with value and return true.  Otherwise, leave the sequence
	// unchanged and return false.
	if (!(0 <= pos && pos < size())) {
		return false;
	}

	arr[pos] = value;

	return true;
}

int Sequence::find(const ItemType& value) const {
	// Let p be the smallest integer such that value == the item at
	// position p in the sequence; if no such item exists, let p be -1.
	// Return p.
	int p = -1;

	for (int i = 0; i < size(); i++) { //if there is arr[i] equal to value, p is initalized to that pos
		if (arr[i] == value) {
			p = i;
			break;
		}
	}

	return p;
}

void Sequence::swap(Sequence& other) {
	// Exchange the contents of this sequence with the other one.
	int temp = vsize;
	vsize = other.vsize;
	other.vsize = temp;
	temp = vmax;
	vmax = other.vmax;
	other.vmax = temp;

	ItemType* tempPtr = arr;
	arr = other.arr;
	other.arr = tempPtr;
}