#pragma once
#include <iostream>
using namespace std;
enum enChoices
{
    Rock = 1,
    Paper = 2,
    Scissors = 3
};
enum enWinner
{
    Player1 = 1,
    Player2 = 2,
    Draw = 3
};
struct stRoundInfo
{
    enChoices Player1Choice;
    enChoices Player2Choice;
    enWinner RoundResult;
    short RoundNumber;
};
struct stGameInfo
{
    short Player1WinTimes = 0;
    short Player2WinTimes = 0;
    short DrawTimes = 0;
    short RoundsTimes = 0;
    enWinner GameWinner;
};
short AskToPlay()
{
    short n;
    do
    {
        cout << "From 1 to 10, How many times do you want to play? ";
        cin >> n;
    } while (n < 1 || n > 10);
    return n;
}
enChoices RandomChoice()
{
    return (enChoices(rand() % (3 - 1 + 1) + 1));
}
enChoices AskForChoices(short Round)
{
    short n;
    do
    {
        cout << "\nYour choice [" << Round << "]\n[1]Rock, [2]Paper, [3] Scissors. ? ";
        cin >> n;

    } while (n < 1 || n > 3);
    return (enChoices)n;
}
string ChoiceToString(enChoices Choice)
{
    switch (Choice)
    {
    case enChoices::Rock:
        return "Rock";
        break;
    case enChoices::Paper:
        return "Paper";
        break;
    case enChoices::Scissors:
        return "Scissors";
        break;
    }
    return "";
}
string ResultToString(enWinner Result)
{
    switch (Result)
    {
    case enWinner::Player1:
        return "[Player1]";
        break;
    case enWinner::Player2:
        return "[Player2]";
        break;
    case enWinner::Draw:
        return "[No Winner]";
        break;
    }
    return "";
}
enWinner WhosWin(enChoices Player1Choice, enChoices Player2Choices)
{
    switch (Player1Choice)
    {
    case enChoices::Rock:
        if (Player2Choices == enChoices::Paper)
            return enWinner::Player2;
        else if (Player2Choices == enChoices::Scissors)
            return enWinner::Player1;
        break;
    case enChoices::Paper:
        if (Player2Choices == enChoices::Rock)
            return enWinner::Player1;
        else if (Player2Choices == enChoices::Scissors)
            return enWinner::Player2;
        break;
    case enChoices::Scissors:
        if (Player2Choices == enChoices::Rock)
            return enWinner::Player2;
        else if (Player2Choices == enChoices::Paper)
            return enWinner::Player1;
        break;
    }
    return enWinner::Draw;
}
stRoundInfo RoundPlay(short Round)
{
    stRoundInfo RoundInfo;
    RoundInfo.Player1Choice = AskForChoices(Round);
    RoundInfo.Player2Choice = RandomChoice();
    RoundInfo.RoundResult = WhosWin(RoundInfo.Player1Choice, RoundInfo.Player2Choice);
    RoundInfo.RoundNumber = Round;
    return RoundInfo;
}
void ColorScreen(enWinner RoundInfo)
{
    switch (RoundInfo)
    {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Player2:
        system("color 4F");
        break;
    case enWinner::Draw:
        system("color 6F");
        break;
    }
    return;
}
void PrintRoundResult(stRoundInfo RoundInfo)
{
    ColorScreen(RoundInfo.RoundResult);
    cout << "__________________________Round [" << RoundInfo.RoundNumber << "]__________________________" << endl;
    cout << "Player 1 Choice    : " << ChoiceToString(RoundInfo.Player1Choice) << endl;
    cout << "Player 2 Choice    : " << ChoiceToString(RoundInfo.Player2Choice) << endl;
    cout << "Round Winner       : " << ResultToString(RoundInfo.RoundResult) << endl;
    cout << "_________________________________________________________" << endl;
    return;
}
stGameInfo PlayGame()
{
    stGameInfo GameInfo;
    stRoundInfo RoundInfo;

    short Rounds = AskToPlay();
    GameInfo.RoundsTimes = Rounds;

    for (short i = 1; i <= Rounds; i++)
    {
        RoundInfo = RoundPlay(i);
        if (RoundInfo.RoundResult == enWinner::Player1)
            GameInfo.Player1WinTimes++;
        else if (RoundInfo.RoundResult == enWinner::Player2)
            GameInfo.Player2WinTimes++;
        else
            GameInfo.DrawTimes++;
        PrintRoundResult(RoundInfo);
    }

    if (GameInfo.Player1WinTimes > GameInfo.Player2WinTimes)
        GameInfo.GameWinner = enWinner::Player1;
    else if (GameInfo.Player2WinTimes > GameInfo.Player1WinTimes)
        GameInfo.GameWinner = enWinner::Player2;
    else
        GameInfo.GameWinner = enWinner::Draw;

    return GameInfo;
}
void EndGame(stGameInfo GameInfo)
{
    ColorScreen(GameInfo.GameWinner);
    cout << "\n\n---------------------------------------------------------" << endl;
    cout << "==========----------(((( [GAME OVER] ))))----------==========" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "_________________________Game Result_________________________" << endl;
    cout << "Game Rounds            : " << GameInfo.RoundsTimes << endl;
    cout << "Player 1 won times     : " << GameInfo.Player1WinTimes << endl;
    cout << "Player 2 won times     : " << GameInfo.Player2WinTimes << endl;
    cout << "Draw times             : " << GameInfo.DrawTimes << endl;
    cout << "Final Winner           : " << ResultToString(GameInfo.GameWinner) << endl;
}
void StartGame()
{
    char g = 'y';
    do
    {
        system("cls");
        system("color 0F");
        EndGame(PlayGame());
        cout << "Do You Want To Play Again ? (y,n)>";
        cin >> g;
    } while (tolower(g) == 'y');
}
