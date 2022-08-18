#include <iostream>
using namespace std;

class Cook
{
private:
    const char *firstName;
    const char *lastName;

public:
    Cook(const char fName[], const char lName[])
    {
        firstName = fName;
        lastName = lName;
    }

    Cook();

    void printFull()
    {
        std::cout << "First name: " << firstName << ", Last name: " << lastName << std::endl;
    }

    void printShort()
    {
        std::cout << firstName << lastName << std::endl;
    }

    char getFirstName()
    {
        return *firstName;
    }

    char getLastName()
    {
        return *lastName;
    }
};

class Dish
{
private:
    const char *name;
    int cost;
    Cook *cook;

public:
    Dish(const char dName[], int dCost, Cook *dCook)
    {
        name = dName;
        cost = dCost;
        cook = dCook;
    }

    Dish();

    virtual Dish operator+(int value);
    virtual Dish operator++(int value);

    virtual void printFull()
    {
        std::cout << "Dish name: " << name << ", Cost: " << cost << std::endl;
        std::cout << "Cook" << std::endl;
        cook->printFull();
    }

    virtual void printShort()
    {
        std::cout << name << " - " << cost << std::endl;
    }

    void incrementCost()
    {
        ++cost;
    }

    void increaseCost(int increaseOn)
    {
        cost += increaseOn;
    }

    char getName()
    {
        return *name;
    }

    int getCost()
    {
        return cost;
    }

    void setCost(int value)
    {
        cost = value;
    }

    Cook getCook()
    {
        return *cook;
    }
};

Dish Dish::operator+(int value)
{
    cost = cost + value;
    return *this;
}

Dish Dish::operator++(int value)
{
    cost = ++cost;
    return *this;
}

class ReadyDish : public Dish
{
private:
    int preparingTime;
    int isAvailable;

public:
    virtual Dish operator+(int value)
    {
        ReadyDish rd(*this);
        Dish::operator+(value);
        return rd;
    }

    ReadyDish(const char dName[], int dCost, Cook *dCook, int dPreparingTime, int dIsAvailable) : Dish(dName, dCost, dCook)
    {
        preparingTime = dPreparingTime;
        isAvailable = dIsAvailable;
    }

    int getPreparingTime()
    {
        return preparingTime;
    }

    int getIsAvailable()
    {
        return isAvailable;
    }

    bool isFirstDishPreparingTime(int secondDishPreparingTime)
    {
        if (preparingTime < secondDishPreparingTime)
            return true;
        else
            return false;
    }

    //    friend Dish operator+ (Dish, int);
};

class ReadyWitted : public Dish
{
private:
    int storageTime;
    int weight;

public:
    virtual Dish operator+(int value)
    {
        ReadyWitted rw(*this);
        Dish::operator+(value);
        return rw;
    }

    ReadyWitted(const char dName[], int dCost, Cook *dCook, int dStorageTime, int dWeight) : Dish(dName, dCost, dCook)
    {
        storageTime = dStorageTime;
        weight = dWeight;
    }

    int getStorageTime()
    {
        return storageTime;
    }

    int getWeight()
    {
        return weight;
    }
};

class PriceList
{
private:
    const char *date;
    int size;
    int indexInt = 0;
    Dish **dishes;

public:
    PriceList();

    PriceList(const char pDate[], int pSize)
    {
        date = pDate;
        size = pSize;
        dishes = new Dish *[pSize];
    }

    char getDate()
    {
        return *date;
    }

    void printPriceListByDate(const char *d)
    {
        int day, month, year;
        if (sscanf(d, "%d/%d/%d", &day, &month, &year) == 3)
        {
            printf("Dish price list on Date is %02d.%02d.%d\n", day, month, year);
            for (int i = 0; i < size; i++)
            {
                dishes[i]->printShort();
            }
        }
    }

    void addDishToPriceList(Dish *dish)
    {
        if (indexInt < size)
        {
            dishes[indexInt++] = dish;
        }
        else
        {
            printf("Price list full");
        }
    }
};

int main()
{
    Cook *cook = new Cook("Taras", "Box");
    Dish dish("Potato", 12, cook);
    dish.printFull();

    dish + 2;
    std::cout << "Potato's cost was changed: " << dish.getCost() << std::endl;

    dish++;
    std::cout << "Potato's cost was changed after increment: " << dish.getCost() << std::endl;

    ReadyDish *salad = new ReadyDish("Salad", 75, cook, 25, 0);
    ReadyDish *juice = new ReadyDish("Juice", 18, new Cook("Mishel", "King"), 35, 1);
    salad->printShort();
    juice->printShort();

    *salad + 13;
    std::cout << "Salad's cost was changed: " << salad->getCost() << std::endl;

    ReadyWitted *milk = new ReadyWitted("Milk", 50, new Cook("Cow", "White"), 2, 10);
    milk->printShort();

    bool isSaladFirstPreparingTime = salad->isFirstDishPreparingTime(juice->getPreparingTime());
    std::cout << "Salad is " << (isSaladFirstPreparingTime ? "first preparing time" : "not first preparing time") << std::endl;

    PriceList *priceListOn_18_7_2022 = new PriceList("18/07/2022", 2);
    priceListOn_18_7_2022->addDishToPriceList(salad);
    priceListOn_18_7_2022->addDishToPriceList(juice);
    priceListOn_18_7_2022->printPriceListByDate("18/07/2022");

    return 0;
}
