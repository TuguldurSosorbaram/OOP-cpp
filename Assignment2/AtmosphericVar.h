#pragma once
#include <string>
#include "LayerofGas.h"

class Ozone;
class Oxygen;
class CarbonDioxide;

class AtmosphericVar{
public:
    virtual AtmosphericVar* change(Ozone *p) = 0;
    virtual AtmosphericVar* change(Oxygen *p) = 0;
    virtual AtmosphericVar* change(CarbonDioxide *p) = 0;
    virtual void transform(Ozone *p)=0;
    virtual void transform(Oxygen *p)=0;
    virtual void transform(CarbonDioxide *p)=0;
    virtual ~AtmosphericVar() {}
};


///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Thunderstorm : public AtmosphericVar
{
public:
    static Thunderstorm* instance();
    AtmosphericVar* change(Ozone *p) override;
    AtmosphericVar* change(Oxygen *p) override;
    AtmosphericVar* change(CarbonDioxide   *p) override;
    void transform(Ozone *p) override;
    void transform(Oxygen *p)override ;
    void transform(CarbonDioxide *p)override;

    static void destroy() ;
protected:
    Thunderstorm(){}
private:
    static Thunderstorm* _instance;
};

class Sunshine : public AtmosphericVar
{
public:
    static Sunshine* instance();
    AtmosphericVar* change(Ozone *p) override;
    AtmosphericVar* change(Oxygen *p) override;
    AtmosphericVar* change(CarbonDioxide   *p) override;
    void transform(Ozone *p) override;
    void transform(Oxygen *p)override ;
    void transform(CarbonDioxide *p)override;
    static void destroy() ;
protected:
    Sunshine(){}
private:
    static Sunshine* _instance;
};

class Other : public AtmosphericVar
{
public:
    static Other* instance();
    AtmosphericVar* change(Ozone *p) override;
    AtmosphericVar* change(Oxygen *p) override;
    AtmosphericVar* change(CarbonDioxide   *p) override;
    void transform(Ozone *p) override;
    void transform(Oxygen *p)override ;
    void transform(CarbonDioxide *p)override;
    static void destroy() ;
protected:
    Other(){}
private:
    static Other* _instance;
};
