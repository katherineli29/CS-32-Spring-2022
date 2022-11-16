#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>

using namespace std;

int findOpen(const vector<Point>& vec, const Point& goal)
{
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].r == goal.r && vec[i].c == goal.c)
            return i;
    }
    return -1;
}

//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
    : Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
    // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if (!b.placeShip(Point(k, 0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
    bool /* shotHit */, bool /* shipDestroyed */,
    int /* shipId */)
{
    // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
    // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

// TODO:  You need to replace this with a real class declaration and
//        implementation.
class HumanPlayer : public Player
{
public:
    HumanPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);

    virtual bool isHuman() const { return true; }
private:
};

HumanPlayer::HumanPlayer(string nm, const Game& g)
    : Player(nm, g)
{}

bool HumanPlayer::placeShips(Board& b)
{
    cout << name() << " the Human must place " << game().nShips() << " ships." << endl;

    for (int k = 0; k < game().nShips(); k++) {
        b.display(false);

        string input;
        Direction dir;

        while (!(input == "h" || input == "v")) {
            cout << "Enter h or v for direction of aircraft carrier (length 5): ";
            input = "";
            cin >> input;
            cin.ignore(10000, '\n');

            if (input == "h") {
                dir = HORIZONTAL;
            }
            else if (input == "v") {
                dir = VERTICAL;
            }
            else {
                cout << "Direction must be h or v." << endl;
            }
        }

        int r = -1;
        int c = -1;
        int nShipsPlaced = 0;

        while (!(r >= 0 && r < game().rows() && c >= 0 && c < game().cols())) {
            cout << "Enter row and column of leftmost cell (e.g., 3 5): ";
            if (!getLineWithTwoIntegers(r, c)) {
                cout << "You must enter two integers." << endl;
            }
            else if (!b.placeShip(Point(r, c), k, dir)) {
                cout << "The ship can not be placed there." << endl;
                r = -1;
                c = -1;
            }
        }
    }
    return true;
}

Point HumanPlayer::recommendAttack()
{
    cout << "Enter the row and column to attack (e.g., 3 5): ";

    int r, c;

    while(!(getLineWithTwoIntegers(r, c)))
    {
        cout << "You must enter two integers." << endl;
        cout << "Enter the row and column to attack (e.g., 3 5): ";
    }

    Point nextAttack(r, c);
    
    return nextAttack;
}

void HumanPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
    bool /* shotHit */, bool /* shipDestroyed */,
    int /* shipId */)
{
    // HumanPlayer doesn't need to record attack
}

void HumanPlayer::recordAttackByOpponent(Point /* p */)
{
    // HumanPlayer doesn't need to record opponent attack
}

//*********************************************************************
//  MediocrePlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
class MediocrePlayer : public Player
{
public:
    MediocrePlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
private:
    Point m_lastCellAttacked;

    int currentState;
    Point holder;
    vector<Point> openPoints;
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g) : Player(nm, g), m_lastCellAttacked(0, 0), currentState(1)
{
    for (int r = 0; r < game().rows(); r++) {
        for (int c = 0; c < game().cols(); c++) {
            openPoints.push_back(Point(r, c));
        }
    }
}

//auxiliary recursion
bool placeShipRecur(const Game& g, Board& b, int shipId) {
    if (shipId == -1) {
        return true;
    }

    for (int i = 0; i < g.rows(); i++) {
        for (int j = 0; j < g.cols(); j++) {

            if (b.placeShip(Point(i, j), shipId, VERTICAL)) { //here?
                if (placeShipRecur(g, b, shipId - 1)) {
                    return true;
                }
                else {
                    b.unplaceShip(Point(i, j), shipId, VERTICAL);
                }
            }

            else if (b.placeShip(Point(i, j), shipId, HORIZONTAL)) { //here
                if (placeShipRecur(g, b, shipId - 1)) {
                    return true;
                }
                else {
                    b.unplaceShip(Point(i, j), shipId, HORIZONTAL);
                }
            }

        }
    }

    return false;
}

bool MediocrePlayer::placeShips(Board& b)
{
    b.clear();
    for (int i = 0; i < 50; i++) {
        b.block();
        if (placeShipRecur(game(), b, game().nShips() - 1)) { 
            b.unblock();
            return true;
        }
        b.clear();
    }
    b.clear();
    return false;
}

Point MediocrePlayer::recommendAttack()
{
    Point result;
    int randomizer;

    if (openPoints.empty()) {
        return Point(0, 0);
    }

    if (currentState == 1) {
        int temp = (int)openPoints.size();
        randomizer = randInt(temp);
        result = openPoints.at(randomizer);
    }
    else {
        bool areAllGone = true;

        for (int i = 0; i < 9; i++)
        {
            if (findOpen(openPoints, Point(holder.r - 4 + i, holder.c)) != -1 || findOpen(openPoints, Point(holder.r, holder.c - 4 + i)) != -1) {
                areAllGone = false;
                break;
            }
        }

        if (areAllGone) {
            currentState = 1;
            return recommendAttack();
        }

        do {
            if (randInt(2) == 0) {
                result = Point(holder.r, holder.c - 4 + randInt(9));
            }
            else {
                result = Point(holder.r - 4 + randInt(9), holder.c);
            }

            randomizer = findOpen(openPoints, result);
        } while (randomizer == -1);
    }

    openPoints.erase(openPoints.begin() + randomizer);
    return result;
}

