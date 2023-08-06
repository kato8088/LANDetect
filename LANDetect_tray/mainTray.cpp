#include <iostream>
#include <Windows.h>
#include "resource.h"

using namespace std;

// colocar acoes de checagem do ping no void (em threads)
// depois implementar possibilidade de trocar o ip a ser pingado (por um arquivo de cfg, editado por um gui, se possivel)

void hideConsoleWindow() {
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void showConsoleWindow() {
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

int main() {
	//hideConsoleWindow();

	NOTIFYICONDATAA nid = {};
	AllocConsole();
	HWND h = FindWindowA("ConsoleWindowClass", NULL);

	nid.cbSize = sizeof(nid);
	nid.hWnd = h;
	nid.uFlags = NIF_ICON;

	string userip;
	cout << "insira o ip a ser testado: ";
	cin >> userip;
	string iptest = "ping ";
	iptest = iptest + userip + " -n 1";
	char* char_iptest = &iptest[0];
	int ping = (system(char_iptest));
	// result 0 if sucess | result 1 if fail //
	system("cls");
	if (ping == 0) {
		cout << "a lan esta ativada para o ip " << userip << endl;
		// (antigo funcionando com arquivo local) nid.hIcon = (HICON)LoadImageA(NULL, "lan_icon_on.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_SHARED);
		nid.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	}
	if (ping == 1) {
		cout << "a lan esta desativada levando em conta o ip " << userip << endl;
		// (antigo funcionando com arquivo local) nid.hIcon = (HICON)LoadImageA(NULL, "lan_icon_on.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_SHARED);
		nid.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
	}

	Shell_NotifyIconA(NIM_ADD, &nid);

	if (ping != 1 && ping != 0)
		cout << "resultado desconhecido...\n";

	system("pause");

	Shell_NotifyIconA(NIM_DELETE, &nid);

	// on click: deletar o icone e ai fechar a aplicacao (ver de clicar com o click direito)

	return 1;
}