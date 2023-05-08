// WFC - Wave Form Collapse
// LASA Advance CS 2
// 2023

#include <wx/wx.h>
#include "SudokuDialog.h"
 
class MyApp : public wxApp
{
public:
    bool OnInit() override;
};
 
wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    wxButton* m_SudokuButton;
    wxButton* m_SchedulerButton;
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSudokuStarted(wxCommandEvent& event);
    void OnSchedulerStarted(wxCommandEvent& event);
};
 
enum
{
    ID_SUDOKU = 1,
    ID_SCHEDULER = 2,
    ID_SUDOKU_BUTTON = 3,
    ID_SCHEDULER_BUTTON = 4
};
 
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 
MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "WFC")
{
    wxMenu *menuApps = new wxMenu;
    menuApps->Append(ID_SUDOKU, "&Sudoku...");
    menuApps->Append(ID_SCHEDULER, "&Scheduler...");
    menuApps->AppendSeparator();
    menuApps->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuApps, "&Apps");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
 
    Bind(wxEVT_MENU, &MyFrame::OnSudokuStarted, this, ID_SUDOKU);
    Bind(wxEVT_MENU, &MyFrame::OnSchedulerStarted, this, ID_SCHEDULER);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &MyFrame::OnSudokuStarted, this, ID_SUDOKU_BUTTON);
    Bind(wxEVT_BUTTON, &MyFrame::OnSchedulerStarted, this, ID_SCHEDULER_BUTTON);


    wxPanel *panel = new wxPanel(this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);

    m_SudokuButton = new wxButton(panel, ID_SUDOKU_BUTTON, "Sudoku");
    sizer->Add(m_SudokuButton, wxSizerFlags().Centre().Border());
    m_SchedulerButton = new wxButton(panel, ID_SCHEDULER_BUTTON, "Scheduler");
    sizer->Add(m_SchedulerButton, wxSizerFlags().Centre().Border());

}
 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("LASA Advanced CS 2\nSameer Agrawal\nLance Moczygemba\nJai Nagaraj\nMax Woodruff-Vale",
                 "About WFC", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnSudokuStarted(wxCommandEvent& WXUNUSED(event))
{
    SetStatusText("Run Sudoku");

    SudokuDialog *sudoku = new SudokuDialog(wxT("SudokuDialog"));
    sudoku->Show(true);


/*
    wxMessageDialog *dial = new wxMessageDialog(this, 
      wxT("Are you sure to quit?"), wxT("Question"), 
      wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
    dial->ShowModal();
*/

}
 
void MyFrame::OnSchedulerStarted(wxCommandEvent& WXUNUSED(event))
{
    SetStatusText("Run Scheduler");
    wxLogMessage("Scheduler started...");
}



   
