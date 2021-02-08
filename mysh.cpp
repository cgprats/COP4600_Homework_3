#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>

// The Shell Class
class Shell {
	private:
		std::string currentDirectory = "";
		std::vector<std::string> history;
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
		void ReplayCommand(int n);
		void ExecSystem(std::vector<std::string> splitCommand);
		void KillSystem(int pid);
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
	currentDirectory = startingDirectory;
	ImportHistory();
}

// Set the Working Directory
void Shell::SetCurrentDirectory(std::string newCurrentDirectory) {
	//Convert Relative Path to Absolute
	if (newCurrentDirectory.at(0) != '/') {
		newCurrentDirectory = currentDirectory + '/' + newCurrentDirectory;
	}
	
	//Create a Char Array to Check if Directory Exists
	char checkDir[newCurrentDirectory.size() + 1];
	newCurrentDirectory.copy(checkDir, newCurrentDirectory.size() + 1);
	checkDir[newCurrentDirectory.size()] = '\0';

	//If directory exists, change directory
	if (realpath(checkDir, NULL) != NULL) {
		currentDirectory = newCurrentDirectory;
	}

	//If directory doesn't exist, print error
	else {
		std::cout << "Error: Directory Does Not Exist" << std::endl;
	}

	//Remove Trailing / if it Exists
	if (currentDirectory.at(currentDirectory.size() - 1) == '/') {
		currentDirectory.erase(currentDirectory.size() - 1);
	}
}

// Get the Working Directory
std::string Shell::GetCurrentDirectory() {
	return currentDirectory;
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
		ReplayCommand(std::stoi(splitCommand[1]));
	}

	//Start a Program
	else if (!splitCommand[0].compare("start")) {
		ExecSystem(splitCommand);
	}

	//Start a Program in the Background
	else if (!splitCommand[0].compare("background")) {
		ExecSystem(splitCommand);
	}

	//Kill a Process
	else if (!splitCommand[0].compare("dalek")) {
		if (splitCommand.size() == 2) {
			KillSystem(std::stoi(splitCommand[1]));
		}
		else {
			std::cout << "Incorrect Amount of Parameters!" << std::endl;
			std::cout << "The correct syntax is dalek pid" << std::endl;
		}
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
	history.push_back(command);
}

// Return the History Vector
std::vector<std::string> Shell::GetHistory() {
	return history;
}

// Import the History from File
void Shell::ImportHistory() {
	std::ifstream historyFile;
	historyFile.open("history.txt");
	std::string historicCommand;
	while(std::getline(historyFile, historicCommand)) {
		history.push_back(historicCommand);
	}
}


// Write the History File
void Shell::WriteHistory() {
	std::ofstream historyFile;
	historyFile.open("history.txt");
	for (unsigned int i = 0; i < history.size(); i++) {
		historyFile << history[i] << std::endl;
	}
	historyFile.close();
}

// Print the Reversed History
void Shell::PrintHistory() {
	for (int i = history.size() - 1, j = 0; i >= 0; i--, j++) {
		std::cout << j << ": " << history[i] << std::endl;
	}
}

// Clear the Command History
void Shell::ClearHistory() {
	history.clear();
}

// Rerun a Command From History
void Shell::ReplayCommand(int n) {
	//Print the Command to be Replayed
	std::cout << history[history.size() - 2 - n] << std::endl;
	//Execute the Command to be Replayed
	ExecuteCommand(history[history.size() - 2 - n]);
}

// Execute a System Command
void Shell::ExecSystem(std::vector<std::string> splitCommand) {
	//Find the System Command to Execute
	std::string baseCommandStr = splitCommand[1];
	if (baseCommandStr.at(0) != '/') {
		baseCommandStr = currentDirectory + "/" + baseCommandStr;
	}

	//Find the Command Arguments
	std::string argumentsStr;
	for (unsigned int i = 2; i < splitCommand.size(); i++) {
		argumentsStr = splitCommand[i] + " ";
	}
	
	//Create Base Command Char Array
	char baseCommand[baseCommandStr.size() + 1];
	baseCommandStr.copy(baseCommand, baseCommandStr.size() + 1);
	baseCommand[baseCommandStr.size()] = '\0';

	//Create Arguments Char Array
	char arguments[argumentsStr.size() + 1];
	argumentsStr.copy(arguments, argumentsStr.size() + 1);
	arguments[argumentsStr.size()] = '\0';

	//Execute the Program
	pid_t pid;
	pid = fork();

	//Handle Fork Error
	if (pid < 0) {
		std::cout << "Failed to Fork Process" << std::endl;
	}

	//Execute Child Process
	else if (pid == 0) {
		execl("/usr/bin/xterm", "/usr/bin/xterm", "-bg", "green", NULL);
	}

	//Run Program in Foreground
	else if (!splitCommand[0].compare("start")) {
		wait(NULL);
	}

	//Run Program in Background
	else if (!splitCommand[0].compare("background")) {
		std::cout << "pid: " << pid << std::endl;
	}
}

// Kill a System Process
void Shell::KillSystem(int pid) {
	kill(pid, 9);
}
