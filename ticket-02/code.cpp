#include <iostream>
using namespace std;

class Coordinates
{
private:
    int latitude;
    int longitude;

public:
    Coordinates(int cLatitude, int cLongitude)
    {
        latitude = cLatitude;
        longitude = cLongitude;
    }

    Coordinates();

    void setLatitude(int lat)
    {
        latitude = lat;
    }

    int getLatitude()
    {
        return latitude;
    }

    void setLongitude(int lng)
    {
        longitude = lng;
    }

    int getLongitude()
    {
        return longitude;
    }

    void print()
    {
        std::cout << latitude << " - " << longitude << std::endl;
    }
};

class FormOfExistence
{
public:
    virtual void move() = 0;
};

class Plant : public FormOfExistence
{
private:
    Coordinates *coordinates;

public:
    Plant(Coordinates *aCoordinates)
    {
        coordinates = aCoordinates;
    }

    void setCoordinates(Coordinates *aCoordinates)
    {
        coordinates = aCoordinates;
    }

    Coordinates *getCoordinates()
    {
        return coordinates;
    }

    void move() override
    {
        coordinates->print();
    }
};

class Entity : public FormOfExistence
{
private:
    const char *name;
    int age;
    int isAlive = 1;
    Coordinates *coordinates;

public:
    Entity(const char aName[], int aAge, Coordinates *aCoordinates)
    {
        name = aName;
        age = aAge;
        coordinates = aCoordinates;
    }

    Entity();

    void setName(const char aName[])
    {
        name = aName;
    }

    const char *getName()
    {
        return name;
    }

    void setAge(int aAge)
    {
        age = aAge;
    }

    int getAge()
    {
        return age;
    }

    void setIsAlive(int num)
    {
        isAlive = num;
    }

    int getIsAlive()
    {
        return isAlive;
    }

    void setCoordinates(Coordinates *aCoordinates)
    {
        coordinates = aCoordinates;
    }

    Coordinates *getCoordinates()
    {
        return coordinates;
    }

    void move() override
    {
        coordinates->setLatitude(coordinates->getLatitude() + 1);
        coordinates->setLongitude(coordinates->getLongitude() + 1);
        coordinates->print();
    }

    virtual void printFull()
    {
        std::cout << "Entity name: " << name << ", Age: " << age
                  << ", Coordinates: { " << coordinates->getLatitude() << ", " << coordinates->getLongitude() << " }"
                  << std::endl;
    }

    virtual void printShort()
    {
        std::cout << name << " - " << age << std::endl;
    }
};

class Predator : public Entity
{
private:
    int maxAge = 0;

public:
    Predator(const char aName[], int aAge, Coordinates *aCoordinates) : Entity(aName, aAge, aCoordinates)
    {
    }

    friend Predator operator-(Predator &, int);

    friend Predator operator++(Predator &);

    friend Predator operator++(Predator &, int);

    void setMaxAge(int mAge)
    {
        maxAge = mAge;
    }

    int getMaxAge()
    {
        return maxAge;
    }

    void move() override
    {
        if (getAge() < getMaxAge())
        {
            getCoordinates()->setLatitude(getCoordinates()->getLatitude() + 1);
            getCoordinates()->setLongitude(getCoordinates()->getLongitude() + 1);
            if (getAge() < getMaxAge())
                setAge(getAge() + 1);
        }
        else if (getIsAlive())
            setIsAlive(0);
        getCoordinates()->print();
    }
};

Predator operator-(Predator &pred, int value)
{
    pred.setAge(pred.getAge() - value);
    return pred;
};

Predator operator++(Predator &pred)
{
    pred.setAge(pred.getAge() + 1);
    return pred;
};

Predator operator++(Predator &pred, int val)
{
    pred.setAge(pred.getAge() + 1);
    return pred;
};

class Booty : public Entity
{
private:
    int maxAge = 0;

public:
    Booty(const char aName[], int aAge, Coordinates *aCoordinates, int mAge) : Entity(aName, aAge, aCoordinates)
    {
        maxAge = mAge;
    }

    friend Booty operator-(Booty &, int);

    void setMaxAge(int mAge)
    {
        maxAge = mAge;
    }

    int getMaxAge()
    {
        return maxAge;
    }

