#include <iostream>
#include <string>
#include <unistd.h>

// The Shell Class
class Shell {
	private:
		std::string _currentDirectory = "";
	public:
		Shell(std::string startingDirectory);
		void SetCurrentDirectory(std::string currentDirectory);
		std::string GetCurrentDirectory();
		void ExecuteCommand(std::string command);
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
	//Print Current Location on 'whereami'
	if (!command.compare("whereami")) {
		std::cout << GetCurrentDirectory() << std::endl;
	}
}
