//
//  main.cpp
//  cmpe135Assignment3
//
//  Created by Alberto Chavez on 3/13/23.
//

#include <iostream>
using namespace std;

#include "ChooserFactory.hpp"

void whoWon(string user, string comp){
    if (user == comp){
        cout<<"It's a Tie!"<<endl;
    }
    else if(user == "rock"){
        if(comp == "paper"){
            cout<<"You loose"<<endl;
        }
        else{
            cout<<"You win!"<<endl;
        }
    }
    else if(user == "paper"){
        if(comp == "scissors"){
            cout<<"You loose"<<endl;
        }
        else{
            cout<<"You win!"<<endl;
        }
    }
    else if(user == "scissors"){
        if(comp == "rock"){
            cout<<"You loose"<<endl;
        }
        else{
            cout<<"You win"<<endl;
        }
    }
    else{
        cout<<"That's not a valid play. Check your spelling!";
    }
    cout<<endl;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    string which = "smart";
    Chooser *chooser = ChooserFactory::make_chooser(which);
    bool play = true;
    char playChoice;
    int i = 0;
    int x = 0;
    while (play) {
        string userChoice = "";
        while(i<(x+20)){
            cout<<"Welcome to rock, paper, scissors for round #"<<i+1<<endl;
            cout<<"Please choose an option"<<endl;
            cin>>userChoice;
            string compChoice = chooser->make_choice(userChoice,i);
            cout<<"You chose: "<<userChoice<<endl;
            cout<<"The computer chose: "<<compChoice<<endl;
            whoWon(userChoice,compChoice);
            i++;
        }
        cout << "Do you want to play again? (y/n) ";
        cin >> playChoice;
        if (playChoice == 'y' || playChoice == 'Y'){
            play = true;
            x += i;
        }
        else{
            play = false;
        }

    }


    
    
    return 0;
}
