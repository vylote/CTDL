#include <bits/stdc++.h>
using namespace std;

class Time {
    private:
        int hour, minute, second;
    public:
        Time() : hour(0), minute(0), second(0) {}
        Time(int h, int min, int sec) {
            if (h < 0 || min < 0 || sec < 0) {
                throw std::invalid_argument("Time: gia tri khong duoc am");
            }
            int remainMinute = 0, remainHour = 0;
            if (sec >= 60) {
                        remainMinute = sec/60;
                        sec = sec % 60;
                    }
            int totalMinute = remainMinute+min;
                    if (totalMinute >= 60) {
                        remainHour = totalMinute/60;
                        min = totalMinute%60;
                    }
            h += remainHour;
            this->hour = h;
            this->minute = min;
            this->second = sec;
        }
        void input(istream& is = cin) {
            int remainMinute = 0, remainHour = 0;
            while (true) {
                is >> second;
                if (second >= 0) {
                    if (second >= 60) {
                        remainMinute = second/60;
                        second = second % 60;
                    }
                    break;
                } 
            }

            while (true) {
                is >> minute;
                if (minute >= 0) {
                    int totalMinute = remainMinute+minute;
                    if (totalMinute >= 60) {
                        remainHour = totalMinute/60;
                        minute = totalMinute%60;
                    }
                    break;
                }
            }

            while (true) {
                is >> hour;
                if (hour >= 0) {
                    hour += remainHour;
                    break;
                }
            }
        }
        string display() const{
            string sec = to_string(second);
            string min = to_string(minute);
            string h = to_string(hour);
            if (second < 10) sec = "0"+sec;  
            if (minute < 10) min = "0"+min;  
            if (hour < 10) h = "0"+h;  
            return h + ":" + min + ":" + sec;
        }

        friend istream& operator>>(istream &is, Time& a) {
            a.input(is);
            return is;
        }

        friend ostream& operator<<(ostream &os, const Time& a) {
            os << a.display();
            return os;
        }
};

int main() {
    Time a;
    cin >> a;
    cout << a;
}