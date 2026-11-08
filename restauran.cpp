
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <limits>
#include <functional>
#include <cctype>

using namespace std;

// 1. STRUKTUR DATA RESTORAN

struct Restoran { 
    int id;
    string nama;
    string kategori;
    float rating;
    float jarak;
};

// 2. DATASET 20 RESTORAN

vector<Restoran> data = {
    {1, "KOTAG Coffee", "Kopi/Kafe", 4.9, 0},
    {2, "RM. Carlos", "Rumah Makan Padang", 4.8, 0},
    {3, "Warung Ayam Penyet Syaidin Fadilah", "Ayam Penyet", 4.3, 0},
    {4, "Java Garden Cafe", "Kopi/Kafe", 4.3, 0},
    {5, "MOCO Coffee", "Kopi/Kafe", 4.5, 0},
    {6, "Champion Cafe", "Kopi/Kafe", 4.5, 0},
    {7, "Perintis Coffee", "Kopi/Kafe", 5.0, 0},
    {8, "Cafe MJ", "Kopi/Kafe", 4.0, 0},
    {9, "Potte House Cafe & All Day Dining", "Kopi/Kafe", 4.7, 0},
    {10, "Cold 'N Brew - Medan Mansyur", "Kopi/Kafe", 4.2, 0},
    {11, "Ayam Penyet Bg Nan", "Ayam Penyet", 4.7, 0},
    {12, "Rumah Makan Pariaman Jaya", "Rumah Makan Padang", 4.6, 0},
    {13, "Habitat Coffee Mansyur", "Kopi/Kafe", 4.7, 0},
    {14, "Kopi Kenangan - Ruko Dr Mansyur", "Kopi/Kafe", 4.9, 0},
    {15, "Kantin Mami", "Kantin/Warung Makan", 4.3, 0},
    {16, "Santè Kopitiam", "Kopi/Kafe", 4.8, 0},
    {17, "BAKMIE YARA", "Bakmi", 5.0, 0},
    {18, "Rumah Makan 699", "Rumah Makan Padang", 4.6, 0},
    {19, "d'BestO Pembangunan USU", "Ayam Goreng", 4.7, 0},
    {20, "WaitingList Coffee", "Kopi/Kafe", 4.8, 0}
};

const int N = 20;

// 3. STRUKTUR GRAPH

struct Edge {
    int tujuan;
    double jarak;
};

vector<Edge> graph[N];

// 4. FUNGSI MENGUBAH HURUF KECIL

string hurufKecil(string teks) {
    transform(teks.begin(), teks.end(), teks.begin(),
        [](unsigned char c) {
            return tolower(c);
        });

    return teks;
}

// 5. MENAMPILKAN DATA RESTORAN

void tampilkanRestoran() {
    cout << "\n========== DAFTAR RESTORAN ==========\n";

    for (const auto& r : data) {
        cout << r.id << ". "
             << r.nama
             << " | Kategori: " << r.kategori
             << " | Rating: " << r.rating;

        cout << endl;
    }
}

// 6. SORTING: SELECTION SORT

// sorting berdasarkan rating tertinggi

void sortingRating() {
    vector<Restoran> temp = data;
    int n = temp.size();

    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (temp[j].rating > temp[maxIndex].rating) {
                maxIndex = j;
            }
        }

        swap(temp[i], temp[maxIndex]);
    }

    cout << "\n=== RESTORAN BERDASARKAN RATING ===\n";

    for (const auto& r : temp) {
        cout << r.nama
             << " | Rating: " << r.rating << endl;
    }
}

// input jarak dari lokasi referensi

void inputJarak() {
    cout << "\nMasukkan jarak dari lokasi referensi "
         << "ke setiap restoran (km).\n";

    for (auto& r : data) {
        cout << r.id << ". " << r.nama
             << "\nJarak: ";

        cin >> r.jarak;

        while (cin.fail() || r.jarak < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Jarak tidak valid. Masukkan ulang: ";
            cin >> r.jarak;
        }
    }

    cout << "\nData jarak berhasil dimasukkan.\n";
}

// sorting berdasarkan jarak terdekat

void sortingJarak() {
    vector<Restoran> temp = data;
    int n = temp.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (temp[j].jarak < temp[minIndex].jarak) {
                minIndex = j;
            }
        }

        swap(temp[i], temp[minIndex]);
    }

    cout << "\n=== RESTORAN BERDASARKAN JARAK ===\n";

    for (const auto& r : temp) {
        cout << r.nama
             << " | Jarak: " << r.jarak << " km\n";
    }
}

// 7. SEARCHING: LINEAR SEARCH

void searchingRestoran() {
    string keyword;
    int ditemukan = 0;

    cout << "\nMasukkan nama restoran atau jenis makanan: ";
    getline(cin >> ws, keyword);

    keyword = hurufKecil(keyword);

    cout << "\n=== HASIL PENCARIAN ===\n";

    for (const auto& r : data) {
        string nama = hurufKecil(r.nama);
        string kategori = hurufKecil(r.kategori);

        if (nama.find(keyword) != string::npos ||
            kategori.find(keyword) != string::npos) {

            ditemukan++;

            cout << "\nID       : " << r.id;
            cout << "\nNama     : " << r.nama;
            cout << "\nKategori : " << r.kategori;
            cout << "\nRating   : " << r.rating;
            cout << "\n-----------------------------\n";
        }
    }

    if (ditemukan == 0) {
        cout << "Restoran tidak ditemukan.\n";
    } else {
        cout << "\nJumlah restoran ditemukan: "
             << ditemukan << endl;
    }
}

// 8. GRAPH: INPUT HUBUNGAN RESTORAN

