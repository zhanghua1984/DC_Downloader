// Translator.h : main header file for the CTranslatorDlg application
//

#if !defined(AFX_COMMTEST_H__094EF004_CBE0_11D7_B4F9_00E04C74763F__INCLUDED_)
#define AFX_COMMTEST_H__094EF004_CBE0_11D7_B4F9_00E04C74763F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// TranslatorApp:
// See Translator.cpp for the implementation of this class
//

class CTranslatorApp : public CWinApp
{
public:
	CTranslatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTranslatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTranslatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSLATOR_H__094EF004_CBE0_11D7_B4F9_00E04C74763F__INCLUDED_)
