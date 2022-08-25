#include <iostream>
using namespace std;

class ExhibitionCenter
{
private:
    string _name;
    string _street;
    int _houseNumber;

public:
    ExhibitionCenter(string name, string street, int houseNumber) : _name(name), _street(street), _houseNumber(houseNumber) {}
    ExhibitionCenter() : _name(""), _street(""), _houseNumber(0) {}
    ~ExhibitionCenter() {}

    void setName(string name) { _name = name; }
    void setStreet(string street) { _street = street; }
    void setHouseNumber(int houseNumber) { _houseNumber = houseNumber; }

    string getName() { return _name; }
    string getStreet() { return _street; }
    int getHouseNumber() { return _houseNumber; }

    virtual void print()
    {
        cout << "name: " << _name
             << ", street: " << _street
             << ", house number: " << _houseNumber
             << endl;
    }

    virtual void printShort()
    {
        cout << _name << ", " << _street << ", " << _houseNumber << endl;
    }

    bool operator==(ExhibitionCenter center)
    {

        return _name == center.getName() && _street == center.getStreet() && _houseNumber == center.getHouseNumber();
    }

    friend ostream &operator<<(ostream &output, ExhibitionCenter &center)
    {
        output << "name: " << center.getName()
               << ", street: " << center.getStreet()
               << ", house number: " << center.getHouseNumber();
        return output;
    }

    friend istream &operator>>(istream &input, ExhibitionCenter &center)
    {
        string name;
        string street;
        int houseNumber;

        cout << "please enter exhibition center name: ";
        getline(cin, name);

        cout << "please enter exhibition center street: ";
        getline(cin, street);
        cin.ignore();

        cout << "please enter exhibition center house number: ";
        cin >> houseNumber;

        center.setName(name);
        center.setStreet(street);
        center.setHouseNumber(houseNumber);

        return input;
    }
};

class Showpiece
{
private:
    int _id;
    string _name;
    ExhibitionCenter *_exhibitionCenter;

public:
    Showpiece(int id, string name, ExhibitionCenter *exhibitionCenter) : _id(id), _name(name), _exhibitionCenter(exhibitionCenter) {}
    Showpiece() : _id(0), _name(""), _exhibitionCenter(NULL) {}
    ~Showpiece(){};

    void setId(int id) { _id = id; }
    void setName(string name) { _name = name; }
    void setExhibitionCenter(ExhibitionCenter *exhibitionCenter) { _exhibitionCenter = exhibitionCenter; }

    int getId() { return _id; }
    string getName() { return _name; }
    ExhibitionCenter *getExhibitionCenter() { return _exhibitionCenter; }

    virtual void print()
    {
        cout << "id: " << _id
             << ", name: " << _name
             << ", exhibition center: " << _exhibitionCenter->getName()
             << endl;
    }

    virtual void printShort()
    {
        cout << _id << ", " << _name << ", " << _exhibitionCenter->getName() << endl;
    }

    friend ostream &operator<<(ostream &output, Showpiece &piece)
    {
        output << "id: " << piece.getId()
               << ", name: " << piece.getName()
               << ", exhibition center: " << piece.getExhibitionCenter()->getName();
        return output;
    }

    friend istream &operator>>(istream &input, Showpiece &piece)
    {
        string center_name;
        string street;
        int houseNumber;
        int id;
        string piece_name;

        cout << "please enter exhibition center name: ";
        getline(cin, center_name);

        cout << "please enter exhibition center street: ";
        getline(cin, street);
        cin.ignore();

        cout << "please enter exhibition center house number: ";
        cin >> houseNumber;

        cout << "please enter showpiece catalogue number: ";
        cin >> id;

        cout << "please enter showpiece name: ";
        getline(cin, piece_name);

        ExhibitionCenter *exhibitionCenter = new ExhibitionCenter(center_name, street, houseNumber);
        piece.setId(id);
        piece.setName(piece_name);
        piece.setExhibitionCenter(exhibitionCenter);

        return input;
    }
};

class HouseholdAppliance;

class FoodProduct : public Showpiece
{
private:
    int _bestBeforeDays;
    string _country;

public:
    FoodProduct(int id,
                string name,
                ExhibitionCenter *exhibitionCenter,
                int bestBeforeDays,
                string country) : Showpiece(id, name, exhibitionCenter),
                                  _bestBeforeDays(bestBeforeDays),
                                  _country(country) {}
    ~FoodProduct(){};

