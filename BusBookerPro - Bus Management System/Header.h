#pragma once
#include<iostream>
using namespace std;
struct nodes {
	int seat = 0;
	nodes* right = NULL;
	nodes* left = NULL;
	string name = "";
};
// An AVL tree node
struct node
{
	int data;
	node* next;
};
// A Struct node
class AVL_tree {
private:
	struct nodes* root = NULL;
	struct node* front = NULL;
	struct node* rear = NULL;
	int seatsAvail = 47;
public:
	int avail();
	int height(nodes*);
	int balancefactors(nodes*);
	nodes* rightrotate(nodes*);
	nodes* leftrotate(nodes*);
	nodes* insert(nodes*, int, string);
	nodes* deletenode(nodes*, int);
	void display(nodes*);
	void inorder(nodes*);
	nodes* ret_root();
	bool search(int);
	void bus(int);
	void EnQueue(int);
	void DeQueue();
	friend void status(AVL_tree *obj, int& time);
	friend void booking(AVL_tree *obj, int a);
	friend void refund(AVL_tree *obj, int time);
};


//program

void menu(AVL_tree *obj, int);

