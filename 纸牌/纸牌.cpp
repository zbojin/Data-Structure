#include <windows.h>
#include <time.h>
#define FPS 10
HINSTANCE hInst;
HDC Image[54],Back;
HWND m_hwnd;
int w=86,pai[54],choose,uu;
int lie[8][100],lnow[8],lastl,cao[5],ml,mg;
int now;
bool can[54],show[54],impossible,must;
POINT pt[54],last,d;
void swap(int &a,int &b){
	int t=a;
	a=b;
	b=t;
}
int flower(int k){
	if(k==0||k==53)return 5;
	if(1<=k&&k<=13)return 1;
	if(14<=k&&k<=26)return 2;
	if(27<=k&&k<=39)return 3;
	if(40<=k&&k<=52)return 4;
}
int value(int k){
	if(k==0)return 17;
	if(k==53)return 16;
	k--;
	return 13-k%13;
}
bool small(int a,int b){
	int ka=value(a),kb=value(b);
	if(ka==17)return 0;
	if(kb==17)return 1;
	if(ka==16)return 0;
	if(kb==16)return 1;
	if(ka==kb)return flower(a)>flower(b);
	return value(a)<value(b);
}
void sort(int pai[],int beg,int end){
	int i,j,k,temp;
	for(i=beg;i<end;i++){
		for(j=i-1;j>=0;j--)if(!small(pai[j],pai[i]))break;
		if(j!=i-1){
			temp=pai[i];
			for(k=i-1;k>j;k--)
				pai[k+1]=pai[k];
			pai[k+1]=temp;
		}
	}
}
void random(int pai[],int beg,int end){
	int i,j,k,temp;
	for(i=beg;i<end;i++){
		for(j=i-1;j>=0;j--)if(rand()%2)break;
		if(j!=i-1){
			temp=pai[i];
			for(k=i-1;k>j;k--)
				pai[k+1]=pai[k];
			pai[k+1]=temp;
		}
	}
}
void init(){
	memset(can,0,sizeof(can));
	memset(show,0,sizeof(show));
	memset(pai,-1,sizeof(pai));
	memset(cao,0,sizeof(cao));
	memset(pt,0,sizeof(pt));
	last.x=0;last.y=0;
	d.x=0;d.y=0;
	srand((int)time(NULL));
	choose=-1;uu=-1;
	impossible=0;must=0;
	int xx=70,yy=150,g=0,gg=1;
	now=27;
	for(int i=0;i<28;i++){
		do{
			pai[i]=rand()%52+1;
		}while(can[pai[i]]);
		can[pai[i]]=1;
	}
	int j=1;
	for(int i=28;i<52;i++){
		while(can[j]&&j<53)j++;
		pai[i]=j;
		pt[pai[i]].x = 20;
		pt[pai[i]].y = 14;
		j++;
	}
	random(pai,28,52);
	for(int i=0;i<28;i++){
		pt[pai[i]].x=xx;
		pt[pai[i]].y=yy;
		lie[gg][g]=pai[i];
		g++;
		yy+=30;
		if(g==gg){
			g=0;
			gg++;
			xx+=100;
			yy=150;
			show[pai[i]]=1;
		}
	}
	for(int i=1;i<=7;i++)
		lnow[i]=i;
	lastl=-1;ml=-1;mg=-1;
}
int next(int now){
	do{
		++now;
	}while(can[pai[now]]&&now<52);
	return now;
}
int pre(int now){
	do{
		--now;
	}while(can[pai[now]]&&now>27);
	return now;
}
void DO(){
	HDC hdc = GetDC(m_hwnd);
	HDC memDC = CreateCompatibleDC(0);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc,1440,600);
	SelectObject(memDC,hBitmap);
	HBRUSH brush = CreateSolidBrush(RGB(0,160,0));
	RECT rect;
	GetClientRect(m_hwnd,&rect);
	FillRect(memDC,&rect,brush);
	HPEN pen = CreatePen(0,1,RGB(255,255,255));
	SelectObject(memDC,pen);
	SelectObject(memDC,brush);
	for(int i=1;i<=4;i++){
		int g=i+1;
		if(g==5)g=1;
		if(cao[g]==0)Rectangle(memDC,800+i*100,20,886+i*100,150);
		else{
			int p=cao[g],u;
			u=1+13*i+13-p;
			if(u>52)u-=52;
			BitBlt(memDC,800+i*100,20,86,130,Image[u],0,0,SRCCOPY);
		}
	}
	if(next(now)!=52)BitBlt(memDC,20,14,86,130,Back,0,0,SRCCOPY);
	else Rectangle(memDC,20,14,106,144);
	if(now!=27)BitBlt(memDC,120,14,86,130,Image[pai[now]],0,0,SRCCOPY);
	for(int i=1;i<=7;i++){
		int ll=lnow[i];
		for(int k=0;k<ll;k++){
			int j=lie[i][k];
			if(j==0||j==53)continue;
			if(show[j])BitBlt(memDC,pt[j].x,pt[j].y,86,130,Image[j],0,0,SRCCOPY);
			else BitBlt(memDC,pt[j].x,pt[j].y,86,130,Back,0,0,SRCCOPY);
		}
	}
	if(!must)BitBlt(memDC,pt[choose].x,pt[choose].y,86,130,Image[choose],0,0,SRCCOPY);
	else{
		int ll=lnow[ml];
		for(int k=mg;k<ll;k++){
			int j=lie[ml][k];
			BitBlt(memDC,pt[j].x,pt[j].y,86,130,Image[j],0,0,SRCCOPY);
		}
	}
	BitBlt(hdc,0,0,1440,600,memDC,0,0,SRCCOPY);
	DeleteDC(memDC);
	DeleteObject(hBitmap);
	ReleaseDC(m_hwnd,hdc);
}
DWORD WINAPI Paint(LPVOID lp){
	while(1){
		DO();
		if(cao[1]==13&&cao[2]==13&&cao[3]==13&&cao[4]==13){
			MessageBox(m_hwnd,"You win.","Game over",MB_OK);
			exit(0);
		}
		Sleep(1000/FPS);
	}
	return 0l;
}
//INT_PTR ShowProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
//	static HWND Button;
//	switch(Message){
//		case WM_INITDIALOG: {
//			ShowWindow(hwnd,SW_SHOW);
//			Button = CreateWindow("BUTTON","Button",WS_CHILD|WS_VISIBLE|WS_BORDER,10,10,300,300,hwnd,(HMENU)1,hInst,NULL);
//			return (INT_PTR)TRUE;
//		}
//		case WM_COMMAND: {
//			if(LOWORD(wParam) == 1){
//				EndDialog(hwnd,LOWORD(wParam));
//			}
//			break;
//		}
//		default:
//			return DefDlgProc(hwnd,Message,wParam,lParam);
//	}
//	return 0;
//}
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	switch(Message) {
		case WM_CREATE: {
//			HMENU hMenu = CreateMenu();
//			HMENU hMenu2 = CreateMenu();
//			AppendMenu(hMenu2,MF_STRING,1,"°ïÖú");
//			AppendMenu(hMenu,MF_POPUP,(UINT_PTR)(hMenu2),"&Help");
//			SetMenu(hwnd,hMenu);
			hdc = GetDC(hwnd);
			for(int i=0;i<54;i++){
				HBITMAP hBitmap = (HBITMAP)LoadImage(NULL,"Ö½ÅÆ.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
				Image[i] = CreateCompatibleDC(hdc);
				HBITMAP bit = CreateCompatibleBitmap(hdc,w,130);
				SelectObject(Image[i],bit);
				HDC memDC = CreateCompatibleDC(0);
				SelectObject(memDC,hBitmap);
				BitBlt(Image[i],0,0,w,130,memDC,(i%9)*(w+1)-1,(i/9)*130,SRCCOPY);
			}
			HBITMAP hBitmap = (HBITMAP)LoadImage(NULL,"±³Ãæ.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			Back = CreateCompatibleDC(hdc);
			HBITMAP bit = CreateCompatibleBitmap(hdc,w,130);
			SelectObject(Back,bit);
			HDC memDC = CreateCompatibleDC(0);
			SelectObject(memDC,hBitmap);
			StretchBlt(Back,0,0,w,130,memDC,80,54,106,150,SRCCOPY);
			ReleaseDC(hwnd,hdc);
			init();
			break;
		}
		case WM_KEYDOWN: {
			init();
			break;
		}
//		case WM_COMMAND: {
//			int wmId = LOWORD(wParam);
//			switch(wmId){
//				case 1: {
//					DLGTEMPLATE a;
//					a.style = DS_CONTEXTHELP;
//					a.dwExtendedStyle = 0;
//					a.cdit = 1;
//					a.x = 100;
//					a.y = 100;
//					a.cx = 400;
//					a.cy = 400;
//					CreateDialogIndirect(hInst,&a,hwnd,(DLGPROC)ShowProc);
//					break;
//				}
//			}
//			break;
//		}
		case WM_LBUTTONDBLCLK: {
			int x=LOWORD(lParam);
			int y=HIWORD(lParam);
			if(20<=x&&x<=106&&14<=y&&y<=144){
				SendMessage(hwnd,WM_LBUTTONDOWN,wParam,lParam);
			}else{
				if(120<=x&&x<=206&&14<=y&&y<=144){
					choose=pai[now];
					if(must){
						must=0;
						return 0;
					}
					int Flower=flower(choose),Value=value(choose);
					if(cao[Flower]+1==Value){
						cao[Flower]++;
						Flower--;
						if(Flower==0)Flower=5;
						pt[choose].x=Flower*100+800;
						pt[choose].y=14;
						can[pai[now]]=1;
						now=pre(now);
					}
				}else if(70<=x&&x<=756){
					int l=(x+30)/100,h;
					if(y<=150+(lnow[l]-1)*30)h=(y-150)/30;
					else if(y<=250+lnow[l]*30)h=lnow[l]-1;
					else return 0;
					int i=lie[l][h];
					if(show[i]==0)return 0;
					if(h!=lnow[l]-1)must=1;
					if(must){
						must=0;
						return 0;
					}
					int Flower=flower(i),Value=value(i);
					if(cao[Flower]+1==Value){
						cao[Flower]++;
						Flower--;
						if(Flower==0)Flower=5;
						lastl=(pt[i].x+30)/100;
						pt[i].x=Flower*100+800;
						pt[i].y=14;
						lie[lastl][lnow[lastl]-1]=0;
						lnow[lastl]--;
						show[lie[lastl][lnow[lastl]-1]]=1;
					}
				}
				ml=0;
				mg=0;
				last.x=-1;
				last.y=-1;
				lastl=0;
				must=0;
			}
			break;
		}
		case WM_LBUTTONDOWN: {
			int x=LOWORD(lParam);
			int y=HIWORD(lParam);
			choose=-1;
			must=0;
			if(20<=x&&x<=106&&14<=y&&y<=144){
				now=next(now);
				if(now==52){
					now=27;
					for(int i=28;i<52;i=next(i)){
						pt[pai[i]].x=20;
						show[pai[i]]=0;
					}
				}
				else{
					pt[pai[now]].x=120;
					show[pai[now]]=1;
				}
				return 0;
			}else if(120<=x&&x<=206&&14<=y&&y<=144){
				if(now!=27){
					choose = pai[now];
					int lx=120,ly=14;
					last.x=lx;last.y=ly;
					pt[pai[now]]=last;
					lastl=-1;
					can[pai[now]]=1;
					now=pre(now);
					d.x=x-lx;
					d.y=y-ly;
				}
				return 0;
			}
			if(y>=14&&y<=144){
				int f=0;
				if(900<=x&&x<=986){
					f=2;
				}else if(1000<=x&&x<=1086){
					f=3;
				}else if(1100<=x&&x<=1186){
					f=4;
				}else if(1200<=x&&x<=1286){
					f=1;
				}else return 0;
				int p=cao[f];
				choose=1+13*f-p;
				if(choose>52)choose-=52;
				if(f==0||choose==0||show[choose]==0)return 0;
				int lx,ly=14;
				if(f==1)f=5;
				lx=800+100*(f-1);
				last.x=lx;last.y=ly;
				pt[choose].x = lx;
				pt[choose].y = ly;
				lastl=-2;
				if(f==5)f=1;
				cao[f]--;
				d.x=x-lx;
				d.y=y-ly;
				return 0;
			}
			int l=(x+30)/100,h;
			if(y<=150+(lnow[l]-1)*30)h=(y-150)/30;
			else if(y<=250+lnow[l]*30)h=lnow[l]-1;
			else return 0;
			int i=lie[l][h];
			if(show[i]==0)return 0;
			choose=i;
			if(h!=lnow[l]-1)must=1;
			int lx=pt[choose].x,ly=pt[choose].y;
			last=pt[choose];
			lastl=(pt[i].x+30)/100;
			d.x=x-lx;
			d.y=y-ly;
			break;
		}
		case WM_MOUSEMOVE: {
			if(choose>0){
				int x=LOWORD(lParam);
				int y=HIWORD(lParam);
				if(lastl<0){
					pt[choose].x = x-d.x;
					pt[choose].y = y-d.y;
					must=0;
					return 0;
				}
				int l,h;
				l=(last.x+30)/100;
				if(last.y<=150+(lnow[l]-1)*30)h=(last.y-150)/30;
				else if(last.y<=250+lnow[l]*30)h=lnow[l]-1;
				if(h==lnow[l]-1){
					pt[choose].x = x-d.x;
					pt[choose].y = y-d.y;
					must=0;
				}else{
					must=1;
					int ll=lnow[l];
					for(int j=h;j<ll;j++){
						pt[lie[l][j]].x = x-d.x;
						pt[lie[l][j]].y = y-d.y+30*(j-h);
					}
					ml=l;
					mg=h;
				}
			}
			break;
		}
		case WM_LBUTTONUP: {
			int x=LOWORD(lParam);
			int y=HIWORD(lParam);
			if(choose==-1)return 0;
			int l=(x+30)/100,c=choose;
			choose=-1;
			int f=0;
			if((150<=y&&x<70||x>776)||(14<=y&&y<=144&&x<900)){
				impossible=1;
			}
			if(!impossible)
			if(14<=y&&y<=144){
				if(must){
					must=0;
					ml=0;
					mg=0;
					last.x=-1;
					last.y=-1;
					lastl=0;
					return 0;
				}
				if(900<=x&&x<=986){
					f=2;
				}else if(1000<=x&&x<=1086){
					f=3;
				}else if(1100<=x&&x<=1186){
					f=4;
				}else if(1200<=x&&x<=1286){
					f=1;
				}else{
					pt[c].x = last.x;
					pt[c].y = last.y;
					if(lastl==-1){
						now=next(now);
						can[pai[now]]=0;
					}
					last={0,0};
					lastl=0;
					return 0;
				}
				if(flower(c)==f&&value(c)==cao[f]+1){
					cao[f]++;
					pt[c].y = 20;
					if(900<=x&&x<=986){
						pt[c].x = 900;
					}else if(1000<=x&&x<=1086){
						pt[c].x = 1000;
					}else if(1100<=x&&x<=1186){
						pt[c].x = 1100;
					}else if(1200<=x&&x<=1286){
						pt[c].x = 1200;
					}
					if(lastl==-1){
						can[pai[next(now)]]=1;
						impossible=0;
						uu=0;
						last.x=-1;
						last.y=-1;
						return 0;
					}else if(lastl==-2){
						return 0;
					}
					lie[lastl][lnow[lastl]-1]=0;
					lnow[lastl]--;
					show[lie[lastl][lnow[lastl]-1]]=1;
					impossible=0;
					uu=0;
					last.x=-1;
					last.y=-1;
					return 0;
				}
			}
			impossible=1;
			if(value(c)==13&&lnow[l]==0)impossible=0;
			if(impossible){
				int p=lie[l][lnow[l]-1];
				int fp=flower(p),fc=flower(c);
				if(value(p)==1+value(c)&&((fp&1)!=(fc&1))){
					impossible=0;
				}
			}
			if(impossible){
				if(lastl==-1){
					pt[c].x = last.x;
					pt[c].y = last.y;
					can[c]=0;
					show[c]=1;
					now=next(now);
					last={0,0};
					lastl=0;
					return 0;
				}else if(lastl==-2){
					cao[flower(c)]++;
					pt[c]=last;
					lastl=0;
					return 0;
				}
				pt[c] = last;
				int h;
				l=(last.x+30)/100;
				if(last.y<=150+(lnow[l]-1)*30)h=(last.y-150)/30;
				else if(last.y<=250+lnow[l]*30)h=lnow[lastl]-1;
				int ll=lnow[l];
				for(int j=h;j<ll;j++){
					pt[lie[l][j]].x = last.x;
					pt[lie[l][j]].y = last.y+30*(j-h);
				}
			}else{
				int h;
				if(y<=150+(lnow[l]-1)*30)h=(y-150)/30;
				else if(y<=250+lnow[l]*30)h=lnow[l]-1;
				if(lastl==-1){
					lie[l][lnow[l]]=c;
					pt[c].x = l*100-30;
					pt[c].y = 150+lnow[l]*30;
					lnow[l]++;
					can[c]=1;
					show[c]=1;
					impossible=0;
					uu=0;
					ml=0;
					mg=0;
					last.x=-1;
					last.y=-1;
					lastl=0;
					must=0;
					return 0;
				}
				pt[c].x = l*100-30;
				pt[c].y = 150+lnow[l]*30;
				if(lastl==-2){
					lie[l][lnow[l]]=c;
					lnow[l]++;
					ml=0;
					mg=0;
					last.x=-1;
					last.y=-1;
					lastl=0;
					must=0;
					return 0;
				}
				if(must){
					ml=l;
					if(last.y<=150+(lnow[lastl]-1)*30)mg=(last.y-150)/30;
					else if(last.y<=250+lnow[lastl]*30)mg=lnow[lastl]-1;
					int dd=lnow[lastl]-mg;
					for(int k=0;k<dd;k++){
						c=lie[lastl][mg+k];
						lie[l][lnow[l]]=c;
						lie[lastl][mg+k]=0;
						pt[c].x = l*100-30;
						pt[c].y = 150+lnow[l]*30;
						lnow[l]++;
					}
					lnow[lastl]-=dd;
					if(lnow[lastl]>0)show[lie[lastl][lnow[lastl]-1]]=1;
				}else{
					lie[l][lnow[l]]=c;
					lie[lastl][lnow[lastl]-1]=0;
					lnow[lastl]--;
					lnow[l]++;
				}
				show[lie[lastl][lnow[lastl]-1]]=1;
			}
			impossible=0;
			uu=0;
			ml=0;
			mg=0;
			last.x=-1;
			last.y=-1;
			lastl=0;
			must=0;
			break;
		}
		/* Upon destruction, tell the main thread to stop */
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
	hInst = hInstance;
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */
	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.style		 = CS_DBLCLKS;	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(0,160,0));
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		1460, /* width */
		640, /* height */
		NULL,NULL,hInstance,NULL);
	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	m_hwnd = hwnd;
	HANDLE handle = CreateThread(NULL,0,Paint,NULL,0,NULL);
	CloseHandle(handle);
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
