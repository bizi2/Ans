// Copyright 2024 Marina Usova
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <cstdint>
#include <random>
#include <chrono>
#define HEAP

#ifdef EASY_EXAMPLE
#include <iomanip>

#include <iostream>

#include "../lib_easy_example/easy_example.h"

int main() {
    int a, b;
    float result;

    a = 1; b = 4;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    a = 1; b = 0;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
    return 0;
}
#endif  // EASY_EXAMPLE

#ifdef PAIR
#include "../lib_pair/pair.h"

int main() {
    TPair<int, int> pair1(1, 4);
    TPair<int, int> pair2;

    pair1.swap(pair2);
    return 0;
}
#endif  // PAIR

#ifdef TLIST
#include <iostream>
#include <iomanip>
#include "../lib_list/list.h"

int main() {
    TList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    // Использование итератора для чтения
    std::cout << "Reading elements using iterator:" << std::endl;
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Использование итератора для записи
    std::cout << "Writing elements using iterator:" << std::endl;
    int newValue = 10;
    for (auto it = list.begin(); it != list.end(); ++it) {
        *it += newValue;
        newValue += 10;
    }

    // Использование итератора для чтения после записи
    std::cout << "Reading elements after writing using iterator:" << std::endl;
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
#endif  // TLIST


#ifdef STACK
#include "../lib_stack/stack.h" // включаем ваш файл заголовка

int main() {


     constexpr size_t N = 1000; // Количество элементов для тестирования
    TStack<int> stack;

    // Измерение времени для push
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        stack.push(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "push time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    // Измерение времени для top
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        volatile int value = stack.top(); // Используем volatile, чтобы избежать оптимизации
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "top time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    // Измерение времени для pop
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        stack.pop();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "pop time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    return 0;
}
#endif  // STACK

#ifdef DMASSIVE
#include "../lib_dmassive/archive.h"

int main() {
    constexpr size_t N = 1000;
    TDMassive<int> massive;

    // Измерение времени для push_back
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        massive.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "push_back time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    // Измерение времени для push_front
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        massive.push_front(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "push_front time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;


    // Измерение времени для pop_front
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        massive.pop_front();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "pop_front time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    // Измерение времени для push_front
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        massive.pop_back();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "pop_back time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    // Измерение времени для insert
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        massive.insert(i, massive.size() / 2); // Вставка в середину
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "insert time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    // Измерение времени для find
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        massive.find_first(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "find_first time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    return 0;
}
#endif  // DMASSIVE

#ifdef TDLIST
#include "../lib_list/list.h"
int main() {
    constexpr size_t N = 100000; // Количество элементов для тестирования
    TList<int> list;

// Измерение времени для push_back
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        list.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "push_back time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    // Измерение времени для push_front
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        list.push_front(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "push_front time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;
             
// Измерение времени для pop_back
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        list.pop_front();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "pop_back time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;





          
   /*  // Измерение времени для insert
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        list.insertAt(N / 2, i); // Вставка в середину
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "insert time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    // Измерение времени для find
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        list.find(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "find time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl; */

    return 0;
}
#endif  // TDLIST

#ifdef STACK_LIST
#include "../lib_stack_list/stack_list.h"

int main() {
    constexpr size_t N = 1000000;
    TStack_LIST<int> stack;

    // Измерение времени для push
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        stack.push(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "push time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    // Проверка количества элементов в стеке
    std::cout << "Stack size after push: " << stack.size() << std::endl;

    // Измерение времени для pop
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        if (!stack.isEmpty()) {
            stack.pop();
        } else {
            std::cerr << "Stack is empty, cannot pop!" << std::endl;
            break;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "pop time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;

    // Проверка количества элементов после pop
    std::cout << "Stack size after pop: " << stack.size() << std::endl;

    return 0;
}
#endif

#ifdef MATRIX
#include "../lib_matrix/matrix.h"



int main() {
    int vec_data[] = { 1, 2, 3, 4, 5 };
    int vec_size = 5;
    TVector<int> vec1(vec_data, vec_size), vec2(5), vec3(10), res_v(5);

    for (int i = 0; i < 5; i++) {
        vec2[i] = -5 + rand() % 11;
    }

    int matrix_size = 3;
    int **matrix_data = new int*[matrix_size];
    for (int i = 0; i < matrix_size; i++) {
        matrix_data[i] = new int[matrix_size];
        for (int j = 0; j < matrix_size; j++) {
            matrix_data[i][j] = -5 + rand() % 11;
        }
    }

    TUpperTriangularMatrix<int> m1(matrix_data, matrix_size);

    for (int i = 0; i < matrix_size; i++) {
        matrix_data[i] = new int[matrix_size];
        for (int j = 0; j < matrix_size; j++) {
            matrix_data[i][j] = -5 + rand() % 11;
        }
    }

    TUpperTriangularMatrix<int> m2(matrix_data, matrix_size), res_m;

    std::cout << "CHECK VECTOR OPERATIONs" << std::endl << std::endl;

    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;

    vec1 += vec2;

    std::cout << "vec1+=vec2" << std::endl; 
    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;

    res_v = vec1 + vec2;

    std::cout << "res = vec1 + vec2" << std::endl;
    std::cout << "res: " << res_v << std::endl;
    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;

    std::cout << std::endl << "CHECK MATRIX OPERATIONs" << std::endl << std::endl;

    std::cout << "m1: " << std::endl << m1 << std::endl;
    std::cout << "m2: " << std::endl << m2 << std::endl;

    m1 += m2;

    std::cout << "m1+=m2" << std::endl;
    std::cout << "m1: " << m1 << std::endl;
    std::cout << "m2: " << m2 << std::endl;

    res_m = m1 + m2;

    std::cout << "res = m1 + m2" << std::endl;
    std::cout << "res: " << std::endl<< res_m << std::endl;
    std::cout << "m1: " << std::endl << m1 << std::endl;
    std::cout << "m2: " << std::endl << m2 << std::endl;



    TDMassive<int> matrix(matrix_size * matrix_size);


    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            if (i == j) {
                matrix[i * matrix_size + j] = -5 + rand() % 10 + 1; // Ненулевая диагональ
            } else {
                matrix[i * matrix_size + j] = -5 + rand() % 11;
            }
        }
    }

    std::cout << "Original Matrix:" << std::endl;
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            std::cout << matrix[i * matrix_size + j] << " ";
        }
        std::cout << std::endl;
    }

    try {
        TDMassive<int> triangular_matrix = to_upper_triangular(matrix, matrix_size);

        std::cout << "\nUpper Triangular Matrix:" << std::endl;
        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++) {
                std::cout << triangular_matrix[i * matrix_size + j] << " ";
            }
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    system("pause");
    return 0;

}
#endif

#ifdef ITERATOR
#include "../lib_vector/vector.h"
int main() {
    TVector<int> vec(10);
    for (int i = 0; i < 10; i++) {
        vec.push_back(i);
    }
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}
#endif
#ifdef HEAP
#include "../lib_heap/heap.h"
#include "../lib_vector/vector.h"
template <typename T>
void sortMassivchettam(TVector<T>& arr, int k ){
    Heap<int , true> minHeap(10); 

    for (int i = 0; i <= k && i < arr.size(); ++i) {
        minHeap.push_heap(arr[i]);
    }

    int index = 0;

    for (int i = k + 1; i < arr.size(); ++i) {

        arr[index++] = minHeap.top();
        minHeap.pop_heap();

        minHeap.push_heap(arr[i]);
    }

    while (!minHeap.is_empty()) {
        arr[index++] = minHeap.top();
        minHeap.pop_heap();
    }
}
int main() {
 TVector<int> arr;
    arr.push_back(6);
    arr.push_back(5);
    arr.push_back(3);
    arr.push_back(2);
    arr.push_back(8);
    arr.push_back(10);
    arr.push_back(9);
    
    int k = 3;
    
    sortMassivchettam(arr, k);
    

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    // Вывод: 2 3 5 6 8 9 10
    
    return 0;
}
#endif