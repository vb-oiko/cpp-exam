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
};

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
};

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

int main()
{
    // Showpiece *showpiece = inputExhibitionCenterAndShowpiece();
    // showpiece->print();
    // showpiece->printShort();
    // showpiece->getExhibitionCenter()->print();
    // showpiece->getExhibitionCenter()->printShort();

    return 0;
}