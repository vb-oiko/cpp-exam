#include <iostream>
#include <list>
using namespace std;

class Date
{
private:
    int _day;
    int _month;
    int _year;

public:
    Date() {}
    Date(const int day, const int month, const int year)
    {
        _day = day;
        _month = month;
        _year = year;
    }

    ~Date() {}

    void setDay(const int day) { _day = day; }
    void setMonth(const int month) { _month = month; }
    void setYear(const int year) { _year = year; }

    int getDay() { return _day; }
    int getMonth() { return _month; }
    int getYear() { return _year; }

    string getDate()
    {
        return to_string(_day) + "/" + to_string(_month) + "/" + to_string(_year);
    }

    void printDate()
    {
        cout << this;
    }

    Date operator+=(int shift)
    {
        Date temp = *this;
        setYear(getYear() + shift);
        return temp;
    };

    bool operator==(Date &d)
    {
        return getDate() == d.getDate();
    }

    friend ostream &operator<<(ostream &out, Date &date)
    {
        out << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << endl;
        return out;
    }

    friend istream &operator>>(istream &in, Date &date)
    {
        int d, m, y;
        cout << "DATE | Enter day: ";
        in >> d;

        cout << "DATE | Enter month: ";
        in >> m;

        cout << "DATE | Enter year: ";
        in >> y;

        date.setDay(d);
        date.setMonth(m);
        date.setYear(y);

        return in;
    }
};

class Person
{
private:
    string _firstName;
    string _lastName;
    Date _birthDate;
    string _phoneNumber;

public:
    Person()
    {
        _firstName = " ";
        _lastName = " ";
        _birthDate = Date(0, 0, 0);
        _phoneNumber = " ";
    }
    Person(string fName, string lName, Date bDate, string pNumber)
    {
        _firstName = fName;
        _lastName = lName;
        _birthDate = bDate;
        _phoneNumber = pNumber;
    }

    ~Person() {}

    void setFirstName(string fName) { _firstName = fName; }
    void setLastName(string lName) { _lastName = lName; }
    void setPhoneNumber(string pNumber) { _phoneNumber = pNumber; }
    void setBirthDate(Date bDate) { _birthDate = bDate; }

    string getFirstName() { return _firstName; }
    string getLastName() { return _lastName; }
    string getPhoneNumber() { return _phoneNumber; }
    string getBirthDate() { return _birthDate.getDate(); }

    virtual void print() { cout << *this; }

    void printStr()
    {
        cout << _firstName << " " << _lastName << endl;
    }

    bool operator==(Person &p)
    {
        return getFirstName() == p.getFirstName() &&
               getLastName() == p.getLastName() &&
               getBirthDate() == p.getBirthDate() &&
               getPhoneNumber() == p.getPhoneNumber();
    }

    friend ostream &operator<<(ostream &out, Person &pers)
    {
        out << "\nPerson information: \n\t"
            << "Full name: " << pers.getFirstName() << " " << pers.getLastName() << "\n\t"
            << "Phone number: " << pers.getPhoneNumber() << "\n\t"
            << "Birth date: " << pers.getBirthDate() << endl;
        return out;
    }

    friend istream &operator>>(istream &in, Person &pers)
    {
        string fn, ln, pn;
        Date bd;

        cout << "Person | Enter first name: ";
        in >> fn;

        cout << "Person | Enter last name: ";
        in >> ln;

        cout << "Person | Enter phone number: ";
        in >> pn;

        cout << "Person | set birth date" << endl;
        in >> bd;

        pers.setFirstName(fn);
        pers.setLastName(ln);
        pers.setPhoneNumber(pn);
        pers.setBirthDate(bd);

        return in;
    }
};

class Student : public Person
{
private:
    string _group;
    int _course;
    int _mark;

public:
    Student() {}
    Student(string fName, string lName, Date bDate, string pNumber) : Person(fName, lName, bDate, pNumber) {}
    Student(string fName, string lName, Date bDate, string pNumber, string groupName, int courseNumber, int mark) : Person(fName, lName, bDate, pNumber)
    {
        _group = groupName;
        _course = courseNumber;
        _mark = mark;
    }

    ~Student() {}

    void setGroup(string groupName) { _group = groupName; }
    void setCourse(const int courseNumber) { _course = courseNumber; }
    void setMark(const int markValue) { _mark = markValue; }

    string getGroup() { return _group; }
    int getCourse() { return _course; }
    int getMark() { return _mark; }

