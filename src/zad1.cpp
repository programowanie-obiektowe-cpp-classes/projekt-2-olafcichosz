#include <iostream>   
#include <fstream>    
#include <vector>     
#include <string>     
#include <unordered_map> 
#include <cctype>    

using namespace std;

// Funkcja przetwarza pojedynczą linię tekstu i wyodrębnia pierwszą oraz ostatnią cyfrę.
// Cyfry te są łączone, tworząc liczbę dwucyfrową (np. pierwsza cyfra: 2, ostatnia cyfra: 3 -> wynik: 23).
// Jeśli linia nie zawiera cyfr, funkcja zwraca 0.
int getCalibrationValue(const string& line) {
    char first_digit = '\0', last_digit = '\0';  // Zmienna przechowująca pierwszą i ostatnią cyfrę w linii

    // Iterujemy przez każdy znak w linii
    for (char ch : line) {
        if (isdigit(ch)) {  
            if (first_digit == '\0') {  
                first_digit = ch; 
            }
            last_digit = ch;  
        }
    }

    // Jeśli znaleziono zarówno pierwszą, jak i ostatnią cyfrę, łączymy je w liczbę dwucyfrową
    if (first_digit != '\0' && last_digit != '\0') {
        return (first_digit - '0') * 10 + (last_digit - '0');  
    }

    return 0; 
}

// Funkcja działa podobnie do `getCalibrationValue`, ale dodatkowo rozpoznaje słowa oznaczające cyfry
// (np. "one" -> 1, "two" -> 2) i przekształca je na odpowiednie liczby.
int extractCalibrationValue(const string& line) {
    // Mapa tłumacząca słowa na odpowiadające im cyfry
    unordered_map<string, int> wordToDigit = {
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5},
        {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
    };

    vector<int> digits;  // Wektor przechowujący cyfry znalezione w linii

   
    for (size_t i = 0; i < line.length(); ++i) {
        if (isdigit(line[i])) {  
            digits.push_back(line[i] - '0');  
        }
        else {
            // Jeśli znak nie jest cyfrą, sprawdzamy, czy fragment tekstu to słowo odpowiadające liczbie
            for (const auto& word : wordToDigit) {
                if (line.substr(i, word.first.length()) == word.first) {  
                    digits.push_back(word.second);  
                }
            }
        }
    }

    // Jeśli wektor zawiera cyfry, tworzymy liczbę dwucyfrową z pierwszej i ostatniej cyfry
    if (!digits.empty()) {
        int calibrationValue = digits.front() * 10 + digits.back();  y
        return calibrationValue;
    }

    return 0; 
}

int main() {
    ifstream inputFile("input.txt");  
    if (!inputFile) {  
        cerr << "Nie mozna otworzyc pliku input.txt!" << endl;  
        return 1;
    }

    string line; 
    int sum = 0;  
    int totalSum = 0;  

    // Wczytujemy plik linia po linii
    while (getline(inputFile, line)) {
       
        totalSum += getCalibrationValue(line);  
        sum += extractCalibrationValue(line);  
    }

    inputFile.close();  

   
    cout << "Zadanie 1: " << totalSum << endl; 
    cout << "Zadanie 2: " << sum << endl; 

    return 0; 
}
