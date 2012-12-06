#include "stdafx.h"
#include "Suspect.h"


Suspect::Suspect(void)
{
}


Suspect::~Suspect(void)
{
}

std::string Suspect::getName()
{
	return name;
}

std::vector<std::string> Suspect::getAttribs()
{
	return attribs;
}

void Suspect::setName(std::string stringIN)
{
	name = stringIN;
}

void Suspect::setAttribs(std::vector<std::string> vectIN)
{
	attribs = vectIN;
}

std::string Suspect::toString()
{
	std::stringstream ss;
	ss << name << " ";
	for (size_t i = 0; i < attribs.size(); i++)
	{
		ss << attribs[i] << " ";
	}
	return ss.str();
}

//std::ostream& Suspect::operator<< (std::ostream &out) //not sure if this is done right
//{
//	std::stringstream ss;
//	std::vector<std::string> tempAtrribs = this->getAttribs();
//	for (size_t i = 0; i < tempAtrribs.size(); i++)
//	{
//		ss << tempAtrribs[i] << " ";
//	}
//	out << this->getName() << " " << ss;
//    return out;
//}
//may need to override > and < symbols for searching in tree.