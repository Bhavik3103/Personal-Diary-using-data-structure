#pragma once
#include <iostream>
using namespace std;
class BST
{
public:
    string filename;
    string date;
    string time;
    BST *left, *right;

    // BST(string name);

    BST();
    // BST(string name, string date, string time);

    ~BST()
    {
    }
};
BST *searchFile(BST *&p, string name);
BST *succesor(BST *t);
BST *predessor(BST *t);
BST *deleteFile(BST *&p, string name);
int height(BST *p);

void insert(BST *&p, BST *t);

void restoring_data(BST *&root);

void store_data(string name, string date, string time);

void checkFilename(string &filename);

void checkDate(string &date);

void checkTime(string &time);

void insert_user(BST *&t);

void insert_name(BST *&t , string name);

void insert_all(BST *&t , string name , string date, string time);