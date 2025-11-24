#include <iostream>
#include <string>
#include <queue>
#include <cstdlib> 
#include <ctime> 
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct Node {
    int matchId = 0;
    string winner = "";
    int round = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    string playerName  = "";
    bool isLeaf = false;
    Node* parent = nullptr;
    int point=0;
};
class Bracket{
    private :
    int maxTeam=8;
    int currentTeam=0;
    int curMatch=1;
    queue<Node*> list;
    queue<Node*> matchList;
    public :

    void insertTeam(const string& name){
        if (currentTeam>=maxTeam){
            cout<<"Full slot cannot insert team "<< name <<endl;
            return;
        }
        Node* nAme = new Node;
        nAme->playerName=name;
        nAme->isLeaf=true;
        list.push(nAme);
        currentTeam++;
    }

    void ranDom(){
        if (list.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        vector<Node*> arr;
        while (!list.empty()) {
            arr.push_back(list.front());
            list.pop();
        }
     
        random_device rd;
        mt19937 g(rd());
        shuffle(arr.begin(), arr.end(), g);
     
        for (Node* t : arr) {
            list.push(t);
        }
    }

    void setPoint(){
        if (list.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        queue<Node*> temp=list;
        while(!temp.empty()){
            temp.front()->point=rand()%21;
            temp.pop();
        }
    }

    void setID(){
        int val=0;
        if (list.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        queue<Node*> temp=list;
        while(!temp.empty()){
            temp.front()->matchId=curMatch;
            temp.pop();
            if(val%2==0){
                curMatch++;
            }
            val++;
        }
    }

    void setRound(){
        if (list.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        queue<Node*> temp=list;
        while(!temp.empty()){
            if(temp.front()->isLeaf){
                temp.front()->round=1;
                temp.pop();
            }
        }
    }

    void matching(){
        if (list.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }
        matchList = queue<Node*>();
        while(!list.empty()){
            Node* parent = new Node;
            parent->left=list.front();

            list.pop();
            if (!list.empty()){
                parent->right=list.front();
                list.pop();
            }
            matchList.push(parent);
        }
    }

    void thinking(){
        if (matchList.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        queue<Node*> nextRound;
        while(!matchList.empty()){
            Node* left = matchList.front()->left;
            Node* right = matchList.front()->right;

            Node* parent = new Node;

            if (left->point > right->point) {
                parent->playerName = left->playerName; 
            } else {
                parent->playerName = right->playerName;
            }

            parent->left = left;
            parent->right = right;
            parent->isLeaf = false;
            parent->round = max(left->round, right->round) + 1;

            left->parent = parent;
            right->parent = parent;

            nextRound.push(parent);
            matchList.pop();
        }
        list = nextRound;
    }

    void play(){
        ranDom();
        setPoint();
        setID();
        setRound();
        while(list.size()>1){
            matching();
            cout<<"================"<<endl;
            printCur();
            thinking();
            setPoint();
            setID();
        }
        cout<<endl;
        cout << "Champion : " << list.front()->playerName << endl;
    }

    void printCur(){
        queue<Node*> temp = matchList;
        while(!temp.empty()){
            cout<<temp.front()->left->matchId;
            cout<<"  "<<temp.front()->left->playerName<<" "<<temp.front()->left->point<<" vs " ;
            cout<<temp.front()->right->playerName<<" "<<temp.front()->right->point<<endl;
            temp.pop();
        }
    }

    Node* findPlayer(Node* root, const string& name) {
        if (root == nullptr){
            return nullptr;
        } 
        if (root->isLeaf && root->playerName == name){
            return root;
        } 

        Node* left = findPlayer(root->left, name);
        if (left) return left;

        return findPlayer(root->right, name);
    }


    void pathQuery(const string& a){
        if (list.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        Node* root = list.front();
        Node* leaf = findPlayer(root,a);

        cout << "\nPath of " << a << " to the final:" << endl;

        Node* cur = leaf;
        while (cur->parent != nullptr) {
            Node* p = cur->parent;
            cout << "Round " << p->left->round << " : "
                << p->left->playerName << " vs " << p->right->playerName
                << " winner : " << p->playerName << endl;

        cur = p;
        }
    }

    void lcaQuery(const string& a,const string& b){
        if (list.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        bool isfound = false;

        Node* root = list.front();
        Node* leaf1 = findPlayer(root,a);
        Node* leaf2 = findPlayer(root,b);

        if (!leaf1 || !leaf2) {
            cout << "Player not found!" << endl;
            return;
        }

        while(leaf1 != leaf2 && leaf1->parent && leaf2->parent){
            leaf1=leaf1->parent;
            leaf2=leaf2->parent;
            if ((leaf1->parent==leaf2->parent)&&(leaf1->playerName==a)&&(leaf2->playerName==b)){
                isfound = true;
                break;
            } 
        }
        if((leaf1->parent==leaf2->parent)&&(leaf1->playerName==a)&&(leaf2->playerName==b)){
            Node* temp = leaf1->parent;
            cout<<"\nMatch : "<<temp->left->matchId<<endl;
            cout<<"Round : "<<temp->left->round<<endl;
            cout<<temp->left->playerName<<" vs "<<temp->right->playerName<<endl;
        }

        if(!isfound){
            cout<<"\nNot found "<<a<<" vs "<<b<<endl;
        }
    }

    

};