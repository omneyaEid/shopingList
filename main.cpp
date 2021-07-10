#include <iostream>
#include <fstream>
#include <sstream>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;

class shoppingList
{
public:
    char Name[15];
    char Category[15];
    int quantity;

};
struct PIndex
{
    int RRN;
    char Name[15];
    bool operator<(const PIndex& r) const   // for the sort function
    {
        return strcmp(Name, r.Name) < 0;
    }
};
struct SIndex
{
    char Name[10];
    char Category[15];
    bool operator<(const SIndex& r) const   // for the sort function
    {
        if (strcmp(Category, r.Category) == 0)
            return strcmp(Name, r.Name) < 0;
        return strcmp(Category, r.Category) < 0;
    }
};

shoppingList GetItem(int RNN, fstream& infile)
{
    shoppingList item;
    infile.seekg(RNN * 40, ios::beg);
    infile.read((char*)&item, sizeof item);
    return item;
}
int GetRecordRRN(PIndex PrmIndxArray[], int numRec, string Name)
{
    int RRN = -1;
    int low = 0, mid, high = numRec - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (Name < PrmIndxArray[mid].Name)
            high = mid - 1;
        else if (Name > PrmIndxArray[mid].Name)
            low = mid + 1;
        else
        {
            RRN = PrmIndxArray[mid].RRN;
            break;
        }
    }
    return RRN;
}
string GetItemName(SIndex ScndIndxArray[], int numRec, string Name)
{
    string name = "";
    int low = 0, mid, high = numRec - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (Name < ScndIndxArray[mid].Category)
            high = mid - 1;
        else if (Name > ScndIndxArray[mid].Category)
            low = mid + 1;
        else
        {
            name = ScndIndxArray[mid].Name;
            break;
        }
    }
    return name;
}
//help functions
void WritePrimIndex(PIndex PrmIndxArray[], int numRec, fstream& outfile)
{
    for (int i = 0; i < numRec; i++)
        outfile.write((char*)&PrmIndxArray[i], sizeof PrmIndxArray[i]);
}
void WriteScndIndex(SIndex ScndIndxArray[], int numRec, fstream& outfile)
{
    for (int i = 0; i < numRec; i++)
        outfile.write((char*)&ScndIndxArray[i], sizeof ScndIndxArray[i]);
}
void ReadPrimIndex(PIndex PrmIndxArray[], int numRec, fstream& inFile)
{
    for (int i = 0; i < numRec; i++)
        inFile.read((char*)&PrmIndxArray[i], sizeof PrmIndxArray[i]);
}
void ReadScndIndex(SIndex ScndIndxArray[], int numRec, fstream& inFile)
{
    for (int i = 0; i < numRec; i++)
        inFile.read((char*)&ScndIndxArray[i], sizeof ScndIndxArray[i]);
}
int AddItems() {
  fstream file, PrimIndex, ScndIndex;
  file.open("Shopping List.txt", ios::out);
  PrimIndex.open("Primary.txt", ios::out);
  ScndIndex.open("Secondry.txt", ios::out);
  int numRec;
  cout << "Enter Number Of Items You Want To Add" << endl;
  cin >> numRec;
  PIndex * PrmIndxArray = new PIndex[numRec];
  SIndex * ScndIndxArray = new SIndex[numRec];
  shoppingList * t = new shoppingList[numRec];
  for (int i = 0; i < numRec; i++) {
    shoppingList tmp;
    cout << endl << "Enter item " << i + 1 << " Name (Max 15 Letters):";
    cin >> tmp.Name;
    cout << "Enter item  " << i + 1 << " Category (Max 15 Letters) :";
    cin >> tmp.Category;
    cout << "Enter item  " << i + 1 << " quantity (int) :";
    cin >> tmp.quantity;
    t[i] = tmp;
    PrmIndxArray[i].RRN = i;
    strcpy(PrmIndxArray[i].Name, tmp.Name);
    strcpy(ScndIndxArray[i].Name, tmp.Name);
    strcpy(ScndIndxArray[i].Category, tmp.Category);
    file.write((char * ) & (t[i]), sizeof(t[i]));
  }
  sort(PrmIndxArray, PrmIndxArray + numRec);
  sort(ScndIndxArray, ScndIndxArray + numRec);
  WritePrimIndex(PrmIndxArray, numRec, PrimIndex);
  WriteScndIndex(ScndIndxArray, numRec, ScndIndex);
  file.close();
  PrimIndex.close();
  ScndIndex.close();
  return numRec;
}

