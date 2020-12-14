#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <ctime>
#include <exception>
#include <iomanip>


/*

Реализовать полнофункциональную систему тестирования.

В системе должны быть  2 режима: Администратор и Тестируемый.
Описание режима работа для Тестируемого (в дальнейшем Гость).
+ Для входа в систему Гость должен зарегистрироваться. Данная процедура выполняется один раз, при дальнейших входах в систему доступ идет по логину и паролю.
+ При регистрации нужно указывать ФИО, телефон.
+ Важно, чтобы логины для пользователей были уникальными.
+ После входа Гость имеет возможность просмотреть свои предыдущие результаты тестирования, сдать новое тестирование.
+ Тестирование  может  осуществляться  по  различным  категориям.

+ После  сдачи  теста  Гость  видит  результат  тестирования,  количество  правильных ответов, процент правильных ответов и полученную оценку.
+ Студент имеет возможность прервать тестирование и продолжить его тогда, когда ему это будет удобно.
+ Оценивание нужно вести на основании 12-ти балльной системы, привязанной к количеству вопросов теста.
+ Пароли гостей хранятся в зашифрованном виде

Описание режима работа для Администратора (в дальнейшем Админ).
+ В системе может быть только один Админ, логин и пароль Админа задается при первом входе в программу.
+ В  дальнейшем  пароль  и  логин  можно  изменить  (но  данную  возможность имеет только Админ).
+ Пароль необходимо хранить только в зашифрованном виде.
+ При работе с системой Админ имеет следующие возможности:
+ управление  пользователями  –  создание,  удаление,  модификация  пользователей;
+ просмотр  статистики  –  количество пройденных тестов в системе в общем и по категориям.
+ Управление тестированием – Админ имеет возможность добавлять категории, тесты, вопросы к тестам, задавать правильные и неправильные ответы

Код  должен  быть  читабельным,  хорошо  прокомментированным,  и  использовать единую систему именования идентификаторов.



  Дополнительно
 + У каждого пользователя есть личная почта для общение
 + У каждого пользователя есть ip4 adresss
 + Есть функция Port Forwarding
 + Можно передавать админство
*/


class Exam;

template<const size_t size_data = 30, const size_t size_path = 100>
struct User_data
{
	enum ROLE { USER, ADMIN };

	ROLE m_role{};
	unsigned int m_phone_number;


	char m_mail[size_data]{};
	char m_name[size_data]{};
	char m_login[size_data]{};
	char m_surname[size_data]{};
	char m_password[size_data]{};
	char m_patronymic[size_data]{};
	char m_repeat_password[size_data]{};


	char m_ip[size_data]{};
	static char m_path[size_path];
	char m_test_pause[size_path]{};
	char m_path_for_mail[size_path]{};
	char m_path_for_result[size_path]{};

	static void set_path(const char* path)noexcept
	{
		strcpy_s(m_path, size_path, path);
	}

	static const char* get_path() noexcept
	{
		return m_path;
	}

	void set_role(const ROLE& role) noexcept
	{
		m_role = role;
	}

	const ROLE& get_role() const noexcept
	{
		return m_role;
	}

	void set_login(const char* login) noexcept
	{
		strcpy_s(m_login, login);
	}

	void set_password(const char* password) noexcept
	{
		strcpy_s(m_password, password);
	}

	void set_name(const char* name) noexcept
	{
		strcpy_s(m_name, name);
	}

	void set_surname(const char* surname) noexcept
	{
		strcpy_s(m_surname, surname);
	}

	void set_patronymic(const char* patronymic) noexcept
	{
		strcpy_s(m_patronymic, patronymic);
	}

	void set_phone_number(const int phone_number) noexcept
	{
		m_phone_number = phone_number;
	}

	void creat_path_for_mail(char* path) noexcept
	{
		strcpy_s(path, size_path, m_path);
		strcat_s(path, size_path, m_login);
		strcat_s(path, size_path, ".txt");
	}

	void creat_path_for_pause(char* path) noexcept
	{
		strcpy_s(path, size_path, m_path);
		strcat_s(path, size_path, m_login);
		strcat_s(path, size_path, m_name);
		strcat_s(path, size_path, ".bin");
	}

	void creat_ip(char* ip) noexcept
	{
		strcpy_s(ip, size_data, "192.168.");

		std::ostringstream ostr, ostr2;
		std::string number_to_string;

		ostr << rand() % 255;
		number_to_string = ostr.str();
		strcat_s(ip, size_data, number_to_string.c_str());
		strcat_s(ip, size_data, ".");

		ostr2 << rand() % 255;
		number_to_string = ostr2.str();
		strcat_s(ip, size_data, number_to_string.c_str());
	}

	void creat_path_for_result(char* path_result) noexcept
	{
		strcpy_s(path_result, size_path, m_path);
		strcat_s(path_result, size_path, m_patronymic);
		strcat_s(path_result, size_path, m_login);
		strcat_s(path_result, size_path, ".txt");
	}

	void creat_mail(char* mail)
	{
		size_t index;
		const size_t size = 8;

		strcpy_s(m_mail, mail);
		std::string site_domains[size]{ "@mail.ru","@gmail.com","@list.ru","@inbox.ru","@bk.ru","@yahoo.com","@outlook.com","@hotmail.com" };
		index = rand() % size;
		strcat_s(m_mail, site_domains[index].c_str());
	}

	friend  std::istream& operator>>(std::istream& is, User_data<>& user)
	{
		std::cout << '\n';
		std::cout << "Enter name          :  ";   is >> user.m_name;
		std::cout << "Enter surname       :  ";     is >> user.m_surname;
		std::cout << "Enter m_patronymic  :  ";     is >> user.m_patronymic;
		std::cout << "Enter phone number  :  ";     is >> user.m_phone_number;
		std::cout << "Enter login         :  ";     is >> user.m_login;
		std::cout << "Enter password      :  ";     is >> user.m_password;
		std::cout << "Repeat password     :  ";     is >> user.m_repeat_password;

		user.creat_mail(user.m_login);
		user.creat_path_for_mail(user.m_path_for_mail);
		user.creat_ip(user.m_ip);
		user.creat_path_for_result(user.m_path_for_result);
		user.creat_path_for_pause(user.m_test_pause);
		user.m_role = User_data<>::USER;

		return is;
	}

	friend  std::ostream& operator<<(std::ostream& os, const User_data<>& n)
	{
		std::cout << '\n';
		std::cout << "Name          : " << n.m_name << std::endl;
		std::cout << "Surname       : " << n.m_surname << std::endl;
		std::cout << "Patronymic    : " << n.m_patronymic << std::endl;
		std::cout << "Phone number  : " << n.m_phone_number << std::endl;
		std::cout << "Login         : " << n.m_login << std::endl;
		std::cout << "Mail          : " << n.m_mail << std::endl;
		std::cout << "Path          : " << n.m_path_for_mail << std::endl;
		std::cout << "Password      : " << n.m_password << std::endl;
		return os;
	}
};

char User_data<>::m_path[]{};

class Users
{
public:
	Users() = default;

	bool add(const User_data<>& user) noexcept
	{
		if (chek_login(user.m_login))  return false;

		m_users.push_back(user);
		return true;
	}

	const size_t get_size() const noexcept
	{
		return m_users.size();
	}

	void modifiy_user(const size_t index, const char* modify, const size_t select)noexcept
	{
		if (select == 1)m_users[index].set_name(modify);
		else if (select == 2)m_users[index].set_surname(modify);
		else if (select == 3)m_users[index].set_patronymic(modify);
		else if (select == 4)m_users[index].set_login(modify);
		else if (select == 5)m_users[index].set_password(modify);
	}

	bool print_test_result() const noexcept
	{
		size_t size;
		bool act = false;
		for (auto element : m_users)
		{
			std::fstream input(element.m_path_for_result);
			if (input) {
				input.seekg(0, std::ios::end);
				size = input.tellg();
				if (size)
				{
					act = true;
					input.seekg(0);
					std::string line;
					while (std::getline(input, line))
					{
						Sleep(50);
						std::cout << line << '\n';
					}
					std::cout << "\n\n";
				}
				input.close();
			}
		}
		if (act)  return true;

		return false;
	}

	bool result_empty()
	{
		size_t size;
		for (auto element : m_users)
		{
			std::fstream input(element.m_path_for_result);
			if (input) {
				input.seekg(0, std::ios::end);
				size = input.tellg();
				if (size) return false;
				input.close();
			}
		}
		return true;
	}

	void change_password_admin(const char* password) noexcept
	{
		for (auto& element : m_users)
		{
			if (element.get_role()) element.set_password(password);
		}
	}

	bool change_login_admin(const char* login) noexcept
	{
		if (!chek_login(login))
		{
			for (auto& element : m_users)
			{
				if (element.get_role())
				{
					element.set_login(login);
					return true;
				}
			}
		}
		return false;
	}

