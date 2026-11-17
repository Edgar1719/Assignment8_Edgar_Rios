#ifndef FIELDS_H
#define FIELDS_H

#include <iostream>

// Base class for electric and magnetic fields
class Field
{
protected:
    double *value;

public:
    Field();
    Field(double x, double y, double z);
    Field(const Field &other);
    Field &operator=(const Field &other);
    virtual ~Field();

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    double getX() const;
    double getY() const;
    double getZ() const;

    double calculateMagnitude() const;
    void printMagnitude() const;
};

// Electric field class
class Electric_Field : public Field
{
private:
    double calculatedElectricField;

public:
    Electric_Field();
    Electric_Field(double x, double y, double z);
    Electric_Field(const Electric_Field &other);
    Electric_Field &operator=(const Electric_Field &other);

    void calculateElectricField(double Q, double r);
    double getCalculatedElectricField() const;

    Electric_Field operator+(const Electric_Field &other) const;

    friend std::ostream &operator<<(std::ostream &out,
                                    const Electric_Field &field);
};

// Magnetic field class
class Magnetic_Field : public Field
{
private:
    double calculatedMagneticField;

public:
    Magnetic_Field();
    Magnetic_Field(double x, double y, double z);
    Magnetic_Field(const Magnetic_Field &other);
    Magnetic_Field &operator=(const Magnetic_Field &other);

    void calculateMagneticField(double I, double r);
    double getCalculatedMagneticField() const;

    Magnetic_Field operator+(const Magnetic_Field &other) const;

    friend std::ostream &operator<<(std::ostream &out,
                                    const Magnetic_Field &field);
};

#endif

