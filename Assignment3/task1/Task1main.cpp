#include <iostream>
#include "library/maxsearch.hpp"
#include "library/SeqInFileEnumerator.hpp"
#include "library/stringstreamenumerator.hpp"

using namespace std;

struct Species{
    string name;
    int size;
    friend istream& operator>>(istream& is, Species &s){
    is >> s.name;
    is >> s.size;
    return is;
    }
};
class MinimumSpecies : public MaxSearch<Species, int>
{
    int func(const Species &e) const override {return e.size;}
    bool cond(const Species &e) const override {return e.name == "catfish";}
};



struct Angler{
    string name;
    string compID;
    int min ;
    bool CaughtCatfish ;
    friend istream& operator>>(istream& is, Angler &a)
    {
        string line;
        getline(is, line, '\n');
        stringstream ss(line);
        ss>>a.name>>a.compID;
        StringStreamEnumerator<Species> ssenor(ss);

        MinimumSpecies pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        a.CaughtCatfish = pr.found();
        a.min = pr.opt();
        return is;
    }

};

class MinimumAngler : public MaxSearch<Angler, int>
{
    int func(const Angler &e) const override {return e.min;}
    bool cond(const Angler &e) const override {return e.CaughtCatfish;}
};



int main()
{
    try
    {
        MinimumAngler pr2;
        SeqInFileEnumerator<Angler>myenor("input.txt");
        pr2.addEnumerator(&myenor);
        pr2.run();
        if(pr2.found()){
            cout << "Smallest catfish size: "<< pr2.opt() << endl << "Caught by: " << pr2.optElem().name << endl << "On competition: " << pr2.optElem().compID <<endl;
        }
        else{
            cout << "There is no catfish caught!" << endl;
        }



    }catch (SeqInFileEnumerator<Angler>::Exceptions exc){
        cout << "File not found!\n";
    }

    return 0;
}
