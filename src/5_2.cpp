#include <iostream>   
#include <fstream>    
#include <vector>    
#include <sstream>   
#include <limits>     
#include <algorithm>  

using namespace std;

// ---------------------- Struktura reprezentująca pojedynczy zakres mapowania ---------------------------
// Struktura `Range` zawiera informacje o pojedynczym zakresie mapowania:
// - dest_start: Początek zakresu w nowej kategorii (destynacja).
// - source_start: Początek zakresu w starej kategorii (źródło).
// - range_length: Długość zakresu (ilość wartości w tym zakresie).
struct Range {
    long long dest_start;     // Początek zakresu w nowej kategorii
    long long source_start;   // Początek zakresu w starej kategorii
    long long range_length;   // Długość zakresu (ilość wartości w tym zakresie)
};

// ---------------------- Funkcja parsująca sekcję mapy ---------------------------
// Funkcja przetwarza sekcję mapy w pliku i wczytuje zakresy do obiektów struktury `Range`.
// Działa na podstawie strumienia wejściowego, gdzie każda linia zawiera trzy liczby (dest, source, length).
// Zwraca wektor obiektów `Range`, który reprezentuje wszystkie zakresy mapy.

vector<Range> parseMapSection(istream& file) {
    vector<Range> ranges;  // Wektor przechowujący zakresy mapy
    string line;           // Zmienna przechowująca aktualnie wczytaną linię

   
    while (getline(file, line) && !line.empty()) {
        istringstream iss(line);  // Tworzymy strumień z aktualnej linii
        long long dest, source, length;

        // Próba odczytania trzech liczb (dest, source, length) z linii
        if (iss >> dest >> source >> length) {
            // Dodajemy nowy zakres do wektora
            ranges.push_back({ dest, source, length });
        }
    }
    return ranges; 
}

// ---------------------- Funkcja mapująca zakresy ---------------------------
// Funkcja mapuje zakresy, przekształcając je na podstawie mapy, której zakresy są zapisane w `map`.
// Dla każdego z istniejących zakresów w `ranges`, sprawdzamy, czy można je przekształcić przy użyciu mapy.
// Jeśli wartość mieści się w którymś z zakresów mapy, obliczamy nowy początek zakresu i dodajemy go do wynikowego wektora.

vector<pair<long long, long long>> mapRanges(const vector<pair<long long, long long>>& ranges, const vector<Range>& map) {
    vector<pair<long long, long long>> new_ranges;  // Wektor na przekształcone zakresy

    // Iteracja po każdym zakresie
    for (auto& range : ranges) {
        long long range_start = range.first;  // Początek zakresu
        long long range_end = range_start + range.second;  // Koniec zakresu

        // Przekształcamy zakres dopóki nie osiągniemy końca zakresu
        while (range_start < range_end) {
            bool mapped = false;  // Flaga do śledzenia, czy zakres został przekształcony

            // Iteracja po wszystkich zakresach mapy
            for (const auto& r : map) {
                long long source_start = r.source_start;  // Początek zakresu w źródłowej kategorii
                long long source_end = source_start + r.range_length;  // Koniec zakresu w źródłowej kategorii
                long long dest_start = r.dest_start;  // Początek zakresu w docelowej kategorii

                // Sprawdzamy, czy nasz zakres nakłada się na zakres mapy
                if (range_start >= source_start && range_start < source_end) {
                    long long overlap_length = min(range_end, source_end) - range_start;  // Obliczamy długość nakładającego się zakresu
                    new_ranges.emplace_back(dest_start + (range_start - source_start), overlap_length);  // Dodajemy nowy zakres do wyniku
                    range_start += overlap_length;  // Przesuwamy początek zakresu
                    mapped = true;  // Oznaczamy, że zakres został przekształcony
                    break;  
                }
            }

            
            if (!mapped) {
                new_ranges.emplace_back(range_start, range_end - range_start);
                break;  // Kończymy, ponieważ brak mapowania
            }
        }
    }

    return new_ranges; 
}

// ---------------------- Funkcja do znalezienia minimalnej lokalizacji ---------------------------
// Funkcja znajduje minimalną lokalizację dla podanych nasion i map.
// Dla każdego nasiona w `seed_ranges`, stosujemy wszystkie mapy i obliczamy minimalną lokalizację,
// która jest osiągnięta przez te nasiona po przekształceniach.
long long findLowestLocation(const vector<pair<long long, long long>>& seed_ranges, const vector<vector<Range>>& maps) {
    vector<pair<long long, long long>> ranges = seed_ranges;  // Inicjalizujemy początkowe zakresy z nasion

    // Dla każdej mapy przekształcamy zakresy nasion
    for (const auto& map : maps) {
        ranges = mapRanges(ranges, map);  // Przekształcamy zakresy przy użyciu mapy
    }

    // Szukamy minimalnej lokalizacji w przekształconych zakresach
    long long min_location = numeric_limits<long long>::max();  // Inicjalizujemy minimalną lokalizację na największą możliwą wartość
    for (const auto& [start, length] : ranges) {
        min_location = min(min_location, start);  // Uaktualniamy minimalną lokalizację
    }

    return min_location;  // Zwracamy minimalną lokalizację
}


int main() {
    ifstream inputFile("input.txt");  
    if (!inputFile) {  
        cerr << "Error: Cannot open input file 'input.txt'." << endl;
        return 1; 
    }

    string line;                          
    vector<pair<long long, long long>> seed_ranges;  
    vector<vector<Range>> maps;            

    // Parsowanie pierwszej linii zawierającej nasiona
    getline(inputFile, line);  // Wczytanie pierwszej linii z nasionami
    istringstream seedsStream(line.substr(line.find(":") + 1));  // Wydzielenie części z nasionami
    long long start, length;
    while (seedsStream >> start >> length) {  // Wczytanie nasion z linii
        seed_ranges.emplace_back(start, length);  // Dodanie każdego nasiona do wektora
    }

    // Parsowanie map (sekcje rozpoczynające się od "map:")
    while (getline(inputFile, line)) {
        if (line.find("map:") != string::npos) {  // Jeśli linia zawiera "map:"
            maps.push_back(parseMapSection(inputFile));  // Parsujemy sekcję mapy
        }
    }

    
    long long result = findLowestLocation(seed_ranges, maps);

   
    cout << "Najniizszy numer lokalizacji: " << result << endl;

    return 0;  
}
