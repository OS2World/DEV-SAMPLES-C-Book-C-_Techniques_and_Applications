//  Header:     Complex
//  Version:    2.20
//
//  Language:   C++ 2.0
//  Environ:    Any
//
//  Purpose:    Provides the class "Complex" for C++ programs. The majority
//              of the class is implemented inline for efficiency. Only
//              the division, power, and i/o methods are actual functions.
//
//  Written by: Scott Robert Ladd

#if !defined(__COMPLEX_HPP)
#define __COMPLEX_HPP 1

class Complex
    {
    private:
        double Real; // Real part
        double Imag; // Imaginary part

        static void (* ErrorHandler)();

    public:
        // constructors
        Complex (void);
        Complex (const Complex & c);
        Complex (const double & r, const double & i);
        Complex (const double & r);

        // method to set error handler function
        static void SetErrorHandler(void (* userHandler)());

        // value extraction methods
        friend double real(const Complex & c);
        friend double imag(const Complex & c);

        // assignment methods
        void operator = (const Complex & c);

        // utility methods
        friend double abs(const Complex & c);
        friend double norm(const Complex & c);
        friend double arg(const Complex & c);

        // unary minus method
        Complex operator - ();

        // calculation methods
        friend Complex operator + (const Complex & c1, const Complex & c2);
        friend Complex operator - (const Complex & c1, const Complex & c2);
        friend Complex operator * (const Complex & c1, const Complex & c2);
        friend Complex operator / (const Complex & c1, const Complex & c2);

        Complex operator += (const Complex & c);
        Complex operator -= (const Complex & c);
        Complex operator *= (const Complex & c);
        Complex operator /= (const Complex & c);

        // comparison methods
        friend int operator == (const Complex & c1, const Complex & c2);
        friend int operator != (const Complex & c1, const Complex & c2);

        friend int operator <  (const Complex & c1, const Complex & c2);
        friend int operator <= (const Complex & c1, const Complex & c2);

        friend int operator >  (const Complex & c1, const Complex & c2);
        friend int operator >= (const Complex & c1, const Complex & c2);

        // polar coordinate methods
        friend Complex polar(const double radius, const double theta = 0.0);
        friend Complex conj(const Complex & c);

        // trigonometric methods
        friend Complex cos(const Complex & c);
        friend Complex sin(const Complex & c);
        friend Complex tan(const Complex & c);

        friend Complex cosh(const Complex & c);
        friend Complex sinh(const Complex & c);
        friend Complex tanh(const Complex & c);

        // logarithmic methods
        friend Complex exp(const Complex & c);
        friend Complex log(const Complex & c);

        // "power" methods
        friend Complex pow(const Complex & c, const Complex & power);
        friend Complex sqrt(const Complex & c);

        // output method
        int Print() const;
    };

#endif
