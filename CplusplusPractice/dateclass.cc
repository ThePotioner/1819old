#include <iostream>

class Date
{
    private:
        int year_, month_, day_;

        int getMonthsMaxDay(int year, int month)
        {
            int months[12] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

            if (month == 2)
            {
                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                     months[1] = 29;
                else months[1] = 28;
            }

            return months[month - 1];
        }

    public:
        Date();
        Date(int year, int month, int day);
        void addDay(int inc);
        void addMonth(int inc);
        void addYear(int inc);
        void showDate();
};

Date::Date()
    : year_(2004), month_(01), day_(01) {}

Date::Date(int year, int month, int day)
    : year_(year), month_(month), day_(day) {}

void Date::addDay(int inc)
{
    day_ += inc;

    for (; day_ > getMonthsMaxDay(year_, month_);)
    {
        day_ -= getMonthsMaxDay(year_, month_);
        addMonth(1);
    }
}

void Date::addMonth(int inc)
{
    month_ += inc;

    for (; month_ > 12;)
    {
        month_ -= 12;
        addYear(1);
    }
}

void Date::addYear(int inc)
{
    year_ += inc;
}

void Date::showDate()
{
    if (month_ < 10 && day_ < 10)
        std::cout << "Now Date() : " << year_ << "-0" << month_ << "-0" << day_ << std::endl;
    else if (month_ < 10 && day_ > 9)
        std::cout << "Now Date() : " << year_ << "-0" << month_ << "-" << day_ << std::endl;
    else if (month_ > 9 && day_ < 10)
        std::cout << "Now Date() : " << year_ << "-" << month_ << "-0" << day_ << std::endl;
    else
        std::cout << "Now Date() : " << year_ << "-" << month_ << "-" << day_ << std::endl;
}

int main()
{
    Date date(2020, 10, 10);
    date.showDate();
}