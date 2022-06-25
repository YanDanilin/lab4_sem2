#pragma once
#include <initializer_list>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>



template <class T>
class BinaryTree {
private:
	struct Node {
		T key;
		int height = 0;
		Node* parent = nullptr;
		Node* left = nullptr;
		Node* right = nullptr;
		Node* thread = nullptr;
		Node() {}
		Node(T value, Node* ptr) {
			key = value;
			height = 1;
			left = nullptr;
			right = nullptr;
			parent = ptr;
			thread = nullptr;
		}
		~Node() {}
	};
	struct ThreadInfo {
		Node* main_thread = nullptr;
		bool is_thread = false;
		std::string order;
		ThreadInfo() {}
		~ThreadInfo() {}
	};
	Node* root = nullptr;
	ThreadInfo t_info;

public:
	BinaryTree() {}
	BinaryTree(T* arr, int size);
	BinaryTree(std::initializer_list<T> list);
	BinaryTree(const BinaryTree<T>& btree);
	~BinaryTree();

	bool Find(T item);
	Node* Search(T item);

	T FindMax();

	int GetQuantity();

	void Insert(T item);
	void DeleteByPointer(Node* target);
	void DeleteByValue(T item);
	void PrintNode(Node* node);
	void Print();
	
	BinaryTree<T>* Map(T(*func)(T));
	BinaryTree<T>* Where(bool(*func)(T));
	T Reduce(T(*func)(T, T), const T value);

	void Traversal(void(*visit)(Node*), std::string direction);
	void PrintWithTraversal(std::string direction);
	void Firmware(std::string direction);

	bool operator==(const BinaryTree<T>& another);

	BinaryTree<T>* GetSubtree(T item);
	BinaryTree<T>* Merge(BinaryTree<T>& tree);

	std::string SaveToString(std::string direction);

	T* SaveToArray();
private:
	void Print1(Node* root);

	Node* LocalMax(Node* root);
	Node* LocalMin(Node* root);

	void DeleteSubTree(Node* node);
	void map(BinaryTree<T>& tree, Node* node, T(*func)(T));
	void where(BinaryTree<T>& tree, Node* node, bool(*func)(T));

	int Height(Node* node);
	int BalanceFactor(Node* node);
	void CorrectHeight(Node* node);

	void RightRotation(Node* node);
	void LeftRotation(Node* node);
	void Balance(Node* node);

	void SubTraversal(std::string direction, Node* node, std::queue<Node*>& q);
	void AuxSaveToString(std::string direction, Node* node, std::string& res);
}; 

template <class T> typename BinaryTree<T>::Node* BinaryTree<T>::Search(T item) {
	Node* temp = root;
	while (temp) {
		if (item > temp->key) {
			temp = temp->right;
			continue;
		}
		else if (item < temp->key) {
			temp = temp->left;
			continue;
		}
		else {
			return temp;
		}
	}
	return nullptr;
}

template <class T> bool BinaryTree<T>::Find(T item) {
	Node* tmp = nullptr;
	tmp = Search(item);
	if (tmp) {
		return true;
	} else {
		return false;
	}
}

template <class T> T BinaryTree<T>::FindMax() {
	return LocalMax(root)->key;
}

template <class T> int BinaryTree<T>::GetQuantity() {
	if (!root) {
		return 0;
	}
	if (!t_info.is_thread) {
		Firmware("LNR");
	}
	int res = 0;
	Node* temp = t_info.main_thread;
	while (temp) {
		++res;
		temp = temp->thread;
	}
	return res;
}

template <class T> void BinaryTree<T>::Insert(T item) {
	if (!root) {
		root = new Node(item, nullptr);
	}
	else if (Search(item)) {
		return;
	}
	else {
		t_info.is_thread = false;
		Node* temp = root;
		while (temp) {
			if (item > temp->key) {
				if (temp->right) {
					temp = temp->right;
					continue;
				}
				else {
					temp->right = new Node(item, temp);
					Node* cur = temp->right;
					while (cur) {
						Balance(cur);
						cur = cur->parent;
					}
					return;
				}
			}
			else if (item < temp->key) {
				if (temp->left) {
					temp = temp->left;
					continue;
				}
				else {
					temp->left = new Node(item, temp);
					Node* cur = temp->left;
					while (cur) {
						Balance(cur);
						cur = cur->parent;
					}
					return;
				}
			}
			else {
				throw std::exception("Equal elements cannot be placed in a search tree");
			}

		}
	}
}

