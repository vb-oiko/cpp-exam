#include <iostream>
using namespace std;

class Periodical;
class Book;
class Publisher
{
private:
    string _name;
    string _phone;
    string _address;

public:
    Publisher(string name,
              string phone,
              string address) : _name(name),
                                _phone(phone),
                                _address(address) {}
    Publisher() : _name(""), _phone(""), _address("") {}
    ~Publisher() {}

    string getName() { return _name; }
    string getPhone() { return _phone; }
    string getAddress() { return _address; }
    string getInfo() { return _name + ", " + _phone + ", " + _address; }

    void setName(string name) { _name = name; }
    void setPhone(string phone) { _phone = phone; }
    void setAddress(string address) { _address = address; }

    virtual void print()
    {
        cout << "name: " << _name
             << ", phone: " << _phone
             << ", address: " << _address
             << endl;
    }

    virtual void printShort()
    {
        cout << _name << ", " << _phone << ", " << _address << endl;
    }

    friend ostream &operator<<(ostream &output, Publisher &publisher)
    {
        output << "name: " << publisher.getName()
               << ", phone: " << publisher.getPhone()
               << ", address: " << publisher.getAddress();
        return output;
    }

    friend istream &operator>>(istream &input, Publisher &publisher)
    {
        string name;
        string phone;
        string address;

        cout << "please enter name: ";
        getline(cin, name);

        cout << "please enter phone: ";
        getline(cin, phone);

        cout << "please enter address: ";
        getline(cin, address);

        publisher.setName(name);
        publisher.setPhone(phone);
        publisher.setAddress(address);

        return input;
    }

    bool operator==(Publisher &publisher)
    {
        return _name == publisher.getName() &&
               _phone == publisher.getPhone() &&
               _address == publisher.getAddress();
    };
};

class Publication
{
private:
    string _name;
    Publisher *_publisher;
    double _price;
    int _pages;
    string _paperType;

public:
    Publication(string name,
                Publisher *publisher,
                double price,
                int pages,
                string paperType) : _name(name),
                                    _publisher(publisher),
                                    _price(price),
                                    _pages(pages),
                                    _paperType(paperType) {}
    Publication() : _name(""),
                    _publisher(NULL),
                    _price(0.0),
                    _pages(0),
                    _paperType("") {}
    ~Publication() {}

    string getName() { return _name; }
    Publisher *getPublisher() { return _publisher; }
    double getPrice() { return _price; }
    int getPages() { return _pages; }
    string getPaperType() { return _paperType; }

    void setName(string name) { _name = name; }
    void setPublisher(Publisher *publisher) { _publisher = publisher; }
    void setPrice(double price) { _price = price; }
    void setPages(int pages) { _pages = pages; }
    void setPaperType(string paperType) { _paperType = paperType; }

    virtual void print()
    {
        cout << "name: " << _name
             << ", publisher: " << _publisher->getInfo()
             << ", price: " << _price
             << ", pages: " << _pages
             << ", paperType: " << _paperType
             << endl;
    }

    virtual void printShort()
    {
        cout << _name << ", "
             << _publisher->getInfo() << ", "
             << _price << ", "
             << _pages << ", "
             << _paperType
             << endl;
    }

    friend ostream &operator<<(ostream &output, Publication &publication)
    {
        output << "name: " << publication.getName()
               << ", publisher: " << publication.getPublisher()->getInfo()
               << ", price: " << publication.getPrice()
               << ", pages: " << publication.getPages()
               << ", paperType: " << publication.getPaperType();

        return output;
    }

    friend istream &operator>>(istream &input, Publication &publication)
    {
        string publisher_name;
        string phone;
        string address;
        string publication_name;
        double price;
        int pages;
        string paperType;

        cout << "please enter publisher name: ";
        getline(cin, publisher_name);

        cout << "please enter publisher phone: ";
        getline(cin, phone);

        cout << "please enter publisher address: ";
        getline(cin, address);

        Publisher *publisher = new Publisher(publisher_name, phone, address);

        cout << "please enter publication name: ";
        getline(cin, publication_name);

        cout << "please enter publication price: ";
        cin >> price;

        cout << "please enter number of pages: ";
        cin >> pages;

        cin.ignore();
        cout << "please enter paper type: ";
        getline(cin, paperType);

        publication.setName(publication_name);
        publication.setPublisher(publisher);
        publication.setPrice(price);
        publication.setPages(pages);
        publication.setPaperType(paperType);

        return input;
    }

    Publication &operator++()
    {
        setPages(getPages() + 1);
        return *this;
    }

    Publication operator++(int)
    {
        Publication temp = *this;
        setPages(getPages() + 1);
        return temp;
    };

    bool operator==(Publication &publication)
    {
        return _name == publication.getName() &&
               _publisher == publication.getPublisher() &&
               _price == publication.getPrice() &&
               _pages == publication.getPages() &&
               _paperType == publication.getPaperType();
    };

    operator Periodical();
    operator Book();
};

