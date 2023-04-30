#include "06_Tree_Forest/BTree/BTree.hpp"

int main()
{
    BTree<int, 4> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);
    tree.insert(45);
    tree.insert(46);
    tree.insert(55);
    tree.insert(56);
    tree.printTree();
    tree.erase(55);
    tree.printTree();
    tree.erase(55);
    tree.erase(40);
    tree.printTree();
}

////template<class _CTy>
////class SC { };
////
////template<class _ATy>
////class SA
////{
////    using MySC = SC<_ATy>;
////
////    class SB
////    {
////        template<class _BTy, class _Iter>
////            requires
////        std::is_same_v<typename std::iterator_traits<_Iter>::value_type, typename SA<_ATy>::MySC>
////        void foo(_BTy b, _Iter bIt);
////    };
////};
////
////template<class _ATy>
////template<class _BTy, class _Iter>
////    requires std::is_same_v<typename std::iterator_traits<_Iter>::value_type, typename SA<_ATy>::MySC>
////void SA<_ATy>::SB::foo(_BTy b, _Iter bIt)
////{
////
////}