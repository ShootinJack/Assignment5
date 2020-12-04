#include "Interface.h"



Interface::Interface() // default constructor looks for the two database files
{
	stdCount = -1;
	facCount = -1;
	openFileF();
	openFileS();

}


Interface::~Interface()
{
}

void Interface::openFileS()								// This function goes through the files and adds the students from the previous session
{
	inFile.open("studentTable.txt");
	if (inFile.good()) {
		int lastId = -1;
		while (inFile.good()) {
			Student *tempStudent = new Student();
			getline(inFile, name, ',');
			inFile >> id;
			getline(inFile, standing, ','); 
			getline(inFile, major, ',');
			inFile >> gpa >> advisorId;
			inFile.ignore();
			tempStudent->setName(name);
			tempStudent->setId(id);
			tempStudent->setStanding(standing);
			tempStudent->setMajor(major);
			tempStudent->setGpa(gpa);
			tempStudent->setAdvisorId(advisorId);
			if (tempStudent->getId() != lastId) {
				studentTree.insertNode(tempStudent);
				lastId = tempStudent->getId();
				stdCount++;
			}
			
		}
		inFile.close();
	}
	else {
		cout << "Database is empty\n";				// if the database is empty then it will create a new file, it will create a root student to keep tree balanced
		outFile.open("studentTable.txt");
		outFile << "Root Node," << 5000 << "God," << "CloudStuff," << 5.5 << " " << 2424 << endl;
		outFile.close();
		Student *tempStudent = new Student();
		tempStudent->setName("Root Node");
		tempStudent->setId(5000);
		tempStudent->setStanding("God");
		tempStudent->setMajor("CloudStuff");
		tempStudent->setGpa(5.5);
		tempStudent->setAdvisorId(2424);
		studentTree.insertNode(tempStudent);
		cout << "Student Database Ready\n";
	}
}

void Interface::openFileF() // This function opens the file and reloads the old faculty members into the database
{
	inFile.open("facultyTable.txt");
	if (inFile.good()) {
		int lastId = -1;
		while (inFile.good()) {
			Faculty *tempFac = new Faculty();
			getline(inFile, name, ',');
			inFile >> id;
			getline(inFile, standing, ',');
			getline(inFile, department, ',');
			inFile >> numOfStuds;
			inFile.ignore();
			if (numOfStuds != 0) {
				for (int i = 0; i < numOfStuds; ++i) {
					inFile >> studNum;
					tempFac->addStudent(studNum);
				}
				inFile.ignore();
			}
			tempFac->setName(name);
			tempFac->setId(id);
			tempFac->setStanding(standing);
			tempFac->setDepartment(department);
			if (tempFac->getId() != lastId) {
				facultyTree.insertNode(tempFac);
				lastId = tempFac->getId();
				++facCount;
			}

		}
		inFile.close();
	}
	else {								//if there is no database file then it will create a new one, it will create a root faculty member to try and keep the tree balanced
		++facCount;
		cout << "Database is empty\n";
		outFile.open("facultyTable.txt");
		outFile << "Root Node, " << 11000 << "GOATteacher," << "DEPARTMENT OF AWESOME, " << 0 << " " << endl;
		outFile.close();
		Faculty *tempFac = new Faculty();
		tempFac->setName("Root Node");
		tempFac->setId(11000);
		tempFac->setStanding("GOATteacher");
		tempFac->setDepartment("DEPARTMENT OF AWESOME");
		tempFac->setNumOfStuds(0);
		facultyTree.insertNode(tempFac);
		cout << "Faculty Database ready\n";
	}
}

void Interface::printMenu() // this is the menu for the database
{
	cout << "1. Print Students\n";
	cout << "2. Print Faculty\n";
	cout << "3. Find Students\n";
	cout << "4. Find Faculty\n";
	cout << "5. Find Students Advisor\n";
	cout << "6. Print Faculty Members Advisees\n";
	cout << "7. Add New Student\n";
	cout << "8. Delete Student\n";
	cout << "9. Add New Faculty\n";
	cout << "10. Delete Faculty Member\n";
	cout << "11. Change Student's Advisor\n";
	cout << "12. Remove Advisee From Faculty Member\n";
	cout << "13. Rollback\n";
	cout << "0. Quit\n";
	cout << "Enter Selection: ";
	setInput();
}