void SearchByName(int numRec, string Name) {
  fstream file, PrimIndex;
  file.open("Shopping List.txt", ios:: in );
  PrimIndex.open("Primary.txt", ios:: in );
  PIndex * PrmIndxArray = new PIndex[numRec];
  shoppingList * item = new shoppingList[numRec];
  ReadPrimIndex(PrmIndxArray, numRec, PrimIndex);
  shoppingList t;
  int RRN;
  transform(Name.begin(), Name.end(), Name.begin(), ::tolower);
  RRN = GetRecordRRN(PrmIndxArray, numRec, Name);
  t = GetItem(RRN, file);
  cout << endl << "item name : " << t.Name << "  Category: " << t.Category <<
    " quantity : " << t.quantity << endl;

  file.close();
  PrimIndex.close();
}

void SearchByCategory(int numRec,string Category)
{
    fstream file, PrimIndex, ScndIndex;
    file.open("Shopping List.txt", ios::in);
    PrimIndex.open("Primary.txt", ios::in);
    ScndIndex.open("Secondry.txt", ios::in);
    PIndex* PrmIndxArray = new PIndex[numRec];
    SIndex* ScndIndxArray = new SIndex[numRec];
    shoppingList* sl = new shoppingList[numRec];
    ReadPrimIndex(PrmIndxArray, numRec, PrimIndex);
    ReadScndIndex(ScndIndxArray, numRec, ScndIndex);
    string Name;
    shoppingList s;
    int RRN;
transform(Category.begin(), Category.end(), Category.begin(), ::tolower);
    Name = GetItemName(ScndIndxArray, numRec, Category);

    if (Name == "")
    {
        cout << endl << "Category name not exist" << endl;
        return;
    }
    RRN = GetRecordRRN(PrmIndxArray, numRec, Name);
    s = GetItem(RRN, file);
    cout << endl << "item name : " << s.Name << "  Category: " << s.Category
         << "  quantity: " << s.quantity << endl;
    file.close();
    PrimIndex.close();
    ScndIndex.close();
}
void print_Names()
{
    fstream file;
    file.open("Shopping List.txt", ios::in);
    shoppingList names ;
    file.read((char*)&names, sizeof(names));
    cout<<"list of items names \n";
    while (!file.eof())
    {
        cout << names.Name<< "  ";
        file.read((char*)&names, sizeof(names));
        cout<<endl;
    }
    file.close();
}
void print_categories(int numRec)
{
    int c=0;
    fstream  ScndIndex;
    ScndIndex.open("Secondry.txt", ios::in);
    SIndex* ScndIndxArray = new SIndex[numRec];
    ReadScndIndex(ScndIndxArray, numRec, ScndIndex);
    cout<<"list of items categories \n";

    string catogeryArr[numRec];

    for(int i=0; i<numRec; i++)
    {
        for(int g=0; g<numRec; g++)
        {
            if(catogeryArr[g]==ScndIndxArray[i].Category)
                c++;
        }
        if(c==0)
            catogeryArr[i]=ScndIndxArray[i].Category;
        else
            c=0;
    }
    for(int i=0; i<numRec; i++)
        cout<<catogeryArr[i]<<endl;

    ScndIndex.close();
}
void count_categories(int numRec)
{
    int c=0;
    fstream  ScndIndex;
    ScndIndex.open("Secondry.txt", ios::in);
    SIndex* ScndIndxArray = new SIndex[numRec];
    ReadScndIndex(ScndIndxArray, numRec, ScndIndex);

    string arr[numRec]; //for catogeries

    for(int i=0; i<numRec; i++)
    {
        for(int g=0; g<numRec; g++)
        {
            if(arr[g]==ScndIndxArray[i].Category)
                c++;
        }
        if(c==0)
            arr[i]=ScndIndxArray[i].Category;
        else
            c=0;
    }
    for (size_t i = 0; i < sizeof(arr)/sizeof(*arr); i++)
    {
        if (arr[i] != "")
            c++;
    }
    cout<<"items Count = "<<c<<endl;
    ScndIndex.close();


};
void count_Items()
{
    fstream file;
    file.open("Shopping List.txt", ios::in);
    shoppingList items ;
    file.read((char*)&items, sizeof(items));
    int itemsCount=0;
    while (!file.eof())
    {
        file.read((char*)&items, sizeof(items));

        itemsCount++;
    }
    cout<<"items Count = " <<itemsCount<<endl;
    file.close();
};

