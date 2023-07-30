#include <iostream>
#include <Windows.h>

using namespace std;

// colocar acoes de checagem do ping no void
// ex: void xxxxx() {xxxxx}
// se for fazer a verificacao do windscribe em si, fazer um branch especificamente pro windscribe e implementar a funcionalidade
// depois implementar possibilidade de trocar o ip a ser pingado (por um arquivo de cfg, editado por um gui, se possivel)

void hideConsoleWindow() {
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void showConsoleWindow() {
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

int main() {
	//hideConsoleWindow();
	string userip;
	cout << "insira o ip a ser testado: ";
	cin >> userip;
	string iptest = "ping ";
	iptest = iptest + userip + " -n 1";
	char* char_iptest = &iptest[0];
	int ping = (system(char_iptest));
	// result 0 if sucess | result 1 if fail //
	system("cls");
	if (ping == 0)
		cout << "a lan esta ativada para o ip " << userip << endl;
	if (ping == 1)
		cout << "a lan esta desativada levando em conta o ip "<< userip << endl;
	if (ping != 1 && ping != 0)
		cout << "resultado desconhecido...\n";
	system("pause");
	
	return 1;
}