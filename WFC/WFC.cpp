// WFC - Wave Function Collapse
// LASA Advanced CS
// 2023

#include <wx/wx.h>
#include "WFC.h"
#include "WaveFunctionCollapse/include/WFC.h"
 
class MyApp : public wxApp
{
public:
    bool OnInit() override;
};
 
wxIMPLEMENT_APP(MyApp);
 
bool MyApp::OnInit()
{
    #if wxUSE_LIBPNG
        wxImage::AddHandler( new wxPNGHandler );
    #endif

    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 
MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "WFC", wxPoint(0,25), wxSize(150,200))
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
    /*
    m_SchedulerButton = new wxButton(panel, ID_SCHEDULER_BUTTON, "Schedule Generation");
    sizer->Add(m_SchedulerButton, wxSizerFlags().Centre().Border());
    m_TextButton = new wxButton(panel, ID_SCHEDULER_BUTTON, "Text Generation");
    sizer->Add(m_TextButton, wxSizerFlags().Centre().Border());
    m_MusicButton = new wxButton(panel, ID_SCHEDULER_BUTTON, "Music Generation");
    sizer->Add(m_MusicButton, wxSizerFlags().Centre().Border());
    m_SudokuButton = new wxButton(panel, ID_SCHEDULER_BUTTON, "Sudoku Solving");
    sizer->Add(m_SudokuButton, wxSizerFlags().Centre().Border());
    */
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

    wxFileDialog dialog
                 (
                    this,
                    "Testing open file dialog",
                    wxEmptyString,
                    wxEmptyString,
                    wxString::Format
                    (
                        "Supported files (*.ppm)|*.ppm|PPM files (*.ppm)|*.ppm",
                        wxFileSelectorDefaultWildcardStr,
                        wxFileSelectorDefaultWildcardStr
                    )
                 );

    dialog.CentreOnParent();
    dialog.SetDirectory(wxGetHomeDir() + "/Desktop");
    wxString filename;
    if (dialog.ShowModal() == wxID_OK)
    {
        filename = dialog.GetPath();
       
    }
    
    if ( !filename.empty() ) {
        // WFC simulation
        PPMImage* input = new PPMImage(filename.mb_str());
        WFC * wfc = new WFC();
        PPMImage output = wfc->collapse(input, 4, 16, 16);
        std::string pixelData = output.toStringBGR();
        ofstream outFile;
        outFile.open("pixels.txt", ios::out);
        outFile << pixelData;
        outFile.close();

        // Use Python to convert pixel text file to PNG
        std::string filename_python = "./WaveFunctionCollapse/src/pixelstoPNG.py";
        std::string command = "/Library/Frameworks/Python.framework/Versions/3.11/bin/python3 ";
        command += filename_python;
        system(command.c_str());

        // Display output image
        wxImage image;
        image.LoadFile("output.png");
        new MyImageFrame(this, "output.png", image, 0.1);
        
    }
}
 
void MyFrame::OnSchedulerStarted(wxCommandEvent& WXUNUSED(event))
{
    SetStatusText("Run Scheduler");
    wxLogMessage("hi");
}

wxString MyFrame::LoadUserImage(wxImage& image)
{
    wxString filename;

#if wxUSE_FILEDLG
    filename = wxLoadFileSelector("image", wxEmptyString);
    if ( !filename.empty() )
    {
        if ( !image.LoadFile(filename) )
        {
            wxLogError("Couldn't load image from '%s'.", filename);

            return wxEmptyString;
        }
    }
#endif // wxUSE_FILEDLG

    return filename;
}

