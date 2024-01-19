#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <time.h>

using namespace std;
using namespace filesystem;

namespace task_1
{
    class Human
    {
    private:
        string first_name;
        string second_name;
        string patronymic;
    public:
        Human() : Human("Иван", "Иванов", "Иванович") {};
        Human(string first_name, string second_name, string patronymic)
        {
            set_first_name(first_name);
            set_second_name(second_name);
            set_patronymic(patronymic);
        }
        void set_first_name(string first_name) { this->first_name = { first_name }; }
        void set_second_name(string second_name) { this->second_name = { second_name }; }
        void set_patronymic(string patronymic) { this->patronymic = { patronymic }; }
        friend ostream& operator<<(ostream& out, Human& human)
        {
            out << human.second_name << " " << human.first_name << " " << human.patronymic;
            return out;
        }
    };

    class Flat
    {
    private:
        int number;
        vector<Human> residents;
    public:
        Flat() : Flat(1) {};
        Flat(int number) { set_number(number); }
        Flat(int number, vector<Human> residents)
        {
            set_number(number);
            set_residents(residents);
        }
        void set_number(int number) { this->number = { number }; }
        void set_residents(vector<Human> residents) { this->residents = residents; }
        friend ostream& operator<<(ostream& out, Flat& flat)
        {
            out << "Квартира " << flat.number << ", жильцы:\n";
            for (vector<Human>::iterator resident = flat.residents.begin(); resident != flat.residents.end(); resident++)
            {
                out << *resident << endl;
            }
            return out;
        }
    };

    class House
    {
    private:
        string street;
        int number;
        vector<Flat> flats;
    public:
        House() : House("им. Ленина", 1) {};
        House(string street, int number)
        {
            set_street(street);
            set_number(number);
        }
        House(string street, int number, vector<Flat> flats)
        {
            set_street(street);
            set_number(number);
            set_flats(flats);
        }
        void set_street(string street) { this->street = { street }; }
        void set_number(int number) { this->number = { number }; }
        void set_flats(vector<Flat> flats) { this->flats = flats; }
        friend ostream& operator<<(ostream& out, House& house)
        {
            out << "Улица " << house.street << ", д. " << house.number << ":\n\n";
            for (vector<Flat>::iterator flat = house.flats.begin(); flat != house.flats.end(); flat++)
            {
                out << *flat << endl;
            }
            return out;
        }
    };

    string generate_name(path path_to_names)
    {
        vector<string> list;
        ifstream file;
        file.open(path_to_names);
        while (not file.eof())
        {
            string name;
            getline(file, name);
            list.push_back(name);
        }
        Sleep(500);
        srand(time(NULL));
        return list[rand() % list.size()];
    }

    Human generate_human()
    {
        cout << "Создаю жильца...\n";
        path path_to_names = current_path() += "\\Files\\first_names.txt";
        string first_name = generate_name(path_to_names);
        path_to_names = current_path() += "\\Files\\second_names.txt";
        string second_name = generate_name(path_to_names);
        path_to_names = current_path() += "\\Files\\patronymics.txt";
        string patronymic = generate_name(path_to_names);
        Human human(first_name, second_name, patronymic);
        return human;
    }

    Flat generate_flat(int number)
    {
        cout << "Создаю квартиру...\n";
        vector<Human> residents;
        Sleep(500);
        srand(time(NULL));
        for (int i = 0; i < rand() % 5 + 1; i++)
        {
            residents.push_back(generate_human());
        }
        Flat flat(number, residents);
        cout << endl;
        return flat;
    }

    House generate_house(int number_of_flats = 45, string street = "им. Ленина", int number = 1)
    {
        vector<Flat> flats;
        for (int i = 1; i <= number_of_flats; i++)
        {
            cout << "Создаётся квартира " << i << " из " << number_of_flats << endl;
            flats.push_back(generate_flat(i));
        }
        House house(street, number, flats);
        system("cls");
        return house;
    }
}

