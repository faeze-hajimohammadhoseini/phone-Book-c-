
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

class phoneBook
{
char name[20],phno[15];
public:
void getdata();
void showdata();
 char *getname(){ return name; }
    char *getphno(){ return phno; }
    void update(char *nm,char *telno){
        strcpy(name,nm);
        strcpy(phno,telno);
    }
};

void phoneBook :: getdata(){
    cout<<"\nEnter Name : ";
    cin>>name;
    cout<<"Enter Phone No. : ";
    cin>>phno;
}

void phoneBook :: showdata(){
    cout<<"\n";
    cout<<setw(20)<<name;
    cout<<setw(15)<<phno;
}


int main(){
    phoneBook rec;
    fstream file;
    file.open("C:/Users/Asus/Desktop/phone.txt", ios::ate | ios::in | ios::out | ios::binary );
    char c,ch,nm[20],telno[6];
    int choice,cnt,found=0;
    do{
        cout<<"\n*****Phone Book*****\n";
        cout<<"1) Add New Record\n";
        cout<<"2) Display All Records\n";
        cout<<"3) Search Telephone No.\n";
        cout<<"4) Search Person Name\n";
        cout<<"5) Update Telephone No.\n";
        cout<<"6) Exit\n";
        cout<<"Choose your choice : ";
        cin>>choice;
        switch(choice){
            case 1 : //New Record
                 rec.getdata();
                 file.write((char *) &rec, sizeof(rec));
   cout<<"Record Added Succesfully\n";
                 break;

            case 2 : //Display All Records
                 file.seekg(0,ios::beg);
                 cout<<"\n\nRecords in Phone Book\n";
                 while(file){
                    file.read((char *) &rec, sizeof(rec));
                    if(!file.eof())
                        rec.showdata();
                 }
                 file.clear();
   break;

            case 3 : //Search Tel. no. when person name is known.
                 cout<<"\n\nEnter Name : ";
                 cin>>nm;
                 file.seekg(0,ios::beg);
                 found=0;
                 while(file.read((char *) &rec, sizeof(rec)))
                 {
                    if(strcmp(nm,rec.getname())==0)
                    {
                        found=1;
                        rec.showdata();
                    }
                 }
                 file.clear();
                 if(found==0)
                    cout<<"\n\n---Record Not found---\n";
                    break;

            case 4 : //Search name on basis of tel. no
                 cout<<"\n\nEnter Telephone No : ";
                 cin>>telno;
                 file.seekg(0,ios::beg);
                 found=0;
                 while(file.read((char *) &rec, sizeof(rec)))
                 {
                    if(strcmp(telno,rec.getphno())==0)
                    {
                        found=1;
                        rec.showdata();
                    }
                 }
                 file.clear();
                 if(found==0)
                    cout<<"\n\n---Record Not found---\n";
                    break;

            case 5 : //Update Telephone No.
                 cout<<"\n\nEnter Name : ";
                 cin>>nm;
                 file.seekg(0,ios::beg);
                 found=0;
                 cnt=0;
                 while(file.read((char *) &rec, sizeof(rec)))
                 {
                    cnt++;
                    if(strcmp(nm,rec.getname())==0)
                    {
                        found=1;
                        break;
                    }
                 }
                 file.clear();
                 if(found==0)
                    cout<<"\n\n---Record Not found---\n";
                 else
                 {
                    int location = (cnt-1) * sizeof(rec);
                    cin.get(ch);
                    if(file.eof())
                        file.clear();

                    cout<<"Enter New Telephone No : ";
                    cin>>telno;
                    file.seekp(location);
                    rec.update(nm,telno);
                    file.write((char *) &rec, sizeof(rec));
                    file.flush();
                 }
                 break;
   case 6:
   break;
              }
cout<<"do you want to exit(y/n): ";
cin>>c;
    }while(c=='n'||c=='N');

file.close();
}