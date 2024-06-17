#pragma once
#include <string>
#include <vector>
#include "conditioners.h"

class relation {
public:
	relation();
	virtual void rel() = 0;
	virtual ~relation();
};

class function : virtual public relation {
	std::string formula;
public:
	function(std::string formula);

	std::string getFormula() const {
		return formula;
	}

	void rel() override;
	void shortenFunction(const function& f);
	void convertIntoRPN(char s[], size_t l);
	std::vector<std::string> inheritRPN(char s[], size_t l);

	virtual ~function();
};