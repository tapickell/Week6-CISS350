#pragma once
class Suspect
{
public:
	Suspect(void);
	~Suspect(void);
	std::string getName();
	std::vector<std::string> getAttribs();
	void setName(std::string);
	void setAttribs(std::vector<std::string>);
	std::string toString();

private:
	std::string name;
	std::vector<std::string> attribs;
};

