# 4. SOURCE CODE SAMPLES

This section provides representative code samples from the Ride Booking System project, including explanations of design and implementation choices.

---

## Sample 1: Vehicle Class - Abstraction and Inheritance

**File:** RideBookingSystem.h / RideBookingSystem.cpp  
**Purpose:** Demonstrates abstraction (base class), inheritance, and polymorphism.

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

text
**Design Reasoning:**  
- Vehicle serves as an abstract base class with a pure virtual method.
- Car (and other subclasses) inherit from Vehicle and provide their own implementations of details.

---

## Sample 2: Driver Class - Encapsulation and Composition

**File:** RideBookingSystem.h / RideBookingSystem.cpp  
**Purpose:** Demonstrates encapsulation of data and composition via Vehicle pointer.

    class Driver {
    std::string name, gender, mobile;
    int id;
    Vehicle* assignedVehicle;
    std::vector<double> ratings;
    std::vector<int> availableDaysOfMonth;
    public:
    Driver(std::string, int, Vehicle*, std::string, std::string,
    std::initializer_list<double>, const std::vector<int>&);

text

    void display() const;
    Vehicle* getVehicle() const;
    std::string getGender() const;
    std::string getName() const;
    int getID() const;
    std::string getMobile() const;
    double averageRating() const;
    bool isAvailableOnDay(int dayOfMonth) const;
    };
    
text
**Design Reasoning:**  
- Fields are private, accessed through public methods for safety.
- Composition allows each driver to own a vehicle.

---

## Sample 3: BookingContainer Template - Generic Programming

**File:** RideBookingSystem.h  
**Purpose:** Demonstrates template-based container for bookings.

    template<class T>
    class BookingContainer {
    std::vector<T> bookings;
    public:
    void addBooking(const T& booking) { bookings.push_back(booking); }
    void displayAll() const { for(const auto& b : bookings) b.printBooking(); }
    };

text
**Design Reasoning:**  
- Template class enables storage and management of bookings generically and efficiently.
- Easy to extend for other entities besides Booking.

---

## Sample 4: Fare Calculation - Functional Logic

**File:** RideBookingSystem.cpp  
**Purpose:** Shows procedural and selection logic applied for fare computation.

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

text
**Design Reasoning:**  
- Branching logic enables dynamic pricing based on user selection.
- Easily extendable for new vehicle types or pricing strategies.

---

## Sample 5: Booking Flow - Main Interactive Loop

**File:** main.cpp  
**Purpose:** Integrates all major classes and user interactions.

    std::cout << "Choose Vehicle Type:\n1. Car\n2. Bike\n3. Auto\nChoice: ";
    int vtype; std::cin >> vtype; std::cin.ignore();
    std::string subtypeChoice, typeString;
    if (vtype == 1) {
    typeString = "Car";
    std::cout << "Choose car type:\n1. Sedan\n2. SUV\nChoice: ";
    int ctype; std::cin >> ctype; std::cin.ignore();
    if (ctype == 1) subtypeChoice = "Sedan";
    else if (ctype == 2) subtypeChoice = "SUV";
    else { /* error handling / }
    } else if (vtype == 2) {
    typeString = "Bike";
    std::cout << "Choose bike type:\n1. Scooty\n2. Motorbike\nChoice: ";
    int btype; std::cin >> btype; std::cin.ignore();
    if (btype == 1) subtypeChoice = "Scooty";
    else if (btype == 2) subtypeChoice = "Motorbike";
    else { / error handling / }
    } else if (vtype == 3) {
    typeString = "Auto";
    subtypeChoice = "Auto";
    } else { / error handling */ }

text
**Design Reasoning:**  
- Interactive prompts structure the flow.
- Selection and error handling organized for a robust user experience.

---

## Sample 6: OTP Generation - Basic Random Utility

**File:** RideBookingSystem.cpp

    int generateOTP() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    return dis(gen);
    }

text
**Design Reasoning:**  
- C++ standard random library generates 4-digit OTP.
- Stateless and secure for booking confirmation.

---

## Sample 7: Resource Cleanup - Manual Memory Management

**File:** RideBookingSystem.cpp

    void cleanup(std::vector<Vehicle*>& vehicles, std::vector<Driver*>& drivers) {
    for (auto v : vehicles) delete v;
    for (auto d : drivers) delete d;
    }

text
**Design Reasoning:**  
- Prevents resource leaks in environments without smart pointers.
- Demonstrates RAII principles for object lifecycle control.

---

## Sample 8: Dynamic Fare Choices and Feedback

**File:** main.cpp

    std::cout << "\nOptions before allocation: \n"
    << "A. Cancel Ride & give feedback\n"
    << "B. Continue ride (back to options)\n"
    << "C. Request Decrease Fare\n"
    << "D. Increase Fare for faster allocation\n"
    << "E. Continue with current fare\n";
    std::string preOpt; getline(std::cin, preOpt);

    if (preOpt == "A" || preOpt == "a") {
    std::cout << "You chose to cancel. Please provide feedback:";
    std::string cancelFeedback; getline(std::cin, cancelFeedback);
    std::cout << "Your feedback is recorded: " << cancelFeedback << "\nBooking cancelled.\n";
    cleanup(vehicles, drivers); return 1;
    } else if (preOpt == "C" || preOpt == "c") {
    fare *= 0.9;
    std::cout << "Fare reduced by 10%. New fare: ₹" << fare << std::endl;
    // back to options...
    }

text
**Design Reasoning:**  
- Flexible business logic lets users modify rides or fares before confirmation.
- Feedback collected for canceled rides.

---

## Sample 9: Polymorphism in Action - Display Details

**File:** Various classes

    Vehicle* v1 = new Car("KA01SED1001", "Sedan");
    Vehicle* v2 = new Bike("KA01SCT3001", "Scooty");

    std::vector<Vehicle*> vehicles = {v1, v2};
    for (auto v : vehicles) {
    v->displayDetails(); // Calls correct override at runtime
    }

text
**Design Reasoning:**  
- Runtime polymorphism ensures correct function calls with base class pointers.

---

## Sample 10: Data Encapsulation in Booking

**File:** RideBookingSystem.h / RideBookingSystem.cpp

    class Booking {
    int bookingID, duration, otp;
    std::string riderName, startLocation, destination, userMobile, bookeeName;
    Driver* driver;
    double rating, fare;
    Date rideDate;
    public:
    Booking(...);
    void printBooking() const;
    void setRating(double rate);
    int getDuration() const;
    };

text
**Design Reasoning:**  
- Private data completely encapsulated.
- Only interface methods for reading/modifying state.

---

Each sample above demonstrates a principle or practice from the codebase, illustrating C++ OOP features and software engineering best practices.
