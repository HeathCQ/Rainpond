#pragma comment(lib, "UxTheme")
#include <windows.h>
#include <uxtheme.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = (HICON) LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(0,128,0));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "window";
    wcex.hIconSm = NULL;

    RegisterClassEx(&wcex);

    HWND hWnd = CreateWindowEx(
        NULL,
        "window",
        NULL,
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        600,
        400,
        NULL,
        NULL,
        hInstance, 
        NULL); 

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_CREATE:
            SetWindowTheme(hWnd, L"", L"");
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_NCCALCSIZE:
        {
            LPNCCALCSIZE_PARAMS ncParams = (LPNCCALCSIZE_PARAMS) lParam;
            ncParams->rgrc[0].top += 4;
            ncParams->rgrc[0].left += 4;
            ncParams->rgrc[0].bottom -= 4;
            ncParams->rgrc[0].right -= 4;
            return 0;
        }
        case WM_NCPAINT:
        {
            RECT rect;
            GetWindowRect(hWnd, &rect);
            HRGN region = NULL;
            if (wParam == NULLREGION) {
                region = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
            } else {
                HRGN copy = CreateRectRgn(0, 0, 0, 0);
                if (CombineRgn(copy, (HRGN) wParam, NULL, RGN_COPY)) {
                    region = copy;
                } else {
                    DeleteObject(copy);
                }
            }
            HDC dc = GetDCEx(hWnd, region, DCX_WINDOW | DCX_CACHE | DCX_INTERSECTRGN | DCX_LOCKWINDOWUPDATE);
            if (!dc && region) {
                DeleteObject(region);
            }
            HPEN pen = CreatePen(PS_INSIDEFRAME, 4, RGB(255, 0, 0));
            HGDIOBJ old = SelectObject(dc, pen);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;
            Rectangle(dc, 0, 0, width, height);
            SelectObject(dc, old);
            ReleaseDC(hWnd, dc);
            DeleteObject(pen);
            return 0;
        }
        case WM_NCACTIVATE:
            RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW);
            return 0;
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



/*
#include <windows.h>
#include <uxtheme.h>
#pragma comment(lib, "UxTheme.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInst;
    wcex.hIcon = NULL;
    wcex.hCursor = (HICON)LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(0, 128, 0));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"window";
    wcex.hIconSm = NULL;

    RegisterClassEx(&wcex);

    HWND hWnd = CreateWindowEx(
        NULL,
        L"window",
        NULL,
        WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
        100,
        100,
        600,
        400,
        NULL,
        NULL,
        hInst,
        NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_CREATE:
        SetWindowTheme(hWnd, L"", L"");
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_NCCALCSIZE:
    {
//         LPNCCALCSIZE_PARAMS ncParams = (LPNCCALCSIZE_PARAMS)lParam;
//         ncParams->rgrc[0].top += 4;
//         ncParams->rgrc[0].left += 4;
//         ncParams->rgrc[0].bottom -= 4;
//         ncParams->rgrc[0].right -= 4;
//         return 0;
        break;
    }
    case WM_NCPAINT:
    {
        RECT rect;
        GetWindowRect(hWnd, &rect);
        HRGN region = NULL;
        if (wParam == NULLREGION) {
            region = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
        }
        else {
            HRGN copy = CreateRectRgn(0, 0, 0, 0);
            if (CombineRgn(copy, (HRGN)wParam, NULL, RGN_COPY)) {
                region = copy;
            }
            else {
                DeleteObject(copy);
            }
        }
        HDC dc = GetDCEx(hWnd, region, DCX_WINDOW | DCX_CACHE | DCX_INTERSECTRGN | DCX_LOCKWINDOWUPDATE);
        if (!dc && region) {
            DeleteObject(region);
            return 0;
        }
        HPEN pen = CreatePen(PS_INSIDEFRAME, 1, RGB(126, 126, 126));
        HGDIOBJ old = SelectObject(dc, pen);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        Rectangle(dc, 0, 0, width, height);
        SelectObject(dc, old);
        ReleaseDC(hWnd, dc);
        DeleteObject(pen);
        return 0;
    }
    case WM_NCACTIVATE:
        RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW);
        return 0;
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

*/

#include <windows.h>
#include <stdio.h>


LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[] = TEXT("SkinTest");


int left_off;
int right_off;
int top_off;
int bottom_off;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */


    wincl.hInstance = hInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if (!RegisterClassEx(&wincl))
        return 0;

    DWORD style = WS_OVERLAPPEDWINDOW;

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        szClassName,
        TEXT("Code::Blocks Template Windows App"),
        style,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        500,
        500,
        HWND_DESKTOP,
        NULL,
        hInstance,
        NULL
    );

    //
    // This prevent the round-rect shape of the overlapped window.
    //
    HRGN rgn = CreateRectRgn(0, 0, 500, 500);
    SetWindowRgn(hwnd, rgn, TRUE);

    left_off = 4;
    right_off = 4;
    top_off = 23;
    bottom_off = 4;

    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}



#define COLOR_TITLEBAR        0
#define COLOR_LEFT_BORDER     2
#define COLOR_RIGHT_BORDER    4
#define COLOR_BOTTOM_BORDER   6

int win_x, win_y, win_width, win_height;
int win_is_not_active = 0;


