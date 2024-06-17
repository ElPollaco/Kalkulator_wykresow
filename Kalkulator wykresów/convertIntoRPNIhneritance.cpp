#include <iostream>
#include "function.h"
#include "conditioners.h"
#include "dataVerifiers.h"
#include "converters.h"

void handleSpecialFunction(const std::string& token, std::vector<char>& operators, std::vector<std::string>& returnStack, char array[], int& i, size_t l) {
	std::vector<std::string> arguments; // tablica argumentów funkcji
	int argCount = 0; // iloœæ zliczonych argumentów

	// Zlicza wszystkie napotkane argumenty funkcji specjalnej (maskymalnie mo¿e byæ ich 2)
	for (int j = i + 1; j < l; j++) {
		if (array[j] == ',') {
			argCount++;
		}
		else if (array[j] == ')' || array[j] == ']') {
			argCount++;
			break;
		}
	}

	// Przetwarza ka¿dy argument jaki napotka na drodze
	while (argCount > 0) {
		std::string arg;
		while (i + 1 < l && array[++i] != ',' && array[i] != ')' && array[i] != ']' && array[i] != '(' && array[i] != '[') {
			arg += array[i];
		}
		if (!arg.empty()) {
			char* argArray = convertStringArray(arg);
			size_t sizeArgArray = arg.length();

			std::vector<std::string> convertedArg = inheritRPN(argArray, sizeArgArray); // Konwersja na ONP argumentu

			// Dodanie skonwertowanego argumentu do stosu zwrotnego ONP
			for (const auto& a : convertedArg) {
				arguments.push_back(a);
			}
			argCount--;
		}
	}

	// Zwraca wszystkie argumenty do tablicy zwrotnej ONP
	for (const auto& arg : arguments) {
		returnStack.push_back(arg);
	}
	returnStack.push_back(token);
}
