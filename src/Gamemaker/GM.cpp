// Copyright Chris Sixsmith 2017. All Rights Reserved.

#include "GM.h"
#include "Project2.h"

using namespace std;

GMResource::GMResource(GMProject2* Project, string Key, string DataPath)
{
	m_Key = Key;
	m_DataPath = DataPath;
	m_Project = Project;
}

