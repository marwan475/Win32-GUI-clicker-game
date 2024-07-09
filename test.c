#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <resources.h>
#include <string.h>

const char WindowClassName[] = "Window"; //name of our window class

HWND hWindow, hbutton, hbutton1, hbutton2, hbutton3, htxt, htxt1, htxt2, htxt3, htxt4, htxt5;
HWND hbutton4, hbutton5, hbutton6, hbutton7, hbutton8, hbutton9, hbutton10,hbutton11;
HWND htxt6, htxt7, htxt8,htxt9;

HANDLE thread;

unsigned long long bits = 0; // amount of data bits
char display[50];
char display1[200];
char display2[50];
double  money; // player money
double price_per_bit = 0.01; // bit selling price
unsigned long long pc_level = 1;
unsigned long long target_level = 1;
unsigned long long pc_price = 1;
unsigned long long target_price = 100;

// pasive income
unsigned long long adwear = 0;
unsigned long long spywear = 0;
unsigned long long virus = 0;
unsigned long long trojan = 0;
unsigned long long ransomwear = 0;
unsigned long long rootkit = 0;
unsigned long long botnet = 0;

unsigned long long adwear_p = 1;
unsigned long long spywear_p = 10;
unsigned long long virus_p = 100;
unsigned long long trojan_p = 1000;
unsigned long long ransomwear_p = 10000;
unsigned long long rootkit_p = 100000;
unsigned long long botnet_p = 1000000;

unsigned long long adwear_c = 1000;
unsigned long long spywear_c = 15000;
unsigned long long virus_c = 150000;
unsigned long long trojan_c = 10000000;
unsigned long long ransomwear_c = 1;
unsigned long long rootkit_c = 1;
unsigned long long botnet_c = 1;

unsigned long long bps = 0;