void Interface::setInput() // this function takes in the users input
{
	bool check = true;
	while (check) {
		cin >> input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Please enter a number listed on the menu.\n";
		}
		else if (input >= 0 && input <= 13) {
			check = false;
		}
		else {
			cout << "Please enter a number listed on the menu.\n";
		}
	}
	cout << endl;
	switch (input) {			// the switch directs the program to the necessary function, then loops it back to the menu
	case 1:
		printStudents(); // works
		printMenu();
		break;
	case 2:
		printFaculty(); // works
		printMenu();
		break;
	case 3:
		findStudent(); // works
		printMenu();
		break;
	case 4:
		findFaculty(); // works
		printMenu();
		break;
	case 5:
		displayAdvisor(); // works
		printMenu();
		break;
	case 6:
		displayAdvisees(); // works
		printMenu();
		break;
	case 7: 
		if (!facultyTree.isFaculty()) {		// works
			newStudent();
			printMenu();
		}
		else {
			cout << "\nA student cannot be added unless there is faculty.\n\n";
			printMenu();
		}
		break;
	case 8:
		deleteStudent(); // works
		printMenu();
		break;
	case 9:
		newFaculty(); // works
		printMenu();
		break;
	case 10:
		deleteFaculty(); // works
		printMenu();
		break;
	case 11:
		changeStudentsAdvisor(); // works
		printMenu();
		break;
	case 12:
		removeAdvisee(); // works
		printMenu();
		break;
	case 13:
		rollBack();
		printMenu();
		break;
	}
}

void Interface::newStudent() // this function adds a new student to the database
{
	Student *tempStudent = new Student();
	bool check = true, check2 = true;
	int selection;
	while (check) {
		check2 = true;
		cout << "Enter student name: ";
		cin.ignore();
		getline(cin, name);
		if (check) {
			while (check2) {
				cout << "Is " << name << " the name you wish to enter?\n";
				cout << "1) Yes\n2) No\nEnter Selection: ";
				cin >> selection;
				if (cin.fail()) {
					cout << "Use correct data type.\nPush 1 or 2 it's not hard.\n";
					cin.clear();
					cin.ignore();
				}
				else if (selection == 1) {
					check = false;
					check2 = false;
				}
				else if (selection == 2) {
					check2 = false;
				}
			}
		}
	}
	tempStudent->setName(name);

	srand(time(NULL));
	id = 5000;
	while (studentTree.searchNode(id)) {
		id = rand() % 9000 + 1000;
	}
	cout << name << "'s Student ID is " << id << endl;
	tempStudent->setId(id);

	cout << "Set Student Standing: ";
	cin.ignore();
	getline(cin, standing);
	tempStudent->setStanding(standing);

	cout << "Set Major: ";
	getline(cin, major);
	tempStudent->setMajor(major);

	check = true;
	while (check) {
		cout << "Set GPA: ";
		cin >> gpa;
		if (cin.fail()) {
			cout << "Use correct data type.\nEnter a number.\n";
			cin.clear();
			cin.ignore();
		}
		else {
			check = false;
		}
	}
	tempStudent->setGpa(gpa);

	check = true;
	while (check) {
		cout << "Select an advisor from the list. Enter their ID number to assign it to the student\n";
		facultyTree.printAdvisors();
		cout << "Select Advisor: ";				
		cin >> advisorId;
		if (cin.fail()) {
			cout << "Use correct data type.\nEnter a number.\n";
			cin.clear();
			cin.ignore();
		}
		else if (facultyTree.searchNode(advisorId)) {
			Faculty *tempFac = new Faculty();
			tempFac = facultyTree.getFaculty(advisorId);
			tempFac->addStudent(id);
			cout << tempFac->getName() << " has been added as an advisor.\n";
			facultyTree.outputToFile();
			check = false;
		}
		else {
			cout << "Faculty Member doesnt exist\n";
		}
	}

	tempStudent->setAdvisorId(advisorId); // after the information is collected the node is pushed into the tree, then the data is also copied to the file
	studentTree.insertNode(tempStudent);
	outFile.open("studentTable.txt", ios_base::app);
	outFile << name << "," << id << standing << "," << major << "," << gpa << " " << advisorId << endl;
	outFile.close();
	Undo node;
	node.setType(1);
	node.setId(id);
	rollBackList.push(node);
}