namespace task_2
{
    class Reservoir
    {
    private:
        enum types { PUDDLE, POND, RIVER, LAKE, SEA, OCEAN };
        string name;
        int type;
        double length;
        double width;
        double depth;
        double area;
        double volume;
        void set_area() { area = length * width; }
        void set_volume() { volume = length * width * depth; }
    public:
        static vector<string> list_of_names;
        Reservoir() : Reservoir("им. Ленина") {}
        Reservoir(string name) : Reservoir(name, LAKE) {}
        Reservoir(string name, int type) : Reservoir(name, type, 100, 100, 10) {}
        Reservoir(string name, int type, double length, double width, double depth)
        {
            set_name(name);
            set_type(type);
            set_length(length);
            set_width(width);
            set_depth(depth);
        }
        void set_name(string name) { this->name = { name }; }
        void set_type(int type)
        {
            if (type < 0 or type > 5) this->type = LAKE;
            else this->type = { type };
        }
        void set_length(double length)
        {
            this->length = { length };
            set_area();
            set_volume();
        }
        void set_width(double width)
        {
            this->width = { width };
            set_area();
            set_volume();
        }
        void set_depth(double depth)
        {
            this->depth = { depth };
            set_area();
            set_volume();
        }
        string get_name() { return name; }
        bool compare_types(Reservoir& other) { return (this->type == other.type); }
        bool operator>(Reservoir& other)
        {
            if (not compare_types(other)) return(this->type > other.type);
            else return (this->area > other.area);
        }
        bool operator<(Reservoir& other)
        {
            if (not compare_types(other)) return(this->type < other.type);
            else return (this->area < other.area);
        }
        bool operator==(Reservoir& other)
        {
            if (not compare_types(other)) return(this->type == other.type);
            else return (this->area == other.area);
        }
        bool operator>=(Reservoir& other)
        {
            if (not compare_types(other)) return(this->type >= other.type);
            else return (this->area >= other.area);
        }
        bool operator<=(Reservoir& other)
        {
            if (not compare_types(other)) return(this->type <= other.type);
            else return (this->area <= other.area);
        }        
        friend ostream& operator<<(ostream& out, Reservoir& reservoir)
        {
            out << "Название:\t\t\t" << reservoir.name << endl;
            out << "Тип:\t\t\t\t";
            switch (reservoir.type)
            {
            case(PUDDLE): out << "лужа\n";
                break;
            case(POND): out << "пруд\n";
                break;
            case(RIVER): out << "река\n";
                break;
            case(LAKE): out << "озеро\n";
                break;
            case(SEA): out << "море\n";
                break;
            case(OCEAN): out << "океан\n";
                break;
            }
            out << "Д*Ш*Г:\t\t\t\t" << reservoir.length << "*" << reservoir.width << "*" << reservoir.depth << endl;
            out << "Площадь водной поверхности:\t" << reservoir.area << endl;
            out << "Объём:\t\t\t\t" << reservoir.volume << endl;
            return out;
        }
        void write_to_file()
        {
            path path_to_savefile = current_path() += "\\Files\\list_of_reservoirs.txt";
            ofstream file;
            file.open(path_to_savefile, ios::app);
            file << name << endl;
            file << type << endl;
            file << length << endl;
            file << width << endl;
            file << depth << endl;
            file << area << endl;
            file << volume << endl;
            file.close();
        }
    };

    vector<string> Reservoir::list_of_names;
    
    Reservoir generate_reservoir()
    {
        cout << "Создаю водоём...\n";
        Sleep(750);
        srand(time(NULL));
        int type = rand() % 6;
        int i = rand() % Reservoir::list_of_names.size();
        string name = Reservoir::list_of_names[i];
        Reservoir::list_of_names.erase(Reservoir::list_of_names.begin() + i);
        double length = 0;
        double width = 0;
        double depth = 0;
        switch (type)
        {
        case(0):
        {
            length = rand() % 10 + 1 + ((double)(rand() % 100) / 100);
            width = rand() % 10 + 1 + ((double)(rand() % 100) / 100);
            depth = (double)(rand() % 100) / 100;
        }
            break;
        case(1):
        {
            length = rand() % 50 + 1 + ((double)(rand() % 100) / 100);
            width = rand() % 50 + 1 + ((double)(rand() % 100) / 100);
            depth = rand() % 10 + 1 + ((double)(rand() % 100) / 100);
        }
            break;
        case(2):
        {
            length = rand() % 100 + 1 + ((double)(rand() % 100) / 100);
            width = rand() % 1000 + 1 + ((double)(rand() % 100) / 100);
            depth = rand() % 50 + 1 + ((double)(rand() % 100) / 100);
        }
            break;
        case(3):
        {
            length = rand() % 500 + 1 + ((double)(rand() % 100) / 100);
            width = rand() % 500 + 1 + ((double)(rand() % 100) / 100);
            depth = rand() % 50 + 1 + ((double)(rand() % 100) / 100);
        }
            break;
        case(4):
        {
            length = rand() % 1000 + 1 + ((double)(rand() % 100) / 100);
            width = rand() % 1000 + 1 + ((double)(rand() % 100) / 100);
            depth = rand() % 500 + 1 + ((double)(rand() % 100) / 100);
        }
            break;
        case(5):
        {
            length = rand() % 5000 + 1 + ((double)(rand() % 100) / 100);
            width = rand() % 5000 + 1 + ((double)(rand() % 100) / 100);
            depth = rand() % 500 + 1 + ((double)(rand() % 100) / 100);
        }
            break;
        }
        Reservoir reservoir(name, type, length, width, depth);
        system("cls");
        return reservoir;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Задача 1\n\n";
    task_1::House house(task_1::generate_house(9));
    cout << house;

    system("pause");

    cout << "\n\nЗадача 2\n\n";
    path path_to_names = current_path() += "\\Files\\reservoirs.txt";
    ifstream file;
    file.open(path_to_names);
    while (not file.eof())
    {
        string name;
        getline(file, name);
        task_2::Reservoir::list_of_names.push_back(name);
    }

    vector<task_2::Reservoir> reservoirs;
    for (int i = 0; i < 10; i++)
    {
        reservoirs.push_back(task_2::generate_reservoir());
    }
    for (vector<task_2::Reservoir>::iterator reservoir = reservoirs.begin(); reservoir != reservoirs.end(); reservoir++)
    {
        cout << *reservoir << endl;
    }
    for (vector<task_2::Reservoir>::iterator reservoir = reservoirs.begin(); reservoir != reservoirs.end(); reservoir++)
    {
        reservoir->write_to_file();
    }
    if (reservoirs[3] >= reservoirs[5]) cout << reservoirs[3].get_name() << " >= " << reservoirs[5].get_name() << endl;
    else cout << reservoirs[3].get_name() << " < " << reservoirs[5].get_name() << endl;

    return 0;
}
