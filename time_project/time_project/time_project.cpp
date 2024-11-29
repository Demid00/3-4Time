#include <iostream>

using namespace std;

class Time {
private:
    int hours, minutes, seconds;

    // Статическая переменная для подсчёта объектов
    static int objectCount;

public:
    // Конструктор по умолчанию
    Time() : hours(0), minutes(0), seconds(0) {
        ++objectCount;
        cout << "Default constructor called. Object count: " << objectCount << endl;
    }

    // Конструктор с параметрами
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        ++objectCount;
        cout << "Parameterized constructor called. Object count: " << objectCount << endl;
    }

    // Конструктор копирования
    Time(const Time& t) : hours(t.hours), minutes(t.minutes), seconds(t.seconds) {
        ++objectCount;
        cout << "Copy constructor called. Object count: " << objectCount << endl;
    }

    // Оператор присваивания
    Time& operator= (const Time& other) {
        if (this != &other) {
            hours = other.hours;
            minutes = other.minutes;
            seconds = other.seconds;
        }
        return *this;
    }

    // Деструктор
    ~Time() {
        --objectCount;
        cout << "Destructor called. Object count: " << objectCount << endl;
    }

    // Статический метод для получения текущего значения счётчика
    static int GetObjectCount() {
        return objectCount;
    }

    void Normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        else if (seconds < 0) {
            minutes -= (seconds / 60);
            seconds = 60 - (seconds % 60);
        }

        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        else if (minutes < 0) {
            hours -= (minutes / 60);
            minutes = 60 - (minutes % 60);
        }

        if (hours >= 24) {
            hours %= 24;
        }
        else if (hours < 0) {
            hours = 24 - (hours % 24);
        }
    }

    int ToSeconds() const {
        return (hours * 60 + minutes) * 60 + seconds;
    }

    void InternalPrint() {
        cout << "HH:MM:SS\n" << hours << ":" << minutes << ":" << seconds << endl;
    }

    void SetHours(int hours) { this->hours = hours; }
    void SetMinutes(int minutes) { this->minutes = minutes; }
    void SetSeconds(int seconds) { this->seconds = seconds; }
    int GetHours() const { return hours; }
    int GetMinutes() const { return minutes; }
    int GetSeconds() const { return seconds; }
};

// Определение статической переменной
int Time::objectCount = 0;

int main() {
    cout << "Initial object count: " << Time::GetObjectCount() << endl;

    Time t1;
    cout << "Object count after creating t1: " << Time::GetObjectCount() << endl;

    Time t2(10, 20, 30);
    cout << "Object count after creating t2: " << Time::GetObjectCount() << endl;

    {
        Time t3(t2);
        cout << "Object count after creating t3: " << Time::GetObjectCount() << endl;
    }  // t3 уничтожается здесь

    cout << "Object count after destroying t3: " << Time::GetObjectCount() << endl;

    return 0;
}
