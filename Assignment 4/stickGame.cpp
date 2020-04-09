/*
Rishabh Niranjan
1801140

##The game of sticks: To design a Min/Max game tree with alpha-beta pruning for the game.
The description of the game is as follows:
•It is a 2-player game.
•There is a heap of sticks on a board, say N.
•Each player picks up sticks alternatively.
•On their turn, each player has to pick at least 1 stick and he can pick at most 3 sticks.
•The one who has to pick the final stick will be the loser.•First turn will be randomly decided with toss.
•To design AIvsHUMAN and AIvsAI game.
*/
#include <bits/stdc++.h>
#include <memory>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef queue<int> qi;
typedef vector<string> vs;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef vector<pair<int, int>> vpii;
typedef vector<pair<long long, long long>> vpll;
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
#define mod 1000000007

void humanVShuman(int);
unique_ptr<int[]> minMax(int, int, int, int);
void humanVSai(int);
void aiVSai(int);

int toss()
{
    return (rand() % 2) + 1;
}

int main()
{
    srand(time(NULL));

    int N, choice;
    cout << "1.)Human v/s Human\n2.Human v/s AI\n3.AI v/s AI\n";
    cout << "Enter value : ";
    do
    {
        cin >> choice;
        if (choice < 1 || choice > 3)
            cout << "Enter valid value again : ";
    } while (choice < 1 || choice > 3);
    cout << "Number of sticks in game : ";
    cin >> N;
    switch (choice)
    {
    case 1:
        humanVShuman(N);
        break;
    case 2:
        humanVSai(N);
        break;
    case 3:
        aiVSai(N);
        break;
    default:
        break;
    }
    return 0;
}

void humanVShuman(int N)
{
    cout << "\nChoosing first turn .... :\n";
    int pick, loser, winner = toss();
    if (winner == 1)
    {
        cout << "Player 1 won the toss!\n";
        loser = 2;
    }
    else
    {
        cout << "Player 2 won the toss!\n";
        loser = 1;
    }
    cout << "**Rule : Pick atleast 1 stick and atmost 3 sticks**\n";
    while (1)
    {
        cout << "\n";
        cout << "Player " << winner << " , choose no. of sticks to pick : ";
        do
        {
            cin >> pick;
            if (pick < 1 || pick > 3)
                cout << "Enter valid value again : ";
        } while (pick <= N && (pick < 1 || pick > 3));
        N -= pick;
        if (!N)
        {
            cout << "\nPlayer " << loser << " Wins!!\n";
            cout << "Player " << winner << " Lose!!\n";
            break;
        }
        cout << "--Remaining Sticks : " << N << "--\n";
        cout << "Player " << loser << " , choose no. of sticks to pick : ";
        do
        {
            cin >> pick;
            if (pick < 1 && pick > 3)
                cout << "Enter valid value again.\n";
        } while (pick <= N && (pick < 1 && pick > 3));
        N -= pick;
        if (!N)
        {
            cout << "\nPlayer " << winner << " Wins!!\n";
            cout << "Player " << loser << " Lose!!\n";
            break;
        }
        cout << "--Remaining Sticks : " << N << "--\n";
    }
    cout << "Thanks for playing !!\n";
}

unique_ptr<int[]> minMax(int N, int player, int alpha, int beta)
{
    auto temp = make_unique<int[]>(4);
    if (N == 1 && player == 1)
    {
        temp[0] = 1;
        temp[1] = 1;
        temp[2] = -1;
        temp[3] = beta;
        return temp;
    }
    else if (N == 1 && player == 2)
    {
        temp[0] = 1;
        temp[1] = 2;
        temp[2] = alpha;
        temp[3] = 1;
        return temp;
    }
    else
    {
        int i; //sticks
        for (int j = 1; j <= 3; j++)
        {
            i = 4 - j;
            if (N > i)
            {
                if (player == 1)
                {
                    auto arr = minMax(N - i, 2, alpha, beta);
                    if (arr[2] < arr[3])
                        alpha = arr[3];
                    if (alpha == 1 || alpha > beta)
                        break;
                }
                else
                {
                    auto arr = minMax(N - i, 1, alpha, beta);
                    if (arr[2] < arr[3])
                        beta = arr[2];
                    if (beta == -1 || alpha > beta)
                        break;
                }
            }
        }
        temp[0] = i;
        temp[1] = player;
        temp[2] = alpha;
        temp[3] = beta;
        return temp;
    }
}

void humanVSai(int N)
{
    cout << "\nChoosing first turn .... :\n";
    int pick, winner = toss();
    if (winner == 1)
    {
        cout << "AI won the toss!\n";
    }
    else
    {
        cout << "You won the toss!\n";
    }
    cout << "**Rule : Pick atleast 1 stick and atmost 3 sticks**\n";
    while (1)
    {
        if (winner == 1)
        {
            auto arr = minMax(N, 1, INT_MIN, INT_MAX);
            cout << "AI picks: " << arr[0] << " sticks.\n";
            N -= arr[0];
            if (N == 0)
            {
                cout << "\nYou Won the game.\nAI Lost the game.\n";
                break;
            }
            cout << "--Remaining Sticks : " << N << "--\n";
            cout << "Choose no. of sticks to pick you want to pick : ";
            do
            {
                cin >> pick;
                if (pick < 1 || pick > 3)
                    cout << "Enter valid value again : ";
            } while (pick <= N && (pick < 1 || pick > 3));
            N -= pick;
            if (N == 0)
            {
                cout << "\nYou lost the game.\nAI won the game.\n";
                break;
            }
            cout << "--Remaining Sticks : " << N << "--\n";
        }
        else
        {
            cout << "Choose no. of sticks to pick you want to pick : ";
            do
            {
                cin >> pick;
                if (pick < 1 || pick > 3)
                    cout << "Enter valid value again : ";
            } while (pick <= N && (pick < 1 || pick > 3));
            N -= pick;
            if (N == 0)
            {
                cout << "\nYou lost the game.\nAI won the game.\n";
                break;
            }
            cout << "--Remaining Sticks : " << N << "--\n";
            auto arr = minMax(N, 1, INT_MIN, INT_MAX);
            cout << "AI picks: " << arr[0] << " sticks.\n";
            N -= arr[0];
            if (N == 0)
            {
                cout << "\nYou Won the game.\nAI Lost the game.\n";
                break;
            }
            cout << "--Remaining Sticks : " << N << "--\n";
        }
    }
}

void aiVSai(int N)
{
    cout << "\nChoosing first turn .... :\n";
    int pick, loser, winner = toss();
    if (winner == 1)
    {
        cout << "AI 1 won the toss!\n";
        loser = 2;
    }
    else
    {
        cout << "AI 2 won the toss!\n";
        loser = 1;
    }
    while (1)
    {
        auto arr = minMax(N, 1, INT_MIN, INT_MAX);
        cout << "AI " << winner << " picks: " << arr[0] << " sticks.\n";
        N -= arr[0];
        if (N == 0)
        {
            cout << "\nAI " << loser << " Won the game.\nAI " << winner << " Lost the game.\n";
            break;
        }
        cout << "--Remaining Sticks : " << N << "--\n";
        arr = minMax(N, 1, INT_MIN, INT_MAX);
        cout << "AI " << loser << " picks: " << arr[0] << " sticks.\n";
        N -= arr[0];
        if (N == 0)
        {
            cout << "\nAI " << loser << " Won the game.\nAI " << winner << " Lost the game.\n";
            break;
        }
        cout << "--Remaining Sticks : " << N << "--\n";
    }
}