class Periodical : public Publication
{
private:
    string _frequency;
    string _category;
    int _edition;

public:
    Periodical(string name,
               Publisher *publisher,
               double price,
               int pages,
               string paperType,
               string frequency,
               string category,
               int edition) : Publication(name, publisher, price, pages, paperType),
                              _frequency(frequency),
                              _category(category),
                              _edition(edition) {}
    Periodical() : Publication("", NULL, 0.0, 0, ""),
                   _frequency(""),
                   _category(""),
                   _edition(0) {}
    ~Periodical() {}

    string getFrequency() { return _frequency; }
    string getCategory() { return _category; }
    int getEdition() { return _edition; }

    void setFrequency(string frequency) { _frequency = frequency; }
    void setCategory(string category) { _category = category; }
    void setEdition(int edition) { _edition = edition; }

    virtual void print()
    {
        cout << "name: " << getName()
             << ", publisher: " << getPublisher()->getInfo()
             << ", price: " << getPrice()
             << ", pages: " << getPages()
             << ", paperType: " << getPaperType()
             << ", frequency: " << _frequency
             << ", category: " << _category
             << ", edition: " << _edition
             << endl;
    }

    virtual void printShort()
    {
        cout << getName() << ", "
             << getPublisher()->getInfo() << ", "
             << getPrice() << ", "
             << getPages() << ", "
             << getPaperType() << ", "
             << _frequency << ", "
             << _category << ", "
             << _edition
             << endl;
    }

    Periodical operator+=(int n)
    {
        Periodical temp = *this;
        setEdition(getEdition() + n);
        return temp;
    };

    bool operator<(Periodical &periodical)
    {
        return getEdition() < periodical.getEdition();
    };

    operator Publication()
    {
        Publication *p = new Publication(getName(), getPublisher(), getPrice(), getPages(), getPaperType());
        return *p;
    }
};

Publication::operator Periodical()
{
    Periodical *p = new Periodical();
    p->setName(getName());
    p->setPublisher(getPublisher());
    p->setPrice(getPrice());
    p->setPages(getPages());
    p->setPaperType(getPaperType());

    return *p;
};

class Book : public Publication
{
private:
    string _binding;
    string _format;

public:
    Book(string name,
         Publisher *publisher,
         double price,
         int pages,
         string paperType,
         string binding,
         string format) : Publication(name, publisher, price, pages, paperType),
                          _binding(binding),
                          _format(format) {}
    Book() : Publication("", NULL, 0.0, 0, ""),
             _binding(""),
             _format("") {}
    ~Book() {}

    string getBinding() { return _binding; }
    string getFormat() { return _format; }

    void setBinding(string binding) { _binding = binding; }
    void setFormat(string format) { _format = format; }

    virtual void print()
    {
        cout << "name: " << getName()
             << ", publisher: " << getPublisher()->getInfo()
             << ", price: " << getPrice()
             << ", pages: " << getPages()
             << ", paperType: " << getPaperType()
             << ", binding: " << _binding
             << ", format: " << _format
             << endl;
    }

    virtual void printShort()
    {
        cout << getName() << ", "
             << getPublisher()->getInfo() << ", "
             << getPrice() << ", "
             << getPages() << ", "
             << getPaperType() << ", "
             << _binding << ", "
             << _format
             << endl;
    }

    operator Publication()
    {
        Publication *p = new Publication(getName(), getPublisher(), getPrice(), getPages(), getPaperType());
        return *p;
    }
};

Publication::operator Book()
{
    Book *b = new Book();
    b->setName(getName());
    b->setPublisher(getPublisher());
    b->setPrice(getPrice());
    b->setPages(getPages());
    b->setPaperType(getPaperType());

    return *b;
};

class Directory
{
private:
    string _name;
    Publication **_items;
    int _capacity;
    int _size;

public:
    Directory(string name, int capacity) : _name(name), _capacity(capacity)
    {
        _size = 0;
        _items = new Publication *[capacity];
    }
    ~Directory()
    {
        delete _items;
    }

    void add(Publication *shop)
    {
        if (_size < _capacity)
        {
            _items[_size] = shop;
            _size++;
            return;
        }

        throw "Cannot add a publication. No capacity.";
    }

    Publication *operator[](int index)
    {
        if (index >= _size || index < 0)
        {
            throw "Array index out of bound";
        }
        return _items[index];
    }

    void print()
    {
        cout << "directory: " << _name << ", publications: [";
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
void removeMinElement(T arr[], int &len)
{
    if (len == 0)
    {
        return;
    }

    if (len == 1)
    {
        len = 0;
        return;
    }

    int minIdx = 0;

    for (int i = 0; i < len; i++)
    {
        if (arr[i] < arr[minIdx])
        {
            minIdx = i;
        }
    }

    for (int i = minIdx; i < len - 1; i++)
    {
        arr[i] < arr[+1];
    }

    len--;
}

int main()
{
    // Publisher publisher;
    // cin >> publisher;
    // publisher.print();

    // Publication publication;
    // cin >> publication;
    // publication.print();

    Publisher publisher1("Acme Publishing", "(234) 555 6745", "Main St. 5");

    Periodical periodical1("Wall Street Magazine", &publisher1, 2.59, 12, "recycled", "weekly", "stock news", 5500);
    periodical1.print();

    Book book1("How to do nothing", &publisher1, 19.99, 204, "glossy white", "hard", "A5");
    book1.print();

    return 0;
}