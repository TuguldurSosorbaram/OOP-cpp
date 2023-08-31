#include "LayerofGas.h"
#include "AtmosphericVar.h"
#include <iostream>

using namespace std;

Thunderstorm* Thunderstorm::_instance = nullptr;
Thunderstorm* Thunderstorm::instance()
{
    if(_instance == nullptr) {
        _instance = new Thunderstorm();
    }
    return _instance;
}
void Thunderstorm::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}

AtmosphericVar* Thunderstorm::change(Ozone *p)
{
    return this;
}

AtmosphericVar* Thunderstorm::change(Oxygen *p)
{
    p->isChanged=true;
    p->addThickness(0-(p->getThickness()/2));
    return this;
}

AtmosphericVar* Thunderstorm::change(CarbonDioxide *p)
{
    return this;
}
void Thunderstorm::transform(Ozone *p)
{
    p->transformType("Ozone");
}
void Thunderstorm::transform(Oxygen *p)
{

}
void Thunderstorm::transform(CarbonDioxide *p)
{

}




///Sunshine~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sunshine* Sunshine::_instance = nullptr;
Sunshine* Sunshine::instance()
{
    if(_instance == nullptr) {
        _instance = new Sunshine();
    }
    return _instance;
}
void Sunshine::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}

AtmosphericVar* Sunshine::change(Ozone *p)
{
    return this;
}

AtmosphericVar* Sunshine::change(Oxygen *p)
{
    p->isChanged=true;
    p->addThickness(0-(p->getThickness()/20));
    return this;
}

AtmosphericVar* Sunshine::change(CarbonDioxide *p)
{
    p->isChanged=true;
    p->addThickness(0-(p->getThickness()/20));
    return this;
}
void Sunshine::transform(Ozone *p)
{
    p->transformType("Ozone");
    p->addThickness(0-(p->getThickness()/95*90));
}
void Sunshine::transform(Oxygen *p)
{
    p->transformType("Oxygen");
    p->addThickness(0-(p->getThickness()/95*90));

}
void Sunshine::transform(CarbonDioxide *p)
{

}
/// Other~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Other* Other::_instance = nullptr;
Other* Other::instance()
{
    if(_instance == nullptr) {
        _instance = new Other();
    }
    return _instance;
}
void Other::destroy()
{
	if ( nullptr!=_instance )
	{
		delete _instance;
		_instance = nullptr;
	}
}

AtmosphericVar* Other::change(Ozone *p)
{
    p->isChanged=true;
    p->addThickness(0-(p->getThickness()/20.0));

    return this;
}

AtmosphericVar* Other::change(Oxygen *p)
{
    p->isChanged=true;
    p->addThickness(0-(p->getThickness()/10.0));
    return this;
}

AtmosphericVar* Other::change(CarbonDioxide *p)
{
    return this;
}
void Other::transform(Ozone *p)
{

}
void Other::transform(Oxygen *p)
{
    p->transformType("Oxygen");
    p->addThickness(0-(p->getThickness()/95*90));
}
void Other::transform(CarbonDioxide *p)
{
    p->transformType("Carbon Dioxide");
    p->addThickness(0-(p->getThickness()/90*80));
}
