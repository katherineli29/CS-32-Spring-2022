#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence() : head(nullptr), tail(nullptr), m_size(0) {
}

Sequence::~Sequence() {
	Node* p; //pointer
	for (p = head; p != nullptr; p = head) {
		head = p->next;
		delete p;
	}
}

Sequence::Sequence(const Sequence& other) {
	cerr << "Created " << "(" << this << ") copied from ("
		<< &other << ")" << endl;
	if (other.head == nullptr) { //empty list
		head = nullptr;
		tail = nullptr;
		m_size = 0;
	}
	else {
		m_size = other.m_size; //set m_size

		head = new Node; //create new head
		head->before = nullptr;
		head->next = nullptr;
		head->m_value = other.head->m_value;

		Node* current = head; //two pointers
		Node* currentOther = other.head;
		
		while (currentOther->next != nullptr) {
			current->next = new Node; //new node
			current->next->before = current; //set before of new node to current
			current = current->next; //update pointers
			currentOther = currentOther->next; 
			current->m_value = currentOther->m_value; //set m_value equal
		}
		current->next = nullptr; //end
		tail = current; //set tail
	}
}

Sequence& Sequence::operator=(const Sequence& other) {
	if (this != &other) {
		Sequence temp(other);
		swap(temp);
	}

	return *this;
}

bool Sequence::empty() const {
	if (m_size == 0) { 
		return true;
	}
	return false;
}

int Sequence::size() const {
	return m_size;
}

int Sequence::insert(int pos, const ItemType& value) {
	// Insert value into the sequence so that it becomes the item at
	// position pos.  The original item at position pos and those that
	// follow it end up at positions one greater than they were at before.
	// Return pos if 0 <= pos <= size() and the value could be
	// inserted. Notice that if pos is equal to size(), the value is 
	// inserted at the end.
	if (pos < 0 || pos > m_size) { //pos is not valid value
		return -1;
	}

	//empty sequence
	if (m_size == 0) {
		m_size++;
		head = new Node;
		head->before = nullptr;
		head->next = nullptr;
		head->m_value = value;
		tail = head;
		return pos;
	}

	if (pos == m_size) { //add at end
		tail->next = new Node;
		tail->next->before = tail;
		tail = tail->next;
		tail->next = nullptr;
		tail->m_value = value;
	}
	else if (pos == 0) { //add at beginning
		head->before = new Node;
		head->before->next = head;
		head = head->before;
		head->before = nullptr;
		head->m_value = value;
	}
	else{ //add in middle
		Node* p = head; //create pointer for node at pos
		for (int i = 0; i < pos; i++) {
			p = p->next;
		}

		Node* temp = new Node; //new node
		temp->next = p;
		temp->before = p->before;
		temp->m_value = value;

		p->before = temp;
		temp->before->next = temp;
	}
	m_size++;
	return pos;
}

int Sequence::insert(const ItemType& value) {
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item in position
// p.  The original item at position p and those that follow it end
// up at positions one greater than before.  Return p if the value
// was actually inserted.  
	if (m_size == 0) {
		return insert(0, value);
	}

	int pos = 0;
	for (Node* p = head; p != nullptr; p = p->next) { //if there is value smaller than value, p is initalized to that pos
		if (value <= p->m_value) {
			break;
		}
		pos++;
	}

	return insert(pos, value);
}

bool Sequence::erase(int pos) {
 // If 0 <= pos < size(), remove the item at position pos from
 // the sequence (so that all items that followed that item end up at
 // positions one lower than they were at before), and return true.
 // Otherwise, leave the sequence unchanged and return false.
	if (!(0 <= pos && pos < m_size)) {
		return false;
	}

	//1 element array being emptied
	if (m_size == 1) {
		delete head;
		head = nullptr;
		tail = nullptr;
		m_size--;
		return true;
	}

	//deleting head
	if (pos == 0) {
		Node* temp = head;
		head = head->next;
		delete temp;
		head->before = nullptr;
		m_size--;
		return true;
	}
	
	//deleting tail
	if(pos == m_size - 1){
		Node* temp = tail;
		tail = tail->before;
		delete temp;
		tail->next = nullptr;
		m_size--;
		return true;
	}

	Node* p = head; //create pointer for node at pos
	for (int i = 0; i < pos; i++) {
		p = p->next;
	}

	p->next->before = p->before;
	p->before->next = p->next;
	delete p;

	m_size--;
	return true;
}

