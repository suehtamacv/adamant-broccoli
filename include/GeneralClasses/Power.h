#ifndef POWER_H
#define POWER_H

#include <GeneralClasses/Gain.h>

/**
 * @brief The Power class represents a power, either measured in dBm or in Watts.
 */
class Power
{
public:
    /**
    * @brief The InitType enum is used to choose how to init the object.
    */
    enum InitType
    {
        dBm, /*!< Use dBm to provide an initial value in dBm */
        Watt /*!< Use Watt to provide an initial value in watts */
    };
    /**
     * @brief Power is the standard constructor for a Power.
     * @param value is the value of the power, either in dBm or in Watts.
     * @param Type is the type of Power initialization, dBm or Watts.
     */
    Power(double value, InitType = dBm);
    /**
     * @brief Power is the copy constructor for a Power.dBm
     */
    Power(const Power &);

    /**
     * @brief operator * applies a Gain G over this Power.
     * @param G is the Gain.
     * @return a Power object, after suffering the Gain G.
     */
    Power operator*(Gain G);
    /**
     * @brief operator + adds another Power P to this Power.
     * @param P is the Power.
     * @return a Power object, result of summing the two Powers.
     */
    Power operator+(const Power &P);
    /**
     * @brief operator *= applies a Gain G over this power.
     * @param G is the Gain.
     * @return a reference to this object.
     */
    Power &operator*=(Gain &G);
    /**
     * @brief operator += adds another Power P to this Power.
     * @param P is the Power.
     * @return a reference to this object.
     */
    Power &operator+=(const Power &P);
    /**
     * @brief operator == compares two Powers for equality.
     * @return true iff powers are equal.
     */
    bool operator==(const Power &P) const;
    /**
     * @brief operator != compares two Powers for unequality.
     * @return true iff powers aren't equal.
     */
    bool operator!=(const Power &P) const;
    /**
     * @brief operator < compares the order of two Powers.
     * @return true iff the value of this power, in Watts, is less than the value of P, in Watts.
     */
    bool operator<(const Power &P) const;
    /**
     * @brief operator <= compares the order of two Powers.
     * @return true iff the value of this power, in Watts, is less than or equal to the value of P, in Watts.
     */
    bool operator<=(const Power &P) const;
    /**
     * @brief operator > compares the order of two Powers.
     * @return true iff the value of this power, in Watts, is greater than the value of P, in Watts.
     */
    bool operator>(const Power &P) const;
    /**
     * @brief operator >= compares the order of two Powers.
     * @return true iff the value of this power, in Watts, is greater than or equal to the value of P, in Watts.
     */
    bool operator>=(const Power &P) const;
    /**
     * @brief operator / returns the quotient between two Powers.
     * @return a gain representing the quotient between the Powers.
     */
    Gain operator/(const Power &P) const;

    /**
     * @brief in_dBm returns the value of this Power in dBm.
     * @return the value of this Power in dBm.
     */
    double in_dBm() const;
    /**
     * @brief in_Watts returns the value of this Power in Watts.
     * @return the value of this Power in Watts.
     */
    double in_Watts() const;

    friend std::ostream& operator<<(std::ostream &out, const Power &P);

private:
    double value_Watts;
};

#endif // POWER_H
