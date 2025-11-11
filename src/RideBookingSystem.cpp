#include "RideBookingSystem.h"

#include <algorithm>

#include <random>

#include <thread>

#include <chrono>

#include <iomanip>



void Date::print() const { std::cout << day << "/" << month << "/" << year; }



Vehicle::Vehicle(std::string num, std::string tp, std::string stp) : number(num), type(tp), subType(stp) {}

std::string Vehicle::getType() const { return type; }

std::string Vehicle::getSubType() const { return subType; }

std::string Vehicle::getNumber() const { return number; }



Car::Car(std::string num, std::string stp) : Vehicle(num, "Car", stp) {}

void Car::displayDetails() const { std::cout << "Car (" << subType << "), Number: " << number << std::endl; }



Bike::Bike(std::string num, std::string stp) : Vehicle(num, "Bike", stp) {}

void Bike::displayDetails() const { std::cout << "Bike (" << subType << "), Number: " << number << std::endl; }



Auto::Auto(std::string num) : Vehicle(num, "Auto", "Auto") {}

void Auto::displayDetails() const { std::cout << "Auto, Number: " << number << std::endl; }



Driver::Driver(std::string n, int i, Vehicle* v, std::string g, std::string m, std::initializer_list<double> r, const std::vector<int>& availDays)

    : name(n), id(i), assignedVehicle(v), gender(g), mobile(m), ratings(r), availableDaysOfMonth(availDays) {}

void Driver::display() const {

    std::cout << "Driver: " << name << ", ID: " << id << ", Gender: " << gender

             << ", Mobile: " << mobile;

    std::cout << ", Avg. Rating: ";

    if (!ratings.empty()) std::cout << std::fixed << std::setprecision(1) << averageRating();

    else std::cout << "N/A";

    std::cout << std::endl << "Vehicle Assigned: "; assignedVehicle->displayDetails();

}

Vehicle* Driver::getVehicle() const { return assignedVehicle; }

std::string Driver::getGender() const { return gender; }

std::string Driver::getName() const { return name; }

int Driver::getID() const { return id; }

std::string Driver::getMobile() const { return mobile; }

double Driver::averageRating() const {

    if (ratings.empty()) return 0.0;

    double sum = 0;

    for (auto x : ratings) sum += x;

    return sum / ratings.size();

}

bool Driver::isAvailableOnDay(int dayOfMonth) const {

    return (std::find(availableDaysOfMonth.begin(), availableDaysOfMonth.end(), dayOfMonth) != availableDaysOfMonth.end());

}



Booking::Booking(int bid, std::string rname, std::string bookingFor, std::string mob, Driver* d,

    std::string startLoc, std::string dest, int dur, int otpCode, double fareVal, Date dt)

: bookingID(bid), riderName(rname), driver(d), startLocation(startLoc), destination(dest), userMobile(mob),

  duration(dur), otp(otpCode), rating(-1.0), fare(fareVal), rideDate(dt), bookeeName(bookingFor) {}

void Booking::printBooking() const {

    std::cout << "\nBooking #" << bookingID << " for " << riderName << std::endl;

    std::cout << "Booking for: " << bookeeName << std::endl;

    std::cout << "User mobile: " << userMobile << std::endl;

    std::cout << "Driver mobile: " << driver->getMobile() << std::endl;

    std::cout << "Date: "; rideDate.print(); std::cout << std::endl;

    std::cout << "From: " << startLocation << " To: " << destination << std::endl;

    driver->display();

    int hours = duration / 60, minutes = duration % 60;

    std::cout << "Estimated Duration: ";

    if (hours > 0) std::cout << hours << " hr ";

    if (minutes > 0 || hours == 0) std::cout << minutes << " min";

    std::cout << std::endl;

    std::cout << "Total Fare: ₹" << std::fixed << std::setprecision(2) << fare << std::endl;

    std::cout << "OTP for Booking Confirmation: " << otp << std::endl;

    if (rating >= 0)

        std::cout << "Your Rating: " << rating << "/5" << std::endl;

}

void Booking::setRating(double rate) { rating = rate; }

int Booking::getDuration() const { return duration; }



int generateOTP() {

    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(1000, 9999);

    return dis(gen);

}

int generateDuration(const std::string& vehicleType, const std::string& subType) {

    std::random_device rd;

    std::mt19937 gen(rd());

    if (vehicleType == "Car" && subType == "Sedan")

        return std::uniform_int_distribution<>(20, 35)(gen);

    if (vehicleType == "Car" && subType == "SUV")

        return std::uniform_int_distribution<>(18, 33)(gen);

    if (vehicleType == "Bike" && subType == "Scooty")

        return std::uniform_int_distribution<>(15, 25)(gen);

    if (vehicleType == "Bike" && subType == "Motorbike")

        return std::uniform_int_distribution<>(15, 22)(gen);

    if (vehicleType == "Auto")

        return std::uniform_int_distribution<>(12, 25)(gen);

    return std::uniform_int_distribution<>(20, 40)(gen);

}

double calculateFare(const std::string& type, const std::string& subType, int dur) {

    if (type == "Car" && subType == "Sedan")

        return 18.0 * dur;

    if (type == "Car" && subType == "SUV")

        return 22.0 * dur;

    if (type == "Bike" && subType == "Scooty")

        return 10.0 * dur;

    if (type == "Bike" && subType == "Motorbike")

        return 12.0 * dur;

    if (type == "Auto")

        return 8.0 * dur;

    return 15.0 * dur;

}



void startTimer(int seconds) {

    std::cout << "\nWaiting for driver allocation: \n";

    auto tend = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);

    while (std::chrono::steady_clock::now() < tend) {

        std::cout << "Time left: " << std::chrono::duration_cast<std::chrono::seconds>(tend - std::chrono::steady_clock::now()).count() << " seconds.\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    std::cout << "--- Driver allocated ---\n";

}



void giveOneUpdate(int estDuration) {

    std::random_device rd;

    std::mt19937 gen(rd());

    int t = estDuration > 5 ? estDuration - 5 : estDuration;

    int speed = std::uniform_int_distribution<>(20, 51)(gen);

    std::cout << "\nUpdate: You will reach your destination in " << t << " min. "

         << "Current speed: " << speed << " km/hr." << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

}



void cleanup(std::vector<Vehicle*>& vehicles, std::vector<Driver*>& drivers) {

    for (auto v : vehicles) delete v;

    for (auto d : drivers) delete d;

}



void printArrivalTime(int startHr, int startMin, int durationMin) {

    int totalMinutes = startHr * 60 + startMin + durationMin;

    int arrivalHr = totalMinutes / 60;

    int arrivalMin = totalMinutes % 60;

    std::cout << "You started at " << startHr << " hr " << startMin << " min. ";

    std::cout << "Estimated arrival at " << arrivalHr << " hr " << arrivalMin << " min." << std::endl;

}



std::vector<int> allDaysOfMonth() {

    std::vector<int> v; for(int i=1;i<=31;++i) v.push_back(i); return v;

}
