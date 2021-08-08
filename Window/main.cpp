#include <windows.h>			// general windows definitions
#include <vector>
#include <string>
#include <iterator>
#include "window.h"
#include "database.h"
#include "version.h"
#include <gdiplus.h>

using namespace Gdiplus;
#pragma comment(lib, "Gdiplus")

using namespace std;


class CWindow
{

/////////////////////////////////////////
//
// Private methods and variables go here
//
/////////////////////////////////////////
private:

	// private methods

	/// <summary>
	/// Handle the <c>WM_CREATE</c> message. Any one-time code or modifications
	/// to the <c>CREATESTRUCT</c> parameters may be performed here.
	/// </summary>
	BOOL OnCreate(
		HWND			hWnd,
		LPCREATESTRUCT	pCreateStruct
	)
	{
		//TODO: add initialisation code here

		return TRUE;		// done!
	}


	/// <summary>
	/// Handle the <c>WM_PAINT</c> message.
	/// Display the application's data in its client window.
	/// </summary>
	void OnPaint(
		HWND	hWnd
	)
	{
		PAINTSTRUCT	paintStruct;			// painting structure
		HDC hDC = BeginPaint(hWnd, &paintStruct);
		// get the window dimensions
		RECT		clientRect;			// client window dimensions
		GetClientRect(hWnd, &clientRect);

		// get the device context and paint information
		Graphics graphics(hDC);
		PointF		point;
		// set origin at top left of window plus a little extra space
		point.Y = static_cast<REAL>(clientRect.top + 4);
		point.X = static_cast<REAL>(clientRect.left + 8);

		// select the font to use for text
		Font font(L"Verdana", 10, FontStyleRegular, UnitPoint, NULL);
		REAL fontHeight = font.GetHeight(graphics.GetDpiY());
		// calculate average width and set tabs every four character positions
		RectF boundRect;
		// Measure the string.
		graphics.MeasureString(L"THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG", 43, &font, RectF(0, 0, 600, fontHeight), &boundRect);

		REAL tabValue = 4 * boundRect.Width / 43;
		StringFormat stringFormat;
		stringFormat.SetTabStops(0.0f, 1, &tabValue);

		// text colour
		SolidBrush	brush(Color(128, 0, 128));
		// step through the data pointers, painting each line of text

		// add your text output codes here

		// tell windows we're finished here...
		EndPaint(hWnd, &paintStruct);
	}


	/// <summary>
	/// Dispatcher for the <c>WM_xxx</c> Windows messages.
	/// Called to action the messages generated
	/// in response to user actions on the main window.
	/// </summary>
	LRESULT CALLBACK WindowProc(
		HWND	hWnd,
		UINT	uMessage,
		WPARAM	wParam,
		LPARAM	lParam
	)
	{
		switch (uMessage)
		{
		case WM_CREATE:
			return OnCreate(hWnd, reinterpret_cast<LPCREATESTRUCT>(lParam));

		case WM_PAINT:
			OnPaint(hWnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);	// application exit code 0
			break;

		default:
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
		}

		return 0;	// the message was handled in the switch block
	}

	/// <summary>
	/// Capture the initial messages and save the 'this' pointer to the HWND
	/// </summary>
	static LRESULT CALLBACK StaticProc(
		HWND	hWnd,
		UINT	uMessage,
		WPARAM	wParam,
		LPARAM	lParam
	)
	{
		if (uMessage == WM_NCCREATE)
		{
			LPCREATESTRUCT pCreatestruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
			// save the object reference
			::SetWindowLongPtr(hWnd, GWL_USERDATA, PtrToUlong(pCreatestruct->lpCreateParams));
			// need to fall through to default handling here
		}
		CWindow* pWindow = (CWindow*)::GetWindowLongPtr(hWnd, GWL_USERDATA);
		if (pWindow != nullptr)
			return pWindow->WindowProc(hWnd, uMessage, wParam, lParam);
		else
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}


/////////////////////////////////////////
//
// Public methods and variables go here
//
/////////////////////////////////////////
public:
	CWindow()
	{
	}

	~CWindow()
	{
		// release any resources ...
	}

	HRESULT Create(
		HINSTANCE	hInstance
	)
	{
		WNDCLASSEX	wndClassEx;	// class structure
		HWND		hWnd;

		//	Register the window class
		wndClassEx.cbSize			= sizeof wndClassEx;
		wndClassEx.style			= CS_HREDRAW | CS_VREDRAW;
		wndClassEx.lpfnWndProc		= StaticProc;
		wndClassEx.cbClsExtra		= 0;
		wndClassEx.cbWndExtra =		0;
		wndClassEx.hInstance		= hInstance;
		wndClassEx.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
		wndClassEx.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wndClassEx.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wndClassEx.lpszMenuName		= MAKEINTRESOURCE(IDR_MAINFRAME);
		wndClassEx.lpszClassName	= TEXT("Win32App1");
		wndClassEx.hIconSm			= NULL;

		if (RegisterClassEx(&wndClassEx))
		{

			// create the main frame window
			hWnd = CreateWindowEx(
				WS_EX_CLIENTEDGE,			// extended window style
				wndClassEx.lpszClassName,	// registered class name
				wndClassEx.lpszClassName,	// and window title
				WS_OVERLAPPEDWINDOW,		// window style
				CW_USEDEFAULT,				// horizontal position of window
				0,							// vertical position of window
				600,						// window width
				350,						// window height
				NULL,						// handle to parent or owner window
				NULL,						// menu handle or child identifier
				hInstance,					// handle to application instance
				this						// sent with WM_CREATE message in CREATESTRUCT
			);
		}
		HRESULT hr = hWnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			// display the main frame window
			ShowWindow(hWnd, SW_SHOWNORMAL);	// show the window frame and
			UpdateWindow(hWnd);				// update the client area
		}

		return hr;
	}

};	// end of class definition


/// <summary>
/// Main function of the windows application.
/// This function registers a Windows class and creates
/// a window which is an instance of that class, then
/// dispatches the <c>WM_xxx</c> messages sent to the window.
/// </summary>
int APIENTRY wWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	PWSTR		pszCmdLine,
	int			nCmdShow
)
{
	CWindow		myWindow;
	int			nAppResult = -1;	// just in case something fails at initialisation

	ULONG_PTR			gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	if (SUCCEEDED(myWindow.Create(hInstance)))	// register and create the window
	{
		MSG		msg;

		// Main message loop:
		while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			// returns when a WM_QUIT message appears
			TranslateMessage(&msg);
			DispatchMessage(&msg);	// calls the static WindowProc function
		}
		nAppResult = msg.wParam;
	}

	GdiplusShutdown(gdiplusToken);

	return nAppResult;
}