void printQuantityByName(int numRec,string itemName)
{
    fstream file, PrimIndex;
    file.open("Shopping List.txt", ios::in);
    PrimIndex.open("Primary.txt", ios::in);
    PIndex* PrmIndxArray = new PIndex[numRec];
    shoppingList* item = new shoppingList[numRec];
    ReadPrimIndex(PrmIndxArray, numRec, PrimIndex);//read from primIndex into primIndexArray
    char Name[15];
    shoppingList t;
    int RRN;
    RRN = GetRecordRRN(PrmIndxArray, numRec, itemName);
    t = GetItem(RRN, file);
    cout<<"The Quantity Of "<<t.Name<<" = "<<t.quantity<<endl;
    file.close();
    PrimIndex.close();

};
void printQuantityByCatogery(int numRec,string Category)
{

     fstream file, PrimIndex, ScndIndex;
    file.open("Shopping List.txt", ios::in);
    PrimIndex.open("Primary.txt", ios::in);
    ScndIndex.open("Secondry.txt", ios::in);
    PIndex* PrmIndxArray = new PIndex[numRec];
    SIndex* ScndIndxArray = new SIndex[numRec];
    shoppingList* sl = new shoppingList[numRec];
    ReadPrimIndex(PrmIndxArray, numRec, PrimIndex);
    ReadScndIndex(ScndIndxArray, numRec, ScndIndex);
    string Name;
    shoppingList s;
    int RRN;
transform(Category.begin(), Category.end(), Category.begin(), ::tolower);
    Name = GetItemName(ScndIndxArray, numRec, Category);
    RRN = GetRecordRRN(PrmIndxArray, numRec, Name);
    s = GetItem(RRN, file);
    cout<<"quantity: " << s.quantity << endl;
    file.close();
    PrimIndex.close();
    ScndIndex.close();

//    fstream  ScndIndex;
//    int q;
//    ScndIndex.open("Secondry.txt", ios::in);
//    SIndex* ScndIndxArray = new SIndex[numRec];
//    ReadScndIndex(ScndIndxArray, numRec, ScndIndex);
//    for(int i=0; i<numRec; i++)
//    {
//        if(ScndIndxArray[i].Category==Category)
//            q++;
//    }
//
//    cout<<"The Quantity Of "<<Category<<" = "<<q<<endl;
//    ScndIndex.close();
};
void update(int numRec,string itemName)
{
    fstream file, PrimIndex, ScndIndex;
    int choice,RRN,quantity;
    char Name[15] , category[15];
    file.open("Shopping List.txt",ios::out|ios::in);
    PrimIndex.open("Primary.txt", ios::in|ios::out);
    ScndIndex.open("Secondry.txt", ios::in|ios::out);

    PIndex* PrmIndxArray = new PIndex[numRec];
    SIndex* ScndIndxArray = new SIndex[numRec];
    shoppingList* sl = new shoppingList[numRec];

    ReadPrimIndex(PrmIndxArray, numRec, PrimIndex);
    ReadScndIndex(ScndIndxArray, numRec, ScndIndex);

    RRN=GetRecordRRN(PrmIndxArray,numRec,itemName);
    shoppingList s;
    PIndex prim;
    SIndex sec;
    s=GetItem(RRN,file);

    cout<<"Name : "<<s.Name<<" Category : "<<s.Category<<" Quantity : "<<s.quantity<<endl;
    cout<<"1) Update item Name"<<endl;
    cout<<"2) Update item Category"<<endl;
    cout<<"3) Update item Quantity"<<endl;
    cout<<"4) Update both (Category&&Quantity)"<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:

        cout<<"Enter New Name"<<endl;
        cin>>Name;
        strcpy(s.Name,Name);

        strcpy(prim.Name,Name);
        prim.RRN=RRN;

        strcpy(sec.Name,Name);

        //first updating the data file
        file.seekg(RRN*sizeof(s), ios::beg);
        file.write((char*)&s,sizeof(s));


        PrimIndex.seekg(RRN*sizeof(prim), ios::beg);
        PrimIndex.write((char*)&prim,sizeof(prim));

        ScndIndex.seekg(RRN*sizeof(sec.Name), ios::beg);
        ScndIndex.write((char*)&sec.Name,sizeof(sec.Name));


        break;
    case 2:
        cout<<"Enter New Category"<<endl;
        cin>>category;
        strcpy(s.Category,category);
        strcpy(Name,s.Name);
        file.seekg(RRN*sizeof(s), ios::beg);
        file.write((char*)&s,sizeof(s));

        strcpy(sec.Category,category);
        strcpy(sec.Name,Name);


        ScndIndex.seekg(RRN*sizeof(sec), ios::beg);
        ScndIndex.write((char*)&sec,sizeof(sec));

        break;
    case 3:
        cout<<"Enter New Quantity"<<endl;
        cin>>quantity;
        s.quantity=quantity;
        file.seekg(RRN*sizeof(s), ios::beg);
        file.write((char*)&s,sizeof(s));
        break;
    case 4:
        cout<<"Enter New Category"<<endl;
        cin>>category;
        cout<<"Enter New Quantity"<<endl;
        cin>>quantity;
        ///update category in file
         s.quantity=quantity;
        file.seekg(RRN*sizeof(s), ios::beg);
        file.write((char*)&s,sizeof(s));

        ///update category in file , secindex
        strcpy(s.Category,category);
        strcpy(Name,s.Name);
        file.seekg(RRN*sizeof(s), ios::beg);
        file.write((char*)&s,sizeof(s));

        strcpy(sec.Category,category);
        strcpy(sec.Name,Name);


        ScndIndex.seekg(RRN*sizeof(sec), ios::beg);
        ScndIndex.write((char*)&sec,sizeof(sec));
        break;
    }
    cout<<"Name : "<<s.Name<<" Category : "<<s.Category<<" Quantity : "<<s.quantity<<endl;

    file.close();
    PrimIndex.close();
    ScndIndex.close();

}
int main()
{
    int ch1,ch2;
    int numRec;
    string userInput=" ";
    do
    {
        cout<<endl;
        cout<<"1) Add New Item To Your Shopping List"<<endl;
        cout<<"2) print all items name in Shopping list"<<endl;
        cout<<"3) print all items categories in Shopping list"<<endl;
        cout<<"4) Print quantity of an item in shopping list "<<endl;
        cout<<"5) Count the number of items"<<endl;
        cout<<"6) Count the number of Categories"<<endl;
        cout<<"7) Search for item "<<endl;
        cout<<"8) Update item information"<<endl;
        cout<<"9) Exit"<<endl;
        cin >>ch1;
        cout<<endl;
        switch(ch1)
        {

        case 1:
            numRec = AddItems();
            break;
        case 2:
            print_Names();
            break;
        case 3:
            print_categories(numRec);
            break;

        case 4:
        {
            cout<<"1) want to enter item name ? "<<endl;
            cout<<"2) want to enter Category name ?"<<endl;
            cin>>ch2;

            switch(ch2)
            {
            case 1:
                cout<<"Enter Item Name ,please"<<endl;
                cin>>userInput;
                printQuantityByName(numRec,userInput);
                break;
            case 2:
                cout<<"Enter Item Category ,please"<<endl;
                cin>>userInput;
                printQuantityByCatogery(numRec,userInput);
                break;
            }
        }
        break;
        case 5:
            count_Items();
            break;
        case 6:
            count_categories(numRec);
            break;

        case 7:
        {
            cout<<"1) search By Item Name"<<endl;
            cout<<"2) search By Item Category"<<endl;
            cin>>ch2;
            switch(ch2)
            {
            case 1:
                cout<<"Enter Item Name , please"<<endl;
                cin>>userInput;
                SearchByName(numRec,userInput);
                break;
            case 2:
                cout<<"Enter Item Category , please"<<endl;
                cin>>userInput;
                SearchByCategory(numRec,userInput);
                break;
            }

            break;
        }
        case 8:
            cout<<"Enter Item Name ,please"<<endl;
            cin>>userInput;
            update(numRec,userInput);
            break;
        } //end of switch
    }
    while(ch1!=9);
    return 0;
}

