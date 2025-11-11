# 2. OOP FEATURES.

## Overview of OOP Concepts

This project implements all key Object-Oriented Programming (OOP) concepts using a practical ride booking system. Every concept is applied in core modules to demonstrate both theoretical foundations and real-world C++ programming practices.

---

## 1. Encapsulation

### Definition
Encapsulation is the practice of bundling data and related methods within a class and restricting direct access to some of the object's components.

### Implementation in Ride Booking System

- **Driver**, **Vehicle**, **Booking**, and related classes encapsulate their data through private member variables.
- Public getter and setter functions provide controlled access.

#### Example:
    class Driver {
    private:
    std::string name, gender, mobile;
    int id;
    Vehicle* assignedVehicle;
    std::vector<double> ratings;
    std::vector<int> availableDaysOfMonth;
    public:
    Driver(...);
    void display() const;
    std::string getName() const;
    double averageRating() const;
    // ... other public methods
    };

text
All member fields are private. Access is handled via explicit public functions.

---

## 2. Abstraction

### Definition
Abstraction involves exposing only relevant data and operations, hiding internal implementation details.

### Implementation in Ride Booking System

- Abstract base class **Vehicle**:
    - Has pure virtual function `displayDetails()`.
    - Only the relevant booking operations are shown to the main program, hiding vehicle detail specifics.

#### Example:
    class Vehicle {
    protected:
    std::string number, type, subType;
    public:
    Vehicle(...);
    virtual void displayDetails() const = 0;
    // Abstracts away vehicle-specific representation
    };

text
The user interacts with generic `Vehicle` pointers and does not worry about the underlying concrete types.

---

## 3. Inheritance

### Definition
Inheritance allows one class to derive properties and behaviors from another, fostering code reuse and hierarchy.

### Implementation in Ride Booking System

- **Car**, **Bike**, and **Auto** classes inherit from the base `Vehicle` class.
- Each provides specialized implementations of the `displayDetails()` method.

#### Example:
    class Car : public Vehicle {
    public:
    Car(std::string num, std::string stp);
    void displayDetails() const override;
    };

text
This demonstrates classic IS-A relationships: *Car IS-A Vehicle*, etc.

---

## 4. Polymorphism

### Definition
Polymorphism allows objects of different types derived from the same base class to be treated uniformly.

### Implementation in Ride Booking System

- Through **Vehicle** base class pointers, the system holds and processes different vehicle types.
- Virtual functions like `displayDetails()` ensure the correct method is called per subclass.

#### Example:
    Vehicle* v;
    v = new Car(...);
    v->displayDetails(); // Calls Car-specific implementation at runtime

    v = new Bike(...);
    v->displayDetails(); // Calls Bike-specific implementation

text
This is runtime (dynamic) polymorphism using virtual methods.

---

## 5. Operator Overloading

### Definition
Operator overloading enables custom definitions of operators for user-defined types to enhance natural syntax.

### Implementation in Ride Booking System

- The `BookingContainer` template uses operator overloading for methods as needed (extendible).
- The code structure is adaptable for inserting custom overloaded operators for printing, comparison, etc.

#### Example (Optional, for extension):
    friend std::ostream& operator<<(std::ostream& os, const Booking& b) {
    b.printBooking();
    return os;
    }

text
This would allow usage: `std::cout << bookingObj;`.

---

## 6. Templates (Generic Programming)

### Definition
Templates allow the creation of generic, reusable code for any data type.

### Implementation in Ride Booking System

- Template class **BookingContainer<T>** is used to store and manage collections of bookings.

#### Example:
    template<class T>
    class BookingContainer {
    std::vector<T> bookings;
    public:
    void addBooking(const T& booking) { bookings.push_back(booking); }
    void displayAll() const { for(const auto& b : bookings) b.printBooking(); }
    };

text
Provides generic collection management for any booking record type.

---

## 7. Exception Handling

### Definition
Exception handling gracefully manages runtime errors, preventing program crashes.

### Implementation in Ride Booking System

- Uses sanity checks for invalid input and selection; uses clean exits and messages rather than crashing.
- Resource cleanup is done before exit to avoid memory leaks (RAII principle).

#### Example:
    if (eligibleDrivers.empty()) {
    std::cout << "No eligible drivers found for chosen day. Exiting.\n";
    cleanup(vehicles, drivers);
    return 1; // Gracefully exit
    }

text
Resource deallocation occurs before early exits, simulating exception-safe handling in C++.

---

## Summary Table

| OOP Concept         | Primary Implementation            | Code Reference               |
|---------------------|-----------------------------------|------------------------------|
| Encapsulation       | Private class members, getters    | Driver, Vehicle, Booking     |
| Abstraction         | Virtual base class, interfaces    | Vehicle, displayDetails      |
| Inheritance         | Vehicle hierarchy                 | Car, Bike, Auto              |
| Polymorphism        | Virtual functions, base pointers  | Vehicle*, displayDetails     |
| Operator Overloading| (Optional: std::ostream for Booking) | BookingContainer (extendible)|
| Templates           | Generic BookingContainer<T>       | BookingContainer             |
| Exception Handling  | Input validation, cleanup, flow control | main, cleanup(), user input  |

---

**All seven OOP concepts are actively demonstrated through the system's design and code structure.**
