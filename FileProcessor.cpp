/** @file *//********************************************************************************************************

                                                  FileProcessor.cpp

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/FileProcessingAppTemplate/FileProcessor.cpp#3 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "stdafx.h"

#include "FileProcessor.h"

#include "Misc/AfxAssert.h"

#include "FileProcessorDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

FileProcessor::FileProcessor( CStringVector const files, Processor processor, CFileProcessorDlg * dialog )
	: m_Files( files ),
	m_Processor( processor ),
	m_pDialog( dialog )
{
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

FileProcessor::~FileProcessor()
{
	// We have to tell the thread to exit and then wait, otherwise we will
	// delete member variables that the thread might still be using.

	End( true );
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

int FileProcessor::Main( int command )
{
	// Wait for the dialog box to appear

	CSingleLock( &m_StartEvent, TRUE );

	// Process each file, updating the dialog box before each one

	CStringVector::const_iterator i; 
	for ( i = m_Files.begin(); i != m_Files.end(); i++ )
	{
		// Check if the processing is canceled

		if ( ::WaitForSingleObject( m_AbortEvent.m_hObject, 0 ) == WAIT_OBJECT_0 )
			return CMD_EXIT;

		// Set the current state to the percent of files processed and the next file to process

		SetStatus( float( i - m_Files.begin() ) / float( m_Files.size() ) * 100.f, *i );

		// Tell the dialog box to update

		if ( m_pDialog )
		{
			::PostMessage( m_pDialog->GetSafeHwnd(), CFileProcessorDlg::WM_THREADUPDATE, 0, 0 );
		}

		// Process the file

		m_Processor( *i );
	}

	// Tell the dialog box to do a final update (clearing the file name)

	SetStatus( 100.f, CString() );
	if ( m_pDialog )
	{
		::PostMessage( m_pDialog->GetSafeHwnd(), CFileProcessorDlg::WM_THREADUPDATE, 0, 0 );
	}

	// Tell the dialog box that we are done

	if ( m_pDialog )
	{
		::PostMessage( m_pDialog->GetSafeHwnd(), CFileProcessorDlg::WM_THREADFINISHED, 0, 0 );
	}

	return CMD_EXIT;
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void FileProcessor::GetStatus( float *pPercentComplete, CString * pCurrentFile )
{
	CSingleLock( &m_StatusCriticalSection, TRUE );

	*pPercentComplete = m_PercentComplete;
	*pCurrentFile = m_CurrentFile;
}


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void FileProcessor::SetStatus( float percentComplete, CString const & currentFile )
{
	ASSERT_LIMITS( 0.f, percentComplete, 100.f );

	CSingleLock( &m_StatusCriticalSection, TRUE );

	m_PercentComplete = percentComplete;
	m_CurrentFile = currentFile;
}
