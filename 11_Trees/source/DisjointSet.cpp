
struct unionFindNode
{
	int parent;	// IF "root" is true, it indicates the weight of the whole tree; Otherwise it is the pointer to it's parent node.
	bool root;	// The value is true only when the node is the root.
	unionFindNode() {
		parent = 1; root = true;
	}
};

unionFindNode* node;

void initialize(int numberOfElements) {
	node = new unionFindNode[numberOfElements + 1];
}

// Return the root of the tree which contains "theElment".
int find_pathTighten(int theElement) {
	// Tighten the path from "theElement" to the root.
	int theRoot = theElement;
	// Loop until "theRoot" is the root of the tree.
	while (!node[theRoot].root) {
		theRoot = node[theRoot].parent;
	}
	// Change all the nodes's parents(from the "theElement" to "root") to "root".
	int currentNode = theElement;
	while (currentNode != theRoot) {
		int parentNode = node[currentNode].parent;
		node[currentNode].parent = theRoot;
		currentNode = parentNode;
	}
	return theRoot;
}

int find_pathSplit(int theElement) {
	int theRoot = theElement;
	while (!node[theRoot].root) {
		theRoot = node[theRoot].parent;
	}
	int currentNode = theElement;
	int grandNode = node[node[theElement].parent].parent;
	while (grandNode != theRoot) {
		node[currentNode].parent = grandNode;
		currentNode = node[currentNode].parent;
		grandNode = node[grandNode].parent;
	}
	return theRoot;
}

void unite(int rootA, int rootB) {
	// IF: "rootA"'s weight is less than "rootB"'s.
	if (node[rootA].parent < node[rootB].parent) {
		node[rootB].parent += node[rootA].parent;
		node[rootA].root = false;
		node[rootA].parent = rootB;
	}
	// ELSE IF: "rootA"'s weight is more than "rootB"'s.
	else {
		node[rootA].parent += node[rootB].parent;
		node[rootB].root = false;
		node[rootB].parent = rootA;
	}
}