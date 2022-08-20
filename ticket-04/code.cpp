#include <iostream>
using namespace std;

class Notation
{
private:
    string digits;
    int base;

public:
    Notation(string aDigits, int aBase)
    {
        digits = aDigits;
        base = aBase;
    }

    ~Notation();

    void setDigits(string aDigits)
    {
        digits = aDigits;
    }

    string getDigits()
    {
        return digits;
    }

    void setBase(int aBase)
    {
        base = aBase;
    }

    int getBase()
    {
        return base;
    }

    virtual void printFull()
    {
        std::cout << "digits: " << digits << ", base: " << base << std::endl;
    }

    virtual void printShort()
    {
        std::cout << digits << " - " << base << std::endl;
    }
};

class Number
{
private:
    string value;
    Notation *notation;

public:
    Number(string aValue, Notation *aNotation)
    {
        value = aValue;
        notation = aNotation;
    }

    // ~Number();

    void setValue(string aValue)
    {
        value = aValue;
    }

    string getValue() const
    {
        return value;
    }

    void setNotation(Notation *aNotation)
    {
        notation = aNotation;
    }

    Notation *getNotation() const
    {
        return notation;
    }

    virtual void printFull()
    {
        std::cout << "value: " << value
                  << ", notation: { digits: " << notation->getDigits() << ", base: " << notation->getBase() << " }"
                  << std::endl;
    }

    virtual void printShort()
    {
        std::cout << value << std::endl;
    }

    virtual void print() {}
};

class Integer : public Number
{
private:
    bool hasSign;

public:
    Integer(string aValue, Notation *aNotation, bool aHasSign) : Number(aValue, aNotation)
    {
        hasSign = aHasSign;
    }

    void setHasSign(bool aHasSign)
    {
        hasSign = aHasSign;
    }

    bool getHasSign() const
    {
        return hasSign;
    }

    virtual void print()
    {
        std::cout << getValue() << std::endl;
    }

    int getIntValue() const
    {
        size_t pos;
        int value = stoi(getValue(), &pos, getNotation()->getBase());
        return value;
    }

    Integer operator+(Integer const &integer)
    {
        int sum = integer.getIntValue() + getIntValue();
        Integer result = Integer(to_string(sum), getNotation(), getHasSign());
        return result;
    };

    Integer &operator++()
    {
        int newValue = getIntValue() + 1;
        setValue(to_string(newValue));
        return *this;
    }

    Integer operator++(int)
    {
        Integer temp = *this;
        int newValue = getIntValue() + 1;
        setValue(to_string(newValue));
        return temp;
    };

    bool operator<(Integer const &integer)
    {
        return getIntValue() < integer.getIntValue();
    };

    bool operator==(Integer const &integer)
    {
        return getIntValue() == integer.getIntValue();
    };

    friend ostream &operator<<(ostream &output, const Integer &integer)
    {
        output << "value: " << integer.getValue() << ", notation base: " << integer.getNotation()->getBase();
        return output;
    }

    friend istream &operator>>(istream &input, Integer &integer)
    {
        string s;
        input >> s;
        integer.setValue(s);
        return input;
    }
};

enum Representation
{
    floating,
    fixed
};

class Real : public Number
{
private:
    bool hasSign;
    int precision;
    inline static Representation representation = floating;

public:
    Real(string aValue, Notation *aNotation, bool aHasSign, int aPrecision) : Number(aValue, aNotation)
    {
        hasSign = aHasSign;
        precision = aPrecision;
    }

    virtual void print()
    {
        std::cout << getValue() << " (Real)" << std::endl;
    }
};

int main()
{
    Notation *notation = new Notation("1 2 3 4 5 6 7 8 9 0", 10);
    notation->printFull();
    notation->printShort();

    Number *number = new Number("1112223", notation);
    number->printFull();
    number->printShort();

    Integer integer1 = Integer("123456", notation, false);
    Integer integer2 = Integer("654321", notation, false);

    Integer *integer = new Integer("8898989", notation, false);
    integer->print();

    Real *real = new Real("8898989", notation, false, 5);
    real->print();

    std::cout << integer->getIntValue() << std::endl;

    Integer integer3 = integer1 + integer2;

    integer1.print();
    integer2.print();
    integer3.print();

    integer1.printFull();
    integer2.printFull();
    integer3.printFull();

    integer1.print();
    integer1++.print();
    integer1.print();
    (++integer1).print();
    integer1.print();

    cout << (integer2 < integer1) << endl;
    cout << (integer1 < integer2) << endl;

    cout << (integer1 == integer2) << endl;
    cout << (integer1 == Integer("123456", notation, false)) << endl;

    cout << integer1 << endl;

    cin >> integer1;
    integer1.printFull();

    return 0;
}