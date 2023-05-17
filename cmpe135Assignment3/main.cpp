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
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include "UserFactory.hpp"
#include "User.hpp"
#include "PaySettings.hpp"
#include "wx/string.h"
using namespace std;

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
enum
{
    ID_About = 1,
    ID_NewUser,
    ID_Start,
    ID_Quit,
    ID_NewUsers,
    ID_PunchIn,
    ID_PunchOut,

};

using namespace std;
class ChildFrame : public wxFrame
{
public:
    ChildFrame(wxWindow *parent, wxWindowID id, const wxString &title,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE) : wxFrame(parent, id, title, pos, size, style)
    {
        // Add child frame widgets
        wxPanel* panel = new wxPanel(this, wxID_ANY);
        wxButton* button = new wxButton(panel, wxID_ANY, wxT("Close"), wxPoint(50, 50));
        button->Bind(wxEVT_BUTTON, &ChildFrame::OnCloseButton, this);
    }

private:
    void OnCloseButton(wxCommandEvent& event)
    {
        Close();
    }
};

class MyFrame : public wxFrame {
public:
    MyFrame(wxWindow *parent, const wxString &title) : wxFrame(NULL, wxID_ANY, title) {


        wxFileDialog openFileDialog(this, _("Open txt file"), "", "", "txt files (*.txt)|*.txt",
                                    wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        // Create a static text control
        wxStaticText *staticText = new wxStaticText(this, wxID_ANY, "WELCOME TO THE RABBIT TIMECARD APPLICATION");

        // Add the static text control to the sizer
        wxBoxSizer *sizer1 = new wxBoxSizer(wxVERTICAL);
        sizer1->Add(staticText, wxSizerFlags().Center());

        // Set the sizer for the frame
        SetSizer(sizer1);
        Connect(ID_About, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnAbout));
        Connect(ID_Quit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnExit));
        Connect(ID_Start, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnStartNewGame));
        Connect(ID_NewUser, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::SetNewUser));
        Connect(ID_PunchIn, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::PunchIN));
        Connect(ID_PunchOut, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::PunchOUT));
        wxMenu *menuFile = new wxMenu;
        menuFile->Append(ID_About, "&About\t", "Help string shown in status bar for this menu item");
        if (testing == 0) {
            menuFile->Append(ID_Start, "&Login", "Start a New Game");
            menuFile->Append(ID_NewUser, "&Create New User", "Create the round limiter");
        };
        menuFile->AppendSeparator();
        menuFile->Append(ID_Quit, "&Exit\tCtrl-Q", "Quit this program");
        if (openFileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }
        m_fileName = openFileDialog.GetPath().ToStdString();
        ifstream inFile(m_fileName);

        if (!inFile.is_open()) {
            wxMessageBox(_("Unable to open file"));
            return;
        }

        // create the Punch menu
        wxMenu *menuPunch = new wxMenu;
        //menuPunch->Append(ID_PunchIn, "&Punch In", "Punch In");
        //menuPunch->Append(ID_PunchOut, "&Punch Out", "Punch Out");

        // create menu bar and attach menus to it
        wxMenuBar *menuBar = new wxMenuBar();
        menuBar->Append(menuFile, "&Menu");
        //menuBar->Append(menuPunch, "&Punch");
        SetMenuBar(menuBar);


        /* This is to delete the menuBar
        size_t punchIndex = menuBar->FindMenu("&Punch");
        if (punchIndex != wxNOT_FOUND) {
            menuBar->Remove(punchIndex);
        }
        */
        cout << "we are adding the punches" << endl;


        string fileContent((std::istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        //wxTextCtrl* textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
        //textCtrl->SetValue(fileContent);

        //For the button in the middle to add the new user
        /*
        button1->Bind(wxEVT_BUTTON, &MyFrame::OnStart, this);

        //wxPanel* panel = new wxPanel(this, wxID_ANY);
        //wxButton* button1 = new wxButton(panel, wxID_ANY, wxT("Create Child Frame"), wxPoint(200, 200));
        //button1->Bind(wxEVT_BUTTON, &MyFrame::OnCreateChildFrame, this);

        // Add the buttons to the sizer
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(button1, wxSizerFlags().Center());
        //sizer->Add(panel, wxSizerFlags().Center());

        // Set the sizer for the frame
        SetSizer(sizer);
         */



    }

private:
    string m_fileName;
    string username, password;
    bool isAuthenticated = false;
    string newUser;
    bool newUserBool = false;
    bool exit = false;
    int testing = 0;
    bool isWorker = false;
    bool isAdmin = false;
    /*
    string line;
    string fileUserName;
    string filePassword;
    string employeeTypeFile;
    bool isAuthenticated = false;
    bool exit = false;
     */
    //wxButton* button1 = new wxButton(this, ID_NewUsers, wxT("New User"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("button1"));
    //wxButton* button1 = new wxButton(this, ID_NewUsers, wxT("new"), wxPoint(50, 50));
    struct Shift {
        std::chrono::system_clock::time_point clockInTime;
        std::chrono::system_clock::time_point clockOutTime;
    };


    bool delete_user() {
        wxTextEntryDialog loginDialogUsername(this, wxT("Enter the user's username:"));
        if (loginDialogUsername.ShowModal() == wxID_OK) {
            string enteredUsername = std::string(loginDialogUsername.GetValue().mb_str());


            std::ifstream inputFile(m_fileName);
            cout << "Here we have the file name: " << m_fileName << endl;
            string line;
            string fileUserName;
            bool isAuthenticated = false;

            // new file to write to
            std::ofstream tempFile(m_fileName + "_temp.txt");

            // loops through the lines, finds matching username
            while (getline(inputFile, line)) {
                istringstream iss(line);
                if (iss >> fileUserName) {
                    cout << "User: " << fileUserName << endl;
                    if (enteredUsername == fileUserName) {
                        isAuthenticated = true;
                        continue;
                    }
                }
                tempFile << line << endl;
            }

            inputFile.close();
            tempFile.close();

            //if it finds the user, copies contents from temp file to the new file
            if (isAuthenticated) {
                std::ifstream tempInputFile(m_fileName + "_temp.txt");
                std::ofstream originalFile(m_fileName);

                originalFile << tempInputFile.rdbuf();
                originalFile.close();
                tempInputFile.close();

                std::remove((m_fileName + "_temp.txt").c_str()); // Delete the temporary file
                return true;
            }
                // else delete file
            else {
                std::remove((m_fileName + "_temp.txt").c_str()); // Delete the temporary file
                wxMessageBox("Invalid username.", "Authentication Failed", wxOK | wxICON_ERROR);
                return false;
            }
        }
    }
    void PunchOUT(wxCommandEvent& event){
        cout << "You wanted to punch out" << endl;
        wxMessageBox(_("Punching Out"));

        if(isAdmin == true){
            wxMessageBox(_("You are a Admin punching out"));
            cout << "5" << endl;
            wxTextEntryDialog dialog3(this, wxT("You are a Admin"));
        }
        else if(isWorker == true){
            wxMessageBox(_("You are a worker punching out"));
            cout << "6" << endl;
            wxTextEntryDialog dialog4(this, wxT("You are a Worker"));
        }
        else{
            wxMessageBox(_("You are a nobody punching out"));
            cout << "7" << endl;
            wxTextEntryDialog dialog5(this, wxT("You are a Nobody"));
        }

    }
    void PunchIN(wxCommandEvent& event){
        cout << "you clicked the button" << endl;
        wxMessageBox(_("Punching In"));
        if(isAdmin == true){
            wxMessageBox(_("You are a Admin punching in"));
            cout << "1" << endl;
            wxTextEntryDialog dialog6(this, wxT("You are a Admin"));
            if (dialog6.ShowModal() == wxID_OK) {

            }
        }
        else if(isWorker == true){
            wxMessageBox(_("You are a worker punching in"));
            cout << "2" << endl;
            wxTextEntryDialog dialog7(this, wxT("You are a Worker"));
            if (dialog7.ShowModal() == wxID_OK) {

            }
        }
        else{
            wxMessageBox(_("You are a nobody"));
            cout << "3" << endl;
            wxTextEntryDialog dialog8(this, wxT("You are a Nobody"));
            if (dialog8.ShowModal() == wxID_OK) {

            }
        }

    }
    void OnExit(wxCommandEvent& event)
    {

        Close(true);
    }

    void getTotalAmountOfShiftsAndTime(){
        std::ifstream inputFile(m_fileName);
        if (!inputFile.is_open()) {
            std::cout << "Failed to open the input file." << std::endl;
        }

        std::string line;
        std::vector<Shift> shifts;

        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string username, password, id;
            std::vector<std::string> clockTimes;

            // Parse the username, password, and ID
            if (iss >> username >> password >> id && username == "jane") {
                std::string shiftTimeStr;

                // Parse the clock-in and clock-out times
                while (iss >> shiftTimeStr) {
                    clockTimes.push_back(shiftTimeStr);
                }

                // Ensure there are pairs of clock-in and clock-out times
                if (clockTimes.size() % 2 == 0) {
                    for (size_t i = 0; i < clockTimes.size(); i += 2) {
                        Shift shift;
                        std::tm tmIn = {};
                        std::tm tmOut = {};

                        // Parse the clock-in time
                        std::istringstream issIn(clockTimes[i]);
                        issIn >> std::get_time(&tmIn, "%Y-%m-%d %H:%M:%S");
                        shift.clockInTime = std::chrono::system_clock::from_time_t(std::mktime(&tmIn));

                        // Parse the clock-out time
                        std::istringstream issOut(clockTimes[i + 1]);
                        issOut >> std::get_time(&tmOut, "%Y-%m-%d %H:%M:%S");
                        shift.clockOutTime = std::chrono::system_clock::from_time_t(std::mktime(&tmOut));

                        shifts.push_back(shift);

                        // Convert clock-in time to std::time_t
                        std::time_t clockInTimeT = std::chrono::system_clock::to_time_t(shift.clockInTime);
                        // Print the clock-in time
                        std::cout << "Clock-in time: "
                                  << std::put_time(std::localtime(&clockInTimeT), "%Y-%m-%d %H:%M:%S") << std::endl;
                        std::time_t clockOutTimeT = std::chrono::system_clock::to_time_t(shift.clockOutTime);

                        // Print the clock-in time
                        std::cout << "Clock-out time: "
                                  << std::put_time(std::localtime(&clockOutTimeT), "%Y-%m-%d %H:%M:%S") << std::endl;

                    }
                }
            }
        }
        // Calculate the shift information for Jane
        int shiftCount = shifts.size();
        std::cout << "Number of Shifts for Jane: " << shiftCount << std::endl;

        for (int i = 0; i < shiftCount; ++i) {
            const Shift& shift = shifts[i];
            std::chrono::duration<double> shiftDuration = shift.clockOutTime - shift.clockInTime;
            std::cout << "Shift " << (i + 1) << " Duration: " << shiftDuration.count() << " seconds" << std::endl;
        }
    }

    void OnStartNewGame(wxCommandEvent& event){
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
                    testing = 3;
                    /*
                    wxFrame* welcomeFrame = new wxFrame(nullptr, wxID_ANY, "Welcome User");
                    wxStaticText* welcomeText = new wxStaticText(welcomeFrame, wxID_ANY, "Welcome " + enteredUsername);
                    welcomeFrame->SetSize(400, 300);
                    welcomeFrame->Centre();
                    welcomeFrame->Show();
                     */
                    //OnCreateChildFrame();
                    wxMessageBox(_("Authentication successful." ));
                    cout << "Authentication successful." << endl;
                    wxString message1 = wxString::Format("Welcome %s, you are logged in as %s", fileUserName, employeeTypeFile);
                    wxMessageBox(message1, "Authentication Status", wxOK | wxICON_INFORMATION);
                    cout << "Welcome, " << employeeTypeFile << " " << username << "!" << endl;
                    User *user = UserFactory::make_users(employeeTypeFile);
                    //while (!exit) {

                        if (employeeTypeFile == "admin") {
                            isAdmin = true;
                            isWorker = false;
                            string clock_in_time;
                            string clock_out_time;
                            while(!exit) {
                                Admin admin;
                                PaySettings workerPaySettings;
                                wxString messageAdmin = "Please choose an option:\n1. Clock in\n2. Clock out\n3. Get shift total time\n4. Create New User\n5. Delete an account\n6. Set Worker Pay\n7. Get Worker Pay\n8. Exit";
                                wxTextEntryDialog dialog(this, messageAdmin, "Choose an Option");
                                dialog.SetTextValidator(wxFILTER_DIGITS); // Only allow digits as input
                                if (dialog.ShowModal() == wxID_OK) {
                                    wxString input = dialog.GetValue();
                                    int option = wxAtoi(input);
                                    if (option == 1) {
                                        user->clock_in();
                                        wxMessageBox(_("Punching In"));
                                        clock_in_time = user->getClock_in();
                                        store_clock_in(clock_in_time, fileUserName, filePassword, employeeTypeFile);
                                    } else if (option == 2) {
                                        user->clock_out();
                                        wxMessageBox(_("Punching Out"));
                                        clock_out_time = user->getClock_out();
                                        store_clock_out(clock_in_time, clock_out_time, fileUserName, filePassword, employeeTypeFile);
                                    } else if (option == 3) {
                                        user->shiftTotalTime();
                                        wxMessageBox(_("Getting Shift Information"));
                                        //cout << user->getShiftDuration() << endl;
                                    } else if (option == 8) {
                                        exit = true;
                                        wxMessageBox(_("Logging out..."));
                                        cout << "Logging out..." << endl;
                                    }
                                    else if (option == 5) {
                                        cout << "Attempting to delete user..." << endl;
                                        if (delete_user()) {
                                            wxMessageBox(_("Deleted User"));
                                        }
                                        else {
                                            wxMessageBox(_("Failed to Delete User"));
                                        }
                                    }
                                    else if (option == 4) {
                                        SetNewUser();
                                        cout << "Creating a new user..." << endl;
                                        wxMessageBox(_("New User Created"));
                                    }
                                    else if (option == 6) {
                                        // SetNewUser();
                                        // Create an instance of Admin
                                        // Create an instance of PaySettings for the worker
                                        // Set the worker's pay using the setWorkerPay function
                                        wxTextEntryDialog payDialog(nullptr, "Enter salary pay:", "Pay");
                                        if (payDialog.ShowModal() == wxID_OK) {
                                            wxString payValue = payDialog.GetValue();
                                            double pay = 0.0;
                                            if (!payValue.ToDouble(&pay)) {
                                                wxMessageBox("Invalid pay value!", "Error", wxICON_ERROR | wxOK);
                                            }

                                            wxTextEntryDialog rateDialog(nullptr, "Enter the hourly rate:", "Hourly Rate");
                                            if (rateDialog.ShowModal() == wxID_OK) {
                                                wxString rateValue = rateDialog.GetValue();
                                                double rate = 0.0;
                                                if (!rateValue.ToDouble(&rate)) {
                                                    wxMessageBox("Invalid rate value!", "Error", wxICON_ERROR | wxOK);
                                                }
                                                wxTextEntryDialog periodDialog(nullptr, "Enter the pay period:", "Pay Period");
                                                if (periodDialog.ShowModal() == wxID_OK) {
                                                    string period = std::string(periodDialog.GetValue().mb_str());
                                                    wxTextEntryDialog overtimeRateDialog(nullptr,
                                                                                         "Enter overtime rate:",
                                                                                         "Overtime Rate");
                                                    if (overtimeRateDialog.ShowModal() == wxID_OK) {
                                                        wxString overtimeRateValue = overtimeRateDialog.GetValue();
                                                        double overtimeRate = 0.0;
                                                        if (!overtimeRateValue.ToDouble(&overtimeRate)) {
                                                            wxMessageBox("Invalid overtime rate value!", "Error",
                                                                         wxICON_ERROR | wxOK);
                                                        }

                                                        // Use the obtained values (pay, rate, period, overtimeRate) here
                                                        // ...
                                                        admin.setWorkerPay(workerPaySettings,pay,rate,period,overtimeRate );
                                                        wxMessageBox("Values entered:\n\nSalary Pay: " + payValue +
                                                                     "\nHourly Rate: " + rateValue +
                                                                     "\nPay Period: " + period +
                                                                     "\nOvertime Rate: " + overtimeRateValue,
                                                                     "Input Values", wxICON_INFORMATION | wxOK);
                                                    }
                                                }
                                            }
                                        }
                                        //admin.setWorkerPay(workerPaySettings, 10.0, 1.5, "monthly", 2.0);

                                        //cout << "Paysettings 1" << endl;
                                        //wxMessageBox(_("TESTING"));
                                    }
                                    else if (option == 7) {
                                        //SetNewUser();
                                        // Get the worker's pay settings using the Admin class
                                        wxMessageBox(_("Getting the workers pay"));
                                        double adminPaySettings = admin.getWorkerPay(workerPaySettings);
                                        double workerPays = workerPaySettings.get_pay_period();
                                        double hourlyRate = workerPaySettings.get_pay_hourly_rate();
                                        double overtimeRate = workerPaySettings.get_overime_rate();
                                        string payPeriod = workerPaySettings.getPayPeriod();
                                        // Output the worker's pay settings
                                        cout << "Worker's pay: $" << workerPays << endl;
                                        cout << "Hourly rate: $" << hourlyRate << endl;
                                        cout << "Overtime rate: $" << overtimeRate << endl;
                                        cout << "Pay period type: " << payPeriod << endl;

                                        // Output the worker's pay settings obtained by the Admin class
                                        cout << "Admin's worker pay: $" << adminPaySettings << endl;

                                        double workerPay = admin.getWorkerPay(workerPaySettings);
                                        cout << "Paysettings 2" << endl;
                                        // Convert the pay value to a string
                                        wxString payString = wxString::Format("%.2f", workerPay);
                                        // Show the pay value in a message box
                                        wxMessageBox("Worker's Pay: " + payString, "Pay Information", wxOK | wxICON_INFORMATION);
                                    }
                                    else {
                                        wxMessageBox(_("Invalid option. Please try again."));
                                        cout << "Invalid option. Please try again." << endl;
                                    }
                                }

                            }
                        } else {
                            int option;
                            isWorker = true;
                            isAdmin = false;
                            string clock_in_time;
                            string clock_out_time;
                            Worker worker;
                            while(!exit) {
                                wxString messageWorker = "Please choose an option:\n1. Clock in\n2. Clock out\n3. Get shift total time\n4. Exit";
                                wxTextEntryDialog dialog(this, messageWorker, "Choose an Option");
                                dialog.SetTextValidator(wxFILTER_DIGITS); // Only allow digits as input
                                if (dialog.ShowModal() == wxID_OK) {
                                    wxString input = dialog.GetValue();
                                    int option = wxAtoi(input);
                                    if (option == 1) {
                                        worker.clock_in();
                                        wxMessageBox(_("Punching In"));
                                        clock_in_time = worker.getClock_in();
                                        store_clock_in(clock_in_time, fileUserName, filePassword, employeeTypeFile);
                                    } else if (option == 2) {
                                        worker.clock_out();
                                        wxMessageBox(_("Punching Out"));
                                        clock_out_time = worker.getClock_out();
                                        store_clock_out(clock_in_time, clock_out_time, fileUserName, filePassword, employeeTypeFile);
                                    } else if (option == 3) {
                                        worker.shiftTotalTime();
                                        std::string shiftTotalTimeString = std::to_string(worker.getShiftTotalTime());
                                        wxString message = "Shift Total Time: " + wxString(shiftTotalTimeString);
                                        getTotalAmountOfShiftsAndTime();
                                        wxMessageBox(message, "Shift Information", wxICON_INFORMATION | wxOK);

                                    } else if (option == 4) {
                                        exit = true;
                                        wxMessageBox(_("Logging out..."));
                                        cout << "Logging out..." << endl;
                                    } else {
                                        wxMessageBox(_("Invalid option. Please try again."));
                                        cout << "Invalid option. Please try again." << endl;
                                    }
                                }

                            }
                        }

                    //}//while(!exit)
                } else {
                    cout << "Authentication failed." << endl;
                    exit = true;
                }
            }
        }
    }

    void SetNewUser(wxCommandEvent& event) {
        int rounds = 0;
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
            if (dialog3.ShowModal() == wxID_OK) {
                string enteredNewPassword = std::string(dialog3.GetValue().mb_str());
                newEmployeeType = "worker";
                ofstream outFile(m_fileName, ios::app);
                //outFile << endl;
                outFile << newUsername << " " << enteredNewPassword << " " << newEmployeeType << endl;


            }
            // Prompt for password and employee type
            // Add new user to file
        }
        /*
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
         */

         //wxMessageBox(message, "Round Limit", wxOK | wxICON_INFORMATION);
    }
    void SetNewUser() {
        int rounds = 0;
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
            if (dialog3.ShowModal() == wxID_OK) {
                string enteredNewPassword = std::string(dialog3.GetValue().mb_str());
                wxTextEntryDialog dialog4(this, wxT("Please enter the desired role for the user (admin/worker): "));
                if (dialog4.ShowModal() == wxID_OK) {
                    string userType = std::string(dialog4.GetValue().mb_str());
                    transform(userType.begin(), userType.end(), userType.begin(), ::tolower);
                    if (userType == "admin" || userType == "worker") {
                        newEmployeeType = userType;
                    }
                    else {
                        newEmployeeType = "worker";
                    }
                    
                    ofstream outFile(m_fileName, ios::app);
                    //outFile << endl;
                    outFile << newUsername << " " << enteredNewPassword << " " << newEmployeeType << endl;
                }



            }
        }
    }
    void store_clock_in(string clock_in, string UserName, string Password, string TypeEmployee) {
        ifstream inputFile(m_fileName);
        string line;
        string fileUserName;
        string lineToReplace = UserName + " " + Password + " " + TypeEmployee + " " + clock_in;

        // new file to write to
        ofstream tempFile(m_fileName + "_temp.txt");

        // loops through the lines, finds matching username
        while (getline(inputFile, line)) {
            istringstream iss(line);
            if (iss >> fileUserName) {
                if (UserName == fileUserName) {
                    tempFile << lineToReplace << endl;
                    continue;
                }
            }
            tempFile << line << endl;
        }

        inputFile.close();
        tempFile.close();
        
        ifstream tempInputFile(m_fileName + "_temp.txt");
        ofstream originalFile(m_fileName);

        originalFile << tempInputFile.rdbuf();
        originalFile.close();
        tempInputFile.close();

        remove((m_fileName + "_temp.txt").c_str()); // Delete the temporary file
    }
    void store_clock_out(string clock_in, string clock_out, string UserName, string Password, string TypeEmployee) {
        ifstream inputFile(m_fileName);
        string line;
        string fileUserName;
        string lineToReplace = UserName + " " + Password + " " + TypeEmployee + " " + clock_in + " " + clock_out;

        // new file to write to
        ofstream tempFile(m_fileName + "_temp.txt");

        // loops through the lines, finds matching username
        while (getline(inputFile, line)) {
            istringstream iss(line);
            if (iss >> fileUserName) {
                if (UserName == fileUserName) {
                    tempFile << lineToReplace << endl;
                    continue;
                }
            }
            tempFile << line << endl;
        }

        inputFile.close();
        tempFile.close();

        ifstream tempInputFile(m_fileName + "_temp.txt");
        ofstream originalFile(m_fileName);

        originalFile << tempInputFile.rdbuf();
        originalFile.close();
        tempInputFile.close();

        remove((m_fileName + "_temp.txt").c_str()); // Delete the temporary file
    }
    void OnAbout(wxCommandEvent& event)
    {
        wxMessageBox("This is a program that will display a simple TimeCard Application. "
                     "Where the user will be able to create the new users or they will have "
                     "the opportunity to log-in as a worker or admin. "
                     "From here the workers should be able to clock in and clock out and then at the "
                     "end of a pay period be able to see their weekly statistics about how many hours "
                     "they worked and how much they made. "
                     "With the admin they should be able to set their workers pay rate and be able to schedule shifts"
                     " for those workers that they have.",
                     "About our Program", wxOK | wxICON_INFORMATION);
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