    virtual void print()
    {
        cout << "\n\tSTUDENT PERSONAL INFORMATION: "
             << "\n First name: " << getFirstName()
             << "\n Last name: " << getLastName()
             << "\n Birth date: " << getBirthDate()
             << "\n Phone number: " << getPhoneNumber()
             << "\n Group: " << getGroup()
             << "\n Course: " << getCourse()
             << "\n Mark: " << getMark() << endl;
    }

    Student &operator++()
    {
        setCourse(getCourse() + 1);
        return *this;
    }

    Student operator++(int)
    {
        Student temp = *this;
        setCourse(getCourse() + 1);
        return temp;
    };

    bool operator<(Student &mark)
    {
        return getMark() < mark.getMark();
    }
};

class Employee : public Person
{
private:
    string _position;
    int _salary;
    int _experience;

public:
    Employee(string fName, string lName, Date bDate, string pNumber, string position, int salary, int experience) : Person(fName, lName, bDate, pNumber)
    {
        _position = position;
        _salary = salary;
        _experience = experience;
    }

    ~Employee() {}

    virtual void print()
    {
        cout << "EMPLOYEE PERSONAL INFORMATION: \n First name: " << getFirstName()
             << ",\n Last name: " << getLastName()
             << ",\n Birth date: " << getBirthDate()
             << ",\n Phone number: " << getPhoneNumber()
             << ",\n Position: " << _position
             << ",\n Salary: " << _salary
             << ",\n Experience: " << _experience << endl;
    }
};

class Department
{
private:
    string _name;
    int _size;
    Person **_peopleArray;

public:
    Department() {}
    Department(string name)
    {
        _name = name;
        _size = 0;
        _peopleArray = new Person *[_size];
    }
    ~Department()
    {
        delete (_peopleArray);
    }

    void setName(string name) { _name = name; }
    string getName() { return _name; }
    int getSize() { return _size; }

    void push(Person person)
    {
        _peopleArray[_size] = &person;
        _size++;
    }

    void pop()
    {
        delete _peopleArray[_size];
        _size--;
    }

    Person *getPersonByIndex(int index)
    {
        if (index >= _size || index < 0)
            throw "Index out of range";

        return _peopleArray[index];
    }

    void print()
    {
        cout << "Department Name: " << _name << endl;
        int length = _size;

        if (length == 0)
        {
            cout << "There are no people in this Department" << endl;
            return;
        }

        for (int i = 0; i < length; i++)
        {
            cout << "Member " << i + 1 << ": " << endl;
            cout << &_peopleArray[i] << endl;
        }
    }
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
T *mergeLists(T *listA, int lengthA, T *listB, int lengthB)
{
    T *mergedList = new T[lengthA + lengthB];
    int i = 0,
        j = 0,
        k = 0;

    while (i < lengthA && j < lengthB)
    {
        if (listA[i] < listB[j])
        {
            mergedList[k] = listA[i];
            i++;
        }
        else
        {
            mergedList[k] = listB[j];
            j++;
        }
        k++;
    }

    while (i < length1)
    {
        mergedList[k] = listA[i];
        i++;
        k++;
    }

    while (j < length2)
    {
        mergedList[k] = listB[j];
        j++;
        k++;
    }

    return mergedList;
}

int main()
{
    Date date = Date(1, 1, 2000);
    Person p1("Mikhailo", "Serdiuk", date, "123456789");
    cout << "Filed: " << p1 << &p1 << endl;
    date += 5;
    Person p2("Petro", "Kozachenko", date, "123456789");
    cout << "Filed: " << p2 << &p2 << endl;

    Student s1("Mikhailo", "Serdiuk", date, "0888888888", "IT", 1, 2);
    Student s2("Petro", "Kozachenko", date, "0888888888", "IT", 1, 3);
    cout << "If s1 and s2 are equal: " << ((s1 == s2) ? "yes" : "no") << endl;

    Student *stUpcast = &s1;
    std::cout << "Object is an instance of " << ((dynamic_cast<Person *>(stUpcast) != nullptr) ? "Person" : "another type") << endl;
    auto *stDowncast = (Student *)stUpcast;
    std::cout << "Object is an instance of " << ((dynamic_cast<Student *>(stDowncast) != nullptr) ? "Student" : "another type") << endl;

    Employee e1("Mikhailo", "Serdiuk", date, "0888888888", "IT", 1, 2);
    Employee e2("Petro", "Kozachenko", date, "0888888888", "IT", 1, 2);

    Department d1("Dep1");
    d1.push(p1);
    d1.push(p2);

    d1.getPersonByIndex(0)->printStr();
    d1.getPersonByIndex(1)->printStr();

    d1.print();

    cout << "\n\n\n\n"
         << endl;

    return 0;
}
