#include <iostream>
using namespace std;

class Organizer
{

private:
    string _name;
    string _phone;
    string _address;
    int _hasExemption;

public:
    Organizer(string name,
              string phone,
              string address,
              int hasExemption) : _name(name),
                                  _phone(phone),
                                  _address(address),
                                  _hasExemption(hasExemption) {}

    Organizer() : _name(""), _phone(""), _address(""), _hasExemption(0) {}
    ~Organizer() {}

    string getName() { return _name; }
    string getPhone() { return _phone; }
    string getAddress() { return _address; }
    int getHasExemption() { return _hasExemption; }
    string getInfo() { return _name + ", " + _phone + ", " + _address + ", " + to_string(_hasExemption); }

    void setName(string name) { _name = name; }
    void setPhone(string phone) { _phone = phone; }
    void setAddress(string address) { _address = address; }
    void setHasExemption(int hasExemption) { _hasExemption = hasExemption; }

    virtual void print()
    {
        cout << "name: " << _name
             << ", phone: " << _phone
             << ", address: " << _address
             << ", has exemption: " << _hasExemption
             << endl;
    }

    virtual void printShort()
    {
        cout << _name << ", " << _phone << ", " << _address << _hasExemption << endl;
    }

    friend ostream &operator<<(ostream &output, Organizer &organizer)
    {
        output << "name: " << organizer.getName()
               << ", phone: " << organizer.getPhone()
               << ", address: " << organizer.getAddress()
               << ", has exemption: " << organizer.getHasExemption();
        return output;
    }

    friend istream &operator>>(istream &input, Organizer &organizer)
    {
        string name;
        string phone;
        string address;
        int hasExemption;

        cout << "please enter name: ";
        getline(cin, name);

        cout << "please enter phone: ";
        getline(cin, phone);

        cout << "please enter address: ";
        getline(cin, address);

        cout << "please enter whether the organizer has an exemption: ";
        cin >> hasExemption;

        organizer.setName(name);
        organizer.setPhone(phone);
        organizer.setAddress(address);
        organizer.setHasExemption(hasExemption);

        return input;
    }

    bool operator==(Organizer &organizer)
    {
        return _name == organizer.getName() &&
               _phone == organizer.getPhone() &&
               _address == organizer.getAddress() &&
               _hasExemption == organizer.getHasExemption();
    };
};

class WalkingExcursion;

class Excursion
{
private:
    string _name;
    Organizer *_organizer;
    int _price;
    int _hasExemption;

public:
    Excursion(string name,
              Organizer *organizer,
              int price,
              int hasExemption) : _name(name),
                                  _organizer(organizer),
                                  _price(price),
                                  _hasExemption(hasExemption) {}
    Excursion() : _name(""), _organizer(NULL), _price(0), _hasExemption(0) {}
    ~Excursion() {}

    string getName() { return _name; }
    Organizer *getOrganizer() { return _organizer; }
    int getPrice() { return _price; }
    int getHasExemption() { return _hasExemption; }

    void setName(string name) { _name = name; }
    void setOrganizer(Organizer *organizer) { _organizer = organizer; }
    void setPrice(int price) { _price = price; }
    void setHasExemption(int hasExemption) { _hasExemption = hasExemption; }

    virtual void print()
    {
        cout << "name: " << _name
             << ", organizer: " << _organizer->getName()
             << ", price: " << _price
             << ", has exemption: " << _hasExemption
             << endl;
    }

    virtual void printShort()
    {
        cout << _name << ", " << _organizer->getName() << ", " << _price << _hasExemption << endl;
    }

    friend ostream &operator<<(ostream &output, Excursion &excursion)
    {
        output << "name: " << excursion.getName()
               << ", organizer: " << excursion.getOrganizer()->getName()
               << ", price: " << excursion.getPrice()
               << ", has exemption: " << excursion.getHasExemption();
        return output;
    }

    friend istream &operator>>(istream &input, Excursion &excursion)
    {
        string organizer_name;
        string phone;
        string address;
        int organizer_hasExemption;
        string excursion_name;
        int price;
        int excursion_hasExemption;

        cout << "please enter organizer name: ";
        getline(cin, organizer_name);

        cout << "please enter organizer phone: ";
        getline(cin, phone);

        cout << "please enter organizer address: ";
        getline(cin, address);

        cout << "please enter whether the organizer has an exemption: ";
        cin >> organizer_hasExemption;

        Organizer *organizer = new Organizer(organizer_name, phone, address, organizer_hasExemption);

        cin.ignore();
        cout << "please enter excursion name: ";
        getline(cin, excursion_name);

        cout << "please enter excursion price: ";
        cin >> price;
        cin.ignore();

        cout << "please enter whether the excursion has an exemption: ";
        cin >> excursion_hasExemption;

        excursion.setName(excursion_name);
        excursion.setOrganizer(organizer);
        excursion.setPrice(price);
        excursion.setHasExemption(excursion_hasExemption);

        return input;
    }

