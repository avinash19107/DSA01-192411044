#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;
class Bill {
protected:string patient;
public:explicit Bill(string p):patient(p){}virtual double total()const=0;
virtual void display()const{cout<<"Patient: "<<patient<<" | Bill: Rs. "<<total()<<'\n';}
virtual ~Bill(){cout<<"Bill base destructor\n";}
};
class OutPatient:public Bill{
 double consultation,tests;
public:OutPatient(string p,double c,double t):Bill(p),consultation(c),tests(t){}
 double total()const override{return consultation+tests;}
 ~OutPatient()override{cout<<"OutPatient destructor\n";}
};
class InPatient:public Bill{
 int days;double room,procedure;
public:InPatient(string p,int d,double r,double s):Bill(p),days(d),room(r),procedure(s){}
 double total()const override{return days*room+procedure;}
 ~InPatient()override{cout<<"InPatient destructor\n";}
};
int main(){
 {vector<unique_ptr<Bill>> bills;
  bills.push_back(make_unique<OutPatient>("Ravi",500,1200));
  bills.push_back(make_unique<InPatient>("Meena",3,2500,40000));
  cout<<"HOSPITAL RAII TEST\n\n";double sum=0;
  for(const auto& b:bills){b->display();sum+=b->total();}
  cout<<"\nGrand total: Rs. "<<sum<<"\n\nLeaving billing scope...\n";
 }
 cout<<"\nAll bill objects released safely\n";
}