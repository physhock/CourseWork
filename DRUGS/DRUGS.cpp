#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
#include<string> 
#include<vector>
#include<time.h>





 
//Описываем структуру считываемого файла
struct StructuredFileRecord
{
	std::string name;
	time_t experationDate;
	int amount;
	float price;
};

//Считываем строки из файла,получаем разбитые строки на стуктуру(Название,Срок годности),заполняем ими вектор.
std::vector<StructuredFileRecord> readData( std::string fileName, std::string lineDelim, std::string paramDelim);

//Разбиваем строчку на Название препарата,срок годности итд
std::vector<std::string> splitString(std::string source , std::string paramDelim);

//Производим подсчеты,выводим результаты
void writeData (std::string fileName, std::vector<StructuredFileRecord>data );

//Форматируем float до двух значащих после запятой.
std::string formatFloat ( float src );

//Форматируем время
time_t stringTimeToUnixTime (std::string strDate);




////В строчках входного текстового файла представлены названия лекарств, сроки их годности,
////количество экземпляров и стоимость одного экземпляра.Вывести в выходной данные о лекарствах 
////с истекшим сроком годности на сегодняшний день и подсчитать общую их стоимость.
//Автор: Школьников Фёдор 13501/4.
int main(int argc, char* argv[]) 
{        
	setlocale(LC_ALL, "Russian");
	for (int i=0; i < argc; ++i )
		std::cout << argv[i] << std::endl;

	std::string inFileName = argc > 1 ? argv[1] :   "in.txt";
	std::string outFileName = argc > 2 ? argv[2] :  "out.txt";
	std::vector<StructuredFileRecord> data = readData (inFileName,  "\0", " ");
	writeData (outFileName, data);     
	return 0;
 }
 

std::vector<StructuredFileRecord> readData( std::string fileName, std::string lineDelim, std::string paramDelim )
{
	std::vector<StructuredFileRecord> result;
	std::string source;
	std::ifstream in;
	in.open(fileName);
	while(std::getline(in,source))
	{
	    
		std::vector<std::string> output = splitString(source,paramDelim);
		StructuredFileRecord  r;
		r.name = output[0];
		std::string strDate = output[1];
		r.experationDate = stringTimeToUnixTime(strDate);		
		r.amount = atoi(output[2].c_str());
		r.price = atof(output[3].c_str());
		result.push_back (r);
	}
	return result;
}


std::vector<std::string> splitString(std::string source , std::string paramDelim)
{
std::vector<std::string> output;



    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = source.find(paramDelim, pos)) != std::string::npos)
    {
        std::string substring( source.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(source.substr(prev_pos, pos-prev_pos)); 
	

	return output;
}


time_t stringTimeToUnixTime (std::string str)
{
    int  dd, mth, yy;
	sscanf( str.c_str(), "%d.%d.%d", &dd, &mth, & yy);
    struct tm when ;
    memset( &when, 0, sizeof( struct tm ) ) ; 
    when.tm_mday = dd;
    when.tm_mon = mth - 1 ; //Jan == 0, Dec == 11
	
	if ( yy >= 70 && yy <= 99) 
		yy += 1900;
	else
		yy += 2000;

    when.tm_year = yy -1900; // years since 1900
	time_t converted = mktime(&when);
	return converted;
}


std::string formatFloat ( float src )
{
	std::string o;
	char buffer[20];
	sprintf(buffer, "%.2f", src);
	o=buffer;
	return o;
}


void writeData ( std::string fileName, std::vector<StructuredFileRecord>data )
{
	time_t ltime;
	time(&ltime);
	float sum = 0.0;
	std::ofstream out;
	out.open(fileName);

	for (int i =0; i < data.size(); ++i )
	{
		StructuredFileRecord r = data[i];
		if ( r.experationDate < ltime ) 
		{
			char buff[20];
			strftime(buff, 20, "%d.%m.%y", localtime(&r.experationDate));
			sum = sum + r.amount*r.price;
			out << r.name << " " << buff << " " << r.amount << " " << formatFloat(r.price) << std::endl; 
		}
	}
	out << "Общая стоимость " << formatFloat(sum) << std::endl;

	out.close();
}

	 //0. Создать струкртуру которая бы отражала одну запись - SructuredFileRecord
	 //1. Открываем файл
	 //2. В цикле читаем из файла строчки в std::string
	 //3. Создаем функцию splitString для std::string, которая возвращает vector<string>. Один из параметров функции - строка разделитель
	 //4. К каждой строке цикла 2 применяем преобразование 3
	 //5. Для каждого вектора из 4 производим:
	 // -валидацию количества параметров
	 // -разбор параметров по занчению. (перевод вектора в сткруктуру SructuredFileRecord)
	 // -сохраняем SructuredFileRecord в вектор.
     //6. Производим вычисления над вектором стурктур



