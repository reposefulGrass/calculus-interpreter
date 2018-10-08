// Corey Wingo (csw170030)
// 10/15/2017
// Project 4 -- Preventing a Paradox
// CS 2336 Jason Smith

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

template <class Type>
struct Node {
	Type data;
	Node<Type>* leftLink;
	Node<Type>* rightLink;
};

template <class Type>
class BinaryTree {
public:
	Node<Type>* root;

	BinaryTree ();
	BinaryTree (BinaryTree<Type>& other);
	~BinaryTree ();

	const BinaryTree<Type>& operator = (const BinaryTree<Type>&);

	void destroyTree ();

	Node<Type>* search (const Type& item) const;
	void insert (const Type& item);
	void deleteNode (const Type& item);

	bool isEmpty () const;
	
	void inorderTraversal () const;
	void preorderTraversal () const;
	void postorderTraversal () const;	

private:
	void deleteFromTree (Node<Type>* &p);

	void copyTree (Node<Type>* &copied, Node<Type>* other);
	void destroy (Node<Type>* &p);
		
	void inorder (Node<Type>* p) const;
	void preorder (Node<Type>* p) const;
	void postorder (Node<Type>* p) const;
};

/* Default Constructor - initialize root.
*/
template <class Type>
BinaryTree<Type>::BinaryTree () {
	root = nullptr;
}

/* Copy Constructor - copy the tree `other` to `this`.
 *
 * parameters:
 * 	+ other - the tree to copy from.
*/
template <class Type>
BinaryTree<Type>::BinaryTree (BinaryTree<Type>& other) {
	if (other.root == nullptr) {
		root = nullptr;
	} else {
		copyTree(root, other.root);
	}
}

/* Destructor - destroy the tree from the root.
*/
template <class Type>
BinaryTree<Type>::~BinaryTree () {
	destroy(root);
}

/* Assignemnt Operator - copy the tree `other` to `this`.
 *
 * parameters:
 * 	+ other - the tree to copy from (assign to `this`).
*/
template <class Type>
const BinaryTree<Type>& BinaryTree<Type>::operator = (const BinaryTree<Type>& other) {
	if (this != &other) {
		if (root != nullptr) {
			destroy(root);
		}

		if (other.root == nullptr) {
			root = nullptr;
		} else {
			copyTree(root, other.root);
		}
	}	

	return *this;
}

/* isEmpty - returns whether the binary tree is empty (root is null).
*/
template <class Type>
bool BinaryTree<Type>::isEmpty () const {
	return root = nullptr;
}

/* inorderTraversal - traverse the tree inorder.
*/
template <class Type>
void BinaryTree<Type>::inorderTraversal () const {
	inorder(root);
}

/* inorder - traverse the root of the tree `p` in an inorder fashion.
 *
 * parameters:
 * 	+ p - the node to traverse from.
*/
template <class Type>
void BinaryTree<Type>::inorder (Node<Type>* p) const {
	if (p != nullptr) {
		inorder(p->leftLink);
		std::cout << p->data << " ";
		inorder(p->rightLink);
	}
}

/* preorderTraversal - traverse the tree preorder.
*/
template <class Type>
void BinaryTree<Type>::preorderTraversal () const {
	preorder(root);
}

/* preorder - traverse the root of the tree `p` in a preorder fashion.
 *
 * parameters:
 * 	+ p - the node to traverse from. 
*/
template <class Type>
void BinaryTree<Type>::preorder (Node<Type>* p) const {
	if (p != nullptr) {
		std::cout << p->data << " ";
		preorder(p->leftLink);
		preorder(p->rightLink);
	}
}

/* postorderTraversal - traverse the tree postorder.
*/
template <class Type>
void BinaryTree<Type>::postorderTraversal () const {
	postorder(root);
}

/* postorder - traverse the root of the tree `p` in a postorder fashion.
 *
 * paramters:
 * 	+ p - the node to traverse from.
*/
template <class Type>
void BinaryTree<Type>::postorder (Node<Type>* p) const {
	if (p != nullptr) {
		postorder(p->leftLink);
		postorder(p->rightLink);
		std::cout << p->data << " ";
	}
}

