/*!********************************************************************

   Audacity: A Digital Audio Editor

   @file MovableControl.h

   @author Vitaly Sverchinsky

**********************************************************************/

#pragma once

#include <wx/event.h>
#include <wx/window.h>

//Event generated by MovableControl when item is picked,
//dragged or dropped, extends wxCommandEvent interface
//with "source" and "target" indices which denote the
//initial and final element positions inside wxSizer (if present)
class MovableControlEvent final : public wxCommandEvent
{
    int mSourceIndex{ -1 };
    int mTargetIndex{ -1 };
public:
    MovableControlEvent(wxEventType eventType, int winid = 0);

    void SetSourceIndex(int index) noexcept;
    int GetSourceIndex() const noexcept;

    void SetTargetIndex(int index) noexcept;
    int GetTargetIndex() const noexcept;

    wxEvent* Clone() const override;
};

wxDECLARE_EVENT(EVT_MOVABLE_CONTROL_DRAG_STARTED, MovableControlEvent);
wxDECLARE_EVENT(EVT_MOVABLE_CONTROL_DRAG_POSITION, MovableControlEvent);
wxDECLARE_EVENT(EVT_MOVABLE_CONTROL_DRAG_FINISHED, MovableControlEvent);

//Base class for the controls that can be moved with drag-and-drop
//action. Currently implementation is far from being generic and
//can work only in pair with wxBoxSizer with wxVERTICAL layout.
class MovableControl : public wxWindow
{
    bool mDragging { false };
    wxPoint mInitialPosition;

    int mTargetIndex { -1 };
    int mSourceIndex { -1 };
public:

    MovableControl() = default;

    MovableControl(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
                   long style = 0, const wxString& name = wxPanelNameStr);

    void Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0,
                const wxString& name = wxPanelNameStr);

    void ProcessDragEvent(wxWindow* target, wxEventType eventType);

    int FindIndexInParent() const;

private:

    void OnKeyDown(wxKeyEvent& evt);

    void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);

    void DragFinished();

    void OnMouseDown(wxMouseEvent& evt);

    void OnMouseUp(wxMouseEvent& evt);

    void OnMove(wxMouseEvent& evt);
};
