#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>


using namespace std;

int main()
{
    char str[] = "Hello World Test C++ AAA BBB aaa ccc"; // Початковий текст
    char strCopy[sizeof(str)]; // Копія рядка для збереження оригінального тексту
    strcpy(strCopy, str); // Копіюємо оригінальний рядок у резервний
    char seps[] = " :?!;,.\t\n"; // Роздільники для поділу тексту на слова
    cout << "Original text: " << str << endl; // Виводимо початковий текст

    char* token = strtok(str, seps); // Виділяємо перше слово (token)
    int lenResult = 0; // Довжина нового рядка, який ми сформуємо
    int countWord = 0; // Лічильник слів, які залишаться у результаті

    // Перший цикл: підрахунок довжини результату та кількості слів, що не закінчуються на "а" чи "А"
    while (token != NULL)
    {
        int last = strlen(token) - 1; // Індекс останнього символа у слові
        if (!(token[last] == 'a' || token[last] == 'A')) // Перевіряємо, чи слово НЕ закінчується на "а" або "А"
        {
            lenResult += (strlen(token) + 1); // Додаємо довжину слова + 1 для пробілу
            ++countWord; // Збільшуємо лічильник слів
        }
        token = strtok(NULL, seps); // Переходимо до наступного слова
    }

    // Виділення пам'яті для результуючого рядка
    char* resString = new char[lenResult]; // Виділяємо пам'ять для результату
    resString[0] = '\0'; // Ініціалізуємо порожній рядок

    // Відновлюємо оригінальний рядок
    strcpy(str, strCopy); // Відновлюємо початковий текст
    token = strtok(str, seps); // Знову ділимо текст на слова

    int currentNumberWord = 0; // Лічильник номеру поточного слова у результаті

    // Другий цикл: формування результуючого рядка
    while (token != NULL)
    {
        int last = strlen(token) - 1; // Індекс останнього символа у слові
        if (!(token[last] == 'a' || token[last] == 'A')) // Перевіряємо, чи слово НЕ закінчується на "а" або "А"
        {
            strcat(resString, token); // Додаємо слово до результуючого рядка
            ++currentNumberWord; // Збільшуємо лічильник доданих слів
            if (countWord != currentNumberWord) // Якщо це не останнє слово, додаємо пробіл
            {
                strcat(resString, " ");
            }
        }
        token = strtok(NULL, seps); // Переходимо до наступного слова
    }

    // Вивід результату
    cout << "\nResult:\n" << resString << endl;

    delete[] resString; // Звільняємо динамічно виділену пам'ять
    cout << "Press Enter to continue...";
    cin.get(); // Очікуємо натискання Enter

    return 0; // Завершення програми
}