COLORREF borders_colors[] =
{
    RGB(255,255,0), RGB(180,180,0),    // Active titlebar - Not active titlebar
    RGB(0,255,255), RGB(0,180,180),    // Active left border - Not active left border
    RGB(255,0,255), RGB(180,0,180),    // Active right border - Not Active right border
    RGB(255,0,0),   RGB(180,0,0)       // Active bottom border - Not active bottom border
};




void draw_titlebar(HDC hdc)
{
    HBRUSH tmp, br = CreateSolidBrush(borders_colors[COLOR_TITLEBAR + win_is_not_active]);
    tmp = (HBRUSH)SelectObject(hdc, br);
    Rectangle(hdc, 0, 0, win_width, top_off);
    SelectObject(hdc, tmp);
    DeleteObject(br);
}

void draw_left_border(HDC hdc)
{
    HBRUSH tmp, br = CreateSolidBrush(borders_colors[COLOR_LEFT_BORDER + win_is_not_active]);
    tmp = (HBRUSH)SelectObject(hdc, br);
    Rectangle(hdc, 0, top_off, left_off, win_height - bottom_off);
    SelectObject(hdc, tmp);
    DeleteObject(br);
}


void draw_right_border(HDC hdc)
{
    HBRUSH tmp, br = CreateSolidBrush(borders_colors[COLOR_RIGHT_BORDER + win_is_not_active]);
    tmp = (HBRUSH)SelectObject(hdc, br);
    Rectangle(hdc, win_width - right_off, top_off, win_width, win_height - bottom_off);
    SelectObject(hdc, tmp);
    DeleteObject(br);
}


void draw_bottom_border(HDC hdc)
{
    HBRUSH tmp, br = CreateSolidBrush(borders_colors[COLOR_BOTTOM_BORDER + win_is_not_active]);
    tmp = (HBRUSH)SelectObject(hdc, br);
    Rectangle(hdc, 0, win_height - bottom_off, win_width, win_height);
    SelectObject(hdc, tmp);
    DeleteObject(br);
}



LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_SIZE:
    {
        RECT rect;
        HRGN rgn;
        GetWindowRect(hwnd, &rect);
        win_x = rect.left;
        win_y = rect.top;
        win_width = rect.right - rect.left;
        win_height = rect.bottom - rect.top;
        //
        // I use this to set a rectangular region for the window, and not a round-rect one.
        //
        rgn = CreateRectRgn(0, 0, rect.right, rect.bottom);
        SetWindowRgn(hwnd, rgn, TRUE);
        DeleteObject(rgn);

        InvalidateRect(hwnd, NULL, 1);
        UpdateWindow(hwnd);
    }
    break;

    case WM_PAINT:
    {
        RECT rect;
        GetClientRect(hwnd, &rect);

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HBRUSH hb = CreateSolidBrush(0);
        FillRect(hdc, &rect, hb);
        DeleteObject(hb);
        EndPaint(hwnd, &ps);
        break;
    }

    case WM_NCPAINT:
    {
        HDC hdc;
        HBRUSH br;
        RECT rect;
        HRGN rgn = (HRGN)wparam;
        HRGN dirty_rgn = nullptr;

        if (wparam == 0 || wparam == 1)
            hdc = GetWindowDC(hwnd);
        else
        {
            RECT box;
            GetRgnBox(rgn, &box);

            dirty_rgn = CreateRectRgnIndirect(&box);
            hdc = GetDCEx(hwnd, dirty_rgn, DCX_WINDOW | DCX_CACHE | DCX_LOCKWINDOWUPDATE | DCX_INTERSECTRGN);
        }
        draw_titlebar(hdc);
        draw_left_border(hdc);
        draw_right_border(hdc);
        draw_bottom_border(hdc);
        ReleaseDC(hwnd, hdc);

        if (dirty_rgn)
        {
            DeleteObject(dirty_rgn);
        }
        return 0;
    }

    case WM_NCACTIVATE:
        if (wparam)
            win_is_not_active = 0;
        else
            win_is_not_active = 1;
        // Force paint our non-client area otherwise Windows will paint its own.
        SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_FRAMECHANGED);
        //RedrawWindow(hwnd, 0, 0, RDW_FRAME | RDW_UPDATENOW | RDW_NOCHILDREN);
        return 0;

    case WM_NCCALCSIZE:
    {
        if (wparam)
        {
            NCCALCSIZE_PARAMS* ncparams = (NCCALCSIZE_PARAMS*)lparam;
            printf("WM_NCCALCSIZE wparam:True\n");
            ncparams->rgrc[0].left += left_off;
            ncparams->rgrc[0].top += top_off;
            ncparams->rgrc[0].right -= right_off;
            ncparams->rgrc[0].bottom -= bottom_off;
            return 0;
        }
        else {

            RECT* rect = (RECT*)lparam;
            return 0;
        }
    }


    case WM_NCHITTEST:
    {
        LRESULT result = DefWindowProc(hwnd, message, wparam, lparam);
        switch (result)
        {
            //
            // I have to set this, because i need to draw my own min/max/close buttons
            // in different coordinates where the system draws them, so let's consider
            // all the titlebar just a tilebar for now, ignoring those buttons.
            //
        case HTCLOSE:
        case HTMAXBUTTON:
        case HTMINBUTTON:
        case HTSYSMENU:
        case HTNOWHERE:
        case HTHELP:
        case HTERROR:
            return HTCAPTION;
        default:
            return  result;
        };
    }

    case WM_ERASEBKGND:
        return 1;

    default:
        return DefWindowProc(hwnd, message, wparam, lparam);
    }

    return 0;
}