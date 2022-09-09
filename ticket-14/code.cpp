#include <iostream>
#include <ctime>
#include <string>

using namespace std;

enum class Placement { Stock, Store, Port };

std::ostream& operator<< (std::ostream& os, Placement placement) {
    switch (placement) {
        case Placement::Stock : return os << "Stock" ;
        case Placement::Store: return os << "Store";
        case Placement::Port: return os << "Port";
    };
    return os << static_cast<std::int32_t>(placement);
}

class Location {
private:
    double lat;
    double lng;
    Placement type;
public:
    Location(double lLat, double lLng, Placement lType) {
        lat = lLat;
        lng = lLng;
        type = lType;
    }

    Location();

    void setLat(double lLat) {
        lat = lLat;
    }

    double getLat() {
        return lat;
    }

    void setLng(double lLng) {
        lng = lLng;
    }

    double getLng() {
        return lng;
    }

    void setType(Placement lType) {
        type = lType;
    }

    Placement getType() {
        return type;
    }

    virtual void print() {
        std::cout << "Latitude: " << lat << ", Longitude: " << lng << ", Placement type: " << type <<  std::endl;
    }

    void printShort() {
        std::cout << lat << ", " << lng << std::endl;
    }
};

class Goods {
private:
    string name;
    Location *location;
    double price;
    int amount;
public:
    Goods(string gName, Location *gLocation, double gPrice, int gAmount) {
        name = std::move(gName);
        location = gLocation;
        price = gPrice;
        amount = gAmount;
    }

    Goods(){};

    ~Goods() {
        delete[] location;
    };

    friend ostream &operator<<(ostream &, Goods &);
    friend istream &operator>>(istream &, Goods &);
    friend Goods operator++(Goods &);
    friend Goods operator+=(Goods &, int);
    friend bool operator<(Goods &, Goods &);
    friend bool operator==(Goods &, Goods &);

    void setName(string gName) {
        name = std::move(gName);
    }

    string getName() {
        return name;
    }

    void setLocation(Location *gLocation) {
        location = gLocation;
    }

    Location getLocation() {
        return *location;
    }

    void setPrice(double gPrice) {
        price = gPrice;
    }

    double getPrice() {
        return price;
    }

    void setAmount(int gAmount) {
        amount = gAmount;
    }

    int getAmount() {
        return amount;
    }

    void print() {
        std::cout << "Goods name: " << name << ", Price: " << price << ", Amount: " << amount << std::endl;
        location->print();
    }

    void printShort() {
        std::cout << name << ", " << price << ", " << amount << std::endl;
    }
};

ostream &operator<<(ostream &output, Goods &goods) {
    output << "Name : " << goods.getName() << " Price : " << goods.getPrice() << " Amount : " << goods.getAmount();
    return output;
};

istream &operator>>(istream &input, Goods &goods) {
    string name;
    double price;
    int amount;
    input >> name >> price >> amount;
    goods.setName(name);
    goods.setPrice(price);
    goods.setAmount(amount);
    return input;
}

Goods operator++(Goods &goods) {
    goods.setPrice(goods.getPrice() + 1);
    return goods;
};

Goods operator+=(Goods &goods, int amount) {
    goods.setAmount(goods.getAmount() + amount);
    return goods;
};

bool operator<(Goods &goods1, Goods &goods2) {
    return goods1.getPrice() < goods2.getPrice();
};

bool operator==(Goods &goods1, Goods &goods2) {
    return goods1.getPrice() == goods2.getPrice() && goods1.getAmount() == goods2.getAmount();
};

class ShortShelfLife : public Goods {
private:
    int optimalTemp;
    const char *deliveryDate;
    int expiration;
public:
    ShortShelfLife(const char sName[], Location *sLocation, double sPrice, int sAmount, int sOptimalTemp,
                   const char sDeliveryDate[], int sExpiration):
            Goods(sName, sLocation, sPrice, sAmount) {
        optimalTemp = sOptimalTemp;
        deliveryDate = sDeliveryDate;
        expiration = sExpiration;
    }

    ShortShelfLife();

    void setOptimalTemp(int sOptimalTemp) {
        optimalTemp = sOptimalTemp;
    }

    int getOptimalTemp() {
        return optimalTemp;
    }

    void setDeliveryDate(const char sDeliveryDate[]) {
        deliveryDate = sDeliveryDate;
    }

    string getDeliveryDate() {
        return deliveryDate;
    }

    void setExpiration(int sExpiration) {
        expiration = sExpiration;
    }

    int getExpiration() {
        return expiration;
    }

    bool attention() {
        int day, month, year;
        sscanf(deliveryDate, "%2d.%2d.%4d",
               &day,
               &month,
               &year);
        std::time_t t = std::time(0);   // get time now
        std::tm* now = std::localtime(&t);
        now->tm_mday -= expiration;
        mktime(now);

        bool isAttention = year > now->tm_year + 1900;
        if (!isAttention) {
            isAttention = month > now->tm_mon + 1;
        }
        if (!isAttention) {
            isAttention = day > now->tm_mday;
        }
        return isAttention;
    }
};

