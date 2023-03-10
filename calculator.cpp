
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
char szCladdName[]="TextEntry";
char textSaved1[20];
char textSaved2[20];
HWND TextBox1;
HWND TextBox2;
//HWND TextBoxAns;


HWND textfield,button;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
       
        /* Upon destruction, tell the main thread to stop */
        case WM_CREATE:
       
        textfield = CreateWindow("STATIC",
                                "    Please input two number",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                20,15,200,25,
                                hwnd, NULL, NULL, NULL);


        TextBox1 = CreateWindow("EDIT",
                                "",
                                WS_BORDER | WS_CHILD | WS_VISIBLE,
                                40,50,150,20,
                                hwnd, NULL ,NULL ,NULL);
        TextBox2 = CreateWindow("EDIT",
                                "",
                                WS_BORDER | WS_CHILD | WS_VISIBLE,
                                40,80,150,20,
                                hwnd, NULL ,NULL ,NULL);


        CreateWindow("BUTTON",
                    "+",
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    40,110,30,30,
                    hwnd, (HMENU) 1, NULL,NULL);
        CreateWindow("BUTTON",
                    "-",
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    80,110,30,30,
                    hwnd, (HMENU) 2, NULL,NULL);
        CreateWindow("BUTTON",
                    "*",
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    120,110,30,30,
                    hwnd, (HMENU) 3, NULL,NULL);
        CreateWindow("BUTTON",
                    "/",
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    160,110,30,30,
                    hwnd, (HMENU) 4, NULL,NULL);
        break;


        case WM_COMMAND:
             if(LOWORD(wParam)!=0){
                int num1=0;
                int num2=0;
                int sum;
                float rs;

                num1=GetWindowText(TextBox1,&textSaved1[0],20);
                num2=GetWindowText(TextBox2,&textSaved2[0],20);
            }

            switch (LOWORD(wParam)){
                 if(LOWORD(wParam)!=0){
                int num1=0;
                int num2=0;
                int sum;
                float rs;

                num1=GetWindowText(TextBox1,&textSaved1[0],20);
                num2=GetWindowText(TextBox2,&textSaved2[0],20);
            }
                {
                case 1:
                    float rs = atof(textSaved1)+atof(textSaved2);
                    char t[100];
                    sprintf(t,"%f",rs);
                    ::MessageBox(hwnd,t,"Result",MB_OK);
                break;
                }
                {
                case 2:
                    float rs = atof(textSaved1)-atof(textSaved2);
                    char t[100];
                    sprintf(t,"%f",rs);
                    ::MessageBox(hwnd,t,"Result",MB_OK);
                break;
                }
                {
                case 3:
                    float rs = atof(textSaved1)*atof(textSaved2);
                    char t[100];
                    sprintf(t,"%f",rs);
                    ::MessageBox(hwnd,t,"Result",MB_OK);
                break;
                }
                {
                case 4:
                    float rs = atof(textSaved1)/atof(textSaved2);
                    char t[100];
                    sprintf(t,"%f",rs);
                    ::MessageBox(hwnd,t,"Result",MB_OK);
                break;
                }
                
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
    wc.cbSize    = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc; /* This is where we will send messages to */
    wc.hInstance     = hInstance;
    wc.hCursor   = LoadCursor(NULL, IDC_ARROW);
   
    /* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+25);
    wc.lpszClassName = "WindowClass";
    wc.hIcon     = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
    wc.hIconSm   = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, /* x */
        CW_USEDEFAULT, /* y */
        250, /* width */
        200, /* height */
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
   

