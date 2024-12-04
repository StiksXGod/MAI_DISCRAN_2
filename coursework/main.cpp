#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>


const int MAX_N = 1000000; 


void split(const std::string& input,std::vector<int>& ans){
    std::string buff;
    for(char c:input){
        if(c==' '){
            ans.push_back(std::stoi(buff));
            buff.clear();
        }
        else{
            buff+=c;
        }
    }
    if(!buff.empty()){
        ans.push_back(std::stoi(buff));
    }
    ans.pop_back(); // delete EOF
}


void fill_start_dict(std::unordered_map<std::string,int>& dict){
    const int START_ASCII_CODE = 97;
    const int END_ASCII_CODE = 123;
    for(int i = START_ASCII_CODE;i<END_ASCII_CODE;i++){
        std::string letter(1, static_cast<char>(i));
        dict[letter] = i - START_ASCII_CODE;
    }
    std::string eof_string(1,static_cast<char>(EOF));
    dict[eof_string] = 26;
}

std::vector<int> compress(std::string& input,std::unordered_map<std::string,int> dict){
    std::vector<int> ans;
    int last_number = 26;
    ans.reserve(input.size());
    for(int left = 0;left<input.size()-1;){
        int right = left;
        std::string cur_slice(1, input[left]);
        while(right<input.size() and dict.find(cur_slice)!=dict.end()){
            right++;
            cur_slice = input.substr(left,right-left+1);
        }
        dict[cur_slice] = ++last_number;
        cur_slice.pop_back();
        ans.push_back(dict[cur_slice]);
        left = right;
    }
    ans.push_back(26);
    return ans;
}

std::string find_values(const std::unordered_map<std::string,int>& dict,const int key){
    for(const auto& pair:dict){
        if(pair.second==key){
            return pair.first;
        }
    }
    return "";
}

std::string decompress(std::vector<int>& codes,std::unordered_map<std::string,int> dict){
    std::string ans;
    ans.reserve(MAX_N);
    int last_number = 26;
    std::string last_push = "";
    for(int code:codes){
        std::string temp = find_values(dict,code);
        if(temp!=""){
            ans+=temp;
            std::string non_added = last_push+temp[0];
            if(non_added.size()>1){
                dict[non_added] = ++last_number;
            }
            last_push = temp;
        }else{
            std::string non_added = last_push+last_push[0];
            ans+=non_added;
            dict[non_added] = ++last_number;
            last_push = non_added;
        }
    }
    return ans;
}


int main(){
    std::unordered_map<std::string,int> start_dict;
    fill_start_dict(start_dict);
    std::string mode;
    std::getline(std::cin, mode);
    if(mode=="compress"){
        std::string text;
        std::vector<int> ans;
        std::getline(std::cin, text);
        text += "$"; // fix sumvol
        ans = compress(text,start_dict);
        for(auto e:ans){
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }else{
        std::string codes;
        std::vector<int> codes_vec;
        std::string ans;
        std::getline(std::cin,codes);
        split(codes,codes_vec);
        ans = decompress(codes_vec,start_dict);
        for(auto e:ans){
            std::cout << e;
        }

    }

    return 0;
}