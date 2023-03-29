#include <set>
#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

list<set<int>> gangSetList{};
map<int, list<set<int>>::iterator> gangMap{};   // gangstar (int) to set he's in (iterator)
map<int, vector<int>> enemyMap{};                       // gangstar (int) to he's enemies (vector<int>)

// @brief Create a singleton, both maintaining {gangSetList} and {gangMap}.
inline void createSingleton(int gangstar) {
    set<int> singleton; singleton.insert(gangstar);     // Create a singleton containing {gangstar1}
    gangSetList.push_front(singleton);                  // Push the singleton to head of {gangSetList}
    gangMap[gangstar] = gangSetList.begin();            // Map {gangStar1} to the iterator of the single set
}

inline void union_2Gangstars(int gangstar1, int gangstar2) {
    if (gangMap[gangstar1] == gangSetList.end() || gangMap[gangstar2] == gangSetList.end()) { return; }
    auto& set1_iter = gangMap[gangstar1];   // The set gangstar1 is in
    auto& set2_iter = gangMap[gangstar2];   // The set gangstar2 is in
    set<int> result{};                      // The set to store the unioned set
    // Union the 2 sets:
    set_union(set1_iter->begin(), set1_iter->end(), set2_iter->begin(), set2_iter->end(), back_inserter(result));
    swap(*set1_iter, result);               // Swap the result and set1
    // Maintain {gangMap}:
    for (auto gangstar : *set2_iter) { gangMap[gangstar] = set1_iter; }
    // Maintain {gangSetList}:
    gangSetList.erase(set2_iter);
}

int main() {
    int numOfGangstar{}, numOfLine{};
    cin >> numOfGangstar >> numOfLine;
    cout << 1;
    while (numOfLine-- > 0) {
        char ch{};
        int gangstar1{}, gangstar2{};
        cin >> ch >> gangstar1 >> gangstar2;
        auto& setOfGangstar1 = gangMap[gangstar1];
        auto& setOfGangstar2 = gangMap[gangstar2];
        switch (ch)
        {
        case 'F': {
            // IF both gangstars are not in set:
            if (setOfGangstar1 == gangSetList.end() && setOfGangstar2 == gangSetList.end()) {
                set<int> set1; set1.insert(gangstar1);
                set<int> set2; set2.insert(gangstar2);
                set<int> result;
                set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(result));
                gangSetList.push_front(result);
                gangMap[gangstar1] = gangMap[gangstar2] = gangSetList.begin();
            }
            // ELSE IF gangstar2 is in a set, but gangstar1 is not:
            else if (setOfGangstar1 == gangSetList.end()) {
                gangMap[gangstar2]->insert(gangstar1);
                gangMap[gangstar1] = gangMap[gangstar2];
            }
            // ELSE IF gangstar1 is in a set, but gangstar2 is not:
            else if (setOfGangstar2 == gangSetList.end()) {
                gangMap[gangstar1]->insert(gangstar2);
                gangMap[gangstar2] = gangMap[gangstar1];
            }
            // ElSE IF in different set:
            else if (setOfGangstar1 != setOfGangstar2) {
                throw "[ERROR] Different Set!";
            }
        }
        case 'E': {
            // IF both not in set:
            if (setOfGangstar1 == gangSetList.end() && setOfGangstar2 == gangSetList.end()) {
                createSingleton(gangstar1);
                enemyMap[gangstar1].push_back(gangstar2);   // Add {gangstar2} to the enemy vector of {gangstar1}
                createSingleton(gangstar2);
                enemyMap[gangstar1].push_back(gangstar2);   // Add {gangstar1} to the enemy vector of {gangstar2}
            }
            // ELSE IF gangstar1 is not in a set:
            else if (setOfGangstar1 == gangSetList.end()) {
                createSingleton(gangstar1);
            }
            // ELSE IF gangstar2 is not in a set:
            else if (setOfGangstar2 == gangSetList.end()) {
                set<int>gang2; gang2.insert(gangstar2);
                gangSetList.push_front(gang2);
            }
            // ELSE IF gangstar1 and gangstar2 are both in the same set:
            else if (setOfGangstar1 == setOfGangstar2) {
                throw "[ERROR] Impossible of enemies!";
            }
            // ELSE gangstar1 and gangstar2 are in different sets:
            else {
            }
        }
        default:
            break;
        }
    }
}