template <class T> typename BinaryTree<T>::Node* BinaryTree<T>::LocalMax(Node* node) {
	if (node) {
		while (node->right) {
			node = node->right;
		}
	}
	return node;
}

template <class T> typename BinaryTree<T>::Node* BinaryTree<T>::LocalMin(Node* node) {
	if (node) {
		while (node->left) {
			node = node->left;
		}
	}
	return node;
}

template <class T> void BinaryTree<T>::DeleteByPointer(Node* target) {
	if (target->left && target->right) {
		Node* temp = LocalMax(target->left); //Here we can also use LocalMin(target->right);
		target->key = temp->key;
		DeleteByPointer(temp);
		Node* cur = target;
		while (cur) {
			Balance(cur);
			cur = cur->parent;
		}
		t_info.is_thread = false;
		return;
	}
	else if (target->left) {
		if (!target->parent) {
			root = target->left;
			target->left->parent = nullptr;
		}
		else if (target->parent->right == target) {
			target->parent->right = target->left;
		}
		else if (target->parent->left == target) {
			target->parent->left = target->left;
		}
	}
	else if (target->right) {
		if (!target->parent) {
			root = target->right;
			target->right->parent = nullptr;
		}
		else if (target->parent->left == target) {
			target->parent->left = target->right;
		}
		else if (target->parent->right == target) {
			target->parent->right = target->right;
		}
	}
	else {
		if (!target->parent) {
			root = nullptr;
		}
		else if (target->parent->right == target) {
			target->parent->right = nullptr;
		}
		else {
			target->parent->left = nullptr;
		}
	}
	t_info.is_thread = false;
	delete target;
}

template <class T> void BinaryTree<T>::DeleteByValue(T item) {
	if (!root) {
		return;
	}
	Node* target = Search(item);
	if (target) {
		DeleteByPointer(target);
	}
}

template <class T> void BinaryTree<T>::DeleteSubTree(Node* node) {
	if (node) {
		DeleteSubTree(node->left);
		DeleteSubTree(node->right);
		delete node;
	}
}

template <class T> BinaryTree<T>::~BinaryTree() {
	DeleteSubTree(root);
}

template <class T> BinaryTree<T>::BinaryTree(T* arr, int size) {
	for (int i = 0; i < size; ++i) {
		Insert(arr[i]);
	}
}

template <class T> BinaryTree<T>::BinaryTree(std::initializer_list<T> list) {
	//int size = list.size();
	//T* arr = new T[size];
	//std::copy(list.begin(), list.end(), arr);
	//for (int i = 0; i < size; ++i) {
	//	Insert(arr[i]);
	//}
	//delete[] arr;
	for (auto item : list) {
		Insert(item);
	}
}

template <class T> BinaryTree<T>::BinaryTree(const BinaryTree<T>& btree) {
	if (btree.root) {
		std::queue<Node*> q;
		Node* temp;
		q.push(btree.root);
		while (!q.empty()) {
			temp = q.front();
			Insert(temp->key);
			if (temp->left) {
				q.push(temp->left);
			}
			if (temp->right) {
				q.push(temp->right);
			}
			q.pop();
		}
	}
}

template <class T> void BinaryTree<T>::Print1(Node* node) {
	if (node) {
		std::cout << node->key << '\n';
		std::cout << "----\n";
		Print1(node->left);
		std::cout << "++++\n";
		Print1(node->right);
	}
}

template <class T> void BinaryTree<T>::PrintNode(Node* node) {
	if (node) {
		std::cout << node->key << " ";
	}
}

template <class T> void BinaryTree<T>::Print() {
	Print1(root);
}

template <class T> void BinaryTree<T>::map(BinaryTree<T>& tree, Node* node, T(*func)(T)) {
	if (node) {
		tree.Insert(func(node->key));
		map(tree, node->left, func);
		map(tree, node->right, func);
	}
}

template <class T> BinaryTree<T>* BinaryTree<T>::Map(T(*func)(T)) {
	BinaryTree<T>* res = new BinaryTree<T>;
	res->map(*res, root, func);
	return res;
}

template <class T> void BinaryTree<T>::where(BinaryTree<T>& tree, Node* node, bool(*func)(T)) {
	if (node) {
		if (func(node->key)) {
			Insert(node->key);
		}
		where(tree, node->left, func);
		where(tree, node->right, func);
	}
}

