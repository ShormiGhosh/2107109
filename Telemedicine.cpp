#include <bits/stdc++.h>
#include <string>
#include <ctime> //header for time function

using namespace std;

int hour = 8;
class Doctor; // forward declaration
class Doctor_manage;
class Patient_manage;

/********patient class*********/
class Patient
{
protected:
    string name;
    int age, ID;
    string email;
    string role;
    string phone;
    string disease;
    string medicine;

public:
    Patient() {}
    Patient(int id, string nP, int agP, string emlP, string phnP)
    {
        ID = id;
        name = nP;
        age = agP;
        email = emlP;
        role = "Patient";
        phone = phnP;
    }
    Patient(int id, string rog, string oshudh)
    {
        ID = id;
        disease = rog;
        medicine = oshudh;
    }

    void displayP() // function for displaying patient details
    {
        cout << "ID: " << ID << "\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Email: " << email << "\n";
        cout << "Role: " << role << "\n";
    }
    void display_pres()
    {
        cout << "Disease: " << disease << "\n";
        cout << "Medicine: " << medicine << "\n\n";
    }
    friend void show_patient(Patient_manage &rogi, Doctor_manage &daktar, int ID); // using friend function to access patient ID
};

/********doctor class*********/
class Doctor
{
protected:
    string D_name;
    string specialist;
    string D_email;
    string D_role;
    string D_phone;

public:
    Doctor() {}
    Doctor(string nD, string spcialD, string emlD, string phnD)
    {
        D_name = nD;
        specialist = spcialD;
        D_email = emlD;
        D_role = "Doctor";
        D_phone = phnD;
    }
    void displayD() // function for displaying doctor details
    {
        cout << "Name: " << D_name << "\n";
        cout << "specialist: " << specialist << "\n";
        cout << "Email: " << D_email << "\n";
        cout << "Role: " << D_role << "\n";
        cout << "mobile: " << D_phone << "\n";
    }
};

/*********patient manage class********/
class Patient_manage
{
public:
    int tot_pat;
    Patient obj_pat[100];
    Patient_manage()
    {
        tot_pat = 0;
    }
    void add_patient();
    void show_All_patient();
    void appointment();
};

/********doctor manage class**********/
class Doctor_manage
{
public:
    int tot_doc;
    Doctor obj_doc[50];
    Patient obj_pat_pres[100];
    Doctor_manage()
    {
        tot_doc = 0;
    }
    void add_doctor();
    void show_All_doctor();
    void prescription();
};
/********function definition starts*********/

/******patient manage functions******/
void Patient_manage::add_patient() // function for adding patient details
{
    int id, age;
    string name, mobile, email;
    cout << "Enter ID :" << endl;
    cin >> id;
    cin.ignore();
    cout << "Enter Name:" << endl;
    getline(cin, name);
    cout << "Enter Age:" << endl;
    cin >> age;
    cin.ignore();
    cout << "Enter email address:" << endl;
    getline(cin, email);
    cout << "Enter Mobile No:" << endl;
    getline(cin, mobile);
    obj_pat[tot_pat] = Patient(id, name, age, email, mobile); // passing patient info to the array
    tot_pat++;
    cout << "Registration completed!" << endl;
}

void Patient_manage::show_All_patient() // function for displaying all patient list
{
    for (int i = 0; i < tot_pat; i++)
    {
        obj_pat[i].displayP();
    }
    cout << endl;
}

/*****doctor manage functions*****/

void Doctor_manage::add_doctor() // function for adding doctor details
{
    string D_name, specialist, D_email, D_phone;
    cout << "Enter Doctor Name: ";
    cin.ignore();
    getline(cin, D_name);
    cout << "Specialist: ";
    getline(cin, specialist);
    cout << "Doctor E-mail: ";
    getline(cin, D_email);
    cout << "Phone No: ";
    getline(cin, D_phone);
    obj_doc[tot_doc] = Doctor(D_name, specialist, D_email, D_phone); // passing doctor info to the array
    tot_doc++;
    cout << "Doctor added successfully!" << endl;
}

