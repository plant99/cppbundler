/*#include <fstream>
using namespace std;
int main()
{
ifstream  fin;   // declares an object of type ifstream
ofstream fout;   // declares an object of type ofstream
fin.open("test/infile.txt");
fout.open("test/output.txt");
string one, two, three;

fout << one << two << three  << endl;
fin.close(); 
fout.close();
return 1;
}
*/
#include <fstream>
#include <iostream>
#include <regex>
#include <thread>         // std::thread
#include <mutex>


using namespace std;
std::mutex mtx;  

bool first_times[2] = {false};
void t_readAndWriteToFile(string s){
  std::ifstream ifs;

  //convert string to char array
  int n = s.length(); 
    
  // declaring character array
  char char_array[n+1]; 
    
  // copying the contents of the 
  // string to char array
  strcpy(char_array, s.c_str()); 


  cout << char_array << endl;
  ifs.open(char_array);
  string content( (std::istreambuf_iterator<char>(ifs) ),(std::istreambuf_iterator<char>() ) );
  //replace new lines
  replace(content.begin(), content.end(), '\n', ' ');
  //replace tabs
  replace(content.begin(), content.end(), '\t', ' ');
  //replace multiple spaces with single ones
  regex reg("[ ]{2,}");
  content = regex_replace(content, reg, " ");
  
  if(s.substr(n-3, 3) == ".js"){
    cout << "To be inserted in JS" << endl;
    std::ofstream outfile;
    if(!first_times[0]){
      outfile.open("output.js");
      first_times[0] = true;
    }else{
      outfile.open("output.js", std::ios_base::app);
    }
    //mutex lock
    mtx.lock();
    outfile << content << std::endl;
    outfile.close();
    mtx.unlock();
    //mutex unlock
  }else if(s.substr(n-4, 4) == ".css"){
    cout << "To be inserted in CSS" << endl;
    std::ofstream outfile;
    if(!first_times[1]){
      outfile.open("output.css");
      first_times[1] = true;
    }else{
      outfile.open("output.css", std::ios_base::app);
    }
    //mutex lock
    mtx.lock();
    outfile << content << std::endl;

    outfile.close();
    mtx.unlock();
    //mutex unlock
  }else{
    cout << s.substr(n-3, 3) << " " << s.substr(n-4, 4) << endl;
  }
  cout << content << endl;
}
 
int main()
{
ifstream fin; // declares an object of type ifstream
ofstream fout; // declares an object of type ofstream
 // ifstream and ofstream are defined in <fstream>


fin.open("test/infile.txt");
fout.open("test/output.txt");
string s;
//int count = 0;
//std::thread threads[100];
int i;
vector<thread> threads;


while(fin >> s){
  if(s.length()){
    //let one thread handle a file listed
    //t_readAndWriteToFile(s);
    //std::thread t_RandW(t_readAndWriteToFile, s);
    //threads[count++] = t_RandW;
    //t_RandW.join();
    threads.push_back(thread(t_readAndWriteToFile, s));
    cout << "Started thread n'" << i << "\n";
  }
}


for(int i=0; i<threads.size(); i++){

  // synchronize threads:
  //threads[i].join();
  threads[i].join();

}
fin.close();
fout.close();
return 1;
}
