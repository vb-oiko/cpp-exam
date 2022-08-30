#include <iostream>
using namespace std;

class Position {
private:
    char x;
    int y;
public:
    Position(char X, int Y) {
        x = X;
        y = Y;
    }

    Position() {
        x = 'A';
        y = 1;
    }

    friend bool operator==(Position &, Position &);
    friend ostream &operator<<(ostream &, Position &);
    friend istream &operator>>(istream &, Position &);

    void setX(char X) {
        x = X;
    }

    char getX() {
        return x;
    }

    void setY(int Y) {
        y = Y;
    }

    int getY() {
        return y;
    }

    virtual void print() {
        std::cout << "Position: " << x << y << std::endl;
    }

    void printShort() {
        std::cout << x << y << std::endl;
    }
};

ostream &operator<<(ostream &output, Position &position) {
    output << "Y : " << position.getY() << " X : " << position.getX();
    return output;
};

istream &operator>>(istream &input, Position &position) {
    char x;
    int y;
    input >> x >> y;
    position.setY(y);
    position.setX(x);
    return input;
}

bool operator==(Position &position1, Position &position2) {
    bool equal = true;
    if (position1.getX() != position2.getX()) {
        equal = false;
    }
    if (position1.getY() != position2.getY()) {
        equal = false;
    }
    return equal;
};


class Chessman {
private:
    const char *color;
    Position *position;
public:
    Chessman(const char cColor[], Position *cPosition) {
        color = cColor;
        position = cPosition;
    }

    Chessman();

    void setColor(const char cColor[]) {
        color = cColor;
    }

    const char *getColor() {
        return color;
    }

    void setPosition(Position *cPosition) {
        position = cPosition;
    }

    Position getPosition() {
        return *position;
    }

    void print() {
        std::cout << "Chessman color: " << color << std::endl;
        position->print();
    }

    void printShort() {
        std::cout << color << std::endl;
    }

    void move(string direction) {
        signed char x = position->getX();
        int y = (int ) position->getY();
        char availableX [] = {'A','B','C','D', 'E', 'F', 'G', 'H'};
        if (direction == "ahead") {
            if (y != 8) ++y;
        } else if (direction == "back") {
            if (y != 1) --y;
        } else if (direction == "left") {
            int currentIndex = getCharIndex(availableX, 8, x);
            if (currentIndex != 0) {
                x = availableX[--currentIndex];
            }
        } else if (direction == "right") {
            int currentIndex = getCharIndex(availableX, 8, x);
            if (currentIndex != 7) {
                x = availableX[++currentIndex];
            }
        }
        position->setX(x);
        position->setY(y);
    }

    int getCharIndex(const char *array, int size, char c) {
        for (int i = 0; i < size; i++) {
            if (array[i] == c)
                return (int)i;
        }
        return -1;
    }
};

class Knight : public Chessman {
private:
    int ordinal;
    bool isOwnField;
public:
    Knight(const char kColor[], Position *kPosition, int kOrdinal, bool kIsOwnField):
            Chessman(kColor, kPosition) {
        ordinal = kOrdinal;
        isOwnField = kIsOwnField;
    }

    Knight();

    friend bool operator==(Knight &, Knight &);
    friend Knight operator++(Knight &);

    void setOrdinal(int kOrdinal) {
        ordinal = kOrdinal;
    }

    int getOrdinal() {
        return ordinal;
    }

    void setIsOwnField(bool kIsOwnField) {
        isOwnField = kIsOwnField;
    }

    int getIsOwnField() {
        return isOwnField;
    }
};

Knight operator++(Knight &knight) {
    char availableX [] = {'A','B','C','D', 'E', 'F', 'G', 'H'};
    Position &&position = knight.getPosition();
    position.setY(position.getY() + 3);
    position.setX(availableX[2]);
    knight.setPosition(&position);
    return knight;
};

bool operator==(Knight &knight1, Knight &knight2) {
    Position position1(knight1.getPosition().getX(), knight1.getPosition().getY());
    Position position2(knight2.getPosition().getX(), knight2.getPosition().getY());
    return position1 == position2;
};

class Pawn : public Chessman {
private:
    int ordinal;
    bool isOwnField;
public:
    Pawn(const char pColor[], Position *pPosition, int pOrdinal, bool pIsOwnField):
            Chessman(pColor, pPosition) {
        ordinal = pOrdinal;
        isOwnField = pIsOwnField;
    }

    Pawn();

    friend bool operator==(Pawn &, Pawn &);
    friend Pawn operator++(Pawn &);

    void setOrdinal(int kOrdinal) {
        ordinal = kOrdinal;
    }

    int getOrdinal() {
        return ordinal;
    }

