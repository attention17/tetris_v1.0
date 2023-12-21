/*
Notes: координатой блока является левый верхний его блок

разобраться почему застревает квадрат после T ----- выполнено!


План для добавления новой фигуры:
1 - Отрисовка и очистка
2 - Проверка упал ли он
3 - можно ли нажать на кнопку

21.12.2023 - доделать кнопки left и right

*/



#include <iostream>
#include <Windows.h>
#include <cstring>п
#include <conio.h>
#include <stdio.h>
#include <random>

const int WIDTH = 32;
const int HEIGHT = 32;

char matrix[32][32];
int block_position_y = 1;
int block_position_x = 10;


// прототипы функций
void cleaning_field_figure(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y, int currentBlock, int rotate);
void writing_field_figure(char(&ptr_matrix)[32][32], int currentBlock, int rotate);


int main() {

    // первое заполнение матрицы(границы)
    for (int i = 0; i < HEIGHT; ++i) {
        if (i == 0 || i == 31) {
            for (int j = 0; j < WIDTH; ++j) {
                matrix[i][j] = '#';
            }
            continue;
        }

        for (int j = 0; j < WIDTH; ++j) {
            if (j == 21) {
                matrix[i][j] = '#';
                continue;
            }
            matrix[i][j] = ' ';
        }

        matrix[i][0] = '#';
        matrix[i][31] = '#';
    }

    // объявление нужных переменных
    int last_block_position_x = 10;
    int last_block_position_y = 1;
    int current_block = rand() % 3 + 1; // менять по мере добавления блоков
    int rotate_pos_block = 1;
    while (1) {
        // сделать выход из прогрммы
        // сделать проверку какой сейчас блок и исходя из этого выдать ему соответствующие координаты

        // считывание нажатий клавиш для движения/поворота фигуры
        if (_kbhit()) {
            switch (_getch()) {
            case 72: // up (поворот блока)
                cleaning_field_figure(matrix, last_block_position_x, last_block_position_y, current_block, rotate_pos_block);
                if (rotate_pos_block == 4) rotate_pos_block = 1;
                else rotate_pos_block++;
                break;

            case 80: // down
                switch (current_block) {
                case 1: // cube
                    if (matrix[block_position_y + 2][block_position_x] == '#' || matrix[block_position_y + 2][block_position_x] == '1' || matrix[block_position_y + 3][block_position_x + 1] == '#' || matrix[block_position_y + 3][block_position_x + 1] == '1') {
                    }
                    else {
                        block_position_y += 1;
                    }
                    break;
                case 2: // T
                    switch (rotate_pos_block) {
                    case 1: // inverted T
                        if (matrix[block_position_y + 2][block_position_x - 1] == '1' || matrix[block_position_y + 2][block_position_x - 1] == '#' || matrix[block_position_y + 2][block_position_x] == '1' || matrix[block_position_y + 2][block_position_x] == '#' || matrix[block_position_y + 2][block_position_x + 1] == '1' || matrix[block_position_y + 2][block_position_x + 1] == '#') {
                        }
                        else {
                            block_position_y += 1;
                        }
                        break;
                    case 2: // |-
                        if (matrix[block_position_y + 3][block_position_x] == '1' || matrix[block_position_y + 2][block_position_x + 1] == '1' || matrix[block_position_y + 3][block_position_x] == '#') {
                        }
                        else {
                            block_position_y += 1;
                        }
                        break;
                    case 3: // T
                        if (matrix[block_position_y + 1][block_position_x - 1] == '1' || matrix[block_position_y + 2][block_position_x] == '1' || matrix[block_position_y + 2][block_position_x] == '#' || matrix[block_position_y + 1][block_position_x + 1] == '1') {
                        }
                        else {
                            block_position_y += 1;
                        }
                        break;
                    case 4:
                        if (matrix[block_position_y + 3][block_position_x] == '1' || matrix[block_position_y + 3][block_position_x] == '#' || matrix[block_position_y + 2][block_position_x - 1] == '1') {
                        }
                        else {
                            block_position_y += 1;
                        }
                        break;

                    }
                    break;
                case 3: // I
                    switch (rotate_pos_block % 2) {
                    case 1: // I
                        if (matrix[block_position_y + 4][block_position_x] == '1' || matrix[block_position_y + 4][block_position_x] == '#') {
                        }
                        else {
                            block_position_y += 1;
                        }
                        break;
                    case 0: // --
                        if (matrix[block_position_y + 1][block_position_x - 1] == '1' || matrix[block_position_y + 1][block_position_x - 1] == '#' || matrix[block_position_y + 1][block_position_x] == '#' || matrix[block_position_y + 1][block_position_x] == '1' || matrix[block_position_y + 1][block_position_x + 1] == '#' || matrix[block_position_y + 1][block_position_x + 1] == '1' || matrix[block_position_y + 1][block_position_x + 2] == '#' || matrix[block_position_y + 1][block_position_x + 2] == '1') {
                        }
                        else {
                            block_position_y += 1;
                        }
                        break;

                    }

                }

            }
        }



        system("cls");


        // проверка упал ли блок
        switch (current_block) {
        case 1: // cube
            if (matrix[block_position_y + 1][block_position_x] == '1' || matrix[block_position_y + 1][block_position_x] == '#' || matrix[block_position_y + 1][block_position_x + 1] == '1' || matrix[block_position_y + 1][block_position_x + 1] == '#') {
                block_position_x = 10;
                block_position_y = 1;
                last_block_position_x = 10;
                last_block_position_y = 1;
                current_block = rand() % 2 + 1;
                rotate_pos_block = 1;
            }
            break;


        case 2: // T
            switch (rotate_pos_block) {
            case 1: // inverted T
                if (matrix[block_position_y + 1][block_position_x - 1] == '1' || matrix[block_position_y + 1][block_position_x - 1] == '#' || matrix[block_position_y + 1][block_position_x] == '1' || matrix[block_position_y + 1][block_position_x] == '#' || matrix[block_position_y + 1][block_position_x + 1] == '1' || matrix[block_position_y + 1][block_position_x + 1] == '#') {

                    block_position_x = 10;
                    block_position_y = 1;
                    last_block_position_x = 10;
                    last_block_position_y = 1;
                    current_block = rand() % 2 + 1;
                    rotate_pos_block = 1;

                }
                break;

            case 2: // |-
                if (matrix[block_position_y + 2][block_position_x] == '1' || matrix[block_position_y + 1][block_position_x + 1] == '1' || matrix[block_position_y + 2][block_position_x] == '#') {

                    block_position_x = 10;
                    block_position_y = 1;
                    last_block_position_x = 10;
                    last_block_position_y = 1;
                    current_block = rand() % 2 + 1;
                    rotate_pos_block = 1;

                }
                break;

            case 3: // T
                if (matrix[block_position_y][block_position_x - 1] == '1' || matrix[block_position_y + 1][block_position_x] == '1' || matrix[block_position_y + 1][block_position_x] == '#' || matrix[block_position_y][block_position_x + 1] == '1') {
                    block_position_x = 10;
                    block_position_y = 1;
                    last_block_position_x = 10;
                    last_block_position_y = 1;
                    current_block = rand() % 2 + 1;
                    rotate_pos_block = 1;
                }
                break;
            case 4: // -|
                if (matrix[block_position_y + 2][block_position_x] == '1' || matrix[block_position_y + 2][block_position_x] == '#' || matrix[block_position_y + 1][block_position_x - 1] == '1') {

                    block_position_x = 10;
                    block_position_y = 1;
                    last_block_position_x = 10;
                    last_block_position_y = 1;
                    current_block = rand() % 2 + 1;
                    rotate_pos_block = 1;

                }
                break;
            }
            break;
        case 3:
            switch (rotate_pos_block % 2) {
            case 1: // I
                if (matrix[block_position_y + 3][block_position_x] == '1' || matrix[block_position_y + 3][block_position_x] == '#') {
                    
                    block_position_x = 10;
                    block_position_y = 1;
                    last_block_position_x = 10;
                    last_block_position_y = 1;
                    current_block = rand() % 2 + 1;
                    rotate_pos_block = 1;
                }
                break;
            case 0: // -
                if (matrix[block_position_y][block_position_x - 1] == '1' || matrix[block_position_y][block_position_x - 1] == '#' || matrix[block_position_y][block_position_x] == '#' || matrix[block_position_y][block_position_x] == '1' || matrix[block_position_y][block_position_x + 1] == '#' || matrix[block_position_y][block_position_x + 1] == '1' || matrix[block_position_y][block_position_x + 2] == '#' || matrix[block_position_y][block_position_x + 2] == '1') {
                    block_position_x = 10;
                    block_position_y = 1;
                    last_block_position_x = 10;
                    last_block_position_y = 1;
                    current_block = rand() % 2 + 1;
                    rotate_pos_block = 1;
                }
                break;
            }
            break;
        }

        // отрисовка блока

        cleaning_field_figure(matrix, last_block_position_x, last_block_position_y, current_block, rotate_pos_block);
        writing_field_figure(matrix, current_block, rotate_pos_block);



        // вывод матрицы
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                std::cout << matrix[i][j];
            }
            std::cout << '\n';
        }

        

        last_block_position_x = block_position_x;
        last_block_position_y = block_position_y;
        // спуск вниз на 1, блок падает вниз
        block_position_y += 1;


    }
}

