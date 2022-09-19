#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

const unsigned MAX_SEATS = 50, MAX_WEIGHT = 10000, MAX_STATION_VEHICLES = 100;

class Bus {
    unsigned seats;
    string model;
public:
    Bus(int seats, string model) : seats(seats), model(model) {}
    Bus() : Bus(0, "") {}
    void get(int& get_seats, string& get_model) {
        get_model = model;
        get_seats = seats;
    }
    string getmodel() { return model; }
    int getseats() { return seats; }
    void set(int set_seats, string& set_model) {
        model = set_model;
        seats = set_seats;
    }
    void print_info() {
        cout << "(i) <Bus> Model -> " << model << "; Seats -> " << seats << ";";
    }
};

class Car {
    unsigned seats;
    string model;
public:
    Car(int seats, string model) : seats(seats), model(model) {}
    Car() : Car(0, "") {}
    void get(int& get_seats, string& get_model) {
        get_model = model;
        get_seats = seats;
    }
    string getmodel() { return model; }
    int getseats() { return seats; }
    void set(int set_seats, string& set_model) {
        model = set_model;
        seats = set_seats;
    }
    void print_info() {
        cout << "(i) <Car> Model -> " << model << "; Seats -> " << seats << ";";
    }
};

class Truck {
    unsigned seats, weight;
    string model;
public:
    Truck(int seats, int weight, string model) : seats(seats), weight(weight), model(model) {}
    Truck() : Truck(0, 0, "") {}
    void get(int& get_seats, int& get_weight, string& get_model) {
        get_model = model;
        get_weight = weight;
        get_seats = seats;
    }
    string getmodel() { return model; }
    int getseats() { return seats; }
    int getweight() { return weight; }
    void set(int set_seats, int set_weight, string& set_model) {
        model = set_model;
        weight = set_weight;
        seats = set_seats;
    }
    void print_info() {
        cout << "(i) <Truck> Model -> " << model << "; Seats -> " << seats << "; Weight -> " << weight << "kg;";
    }
};

