#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

enum type {
    FIVE_OF_KIND = 5,
    FOUR_OF_KIND = 4,
    FULL_HOUSE = 3,
    THREE_OF_KIND = 2,
    TWO_PAIR = 1,
    ONE_PAIR = 0,
    HIGH_CARD = -1,
};

std::map<char, int> vals = {
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'T', 10},
        {'Q', 12},
        {'K', 13},
        {'A', 14},
        {'J', 1}
};

struct CamelHand {
    type rank;
    int value;
    char cards[5];
    std::string cards_str;
    std::map<int, int> occurances;

    CamelHand(std::string cards_str, int value)
    {
        this->cards_str = cards_str;
        this->value = value;

        for(int i = 0; i < cards_str.size(); i++)
        {
            cards[i] = vals[cards_str[i]];
        }
        this->determine_rank();
    }

    void determine_rank()
    {
        int joker_count = 0;
        for(auto element : cards)
        {
            if(element == 1)
            {
                joker_count += 1;
            }
            else {
                occurances[element]++;
            }
        }

        std::vector<int> occ;
        for(auto element : occurances)
        {
            occ.push_back(element.second);
        }
        std::sort(occ.begin(), occ.end(), std::greater<int>());

        if(joker_count == 5)
        {
            rank = FIVE_OF_KIND;
            return;
        }
        int t = occ[0] + joker_count;
        if(t == 5)
        {
            rank = FIVE_OF_KIND;
            return;
        }
        t = occ[0] + joker_count;
        if(t == 4)
        {
            rank = FOUR_OF_KIND;
            return;
        }
        //joker count is CERTAINLY lower than 4
        // j1 + j2 = joker_count
        // occ[0] + j1 >= 3
        // occ[1] + j2 >= 2
        // occ[1] + occ[0] + j1 + j2 >= 5
        if(occ[0] + occ[1] + joker_count >= 5)
        {
            rank = FULL_HOUSE;
            return;
        }
        // occ[0] + j1 >= 3
        // occ[1] + j2 >= 1
        // occ[2] + j3 >= 1
        if(occ[0] + occ[1] + occ[2] + joker_count >= 5)
        {
            rank = THREE_OF_KIND;
            return;
        }
        if(occ[0] == 2 && occ[1] == 2 && occ[2] == 1)
        {
            rank = TWO_PAIR;
            return;
        }

        t = occ[0] + joker_count;
        if(t >= 2)
        {
            rank = ONE_PAIR;
        }
        else
        {
            rank = HIGH_CARD;
            return;
        }




    }

    bool operator<(const CamelHand & right) const {
        if(this->rank > right.rank)
        {
            return true;
        }
        if(this->rank == right.rank) {
            for(int i = 0; i < 5; i++)
            {
                if(this->cards[i] == right.cards[i]) continue;
                if(this->cards[i] > right.cards[i])
                {
                    return true;
                }
                else return false;
            }
        }
        return false;
    }

};

int main() {
    std::vector<CamelHand> hands;
    while(true)
    {
        int value;
        std::string hand;
        std::cin >> hand;
        if(hand == "end") break;
        std::cin >> value;

        CamelHand ch = CamelHand(hand, value);
        hands.push_back(std::move(ch));
    }

    std::sort(hands.begin(), hands.end());
    std::reverse(hands.begin(), hands.end());

    unsigned long long int score = 0;
    for(int i = 0; i < hands.size(); i++)
    {
        score += hands[i].value * (i+1);
    }
    for(auto & hand : hands)
    {
        for(auto c : hand.cards_str)
        {
            //if(c == 'J')
            //{
                std::cout << hand.cards_str << " " << hand.rank << std::endl;
                break;
            //}

        }

    }

    std::cout << score << std::endl;
}
