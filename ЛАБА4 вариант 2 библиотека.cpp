#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
template <typename T1, typename T2>
class Pair {
public:
	Pair() {}
	Pair(const T1& first, const T2& second) : first(first), second(second) {}

	void displayPair() const {
		std::cout << first << ": " << second << std::endl;
	}

	void savePairToFile(std::ofstream& outFile) const {
		outFile << first << " " << second << " ";
	}

private:
	T1 first;
	T2 second;
};
template <typename T> //Шаблон для представления сущностей(крч связи разных переменных и функций в классе оценок)

class NFiction {
	public:
	NFiction(const std::string& fiction, const std::string& nonfiction);
};
//Создание базового класса книга для управления его данными, внутри него определенны необ. хар-ки
class Book {
public:
	Book(const std::string& Title, const std::string& Author, const std::string& genre)
		: Title(Title), Author(Author), genre(genre) {}

	~Book() {} // ~ очищает память после работы с книгой 

	const std::string& getTitle() const {
		return Title;
	}

	const std::string& getAuthor() const {
		return Author;
	}

	const std::string& getGenre() const {
		return genre;
	}

	void setTitle(const std::string& newTitle) {
		Title = newTitle;
	}

	void setAuthor(const std::string& newAuthor) {
		Author = newAuthor;
	}

	void setGenre(const std::string& newGenre) {
		genre = newGenre;
	}

	void displayInfo() const {
		std::cout << "Название: " << Title << ", Автор: " << Author << ", Жанр: " << genre;
	}

	void saveToFile(std::ofstream& outFile) const {
		outFile << Title << " " << Author << " " << genre << " ";
	}

	static bool compareByTitle(const Book* book1, const Book* book2) { //корпоратор, сравнивает первые буквы фамилий авторов
		return book1->getAuthor() < book2->getAuthor();
	}
protected:
	std::string Title;
	std::string Author;
	std::string genre;
};

void modifyBook(Book* book) { //Функция изменения студента
	std::cout << "Книга найдена. Что вы хотите изменить?" << std::endl;
	std::cout << "1. Название" << std::endl;
	std::cout << "2. Автор" << std::endl;
	std::cout << "3. Жанр" << std::endl;
	int choice;
	std::cout << "Введите ваш выбор: ";
	std::cin >> choice;

	switch (choice) {
	case 1: {
				std::string newName;
				std::cout << "Введите новое название: ";
				std::cin >> newName;
				book->setTitle(newName);
				break;
	}
	case 2: {
				std::string newAuthor;
				std::cout << "Введите нового автора: ";
				std::cin >> newAuthor;
				book->setAuthor(newAuthor);
				break;
	}
	case 3: {
				std::string newGenre;
				std::cout << "Введите новый жанр: ";
				std::cin >> newGenre;
				book->setGenre(newGenre);
				break;
	}
	default:
		std::cout << "Неверный выбор." << std::endl;
	}
}

void saveBooksToFile(const std::vector<Book*>& books, const std::string& filename) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cerr << "Ошибка открытия файла для записи." << std::endl;
		return;
	}

	for (const auto* book : books) {
		book->saveToFile(outFile);
	}

	outFile.close();
}

int main() {
	setlocale(LC_ALL, "Russian");

	std::vector<Book*> books; //список студентов

	int choice;
	std::string filename;

	do {
		std::cout << "Меню:" << std::endl;
		std::cout << "1. Добавить книгу" << std::endl;
		std::cout << "2. Изменить данные о книге" << std::endl; //один из доп функционалов
		std::cout << "3. Вернуть книгу в библиотеку" << std::endl; 
		std::cout << "4. Найти книги" << std::endl;
		std::cout << "5. Вывести список книг" << std::endl;
		std::cout << "6. Сохранить в файл" << std::endl;
		std::cout << "7. Сортировать по автору" << std::endl;
		std::cout << "8. Выход" << std::endl;

		std::cout << "Введите ваш выбор: ";
		std::cin >> choice;

		switch (choice) {
		case 1: {
					std::string Title, Author, genre;
					std::cout << "Введите данные о книге:" << std::endl;
					std::cout << "название: ";
					std::cin >> Title;
					std::cout << "Автор: ";
					std::cin >> Author;
					std::cout << "Жанр: ";
					std::cin >> genre;
					books.push_back(new Book(Title, Author, genre)); //push back ставит на последнее место в векторе(списке) новую книгу
					break;
		}
			
		case 2: {
					std::string Title, Author;
					std::cout << "Введите данные о книге для изменения:" << std::endl;
					std::cout << "Название: ";
					std::cin >> Title;
					std::cout << "Автор: ";
					std::cin >> Author;

					auto it = std::find_if(books.begin(), books.end(), [&](const Book* book) { //автоматическая переменная auto короче 
						return book->getTitle() == Title && book->getAuthor() == Author;//принимает тип инициализированного выражения
					});//в переборе ищем от начала до канца списка пока выполнется 3-е условие, какое? а хрен его знает ваще))

					if (it != books.end()) {
						modifyBook(*it);
					}
					else {
						std::cout << "Книга не найдена." << std::endl;
					}

					break;
		}
			//доп задания можно их не делать
		case 3: {
					std::string Title, Author;
					std::cout << "Введите книги для возврата:" << std::endl;
					std::cout << "Название: ";
					std::cin >> Title;
					std::cout << "Автор: ";
					std::cin >> Author;

					auto it = std::find_if(books.begin(), books.end(), [&](const Book* book) {//такая же херня, думаю с этим просто смирится
						return book->getTitle() == Title && book->getAuthor() == Author;
					});

					if (it != books.end()) {
						delete* it;
						books.erase(it); //в it-e ллежит студент, удаляем его по команде
						std::cout << "Книга возвращена." << std::endl;
					}
					else {
						std::cout << "Книга не найдена." << std::endl;
					}

					break;
		}
		case 4: {
					std::string Title, Author;
					std::cout << "Введите данные книги для поиска:" << std::endl;
					std::cout << "Название: ";
					std::cin >> Title;
					std::cout << "Автор: ";
					std::cin >> Author;

					auto it = std::find_if(books.begin(), books.end(), [&](const Book* book) { //приятно
						return book->getTitle() == Title && book->getAuthor() == Author;
					});

					if (it != books.end()) {
						(*it)->displayInfo();
					}
					else {
						std::cout << "Книга не найдена." << std::endl;
					}

					break;
		}
		case 5: {
					std::cout << "Список книг:" << std::endl;
					for (const auto* book : books) {
						book->displayInfo();
					}
					break;
		}
		case 6: {
					std::cout << "Введите имя файла для сохранения данных: ";
					std::cin >> filename;
					saveBooksToFile(books, filename);
					break;
		}
		case 7: {
					std::sort(books.begin(), books.end(), Book::compareByTitle); //сортировка книг от начала до конца по корпаратору(условию)
					std::cout << "Список книг отсортирован по автору." << std::endl;
					break;
		}
		case 8:
			std::cout << "Выход." << std::endl;
			break;
		default:
			std::cout << "Неверный выбор." << std::endl;
		}
	} while (choice != 8);

	for (const auto* book : books) { //очистка
		delete book;
	}

	return 0;
}