#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int rollNumber;
	string name;
	Node* next;
};

class CircularLinkedList {
private:
	Node* LAST;
public:
	CircularLinkedList() {
		LAST = NULL;
	}
	void addNode();
	bool search(int rollno, Node** widyaningrum, Node** anggia);
	bool listEmpty();
	bool delNode();
	void traverse();
};

void CircularLinkedList::addNode() {
	int rollno;
	string name;

	cout << "\nEnter roll number: ";
	cin >> rollno;
	cout << "Enter name: ";
	cin.ignore();
	getline(cin, name);

	Node* newnode = new Node();
	newnode->rollNumber = rollno;
	newnode->name = name;

	// a) beginning of the list
	if (LAST == NULL) {
		newnode->next = newnode;
		LAST = newnode;
	}
	else {
		Node* successor = LAST->next;

		// b) Between two nodes in the list
		Node* anggia = successor;
		Node* widyaningrum = NULL;
		while (anggia != LAST && anggia->rollNumber < rollno) {
			widyaningrum = anggia;
			anggia = anggia->next;
		}

		widyaningrum->next = newnode;
		newnode->next = anggia;

		// c) End of the list
		if (anggia == successor && anggia->rollNumber < rollno) {
			LAST = newnode;
		}
	}


	cout << "Record added successfully!\n";
}

bool CircularLinkedList::search(int rollno, Node** widyaningrum, Node** anggia) {
	*widyaningrum = LAST->next;
	*anggia = LAST->next;

	while (*anggia != LAST) {
		if (rollno == (*anggia)->rollNumber) {
			return true;
		}
		*widyaningrum = *anggia;
		*anggia = (*anggia)->next;
	}

	if (rollno == LAST->rollNumber) {
		return true;
	}
	else {
		return false;
	}
}

bool CircularLinkedList::listEmpty() {
	return LAST == NULL;
}

bool CircularLinkedList::delNode() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
		return false;
	}

	int rollno;
	cout << "\nEnter the roll number to delete: ";
	cin >> rollno;

	Node* widyaningrum = NULL;
	Node* anggia = NULL;

	if (search(rollno, &widyaningrum, &anggia)) {
		// a) Beginning of the list
		if (anggia == LAST->next) {
			// If LAST points to itself
			if (LAST == LAST->next) {
				LAST = NULL;
				delete anggia;
				return true;
			}

			LAST->next = anggia->next;
			delete anggia;
			return true;
		}
		else if (anggia == LAST) { // b) End of the list
			widyaningrum->next = anggia->next;
			LAST = widyaningrum;
			delete anggia;
			return true;
		}
		else { // c) Between two nodes in the list
			widyaningrum->next = anggia->next;
			delete anggia;
			return true;
		}
	}
	else {
		cout << "Record not found!\n";
		return false;
	}
}

void CircularLinkedList::traverse() {
	if (listEmpty()) {
		cout << "\nList is empty\n";
	}
	else {
		cout << "\nRecords in the list are:\n";
		Node* anggiaNode = LAST->next;
		while (anggiaNode != LAST) {
			cout << anggiaNode->rollNumber << " " << anggiaNode->name << endl;
			anggiaNode = anggiaNode->next;
		}
		cout << LAST->rollNumber << " " << LAST->name << endl;
	}
}

int main() {
	CircularLinkedList obj;

	while (true) {
		try {
			cout << "\nMenu" << endl;
			cout << "1. Add a record to the list" << endl;
			cout << "2. Delete a record from the list" << endl;
			cout << "3. View all the records in the list" << endl;
			cout << "4. Exit" << endl;
			cout << "\nEnter your choice (1-4): ";
			char ch;
			cin >> ch;

			switch (ch) {
			case '1': {
				obj.addNode();
				break;
			}
			case '2': {
				obj.delNode();
				break;
			}
			case '3': {
				obj.traverse();
				break;
			}
			case '4': {
				return 0;
			}
			default: {
				cout << "Invalid option" << endl;
				break;
			}
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	return 0;
}
