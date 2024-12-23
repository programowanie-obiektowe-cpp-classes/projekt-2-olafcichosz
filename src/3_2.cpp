#include <iostream>   
#include <fstream>    
#include <vector>     
#include <cctype>    
#include <string>     
using namespace std;

// Funkcja sprawdzająca, czy znak jest cyfrą
bool isDigit(char ch) {
    return isdigit(ch); // Sprawdzenie, czy znak `ch` jest cyfrą
}

// Funkcja sprawdzająca, czy znak jest symbolem zębatki '*'
bool isGear(char ch) {
    return ch == '*';  // Zwraca true, jeśli znak `ch` to '*'
}

// Funkcja do odczytu pełnej liczby oraz jej granic w danym wierszu
// Parametry:
// - `schematic`: wektor przechowujący schemat
// - `row`: indeks aktualnego wiersza
// - `col`: referencja do kolumny, na której znaleziono cyfrę
int extractNumber(const vector<string>& schematic, int row, int& col) {
    int start_col = col;  
    
    while (start_col > 0 && isdigit(schematic[row][start_col - 1])) {
        start_col--;
    }

    int end_col = col; 
    // Szukamy końca liczby przesuwając się w prawo, dopóki napotykamy cyfry
    while (end_col < schematic[row].size() && isdigit(schematic[row][end_col])) {
        end_col++;
    }

    col = end_col;  // Przesuwamy wskaźnik kolumny na koniec liczby (dla następnych operacji)

   
    return stoi(schematic[row].substr(start_col, end_col - start_col));
}


int calculateGearRatio(const vector<string>& schematic) {
    int rows = schematic.size();         
    int cols = schematic[0].size();      
    int total_sum = 0;                  

    // Przeszukiwanie całego schematu w poszukiwaniu symboli '*'
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (schematic[row][col] == '*') {  // Znaleziono symbol '*'
                vector<int> adjacent_numbers;  

              
                for (int r = row - 1; r <= row + 1; r++) {  // Sąsiednie wiersze
                    for (int c = col - 1; c <= col + 1; c++) {  // Sąsiednie kolumny
                        // Sprawdzenie, czy aktualna komórka mieści się w granicach schematu
                        if (r >= 0 && r < rows && c >= 0 && c < cols && isdigit(schematic[r][c])) {
                            // Pobranie pełnej liczby i przesunięcie wskaźnika kolumny na jej koniec
                            int number = extractNumber(schematic, r, c);
                            adjacent_numbers.push_back(number);  // Dodanie liczby do wektora
                        }
                    }
                }

                // Jeśli w sąsiedztwie znajdują się dokładnie dwie liczby, obliczamy ich iloczyn
                if (adjacent_numbers.size() == 2) {
                    total_sum += adjacent_numbers[0] * adjacent_numbers[1];  // Dodajemy iloczyn do sumy
                }
            }
        }
    }

    return total_sum;  // Zwracamy sumę wszystkich ilorazów zębatek
}

int main() {
    ifstream inputFile("input.txt");  
    if (!inputFile) { 
        cerr << "Nie można otworzyć pliku input.txt!" << endl;
        return 1;  
    }

    vector<string> schematic;  
    string line;

    
    while (getline(inputFile, line)) {
        schematic.push_back(line);  
    }
    inputFile.close();  

    
    int result = calculateGearRatio(schematic);

    
    cout << "Suma wszystkich ilorazów liczb przy *: " << result << endl;

    return 0;  
}
