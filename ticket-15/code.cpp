#include <iostream>
#include <stdlib.h>
using namespace std;

class Location
{
private:
    double _lat;
    double _lng;
    int _id;

public:
    Location(double lat, double lng, int id) : _lat(lat), _lng(lng), _id(id) {}
    Location() : _lat(0), _lng(0), _id(0) {}
    ~Location() {}

    double getLat() { return _lat; }
    double getLng() { return _lng; }
    int getId() { return _id; }

    void setLat(double lat) { _lat = lat; }
    void setLng(double lng) { _lng = lng; }
    void setId(int id) { _id = id; }

    string toString() { return to_string(_lat) + ", " + to_string(_lng) + ", " + to_string(_id); }

    virtual void print()
    {
        cout << "lat: " << _lat
             << ", lng: " << _lng
             << ", id: " << _id
             << endl;
    }

    virtual void printShort()
    {
        cout << _lat << ", " << _lng << ", " << _id << endl;
    }

    friend ostream &operator<<(ostream &output, Location &location)
    {
        output << "lat: " << location.getLat()
               << ", lng: " << location.getLng()
               << ", id: " << location.getId();
        return output;
    }

    friend istream &operator>>(istream &input, Location &location)
    {
        double lat;
        double lng;
        int id;

        cout << "please enter latitude: ";
        cin >> lat;

        cout << "please enter longitude: ";
        cin >> lng;

        cout << "please enter id: ";
        cin >> id;

        location.setLat(lat);
        location.setLng(lng);
        location.setId(id);

        return input;
    }
};

class GardenConditions;
class ClimateConditions
{
private:
    double _temperature;
    double _light;
    double _humidity;
    double _soilAcidity;

public:
    ClimateConditions(double temperature,
                      double light,
                      double humidity,
                      double soilAcidity) : _temperature(temperature),
                                            _light(light),
                                            _humidity(humidity),
                                            _soilAcidity(soilAcidity) {}
    ClimateConditions() : _temperature(0),
                          _light(0),
                          _humidity(0),
                          _soilAcidity(0) {}
    ~ClimateConditions() {}

    double getTemperature() { return _temperature; }
    double getLight() { return _light; }
    double getHumidity() { return _humidity; }
    double getSoilAcidity() { return _soilAcidity; }

    void setTemperature(double temperature) { _temperature = temperature; }
    void setLight(double light) { _light = light; }
    void setHumidity(double humidity) { _humidity = humidity; }
    void setSoilAcidity(double soilAcidity) { _soilAcidity = soilAcidity; }

    string toString() { return to_string(_temperature) + ", " + to_string(_light) + ", " + to_string(_humidity) + ", " + to_string(_soilAcidity); }

    virtual void print()
    {
        cout << "temperature: " << _temperature
             << ", light: " << _light
             << ", humidity: " << _humidity
             << ", soil acidity: " << _soilAcidity
             << endl;
    }

    virtual void printShort()
    {
        cout << _temperature << ", " << _light << ", " << _humidity << ", " << _soilAcidity << endl;
    }

    virtual void show()
    {
        print();
    };

    friend ostream &operator<<(ostream &output, ClimateConditions &conditions)
    {
        output << "temperature: " << conditions.getTemperature()
               << ", light: " << conditions.getLight()
               << ", humidity: " << conditions.getHumidity()
               << ", soil acidity: " << conditions.getSoilAcidity();
        return output;
    }

    friend istream &operator>>(istream &input, ClimateConditions &conditions)
    {
        double temperature;
        double light;
        double humidity;
        double soilAcidity;

        cout
            << "please enter temperature: ";
        cin >> temperature;

        cout << "please enter light: ";
        cin >> light;

        cout << "please enter humidity: ";
        cin >> humidity;
        cout << "please enter soilAcidity: ";
        cin >> soilAcidity;

        conditions.setTemperature(temperature);
        conditions.setLight(light);
        conditions.setHumidity(humidity);
        conditions.setSoilAcidity(soilAcidity);

        return input;
    }

