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
using namespace std;

#include "ChooserFactory.hpp"
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
    void OnButtonClicked(wxCommandEvent& event);

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1
};

wxIMPLEMENT_APP(MyApp);

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

    bool MyApp::OnInit() {
        MyFrame *frame = new MyFrame();
        frame->Show(true);
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
    }

    MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
    {
        wxButton* Button = new wxButton(this, wxID_ANY, "Click ME!");
        // Create a horizontal box sizer
        wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

        // Add the button to the sizer
        hbox->Add(Button, wxSizerFlags().Centre());

        // Create a vertical box sizer
        wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

        // Add the horizontal sizer to the vertical sizer
        vbox->Add(hbox, wxSizerFlags().Centre());

        // Set the sizer for the frame
        SetSizer(vbox);

        // Set the status bar text
        CreateStatusBar();
        SetStatusText("Welcome to wxWidgets!");



        wxMenu *menuFile = new wxMenu;
        menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                         "Help string shown in status bar for this menu item");
        menuFile->AppendSeparator();
        menuFile->Append(wxID_EXIT);

        wxMenu *menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);

        wxMenuBar *menuBar = new wxMenuBar;
        menuBar->Append(menuFile, "&File");
        menuBar->Append(menuHelp, "&Help");

        SetMenuBar( menuBar );

        CreateStatusBar();
        SetStatusText("Welcome to wxWidgets!");

        Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
        Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
        Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
        // Bind the button click event to a handler function
        Bind(wxEVT_BUTTON, &MyFrame::OnButtonClicked, this, Button->GetId());
    }

    void MyFrame::OnExit(wxCommandEvent& event)
    {
        Close(true);
    }

    void MyFrame::OnAbout(wxCommandEvent& event)
    {
        wxMessageBox("This is a wxWidgets Hello World example",
                     "About Hello World", wxOK | wxICON_INFORMATION);
    }

    void MyFrame::OnHello(wxCommandEvent& event)
    {
        wxLogMessage("Hello world from wxWidgets!");
    }
    void MyFrame::OnButtonClicked(wxCommandEvent& event)
    {
        wxLogMessage("Button clicked!");
    }

