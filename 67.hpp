#include <iostream>
#include <string>
#include <queue>
#include <cstdlib> 
#include <ctime> 

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
    public :

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
        cout<<"Round "<<round<<endl;
        while(!temp.empty()){
            Node* temp2 = temp.front();
            temp.pop();
            cout<< temp2->left->team << " : "<<temp2->left->point<<endl;
            cout<< temp2->right->team << " : " <<temp2->right->point<<endl;
        }
        round++;
    }

    void thinking(Node* team1, Node* team2, queue<Node*>& next){
        while (team1->point == team2->point){
                cout << "Tie! Rematch: "<<endl;
                team1->point=rand()%20;
                team2->point=rand()%20;
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

        if (teamList.size() == 1) { // only one team left
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
    
  
};