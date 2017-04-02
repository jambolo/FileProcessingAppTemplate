#if !defined( FILEPROCESSOR_H_INCLUDED )
#define FILEPROCESSOR_H_INCLUDED

#pragma once

/** @file *//********************************************************************************************************

                                                   FileProcessor.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/FileProcessingAppTemplate/FileProcessor.h#3 $

	$NoKeywords: $

 ********************************************************************************************************************/


#include "Thread/Thread.h"

#include <vector>

class CFileProcessorDlg;


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

class FileProcessor : public Thread  
{
public:

	typedef std::vector< CString >	CStringVector;
	typedef void ( * Processor )( char const * filename );

	FileProcessor( CStringVector const files, Processor processor, CFileProcessorDlg * dialog = 0 );
	virtual ~FileProcessor();

	// Get the current complete percentage (0-100) and file being processed
	void GetStatus( float * pPercentComplete, CString * pCurrentFile );

	// Signal to start processing (processing will not start without this)
	void Start()							{ m_StartEvent.SetEvent(); }

	// Signal to abort processing
	void Abort()							{ m_AbortEvent.SetEvent(); }

protected:

	// Thread main

	int Main( int command );

private:

	// Set the current complete percentage (0-100) and file being processed
	void SetStatus( float percentComplete, CString const & currentFile );

	CStringVector const		m_Files;					// List of files to process
	Processor				m_Processor;				// Processing function
	CFileProcessorDlg *		m_pDialog;					// Dialog box to send updates to

	// Processing status
	CString					m_CurrentFile;				// Name of the current file being processed
	float					m_PercentComplete;			// Progress in percent

	CCriticalSection		m_StatusCriticalSection;	// Critical section to guard processing Status
	CEvent					m_StartEvent;				// This event signals that the thread should start processing
	CEvent					m_AbortEvent;				// This event signals that the thread should abort
};



#endif // !defined( FILEPROCESSOR_H_INCLUDED )
