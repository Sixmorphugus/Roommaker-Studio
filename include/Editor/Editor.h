// Copyright Chris Sixsmith 2017. All Rights Reserved.

#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Platform.h"

class RMSDLL RMSEditor : public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit();
};