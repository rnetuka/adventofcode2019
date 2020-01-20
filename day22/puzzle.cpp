//
// Created by rnetuka on 22.12.19.
//

#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../utils.h"

using namespace std;
using deck = deque<long>;

constexpr long oversized_deck_size = 119'315'717'514'047;


deck create_deck()
{
    deck cards(10'007);
    iota(cards.begin(), cards.end(), 0);
    return cards;
}

long index_of(const deck& cards, long card) {
    auto it = find(cards.begin(), cards.end(), card);
    return distance(cards.begin(), it);
}

void deal_into_new_stack(deck& cards)
{
    deck new_stack { cards };
    reverse(new_stack.begin(), new_stack.end());
    cards = new_stack;
}

void cut(deck& cards, int n)
{
    deck result;

    if (n > 0) {
        result.insert(result.begin(), cards.begin() + n, cards.end());
        result.insert(result.end(), cards.begin(), cards.begin() + n);
    }
    else if (n < 0) {
        result.insert(result.begin(), cards.end() - abs(n), cards.end());
        result.insert(result.end(), cards.begin(), cards.end() - abs(n));
    }
    cards = result;
}

void deal_with_increment(deck& cards, int n)
{
    int size = cards.size();

    deck dealed_cards(size);
    int i = 0;

    while (! cards.empty()) {
        int card = cards.front();
        cards.pop_front();
        dealed_cards[i % size] = card;
        i += n;
    }
    cards = dealed_cards;
}

int position_of_2019()
{
    deck cards = create_deck();

    vector<string> lines = read_lines<string>("day22/res/input.txt");

    for (const string& line : lines)
    {
        stringstream stream { line };
        string order;
        int n = 0;

        if (line.find("deal with increment ") == 0) {
            stream >> order >> order >> order;
            stream >> n;
            deal_with_increment(cards, n);
        }
        else if (line == "deal into new stack")
            deal_into_new_stack(cards);

        else if (line.find("cut ") == 0) {
            stream >> order;
            stream >> n;
            cut(cards, n);
        }
    }
    return (int) index_of(cards, 2019);
}

long deal_into_new_stack(long position, long deck_size) {
    return deck_size - position - 1;
}

long deal_with_increment(long position, int n, long deck_size) {
    return (n * position) % deck_size;
}

long cut(long position, int n, long deck_size) {
    /*if (n < 0) {
        if (position >= deck_size - abs(n))
            return position + abs(n) - deck_size;
    }
    else {
        // n > 0
        return position + (deck_size - abs(n)) % deck_size;
    }
    return position;*/
    //return position + (deck_size - abs(n)) % deck_size;
    long offset = n < 0 ? abs(n) : deck_size - n;
    return (position + offset) % deck_size;
}

long position_of_2020()
{
    long deck_size = 10'007;
    long card = 2019;

    //long deck_size = 119'315'717'514'047;
    //long card = 2020;
    long position = card;

    vector<string> lines = read_lines<string>("day22/res/input.txt");
    vector<function<long(long)>> operations;

    for (const string& line : lines)
    {
        stringstream stream { line };
        string order;
        int n = 0;

        if (line.find("deal with increment ") == 0) {
            stream >> order >> order >> order;
            stream >> n;
            operations.emplace_back([n, deck_size](long position) {
                return deal_with_increment(position, n, deck_size);
            });
        }
        else if (line == "deal into new stack") {
            operations.emplace_back([deck_size](long position) {
                return deal_into_new_stack(position, deck_size);
            });
        }

        else if (line.find("cut ") == 0) {
            stream >> order;
            stream >> n;
            operations.emplace_back([n, deck_size](long position) {
                return cut(position, n, deck_size);
            });
        }
    }

    for (auto& operation : operations) {
        position = (2 * operation(position)) % deck_size;
    }
    return position;
    position %= deck_size;

    /*long max_i = 101'741'582'076'661 + 1;
    set<long> part_results;

    for (long i = 0; i < 170'000; i++) {
        for (auto& operation : operations) {
            position = operation(position);
            if (position == 108'705'724'129'205) {
                return -i;
            }
            if (part_results.find(position) != part_results.end()) {
                return position;
            }
            part_results.insert(position);
        }
    }*/

    // position of 2020 repeats:
    // after 137'070 steps = 108'705'724'129'205
    // after 165'855 steps = 108'705'724'129'205

    return position;
}