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

        if(list.size()%2!=0){
            Node* nAme = new Node;
            nAme->playerName="BYE";
            nAme->isLeaf=true;
            list.push(nAme);
            currentTeam++;
        }


        int c;
        if(currentTeam<8){
            c=maxTeam-currentTeam;
        }

        for (int i=0;i<c;i++){
            Node* nAme = new Node;
            nAme->playerName="BYE";
            nAme->isLeaf=true;
            list.push(nAme);
            currentTeam++;
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
            if(temp.front()->playerName=="BYE"){
                temp.front()->point=0;
                temp.pop();
                continue;
            }
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

    Node* getLCA(Node* a, Node* b) {
        if (!a || !b) return nullptr;

        int depthA = 0, depthB = 0;
        Node* tempA = a;
        Node* tempB = b;
        while (tempA) { depthA++; tempA = tempA->parent; }
        while (tempB) { depthB++; tempB = tempB->parent; }

        while (depthA > depthB) { a = a->parent; depthA--; }
        while (depthB > depthA) { b = b->parent; depthB--; }

        while (a != b) {
            a = a->parent;
            b = b->parent;
        }

        return a;
    }

    void lcaQuery(const string& a, const string& b){
        if (list.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        Node* root = list.front(); 
        Node* leaf1 = findPlayer(root,a);
        Node* leaf2 = findPlayer(root,b);

        if (!leaf1 || !leaf2) {
            cout << "Player not found!" << endl;
            return;
        }

        Node* lca = getLCA(leaf1, leaf2);
        if (!lca) {
            cout << "LCA not found!" << endl;
            return;
        }

        cout << "\nMatch : " << lca->left->matchId << endl;
        cout << "Round : " << lca->left->round << endl;
        cout << lca->left->playerName << " vs " << lca->right->playerName << endl;
    }

    void printBracket() {
        if (list.empty()) {
            cout << "No bracket available!\n";
            return;
        }

        Node* root = list.front();

        queue<Node*> q;
        q.push(root);

        int currentRound = root->round; 

        cout << "\n====== Full Bracket ======\n";

        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();

            if (!cur->isLeaf && cur->left && cur->right) {

            if (cur->round != currentRound) {
                currentRound = cur->round;
                cout << "==========================\n";
            }

            if (cur->round == 1) 
                cout << "[Round 1] ";

            else if (cur->round == 2)
                cout << "[Round 2] ";

            else if (cur->right->parent == root)
                cout << "[Final] ";

            else
                cout << "[Round " << cur->round << "] ";

            cout << cur->left->playerName << " (" << cur->left->point << ") vs "
                 << cur->right->playerName << " (" << cur->right->point << ")  "
                 << "winner: " << cur->playerName << endl;
            }

            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }

        cout << "==========================\n";
        cout << "Champion: " << root->playerName << "\n";
    }



};