class Substance : public Goods {
private:
    int optimalTemp;
    int optimalHumidity;
    int maxDeviationTemp;
    int maxDeviationHumidity;
public:
    Substance(const char sName[], Location *sLocation, double sPrice, int sAmount, int sOptimalTemp,
              int sOptimalHumidity, int sMaxDeviationTemp, int sMaxDeviationHumidity):
            Goods(sName, sLocation, sPrice, sAmount) {
        optimalTemp = sOptimalTemp;
        optimalHumidity = sOptimalHumidity;
        maxDeviationTemp = sMaxDeviationTemp;
        maxDeviationHumidity = sMaxDeviationHumidity;
    }

    Substance();

    void setOptimalTemp(int sOptimalTemp) {
        optimalTemp = sOptimalTemp;
    }

    int getOptimalTemp() {
        return optimalTemp;
    }

    void setOptimalHumidity(int sOptimalHumidity) {
        optimalHumidity = sOptimalHumidity;
    }

    int getOptimalHumidity() {
        return optimalHumidity;
    }

    void setMaxDeviationTemp(int sMaxDeviationTemp) {
        maxDeviationTemp = sMaxDeviationTemp;
    }

    int getMaxDeviationTemp() {
        return maxDeviationTemp;
    }

    void setMaxDeviationHumidity(int sMaxDeviationHumidity) {
        maxDeviationHumidity = sMaxDeviationHumidity;
    }

    int getMaxDeviationHumidity() {
        return maxDeviationHumidity;
    }

    bool attention(int currentTemp, int currentHumidity) {
        bool isAttention = false;
        isAttention = !((optimalTemp - maxDeviationTemp) < currentTemp &&
                        (optimalTemp + maxDeviationTemp) > currentTemp);
        if (!isAttention) {
            isAttention = !((optimalHumidity - maxDeviationHumidity) < currentHumidity &&
                            (optimalHumidity + maxDeviationHumidity) > currentHumidity);
        }
        return isAttention;
    }
};

class Stock {
private:
    int size;
    int indexInt = 0;
    Goods **goodsArr;
public:

    Stock(int gSize) {
        size = gSize;
        goodsArr = new Goods*[gSize];
    }

    Stock();

    void addGoods(Goods *goods) {
        if (indexInt < size) {
            goodsArr[indexInt++] = goods;
        } else {
            printf("List full");
        }
    }

    Goods * getGoodsByIndex(int index) {
        return goodsArr[index];
    }

    void sort() {
        for(int i = 0; i < size; i++) {
            for(int j = i + 1; j < size; j++) {
                if (*goodsArr[j] < *goodsArr[i] ) {
                    std::swap(goodsArr[j], goodsArr[i]);
                }
            }
        }
    }
};

int main() {
    Goods goods;

    cout << "Enter goods : " << endl;
    cin >> goods;
    cout << "Out goods -> " << goods << endl;

    Location *meatLocation = new Location(25.34547, 17.849, Placement::Port);
    Location *milkLocation = new Location(7.1589, -5.3247, Placement::Store);

    ShortShelfLife *meat = new ShortShelfLife("meat", meatLocation, 17.85, 300,
                                              -2,"22.05.2022", 10);
    meat->print();

    ShortShelfLife *milk = new ShortShelfLife("milk", milkLocation, 2.5, 150,
                                              12,"20.10.2022", 7);

    milk->printShort();

    std::cout << "Product is expired? " << (meat->attention() ? "No" : "Yes") <<  std::endl;
    std::cout << "Product is expired? " << (milk->attention() ? "No" : "Yes") <<  std::endl;

    Substance *flour = new Substance("flour", meatLocation, 1.7, 500, 16,
                                     30, 10, 20);

    std::cout << "Substance is damaged? " << (flour->attention(20, 25) ? "Yes" : "No") <<  std::endl;
    std::cout << "Substance is damaged? " << (flour->attention(50, -30) ? "Yes" : "No") <<  std::endl;

    ++*milk;

    milk->printShort();

    *meat += 600;

    meat->printShort();

    std::cout << "Milk is more expensive than meat? " << (*milk < *meat ? "No" : "Yes") <<  std::endl;
    std::cout << "Milk and meat equals? " << (*milk == *meat ? "Yes" : "No") <<  std::endl;

    Stock *stock = new Stock(2);
    stock->addGoods(meat);
    stock->addGoods(milk);

    std::cout << "----------Print added-------------- " <<  std::endl;

    stock->getGoodsByIndex(0)->printShort();
    stock->getGoodsByIndex(1)->printShort();

    stock->sort();

    std::cout << "----------Print sorted-------------- " <<  std::endl;

    stock->getGoodsByIndex(0)->printShort();
    stock->getGoodsByIndex(1)->printShort();
    return 0;
}