	void encrypting(char* password) noexcept
	{
		size_t size = strlen(password);
		for (size_t i = 0; i < size; ++i)
		{
			password[i] ^= 1;
		}
	}

	const User_data<>& get_ip(char* ip)
	{
		for (size_t i = 0; i < m_users.size(); ++i)
		{
			if (!strcmp(m_users[i].m_ip, ip)) return m_users[i];
		}
		throw std::invalid_argument("There is no user with this ip address!");
	}

	void pass_admin(const size_t index)noexcept
	{
		for (size_t i = 0; i < m_users.size(); ++i)
		{
			if (i == index) m_users[i].set_role(User_data<>::ADMIN);
			else m_users[i].set_role(User_data<>::USER);
		}
	}

	User_data<>& user_access(const size_t index)
	{
		if (m_users.size() > index) return m_users[index];
		else throw std::range_error("You are out of range");
	}

	void deleted(const size_t index)
	{
		if (m_users.size() > index) m_users.erase(m_users.begin() + index);
		else throw std::range_error("Out of range!");
	}

	bool chek_login(const std::string& login)const noexcept
	{
		for (size_t i = 0; i < m_users.size(); ++i) {
			if (m_users[i].m_login == login)
				return true;
		}
		return false;
	}

	bool sign_in(const char* login, const char* password)const noexcept
	{
		for (size_t i = 0; i < m_users.size(); ++i) {
			if (!strcmp(m_users[i].m_login, login) &&
				!strcmp(password, m_users[i].m_password))
			{
				return true;
			}
		}
		return false;
	}

	size_t get_index_admin()const noexcept
	{
		for (size_t i = 0; i < m_users.size(); ++i)
		{
			if (m_users[i].get_role())
			{
				return i;
			}
		}
	}

	User_data<>::ROLE get_role(const size_t index)const noexcept
	{
		return m_users[index].m_role;
	}

	const User_data<>& get_user(const char* login, const char* password)const
	{
		for (size_t i = 0; i < m_users.size(); ++i)
		{
			if (!strcmp(m_users[i].m_login, login) && !strcmp(m_users[i].m_password, password))
			{
				return m_users[i];
			}
		}
		throw std::invalid_argument("Not user!");
	}

	const std::string& get_path(const std::string& mail)const
	{
		for (auto element : m_users)
		{
			if (element.m_mail == mail)
			{
				return element.m_path_for_mail;
			}
		}
		throw std::invalid_argument("Not user!");
	}

private:

	friend std::ostream& operator<<(std::ostream& os, const Users& users)
	{
		char b = 177;
		for (size_t i = 0; i < users.m_users.size(); ++i)
		{

			os << b << b << std::right << std::setw(2) << std::setfill(' ') << i << ". " << b
				<< b << std::left << std::setw(12) << std::setfill(' ') << users.m_users[i].m_name << b
				<< b << std::left << std::setw(15) << std::setfill(' ') << users.m_users[i].m_surname << b
				<< b << std::left << std::setw(12) << std::setfill(' ') << users.m_users[i].m_patronymic << b
				<< b << std::left << std::setw(12) << std::setfill(' ') << users.m_users[i].m_phone_number << b
				<< b << std::left << std::setw(12) << std::setfill(' ') << users.m_users[i].m_login << b
				<< b << std::left << std::setw(18) << std::setfill(' ') << users.m_users[i].m_mail << b
				<< b << std::left << std::setw(12) << std::setfill(' ') << users.m_users[i].m_password << b;

			if (users.m_users[i].m_role) os << b << std::left << std::setw(8) << std::setfill(' ') << "ADMIN" << b;
			else os << b << std::left << std::setw(8) << std::setfill(' ') << "User" << b;

			os << b << std::left << std::setw(17) << std::setfill(' ') << users.m_users[i].m_ip << b;
			os << b << std::left << std::setw(40) << std::setfill(' ') << users.m_users[i].m_path_for_mail << b << b << '\n';
			for (size_t i = 0; i < 186; ++i)std::cout << b;
			std::cout << '\n';
		}
		return os;
	}

	std::vector<User_data<>> m_users;
};

const size_t size_question = 6;
const size_t size_answer = 4;
const size_t size_text = 50;

class Subject_tests
{
	struct One_test
	{
		char m_question[size_text];
		char m_answer_1[size_text];
		char m_answer_2[size_text];
		char m_answer_3[size_text];
		char m_answer_4[size_text];
		size_t m_correct_answer;
	};

	One_test m_arr_test[size_question];
	char m_subject[size_text];
	friend class Exam;

	friend std::ostream& operator<<(std::ostream& os, const Exam& exam);
	friend std::istream& operator>>(std::istream& is, Subject_tests& n)
	{
		std::cout << "\nEnter subject name\t: ";
		is.ignore();
		is.getline(n.m_subject, size_text);
		for (size_t a = 0; a < size_question; ++a)
		{
			std::cout << '\n' << a + 1 << ". " << "Question : ";
			is.getline(n.m_arr_test[a].m_question, size_text);

			size_t b = 0;

			std::cout << b++ << ") ";
			is.getline(n.m_arr_test[a].m_answer_1, size_text);

			std::cout << b++ << ") ";
			is.getline(n.m_arr_test[a].m_answer_2, size_text);

			std::cout << b++ << ") ";
			is.getline(n.m_arr_test[a].m_answer_3, size_text);

			std::cout << b << ") ";
			is.getline(n.m_arr_test[a].m_answer_4, size_text);

			do
			{
				std::cout << "\nEnter correctly answer\t: ";
				is >> n.m_arr_test[a].m_correct_answer;
				std::cin.ignore();
				if (n.m_arr_test[a].m_correct_answer >= 0 && n.m_arr_test[a].m_correct_answer < size_answer)
				{
					break;
				}
				else
				{
					if (n.m_arr_test[a].m_correct_answer > 1)
						std::cout << "\nThe correct answer should be from " << 0 << " to  " << 3;
					else
						std::cout << "\nThe correct answer can only be 0";
				}
			} while (true);

		}
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const Subject_tests& n)
	{
		std::cout << "\n--------------------------------------\nSubject name\t:\t" << n.m_subject;
		std::cout << "\nCount question = " << size_question << "\n--------------------------------------\n";

		for (size_t a = 0; a < size_question; ++a)
		{
			std::cout << "\n\n------------------------------------\n" << a + 1 << ". " << n.m_arr_test[a].m_question
				<< " ?\n";

			size_t b = 0;
			std::cout << b++ << ") " << n.m_arr_test[a].m_answer_1 << '\n';
			std::cout << b++ << ") " << n.m_arr_test[a].m_answer_2 << '\n';
			std::cout << b++ << ") " << n.m_arr_test[a].m_answer_3 << '\n';
			std::cout << b << ") " << n.m_arr_test[a].m_answer_4 << '\n';

			std::cout << '\n' << b << ") " << n.m_arr_test[a].m_correct_answer << '\n';

		}
		return os;
	}
};

class Exam
{
public:
	Exam() = default;

	void print_subject()const noexcept
	{
		for (size_t i = 0; i < m_arr_subject.size(); ++i)
		{
			std::cout << i << ". " << m_arr_subject[i].m_subject << '\n';
		}
	}

	const char* subject_name(const size_t index)const noexcept
	{
		return m_arr_subject[index].m_subject;
	}

	size_t get_size() const noexcept
	{
		return m_arr_subject.size();
	}

	void add(const Subject_tests& test)noexcept
	{
		m_arr_subject.push_back(test);
	}

	void delete_test(const size_t index)noexcept
	{
		m_arr_subject.erase(m_arr_subject.begin() + index);
	}

	size_t get_correct_answer(const size_t subject_index, const size_t test_index) const noexcept
	{
		return m_arr_subject[subject_index].m_arr_test[test_index].m_correct_answer;
	}

	const char* get_test_subject(const size_t index) const
	{
		if (m_arr_subject.size() > index)
		{
			return m_arr_subject[index].m_subject;
		}

		throw std::range_error("Out of range");
	}

	size_t get_size()noexcept
	{
		return m_arr_subject.size();
	}

	void print_testing(const size_t index) const noexcept
	{
		std::cout << "\n--------------------------------------\nSubject name\t:\t" << m_arr_subject[index].m_subject;
		std::cout << "\nCount question = " << size_question << "\n--------------------------------------\n";

		for (size_t a = 0; a < size_question; ++a)
		{
			std::cout << "\n\n------------------------------------\n" << a + 1 << ". " << m_arr_subject[index].m_arr_test[a].m_question
				<< " ?\n";

			size_t variant = 0;
			std::cout << variant++ << ") " << m_arr_subject[index].m_arr_test[a].m_answer_1 << '\n';
			std::cout << variant++ << ") " << m_arr_subject[index].m_arr_test[a].m_answer_2 << '\n';
			std::cout << variant++ << ") " << m_arr_subject[index].m_arr_test[a].m_answer_3 << '\n';
			std::cout << variant << ") " << m_arr_subject[index].m_arr_test[a].m_answer_4 << '\n';

		}
	}

private:

