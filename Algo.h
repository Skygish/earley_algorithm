#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <set>
#include <tuple>
#include <map>

class Algo {
private:
	struct Rule {
		char notTerminal;
		std::string rule;
		Rule(const std::pair<char, std::string>& rule) : notTerminal(rule.first), rule(rule.second) {}
		bool operator == (const Rule& other) const {
			return notTerminal == other.notTerminal && rule == other.rule;
		}
		bool operator < (const Rule& other) const {
			return notTerminal != other.notTerminal ? notTerminal < other.notTerminal : rule < other.rule;
		}
		const char& operator [] (size_t i) const {
			return rule[i];
		}
		size_t size() const {
			return rule.size();
		}
		Rule() {}
	};
	std::vector<Rule> rules;
	std::vector<std::set<std::tuple<Rule, int, int>>> D;
	std::map<char, std::vector<Rule>> rulesBySymb;
	static bool isNotTerminal(char c);
	void Scan(size_t j, char wj);
	void Predict(size_t j);
	void Complete(size_t j);
	bool earley(const std::string& s);
	static std::string deleteNotLetters(const std::string& s);
public:
	Algo() {}
	Algo fit(const std::vector<std::string>& g);
	bool predict(const std::string& s);
};
