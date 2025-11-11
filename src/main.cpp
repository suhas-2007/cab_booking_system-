
#include "RideBookingSystem.h"

#include <algorithm>

#include <ctime>

#include <random>



int main() {

    auto alldays = allDaysOfMonth();

    std::vector<Vehicle*> vehicles = {

        new Car("KA01SED1001", "Sedan"),  new Car("KA01SUV2001", "SUV"),

        new Bike("KA01SCT3001", "Scooty"), new Bike("KA01MOT4001", "Motorbike"),

        new Car("KA02SED2002", "Sedan"),   new Bike("KA02SCT3002", "Scooty"),

        new Car("KA02SUV2003", "SUV"),     new Bike("KA02MOT4002", "Motorbike"),

        new Auto("KA03AUTO101"), new Auto("KA03AUTO102"),

        new Auto("KA04AUTO201"), new Auto("KA05AUTO301")

    };



    std::vector<Driver*> drivers = {

        new Driver("Ajay", 101, vehicles[0], "male",   "8899001100", {4.2, 4.4, 4.3}, alldays),

        new Driver("Sneha", 102, vehicles[1], "female", "9001100111", {4.9, 4.8}, alldays),

        new Driver("Rahul", 103, vehicles[2], "male",   "9112233441", {4.1, 4.0, 4.2}, alldays),

        new Driver("Pooja", 104, vehicles[3], "female", "9000101234", {4.95, 4.8, 5.0}, alldays),

        new Driver("Manish", 105, vehicles[4], "male",  "9234567812", {4.3, 4.6}, alldays),

        new Driver("Anita", 106, vehicles[5], "female", "8798765432", {4.8}, alldays),

        new Driver("Gaurav", 107, vehicles[6], "male",  "7888999000", {4.0, 3.9}, alldays),

        new Driver("Ritu", 108, vehicles[7], "female",  "9123456712", {4.7, 4.9}, alldays),

        new Driver("Harish", 109, vehicles[8], "male",  "9999888877", {4.4, 4.7}, alldays),

        new Driver("Vijay", 110, vehicles[9], "male",   "9587456321", {4.0, 4.1}, alldays),

        new Driver("Suman", 111, vehicles[10], "female", "8000000001", {4.8, 4.5}, alldays),

        new Driver("Lata", 112, vehicles[11], "female", "8000000002", {5.0, 4.9, 4.8}, alldays),

        new Driver("Deepak", 113, vehicles[0],  "male",   "8333111222", {4.2, 4.6}, alldays),

        new Driver("Meena", 114, vehicles[3],   "female", "9002112233", {4.6, 4.9}, alldays),

        new Driver("Satish", 115, vehicles[9],  "male",   "9448877665", {4.3, 4.1}, alldays),

        new Driver("Kamal", 116, vehicles[8],   "male",   "8888000200", {4.5}, alldays),

        new Driver("Priya", 117, vehicles[10],  "female", "8555045678", {4.7, 4.6}, alldays),

        new Driver("Arjun", 118, vehicles[2],   "male",   "9000099991", {4.1, 4.4}, alldays),

        new Driver("Sarita", 119, vehicles[1],  "female", "7878121212", {4.8}, alldays),

        new Driver("Neha", 120, vehicles[11],   "female", "7900456123", {4.9}, alldays)

    };



    BookingContainer<Booking> bookingList;

    int bookingCount = 1;



    std::cout << "Welcome to Ride Booking System!\n";

    std::string selfOrOther;

    std::cout << "Are you booking for yourself or someone else? (self/other): ";

    getline(std::cin, selfOrOther);

    std::string riderName, bookingFor = "", userMobile;

    if (selfOrOther == "self") {

        std::cout << "Enter your name: ";

        getline(std::cin, riderName);

        bookingFor = riderName;

    } else {

        std::cout << "Enter your name: ";

        getline(std::cin, riderName);

        std::cout << "Enter the name of the person you are booking for: ";

        getline(std::cin, bookingFor);

    }

    std::cout << "Enter your mobile number: ";

    getline(std::cin, userMobile);



    std::cout << "Enter your gender (male/female): ";

    std::string userGender; getline(std::cin, userGender);

    std::transform(userGender.begin(), userGender.end(), userGender.begin(), ::tolower);



    std::cout << "Book ride for today or another day? (today/other): ";

    std::string dayChoice; getline(std::cin, dayChoice);

    Date rideDate;

    if (dayChoice == "today") {

        time_t tnow = time(0);

        tm* now = localtime(&tnow);

        rideDate.day = now->tm_mday;

        rideDate.month = now->tm_mon + 1;

        rideDate.year = now->tm_year + 1900;

    } else {

        std::cout << "Enter ride date (day month year): ";

        std::cin >> rideDate.day >> rideDate.month >> rideDate.year;

        std::cin.ignore();

    }



    std::cout << "Enter your current location: ";

    std::string startLoc; getline(std::cin, startLoc);

    std::cout << "Enter your destination location: ";

    std::string destLoc; getline(std::cin, destLoc);



    std::cout << "Enter your journey start time (hour min): ";

    int startHr, startMin; std::cin >> startHr >> startMin; std::cin.ignore();



    std::cout << "Choose Vehicle Type:\n1. Car\n2. Bike\n3. Auto\nChoice: ";

    int vtype; std::cin >> vtype; std::cin.ignore();

    std::string subtypeChoice, typeString;

    if (vtype == 1) {

        typeString = "Car";

        std::cout << "Choose car type:\n1. Sedan\n2. SUV\nChoice: ";

        int ctype; std::cin >> ctype; std::cin.ignore();

        if (ctype == 1) subtypeChoice = "Sedan";

        else if (ctype == 2) subtypeChoice = "SUV";

        else { std::cout << "Invalid car subtype selected.\n"; cleanup(vehicles, drivers); return 1; }

    } else if (vtype == 2) {

        typeString = "Bike";

        std::cout << "Choose bike type:\n1. Scooty\n2. Motorbike\nChoice: ";

        int btype; std::cin >> btype; std::cin.ignore();

        if (btype == 1) subtypeChoice = "Scooty";

        else if (btype == 2) subtypeChoice = "Motorbike";

        else { std::cout << "Invalid bike subtype selected.\n"; cleanup(vehicles, drivers); return 1; }

    } else if (vtype == 3) {

        typeString = "Auto";

        subtypeChoice = "Auto";

    } else {

        std::cout << "Invalid vehicle type selected.\n"; cleanup(vehicles, drivers); return 1;

    }



    std::vector<Driver*> eligibleDrivers;

    std::string driverGenderFilter = "";

    if (userGender == "female") {

        std::cout << "\nDo you want a male or female driver? (male/female): ";

        getline(std::cin, driverGenderFilter);

        std::transform(driverGenderFilter.begin(), driverGenderFilter.end(), driverGenderFilter.begin(), ::tolower);

    } else {

        driverGenderFilter = "male";

    }

    for (auto d : drivers) {

        if (d->getVehicle()->getType() == typeString

            && d->getVehicle()->getSubType() == subtypeChoice

            && d->getGender() == driverGenderFilter

            && d->isAvailableOnDay(rideDate.day))

            eligibleDrivers.push_back(d);

    }
