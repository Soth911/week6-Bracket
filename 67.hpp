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
    string team;            
    Node* left = nullptr;
    Node* right = nullptr;
    int point;
    bool isLeaf = false;
};


class Bracket{
    private :
    queue<Node*> teamList;
    queue<Node*> qualify ;
    queue<Node*> semiFinal ;
    queue<Node*> finall ;
    queue<Node*> matchList;
    int currentTeam = 0;
    int maxTeam = 8 ;
    int match = 1;
    int round = 1;
    vector<Node*> allMatches;
    public :

    void input(){
        for (int i=0;i<8;i++){
            string nam;
            cout<<"Enter name : ";
            cin>>nam;
            insertTeam(nam);
        }
        
    }

    void insertTeam(const string& name){
        if (currentTeam>=maxTeam){
            cout<<"Full slot cannot insert team "<< name <<endl;
            return;
        }
        Node* teamName = new Node;
        teamName->team=name;
        teamName->isLeaf=true;
        teamList.push(teamName);
        currentTeam++;
    }

    void matching(){
        if (teamList.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        if (round<3){
            // --- Step 1: extract queue into vector ---
             vector<Node*> arr;
             while (!teamList.empty()) {
                 arr.push_back(teamList.front());
                 teamList.pop();
             }
     
             // --- Step 2: shuffle vector (randomize order) ---
             random_device rd;
             mt19937 g(rd());
             shuffle(arr.begin(), arr.end(), g);
     
             // --- Step 3: rebuild teamList with shuffled teams ---
             for (Node* t : arr) {
                 teamList.push(t);
             }

        }


        



        
        matchList = queue<Node*>(); 
        queue<Node*> temp = teamList;
        while (!temp.empty()) {
            Node* parent = new Node;
            parent->left = temp.front();
            temp.pop();
            if (temp.empty()) break;
            parent->right = temp.front();
            temp.pop();
            matchList.push(parent);
            allMatches.push_back(parent);
        }
        

        if(round==1){
            qualify=teamList;
        } 
        else if(round==2){
            semiFinal=teamList;
        } 
        else if(round==3){
            finall=teamList;
        }

    }

    void all(){
        cout << "All Matches :" << endl;
        for (size_t i = 0; i < allMatches.size(); i++) {
        Node* match = allMatches[i]; 
        cout << match->left->team << " vs " << match->right->team << endl;
        }
        cout<<endl;

    }

    void lca(const string& a, const string& b){
        bool found = false;

        for (Node* match : allMatches) {
            if (match->left && match->right){
                if((match->left->team==a || match->right->team==a) && (match->left->team==b || match->right->team==b)){
                    cout<<a<<" met "<<b<<endl;
                    found = true;
                }
            }
        

        
        }

    if (!found) {
        cout << "No match found for team " << a << " and " << b <<endl;
    }
    }

    void atMatch(int x){
        if (x>7||x<1){
            cout<<"We have only 7 matches or less than"<<endl;
            return;
        }

        cout << "Match "<< x << endl;
        if (x<5){
            cout<<"Qualify match"<<endl;
        }else if(x<7){
            cout<<"Semi Final match"<<endl;
        }else{
            cout<<"Final match"<<endl;
        }
        Node* match = allMatches[x-1]; 
        cout << match->left->team << " vs " << match->right->team << endl;
        if(match->left->point > match->right->point){
            cout<<match->left->team<<" won"<<endl;
        }else{
            cout<<match->right->team<<" won"<<endl;
        }
        cout<<endl;
    }

    void searchMatch(const string& what) {
    bool found = false;

    for (Node* match : allMatches) {


        if (!match->left) continue;


        if (match->right) {
            if (match->left->team == what || match->right->team == what) {
                cout << match->left->team << " vs " << match->right->team << endl;
                found = true;
            }
        }

        else {
            if (match->left->team == what) {
                cout << match->left->team << " gets a bye" << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No match found for team: " << what << endl;
    }
    cout<<endl;
}


    void printTeams(){
        if (matchList.empty()) {
            cout << "No matches!\n";
            return;
        }
        queue<Node*> temp = matchList;
        while(!temp.empty()){
            Node* temp2 = temp.front();
            temp.pop();
            cout<<temp2->left->team<<endl;
            cout<<temp2->right->team<<endl;
        }

    }
    void printQualify() {
        queue<Node*> temp = qualify; 
        cout << "Quarterfinal teams:" << endl;
        while (!temp.empty()) {
            cout << temp.front()->team << endl;
            temp.pop();
        }
        cout << endl;
    }
    void printSemiFinal() {
        queue<Node*> temp = semiFinal;
        cout << "Semifinal teams:" << endl;
        while (!temp.empty()) {
            cout << temp.front()->team << endl;
            temp.pop();
        }
        cout << endl;
    }

    void printFinal() {
        queue<Node*> temp = finall;
        cout << "Final teams:" << endl;
        while (!temp.empty()) {
            cout << temp.front()->team << endl;
            temp.pop();
        }
        cout << endl;
    }


    void play(){
        if (matchList.empty()) {
            cout << "No matches!\n";
            return;
        }
        queue<Node*> temp = matchList;
        while(!temp.empty()){
            Node* temp2 = temp.front();
            temp.pop();
            temp2->left->point=rand()%20;
            temp2->right->point=rand()%20;
        }
    }

    void printPoint(){
        play();
        if (matchList.empty()) {
            cout << "No matches!\n";
            return;
        }
        queue<Node*> temp = matchList;
        cout<<"=== Round "<<round<<" ==="<<endl;
        while(!temp.empty()){
            Node* temp2 = temp.front();
            temp.pop();
            cout<< temp2->left->team << " : "<<temp2->left->point<<endl;
            cout<< temp2->right->team << " : " <<temp2->right->point<<endl;
            cout<<endl;
        }
        round++;
    }

    void thinking(Node* team1, Node* team2, queue<Node*>& next){
        while (team1->point == team2->point){
                cout << "Tie! Rematch: "<<endl;
                team1->point=rand()%20;
                team2->point=rand()%20;
                cout<<team1->team<<" : "<<team1->point<<endl;
                cout<<team2->team<<" : "<<team2->point<<endl;
            }
       if (team1->point > team2->point){
        next.push(team1);
       }else {
        next.push(team2);
       }
    }

    void update(){
        if (teamList.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        if (teamList.size() == 1) { 
            cout << "Winner: " << teamList.front()->team << endl;
            return;
        }

        queue<Node*> temp = matchList;
        queue<Node*> next;
        while(!temp.empty()){ 
           Node* temp2 = temp.front();
           temp.pop();
           thinking(temp2->left, temp2->right, next);
        }
        matchList = next;
        teamList = next;
    }

    void toEnd(){
        //1
        matching();
        printTeams();
        cout<<endl;
        printPoint();
        cout<<endl;
        update();
        //2
        matching();
        cout<<endl;
        printPoint();
        cout<<endl;
        update();
        //3
        matching();
        cout<<endl;
        printPoint();
        cout<<endl;
        update();

        update();
        cout<<endl;
        
    }
    
   
  
};