template <class T> BinaryTree<T>* BinaryTree<T>::Where(bool(*func)(T)) {
	BinaryTree<T>* res = new BinaryTree<T>;
	res->where(*res, root, func);
	return res;
}

template <class T> T BinaryTree<T>::Reduce(T(*func)(T, T), const T value) {
	if (root) {
		std::queue<Node*> q;
		Node* temp;
		q.push(root);
		T res = func(root->key, value);
		if (root->left) {
			q.push(root->left);
		}
		if (root->right) {
			q.push(root->right);
		}
		q.pop();
		while (!q.empty()) {
			temp = q.front();
			res = func(temp->key, res);
			if (temp->left) {
				q.push(temp->left);
			}
			if (temp->right) {
				q.push(temp->right);
			}
			q.pop();
		}
		return res;
	}
	else {
		throw std::exception("There is no root");
	}
}

template <class T> int BinaryTree<T>::Height(Node* node) {
	if (node) {
		return node->height;
	}
	else {
		return 0;
	}
}

template <class T> int BinaryTree<T>::BalanceFactor(Node* node) {
	if (node) {
		return Height(node->right) - Height(node->left);
	}
	else {
		return 0;
	}
}

template <class T> void BinaryTree<T>::CorrectHeight(Node* node) {
	if (node) {
		int lh = Height(node->left);
		int rh = Height(node->right);
		if (lh > rh) {
			node->height = lh + 1;
		}
		else {
			node->height = rh + 1;
		}
	}
}

template <class T> void BinaryTree<T>::RightRotation(Node* node) {
	if (node) {
		if (node->parent) {
			if (node->parent->right == node) {
				node->parent->right = node->left;
			}
			else {
				node->parent->left = node->left;
			}
		}
		if (root == node) {
			root = node->left;
		}
		Node* buf = node->left;
		buf->parent = node->parent;
		node->parent = buf;
		node->left = buf->right;
		if (buf->right) {
			buf->right->parent = node;
		}
		buf->right = node;
		CorrectHeight(buf);
		CorrectHeight(node);
	}
}

template <class T> void BinaryTree<T>::LeftRotation(Node* node) {
	if (node) {
		if (node->parent) {
			if (node->parent->right == node) {
				node->parent->right = node->right;
			}
			else {
				node->parent->left = node->right;
			}
		}
		if (root == node) {
			root = node->right;
		}
		Node* buf = node->right;
		buf->parent = node->parent;
		node->parent = buf;
		node->right = buf->left;
		if (buf->left) {
			buf->left->parent = node;
		}
		buf->left = node;
		CorrectHeight(buf);
		CorrectHeight(node);
	}
}

template <class T> void BinaryTree<T>::Balance(Node* node) {
	CorrectHeight(node);
	if (BalanceFactor(node) == 2) {
		if (BalanceFactor(node->right) < 0) {
			RightRotation(node->right);
		}
		LeftRotation(node);
		return;
	}
	if (BalanceFactor(node) == -2) {
		if (BalanceFactor(node->left) > 0) {
			LeftRotation(node->left);
		}
		RightRotation(node);
		return;
	}
}

template <class T> void BinaryTree<T>::SubTraversal(std::string direction, Node* node, std::queue<Node*>& q) {
	if (!node) {
		return;
	}
	for (int i = 0; i < 3; ++i) {
		switch (direction[i]) {
		case 'N':
			q.push(node);
			break;
		case 'L':
			SubTraversal(direction, node->left, q);
			break;
		case 'R':
			SubTraversal(direction, node->right, q);
			break;
		}
	}
}

template <class T> void BinaryTree<T>::Traversal(void (*visit)(Node*), std::string direction) {
	/*if (!root) {
		return;
	}
	std::queue<Node*> q;
	for (int i = 0; i < 3; ++i) {
		switch (direction[i]) {
		case 'N':
			q.push(root);
			break;
		case 'L':
			SubTraversal(direction, root->left, q);
			break;
		case 'R':
			SubTraversal(direction, root->right, q);
			break;
		}
	}
	while (!q.empty()) {
		visit(q.front());
		q.pop();
	}*/
	if (!t_info.is_thread || t_info.order != direction) {
		Firmware(direction);
	}
	Node* temp = t_info.main_thread;
	while (temp) {
		visit(temp);
		temp = temp->thread;
	}
}

