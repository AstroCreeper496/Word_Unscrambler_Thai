#include<string>
#include<iostream>
#include<fstream>
#include<filesystem>
using namespace std;

class thailettercount{
        int lettercount[96] = {0}; 
                            // letterlist[1] = 1 means the word has one ก
                            //letterlist[i] index are listed from unicode start with i = 0 is U+0E00
                            //letterlist[0] is unused
    public:
        thailettercount(string);
        void coutthailettercount();
        int obtainlettercount(int);
};

thailettercount::thailettercount(string str){
    while(1){
    if(str.substr(0,3) >= "ก" && str.substr(0,3) <= "฿"){
        lettercount[int(str[2]) +128]++;
        //cout << " / " << int(str[2] +128) << " / ";
    }else if(str.substr(0,3) >= "เ" && str.substr(0,3) <= "๛"){
        lettercount[int(str[2]) +192]++;
        //cout << " / " << int(str[2]) +192 << " / ";
    }
    if(str.size() < 3) break;
    else str.erase(0,3);
    }
}
string ก = "ก";
void thailettercount::coutthailettercount(){
    for(int i = 0; i < 96; i++){
        cout << lettercount[i] << " ";
    }
    cout << endl;
}
int thailettercount::obtainlettercount(int pos){
    return lettercount[pos];
}
void thaicout(int n){
    if(n >= 1 && n <= 63){
        cout << ก[0] << ก[1] << char(ก[2] + (n-1));
    }else if(n > 63 && n < 127){
        cout  << ก[0] << char(ก[1] + 1) << char(ก[2] + (n-65));
    }else if(n >= 900){
        cout << char(' ' + (n - 900));
    }
}

int main(){
    string s;
    int lettercount[96] = {0};
    ifstream wordlist("thaiwordlistencoded.txt");
    string line;
    //cout << filesystem::current_path() << endl;
cin >> s;
thailettercount t(s); // finished
//t.coutthailettercount(); // finished
    if (wordlist.is_open()){
    for(int i = 0; i < 96; i++){
        lettercount[i] = t.obtainlettercount(i);
    }

    getline(wordlist,line);
    while(getline(wordlist,line)){
        bool moddedtag = 0;
        bool wordfound = 1;
            int wordindex[50] = {0};
        for(int j = 0;line.size()>3; j++){
            if(line[0]=='a'){
                line.erase(0,1);
                int num = stoi(line);
                if(num > 95) wordindex[j] = num;
                else {
                    if(lettercount[num]>0){
                        moddedtag = 1;
                        lettercount[num]--;
                        wordindex[j] = num;
                    }else wordfound = 0;
                }
            line.erase(0,3);
            }else cerr << "Invalid file data";
        }
        if(wordfound){
            for (int i = 0; i < 50; i++){
            thaicout(wordindex[i]);
            }
            cout << endl;
        }
            line = "";
             if(moddedtag) {    
                        for(int i = 0; i < 96; i++){
                lettercount[i] = t.obtainlettercount(i);
                }
                    }
    }
    wordlist.close();
    return 0;
    }else cerr << "Error opening file";
}
