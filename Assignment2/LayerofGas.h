#pragma once
#include "AtmosphericVar.h"
#include <iostream>
//#include <string>

class LayerofGas{
protected:
    std::string _type;
    double _thickness;
    LayerofGas (const std::string &str, double e = 0) :_type(str), _thickness(e) {}
public:
    std::string getType() const { return _type; }
    double getThickness() const {return _thickness;}
    bool isChanged = false;
    bool isLayer() {return _thickness >= 0.5;}
    void addThickness(double e) { _thickness += e; }
    void transformType(std::string t){_type.clear(); _type = t;}
    virtual void change(AtmosphericVar* &atmosphericVar) =0;
    virtual void transform(AtmosphericVar* &atmosphericVar) =0;
    virtual ~LayerofGas () {}
};

class Ozone : public LayerofGas {
public:
    Ozone(const std::string &str, double e = 0) : LayerofGas(str, e){}
    void change(AtmosphericVar* &atmosphericVar) override {
        atmosphericVar = atmosphericVar->change(this);
    }
    virtual void transform(AtmosphericVar* &atmosphericVar) override{
        atmosphericVar->transform(this);
    }
};
class Oxygen : public LayerofGas {
public:
    Oxygen(const std::string &str, double e = 0) : LayerofGas(str, e){}
    void change(AtmosphericVar* &atmosphericVar) override {
        atmosphericVar = atmosphericVar->change(this);
    }
    virtual void transform(AtmosphericVar* &atmosphericVar) override{
        atmosphericVar->transform(this);
    }
};
class CarbonDioxide : public LayerofGas {
public:
    CarbonDioxide(const std::string &str, double e = 0) : LayerofGas(str, e){}
    void change(AtmosphericVar* &atmosphericVar) override {
        atmosphericVar = atmosphericVar->change(this);
    }
    virtual void transform(AtmosphericVar* &atmosphericVar) override{
        atmosphericVar->transform(this);
    }

};

