#pragma once

#include "PriorityQueue.h"

#include <iostream>
#include <vector>

int redouble(int a) {
	a *= 2;
	return a;
}

bool positive(int a) {
	if (a > 0) {
		return true;
	}
	else {
		return false;
	}
}
int sum(int a, int b) {
	return a + b;
}

void OperationListTree(int& var) {
	std::cout << "==========================\n";
	std::cout << "Choose operation : \n 1. Create a tree\n 2. Insert in a tree\n 3. Use map function\n 4. Use reduce function\n";
	std::cout << " 5. Use where function\n 6. Delete element by key\n 7. Get subtree by key\n 8. Merge\n 9. Output in console\n 10. Exit\n> ";
	std::cin >> var;
}

int ChooseNumber(size_t range, std::string obj) {
	std::cout << "Choose " << obj << " number in a list of trees\n> ";
	int index = -1;
	std::cin >> index;
	while (index < 1 || index > range) {
		std::cout << "Wrong number... Try again\n> ";
		std::cin >> index;
	}
	return index;
}

template <typename T>
void CreateTree(std::vector<BinaryTree<T>*>& v) {
	BinaryTree<T>* new_tree = new BinaryTree<T>;
	v.push_back(new_tree);
}

template <typename T>
void InsertInTree(std::vector<BinaryTree<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one tree before\n";
		return;
	}
	int index = ChooseNumber(v.size(), "tree");
	BinaryTree<T>* temp = v[index - 1];
	int var = 1;
	do {
		switch (var) {
		case 1:
			int data;
			std::cout << "Enter value:\n> ";
			std::cin >> data;
			temp->Insert(data);
			std::cout << "---------------\n  1. Insert one more\n  2. Stop\n> ";
			std::cin >> var;
			break;
		case 2:
			var = 0;
			break;
		default:
			std::cout << "Try again ...\n> ";
			std::cout << "---------------\n  1. Insert one more\n  2. Stop\n> ";
			std::cin >> var;
		}
	} while (var);
}

template <typename T>
void Output(std::vector<BinaryTree<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one tree\n";
		return;
	}
	int index = ChooseNumber(v.size(), "tree");
	std::cout << "Enter order of traversal(example: LNR)\n> ";
	std::string order;
	std::cin >> order;
	while (order.size() != 3) {
		std::cout << "Try again...";
		std::cin >> order;
	}
	BinaryTree<T>* temp = v[index - 1];
	std::cout << temp->SaveToString(order) << '\n';
}

template <typename T>
void Destruct(std::vector<BinaryTree<T>*>& v) {
	size_t size = v.size();
	for (int i = 0; i < size; ++i) {
		delete v[i];
	}
}

template <typename T>
void UseMap(std::vector<BinaryTree<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one tree\n";
		return;
	}
	int index = ChooseNumber(v.size(), "tree");
	std::cout << "Multiplying by 2 is used as function by default (just for test)\n";
	BinaryTree<T>* temp = v[index - 1];
	BinaryTree<T>* res = temp->Map(redouble);
	v.push_back(res);
}

template <typename T>
void UseReduce(std::vector<BinaryTree<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one tree\n";
		return;
	}
	int index = ChooseNumber(v.size(), "tree");
	std::cout << "Sum of all elements is used as function by default (just for test)\n";
	BinaryTree<T>* temp = v[index - 1];
	int res = temp->Reduce(sum, 0);
	std::cout << res << '\n';
}

template <typename T>
void UseWhere(std::vector<BinaryTree<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one tree\n";
		return;
	}
	int index = ChooseNumber(v.size(), "tree");
	std::cout << "Selecting positive numbers is used as function by default (just for test)\n";
	BinaryTree<T>* temp = v[index - 1];
	BinaryTree<T>* res = temp->Where(positive);
	v.push_back(res);
}

template <typename T>
void DeleteElement(std::vector<BinaryTree<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one tree\n";
		return;
	}
	int index = ChooseNumber(v.size(), "tree");
	BinaryTree<T>* temp = v[index - 1];
	int data;
	std::cout << "Enter value:\n> ";
	std::cin >> data;
	temp->DeleteByValue(data);
}

