#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class Track {
    string name; int duration;
public:
    Track(string n,int d):name(n),duration(d){}
    bool operator<(const Track& o) const{return duration<o.duration;}
    bool operator==(const Track& o) const{return duration==o.duration;}
    void display() const{cout<<name<<" - "<<duration<<" seconds\n";}
};
int main(){
    Track tracks[]={{"Song A",240},{"Song B",180},{"Song C",210}};
    sort(tracks,tracks+3); cout<<"Sorted playlist:\n";
    for(const auto& t:tracks)t.display();
    cout<<boolalpha<<"Equal duration: "<<(Track("X",180)==Track("Y",180))<<'\n';
}