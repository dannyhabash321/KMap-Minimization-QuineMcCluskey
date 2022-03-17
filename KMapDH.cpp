// Author: Danny Habash
// Course: COSC 2425 
// Program Set 2
// Comments: toBinary was borrowed from stackoverflow and made useful for this code
            // this code is not very efficient and can be refactored in terms of space and speed but it works and i dont feel like messing with it to make it more efficient
            //this program uses quine mclusky to solve 2,3,4 variable minterms
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

//converts dec to binary
string toBinary(int n, int varNum){
   string r;
   string b= "0";
   while(n!=0) {
      r=(n%2==0 ?"0":"1")+r; 
      n/=2;
   }
   while(r.length() != varNum){
      r.insert(0,b);
   }
   return r;
}

//accespts two strings and compares them to see if theyre off by one bit
string offByOne(string one, string two){
   for(int i=0; i<one.length();i++){
      if (one[i]=='0'){
         one[i]='1';
         if(one.compare(two)==0){
            one[i]='-';
            return one;
         } 
         one[i]='0';
      }
      else if (one[i]=='1'){
         one[i]='0';
         if(one.compare(two)==0){
            one[i]='-';
            return one;
         }
         one[i]='1';  
      }
   }
   return "0";

}


int main(){   
   //number of vars and var location
   int varNum=0;
   string varLocations;
   //prompt to enter var number
   cout<< "Enter the number of variables: ";
   cin >> varNum;
   //checking if vars are between 2-4
   if(varNum>4 || varNum<2){
      cout<< "Error, number must be 2, 3 or 4!";
      exit(1);
   }

   //initializing vector of locations to 4
   vector<int> locations(4,0);
   //change size to 8 if vars are 3
   if(varNum==3){
      locations.resize(8,0);
   }
   //change size to 16 if vars are 4
   if(varNum==4){
      locations.resize(16,0);
   }

   //ignore buffer newline and read in locations of 1s
   cin.ignore();
   cout<< "Enter the location of the 1 values: ";
   getline(cin, varLocations);

   //create a stream of the entered input
   stringstream streamData(varLocations);
   string location;
   //change locations to 1
   while(getline(streamData, location, ' ')){
      locations[stoi(location)]=1;     
   }

   //map to output if there are 2 vars
   if(varNum==2){
      cout<<"=====K Map===="<<endl;
      cout<<"  \\A |"<<endl;
      cout<<"B  \\ | 0   1 "<<endl;
      cout<<"-----+--------"<<endl;
      cout<<"  0  | " <<locations[0]<< " | "<<locations[2]<<" |"<<endl;
      cout<<"-----+--+-----"<<endl;
      cout<<"  1  | "<<locations[1]<< " | "<<locations[3]<<" |"<<endl;
      cout<<"--------------"<<endl;

   }

   //map to output if there are 3 vars
   if(varNum==3){
      cout<<"=========K Map========"<<endl;
      cout<<"  \\AB|"<<endl;
      cout<<"C  \\ | 00  01  11  10 "<<endl;
      cout<< "-----+----------------"<<endl;
      cout<< "  0  | "<<locations[0]<< " | "<<locations[2]<<" | " <<locations[6]<<" | " <<locations[4]<<" |"<<endl;
      cout<< "-----+---+---+---+----"<<endl;
      cout<< "  1  | "<<locations[1]<< " | "<<locations[3]<<" | " <<locations[7]<<" | " <<locations[5]<<" |"<<endl;
      cout<<"----------------------"<<endl;
   }

   //map to output if there are 4 vars
   if(varNum==4){
      cout<<"=========K Map========"<<endl;
      cout<<"  \\AB|"<<endl;
      cout<<"CD \\ | 00  01  11  10 "<<endl;
      cout<< "-----+----------------"<<endl;
      cout<< "  00 | "<<locations[0]<< " | "<<locations[4]<<" | " <<locations[12]<<" | " <<locations[8]<<" |"<<endl;
      cout<< "-----+---+---+---+----"<<endl;
      cout<< "  01 | " <<locations[1]<< " | "<<locations[5]<<" | " <<locations[13]<<" | " <<locations[9]<<" |"<<endl;
      cout<< "-----+---+---+---+----"<<endl;
      cout<< "  11 | "  <<locations[3]<< " | "<<locations[7]<<" | " <<locations[15]<<" | " <<locations[11]<<" |"<<endl;
      cout<< "-----+---+---+---+----"<<endl;
      cout<< "  10 | " <<locations[2]<< " | "<<locations[6]<<" | " <<locations[14]<<" | " <<locations[10]<<" |"<<endl;
      cout<<"----------------------"<<endl;

   }

   //holds 4 maps to store the groups to be made and their corresponding binary numbers with dashes
   unordered_map <string,string> map1;
   unordered_map <string,string> map2;
   unordered_map <string,string> map3;
   unordered_map <string,string> map4;

   //changes 1 locations to binary numbers
   for(int i=0; i < locations.size();i++){
      if(locations[i]==1){
         map1[to_string(i)] = toBinary(i,varNum);
      }
   }

   //holds used numbers to be deleted from map
   vector<string> used;
   //checks if any binry numbers can be compared to other groups and adds them to map 2 then adds those groups to used so they can be deleted after
   for(auto i : map1){
      for(auto j : map1){
         if(offByOne(i.second,j.second) != "0"){
            string k=i.first+","+j.first;
            string comp=j.first+","+i.first;
            
            if(map2.find(comp) == map2.end()){
               map2[k]=offByOne(i.second,j.second);
               used.push_back(i.first);
               used.push_back(j.first);
            }
         }
      }
   }

   //erases used up numbers in map1
   for(auto i: used){
      map1.erase(i);
   }

   //initializes used back to 0
   used={};
   //checks if any binry numbers from map2 can be compared to other groups and adds them to map3 then adds those groups to used so they can be deleted after
   for(auto i : map2){
      for(auto j : map2){
         if(offByOne(i.second,j.second) != "0"){
            string k=i.first+","+j.first;
            string comp=j.first+","+i.first;
            if(map3.find(comp) == map3.end()){
               map3[k]=offByOne(i.second,j.second);
               used.push_back(i.first);
               used.push_back(j.first);
            }
         }
      }
   }

//erases used up numbers in map2
   for(auto i: used){
      map2.erase(i);
   }

//removes duplicates from map 3
   for(auto i : map3){
      for(auto j : map3){
         if (i.second == j.second && i!=j){
            map3.erase(j.first);
         }
      }
   }

   //initializes used back to 0
   used={};
   //checks if any binry numbers from map2 can be compared to other groups and adds them to map3 then adds those groups to used so they can be deleted after
   for(auto i : map3){
      for(auto j : map3){
         if(offByOne(i.second,j.second) != "0"){
            string k=i.first+","+j.first;
            string comp=j.first+","+i.first;
            if(map4.find(comp) == map4.end()){
               map4[k]=offByOne(i.second,j.second);
               used.push_back(i.first);
               used.push_back(j.first);
            }
         }
      }
   }

   //erases used up numbers in map3
   for(auto i: used){
      map3.erase(i);
   }

   //removes duplicates from map4
   for(auto i : map4){
      for(auto j : map4){
         if (i.second == j.second && i!=j){
            map4.erase(j.first);
         }
      }
   }

   //combines all maps together to find the resulting prime implicants not used or ones that cant be further minimized
   unordered_map<string, string> result = map1;
   result.insert(map2.begin(), map2.end());
   result.insert(map3.begin(), map3.end());
   result.insert(map4.begin(), map4.end());
   
   //stores resulting groups into a vector to be ordered and simplified
   vector<char>variables{'A', 'B', 'C', 'D'};
   vector<vector<int>> groups(result.size());
   vector<string> simplifications(result.size());
   int j=0;
   for(auto i : result){
      //works on parsing the keys of the resulting map for output
      stringstream streamData(i.first);
      string group;
      while(getline(streamData, group, ',')){
         groups[j].push_back(stoi(group));     
      }

      //works on parsing the groups for simplification
      for(int k=0;k<i.second.length();k++){
         if(i.second[k]=='0'){
            simplifications[j] += variables[k];
            simplifications[j] += '\'';
         }
         else if(i.second[k]=='1'){
            simplifications[j] += variables[k];
         }
      }
      j++;
   }

   //the rest of the program is how the solution is outputted
   for (int i = 0; i < groups.size(); i++){
      sort(groups[i].begin(),groups[i].end());
      cout<< endl<<"Group "<<i+1<<": ";
      for (int j = 0; j < groups[i].size(); j++){
         cout<< groups[i][j]<< " ";
      }
      cout<< "\nSimplification of group "<< i+1<<"-> " <<simplifications[i]<<endl;  
   }
   cout<<"\nF(";
   for(int i=0; i<varNum;i++){
      cout<< variables[i];
      if(i!=varNum-1){
         cout<<",";
      }
   }
   cout<<") = ";
   for(int i=0; i<simplifications.size();i++){
      cout<< simplifications[i];
      if(i!=simplifications.size()-1 ){
         cout<<" + ";
      }
   }
   cout<< endl;


   return 0;
}