    void setIsOwnField(bool kIsOwnField) {
        isOwnField = kIsOwnField;
    }

    int getIsOwnField() {
        return isOwnField;
    }
};

Pawn operator++(Pawn &pawn) {
    Position position = pawn.getPosition();
    position.setY(position.getY() + 1);
    pawn.setPosition(&position);
    return pawn;
};

bool operator==(Pawn &pawn1, Pawn &pawn2) {
    Position position1(pawn1.getPosition().getX(), pawn1.getPosition().getY());
    Position position2(pawn2.getPosition().getX(), pawn2.getPosition().getY());
    return position1 == position2;
};

class Queen : public Chessman {
private:
    int ordinal;
    bool isOwnField;
public:
    Queen(const char pColor[], Position *pPosition, int pOrdinal, bool pIsOwnField):
            Chessman(pColor, pPosition) {
        ordinal = pOrdinal;
        isOwnField = pIsOwnField;
    }

    Queen();

    friend bool operator==(Queen &, Queen &);

    void setOrdinal(int kOrdinal) {
        ordinal = kOrdinal;
    }

    int getOrdinal() {
        return ordinal;
    }

    void setIsOwnField(bool kIsOwnField) {
        isOwnField = kIsOwnField;
    }

    int getIsOwnField() {
        return isOwnField;
    }

    void move(string direction, int points) {
        signed char x = this->getPosition().getX();
        int y = this->getPosition().getY();
        char availableX [] = {'A','B','C','D', 'E', 'F', 'G', 'H'};
        if (direction == "ahead") {
            if (y != 8 && (y + points) < 8) y += points;
        } else if (direction == "back") {
            if (y != 1 && (y - points) > 1) y -= points;
        } else if (direction == "left") {
            int currentIndex = getCharIndex(availableX, 8, x);
            if (currentIndex != 0 && (currentIndex - points) >= 0) {
                x = availableX[currentIndex - points];
            }
        } else if (direction == "right") {
            int currentIndex = getCharIndex(availableX, 8, x);
            if (currentIndex != 7 && (currentIndex + points) <= 7) {
                x = availableX[currentIndex + points];
            }
        }
        this->getPosition().setX(x);
        this->getPosition().setY(y);
    }
};

bool operator==(Queen &queen1, Queen &queen2) {
    Position position1(queen1.getPosition().getX(), queen1.getPosition().getY());
    Position position2(queen2.getPosition().getX(), queen2.getPosition().getY());
    return position1 == position2;
};

class Game {
private:
    string gamerName1;
    string gamerName2;
    int size;
    int indexInt = 0;
    Chessman **chessmans;
public:

    Game(string gGamerName1, string gGamerName2, int gSize) {
        gamerName1 = std::move(gGamerName1);
        gamerName2 = std::move(gGamerName2);
        size = gSize;
        chessmans = new Chessman*[gSize];
    }

    Game();

    void setGamerName1(string gGamerName1) {
        gamerName1 = std::move(gGamerName1);
    }

    string getGamerName1() {
        return gamerName1;
    }

    void setGamerName2(string gGamerName2) {
        gamerName2 = std::move(gGamerName2);
    }

    string getGamerName2() {
        return gamerName2;
    }

    void addChessman(Chessman *chessman) {
        if (indexInt < size) {
            chessmans[indexInt++] = chessman;
        } else {
            printf("List full");
        }
    }

    Chessman * getChessmanByIndex(int index) {
        return chessmans[index];
    }
};

int main() {
    Position position;

    cout << "Enter position : " << endl;
    cin >> position;
    cout << "Out position : " << position << endl;

    Chessman *chessman = new Chessman("white", new Position('A', 1));
    chessman->print();
    chessman->printShort();

    Pawn *pawn1 = new Pawn("white", new Position('A', 2), 2, true);
    Pawn *pawn2 = new Pawn("white", new Position('B', 2), 3, true);

    std::cout << "Pawns " << ((*pawn1 == *pawn1) ?
                              "are same" : "are different") <<  std::endl;
    std::cout << "Pawns " << ((*pawn1 == *pawn2) ?
                              "are same" : "are different") <<  std::endl;

    pawn1->getPosition().print();
    pawn1->move("ahead");
    pawn1->getPosition().print();
    ++*pawn1;
    pawn1->getPosition().print();

    Game *game = new Game("Ted", "Robert", 4);
    game->addChessman(new Pawn("white", new Position('A', 2), 1, true));
    game->addChessman(new Pawn("black", new Position('B', 7), 2, true));
    game->addChessman(new Queen("black", new Position('H', 4), 1, false));
    game->addChessman(new Knight("white", new Position('D', 1), 1, true));

    game->getChessmanByIndex(2)->print();

    return 0;
}