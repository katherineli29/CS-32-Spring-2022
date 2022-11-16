void listAll(const Domain* d, string path) // two-parameter overload
{
    if (d->subdomains().size() == 0) {
        cout << path << endl;
    }
    else if (path.size() == 0) {
        const vector<Domain*>& subdomains = d->subdomains();
        for (int i = 0; i < subdomains.size(); i++) {
            listAll(subdomains[i], subdomains[i]->label());
        }
    } 
    else {
        const vector<Domain*>& subdomains = d->subdomains();
        for (int i = 0; i < subdomains.size(); i++) {
            listAll(subdomains[i], subdomains[i]->label() + "." + path);
        }
    }
}