DWORD WINAPI tfun(void* data) 
{
  while(1){

    bits = bits + adwear_p*adwear + spywear_p*spywear + virus_p*virus + trojan_p*trojan + ransomwear_p*ransomwear + rootkit_p*rootkit + botnet_p*botnet;

    sprintf(display,"Money: $%.2f",money);
    SetWindowText(htxt2,TEXT(display));
    sprintf(display,"%d bits | %d bps",bits,bps);
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
	        sprintf(display,"%d bits | %d bps",bits,bps);
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
	        if(money >= pc_price){
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
	        if(bits >= target_price){
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
	      if(LOWORD(wParam) == 154){
	        if(bits >= 500){
		  adwear++;
		  bits = bits - 500;
		  sprintf(display1,"Adwear: %d    Spywear: %d    Virus: %d    Trojan: %d    Ransomwear: %d    Rootkit: %d    Botnet: %d",adwear,spywear,virus,trojan,ransomwear,rootkit,botnet);
                  SetWindowText(htxt5,TEXT(display1));
		  bps = adwear_p*adwear + spywear_p*spywear + virus_p*virus + trojan_p*trojan + ransomwear_p*ransomwear + rootkit_p*rootkit + botnet_p*botnet;
		}else{
		  MessageBox(NULL, "Not enough bits", "Buy Adwear", MB_OK);
		}
	      }
	      if(LOWORD(wParam) == 155){
	        if( bits >= adwear_c){
		  bits = bits - adwear_c;	
		  adwear_p = adwear_p + 1;
		  adwear_c = adwear_c*2;	  
		  memset(display2,0,50);
		  sprintf(display2,"%d bps | %d  to upgrade",adwear_p,adwear_c);
                  SetWindowText(htxt6,TEXT(display2));
		  bps = adwear_p*adwear + spywear_p*spywear + virus_p*virus + trojan_p*trojan + ransomwear_p*ransomwear + rootkit_p*rootkit + botnet_p*botnet;
		}else{
		  MessageBox(NULL, "Not enough bits", "Upgrade Adwear", MB_OK);
		}
	      }	
	      if(LOWORD(wParam) == 156){
	        if(bits >= 7500){
		  spywear++;
		  bits = bits - 7500;
		  sprintf(display1,"Adwear: %d    Spywear: %d    Virus: %d    Trojan: %d    Ransomwear: %d    Rootkit: %d    Botnet: %d",adwear,spywear,virus,trojan,ransomwear,rootkit,botnet);
                  SetWindowText(htxt5,TEXT(display1));
		  bps = adwear_p*adwear + spywear_p*spywear + virus_p*virus + trojan_p*trojan + ransomwear_p*ransomwear + rootkit_p*rootkit + botnet_p*botnet;
		}else{
		  MessageBox(NULL, "Not enough bits", "Buy Spywear", MB_OK);
		}
	      }
              if(LOWORD(wParam) == 157){
	        if( bits >= spywear_c){
		  bits = bits - spywear_c;	
		  spywear_p = spywear_p + 10;
		  spywear_c = spywear_c*2;	  
		  memset(display2,0,50);
		  sprintf(display2,"%d bps | %d  to upgrade",spywear_p,spywear_c);
                  SetWindowText(htxt7,TEXT(display2));
		  bps = adwear_p*adwear + spywear_p*spywear + virus_p*virus + trojan_p*trojan + ransomwear_p*ransomwear + rootkit_p*rootkit + botnet_p*botnet;
		}else{
		  MessageBox(NULL, "Not enough bits", "Upgrade Spywear", MB_OK);
		}
	      }
              if(LOWORD(wParam) == 158){
	        if(bits >= 75000){
		  virus++;
		  bits = bits - 75000;
		  sprintf(display1,"Adwear: %d    Spywear: %d    Virus: %d    Trojan: %d    Ransomwear: %d    Rootkit: %d    Botnet: %d",adwear,spywear,virus,trojan,ransomwear,rootkit,botnet);
                  SetWindowText(htxt5,TEXT(display1));
		  bps = adwear_p*adwear + spywear_p*spywear + virus_p*virus + trojan_p*trojan + ransomwear_p*ransomwear + rootkit_p*rootkit + botnet_p*botnet;
		}else{
		  MessageBox(NULL, "Not enough bits", "Buy Virus", MB_OK);
		}
	      }
              if(LOWORD(wParam) == 159){
	        if( bits >= virus_c){
		  bits = bits - virus_c;	
		  virus_p = virus_p + 100;
		  virus_c = virus_c*2;	  
		  memset(display2,0,50);
		  sprintf(display2,"%d bps | %d  to upgrade",virus_p,virus_c);
                  SetWindowText(htxt8,TEXT(display2));
		  bps = adwear_p*adwear + spywear_p*spywear + virus_p*virus + trojan_p*trojan + ransomwear_p*ransomwear + rootkit_p*rootkit + botnet_p*botnet;
		}else{
		  MessageBox(NULL, "Not enough bits", "Upgrade Virus", MB_OK);
		}
	      }
              if(LOWORD(wParam) == 160){
	        if(bits >= 1000000){
		  trojan++;
		  bits = bits - 1000000;
		  sprintf(display1,"Adwear: %d    Spywear: %d    Virus: %d    Trojan: %d    Ransomwear: %d    Rootkit: %d    Botnet: %d",adwear,spywear,virus,trojan,ransomwear,rootkit,botnet);
                  SetWindowText(htxt5,TEXT(display1));
		  bps = adwear_p*adwear + spywear_p*spywear + virus_p*virus + trojan_p*trojan + ransomwear_p*ransomwear + rootkit_p*rootkit + botnet_p*botnet;
		}else{
		  MessageBox(NULL, "Not enough bits", "Buy Trojan", MB_OK);
		}
	      }
              if(LOWORD(wParam) == 161){
	        if( bits >= trojan_c){
		  bits = bits - trojan_c;	
		  trojan_p = trojan_p + 1000;
		  trojan_c = trojan_c*2;	  
		  memset(display2,0,50);
		  sprintf(display2,"%d bps | %d  to upgrade",trojan_p,trojan_c);
                  SetWindowText(htxt9,TEXT(display2));
		  bps = adwear_p*adwear + spywear_p*spywear + virus_p*virus + trojan_p*trojan + ransomwear_p*ransomwear + rootkit_p*rootkit + botnet_p*botnet;
		}else{
		  MessageBox(NULL, "Not enough bits", "Upgrade Trojan", MB_OK);
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
		    "Adwear | 500 bits",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    10,
		    400,
		    175,
		    125,
		    hWindow,
		    (HMENU)154, // id of button
		    hInstance,
		    NULL);

    hbutton5 = CreateWindow(
		    "BUTTON",
		    "Upgrade",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    10,
		    600,
		    175,
		    125,
		    hWindow,
		    (HMENU)155, // id of button
		    hInstance,
		    NULL);

    hbutton6 = CreateWindow(
		    "BUTTON",
		    "Spywear | 7500 bits",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    210,
		    400,
		    175,
		    125,
		    hWindow,
		    (HMENU)156, // id of button
		    hInstance,
		    NULL);

    hbutton7 = CreateWindow(
		    "BUTTON",
		    "Upgrade",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    210,
		    600,
		    175,
		    125,
		    hWindow,
		    (HMENU)157, // id of button
		    hInstance,
		    NULL);

    hbutton8 = CreateWindow(
		    "BUTTON",
		    "Spywear | 75000 bits",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    410,
		    400,
		    175,
		    125,
		    hWindow,
		    (HMENU)158, // id of button
		    hInstance,
		    NULL);

    hbutton9 = CreateWindow(
		    "BUTTON",
		    "Upgrade",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    410,
		    600,
		    175,
		    125,
		    hWindow,
		    (HMENU)159, // id of button
		    hInstance,
		    NULL);

    hbutton10 = CreateWindow(
		    "BUTTON",
		    "Trojan | 1000000 bits",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    610,
		    400,
		    175,
		    125,
		    hWindow,
		    (HMENU)160, // id of button
		    hInstance,
		    NULL);

    hbutton11 = CreateWindow(
		    "BUTTON",
		    "Upgrade",
		    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		    610,
		    600,
		    175,
		    125,
		    hWindow,
		    (HMENU)161, // id of button
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

   htxt6 = CreateWindow(
		   "STATIC",
		   "1 bps | 1000 to upgrade",
		   WS_VISIBLE | WS_CHILD | SS_LEFT,
		   10,550,175,40,
		   hWindow,
		   NULL,
		   hInstance,
		   NULL);

   htxt7 = CreateWindow(
		   "STATIC",
		   "10 bps | 15000 to upgrade",
		   WS_VISIBLE | WS_CHILD | SS_LEFT,
		   210,550,175,40,
		   hWindow,
		   NULL,
		   hInstance,
		   NULL);

    htxt8 = CreateWindow(
		   "STATIC",
		   "100 bps | 150000 to upgrade",
		   WS_VISIBLE | WS_CHILD | SS_LEFT,
		   410,550,175,40,
		   hWindow,
		   NULL,
		   hInstance,
		   NULL);

    htxt9 = CreateWindow(
		   "STATIC",
		   "1000 bps | 10000000 to upgrade",
		   WS_VISIBLE | WS_CHILD | SS_LEFT,
		   610,550,175,40,
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
