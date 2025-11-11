
# 3. SYSTEM DESIGN

## Architecture Overview

The **Ride Booking System** follows a modular design approach, ensuring clear separation of concerns and maintainability. The architecture reflects principles inspired by the Model-View-Controller (MVC) paradigm for command-line applications:
- **Model**: Entity classes such as `Vehicle`, `Car`, `Bike`, `Auto`, `Driver`, and `Booking` represent system state and core data.
- **Controller**: The main application logic (within `main.cpp`) orchestrates user interaction, data flow, and driver allocation.
- **View**: All interactions and outputs are provided as formatted console messages for a user-friendly experience.

---

## Class Diagram Structure

### Core Classes

- **Vehicle (Abstract)**
  - Base class for all vehicles. Implements common attributes and exposes a virtual display method.
- **Car, Bike, Auto**
  - Inherit from `Vehicle`. Each implements vehicle-specific details and overrides display features.
- **Driver**
  - Manages driver details, assigned vehicle, rating system, and availability for specific dates.
- **Booking**
  - Encapsulates a ride booking's details, such as user name, allocated driver, route, fare, OTP, rating, and ride date.
- **BookingContainer\<T\> (Template)**
  - Generic container to manage multiple bookings with batch display and addition functionality.

---

## Utility Functions & Features

- `generateOTP()` - Creates random OTP for booking confirmation.
- `generateDuration()` - Estimates trip duration based on vehicle type and subtype.
- `calculateFare()` - Dynamically calculates fare using type, subtype, and duration.
- `startTimer()` - Simulates allocation wait before ride is confirmed.
- `giveOneUpdate()` - Provides real-time ride status (ETA & speed) during travel.
- `cleanup()` - Deallocates dynamically created vehicles/drivers, preventing resource leaks.
- `printArrivalTime()` - Shows journey start and computed arrival times.

---

## Detailed Class Descriptions

### 1. Vehicle (Abstract Base Class)
**File:** RideBookingSystem.h / RideBookingSystem.cpp  
**Purpose:** Defines the common fields and interface for all vehicle types.

- Private/Protected Members:
  - `number`          // Vehicle registration number
  - `type`            // Vehicle category (Car, Bike, Auto)
  - `subType`         // Specific subcategory (Sedan, SUV, etc.)

- Public Methods:
  - `getType()`
  - `getSubType()`
  - `getNumber()`
  - `virtual displayDetails()`    // Pure virtual for info display

**OOP Concepts:** Abstraction, Inheritance, Polymorphism

---

### 2. Car, Bike, Auto Classes
**File:** RideBookingSystem.h / RideBookingSystem.cpp  
**Purpose:** Specialized vehicle classes with unique display implementations.

- Constructors initialize type/subType info.
- Overrides `displayDetails()` for vehicle-specific output.

**OOP Concepts:** Inheritance, Polymorphism

---

### 3. Driver Class
**File:** RideBookingSystem.h / RideBookingSystem.cpp  
**Purpose:** Handles driver identity, allocated vehicle, contact, real-time average ratings, and date availability.

- Members:
  - `name`, `gender`, `mobile`, `id`
  - `Vehicle* assignedVehicle`       // Association with vehicle
  - `std::vector<double> ratings`    // User ratings
  - `std::vector<int> availableDaysOfMonth` // Availability control

- Methods:
  - `display()`                     // Print driver and vehicle info
  - `averageRating()`               // Compute average rating
  - `isAvailableOnDay()`            // Date-wise query for allocation

**OOP Concepts:** Encapsulation, Composition

---

### 4. Booking Class
**File:** RideBookingSystem.h / RideBookingSystem.cpp  
**Purpose:** Central unit representing each confirmed ride.

- Members:
  - `bookingID`, `duration`, `otp`
  - `riderName`, `bookeeName`, `userMobile`
  - `Driver* driver`, `rating`, `fare`, `Date rideDate`
  - `startLocation`, `destination`

- Methods:
  - `printBooking()`                // Print complete ticket details
  - `setRating(double)`             // Update feedback/rating

**OOP Concepts:** Encapsulation, Composition

---

### 5. BookingContainer\<T\> (Template Class)
**File:** RideBookingSystem.h  
**Purpose:** Generic class for handling lists/arrays of bookings or future extensible types.

- Members:
  - `std::vector<T> bookings`
- Methods:
  - `addBooking(const T&)`
  - `displayAll()`                  // Batch show all bookings

**OOP Concepts:** Templates, Encapsulation

---

## Data Structures and Relationships

- **Associations:**  
  - Each `Driver` HAS-A `Vehicle`.
  - Each `Booking` HAS-A `Driver` and `Date`.

- **Composition:**  
  - The system owns vehicles and drivers via vectors and pointers.

- **Generic Containers:**  
  - `BookingContainer\<T\>` can manage multiple booking records in an extensible way.

---

## Control Flow

### Program Execution

1. **Startup:**  
   - System initializes vehicles and drivers, including setting their availability.

2. **Booking Process:**  
   - User prompted for details (self/other, gender, date, locations).
   - Vehicle and driver options shown per availability.
   - Fare is computed, user can adjust it or cancel (with feedback).
   - Confirmation allocates driver, generates OTP.
   - Arrival time calculated, optional ride updates and progress simulated.

3. **Rating and Feedback:**  
   - At journey end, user rates ride, leaves comments.
   - All details printed and logs updated.

4. **Cleanup:**  
   - All dynamically created objects are deallocated at program end.

---

### Data & Memory Management

- Vectors and pointers used for vehicles, drivers, and bookings.
- Manual resource cleanup with the `cleanup()` function to avoid memory leaks (no standard smart pointers for educational clarity).

### Input Validation

- User entries and selections are validated, with reprompts for invalid choices (vehicle type, driver number, options).
- Graceful error exits for unavailable resources.

---

## Configuration and Extensibility

- Additional vehicle types/subtypes can be easily added by creating new classes inheriting from `Vehicle`.
- Booking and driver logic can be extended to include rating algorithms, history, etc.
- Template classes support batch record management for future upgrades.

---

## Summary

The overall system design combines best practices in OOP, modularity, and interactive command-line programming. Each class has a distinct role, resulting in flexible, maintainable, and easily extensible code.

---

