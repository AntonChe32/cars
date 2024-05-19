#include <iostream>
#include <string>

// Обернем данные в типы чтобы отличать объекты при помещении и при связывании

class Model {
public:
    std::string value;
    Model(const std::string& val) : value(val) {}
};

class Cylinders {
public:
    int value;
    Cylinders(int val) : value(val) {}
};

class Horsepower {
public:
    int value;
    Horsepower(int val) : value(val) {}
};

class LoadCapacity {
public:
    int value;
    LoadCapacity(int val) : value(val) {}
};


// Класс Car
class Car {
protected:
    static int car_counter;
    std::string model;
    int cylinders;
    int horsepower;

public:
    // Конструктор по умолчанию
    Car() :  model(""), cylinders(0), horsepower(0) { car_counter ++; }
    // Конструктор с параметрами
    Car(const char *model, int cylinders, int horsepower): model(model), cylinders(cylinders),horsepower(horsepower){ car_counter ++; }
    // Явное описание конструктора копии
    Car(const Car &c) : model(c.model), cylinders(c.cylinders), horsepower(c.horsepower) { car_counter ++; }
    // Разве в C++ есть геттеры и сеттеры - как в JS или Python
    // Ниже если это можно назвать getter и  setter - на мой взгляд обычные методы
    std::string& get_model(){
        return model;
    }
    void set_model(const std::string &str){
        model = str;
    }
    int get_cylinders(){
        return cylinders;
    }
    void set_cylinders(int c){
        cylinders = c;
    }
    int get_horsepower(){
        return horsepower;
    }
    void set_horsepower(int c){
        horsepower = c;
    }

    // оператор помещения для класса Model
    Car& operator<<(const Model& m) {
        this->model = m.value;
        return *this;
    }
    // Перегрузим для  Cilinders
    Car& operator<<(const Cylinders& c) {
        this->cylinders = c.value;
        return *this;
    }

    // Перегрузим для Horsepower
    Car& operator<<(const Horsepower& h) {
        this->horsepower = h.value;
        return *this;
    }
    Car& operator = (Car &c){
        this->model = c.model;
        this->cylinders = c.cylinders;
        this->horsepower = c.horsepower;
        return *this;
    }
    Car& operator = (const int &p){
        this->horsepower = p;
        return *this;
    }
    Car& operator = (const std::string &m){
        this->model = m;
        return *this;
    }
    Car& operator = (const char *m){
        this->model = m;
        return *this;
    }
    Car& operator=(const Model& m) {
        this->model = m.value;
        return *this;
    }
    // Перегрузим для  Cilinders
    Car& operator=(const Cylinders& c) {
        this->cylinders = c.value;
        return *this;
    }

    // Перегрузим для Horsepower
    Car& operator=(const Horsepower& h) {
        this->horsepower = h.value;
        return *this;
    }
    ~Car(){
        std::cout << "Car destructor was called" << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& out, const Car& car);
    friend int get_car_count();
};
int Car::car_counter = 0;
int get_car_count(){
    return Car::car_counter;
}
// Дружественный оператор, выводим содержимое в stdout
std::ostream& operator<<(std::ostream& out, const Car& car) {
    out << "Model: " << car.model << ", Cylinders: " << car.cylinders
        << ", Horsepower: " << car.horsepower;
    return out;
}

// Класс Truck, наследующий Car
class Truck : public Car {
private:
    int load_capacity;
protected:
    static int truck_counter;
public:
    Truck() : Car(), load_capacity(0) { truck_counter ++; }
    Truck(const char *model, int cylinders, int horsepower, int load_capacity): 
        Car(model, cylinders ,horsepower), load_capacity(load_capacity){ 
        truck_counter ++; 
    }
    // Явное описание конструктора копии
    Truck(const Truck& t): Car(t), load_capacity(t.load_capacity){ 
        truck_counter ++; 
    }
    // getter / setter
    int get_load_capacity(){
        return load_capacity;
    }
    void set_load_capacity(int c){
        load_capacity = c;
    }

    // перегруженный оператор помещения
    Truck& operator<<(const Model& m) {
        Car::operator<<(m);
        return *this;
    }

    Truck& operator<<(const Cylinders& c) {
        Car::operator<<(c);
        return *this;
    }

    Truck& operator<<(const Horsepower& h) {
        Car::operator<<(h);
        return *this;
    }

    Truck& operator<<(const LoadCapacity& l) {
        this->load_capacity = l.value;
        return *this;
    }
    Truck& operator = (const int &p){
        Car::operator=(p);
        return *this;
    }
    Truck& operator = (const std::string &m){
        Car::operator=(m);
        return *this;
    }
    Truck& operator = (const char *m){
        Car::operator=(m);
        return *this;
    }
    Truck& operator=(const Cylinders& c) {
        Car::operator=(c);
        return *this;
    }

    Truck& operator=(const Horsepower& h) {
        Car::operator=(h);
        return *this;
    }

    Truck& operator=(const LoadCapacity& l) {
        this->load_capacity = l.value;
        return *this;
    }
    Truck& operator=(Truck &c){
        Car::operator=(c);
        this->load_capacity = c.load_capacity;
        return *this;
    }
    ~Truck(){
        std::cout << "Truck destructor was called" << std::endl;
    }
    friend std::ostream& operator<<(std::ostream& out, const Truck& truck);
    friend int get_truck_count();
};
int Truck::truck_counter = 0;
int get_truck_count(){
    return Truck::truck_counter;
}
std::ostream& operator<<(std::ostream& out, const Truck& truck) {
    // статическое приведение типа и вывод на stdout
    out << static_cast<const Car&>(truck)
        << ", Load Capacity: " << truck.load_capacity << " kg";
    return out;
}

int main() {
    Car car;
    car << Model("Lada") << Cylinders(16) << Horsepower(1300);
    // Неявный вызов конструктора копии
    Car car1 = car;
    car1 = "Moskvich";
    car1 = 1400;
    //  Явный вызов конструктора копии
    Car car2(car1);
    // Перегруженный оператор = 
    car2 = Horsepower(1100);
    car2 = Cylinders(10);
    car2 = "Запорожец";
    // Конструктор с параметрами.
    Car car3("Niva", 12, 1600);
    // в stdout
    std::cout << car << std::endl << car1 << std::endl << car2 << std::endl << car3 << std::endl;

    Truck truck;
    truck << Model("Kamaz") << Cylinders(18) << Horsepower(3200) << LoadCapacity(5000);
    Truck truck1(truck);
    truck1 << Model("Maz");
    truck1 = Cylinders(12);
    truck1 << LoadCapacity(truck1.get_load_capacity()+100);
    truck1.set_load_capacity(truck1.get_load_capacity()+100);
    Truck truck2 = truck1;
    truck2 << Model("Zil");

    std::cout << truck << std::endl << truck1 << std::endl << truck2 << std::endl 
        << "Cоздано объектов класса Car " << get_car_count() << std::endl 
        << "Создано объектов класса Truck " << get_truck_count() << std::endl;

    return 0;
}