template <typename T>
void Subtree(std::vector<BinaryTree<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one tree\n";
		return;
	}
	int index = ChooseNumber(v.size(), "tree");
	BinaryTree<T>* temp = v[index - 1];
	int data;
	std::cout << "Enter value:\n";
	std::cin >> data;
	BinaryTree<T>* res = temp->GetSubtree(data);
	v.push_back(res);
}

template <typename T>
void Merging(std::vector<BinaryTree<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one tree\n";
		return;
	}
	std::cout << "What trees do you want to merge?";
	int index1 = ChooseNumber(v.size(), "tree");
	int index2 = ChooseNumber(v.size(), "tree");
	BinaryTree<T>* temp1 = v[index1 - 1];
	BinaryTree<T>* temp2 = v[index2 - 1];
	BinaryTree<T>* result = temp1->Merge(*temp2);
	v.push_back(result);
}

void menu_tree_int() {
	std::vector<BinaryTree<int>*> v;
	int var = 1;
	while (var) {
		OperationListTree(var);
		switch (var) {
		case 1:
			CreateTree(v);
			break;
		case 2:
			InsertInTree(v);
			break;
		case 3:
			UseMap(v);
			break;
		case 4:
			UseReduce(v);
			break;
		case 5:
			UseWhere(v);
			break;
		case 6:
			DeleteElement(v);
			break;
		case 7:
			Subtree(v);
			break;
		case 8:
			Merging(v);
			break;
		case 9:
			Output(v);
			break;
		case 10:
			Destruct(v);
			var = 0;
			break;
		default:
			std::cout << "Wrong option number... Try again\n> ";
		}
	}
}

void OperationList(int& var) {
	std::cout << "==========================\n";
	std::cout << "Choose operation : \n 1. Work with trees\n 2. Work with priority queues\n 3. Exit\n> ";
	std::cin >> var;
}

void OperationListPQueue(int& var) {
	std::cout << "==========================\n";
	std::cout << "Choose operation : \n 1. Create a queue\n 2. Push an element\n 3. Use map function\n 4. Use reduce function\n";
	std::cout << " 5. Use where function\n 6. Pop an element\n 7. Get subqueue\n 8. Check if subqueue\n 9. Merge\n 10. Output in console\n 11. Exit\n> ";
	std::cin >> var;
}

template <typename T>
void CreateQueue(std::vector<PriorityQueue<T>*>& v) {
	PriorityQueue<T>* new_queue = new PriorityQueue<T>;
	v.push_back(new_queue);
}

template <typename T>
void PushInQueue(std::vector<PriorityQueue<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one queue before\n";
		return;
	}
	int index = ChooseNumber(v.size(), "queue");
	PriorityQueue<T>* temp = v[index - 1];
	int var = 1;
	do {
		switch (var) {
		case 1:
			int data;
			std::cout << "Enter value:\n> ";
			std::cin >> data;
			temp->Push(data);
			std::cout << "---------------\n  1. Insert one more\n  2. Stop\n> ";
			std::cin >> var;
			break;
		case 2:
			var = 0;
			break;
		default:
			std::cout << "Try again ...\n> ";
			std::cout << "---------------\n  1. Insert one more\n  2. Stop\n> ";
			std::cin >> var;
		}
	} while (var);
}

template <typename T>
void UseMapPQ(std::vector<PriorityQueue<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one queue\n";
		return;
	}
	int index = ChooseNumber(v.size(), "queue");
	std::cout << "Multiplying by 2 is used as function by default (just for test)\n";
	PriorityQueue<T>* temp = v[index - 1];
	PriorityQueue<T>* res = temp->Map(redouble);
	v.push_back(res);
}

template <typename T>
void UseReducePQ(std::vector<PriorityQueue<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one queue\n";
		return;
	}
	int index = ChooseNumber(v.size(), "queue");
	std::cout << "Sum of all elements is used as function by default (just for test)\n";
	PriorityQueue<T>* temp = v[index - 1];
	int res = temp->Reduce(sum, 0);
	std::cout << res << '\n';
}