	std::vector<Subject_tests> m_arr_subject;

	friend std::ostream& operator<<(std::ostream& os, const Exam& exam)
	{
		std::cout << "\n\n____________________________________________\n\nCount subject\t: ";
		os << exam.m_arr_subject.size();
		std::cout << "\n____________________________________________\n\n";
		for (size_t a = 0; a < exam.m_arr_subject.size(); ++a)
		{
			std::cout << "\n----------------------------------\nSubject\t: ";
			os << a + 1 << ". " << exam.m_arr_subject[a].m_subject;

			std::cout << "\n----------------------------------\n\n";
			for (size_t b = 0; b < size_question; ++b)
			{
				std::cout << b + 1 << ". " << exam.m_arr_subject[a].m_arr_test[b].m_question << '\n';


				size_t variant = 0;
				std::cout << variant++ << ") " << exam.m_arr_subject[a].m_arr_test[b].m_answer_1 << '\n';
				std::cout << variant++ << ") " << exam.m_arr_subject[a].m_arr_test[b].m_answer_2 << '\n';
				std::cout << variant++ << ") " << exam.m_arr_subject[a].m_arr_test[b].m_answer_3 << '\n';
				std::cout << variant << ") " << exam.m_arr_subject[a].m_arr_test[b].m_answer_4 << '\n';

				std::cout << "\nCorrectly answer\t: ";
				os << exam.m_arr_subject[a].m_arr_test[b].m_correct_answer;
				std::cout << "\n\n----------------------------------\n\n";
			}
		}
		return os;
	}
};

class Time
{
public:
	Time()
	{
		Now();
	}

	void refresh()noexcept
	{
		Now();
	}


private:
	void Now()noexcept
	{
		size_t seconds = time(nullptr);
		size_t today = seconds % (60 * 60 * 24);
		size_t day = seconds / (60 * 60 * 24);

		m_minutes = (seconds / 60) % 60;
		m_hours = today / 3600 + 4; // 4 eto vremennaya razmetka baku
		m_day = day % 31 + 2;
		m_month = day % 12 - 2;
		m_year = (day / 365) + 1970;
	}

	friend std::ostream& operator<<(std::ostream& os, const Time& n)
	{
		os << std::right << std::setw(2) << std::setfill('0') << n.m_day << "."
			<< std::right << std::setw(2) << std::setfill('0') << n.m_month << '.' << n.m_year << "  "
			<< std::right << std::setw(2) << std::setfill('0') << n.m_hours << ":"
			<< std::right << std::setw(2) << std::setfill('0') << n.m_minutes << ' ';

		return os;
	}

	size_t m_day;
	size_t m_month;
	size_t m_year;
	size_t m_hours;
	size_t m_minutes;
};

class File
{
public:

	File(const std::string& path_user, const std::string& path_test, const std::string& frame)
	{
		m_path_test = path_test;
		m_path_user = path_user;
		m_ramka = frame;
	}

	void read_test(Subject_tests& subject_test, Exam& test)noexcept
	{
		m_fstrm.open(m_path_test, m_mode);
		while (m_fstrm.read(reinterpret_cast<char*>(&subject_test), sizeof(Subject_tests)))
		{
			test.add(subject_test);
		}
		m_fstrm.close();
	}

	void write_test(Subject_tests& subject_test)noexcept
	{
		m_fstrm.open(m_path_test, m_mode);
		m_fstrm.write(reinterpret_cast<char*>(&subject_test), sizeof(Subject_tests));
		m_fstrm.close();
	}

	void write_user(User_data<>& sign_up)noexcept
	{
		m_fstrm.open(m_path_user, m_mode);
		m_fstrm.write(reinterpret_cast<char*>(&sign_up), sizeof(User_data<>));
		m_fstrm.close();
	}

	void read_user(User_data<>& user, Users& users)noexcept
	{
		m_fstrm.open(m_path_user, m_mode);
		if (m_fstrm)
		{
			while (m_fstrm.read(reinterpret_cast<char*>(&user), sizeof(User_data<>)))
			{
				users.add(user);
			}
			m_fstrm.close();
		}
	}

	bool result_read(const char* path) noexcept
	{
		m_fstrm.open(path, m_mode);
		if (m_fstrm) {
			m_fstrm.seekg(0, std::ios::end);
			size_t size = m_fstrm.tellg();
			if (size)
			{
				m_fstrm.seekg(0);
				std::string line;
				while (std::getline(m_fstrm, line))
				{
					Sleep(350);
					std::cout << line << '\n';
				}
			}
			else
			{
				return false;
			}
			m_fstrm.close();
			return true;
		}

	}

	bool result_empty(const char* path) noexcept
	{
		m_fstrm.open(path, m_mode);
		if (m_fstrm) {
			m_fstrm.seekg(0, std::ios::end);
			size_t size = m_fstrm.tellg();
			m_fstrm.close();
			if (size) return false;
		}
		return true;
	}

	bool inbox_read(const char* path)noexcept
	{
		m_fstrm.open(path, m_mode);
		if (m_fstrm) {
			m_fstrm.seekg(0);
			size_t size = 0;
			m_fstrm.seekg(0, std::ios::end);
			size = m_fstrm.tellg();
			if (!size)return false;
			m_fstrm.seekg(0);
			std::string line;
			while (std::getline(m_fstrm, line))
			{
				std::cout << line << '\n';
			}
			m_fstrm.close();
			return true;
		}
		return false;
	}

	void send_message(const std::string& path, const char* name)
	{
		m_fstrm.open(path, m_mode);
		if (m_fstrm) {
			std::cout << "Chat is opened!\nEnter message\n\nSend message - 0\n\n";
			std::string text;
			m_fstrm << name << " : ";
			do
			{
				std::getline(std::cin, text);
				if (text == "0")
				{
					std::cout << "Message send\n";
					break;
				}
				m_fstrm << text << "\n";
			} while (true);
			m_fstrm << "\n\n";
			m_fstrm.close();
		}
	}

	void overwrite_users(Users& users)noexcept
	{
		std::ios::openmode mode = std::ios::binary | std::ios::trunc | std::ios::in | std::ios::out;
		m_fstrm.open(m_path_user, mode);
		for (size_t i = 0; i < users.get_size(); ++i)
		{
			try
			{
				m_fstrm.write(reinterpret_cast<char*>(&users.user_access(i)), sizeof(User_data<>));
			}
			catch (std::range_error& ex)
			{
				std::cout << ex.what() << '\n';
			}
		}
		m_fstrm.close();
	}

	bool read_ramka(char& simvol)const noexcept
	{
		std::ifstream fileread(m_ramka);
		if (fileread)
		{
			fileread.read(reinterpret_cast<char*>(&simvol), sizeof(char));
			fileread.close();
			return true;
		}
		return false;
	}

	bool write_ramka(char& simvol)noexcept
	{
		std::ofstream filewrite(m_ramka);
		if (filewrite)
		{
			filewrite.write(reinterpret_cast<char*>(&simvol), sizeof(char));
			filewrite.close();
			return true;
		}
		return false;
	}

	bool write_pause(char* path, size_t& j, size_t& count, size_t& index)noexcept
	{
		std::fstream filewrite(path, std::ios::app);
		if (filewrite)
		{
			filewrite.write(reinterpret_cast<char*>(&j), sizeof(size_t));
			filewrite.write(reinterpret_cast<char*>(&count), sizeof(size_t));
			filewrite.write(reinterpret_cast<char*>(&index), sizeof(size_t));
			filewrite.close();
			return true;
		}
		return false;
	}

	bool removve(const char* path)noexcept
	{
		if (std::remove(path) != 0)
			return false;
		else
			return true;
	}

	bool read_pause(char* path, size_t& j, size_t& count, size_t& index)
	{
		std::fstream filewrite(path);
		if (filewrite)
		{
			filewrite.read(reinterpret_cast<char*>(&j), sizeof(size_t));
			filewrite.read(reinterpret_cast<char*>(&count), sizeof(size_t));
			filewrite.read(reinterpret_cast<char*>(&index), sizeof(size_t));
			filewrite.close();
			return true;
		}
		return false;
	}

private:
	std::ios::openmode m_mode = std::ios::binary | std::ios::app | std::ios::in | std::ios::out;
	std::string m_path_user;
	std::string m_path_test;
	std::string m_ramka;
	std::fstream m_fstrm;
};

void loading_successful(const char b)
{
	char a = 221;
	char arr[60]{};
	const int size = 100;
	const int size_frame = 58;

	for (size_t j = 0, i = 0; j <= size; j += 2)
	{
		system("cls");
		if (j % 2 == 0) arr[i++] = a;
		std::cout << " ";
		for (size_t i = 0; i < size_frame; ++i)std::cout << b;
		std::cout << "\n " << b << b << "\t\t\t\t\t\t\t " << b << b << '\n'
			<< " " << b << b << "\t\t\tLOADING " << std::left << std::setw(3) << std::setfill(' ') << j
			<< " %\t\t\t " << b << b << "\n " << b << b << "  " << std::left << std::setw(52) << std::setfill(' ') << arr
			<< b << b << '\n' << " " << b << b << "\t\t\t\t\t\t\t " << b << b << '\n' << " ";
		for (size_t i = 0; i < size_frame; ++i)std::cout << b;
		std::cout << "\n\n";

		Sleep(0);
	}
}

