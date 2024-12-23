#include <fstream>    
#include <iostream>   
#include <string>    
#include <vector>     
#include <cmath>      


// Funkcja analizuje każdą linię z pliku, oblicza dopasowania między liczbami wygrywającymi 
// a liczbami wybranymi przez gracza, a następnie dodaje wynik w formie 2^(liczba_dopasowań - 1)
// do końcowego rozwiązania.
void firstProblem(std::vector<std::string>& lines) {
    int solution = 0; 

    // Rozdzielacze służące do podziału linii na części
    std::string startDelimiter = ": ";   
    std::string cardDelimiter = " | ";   
    std::string numbersDelimiter = " ";  

    // Przechodzimy przez każdą linię wejściową
    for (int i = 0; i < lines.size(); i++) {
        std::string line = lines[i];  // Pobieramy aktualną linię

        // Zamiana podwójnych spacji na "0" (przydatne przy formatowaniu danych wejściowych)
        for (int k = 0; k < line.length() - 1; k++) {
            if (line[k] == ' ' && line[k + 1] == ' ') {
                line.replace(k + 1, 1, "0");
            }
        }

        // Usuwamy prefiks "Card X:" z linii, aby pozostały tylko dane liczbowe
        line.erase(0, line.find(startDelimiter) + startDelimiter.length());

        // Podział linii na część z liczbami wygrywającymi i część z liczbami gracza
        std::string winningNumbers = line.substr(0, line.find(cardDelimiter));
        line.erase(0, line.find(cardDelimiter) + cardDelimiter.length());
        std::string cardNumbers = line;

        std::vector<std::string> winningNumbersVector;  // Wektor na liczby wygrywające
        std::vector<std::string> cardNumbersVector;     // Wektor na liczby gracza
        size_t pos = 0;

        // Rozdzielenie liczb wygrywających na pojedyncze elementy
        while ((pos = winningNumbers.find(numbersDelimiter)) != std::string::npos) {
            winningNumbersVector.push_back(winningNumbers.substr(0, pos));
            winningNumbers.erase(0, pos + numbersDelimiter.length());
        }

        // Rozdzielenie liczb gracza na pojedyncze elementy
        while ((pos = cardNumbers.find(numbersDelimiter)) != std::string::npos) {
            cardNumbersVector.push_back(cardNumbers.substr(0, pos));
            cardNumbers.erase(0, pos + numbersDelimiter.length());
        }

        // Dodanie ostatniej liczby (poza pętlą)
        winningNumbersVector.push_back(winningNumbers);
        cardNumbersVector.push_back(cardNumbers);

        int matches = 0;  // Zmienna zliczająca liczbę dopasowań

        // Porównanie wszystkich liczb wygrywających z liczbami gracza
        for (int j = 0; j < winningNumbersVector.size(); j++) {
            for (int k = 0; k < cardNumbersVector.size(); k++) {
                if (winningNumbersVector[j] == cardNumbersVector[k]) {
                    matches++;  // Zliczanie liczby dopasowań
                }
            }
        }

       
        if (matches >= 1) {
            solution += std::pow(2, matches - 1);
        }
    }

    // Wypisanie wyniku końcowego dla pierwszego problemu
    std::cout <<"Pierwszy problem:" << solution << std::endl;
}



// Funkcja analizuje dane i oblicza powielenia kart w oparciu o liczbę dopasowań.
// Liczba kopii kart rośnie proporcjonalnie do liczby dopasowań.
void secondProblem(std::vector<std::string>& lines) {
    int solution = 0;  

    // Podstawowe delimitery
    std::string startDelimiter = ": ";
    std::string cardDelimiter = " | ";
    std::string numbersDelimiter = " ";

    // Wektor, który przechowuje liczbę kopii każdej karty (domyślnie 1 kopia na kartę)
    std::vector<int> cards(lines.size(), 1);

    // Przechodzimy przez każdą linię wejściową
    for (int i = 0; i < lines.size(); i++) {
        std::string line = lines[i];

        // Zamiana podwójnych spacji na "0"
        for (int k = 0; k < line.length() - 1; k++) {
            if (line[k] == ' ' && line[k + 1] == ' ') {
                line.replace(k + 1, 1, "0");
            }
        }

        
        line.erase(0, line.find(startDelimiter) + startDelimiter.length());

        // Podział linii na liczby wygrywające i liczby gracza
        std::string winningNumbers = line.substr(0, line.find(cardDelimiter));
        line.erase(0, line.find(cardDelimiter) + cardDelimiter.length());
        std::string cardNumbers = line;

        std::vector<std::string> winningNumbersVector;
        std::vector<std::string> cardNumbersVector;
        size_t pos = 0;

        // Rozdzielenie liczb
        while ((pos = winningNumbers.find(numbersDelimiter)) != std::string::npos) {
            winningNumbersVector.push_back(winningNumbers.substr(0, pos));
            winningNumbers.erase(0, pos + numbersDelimiter.length());
        }

        while ((pos = cardNumbers.find(numbersDelimiter)) != std::string::npos) {
            cardNumbersVector.push_back(cardNumbers.substr(0, pos));
            cardNumbers.erase(0, pos + numbersDelimiter.length());
        }

        winningNumbersVector.push_back(winningNumbers);
        cardNumbersVector.push_back(cardNumbers);

        int matches = 0;  // Zliczanie dopasowań

        // Porównanie liczb wygrywających z liczbami karty gracza
        for (int j = 0; j < winningNumbersVector.size(); j++) {
            for (int k = 0; k < cardNumbersVector.size(); k++) {
                if (winningNumbersVector[j] == cardNumbersVector[k]) {
                    matches++;
                }
            }
        }

        // Powielenie kart w kolejnych wierszach na podstawie liczby dopasowań
        for (int j = 0; j < matches; j++) {
            if (i + j + 1 < cards.size()) {
                cards[i + j + 1] += cards[i];
            }
        }
    }

    // Suma wszystkich kopii kart
    for (int i = 0; i < cards.size(); i++) {
        solution += cards[i];
    }

    
    std::cout <<"Drugi problem:" << solution << std::endl;
}


int main() {
    std::ifstream myFile("input.txt");  
    if (!myFile.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return 1; 
    }

    std::string line;
    std::vector<std::string> lines;

    // Wczytanie wszystkich linii z pliku
    while (std::getline(myFile, line)) {
        if (line.empty()) {
            break;  
        }
        lines.push_back(line);
    }

    myFile.close();

    
    firstProblem(lines);
    secondProblem(lines);

    return 0;
}
