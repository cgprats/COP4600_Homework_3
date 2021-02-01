#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>

// The Shell Class
class Shell {
	private:
		std::string _currentDirectory = "";
		std::vector<std::string> _history;
	public:
		Shell(std::string startingDirectory);
		void SetCurrentDirectory(std::string currentDirectory);
		std::string GetCurrentDirectory();
		void ExecuteCommand(std::string command);
		void AddToHistory(std::string command);
		std::vector<std::string> GetHistory();
		void WriteHistory();
};

void Prompt(Shell);

// The Main Function
int main() {
	//Create the Instance of mysh
	Shell mysh(get_current_dir_name());

	//Start the Command Prompt
	Prompt(mysh);

	//Return 0 to Cleanly Exit the Program
	return 0;
}

// The Command Prompt
void Prompt(Shell mysh) {
	//Create Local Variables
	std::string command;

	//Continue Prompting for Command Until User Exits
	while (command.compare("byebye")) {
		//Ask User for Command
		std::cout << "# ";
		std::cin >> command;

		//Execute the Given Command
		mysh.ExecuteCommand(command);
	}

}

// Shell Constructor
Shell::Shell(std::string startingDirectory) {
	_currentDirectory = startingDirectory;
}

// Set the Working Directory
void Shell::SetCurrentDirectory(std::string currentDirectory) {
	_currentDirectory = currentDirectory;
}

// Get the Working Directory
std::string Shell::GetCurrentDirectory() {
	return _currentDirectory;
}

// Execute the Given Command
void Shell::ExecuteCommand(std::string command) {
	//Change the Working Directory
	if (!command.substr(0, 8).compare("movetodir")) {
		std::cout << "change dir" << std::endl;
	}

	//Print Current Location on 'whereami'
	else if (!command.compare("whereami")) {
		std::cout << GetCurrentDirectory() << std::endl;
	}

	//Write to the History File and Exit
	else if (!command.compare("byebye")) {
		WriteHistory();
	}

	//Add the Previously Executed Command to History
	AddToHistory(command);
}

// Add A Command to the History Vector
void Shell::AddToHistory(std::string command) {
	_history.push_back(command);
}

// Return the History Vector
std::vector<std::string> Shell::GetHistory() {
	return _history;
}

// Write the History File
void Shell::WriteHistory() {
	std::ofstream historyFile;
	historyFile.open("history.txt", std::ofstream::out | std::ofstream::app);
	for (unsigned int i = 0; i < _history.size(); i++) {
		historyFile << _history[i] << std::endl;
	}
	historyFile.close();
}
