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
};


class Bracket{
    private :
    queue<Node*> teamList;
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
        teamList.push(teamName);
        currentTeam++;
    }

    void play(){
        if (teamList.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        queue<Node*> temp = teamList;
        while(!temp.empty()){
            int ran = rand()%21;
            temp.front()->point=ran;
            temp.pop();
        }
        
    }

    void printTeams(){
        if (teamList.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        queue<Node*> temp = teamList;
        int num = 1;
        while(!temp.empty()){
            cout<<"Team"<<num<<" : "<<temp.front()->team<<endl;
            temp.pop();
            num++;
        }
    }

    void printPoint(){
        if (teamList.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }
        queue<Node*> temp = teamList;
        int num = 1;
        while(!temp.empty()){ 
            if (num%2!=0){
                cout<<"Match "<<match<<endl;
                match++;
            }
            cout<<"Team"<<num<<" : "<<temp.front()->team<< " has point "<<temp.front()->point <<endl;
            temp.pop();
            num++;
        }
    }

    void winner(){
        if (teamList.size() == 1) {
        Node* champ = teamList.front();
        cout << "Winner: " << champ->team 
             << " with " << champ->point << " points!" << endl;
    }
    }

    void update(){
        if (teamList.empty()){
            cout<<"No team yet!"<<endl;
            return;
        }

        queue<Node*> temp = teamList;
        queue<Node*> next;
        while(!temp.empty()){ 
           Node* team1 = temp.front();
           temp.pop();
           Node* team2 = nullptr;
           if (!temp.empty()){
            team2=temp.front();
            temp.pop();
           }
           if(team2==nullptr){
            next.push(team1);
           }else {
            if (team1->point>team2->point){
                next.push(team1);
            }else if (team1->point<team2->point){
                next.push(team2);
            }else {
                while(team1->point==team2->point){
                    team1->point = rand() % 21;
                    team2->point = rand() % 21;
                    cout << "Tie! Rematch: "<<endl;
                    cout << team1->team << " has point " << team1->point <<endl;
                    cout << team2->team << " has point " << team2->point <<endl;
                    update();
                }
            }
           }
           
        }
        teamList = next;

        winner();
    }



};