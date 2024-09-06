#include <windows.h>
#include <commdlg.h> // For common dialogs like OpenFile and SaveFile
#include <stdio.h>
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static char sourceFileName[MAX_PATH];
    static char destFileName[MAX_PATH];

    switch (msg) {
        case WM_CREATE:
            CreateWindow("BUTTON", "Select Source File", WS_VISIBLE | WS_CHILD, 20, 20, 150, 30, hwnd, (HMENU) 1, NULL, NULL);
            CreateWindow("BUTTON", "Select Destination File", WS_VISIBLE | WS_CHILD, 20, 70, 150, 30, hwnd, (HMENU) 2, NULL, NULL);
            CreateWindow("BUTTON", "Copy File", WS_VISIBLE | WS_CHILD, 20, 120, 150, 30, hwnd, (HMENU) 3, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                OPENFILENAME ofn;
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hwnd;
                ofn.lpstrFile = sourceFileName;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(sourceFileName);
                ofn.lpstrFilter = "All Files\0*.*\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrTitle = "Select Source File";
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                GetOpenFileName(&ofn);
            } else if (LOWORD(wParam) == 2) {
                OPENFILENAME ofn;
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hwnd;
                ofn.lpstrFile = destFileName;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(destFileName);
                ofn.lpstrFilter = "All Files\0*.*\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrTitle = "Select Destination File";
                ofn.Flags = OFN_PATHMUSTEXIST;
                GetSaveFileName(&ofn);
            } else if (LOWORD(wParam) == 3) {
                if (sourceFileName[0] != '\0' && destFileName[0] != '\0') {
                    FILE *srcFile = fopen(sourceFileName, "rb");
                    if (srcFile == NULL) {
                        MessageBox(hwnd, "Could not open source file.", "Error", MB_OK | MB_ICONERROR);
                        return 0;
                    }

                    FILE *dstFile = fopen(destFileName, "wb");
                    if (dstFile == NULL) {
                        MessageBox(hwnd, "Could not open destination file.", "Error", MB_OK | MB_ICONERROR);
                        fclose(srcFile);
                        return 0;
                    }

                    char buffer[1024];
                    size_t bytesRead;

                    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
                        fwrite(buffer, 1, bytesRead, dstFile);
                    }

                    fclose(srcFile);
                    fclose(dstFile);

                    MessageBox(hwnd, "File copied successfully.", "Success", MB_OK | MB_ICONINFORMATION);
                } else {
                    MessageBox(hwnd, "Please select both source and destination files.", "Error", MB_OK | MB_ICONERROR);
                }
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WindowProcedure;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "MyWindowClass";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "MyWindowClass",
        "File Copy Application",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}
