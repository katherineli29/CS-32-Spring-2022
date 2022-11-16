// NameTable.cpp

// This is a correct but inefficient implementation of
// the NameTable functionality.
#include <iostream>

#include "NameTable.h"
#include <string>
#include <list>
#include <functional>
#include <stack>
#include <vector>
using namespace std;

// This class does the real work of the implementation.

class NameTableImpl
{
public:
    NameTableImpl() {
        vector<string> temp;
        m_ids.push_back(temp);
    }

    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id) const;
private:
    int scopes = 0;

    struct Node {
        string identifier;
        int line;
    };

    list<Node> m_table[20000];
    vector<vector<string>> m_ids; 

    unsigned int hashFxn(const string& hashMe) const {
        hash<string> str_hash;
        return str_hash(hashMe) % 20000;
    }
};

void NameTableImpl::enterScope()
{
    // Extend the id vector with an empty string that
    // serves as a scope entry marker.

    scopes++;
    vector<string> temp;
    m_ids.push_back(temp);
}

bool NameTableImpl::exitScope()
{// Remove ids back to the last scope entry.
    if (scopes == 0) {
        return false;
    }

    while (m_ids.back().size() != 0) {
        //string last id (back.back) delete node by pop_front, create new bucket for new scope (change declare)
        string lastID = m_ids.back().back();
        m_ids[scopes].pop_back();

        unsigned int x = hashFxn(lastID);
        m_table[x].pop_front();
    }

    //while (!m_ids.empty() && !m_ids[scopes].empty()) //prob inefficient
    //{
    //    int x = hashFxn(m_ids[scopes].back());

    //    for (list<Node>::iterator p = m_table[x].begin(); p != m_table[x].end(); p++) {

    //        if ((*p).identifier == m_ids[scopes].back()) {
    //            (*p).scopeNumber.pop();
    //            (*p).line.pop();

    //            if ((*p).scopeNumber.empty()) {
    //                p = m_table[x].erase(p);
    //            }
    //            break;
    //        }
    //    }

    //    m_ids[scopes].pop_back();
    //}
    /*if (m_ids.empty())
        return false;*/

    // Remove the scope entry marker itself.

    m_ids.pop_back();
    scopes--;
    return true;
}

bool NameTableImpl::declare(const string& id, int lineNum)
{
    if (id.empty())
        return false;

    // Check for another declaration in the same scope. use hash table
    // Return if found, break out if encounter the scope
    // entry marker.

    //put name into hash table, check if name is in there and then scope number
    //if name and scope
    unsigned int x = hashFxn(id);

    if (m_table[x].empty()) {
        Node temp = { id, lineNum };
        m_table[x].push_front(temp);

        m_ids[scopes].push_back(id);
        return true;
    }

    //use vector isntead of list
    for (int i = 0; i < m_ids[scopes].size(); i++) {
        if (m_ids[scopes][i] == id) {
            return false;
        }
    }

    //for (list<Node>::iterator p = m_table[x].begin(); p != m_table[x].end(); p++) { 

    //    if ((*p).identifier == id) {
    //        if((*p).scopeNumber.top() == scopes) { //declared in scope
    //            return false;
    //        }
    //        //declared, but not in scope (shadowing)
    //        (*p).line.push(lineNum);
    //        (*p).scopeNumber.push(scopes);
    //        m_ids[scopes].push_back(id);
    //        return true;
    //    }
    //}

    // Save the declaration

    Node temp = {id, lineNum};
    m_table[x].push_front(temp);

    m_ids[scopes].push_back(id);
    return true;
}

int NameTableImpl::find(const string& id) const
{
    if (id.empty())
        return -1;

    // Search back for the most recent declaration still
    // available.

    unsigned int x = hashFxn(id);

    if (m_table[x].empty()) {
        return -1;
    }

    for (list<Node>::const_iterator p = m_table[x].begin(); p != m_table[x].end(); p++) {
        if ((*p).identifier == id) {
            return (*p).line;
        }
    }

    return -1;
}

//*********** NameTable functions **************

// For the most part, these functions simply delegate to NameTableImpl's
// functions.

NameTable::NameTable()
{
    m_impl = new NameTableImpl;
}

NameTable::~NameTable()
{
    delete m_impl;
}

void NameTable::enterScope()
{
    m_impl->enterScope();
}

bool NameTable::exitScope()
{
    return m_impl->exitScope();
}

bool NameTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int NameTable::find(const string& id) const
{
    return m_impl->find(id);
}