    ClimateConditions &operator++()
    {
        setHumidity(getHumidity() + 1);
        return *this;
    }

    ClimateConditions operator++(int)
    {
        ClimateConditions temp = *this;
        setHumidity(getHumidity() + 1);
        return temp;
    };

    ClimateConditions &operator--()
    {
        setHumidity(getHumidity() - 1);
        return *this;
    }

    ClimateConditions operator--(int)
    {
        ClimateConditions temp = *this;
        setHumidity(getHumidity() - 1);
        return temp;
    };

    bool operator<(ClimateConditions &condition)
    {
        return getHumidity() < condition.getHumidity();
    };

    bool operator==(ClimateConditions &condition)
    {
        return _temperature == condition.getTemperature() &&
               _light == condition.getLight() &&
               _humidity == condition.getHumidity() &&
               _soilAcidity == condition.getSoilAcidity();
    };

    operator GardenConditions();
};

class GreenhouseConditions : public ClimateConditions
{
private:
    ClimateConditions *_optimalConditions;
    double _tolerancePercents;

    bool isToleranceExceeded(double curValue, double optimalValue)
    {
        return abs(curValue - optimalValue) * 100 / optimalValue > _tolerancePercents;
    }

public:
    GreenhouseConditions(double temperature,
                         double light,
                         double humidity,
                         double soilAcidity,
                         ClimateConditions *optimalConditions,
                         double tolerancePercents) : ClimateConditions(temperature, light, humidity, soilAcidity),
                                                     _optimalConditions(optimalConditions),
                                                     _tolerancePercents(tolerancePercents) {}
    GreenhouseConditions() : ClimateConditions(0, 0, 0, 0),
                             _optimalConditions(NULL),
                             _tolerancePercents(0) {}
    ~GreenhouseConditions() {}

    ClimateConditions *getOptimalConditions() { return _optimalConditions; }
    double getTolerance() { return _tolerancePercents; }

    void setOptimalConditions(ClimateConditions *optimalConditions) { _optimalConditions = optimalConditions; }
    void setTolerance(double tolerancePercents) { _tolerancePercents = tolerancePercents; }

    virtual void printShort()
    {
        cout << getTemperature() << ", "
             << getLight() << ", "
             << getHumidity() << ", "
             << getSoilAcidity() << ", "
             << _optimalConditions->toString() << ", "
             << _tolerancePercents
             << endl;
    }

    virtual void show()
    {
        bool isAllGood = true;

        if (isToleranceExceeded(getTemperature(), _optimalConditions->getTemperature()))
        {
            cout << "temperature: " << getTemperature() << ", excess: " << getTemperature() - _optimalConditions->getTemperature();
            isAllGood = false;
        }

        if (isToleranceExceeded(getLight(), _optimalConditions->getLight()))
        {
            cout << "light: " << getLight() << ", excess: " << getLight() - _optimalConditions->getLight();
            isAllGood = false;
        }

        if (isToleranceExceeded(getHumidity(), _optimalConditions->getHumidity()))
        {
            cout << "humidity: " << getHumidity() << ", excess: " << getHumidity() - _optimalConditions->getHumidity();
            isAllGood = false;
        }

        if (isToleranceExceeded(getSoilAcidity(), _optimalConditions->getSoilAcidity()))
        {
            cout << "soil acidity: " << getSoilAcidity() << ", excess: " << getSoilAcidity() - _optimalConditions->getSoilAcidity();
            isAllGood = false;
        }

        if (isAllGood)
        {
            cout << "All indicators are within tolerances";
        }

        cout << endl;
    }
};

class GardenConditions : public ClimateConditions
{
private:
    double _criticalTemperature;
    double _criticalSoilAcidity;
    Location *_location;

public:
    GardenConditions(double temperature,
                     double light,
                     double humidity,
                     double soilAcidity,
                     double criticalTemperature,
                     double criticalSoilAcidity,
                     Location *location) : ClimateConditions(temperature, light, humidity, soilAcidity),
                                           _criticalTemperature(criticalTemperature),
                                           _criticalSoilAcidity(criticalSoilAcidity),
                                           _location(location) {}
    GardenConditions() : ClimateConditions(0, 0, 0, 0),
                         _criticalTemperature(0),
                         _criticalSoilAcidity(0),
                         _location(NULL) {}
    ~GardenConditions() {}

