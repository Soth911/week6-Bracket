#include "67.hpp"
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
//1
    b.matching();
    b.printTeams();
    cout<<endl;
    b.printPoint();
    cout<<endl;
    b.update();
//2
    b.matching();
    cout<<endl;
    b.printPoint();
    cout<<endl;
    b.update();
//3
    b.matching();
    cout<<endl;
    b.printPoint();
    cout<<endl;
    b.update();

    b.update();
    cout<<endl;
    b.printQualify();
    b.printSemiFinal();
    b.printFinal();




    
   

    return 0;
}