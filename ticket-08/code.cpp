#include <iostream>
using namespace std;

class Owner
{
private:
    string _firstName;
    string _lastName;
    string _phone;

public:
    Owner(string firstName, string lastName, string phone) : _firstName(firstName), _lastName(lastName), _phone(phone) {}
    Owner() : _firstName(""), _lastName(""), _phone("") {}
    ~Owner() {}

    void setFirstName(string firstName) { _firstName = firstName; }
    void setLastName(string lastName) { _lastName = lastName; }
    void setPhone(string phone) { _phone = phone; }

    string getFirstName() { return _firstName; }
    string getLastName() { return _lastName; }
    string getPhone() { return _phone; }

    virtual void print()
    {
        cout << "first name: " << _firstName
             << ", last name: " << _lastName
             << ", phone: " << _phone
             << endl;
    }

    virtual void printShort()
    {
        cout << _firstName << ", " << _lastName << ", " << _phone << endl;
    }

    bool operator==(Owner owner)
    {

        return _firstName == owner.getFirstName() && _lastName == owner.getLastName() && _phone == owner.getPhone();
    }

    friend ostream &operator<<(ostream &output, Owner &owner)
    {
        output << "first name: " << owner.getFirstName()
               << ", last name: " << owner.getFirstName()
               << ", phone: " << owner.getPhone();
        return output;
    }

    friend istream &operator>>(istream &input, Owner &owner)
    {
        string firstName;
        string lastName;
        string phone;

        cout << "please enter owner's first name: ";
        getline(cin, firstName);

        cout << "please enter owner's last name: ";
        getline(cin, lastName);

        cout << "please enter owner's phone: ";
        getline(cin, phone);

        owner.setFirstName(firstName);
        owner.setLastName(lastName);
        owner.setPhone(phone);

        return input;
    }
};

class Lot
{
private:
    Owner *_owner;
    string _city;
    double _lat;
    double _lng;

public:
    Lot(Owner *owner, string city, double lat, double lng) : _owner(owner), _city(city), _lat(lat), _lng(lng) {}
    ~Lot() {}

    void setOwner(Owner *owner) { _owner = owner; }
    void setCity(string city) { _city = city; }
    void setLat(double lat) { _lat = lat; }
    void setLng(double lng) { _lng = lng; }

    Owner *getOwner() { return _owner; }
    string getCity() { return _city; }
    double getLat() { return _lat; }
    double getLng() { return _lng; }

    virtual void print()
    {
        cout << "owner: " << _owner->getFirstName() << " " << _owner->getLastName()
             << ", city: " << _city
             << ", position: " << _lat << "," << _lng
             << endl;
    }

    virtual void printShort()
    {
        cout << _owner->getFirstName() << " " << _owner->getLastName() << ", " << _city << ", " << _lat << "," << _lng << endl;
    }

    friend ostream &operator<<(ostream &output, Lot &lot)
    {
        output << "owner: " << lot.getOwner()->getFirstName() << " " << lot.getOwner()->getLastName()
               << ", city: " << lot._city
               << ", position: " << lot._lat << "," << lot._lng;
        return output;
    }

    friend istream &operator>>(istream &input, Lot &lot)
    {
        string firstName;
        string lastName;
        string phone;
        string city;
        double lat;
        double lng;

        cout << "please enter owner's first name: ";
        getline(cin, firstName);

        cout << "please enter owner's last name: ";
        getline(cin, lastName);

        cout << "please enter owner's phone: ";
        getline(cin, phone);

        cout << "please enter lot's city: ";
        getline(cin, city);

        cout << "please enter lot's latitude: ";
        cin >> lat;

        cout << "please enter lot's longitude: ";
        cin >> lng;

        Owner *owner = new Owner(firstName, lastName, phone);

        lot.setOwner(owner);
        lot.setCity(city);
        lot.setLat(lat);
        lot.setLng(lng);

        return input;
    }
};

Lot *inputOwnerAndLot()
{
    string firstName;
    string lastName;
    string phone;
    string city;
    double lat;
    double lng;

    cout << "please enter owner's first name: ";
    getline(cin, firstName);

    cout << "please enter owner's last name: ";
    getline(cin, lastName);

    cout << "please enter owner's phone: ";
    getline(cin, phone);

    cout << "please enter lot's city: ";
    getline(cin, city);

    cout << "please enter lot's latitude: ";
    cin >> lat;

    cout << "please enter lot's longitude: ";
    cin >> lng;

    Owner *owner = new Owner(firstName, lastName, phone);
    Lot *lot = new Lot(owner, city, lat, lng);

    return lot;
}

class AgricultureLot : public Lot
{
private:
    string _soilType;
    string _lastReCultivationDate;

public:
    AgricultureLot(Owner *owner,
                   string city,
                   double lat,
                   double lng,
                   string soilType,
                   string lastReCultivationDate) : Lot(owner, city, lat, lng),
                                                   _soilType(soilType),
                                                   _lastReCultivationDate(lastReCultivationDate) {}
    ~AgricultureLot() {}

    virtual void print()
    {
        cout << "owner: " << getOwner()->getFirstName() << " " << getOwner()->getLastName()
             << ", city: " << getCity()
             << ", position: " << getLat() << "," << getLng()
             << ", soil type: " << _soilType
             << ", last re-cultivation date: " << _lastReCultivationDate
             << endl;
    }

    virtual void printShort()
    {
        cout << getOwner()->getFirstName()
             << " " << getOwner()->getLastName()
             << ", " << getCity()
             << ", " << getLat() << "," << getLng()
             << _soilType
             << _lastReCultivationDate
             << endl;
    }
};