    double getCriticalTemperature() { return _criticalTemperature; }
    double getCriticalSoilAcidity() { return _criticalSoilAcidity; }
    Location *getLocation() { return _location; }

    void setCriticalTemperature(double criticalTemperature) { _criticalTemperature = criticalTemperature; }
    void setCriticalSoilAcidity(double criticalSoilAcidity) { _criticalSoilAcidity = criticalSoilAcidity; }
    void setLocation(Location *location) { _location = location; }

    virtual void printShort()
    {
        cout << getTemperature() << ", "
             << getLight() << ", "
             << getHumidity() << ", "
             << getSoilAcidity() << ", "
             << _criticalTemperature << ", "
             << _criticalSoilAcidity << ", "
             << _location->toString()
             << endl;
    }

    virtual void show()
    {
        bool isAllGood = true;

        if (getTemperature() > _criticalTemperature)
        {
            cout << "temperature: " << getTemperature() << ", excess: " << getTemperature() - _criticalTemperature;
            isAllGood = false;
        }

        if (getSoilAcidity() > _criticalSoilAcidity)
        {
            cout << "soil acidity: " << getSoilAcidity() << ", excess: " << getSoilAcidity() - _criticalSoilAcidity;
            isAllGood = false;
        }

        if (isAllGood)
        {
            cout << "All indicators are lower than critical";
        }

        cout << endl;
    }

    operator ClimateConditions()
    {
        ClimateConditions *conditions = new ClimateConditions(getTemperature(), getLight(), getHumidity(), getSoilAcidity());
        return *conditions;
    }
};

ClimateConditions::operator GardenConditions()
{
    GardenConditions *conditions = new GardenConditions();
    conditions->setTemperature(getTemperature());
    conditions->setLight(getLight());
    conditions->setHumidity(getHumidity());
    conditions->setSoilAcidity(getSoilAcidity());

    return *conditions;
}

class Forecast
{
private:
    int _id;
    ClimateConditions **_items;
    int _capacity;
    int _size;

public:
    Forecast(int id, int capacity) : _id(id), _capacity(capacity)
    {
        _size = 0;
        _items = new ClimateConditions *[capacity];
    }
    ~Forecast()
    {
        delete _items;
    }

    void add(ClimateConditions *conditions)
    {
        if (_size < _capacity)
        {
            _items[_size] = conditions;
            _size++;
            return;
        }

        throw "Cannot add an item. No capacity.";
    }

    ClimateConditions *operator[](int index)
    {
        if (index >= _size || index < 0)
        {
            throw "Array index out of bound";
        }
        return _items[index];
    }
};

template <typename T>
bool isAscSorted(T arr[], int len)
{
    if (len < 2)
    {
        return true;
    }

    for (int i = 0; i < len - 1; i++)
    {
        if (arr[i + 1] < arr[i])
        {
            return false;
        }
    }

    return true;
}
template <typename T>
bool isAscSorted(T arr[], int len, bool (*isLessThan)(T a, T b))
{
    if (len < 2)
    {
        return true;
    }

    for (int i = 0; i < len - 1; i++)
    {
        if (isLessThan(arr[i + 1], arr[i]))
        {
            return false;
        }
    }

    return true;
}

int main()
{
    Location *location1 = new Location(20.4354634, 56.235235235, 1);
    ClimateConditions *conditions1 = new ClimateConditions(24.0, 80.0, 75.0, 5.6);

    location1->print();
    location1->printShort();

    conditions1->print();
    conditions1->printShort();

    GreenhouseConditions *conditions2 = new GreenhouseConditions(24.0, 80.0, 75.0, 5.6, conditions1, 0.05);
    conditions2->printShort();

    GardenConditions *conditions3 = new GardenConditions(24.0, 80.0, 75.0, 5.6, 29, 95, location1);
    conditions3->printShort();

    return 0;
}