template <typename T>
void UseWherePQ(std::vector<PriorityQueue<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one queue\n";
		return;
	}
	int index = ChooseNumber(v.size(), "queue");
	std::cout << "Selecting positive numbers is used as function by default (just for test)\n";
	PriorityQueue<T>* temp = v[index - 1];
	PriorityQueue<T>* res = temp->Where(positive);
	v.push_back(res);
}

template <typename T>
void PopEl(std::vector<PriorityQueue<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one queue\n";
		return;
	}
	int index = ChooseNumber(v.size(), "queue");
	PriorityQueue<T>* temp = v[index - 1];
	if (temp->Size()) {
		temp->Pop();
	} else {
		std::cout << "This queue is empty\n";
	}
}

template <typename T>
void Subqueue(std::vector<PriorityQueue<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one queue\n";
		return;
	}
	int index = ChooseNumber(v.size(), "queue");
	PriorityQueue<T>* temp = v[index - 1];
	int start;
	int end;
	std::cout << "Enter index to begin with:\n";
	std::cin >> start;
	std::cout << "Enter ending index:\n";
	std::cin >> end;
	PriorityQueue<T>* res = temp->GetSubqueue(start, end);
	v.push_back(res);
}

template <typename T>
void IfSubqueuePQ(std::vector<PriorityQueue<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one queue\n";
		return;
	}
	std::cout << "Choose subqueue:\n";
	int index1 = ChooseNumber(v.size(), "queue");
	std::cout << "In what queue to check subqueue?\n";
	int index2 = ChooseNumber(v.size(), "queue");
	PriorityQueue<T>* temp1 = v[index1 - 1];
	PriorityQueue<T>* temp2 = v[index2 - 1];
	if (temp2->IfSubqueue(*temp1)) {
		std::cout << "Subqueue\n";
	} else {
		std::cout << "Not subqueue\n";
	}
}

template <typename T>
void MergingPQ(std::vector<PriorityQueue<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one queue\n";
		return;
	}
	std::cout << "What queues do you want to merge?\n";
	int index1 = ChooseNumber(v.size(), "queue");
	int index2 = ChooseNumber(v.size(), "queue");
	PriorityQueue<T>* temp1 = v[index1 - 1];
	PriorityQueue<T>* temp2 = v[index2 - 1];
	PriorityQueue<T>* result = temp1->Merge(*temp2);
	v.push_back(result);
}

template <typename T>
void OutputPQ(std::vector<PriorityQueue<T>*>& v) {
	if (v.empty()) {
		std::cout << "Create at least one queue\n";
		return;
	}
	int index = ChooseNumber(v.size(), "queue");
	PriorityQueue<T>* temp = v[index - 1];
	if (temp->Size()) {
		temp->Print();
	} else {
		std::cout << "This queue is empty\n";
	}
}

template <typename T>
void DestructPQ(std::vector<PriorityQueue<T>*>& v) {
	size_t size = v.size();
	for (int i = 0; i < size; ++i) {
		delete v[i];
	}
}

void menu_pqueue_int() {
	std::vector<PriorityQueue<int>*> v;
	int var = 1;
	while (var) {
		OperationListPQueue(var);
		switch (var) {
		case 1:
			CreateQueue(v);
			break;
		case 2:
			PushInQueue(v);
			break;
		case 3:
			UseMapPQ(v);
			break;
		case 4:
			UseReducePQ(v);
			break;
		case 5:
			UseWherePQ(v);
			break;
		case 6:
			PopEl(v);
			break;
		case 7:
			Subqueue(v);
			break;
		case 8:
			IfSubqueuePQ(v);
			break;
		case 9:
			MergingPQ(v);
			break;
		case 10:
			OutputPQ(v);
			break;
		case 11:
			var = 0;
			DestructPQ(v);
			break;
		default:
			std::cout << "Wrong option... Try again\n> ";
		}
	}
}

void general_menu() {
	int var = 1;
	while (var) {
		OperationList(var);
		switch (var) {
		case 1:
			menu_tree_int();
			break;
		case 2:
			menu_pqueue_int();
			break;
		case 3:
			var = 0;
			break;
		default:
			std::cout << "Wrong option... Try again\n> ";
		}
	}
}