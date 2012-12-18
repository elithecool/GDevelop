/** \file
 *  Game Develop
 *  2008-2012 Florian Rival (Florian.Rival@gmail.com)
 */
#include "EditorScene.h"

//(*InternalHeaders(EditorScene)
#include <wx/bitmap.h>
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)
#include <wx/aui/aui.h>
#include <wx/toolbar.h>
#include <wx/config.h>
#include <wx/brush.h>
#include <wx/log.h>
#include <wx/dcclient.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/ribbon/toolbar.h>

#include "GDCore/PlatformDefinition/Layout.h"
#include "GDL/Game.h"
#include "GDL/RuntimeGame.h"
#include "MainFrame.h"
#include "GDCore/IDE/Dialogs/MainFrameWrapper.h"
#include "SceneCanvas.h"
#include "GDL/IDE/Dialogs/DebuggerGUI.h"
#include "EditorObjets.h"
#include "EditorLayers.h"
#include "InitialPositionBrowserDlg.h"
#include "GDL/IDE/Dialogs/ProfileDlg.h"
#include "GDL/IDE/Dialogs/RenderDialog.h"
#include "GDCore/IDE/Dialogs/ChooseLayerDialog.h"
#include "GDCore/IDE/Dialogs/ChooseObjectDialog.h"
#include "GDCore/Tools/HelpFileAccess.h"
#include "EventsEditor.h"
#include "GridSetup.h"
#include "GDCore/IDE/wxTools/SkinHelper.h"
#include "Dialogs/LayoutEditorPropertiesPnl.h"

#ifdef __WXGTK__
#include <gtk/gtk.h>
#endif

//(*IdInit(EditorScene)
const long EditorScene::ID_SCROLLBAR3 = wxNewId();
const long EditorScene::ID_SCROLLBAR4 = wxNewId();
const long EditorScene::ID_CUSTOM3 = wxNewId();
const long EditorScene::ID_PANEL1 = wxNewId();
const long EditorScene::ID_SCROLLBAR2 = wxNewId();
const long EditorScene::ID_SCROLLBAR1 = wxNewId();
const long EditorScene::ID_CUSTOM1 = wxNewId();
const long EditorScene::ID_PANEL5 = wxNewId();
const long EditorScene::ID_CUSTOM2 = wxNewId();
const long EditorScene::ID_PANEL6 = wxNewId();
const long EditorScene::ID_AUINOTEBOOK1 = wxNewId();
//*)


BEGIN_EVENT_TABLE(EditorScene,wxPanel)
	//(*EventTable(EditorScene)
	//*)
END_EVENT_TABLE()

