#include <windows.h>

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
char szCladdName[]="TextEntry";
char textSaved[20];
HWND TextBox;


HWND textfield,button;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_CREATE:
		TextBox = CreateWindow("EDIT",
								"",
								WS_BORDER | WS_CHILD | WS_VISIBLE,
								10,10,400,20,
								hwnd, NULL ,NULL ,NULL);

		CreateWindow("BUTTON",
					"GO",
					WS_VISIBLE | WS_CHILD | WS_BORDER,
					420,10,70,20,
					hwnd, (HMENU) 1, NULL,NULL);

		/*textfield = CreateWindow("STATIC",
								"Please input two number",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								20,20,300,25,
								hwnd, NULL, NULL, NULL);
		button = CreateWindow ("BUTTON",
								"Close",
								WS_VISIBLE | WS_CHILD | WS_BORDER,
								20,50,100,20,
								hwnd, (HMENU) 1, NULL, NULL);*/


		break;


		case WM_COMMAND:

			switch (LOWORD(wParam)){

				case 1:

					int gwtstat=0;
					//char *t = &textSaved[0];
					gwtstat = GetWindowText(TextBox, &textSaved[0], 20);
					if(gwtstat == 0){
						//promt to enter text again
					}

					::MessageBox(hwnd, textSaved, textSaved, MB_OK);
				/*case 1:
					PostQuitMessage(0);
				break;*/
				break;
			}

			break;
			
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
	
