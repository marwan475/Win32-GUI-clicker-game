#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <resources.h>
#include <string.h>

const char WindowClassName[] = "Window"; //name of our window class

HWND hWindow, hbutton, hbutton1, hbutton2, hbutton3, htxt, htxt1, htxt2, htxt3, htxt4, htxt5;
HWND hbutton4;

HANDLE thread;

unsigned long long bits; // amount of data bits
char display[50];
double  money; // player money
double price_per_bit = 0.01; // bit selling price
int pc_level = 1;
int target_level = 1;
unsigned long long pc_price = 1;
unsigned long long target_price = 100;

// pasive income
int adwear = 0;
int spywear = 0;
int virus = 0;
int trojan = 0;
int ransomwear = 0;
int rootkit = 0;
int botnet = 0;

DWORD WINAPI tfun(void* data) 
{
  while(1){
    sprintf(display,"Money: $%.2f",money);
    SetWindowText(htxt2,TEXT(display));
    sprintf(display,"%d bits",bits);
    SetWindowText(htxt,TEXT(display));
    Sleep(1000);
    
  }	
  return 0;
}

// windows main functionality
LRESULT CALLBACK WindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
    switch(msg){
      case WM_MENUSELECT:
  	      {
	      if(LOWORD(wParam) == 9001)
	        fprintf(stdout,"menuoption selected\n");
	      break;
	      }	      
      case WM_COMMAND:
	      {
	      if(LOWORD(wParam) == 150){ // check button id	      
	        bits = bits +1*pc_level;
	        sprintf(display,"%d bits",bits);
	        SetWindowText(htxt,TEXT(display));
	      }
	      if(LOWORD(wParam) == 9001)
	        fprintf(stdout,"menuopt clicked\n");
	      if(LOWORD(wParam) == 151){
	        money = money + bits*price_per_bit*target_level;
		bits = 0;
                sprintf(display,"Money: $%.2f",money);
		SetWindowText(htxt2,TEXT(display));
	        sprintf(display,"%d bits",bits);
	        SetWindowText(htxt,TEXT(display));
	      }
	      if(LOWORD(wParam) == 152){
	        if (money >= pc_price){
		  money = money - pc_price;
		  pc_price = pc_price*2;
		  pc_level++;
		  sprintf(display,"PC level: %d | $%d",pc_level,pc_price);
	          SetWindowText(htxt3,TEXT(display));
		  sprintf(display,"Money: $%.3f",money);
		  SetWindowText(htxt2,TEXT(display));
	          sprintf(display,"%d bits",bits);
	          SetWindowText(htxt,TEXT(display));
		}else{
		  MessageBox(NULL, "Not enough money", "Upgrade PC", MB_OK);
		}
	      }
	      if(LOWORD(wParam) == 153){
	        if (bits >= target_price){
		  bits = bits - target_price;
		  target_price = target_price*2;
		  target_level++;
		  sprintf(display,"Target level: %d | %d bits",target_level,target_price);
	          SetWindowText(htxt4,TEXT(display));
		  sprintf(display,"Money: $%.3f",money);
		  SetWindowText(htxt2,TEXT(display));
	          sprintf(display,"%d bits",bits);
	          SetWindowText(htxt,TEXT(display));
		}else{
		  MessageBox(NULL, "Not enough bits", "Upgrade Target", MB_OK);
		}
	      }
	      break;
	      }	      
      case WM_LBUTTONDOWN:
  	      fprintf(stdout,"left mouse clicked on window\n");
	      break;	      
      case WM_CLOSE:
	      DestroyWindow(hwnd);
	      break;
      case WM_DESTROY:
	      PostQuitMessage(0);
	      break;
      default:
	      return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, int nCmdShow)
{
    //creating a window
    WNDCLASSEX wc; //window class var
    int rtrc; // return value for regitering class

    MSG msg;
    
    //filling out window class details
    wc.cbSize = sizeof(WNDCLASSEX); //size of our window class
    wc.style = 0;
    wc.lpfnWndProc = WindowProc; //pointer to window function for this window class
    wc.cbClsExtra = 0; // amount of extra data allocated for this class in memory
    wc.cbWndExtra = 0; // amount of extra data allocated for each window of this type
    wc.hInstance = hInstance; //handle to application instance
    wc.hIcon = LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON)); // window icon when alt tabing
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // cursor that will show when on window 
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // color of ou window
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU); // name of a menu resource to use with our window
    wc.lpszClassName = WindowClassName; //name of our class
    wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON),IMAGE_ICON,16,16,0); // icon of window
    
    //registering our window class
    rtrc = RegisterClassEx(&wc);

    if (!rtrc){
      fprintf(stderr,"Failed to register window class");
      return 0;
    }

    // Main game window
    hWindow = CreateWindowEx(
		    WS_EX_CLIENTEDGE, //window style
		    WindowClassName, // name of our window class
		    "Hacker Clicker", // title for our window
		    WS_OVERLAPPEDWINDOW, //more windows styling
		    CW_USEDEFAULT, // X cord of window
		    CW_USEDEFAULT, // Y cor dof window
		    1500, //width
		    1000, //height
		    NULL, // parent window handle
		    NULL, // menu handle
		    hInstance, // application instance handle, got from WinMain
		    NULL // pointer to send additional data to window
		    );

    if(hWindow == NULL){
       fprintf(stderr,"Failed to create window");
       return 0;	       
    }

    htxt1 = CreateWindow(
		   "STATIC",
		   "Hacker Clicker: Steal everyones data",
		   WS_VISIBLE | WS_CHILD | SS_LEFT,
		   10,10,300,50,
		   hWindow,
		   NULL,
		   hInstance,
		   NULL); 

    // create button
    hbutton = CreateWindow(
		    "BUTTON",
		    "Hack",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    10,
		    100,
		    50,
		    50,
		    hWindow,
		    (HMENU)150, // id of button
		    hInstance,
		    NULL);

    hbutton1 = CreateWindow(
		    "BUTTON",
		    "Sell",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    100,
		    100,
		    50,
		    50,
		    hWindow,
		    (HMENU)151, // id of button
		    hInstance,
		    NULL);

    hbutton2 = CreateWindow(
		    "BUTTON",
		    "UPGRADE PC",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    180,
		    100,
		    120,
		    50,
		    hWindow,
		    (HMENU)152, // id of button
		    hInstance,
		    NULL);

    hbutton3 = CreateWindow(
		    "BUTTON",
		    "UPGRADE TARGET",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    320,
		    100,
		    130,
		    50,
		    hWindow,
		    (HMENU)153, // id of button
		    hInstance,
		    NULL);

    hbutton4 = CreateWindow(
		    "BUTTON",
		    "Adwear | 1000bits",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    10,
		    400,
		    175,
		    125,
		    hWindow,
		    (HMENU)154, // id of button
		    hInstance,
		    NULL);
		   
    htxt = CreateWindow(
		   "STATIC",
		   "0 bits",
		   WS_VISIBLE | WS_CHILD | SS_LEFT,
		   10,170,150,40,
		   hWindow,
		   NULL,
		   hInstance,
		   NULL);

   htxt2 = CreateWindow(
		   "STATIC",
		   "Money: $0",
		   WS_VISIBLE | WS_CHILD | SS_LEFT,
		   10,210,150,40,
		   hWindow,
		   NULL,
		   hInstance,
		   NULL);  

   htxt3 = CreateWindow(
		   "STATIC",
		   "PC level: 1 | $1 to upgrade",
		   WS_VISIBLE | WS_CHILD | SS_LEFT,
		   10,270,300,40,
		   hWindow,
		   NULL,
		   hInstance,
		   NULL);

   htxt4 = CreateWindow(
		   "STATIC",
		   "Target level: 1 | 100 bits to upgrade",
		   WS_VISIBLE | WS_CHILD | SS_LEFT,
		   10,320,300,40,
		   hWindow,
		   NULL,
		   hInstance,
		   NULL);

   htxt5 = CreateWindow(
		   "STATIC",
		   "Adwear: 0    Spywear: 0    Virus: 0    Trojan: 0    Ransomwear: 0    Rootkit: 0    Botnet: 0",
		   WS_VISIBLE | WS_CHILD | SS_LEFT,
		   400,10,1000,40,
		   hWindow,
		   NULL,
		   hInstance,
		   NULL);  

    //Showing window on screen
    ShowWindow(hWindow,nCmdShow);
    //Updating the window
    UpdateWindow(hWindow);

    // thread for passive income
    thread = CreateThread(NULL, 0, tfun, NULL, 0, NULL);

    //Main Loop of window
    while(GetMessage(&msg,NULL,0,0) > 0){ // gets a msg from the windows Que,
					  // msgs are added to que every time a user does somehing on your window
      TranslateMessage(&msg);
      DispatchMessage(&msg); //send msg to window
    
    }

    return msg.wParam;
}
