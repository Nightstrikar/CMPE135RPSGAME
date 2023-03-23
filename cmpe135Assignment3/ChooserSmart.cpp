//
//  ChooserSmart.cpp
//  cmpe135Assignment3
//
//  Created by Alberto Chavez on 3/20/23.
//

#include "ChooserSmart.hpp"
#include <iostream>
#include <unordered_map>
using namespace std;

string SmartChooser::make_choice(string user_choice, int turn_number){
    const int N=5; //Here we say the number moves to remember for each sequence
    static vector<string> choices(N); //We are using this to store the amount of choices previously made
    static unordered_map<string, int> freq; //This is going to to be used for the frequencies of each sequence
    //vector<string> seq;
    static unordered_map<string, int> choiceFreq;
    
    //When we do not have enough choices to make a sequence then we run this to just do a
    //random choice like in the random chooser function (maybe in the future we can just call
    //that function instead) but might break the code so this will work for now
    if (turn_number < N){
        cout << "Not enough choices" << endl;
        value_rad = rand() % 3;
        if (value_rad == 0) {
                choice = "rock";
        } else if (value_rad == 1) {
                choice = "scissors";
        } else {
                choice = "paper";
        }
        return choice;
    }
    
    //If there are enought choices to make a sequence then go here and append the choice into
    //the vector for the sequence
    else{
        cout << "Shift to make more room for choices" << endl;
        for (int i = 0; i < N-1; i++){
            choices[i] = choices[i+1];
        }
        
        //once we make space in the vector we can go ahead and add that choice the user just made
        cout << "Lets add the new choice at the end of the vector" << endl;
        choices[N-1] = user_choice;
        
        //Npw we are going to be have to increment all the frequencies that have that choice
        cout << "Update the freq that end with that user choice" << endl;
        for (int i = 0; i < N-1; i++){
            if (choices[i] == user_choice){
                //Here we are going to be storing the current sequence that we have in the string
                string seq = "";
                for (int j = i; j< N-1; j++){
                    seq += choices[j] + ",";
                }
                seq += user_choice;
                cout << "here is the current seq:" << seq << endl;
                //Then we are going to increase the frequncy count for that given sequence that we
                //have in the seq string so that way we can have a smart model with frequencies of
                //player moves
                freq[seq]++;
            }
        }
        
        choiceFreq[user_choice]++;//The choice from the user will now updates the choice frequency
        
        string max_seq = "";
        int max_freq = 0;
        //now we are locating and doing the algorithm to find the sequence that has all the user's
        //choice with the greatest frequency
        cout << "Now we are locating the best sequence" << endl;
        for (auto it = freq.begin(); it != freq.end(); ++it){
            string seq = it->first;
            //vector<string> subseq(it)
            int f = it->second;
            //Then we are going to see if the seq and frequenct stored in the max variables if
            //something new gets located
            if (seq.back() == user_choice[0] && (f > max_freq)){
                max_seq = seq;
                max_freq = f;
            }
        }
        
        //Here is where we are actually deciding what move to make, the program will make a choice
        //based on the sequence that has the highest frequency or that happens more often.
        
        //Here we are seeing to see if the computer found no sequence then it will make another
        //random decision to make
        if (max_seq.empty()){
            cout << "Got here" << endl;
            value_rad = rand() % 3;
            if (value_rad == 0) {
                    choice = "rock";
            } else if (value_rad == 1) {
                    choice = "scissors";
            } else {
                    choice = "paper";
            }
            return choice;
        }
        
        else{
            cout << "Big Head Move" << endl;
                //Now in this string we are going to be storing the next_choice the player might
                //make that is given from the string max_seq and then it will choose the move to
                //given the parameter below
                //string next_choice = max_seq.substr(N, string::npos);
            //Now we figuring out what choice will happen most often
            unordered_map<string, int> next_choice_find;
            
            for (int i = 0; i < N; i++){
                //Get the choice that was made fromt the sequence
                string choice = max_seq.substr(i*2, 6);
                //This Here will sum up the choices frequncy and the sequence where it shows up
                next_choice_find[choice] += choiceFreq[choice.substr(0,5)];
            }
            string next_choice = "";
            int freqMax = 0;
            for (auto it = next_choice_find.begin(); it != next_choice_find.end(); ++it) {
                string choice02 = it->first;
                int x = it->second;
                //Here we are locating where the frequcny is the highest from teh choices.
                if (x> freqMax){
                    next_choice = choice02;
                    freqMax = x;
                }
            }
            
            //Here we make the ultimate pwer move.
            if (next_choice == "rock"){
                return "paper";
            }
            else if(next_choice == "paper"){
                return "scissors";
            }
            else{
                return "rock";
            }
        }
        
        return choice = user_choice;
    }
}