class ConstructionLot : public Lot
{
private:
    bool _isUtilitiesAvailable;
    double _distanceToNearestCityKm;
    double _constructionCost;

public:
    ConstructionLot(Owner *owner,
                    string city,
                    double lat,
                    double lng,
                    bool isUtilitiesAvailable,
                    double distanceToNearestCityKm,
                    double constructionCost) : Lot(owner, city, lat, lng),
                                               _isUtilitiesAvailable(isUtilitiesAvailable),
                                               _distanceToNearestCityKm(distanceToNearestCityKm),
                                               _constructionCost(constructionCost) {}
    ~ConstructionLot() {}

    void setIsUtilitiesAvailable(bool val) { _isUtilitiesAvailable = val; }
    void setDistanceToNearestCityKm(double val) { _distanceToNearestCityKm = val; }
    void setConstructionCost(double val) { _constructionCost = val; }

    bool getIsUtilitiesAvailable() { return _isUtilitiesAvailable; }
    double getDistanceToNearestCityKm() { return _distanceToNearestCityKm; }
    double getConstructionCost() { return _constructionCost; }

    virtual void print()
    {
        cout << "owner: " << getOwner()->getFirstName() << " " << getOwner()->getLastName()
             << ", city: " << getCity()
             << ", position: " << getLat() << "," << getLng()
             << ", utilities availability: " << _isUtilitiesAvailable
             << ", distance to the nearest city: " << _distanceToNearestCityKm << "km"
             << ", cost of construction: " << _constructionCost << "USD"
             << endl;
    }

    virtual void printShort()
    {
        cout << getOwner()->getFirstName()
             << " " << getOwner()->getLastName()
             << ", " << getCity()
             << ", " << getLat() << "," << getLng()
             << _isUtilitiesAvailable
             << _distanceToNearestCityKm << "km"
             << _constructionCost
             << endl;
    }

    ConstructionLot &operator++()
    {
        setConstructionCost(getConstructionCost() + 1);
        return *this;
    }

    ConstructionLot operator++(int)
    {
        ConstructionLot temp = *this;
        setConstructionCost(getConstructionCost() + 1);
        return temp;
    };

    ConstructionLot operator+=(int n)
    {
        ConstructionLot temp = *this;
        setConstructionCost(getConstructionCost() + n);
        return temp;
    };

    bool operator<(ConstructionLot &lot)
    {
        return getConstructionCost() < lot.getConstructionCost();
    };
};

class City
{
private:
    string _name;
    Lot **_lots;
    int _capacity;
    int _size;

public:
    City(string name, int capacity) : _name(name), _capacity(capacity)
    {
        _size = 0;
        _lots = new Lot *[capacity];
    }
    ~City()
    {
        delete _lots;
    }

    void add(Lot *lot)
    {
        if (_size < _capacity)
        {
            _lots[_size] = lot;
            _size++;
            return;
        }

        throw "Cannot add a lot. No capacity.";
    }

    Lot *operator[](int index)
    {
        if (index >= _size)
        {
            throw "Array index out of bound, exiting";
        }
        return _lots[index];
    }

    void print()
    {
        cout << "city: " << _name << ", lots: [";
        for (int i = 0; i < _size; i++)
        {
            cout << _lots[i]->getCity();
            if (i != _size - 1)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

template <class T>
T **merge(T **a, int aLen, T **b, int bLen, bool (*isSmallerCallback)(T a, T b))
{
    T **result = new T *[aLen + bLen];
    int aInd = 0;
    int bInd = 0;
    int rInd = 0;

    while (aInd < aLen || bInd < bLen)
    {
        if (aInd == aLen)
        {
            result[rInd] = b[bInd];
            rInd++;
            bInd++;
            continue;
        }

        if (bInd == bLen)
        {
            result[rInd] = a[aInd];
            rInd++;
            aInd++;
            continue;
        }

        if (isSmallerCallback(*a[aInd], *b[bInd]))
        {
            result[rInd] = a[aInd];
            rInd++;
            aInd++;
            continue;
        }
        else
        {
            result[rInd] = b[bInd];
            rInd++;
            bInd++;
            continue;
        }
    }

    delete a;
    delete b;
    a = result;
};

template <class T>
bool isSmaller(T a, T b)
{
    return a < b;
}

template <class T>
T **merge(T **a, int aLen, T **b, int bLen)
{
    return merge(a, aLen, b, aLen, isSmaller);
}

int main()
{
    Lot *lot = inputOwnerAndLot();
    Owner *owner = lot->getOwner();
    lot->print();
    owner->print();

    Owner owner1("John", "Doe", "(456) 555 0909");
    Lot lot1(&owner1, "New York", 40.34534634, 34.235234534);

    Owner owner2("Jane", "Smith", "(856) 555 1234");
    Lot lot2(&owner1, "New Ark", 25.87976456, 67.56858685);

    owner1.print();
    owner2.print();
    lot1.print();
    lot2.print();

    AgricultureLot lot3(&owner1, "New Jersey", 43.2342664, 35.5685623, "sandy", "2021-09-11");
    lot3.print();
    ConstructionLot lot4(&owner2, "Denver", 34.1534123513, 55.34313451, true, 2.54, 230000);
    lot4.print();

    Owner owner3;
    cin >> owner3;
    cout << owner3;

    City city1("New York", 10);
    city1.add(&lot1);
    city1.add(&lot3);
    City city2("New Jersey", 10);
    city2.add(&lot2);
    city2.add(&lot4);
    city1.print();
    city2.print();

    city1[0]->print();
};