    Excursion &operator++()
    {
        setPrice(getPrice() + 1);
        return *this;
    }

    Excursion operator++(int)
    {
        Excursion temp = *this;
        setPrice(getPrice() + 1);
        return temp;
    };

    Excursion operator+=(int n)
    {
        Excursion temp = *this;
        setPrice(getPrice() + n);
        return temp;
    };

    bool operator<(Excursion &excursion)
    {
        return getPrice() < excursion.getPrice();
    };

    bool operator==(Excursion &excursion)
    {
        return _name == excursion.getName() &&
               _organizer == excursion.getOrganizer() &&
               _price == excursion.getPrice() &&
               _hasExemption == excursion.getHasExemption();
    };

    operator WalkingExcursion();
};

class WalkingExcursion : public Excursion
{
private:
    double _routeLengthKm;
    string _category;
    string _destination;

public:
    WalkingExcursion(string name,
                     Organizer *organizer,
                     int price,
                     int hasExemption,
                     double routeLengthKm,
                     string category,
                     string destination) : Excursion(name, organizer, price, hasExemption),
                                           _routeLengthKm(routeLengthKm),
                                           _category(category),
                                           _destination(destination) {}
    WalkingExcursion() : Excursion("", NULL, 0, 0),
                         _routeLengthKm(0),
                         _category(""),
                         _destination("") {}

    ~WalkingExcursion() {}

    virtual void print()
    {
        cout << "name: " << getName()
             << ", organizer: " << getOrganizer()->getName()
             << ", price: " << getPrice()
             << ", has exemption: " << getHasExemption()
             << ", route length (km): " << _routeLengthKm
             << ", category: " << _category
             << ", destination: " << _destination
             << endl;
    }

    operator Excursion()
    {
        Excursion *e = new Excursion(getName(), getOrganizer(), getPrice(), getHasExemption());
        return *e;
    }
};

Excursion::operator WalkingExcursion()
{
    WalkingExcursion *w = new WalkingExcursion();
    w->setName(getName());
    w->setOrganizer(getOrganizer());
    w->setPrice(getPrice());
    w->setHasExemption(getHasExemption());

    return *w;
};

class BusExcursion : public Excursion
{
private:
    string _busType;
    int _groupSize;
    string _busNumber;

public:
    BusExcursion(string name,
                 Organizer *organizer,
                 int price,
                 int hasExemption,
                 string busType,
                 int groupSize,
                 string busNumber) : Excursion(name, organizer, price, hasExemption),
                                     _busType(busType),
                                     _groupSize(groupSize),
                                     _busNumber(busNumber) {}
    BusExcursion() : Excursion("", NULL, 0, 0),
                     _busType(""),
                     _groupSize(0),
                     _busNumber("") {}

    ~BusExcursion() {}

    virtual void print()
    {
        cout << "name: " << getName()
             << ", organizer: " << getOrganizer()->getName()
             << ", price: " << getPrice()
             << ", has exemption: " << getHasExemption()
             << ", bus type: " << _busType
             << ", group size: " << _groupSize
             << ", bus number: " << _busNumber
             << endl;
    }
};

class Tour
{
private:
    string _name;
    Excursion **_items;
    int _capacity;
    int _size;

public:
    Tour(string name, int capacity) : _name(name), _capacity(capacity)
    {
        _size = 0;
        _items = new Excursion *[capacity];
    }
    ~Tour()
    {
        delete _items;
    }

    void add(Excursion *excursion)
    {
        if (_size < _capacity)
        {
            _items[_size] = excursion;
            _size++;
            return;
        }

        throw "Cannot add an excursion. No capacity.";
    }

    Excursion *operator[](int index)
    {
        if (index >= _size || index < 0)
        {
            throw "Array index out of bound";
        }
        return _items[index];
    }

    void print()
    {
        cout << "tour: " << _name << ", excursions: [";
        for (int i = 0; i < _size; i++)
        {
            cout << _items[i]->getName();
            if (i != _size - 1)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

template <typename T>
void replaceElementByVals(T arr[], int len, T val1, T val2)
{

    for (int i = 0; i < len; i++)
    {
        if (arr[i] == val1)
        {
            arr[i] = val2;
        }
    }
}

int main()
{
    Organizer organizer;
    cin >> organizer;
    organizer.print();

    Excursion excursion;
    cin >> excursion;
    excursion.print();

    Organizer *organizer1 = new Organizer("Marvel Excursions", "(823) 555 4533", "Main St. 5", 0);

    Excursion *excursion1 = new WalkingExcursion("Underground Caves", organizer1, 29, 0, 5.5, "challenging", "Dragons Cave");
    excursion1->print();

    Excursion *excursion2 = new BusExcursion("Downttown Sightseeing", organizer1, 35, 0, "comfort", 40, "JKL 564");
    excursion2->print();

    return 0;
}