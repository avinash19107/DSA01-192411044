#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
class Playlist {
    string tracks[5]; int count=0;
public:
    void addTrack(const string& n) { if(count<5) tracks[count++]=n; }
    string& operator[](int i) {
        if(i<0 || i>=count) throw out_of_range("Invalid track index");
        return tracks[i];
    }
    const string& operator[](int i) const {
        if(i<0 || i>=count) throw out_of_range("Invalid track index");
        return tracks[i];
    }
    int size() const { return count; }
};
int main() {
    Playlist p; p.addTrack("Track One"); p.addTrack("Track Two"); p.addTrack("Track Three");
    cout<<"Playlist:\n";
    for(int i=0;i<p.size();++i) cout<<i<<": "<<p[i]<<'\n';
    p[1]="Updated Track";
    cout<<"\nAfter modification:\n"<<p[1]<<'\n';
    try { cout<<p[5]<<'\n'; }
    catch(const out_of_range& e) { cout<<"Error: "<<e.what()<<'\n'; }
}