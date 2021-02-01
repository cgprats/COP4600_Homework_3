#include <iostream>
#include <string>
#include <unistd.h>

// The Shell Class
class Shell {
	private:
		std::string _currentDirectory = "";
	public:
		Shell(std::string);
		void SetCurrentDirectory(std::string);
		std::string GetCurrentDirectory();
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

	while (command.compare("byebye")) {
		std::cout << "# ";
		std::cin >> command;
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
