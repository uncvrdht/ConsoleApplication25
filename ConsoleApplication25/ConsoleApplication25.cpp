#include <iostream>
using namespace std;

class Fraction
{
	int numerator; // числитель
	int denominator; // знаменатель

public:
	Fraction();
	Fraction(int numerator, int denominator);

	// конструктор преобразования
	/*explicit*/ Fraction(int value)
	{
		numerator = value;
		denominator = 1;
	}

	double GetDecimal() const;
	void Print() const;
	void PrintDecimal() const;

	static Fraction Sum(const Fraction& left, const Fraction& right);
	bool GreaterThan(const Fraction& another) const;
	bool IsEquals(const Fraction& another) const;
	bool LessThan(const Fraction& another) const;

	int GetNumerator() const;
	int GetDenominator() const;
	void SetNumerator(int numerator);
	void SetDenominator(int denominator);
};

/////////////////////////////////////////////////////////////////////////////////////
// прототипы глобальных функций
Fraction operator + (const Fraction& f1, const Fraction& f2);
Fraction operator * (const Fraction& f1, const Fraction& f2);
Fraction operator / (const Fraction& f1, const Fraction& f2);
void F1(Fraction a);
Fraction F2();

/////////////////////////////////////////////////////////////////////////////////////
// пример тестовых вызовов функций для проверки работы конструктора преобразования
// F1(3);
// F2();

// явный конструктор без параметров с делегированием
Fraction::Fraction() : Fraction(0, 1)
{
	// благодаря делегированию в теле этого метода делать уже нечего
}

// "главный" конструктор
Fraction::Fraction(int numerator, int denominator)
{
	SetNumerator(numerator);
	SetDenominator(denominator);
}

// получение дроби в десятичном формате
double Fraction::GetDecimal() const
{
	return (double)numerator / denominator;
}

// распечатка обычной дроби
void Fraction::Print() const
{
	cout << numerator << "/" << denominator << "\n";
}

// распечатка десятичной дроби
void Fraction::PrintDecimal() const
{
	cout << GetDecimal() << "\n";
}

// геттер числителя
int Fraction::GetNumerator() const
{
	return numerator;
}

// геттер знаменателя
int Fraction::GetDenominator() const
{
	return denominator;
}

// сеттер числителя (без проверок)
void Fraction::SetNumerator(int numerator)
{
	this->numerator = numerator;
}

// сеттер знаменателя (знаменатель не должен быть равен 0!)
void Fraction::SetDenominator(int denominator)
{
	if (denominator != 0)
	{
		this->denominator = denominator;
	}
	else
	{
		throw "ERROR!";
	}
}

// сравнение двух дробей (левая дробь сравнивает себя с правой)
bool Fraction::LessThan(const Fraction& right) const
{
	return this->GetDecimal() < right.GetDecimal();
}

// сравнение двух дробей (левая дробь сравнивает себя с правой)
bool Fraction::GreaterThan(const Fraction& right) const
{
	return this->GetDecimal() > right.GetDecimal();
}

// сравнение двух дробей (левая дробь сравнивает себя с правой)
bool Fraction::IsEquals(const Fraction& right) const
{
	return this->GetDecimal() == right.GetDecimal();
}

// тестовая глобальная функция преобразования инта в дробь №1
void F1(Fraction a)
{
	cout << "explicit c-tor test global function F1\n";
}

// тестовая глобальная функция преобразования инта в дробь №2
Fraction F2()
{
	cout << "explicit c-tor test global function F2\n";
	return 5;
}

// сложение двух дробей (статическим методом класса)
Fraction Fraction::Sum(const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.SetNumerator(left.numerator * right.denominator + right.numerator * left.denominator);
	result.SetDenominator(left.denominator * right.denominator);
	return result;
}

///////////////////////////////////////////////////////////////////

// пример перегрузки операции +
Fraction operator + (const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.SetNumerator(left.GetNumerator() * right.GetDenominator() + right.GetNumerator() * left.GetDenominator());
	result.SetDenominator(left.GetDenominator() * right.GetDenominator());
	return result;
}

// перегрузка оператора *
Fraction operator * (const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.SetNumerator(left.GetNumerator() * right.GetNumerator());
	result.SetDenominator(left.GetDenominator() * right.GetDenominator());
	return result;
}

// перегрузка оператора /
Fraction operator / (const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.SetNumerator(left.GetNumerator() * right.GetDenominator());
	result.SetDenominator(left.GetDenominator() * right.GetNumerator());
	return result;
}

int main()
{
	Fraction a(1, 2); // 1/2
	Fraction b(1, 4); // 1/4

	Fraction result = a + b; // 1/2 + 1/4
	result.Print(); // 6/8

	result = a * b; // 1/2 * 1/4
	result.Print(); // 1/8

	result = a / b; // 1/2 / 1/4
	result.Print(); // 2

	return 0;
}