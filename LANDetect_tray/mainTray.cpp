#include <iostream>
#include <Windows.h>
#include "resource.h"
#include <thread>


using namespace std;

// DONE! colocar acoes de checagem do ping no void (em threads)
// depois implementar possibilidade de trocar o ip a ser pingado (por um arquivo de cfg, editado por um gui, se possivel)

void hideConsoleWindow() {
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void showConsoleWindow() {
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

string userip;
string iptest;
char* char_iptest;
int ping;
bool running = true;

/*
int pingThread() {
	ping = 0;
	ping = (system(char_iptest));
	cout << "AAAAAAAAAAAAAAAAAA";
	return 2;
}
*/

#define WM_TRAYICON (WM_USER + 1)
#define TIMER_ID 1
#define TIMER_INTERVAL 10000  // Intervalo em milissegundos (10 segundo no exemplo)

NOTIFYICONDATAA nid = {};
HWND hwnd;

int main() {

	// hideConsoleWindow();

	// NOTIFYICONDATAA nid = {}; (declarado globalmente)
	AllocConsole();
	HWND h = FindWindowA("ConsoleWindowClass", NULL);
	nid.cbSize = sizeof(nid);
	nid.hWnd = h;
	nid.uID = 1;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_TRAYICON;

	//thread pingLoop(pingThread);

	// temporario enquanto nao tem o sistema de leitura de registro!
	userip = "192.168.15.1";
//	userip = "0.0.0.0";
	iptest = "ping ";
	iptest = iptest + userip + " -n 1";
	char_iptest = &iptest[0];
	// temp end

	string trayTip1 = "LANDetect - LAN Ativada para o IP " + userip + "!";
	string trayTip0 = "LANDetect - LAN Desativada para o IP " + userip + "!";

	// while (running = true) {
	 while(true) {
		Shell_NotifyIconA(NIM_ADD, &nid);

	//	pingLoop.join();

		ping = 0;
		ping = (system(char_iptest));

		if (ping == 0) {
			// lan ativada
			cout << "a lan esta ativada para o ip " << userip << endl;
			nid.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
			lstrcpyA(nid.szTip, trayTip1.c_str());
			Shell_NotifyIconA(NIM_MODIFY, &nid);
		}
		if (ping == 1) {
			// lan desativada
			nid.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
			lstrcpyA(nid.szTip, trayTip0.c_str());
			Shell_NotifyIconA(NIM_MODIFY, &nid);
		}
	// nim modify funcionando 100% :DDDD
	// sleep em ms!
	//	Sleep(900000);
	// debug abaixo!
	
		Sleep(5000);
	 }
	return 0;
}