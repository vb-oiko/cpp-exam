#include <iostream>
using namespace std;

class Author {
private:
    string firstName;
    string lastName;
public:
    Author(const char fName[], const char lName[]) {
        firstName = fName;
        lastName = lName;
    }

    Author() {};

    ~Author() {
    };

    friend ostream &operator<<(ostream &, Author &);

    friend istream &operator>>(istream &, Author &);

    friend bool operator==(Author &, Author &);

    void printFull() {
        std::cout << "First name: " << firstName << ", Last name: " << lastName << std::endl;
    }

    void printShort() {
        std::cout << firstName << " " << lastName << std::endl;
    }

    string getFirstName() {
        return firstName;
    }

    void setFirstName(string aFirstName) {
        firstName = aFirstName;
    }

    string getLastName() {
        return lastName;
    }

    void setLastName(string aLastName) {
        lastName = aLastName;
    }
};


// This code fo string return only first char
//const char * getConvertedStringToChars(string str) {
//    return str.c_str();
//}

// This code fo string return only first char

//const char * getConvertedStringToChars(string str) {
//    char * writable = new char[str.size() + 1];
//    std::copy(str.begin(), str.end(), writable);
//    writable[str.size()] = '\0';
//    return writable;
//}

ostream &operator<<(ostream &output, Author &author) {
    output << "First Name : " << author.getFirstName() << " Last Name : " << author.getLastName();
    return output;
};

istream &operator>>(istream &input, Author &author) {
    string firstName;
    string lastName;
    input >> firstName >> lastName;
    author.setFirstName(firstName);
    author.setLastName(lastName);
    return input;
}

bool operator==(Author &author1, Author &author2) {
    return author1.getFirstName() == author2.getFirstName() && author1.getLastName() == author2.getLastName();
};

class Book {
private:
    const char *name;
    const char *code;
    Author *author;
    int year;
    int pages;
public:
    Book(const char bName[], const char bCode[], Author *bAuthor, int bYear, int bPages) {
        name = bName;
        code = bCode;
        author = bAuthor;
        year = bYear;
        pages = bPages;
    }

    Book();

    friend bool operator==(Book &, Book &);

    void printFull() {
        std::cout << "Name: " << name << ", Code: " << code << ", Year: " << year << ", Pages: " << pages << std::endl;
    }

    void printShort() {
        std::cout << name << " " << code << std::endl;
    }

    char getName() {
        return *name;
    }

    void setName(const char bName[]) {
        name = bName;
    }

    char getCode() {
        return *code;
    }

    void setCode(const char bCode[]) {
        code = bCode;
    }

    Author getAuthor() {
        return *author;
    }

    void setAuthor(Author *bAuthor) {
        author = bAuthor;
    }

    int getYear() {
        return year;
    }

    void setYear(int bYear) {
        year = bYear;
    }

    int getPages() {
        return pages;
    }

    void setPages(int bPages) {
        pages = bPages;
    }
};

bool operator==(Book &book1, Book &book2) {
    Author author1 = book1.getAuthor();
    Author author2 = book2.getAuthor();
    return book1.getName() == book2.getName() && book1.getYear() == book2.getYear()
           && book1.getCode() == book2.getCode() && book1.getPages() == book2.getPages() && author1 == author2;
};

class LibraryBook : public Book {
private:
    const char *inventoryNumber;
    bool available;
    double price;
public:
    LibraryBook(const char lName[], const char lCode[], Author *lAuthor, int lYear, int lPages,
                const char lInventoryNumber[], bool lAvailable, double lPrice) :
            Book(lName, lCode, lAuthor, lYear, lPages) {
        inventoryNumber = lInventoryNumber;
        available = lAvailable;
        price = lPrice;
    }

    LibraryBook();

    friend bool operator<(LibraryBook &, LibraryBook &);

    char getInventoryNumber() {
        return *inventoryNumber;
    }

    void setInventoryNumber(const char lInventoryNumber[]) {
        inventoryNumber = lInventoryNumber;
    }

    bool getAvailable() {
        return available;
    }

    void setAvailable(bool lAvailable) {
        available = lAvailable;
    }

    double getPrice() {
        return price;
    }

    void setPrice(double lPrice) {
        price = lPrice;
    }
};

bool operator<(LibraryBook &libraryBook1, LibraryBook &libraryBook2) {
    return libraryBook1.getPrice() < libraryBook2.getPrice();
};

