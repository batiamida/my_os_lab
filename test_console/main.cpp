#include <iostream>
#include <windows.h>

//#define FUNC "SomeFunction"
//
//typedef void(__cdecl *my_functionProc)();
//my_functionProc my_function;
//
//using namespace std;

using namespace std;

int main()
{

    HANDLE hFileMap;
    BOOL bResult;
    PCHAR lpBuffer = NULL;
    int Buffer[10000];
    for(int _=0; _ < 10000; _++){
        int r = rand();
        Buffer[_] = r;
    }

    size_t szBuffer = sizeof(Buffer);
    hFileMap = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            256,
            "C:\\Users\\Gram\\Desktop\\testProject_cpp\\test_console\\MyFileMap"
    );
    if (hFileMap == 0){
        cout << " Creation of our file mapping Failed: " << GetLastError() << endl;
    }
    cout << "Success" << endl;

    lpBuffer = (PCHAR)MapViewOfFile(
                     hFileMap,
                     FILE_MAP_ALL_ACCESS,
                     0,
                     0,
                     256
                );
    if (lpBuffer == NULL){
        cout << "Map view of our file is failed: " << GetLastError() << endl;
    }
    cout << "Map view success" << endl;

    CopyMemory(lpBuffer, Buffer, szBuffer);

    bResult = UnmapViewOfFile(lpBuffer);

    if (bResult == 0){
        cout << "Unmap View of File failed: " << GetLastError() << endl;
    }
    cout << "Unmap View of File success" << endl;




//    HINSTANCE lib = LoadLibrary("C:\\Users\\Gram\\Desktop\\os_lab\\LabDLL\\bin\\Debug\\LabDLL.dll");
//    my_function = (my_functionProc)GetProcAddress(lib, FUNC);
//    my_function();
//    FreeLibrary(lib);
    return 0;
}