template <class T> void BinaryTree<T>::PrintWithTraversal(std::string direction) {
	if (!t_info.is_thread || t_info.order != direction) {
		/*if (!root) {
			return;
		}
		std::queue<Node*> q;
		for (int i = 0; i < 3; ++i) {
			switch (direction[i]) {
			case 'N':
				q.push(root);
				break;
			case 'L':
				SubTraversal(direction, root->left, q);
				break;
			case 'R':
				SubTraversal(direction, root->right, q);
				break;
			}
		}
		while (!q.empty()) {
			PrintNode(q.front());
			q.pop();
		}*/
		Firmware(direction);
	}
	Node* temp = t_info.main_thread;
	while (temp) {
		PrintNode(temp);
		temp = temp->thread;
	}
}

template <class T> void BinaryTree<T>::Firmware(std::string direction) {
	if (!root) {
		return;
	}
	std::queue<Node*> q;
	for (int i = 0; i < 3; ++i) {
		switch (direction[i]) {
		case 'N':
			q.push(root);
			break;
		case 'L':
			SubTraversal(direction, root->left, q);
			break;
		case 'R':
			SubTraversal(direction, root->right, q);
			break;
		}
	}
	Node* temp = q.front();
	q.pop();
	t_info.main_thread = temp;
	Node* next;
	while (!q.empty()) {
		next = q.front();
		temp->thread = next;
		temp = next;
		q.pop();
	}
	temp->thread = nullptr;
	t_info.is_thread = true;
	t_info.order = direction;
}

template <class T> bool BinaryTree<T>::operator==(const BinaryTree<T>& another) {
	Firmware("NLR");
	BinaryTree<T> copy = another;
	copy.Firmware("NLR");
	Node* temp1 = t_info.main_thread;
	Node* temp2 = copy.t_info.main_thread;
	while (temp1 || temp2) {
		if (temp1 && !temp2 || !temp1 && temp2) {
			return false;
		}
		if (temp1->key != temp2->key) {
			return false;
		}
		temp1 = temp1->thread;
		temp2 = temp2->thread;
	}
	return true;
}

template <class T> BinaryTree<T>* BinaryTree<T>::GetSubtree(T item) {
	Node* new_root = Search(item);
	if (!new_root) {
		return new BinaryTree<T>;
	}
	BinaryTree<T>* res = new BinaryTree<T>;
	std::queue<Node*> q;
	SubTraversal("NLR", new_root, q);
	Node* temp;
	while (!q.empty()) {
		temp = q.front();
		res->Insert(temp->key);
		q.pop();
	}
	return res;
}

template <class T> BinaryTree<T>* BinaryTree<T>::Merge(BinaryTree<T>& tree) {
	BinaryTree<T>* res = new BinaryTree<T>(tree);
	Firmware("NLR");
	Node* temp = t_info.main_thread;
	while (temp) {
		res->Insert(temp->key);
		temp = temp->thread;
	}
	return res;
}

template <class T> std::string BinaryTree<T>::SaveToString(std::string direction) {
	std::string res = "";
	if (!root) {
		return res;
	}
	for (int i = 0; i < 3; ++i) {
		switch (direction[i]) {
		case 'N':
			res = res + '{' + std::to_string(root->key) + '}';
			break;
		case 'L':
			if (root->left) {
				res = res + '(';
				AuxSaveToString(direction, root->left, res);
				res = res + ')';
			}
			break;
		case 'R':
			if (root->right) {
				res = res + '[';
				AuxSaveToString(direction, root->right, res);
				res = res + ']';
			}
			break;
		}
	}
	return res;
}

template <class T> void BinaryTree<T>::AuxSaveToString(std::string direction, Node* node, std::string& res) {
	if (!node) {
		return;
	}
	for (int i = 0; i < 3; ++i) {
		switch (direction[i]) {
		case 'N':
			res = res + std::to_string(node->key);
			break;
		case 'L':
			if (node->left) {
				res = res + '(';
				AuxSaveToString(direction, node->left, res);
				res = res + ')';
			}
			break;
		case 'R':
			if (node->right) {
				res = res + '[';
				AuxSaveToString(direction, node->right, res);
				res = res + ']';
			}
			break;
		}
	}
}

template <class T> T* BinaryTree<T>::SaveToArray() {
	Firmware("LNR");
	Node* temp = t_info.main_thread;
	int size = GetQuantity();
	T* array = new T[size];
	int i = 0;
	while (temp) {
		array[i] = temp->key;
		temp = temp->thread;
		++i;
	}
	return array;
}
