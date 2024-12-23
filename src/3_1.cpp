#include <iostream>   
#include <fstream>   
#include <vector>     
#include <cctype>     
#include <string>     

using namespace std;

// Funkcja sprawdza, czy znak jest symbolem (czyli nie jest cyfrą ani kropką)
bool isSymbol(char ch) {
    return !isdigit(ch) && ch != '.';  
}

// Funkcja sprawdza, czy liczba ma symbol w sąsiedztwie
// Przeszukiwany obszar to wszystkie komórki wokół liczby (łącznie 8 komórek, czyli sąsiadujące)
bool hasAdjacentSymbol(const vector<string>& schematic, int row, int start_col, int end_col) {
    size_t max_row = schematic.size();       
    size_t max_col = schematic[0].size();    

    // Przechodzimy przez wszystkie komórki wokół liczby (w obrębie 3x3 obszaru)
    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = start_col - 1; c <= end_col + 1; c++) {
           
            if (r >= 0 && r < max_row && c >= 0 && c < max_col) {
                
                if (r == row && c >= start_col && c <= end_col) {
                    continue;
                }
                
                if (isSymbol(schematic[r][c])) {
                    return true;  
                }
            }
        }
    }
    return false;  // Brak symbolu w sąsiedztwie
}

int main() {
    
    ifstream inputFile("C:\\Users\\Olaf Cichosz\\Desktop\\laby c++\\projekt2\\zad3\\3_1\\3_1\\input.txt");
    if (!inputFile) {  
        cerr << "Nie można otworzyć pliku input.txt!" << endl;
        return 1; 
    }

    vector<string> schematic;  // Wektor do przechowywania wierszy schematu
    string line;

    // Wczytywanie pliku linia po linii
    while (getline(inputFile, line)) {
        schematic.push_back(line);  // Dodanie linii do wektora
    }
    inputFile.close();  // Zamknięcie pliku po wczytaniu danych

    int total_sum = 0;  // Zmienna do przechowywania sumy wszystkich numerów części

    // Iteracja przez każdy wiersz schematu
    for (size_t row = 0; row < schematic.size(); row++) {
        size_t col = 0; 
        while (col < schematic[row].size()) {  
            if (isdigit(schematic[row][col])) {  
                size_t start_col = col; 

                // Przechodzimy przez całą liczbę (dopóki kolejne znaki to cyfry)
                while (col < schematic[row].size() && isdigit(schematic[row][col])) {
                    col++;
                }
                size_t end_col = col - 1;  // Zapisujemy końcową kolumnę liczby

               
                int number = stoi(schematic[row].substr(start_col, end_col - start_col + 1));

                
                if (hasAdjacentSymbol(schematic, row, start_col, end_col)) {
                    total_sum += number;  // Dodanie liczby do sumy, jeśli ma symbol w sąsiedztwie
                }
            }
            else {
                col++;  // Przechodzimy do następnego znaku
            }
        }
    }

   
    cout << "Suma wszystkich numerów części: " << total_sum << endl;

    return 0; 
}
