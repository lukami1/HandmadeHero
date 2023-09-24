#include <windows.h>
#include <wingdi.h>
#include <winuser.h>


LRESULT CALLBACK MainWindowCallBack(
  HWND Window,
  UINT Message,
  WPARAM WParam,
  LPARAM LParam 
)
{

    LRESULT Result = 0;
    switch (Message) {
        case WM_SIZE:
            {
                OutputDebugStringA("WM_SIZE \n");
            }
            break;
        case WM_DESTROY:
            {
                OutputDebugStringA("WM_DESTROY \n");
            }
            break;
        case WM_CLOSE:
            {
                OutputDebugStringA("WM_CLOSE \n");
            }
            break;
        case WM_ACTIVATEAPP:
            {
                OutputDebugStringA("WM_ACTIVATEAPP \n");
            }
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT Paint;
                HDC DeviceContext = BeginPaint(Window, &Paint);
                int x = Paint.rcPaint.left;
                int y =  Paint.rcPaint.right;
                int width = Paint.rcPaint.right - Paint.rcPaint.left;
                int height = Paint.rcPaint.bottom - Paint.rcPaint.top;
                static DWORD Operation = WHITENESS;
                BOOL res = PatBlt(DeviceContext,x,y, width,height,Operation);
                EndPaint(Window,&Paint);
            }break;
        default :
            {
                Result = DefWindowProc(Window,Message,WParam,LParam) ;
            }
            break;

    }
    return(Result);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    WNDCLASS WindowClass = {};
    WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallBack;
    WindowClass.hInstance = hInstance;
    //    HICON     hIcon;
    WindowClass.lpszClassName = "HandmadeHeroWindowClass"; 
    if (RegisterClass(&WindowClass)) {
        HWND Windowhandle = CreateWindowExA(
                0,
                WindowClass.lpszClassName,
                "Handmade Hero",
                WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                hInstance,
                0);
        if (Windowhandle) {
            while (true) {

                MSG Message;
                BOOL MessageResult = GetMessage(&Message,0,0,0);
                if(MessageResult > 0){
                    TranslateMessage(&Message);
                    DispatchMessageA(&Message);
                }else {
                    break;
                }
            }
        }
    }else
    {
    }

    return 0;
}
