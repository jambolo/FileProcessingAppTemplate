/** @file *//********************************************************************************************************

                                                 FileProcessorDlg.cpp

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/FileProcessingAppTemplate/FileProcessorDlg.cpp#3 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "stdafx.h"

#include "FileProcessorDlg.h"

#include "FileProcessor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

CFileProcessorDlg::CFileProcessorDlg( CWnd* pParent /*=NULL*/ )
	: CDialog( CFileProcessorDlg::IDD, pParent )
{
	//{{AFX_DATA_INIT( CFileProcessorDlg )
	m_FileName = _T( "" );
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CFileProcessorDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP( CFileProcessorDlg )
	DDX_Control( pDX, IDC_PROGRESSBAR, m_ProgressBar );
	DDX_Text( pDX, IDC_FILENAME, m_FileName );
	//}}AFX_DATA_MAP
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

BEGIN_MESSAGE_MAP( CFileProcessorDlg, CDialog )
	//{{AFX_MSG_MAP( CFileProcessorDlg )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_THREADFINISHED, OnThreadFinished )
	ON_MESSAGE( WM_THREADUPDATE, OnThreadUpdate )
END_MESSAGE_MAP()



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/


BOOL CFileProcessorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon( m_hIcon, TRUE );			// Set big icon
	SetIcon( m_hIcon, FALSE );		// Set small icon
	
	m_ProgressBar.SetPos( 0 );

	// Signal the processing thread that we are ready to go

	m_Processor->Start();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

int CFileProcessorDlg::DoModal( FileProcessor * processorThread )
{
	m_Processor = processorThread;

	return CDialog::DoModal();
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

LONG CFileProcessorDlg::OnThreadFinished( UINT wParam, LONG lParam )
{
	CDialog::OnOK();

	return 0;
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

LONG CFileProcessorDlg::OnThreadUpdate( UINT wParam, LONG lParam )
{
	float percentComplete;

	m_Processor->GetStatus( &percentComplete, &m_FileName );

	m_ProgressBar.SetPos( int( percentComplete + .5f ) );

	UpdateData( FALSE );

	return 0;
}





/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CFileProcessorDlg::OnPaint() 
{
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
	if ( IsIconic() )
	{
		CPaintDC dc( this ); // device context for painting

		SendMessage( WM_ICONERASEBKGND, ( WPARAM ) dc.GetSafeHdc(), 0 );

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics( SM_CXICON );
		int cyIcon = GetSystemMetrics( SM_CYICON );
		CRect rect;
		GetClientRect( &rect );
		int x = ( rect.Width() - cxIcon + 1 ) / 2;
		int y = ( rect.Height() - cyIcon + 1 ) / 2;

		// Draw the icon
		dc.DrawIcon( x, y, m_hIcon );
	}
	else
	{
		CDialog::OnPaint();
	}
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

HCURSOR CFileProcessorDlg::OnQueryDragIcon()
{
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
	return ( HCURSOR ) m_hIcon;
}
