#include <iostream>
#include <cmath>
#include "fields.h"

int main()
{
    // Create electric and magnetic field objects
    Electric_Field e1(0, 1e5, 1e3);
    Magnetic_Field b1(2, 3, 6);

    std::cout << "Electric field components: "
              << e1 << std::endl;
    e1.printMagnitude();

    std::cout << "\nMagnetic field components: "
              << b1 << std::endl;
    b1.printMagnitude();

    // Example values for the field calculations
    e1.calculateElectricField(1e-9, 0.1);
    b1.calculateMagneticField(2, 0.1);

    std::cout << "\nElectric field from Gauss' Law: "
              << e1.getCalculatedElectricField()
              << " N/C" << std::endl;

    std::cout << "Magnetic field from Ampere's Law: "
              << b1.getCalculatedMagneticField()
              << " T" << std::endl;

    // Demonstrate electric field addition
    Electric_Field e2(3, 4, 5);
    Electric_Field e3;

    e3 = e1 + e2;

    std::cout << "\nElectric field addition:" << std::endl;
    std::cout << "e1 = " << e1 << std::endl;
    std::cout << "e2 = " << e2 << std::endl;
    std::cout << "e3 = e1 + e2 = " << e3 << std::endl;

    // Demonstrate magnetic field addition
    Magnetic_Field b2(1, 2, 3);
    Magnetic_Field b3;

    b3 = b1 + b2;

    std::cout << "\nMagnetic field addition:" << std::endl;
    std::cout << "b1 = " << b1 << std::endl;
    std::cout << "b2 = " << b2 << std::endl;
    std::cout << "b3 = b1 + b2 = " << b3 << std::endl;

    // Demonstrate the copy constructor
    Electric_Field e4(e1);

    std::cout << "\nCopied electric field: "
              << e4 << std::endl;

    return 0;
}


// Base Field class

// Default constructor
Field::Field()
{
    value = new double[3];
    value[0] = 0;
    value[1] = 0;
    value[2] = 0;
}

// Constructor with three components
Field::Field(double x, double y, double z)
{
    value = new double[3];
    value[0] = x;
    value[1] = y;
    value[2] = z;
}

// Copy constructor
Field::Field(const Field &other)
{
    value = new double[3];

    for(int i = 0; i < 3; i++)
        value[i] = other.value[i];
}

// Copy assignment operator
Field &Field::operator=(const Field &other)
{
    if(this != &other)
    {
        for(int i = 0; i < 3; i++)
            value[i] = other.value[i];
    }

    return *this;
}

// Free dynamically allocated memory
Field::~Field()
{
    delete[] value;
}

// Setters
void Field::setX(double x) { value[0] = x; }
void Field::setY(double y) { value[1] = y; }
void Field::setZ(double z) { value[2] = z; }

// Getters
double Field::getX() const { return value[0]; }
double Field::getY() const { return value[1]; }
double Field::getZ() const { return value[2]; }

// Calculate the vector magnitude
double Field::calculateMagnitude() const
{
    return std::sqrt(value[0]*value[0]
                   + value[1]*value[1]
                   + value[2]*value[2]);
}

// Print components and magnitude
void Field::printMagnitude() const
{
    std::cout << "Components: ("
              << value[0] << ", "
              << value[1] << ", "
              << value[2] << ")" << std::endl;

    std::cout << "Magnitude: "
              << calculateMagnitude() << std::endl;
}


// Electric Field class

// Default constructor
Electric_Field::Electric_Field() : Field()
{
    calculatedElectricField = 0;
}

// Constructor calls the base class constructor
Electric_Field::Electric_Field(double x, double y, double z)
    : Field(x, y, z)
{
    calculatedElectricField = 0;
}

// Copy constructor
Electric_Field::Electric_Field(const Electric_Field &other)
    : Field(other)
{
    calculatedElectricField = other.calculatedElectricField;
}

// Copy assignment
Electric_Field &Electric_Field::operator=(const Electric_Field &other)
{
    if(this != &other)
    {
        Field::operator=(other);
        calculatedElectricField = other.calculatedElectricField;
    }

    return *this;
}

// Calculate electric field using Gauss' Law
void Electric_Field::calculateElectricField(double Q, double r)
{
    const double pi = 3.141592653589793;
    const double epsilon0 = 8.854187817e-12;

    if(r <= 0)
    {
        std::cout << "Distance must be greater than zero."
                  << std::endl;
        return;
    }

    calculatedElectricField = Q / (4 * pi * r * r * epsilon0);
}

// Return the calculated electric field
double Electric_Field::getCalculatedElectricField() const
{
    return calculatedElectricField;
}

// Add two electric field vectors
Electric_Field Electric_Field::operator+(const Electric_Field &other) const
{
    Electric_Field result(getX() + other.getX(),
                          getY() + other.getY(),
                          getZ() + other.getZ());

    return result;
}

// Output electric field components
std::ostream &operator<<(std::ostream &out, const Electric_Field &field)
{
    out << "(" << field.getX() << ", "
        << field.getY() << ", "
        << field.getZ() << ")";

    return out;
}


// Magnetic Field class

// Default constructor
Magnetic_Field::Magnetic_Field() : Field()
{
    calculatedMagneticField = 0;
}

// Constructor calls the base class constructor
Magnetic_Field::Magnetic_Field(double x, double y, double z)
    : Field(x, y, z)
{
    calculatedMagneticField = 0;
}

// Copy constructor
Magnetic_Field::Magnetic_Field(const Magnetic_Field &other)
    : Field(other)
{
    calculatedMagneticField = other.calculatedMagneticField;
}

// Copy assignment
Magnetic_Field &Magnetic_Field::operator=(const Magnetic_Field &other)
{
    if(this != &other)
    {
        Field::operator=(other);
        calculatedMagneticField = other.calculatedMagneticField;
    }

    return *this;
}

// Calculate magnetic field using the assignment formula
void Magnetic_Field::calculateMagneticField(double I, double r)
{
    const double pi = 3.141592653589793;
    const double mu0 = 4 * pi * 1e-7;

    if(r <= 0)
    {
        std::cout << "Distance must be greater than zero."
                  << std::endl;
        return;
    }

    calculatedMagneticField = I / (2 * pi * r * mu0);
}

// Return the calculated magnetic field
double Magnetic_Field::getCalculatedMagneticField() const
{
    return calculatedMagneticField;
}

// Add two magnetic field vectors
Magnetic_Field Magnetic_Field::operator+(const Magnetic_Field &other) const
{
    Magnetic_Field result(getX() + other.getX(),
                          getY() + other.getY(),
                          getZ() + other.getZ());

    return result;
}

// Output magnetic field components
std::ostream &operator<<(std::ostream &out, const Magnetic_Field &field)
{
    out << "(" << field.getX() << ", "
        << field.getY() << ", "
        << field.getZ() << ")";

    return out;
}

