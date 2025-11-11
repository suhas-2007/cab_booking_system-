
#ifndef RIDEBOOKINGSYSTEM_H

#define RIDEBOOKINGSYSTEM_H



#include <iostream>

#include <vector>

#include <string>

#include <initializer_list>



struct Date {

    int day, month, year;

    void print() const;

};



class Vehicle {

protected:

    std::string number, type, subType;

public:

    Vehicle(std::string num, std::string tp, std::string stp);

    virtual void displayDetails() const = 0;

    std::string getType() const;

    std::string getSubType() const;

    std::string getNumber() const;

    virtual ~Vehicle() {}

};



class Car : public Vehicle {

public:

    Car(std::string num, std::string stp);

    void displayDetails() const override;

};



class Bike : public Vehicle {

public:

    Bike(std::string num, std::string stp);

    void displayDetails() const override;

};



class Auto : public Vehicle {

public:

    Auto(std::string num);

    void displayDetails() const override;

};



class Driver {

    std::string name, gender, mobile;

    int id;

    Vehicle* assignedVehicle;

    std::vector<double> ratings;

    std::vector<int> availableDaysOfMonth;

public:

    Driver(std::string, int, Vehicle*, std::string, std::string, std::initializer_list<double>, const std::vector<int>&);

    void display() const;

    Vehicle* getVehicle() const;

    std::string getGender() const;

    std::string getName() const;

    int getID() const;

    std::string getMobile() const;

    double averageRating() const;

    bool isAvailableOnDay(int dayOfMonth) const;

};



class Booking {

    int bookingID, duration, otp;

    std::string riderName, startLocation, destination, userMobile, bookeeName;

    Driver* driver;

    double rating, fare;

    Date rideDate;

public:

    Booking(int, std::string, std::string, std::string, Driver*, std::string, std::string, int, int, double, Date);

    void printBooking() const;

    void setRating(double rate);

    int getDuration() const;

};



template<class T>

class BookingContainer {

    std::vector<T> bookings;

public:

    void addBooking(const T& booking) { bookings.push_back(booking); }

    void displayAll() const { for(const auto& b : bookings) b.printBooking(); }

};



int generateOTP();

int generateDuration(const std::string&, const std::string&);

double calculateFare(const std::string&, const std::string&, int);

void startTimer(int seconds);

void giveOneUpdate(int estDuration);

void cleanup(std::vector<Vehicle*>& vehicles, std::vector<Driver*>& drivers);

void printArrivalTime(int startHr, int startMin, int durationMin);

std::vector<int> allDaysOfMonth();



#endif // RIDEBOOKINGSYSTEM_H
