#pragma once
#include <list>
#include <utility>
#include <vector>
#include <iostream>

template<typename T>
class HashTable {
private:
	int size;
	//IMPLEMENT
    int hash(const int _key){return _key % size;}
	std::vector<std::list<std::pair<int,T>>> table;

public:
    HashTable(const int _size) : table(std::vector<std::list<std::pair<int,T>>>(_size))
    {
    	size = _size;
    }
	
	~HashTable()
	{
		//the destructor for std::vector will be called automatically	
	}
    
    void insert(const int _key, T _value)
    {  
    	//std::cout << "Inserting" <<std::endl;
    	int h = hash(_key);
    	std::list<std::pair<int, T>> &l = table.at(h);
    	l.push_back({_key, _value});
    }
	
	int minChainLen()
	{
		int min = 100000;
		for (int i = 0; i < table.size(); ++i)
		{
			int count = 0;
			std::list<std::pair<int, T>>& c = table.at(i);

			for(std::pair<int, T>& item : c)
			{
				//std::cout << "Inside MIN for loop " <<std::endl;
				count++;
	    	}
	    	//std::cout << "Count is:" <<count <<std::endl;

	    	if (count < min)
	    	{
	    		min = count;
	    	}
		}
		//std::cout << "Min is " << min <<std::endl;
		return min;
	}
	
	int maxChainLen()
	{
		int max = 0;
		for (int i = 0; i < table.size(); ++i)
		{
			int count = 0;
			std::list<std::pair<int, T>>& c = table.at(i);

			for(std::pair<int, T>& item : c)
			{
				//std::cout << "Inside MAX for loop " <<std::endl;
				count++;
	    	}
	    	//std::cout << "Count is:" <<count <<std::endl;

	    	if (count > max)
	    	{
	    		max = count;
	    	}
		}
		//std::cout << "Max is " << max <<std::endl;
		return max;
	}


	double averageChainLen()
	{
		double average = 0.0;
		int count = 0;
		for (int i = 0; i < table.size(); ++i)
		{
			//int count = 0;
			std::list<std::pair<int, T>>& c = table.at(i);

			for(std::pair<int, T>& item : c)
			{
				//std::cout << "Inside Average for loop " <<std::endl;
				count++;
	    	}
		}
		average = double(count)/size;
		//std::cout << "average is " << average <<std::endl;
		return average;
	}

    
    T* search(int _key) 
    {
    	int h = hash(_key);
    	std::list<std::pair<int, T>>& c = table.at(h);

    	for (std::pair<int, T>& item : c)
    	{
    		if(item.first == _key)
    		{
    			//std::cout << "Searching" <<std::endl;
    			//std::cout << item.second << std::endl;
    			return &item.second;
    		}
    	}

    	//std::cout << _key << " not found" <<std::endl;
    	return NULL;
    }    
};
