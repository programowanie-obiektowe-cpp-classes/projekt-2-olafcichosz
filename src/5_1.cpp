#include <iostream>   
#include <fstream>   
#include <vector>    
#include <sstream>    
#include <limits>     
#include <string>     
#include <algorithm>  

using namespace std;

// ---------------------- Struktura reprezentująca zakres mapy ---------------------------
// Struktura `Range` przechowuje dane o jednym zakresie mapowania: 
// - dest_start: początek zakresu w nowej kategorii (docelowy),
// - source_start: początek zakresu w starej kategorii (źródłowy),
// - range_length: długość zakresu (ilość wartości w tym zakresie).
struct Range {
    long long dest_start;     // Początkowa wartość w nowej kategorii
    long long source_start;   // Początkowa wartość w starej kategorii
    long long range_length;   // Długość zakresu
};

// ---------------------- Funkcja do parsowania sekcji mapy ---------------------------
// Funkcja wczytuje sekcję mapy z pliku i zapisuje zakresy w postaci obiektów `Range`.
// - Funkcja przetwarza każdą linię, dzieląc ją na trzy liczby: dest, source, length,
// - Następnie dodaje ten zakres do wektora `ranges`.
// Funkcja kończy działanie, gdy napotka pustą linię.
vector<Range> parseMapSection(istream& file) {
    vector<Range> ranges;  
    string line;           

    // Czytanie kolejnych linii z pliku, aż napotkamy pustą linię
    while (getline(file, line) && !line.empty()) {
        istringstream iss(line);  // Tworzymy strumień z linii
        long long dest, source, length;

        // Wczytujemy trzy liczby z linii (dest, source, length)
        if (iss >> dest >> source >> length) {
            // Tworzymy obiekt Range i dodajemy go do wektora
            ranges.push_back({ dest, source, length });
        }
    }
    return ranges; 
}

// ---------------------- Funkcja mapująca pojedynczą wartość przez mapę ---------------------------
// Funkcja przyjmuje wartość (value) i przekształca ją na podstawie dostępnych zakresów w mapie.
// - Sprawdza, czy wartość mieści się w którymś z zakresów w mapie.
// - Jeśli tak, to przekształca ją na nową wartość zgodnie z docelowym zakresem.
// - Jeśli nie pasuje do żadnego zakresu, zwraca oryginalną wartość.
long long mapValue(long long value, const vector<Range>& ranges) {
    for (const Range& range : ranges) {
        // Sprawdzamy, czy wartość mieści się w zakresie mapy
        if (value >= range.source_start && value < range.source_start + range.range_length) {
            // Przekształcamy wartość na podstawie mapy
            return range.dest_start + (value - range.source_start);
        }
    }
    return value;  // Jeśli brak mapowania, wartość pozostaje bez zmian
}

// ---------------------- Funkcja do znalezienia minimalnej lokalizacji ---------------------------
// Funkcja przyjmuje listę nasion (`seeds`) oraz mapy (`maps`) i dla każdego nasiona,
// aplikuje mapy, aby znaleźć najmniejszą możliwą lokalizację.
// - Każde nasiono jest przekształcane przez wszystkie mapy w kolejności.
// - Na końcu funkcja zwraca minimalną lokalizację, którą uzyskujemy po wszystkich przekształceniach.
long long findLowestLocation(const vector<long long>& seeds, const vector<vector<Range>>& maps) {
    long long min_location = numeric_limits<long long>::max();  // Inicjalizujemy minimalną lokalizację na wartość maksymalną

    // Dla każdego nasiona przekształcamy je przez wszystkie mapy
    for (long long seed : seeds) {
        long long value = seed;  // Ustawiamy początkową wartość jako nasiono

        // Przechodzimy przez wszystkie mapy i aplikujemy mapowanie na nasionie
        for (const vector<Range>& map : maps) {
            value = mapValue(value, map);  // Mapowanie wartości przez mapę
        }

        // Zaktualizowanie minimalnej lokalizacji
        min_location = min(min_location, value);
    }

    return min_location;  // Zwracamy najmniejszą lokalizację
}


int main() {
    ifstream inputFile("input.txt"); 
    if (!inputFile) {  
        cerr << "Error: Cannot open input file." << endl;  
        return 1;  
    }

    string line;                          
    vector<long long> seeds;               
    vector<vector<Range>> maps;            

    
    getline(inputFile, line);  // Wczytanie linii z nasionami
    istringstream seedsStream(line.substr(line.find(":") + 1));  
    long long seed;
    while (seedsStream >> seed) {  // Wczytujemy poszczególne nasiona
        seeds.push_back(seed);  // Dodajemy nasiono do wektora
    }

    // Parsowanie sekcji map w pliku
    while (getline(inputFile, line)) {
        if (line.find("map:") != string::npos) {  // Jeśli linia zawiera "map:"
            maps.push_back(parseMapSection(inputFile));  // Parsujemy mapę i dodajemy do wektora
        }
    }

    // Rozwiązanie problemu - znalezienie minimalnej lokalizacji dla podanych nasion i map
    long long result = findLowestLocation(seeds, maps);

   
    cout << "Najnizszy numer lokalizacji: " << result << endl;

    return 0;  
}
