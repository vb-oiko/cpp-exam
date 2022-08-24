#include <iostream>
using namespace std;

class Manufacturer
{
private:
    string name;
    string address;
    string phone;
    int warrantyPeriodDays;

public:
    Manufacturer(string n, string a, string p, int w) : name(n), address(a), phone(p), warrantyPeriodDays(w){};
    ~Manufacturer() {}

    void setName(const string n) { name = n; }
    void setAddress(const string a) { address = a; }
    void setPhone(const string p) { phone = p; }
    void setWarrantyPeriodDays(const int w) { warrantyPeriodDays = w; }

    string getName() { return name; }
    string getAddress() { return address; }
    string getPhone() { return phone; }
    int getWarrantyPeriodDays() { return warrantyPeriodDays; }

    virtual void print()
    {
        cout << "name: " << name
             << ", address: " << address
             << ", phone: " << phone
             << "warranty: " << warrantyPeriodDays << " days"
             << endl;
    }

    virtual void printShort()
    {
        cout << name << ", " << address << ", " << phone << ", " << warrantyPeriodDays << endl;
    }

    bool operator==(Manufacturer &m)
    {
        return name == m.getName() &&
               address == m.getAddress() &&
               phone == m.getPhone() &&
               warrantyPeriodDays == m.getWarrantyPeriodDays();
    };
};

class Sku
{
private:
    string name;
    double price;
    Manufacturer *manufacturer;

public:
    Sku(string n, double p, Manufacturer *m) : name(n), price(p), manufacturer(m) {}
    ~Sku() {}

    void setName(const string n) { name = n; }
    void setPrice(const double p) { price = p; }
    void setManufacturer(Manufacturer *m) { manufacturer = m; }

    string getName() { return name; }
    double getPrice() { return price; }
    Manufacturer *getManufacturer() { return manufacturer; }

    virtual void print()
    {
        cout << "name: " << name
             << ", price: " << price
             << ", manufacturer: " << manufacturer->getName()
             << endl;
    }

    virtual void printShort()
    {
        cout << name << ", " << price << ", " << manufacturer->getName() << endl;
    }

    bool operator==(Sku &sku)
    {
        return name == sku.getName() &&
               price == sku.getPrice() &&
               manufacturer == sku.getManufacturer();
    };
};

class ProducedSku : public Sku
{
private:
    string productionDate;
    int qty;

public:
    ProducedSku(string n, double p, Manufacturer *m, string pd, int q) : Sku(n, p, m),
                                                                         productionDate(pd), qty(q) {}
    ~ProducedSku() {}

    void setProductionDate(const string pd) { productionDate = pd; }
    void setQty(const int q) { qty = q; }

    string getProductionDate() { return productionDate; }
    int getQty() { return qty; }

    void print()
    {
        cout << "produced sku: "
             << "name: " << getName()
             << ", price: " << getPrice()
             << ", manufacturer: " << getManufacturer()->getName()
             << ", production date: " << productionDate
             << ", quantity: " << qty
             << endl;
    }

    ProducedSku &operator++()
    {
        setQty(getQty() + 1);
        return *this;
    }

    ProducedSku operator++(int)
    {
        ProducedSku temp = *this;
        setQty(getQty() + 1);
        return temp;
    };

    ProducedSku operator+=(int n)
    {
        ProducedSku temp = *this;
        setQty(getQty() + n);
        return temp;
    };

    bool operator<(ProducedSku &sku)
    {
        return getQty() < sku.getQty();
    };
};

class SoldSku : public ProducedSku
{
private:
    string lotId;
    string saleDate;
    int lotQty;

public:
    SoldSku(string n, double p, Manufacturer *m, string pd, int q, int id, string s, int lq) : ProducedSku(n, p, m, pd, q),
                                                                                               saleDate(s), lotQty(lq)
    {
        lotId = getProductionDate() + to_string(id);
    }
    ~SoldSku() {}

    void setLotId(const int id) { lotId = getProductionDate() + to_string(id); }
    void setSaleDate(const string pd) { saleDate = pd; }
    void setLotQty(const int q) { lotQty = q; }

    string getLotId() { return lotId; }
    string getSaleDate() { return saleDate; }
    int getLotQty() { return lotQty; }

    void print()
    {
        cout << "sold sku: "
             << "name: " << getName()
             << ", price: " << getPrice()
             << ", manufacturer: " << getManufacturer()->getName()
             << ", production date: " << getProductionDate()
             << ", quantity: " << getQty()
             << ", lot id: " << lotId
             << ", sale date: " << saleDate
             << ", lot qty: " << lotQty
             << endl;
    }
};

class Storage
{
private:
    int id;
    int capacity;
    int size;
    Sku **skus;

public:
    Storage(int i, int c) : id(i), capacity(c)
    {
        size = 0;
        skus = new Sku *[c];
    };

    ~Storage()
    {
        delete (skus);
    }

    int getId() { return id; }
    int getSize() { return size; }

    void add(Sku *sku)
    {
        if (size < capacity)
        {
            skus[size] = sku;
            size++;
            return;
        }

        throw "Sku adding failed. Storage is full.";
    }

    Sku *at(int i)
    {
        if (i >= 0 && i < size)
        {
            return skus[i];
        }

        throw "Index out of range.";
    }
};

template <class T>
bool isFirstNItemsEqual(T *a, T *b, int n)
{
    if (a->getSize() < n || b->getSize() < n)
    {
        throw "size(s) of the lists is less than the range of comparison";
    }

    for (int i = 0; i < n; i++)
    {
        if (a->at(i) == b->at(i))
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
};

template <class T>
bool isFirstNItemsEqual(T *a, T *b, int n, bool (*isEqual)(T *, T *))
{
    if (a->getSize() < n || b->getSize() < n)
    {
        throw "size(s) of the lists is less than the range of comparison";
    }

    for (int i = 0; i < n; i++)
    {
        if (isEqual(a, b))
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
};

template <class T>
bool isEqual(T a, T b)
{
    return a == b;
};

int main()
{
    Manufacturer acme("ACME Ltd", "Main St. 2", "836 555 5678", 365);
    acme.print();
    acme.printShort();

    Sku item1("Item 1", 2.50, &acme);
    item1.print();
    item1.printShort();

    ProducedSku item2("Item 2", 10.50, &acme, "01.02.2022", 1000);
    item2.print();
    item2.printShort();
    item2.print();

    SoldSku item3("Item 3", 7.25, &acme, "20.04.2022", 100, 1, "20.07.2022", 5);
    item3.print();
    item3.printShort();
    item3.print();

    item2++;
    item2.print();
    ++item2;
    item2.print();
    item2 += 15;
    item2.print();

    cout << item2.getQty() << " < " << item3.getQty() << " == " << (item2 < item3) << endl;

    Storage s1(1, 10);
    Storage s2(2, 10);
    Storage s3(3, 10);

    s1.add(&item1);
    s1.add(&item2);
    s1.add(&item3);

    s2.add(&item1);
    s2.add(&item2);
    s2.add(&item3);

    s3.add(&item1);
    s3.add(&item1);
    s3.add(&item3);

    cout << "First 3 items in storage1 and storage2 are equal == " << isFirstNItemsEqual(&s1, &s2, 3) << endl;
    cout << "First 3 items in storage1 and storage3 are equal == " << isFirstNItemsEqual(&s1, &s3, 3, &isEqual) << endl;
}