    void move() override
    {
        if (getAge() < getMaxAge())
        {
            getCoordinates()->setLatitude(getCoordinates()->getLatitude() + 1);
            getCoordinates()->setLongitude(getCoordinates()->getLongitude() + 1);
            if (getAge() < getMaxAge())
                setAge(getAge() + 1);
        }
        else if (getIsAlive())
            setIsAlive(0);
        getCoordinates()->print();
    }
};

Booty operator-(Booty &booty, int value)
{
    booty.setAge(booty.getAge() - value);
    return booty;
};

Booty operator++(Booty &booty)
{
    booty.setAge(booty.getAge() + 1);
    return booty;
};

Booty operator++(Booty &booty, int val)
{
    booty.setAge(booty.getAge() + 1);
    return booty;
};

class Object : public FormOfExistence
{
private:
    const char *name;
    Coordinates *coordinates;

public:
    Object(const char aName[], Coordinates *aCoordinates)
    {
        name = aName;
        coordinates = aCoordinates;
    }

    friend bool operator==(const Object &, const Object &);

    void setName(const char aName[])
    {
        name = aName;
    }

    const char *getName() const
    {
        return name;
    }

    void setCoordinates(Coordinates *aCoordinates)
    {
        coordinates = aCoordinates;
    }

    Coordinates *getCoordinates() const
    {
        return coordinates;
    }

    void move() override
    {
        coordinates->setLatitude(coordinates->getLatitude() + 1);
        coordinates->setLongitude(coordinates->getLongitude() + 1);
        coordinates->print();
    }
};

bool operator==(const Object &obj1, const Object &obj2)
{
    bool equal = true;
    Coordinates *coordinates1 = obj1.getCoordinates();
    Coordinates *coordinates2 = obj2.getCoordinates();
    if (coordinates1->getLatitude() != coordinates2->getLatitude())
    {
        equal = false;
    }
    if (coordinates1->getLongitude() != coordinates2->getLongitude())
    {
        equal = false;
    }
    if (obj1.getName() != obj2.getName())
    {
        equal = false;
    }
    return equal;
};

class Field
{
private:
    int number;
    int size;
    int indexInt = 0;
    FormOfExistence **formOfExistences;

public:
    Field();

    Field(int num, int pSize)
    {
        number = num;
        size = pSize;
        formOfExistences = new FormOfExistence *[pSize];
    }

    int getNumber()
    {
        return number;
    }

    void addSomethingToFormOfExistenceList(FormOfExistence *formOfExistence)
    {
        if (indexInt < size)
        {
            formOfExistences[indexInt++] = formOfExistence;
        }
        else
        {
            printf("List full");
        }
    }

    FormOfExistence *getByIndex(int index)
    {
        return formOfExistences[index];
    }
};

int main()
{
    Coordinates *coordinates = new Coordinates(25, 34);
    Entity *entity = new Entity("Atom", 365, coordinates);
    entity->printFull();
    entity->getCoordinates()->print();

    Plant *plant = new Plant(new Coordinates(12, 21));
    plant->getCoordinates()->print();
    plant->move();
    plant->getCoordinates()->print();

    Predator *predator = new Predator("Wolf", 20, new Coordinates(17, 28));
    predator->setMaxAge(23);
    predator->printFull();
    predator->move();
    predator->move();
    predator->move();
    predator->move();
    predator->printFull();

    Predator pred("Eagle", 20, new Coordinates(100, 100));
    pred = pred - 10;
    pred.printFull();
    ++pred;
    pred.printFull();
    pred++;
    pred.printFull();

    Object obj1("House", new Coordinates(0, 0));
    Object obj2("Tree", new Coordinates(0, 0));
    Object obj3("House", new Coordinates(0, 0));

    std::cout << (obj1 == obj2 ? "They are equals" : "They are not equals") << std::endl;
    std::cout << (obj1 == obj3 ? "They are equals" : "They are not equals") << std::endl;

    Field *field = new Field(2, 2);
    field->addSomethingToFormOfExistenceList(predator);
    field->addSomethingToFormOfExistenceList(&pred);

    Predator *c = dynamic_cast<Predator *>(field->getByIndex(1));
    c->printShort();

    return 0;
}
