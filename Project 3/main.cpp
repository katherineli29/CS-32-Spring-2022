#include "Game.h"
#include "Player.h"
#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

bool addStandardShips(Game& g)
{
    return g.addShip(5, 'A', "aircraft carrier") &&
        g.addShip(4, 'B', "battleship") &&
        g.addShip(3, 'D', "destroyer") &&
        g.addShip(3, 'S', "submarine") &&
        g.addShip(2, 'P', "patrol boat");
}

struct TestShip {
    int id;
    int length;
    char symbol;
    std::string name;
};


void mediocre_player_tests() {
    Game g{ 10, 10 };
    addStandardShips(g);

    Player* m = createPlayer("mediocre", "test_mediocre", g);

    Board b(g);

    assert(!m->isHuman());

    const bool test_place_ships = true;
    const int MAX_PLACES = 100;
    int fail_count = 0;

    cerr << "total ships: " << g.nShips() << endl;

    if (test_place_ships) {
        for (int i = 0; i < MAX_PLACES; i++) {
            if (m->placeShips(b)) { 
                b.display(false);
                std::cerr << "Above is Board " << i
                    << ": Should contain the 5 standard Battleship vessels, "
                    "arranged randomly.\n\n";
                b.clear();
            }
            else {
                fail_count++;
                std::cerr << "Above is Board " << i
                    << ": Could not place all ships.\n\n ";
            }
        }

        std::cerr << "Could not place " << fail_count << " ships.\n";
    }
}

int main()
{
    //mediocre_player_tests();

    //good vs medicore
    int nMediocreWins = 0;

    for (int k = 1; k <= 10; k++)
    {
        cout << "============================= Game " << k
            << " =============================" << endl;
        Game g(10, 10);
        addStandardShips(g);
        Player* p1 = createPlayer("good", "Good Godfrey", g);
        Player* p2 = createPlayer("mediocre", "Mediocre Mimi", g);
        Player* winner = (k % 2 == 1 ?
            g.play(p1, p2, false) : g.play(p2, p1, false));
        if (winner == p2)
            nMediocreWins++;
        delete p1;
        delete p2;
    }
    cout << "The mediocre player won " << nMediocreWins << " out of "
        << 10 << " games." << endl;

    //provided
    const int NTRIALS = 10;

    cout << "Select one of these choices for an example of the game:" << endl;
    cout << "  1.  A mini-game between two mediocre players" << endl;
    cout << "  2.  A mediocre player against a human player" << endl;
    cout << "  3.  A " << NTRIALS
        << "-game match between a mediocre and an awful player, with no pauses"
        << endl;
    cout << "Enter your choice: ";
    string line;
    getline(cin, line);
    if (line.empty())
    {
        cout << "You did not enter a choice" << endl;
    }
    else if (line[0] == '1')
    {
        Game g(2, 3);
        g.addShip(2, 'R', "rowboat");
        Player* p1 = createPlayer("mediocre", "Popeye", g);
        Player* p2 = createPlayer("mediocre", "Bluto", g);
        cout << "This mini-game has one ship, a 2-segment rowboat." << endl;
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '2')
    {
        Game g(10, 10);
        addStandardShips(g);
        Player* p1 = createPlayer("mediocre", "Mediocre Midori", g);
        Player* p2 = createPlayer("human", "Shuman the Human", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '3')
    {
        int nMediocreWins = 0;

        for (int k = 1; k <= NTRIALS; k++)
        {
            cout << "============================= Game " << k
                << " =============================" << endl;
            Game g(10, 10);
            addStandardShips(g);
            Player* p1 = createPlayer("awful", "Awful Audrey", g);
            Player* p2 = createPlayer("mediocre", "Mediocre Mimi", g);
            Player* winner = (k % 2 == 1 ?
                g.play(p1, p2, false) : g.play(p2, p1, false));
            if (winner == p2)
                nMediocreWins++;
            delete p1;
            delete p2;
        }
        cout << "The mediocre player won " << nMediocreWins << " out of "
            << NTRIALS << " games." << endl;
        // We'd expect a mediocre player to win most of the games against
        // an awful player.  Similarly, a good player should outperform
        // a mediocre player.
    }
    else
    {
        cout << "That's not one of the choices." << endl;
    }
}
