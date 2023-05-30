
// FileAttributeCheckerDlg.h : header file
//

#pragma once
#include <memory>
#include <vector>
#include <map>
#include<string>

// CFileAttributeCheckerDlg dialog
class CFileAttributeCheckerDlg : public CDialogEx
{
// Construction
public:
	CFileAttributeCheckerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEATTRIBUTECHECKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	std::map<std::wstring, std::shared_ptr<CButton>> m_fileAttrsCtrlsMap;
	std::map<int, std::wstring> m_fileAttrsIntStrMap;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChangeFiledirPath();
	CEdit m_fileDirPathControl;
	CStatic m_staticStatus;
};
