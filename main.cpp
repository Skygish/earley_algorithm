#include "Algo.h"
#include <vector>
#include <string>

using namespace std;

int main() {
	vector<string> g;
	int n;
	cout << "Введите кол-во правил в грамматике" << endl;
	cin >> n;
	cout << "Введите правила грамматики (Вместо S->eps пишите S->1)" << endl;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		g.push_back(s);
	}
	Algo algo;
	algo = algo.fit(g);
	cout << "Введите слово, которое вы хотите проверить на выводимость" << endl;
	string s;
	cin >> s;
	bool inLanguage = algo.predict(s);
	if (inLanguage)
		cout << "Выводится =)" << endl;
	else
		cout << "Не выводится =(" << endl;
}