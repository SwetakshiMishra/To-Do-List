#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class ToDo {
    string task;
    string name;
public:
    void add_task() {
        cout << "Enter your name: ";
        cin >> name;
        cin.ignore();
        cout << "Enter the task: ";
        getline(cin, task);

        ofstream save("To_do_list.csv", ios::app);
        if (!save) {
            cout << "Error opening file!\n";
            return;
        }
        save << name << "," << task << "\n";
        save.close();
        cout << "Task successfully added!\n";
    }

    void view_list() {
        ifstream in("To_do_list.csv");
        if (!in) {
            cout << "No data found.\n";
            return;
        }
        string line;
        cout << "\n--- All TO-DO-LIST Data ---\n";
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
    }

    void search_task() {
        string search_name, search_task;
        cout << "Enter name to search: ";
        cin >> search_name;
        cin.ignore();
        cout << "Enter task to search: ";
        getline(cin, search_task);

        ifstream in("To_do_list.csv");
        if (!in) {
            cout << "No data found.\n";
            return;
        }

        string line;
        bool found = false;
        while (getline(in, line)) {
            stringstream ss(line);
            string file_name, file_task;
            getline(ss, file_name, ',');
            getline(ss, file_task);

            if (file_name == search_name && file_task == search_task) {
                cout << "Task Found: " << line << endl;
                found = true;
            }
        }
        in.close();

        if (!found) cout << "Task not found.\n";
    }

    void delete_task() {
        string search_name, search_task;
        cout << "Enter name for deletion: ";
        cin >> search_name;
        cin.ignore();
        cout << "Enter task to delete: ";
        getline(cin, search_task);

        ifstream in("To_do_list.csv");
        if (!in) {
            cout << "No data found.\n";
            return;
        }

        vector<string> lines;
        string line;
        bool deleted = false;
        while (getline(in, line)) {
            stringstream ss(line);
            string file_name, file_task;
            getline(ss, file_name, ',');
            getline(ss, file_task);

            if (file_name == search_name && file_task == search_task) {
                deleted = true;
                continue; // skip adding this line to new file
            }
            lines.push_back(line);
        }
        in.close();

        ofstream out("To_do_list.csv");
        for (string &l : lines) {
            out << l << "\n";
        }
        out.close();

        if (deleted) cout << "Task deleted successfully!\n";
        else cout << "Task not found.\n";
    }

    void edit_task() {
        string search_name, search_task, new_task;
        cout << "Enter name for editing: ";
        cin >> search_name;
        cin.ignore();
        cout << "Enter task to edit: ";
        getline(cin, search_task);

        ifstream in("To_do_list.csv");
        if (!in) {
            cout << "No data found.\n";
            return;
        }

        vector<string> lines;
        string line;
        bool edited = false;
        while (getline(in, line)) {
            stringstream ss(line);
            string file_name, file_task;
            getline(ss, file_name, ',');
            getline(ss, file_task);

            if (file_name == search_name && file_task == search_task) {
                cout << "Enter new task: ";
                getline(cin, new_task);
                lines.push_back(file_name + "," + new_task);
                edited = true;
            } else {
                lines.push_back(line);
            }
        }
        in.close();

        ofstream out("To_do_list.csv");
        for (string &l : lines) {
            out << l << "\n";
        }
        out.close();

        if (edited) cout << "Task edited successfully!\n";
        else cout << "Task not found.\n";
    }
};

int main() {
    ToDo todo;
    int choice;

    do {
        cout << "\n--- TO-DO LIST MENU ---\n";
        cout << "1. Add Task\n";
        cout << "2. View All Tasks\n";
        cout << "3. Search Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Edit Task\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: todo.add_task(); break;
            case 2: todo.view_list(); break;
            case 3: todo.search_task(); break;
            case 4: todo.delete_task(); break;
            case 5: todo.edit_task(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
