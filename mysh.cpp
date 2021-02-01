#include <iostream>
#include <string>

// The Shell Class
class Shell {
	private:
		std::string _currentDirectory = "";
	public:
		Shell(std::string);
		void SetCurrentDirectory(std::string);
		std::string GetCurrentDirectory();
};

// The Main Function
int main() {
	return 0;
}

// Shell Constructor

// Set the Working Directory
void Shell::SetCurrentDirectory(std::string currentDirectory) {
	_currentDirectory = currentDirectory;
}

// Get the Working Directory
std::string Shell::GetCurrentDirectory() {
	return _currentDirectory;
}