template <class Type>
void BinaryTree<Type>::destroyTree () {
	destroy(root);
}

template <class Type>
void BinaryTree<Type>::destroy (Node<Type>* &p) {
	if (p != nullptr) {
		destroy(p->leftLink);
		destroy(p->rightLink);
		delete p;
		p = nullptr;
	}
}

template <class Type>
void BinaryTree<Type>::copyTree (Node<Type>* &copied, Node<Type>* other) {
	if (other == nullptr) {
		copied = nullptr;
	} else {
		copied = new Node<Type>;
		copied->data = other->data;

		copyTree(copied->leftLink, other->leftLink);
		copyTree(copied->rightLink, other->rightLink);
	}
}

// Change to return a pointer to the item found
template <class Type>
Node<Type>* BinaryTree<Type>::search (const Type& item) const {
	Node<Type>* current;
	Node<Type>* found = nullptr;

	if (root != nullptr) {
		current = root;

		while (current != nullptr && (found == nullptr)) {
			//std::cout << current->data << std::endl;

			if (current->data == item) {
				//std::cout << "It is equal!" << std::endl;
				found = current;
			} else if (item < current->data) {
				//std::cout << "Traversing left side" << std::endl;
				current = current->leftLink;
			} else {
				//std::cout << "Traversing right side" << std::endl;
				current = current->rightLink;
			}
		}
	}	

	return found;
}

template <class Type>
void BinaryTree<Type>::insert (const Type& item) {
	Node<Type>* current;
	Node<Type>* trailCurrent = nullptr;
	Node<Type>* newNode;

	newNode = new Node<Type>;
	newNode->data = item;
	newNode->leftLink = nullptr;
	newNode->rightLink = nullptr;	

	if (root == nullptr) {
		root = newNode;
	} else {
		current = root;

		while (current != nullptr) {
			trailCurrent = current;

			if (item < current->data) {
				current = current->leftLink;	
			} else {
				current = current->rightLink;
			}

		}

		if (trailCurrent->data > item) {
			trailCurrent->leftLink = newNode;
		} else {
			trailCurrent->rightLink = newNode;
		}
	}
}

template <class Type>
void BinaryTree<Type>::deleteFromTree (Node<Type>* &p) {
	Node<Type>* current;
	Node<Type>* trailCurrent;
	Node<Type>* temp;

	if (p->leftLink == nullptr && p->rightLink == nullptr) {
		temp = p;
		p = nullptr;
		delete temp;
	} else if (p->leftLink == nullptr) {
		temp = p;
		p = temp->rightLink;
		delete temp;
	} else if (p->rightLink == nullptr) {
		temp = p;
		p = temp->leftLink;
		delete temp;
	} else {
		current = p->leftLink;
		trailCurrent = nullptr;

		while (current->rightLink != nullptr) {
			trailCurrent = current;
			current = current->rightLink;
		}

		p->data = current->data;

		if (trailCurrent == nullptr) {
			p->leftLink = current->leftLink;
		} else {
			trailCurrent->rightLink = current->leftLink;
		}

		delete current;
	}
}

template <class Type>
void BinaryTree<Type>::deleteNode (const Type& item) {
	Node<Type>* current;
	Node<Type>* trailCurrent;
	bool found = false;

	if (root != nullptr) {
		current = root;
		trailCurrent = root;	

		// search for the item
		while (current != nullptr && !found) {
			if (current->data == item) {
				found = true;
			} else {
				trailCurrent = current;
				if (item < current->data) {
					current = current->leftLink;
				} else {
					current = current->rightLink;
				}
			}
		}

		if (found) {
			if (current == root) {
				deleteFromTree(root);
			} else if (trailCurrent->data > item) {
				deleteFromTree(trailCurrent->leftLink);	
			} else {
				deleteFromTree(trailCurrent->rightLink);
			}
		}
	}	
}

#endif