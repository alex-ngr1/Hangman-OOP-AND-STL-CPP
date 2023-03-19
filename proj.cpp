#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <fstream>
#include <random>
#include <cstdlib>

using namespace std;

// Ограничение на количество попыток
const int MAX_WRONG = 6;
// кьасс расшифровки
class Word {
public:
    Word() {}
    Word(string word) : encrypted_word(word) {}
    string decrypt(int shift);
    void set_word(string word);
    string get_word();
private:
    string encrypted_word;
    string decrypted_word;
};
// разшифровка одного слова
string Word::decrypt(int shift) {
    string plain;
    for (char c : encrypted_word) {
        if (c >= 'A' && c <= 'Z') {
            c = c - shift;
            if (c < 'A') {
                c = c + 26;
            }
        } else if (c >= 'a' && c <= 'z') {
            c = c - shift;
            if (c < 'a') {
                c = c + 26;
            }
        }
        plain.push_back(c);
    }
    decrypted_word = plain;
    return plain;
}
// Расшифровка , обозначения здивга на 5 пунктов в вперед в алфавите
void Word::set_word(string word) {
    encrypted_word = word;
    decrypt(5);
}

string Word::get_word() {
    return decrypted_word;
}
// class hangman Выводит игру
class Hangman {
public:
    Hangman();
    void play_game();
private: // добовляет ошибки слова, использывание слова
    int wrong;
    string used;
    Word word;
    void draw_hangman();
};
// Рисовка висильницы если человек допустил ошибку
void Hangman::draw_hangman() {
    switch(wrong) {
        case 1:
            cout << "   _______\n";
            cout << "  |       |\n";
            cout << "  |       O\n";
            cout << "  |         \n";
            cout << "  |         \n";
            cout << "  |         \n";
            cout << "__|__\n";
            break;
        case 2:
            cout << "   _______\n";
            cout << "  |       |\n";
            cout << "  |       O\n";
            cout << "  |       |\n";
            cout << "  |         \n";
            cout << "  |         \n";
            cout << "__|__\n";
            break;
        case 3:
            cout << "   _______\n";
            cout << "  |       |\n";
            cout << "  |       O\n";
            cout << "  |      /|\n";
            cout << "  |         \n";
            cout << "  |         \n";
            cout << "__|__\n";
            break;
        case 4:
            cout << "   _______\n";
            cout << "  |       |\n";
            cout << "  |       O\n";
            cout << "  |      /|\\\n";
            cout << "  |         \n";
            cout << "  |         \n";
            cout << "__|__\n";
            break;
        case 5:
            cout << "   _______\n";
            cout << "  |       |\n";
            cout << "  |       O\n";
            cout << "  |      /|\\\n";
            cout << "  |      /  \n";
            cout << "  |         \n";
            cout << "__|__\n";
            break;
        case 6:
            cout << "   _______\n";
            cout << "  |       |\n";
            cout << "  |       O\n";
            cout << "  |      /|\\\n";
            cout << "  |      / \\\n";
            cout << "  |         \n";
            cout << "__|__\n";
            break;
        default:
            break;
    }
}



Hangman::Hangman() {
    // Выбираем случайное слово из файла и расшифровываем его
    std::vector<std::string> words;
    std::ifstream myfile("word.txt");
    std::string word_str;

    if (myfile.is_open()) {
        while (myfile >> word_str) {
            words.push_back(word_str);
        }
        myfile.close();
    } else {
        std::cout << "Unable to open file";
    }

    srand(time(0));
    std::random_shuffle(words.begin(), words.end());
    string encrypted_word = words[0];

    word.set_word(encrypted_word);
    wrong = 0;
    used = "";
}

void Hangman::play_game() {
    int start_time, end_time; // создаем переменные для времини
    srand(static_cast<unsigned int>(time(0)));
    cout << "Добро пожаловать в игру \"Весильница\". Удачи вам!\n";
    start_time = time(nullptr); // начало времини

    string THE_WORD = word.get_word();
    string soFar(THE_WORD.size(), '-');
    // Проверка использывание той же буквы и неправильно использывание буквы
    while ((wrong < MAX_WRONG) && (soFar != THE_WORD)) {
        cout << "\n\nОшибки: " << wrong << " из " << MAX_WRONG << endl;
        cout << "Неправильно использованные буквы: " << used << endl;
        cout << "Текущее слово: " << soFar << endl;
        cout << "Введите букву: ";
        char guess;
        cin >> guess;
        guess = toupper(guess);
        while (used.find(guess) != string::npos) {
            cout << "Вы уже использовали эту букву. Введите другую: ";
            cin >> guess;
            guess = toupper(guess);
        }
            used += guess; // добовления Буквы
    // Если буква находится в слове
    if (THE_WORD.find(guess) != string::npos) {
        cout << "Буква " << guess << " содержится в слове!\n";
        for (int i = 0; i < THE_WORD.length(); ++i) {
            if (THE_WORD[i] == guess) {
                soFar[i] = guess;
            }
        }
    } else {
        cout << "К сожалению, буквы " << guess << " нет в слове.\n";
        ++wrong; // добовления ошибки
        draw_hangman(); // ресовка висельницы
    }
}
// если максимум ошибок то выводит статистику и проигрыш
if (wrong == MAX_WRONG) {
    cout << "\nВас повесили!";
    cout << "\nКол-во попыток: " << wrong << std::endl;
} else {
    cout << "\nВы спасены!";
    cout << "\nКол-во попыток:" << wrong << std::endl;
}

end_time = time(nullptr);
int time_taken = end_time - start_time;
cout << "\nБыло загадано слово \"" << THE_WORD << "\".\n";
cout << "Игра закончена! Заняло " << time_taken << " секунд.\n";

}


// Запуск/Старт игры
int main(){
    Hangman game;
    game.play_game();
    return 0;
}