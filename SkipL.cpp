#include<iostream>
#include<cmath>
#include<cstdlib>
#include<conio.h>
using namespace std;

#define MAX_LEVEL 8

struct Node{
    int val;
    Node *right[100];

    Node(int level, int value)
    {
        memset(right, 0, sizeof(Node*)*(level+1));
        this->val = value;
    }
    ~Node()
    {
        delete right;
    }
};

struct NodeS{
    Node *start;
    int level;

    NodeS() {
        start = new Node(MAX_LEVEL,0);
        level = 0;
    }
    ~NodeS() {
        delete start;
    }
    void skip_print() const;
    bool skip_contains(int sval);
    void skip_insert(int value);
    void skip_erase(int dval);
    void skip_change(int cvalFrom,int cvalTo);
};
NodeS D;

int random_level() {
    static bool first = true;
    int lvl=0,a;
    if (first) {
        srand( (unsigned)time( NULL ) );
        first = false;
    }

    while(lvl<MAX_LEVEL)
    {
        a=rand()%2;
        if(a==1)
        {
            lvl++;
        }
        else
        {
            return lvl;
        }
    }

    return MAX_LEVEL;

}


void NodeS::skip_print() const {
    for(int i=MAX_LEVEL-1;i>=0;i--)
    {
    Node *x = start;
    while (x != NULL) {
        cout << x->val;
        x = x->right[i];
        if (x != NULL)
            cout << ",";
       //  else cout<<",   ";
    }
    cout << "\n";
    }
}
/*
bool NodeS::contains(int sval){
    Node *x = start;
    for (int i = level; i >= 0; i--) {
        while (x->right[i] != NULL && x->right[i]->val < sval) {
            x = x->right[i];
        }
    }
    x = x->right[0];
    return x != NULL && x->val == sval;
}

void NodeS::insert(int value) {
    Node *x = start;
    Node *ins[MAX_LEVEL + 1];
    int lvl=0;
    memset(ins, 0, sizeof(Node*)*(MAX_LEVEL + 1));

    for (int i = level; i >= 0; i--) {
        while (x->right[i] != NULL && x->right[i]->val < value) {
            x = x->right[i];
        }
        ins[i] = x;
    }
    x = x->right[0];


    if (x == NULL || x->val != value) {
        int lvl = random_level();

        if (lvl > level) {
	    for (int i = level + 1; i <= lvl; i++) {
	        ins[i] = start;
	    }
	    level = lvl;
	}


/*int a;
lvl=level+1;
        if (x == NULL || x->val != value) {

            while(lvl<MAX_LEVEL)
            {
            a=rand()%2;
            if(a==1)
            {
                ins[lvl] = start;
                lvl++;
            }
            else
            {
                break;
            }
            }

         level = lvl;
	   }
*/
/*        x = new Node(lvl, value);
	for(int i = 0; i <= lvl; i++) {
	    x->right[i] = ins[i]->right[i];
	    ins[i]->right[i] = x;
	}
    }
}*/

bool NodeS::skip_contains(int sval){
    Node *x = start;
    for (int i = level; i >= 0; i--) {
        while (x->right[i] != NULL && x->right[i]->val < sval) {
            x = x->right[i];
        }
    }
    x = x->right[0];
    return x != NULL && x->val == sval;
}

void NodeS::skip_insert(int value) {
    Node *x = start;
    Node *ins[MAX_LEVEL + 1];
    int lvl=0;
    memset(ins, 0, sizeof(Node*)*(MAX_LEVEL + 1));

    for (int i = level; i >= 0; i--) {
        while (x->right[i] != NULL && x->right[i]->val < value) {
            x = x->right[i];
        }
        ins[i] = x;
    }
    x = x->right[0];


    if (x == NULL || x->val != value) {
        int lvl = random_level();

        if (lvl > level) {
	    for (int i = level + 1; i <= lvl; i++) {
	        ins[i] = start;
	    }
	    level = lvl;
	}


/*int a;
lvl=level+1;
        if (x == NULL || x->val != value) {

            while(lvl<MAX_LEVEL)
            {
            a=rand()%2;
            if(a==1)
            {
                ins[lvl] = start;
                lvl++;
            }
            else
            {
                break;
            }
            }

         level = lvl;
	   }
*/
        x = new Node(lvl, value);
	for(int i = 0; i <= lvl; i++) {
	    x->right[i] = ins[i]->right[i];
	    ins[i]->right[i] = x;
	}
    }
}


void NodeS::skip_erase(int dval) {
    Node *x = start;
    Node *ins[MAX_LEVEL + 1];
    memset(ins, 0, sizeof(Node*)*(MAX_LEVEL + 1));

    for (int i = level; i >= 0; i--) {
        while (x->right[i] != NULL && x->right[i]->val < dval) {
            x = x->right[i];
        }
        ins[i] = x;
    }
    x = x->right[0];

    if (x->val == dval) {
        for (int i = 0; i <= level; i++) {
	    if (ins[i]->right[i] != x)
	        break;
	    ins[i]->right[i] = x->right[i];
	}
        delete x;
        while (level > 0 && start->right[level] == NULL) {
	    level--;
	}
    }
}


void NodeS::skip_change(int cvalFrom,int cvalTo) {

    if(D.skip_contains(cvalFrom))
    {
     D.skip_erase(cvalFrom);
    // ss.print();
     D.skip_insert(cvalTo);
     //ss.print();
    }
    else
    {
        cout<<"not present\n";
    }

}




int main()
{
int valu,choice,valu1,valu2;

while(1)
{
cout<<"Choice: 1.print 2.search 3.change 4.insert 5.delete 6.exit" <<endl;

    cin>>choice;

    if(choice==1)
    {
        D.skip_print();
    }

    if(choice==2)
    {
        cout<<"search value :";
        cin>>valu;
        D.skip_contains(valu);
    }
    if(choice==3)
    {
        cout<<"change from value to value :";
        cin>>valu1;
        cin>>valu2;
        D.skip_change(valu1,valu2);
    }
    if(choice==4)
    {
        cout<<"insert value :";
        cin>>valu;
        D.skip_insert(valu);
    }
    if(choice==5)
    {
        cout<<"delete value :";
        cin>>valu;
        D.skip_erase(valu);
    }
    if(choice==6)
    {
        exit(0);
    }



}
 getch();
 return 0;
}
