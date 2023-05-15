#ifndef WFC_H
#define WFC_H

#include <wx/wx.h>

// Enumerations
enum
{
    ID_IMAGEEXPANSION = 1,
    ID_SCHEDULER = 2,
    ID_IMAGEEXPANSION_BUTTON = 3,
    ID_SCHEDULER_BUTTON = 4,
    ID_ROTATE_LEFT = wxID_HIGHEST+1,
    ID_ROTATE_RIGHT,
    ID_RESIZE,
    ID_ZOOM_x2,
    ID_ZOOM_DC,
    ID_ZOOM_NEAREST,
    ID_ZOOM_BILINEAR,
    ID_ZOOM_BICUBIC,
    ID_ZOOM_BOX_AVERAGE,
    ID_PAINT_BG
};


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
    wxString LoadUserImage(wxImage& image);
};

class MyImageFrame : public wxFrame
{
public:
    MyImageFrame(wxFrame *parent, const wxString& desc, const wxImage& image, double scale = 1.0)
    {
        // Retrieve image info
        wxString info;
        int xres, yres;

        switch ( GetResolutionFromOptions(image, &xres, &yres) )
        {
            case wxIMAGE_RESOLUTION_NONE:
                break;

            case wxIMAGE_RESOLUTION_CM:
                // convert to DPI
                xres = wxRound(xres / 10.0 * inches2mm);
                yres = wxRound(yres / 10.0 * inches2mm);
                wxFALLTHROUGH;

            case wxIMAGE_RESOLUTION_INCHES:
                info = wxString::Format("DPI %i x %i", xres, yres);
                break;

            default:
                wxFAIL_MSG("unexpected image resolution units");
                break;
        }

        int numImages = desc.StartsWith("Clipboard") ? 1 : image.GetImageCount(desc);
        if ( numImages > 1 )
        {
            if ( !info.empty() )
                info += ", ";

            info += wxString::Format("%d images", numImages);
        }

        Create(parent, desc, wxBitmap(image, wxBITMAP_SCREEN_DEPTH, scale), info);
    }

    MyImageFrame(wxFrame *parent, const wxString& desc, const wxBitmap& bitmap)
    {
        Create(parent, desc, bitmap);
    }

private:
    bool Create(wxFrame *parent,
                const wxString& desc,
                const wxBitmap& bitmap,
                wxString info = wxString())
    {
        if ( !wxFrame::Create(parent, wxID_ANY,
                              wxString::Format("Image from %s", desc),
                              wxPoint(70,30), wxDefaultSize,
                              wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE) )
            return false;

        m_bitmap = bitmap;
        m_zoom = 1.;
        m_useImageForZoom = false;

        wxMenu *menu = new wxMenu;
        menu->Append(wxID_SAVEAS);

        wxMenuBar *mbar = new wxMenuBar;
        mbar->Append(menu, "&Image");
        SetMenuBar(mbar);

        CreateStatusBar(2);
        SetStatusText(info, 1);

        SetClientSize(bitmap.GetWidth() /  0.1, bitmap.GetHeight() / 0.1);

        UpdateStatusBar();

        Show();

        return true;
    }

    void OnEraseBackground(wxEraseEvent& WXUNUSED(event))
    {
        // do nothing here to be able to see how transparent images are shown
    }

    void OnPaint(wxPaintEvent& WXUNUSED(event))
    {
        wxPaintDC dc(this);

        const int width = int(10 * m_zoom * m_bitmap.GetWidth());
        const int height = int(10 * m_zoom * m_bitmap.GetHeight());

        wxBitmap bitmap;
        if ( m_useImageForZoom )
        {
            bitmap = m_bitmap.ConvertToImage().Scale(width, height,
                                                     m_resizeQuality);
        }
        else
        {
            dc.SetUserScale(m_zoom, m_zoom);
            bitmap = m_bitmap;
        }

        const wxSize size = GetClientSize();
        dc.DrawBitmap
           (
                bitmap,
                dc.DeviceToLogicalX((size.x - width) / 2),
                dc.DeviceToLogicalY((size.y - height) / 2),
                true /* use mask */
           );
    }

    void UpdateStatusBar()
    {
        wxLogStatus(this, "Image size: (%d, %d), zoom %.2f",
                    m_bitmap.GetWidth(),
                    m_bitmap.GetHeight(),
                    m_zoom);
        Refresh();
    }

   // This is a copy of protected wxImageHandler::GetResolutionFromOptions()
    static wxImageResolution GetResolutionFromOptions(const wxImage& image, int* x, int* y)
    {
        wxCHECK_MSG(x && y, wxIMAGE_RESOLUTION_NONE, wxT("NULL pointer"));

        if ( image.HasOption(wxIMAGE_OPTION_RESOLUTIONX) &&
            image.HasOption(wxIMAGE_OPTION_RESOLUTIONY) )
        {
            *x = image.GetOptionInt(wxIMAGE_OPTION_RESOLUTIONX);
            *y = image.GetOptionInt(wxIMAGE_OPTION_RESOLUTIONY);
        }
        else if ( image.HasOption(wxIMAGE_OPTION_RESOLUTION) )
        {
            *x =
            *y = image.GetOptionInt(wxIMAGE_OPTION_RESOLUTION);
        }
        else // no resolution options specified
        {
            *x =
            *y = 0;

            return wxIMAGE_RESOLUTION_NONE;
        }

        // get the resolution unit too
        int resUnit = image.GetOptionInt(wxIMAGE_OPTION_RESOLUTIONUNIT);
        if ( !resUnit )
        {
            // this is the default
            resUnit = wxIMAGE_RESOLUTION_INCHES;
        }

        return (wxImageResolution)resUnit;
    }

    wxBitmap m_bitmap;
    double m_zoom;

    // If false, then wxDC is used for zooming. If true, then m_resizeQuality
    // is used with wxImage::Scale() for zooming.
    bool m_useImageForZoom = false;
    wxImageResizeQuality m_resizeQuality;

    wxDECLARE_EVENT_TABLE();

};

    wxBEGIN_EVENT_TABLE(MyImageFrame, wxFrame)
        EVT_PAINT(MyImageFrame::OnPaint)
    wxEND_EVENT_TABLE()

#endif