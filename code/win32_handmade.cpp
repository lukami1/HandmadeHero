#include <windows.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    MessageBox(0,"This is handmade hero", "Handmade hero", MB_OK | MB_ICONINFORMATION);
    return 0;
}
