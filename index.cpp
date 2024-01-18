#include <iostream>
#include <fstream>
#include <vector>

struct Task {
    std::string description;
    bool completed;
};

void displayMenu() {
    std::cout << "\nTodo List Manager\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. List Tasks\n";
    std::cout << "3. Mark as Completed\n";
    std::cout << "4. Remove Task\n";
    std::cout << "5. Save and Quit\n";
}

void saveToFile(const std::vector<Task>& tasks) {
    std::ofstream file("todo_list.txt");

    for (const auto& task : tasks) {
        file << task.description << "," << task.completed << "\n";
    }
}

void loadFromFile(std::vector<Task>& tasks) {
    std::ifstream file("todo_list.txt");

    if (file.is_open()) {
        tasks.clear();

        std::string line;
        while (std::getline(file, line)) {
            Task task;
            size_t commaPos = line.find(',');
            task.description = line.substr(0, commaPos);
            task.completed = line.substr(commaPos + 1) == "1";
            tasks.push_back(task);
        }

        file.close();
    }
}

int main() {
    std::vector<Task> tasks;
    loadFromFile(tasks);

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;
        std::cin.ignore(); // Consume newline character

        switch (choice) {
            case 1: {
                Task task;
                std::cout << "Enter task description: ";
                std::getline(std::cin, task.description);
                task.completed = false;
                tasks.push_back(task);
                break;
            }
            case 2: {
                std::cout << "\nTasks:\n";
                for (const auto& task : tasks) {
                    std::cout << (task.completed ? "[X] " : "[ ] ") << task.description << "\n";
                }
                break;
            }
            case 3: {
                std::cout << "Enter the index of the task to mark as completed: ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < tasks.size()) {
                    tasks[index].completed = true;
                    std::cout << "Task marked as completed.\n";
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case 4: {
                std::cout << "Enter the index of the task to remove: ";
                int index;
                std::cin >> index;
                if (index >= 0 && index < tasks.size()) {
                    tasks.erase(tasks.begin() + index);
                    std::cout << "Task removed.\n";
                } else {
                    std::cout << "Invalid index.\n";
                }
                break;
            }
            case 5: {
                saveToFile(tasks);
                std::cout << "Todo list saved. Quitting...\n";
                break;
            }
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}