void Interface::newFaculty()		// This function creates a new faculty member
{
	Faculty *tempFac = new Faculty();
	bool check = true, check2 = true;
	int selection;
	while (check) {
		check2 = true;
		cout << "Enter faculty name: ";
		cin.ignore();
		getline(cin, name);
		if (check) {
			while (check2) {
				cout << "Is " << name << " the name you wish to enter?\n";
				cout << "1) Yes\n2) No\nEnter Selection: ";
				cin >> selection;
				if (cin.fail()) {
					cout << "Use correct data type.\nPush 1 or 2 it's not hard.\n";
					cin.clear();
					cin.ignore();
				}
				else if (selection == 1) {
					check = false;
					check2 = false;
				}
				else if (selection == 2) {
					check2 = false;
				}
			}
		}
	}
	tempFac->setName(name);

	srand(time(NULL));
	id = 11000;
	while (facultyTree.searchNode(id)) {
		id = rand() % 2000 + 10000;
	}
	cout << name << "'s Faculty ID is " << id << endl;
	tempFac->setId(id);

	cout << "Set Faculty's Level: ";
	cin.ignore();
	getline(cin, standing);
	tempFac->setStanding(standing);

	cout << "Set Department: ";
	getline(cin, department);
	tempFac->setDepartment(department);
	tempFac->setNumOfStuds(0);
	facultyTree.insertNode(tempFac);		// after the information is collected the faculty member is pushed into the tree, then a copy is made to the database

	outFile.open("facultyTable.txt", ios_base::app);
	outFile << name << "," << id << standing << "," << department << ", " << 0 << endl;
	outFile.close();
	facCount++;
	Undo node;
	node.setType(2);
	node.setId(id);
	rollBackList.push(node);
}

void Interface::printStudents() // this function prints the students
{
	studentTree.printTree();
}

void Interface::printFaculty() // this function prints the faculty members
{
	facultyTree.printTree();
}

void Interface::findStudent() // this function searches the tree and checks if there is a student in the tree then prints the results
{
	bool check = true;
	while (check)
	{
		cout << "\nEnter Student ID: ";
		cin >> id;
		if (cin.fail()) {
			cout << "Please enter an integer.\n";
			cin.clear();
			cin.ignore();
		}
		else {
			check = false;
			if (studentTree.searchNode(id)) {
				cout << studentTree.getStudent(id);
			}
			else {
				cout << "\nThis student does not exist.\n\n";
			}
		}
	}
}

void Interface::findFaculty() // this function searches the faculty tree to check if the faculty member is in there
{
	bool check = true;
	while (check)
	{
		cout << "\nEnter Faculty Member's ID: ";
		cin >> id;
		if (cin.fail()) {
			cout << "Please enter an integer.\n";
			cin.clear();
			cin.ignore();
		}
		else {
			check = false;
			if (facultyTree.searchNode(id)) {
				cout << facultyTree.getFaculty(id);
			}
			else {
				cout << "\nThis faculty member does not exist.\n\n";
			}
		}
	}
}

void Interface::deleteStudent() // this function finds the student in the tree then deletes the information
{
	Undo node;
	bool check = true;
	while (check)
	{
		cout << "\nEnter Student ID: ";
		cin >> id;
		if (cin.fail()) {
			cout << "Please enter an integer.\n";
			cin.clear();
			cin.ignore();
		}
		else {
			check = false;
			if (id == 5000) {
				cout << "\nThis student does not exist\n\n";		// this stops the user from deleting the root
			}
			else if (studentTree.searchNode(id)) {
				facultyTree.getFaculty(studentTree.getStudent(id)->getAdvisorId())->removeStudent(id);		// this part of the code sets up the rollback feature
				facultyTree.outputToFile();
				node.setType(3);
				node.setName(studentTree.getStudent(id)->getName());
				node.setId(studentTree.getStudent(id)->getId());
				node.setStanding(studentTree.getStudent(id)->getStanding());
				node.setStr2(studentTree.getStudent(id)->getMajor());
				node.setGpa(studentTree.getStudent(id)->getGpa());
				node.setAdvisorId(studentTree.getStudent(id)->getAdvisorId());
				rollBackList.push(node);
				if (studentTree.deleteNode(id)) {	// this if the student is deleted it is acknowledged here
					cout << "\nStudent Deleted\n\n";
					stdCount--;
				}
				else {
					cout << "\nNot Deleted\n\n";
					rollBackList.pop();
				}
				studentTree.outputToFile();
			}
			else {
				cout << "\nThis student does not exist.\n\n";
			}
		}
	}
}

