#include <iostream>
#include "library/LinSearch.hpp"
#include "library/summation.hpp"
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



class CaughtCatfish : public LinSearch<Species>
{
    bool cond(const Species &s) const override
    {
        return s.name == "catfish";
    }
};


struct Angler{
    string name;
    string compID;
    bool CaughtCatfishAngler;
    friend istream& operator>>(istream& is, Angler &a)
    {
        string line;
        getline(is, line, '\n');
        stringstream ss(line);
        ss>>a.name>>a.compID;
        StringStreamEnumerator<Species> ssenor(ss);

        CaughtCatfish pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        a.CaughtCatfishAngler = pr.found();
        return is;

    }

};

struct Result{
    string name;
    int count;
    Result(){}
    Result(string n, int c): name(n),count(c){}
};

class Counter : public Summation<Angler,Result>
{
private:
    string _name;
public:
    Counter(const string &name): _name(name){}
protected:
    Result func(const Angler &a)const override {return Result(a.name,1);}
    Result neutral() const override {return Result("",0);}
    Result add( const Result& a, const Result& b ) const override {return Result(a.name,a.count+b.count);}
    bool cond(const Angler& a) const { return a.CaughtCatfishAngler; }
    bool whileCond(const Angler &a) const override {return a.name == _name;}
    void first() override{}
};

struct AnglerBlock{
    string name;
    int count;
};

class AnglerEnumerator : public Enumerator<AnglerBlock>
{
private:
    SeqInFileEnumerator<Angler>* _f;
    AnglerBlock _block;
    bool _end;
public:
    AnglerEnumerator(const string &fname) {_f = new SeqInFileEnumerator<Angler>(fname); }
    ~AnglerEnumerator() {delete _f;}
    void first() override {_f->first(); next();}
    void next();
    AnglerBlock current() const override {return _block;}
    bool end() const override {return _end;}

};

void AnglerEnumerator::next()
{
    if ((_end = _f->end()))return;
    _block.name = _f->current().name;
    Counter pr2(_block.name);
    pr2.addEnumerator(_f);

    pr2.run();

    _block.count = pr2.result().count;
}

class AtLeastTwo : public LinSearch<AnglerBlock>
{
    bool cond(const AnglerBlock &ab) const override
    {
        return ab.count < 2;
    }
};

int main()
{
    try
    {
        AtLeastTwo pr3;
        AnglerEnumerator myenor("input.txt");
        pr3.addEnumerator(&myenor);

        pr3.run();

        if (pr3.found())
        {
            cout << "No not every angler caught catfish on at least two contests!" << endl;
        }else{
        cout << "Yes every angler caught catfish on at least two contests!" << endl;
        }




    }catch (SeqInFileEnumerator<Angler>::Exceptions exc){
        cout << "File not found!\n";
    }



    return 0;
}
