
// FileAttributeCheckerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FileAttributeChecker.h"
#include "afxdialogex.h"
#include "FileAttributeCheckerDlg.h"
#include <filesystem>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileAttributeCheckerDlg dialog

//std::wstring fileAttrs[] = {
//	L"READONLY", L"HIDDEN", L"SYSTEM", L"DIRECTORY", L"ARCHIVE", L"DEVICE", L"NORMAL", L"TEMPORARY", L"SPARSE FILE", L"REPARSE POINT", L"COMPRESSED", L"OFFLINE", L"NOT CONTENT INDEXED", L"ENCRYPTED", L"INTEGRITY STREAM", L"VIRTUAL", L"NO SCRUB DATA", L"EA", L"PINNED", L"UNPINNED", L"RECALL ON OPEN", L"RECALL ON DATA ACCESS"
//};

std::map<int, std::wstring> fileAttrsMap = {
{FILE_ATTRIBUTE_READONLY,				L"READONLY"},
{FILE_ATTRIBUTE_HIDDEN,					L"HIDDEN"},
{FILE_ATTRIBUTE_SYSTEM,					L"SYSTEM"},
{FILE_ATTRIBUTE_DIRECTORY,				L"DIRECTORY"},
{FILE_ATTRIBUTE_ARCHIVE,				L"ARCHIVE"},
{FILE_ATTRIBUTE_DEVICE,					L"DEVICE"},
{FILE_ATTRIBUTE_NORMAL,					L"NORMAL"},
{FILE_ATTRIBUTE_TEMPORARY,				L"TEMPORARY"},
{FILE_ATTRIBUTE_SPARSE_FILE,			L"SPARSE FILE"},
{FILE_ATTRIBUTE_REPARSE_POINT,			L"REPARSE POINT"},
{FILE_ATTRIBUTE_COMPRESSED,				L"COMPRESSED"},
{FILE_ATTRIBUTE_OFFLINE,				L"OFFLINE"},
{FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,	L"NOT CONTENT INDEXED"},
{FILE_ATTRIBUTE_ENCRYPTED,				L"ENCRYPTED"},
{FILE_ATTRIBUTE_INTEGRITY_STREAM,		L"INTEGRITY STREAM"},
{FILE_ATTRIBUTE_VIRTUAL,				L"VIRTUAL"},
{FILE_ATTRIBUTE_NO_SCRUB_DATA,			L"NO SCRUB DATA"},
{FILE_ATTRIBUTE_EA,					    L"EA"},
{FILE_ATTRIBUTE_PINNED,					L"PINNED"},
{FILE_ATTRIBUTE_UNPINNED,				L"UNPINNED"},
{FILE_ATTRIBUTE_RECALL_ON_OPEN,			L"RECALL ON OPEN"},
{FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS,	L"RECALL ON DATA ACCESS"},
};

CFileAttributeCheckerDlg::CFileAttributeCheckerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEATTRIBUTECHECKER_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileAttributeCheckerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILEDIR_PATH, m_fileDirPathControl);
	DDX_Control(pDX, IDC_STATUS_TEXT, m_staticStatus);
}

BEGIN_MESSAGE_MAP(CFileAttributeCheckerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_FILEDIR_PATH, &CFileAttributeCheckerDlg::OnChangeFiledirPath)
END_MESSAGE_MAP()


// CFileAttributeCheckerDlg message handlers

BOOL CFileAttributeCheckerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rcStatusRect;
	
	
	m_staticStatus.GetWindowRect(rcStatusRect);
	this->ScreenToClient(rcStatusRect);

	//all of the following are in dialog units
	constexpr int clb_v_space = 20;
	constexpr int clb_v_size = 15;
	constexpr int clb_h_size = 80;
	constexpr int stat_text_v_loc = 44;
	constexpr int stat_text_h_loc = 7;
	constexpr int clb_text_h_space = 20;

	constexpr int clb_id_start = 10001;
	int ctr = 0;

	for (auto& attrMapEle : fileAttrsMap)
	{
		std::wstring attr = attrMapEle.second;

		std::shared_ptr<CButton> cb(new CButton);
		
		CRect cbRectDlg;
		//cbRectDlg.top = rcStatusRect.top + clb_v_space * ctr;
		//cbRectDlg.bottom = cbRectDlg.top + clb_v_size;
		//cbRectDlg.left = rcStatusRect.left;
		//cbRectDlg.right = cbRectDlg.left + clb_h_size;

		cbRectDlg.top = stat_text_v_loc + clb_v_space * ( ctr % 8 + 1);
		cbRectDlg.bottom = cbRectDlg.top + clb_v_size;
		cbRectDlg.left = stat_text_h_loc + (clb_text_h_space + clb_h_size) * (ctr/8);
		cbRectDlg.right = cbRectDlg.left + clb_h_size;


		CRect cbRectPx = cbRectDlg;
		this->MapDialogRect(cbRectPx);
		
		//cbRectPx.MoveToX(rcStatusRect.left);
		

		cb->Create(attr.c_str(), BS_CHECKBOX, cbRectPx, this, clb_id_start + ctr);

		//clb->Create(LBS_HASSTRINGS | LBS_OWNERDRAWFIXED, clbRect, this, );
		//clb->SetWindowTextW(attr.c_str());
		cb->SetCheck(BST_UNCHECKED);
		cb->ShowWindow(SW_NORMAL);

		m_fileAttrsCtrlsMap[attr] = cb;

		ctr++;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileAttributeCheckerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileAttributeCheckerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileAttributeCheckerDlg::OnChangeFiledirPath()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString pathStr;
	m_fileDirPathControl.GetWindowTextW(pathStr);
	if (std::filesystem::exists(pathStr.GetBuffer()))
	{
		m_staticStatus.SetWindowTextW(L"");
		
		DWORD attrs = GetFileAttributes(pathStr.GetBuffer());
		std::wstringstream ss;
		ss << "0x" << std::hex << attrs;
		m_staticStatus.SetWindowTextW(ss.str().c_str());
		
		for (auto& attrMapEle : fileAttrsMap)
		{
			int attrInt = attrMapEle.first;
			std::wstring attrStr = attrMapEle.second;
			auto attrCtrl = m_fileAttrsCtrlsMap[attrStr];

			if (attrs & attrInt)
			{
				attrCtrl->SetCheck(BST_CHECKED);
			}
			else
			{
				attrCtrl->SetCheck(BST_UNCHECKED);
			}
		}

		//WIN32_FILE_ATTRIBUTE_DATA exAttrs = {};
		//GetFileAttributesEx(pathStr.GetBuffer(), GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard, &exAttrs);
		//
		//ss << " | 0x" << std::hex << exAttrs.dwFileAttributes;
		//m_staticStatus.SetWindowTextW(ss.str().c_str());
	}
	else
	{
		m_staticStatus.SetWindowTextW(L"Error! Invalid path");

		for (auto& attrMapEle : fileAttrsMap)
		{
			std::wstring attrStr = attrMapEle.second;
			auto attrCtrl = m_fileAttrsCtrlsMap[attrStr];
			attrCtrl->SetCheck(BST_UNCHECKED);
		}
	}
}
