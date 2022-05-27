#include <iostream>
#include <string>
#include <fstream>
#include "BackEnd.h"
using namespace std;

BST :: BST(){}
void insert(BST *&p, BST *t)
{
    if (p == NULL)
    {
        p = t;
        return;
    }

    if (p->filename.compare(t->filename) < 0)
        insert(p->right, t);
    else
        insert(p->left, t);
}
void insert_all(BST *&t , string name, string date, string time)
{
    t->filename = name;
    t->date = date;
    t->time = time;
    t->right = t->left = NULL;
}
void restoring_data(BST *&root)
{
    ifstream in("info.txt");
    string t1, t2, t3;
    while (!in.eof())
    {
        in >> t1;
        in >> t2;
        in >> t3;
        BST *t = new BST();
        insert_all(t, t1, t2, t3);
        insert(root, t);
    }
}

void store_data(string name, string date, string time)
{
    ofstream in("info.txt", ios ::app);
    in << name << endl;
    in << date << endl;
    in << time << endl;
}

void checkFilename(string &filename)
{
    while ((filename[filename.size() - 1] != 't') || (filename[filename.size() - 2] != 'x') || (filename[filename.size() - 3] != 't') || (filename[filename.size() - 4] != '.'))
    {
        printf("Please enter the correct filename with \".txt\" file extention :\n--->");
        cin >> filename;
    }
}
void checkDate(string &date)
{
    while (date[4] != '-' || date[7] != '-')
    {
        printf("Please enter the date in the correct formate :--\n");
        printf(">>> [NOTE : Date must be in \"yyyy-mm-dd\" formate only]\n--->");
        cin >> date;
    }
}
void checkTime(string &time)
{
    while ((time[2] != '.' && time[2] != ':') || time.size() != 5)
    {
        printf("Please enter the time in the correct formate :--\n");
        printf("[NOTE : Time must be in \"HH.MM\" formate only]\n--->");
        cin >> time;
    }
}
void insert_name(BST *&t , string name)
{
    t->filename = name;
}
void insert_user(BST *&t)
{
    printf("--->Enter the file name [in .txt formate]:-\n");
    printf(">>> [ NOTE : Write new filename or else same name old file will be ereased ]\n--->");
    cin >> t->filename;
    checkFilename(t->filename);
    printf("--->Enter the date [yyyy-mm-dd]:\n--->");
    cin >> t->date;
    checkDate(t->date);
    printf("--->Enter the time [HH.MM]:\n--->");
    cin >> t->time;
    checkTime(t->time);
    t->left = t->right = NULL;
    store_data(t->filename, t->date, t->time);
}

BST *searchFile(BST *&p, string name)
{
    if (p == NULL || p->filename.compare(name) == 0)
    {
        return p;
    }

    if (name.compare(p->filename) > 0)
        return searchFile(p->right, name);
    else
        return searchFile(p->left, name);
}
BST *succesor(BST *t)
{
    while (t->left != NULL)
        t = t->left;
    return t;
}
BST *predessor(BST *t)
{
    while (t->right != NULL)
        t = t->right;
    return t;
}
int height(BST *p)
{
    int x = 0, y = 0;
    if (p == NULL)
        return 0;
    x = height(p->left);
    y = height(p->right);
    return ((x > y) ? (x + 1) : (y + 1));
}
BST *deleteFile(BST *&p, string name)
{
    if (p == NULL)
        return NULL;

    if (p->left == NULL && p->right == NULL)
    {
        remove(name.c_str());
        if (name.compare(p->filename) == 0)
        {
            p = NULL;
        }
        return NULL;
    }
    if (name.compare(p->filename) > 0)
        p->right = deleteFile(p->right, name);
    else if (name.compare(p->filename) < 0)
        p->left = deleteFile(p->left, name);
    else
    {
        if (height(p->left) > height(p->right))
        {
            BST *t = predessor(p);
            // remove(name.c_str());
            p->filename = t->filename;
            p->date = t->date;
            p->time = t->time;
            p->left = deleteFile(p->left, t->filename);
        }
        else
        {
            BST *t = succesor(p);
            p->filename = t->filename;
            p->date = t->date;
            p->time = t->time;
            p->right = deleteFile(p->right, t->filename);
        }
    }
    return p;
}