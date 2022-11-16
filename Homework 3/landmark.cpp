class Landmark {
public:
    Landmark(string n) : m_name(n) {}
    virtual ~Landmark() {}
    string name() const { return m_name; }
    virtual string color() const { return "yellow"; }
    virtual string icon() const = 0;
    virtual string type() const = 0;

private:
    string m_name;
};

class Hotel : public Landmark {
public:
    Hotel(string n) : Landmark(n) {}
    ~Hotel() { cout << "Destroying the hotel " << name() << "." << endl; }
    string icon() const { return "bed"; }
    string type() const { return "hotel"; }
};

class Restaurant : public Landmark {
public:
    Restaurant(string n, int s) : Landmark(n), m_seats(s) {}
    ~Restaurant() { cout << "Destroying the restaurant " << name() << "." << endl; }
    string icon() const { 
        if (m_seats < 40) {
            return "small knife/fork";
        }

        return "large knife/fork";
    }
    string type() const { return "restaurant"; }

private:
    int m_seats;
};

class Hospital : public Landmark {
public:
    Hospital(string n) : Landmark(n) {}
    ~Hospital() { cout << "Destroying the hospital " << name() << "." << endl; }
    string color() const { return "blue"; }
    string icon() const { return "H"; }
    string type() const { return "hospital"; }
};