int Sequence::remove(const ItemType& value) {
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
	if (m_size == 0) {
		return 0;
	}

	int num = 0;
	Node* p = head;

	for (int pos = 0; p != nullptr; pos++) {
		if (p->m_value == value) {
			p = p->next;
			erase(pos);
			num++;
			pos--;
		}
		else {
			p = p->next;
		}
	}

	return num;
}

bool Sequence::get(int pos, ItemType& value) const {
// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
	if (!(0 <= pos && pos < m_size)) {
		return false;
	}

	Node* p = head; //create pointer for node at pos
	for (int i = 0; i < pos; i++) {
		p = p->next;
	}

	value = p->m_value;

	return true;
}

bool Sequence::set(int pos, const ItemType& value) {
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
	if (!(0 <= pos && pos < m_size)) {
		return false;
	}

	Node* p = head; //create pointer for node at pos
	for (int i = 0; i < pos; i++) {
		p = p->next;
	}

	p->m_value = value;
	return true;
}

int Sequence::find(const ItemType& value) const {
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
	int p = -1;

	Node* pointer;
	int pos = 0;

	for (pointer = head; pointer != nullptr; pointer = pointer->next, pos++) {
		if (pointer->m_value == value) {
			p = pos;
			break;
		}
	}

	return p;
}

void Sequence::swap(Sequence& other) {
	// Exchange the contents of this sequence with the other one.

	int temp = m_size;
	m_size = other.m_size;
	other.m_size = temp;
	
	Node* tempHead = head;
	Node* tempTail = tail;
	head = other.head;
	tail = other.tail;
	other.head = tempHead;
	other.tail = tempTail;
}

//Consider all the items in seq2; let's call them seq20, seq21, ..., seq2n. 
//If there exists at least one k such that seq1k == seq20 and seq1k+1 == seq21 
//and ... and seq1k+n == seq2n, and k+n < seq1.size(), then this function 
//returns the smallest such k. (In other words, if seq2 is a consecutive 
//subsequence of seq1, the function returns the earliest place in seq1 
//where that subsequence starts.) If no such k exists or if seq2 is empty, the 
//function returns -1.
int subsequence(const Sequence& seq1, const Sequence& seq2) {
	if (seq2.empty() || seq1.empty()) {
		return -1;
	}

	int pos = -1;
	for (int i = 0; i <= seq1.size() - seq2.size(); i++) { //run through values of seq1
		ItemType value1;
		ItemType value2;
		seq1.get(i, value1);
		seq2.get(0, value2);
		
		if (value1 == value2) { //compare first value of seq1 to seq2
			for (int j = 0; j < seq2.size(); j++) { //run through values of seq2
				seq1.get(i+j, value1);
				seq2.get(j, value2);

				if (value1 != value2) { //break checking if there is smth not equal
					break;
				}

				if (j == seq2.size() - 1) { //once j is seq2.size() - 1, subsequence confirmed
					pos = i;
					break;
				}
			}
		}

		if (pos != -1) { //can stop checking once subsequence is found
			break;
		}
	}

	return pos;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
	if (seq1.empty()) { 
		result = seq2;
	}
	else if (seq2.empty()) {
		result = seq1;
	}
	else if (seq1.empty() && seq2.empty()) {
		result = Sequence();
	}
	else { //neither sequence empty
		Sequence temp = Sequence();

		int pos = 0;
		for (int i = 0; i < seq1.size() && i < seq2.size(); i++) { //interleave
			ItemType value;
			seq1.get(i, value);
			temp.insert(pos, value);
			pos++;

			seq2.get(i, value);
			temp.insert(pos, value);
			pos++;
		}

		if (seq1.size() > seq2.size()) { //seq1 is longer
			for (int i = 0; i < seq1.size() - seq2.size(); i++) {
				ItemType value;
				seq1.get(seq2.size() + i, value);
				temp.insert(pos, value);
				pos++;
			}
		}
		else if (seq1.size() < seq2.size()) { //seq2 is longer
			for (int i = 0; i < seq2.size() - seq1.size(); i++) {
				ItemType value;
				seq2.get(seq1.size() + i, value);
				temp.insert(pos, value);
				pos++;
			}
		}

		result = temp;
	}
}