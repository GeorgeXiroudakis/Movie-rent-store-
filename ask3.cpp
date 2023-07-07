//this program read a file with a name cost status format
//presents the movie optios and ast with movies to bye or rent 
//finaly it uptates the file

//#include "std_lib_facilities.h"

#include <iostream>
#include<vector>
#include <fstream>
using namespace std;


// error() simply disguises throws:
inline void error(const string& s)
{
    throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
    error(s+s2);
}

//a struct to read the info
struct movies{

    string name;
    int status;
    int price;

    movies(string n, int s, int p) : name(n), status(s), price(p){}

};


int main(){
    string file_name, name, title;
    vector<movies> info;
    int status, price;
    unsigned int i;
    int loc = -1, mode, cost = 0;


    cout << "Plese enter the name of the file\n>";  //open the file
    cin >> file_name;
    ifstream ist(file_name.c_str());
    if (!ist) error("can not open input file ", name);
    


    while (ist >> name >> status >> price){  //read, check and save the info in the vector
        if (status < 0 || status > 3) {cerr << "invalid status number found\n\n"; cerr << "invalid status number f ound";}
        if (price < 0) {cerr << "invalid price number found\n\n"; cerr << "invalid price number f ound";}

        info.push_back(movies(name, status, price));
    }

    cout << "This is the list of your options:\n\n"; ///print options
    for (i = 0; i < info.size(); i++){
        cout << "Name: " << info[i].name << "    ---------    price: " << info[i].price << "    ---------    status: " << info[i].status << endl;
    } 
    
    while(true){     //take movies he is interested in
        cout << "Give the title of the movie you are interested in\n>";
        cin >> title;
        
        if (title == "-1" || title == "exit") break;   //exit case

        for (i = 0; i < info.size(); i++){       //find the loc of the given movie
            if (info[i].name == title){
                loc = i;
                break;
            }
        }
        
        if (loc == -1){                        //check if it exists
            cerr << "\n\ntitle not found\n";
            error("tittle not found");
        }
        
        cout << "If you want  to rent the movie for 3$ press 1\nIf you want to buy it for " << info[loc].price << "$ press 2\n>";
        //check if bye op rend or invalid inpute
        try{
            cin >> mode;
            if ( (mode != 1 && mode != 2) || cin.fail() ) throw mode;
        }catch(int mode){
            cerr << ("\ninvalid mode mode must be 1 or 2 as discribed you gave ") << mode << endl;
            error("invalid mode");
        }

        //if to rent
        if (mode == 1){
            //if ( mode != 0) {cerr << "\nMovie unavailabele for rend or purchase\n"; error("Movie unavailable");}      //is this needed????

            info[loc].status = 1; //change status in vector 
            cost += 3;          //uptates cost

        }else{
            //same for bue

            //if ( mode != 0) {cerr << "\nMovie unavailabele for rend or purchase\n"; error("Movie unavailable");}

            info[loc].status = 2;
            cost += info[loc].price;
        }

        cout << "\nYour cost so far is " << cost << endl << endl;    //print the cost so far
    }
    
    cout << "\n\n\nYour tottal cost is " << cost;           //print tottal cost

    ist.close();           //close file


    ofstream ofc(file_name.c_str());       //open file for writing delleting deleting the previus values 
    if (!ofc) error("canʼt open input file ", file_name);

    //write new data
    for (i = 0; i < info.size(); i++) ofc << info[i].name << " " << info[i].price << " " << info[i].status << endl;

    system("pause");   
    return 0;
}