void Interface::deleteFaculty() // this function deletes faculty members from the tree
{
	bool check = true;
	while (check)
	{
		Undo node;
		cout << "\nEnter Faculty Member's ID: ";
		cin >> id;
		if (cin.fail()) {
			cout << "Please enter an integer.\n";
			cin.clear();
			cin.ignore();
		}
		else {
			check = false;
			if (facCount == 1) {			// this stops the user from deleting the last faculty member
				cout << "You can't delete the only faculty member!\n";
				cout << "Add a new one first then delete\n";
			}
			else if (id == 11000) {
				cout << "\nThat faculty member does not exist.\n\n";
			}
			else if (facultyTree.searchNode(id)) {		// this sets up the node and pushes it into the rollback list
				int num = facultyTree.getFaculty(id)->getNumOfStuds();
				node.setType(4);
				node.setName(facultyTree.getFaculty(id)->getName());
				node.setId(id);
				node.setStanding(facultyTree.getFaculty(id)->getStanding());
				node.setStr2(facultyTree.getFaculty(id)->getDepartment());
				node.setSize(num);
				node.setList(facultyTree.getFaculty(id)->getList());
				bool check = true;
				if (num > 0) {
					while (check) {			// this transfers the faculty members advisees another faculty member
						cout << "Select an advisor to transfer " << facultyTree.getFaculty(id)->getName() << "'s advisees to.\n";
						facultyTree.printAdvisors();
						cout << "Select Advisor: ";
						cin >> advisorId;
						if (cin.fail()) {
							cout << "Use correct data type.\nEnter a number.\n";
							cin.clear();
							cin.ignore();
						}
						else if (advisorId == facultyTree.getFaculty(id)->getId()) {
							cout << "You can't select the same faculty member.\nTry again.\n";
						}
						else if (!facultyTree.searchNode(advisorId)) {
							cout << "\nThat faculty member does not exist\n\n";
						}
						else {
							check = false;
						}
					}
					node.setAdvisorId(advisorId);
					rollBackList.push(node);
					for (int i = 0; i < num; ++i) {
						facultyTree.getFaculty(advisorId)->addStudent(facultyTree.getFaculty(id)->getList()[i]);
						studentTree.getStudent(facultyTree.getFaculty(id)->getList()[i])->setAdvisorId(advisorId);
					}
				}
				if (facultyTree.deleteNode(id)) {		// this is where the deleting happens and the database file gets updated
					cout << "\nFaculty Member Deleted\n";
					cout << "Advisees transfered to " << facultyTree.getFaculty(advisorId)->getName() << " ID: " << facultyTree.getFaculty(advisorId)->getId() << endl << endl;
					facultyTree.outputToFile();
					studentTree.outputToFile();
					facCount--;
				}
				else {
					cout << "Not Deleted\n";
				}
			}
			else {
				cout << "\nThis faculty member does not exist.\n\n";
			}
		}
	}
}

void Interface::displayAdvisor() //  this function finds a student and delays their advisor
{
	bool check = true;
	while (check)
	{
		cout << "\nEnter Student ID: ";
		cin >> id;
		if (cin.fail()) {
			cout << "Please enter an integer.\n";
			cin.clear();
			cin.ignore();
		}
		else {
			check = false;
			int tempId;
			if (studentTree.searchNode(id)) {
				tempId = studentTree.getStudent(id)->getAdvisorId();
				cout << endl << studentTree.getStudent(id)->getName() << "'s advisor is\n";
				cout << facultyTree.getFaculty(tempId) << endl;
			}
			else {
				cout << "\nThis student does not exist.\n\n";
			}
		}
	}
}

