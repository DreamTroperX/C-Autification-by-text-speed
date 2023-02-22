#include <iostream>
#include <chrono>
#include <cstring>

using namespace std;

const double SPEED_LIMIT = 310.2;
const double ERROR_LIMIT = 96.6;

const double ALLOWED_DEVIATION = 0.1; // допустиме відхилення від параметрів становить 10%

const string TEXT_TO_TYPE = "Ой у лузі червона калина похилилася.";

// Функція для вимірювання часу вводу тексту
double measureTypingSpeed(string&input_text) {
    cout << "Enter the password: \n" << endl;

    auto start_time = chrono::steady_clock::now(); // запам'ятовуємо час початку вводу

    getline(cin, input_text); // зчитуємо введений текст

    auto end_time = chrono::steady_clock::now(); // запам'ятовуємо час закінчення вводу

    double time_diff = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() / 1000.0; // розраховуємо час вводу в секундах
    double text_length = static_cast<double>(TEXT_TO_TYPE.length()); // отримуємо довжину тексту

    double typing_speed = text_length / (time_diff / 60.0); // розраховуємо швидкість друку

    return typing_speed;
}

// Функція для підрахунку кількості помилок
double countErrors(string input_text) {
    int text_length = TEXT_TO_TYPE.length();
    int input_length = input_text.length();
    int error_count = 0;

    for (int i = 0; i < text_length; i++) {
        if (i >= input_length || TEXT_TO_TYPE[i] != input_text[i]) {
            error_count++;
        }
    }

    return static_cast<double>(error_count) / static_cast<double>(text_length) * 100.0;
}

int main() {
    string input_text;
    // вимірюємо швидкість друку та кількість помилок
    double typing_speed = measureTypingSpeed(input_text);
    double error_rate = countErrors(input_text);
    // порівнюємо отримані параметри з заданими параметрами
    if (typing_speed >= (SPEED_LIMIT * (1.0 - ALLOWED_DEVIATION)) && typing_speed <= (SPEED_LIMIT * (1.0 + ALLOWED_DEVIATION)) &&
        error_rate <= (ERROR_LIMIT * (1.0 + ALLOWED_DEVIATION))) {
        cout << "Authentication successful!" << endl;
    } else {
        cout << "Authentication failed. Please try again." << endl;
        cout << typing_speed<<" "<<error_rate << endl;
    }

    return 0;
}
