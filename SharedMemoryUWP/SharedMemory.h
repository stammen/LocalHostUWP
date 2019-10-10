//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#pragma once

#include <atomic>

namespace SharedMemoryUWP
{
    // currently using atomic locks to sync access between processes
    // for more complex data types, a cross process mutex may be needed

    struct AppInfo
    {
        std::atomic<int> page;
        std::atomic<int> numPages;
    };

    public ref class SharedMemory sealed
    {
    public:
        SharedMemory();
        int Initialize();
        int OpenSharedMemory();
        int GetNumPages();
        void SetNumPages(int numPages);
        int GetPage();
        void SetPage(int numPages);
    private:
        AppInfo* m_pAppInfo;
        ~SharedMemory();
        void Close();

        HANDLE m_handle;
    };
}
