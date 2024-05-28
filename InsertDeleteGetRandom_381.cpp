//https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/submissions/1262494513/

#include <cstdlib>

class RandomizedCollection {
    std::unordered_map<int, std::unordered_set<int>> number_positions;
    std::unordered_map<int, int> pos_number;
    int counter;
    void print()
    {
        for (auto& [number, positions] : number_positions)
        {
            std::cout << number << " : {";
            for(int n : positions) { std::cout << n << ", "; }
            std::cout << "}" << std::endl;
        }
        std::cout << "[ ";
        for (auto [pos, number] : pos_number)
        {
            std::cout << "(" << pos << ", " << number << "), ";
        }
        std::cout << "]" << std::endl;
    }
public:
    RandomizedCollection() : counter(0) {}
    
    bool insert(int val) {
        bool not_present = !number_positions.contains(val);
        number_positions[val].insert(counter);
        pos_number[counter] = val;
        counter++;
        return not_present;
    }
    
    bool remove(int val) {
        if (number_positions.contains(val) and !number_positions[val].empty())
        {
            int pos = (number_positions[val].contains(counter - 1) ? counter - 1 : *number_positions[val].begin());
            number_positions[val].erase(pos);
            if(number_positions[val].empty()) { number_positions.erase(val); }
            if (pos != counter - 1)
            {
                int last = pos_number[counter - 1];
                pos_number[pos] = last;
                number_positions[last].insert(pos);
                number_positions[last].erase(counter - 1);
            }
            pos_number.erase(counter - 1);
            counter--;
            return true;
        }
        return false;
    }
    
    int getRandom() {
        int randomNumber = rand();
        return pos_number[randomNumber % counter];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */