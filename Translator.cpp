// commtest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Translator.h"
#include "TranslatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTranslatorApp

BEGIN_MESSAGE_MAP(CTranslatorApp, CWinApp)
	//{{AFX_MSG_MAP(CTranslatorApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTranslatorApp construction

CTranslatorApp::CTranslatorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTranslatorApp object

CTranslatorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTranslatorApp initialization

BOOL CTranslatorApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	
	if (CoInitialize(NULL)!=0) 
		
	{ 
		
		AfxMessageBox("初始化COM支持库失败!"); 
		
		exit(1); 
		
	 } 



	CTranslatorDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	CoUninitialize(); 

	using namespace std;

	return FALSE;
}