    void setBestBefore(int bestBeforeDays) { _bestBeforeDays = bestBeforeDays; }
    void setCountry(string country) { _country = country; }

    int getBestBefore() { return _bestBeforeDays; }
    string getCountry() { return _country; }

    FoodProduct &operator++()
    {
        setBestBefore(getBestBefore() + 1);
        return *this;
    }

    FoodProduct operator++(int)
    {
        FoodProduct temp = *this;
        setBestBefore(getBestBefore() + 1);
        return temp;
    };

    operator HouseholdAppliance();
};

class HouseholdAppliance : public Showpiece
{
private:
    int _category;
    double _price;
    string _producerName;

public:
    HouseholdAppliance(int id,
                       string name,
                       ExhibitionCenter *exhibitionCenter,
                       int category,
                       double price,
                       string producerName) : Showpiece(id, name, exhibitionCenter),
                                              _category(category),
                                              _price(price),
                                              _producerName(producerName) {}
    ~HouseholdAppliance() {}

    void setCategory(int category) { _category = category; }
    void setPrice(double price) { _price = price; }
    void setProducerName(string producerName) { _producerName = producerName; }

    int getCategory() { return _category; }
    double getPrice() { return _price; }
    string getProducerName() { return _producerName; }

    bool operator<(HouseholdAppliance &product)
    {
        return getPrice() < product.getPrice();
    };

    operator FoodProduct();
};

HouseholdAppliance::operator FoodProduct()
{
    FoodProduct *fp = new FoodProduct(getId(), getName(), getExhibitionCenter(), 0, "");
    return *fp;
}

FoodProduct::operator HouseholdAppliance()
{
    HouseholdAppliance *ha = new HouseholdAppliance(getId(), getName(), getExhibitionCenter(), 0, 0, "");
    return *ha;
}

Showpiece *inputExhibitionCenterAndShowpiece()
{
    string center_name;
    string street;
    int houseNumber;
    int id;
    string piece_name;

    cout << "please enter exhibition center name: ";
    getline(cin, center_name);

    cout << "please enter exhibition center street name: ";
    getline(cin, street);

    cout << "please enter exhibition center house number: ";
    cin >> houseNumber;

    cout << "please enter showpiece catalog id: ";
    cin >> id;
    cin.ignore();

    cout << "please enter showpiece name: ";
    getline(cin, piece_name);

    ExhibitionCenter *exhibitionCenter = new ExhibitionCenter(center_name, street, houseNumber);
    Showpiece *showpiece = new Showpiece(id, piece_name, exhibitionCenter);

    return showpiece;
}

class Exhibition
{
private:
    string _name;
    Showpiece **_showpieces;
    int _capacity;
    int _size;

public:
    Exhibition(string name, int capacity) : _name(name), _capacity(capacity)
    {
        _size = 0;
        _showpieces = new Showpiece *[capacity];
    }
    ~Exhibition()
    {
        delete _showpieces;
    }

    void add(Showpiece *showpiece)
    {
        if (_size < _capacity)
        {
            _showpieces[_size] = showpiece;
            _size++;
            return;
        }

        throw "Cannot add a showpiece. No capacity.";
    }

    Showpiece *operator[](int index)
    {
        if (index >= _size || index < 0)
        {
            throw "Array index out of bound, exiting";
        }
        return _showpieces[index];
    }

    void print()
    {
        cout << "exhibition: " << _name << ", showpieces: [";
        for (int i = 0; i < _size; i++)
        {
            cout << _showpieces[i]->getName();
            if (i != _size - 1)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

template <class T>
T **removeAllAfter(T **arr, int n)
{
    T **result = new T[n];
    for (int i = 0; i < n; i++)
    {
        result[i] = arr[i];
    }

    delete arr;
    return result;
}

int main()
{
    Showpiece *showpiece = inputExhibitionCenterAndShowpiece();
    showpiece->print();
    showpiece->printShort();
    showpiece->getExhibitionCenter()->print();
    showpiece->getExhibitionCenter()->printShort();

    ExhibitionCenter center1("ACME EXPO", "Main St.", 1);
    Showpiece piece1(1, "Showpiece1", &center1);
    center1.print();
    center1.printShort();

    piece1.print();
    piece1.printShort();

    HouseholdAppliance piece2(2, "Mixer", &center1, 1, 2.50, "Philips");
    piece2.print();
    piece2.printShort();

    FoodProduct piece3(3, "Coca-Cola", &center1, 365, "USA");
    piece3.print();
    piece3.printShort();

    return 0;
}