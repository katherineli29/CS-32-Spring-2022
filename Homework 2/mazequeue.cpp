//#include <iostream>
//#include <queue>
//using namespace std;
//
//class Coord
//{
//public:
//    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
//    int r() const { return m_row; }
//    int c() const { return m_col; }
//private:
//    int m_row;
//    int m_col;
//};
//
//bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
//    // Return true if there is a path from (sr,sc) to (er,ec)
//    // through the maze; return false otherwise
//    queue<Coord> s;
//
//    s.push(Coord(sr, sc));
//    maze[sr][sc] = '!';
//
//    while (!s.empty()) {
//        Coord temp = s.front();
//        s.pop();
//
//        int r = temp.r();
//        int c = temp.c();
//
//        if (r == er && c == ec) {
//            return true;
//        }
//
//        if (maze[r][c - 1] == '.') {
//            s.push(Coord(r, c - 1));
//            maze[r][c - 1] = '!';
//        }
//        if (maze[r - 1][c] == '.') {
//            s.push(Coord(r - 1, c));
//            maze[r - 1][c] = '!';
//        }
//        if (maze[r][c + 1] == '.') {
//            s.push(Coord(r, c + 1));
//            maze[r][c + 1] = '!';
//        }
//        if (maze[r + 1][c] == '.') {
//            s.push(Coord(r + 1, c));
//            maze[r + 1][c] = '!';
//        }
//    }
//
//    return false;
//}
//
//int main()
//{
//    char yk[10][10] = {
//                { 'X','X','X','X','X','X','X','X','X','X' },
//                { 'X','.','X','.','.','X','X','X','.','X' },
//                { 'X','.','X','.','X','X','X','X','.','X' },
//                { 'X','.','X','.','.','X','.','X','.','X' },
//                { 'X','.','X','X','.','.','.','.','.','X' },
//                { 'X','.','.','.','.','X','.','X','X','X' },
//                { 'X','.','X','X','.','X','.','X','.','X' },
//                { 'X','.','.','.','.','X','.','X','.','X' },
//                { 'X','.','X','.','.','X','.','.','.','X' },
//                { 'X','X','X','X','X','X','X','X','X','X' }
//    };
//
//    if (pathExists(yk, 1, 1, 8, 8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//
//    return 0;
//}