void removeBad(list<Restaurant*>& li)
{
	for (list<Restaurant*>::iterator p = li.begin(); p != li.end(); p++) {
		if ((**p).stars() <= 2) {
			delete* p;
			p = li.erase(p);
			p--;
		}
	}
}