void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
    if (!validShot) {
        currentState = 1;
        return;
    }

    if (currentState == 1) {
        if (!shotHit) {
            return;
        }

        if (shipDestroyed) {
            return;
        }

        if (shotHit && !shipDestroyed) {
            currentState = 2;
            holder = p;
            return;
        }
    }

    if (currentState == 2) {
        if (!shotHit) {
            return;
        }

        if (shipDestroyed) {
            currentState = 1;
            return;
        }

        if (shotHit && !shipDestroyed) {
            return;
        }
    }
}

void MediocrePlayer::recordAttackByOpponent(Point /* p */)
{
    // MedicorePlayer completely ignores what the opponent does
}

// Remember that Mediocre::placeShips(Board& b) must start by calling
// b.block(), and must call b.unblock() just before returning.

//*********************************************************************
//  GoodPlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
class GoodPlayer : public Player
{
public:
    GoodPlayer(string nm, const Game& g) : Player(nm, g), currentState(1) {
        for (int r = 0; r < g.rows(); r++)
            for (int c = 0; c < g.cols(); c++)
                openPoints.push_back(Point(r, c));
    }
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p) {  };
private:
    int currentState;
    vector<Point> openPoints;
    vector<Point> possibilities;

    void addToVect(Point p);
    bool placeShipsRecur(const Game& g, Board& b, int shipId);
};

int findInVect(const vector<Point>& vec, const Point& target) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].r == target.r && vec[i].c == target.c) {
            return i;
        }
    }
    return -1;
}

bool GoodPlayer::placeShips(Board& b) {
    for (int i = 0; i < 500; i++) {
        b.block();
        if (placeShipsRecur(game(), b, game().nShips() - 1)) {
            b.unblock();
            return true;
        }
        b.unblock();
    }

    b.unblock();
    return false;
}

bool GoodPlayer::placeShipsRecur(const Game& g, Board& b, int shipId) {
    if (shipId == -1) {
        return true;
    }

    for (int i = 0; i < g.rows(); i++) {
        for (int j = 0; j < g.cols(); j++) {

            if (b.placeShip(Point(i, j), shipId, VERTICAL)) { //here?
                if (placeShipRecur(g, b, shipId - 1)) {
                    return true;
                }
                else {
                    b.unplaceShip(Point(i, j), shipId, VERTICAL);
                }
            }

            else if (b.placeShip(Point(i, j), shipId, HORIZONTAL)) { //here
                if (placeShipRecur(g, b, shipId - 1)) {
                    return true;
                }
                else {
                    b.unplaceShip(Point(i, j), shipId, HORIZONTAL);
                }
            }

        }
    }

    return false;
}

Point GoodPlayer::recommendAttack()
{
    Point result;
    int randomizer;

    if (openPoints.empty()) {
        return Point(0, 0);
    }

    if (currentState == 1) {
        int nSize = (int)openPoints.size();

        randomizer = randInt(nSize);

        result = openPoints.at(randomizer);

        for (int i = 0; i < 30; i++) {
            if ((result.r + result.c) % 2) {
                int nSize = (int)openPoints.size();
                randomizer = randInt(nSize);
                result = openPoints.at(randomizer);
            }
            else {
                break;
            }
        }
    }
    else if (possibilities.size() == 0) {
        currentState = 1;
        return recommendAttack();
    }
    else {
        result = possibilities.back();
        possibilities.pop_back();

        randomizer = findInVect(openPoints, result);
    }

    openPoints.erase(openPoints.begin() + randomizer);
    return result;
}

void GoodPlayer::addToVect(Point p) {
    if (findInVect(openPoints, p) != -1)
    {
        possibilities.push_back(p);
    }
}

void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
    Point temp(0, 0);
    Point arr[4] = { Point(p.r, p.c - 1), Point(p.r, p.c + 1), Point(p.r - 1, p.c), Point(p.r + 1, p.c) };

    if (!validShot) {
        currentState = 1;
        return;
    }

    if (currentState == 1) {
        if (!shotHit) {
            return;
        }
        if (shipDestroyed) {
            return;
        }
        if (shotHit && !shipDestroyed) {
            currentState = 2;
            temp = p;

            addToVect(arr[0]);
            addToVect(arr[1]);
            addToVect(arr[2]);
            addToVect(arr[3]);
            return;
        }
    }

    if (currentState == 2) {

        if (!shotHit) {
            return;
        }
        if (shipDestroyed) {
            while (!possibilities.empty()) {
                possibilities.pop_back();
            }
            currentState = 1;
            return;
        }

        if (shotHit && !shipDestroyed) {
            if (temp.r > p.r && temp.c == p.c)
            {
                addToVect(arr[2]);
            }
            if (temp.r < p.r && temp.c == p.c) {
                addToVect(arr[3]);
            }
            if (temp.r == p.r && temp.c > p.c) {
                addToVect(arr[0]);
            }
            if (temp.r == p.r && temp.c < p.c) {
                addToVect(arr[1]);
            }
            return;
        }
    }
}

//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };

    int pos;
    for (pos = 0; pos != sizeof(types) / sizeof(types[0]) &&
        type != types[pos]; pos++)
        ;
    switch (pos)
    {
    case 0:  return new HumanPlayer(nm, g);
    case 1:  return new AwfulPlayer(nm, g);
    case 2:  return new MediocrePlayer(nm, g);
    case 3:  return new GoodPlayer(nm, g);
    default: return nullptr;
    }
}
