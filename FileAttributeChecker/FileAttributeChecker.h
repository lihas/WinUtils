
// FileAttributeChecker.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFileAttributeCheckerApp:
// See FileAttributeChecker.cpp for the implementation of this class
//

class CFileAttributeCheckerApp : public CWinApp
{
public:
	CFileAttributeCheckerApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFileAttributeCheckerApp theApp;
