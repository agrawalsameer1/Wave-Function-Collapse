#include <wx/wx.h>
#include "ImageExpansionDialog.h"

wxBEGIN_EVENT_TABLE(ImageExpansionDialog, wxDialog)
    EVT_PAINT(ImageExpansionDialog::OnPaint)
wxEND_EVENT_TABLE()

ImageExpansionDialog::ImageExpansionDialog(const wxString & title)
       : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(1024, 768))
{

  wxPanel *panel = new wxPanel(this, -1);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  wxButton *openButton = new wxButton(this, ID_OPEN_BUTTON, wxT("Open..."), 
      wxDefaultPosition, wxSize(70, 30));
  wxButton *saveButton = new wxButton(this, ID_SAVE_BUTTON, wxT("Save..."), 
      wxDefaultPosition, wxSize(70, 30));

  hbox->Add(openButton, 1);
  hbox->Add(saveButton, 1, wxLEFT, 5);

  Bind(wxEVT_BUTTON, &ImageExpansionDialog::FileOpen, this, ID_OPEN_BUTTON);
  Bind(wxEVT_BUTTON, &ImageExpansionDialog::FileSave, this, ID_SAVE_BUTTON);

  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
  vbox->Add(panel, 1);
  //vbox->Add(wfc_image);
  //wfc_image;

  SetSizer(vbox);

  //Centre();
  ShowModal();

  Destroy(); 
}

void ImageExpansionDialog::FileOpen(wxCommandEvent& WXUNUSED(event) )
{
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
    dialog.SetDirectory(wxGetHomeDir());

    if (dialog.ShowModal() == wxID_OK)
    {
        /*
        wxString extraInfo;
        wxString info;
        info.Printf("Full file name: %s\n"
                    "Path: %s\n"
                    "Name: %s\n"
                    "Custom window: %s",
                    dialog.GetPath(),
                    dialog.GetDirectory(),
                    dialog.GetFilename(),
                    extraInfo);
        wxMessageDialog dialog2(this, info, "Selected file");
        dialog2.ShowModal();
        */

        wxImage image;
        if (image.LoadFile(dialog.GetPath(), wxBITMAP_TYPE_PNG))
        {
            image.Rescale(1024, 768);
            wfc_image = wxBitmap(image);
            image.Destroy();
        }
    }
}

void ImageExpansionDialog::OnPaint( wxPaintEvent &WXUNUSED(event) )
{
    wxPaintDC dc( this );
    PrepareDC( dc );

    if (wfc_image.IsOk())
    {
        wxLogMessage("showing image");
        dc.DrawBitmap( wfc_image, 5, 15, false );
    }

}

void ImageExpansionDialog::FileSave(wxCommandEvent& WXUNUSED(event) )
{
    wxFileDialog dialog(this,
                        "Save",
                        wxEmptyString,
                        "WFC_Example.ppm",
                        "Portable Pixmap (*.ppm)|*.ppm|Image files (*.ppm)|*.ppm",
                        wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    dialog.SetFilterIndex(1);

    if (dialog.ShowModal() == wxID_OK)
    {
        wxLogMessage("%s, filter %d%s",
                     dialog.GetPath(),
                     dialog.GetFilterIndex());
    }
}


