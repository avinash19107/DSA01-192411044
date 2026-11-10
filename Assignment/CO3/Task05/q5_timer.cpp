#include <iostream>
using namespace std;
class TrackTimer {
    int seconds;
public:
    explicit TrackTimer(int s=0):seconds(s){}
    TrackTimer& operator++(){++seconds;return *this;}
    TrackTimer operator++(int){TrackTimer old=*this;++seconds;return old;}
    void display() const { cout<<seconds<<" seconds\n"; }
};
int main(){
    TrackTimer timer(120); cout<<"Initial: ";timer.display();
    TrackTimer old=timer++; cout<<"Postfix returned: ";old.display();
    cout<<"After postfix: ";timer.display(); ++timer;
    cout<<"After prefix: ";timer.display();
}