void Doctor_manage::show_All_doctor() // function for displaying all doctor list
{
    for (int i = 0; i < tot_doc; i++)
    {
        obj_doc[i].displayD();
    }
    cout << endl;
}

void Doctor_manage::prescription() // function through which doctor will prescribe
{
    int ID;
    string disease, medicine;
    cout << "Enter patient ID: " << endl;
    cin >> ID;
    cout << "Disease name: " << endl;
    cin.ignore();
    getline(cin, disease);
    cout << "Medicine name: " << endl;
    getline(cin, medicine);
    obj_pat_pres[ID] = Patient(ID, disease, medicine);
}

/****functions outside the classes****/

void show_patient(Patient_manage &rogi, Doctor_manage &daktar, int ID) // function for showing patient personal details
{
    for (int i = 0; i < rogi.tot_pat; i++)
    {
        if (rogi.obj_pat[i].ID == ID) // comparing id with the user input
        {
            rogi.obj_pat[i].displayP();
            daktar.obj_pat_pres[ID].display_pres();
            return;
        }
    }
}

void time() // time management function
{
    time_t now = time(NULL);
    tm *localTime = localtime(&now);
    mktime(localTime);
    cout << "\nTime of booking your appointment " << asctime(localTime);
    localTime->tm_mday += 1;
    cout << "\nYour appointment schedule:";
    cout << "\ndate: ";
    cout << localTime->tm_mday << "/" << localTime->tm_mon + 1;
    cout << "/" << localTime->tm_year + 1900 << endl;
    cout << "Time: " << hour << ":00" << endl;
    hour++;
    if (hour == 20)
        hour = 8;
}

void Patient_manage::appointment() // function for booking appointment
{
    string name;
    string specialist;
    cout << "\nEnter doctor name\n";
    cin.ignore();
    getline(cin, name);
    cout << "Specialist: ";
    getline(cin, specialist);
    cout << "\nAppointment successfully booked to " << name << " (" << specialist << " Specialist)" << endl;
    time();
    cout << "Make online payment 500 BDT" << endl;
}

void initial_doc_list() // adding some doctors to the system manually
{
    Doctor doc1("Dr. Mahfuj Alam", "Medicine & Chest Diseases", " alammahfuj@gmail.com", "01784545784");
    doc1.displayD();
    cout << endl;
    Doctor doc2("Dr. Ayesha Begum", "Medicine & Neurology", "ayesha4545@gmail.com", "01784702135");
    doc2.displayD();
    cout << endl;
    Doctor doc3("Dr. Forhadul Islam", "Consultant (Medicine)", "forhad@gmail.com", "01487596555");
    doc3.displayD();
    cout << endl;
}

/*******main function starts********/

int main()
{
    Patient_manage rogi;
    Doctor_manage daktar;
    int choice;
    do
    {
        cout << "\n\n--------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                                           TELEMEDICINE SHEBA                      " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\n     1. Add Patient Information              2. Add Doctor Information         3. Show Doctor list               4. Show Patient list" << endl;
        cout << "     5. Show Patient personal details        6. Book Appointment               7. Prescribe patient              8. Leave" << endl<<endl;;
        cin >> choice;
        switch (choice)
        {
        case 1:
            rogi.add_patient();
            break;
        case 2:
            daktar.add_doctor();
            break;
        case 3:
            cout << "All registered doctors:\n\n";
            initial_doc_list();
            daktar.show_All_doctor();
            break;
        case 4:
            cout << "All patients:\n\n";
            rogi.show_All_patient();
            break;
        case 5:
            int ID;
            cout << "Enter patient Id: " << endl;
            cin >> ID;
            cout << "Patient Profile" << endl;
            show_patient(rogi, daktar, ID);
            break;
        case 6:
            cout << "All registered doctors:\n\n";
            initial_doc_list();
            daktar.show_All_doctor();
            rogi.appointment();
            break;
        case 7:
            daktar.prescription();
            break;
        case 8:
            cout << "Leaving..." << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 8);
    return 0;
}
