#pragma once

#include <iostream>
#include <vector>
#include <fstream>

template<class kc>
bool in(vector<kc> v, kc i){
    for(kc k : v){
        if(k == i){
            return true;
        }
    }
    return false;
}

template<class vc>
int index(vector<vc> vecs, vc key){
    int ind = 0;
    for(vc vkey : vecs){
        if(vkey == key) return ind;
        ind++;
    }

    return -1;
}

template<class kc, class vc>
class dict{
    public:
    std::vector<kc> keys;
    std::vector<vc> values;
    dict(){
        ;
    }

    int size(){
        return values.size();
    }

    void set(kc key, vc val){
        if(in(keys, key)){
            values.at(index(keys, key)) = val;
        } else {
            keys.push_back(key);
            values.push_back(val);
        }
    }

    vc get(kc key){
        return values[index(keys, key)];
    }
};

template<class kc, class vc>
class paar{
    public:
    kc key;
    vc value;
    bool nvalue = false;

    paar(){}

    paar(kc k, vc v){
        key=k;
        value=v;
    }

    void setv(vc val){
        value=val;
    }

    void setk(kc key_){
        key=key_;
    }

    vc &get(){
        return value;
    }

    bool operator==(const paar<kc, vc> &other){
        return key==other.key && value==other.value;
    }
};

template<class alpha>
class Ideoma{
    public:
    
    alpha a, b;
    
    Ideoma(alpha a_, alpha b_){
        a = a_;
        b = b_;
    }

    Ideoma(){
        a = alpha();
        b = alpha();
    }
};

template<class kc, class vc>
paar<kc, vc> &getPaarByName(vector<paar<kc, vc>> vd, kc name){
    for(paar<kc, vc> &p : vd){
        if(p.key == name){
            return p;
        }
    }
    cout<<1<<endl;
    //return npos
}

template<class kc, class vc>
int paarIndex(vector<paar<kc, vc>> vd, paar<kc, vc> paar){
    for(int i = 0; i < vd.size(); i++){
        if(vd[i] == paar){
            return i;
        }
    }
    return -1;
}

template<class kc, class vc>
vector<reference_wrapper<vc>> getOnlyVals(vector<paar<kc, vc>> vd){
    vector<reference_wrapper<vc>> vals;
    for(paar<kc, vc> p : vd){
        vals.push_back(reference_wrapper<vc>(p.value));
    }
    return {vals};
}

template<class k>
k getLast(vector<k> v){
    return v[v.size()-1];
}

template<class cs>
void printv(vector<cs> vs, bool qoutes = false, char end=' '){
    for(cs s: vs){
        if(qoutes) cout<<"'"<<s<<"'"<<end;
        else cout<<s<<end;
    }
    cout<<endl;
}

vector<string> getFileLines(std::string fileName, char sep = '\n'){
    ifstream ogfile(fileName);
    string line;
    vector<string> lines;
    while (!ogfile.eof()){
        getline(ogfile,line, sep);
        lines.push_back(line);
    }

    return {lines};
}

vector<string> split(string line, char delim = ' '){
    vector<string> elems{""};
    bool isSpace = true;
    for(char ch : line){
        if(isSpace && ch!=delim || !isSpace && ch!=delim){
            elems[elems.size()-1]+=ch;
        }
        isSpace = ch == delim;
        if (isSpace) elems.push_back("");
    }

    return {elems};

}

string join(vector<string> vs, char udel = ' '){
    string o;
    for(string s : vs){
        o+=s;
        o+=udel;
    }

    return {o};
}

bool isInteger(const std::string & s){
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
   char * p;
   strtol(s.c_str(), &p, 10);
   return (*p == 0);
}