#include "6.hpp"
#include <string>


int main() {
    srand(time(0));
    Bracket b;

    b.insertTeam("Team A");
    b.insertTeam("Team B");
    b.insertTeam("Team C");
    b.insertTeam("Team D");
    b.insertTeam("Team E");
    b.insertTeam("Team F");
    b.insertTeam("Team G");
    b.insertTeam("Team H");
    b.insertTeam("Team I");

    b.play();
    b.printTeams();
    cout<<endl;
    b.printPoint();
    cout<<endl;
    b.update();
    cout<<endl;
    b.printTeams();
    cout<<endl;
    b.printPoint();
    cout<<endl;
    b.update();
    cout<<endl;
    b.printTeams();
    cout<<endl;
    b.printPoint();
    b.update();
    cout<<endl;
    cout<<endl;
}