#if !defined( FILEPROCESSINGAPPTEMPLATE_H_INCLUDED )
#define FILEPROCESSINGAPPTEMPLATE_H_INCLUDED

#pragma once

/** @file *//********************************************************************************************************

                                             FileProcessingAppTemplate.h

						                    Copyright 2003, John J. Bolton
	--------------------------------------------------------------------------------------------------------------

	$Header: //depot/FileProcessingAppTemplate/FileProcessingAppTemplate.h#3 $

	$NoKeywords: $

 ********************************************************************************************************************/

#include "resource.h"		// main symbols


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

class CFileProcessingAppTemplateApp : public CWinApp
{
public:
	CFileProcessingAppTemplateApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileProcessingAppTemplateApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFileProcessingAppTemplateApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



#endif // !defined( FILEPROCESSINGAPPTEMPLATE_H_INCLUDED )
