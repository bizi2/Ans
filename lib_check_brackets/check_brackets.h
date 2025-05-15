#ifndef LIB_CHECKBRACKETS_CHECKBRACKETS_H_
#define LIB_CHECKBRACKETS_CHECKBRACKETS_H_

#include <iostream>
#include <stdexcept>
#include <stack>
#include <string>

class TCheckBrackets {
private:
    std::string _data;
public:
    TCheckBrackets(const std::string& data);
    ~TCheckBrackets();
    bool areBracketsBalanced();
};

TCheckBrackets::TCheckBrackets(const std::string& data) : _data(data) {
}

TCheckBrackets::~TCheckBrackets() {
}

bool TCheckBrackets::areBracketsBalanced() {
    std::stack<char> s;
    char x;
    for (size_t i = 0; i < _data.size(); i++) {
        if (_data[i] == '(' || _data[i] == '[' || _data[i] == '{') {
            s.push(_data[i]);
            continue;
        }

        if (s.empty())
            return false;

        switch (_data[i]) {
        case ')':
            x = s.top();
            s.pop();
            if (x == '{' || x == '[')
                return false;
            break;

        case '}':

            x = s.top();
            s.pop();
            if (x == '(' || x == '[')
                return false;
            break;

        case ']':

            x = s.top();
            s.pop();
            if (x == '(' || x == '{')
                return false;
            break;
        }
    }

    return (s.empty());
}

#endif  // LIB_CHECKBRACKETS_CHECKBRACKETS_H_
