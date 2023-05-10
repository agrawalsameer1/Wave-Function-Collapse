// WFC - Wave Function Collapse
// LASA Advance CS 2
// 2023

#include <wx/wx.h>
#include "ImageExpansionDialog.h"
 
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
    wxButton* m_ImageExpansionButton;
    wxButton* m_SchedulerButton;
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnImageExpansionStarted(wxCommandEvent& event);
    void OnSchedulerStarted(wxCommandEvent& event);
};
 
enum
{
    ID_IMAGEEXPANSION = 1,
    ID_SCHEDULER = 2,
    ID_IMAGEEXPANSION_BUTTON = 3,
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
    menuApps->Append(ID_IMAGEEXPANSION, "&Image Expansion...");
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
 
    Bind(wxEVT_MENU, &MyFrame::OnImageExpansionStarted, this, ID_IMAGEEXPANSION);
    Bind(wxEVT_MENU, &MyFrame::OnSchedulerStarted, this, ID_SCHEDULER);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &MyFrame::OnImageExpansionStarted, this, ID_IMAGEEXPANSION_BUTTON);
    Bind(wxEVT_BUTTON, &MyFrame::OnSchedulerStarted, this, ID_SCHEDULER_BUTTON);


    wxPanel *panel = new wxPanel(this);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(sizer);

    m_ImageExpansionButton = new wxButton(panel, ID_IMAGEEXPANSION_BUTTON, "Image Expansion");
    sizer->Add(m_ImageExpansionButton, wxSizerFlags().Centre().Border());
    m_SchedulerButton = new wxButton(panel, ID_SCHEDULER_BUTTON, "Test Button");
    sizer->Add(m_SchedulerButton, wxSizerFlags().Centre().Border());
    

}
 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("LASA Advanced CS \nSameer Agrawal\nLance Moczygemba\nJai Nagaraj\nMax Woodruff-Vale",
                 "About WFC", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnImageExpansionStarted(wxCommandEvent& WXUNUSED(event))
{
    SetStatusText("Run Image Expansion");

    ImageExpansionDialog *imgexp= new ImageExpansionDialog(wxT("ImageExpansionDialog"));
    imgexp->Show(true);


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
    wxLogMessage("hi");
}



   
