// Copyright 2024 Anvar
#pragma once
#include <iostream>
#include <Windows.h>
#include "../lib_dmassive/archive.h"

namespace InputSystem {
enum RemoveMode {
    Back1, Front1, All, First, Last, OneValue1, SeveralValues1
};
enum InsertMode { Back, Front, OneValue, SeveralValues };
enum FindMode { FAll, FFirst, FLast };

template <typename T>
T* remove(const size_t& n, const size_t& pos,
           const InputSystem::RemoveMode& mode) noexcept {
    T* value = nullptr;
    int user;
    std::cout << "Choose remove mode:\n"
                 << "1 - back,\n"
                 << "2 - front,\n"
                 << "3 - by value,\n"
                 << "4 - at given position.\n"
                 << "Your choose: ";
    std::cin >> user;
    if (user == 1) {
        mode = Back1;
    } else if (user == 2) {
        mode = Front1;
    } else if (user == 3) {
        std::cout << "Remove by value:\n"
                     << "1 - first coincidence,\n"
                     << "2 - last coincidence,\n"
                     << "3 - all coincidence.\n"
                     << "Your choose: ";
        std::cin >> user;
        if (user == 1) {
            mode = First;
        } else if (user == 2) {
            mode = Last;
        } else if (user == 3) {
            mode = All;
        }
    } else if (user == 4) {
        std::cout << "How many values need to be removed:\n"
                     << "1 - one value,\n"
                     << "2 - several values.\n"
                     << "Your choose: ";
        std::cin >> user;
        mode = (user == 1) ? OneValue1 : SeveralValues1;
    }

    if (mode == First || mode == Last || mode == All) {
        value = new T[1];
        std::cout << "Input value for remove: ";
        std::cin >> value[0];
    } else if (mode == SeveralValues1) {
        std::cout << "Input number of values for remove: ";
        std::cin >> n;
        value = new T[n];
    }

    if (mode == OneValue1 || mode == SeveralValues1) {
        std::cout << "Input position for remove: ";
        std::cin >> pos;
    }
    return value;
}

template <typename T>
T* insert(const size_t& n, const size_t& pos,
           const InputSystem::InsertMode& mode) noexcept {
    T* value = nullptr;
    int user;
    std::cout << "Choose insert mode:\n"
                 << "1 - to the back,\n"
                 << "2 - to the front,\n"
                 << "3 - at given position.\n"
                 << "Your choose: ";
    std::cin >> user;
    if (user == 1) {
        mode = Back;
    } else if (user == 2) {
        mode = Front;
    } else if (user == 3) {
        std::cout << "How many values need to insert:\n"
                     << "1 - one value,\n"
                     << "2 - several values.\n"
                     << "Your choose: ";
        std::cin >> user;
        mode = (user == 1) ? OneValue : SeveralValues;
    }
    if (mode == Back || mode == Front || mode == OneValue) {
        value = new T[1];
        std::cout << "Input value for insert: ";
        std::cin >> value[0];
    } else if (mode == SeveralValues) {
        std::cout << "Input number of values for insert: ";
        std::cin >> n;
        value = new T[n];
        std::cout << "Input values for insert (between space): ";
        for (size_t i = 0; i < n; i++) {
            std::cin >> value[i];
        }
    }
    if (mode == OneValue || mode == SeveralValues) {
        std::cout << "Input position for insert: ";
        std::cin >> pos;
    }
    return value;
}

template <typename T>
T* find(const InputSystem::FindMode& mode) noexcept {
    T* value = nullptr;
    int user;
    std::cout << "Choose find mode:\n"
                 << "1 - find all,\n"
                 << "2 - find first,\n"
                 << "3 - find last.\n"
                 << "Your choose: ";
    std::cin >> user;
    if (user == 1) {
        mode = FAll;
    } else if (user == 2) {
        mode = FFirst;
    } else if (user == 3) {
        mode = FLast;
    }
    if (mode == FFirst || mode == FLast) {
        value = new T;
        std::cout << "Input value for find: ";
        std::cin >> value[0];
    } else if (mode == FAll) {
        value = new T[5];
        std::cout << "Input values for find (max 5) ('.' for exit): ";
        for (size_t i = 0; i < 5; i++) {
            std::cin >> value[i];
            if (value[i] == '.') {
                break;
            }
        }
    }
    return value;
}
}  // namespace InputSystem

namespace OutputSystem {
static void setCursor(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

static void getCursor(int* column, int* line) noexcept {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        if (column != nullptr) {
            *column = csbi.dwCursorPosition.X;
        }
        if (line != nullptr) {
            *line = csbi.dwCursorPosition.Y;
        }
    } else {
        if (column != nullptr) {
            *column = 0;
        }
        if (line != nullptr) {
            *line = 0;
        }
    }
}

static void insert() noexcept {
    std::cout << "Done." << std::endl;
}

static void remove() noexcept {
    std::cout << "Done." << std::endl;
}

template <typename T>
static void find(size_t* values, const InputSystem::FindMode mode,
                 const TDMassive<T>& archive, size_t count) noexcept {
    system("cls");
    const auto& data = archive.data();
    std::cout << "Matches found: ";
    for (size_t i = 0; i < count; i++) {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;
    archive.print();
    std::cout << std::endl;
    for (int i = 0; i < count; i++) {
        std::cout << data[values[i]];
        if (i < count - 1) {
            std::cout << ", ";
        }
    }
}

template <typename T>
void show(const TDMassive<T>& archive) noexcept {
    std::cout << "Archive: { ";
    archive.print();
    if (!archive.empty()) {
        int column, line;
        getCursor(column, line);
        column -= 2;
        setCursor(column, line);
    }
    std::cout << " }\n";
}
}  // namespace OutputSystem