void Interface::displayAdvisees() // this function finds finds a faculty members and prints out all the students they advise
{
	bool check = true;
	while (check)
	{
		cout << "\nEnter Faculty ID: ";
		cin >> id;
		if (cin.fail()) {
			cout << "Please enter an integer.\n";
			cin.clear();
			cin.ignore();
		}
		else {
			check = false;
			if (facultyTree.searchNode(id)) {
				cout << facultyTree.getFaculty(id)->getName() << " is advisor to the following students.\n\n";
				for (int i = 0; i < facultyTree.getFaculty(id)->getNumOfStuds(); ++i) {
					cout << endl << studentTree.getStudent(facultyTree.getFaculty(id)->getList()[i]) << endl;
				}
			}
			else {
				cout << "\nThis faculty member does not exist.\n\n";
			}
		}
	}
}

void Interface::changeStudentsAdvisor() // this function finds a students advisor and then changes it to another advisor
{
	bool check = true;
	while (check) {
		cout << "Enter the Student's ID.\nEnter ID: ";
		cin >> id;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Please enter a valid student id.\n";
		}
		else if (!studentTree.searchNode(id)) {
			cout << "This student does not exist.\n";
		}
		else {
			check = false;
		}
	}
	check = true;
	while (check) {
		cout << "Enter the new advisors faculty ID.\nEnter ID: ";
		cin >> advisorId;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Please enter a valid student id.\n";
		}
		else if (!facultyTree.searchNode(advisorId)) {
			cout << "This faculty member does not exist.\n";
		}
		else {
			check = false;
		}
	}
	facultyTree.getFaculty(studentTree.getStudent(id)->getAdvisorId())->removeStudent(id); // this part makes sure that all the files are correctly updated
	studentTree.getStudent(id)->setAdvisorId(advisorId);
	facultyTree.getFaculty(advisorId)->addStudent(id);
	studentTree.outputToFile();
	facultyTree.outputToFile();
}

void Interface::removeAdvisee() // this function removes advisees from the advisor and reassigns it to another
{
	bool check = true;
	while (check) {
		cout << "Enter the advisors faculty ID.\nEnter ID: ";
		cin >> advisorId;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Please enter a valid faculty id.\n";
		}
		else if (!facultyTree.searchNode(advisorId)) {
			cout << "This faculty member does not exist.\n";
		}
		else {
			check = false;
		}
	}
	int num = facultyTree.getFaculty(advisorId)->getNumOfStuds();
	cout << "Choose a student to remove\n";
	for (int i = 0; i < num; ++i) {
		cout << "Student Name: " << studentTree.getStudent(facultyTree.getFaculty(advisorId)->getList()[i])->getName() << "\nID number: "
			<< studentTree.getStudent(facultyTree.getFaculty(advisorId)->getList()[i])->getId() << endl;
	}
	check = true;
	while (check) {
		cout << "Enter the Student's ID.\nEnter ID: ";
		cin >> id;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Please enter a valid student id.\n";
		}
		else if (!studentTree.searchNode(id)) {
			cout << "This student does not exist.\n";
		}
		else {
			check = false;
		}
	}
	facultyTree.getFaculty(advisorId)->removeStudent(id);
	cout << "Choose a replacement advisor for this student\n";
	facultyTree.printAdvisors();
	int original = advisorId;
	check = true;

	while (check) {
		cout << "Enter the new advisors faculty ID.\nEnter ID: ";
		cin >> advisorId;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Please enter a valid faculty id.\n";
		}
		else if (!facultyTree.searchNode(advisorId)) {
			cout << "This faculty member does not exist.\n";
		}
		else {
			check = false;
		}
	}
	studentTree.getStudent(id)->setAdvisorId(advisorId);		// this part makes sure all the files are updated correctly
	facultyTree.getFaculty(advisorId)->addStudent(id);
	studentTree.outputToFile();
	facultyTree.outputToFile();
}