EditorScene::EditorScene(wxWindow* parent, gd::Project & project_, gd::Layout & layout_, const gd::MainFrameWrapper & mainFrameWrapper_) :
project(project_),
layout(layout_),
mainFrameWrapper(mainFrameWrapper_)
{
    //TODO: GD C++ Platform specific code
    try
    {
        Scene & scene = dynamic_cast<Scene&>(layout);
        Game & game = dynamic_cast<Game&>(project);
    }
    catch (...) { std::cout << "Scene editor is not adapted to arbitrary gd::Layout, GD will crash."; std::cout << char(7); /*Not a GD C++ Platform scene*/ }

    Scene & scene = dynamic_cast<Scene&>(layout);
    RuntimeGame & game = dynamic_cast<RuntimeGame&>(project);

	//(*Initialize(EditorScene)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	notebook = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_SPLIT|wxAUI_NB_TAB_MOVE|wxAUI_NB_SCROLL_BUTTONS|wxAUI_NB_BOTTOM|wxNO_BORDER);
	scenePanel = new wxPanel(notebook, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	scenePanel->SetBackgroundColour(wxColour(255,255,255));
	vScrollbar = new wxScrollBar(scenePanel, ID_SCROLLBAR3, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL, wxDefaultValidator, _T("ID_SCROLLBAR3"));
	vScrollbar->SetScrollbar(2500, 10, 5000, 10);
	hScrollbar = new wxScrollBar(scenePanel, ID_SCROLLBAR4, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL, wxDefaultValidator, _T("ID_SCROLLBAR4"));
	hScrollbar->SetScrollbar(2500, 10, 5000, 10);
	layoutEditorCanvas = new SceneEditorCanvas(scenePanel, game, scene, scene.GetInitialInstances(), scene.GetAssociatedLayoutEditorCanvasOptions(), mainFrameWrapper);
	oldScenePanel = new wxPanel(notebook, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	oldScenePanel->SetBackgroundColour(wxColour(255,255,255));
	oldScrollBar2 = new wxScrollBar(oldScenePanel, ID_SCROLLBAR2, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL, wxDefaultValidator, _T("ID_SCROLLBAR2"));
	oldScrollBar2->SetScrollbar(2500, 10, 5000, 10);
	oldScrollBar1 = new wxScrollBar(oldScenePanel, ID_SCROLLBAR1, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL, wxDefaultValidator, _T("ID_SCROLLBAR1"));
	oldScrollBar1->SetScrollbar(2500, 10, 5000, 10);
	sceneCanvas = new SceneCanvas(oldScenePanel, game, scene, scene.GetInitialInstances(), scene.GetAssociatedLayoutEditorCanvasOptions(), mainFrameWrapper);
	eventsPanel = new wxPanel(notebook, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	eventsPanel->SetBackgroundColour(wxColour(255,255,255));
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableRow(0);
	eventsEditor = new EventsEditor(eventsPanel, game, scene, &scene.GetEvents(), mainFrameWrapper);
	FlexGridSizer3->Add(eventsEditor, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	eventsPanel->SetSizer(FlexGridSizer3);
	FlexGridSizer3->Fit(eventsPanel);
	FlexGridSizer3->SetSizeHints(eventsPanel);
	notebook->AddPage(scenePanel, _("New scene editor"));
	notebook->AddPage(oldScenePanel, _("Scene"), false, wxBitmap(wxImage(_T("res/sceneeditor.png"))));
	notebook->AddPage(eventsPanel, _("Events"), false, wxBitmap(wxImage(_T("res/events16.png"))));
	FlexGridSizer1->Add(notebook, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_SCROLLBAR3,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnvScrollbarScroll);
	Connect(ID_SCROLLBAR3,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&EditorScene::OnvScrollbarScroll);
	Connect(ID_SCROLLBAR3,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnvScrollbarScroll);
	Connect(ID_SCROLLBAR4,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnhScrollbarScroll);
	Connect(ID_SCROLLBAR4,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&EditorScene::OnhScrollbarScroll);
	Connect(ID_SCROLLBAR4,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnhScrollbarScroll);
	layoutEditorCanvas->Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&EditorScene::OnsceneCanvasSetFocus,0,this);
	scenePanel->Connect(wxEVT_SIZE,(wxObjectEventFunction)&EditorScene::OnscenePanelResize,0,this);
	Connect(ID_SCROLLBAR2,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnScrollBar2Scroll);
	Connect(ID_SCROLLBAR2,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&EditorScene::OnScrollBar2Scroll);
	Connect(ID_SCROLLBAR2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnScrollBar2Scroll);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnScrollBar1Scroll);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&EditorScene::OnScrollBar1Scroll);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnScrollBar1Scroll);
	sceneCanvas->Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&EditorScene::OnsceneCanvasSetFocus,0,this);
	oldScenePanel->Connect(wxEVT_SIZE,(wxObjectEventFunction)&EditorScene::OnscenePanelResize,0,this);
	Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&EditorScene::OnnotebookPageChanged);
	Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGING,(wxObjectEventFunction)&EditorScene::OnnotebookPageChanging);
	//*)

	//Prepare pane manager
    m_mgr.SetManagedWindow( this );

    layoutEditorCanvas->SetParentAuiManager(&m_mgr);
    layoutEditorCanvas->SetScrollbars(hScrollbar, vScrollbar);

    //Create all editors linked to scene canvas.
    objectsEditor = boost::shared_ptr<EditorObjets>(new EditorObjets(this, game, scene, mainFrameWrapper) );
    layersEditor =  boost::shared_ptr<EditorLayers>(new EditorLayers(this, game, scene, mainFrameWrapper) );
    //debugger =  boost::shared_ptr<DebuggerGUI>(new DebuggerGUI(this, sceneCanvas->GetRuntimeScene()) );
    //externalPreviewWindow = boost::shared_ptr<RenderDialog>(new RenderDialog(this, sceneCanvas) );
    initialPositionBrowser =  boost::shared_ptr<InitialPositionBrowserDlg>(new InitialPositionBrowserDlg(this, scene.GetInitialInstances(), *sceneCanvas) );
    //profilerDlg =  boost::shared_ptr<ProfileDlg>(new ProfileDlg(this));
    propertiesPnl = boost::shared_ptr<LayoutEditorPropertiesPnl>(new LayoutEditorPropertiesPnl(this));

    //Link some editors together
    sceneCanvas->SetObjectsEditor( objectsEditor );
    sceneCanvas->SetLayersEditor( layersEditor );
    //sceneCanvas->SetDebugger( debugger );
    sceneCanvas->SetExternalWindow( externalPreviewWindow );
    sceneCanvas->SetInitialPositionBrowser( initialPositionBrowser );
    //sceneCanvas->SetProfileDialog( profilerDlg );
    sceneCanvas->SetPropertiesPanel( propertiesPnl );
    sceneCanvas->SetParentPanelAndDockManager( oldScenePanel, &m_mgr );
    sceneCanvas->SetScrollbars(oldScrollBar1, oldScrollBar2);

    eventsEditor->SetAssociatedSceneCanvas(sceneCanvas);

    //Display editors in panes
    m_mgr.AddPane( notebook, wxAuiPaneInfo().Name( wxT( "ESCenter" ) ).PaneBorder(false).Center().CloseButton( false ).Caption( _( "Scene's editor" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(false) );
    m_mgr.AddPane( objectsEditor.get(), wxAuiPaneInfo().Name( wxT( "EO" ) ).Right().CloseButton( true ).Caption( _( "Objects' editor" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(true).MinSize(208, 100) );
    m_mgr.AddPane( layersEditor.get(), wxAuiPaneInfo().Name( wxT( "EL" ) ).Float().CloseButton( true ).Caption( _( "Layers' editor" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(true).MinSize(200, 100).Show(false) );
    //m_mgr.AddPane( debugger.get(), wxAuiPaneInfo().Name( wxT( "DBG" ) ).Float().CloseButton( true ).Caption( _( "Debugger" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(true).MinSize(200, 100).Show(false) );
    m_mgr.AddPane( initialPositionBrowser.get(), wxAuiPaneInfo().Name( wxT( "IPB" ) ).Float().CloseButton( true ).Caption( _( "Initial positions of objects" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(true).MinSize(200, 100).Show(false) );
    //m_mgr.AddPane( profilerDlg.get(), wxAuiPaneInfo().Name( wxT( "PROFILER" ) ).Float().CloseButton( true ).Caption( _( "Profiling" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(true).MinSize(50, 50).BestSize(230,100).Show(false) );
    m_mgr.AddPane( propertiesPnl.get(), wxAuiPaneInfo().Name( wxT( "PROPERTIES" ) ).Float().CloseButton( true ).Caption( _( "Properties" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(true).MinSize(50, 50).BestSize(230,200).Show(true) );

    //Load preferences
    {
        int position = 1;
        wxConfigBase::Get()->Read("/SceneEditor/SceneEventsTab", &position);
        if (position == 0)
        {
            long style = notebook->GetWindowStyleFlag();
            style |= wxAUI_NB_TOP;
            style &= ~wxAUI_NB_BOTTOM;
            notebook->SetWindowStyleFlag(style);
        }
    }

    gd::SkinHelper::ApplyCurrentSkin(m_mgr);
    gd::SkinHelper::ApplyCurrentSkin(*notebook);

    mainFrameWrapper.GetRibbon()->SetActivePage(2);
    layoutEditorCanvas->ConnectEvents();

    wxString perspective;
	wxConfigBase::Get()->Read("/SceneEditor/LastWorkspace", &perspective);
	m_mgr.LoadPerspective(perspective);

    m_mgr.Update();
    layoutEditorCanvas->Reload();
    sceneCanvas->Reload();
}
void EditorScene::OnscenePanelResize(wxSizeEvent& event)
{
    //Manual resizing of scene's panel
    sceneCanvas->UpdateSize();

    oldScrollBar1->SetSize(0, scenePanel->GetSize().GetHeight()-oldScrollBar1->GetSize().GetHeight(), scenePanel->GetSize().GetWidth()-oldScrollBar2->GetSize().GetWidth(), oldScrollBar1->GetSize().GetHeight());
    oldScrollBar2->SetSize(scenePanel->GetSize().GetWidth()-oldScrollBar2->GetSize().GetWidth(), 0, oldScrollBar2->GetSize().GetWidth(), scenePanel->GetSize().GetHeight()-oldScrollBar1->GetSize().GetHeight());

    layoutEditorCanvas->UpdateSize();
    hScrollbar->SetSize(0, scenePanel->GetSize().GetHeight()-hScrollbar->GetSize().GetHeight(), scenePanel->GetSize().GetWidth()-vScrollbar->GetSize().GetWidth(), hScrollbar->GetSize().GetHeight());
    vScrollbar->SetSize(scenePanel->GetSize().GetWidth()-vScrollbar->GetSize().GetWidth(), 0, vScrollbar->GetSize().GetWidth(), scenePanel->GetSize().GetHeight()-hScrollbar->GetSize().GetHeight());
}

EditorScene::~EditorScene()
{
	//(*Destroy(EditorScene)
	//*)

	wxConfigBase::Get()->Write("/SceneEditor/LastWorkspace", m_mgr.SavePerspective());
	m_mgr.UnInit();
}

/**
 * Manually change the view position when the scrollbar is moved
 */
void EditorScene::OnScrollBar2Scroll(wxScrollEvent& event)
{
    int position = event.GetPosition();

    int newY = position-(oldScrollBar2->GetRange()/2)+(sceneCanvas->getSize().y/2);
    sceneCanvas->GetEditionView().setCenter( sceneCanvas->GetEditionView().getCenter().x, newY);

    sceneCanvas->ManualRefresh();
}

/**
 * Manually change the view position when the scrollbar is moved
 */
void EditorScene::OnScrollBar1Scroll(wxScrollEvent& event)
{
    int position = event.GetPosition();

    int newX = position-(oldScrollBar1->GetRange()/2)+(sceneCanvas->getSize().x/2);
    sceneCanvas->GetEditionView().setCenter( newX,  sceneCanvas->GetEditionView().getCenter().y);

    sceneCanvas->ManualRefresh();
}

void EditorScene::ForceRefreshRibbonAndConnect()
{
    if ( notebook->GetPageText(notebook->GetSelection()) == _("Scene") )
    {
        layoutEditorCanvas->RecreateRibbonToolbar();
        mainFrameWrapper.GetRibbon()->SetActivePage(2);
        layoutEditorCanvas->ConnectEvents();
    }
    else if ( notebook->GetPageText(notebook->GetSelection()) == _("Events") )
    {
        mainFrameWrapper.GetRibbon()->SetActivePage(3);
        eventsEditor->ConnectEvents();
    }
}

/**
 * Return true if the editor can be closed, false otherwise ( i.e. Scene is being previewed )
 */
bool EditorScene::CanBeClosed()
{
    if ( !sceneCanvas ) return true;

    return sceneCanvas->IsEditing();
}

/**
 * Update ribbon when notebook page has changed
 */
void EditorScene::OnnotebookPageChanged(wxAuiNotebookEvent& event)
{
    ForceRefreshRibbonAndConnect();
}

void EditorScene::OnnotebookPageChanging(wxAuiNotebookEvent& event)
{
    if ( !sceneCanvas->IsEditing() )
    {
        event.Veto();
        mainFrameWrapper.GetInfoBar()->ShowMessage(_("You can not edit events while previewing the scene."));
    }
}


void EditorScene::OnsceneCanvasSetFocus(wxFocusEvent& event)
{
    mainFrameWrapper.GetRibbon()->SetActivePage(2);
    layoutEditorCanvas->ConnectEvents();
}

void EditorScene::OnvScrollbarScroll(wxScrollEvent& event)
{
    layoutEditorCanvas->OnvScrollbarScroll(event);
}

void EditorScene::OnhScrollbarScroll(wxScrollEvent& event)
{
    layoutEditorCanvas->OnhScrollbarScroll(event);
}