class StoreBook : public Book {
private:
    double sellingPrice;
    int amount;
public:
    StoreBook(const char sName[], const char sCode[], Author *sAuthor, int sYear, int sPages,
              double sSellingPrice, int sAmount) :
            Book(sName, sCode, sAuthor, sYear, sPages) {
        sellingPrice = sSellingPrice;
        amount = sAmount;
    }

    StoreBook();

    friend StoreBook operator++(StoreBook &);

    friend StoreBook operator+(StoreBook &, int);

    double getSellingPrice() {
        return sellingPrice;
    }

    void setSellingPrice(double sSellingPrice) {
        sellingPrice = sSellingPrice;
    }

    int getAmount() {
        return amount;
    }

    void setAmount(int sAmount) {
        amount = sAmount;
    }
};

StoreBook operator++(StoreBook &storeBook) {
    storeBook.setAmount(storeBook.getAmount() + 1);
    return storeBook;
};

StoreBook operator+(StoreBook &storeBook, int amount) {
    storeBook.setAmount(storeBook.getAmount() + amount);
    return storeBook;
};

class Library {
private:
    int size;
    int indexInt = 0;
    LibraryBook **libraryBookArr;
public:

    Library(int gSize) {
        size = gSize;
        libraryBookArr = new LibraryBook *[gSize];
    }

    Library() {};

    LibraryBook ** getLibraryBookArr() {
        return libraryBookArr;
    };

    void addBook(LibraryBook *libraryBook) {
        if (indexInt < size) {
            libraryBookArr[indexInt++] = libraryBook;
        } else {
            printf("List full");
        }
    }

    LibraryBook *getLibraryBookByIndex(int index) {
        return libraryBookArr[index];
    }
};

void compare(LibraryBook **libraryBookArr1, LibraryBook **libraryBookArr2, int size1, int size2) {
    int i, j;
    for (i = 0, j = 0; i < size1 && j < size2; j++) {
        if (libraryBookArr1[i]->getInventoryNumber() == libraryBookArr2[j]->getInventoryNumber()) i++;
    }

    printf("Sub was %s\n", i < size1 ? "not found" : "found");
}

void compareEqualSubsequence(LibraryBook **libraryBookArr1, LibraryBook **libraryBookArr2) {
    int size1 = sizeof(libraryBookArr1) / sizeof(libraryBookArr1[0]);
    int size2 = sizeof(libraryBookArr2) / sizeof(libraryBookArr2[0]);
    if (size1 <= size2) compare(libraryBookArr1, libraryBookArr2, size1, size2);
    else compare(libraryBookArr2, libraryBookArr1, size2, size1);
}

int main() {
    Author author;

    cout << "Enter author : " << endl;
    cin >> author;
    cout << "Out author -> " << author << endl;

    StoreBook *storeBook = new StoreBook("Hadoop", "LS254", new Author("Tom", "White"), 2015, 789,
                                         185.7, 206);

    storeBook->printFull();

    ++*storeBook;

    storeBook->printFull();

    *storeBook + 200;

    storeBook->printFull();

    LibraryBook *axelBook = new LibraryBook("JavaScript", "POR287",
                                            new Author("Axel", "Rauschmayer"), 2022, 500,
                                            "PP254", false, 17.56);
    LibraryBook *flananganBook = new LibraryBook("JavaScript", "POR288",
                                                 new Author("David", "Flanagan"), 2019, 1789,
                                                 "PP2114", true, 19);

    std::cout << "Flanagan book is more expensive? " << (*axelBook < *flananganBook ? "Yes" : "No") <<  std::endl;

    Library *library1 = new Library(2);
    library1->addBook(axelBook);
    library1->addBook(flananganBook);

    Library *library2 = new Library(2);
    library2->addBook(axelBook);
    library2->addBook(flananganBook);

    LibraryBook *storiesBook = new LibraryBook("Stories", "P288",
                                               new Author("Mishel", "Port"), 2000, 2,
                                               "P8784", true, 1);

    library2->addBook(storiesBook);

    compareEqualSubsequence(library2->getLibraryBookArr(), library1->getLibraryBookArr());

    std::cout << "Axel and Stories books equals? " << (*axelBook == *storiesBook ? "Yes" : "No") <<  std::endl;
    return 0;
}
