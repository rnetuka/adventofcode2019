//
// Created by rnetuka on 03.12.19.
//

/*
 * --- Day 4: Secure Container ---
 * You arrive at the Venus fuel depot only to discover it's protected by a password. The Elves had written the password
 * on a sticky note, but someone threw it out.
 *
 * However, they do remember a few key facts about the password:
 *
 * It is a six-digit number.
 * The value is within the range given in your puzzle input.
 * Two adjacent digits are the same (like 22 in 122345).
 * Going from left to right, the digits never decrease; they only ever increase or stay the same (like 111123 or 135679).
 * Other than the range rule, the following are true:
 *
 * 111111 meets these criteria (double 11, never decreases).
 * 223450 does not meet these criteria (decreasing pair of digits 50).
 * 123789 does not meet these criteria (no double).
 *
 * How many different passwords within the range given in your puzzle input meet these criteria?
 *
 * Your puzzle input is 240920-789857.
 *
 * --- Part Two ---
 * An Elf just remembered one more important detail: the two adjacent matching digits are not part of a larger group of
 * matching digits.
 *
 * Given this additional criterion, but still ignoring the range rule, the following are now true:
 *
 * 112233 meets these criteria because the digits never decrease and all repeated digits are exactly two digits long.
 * 123444 no longer meets the criteria (the repeated 44 is part of a larger group of 444).
 * 111122 meets the criteria (even though 1 is repeated more than twice, it still contains a double 22).
 *
 * How many different passwords within the range given in your puzzle input meet all of the criteria?
 *
 * Your puzzle input is still 240920-789857.
 */

#include <cmath>
#include <functional>

using namespace std;


namespace day4 {

    constexpr int password_size = 6;
    constexpr int min_password = 240920;
    constexpr int max_password = 789857;

    constexpr int digit_count(int value) {
        return (int) log10(value) + 1;
    }

    struct password {
        const int value;
        const int size;

        password(int value) : value { value }, size { digit_count(value) } {

        }

        int digit(int i) const
        {
            if (i < 0 || i > size)
                return -1;

            int n = password_size - i - 1;
            return (int) (value / pow(10, n)) % 10;
        }
    };

    bool meets_criteria(const password& password)
    {
        if (password.size != password_size)
            return false;

        if (password.value < min_password || password.value > max_password)
            return false;

        for (int i = 0; i < password_size - 1; i++) {
            if (password.digit(i) > password.digit(i + 1))
                return false;
        }

        for (int i = 0; i < password_size - 1; i++) {
            if (password.digit(i) == password.digit(i + 1))
                return true;
        }

        return false;
    }

    bool meets_additional_criteria(const password& password)
    {
        if (! meets_criteria(password))
            return false;

        for (int i = 0; i < password_size - 1; i++) {
            if (password.digit(i) == password.digit(i + 1))
                if (password.digit(i - 1) != password.digit(i) && password.digit(i + 1) != password.digit(i + 2))
                    return true;
        }

        return false;
    }

    int password_combinations(const function<bool(const password&)>& predicate)
    {
        int count = 0;

        for (int password = min_password; password < max_password; password++) {
            if (predicate(password))
                count++;
        }

        return count;
    }

    int password_combinations1()
    {
        return password_combinations(meets_criteria);
    }

    int password_combinations2()
    {
        return password_combinations(meets_additional_criteria);
    }

}