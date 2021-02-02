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

// The Prompt Prototype
void Prompt(Shell);

// The Main Function
int main() {
	//Create the Instance of mysh
	Shell mysh(get_current_dir_name());

	//Start the Command Prompt
	Prompt(mysh);
	
	std::string temp;
	std::cout << temp;

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
		std::getline(std::cin >> std::ws, command);

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
	if (!command.substr(0, command.find(' ')).compare("movetodir")) {
		SetCurrentDirectory(command.substr(command.find(' ') + 1, command.length()));
	}

	//Print Current Location
	else if (!command.compare("whereami")) {
		std::cout << GetCurrentDirectory() << std::endl;
	}

	//Perform History Related Operations
	//TODO: FIX PARSING FOR -c FLAG
	else if (!command.compare("history")) {
		if (!command.substr(command.find(' ') + 1, command.length() - 1).compare("-c")) {
			std::cout << "print history" << std::endl;
		}
	}

	//Write to the History File and Exit
	else if (!command.compare("byebye")) {
		WriteHistory();
	}

	//Re-Execute a Command from History
	else if (!command.compare("replay")) {
	}

	//Start a Program
	else if (!command.compare("start")) {
	}

	//Start a Program in the Background
	else if (!command.compare("background")) {
	}

	//Kill a Process
	else if (!command.compare("dalek")) {
	}

	//Repeatedly Run a Process
	else if (!command.compare("repeat")) {
	}

	//Kill All Processes Started by the Shell
	else if (!command.compare("dalekall")) {
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