// функции очистки и отрисовки поля после блоков
void cleaning_field_figure(char(&ptr_matrix)[32][32], int last_pos_x, int last_pos_y, int currentBlock, int rotate) {
    // cleaning field after figure
    switch (currentBlock) {
    case 1:
        ptr_matrix[last_pos_y][last_pos_x] = ' ';
        ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
        ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
        ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
        break;
    case 2:
        switch (rotate) {
        case 1: // T inverted
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
            break;
        case 2: // |-
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            break;
        case 3: // T главная точка центральная
            ptr_matrix[last_pos_y][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            break;
        case 4: // -|
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            break;
        }
        break;
    case 3:
        switch (rotate % 2) {
        case 1:
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 1][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 2][last_pos_x] = ' ';
            ptr_matrix[last_pos_y + 3][last_pos_x] = ' ';
            break;
        case 0:
            ptr_matrix[last_pos_y][last_pos_x - 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 1] = ' ';
            ptr_matrix[last_pos_y][last_pos_x + 2] = ' ';
            break;
        }

    }
}

void writing_field_figure(char(&ptr_matrix)[32][32], int currentBlock, int rotate) {


    // writing figure
    switch (currentBlock) {
    case 1:
        ptr_matrix[block_position_y][block_position_x] = '1';
        ptr_matrix[block_position_y][block_position_x + 1] = '1';
        ptr_matrix[block_position_y + 1][block_position_x] = '1';
        ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
        break;
    case 2:
        switch (rotate) {
        case 1: // T inverted
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x - 1] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
            break;
        case 2: // |-    <- figure
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x + 1] = '1';
            ptr_matrix[block_position_y + 2][block_position_x] = '1';
            break;
        case 3: // T исключение главная точка верхняя центраальная
            ptr_matrix[block_position_y][block_position_x - 1] = '1';
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            break;
        case 4: // -|
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x - 1] = '1';
            ptr_matrix[block_position_y + 2][block_position_x] = '1';
            break;
        }
        break;
    case 3: // I
        switch (rotate % 2) { // потому что поворотов фигуры всего 2
        case 1: // I
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y + 1][block_position_x] = '1';
            ptr_matrix[block_position_y + 2][block_position_x] = '1';
            ptr_matrix[block_position_y + 3][block_position_x] = '1';
            break;
        case 0: // -
            ptr_matrix[block_position_y][block_position_x - 1] = '1';
            ptr_matrix[block_position_y][block_position_x] = '1';
            ptr_matrix[block_position_y][block_position_x + 1] = '1';
            ptr_matrix[block_position_y][block_position_x + 2] = '1';
            break;
            

        }
        break;
    }

}
