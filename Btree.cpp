#include<iostream>
#include<string>
#include<vector>

#include "Node.cpp"

using namespace std;

class Contact {
public:
    string name;
    string phone_number;
public:
    Contact() {
        Contact("", "");
    }
    
    Contact(string name, string phone_number) {
        this->name = name;
        this->phone_number = phone_number;
    }
    
    bool operator < (const Contact &contact)
    {
        return name<contact.name;
    }
    
    bool operator > (const Contact &contact)
    {
        return name>contact.name;
    }
    
    friend ostream & operator << (ostream &os, const Contact &contact)
    {
        os<<contact.name<<','<<contact.phone_number;
        return os;
    }
};

template<class T>
class Btree {
    Node<T> *root;
    int t;
    
    public :
    Btree (int _t) {
        t = _t;
        root = NULL;
    }
    
    void traverse () {
        if(root!=NULL)
            root->traverse();
    }
    
    vector<T> search(T k, bool(* cmp)(T a, T b)) {
        vector<T> result;
        if(root != NULL)
            root->search(k, cmp, result);
        return result;
    }
    
    Node<T> *search(T k) {
        return (root==NULL) ? NULL : root->search(k);
    }
    
    void insert(T k) {
        if(root == NULL) {
            root = new Node<T>(t, true);
            root->keys[0] = k;
            root->n = 1;
        }
        else {
            if(root->n == 2*t-1) {
                Node<T> *s = new Node<T>(t, false);
                
                s->C[0] = root;
                
                s->splitChild(0, root);
                
                int i=0;
                if(s->keys[0] < k)
                    i++;
                s->C[i]->insertNonFull(k);
                
                root = s;
            }
            else
                root->insertNonFull(k);
        }
    }
};

bool cmp(Contact a, Contact b) {
    for(int i=0; i<a.name.length(); i++)
        if(i >= b.name.length() || a.name[i] != b.name[i])
            return false;
    return true;
}

int main() {
    
    string name[]={"souvik Mondal",
        "souvik ",
        "avik",
        "asik das",
        "ajoy",
        "ajay",
        "anil",
        "sanjit",
        "sudip ",
        "subra",
        "nil",
        "nilu",
        "dipsita",
        "dipu",
        "binu",
        "vivek",
        "vijay",
        "nilesh",
        "rajnee",
        "soura",
        "ranjit",
        "rani"};
    string phone[]= {"65786","9874894778"
        ,"11122334333"
        ,"5664556655"
        ,"1234324"
        ,"2222222"
        ,"234235432"
        ,"2134214"
        ,"65656776"
        ,"167653471"
        ,"8723542534"
        ,"7826"
        ,"764321734815"
        ,"2343242"
        ,"3245322"
        ,"12343532"
        ,"324532"
        ,"3"
        ,"34564645"
        ,"5644e54455"
        ,"6785754"
        ,"5567876"};
    
    
    // Initialize btree
    int nodes;
    
    cout<<"Enter the number of nodes for btree : ";
    cin>>nodes;
    Btree<Contact> btree(nodes);
    
    cout<<"Initializing Btree..."<<endl<<endl;
    
    for(int i=0;i<22;i++)
        btree.insert(Contact(name[i],phone[i]));

    string s;
    
    cout<<"Enter some key string to search for : ";
    cin>>s;
    cout<<endl<<endl;
    
    cout<<"Searching for '"<<s<<"' in the database..."<<endl<<endl;
    Contact contact(s, "");
    vector<Contact> result = btree.search(contact, cmp);
    if(result.size()) {
        for(int i=0;i<result.size();i++)
            cout<<(i+1)<<": "<<result[i]<<endl;
    }
    else
        cout<<"No result found!";
    cout<<endl<<endl;;
    
    return 0;
}
