#include <iostream>   
#include <fstream>   
#include <sstream>    
#include <string>     
#include <map>        

using namespace std;

// Funkcja `parseCubes` analizuje tekst w formacie "3 blue, 4 red"
// i tworzy mapę, która zlicza ilości klocków dla każdego koloru.
map<string, int> parseCubes(const string& line) {
    map<string, int> cubes;         // Mapa do przechowywania liczby klocków dla każdego koloru
    stringstream ss(line);
    string part;                   

    // Pętla dzieli ciąg znaków po przecinkach i analizuje każdy fragment
    while (getline(ss, part, ',')) {
        stringstream partStream(part); 
        int count;                     
        string color;                   

        partStream >> count >> color;   // Wczytanie liczby i koloru z fragmentu do zmiennych

       
        cubes[color] += count;
    }

    return cubes;  
}

int main() {
    // Ustawienie maksymalnych dozwolonych ilości klocków dla każdego koloru
    int maxRed = 12, maxGreen = 13, maxBlue = 14;

  
    ifstream file("input.txt");
    if (!file) {  
        cerr << "Error opening file." << endl;  
        return 1;  
    }

    string line;                    
    int sumOfValidGameIDs = 0;      

  
    while (getline(file, line)) {
        stringstream gameStream(line);   // Tworzenie strumienia do analizy linii gry

        // Odczytanie identyfikatora gry z formatu "Game X:"
        string gameIDStr;
        getline(gameStream, gameIDStr, ':');  
        int gameID = stoi(gameIDStr.substr(5));  

        bool isValidGame = true;  

        // Pętla analizująca każdy zestaw klocków oddzielony średnikiem ';'
        string set;
        while (getline(gameStream, set, ';')) {
            
            map<string, int> cubes = parseCubes(set);

          
            if (cubes["red"] > maxRed || cubes["green"] > maxGreen || cubes["blue"] > maxBlue) {
                isValidGame = false;  // Jeśli limit jest przekroczony, gra jest nieważna
                break;  
            }
        }

        // Jeśli gra jest ważna, dodajemy jej identyfikator do sumy
        if (isValidGame) {
            sumOfValidGameIDs += gameID;
        }
    }

    file.close(); 

    
    cout << "Suma ID dla wszystkich gier: " << sumOfValidGameIDs << endl;

    return 0;  
}
