#include <iostream>  
#include <fstream>    
#include <sstream>   
#include <string>    
#include <map>        
#include <algorithm>  

using namespace std;

// Funkcja `parseCubes` analizuje zestaw klocków w postaci tekstowej i zlicza ilość klocków każdego koloru.
// Przykładowy format: "3 red, 2 blue, 5 green"
// Wynik: mapa, która zawiera liczbę klocków dla każdego koloru (np. {"red": 3, "blue": 2, "green": 5}).
map<string, int> parseCubes(const string& line) {
    map<string, int> cubes;        
    stringstream ss(line);         
    string part;                    

    // Pętla dzieli linię po przecinkach i analizuje każdy fragment
    while (getline(ss, part, ',')) {
        stringstream partStream(part);
        int count;                      
        string color;                  

        partStream >> count >> color;  

        cubes[color] += count;         
    }

    return cubes;  // Zwrócenie mapy z liczbami klocków dla każdego koloru
}

int main() {
    ifstream file("input.txt"); 
    if (!file) {  
        cerr << "Error opening file." << endl; 
        return 1; 
    }

    string line;           
    int sumOfPowers = 0;  

    // Główna pętla czytająca plik linia po linii
    while (getline(file, line)) {
        stringstream gameStream(line);  

      
        string gameIDStr;
        getline(gameStream, gameIDStr, ':');  

        // Zmienne do śledzenia maksymalnej liczby klocków dla każdego koloru
        int maxRed = 0, maxGreen = 0, maxBlue = 0;

       
        string set;
        while (getline(gameStream, set, ';')) {
          
            map<string, int> cubes = parseCubes(set);

            // Aktualizacja maksymalnej liczby klocków dla każdego koloru
            // Używamy funkcji `max`, aby znaleźć maksymalną wartość spośród dotychczasowej i obecnej liczby klocków
            maxRed = max(maxRed, cubes["red"]);
            maxGreen = max(maxGreen, cubes["green"]);
            maxBlue = max(maxBlue, cubes["blue"]);
        }

        
        int power = maxRed * maxGreen * maxBlue;

       
        sumOfPowers += power;
    }

    file.close();  

   
    cout << "Suma cakowita mocy gier: " << sumOfPowers << endl;

    return 0;  
}
