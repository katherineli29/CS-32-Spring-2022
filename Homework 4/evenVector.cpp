void removeEven(vector<int>& v)
{
	for (vector<int>::iterator p = v.begin(); p != v.end(); p++) {
			if ((*p) % 2 == 0) {
				p = v.erase(p);
				p--;
			}
		}
}