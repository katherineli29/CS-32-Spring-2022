void removeBad(vector<Restaurant*>& v)
{
	for (vector<Restaurant*>::iterator p = v.begin(); p != v.end(); p++) {
		if ((**p).stars() <= 2) {
			delete* p;
			p = v.erase(p);
			p--;
		}
	}
}