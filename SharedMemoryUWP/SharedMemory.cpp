//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#include "pch.h"
#include "SharedMemory.h"

using namespace SharedMemoryUWP;
using namespace Platform;

static const TCHAR szName[] = TEXT("Local\\LocalHostUWPSharedMemory");

SharedMemory::SharedMemory()
{
    m_handle = NULL;
    m_pAppInfo = nullptr;
}

SharedMemory::~SharedMemory()
{
    Close();
}

void SharedMemory::Close()
{
    if (m_pAppInfo)
    {
        UnmapViewOfFile(m_pAppInfo);
        m_pAppInfo = nullptr;
    }

    if (m_handle)
    {
        CloseHandle(m_handle);
        m_handle = NULL;
    }
}

int SharedMemory::GetNumPages()
{
    if (m_pAppInfo)
    {
        return m_pAppInfo->numPages.load();
    }
    return 0;
}

void SharedMemory::SetNumPages(int numPages)
{
    if (m_pAppInfo)
    {
        m_pAppInfo->numPages = numPages;
    }
}

int SharedMemory::GetPage()
{
    if (m_pAppInfo)
    {
        return m_pAppInfo->page.load();
    }
    return 0;
}

void SharedMemory::SetPage(int page)
{
    if (m_pAppInfo)
    {
        m_pAppInfo->page = page;
    }
}

int SharedMemory::Initialize()
{
    int hr = S_OK;
    m_handle = CreateFileMappingFromApp(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        sizeof(KindleAppInfo),
        szName
    );

    if (m_handle == NULL)
    {
        return GetLastError();
    }

    m_pAppInfo = (KindleAppInfo*)MapViewOfFile(m_handle, // handle to map object
        FILE_MAP_ALL_ACCESS,  // read/write permission
        0,
        0,
        sizeof(KindleAppInfo));


    if (m_pAppInfo == NULL)
    {
        hr = GetLastError();
        Close();
    }

    m_pAppInfo->numPages = 0;
    m_pAppInfo->page = 0;

    return hr;
}

int SharedMemory::OpenSharedMemory()
{
    int hr = S_OK;

    Close();

    m_handle = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write access
        FALSE,                 // do not inherit the name
        szName);

    if (m_handle == NULL)
    {
        return GetLastError();
    }

    m_pAppInfo = (KindleAppInfo*)MapViewOfFile(m_handle, // handle to map object
        FILE_MAP_ALL_ACCESS,  // read/write permission
        0,
        0,
        sizeof(KindleAppInfo));

    if (m_pAppInfo == NULL)
    {
        hr = GetLastError();
        Close();
    }

    return hr;
}


