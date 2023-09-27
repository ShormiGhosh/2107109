///Ride_Sharing_system
#include <iostream>
#include <algorithm>
#include<cmath>
#include<vector>
#include <unordered_map>
#include<string>
#include <cstdlib>
#include <ctime>
using namespace std;
class passenger;
class Driver;
class passenger_manager;
class driver_manager;

const double EarthRadius= 6371.0;
double degreesToRadians(double degrees)
{
    return degrees*M_PI/180.0;
}
// Function to calculate the distance between two points
double calculateHaversineDistance(double lati1, double long1, double lati2, double long2)
{
    lati1 = degreesToRadians(lati1);
    long1 = degreesToRadians(long1);
    lati2 = degreesToRadians(lati2);
    long2 = degreesToRadians(long2);
    double dLat = lati2-lati1;
    double dLon = long2-long1;
    double a = sin(dLat / 2.0)*sin(dLat/2.0)+cos(lati1)*cos(lati2)*sin(dLon/2.0)*sin(dLon/2.0);
    double c = 2.0*atan2(sqrt(a),sqrt(1.0-a));
    double distance = EarthRadius*c;
    return distance;
}
int RandomCar(int lower, int upper)
{
    return lower + rand() % (upper-lower + 1);
}

class User
{
protected:
    string Name;
    string Phone;
    string Email;
    string Location;
public:

    User() {}
    User(string n,string p, string em,string l):Name(n),Phone(p),Email(em),Location(l) {}
    virtual void ShowProfile()=0;
};
class Driver: public User
{
    string car_model;
    int licence_no;
public:
    Driver() {}
    Driver(string n,string p, string em,string l,string cm,int licence):User(n,p,em,l)
    {
        car_model=cm;
        licence_no=licence;
    }
    friend class passenger_manager;
    void ShowProfile()
    {
        cout<<"\n\nDriver's Profile"<<endl;
        cout<<"Name: "<<Name<<endl;
        cout<<"Mobile: "<<Phone<<endl;
        cout<<"Email: "<<Email<<endl;
        cout<<"Location: "<<Location<<endl;
        cout<<"Vehicle: "<<car_model<<endl;
        cout<<"Licence: "<<licence_no<<endl;
    }
    friend void show_driver(driver_manager &chalok, int licence);

};

class passenger: public User
{
    string Payment_method;
    string PIN;
    string source,destination;
    int shal,mash,tarikh,car;
public:
    passenger() {}
    passenger(string n,string p, string em,string l,string pm,string pin):User(n,p,em,l)
    {
        Payment_method=pm;
        PIN=pin;
    }
    passenger(string pin,string s, string d,int rc,int yr,int mnth,int dt)
    {
        PIN=pin;
        source=s;
        destination=d;
        car=rc;
        shal=yr;
        mash=mnth;
        tarikh=dt;
    }
    void ShowProfile()
    {
        cout<<"Passenger's Profile"<<endl;
        cout<<"Name: "<<Name<<endl;
        cout<<"Mobile: "<<Phone<<endl;
        cout<<"Email: "<<Email<<endl;
        cout<<"Location: "<<Location<<endl;
        cout<<"Payment method: "<<Payment_method<<endl;
    }
    void display_booking()
    {
        cout<<"Booked a trip from "<<source<<" to "<<destination<<" on date "<<shal<<"-"<<mash<<"-"<<tarikh<<endl;
        cout<<"Driver's licence no: "<<car<<endl;
    }
    friend void passenger_status(passenger_manager &jatri, string mobile, string PIN);
};

class passenger_manager:public passenger
{
public:
    unordered_map<string,string> password;
    vector<passenger>psngr;
    vector<passenger>book_ride;
    vector<Driver> drv;
    void sign_in_as_passenger();
    void Trip();
    double make_payment();
    friend class driver_manager;
    void addPassword(const string &mobile, const string &pin)
    {
        password[mobile] = pin;
    }
    string getPassword(const string &mobile)
    {
        string key = mobile;
        if (password.find(key) != password.end())
        {
            return password[key];
        }
        else
        {
            cout << "No user found" << endl;
            return "";
        }
    }
};

class driver_manager: public Driver
{
public:
    vector<Driver>drv;
    void sign_in_as_driver();
    void Show_all_driver();
    void initial_drivers();
};

void passenger_manager::sign_in_as_passenger()
{
    string name, mobile, email,loc,pay,pin;
    cout << "Enter Name:";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Mobile No:";
    getline(cin, mobile);
    cout << "Enter email address:";
    getline(cin, email);
    cout << "Enter Location:";
    getline(cin, loc);
    cout << "Enter Payment method:";
    getline(cin, pay);
    cout<<"Set Password: ";
    getline(cin, pin);
    addPassword(mobile,pin);
    psngr.push_back(passenger(name,mobile,email,loc,pay,pin));
    cout << "\n\nRegistration completed!" << endl;
    cout<<"Login Info "<<endl;
    cout<<"Phone Number: "<<mobile<<endl;
    cout<<"Your password is: "<<pin<<endl;
}

