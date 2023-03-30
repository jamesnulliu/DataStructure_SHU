#include <iostream>
#include <unordered_set>

using namespace std;

using Set = unordered_set<int>;

Set A, B, C;  // A->B->C->A

int lies{};

inline Set* findSet(int animal)
{
    Set* setPtr = A.count(animal) ?
        &A : B.count(animal) ?
        &B : C.count(animal) ?
        &C : nullptr;
    return setPtr;
}

inline Set* findPreySet(Set* predation_set) {
    return predation_set == &A ?
        &B : predation_set == &B ?
        &C : predation_set == &C ?
        &A : nullptr;
}

inline Set* findPredationSet(Set* prey_set) {
    return findPreySet(findPreySet(prey_set));
}

int main() {
   int numOfAnimals{}, numOfLines{};
   cin >> numOfAnimals >> numOfLines;
   while (numOfLines-- > 0) {
       int D{}, X{}, Y{};
       cin >> D >> X >> Y;
       if(X>numOfAnimals||Y>numOfAnimals||X<1||Y<1){
            ++lies;
            continue;
       }
       Set* x_set = findSet(X);
       Set* y_set = findSet(Y);
       switch (D)
       {
       case 1: {
           if (x_set == nullptr && y_set == nullptr) {  // If not found
               // Insert to set A
               A.insert(X); A.insert(Y);
               break;
           } else if (x_set == nullptr) {  // If Y is in a set, but X is not
               y_set->insert(X);
           } else if (y_set == nullptr) {  // If X is in a set, but Y is not
               x_set->insert(Y);
           } else if (x_set != y_set) {  // If X and Y are in different sets
               ++lies;
           }
           break;  // The left case is  X and Y are in the same set
       }
       case 2: {
           if (x_set == nullptr && y_set == nullptr) {  // Both not found
               A.insert(X);
               B.insert(Y);
           } else if (x_set == nullptr) {  // IF Y is in, X not
               findPredationSet(y_set)->insert(X);
           } else if (y_set == nullptr) {  // IF X is in, Y not
               findPreySet(x_set)->insert(Y);
               // If X and Y are in the same set or Prey of X is not Y:
           } else if (x_set == y_set || findPreySet(x_set) != y_set) {
               ++lies;
           }
           break;  // The left case is X and Y are in different but valid sets.
       }
       default: break;
       }
   }
   cout << lies;
   return 0;
}