#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include <list>


int TableShow(std::string high_scores_filename, bool unicalMin=false){
                std::ifstream in_file{high_scores_filename};
                if (!in_file.is_open()) {
                    std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
                    return -1;
                }

                std::cout << "High scores table:" << std::endl;

                std::string username;
                //std::list usernameList;
                int high_score = 0;
                while (true) {
                    // Read the username first
                    in_file >> username;
                    //usernameL 
                    // Read the high score next
                    in_file >> high_score;
                    // Ignore the end of line symbol
                    in_file.ignore();

                    if (in_file.fail()) {
                        break;
                    }

                    // Print the information to the screen
                    std::cout << username << '\t' << high_score << std::endl;
                }
                in_file.close();
    return 0;                
};


int main(int argc, char** argv)
{
    //enum Argum {'-max', '-level', '-table'};
    int MAXDIAPAZON = 100;
    int LEVEL = 3; //1 - MAXDIAPAZON=10, 2 - MAXDIAPAZON=50, 3 - MAXDIAPAZON=100
    //std::string pathexec = std::filesystem::path(argv[0]);
    //std::string high_scores_filename  = pathexec + "e:\\repo\\guess_the_number\\high_scores.txt";
    const std::string high_scores_filename  = "high_scores.txt";

    if (argc > 0 ){
            //std::cout<<"MAXDIAPAZON="<< MAXDIAPAZON <<std::endl;
            for(int i = 0; i<argc; i++){
            //1.std::string ftmp {argv[i]};

            std::string ftmp {argv[i]};
            //ftmp = argv[i];// ошибка
            if(ftmp == "-max"){
                MAXDIAPAZON = std::stoi(argv[i+1]);
                continue;
            };
            if(ftmp == "-h"){
                 std::cout<<"-max [10..32000], -level [1,2,3], -table" <<std::endl;
            };
            if(ftmp == "-level"){
                switch (std::stoi(argv[i+1]))
                {
                case 1:  MAXDIAPAZON = 10;   break;
                case 2:  MAXDIAPAZON = 50;   break;
                case 3:  MAXDIAPAZON = 100;   break;                
                default:    MAXDIAPAZON = 100;   break;
                }
                continue;
            };
            if(ftmp == "-table"){
                TableShow(high_scores_filename);
                abort;
            }   
        }

        std::cout<<"MAXDIAPAZON="<< MAXDIAPAZON <<std::endl;
    }else{
         std::cout<<"MAXDIAPAZON="<< MAXDIAPAZON <<std::endl;
    }

	//const int target_value = 54;
	int current_value = 0;
	//bool not_win = true;
    int attempts_count = 0;

	std::srand(std::time(nullptr)); // use current time as seed for random generator

	const int target_value = std::rand() % MAXDIAPAZON; //55;


	// Ask about name
    std::cout << "Hi! This soft for guess the number from MAXDIAPAZON" << std::endl;
	std::cout << "Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

	std::cout << "Enter your guess:" << std::endl;
	do {
		std::cin >> current_value;

        if(current_value>MAXDIAPAZON || current_value<0){
            std::cout << "current_value " << current_value <<" not in given diapazon "<< std::endl;
            continue;
        }

		if (current_value > target_value) {
			std::cout << "less than " << current_value << std::endl;
            attempts_count++;
		}
		else if (current_value < target_value) {
			std::cout << "greater than " << current_value << std::endl;
            attempts_count++;
		}
		else {
			std::cout << "you win!" << std::endl;
            attempts_count++;
            std::cout<<"attempts_count="<< attempts_count <<std::endl;
			break;
		}

	} while(true);

   	// Write new high score to the records table
	{
		// We should open the output file in the append mode - we don't want
		// to erase previous results.
		std::ofstream out_file{high_scores_filename, std::ios_base::app};
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		// Append new results to the table:
		out_file << user_name << ' ';
		out_file << attempts_count;
		out_file << std::endl;
       // out_file.close; ?????
        
        TableShow(high_scores_filename);
	} // end of score here just to mark end of the logic block of code

    return 0;
}