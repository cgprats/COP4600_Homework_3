#include <iostream>
#include <string>
#include <sstream>
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
		void ImportHistory();
		void WriteHistory();
		void PrintHistory();
		void ClearHistory();
};

// The Prompt Prototype
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
		std::getline(std::cin >> std::ws, command);

		//Execute the Given Command
		mysh.ExecuteCommand(command);
	}

}

// Shell Constructor
Shell::Shell(std::string startingDirectory) {
	_currentDirectory = startingDirectory;
	ImportHistory();
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
	//Add the Command to History
	AddToHistory(command);

	//Split the Command into Vector
	std::stringstream stream(command);
	std::string tempstr;
	std::vector<std::string> splitCommand;
	while (std::getline(stream, tempstr, ' ')) {
		splitCommand.push_back(tempstr);
	}

	//Change the Working Directory
	if (!splitCommand[0].compare("movetodir")) {
		if (splitCommand.size() == 2) {
			SetCurrentDirectory(splitCommand[1]);
		}
		else {
			std::cout << "Incorrect Amount of Parameters!" << std::endl;
			std::cout << "The correct syntax is movetodir directory" << std::endl;
		}
	}

	//Print Current Location
	else if (!splitCommand[0].compare("whereami")) {
		std::cout << GetCurrentDirectory() << std::endl;
	}

	//Perform History Related Operations
	else if (!splitCommand[0].compare("history")) {
		//Clear the History
		if (splitCommand.size() == 2 && !splitCommand[1].compare("-c")) {
			ClearHistory();
		}
		//Print the History
		else if (splitCommand.size() == 1) {
			PrintHistory();
		}
		else {
			std::cout << "Incorrect Amount of Parameters!" << std::endl;
			std::cout << "The correct syntax is history [-c]" << std::endl;
		}
	}

	//Write to the History File and Exit
	else if (!splitCommand[0].compare("byebye")) {
		WriteHistory();
	}

	//Re-Execute a Command from History
	else if (!splitCommand[0].compare("replay")) {
	}

	//Start a Program
	else if (!splitCommand[0].compare("start")) {
	}

	//Start a Program in the Background
	else if (!splitCommand[0].compare("background")) {
	}

	//Kill a Process
	else if (!splitCommand[0].compare("dalek")) {
	}

	//Repeatedly Run a Process
	else if (!splitCommand[0].compare("repeat")) {
	}

	//Kill All Processes Started by the Shell
	else if (!splitCommand[0].compare("dalekall")) {
	}

	else {
		std::cout << "Command Not Found" << std::endl;
	}
}

// Add A Command to the History Vector
void Shell::AddToHistory(std::string command) {
	_history.push_back(command);
}

// Return the History Vector
std::vector<std::string> Shell::GetHistory() {
	return _history;
}

// Import the History from File
void Shell::ImportHistory() {
	std::ifstream historyFile;
	historyFile.open("history.txt");
	std::string historicCommand;
	while(std::getline(historyFile, historicCommand)) {
		_history.push_back(historicCommand);
	}
}


// Write the History File
void Shell::WriteHistory() {
	std::ofstream historyFile;
	historyFile.open("history.txt");
	for (unsigned int i = 0; i < _history.size(); i++) {
		historyFile << _history[i] << std::endl;
	}
	historyFile.close();
}

// Print the Reversed History
void Shell::PrintHistory() {
	for (int i = _history.size() - 1, j = 0; i >= 0; i--, j++) {
		std::cout << j << ": " << _history[i] << std::endl;
	}
}

// Clear the Command History
void Shell::ClearHistory() {
	_history.clear();
}
