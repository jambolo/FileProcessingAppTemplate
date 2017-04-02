#if !defined( FILEPROCESSORDLG_H_INCLUDED )
#define FILEPROCESSORDLG_H_INCLUDED

#pragma once

/** @file *//********************************************************************************************************

                                                  FileProcessorDlg.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/FileProcessingAppTemplate/FileProcessorDlg.h#3 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "resource.h"

class FileProcessor;


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

class CFileProcessorDlg : public CDialog
{
public:

	// Custom Windows messages handled by this dialog box

	enum CustomWindowsMessages
	{
		WM_THREADFINISHED = WM_APP,
		WM_THREADUPDATE
	};

// Construction
	CFileProcessorDlg( CWnd* pParent = NULL );	// standard constructor

	// Override
	virtual int DoModal( FileProcessor * processor );

// Dialog Data
	//{{AFX_DATA( CFileProcessorDlg )
	enum { IDD = IDD_FILEPROCESSOR_DIALOG };
	CProgressCtrl	m_ProgressBar;
	CString	m_FileName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL( CFileProcessorDlg )
	protected:
	virtual void DoDataExchange( CDataExchange* pDX );	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG( CFileProcessorDlg )
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LONG OnThreadFinished( UINT wParam, LONG lParam );
	LONG OnThreadUpdate(UINT wParam, LONG lParam);

	FileProcessor * m_Processor;
};

//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined( FILEPROCESSORDLG_H_INCLUDED )