void Interface::rollBack()
{
	if (!rollBackList.isEmpty()) {
		switch (rollBackList.peek().getType()) {
		case 1:	// case rolls back the creation of a new student, it deletes it. Then updates the database files
			cout << "Rolling back new student: " << rollBackList.peek().getId() << endl << endl;
			facultyTree.getFaculty(studentTree.getStudent(rollBackList.peek().getId())->getAdvisorId())->removeStudent(rollBackList.peek().getId());
			studentTree.deleteNode(rollBackList.pop().getId());
			facultyTree.outputToFile();
			studentTree.outputToFile();
			break;
		case 2: // this case rolls back the creation of a new faculty member, it deletes it. Then it updates the database
			cout << "Rolling back new faculty" << rollBackList.peek().getId() << endl << endl;
			rollNum = facultyTree.getFaculty(rollBackList.peek().getId())->getNumOfStuds();
			rollCheck = true;
			if (rollNum > 0) {
				while (rollCheck) {
					cout << "Select an advisor to transfer " << facultyTree.getFaculty(rollBackList.peek().getId())->getName() << "'s advisees to.\n";
					facultyTree.printAdvisors();
					cout << "Select Advisor: ";
					cin >> advisorId;
					if (cin.fail()) {
						cout << "Use correct data type.\nEnter a number.\n";
						cin.clear();
						cin.ignore();
					}
					else if (advisorId == facultyTree.getFaculty(rollBackList.peek().getId())->getId()) {
						cout << "You can't select the same faculty member.\nTry again.\n";
					}
					else if (!facultyTree.searchNode(advisorId)) {
						cout << "That faculty member does not exist\n";
					}
					else {
						rollCheck = false;
					}
				}
				for (int i = 0; i < rollNum; ++i) {	// this part makes sure the database has all the correct numbers.
					facultyTree.getFaculty(advisorId)->addStudent(facultyTree.getFaculty(rollBackList.peek().getId())->getList()[i]);
					studentTree.getStudent(facultyTree.getFaculty(rollBackList.peek().getId())->getList()[i])->setAdvisorId(advisorId);
					facultyTree.getFaculty(rollBackList.peek().getId())->removeStudent(facultyTree.getFaculty(rollBackList.peek().getId())->getList()[i]);
				}
			}
			facultyTree.deleteNode(rollBackList.pop().getId());
			cout << "Faculty Member Deleted\n";
			if (rollNum > 0) {
				cout << "Advisees transfered to " << facultyTree.getFaculty(advisorId)->getName() << " ID: " << facultyTree.getFaculty(advisorId)->getId() << endl << endl;
			}
			facultyTree.outputToFile();
			studentTree.outputToFile();
			facCount--;
			break;
		case 3: // if a student is deleted this function rolls it back, it saves all the original info and recreates the student and pushes it back into the tree
			cout << "Rolling back delete Student: " << rollBackList.peek().getName() << endl << endl;
			rollStud = new Student();
			rollStud->setName(rollBackList.peek().getName());
			rollStud->setId(rollBackList.peek().getId());
			rollStud->setStanding(rollBackList.peek().getStanding());
			rollStud->setMajor(rollBackList.peek().getStr2());
			rollStud->setGpa(rollBackList.peek().getGpa());
			rollStud->setAdvisorId(rollBackList.peek().getAdvisorId());
			facultyTree.getFaculty(rollBackList.peek().getAdvisorId())->addStudent(rollStud->getId());
			rollBackList.pop();
			studentTree.insertNode(rollStud);		// then it makes sure the files are reupdated
			studentTree.outputToFile();
			facultyTree.outputToFile();
			break;
		case 4:		// this case rolls back deleting a faculty member, it recreates the member and then puts them back in the tree. It also readds all its old advisees
			cout << "Rolling back delete Faculty: " << rollBackList.peek().getName() << endl << endl;
			rollFac = new Faculty();
			rollFac->setName(rollBackList.peek().getName());
			rollFac->setId(rollBackList.peek().getId());
			rollFac->setStanding(rollBackList.peek().getStanding());
			rollFac->setDepartment(rollBackList.peek().getStr2());
			for (int i = 0; i < rollBackList.peek().getSize(); ++i) {
				rollFac->addStudent(rollBackList.peek().getList()[i]);
				facultyTree.getFaculty(rollBackList.peek().getAdvisorId())->removeStudent(rollBackList.peek().getList()[i]);
				studentTree.getStudent(rollBackList.peek().getList()[i])->setAdvisorId(rollBackList.peek().getId());
			}
			rollBackList.pop();
			facultyTree.insertNode(rollFac);
			facultyTree.outputToFile();		// then it makes sure the database is up to date
			studentTree.outputToFile();
			break;
		}
	}
	else {
		cout << "\nThere is nothing to roll back\n\n";
	}
}

