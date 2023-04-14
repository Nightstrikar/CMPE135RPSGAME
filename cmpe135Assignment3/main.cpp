//
//  main.cpp
//  cmpe135Assignment3
//
//  Created by Alberto Chavez on 3/13/23.
//
// wxWidgets "Hello World" Program

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <iostream>
#include <string>
using namespace std;


#include "ChooserFactory.hpp"
/*
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
*/


class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size), chosenLabel(nullptr), computerChosenLabel(nullptr), winnerLabel(nullptr)
    {


        //while (play) {
            //while (i < (x+20)) {
        wxPanel* panel = new wxPanel(this, wxID_ANY);
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        roundLabel = new wxStaticText(panel, wxID_ANY, wxString::Format("Round %d", i));
        wxFont font = roundLabel->GetFont();
        font.MakeBold();
        roundLabel->SetFont(font);
        sizer->Add(roundLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

        wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

        wxButton* rockButton = new wxButton(panel, wxID_ANY, "Rock");
        buttonsSizer->Add(rockButton, 0, wxALL, 10);

        wxButton* paperButton = new wxButton(panel, wxID_ANY, "Paper");
        buttonsSizer->Add(paperButton, 0, wxALL, 10);

        wxButton* scissorsButton = new wxButton(panel, wxID_ANY, "Scissors");
        buttonsSizer->Add(scissorsButton, 0, wxALL, 10);

        sizer->Add(buttonsSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

        chosenLabel = new wxStaticText(panel, wxID_ANY, "Human Chooses: ");
        sizer->Add(chosenLabel, 0, wxALL, 10);

        wxStaticText* computerLabel = new wxStaticText(panel, wxID_ANY, "Computer ");
        wxFont font2 = computerLabel->GetFont();
        font2.MakeBold();
        computerLabel->SetFont(font2);
        sizer->Add(computerLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

        humanLabel = new wxStaticText(panel, wxID_ANY, "Predicted Human Choice: ");
        sizer->Add(humanLabel, 0, wxALL, 10);

        computerChosenLabel = new wxStaticText(panel, wxID_ANY, "Therefore computer chooses: ");
        sizer->Add(computerChosenLabel, 0, wxALL, 10);

        winnerLabel = new wxStaticText(panel, wxID_ANY, "The Winner: ");
        wxFont font3 = winnerLabel->GetFont();
        font3.MakeBold();
        winnerLabel->SetFont(font3);
        sizer->Add(winnerLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

        wxStaticText* statlabel = new wxStaticText(panel, wxID_ANY, "Statistics ");
        wxFont font4 = statlabel->GetFont();
        font4.MakeBold();
        statlabel->SetFont(font4);
        sizer->Add(statlabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

        humanWinLabel = new wxStaticText(panel, wxID_ANY, wxString::Format("Human wins: %d", hWin));
        sizer->Add(humanWinLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

        computerWinLabel = new wxStaticText(panel, wxID_ANY, wxString::Format("Computer wins: %d", cWin));
        sizer->Add(computerWinLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

        tieLabel = new wxStaticText(panel, wxID_ANY, wxString::Format("Ties: %d", tie));
        sizer->Add(tieLabel, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

        panel->SetSizer(sizer);

        rockButton->Bind(wxEVT_BUTTON, &MyFrame::OnRockButtonClicked, this);
        paperButton->Bind(wxEVT_BUTTON, &MyFrame::OnPaperButtonClicked, this);
        scissorsButton->Bind(wxEVT_BUTTON, &MyFrame::OnScissorsButtonClicked, this);
        //}
    //}
    }

private:
    wxStaticText* chosenLabel;
    wxStaticText* computerChosenLabel;
    wxStaticText* roundLabel;
    wxStaticText* winnerLabel;
    wxStaticText* humanWinLabel;
    wxStaticText* computerWinLabel;
    wxStaticText* tieLabel;
    wxStaticText* humanLabel;
    string which = "smart";
    Chooser* chooser = ChooserFactory::make_chooser(which);
    bool play = true;
    char playChoice;
    int i = 0;
    int x = 0;
    int hWin = 0;
    int cWin = 0;
    int tie = 0;
    string userChoice = "";
    string compUserChoice = "";
    string compChoiceStd = "";
    string winnerStd = "";

    string whoWon(string user, string comp) {
        string win = "";
        if (user == comp) {
             win = "Tie";
             tie++;
        }
        else if (user == "rock") {
            if (comp == "paper") {
                win = "Computer";
                cWin++;
            }
            else {
                win = "Human";
                hWin++;
            }
        }
        else if (user == "paper") {
            if (comp == "scissors") {
                win = "Computer";
                cWin++;
            }
            else {
                win = "Human";
                hWin++;
            }
        }
        else if (user == "scissors") {
            if (comp == "rock") {
                win = "Computer";
                cWin++;
            }
            else {
                win = "Human";
                hWin++;
            }
        }
        return win;
    }

    

    void OnRockButtonClicked(wxCommandEvent& event) {
        i++;
        if(i>20){
            i = 1;
            hWin = 0;
            cWin = 0;
            tie = 0;
        }
        roundLabel->SetLabel(wxString::Format("Round %d", i));
        chosenLabel->SetLabelText("Human chooses: Rock");
        userChoice = "rock";
        compChoiceStd = chooser->make_choice(userChoice, i);
        //compUserChoice = chooser->next_choice;
        wxString compChoice(compChoiceStd.c_str());
        humanLabel->SetLabelText("Predicted Human Choice: " + compChoice);
        computerChosenLabel->SetLabelText("Therefore computer chooses: " + compChoice);
        winnerStd = whoWon(userChoice, compChoiceStd);
        wxString winner(winnerStd.c_str());
        winnerLabel->SetLabelText("The Winner: " + winner);
        humanWinLabel->SetLabel(wxString::Format("Human wins: %d", hWin));
        computerWinLabel->SetLabel(wxString::Format("Computer wins: %d", cWin));
        tieLabel->SetLabel(wxString::Format("Ties: %d", tie));

    }

    void OnPaperButtonClicked(wxCommandEvent& event) {
        i++;
        if(i>20){
            i = 1;
            hWin = 0;
            cWin = 0;
            tie = 0;
        }
        roundLabel->SetLabel(wxString::Format("Round %d", i));
        chosenLabel->SetLabelText("Human chooses: Paper");
        userChoice = "paper";
        compChoiceStd = chooser->make_choice(userChoice, i);
        wxString compChoice(compChoiceStd.c_str());
        computerChosenLabel->SetLabelText("Therefore computer chooses: " + compChoice);
        winnerStd = whoWon(userChoice, compChoiceStd);
        wxString winner(winnerStd.c_str());
        winnerLabel->SetLabelText("The Winner: " + winner);
        humanWinLabel->SetLabel(wxString::Format("Human wins: %d", hWin));
        computerWinLabel->SetLabel(wxString::Format("Computer wins: %d", cWin));
        tieLabel->SetLabel(wxString::Format("Ties: %d", tie));

    }

    void OnScissorsButtonClicked(wxCommandEvent& event) {
        i++;
        if(i>20){
            i = 1;
            hWin = 0;
            cWin = 0;
            tie = 0;
        }
        roundLabel->SetLabel(wxString::Format("Round %d", i));
        chosenLabel->SetLabelText("Human chooses: Scissors");
        userChoice = "scissors";
        compChoiceStd = chooser->make_choice(userChoice, i);
        wxString compChoice(compChoiceStd.c_str());
        computerChosenLabel->SetLabelText("Therefore computer chooses: " + compChoice);
        winnerStd = whoWon(userChoice, compChoiceStd);
        wxString winner(winnerStd.c_str());
        winnerLabel->SetLabelText("The Winner: " + winner);
        humanWinLabel->SetLabel(wxString::Format("Human wins: %d", hWin));
        computerWinLabel->SetLabel(wxString::Format("Computer wins: %d", cWin));
        tieLabel->SetLabel(wxString::Format("Ties: %d", tie));

    }
};

class MyApp : public wxApp {
public:
    virtual bool OnInit()
    {
        MyFrame* frame = new MyFrame("Rock Paper Scissors", wxPoint(50, 50), wxSize(400, 600));
        frame->Show(true);

        return true;
    }
};

enum
{
    ID_Hello = 1
};



wxIMPLEMENT_APP(MyApp);




/*
    bool MyApp::OnInit() {
        MyFrame *frame = new MyFrame();
        frame->Show(true);
        //std::thread console_thread([]() {
            string which = "smart";
            Chooser *chooser = ChooserFactory::make_chooser(which);
            bool play = true;
            char playChoice;
            int i = 0;
            int x = 0;
            while (play) {
                string userChoice = "";
                while (i < (x + 20)) {
                    cout << "Welcome to rock, paper, scissors for round #" << i + 1 << endl;
                    cout << "Please choose an option" << endl;
                    cin >> userChoice;
                    string compChoice = chooser->make_choice(userChoice, i);
                    cout << "You chose: " << userChoice << endl;
                    cout << "The computer chose: " << compChoice << endl;
                    whoWon(userChoice, compChoice);
                    i++;
                }
                cout << "Do you want to play again? (y/n) ";
                cin >> playChoice;
                if (playChoice == 'y' || playChoice == 'Y') {
                    play = true;
                    x += i;
                } else {
                    play = false;
                }
            }
        //});//console thread
        return true;
    };
*/