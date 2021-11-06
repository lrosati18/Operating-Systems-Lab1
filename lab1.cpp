#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>

using namespace std;

//define method
void newProcess(int process);

int main(){
	//initialize process number to zero, this variable helps keep track of new processes
	int processNumber = 0;

	//call method
	newProcess(processNumber);
}

void newProcess(int process){
	string userData; //define variable userData

	cout << "Enter some text: "; //request user input
	cin >> userData; //get user input
	process++; //increment process number after each user input

	//if user inputs any string other than "Done"
	if(userData != "Done"){

		//fork to create child process
		pid_t id = fork();
		
		//parent process
		if(id > 0){
		       newProcess(process);
		}	       
		
		//child process
		else if(id == 0){
			pid_t parentId = getppid();
			pid_t childId = getpid();
			stringstream s;

		//	cout << "\n The child id is: " << childId << endl;
		//	cout << "The parent id is: " << parentId << endl;

			//name of text files that are created for each user input and hold the userData string
			s <<"childFile" << process <<".txt";
			string file = s.str(); //name of file is "childFile"+process number.txt

			//call ofstream to write output to text file
			ofstream outfile;

			//open corresponding text file 
			outfile.open(file.c_str());

			//while in the same process
			while(getppid() == parentId){
				
				//write userData to text file
				outfile << userData << endl;

				sleep(1); //suspends process
			}

			//user inputs "Done"
			outfile.close();
		}

	}
}
