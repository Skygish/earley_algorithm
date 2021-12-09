#include "Algo.h"

using std::string;
using std::vector;
using std::pair;

bool Algo::isNotTerminal(char c) {
	return c >= 'A' && c <= 'Z';
}

string Algo::deleteNotLetters(const string& s){
	string new_s = "";
	for (int i = 0; i < s.size(); ++i) {
		if (isalpha(s[i]))
			new_s.push_back(s[i]);
	}
	return new_s;
}

Algo Algo::fit(const vector<string>& g) {
	for (auto s : g) {
		s = deleteNotLetters(s);
		char notTerminal = s[0];
		rules.push_back(Rule({notTerminal, string(s.begin() + 1, s.end())}));
		rulesBySymb[notTerminal].push_back(rules.back());
	}
	return *this;
}

bool Algo::predict(const string& s) {
	return earley(s);
}

void Algo::Scan(size_t j, char wj) {
	for (auto [rule, parent, pos] : D[j]) {
		if (rule[pos] == wj) {
			D[j + 1].insert({rule, parent, pos + 1});
		}
	}
}

void Algo::Predict(size_t j) {
	for (auto [rule, parent, pos] : D[j]) {
		if (isNotTerminal(rule[pos])) {
			for (auto newRules : rulesBySymb[rule[pos]]) {
				D[j].insert({newRules, j, 0});
			}
		}
	}
}

void Algo::Complete(size_t j) {
	for (auto [rule, parent, pos] : D[j]) {
		if (pos == rule.size()) {
			for (auto [ruleInParent, parentInParent, posInParent] : D[parent]) {
				if (posInParent < ruleInParent.size() && ruleInParent[posInParent] == rule.notTerminal)
					D[j].insert({ruleInParent, parentInParent, posInParent + 1});
			}
		}
	}
}

bool Algo::earley(const string& s) {
	D.resize(s.size() + 1);
	D[0].insert(std::make_tuple(Rule({0, "S"}), 0, 0));

	size_t old_sz = D[0].size();
	do {
		old_sz = D[0].size();
		Predict(0);
		Complete(0);
	} while (D[0].size() != old_sz);

	for (size_t i = 0; i < s.size(); ++i) {
		Scan(i, s[i]);

		do {
			old_sz = D[i + 1].size();
			Predict(i + 1);
			Complete(i + 1);
		} while (D[i + 1].size() != old_sz);
	}

	for (auto [rule, parent, pos] : D[s.size()]) {
		if (rule == Rule({0, "S"}) && parent == 0)
			return true;
	}
	return false;
}