void inputGraph() {
    int jumlahEdge;

    // Menghapus hubungan sebelumnya
    for (int i = 0; i < N; i++) {
        graph[i].clear();
    }

    cout << "\nMasukkan jumlah hubungan antarrestoran: ";
    cin >> jumlahEdge;

    while (cin.fail() || jumlahEdge < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Jumlah tidak valid. Masukkan ulang: ";
        cin >> jumlahEdge;
    }

    for (int i = 0; i < jumlahEdge; i++) {
        int asal, tujuan;
        double jarak;

        cout << "\nHubungan ke-" << i + 1 << endl;

        cout << "ID restoran asal: ";
        cin >> asal;

        cout << "ID restoran tujuan: ";
        cin >> tujuan;

        if (cin.fail() || asal < 1 || asal > N ||
            tujuan < 1 || tujuan > N || asal == tujuan) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "ID tidak valid. Ulangi.\n";
            i--;
            continue;
        }

        cout << "Jarak antarrestoran (km): ";
        cin >> jarak;

        if (cin.fail() || jarak <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Jarak tidak valid. Ulangi.\n";
            i--;
            continue;
        }

        // Graph tidak berarah
        graph[asal - 1].push_back({tujuan - 1, jarak});
        graph[tujuan - 1].push_back({asal - 1, jarak});
    }

    cout << "\nGraph berhasil dibuat.\n";
}

// 9. MENAMPILKAN GRAPH

void tampilkanGraph() {
    cout << "\n========== GRAPH RESTORAN ==========\n";

    for (int i = 0; i < N; i++) {
        cout << data[i].id << ". "
             << data[i].nama << " -> ";

        for (const auto& e : graph[i]) {
            cout << data[e.tujuan].nama
                 << " (" << e.jarak << " km), ";
        }

        cout << endl;
    }
}

// 10. DIJKSTRA: RUTE TERPENDEK

void dijkstra(int awal, int tujuan) {
    const double INF = numeric_limits<double>::infinity();

    vector<double> jarak(N, INF);
    vector<int> sebelumnya(N, -1);

    priority_queue<
        pair<double, int>,
        vector<pair<double, int>>,
        greater<pair<double, int>>
    > pq;

    int start = awal - 1;
    int finish = tujuan - 1;

    jarak[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        double jarakSekarang = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (jarakSekarang > jarak[node]) {
            continue;
        }

        for (const auto& e : graph[node]) {
            int tetangga = e.tujuan;

            double jarakBaru = jarak[node] + e.jarak;

            if (jarakBaru < jarak[tetangga]) {
                jarak[tetangga] = jarakBaru;
                sebelumnya[tetangga] = node;

                pq.push({jarakBaru, tetangga});
            }
        }
    }

    if (jarak[finish] == INF) {
        cout << "\nRute tidak ditemukan.\n";
        return;
    }

    // Menyusun jalur terpendek
    vector<int> rute;

    for (int node = finish; node != -1;
         node = sebelumnya[node]) {
        rute.push_back(node);
    }

    reverse(rute.begin(), rute.end());

    cout << "\n========== HASIL DIJKSTRA ==========\n";
    cout << "Rute terpendek:\n";

    for (int i = 0; i < (int)rute.size(); i++) {
        cout << data[rute[i]].nama;

        if (i < (int)rute.size() - 1) {
            cout << " -> ";
        }
    }

    cout << "\nTotal jarak: "
         << fixed << setprecision(2)
         << jarak[finish] << " km\n";
}

// 11. MENU DIJKSTRA

void menuDijkstra() {
    int awal, tujuan;

    cout << "\n========== PILIH RESTORAN ==========\n";

    for (const auto& r : data) {
        cout << r.id << ". " << r.nama
             << " (" << r.kategori << ")\n";
    }

    cout << "\nID restoran awal: ";
    cin >> awal;

    cout << "ID restoran tujuan: ";
    cin >> tujuan;

    if (cin.fail() || awal < 1 || awal > N ||
        tujuan < 1 || tujuan > N) {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "ID tidak valid.\n";
        return;
    }

    if (awal == tujuan) {
        cout << "Pilih dua restoran yang berbeda.\n";
        return;
    }

    // Memastikan kedua restoran sejenis
    if (data[awal - 1].kategori !=
        data[tujuan - 1].kategori) {

        cout << "\nKedua restoran bukan kategori sejenis.\n";
        return;
    }

    dijkstra(awal, tujuan);
}

// 12. MENU UTAMA

int main() {
    int pilihan;

    do {
        cout << "\n====================================\n";
        cout << "       SISTEM REKOMENDASI RESTORAN\n";
        cout << "====================================\n";

        cout << "1. Lihat Daftar Seluruh Restoran\n";
        cout << "2. Tampilkan Restoran dengan Rating Tertinggi\n";
        cout << "3. Masukkan Jarak dari Lokasi Anda\n";
        cout << "4. Tampilkan Restoran Terdekat\n";
        cout << "5. Cari Restoran Berdasarkan Nama atau Jenis Makanan\n";
        cout << "6. Atur Jarak Antarrestoran\n";
        cout << "7. Lihat Hubungan Antarrestoran\n";
        cout << "8. Temukan Rute Terpendek Antarrestoran\n";
        cout << "0. Keluar\n";

        cout << "------------------------------------\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanRestoran();
                break;

            case 2:
                sortingRating();
                break;

            case 3:
                inputJarak();
                break;

            case 4:
                sortingJarak();
                break;

            case 5:
                searchingRestoran();
                break;

            case 6:
                inputGraph();
                break;

            case 7:
                tampilkanGraph();
                break;

            case 8:
                menuDijkstra();
                break;

            case 0:
                cout << "\nProgram selesai. Terima kasih!\n";
                break;

            default:
                cout << "\nPilihan tidak tersedia.\n";
        }

    } while (pilihan != 0);

    return 0;
}
