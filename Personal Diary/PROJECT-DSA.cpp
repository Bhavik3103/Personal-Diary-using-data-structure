#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "BackEnd.h"

using namespace std;

void addRecord(BST *&root);
void Inorder(BST *p);
void removeRecord(BST *&root);
void viewRecords(BST *&root);
void searchAndEditRecords(BST *&root);

void menu()
{
    system("cls");
    printf("\n\t\t\t\t*********************************************************************\n");
    printf("\t\t\t\t1. Add Record\n\t\t\t\t2. View Record\n\t\t\t\t3. Remove Record\n\t\t\t\t4. Edit Record\n\t\t\t\t5. Exit the program\n");
    printf("\t\t\t\t*********************************************************************\n");
    printf("\n>>>> Select any of the followig options\n -->");
}

int main()
{
    BST *root = NULL;
    restoring_data(root);
    // addRecord(root);
    // viewRecords(root);
    // searchAndEditRecord(root);
    // removeRecord(root);
    menu();
    int n;
    cin >> n;
    char c;
    while (1)
    {
        switch (n)
        {
        case 1:
            system("cls");
            addRecord(root);
            printf("\n\n\t\t\t>>>>The record has been successfully entered .\n");
            printf("\n\nPRESS ANY KEY TO CONTINUE\n");
            c = getchar();
            c = getchar();
            menu();
            cin >> n;
            break;
        case 2:
            system("cls");
            viewRecords(root);
            printf("\n\nPRESS ANY KEY TO CONTINUE\n");
            c = getchar();
            c = getchar();
            menu();
            cin >> n;
            break;
        case 4:
            system("cls");
            searchAndEditRecords(root);
            printf("\n\nPRESS ANY KEY TO CONTINUE\n");
            c = getchar();
            c = getchar();
            menu();
            cin >> n;
            break;
        case 3:
            system("cls");
            removeRecord(root);
            printf("\n\nPRESS ANY KEY TO CONTINUE\n");
            c = getchar();
            c = getchar();
            menu();
            cin >> n;
            break;
        case 5:
            printf("\n\nPRESS ANY KEY TO EXIT THE PROGRAM ... DO VISIT AGAIN :)\n");
            c = getchar();
            c = getchar();
            return 0;
        default:
            printf("\n\n\t\t\t>>>>ERROR :: Unknown command encountered");
            printf("\n\nPRESS ANY KEY TO CONTINUE\n");
            c = getchar();
            c = getchar();
            menu();
            cin >> n;
        }
    }

    return 0;
}

void Inorder(BST *p)
{
    if (p == NULL)
        return;

    Inorder(p->left);
    cout << p->filename << endl;
    cout << p->date << endl;
    cout << p->time << endl;
    Inorder(p->right);
}
void addRecord(BST *&root)
{
    BST *t = new BST();
    insert_user(t);
    ofstream FileOut(t->filename);

    FileOut << "\t\t\t\t\t\t\t\t" << t->filename << "\n";
    FileOut << "\t\t\tDATE : " << t->date << "\t\t\t\t\tTIME : " << t->time << "\n";

    string str = "--> ";
    string g = "Good bye";
    printf("--->Enter the daily note : [Write only \"Good bye\" at last line - to end the file]\n>>>>   ");
    while (str.compare(g) != 0)
    {
        getline(cin, str);
        FileOut << str << endl;
    }
    FileOut.close();
    if (root == NULL)
    {
        root = t;
        return;
    }

    BST *prev = NULL;
    BST *temp = NULL;

    temp = root;

    while (temp != NULL)
    {
        prev = temp;
        if (t->filename.compare(temp->filename) > 0)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }
    if (t->filename.compare(prev->filename) > 0)
    {
        prev->right = t;
    }
    else
    {
        prev->left = t;
    }
}

void viewRecords(BST *&root)
{
    string name;
    printf("\t\t\tEnter the name of the file in \".txt\" formate : ");
    cin >> name;
    BST *search = NULL;
    checkFilename(name);
    search = searchFile(root, name);

    printf("\t\t\t\t\tThe content of the file ");
    cout << search->filename << " is :--\n";
    printf("\n________________________________________________________________________________________________________\n");
    ifstream out(search->filename);
    string str;
    while (!out.eof())
    {
        getline(out, str);
        cout << str << "\n";
    }
    out.close();
    printf("\n________________________________________________________________________________________________________\n");
    cout << "\n\n";
}

void searchAndEditRecords(BST *&root)
{
    string name;
    printf("\t\t\tEnter the name of the file in \".txt\" formate : ");
    cin >> name;
    BST *search = NULL;
    checkFilename(name);
    search = searchFile(root, name);

    ifstream out(search->filename);
    string str;
    while (!out.eof())
    {
        getline(out, str);
        cout << str << "\n";
    }
    out.close();

    ofstream in(search->filename, ios ::app);
    str = "--> ";
    string g = "Good bye";
    printf("\n\n--->You can continue to enter from here : [Write only \"Good bye\" at last line - to end the file]\n>>>>   ");
    while (str.compare(g) != 0)
    {
        getline(cin, str);
        in << str << endl;
    }
    out.close();

    printf("\n\n\t\t\t\tThe note has been successfully edited in the file .");
}

void removeRecord(BST *&root)
{

    string line, name, date, time;
    printf("\t\t\tEnter the name of the file in \".txt\" formate : ");
    cin >> name;
    printf("\t\t\tEnter the date in this formate [YYYY-MM-DD] : ");
    cin >> date;
    printf("\t\t\tEnter the time in this formate [hh:mm] : ");
    cin >> time;
    ifstream myfile;
    ofstream temp;
    myfile.open("info.txt");
    temp.open("temp.txt");
    while (getline(myfile, line))
    {
        if (line == name || line == date || line == time)
            continue;
        else
            temp << line << endl;
    }
    cout << "The record with the name " << name << " has been deleted if it exsisted" << endl;
    myfile.close();
    temp.close();
    remove("info.txt");
    rename("temp.txt", "info.txt");
    deleteFile(root, name);
}