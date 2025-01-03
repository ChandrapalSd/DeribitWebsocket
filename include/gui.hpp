#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


namespace dw {
    class MyApp : public wxApp
    {
    public:
        virtual bool OnInit();
    };

    class MyFrame : public wxFrame
    {
    public:
        MyFrame();

    private:
        void OnHello(wxCommandEvent& event);
        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
    };

    enum WXID {
        Hello = 1,
        Count
    };

}