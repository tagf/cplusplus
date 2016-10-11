#include <iostream>
#include <vector>
#include <algorithm>


int ReadNumber(std::istream &in_stream = std::cin) {
    int number;
    in_stream >> number;
    return number;
}

int ReadChar(std::istream &in_stream = std::cin) {
    char character;
    in_stream >> character;
    return character;
}

std::vector<int> ReadArray(std::istream &in_stream = std::cin) {
    int length = ReadNumber(in_stream);
    std::vector<int> array(length);
    for (int i = 0; i < length; ++i) {
        array[i] = ReadNumber(in_stream);
    }
    return array;
}

class compare_greater {
    bool operator() (int left, int right) {
        return left > right;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> array = ReadArray();
    
    // ýëåìåíòû äýêà äîëæíû èäòè â ïîðÿäêå íåâîçðàñòàíèÿ !
    std::vector<int> deque;
    int deque_start = 0;
    
    int num_of_instructions = ReadNumber();
    
    // int curr_max = deque[deque_start];
    int pos_left = 0;
    int pos_right = 0;
    
    for (int i = 0; i < num_of_instructions; ++i) {
        char instruction = ReadChar();
        if (instruction == 'R') {
            ++pos_right;
            // update deque
            if (deque.back() >= array[pos_right]) {
                deque.push_back(array[pos_right]);
            } else {
                int insert_pos =
                  std::upper_bound(deque.begin() + deque_start, deque.end(), compare_greater())
                  - deque.begin();
                deque[insert_pos] = array[pos_right];
                deque.resize(insert_pos - deque_start + 1);
            }
        } else /* if (instruction == 'L') */ {
            if (deque[deque_start] == array[pos_left]) {
                ++deque_start;
            }
            ++pos_left;
        }
        
        std::cout << deque[deque_start];
    }

    return 0;
}
