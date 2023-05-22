#ifndef IMAGE_EXPANSION_DIALOG_H
#define IMAGE_EXPANSION_DIALOG_H

#include <wx/wx.h>

class ImageExpansionDialog : public wxDialog
{
public:
  ImageExpansionDialog(const wxString& title);
  wxBitmap wfc_image;

private:
  void FileOpen(wxCommandEvent& WXUNUSED(event) );
  void FileSave(wxCommandEvent& WXUNUSED(event) );
  void OnPaint( wxPaintEvent &WXUNUSED(event) );

  wxDECLARE_EVENT_TABLE();

};

enum
{
    ID_OPEN_BUTTON = 1,
    ID_SAVE_BUTTON = 2
};

#endif