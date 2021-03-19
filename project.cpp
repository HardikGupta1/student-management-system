#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

class student
{
private:
    int rno, adm, mk[5];
    char na[40], gd, remrk[20];
    char batch[100];
    float percentage;
    void calcgd();
    int calcmk();

public:
    void getdata();

    void display();

    void show();

    int getadm()
    {
        return (adm);
    }

    string getstd() // fumction to retuen batch name
    {
        return (batch);
    }
};

void student::getdata()
{
    cout << " Enter the student admission no : ";
    cin >> adm;
    cout << "\n Enter the roll no :  ";
    cin >> rno;
    cout << "\n Enter the name of the student : ";
    cin >> na;
    cout << "\n Enter the batch of the student : ";
    cin >> batch;
    cout << "\n Enter the 5 subject marks : ";
    for (int i = 0; i < 5; i++)
    {
        cout << " ";
        cin >> mk[i];
    }
}

int student::calcmk()
{
    int tot = 0;
    for (int i = 0; i < 5; i++)
    {
        tot += mk[i];
    }
    return (tot);
}

void student::calcgd()
{

    percentage = (calcmk()) / 5;
    if (percentage >= 85)
    {
        gd = 'A';
        strcpy(remrk, "EXCELLENT!");
    }
    else if (percentage >= 75 && percentage < 85)
    {
        gd = 'B';
        strcpy(remrk, "GOOD!");
    }
    else if (percentage >= 65 && percentage < 75)
    {
        gd = 'C';
        strcpy(remrk, "AVERAGE");
    }
    else
    {
        gd = 'F';
        strcpy(remrk, "FAIL!");
    }
}

