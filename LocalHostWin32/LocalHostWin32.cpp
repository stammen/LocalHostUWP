//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#include "stdafx.h"
#include "LocalHostWin32.h"

#include <string>
#include <sstream>
#include <vector>
#include <wininet.h>
#include <iostream>

#pragma comment (lib, "wininet.lib")

int launchUWPApp(const std::string& cmd) {
    PROCESS_INFORMATION p_info;
    STARTUPINFOA s_info;
    DWORD ReturnValue;

    memset(&s_info, 0, sizeof(s_info));
    memset(&p_info, 0, sizeof(p_info));
    s_info.cb = sizeof(s_info);

    char systemDir[MAX_PATH];
    GetSystemDirectoryA(systemDir, MAX_PATH);
    std::string cmdPath(systemDir);
    cmdPath.append("\\cmd.exe");

    if (CreateProcessA(cmdPath.c_str(), (LPSTR)cmd.c_str(), NULL, NULL, 0, CREATE_NO_WINDOW, NULL, NULL, &s_info, &p_info)) {
        WaitForSingleObject(p_info.hProcess, INFINITE);
        GetExitCodeProcess(p_info.hProcess, &ReturnValue);
        CloseHandle(p_info.hProcess);
        CloseHandle(p_info.hThread);
    }
    return ReturnValue;
}


HRESULT getStringFromServer(const std::wstring& url, std::string& result)
{
    HINTERNET hInternet = NULL;
    HINTERNET hFile = NULL;

    hInternet = InternetOpenW(L"WMP", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    hFile = InternetOpenUrl(hInternet, url.c_str(), NULL, 0, 0, 0);
    if (hFile != NULL)
    {
        std::vector<char> buffer(4096);
        DWORD dwBytesRead = -1;
        BOOL bKeepReading = true;

        while (bKeepReading && dwBytesRead != 0)
        {
            bKeepReading = InternetReadFile(hFile, buffer.data(), static_cast<DWORD>(buffer.capacity()), &dwBytesRead);
            if (dwBytesRead > 0)
            {
                result.append(buffer.data(), dwBytesRead);
            }
        }
    }

    HRESULT hr = HRESULT_FROM_WIN32(GetLastError());

    // Close any open handles.
    if (hFile) InternetCloseHandle(hFile);
    if (hInternet) InternetCloseHandle(hInternet);

    return hr;
}

std::string urlEncode(const std::string& input)
{
    // urlencode the result from the server
    std::vector<char> buffer;
    DWORD size = static_cast<DWORD>(input.length() * 2);
    buffer.reserve(size);
    InternetCanonicalizeUrlA((LPCSTR)input.c_str(), (LPSTR)buffer.data(), &size, NULL);
    std::string encoded;
    encoded.append(buffer.data(), size);
    return encoded;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // cmd line of app contains protocol in form "com.stammen.localhostwin32:?url=http://localhost:8000/test.json?foo=bar"
    // we need everything after url=
    std::wstring cmdLine(lpCmdLine);
    auto pos = cmdLine.find_first_of(L'=');
    std::wstring url = cmdLine.substr(pos + 1);

    // get the data from the server (localhost in this example)
    std::string result;
    HRESULT error = getStringFromServer(url, result);

    // com.stammen.localhostuwp: is the protocol of the UWP app
    std::string command = "/c start com.stammen.localhostuwp:?";

    // urlencode the result from the server
    std::string encoded = urlEncode(result);

    // create the command to return the result to the UWP app via protocol launch
    command.append(encoded);
    launchUWPApp(command.c_str());
    return 0;
}





