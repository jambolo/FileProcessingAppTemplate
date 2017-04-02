/** @file *//********************************************************************************************************

                                            FileProcessingAppTemplate.cpp

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/FileProcessingAppTemplate/FileProcessingAppTemplate.cpp#3 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "StdAfx.h"

#include "FileProcessingAppTemplate.h"

#include "FileProcessor.h"
#include "FileProcessorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static void Process( char const * filename );
static FileProcessor::CStringVector GetFiles( CString const & lpCmdLine );

static int s_FileCount	= 0;


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

BEGIN_MESSAGE_MAP(CFileProcessingAppTemplateApp, CWinApp)
	//{{AFX_MSG_MAP(CFileProcessingAppTemplateApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

CFileProcessingAppTemplateApp::CFileProcessingAppTemplateApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

CFileProcessingAppTemplateApp theApp;


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

BOOL CFileProcessingAppTemplateApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CFileProcessorDlg dlg;
	m_pMainWnd = &dlg;

	// Start the file processing. The processing will stop when canceled or
	// the object is deleted.

	FileProcessor::CStringVector	files( GetFiles( m_lpCmdLine ) );

#if defined( _DEBUG )

	TRACE( "Files to process:\n" );
	for ( FileProcessor::CStringVector::iterator i = files.begin(); i != files.end(); ++i )
	{
		TRACE( "        %s\n", LPCTSTR( *i ) );
	}
	TRACE( "\n" );

#endif // defined( _DEBUG )

	FileProcessor	processor( files, Process, &dlg ); 
	
	// Display the dialog box (which will start processing) until the Cancel
	// button is clicked.

	dlg.DoModal( &processor );

	// Abort the processing if it is still running

	processor.Abort();

	TRACE( "Processed %d files.\n", s_FileCount );
	return FALSE;
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

static void Process( char const * filename )
{
	// INSERT YOUR PROCESSING CODE HERE
	// Note: This function is runs in a different thread.

	TRACE( "Processing file \"%s\".\n", filename );
	Sleep( 1000 );

	++s_FileCount;
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

static FileProcessor::CStringVector GetFiles( CString const & lpCmdLine )
{
	FileProcessor::CStringVector	files;
	int								start	= 0;
	int								end		= 0;

	do
	{
		CString fileName;

		end = lpCmdLine.Find( ' ', start );
		if ( end != -1 )
		{
			fileName = lpCmdLine.Mid( start, end-start );
		}
		else
		{
			fileName = lpCmdLine.Mid( start );
		}

		if ( !fileName.IsEmpty() )
		{
			files.push_back( fileName );
		}

		start = end + 1;
	} while ( end != -1 );

	return files;
}
