#include <windows.h>
#include <wingdi.h>
#include <winuser.h>

#define global_variable static
#define local_variable static 
#define internal static 

global_variable bool Running = true;
global_variable BITMAPINFO BitmapInfo;
global_variable void *BitmapMemory;
global_variable HBITMAP BitmapHandle; 
global_variable HDC BitmapDeviceContext;

//Device independant bitmap function. Passes custom bitmap for rendering.
internal void Win32ResizeDIBSection(int width, int height)
{
    if(BitmapHandle){
        DeleteObject(BitmapHandle);
    }
    if(!BitmapDeviceContext){
        BitmapDeviceContext = CreateCompatibleDC(0);
    }
    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = width;
    BitmapInfo.bmiHeader.biHeight = height;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;



    BitmapHandle = CreateDIBSection(
            BitmapDeviceContext,
            &BitmapInfo,
            DIB_RGB_COLORS,
            &BitmapMemory,
            0,0);
};

internal void Win32UpdateWindow(HDC DeviceContext, int x, int y, int height, int width)
{
    StretchDIBits(
            DeviceContext,
            x,
            y,
            width,
            height,
            x,
            y, 
            width, 
            height,
            BitmapMemory,
            &BitmapInfo,
            DIB_RGB_COLORS,
            SRCCOPY
            ); 
}

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
                RECT ClientRect;
                GetClientRect(
                        Window, 
                        &ClientRect 
                        );
                int width = ClientRect.right - ClientRect.left;
                int height = ClientRect.bottom - ClientRect.top;
                Win32ResizeDIBSection(width,height);
            }
            break;
        case WM_DESTROY:
            {
                Running = false;
                break;
                case WM_CLOSE:
                {
                    Running = false;
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
                    Win32UpdateWindow(DeviceContext,x,y,width,height);
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
                Running = true;
                while (Running) {

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
