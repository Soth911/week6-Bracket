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

        Node* parent = new Node;
        while(!list.empty()){
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
            thinking();
            setPoint();
        }
        cout << "Champion: " << list.front()->playerName << endl;
    }
};