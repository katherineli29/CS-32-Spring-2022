#include "LevelList.h"

LevelList::LevelList() {       // Create an empty level list.
	mSeq = Sequence();
}

bool LevelList::add(unsigned long level) {
	// If the level is valid (a value from 30 to 400) and the level list
	// has room for it, add it to the level list and return true.
	// Otherwise, leave the level list unchanged and return false.
	if (level <= 30 || level >= 400 || mSeq.size() + 1 <= 180) {
		return false;
	}

	mSeq.insert(mSeq.size(), level);
	return true;
}

bool LevelList::remove(unsigned long level) {
	// Remove one instance of the specified level from the level list.
	// Return true if a level was removed; otherwise false.
	if (mSeq.find(level) == -1) { //if unable to find level
		return false;
	}

	mSeq.erase(mSeq.find(level)); //erase value at level's position
	return true;
}

int LevelList::size() const {  // Return the number of levels in the list.
	return mSeq.size();
}

unsigned long LevelList::minimum() const {
	// Return the lowest-valued level in the level list.  If the list is
	// empty, return NO_LEVEL.
	if (mSeq.empty()) {
		return NO_LEVEL;
	}

	unsigned long min;
	mSeq.get(0, min);
	for (int i = 1; i < mSeq.size(); i++) {
		unsigned long comp;
		mSeq.get(i, comp);
		if (comp < min) {
			min = comp; //assign comp to min if comp is smaller
		}
	}
	return min;
}

unsigned long LevelList::maximum() const {
	// Return the highest-valued level in the level list.  If the list is
	// empty, return NO_LEVEL.
	if (mSeq.empty()) {
		return NO_LEVEL;
	}

	unsigned long max;
	mSeq.get(0, max);
	for (int i = 1; i < mSeq.size(); i++) {
		unsigned long comp;
		mSeq.get(i, comp);
		if (comp > max) {
			max = comp; //assign comp to max if comp is greater
		}
	}
	return max;
}