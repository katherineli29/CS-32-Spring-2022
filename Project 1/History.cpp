#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows), m_cols(nCols) {
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			m_array[i][j] = 0;
		}
	}
}

bool History::record(int r, int c) {
	if (r > m_rows || r < 1 || c > m_cols || c < 1) {
		return false;
	}
	else {
		m_array[r - 1][c - 1]++;
	}
	return true;
}

void History::display() const {
	clearScreen();

	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			if (m_array[i][j] <= 0) {
				cout << ".";
			}
			else if (m_array[i][j] >= 1 && m_array[i][j] <= 26) {
				char temp = 'A' + (m_array[i][j] - 1);
				cout << temp;
			}
			else {
				cout << 'Z';
			}
		}
		cout << endl;
	}

	cout << endl;
}