void driver_manager::sign_in_as_driver()
{
    string name, mobile, email,loc,car;
    int licence;
    cout << "Enter Name:";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Mobile No:";
    getline(cin, mobile);
    cout << "Enter Email Address:";
    getline(cin, email);
    cout << "Enter Location:";
    getline(cin, loc);
    cout << "Enter Your Car:";
    getline(cin, car);
    cout << "Enter Your Licence:";
    cin>>licence;
    drv.push_back(Driver(name,mobile,email,loc,car,licence));
    cout << "\nRegistration completed!" << endl;
}
void driver_manager::initial_drivers()
{
    drv.push_back(Driver("Faruk Ahmed","01358974522","faruk@gmail.com","Mirpur 10,Dhaka","AM General MV-1",10001));
    drv.push_back(Driver("Sheikh Miraj","01457220350","miraj@gmail.com","Mirpur 2,Dhaka","Acura MDX",10002));
    drv.push_back(Driver("Md. abu Taleb","01358474527","abu1101@gmail.com","Keraniganj","Tata Indigo ECS",10003));
    drv.push_back(Driver("Chinmoy Saha","01785974572","saha78@gmail.com","SHEIKH MUJIB RD,Chittagong","Acura TLX",10004));
    drv.push_back(Driver("Md Sumon","01358457865","sumon551@gmail.com","CDA AVENUE","Suzuki Alto 800",10005));
}
double passenger_manager::make_payment()
{
    double lat1, lat2, lon1, lon2;
    cout << "\nEnter latitude and longitude of your current location: ";
    cin >> lat1 >> lon1;
    cout << "\nEnter latitude and longitude of your destination: ";
    cin >> lat2 >> lon2;

    double range=calculateHaversineDistance(lat1, lon1, lat2, lon2);
    return range*10;
}
void passenger_manager::Trip()
{
    string locate,destin,pass;

    cout<<"Enter password ";
    cin.ignore();
    getline(cin,pass);
    cout<<"Enter your current location: ";
    getline(cin,locate);
    cout<<"Enter destination: ";
    getline(cin,destin);
    int largestLicence = 0;
    for (const Driver& driver : drv)
    {
        if (driver.licence_no > largestLicence)
        {
            largestLicence = driver.licence_no;
        }
    }
    int lower=10001,upper=largestLicence;
    int random_car=RandomCar(lower,upper);
    cout<<"Making a trip from "<<locate<<" to "<<destin<<endl;
    cout<<"Driver with licence "<<random_car<<" is in proximity to you"<<endl;

    time_t currentTime = time(nullptr);
    struct tm* currentDate =localtime(&currentTime);
    int year = currentDate->tm_year + 1900;
    int month = currentDate->tm_mon + 1;
    int day = currentDate->tm_mday;

    book_ride.push_back(passenger(pass,locate,destin,random_car,year,month,day));
}

void passenger_status(passenger_manager &jatri, string mobile, string PIN)
{
    auto it = jatri.password.find(mobile);
    if (it != jatri.password.end())
    {
        if (it->second == PIN)
        {
            for(int i=0; i<jatri.psngr.size(); i++)
            {
                if(jatri.psngr[i].PIN==PIN)
                {
                    jatri.psngr[i].ShowProfile();
                }
            }
        }
        if (it->second == PIN)
        {
            for(int i=0; i<jatri.book_ride.size(); i++)
            {
                if(jatri.book_ride[i].PIN==PIN)
                {
                    jatri.book_ride[i].display_booking();
                    return;
                }
            }
        }
        cout << "Invalid login information!" << endl;
    }
}
void show_driver(driver_manager &chalok, int licence) // function for showing driver's details
{
    int i;
    for (i = 0; i < chalok.drv.size(); i++)
    {
        if (chalok.drv[i].licence_no == licence) // comparing licence with the user input
        {
            chalok.drv[i].ShowProfile();
            return;
        }
    }
    if(i==chalok.drv.size())
        cout<<"No driver found"<<endl;
}
void driver_manager::Show_all_driver()
{
    for (int i = 0; i <drv.size(); i++)
    {
        drv[i].ShowProfile();
    }
    cout << endl;
}
int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    driver_manager chalok;
    passenger_manager jatri;
    chalok.initial_drivers();
    jatri.drv = chalok.drv;
    int choice;
    do
    {
        cout << "\n\n--------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                                           RIDE SHARE                    " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\n   1. Sign up as passanger                 2. Register as driver         3. Show Driver list               4. Request a trip" << endl;
        cout << "   5. Login to passenger's profile         6. Show My driver             7. Make payment                   8. Leave" << endl<<endl;;
        cin >> choice;
        switch(choice)
        {
        case 1:
        {
            jatri.sign_in_as_passenger();
            break;
        }
        case 2:
        {
            chalok.sign_in_as_driver();
            break;
        }
        case 3:
        {
            chalok.Show_all_driver();
            break;
        }
        case 4:
        {
            jatri.Trip();
            break;
        }
        case 5:
        {
            string pswrd,phn;
            cout<<"Login"<<endl;
            cout<<"Enter mobile no: ";
            cin.ignore();
            getline(cin,phn);
            cout<<"Enter password: ";
            getline(cin,pswrd);
            passenger_status(jatri,phn,pswrd);
            break;
        }
        case 6:
        {
            int lcn;
            cout<<"Enter driver's licence number: ";
            cin>>lcn;
            show_driver(chalok,lcn);
            break;
        }
        case 7:
        {
            double payment=jatri.make_payment();
            cout<<"\nYou have to pay "<<payment<<" taka."<<endl;
            break;
        }
        case 8:
        {
            cout<<"Leaving app..."<<endl;
            break;
        }
        }
    }
    while(choice!=8);

    return 0;
}
