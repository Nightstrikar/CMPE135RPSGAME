//
//  main.cpp
//  cmpe135Assignment3
//
//  Created by Alberto Chavez on 3/13/23.
//
// wxWidgets "Hello World" Program

// For compilers that support precompilation, includes "wx/wx.h".
///////////NEW CODE/////////////////////////////


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "UserFactory.hpp"
#include "User.hpp"

using namespace std;

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
enum
{
    ID_NewUser = 1,
    ID_Start,
    ID_Quit,
    ID_Round,
};

using namespace std;
class MyFrame : public wxFrame {
public:
    MyFrame(wxWindow* parent, const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
        wxFileDialog openFileDialog(this, _("Open txt file"), "", "", "txt files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (openFileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }
        m_fileName = openFileDialog.GetPath().ToStdString();
        ifstream inFile(m_fileName);

        if (!inFile.is_open())
        {
            wxMessageBox(_("Unable to open file"));
            return;
        }
        string fileContent((std::istreambuf_iterator<char>(inFile)),istreambuf_iterator<char>());
        //wxTextCtrl* textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
        //textCtrl->SetValue(fileContent);*/
        wxButton* button = new wxButton(this, ID_NewUser, wxT("New User"));
        button->Bind(wxEVT_BUTTON, &MyFrame::OnStart, this);

        // Add the button to the sizer
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(button, wxSizerFlags().Center());

    }
private:
    string m_fileName;
    string username, password;
    bool isAuthenticated = false;
    string newUser;
    bool newUserBool = false;
    bool exit = false;

    void OnStart(wxCommandEvent& event) {
        cout << "Does this still work?" << endl;
        wxTextEntryDialog dialog(this, wxT("Are you a new user?"));
        if (dialog.ShowModal() == wxID_OK)
        {
            wxString wxnewUser = dialog.GetValue();
            newUser = std::string(wxnewUser.mb_str());
            transform(newUser.begin(), newUser.end(), newUser.begin(), ::tolower);
            if (newUser == "yes" || newUser == "y") {
                newUserBool = true;
            }
            else {
                wxTextEntryDialog loginDialogUsername(this, wxT("Enter your username:"));
                wxTextEntryDialog loginDialogPassword(this, wxT("Enter your password:"), wxT("Password"));
                if (loginDialogUsername.ShowModal() == wxID_OK) {
                    string enteredUsername = std::string(loginDialogUsername.GetValue().mb_str());
                    if (loginDialogPassword.ShowModal() == wxID_OK) {
                        string enteredPassword = std::string(loginDialogPassword.GetValue().mb_str());
                        std::ifstream checkFile(m_fileName);
                        cout << "Here we have the file name: " << m_fileName << endl;
                        string line;
                        string fileUserName;
                        string filePassword;
                        string employeeTypeFile;
                        bool isAuthenticated = false;
                        bool exit = false;
                        checkFile.seekg(0, ios::beg);
                        while (getline(checkFile, line) && !isAuthenticated) {
                            istringstream iss(line);
                            if (iss >> fileUserName >> filePassword >> employeeTypeFile) {
                                cout << "User: " << fileUserName << "Password: " << filePassword << "employeeType: " << endl;
                                if (enteredUsername == fileUserName && enteredPassword == filePassword) {
                                    isAuthenticated = true;
                                }
                            }
                        }
                        if (isAuthenticated) {
                            /*
                            wxFrame* welcomeFrame = new wxFrame(nullptr, wxID_ANY, "Welcome User");
                            wxStaticText* welcomeText = new wxStaticText(welcomeFrame, wxID_ANY, "Welcome " + enteredUsername);
                            welcomeFrame->SetSize(400, 300);
                            welcomeFrame->Centre();
                            welcomeFrame->Show();
                             */
                            cout << "Authentication successful." << endl;
                            cout << "Welcome, " << employeeTypeFile << " " << username << "!" << endl;
                            User *user = UserFactory::make_users(employeeTypeFile);
                            while (!exit) {


                                if (employeeTypeFile == "admin") {
                                    int option;
                                    cout << "Please choose an option:" << endl;
                                    cout << "1. Clock in" << endl;
                                    cout << "2. Clock out" << endl;
                                    cout << "3. Get shift total time" << endl;
                                    cout << "4. Exit" << endl;
                                    cin >> option;

                                    if (option == 1) {
                                        user->clock_in();
                                    } else if (option == 2) {
                                        user->clock_out();
                                    } else if (option == 3) {
                                        user->shiftTotalTime();
                                        //cout << user->getShiftDuration() << endl;
                                    } else if (option == 4) {
                                        exit = true;
                                        cout << "Logging out..." << endl;
                                    } else {
                                        cout << "Invalid option. Please try again." << endl;
                                    }

                                } else {
                                    int option;
                                    cout << "Please choose an option:" << endl;
                                    cout << "1. Clock in" << endl;
                                    cout << "2. Clock out" << endl;
                                    cout << "3. Get shift total time" << endl;
                                    cout << "4. Exit" << endl;
                                    cin >> option;

                                    if (option == 1) {
                                        user->clock_in();
                                    } else if (option == 2) {
                                        user->clock_out();
                                    } else if (option == 3) {

                                        user->shiftTotalTime();
                                    } else if (option == 4) {
                                        exit = true;
                                        cout << "Logging out..." << endl;
                                    } else {
                                        cout << "Invalid option. Please try again." << endl;
                                    }
                                }

                            }
                        }
                        else {
                            cout << "Authentication failed." << endl;
                            exit = true;
                        }
                    }
                        // Perform authentication check here
                    // ...
                }
                else {
                    // User cancelled login dialog
                    return;
                }
            }
            //wxMessageBox(wxT("Hello, ") + newUser + wxT("!"), wxT("Greeting"));
        }
        if (newUserBool) {
            string newUsername, newPassword, newEmployeeType;
            bool usernameExists = false;
            bool validUserName = false;

            // Check if username already exists
            do {
                usernameExists = false;
                wxTextEntryDialog dialog2(this, wxT("Please enter your desired username: "));
                if (dialog2.ShowModal() == wxID_OK)
                {
                    string enteredUsername = std::string(dialog2.GetValue().mb_str());
                    ifstream checkFile(m_fileName);
                    cout << "Here we have the file name: " << m_fileName << endl;
                    string line;
                    while (getline(checkFile, line)) {
                        cout << "Hi" << endl;
                        istringstream iss(line);
                        string fileUsername, filePassword, fileEmployeeType;
                        if (iss >> fileUsername >> filePassword >> fileEmployeeType) {
                            if (enteredUsername == fileUsername) {
                                usernameExists = true;
                                cout << "Username already exists. Please choose a different username." << endl;
                                wxMessageBox(_("Username already exists. Please choose a different username."));
                                break;
                            }
                        }
                    }
                    if (!usernameExists) {
                        validUserName = true;
                        newUsername = enteredUsername;
                    }
                }
            } while (!validUserName);

            if (validUserName) {
                cout << "Now we are going to need a password" << endl;
                wxTextEntryDialog dialog3(this, wxT("Please enter your desired password: "));
                if (dialog3.ShowModal() == wxID_OK){
                    string enteredNewPassword = std::string(dialog3.GetValue().mb_str());
                    newEmployeeType = "worker";
                    ofstream outFile(m_fileName, ios::app);
                    //outFile << endl;
                    outFile << newUsername << " " << enteredNewPassword << " " << newEmployeeType << endl;


                }
                // Prompt for password and employee type
                // Add new user to file
            }
        }
    }
};

class MyApp : public wxApp {
public:
    virtual bool OnInit()
    {
        MyFrame* frame = new MyFrame(nullptr,"Timecard Application");
        frame->SetClientSize(400, 600);
        frame ->Center();
        frame->Show(true);

        return true;
    }

};

wxIMPLEMENT_APP(MyApp);


/*
int main() {
    fstream file("/Users/alberto/CLionProjects/CMPE135RPSGAME/cmpe135Assignment3/users.txt", ios::in | ios::app);
    if (!file.is_open()) {
        cerr << "Error: could not open users file." << endl;
        return 1;
    }

    string username, password;
    bool isAuthenticated = false;
    string newUser;
    bool newUserBool = false;
    bool exit = false;
    string fileUsername, filePassword, employeeType;

    cout << "Are you a new user? ";
    cin >> newUser;

    transform(newUser.begin(), newUser.end(), newUser.begin(), ::tolower);

    if (newUser == "yes" || newUser == "y") {
        newUserBool = true;
    }

    // creating new user
    if (newUserBool) {
        string newUsername, newPassword, newEmployeeType;
        bool usernameExists = false;

        // Check if username already exists
        do{
            usernameExists = false;
            cout << "Please enter your desired username: ";
            cin >> newUsername;
            ifstream checkFile("users.txt");
            string line;
            while (getline(checkFile, line)) {
                istringstream iss(line);
                string fileUsername, filePassword, fileEmployeeType;
                if (iss >> fileUsername >> filePassword >> fileEmployeeType) {
                    if (newUsername == fileUsername) {
                        usernameExists = true;
                        cout << "Username already exists. Please choose a different username." << endl;
                    }
                }
            }
        }while(usernameExists == true);

        cout << "Please enter your desired password: ";
        cin >> newPassword;

        newEmployeeType = "worker";

        // Append new user to file
        file << newUsername << " " << newPassword << " " << newEmployeeType << endl;

        cout << "Account created successfully!" << endl;
        //}
    }

    cout << "Please enter your username: ";
    cin >> username;

    cout << "Please enter your password: ";
    cin >> password;



    // logging in
    string line;
    file.seekg(0, ios::beg);
    while (getline(file, line) && !isAuthenticated) {
        istringstream iss(line);
        if (iss >> fileUsername >> filePassword >> employeeType) {
            if (username == fileUsername && password == filePassword) {
                isAuthenticated = true;
            }
        }
    }
    if (isAuthenticated) {
        cout << "Authentication successful." << endl;
        cout << "Welcome, " << employeeType << " " << username << "!" << endl;
        User* user = UserFactory::make_users(employeeType);
    while (!exit) {


            if (employeeType == "admin") {
                int option;
                cout << "Please choose an option:" << endl;
                cout << "1. Clock in" << endl;
                cout << "2. Clock out" << endl;
                cout << "3. Get shift total time" << endl;
                cout << "4. Exit" << endl;
                cin >> option;

                if (option == 1) {
                    user->clock_in();
                }
                else if (option == 2) {
                    user->clock_out();
                }
                else if (option == 3) {
                    user->shiftTotalTime();
                    //cout << user->getShiftDuration() << endl;
                }
                else if (option == 4) {
                    exit = true;
                    cout << "Logging out..." << endl;
                }
                else {
                    cout << "Invalid option. Please try again." << endl;
                }

            }
            else {
                int option;
                cout << "Please choose an option:" << endl;
                cout << "1. Clock in" << endl;
                cout << "2. Clock out" << endl;
                cout << "3. Get shift total time" << endl;
                cout << "4. Exit" << endl;
                cin >> option;

                if (option == 1) {
                    user->clock_in();
                }
                else if (option == 2) {
                    user->clock_out();
                }
                else if (option == 3) {

                    user->shiftTotalTime();
                }
                else if (option == 4) {
                    exit = true;
                    cout << "Logging out..." << endl;
                }
                else {
                    cout << "Invalid option. Please try again." << endl;
                }
            }

    }
    }
    else {
        cout << "Authentication failed." << endl;
        exit = true;
    }

    file.close();

    return 0;
}

*/


///////////OLD CODE/////////////////////////////
/*
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <iostream>
#include <string>
using namespace std;


#include "ChooserFactory.hpp"

enum
{
    ID_About = 1,
    ID_Start,
    ID_Quit,
    ID_Round,
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size), chosenLabel(nullptr), computerChosenLabel(nullptr), winnerLabel(nullptr)
    {
        Connect(ID_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnAbout));
        Connect(ID_Quit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnExit));
        Connect(ID_Start, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnStartNewGame));
        Connect(ID_Round, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::SetNewRound));
        wxMenu *menuFile = new wxMenu;
        menuFile->Append(ID_About, "&About\t", "Help string shown in status bar for this menu item");
        menuFile->Append(ID_Start, "&Start New Game", "Start a New Game");
        menuFile->Append(ID_Round, "&Set Round Limit", "Create the round limiter");
        menuFile->AppendSeparator();
        menuFile->Append(ID_Quit, "&Exit\tCtrl-Q", "Quit this program");


        // create menu bar and attach menu to it
        wxMenuBar *menuBar = new wxMenuBar();
        menuBar->Append(menuFile, "&Menu");
        SetMenuBar(menuBar);



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
    long rounds = 20;
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

    void OnExit(wxCommandEvent& event)
    {
        Close(true);
    }

    void OnStartNewGame(wxCommandEvent& event){
        i = 0;
        hWin = 0;
        cWin = 0;
        tie = 0;
        roundLabel->SetLabel(wxString::Format("Round %d", i));
        chosenLabel->SetLabelText("Human chooses: ");
        //userChoice = "rock";
        compChoiceStd = chooser->make_choice(userChoice, x);
        //compUserChoice = chooser->prediction;
        //wxString compChoice(compChoiceStd.c_str());
        humanLabel->SetLabelText("Predicted Human Choice: ");
        computerChosenLabel->SetLabelText("Therefore computer chooses: ");
        //winnerStd = whoWon(userChoice, compChoiceStd);
        //wxString winner(winnerStd.c_str());
        winnerLabel->SetLabelText("The Winner: ");
        humanWinLabel->SetLabel(wxString::Format("Human wins: %d", hWin));
        computerWinLabel->SetLabel(wxString::Format("Computer wins: %d", cWin));
        tieLabel->SetLabel(wxString::Format("Ties: %d", tie));
    }

    void SetNewRound(wxCommandEvent& event) {

        wxString prompt = "Please set how many rounds you are going to want for the game to stop at each game.";
        wxString caption = "Setting the Round Limit";
        wxString default_value = "0";

        // Display a dialog to get user input
        wxTextEntryDialog dialog(this, prompt, caption, default_value, wxTextEntryDialogStyle, wxDefaultPosition);
        if (dialog.ShowModal() == wxID_OK) {
            rounds = wxAtoi(dialog.GetValue());
        }

        // Do something with the user input
        wxString message;
        if (rounds > 0) {
            message.Printf("You set the round limit to %ld.", rounds);

        } else {
            message = "Invalid round limit. Please enter a positive integer.";
        }
        wxMessageBox(message, "Round Limit", wxOK | wxICON_INFORMATION);
    }
    void OnAbout(wxCommandEvent& event)
    {
        wxMessageBox("This is a program that will display a rock paper "
                     "scissors game and the use of wxwidgets. We were tasked to "
                     "incorperate our game with the GUI program in order to show "
                     "our knowledge and understanding of how to incorperate a "
                     "command line program into a functional GUI that uses "
                     "buttons as the choices the user would make.",
                     "About our Program", wxOK | wxICON_INFORMATION);
    }


    void OnRockButtonClicked(wxCommandEvent& event) {
        i++;
        x++;
        if(i>rounds){
            i = 1;
            hWin = 0;
            cWin = 0;
            tie = 0;
        }
        roundLabel->SetLabel(wxString::Format("Round %d", i));
        chosenLabel->SetLabelText("Human chooses: Rock");
        userChoice = "rock";
        compChoiceStd = chooser->make_choice(userChoice, x);
        //compUserChoice = chooser->prediction;
        wxString compChoice(compChoiceStd.c_str());
        humanLabel->SetLabelText("Predicted Human Choice: " + chooser->prediction);
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
        x++;
        if(i>rounds){
            i = 1;
            hWin = 0;
            cWin = 0;
            tie = 0;
        }
        roundLabel->SetLabel(wxString::Format("Round %d", i));
        chosenLabel->SetLabelText("Human chooses: Paper");
        userChoice = "paper";
        compChoiceStd = chooser->make_choice(userChoice, x);
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
        x++;
        if(i>rounds){
            i = 1;
            hWin = 0;
            cWin = 0;
            tie = 0;
        }
        roundLabel->SetLabel(wxString::Format("Round %d", i));
        chosenLabel->SetLabelText("Human chooses: Scissors");
        userChoice = "scissors";
        compChoiceStd = chooser->make_choice(userChoice, x);
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

wxIMPLEMENT_APP(MyApp);
 */