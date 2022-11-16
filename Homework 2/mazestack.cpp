//#include <stack>
//#include <iostream>
//using namespace std;
//
//class coord
//{
//public:
//    coord(int rr, int cc) : m_row(rr), m_col(cc) {}
//    int r() const { return m_row; }
//    int c() const { return m_col; }
//private:
//    int m_row;
//    int m_col;
//};
//
//bool pathexists(char maze[][10], int sr, int sc, int er, int ec){
//    // return true if there is a path from (sr,sc) to (er,ec)
//    // through the maze; return false otherwise
//    stack<coord> s;
//
//    s.push(coord(sr, sc));
//    maze[sr][sc] = '!';
//
//    while (!s.empty()) {
//        coord temp = s.top();
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
//            s.push(coord(r, c - 1));
//            maze[r][c - 1] = '!';
//        }
//        if (maze[r - 1][c] == '.') {
//            s.push(coord(r - 1, c));
//            maze[r - 1][c] = '!';
//        }
//        if (maze[r][c + 1] == '.') {
//            s.push(coord(r, c + 1));
//            maze[r][c + 1] = '!';
//        }
//        if (maze[r + 1][c] == '.') {
//            s.push(coord(r + 1, c));
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
//                { 'x','x','x','x','x','x','x','x','x','x' },
//                { 'x','.','x','.','.','x','x','.','.','x' },
//                { 'x','.','x','.','x','x','x','x','.','x' },
//                { 'x','.','x','.','.','x','.','x','.','x' },
//                { 'x','.','x','x','.','x','.','.','.','x' },
//                { 'x','.','x','.','.','x','.','x','.','x' },
//                { 'x','.','x','x','x','x','.','x','.','x' },
//                { 'x','.','x','.','.','x','x','x','.','x' },
//                { 'x','.','x','.','.','x','.','.','.','x' },
//                { 'x','x','x','x','x','x','x','x','x','x' }
//    };
//
//    if (pathexists(yk, 1, 1, 8, 1))
//        cout << "solvable!" << endl;
//    else
//        cout << "out of luck!" << endl;
//
//    return 0;
//}