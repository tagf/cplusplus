#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    map <string, vector<string>> lateng;
    int n;
    cin >> n;
    for (int wc = 0; wc < n; ++wc) {
        string eng, dummy, lat;
        cin >> eng >> dummy;

        bool cont = true;
        do {
            cin >> lat;
            int len = lat.length();
            if (lat[len - 1] == ',') {
                lat = lat.substr(0, len - 1);
            } else {
                cont = false;
            }

            if (lateng.find(lat) == lateng.end()) {
                vector <string> temp(1);
                temp[0] = eng;
                lateng[lat] = temp;
            } else {
                lateng[lat].push_back(eng);
            }
        } while (cont);
    }
    
    for (auto lat : lateng) {
        cout << lat.first << " - ";
        lat.second.sort();
        for (int i = 0; i + 1 < lat.second.size(); ++i) {
            cout << lat.second[i] << ", "
        }
        cout << lat.second[lat.second.size() - 1] << "\n"
    }
    return 0;
}
