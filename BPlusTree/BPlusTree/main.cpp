
#include "BPlus_tree.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	CBPlusTree m_BPlusTree;
	m_BPlusTree.insert(1.1, 1);
	m_BPlusTree.insert(2.2, 6);
	m_BPlusTree.insert(3.4, 7);
	m_BPlusTree.insert(3.5, 8);
	m_BPlusTree.insert(3.6, 9);
	m_BPlusTree.insert(1.2, 2);
	m_BPlusTree.insert(1.3, 3);
	m_BPlusTree.insert(1.4, 4);
	m_BPlusTree.insert(2.1, 5);
	m_BPlusTree.print();
	system("pause");
	return 0;
}