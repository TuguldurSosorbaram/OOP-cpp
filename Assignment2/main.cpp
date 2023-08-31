#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "LayerofGas.h"
#include "AtmosphericVar.h"

using namespace std;
void create(const string &str, vector<LayerofGas*> &Layers, vector<AtmosphericVar*> &Effects);
void simulate (vector<LayerofGas*> &Layers, vector<AtmosphericVar*> &Effects);
int searchLayer (vector<LayerofGas*> &Layers, LayerofGas* &searchingLayer,int c);
void addNewLayer(vector<LayerofGas*> &Layers, LayerofGas* &layer);
void print(vector <LayerofGas*> &Layers);
void simulateLoop (vector<LayerofGas*> &Layers, vector<AtmosphericVar*> &Effects);
void destroyer (vector<LayerofGas*> &Layers, vector<AtmosphericVar*> &Effects);

//#define NORMAL_MODE
#ifdef NORMAL_MODE
int main(){
    vector<LayerofGas*> Layers;
    vector<AtmosphericVar*> Effects;
    string filename;
    cout << "Please enter filename." << endl;
    cin >> filename;
    create(filename, Layers, Effects );
    simulateLoop(Layers, Effects);

    /// destroying
    destroyer(Layers,Effects);
    return 0;
}
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1", "input1*.txt")
{
    vector<LayerofGas*> Layers;
    vector<AtmosphericVar*> Effects;
    create("input11.txt", Layers, Effects );
    simulateLoop(Layers, Effects);
    CHECK(Layers.size() == 0);
    destroyer(Layers, Effects);

    create("input12.txt", Layers, Effects );
    simulateLoop(Layers, Effects);
    CHECK(Layers.size() == 1);
    destroyer(Layers, Effects);

    create("input13.txt", Layers, Effects );
    simulateLoop(Layers, Effects);
    CHECK(Layers.size() == 1);
    destroyer(Layers, Effects);

    create("input14.txt", Layers, Effects );
    simulateLoop(Layers, Effects);
    CHECK(Layers.size() == 1);
    destroyer(Layers, Effects);

}
TEST_CASE("2", "input2*.txt")
{
    vector<LayerofGas*> Layers;
    vector<AtmosphericVar*> Effects;
    create("input21.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers[0]->getType() == "Ozone");
    CHECK(Layers[0]->getThickness() == 5 );
    destroyer(Layers, Effects);

    create("input22.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers[0]->getType() == "Ozone");
    CHECK(Layers[0]->getThickness() == 7 );
    destroyer(Layers, Effects);

    create("input23.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers[1]->getType() == "Ozone");
    CHECK(Layers[0]->getThickness() == 2 );
    CHECK(Layers[1]->getThickness() == 6 );
    destroyer(Layers, Effects);
}
TEST_CASE("3", "input3*.txt")
{
    vector<LayerofGas*> Layers;
    vector<AtmosphericVar*> Effects;
    create("input31.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers.size() == 2);
    CHECK(Layers[0]->getThickness() == 2.4 );
    destroyer(Layers, Effects);

    create("input32.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers.size() == 2);
    CHECK(Layers[0]->getType() != "Oxygen" );
    destroyer(Layers, Effects);
}
TEST_CASE("4", "input4*.txt")
{
    vector<LayerofGas*> Layers;
    vector<AtmosphericVar*> Effects;
    create("input41.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers[0]->getThickness() == 0.76);
    CHECK(Layers[0]->getType() == "Oxygen" );
    destroyer(Layers, Effects);

    create("input42.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers.size() == 2);
    CHECK(Layers[0]->getThickness() == 2.025 );
    destroyer(Layers, Effects);

    create("input43.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers.size() == 2);
    destroyer(Layers, Effects);

    create("input44.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers.size() == 3);
    CHECK(Layers[1]->getThickness() == 0.76 );
    destroyer(Layers, Effects);

}
TEST_CASE("5", "input5*.txt")
{
    vector<LayerofGas*> Layers;
    vector<AtmosphericVar*> Effects;
    create("input51.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers.size() == 3);
    CHECK(Layers[1]->getThickness() == 0.76 );
    destroyer(Layers, Effects);

    create("input52.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers.size() == 2);
    destroyer(Layers, Effects);

    create("input53.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers.size() == 3);
    CHECK(Layers[0]->getThickness() == 3.6 );
    destroyer(Layers, Effects);

    create("input54.txt", Layers, Effects );
    simulate(Layers, Effects);
    CHECK(Layers.size() == 2);
    destroyer(Layers, Effects);

}
TEST_CASE("6", "input*.txt")
{
    vector<LayerofGas*> Layers;
    vector<AtmosphericVar*> Effects;
    create("input1.txt", Layers, Effects );
    simulateLoop(Layers, Effects);
    CHECK(Layers.size() == 9);
    destroyer(Layers, Effects);

    create("input2.txt", Layers, Effects );
    simulateLoop(Layers, Effects);
    CHECK(Layers.size() < 3);
    destroyer(Layers, Effects);


}
#endif
void destroyer (vector<LayerofGas*> &Layers, vector<AtmosphericVar*> &Effects)
{
    for (unsigned int i=0;i<Layers.size();i++){
        delete Layers[i];
    }
    Thunderstorm::destroy();
    Sunshine::destroy();
    Other::destroy();

}

void simulateLoop (vector<LayerofGas*> &Layers, vector<AtmosphericVar*> &Effects)
{
    print(Layers);
    cout << " :INPUT FROM FILE " << endl;
    unsigned int max = 3*Layers.size();
    int count  = 1;
    while(Layers.size()<max && Layers.size() >=3){
        simulate(Layers,Effects);
        print(Layers);
        cout << " :SIMULATION NUMBER " << count << endl;
        count++;
    }
    if (count ==1){
        cout << "Initial layers number is not enough! It must be at least 3." << endl;
    }
    else if (count<3){
        cout << "Simulation ended because layers are less than 3 now! " << endl;
    }
    else {
        cout << "Simulation ended because layers are triple the initial layers now! " << endl;
    }
}
void create(const string &str, vector<LayerofGas*> &Layers, vector<AtmosphericVar*> &Effects)
{
    ifstream f(str);
    if(f.fail()) { cout << "Wrong file name!\n"; exit(1);}

    int n;
    f >> n;
    Layers.resize(n);

    for( int i=0; i<n; ++i ){
        char ch; double p;
        f >> ch;
        f >> p;
        switch(ch){
            case 'Z' : Layers[i] = new Ozone("Ozone", p); break;
            case 'C' : Layers[i] = new CarbonDioxide("Carbon Dioxide", p); break;
            case 'X' : Layers[i] = new Oxygen("Oxygen", p); break;
        }
    }
    string effectLine;
    f >> effectLine;
    Effects.resize(effectLine.length());
    for (unsigned int j=0;j<effectLine.length();j++){
        char chr;
        chr = effectLine.at(j);
        switch(chr){
            case 'T' : Effects[j] = Thunderstorm::instance(); break;
            case 'S' : Effects[j] = Sunshine::instance(); break;
            case 'O' : Effects[j] = Other::instance(); break;
    }
    }
}
int searchLayer (vector<LayerofGas*> &Layers, LayerofGas* &searchingLayer,int c){
    bool found=false;
    c = c-1;
    while (c>=0 && !found){
        if (Layers[c]->getType()==searchingLayer->getType()){
            found = true;
            c= c+1;
        }
        c=c-1;
    }
    return c;
}
void addNewLayer(vector<LayerofGas*> &Layers, LayerofGas* &layer){

    Layers.insert(Layers.begin(), layer);
}
void simulate (vector<LayerofGas*> &Layers, vector<AtmosphericVar*> &Effects){
    for(unsigned int i=0;i<Effects.size(); i++){
        for (unsigned int j=0;j<Layers.size();j++){
            Layers[j]->change(Effects[i]);
            if (Layers[j]->isChanged){
                if (Layers[j]->getType()=="Ozone"){
                    LayerofGas *temp = new Oxygen(Layers[j]->getType(),Layers[j]->getThickness());
                    temp->transform(Effects[i]);
                    int c = searchLayer(Layers,temp,j);
                    if (c>=0){
                        Layers[c]->addThickness(temp->getThickness());
                    }
                    else{
                        if (temp->isLayer()){
                                addNewLayer(Layers,temp);
                                j=j+1;
                            }
                    }
                } else if (Layers[j]->getType()=="Oxygen"){
                    if (Effects[i]==Other::instance()){
                        LayerofGas *temp = new CarbonDioxide(Layers[j]->getType(),Layers[j]->getThickness());
                        temp->transform(Effects[i]);
                        int c = searchLayer(Layers,temp,j);
                        if (c>=0){
                            Layers[c]->addThickness(temp->getThickness());
                        }
                        else{
                            if (temp->isLayer()){
                                addNewLayer(Layers,temp);
                                j=j+1;
                            }
                        }
                    }else{
                        LayerofGas *temp = new Ozone(Layers[j]->getType(),Layers[j]->getThickness());
                        temp->transform(Effects[i]);
                        int c = searchLayer(Layers,temp,j);
                        if (c>=0){
                            Layers[c]->addThickness(temp->getThickness());
                        }
                        else{
                            if (temp->isLayer()){
                                addNewLayer(Layers,temp);
                                j=j+1;
                            }
                        }
                    }
                } else {
                    LayerofGas *temp = new Oxygen(Layers[j]->getType(),Layers[j]->getThickness());
                    temp->transform(Effects[i]);
                    int c = searchLayer(Layers,temp,j);
                        if (c>=0){
                            Layers[c]->addThickness(temp->getThickness());
                        }
                        else{
                            if (temp->isLayer()){
                                addNewLayer(Layers,temp);
                                j=j+1;
                            }
                        }
                }
                if(!(Layers[j]->isLayer())){
                    Layers.erase(Layers.begin()+j);
                }
            }

        }
    }
}

void print(vector <LayerofGas*> &Layers){
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    for (unsigned int i=0;i<Layers.size();i++){
        cout<< Layers[i]->getType() << " " << Layers[i]->getThickness() <<endl;
    }
}

