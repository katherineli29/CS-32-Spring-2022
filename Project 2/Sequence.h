#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

using ItemType = unsigned long;

class Sequence
{
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& other);
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
private:
    struct Node {
        ItemType m_value;
        Node* next;
        Node* before;
    };
    
    Node* head;
    Node* tail;
    int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif