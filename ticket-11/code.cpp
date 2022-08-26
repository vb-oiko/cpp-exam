#include <iostream>
using namespace std;

class Address
{
private:
    string _city;
    string _street;
    int _houseNumber;

public:
    Address(string city, string street, int houseNumber) : _city(city), _street(street), _houseNumber(houseNumber) {}
    Address() : _city(""), _street(""), _houseNumber(0) {}
    ~Address() {}

    void setCity(string city) { _city = city; }
    void setStreet(string street) { _street = street; }
    void setHouseNumber(int houseNumber) { _houseNumber = houseNumber; }

    string getCity() { return _city; }
    string getStreet() { return _street; }
    int getHouseNumber() { return _houseNumber; }

    string getAddress()
    {
        return _city + ", " + _street + ", " + to_string(_houseNumber);
    }

    virtual void print()
    {
        cout << "city: " << _city
             << ", street: " << _street
             << ", house number: " << _houseNumber
             << endl;
    }

    virtual void printShort()
    {
        cout << _city << ", " << _street << ", " << _houseNumber << endl;
    }

    bool operator==(Address &address)
    {
        return _city == address.getCity() &&
               _street == address.getStreet() &&
               _houseNumber == address.getHouseNumber();
    };

    friend ostream &operator<<(ostream &output, Address &address)
    {
        output << "city: " << address.getCity()
               << ", street: " << address.getStreet()
               << ", house number: " << address.getHouseNumber();
        return output;
    }

    friend istream &operator>>(istream &input, Address &address)
    {
        string city;
        string street;
        int houseNumber;

        cout << "please enter city: ";
        getline(cin, city);

        cout << "please enter street: ";
        getline(cin, street);
        cin.ignore();

        cout << "please enter house number: ";
        cin >> houseNumber;

        address.setCity(city);
        address.setStreet(street);
        address.setHouseNumber(houseNumber);

        return input;
    }
};

class Shop
{
private:
    string _name;
    string _phone;
    Address *_address;

public:
    Shop(string name, string phone, Address *address) : _name(name), _phone(phone), _address(address) {}
    Shop() : _name(""), _phone(""), _address(NULL) {}
    ~Shop() {}

    void setName(string name) { _name = name; }
    void setPhone(string phone) { _phone = phone; }
    void setAddress(Address *address) { _address = address; }

    string getName() { return _name; }
    string getPhone() { return _phone; }
    Address *getAddress() { return _address; }

    virtual void print()
    {
        cout << "name: " << _name
             << ", phone: " << _phone
             << ", address: " << _address->getAddress()
             << endl;
    }

    virtual void printShort()
    {
        cout << _name << ", " << _phone << ", " << _address->getAddress() << endl;
    }

    bool operator==(Shop &shop)
    {
        return _name == shop.getName() &&
               _phone == shop.getPhone() &&
               _address == shop.getAddress();
    };

    friend ostream &operator<<(ostream &output, Shop &shop)
    {
        output << "name: " << shop.getName()
               << ", phone: " << shop.getPhone()
               << ", house number: " << shop.getAddress()->getAddress();
        return output;
    }

    friend istream &operator>>(istream &input, Shop &shop)
    {
        string name;
        string phone;
        Address *address = new Address();

        cout << "please enter name: ";
        getline(cin, name);

        cout << "please enter phone: ";
        getline(cin, phone);
        cin.ignore();

        cout << "please enter address ";
        cin >> *address;

        shop.setName(name);
        shop.setPhone(phone);
        shop.setAddress(address);

        return input;
    }
};

class TailorShop : public Shop
{
private:
    int _serviceNumber;
    bool _isOnsiteAvailable;
    double _averageCost;

public:
    TailorShop(string name, string phone, Address *address, int serviceNumber,
               bool isOnsiteAvailable,
               double averageCost) : Shop(name, phone, address),
                                     _serviceNumber(serviceNumber),
                                     _isOnsiteAvailable(isOnsiteAvailable),
                                     _averageCost(averageCost) {}
    TailorShop() : _serviceNumber(0), _isOnsiteAvailable(false), _averageCost(0) {}
    ~TailorShop() {}

    int getServiceNumber() { return _serviceNumber; }
    bool getIsOnsiteAvailable() { return _isOnsiteAvailable; }
    double getAverageCost() { return _averageCost; }

    void setServiceNumber(int serviceNumber) { _serviceNumber = serviceNumber; }
    void setIsOnsiteAvailable(bool isOnsiteAvailable) { _isOnsiteAvailable = isOnsiteAvailable; }
    void setAverageCost(double averageCost) { _averageCost = averageCost; }

    TailorShop &operator++()
    {
        setServiceNumber(getServiceNumber() + 1);
        return *this;
    }

    TailorShop operator++(int)
    {
        TailorShop temp = *this;
        setServiceNumber(getServiceNumber() + 1);
        return temp;
    };

    virtual void print()
    {
        cout << "name: " << getName()
             << ", phone: " << getPhone()
             << ", address: " << getAddress()->getAddress()
             << ", number of services: " << _serviceNumber
             << ", onsite available: " << _isOnsiteAvailable
             << ", average cost: " << _averageCost
             << endl;
    }
};

class CarShop : public Shop
{
private:
    string _carClass;
    double _rating;
    int _staffNumber;

public:
    CarShop(string name, string phone, Address *address, string _carClass,
            double _rating,
            int _staffNumber) : Shop(name, phone, address),
                                _carClass(_carClass),
                                _rating(_rating),
                                _staffNumber(_staffNumber) {}
    CarShop() : _carClass(""), _rating(0), _staffNumber(0) {}
    ~CarShop() {}

    string getCarClass() { return _carClass; }
    double getRating() { return _rating; }
    int getStaffNumber() { return _staffNumber; }

    void setCarClass(string carClass) { _carClass = carClass; }
    void setRating(double rating) { _rating = rating; }
    void setStaffNumber(int staffNumber) { _staffNumber = staffNumber; }

    bool operator<(CarShop &carShop)
    {
        return getRating() < carShop.getRating();
    };

    virtual void print()
    {
        cout << "name: " << getName()
             << ", phone: " << getPhone()
             << ", address: " << getAddress()->getAddress()
             << ", car class: " << _carClass
             << ", rating: " << _rating
             << ", number of staff: " << _staffNumber
             << endl;
    }
};

class City
{
private:
    string _name;
    Shop **_shops;
    int _capacity;
    int _size;

public:
    City(string name, int capacity) : _name(name), _capacity(capacity)
    {
        _size = 0;
        _shops = new Shop *[capacity];
    }
    ~City()
    {
        delete _shops;
    }

    void add(Shop *shop)
    {
        if (_size < _capacity)
        {
            _shops[_size] = shop;
            _size++;
            return;
        }

        throw "Cannot add a shop. No capacity.";
    }

    Shop *operator[](int index)
    {
        if (index >= _size || index < 0)
        {
            throw "Array index out of bound";
        }
        return _shops[index];
    }

    void print()
    {
        cout << "city: " << _name << ", shops: [";
        for (int i = 0; i < _size; i++)
        {
            cout << _shops[i]->getName();
            if (i != _size - 1)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

template <typename T>
void swapMinAndMaxElements(T arr[], int len)
{
    if (len < 2)
    {
        return;
    }

    int minIdx = 0;
    int maxIdx = 0;

    for (int i = 0; i < len; i++)
    {
        if (arr[i] < arr[minIdx])
        {
            minIdx = i;
        }

        if (arr[i] > arr[maxIdx])
        {
            maxIdx = i;
        }
    }

    T temp = arr[minIdx];
    arr[minIdx] = arr[maxIdx];
    arr[maxIdx] = temp;
}

int main()
{
    string city;
    string street;
    int houseNumber;

    cout << "please enter city: ";
    getline(cin, city);

    cout << "please enter street name: ";
    getline(cin, street);

    cout << "please enter house number: ";
    cin >> houseNumber;

    Address address(city, street, houseNumber);
    address.print();
    address.printShort();

    Shop shop("Tire shop", "(345) 555 7867", &address);
    shop.print();
    shop.printShort();

    Address *address1 = new Address("Kyiv", "Peremohy Ave.", 30);
    Shop *shop1 = new TailorShop("Luxury Suits", "(044) 231 45 65", address1, 2, true, 35.80);
    Shop *shop2 = new CarShop("Top Auto", "(044) 231 45 78", address1, "business", 4.7, 15);

    shop1->print();
    shop2->print();

    int arr[] = {1, 2, 3};
    cout << "[" << arr[0] << ", " << arr[1] << ", " << arr[2] << "]" << endl;
    swapMinAndMaxElements(arr, 3);
    cout << "[" << arr[0] << ", " << arr[1] << ", " << arr[2] << "]" << endl;

    return 0;
}