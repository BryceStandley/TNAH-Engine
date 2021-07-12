#pragma once

class TNAH_API DynamicEnum
{
private:
	std::vector<std::string> values;
public:
	void AddValue(std::string desc)
	{
		values.push_back(desc);
	}

	int GetValue(std::string desc)
	{
		if (values.size() == 0)
			return -1;
		
		std::vector<std::string>::iterator iterate;
		int c = 0;
		for (iterate = values.begin(); iterate != values.end(); iterate++)
		{
			if (desc == *iterate)
				return c;
			c++;
		}
		return -1;
	}

	std::string GetDescription(int value)
	{
		if (value > values.size() - 1 || value < 0 || values.size() == 0)
		{
			return "INVALID_MESSAGE";
		}
		else
			return values[value];
	}
	friend std::ostream& operator<<(std::ostream& os, DynamicEnum& dn)
	{
		std::string out = "";
		int count = 0;
		std::vector<std::string>::iterator iterate;

		for (iterate = dn.values.begin(); iterate != dn.values.end(); iterate++)
		{
			os << count << " " << *iterate << std::endl;
			count++;
		}

		return os;
	}
};