void loading_error(const char b)
{
	const char loading = 221;
	const int size = 100;
	int size_load = rand() % size;
	const int size_frame = 58;
	char arr[size]{};

	for (size_t j = 0, i = 0; j <= size_load; j += 2)
	{
		system("cls");
		if (j % 2 == 0) arr[i++] = loading;
		std::cout << " ";
		for (size_t i = 0; i < size_frame; ++i)std::cout << b;

		std::cout << "\n " << b << b << "\t\t\t\t\t\t\t " << b << b << '\n' << " " << b
			<< b << "\t\t\tLOADING " << std::left << std::setw(3) << std::setfill(' ') <<
			j << " %\t\t\t " << b << b << "\n " << b << b << "  " << std::left << std::setw(52)
			<< std::setfill(' ') << arr << b << b << '\n' << " " << b << b;

		std::cout << "\t\t      ERROR LOADING !!!\t\t\t \a";

		std::cout << b << b << '\n' << " ";
		for (size_t i = 0; i < size_frame; ++i)std::cout << b;
		std::cout << "\n\n";

		Sleep(0);
	}
}

int grading(const int result)
{
	int rating;
	if (result >= 95) { rating = 12; }
	else if (result >= 90) { rating = 11; }
	else if (result >= 85) { rating = 10; }
	else if (result >= 80) { rating = 9; }
	else if (result >= 75) { rating = 8; }
	else if (result >= 70) { rating = 7; }
	else if (result >= 60) { rating = 6; }
	else if (result >= 50) { rating = 5; }
	else if (result >= 40) { rating = 4; }
	else if (result >= 30) { rating = 3; }
	else if (result >= 20) { rating = 2; }
	else if (result >= 10) { rating = 1; }
	else if (result >= 0) { rating = 0; }
	return rating;
}


enum MainMenyu
{
	EXIT, SIGN_UP, SIGN_IN
};

enum AdminMenyu
{
	COME_BACK = -1, PASS_ADMIN = 1, SEND_MESSAGE, INBOX_MESSAGE, REMOTE_CONNECTION, INTERNET, CHANGE_PASSWORD, CHANGE_LOGIN, PRINT_USERS,
	CREAT_USER, DELETE_USER, MODIFIY_USER, PRINT_TEST, CREATE_TEST, PRINT_RESULT_TEST
};

enum UserMenyu
{
	PASS_THE_TEST = 1, RESULT_TEST_IP = 4, RESULT_TEST = 5
};