class AutoStation {
    vector<Bus>B;
    vector<Car>C;
    vector<Truck>T;
    unsigned truckN, carN, busN;
    class Coordinate {
        double x, y;
    public:
        Coordinate(double x = 0., double y = 0.) : x(x), y(y) {}
        double getX() { return x; }
        double getY() { return y; }
        void update(double new_x = 0, double new_y = 0) { x = new_x; y = new_y; }
        void upto(double x_plus = 1, double y_plus = 1) { x += x_plus; y += y_plus; }
        void inline print_info() {
            cout << "(" << x << "; " << y << ")\n";
        }
    };
    Coordinate HomeCoord;
    vector<Coordinate>PosB;
    vector<Coordinate>PosC;
    vector<Coordinate>PosT;
public:
    void updateHomePos(double x, double y) { HomeCoord.update(x, y); }
    int inline getBusN() { return busN; }
    int inline getCarN() { return carN; }
    int inline getTruckN() { return truckN; }
    AutoStation() {
        truckN = carN = busN = 0;
        copydata();
    }
    void inline print_info() {
        cout << "\n|==========(iGENERAL)==========|\n" <<
            "|STATION CAPACITY   |[" << MAX_STATION_VEHICLES <<
            "]\n|FREE PLACES        |[" << MAX_STATION_VEHICLES - (getCarN() + getBusN() + getTruckN()) <<
            "]\n|VEHICLES AVALIABLE |[" << getHomeVehiclesN() <<
            "]\n|::BUSES            |[" << getBusN() << "][H::" << getHomeVehiclesN(0) <<
            "]\n|::CARS             |[" << getCarN() << "][H::" << getHomeVehiclesN(1) <<
            "]\n|::TRUCKS           |[" << getTruckN() << "][H::" << getHomeVehiclesN(2) <<
            "]\n|==============================|\n";
    }
    void inline print_detail_info() {
        cout << "\n|================================(iDETAIL)================================|\n|BUSES:\n";
        for (int i = 1; i <= getBusN(); i++) {
            cout << "|#" << i;
            getBus(i).print_info();
            if (getBusDistance(i) == 0)
                cout << " ::AT HOME\n";
            else cout << " ~" << getBusDistance(i) << " KM AWAY\n";
        }
        cout << "|CARS:\n";
        for (int i = 1; i <= getCarN(); i++) {
            cout << "|#" << i;
            getCar(i).print_info();
            if (getCarDistance(i) == 0)
                cout << " ::AT HOME\n";
            else cout << " ~" << getCarDistance(i) << " KM AWAY\n";
        }
        cout << "|TRUCKS:\n";
        for (int i = 1; i <= getTruckN(); i++) {
            cout << "|#" << i;
            getTruck(i).print_info();
            if (getTruckDistance(i) == 0)
                cout << " ::AT HOME\n";
            else cout << " ~" << getTruckDistance(i) << " KM AWAY\n";
        }
        cout << "|=========================================================================|\n";
    }
    /*true-home list info; false-away list info*/
    void print_position_list(bool is_home_list) {
        cout << "\n|==============================(" << (is_home_list ? "HOME_LIST)================================|\n|BUSES:\n" : "AWAY_LIST)================================|\n|BUSES:\n");
        for (int i = 1; i <= getBusN(); i++) {
            if (is_home_list) {
                if (getBusDistance(i) == 0) {
                    cout << "|#" << i;
                    getBus(i).print_info();
                    cout << endl;
                }
            }
            else 
                if (getBusDistance(i) != 0) {
                    cout << "|#" << i;
                    getBus(i).print_info();
                    cout << " ~" << getBusDistance(i) << " KM AWAY\n";
                }
        }
        cout << "|CARS:\n";
        for (int i = 1; i <= getCarN(); i++) {
            if (is_home_list) {
                if (getCarDistance(i) == 0) {
                    cout << "|#" << i;
                    getCar(i).print_info();
                    cout << endl;
                }
            }
            else
                if (getCarDistance(i) != 0) {
                    cout << "|#" << i;
                    getCar(i).print_info();
                    cout << " ~" << getCarDistance(i) << " KM AWAY\n";
                }
        }
        cout << "|TRUCKS:\n";
        for (int i = 1; i <= getTruckN(); i++) {
            if (is_home_list) {
                if (getTruckDistance(i) == 0) {
                    cout << "|#" << i;
                    getTruck(i).print_info();
                    cout << endl;
                }
            }
            else
                if (getTruckDistance(i) != 0) {
                    cout << "|#" << i;
                    getTruck(i).print_info();
                    cout << " ~" << getTruckDistance(i) << " KM AWAY\n";
                }
        }
        cout << "|=========================================================================|\n";
    }
    Bus inline getBus(unsigned number) {
        if (number - 1 < busN) return B[number - 1];
        cout << "(!) bus number error ::getting #n bus\n";
        return Bus(0, "");
    }
    Coordinate inline getBusPosition(unsigned number) {
        if (number - 1 < busN) return PosB[number - 1];
        cout << "(!) bus number error ::getting #n bus position\n";
        return Coordinate();
    }
    void moveBus(unsigned number, double x = 1, double y = 1) {
        if (number - 1 < busN) {
            PosB[number - 1].upto(x, y);
            rewrite();
            return;
        }
        cout << "(!) bus number error ::moving #n bus position\n";
    }
    void updateBusPos(unsigned number, double x = 0, double y = 0){
        if (number - 1 < busN) {
            PosB[number - 1].update(x, y);
            rewrite();
            return;
        }
        cout << "(!) bus number error ::updating #n bus position\n";
    }
    int inline getBusDistance(unsigned number) {
        if (number - 1 < busN)
            return static_cast<int>(sqrt(pow(getBusPosition(number).getX() - HomeCoord.getX(), 2) + pow(getBusPosition(number).getY() - HomeCoord.getY(), 2)));
        cout << "(!) bus number error ::getting distance to #n bus\n";
        return -1;
    }
    void addBus(int seats, string model) {
        if (carN + busN + truckN < MAX_STATION_VEHICLES && seats <= MAX_SEATS) {
            busN++;
            B.push_back(Bus(seats, model));
            PosB.push_back(Coordinate());
            cout << "(+) bus has been added\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to add new bus" << (seats > MAX_SEATS ? ":<too many seats>\n" : ":<station is full>\n");
    }
    void delBus(unsigned number) {
        if (busN > number - 1) {
            B.erase(B.begin() + (number - 1));
            PosB.erase(PosB.begin() + (number - 1));
            busN--;
            cout << "(-) bus #" << number << " has been deleted\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to delete the bus\n";
    }

    Car inline getCar(unsigned number) {
        if (number - 1 < carN) return C[number - 1];
        cout << "(!) car number error ::getting #n car\n";
        return Car(0, "");
    }
    Coordinate inline getCarPosition(unsigned number) {
        if (number - 1 < carN) return PosC[number - 1];
        cout << "(!) car number error ::getting #n car position\n";
        return Coordinate();
    }
    void moveCar(unsigned number, double x = 1, double y = 1) {
        if (number - 1 < carN) {
            PosC[number - 1].upto(x, y);
            rewrite();
            return;
        }
        cout << "(!) car number error ::moving #n car position\n";
    }
    void updateCarPos(unsigned number, double x = 0, double y = 0) {
        if (number - 1 < carN) {
            PosC[number - 1].update(x, y);
            rewrite();
            return;
        }
        cout << "(!) car number error ::updating #n car position\n";
    }
    int inline getCarDistance(unsigned number) {
        if (number - 1 < carN)
            return static_cast<int>(sqrt(pow(getCarPosition(number).getX() - HomeCoord.getX(), 2) + pow(getCarPosition(number).getY() - HomeCoord.getY(), 2)));
        cout << "(!) car number error ::getting distance to #n car\n";
        return -1;
    }
    void addCar(int seats, string model) {
        if (carN + busN + truckN < MAX_STATION_VEHICLES && seats <= MAX_SEATS) {
            carN++;
            C.push_back(Car(seats, model));
            PosC.push_back(Coordinate());
            cout << "(+) car has been added\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to add new car" << (seats > MAX_SEATS ? ":<too many seats>\n" : ":<station is full>\n");
    }
    void delCar(unsigned number) {
        if (carN > number - 1) {
            C.erase(C.begin() + (number - 1));
            PosC.erase(PosC.begin() + (number - 1));
            carN--;
            cout << "(-) car #" << number << " has been deleted\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to delete the car\n";
    }

    Truck inline getTruck(unsigned number) {
        if (number - 1 < truckN) return T[number - 1];
        cout << "(!) truck number error ::getting #n truck\n";
        return Truck(0, 0, "");
    }
    Coordinate inline getTruckPosition(unsigned number) {
        if (number - 1 < truckN) return PosT[number - 1];
        cout << "(!) truck number error ::getting #n truck position\n";
        return Coordinate();
    }
    void moveTruck(unsigned number, double x = 1, double y = 1) {
        if (number - 1 < truckN) {
            PosT[number - 1].upto(x, y);
            rewrite();
            return;
        }
        cout << "(!) truck number error ::moving #n truck position\n";
    }
    void updateTruckPos(unsigned number, double x = 0, double y = 0) {
        if (number - 1 < truckN) {
            PosT[number - 1].update(x, y);
            rewrite();
            return;
        }
        cout << "(!) truck number error ::updating #n truck position\n";
    }
    int inline getTruckDistance(unsigned number) {
        if (number - 1 < truckN)
            return static_cast<int>(sqrt(pow(getTruckPosition(number).getX() - HomeCoord.getX(), 2) + pow(getTruckPosition(number).getY() - HomeCoord.getY(), 2)));
        cout << "(!) truck number error ::getting distance to #n truck\n";
        return -1;
    }
    void addTruck(int seats, int weight, string model) {
        if (carN + busN + truckN < MAX_STATION_VEHICLES && weight <= MAX_WEIGHT) {
            truckN++;
            T.push_back(Truck(seats, weight, model));
            PosT.push_back(Coordinate());
            cout << "(+) truck has been added\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to add new truck" << (weight > MAX_WEIGHT ? ":<too much weigth>\n" : ":<station is full>\n");
    }
    void delTruck(unsigned number) {
        if (truckN > number - 1) {
            T.erase(T.begin() + (number - 1));
            PosT.erase(PosT.begin() + (number - 1));
            truckN--;
            cout << "(-) truck #" << number << " has been deleted\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to delete the truck\n";
    }
    inline int getHomeVehiclesN() {
        int N = 0;
        for (int i = 1; i <= PosB.size(); i++)
            if (getBusDistance(i) == 0) N++;
        for (int i = 1; i <= PosC.size(); i++)
            if (getCarDistance(i) == 0) N++;
        for (int i = 1; i <= PosT.size(); i++)
            if (getTruckDistance(i) == 0) N++;
        return N;
    }
    /*0-Buses; 1-Cars; 2-Trucks; Else-Error*/
    inline int getHomeVehiclesN(int parameter) {
        int N = 0;
        if (parameter == 0) {
            for (int i = 1; i <= PosB.size(); i++)
                if (getBusDistance(i) == 0) N++;
            return N;
        }
        if (parameter == 1) {
            for (int i = 1; i <= PosC.size(); i++)
                if (getCarDistance(i) == 0) N++;
            return N;
        }
        if (parameter == 2) {
            for (int i = 1; i <= PosT.size(); i++)
                if (getTruckDistance(i) == 0) N++;
            return N;
        }
        cout << "(!) error <getHomeVelichesN> funcion parameter\n";
        return 0;
    }
private:
    void rewrite() {
        ofstream data("DATA.txt");
        data << "B" << busN << "C" << carN << "T" << truckN << endl;
        for (int i = 1; i <= B.size(); i++) 
            data << "!B!*" << getBus(i).getmodel() << "*+" << getBus(i).getseats() << "+/" << i << "/&" << getBusPosition(i).getX() << "&:" << getBusPosition(i).getY() << ":\n";
        for (int i = 1; i <= C.size(); i++)
            data << "!C!*" << getCar(i).getmodel() << "*+" << getCar(i).getseats() << "+/" << i << "/&" << getCarPosition(i).getX() << "&:" << getCarPosition(i).getY() << ":\n";
        for (int i = 1; i <= T.size(); i++)
            data << "!T!*" << getTruck(i).getmodel() << "*+" << getTruck(i).getseats() << "+^" << getTruck(i).getweight() << "^/" << i << "/&" << getTruckPosition(i).getX() << "&:" << getTruckPosition(i).getY() << ":\n";
        data.close();
    }
    void copydata() {
        string info;
        ifstream data("DATA.txt");
        while (getline(data, info)) {
            string p1, p2, p3, p4, p5;
            switch (info[1]) {
            case 'B':
                busN++;
                p1 = transcript(info, '+'), p2 = transcript(info, '*'), p3 = transcript(info, '&'), p4 = transcript(info, ':');
                B.push_back(Bus(stoi(p1), p2));
                PosB.push_back(Coordinate(stoi(p3), stoi(p4)));
                info = "";
                continue;
            case 'C':
                carN++;
                p1 = transcript(info, '+'), p2 = transcript(info, '*'), p3 = transcript(info, '&'), p4 = transcript(info, ':');
                C.push_back(Car(stoi(p1), p2));
                PosC.push_back(Coordinate(stoi(p3), stoi(p4)));
                info = "";
                continue;
            case 'T':
                truckN++;
                p1 = transcript(info, '+'), p2 = transcript(info, '*'), p3 = transcript(info, '&'), p4 = transcript(info, ':'), p5 = transcript(info, '^');
                T.push_back(Truck(stoi(p1), stoi(p5), p2));
                PosT.push_back(Coordinate(stoi(p3), stoi(p4)));
                info = "";
                continue;
            default:
                info = "";
                continue;
            }
        }
        data.close();
    }
    string transcript(string str, char character) {
        do {
            str.erase(str.find(str[0]), 1);
        } while (str[0] != character);
        str.erase(str.find(str[0]), 1);
        str.erase(str.find(character));
        return str;
    }
    
};


int main() {

    srand(time(NULL));
    vector<string>bus_trucks_models{ "MERCEDES", "VOLVO", "SCANIA", "MAN", "SETRA", "TEMSA", "IVECO", "SUFFLE" };
    vector<string>car_models{ "AUDI", "MITSUBISHI", "MERCEDES", "VOLVO", "FORD", "BMW", "TOYOTA", "VOLKSWAGEN" };

    AutoStation station;
    /*station.addCar(rand() % 5 + 2, car_models[rand() % car_models.size()]);*/
    for (int i = 0; i < 150; i++)
        station.moveCar(1);
    /*for (int i = 0; i < 150; i++)
        station.moveCar(1, -1, -1);*/

    /*station.updateCarPos(1);*/
    station.print_info();
    station.print_detail_info();

    /* 
    параметр наступної функції:
    значення true виводить список всіх транспортних засобів які в цей час знаходяться НА території станції
    значення false виводить список всіх транспортних засобів які в цей час знаходяться ПОЗА території станції
    */
    /*station.print_position_list(1);
    station.print_position_list(0);*/
}