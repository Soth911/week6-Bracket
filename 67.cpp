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
    // b.input();
    b.toEnd();
    // b.printQualify();
    // b.printSemiFinal();
    // b.printFinal();
    
    b.all();
    b.atMatch(4);
    b.searchMatch("Team G");
    b.lca("Team A","Team B");


 

    
   

    return 0;
}