int main()
{
	srand(time(nullptr));
	system("color e4");

	std::string location = "";
	std::string path_users = "Users.txt";
	std::string path_test = "test_result.txt";
	std::string path_frame = "frame.bin";

	size_t action, act, correct_answer, index, result, rating, j;
	const int size = 6;
	char modify[50];
	char login[30];
	char password[30];
	char old_password[30];
	char password_repeat[30];
	char ip[30];
	std::fstream output;

	Time time;
	Exam test;
	Users users;
	User_data<>::set_path(location.c_str());
	User_data<> sign_up, sig_up_ip, user;
	Subject_tests subject_test;

	std::string path, mail;

	bool chek = true, internet = true;

	char b = 179;
	const int frame_size_1 = 30;
	const int frame_size_2 = 28;
	const int frame_size_3 = 31;
	const int NAME = 1;
	const int SURNAME = 2;
	const int PATRONYMIC = 3;

	File file(path_users, path_test, path_frame);
	std::ios::openmode mode = std::ios::binary | std::ios::app | std::ios::in | std::ios::out;
	std::cout << std::boolalpha;



	if (!file.read_ramka(b))
	{
		std::cout << "Select a frame for the program\n";
		std::cout << "1) view :   " << b << b << b << b << b << b << b << b << b << b << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << b << b << b << b << b << b << b << b << b << b << "\n\n";
		b--;
		std::cout << "2) view :   " << b << b << b << b << b << b << b << b << b << b << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << b << b << b << b << b << b << b << b << b << b << "\n\n";
		b--;
		std::cout << "3) view :   " << b << b << b << b << b << b << b << b << b << b << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << b << b << b << b << b << b << b << b << b << b << "\n\n";
		b--;
		std::cout << "4) view :   " << b << b << b << b << b << b << b << b << b << b << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << b << b << b << b << b << b << b << b << b << b << "\n\n";
		b += 43;
		std::cout << "5) view :   " << b << b << b << b << b << b << b << b << b << b << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << "        " << b << b << '\n';
		std::cout << "            " << b << b << b << b << b << b << b << b << b << b << b << b << "\n\n";
		do
		{
			std::cout << "Make a choice\n";
			std::cin >> action;
			if (action == 1) { b = 179; break; }
			else if (action == 2) { b = 178; break; }
			else if (action == 3) { b = 177; break; }
			else if (action == 4) { b = 176; break; }
			else if (action == 5) { b = 219; break; }
			else { std::cout << "Incorrect choose\n"; }
		} while (true);
		file.write_ramka(b);
		system("cls");
	}

	file.read_test(subject_test, test);
	file.read_user(user, users);


	if (!users.get_size())
	{
		while (true)
		{
			std::cout << "\n\n<< Fill in the registration Admin >> \n\n";
			std::cin >> sign_up;
			system("cls");

			if (!strcmp(sign_up.m_password, sign_up.m_repeat_password)) {
				sign_up.set_role(User_data<>::ADMIN);
				users.encrypting(sign_up.m_password);
				users.add(sign_up);
				file.write_user(sign_up);
				break;
			}
			else {
				std::cout << "Password mismatch\n";
			}
		}
	}

	do
	{
		time.refresh();

		for (size_t i = 0; i < frame_size_1; ++i)std::cout << b;
		std::cout << '\n' << b << b << "                          " << b << b << '\n'
			<< b << b << " Data : " << time << b << b << '\n'
			<< b << b << "                          " << b << b << '\n'
			<< b << b << "    0 - Exit              " << b << b << '\n'
			<< b << b << "    1 - Sign up           " << b << b << '\n'
			<< b << b << "    2 - Sign in           " << b << b << '\n'
			<< b << b << "                          " << b << b << '\n'
			<< b << b << "                          " << b << b << '\n';
		for (size_t i = 0; i < frame_size_1; ++i)std::cout << b;
		std::cout << "\n\n";

		std::cin >> action;
		system("cls");
		std::cin.ignore();
		if (action == EXIT) {
			break;
		}
		else if (action == SIGN_UP)
		{
			for (size_t i = 0; i < 39; ++i)std::cout << b;
			std::cout << '\n';
			std::cout << b << b << "                                   " << b << b << '\n';
			std::cout << b << b << "   Fill in the registration User   " << b << b << '\n';
			std::cout << b << b << "                                   " << b << b << '\n';
			for (size_t i = 0; i < 39; ++i)std::cout << b;
			std::cout << "\n\n";
			std::cin >> sign_up;

			if (!strcmp(sign_up.m_password, sign_up.m_repeat_password)) {
				users.encrypting(sign_up.m_password);
				for (size_t i = 0; i < 39; ++i)std::cout << b;
				std::cout << '\n' << b << b << "                                   " << b << b << '\n';

				if (users.add(sign_up)) std::cout << b << b << "   Registration was successful     " << b << b << '\n';
				else std::cout << b << b << "  A user with such data exists     " << b << b << '\n';

				std::cout << b << b << "                                   " << b << b << '\n';
				for (size_t i = 0; i < 39; ++i)std::cout << b;
				std::cout << "\n\n";

			}
			else {
				for (size_t i = 0; i < 25; ++i)std::cout << b;
				std::cout << '\n' << b << b << "                     " << b << b << '\n';
				std::cout << b << b << "  Password mismatch  " << b << b << '\n';
				std::cout << b << b << "                     " << b << b << '\n';
				for (size_t i = 0; i < 25; ++i)std::cout << b;
				std::cout << "\n\n";
			}
		}
		else if (action == SIGN_IN)
		{
			for (size_t i = 0; i < frame_size_2; ++i)std::cout << b;
			std::cout << '\n' << b << b << "                        " << b << b << '\n'
				<< b << b << " Enter data for Sign in " << b << b << '\n'
				<< b << b << "                        " << b << b << '\n';
			for (size_t i = 0; i < frame_size_2; ++i)std::cout << b;
			std::cout << "\n\n";

			std::cout << "\nEnter data for Sign in\n";
			std::cout << "Login     :  ";
			std::cin >> login;

			std::cout << "Password  :  ";
			std::cin >> password;
			system("cls");

			users.encrypting(password);

			if (users.sign_in(login, password))
			{
				try
				{
					sign_up = users.get_user(login, password);
				}
				catch (std::exception& ex)
				{
					std::cout << ex.what();
				}

				if (!sign_up.m_role)
				{
					do
					{
						time.refresh();
						for (size_t i = 0; i < 30; ++i)std::cout << b;
						std::cout << '\n' << b << b << "                          " << b << b << '\n'
							<< b << b << " Data : " << time << b << b << '\n'
							<< b << b << "                          " << b << b << '\n'
							<< b << b << "  " << std::left << std::setw(16) << std::setfill(' ') << sign_up.m_name << "( USER )" << b << b << '\n'
							<< b << b << "  Internet status : " << std::left << std::setw(6) << std::setfill(' ') << internet << b << b << '\n'
							<< b << b << "                          " << b << b << '\n'
							<< b << b << "                          " << b << b << '\n'
							<< b << b << " -1 - Come back           " << b << b << '\n'
							<< b << b << "  0 - Exit                " << b << b << '\n'
							<< b << b << "  1 - Pass the test       " << b << b << '\n'
							<< b << b << "  2 - Send Message        " << b << b << '\n'
							<< b << b << "  3 - Inbox               " << b << b << '\n'
							<< b << b << "  4 - Enter on ip adress  " << b << b << '\n'
							<< b << b << "  5 - Result test         " << b << b << '\n'
							<< b << b << "                          " << b << b << '\n'
							<< b << b << "                          " << b << b << '\n';
						for (size_t i = 0; i < 30; ++i) std::cout << b;
						std::cout << "\n\n";
						std::cin >> action;
						system("cls");

						if (action == COME_BACK || action == EXIT)
						{
							break;
						}
						else if (action == PASS_THE_TEST)
						{
							if (test.get_size())
							{
								j = 0; correct_answer = 0;
								if (!file.read_pause(sign_up.m_test_pause, j, correct_answer, index))
								{
									std::cout << "\n\n------------------------\n\n";
									test.print_subject();
									std::cout << "\n----------------------------\n\n";

									std::cout << "Please choose subject for test\n";
									do
									{
										std::cin >> index;

										if (index < test.get_size() && index >= 0) break;
										else  std::cout << "Incorect choose\n";

									} while (true);

									system("cls");

									try
									{
										std::cout << "\n\nYou select :  test on " << test.get_test_subject(index) << "\n";
									}
									catch (std::exception& ex)
									{
										std::cout << ex.what() << "\n";
									}
								}
								else
								{
									std::cout << "Continue test\n";
								}

								test.print_testing(index);
								std::cout << "\n\n-1  Leave tests for later\n\n";

								for (j; j < size; ++j)
								{
									do
									{
										std::cout << j + 1 << ") ";
										std::cin >> act;
										if (act == -1)
										{
											file.write_pause(sign_up.m_test_pause, j, correct_answer, index);
											break;
										}
										if (act >= 0 && act < 4) break;
										else std::cout << "There is no such option\n\n";

									} while (true);

									if (act == -1)break;

									if (test.get_correct_answer(index, j) == act) correct_answer++;
								}

								if (act != -1)
								{
									file.removve(sign_up.m_test_pause);
									if (correct_answer) result = correct_answer * 100 / size;
									else  result = correct_answer;

									rating = grading(result);

									std::cout << "\nresult = " << result << " % \n";
									std::cout << "Number of correct answers    : " << correct_answer << '\n';
									std::cout << "Number of incorrect answers  : " << size - correct_answer << '\n';
									std::cout << "Rating : " << rating << '\n';

									output.open(sign_up.m_path_for_result, mode);
									if (output) {
										std::string text;
										time.refresh();

										output << b << b << std::left << std::setw(12) << std::setfill(' ') << sign_up.m_name << b
											<< b << std::left << std::setw(12) << std::setfill(' ') << sign_up.m_surname << b
											<< b << std::left << std::setw(12) << std::setfill(' ') << sign_up.m_patronymic << b
											<< b << std::left << std::setw(13) << std::setfill(' ') << sign_up.m_phone_number << b
											<< b << std::left << std::setw(18) << std::setfill(' ') << sign_up.m_mail << b
											<< b << std::left << std::setw(12) << std::setfill(' ') << test.subject_name(index) << b
											<< b << std::left << std::setw(7) << std::setfill(' ') << result << " % " << b
											<< b << std::left << std::setw(6) << std::setfill(' ') << correct_answer << b
											<< b << std::left << std::setw(6) << std::setfill(' ') << size - correct_answer << b
											<< b << std::left << std::setw(8) << std::setfill(' ') << rating << b
											<< b << std::left << std::setw(15) << std::setfill(' ') << time << b << b << '\n';
										for (size_t i = 0; i < 151; ++i)output << b;
										output << '\n';
										std::cout << '\n';
										output.close();
									}
								}
							}
							else {
								std::cout << "\nNot test!\n\n";
							}
						}
						else if (action == 2)
						{
							if (internet)
							{
								std::cout << "Enter the mail to whom you want to send\n";
								std::cin >> mail;
								try
								{
									path = users.get_path(mail);
									file.send_message(path, sign_up.m_name);
								}
								catch (std::exception& ex)
								{
									std::cout << ex.what() << '\n';
								}
							}
							else {
								std::cout << "No internet\n";
							}
						}
						else if (action == 3)
						{
							if (internet) {
								if (!file.inbox_read(sign_up.m_path_for_mail)) {
									std::cout << "You don't have a message\n";
								}
							}
							else {
								std::cout << "No internet\n";
							}
						}
						else if (action == 4) {
							if (internet) {
								std::cout << "Enter ip address for remote connection\n";
								std::cin >> ip;
								try
								{
									sig_up_ip = users.get_ip(ip);
								}
								catch (std::exception& ex)
								{
									chek = false;
									std::cout << ex.what() << '\n';
								}

								if (chek)
								{
									do
									{
										time.refresh();
										std::cout << " Data : " << time;
										std::cout << "\n-1 Come back\nEnter data for Sign in on ip adress\n";
										std::cout << "Login     :  ";
										std::cin >> login;
										if (!strcmp(login, "-1"))break;
										std::cout << "Password  :  ";
										std::cin >> password;
										if (!strcmp(password, "-1"))break;
										system("cls");

										users.encrypting(password);

										if (!strcmp(sig_up_ip.m_password, password) && !strcmp(sig_up_ip.m_login, login)) break;
										else {
											loading_error(b);
											std::cout << "Data entered incorrectly\n";
										}

									} while (true);

									if (!strcmp(sig_up_ip.m_password, password) && !strcmp(sig_up_ip.m_login, login))
									{
										loading_successful(b);
										std::cout << "\n Loading successful done\n";
										do
										{
											time.refresh();
											for (size_t i = 0; i < 30; ++i)std::cout << b;
											std::cout << '\n' << b << b << "                          " << b << b << '\n';
											std::cout << b << b << " Data : " << time << b << b << '\n';
											std::cout << b << b << "                          " << b << b << '\n';
											std::cout << b << b << "  " << std::left << std::setw(16) << std::setfill(' ') << sig_up_ip.m_name << "( USER )" << b << b << '\n';
											std::cout << b << b << "  Internet status : " << std::left << std::setw(6) << std::setfill(' ') << internet << b << b << '\n';
											std::cout << b << b << "                          " << b << b << '\n';
											std::cout << b << b << "                          " << b << b << '\n';
											std::cout << b << b << " -1 - Come back           " << b << b << '\n';
											std::cout << b << b << "  0 - Exit                " << b << b << '\n';
											std::cout << b << b << "  1 - Pass the test       " << b << b << '\n';
											std::cout << b << b << "  2 - Send Message        " << b << b << '\n';
											std::cout << b << b << "  3 - Inbox               " << b << b << '\n';
											std::cout << b << b << "  4 - Result test         " << b << b << '\n';
											std::cout << b << b << "                          " << b << b << '\n';
											std::cout << b << b << "                          " << b << b << '\n';
											for (size_t i = 0; i < 30; ++i)std::cout << b;
											std::cout << "\n\n";
											std::cin >> action;
											system("cls");
											if (action == COME_BACK || action == EXIT)
											{
												break;
											}
											else if (action == PASS_THE_TEST)
											{
												if (test.get_size())
												{
													j = 0; correct_answer = 0;
													if (!file.read_pause(sig_up_ip.m_test_pause, j, correct_answer, index))
													{
														std::cout << "\n\n------------------------\n\n";
														test.print_subject();
														std::cout << "\n----------------------------\n\n";

														std::cout << "Please choose subject for test\n";
														do
														{
															std::cin >> index;

															if (index < test.get_size() && index >= 0) break;
															else  std::cout << "Incorect choose\n";

														} while (true);

														system("cls");

														try {
															std::cout << "\n\nYou select :  test on " << test.get_test_subject(index) << "\n";
														}
														catch (std::exception& ex) {
															std::cout << ex.what() << "\n";
														}
													}
													else
													{
														std::cout << "Continue test\n";
													}

													test.print_testing(index);
													std::cout << "\n\n-1  Leave tests for later\n\n";

													for (j; j < size; ++j)
													{
														do
														{
															std::cout << j + 1 << ") ";
															std::cin >> act;
															if (act == -1) {

																file.write_pause(sig_up_ip.m_test_pause, j, correct_answer, index);
																break;
															}
															if (act >= 0 && act < 4) break;
															else std::cout << "There is no such option\n\n";

														} while (true);

														if (act == -1) break;

														if (test.get_correct_answer(index, j) == act) correct_answer++;
													}

													if (act != -1)
													{
														file.removve(sig_up_ip.m_test_pause);

														if (correct_answer) result = correct_answer * 100 / size;
														else  result = correct_answer;

														rating = grading(result);

														std::cout << "\nresult = " << result << " % \n";
														std::cout << "Number of correct answers    : " << correct_answer << '\n';
														std::cout << "Number of incorrect answers  : " << size - correct_answer << '\n';
														std::cout << "Rating : " << rating << '\n';

														output.open(sig_up_ip.m_path_for_result, mode);
														if (output) {
															std::string text;
															time.refresh();

															output << b << b << std::left << std::setw(12) << std::setfill(' ') << sig_up_ip.m_name << b
																<< b << std::left << std::setw(12) << std::setfill(' ') << sig_up_ip.m_surname << b
																<< b << std::left << std::setw(12) << std::setfill(' ') << sig_up_ip.m_patronymic << b
																<< b << std::left << std::setw(13) << std::setfill(' ') << sig_up_ip.m_phone_number << b
																<< b << std::left << std::setw(18) << std::setfill(' ') << sig_up_ip.m_mail << b
																<< b << std::left << std::setw(12) << std::setfill(' ') << test.subject_name(index) << b
																<< b << std::left << std::setw(7) << std::setfill(' ') << result << " % " << b
																<< b << std::left << std::setw(6) << std::setfill(' ') << correct_answer << b
																<< b << std::left << std::setw(6) << std::setfill(' ') << size - correct_answer << b
																<< b << std::left << std::setw(8) << std::setfill(' ') << rating << b
																<< b << std::left << std::setw(15) << std::setfill(' ') << time << b << b << '\n';
															for (size_t i = 0; i < 151; ++i)output << b;
															output << '\n';
															std::cout << '\n';
															output.close();
														}
													}
												}
												else {
													std::cout << "\nNot test!\n\n";
												}
											}
											else if (action == 2)
											{
												if (internet)
												{

													std::cout << "Enter the mail to whom you want to send\n";

													std::cin >> mail;
													try
													{
														path = users.get_path(mail);
														file.send_message(path, sig_up_ip.m_name);
													}
													catch (std::exception& ex)
													{
														std::cout << ex.what() << '\n';
													}
												}
												else
												{
													std::cout << "No internet\n";
												}

											}
											else if (action == 3)
											{
												if (internet)
												{
													if (!file.inbox_read(sig_up_ip.m_path_for_mail))
													{
														std::cout << "You don't have a message\n";
													}
												}
												else
												{
													std::cout << "No internet\n";
												}
											}
											else if (action == 4)
											{
												if (!file.result_empty(sig_up_ip.m_path_for_result))
												{
													std::cout << "\nYour result\n";
													for (size_t i = 0; i < 151; ++i)std::cout << b;
													std::cout << '\n';
													std::cout << b << b << std::left << std::setw(12) << std::setfill(' ') << "Name" << b
														<< b << std::left << std::setw(12) << std::setfill(' ') << "Surname" << b
														<< b << std::left << std::setw(12) << std::setfill(' ') << "Patronymic" << b
														<< b << std::left << std::setw(13) << std::setfill(' ') << "Phone number" << b
														<< b << std::left << std::setw(18) << std::setfill(' ') << "Mail" << b
														<< b << std::left << std::setw(12) << std::setfill(' ') << "Subject name" << b
														<< b << std::left << std::setw(10) << std::setfill(' ') << "Result (%)" << b
														<< b << std::left << std::setw(6) << std::setfill(' ') << "Right" << b
														<< b << std::left << std::setw(6) << std::setfill(' ') << "Wrong" << b
														<< b << std::left << std::setw(8) << std::setfill(' ') << "Rating" << b
														<< b << std::left << std::setw(18) << std::setfill(' ') << " dd.mm.yy    h:m" << b << b << '\n';
													for (size_t i = 0; i < 151; ++i)std::cout << b;
													std::cout << '\n';
													file.result_read(sig_up_ip.m_path_for_result);
												}
												else
												{
													std::cout << "You haven't passed the tests\n";
												}
											}
											else {
												std::cout << "\nIncorrect choice\n";
											}

										} while (true);
									}
								}
							}
							else {
								std::cout << "No internet\n";
							}
						}
						else if (action == 5)
						{
							if (!file.result_empty(sign_up.m_path_for_result))
							{
								std::cout << "\nYour result\n";
								for (size_t i = 0; i < 151; ++i)std::cout << b;
								std::cout << '\n';
								std::cout << b << b << std::left << std::setw(12) << std::setfill(' ') << "Name" << b
									<< b << std::left << std::setw(12) << std::setfill(' ') << "Surname" << b
									<< b << std::left << std::setw(12) << std::setfill(' ') << "Patronymic" << b
									<< b << std::left << std::setw(13) << std::setfill(' ') << "Phone number" << b
									<< b << std::left << std::setw(18) << std::setfill(' ') << "Mail" << b
									<< b << std::left << std::setw(12) << std::setfill(' ') << "Subject name" << b
									<< b << std::left << std::setw(10) << std::setfill(' ') << "Result (%)" << b
									<< b << std::left << std::setw(6) << std::setfill(' ') << "Right" << b
									<< b << std::left << std::setw(6) << std::setfill(' ') << "Wrong" << b
									<< b << std::left << std::setw(8) << std::setfill(' ') << "Rating" << b
									<< b << std::left << std::setw(18) << std::setfill(' ') << " dd.mm.yy    h:m" << b << b << '\n';
								for (size_t i = 0; i < 151; ++i)std::cout << b;
								std::cout << '\n';
								file.result_read(sign_up.m_path_for_result);
							}
							else
							{
								std::cout << "You haven't passed the tests\n";
							}

						}
						else {
							std::cout << "\nIncorrect choice\n";
						}

					} while (true);
				}
				else
				{
					do
					{
						time.refresh();

						for (size_t i = 0; i < frame_size_3; ++i)std::cout << b;
						std::cout << '\n' << b << b << "                           " << b << b << '\n'
							<< b << b << " Data : " << time << ' ' << b << b << '\n'
							<< b << b << "                           " << b << b << '\n'
							<< b << b << "  " << std::left << std::setw(16) << std::setfill(' ') << sign_up.m_name << "( ADMIN )" << b << b << '\n'
							<< b << b << "  Internet status : " << std::left << std::setw(7) << std::setfill(' ') << internet << b << b << '\n'
							<< b << b << "                           " << b << b << '\n';
						for (size_t i = 0; i < frame_size_3; ++i)std::cout << b; std::cout << '\n';
						std::cout << b << b << "     Actions on ADMIN      " << b << b << '\n';
						for (size_t i = 0; i < frame_size_3; ++i)std::cout << b; std::cout << '\n';
						std::cout << b << b << "                           " << b << b << '\n'
							<< b << b << " -1  - Come back           " << b << b << '\n'
							<< b << b << "  0  - Exit                " << b << b << '\n'
							<< b << b << "  1  - Pass admin          " << b << b << '\n'
							<< b << b << "  2  - Send message        " << b << b << '\n'
							<< b << b << "  3  - Inbox message       " << b << b << '\n'
							<< b << b << "  4  - Enter on ip adress  " << b << b << '\n'
							<< b << b << "  5  - Internet(ON/OFF)    " << b << b << '\n'
							<< b << b << "  6  - Change password     " << b << b << '\n'
							<< b << b << "  7  - Change login        " << b << b << '\n'
							<< b << b << "                           " << b << b << '\n';
						for (size_t i = 0; i < frame_size_3; ++i)std::cout << b; std::cout << '\n';
						std::cout << b << b << "     Actions on User       " << b << b << '\n';
						for (size_t i = 0; i < frame_size_3; ++i)std::cout << b; std::cout << '\n';
						std::cout << b << b << "                           " << b << b << '\n'
							<< b << b << "  8  - Print users         " << b << b << '\n'
							<< b << b << "  9  - Creat user          " << b << b << '\n'
							<< b << b << "  10 - Delete user         " << b << b << '\n'
							<< b << b << "  11 - Modifiy User        " << b << b << '\n'
							<< b << b << "                           " << b << b << '\n';
						for (size_t i = 0; i < frame_size_3; ++i)std::cout << b; std::cout << '\n';
						std::cout << b << b << "     Actions on Test       " << b << b << '\n';
						for (size_t i = 0; i < frame_size_3; ++i)std::cout << b; std::cout << '\n';
						std::cout << b << b << "                           " << b << b << '\n'
							<< b << b << "  12  - Print test         " << b << b << '\n'
							<< b << b << "  13  - Creat test         " << b << b << '\n'
							<< b << b << "  14  - Print result test  " << b << b << '\n'
							<< b << b << "                           " << b << b << '\n'
							<< b << b << "                           " << b << b << '\n';
						for (size_t i = 0; i < frame_size_3; ++i)std::cout << b;
						std::cout << "\n\n";

						std::cin >> action;
						system("cls");
						if (action == EXIT || action == COME_BACK)
						{
							break;
						}
						else if (action == PASS_ADMIN)
						{
							std::cout << users << '\n';
							std::cout << "\nWho pass admin?\n";
							std::cin >> action;
							users.pass_admin(action);
							std::cout << users << '\n';
							break;
						}
						else if (action == SEND_MESSAGE)
						{
							if (internet)
							{
								std::cout << "Enter the mail to whom you want to send\n";

								std::cin >> mail;
								try
								{
									path = users.get_path(mail);
									file.send_message(path, sign_up.m_name);
								}
								catch (std::exception& ex)
								{
									std::cout << ex.what() << '\n';
								}
							}
							else {
								std::cout << "No internet\n";
							}
						}
						else if (action == INBOX_MESSAGE)
						{
							if (internet)
							{
								if (!file.inbox_read(sign_up.m_path_for_mail)) std::cout << "You don't have a message\n";
							}
							else {
								std::cout << "No internet\n";
							}
						}
						else if (action == REMOTE_CONNECTION)
						{
							if (internet)
							{
								std::cout << "Enter ip address for remote connection\n";
								std::cin >> ip;
								act = true;
								try
								{
									sig_up_ip = users.get_ip(ip);
								}
								catch (std::exception& ex)
								{
									act = false;
									std::cout << ex.what() << '\n';
								}
								if (act)
								{
									do
									{
										std::cout << "\n-1 Come back\nEnter data for Sign in on ip adress\n";
										std::cout << "Login     :  ";
										std::cin >> login;
										if (!strcmp(login, "-1"))break;
										std::cout << "Password  :  ";
										std::cin >> password;
										if (!strcmp(password, "-1"))break;
										system("cls");

										users.encrypting(password);

										if (!strcmp(sig_up_ip.m_password, password) && !strcmp(sig_up_ip.m_login, login)) break;
										else
										{
											loading_error(b);
											std::cout << "Wrong data\n";
										}

									} while (true);

									if (!strcmp(sig_up_ip.m_password, password) && !strcmp(sig_up_ip.m_login, login))
									{
										loading_successful(b);
										std::cout << "\n Loading successful done\n";
										do
										{
											time.refresh();

											for (int i = 0; i < frame_size_1; ++i)std::cout << b;
											std::cout << '\n' << b << b << "                          " << b << b << '\n'
												<< b << b << " Data : " << time << b << b << '\n'
												<< b << b << "                          " << b << b << '\n'
												<< b << b << "  " << std::left << std::setw(16) << std::setfill(' ') << sig_up_ip.m_name << "( USER )" << b << b << '\n'
												<< b << b << "  Internet status : " << std::left << std::setw(6) << std::setfill(' ') << internet << b << b << '\n'
												<< b << b << "                          " << b << b << '\n'
												<< b << b << "                          " << b << b << '\n'
												<< b << b << " -1 - Come back           " << b << b << '\n'
												<< b << b << "  0 - Exit                " << b << b << '\n'
												<< b << b << "  1 - Pass the test       " << b << b << '\n'
												<< b << b << "  2 - Send Message        " << b << b << '\n'
												<< b << b << "  3 - Inbox               " << b << b << '\n'
												<< b << b << "  4 - Result test         " << b << b << '\n'
												<< b << b << "                          " << b << b << '\n'
												<< b << b << "                          " << b << b << '\n';
											for (size_t i = 0; i < frame_size_1; ++i)std::cout << b;
											std::cout << "\n\n";

											std::cin >> action;
											system("cls");

											if (action == COME_BACK || action == EXIT)
											{
												break;
											}
											else if (action == PASS_THE_TEST)
											{
												if (test.get_size())
												{
													j = 0; correct_answer = 0;
													if (!file.read_pause(sig_up_ip.m_test_pause, j, correct_answer, index))
													{
														std::cout << "\n\n------------------------\n\n";
														test.print_subject();
														std::cout << "\n----------------------------\n\n";

														std::cout << "Please choose subject for test\n";
														do
														{
															std::cin >> index;

															if (index < test.get_size() && index >= 0) break;
															else  std::cout << "Incorect choose\n";

														} while (true);

														system("cls");

														try {
															std::cout << "\n\nYou select :  test on " << test.get_test_subject(index) << "\n";
														}
														catch (std::exception& ex) {
															std::cout << ex.what() << "\n";
														}
													}
													else
													{
														std::cout << "Continue test\n";
													}

													test.print_testing(index);
													std::cout << "\n\n-1  Leave tests for later\n\n";

													for (j; j < size; ++j)
													{
														do
														{
															std::cout << j + 1 << ") ";
															std::cin >> act;
															if (act == -1) {

																file.write_pause(sig_up_ip.m_test_pause, j, correct_answer, index);
																break;
															}
															if (act >= 0 && act < 4) break;
															else std::cout << "There is no such option\n\n";

														} while (true);

														if (act == -1) break;

														if (test.get_correct_answer(index, j) == act) correct_answer++;
													}

													if (act != -1)
													{
														file.removve(sig_up_ip.m_test_pause);
														if (correct_answer) result = correct_answer * 100 / size;
														else  result = correct_answer;

														rating = grading(result);

														std::cout << "\nresult = " << result << " % \n";
														std::cout << "Number of correct answers    : " << correct_answer << '\n';
														std::cout << "Number of incorrect answers  : " << size - correct_answer << '\n';
														std::cout << "Rating : " << rating << '\n';

														output.open(sig_up_ip.m_path_for_result, mode);
														if (output) {
															std::string text;
															time.refresh();

															output << b << b << std::left << std::setw(12) << std::setfill(' ') << sig_up_ip.m_name << b
																<< b << std::left << std::setw(12) << std::setfill(' ') << sig_up_ip.m_surname << b
																<< b << std::left << std::setw(12) << std::setfill(' ') << sig_up_ip.m_patronymic << b
																<< b << std::left << std::setw(13) << std::setfill(' ') << sig_up_ip.m_phone_number << b
																<< b << std::left << std::setw(18) << std::setfill(' ') << sig_up_ip.m_mail << b
																<< b << std::left << std::setw(12) << std::setfill(' ') << test.subject_name(index) << b
																<< b << std::left << std::setw(7) << std::setfill(' ') << result << " % " << b
																<< b << std::left << std::setw(6) << std::setfill(' ') << correct_answer << b
																<< b << std::left << std::setw(6) << std::setfill(' ') << size - correct_answer << b
																<< b << std::left << std::setw(8) << std::setfill(' ') << rating << b
																<< b << std::left << std::setw(15) << std::setfill(' ') << time << b << b << '\n';
															for (size_t i = 0; i < 151; ++i)output << b;
															output << '\n';
															std::cout << '\n';
															output.close();
														}
													}
												}
												else {
													std::cout << "\nNot test!\n\n";
												}
											}
											else if (action == SEND_MESSAGE)
											{
												if (internet)
												{
													std::cout << "Enter the mail to whom you want to send\n";

													std::cin >> mail;
													try
													{
														path = users.get_path(mail);
														file.send_message(path, sig_up_ip.m_name);
													}
													catch (std::exception& ex)
													{
														std::cout << ex.what() << '\n';
													}
												}
												else {
													std::cout << "No internet\n";
												}
											}
											else if (action == INBOX_MESSAGE)
											{
												if (!file.inbox_read(sig_up_ip.m_path_for_mail)) std::cout << "\nUvas netu soobwenii\n";
											}
											else if (action == RESULT_TEST_IP)
											{
												if (!file.result_empty(sig_up_ip.m_path_for_result))
												{
													std::cout << "\nYour result\n";
													for (size_t i = 0; i < 151; ++i)std::cout << b;
													std::cout << '\n';
													std::cout << b << b << std::left << std::setw(12) << std::setfill(' ') << "Name" << b
														<< b << std::left << std::setw(12) << std::setfill(' ') << "Surname" << b
														<< b << std::left << std::setw(12) << std::setfill(' ') << "Patronymic" << b
														<< b << std::left << std::setw(13) << std::setfill(' ') << "Phone number" << b
														<< b << std::left << std::setw(18) << std::setfill(' ') << "Mail" << b
														<< b << std::left << std::setw(12) << std::setfill(' ') << "Subject name" << b
														<< b << std::left << std::setw(10) << std::setfill(' ') << "Result (%)" << b
														<< b << std::left << std::setw(6) << std::setfill(' ') << "Right" << b
														<< b << std::left << std::setw(6) << std::setfill(' ') << "Wrong" << b
														<< b << std::left << std::setw(8) << std::setfill(' ') << "Rating" << b
														<< b << std::left << std::setw(18) << std::setfill(' ') << " dd.mm.yy    h:m" << b << b << '\n';
													for (size_t i = 0; i < 151; ++i)std::cout << b;
													std::cout << '\n';
													file.result_read(sig_up_ip.m_path_for_result);
												}
												else
												{
													std::cout << "You haven't passed the tests\n";
												}
											}
											else {
												std::cout << "\nIncorrect choice\n";
											}
										} while (true);
									}
								}
							}
							else {
								std::cout << "No internet\n";
							}
						}
						else if (action == INTERNET)
						{
							std::cout << "\n 1 - ON \n";
							std::cout << " 2 - OFF \n";
							std::cin >> action;

							if (action == 1)
							{
								if (internet) {
									std::cout << "First turn OFF the internet to turn it on!!\n";
								}
								else {
									std::cout << "You turned ON the internet\n";
									internet = true;
								}
							}
							else if (action == 2)
							{
								if (internet) {
									std::cout << "You turned OFF the internet\n";
									internet = false;
								}
								else {
									std::cout << "First turn ON the internet to turn it OFF!!\n";
								}
							}
							else {
								std::cout << "Incorect chooce\n";
							}
						}
						else if (action == CHANGE_PASSWORD)
						{
							std::cout << "\n Change password\n\nVvedite stariy parol\n";

							std::cin >> old_password;
							users.encrypting(old_password);

							if (!strcmp(old_password, sign_up.m_password))
							{
								std::cout << "Enter new password\n";
								std::cin >> password;
								std::cout << "Please repeat password\n";
								std::cin >> password_repeat;

								if (!strcmp(password, password_repeat)) {
									users.encrypting(password);

									if (strcmp(old_password, password)) {
										users.change_password_admin(password);
										std::cout << "Parol izmenen\n";
									}
									else {
										std::cout << "Parol doljen otlicatsa ot staroqo!\n";
									}
								}
								else {
									std::cout << "Paroli ne sovpadayut\n";
								}
							}
							else {
								std::cout << "Stariy parol vveden ne pravilno\n";
							}
						}
						else if (action == CHANGE_LOGIN)
						{
							std::cout << "\n Change login\n\n";
							std::cout << "Enter new login\n";
							std::cin >> login;

							if (users.change_login_admin(login)) std::cout << "Login izmenen!\n";
							else std::cout << "Danniy login zanet\n";

						}
						else if (action == PRINT_USERS)
						{
							char frame = 177;
							for (size_t i = 0; i < 186; ++i)std::cout << frame;
							std::cout << '\n';
							std::cout << frame << frame << "#   " << frame
								<< frame << std::right << std::setw(12) << std::setfill(' ') << "Name" << frame
								<< frame << std::right << std::setw(15) << std::setfill(' ') << "Surname" << frame
								<< frame << std::right << std::setw(12) << std::setfill(' ') << "Patronymic" << frame
								<< frame << std::right << std::setw(12) << std::setfill(' ') << "Phone" << frame
								<< frame << std::right << std::setw(12) << std::setfill(' ') << "Login" << frame
								<< frame << std::right << std::setw(18) << std::setfill(' ') << "Mail" << frame
								<< frame << std::right << std::setw(12) << std::setfill(' ') << "Password" << frame
								<< frame << std::right << std::setw(8) << std::setfill(' ') << "Role" << frame
								<< frame << std::right << std::setw(17) << std::setfill(' ') << "Ip" << frame
								<< frame << std::right << std::setw(30) << std::setfill(' ') << "Path" << "\t        " << frame << frame << '\n';
							for (size_t i = 0; i < 186; ++i)std::cout << frame;
							std::cout << '\n';
							std::cout << users;
						}
						else if (action == CREAT_USER) {
							std::cout << "\n\n<< Fill in the registration User >> \n\n";
							std::cin >> user;

							if (!strcmp(user.m_password, user.m_repeat_password))
							{
								if (users.add(user))
								{
									std::cout << "\nRegistration was successful\n";
									file.write_user(user);
								}
								else {
									std::cout << "A user with such data exists\n";
								}
							}
							else {
								std::cout << "Password mismatch\n";
							}
						}
						else if (action == DELETE_USER)
						{
							std::cout << users << '\n';;
							std::cout << "Enter number for delete user\n";
							std::cin >> action;
							if (users.get_role(action) == User_data<>::ADMIN)
							{
								std::cout << "Cannot remove admin\n";
							}
							else
							{
								try
								{
									users.deleted(action);
								}
								catch (std::range_error& ex)
								{
									std::cout << ex.what();
								}
							}
						}
						else if (action == MODIFIY_USER)
						{
							do
							{
								std::cout << users;
								std::cout << "\n-1 - Come back\nViberite nomer USERA dlya modofikacii\n";
								std::cin >> index;
								system("cls");
								if (users.get_index_admin() == index)
								{
									std::cout << "Viberite polzovatelya a ne admina!\n";
								}
								else if (index == COME_BACK)
								{
									break;
								}
								else if (users.get_size() > index)
								{

									std::cout << "What do you want to change\n1 - Name\n2 - Surname\n";
									std::cout << "3 - Patronymic\n4 - login\n5 - Password\n\n";
									std::cin >> action;
									system("cls");
									if (action == NAME || action == SURNAME || action == PATRONYMIC)
									{
										if (action == NAME)std::cout << "You enter name \n";
										else if (action == SURNAME)std::cout << "You enter surname \n";
										else if (action == PATRONYMIC)std::cout << "You enter patronymic \n";

										std::cin >> modify;

										users.modifiy_user(index, modify, action);
										if (action == NAME)std::cout << "You modify name \n";
										else if (action == SURNAME)std::cout << "You modify surname \n";
										else if (action == PATRONYMIC)std::cout << "You modify patroyic \n";
										break;
									}
									else if (action == 5)
									{
										std::cout << "Enter password\n";
										std::cin >> modify;
										users.encrypting(modify);
										users.modifiy_user(index, modify, action);
										std::cout << "You modify password \n";
										break;
									}
									else if (action == 4)
									{
										std::cout << "Enter login\n";
										std::cin >> modify;
										if (!users.chek_login(modify))
										{
											users.modifiy_user(index, modify, action);
											std::cout << "You modify login \n";
											break;
										}
										else {
											std::cout << "Danniy login zanet\n";
										}
									}
									else {
										std::cout << "Incorect choose\n";
									}
								}
								else {
									std::cout << "dannoqo polzovatelya netu\n";
								}
							} while (true);
						}
						else if (action == PRINT_TEST)
						{
							std::cout << test;
						}
						else if (action == CREATE_TEST)
						{
							std::cin >> subject_test;
							file.write_test(subject_test);

							test.add(subject_test);
						}
						else if (action == PRINT_RESULT_TEST)
						{
							if (!users.result_empty())
							{
								for (size_t i = 0; i < 151; ++i)std::cout << b;
								std::cout << '\n';
								std::cout << b << b << std::left << std::setw(12) << std::setfill(' ') << "Name" << b
									<< b << std::left << std::setw(12) << std::setfill(' ') << "Surname" << b
									<< b << std::left << std::setw(12) << std::setfill(' ') << "Patronymic" << b
									<< b << std::left << std::setw(13) << std::setfill(' ') << "Phone number" << b
									<< b << std::left << std::setw(18) << std::setfill(' ') << "Mail" << b
									<< b << std::left << std::setw(12) << std::setfill(' ') << "Subject name" << b
									<< b << std::left << std::setw(10) << std::setfill(' ') << "Result (%)" << b
									<< b << std::left << std::setw(6) << std::setfill(' ') << "Right" << b
									<< b << std::left << std::setw(6) << std::setfill(' ') << "Wrong" << b
									<< b << std::left << std::setw(8) << std::setfill(' ') << "Rating" << b
									<< b << std::left << std::setw(18) << std::setfill(' ') << " dd.mm.yy    h:m" << b << b << '\n';
								for (size_t i = 0; i < 151; ++i)std::cout << b;
								std::cout << '\n';
								users.print_test_result();
							}
							else
							{
								std::cout << "Nobody took the tests\n";
							}
						}
						else {
							std::cout << "\nIncorrect choice\n";
						}
						file.overwrite_users(users);
					} while (true);
				}
			}
			else {
				std::cout << "Data entered incorrectly\n";
			}
		}
		else {
			std::cout << "\nIncorrect choice\n";
		}
	} while (action != EXIT);

	file.overwrite_users(users);
}