void student::display()
{
    for (int i = 1; i < 78; i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << "Admission   Roll   Student   Batch  Total  Percentage  Grade   Remark" << endl;
    cout << "   No.       No.    Name            Marks" << endl;
    for (int i = 1; i < 78; i++)
    {
        cout << "-";
    }
}

void student::show()
{
    calcgd();
    cout << "\n\n ";
    cout << adm << "\t    " << rno << "     " << na << "   " << batch << "    " << calcmk() << "     " << percentage << "\t\t" << gd << "     " << remrk << endl;
}

// Function to add a record

void add()
{
    cout << "\n\n\t\t\t ----- WELCOME TO ONLINE PORTAL OF DELHI TECHNOLOGICAL UNIVERSITY ----- \n\n";
    fstream ff;
    student x;
    char ch = 'y';
    ff.open("ckl.DAT", ios::in | ios::app | ios::binary);
    ff.seekp(0, ios::beg);
    while (ch == 'y')
    {
        cout << "  --- Enter the data ---\n\n " << endl;
        x.getdata();
        ff.write((char *)&x, sizeof(x));
        cout << " Do you enter more data ( y / n ) ? " << endl;
        cout << " ";
        cin >> ch;
        cout<<"\n\n";
    }
    ff.close();
}

// Function to modify a particular record

void modify()
{
    cout << "\n\n\t\t\t ----- WELCOME TO ONLINE PORTAL OF DELHI TECHNOLOGICAL UNIVERSITY ----- \n\n";
    int ad, n = 0, f = 0, p = 0;
    fstream ff;
    student x;
    ff.open("ckl.DAT", ios::in | ios::out | ios::binary);
    cout << " Enter the student's admission number whose record has to be modified : ";
    cin >> ad;
    ff.seekg(0, ios::beg);
    while (ff.read((char *)&x, sizeof(x)))
    {
        n++;
        if (ad == x.getadm())
        {
            cout << "\n Record is Found ! \n" << endl;
            x.display();
            x.show();
            cout << "\n Enter the new data " << endl;
            x.getdata();
            p = (n - 1) * sizeof(x);
            ff.seekp(p, ios::beg);
            ff.write((char *)&x, sizeof(x));
            f = 1;
            break;
        }
    }
    if (f == 0)
        cout << " Record Not Found ";
    else
        cout << "\n\n Record Updated  ";
    ff.close();
    cout << "\n Press ENTER key to return to Main Menu.......... ";
}

// Funcion to delete a particular record

void dele()
{
    cout << "\n\n\t\t\t   ----- WELCOME TO ONLINE PORTAL OF DELHI TECHNOLOGICAL UNIVERSITY ----- \n\n";
    fstream ff, rr;
    student x;
    int ad, f = 0;
    ff.open("ckl.DAT", ios::in | ios::binary);
    rr.open("temp.DAT", ios::out | ios::binary);
    cout << endl;
    cout << " Enter the admission no to  be searched : ";
    cin >> ad;
    ff.seekg(0, ios::beg);
    rr.seekp(0, ios::beg);
    while (ff.read((char *)&x, sizeof(x)))
    {
        if (ad == x.getadm())
        {
            cout << "\n RECORD IS FOUND AND THE RECORD IS : \n";
            x.display();
            x.show();
            cout << endl;
            for (int i = 1; i < 78; i++)
            {
                cout << "-";
            }
            cout<<"\n";
            f = 1;
        }
        else
        {
            rr.write((char *)&x, sizeof(x));
        }
    }
    cout << endl;
    if (f == 0)
    {
        cout << " RECORD NOT FOUND " << endl;
    }
    else
    {
        cout << " This record is deleted ! " << endl;
        ff.close();
        rr.close();
        remove("ckl.DAT");
        rename("temp.DAT", "ckl.DAT");
    }
    cout << "\n Press ENTER key to return to Main Menu.......... ";
}

// Function to display all records

void disp()
{
    cout << "\n\n\t\t\t ----- WELCOME TO ONLINE PORTAL OF DELHI TECHNOLOGICAL UNIVERSITY ----- \n\n";
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf(" Date : %d-%d-%d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    cout << "\n\n\t\t\t\t   ALL RECORDS \n\n";
    int i;
    student x;
    fstream ff;
    ff.open("ckl.DAT", ios::in | ios::binary);
    x.display();
    ff.seekg(0, ios::beg);
    while (ff.read((char *)&x, sizeof(x)))
    {
        x.show();
    }
    cout << "\n";
    for (i = 1; i < 78; i++)
    {
        cout << "-";
    }
    ff.close();
}

// Function to search record batch wise

void search()
{
    cout << "\n\n\t\t\t ----- WELCOME TO ONLINE PORTAL OF DELHI TECHNOLOGICAL UNIVERSITY ----- \n\n";
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf(" Date : %d-%d-%d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    int f = 0;
    fstream ff;
    student x;
    char cls[100];
    cout << "\n  Enter the batch name whose result has to be displayed : ";
    cin >> cls;
    cout<<"\n  The Result of the batch "<<cls<<" is -";
    cout << "\n";
    ff.open("ckl.DAT", ios::in | ios::binary);
    ff.seekg(0, ios::beg);
    while (ff.read((char *)&x, sizeof(x)))
    {
        if (cls == x.getstd())
        {
            f = 1;
        }
        else
            f = 0;
        if (f == 1)
        {
            x.show();            
        }
        else
            cout << "\n Record Not Found ";
    }
    ff.close();
    cout << "\n\nPress ENTER key to return to Main Menu..........";
}

// Function to show the record of a particular student

void report()
{
    cout << "\n\n\t\t\t ----- WELCOME TO ONLINE PORTAL OF DELHI TECHNOLOGICAL UNIVERSITY ----- \n\n";
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf(" Date : %d-%d-%d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    fstream ff;
    student x;
    int ad;
    cout << "\n Enter the admission no to be searched : ";
    cin >> ad;
    cout << "\n";
    cout << "\n\t\t\t\t     REPORT CARD OF THE ADMISSION NUMBER " <<ad<<" IS - \n"<< endl;
    ff.open("ckl.DAT", ios::in | ios::binary);
    x.display();
    ff.seekg(0, ios::beg);
    while (ff.read((char *)&x, sizeof(x)))
    {
        if (ad == x.getadm())
        {
            x.show();
            cout << endl;
            for (int i = 1; i < 78; i++)
            {
                cout << "-";
            }
        }
        else
        {
            cout << "\n\n Record Not Found";
        }    
    }
    ff.close();
}

// Main Function

int main()
{
    int ch = 1; //ch=1 has been taken for initialization of loop.
    while (ch != 7)
    {
        cout << "\n\n\t\t\t ----- WELCOME TO ONLINE PORTAL OF DELHI TECHNOLOGICAL UNIVERSITY ----- \n\n";
        cout << "1. Add a record " << endl;
        cout << "2. Modify a record" << endl;
        cout << "3. Delete a record" << endl;
        cout << "4. Show all record" << endl;
        cout << "5. Show records Batch wise" << endl;
        cout << "6. Report of student" << endl;
        cout << "7. Exit \n\n";
        cout << "  Enter your choice : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            add();
            break;
        case 2:
            modify();
            break;
        case 3:
            dele();
            break;
        case 4:
            disp();
            break;
        case 5:
            search();
            break;
        case 6:
            report();
            break;
        case 7:
            exit(0);
        default:
            cout << "\nInvalid choice....\n";
        }
    }
    return 0;
}