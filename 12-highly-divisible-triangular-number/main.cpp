/*
 * The sequence of triangle numbers is generated by adding the natural numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:
 *
 *		1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 *
 * Let us list the factors of the first seven triangle numbers:

 *  1: 1
 *  3: 1,3
 *  6: 1,2,3,6
 * 10: 1,2,5,10
 * 15: 1,3,5,15
 * 21: 1,3,7,21
 * 28: 1,2,4,7,14,28
 *
 * We can see that 28 is the first triangle number to have over five divisors.
 *
 * What is the value of the first triangle number to have over five hundred divisors?
 */

#include <iostream>

unsigned long long generate_triangular_numbers(unsigned long long nth_triangular_number)
{
    return ((nth_triangular_number + 1) * nth_triangular_number) / 2;
}

// takes about 10 minutes
long method1(int divisor_count_limit)
{
    //std::cout << generate_triangular_numbers(7) << std::endl;

    int i = 2;
    long triangular_number = generate_triangular_numbers(i);

    long number_of_divisors = 1;
    do {
        //if (triangular_number % 10 == 0)
            //std::cout << triangular_number << std::endl;
        number_of_divisors = 1;
        int firstprime = 1;
        for (int j = 2; j <= 5; j++)
        {
            if (triangular_number % j == 0)
            {
                firstprime = j;
                //std::cout << triangular_number << " : 1, " << firstprime << ", ";
                number_of_divisors += 1;
                break;
            }
        }

        for (int k = firstprime + 1; k <= (triangular_number / firstprime); k++)
        {
            if (triangular_number % k == 0)
            {
                number_of_divisors += 1;
                //std::cout << k << ", ";
            }
        }
        //std::cout << triangular_number << "\n";
        triangular_number = generate_triangular_numbers(++i);

    } while (number_of_divisors < divisor_count_limit);

    return generate_triangular_numbers(i - 1);
}


/* Example:
 * 8th triangle number = 36
 * Right of the bat, 1 and 36 are known factors.
 * So, we should search to see which of the numbers between those two are factors.
 * But for each factor we find there is an accompanying factor.
 * That accompanying factor replaces 35 as our new solution space upper bound.
 * 36 is divisible by two, so we know 2 is a factor. Its corresponding factor is 18.
 * Now, the space we need to search has been reduced to 3 to 17.
 * This pattern is continued until the ascending factors meet the decending ones.
 ****Disclaimer****
 * The number of divisors may not always be accurate. Each traiangle number that is
 * a square will be short one factor. But, for the purposes of this problem, it is
 * accurate enough.
 */
// takes about 1 second
long method2(int n)
{
    long number_of_divisors = 2; // this counts 1 and the nth triangle number as factors
    long nth_triangle_number = 2; // starts at the 2nd triangle number since the first is just 1
    while (number_of_divisors < n)
    {
        long triangular_number = generate_triangular_numbers(nth_triangle_number++);
        int divisor_count_limit = triangular_number; // the limit of
        number_of_divisors = 2; // this resets the number of divisors for the new triangle number
        for (int i = 2; i < divisor_count_limit; i++)
        {
            if (triangular_number % i == 0)
            {
                number_of_divisors += 2;
                divisor_count_limit = triangular_number / i;
            }

        }
    }
    return generate_triangular_numbers(nth_triangle_number - 1);
}


int main()
{

    //std::cout << method1(40) << std::endl;
    std::cout << method2(500) << std::endl;
    return 0;
}