#include <cstdio>
#include <string>
#include <windows.h>

std::string ue4ss_dll_name = "UE4SS.dll";
std::string palserver_exe_name = "PalServer-Win64-Shipping-Cmd.exe";

int wmain(int argc, wchar_t *argv[ ]) {
    std::string arguments;
    for (int i = 1; i < argc; i++) {
        std::wstring ws(argv[i]);
        std::string arg(ws.begin(), ws.end());
        arguments += std::string(" ") + arg;
    }

    std::string commandLine = palserver_exe_name + arguments;
    printf("Starting as: %s\n", commandLine.c_str());


    // Start PalServer .exe
    STARTUPINFOA si = {.cb = sizeof si};
    PROCESS_INFORMATION pi = {0};

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    ZeroMemory(&pi, sizeof(pi));

    // Create process, but suspended
    CreateProcessA(palserver_exe_name.c_str(), (char*)commandLine.c_str(), NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);

    printf("Started PalServer (suspended)...\n");

    // Inject
    LPVOID alloc = VirtualAllocEx(pi.hProcess, NULL, ue4ss_dll_name.size(), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!alloc) {
        printf("VirtualAllocEx failed.\n");
        goto cleanup;
    }

    if (WriteProcessMemory(pi.hProcess, alloc, ue4ss_dll_name.c_str(), ue4ss_dll_name.size(), NULL) == 0) {
        printf("WriteProcessMemory failed.\n");
        goto free_and_cleanup;
    }

    HANDLE handle = CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, alloc, 0, NULL);
    if (!handle) {
        printf("CreateRemoteThread failed.\n");
        goto free_and_cleanup;
    }

    WaitForSingleObject(handle, 5000);
    VirtualFreeEx(pi.hProcess, alloc, 0, MEM_RELEASE);
    printf("DLL Injected...\n");

    // Resume
    ResumeThread(pi.hThread);
    printf("Server should now be running!\n");

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);
    // Close process and thread handles.
free_and_cleanup:
    VirtualFreeEx(pi.hProcess, alloc, 0, MEM_RELEASE);
cleanup:
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    fflush(stdout);
    return EXIT_SUCCESS;
}
