#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
using namespace std;
class Bill {
protected:string patient;
public:explicit Bill(string p):patient(p){}virtual double total()const=0;virtual string type()const=0;
virtual void print()const{cout<<type()<<" | "<<patient<<" | Rs. "<<total()<<'\n';}virtual ~Bill()=default;
};
class OutPatient:public Bill{double c,t;public:OutPatient(string p,double a,double b):Bill(p),c(a),t(b){}double total()const override{return c+t;}string type()const override{return"OP";}};
class InPatient:public Bill{int d;double r,s;public:InPatient(string p,int x,double y,double z):Bill(p),d(x),r(y),s(z){}double total()const override{return d*r+s;}string type()const override{return"IP";}};
class DayCareBill:public Bill{double price;public:DayCareBill(string p,double x):Bill(p),price(x){}double total()const override{return price;}string type()const override{return"DayCare";}};
class EmergencyBill:public Bill{double base;int hours;double rate;public:EmergencyBill(string p,double b,int h,double r):Bill(p),base(b),hours(h),rate(r){}double total()const override{return base+hours*rate;}string type()const override{return"Emergency";}};
class HomeCareBill:public Bill{double service,equipment;public:HomeCareBill(string p,double s,double e):Bill(p),service(s),equipment(e){}double total()const override{return service+equipment;}string type()const override{return"HomeCare";}};
class Payer{public:virtual double amountCovered(const Bill&)const=0;virtual string name()const=0;virtual ~Payer()=default;};
class SelfPay:public Payer{public:double amountCovered(const Bill&b)const override{return b.total();}string name()const override{return"SelfPay";}};
class Insurance:public Payer{double limit,copay;public:Insurance(double l,double c):limit(l),copay(c){}double amountCovered(const Bill&b)const override{return min(b.total()*(1.0-copay/100.0),limit);}string name()const override{return"Insurance";}};
class GovernmentScheme:public Payer{map<string,double> rates;public:GovernmentScheme(){rates={{"OP",1500},{"IP",40000},{"DayCare",20000},{"Emergency",10000}};}double amountCovered(const Bill&b)const override{auto i=rates.find(b.type());if(i==rates.end())return 0;return min(b.total(),i->second);}string name()const override{return"GovernmentScheme";}};
class CorporatePayer:public Payer{double percent;public:explicit CorporatePayer(double p):percent(p){}double amountCovered(const Bill&b)const override{return b.total()*percent/100.0;}string name()const override{return"CorporatePayer";}};
void process(const Bill&b,const Payer&p){cout<<p.name()<<" covers Rs. "<<p.amountCovered(b)<<'\n';}
int main(){
 vector<unique_ptr<Bill>> bills;
 bills.push_back(make_unique<OutPatient>("Ravi",500,1200));bills.push_back(make_unique<InPatient>("Meena",3,2500,40000));
 bills.push_back(make_unique<DayCareBill>("Anita",25000));bills.push_back(make_unique<EmergencyBill>("Rahul",5000,3,2000));
 bills.push_back(make_unique<HomeCareBill>("Kavya",3000,1500));
 SelfPay self;Insurance insurance(50000,20);GovernmentScheme govt;CorporatePayer corporate(80);
 const Payer* old[]={&self,&insurance,&govt};
 cout<<"HOSPITAL BILLING EXTENSION\n\n";
 for(size_t i=0;i<4;++i){bills[i]->print();for(auto p:old)process(*bills[i],*p);cout<<'\n';}
 cout<<"NEW BILL AND PAYER TEST\n";bills[4]->print();process(*bills[4],self);process(*bills[4],insurance);process(*bills[4],corporate);
 cout<<"\nExtension successful\n";
}