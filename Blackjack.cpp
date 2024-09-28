#include <iostream>
#include <cstdlib>
#include <utility>
#include <ctime>
#include <vector>
using namespace std;

void PlayingCardChecker(int x, int y, char& card, string& type) {
    switch (y) {
    case 0:
        card = 'A';
        break;
    case 1:
        card = '2';
        break;
    case 2:
        card = '3';
        break;
    case 3:
        card = '4';
        break;
    case 4:
        card = '5';
        break;
    case 5:
        card = '6';
        break;
    case 6:
        card = '7';
        break;
    case 7:
        card = '8';
        break;
    case 8:
        card = '9';
        break;
    case 9:
        card = '1'; 
        break;
    case 10:
        card = 'J';
        break;
    case 11:
        card = 'Q';
        break;
    case 12:
        card = 'K';
        break;
    }

    switch (x) {
    case 0:
        type = "inima rosie";
        break;
    case 1:
        type = "trefla";
        break;
    case 2:
        type = "inima neagra";
        break;
    case 3:
        type = "romb";
        break;
    }
}

pair<int, int> Hit(int deck[][13]) {
    int x, y;
    do {
        x = rand() % 4;
        y = rand() % 13;
    } while (deck[x][y] == 0);
    deck[x][y] = 0;
    return make_pair(x, y);
}

int GetCardValue(char card) {
    if (card == 'A') return 11;
    if (card == 'J' || card == 'Q' || card == 'K') return 10;
    if (card == '1') return 10;
    return card - '0';
}

int CalculateHandValue(const vector<pair<char, string>>& hand) {
    int value = 0;
    int aceCount = 0;

    for (const auto& card : hand) {
        int cardValue = GetCardValue(card.first);
        value += cardValue;

        if (card.first == 'A')
            aceCount++;
    }

    while (value > 21 && aceCount > 0) {
        value -= 10;
        aceCount--;
    }

    return value;
}

void PrintHand(const vector<pair<char, string>>& hand, const string& owner) {
    cout << owner << "'s hand:" << endl;
    for (const auto& card : hand) {
        cout << card.first;
        if (card.first == '1') cout << '0';
        cout << " de " << card.second << endl;
    }
    cout << "Total puncte: " << CalculateHandValue(hand) << endl << endl;
}

void DealerTurn(int deck[][13], vector<pair<char, string>>& dealerHand) {
    while (CalculateHandValue(dealerHand) < 17) {
        pair<int, int> coords = Hit(deck);
        char card;
        string type;
        PlayingCardChecker(coords.first, coords.second, card, type);
        dealerHand.push_back(make_pair(card, type));
    }
}

bool CheckBust(const vector<pair<char, string>>& hand) {
    return CalculateHandValue(hand) > 21;
}

bool Check21(const vector<pair<char, string>>& hand) {
    return CalculateHandValue(hand) == 21;
}

int main() {
    srand(time(0));
    int deck[4][13];
    char card;
    string type;

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            deck[j][i] = 1;
        }
    }

    vector<pair<char, string>> playerHand, dealerHand;
    string action;
    
    for (int i = 0; i < 2; i++) {
        pair<int, int> coords = Hit(deck);
        PlayingCardChecker(coords.first, coords.second, card, type);
        playerHand.push_back(make_pair(card, type));

        coords = Hit(deck);
        PlayingCardChecker(coords.first, coords.second, card, type);
        dealerHand.push_back(make_pair(card, type));
    }
        
    cout << "BLACKJACK" << endl;
   
    cout << "Dealer's hand:" << endl;
    cout << "1. ";
    cout << dealerHand[0].first;
    if (dealerHand[0].first == '1') cout << "0";
    cout << " de " << dealerHand[0].second << endl;
    cout << endl;

    while (true) {
        PrintHand(playerHand, "Player");
        if (CheckBust(playerHand)) {
            cout << "Player-ul a pierdut! Dealer-ul a castigat." << endl;
            return 0;
        }

        else if (Check21(playerHand)) {
            cout << "Player-ul a castigat! Dealer-ul a pierdut." << endl;
            return 0;
        }

        cout << "Hit sau stand? (hit/stand): ";
        cin >> action;
        cout << endl;
        
        if (action == "stand") break;
        if (action == "hit") {
            pair<int, int> coords = Hit(deck);
            PlayingCardChecker(coords.first, coords.second, card, type);
            playerHand.push_back(make_pair(card, type));
        }
    }

    DealerTurn(deck, dealerHand);
    PrintHand(dealerHand, "Dealer");

    if (CheckBust(dealerHand)) {
        cout << "Dealer-ul a pierdut. Jucatorul a castigat." << endl;
        return 0;
    }

    int playerValue = CalculateHandValue(playerHand);
    int dealerValue = CalculateHandValue(dealerHand);

    if (playerValue > dealerValue)
        cout << "Jucatorul a castigat cu " << playerValue << " puncte!" << endl;
    else if (dealerValue > playerValue)
        cout << "Dealer-ul a castigat cu " << dealerValue << " puncte!" << endl;
    else
        cout << "Remiza!" << endl;

    return 0;
}
