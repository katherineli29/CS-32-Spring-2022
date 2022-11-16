#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>

using namespace std;

class BoardImpl
{
public:
    BoardImpl(const Game& g);
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;

private:
    // TODO:  Decide what private members you need.  Here's one that's likely
    //        to be useful:
    const Game& m_game;

    int rows;
    int cols;

    struct Ship {
        Ship() : m_length(0), m_symbol(0), m_name(""), timesHit(0) {};
        Ship(int nLength, char nSymbol, string nName) : m_length(nLength), m_symbol(nSymbol), m_name(nName), timesHit(0) {};

        int m_length;
        char m_symbol;
        string m_name;
        int timesHit;
    };

    vector<Ship> shipsPlaced;
    char grid[MAXROWS][MAXCOLS];
    int shipsDestroyed;
};

BoardImpl::BoardImpl(const Game& g)
    : m_game(g), shipsDestroyed(0)
{
    rows = m_game.rows();
    cols = m_game.cols();

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = '.';
        }
    }

    for (int i = 0; i < m_game.nShips(); i++) {
        shipsPlaced.push_back(Ship());
    }
}

void BoardImpl::clear()
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = '.';
        }
    }

    int size = shipsPlaced.size();
    for (int i = 0; i < size; i++) {
        shipsPlaced[i] = Ship();
    }

    shipsDestroyed = 0;
}

void BoardImpl::block()
{
    // TODO:  Replace this with code to block half of the cells on the board
    // change to !
    int half = (rows * cols)/2;
    int blocked = 0;

    while (blocked <= half) {
        //rand point, if not '#', then change and blocked++
        int r = randInt(rows);
        int c = randInt(cols);

        if (grid[r][c] != '#') {
            grid[r][c] = '#';
            blocked++;
        }
    }
}

void BoardImpl::unblock()
{
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '#') {
                grid[r][c] = '.';
            }
        }
    }
}

//return false if:
//1. The shipId is invalid
//2. The ship would be partly or fully outside the board.
//3. The ship would overlap an already - placed ship.
//4. The ship would overlap one or more positions that were blocked by a previous
//call to the block function.
//5. The ship with that ship ID has previously been placed on this Board and not
//yet been unplaced since its most recent placement.
bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    //invalid ship
    if (shipId >= m_game.nShips() || shipId < 0) {
        return false;
    }
    //partly or fully outside board
    if (topOrLeft.r > m_game.rows() || topOrLeft.c > m_game.cols() || topOrLeft.r < 0 || topOrLeft.c < 0)
        return false;

    if (dir == HORIZONTAL) {
        int left = topOrLeft.c;
        if (left + m_game.shipLength(shipId) > cols) {
            return false;
        }

        //overlap other ship or blocked
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            if (grid[topOrLeft.r][i + topOrLeft.c] != '.') {
                return false;
            }
        }
    }
    else if (dir == VERTICAL) {
        //partly or fully out of board
        int top = topOrLeft.r;
        if (top + m_game.shipLength(shipId) > rows) {
            return false;
        }

        //overlap other ship or blocked
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            if (grid[i + topOrLeft.r][topOrLeft.c] != '.') {
                return false;
            }
        }
    }
    //negative value
    if (topOrLeft.r < 0 || topOrLeft.c < 0) {
        return false;
    }
    //ship has been placed
    if (shipsPlaced[shipId].m_symbol == m_game.shipSymbol(shipId)) { //HERE
        return false;
    }

    //place ship
    if (dir == HORIZONTAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            grid[topOrLeft.r][i + topOrLeft.c] = m_game.shipSymbol(shipId);
        }
    }
    else {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            grid[i + topOrLeft.r][topOrLeft.c] = m_game.shipSymbol(shipId);
        }
    }

    //add to array
    int length = m_game.shipLength(shipId);
    char symbol = m_game.shipSymbol(shipId);
    string name = m_game.shipName(shipId);

    shipsPlaced[shipId] = (Ship(length, symbol, name));

    return true;
}

//This function attempts to remove the specified ship from the board, so the positions it
//occupied may be used to place other ships.
//This function returns false if the ship cannot be removed because :
//1. The shipId is invalid
//2. The board does not contain the entire ship at the indicated locations.
bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    if (shipId >= m_game.nShips() || shipId < 0) {
        return false;
    }
    //not on board
    if (grid[topOrLeft.r][topOrLeft.c] != m_game.shipSymbol(shipId)) {
        return false;
    }
    if (shipsPlaced[shipId].m_symbol == 0) {
        return false;
    }

    if (dir == HORIZONTAL) {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            grid[topOrLeft.r][i + topOrLeft.c] = '.';
        }
    }
    else {
        for (int i = 0; i < m_game.shipLength(shipId); i++) {
            grid[i + topOrLeft.r][topOrLeft.c] = '.';
        }
    }

    shipsPlaced[shipId] = Ship();

    return true;
}

void BoardImpl::display(bool shotsOnly) const
{
    int rows = m_game.rows();
    int cols = m_game.cols();
    int r, c;

    //print cols
    cout << "  ";
    for (int i = 0; i < cols; i++) {
        cout << i;
    }
    cout << endl;

    //print board
    for (r = 0; r < rows; r++) {
        cout << r << " ";
        for (c = 0; c < cols; c++) {
            if (!shotsOnly) {
                cout << grid[r][c];
            }
            else {
                if (grid[r][c] != 'X' && grid[r][c] != 'o') {
                    cout << ".";
                }
                else {
                    cout << grid[r][c];
                }
            }
        }
        cout << endl;
    }
}

//The function must return
//false if the attack is invalid(the attack point is outside of the board area, or an attack is
//made on a previously attacked location).The function returns true if the attack is valid,
//regardless of whether or not any ship is damaged.
bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    int shotRow = p.r;
    int shotCol = p.c;

    // invalid
    if (shotRow >= rows || shotRow < 0 || shotCol >= cols || shotCol < 0) {
        return false;
    }
 
    //shot a boat
    if (grid[shotRow][shotCol] != '.' && grid[shotRow][shotCol] != 'X' && grid[shotRow][shotCol] != 'o') {
        shotHit = true;

        //shipId change
        char hitSymbol = grid[shotRow][shotCol];
        for (int i = 0; i < m_game.nShips(); i++) {
            if (m_game.shipSymbol(i) == hitSymbol) {
                shipId = i;
            }
        }

        grid[shotRow][shotCol] = 'X';
        shipsPlaced[shipId].timesHit++;

        //check if destroyed
        if (shipsPlaced[shipId].timesHit >= m_game.shipLength(shipId)) {
            shipDestroyed = true;
            shipsDestroyed++;
        }
        else {
            shipDestroyed = false;
        }
    }
    else if (grid[shotRow][shotCol] == 'X' || grid[shotRow][shotCol] == 'o') {
        return false;
    }
    else { //did not shoot boat
        grid[shotRow][shotCol] = 'o';

        shotHit = false;
        shipDestroyed = false;
    }

    return true;
}

bool BoardImpl::allShipsDestroyed() const
{
    int nShipsPlaced = 0;
    for (int i = 0; i < shipsPlaced.size(); i++) {
        if (shipsPlaced[i].m_symbol != 0) {
            nShipsPlaced++;
        }
    }

    if (nShipsPlaced <= shipsDestroyed) {
        return true;
    }

    return false;
}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
