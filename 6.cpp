#include "6.hpp"

int main(){
    Bracket b;
    b.insertTeam("A");
    b.insertTeam("B");
    b.insertTeam("C");
    b.insertTeam("D");
    b.insertTeam("E");
    b.insertTeam("F");
    b.insertTeam("G");
    

    b.play();   
    b.pathQuery("A");   
    b.lcaQuery("A","B");  
    b.printBracket() ;


    return 0;
}