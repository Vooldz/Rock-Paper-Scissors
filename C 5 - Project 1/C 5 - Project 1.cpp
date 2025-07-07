#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

enum enGameChoice { Rock = 1, Paper = 2, Scissor = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumberFromTo(int From, int To)
{

    return rand() % (To - From + 1) + From;

}

string Tabs(short NumberOfTabs)
{
    string tabs = "";

    for (int i = 1; i <= NumberOfTabs; i++)
    {
        tabs = tabs + "\t";
    }

    return tabs;
}

short ReadHowManyRounds()
{
    short GameRounds = 1;

    do
    {
        cout << "How Many Rounds Do You Want To Play 1 To 10?\n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;

}

enGameChoice ReadPlayer1Choice()
{

    short Choice;

    do
    {
        cout << "\nYour Choice : [1] : Rock, [2] : Paper, [3] : Scissors? ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;

}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumberFromTo(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    
    if (RoundInfo.ComputerChoice == RoundInfo.Player1Choice)
        return enWinner::Draw;

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Rock:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissor:
        if (RoundInfo.ComputerChoice == enGameChoice::Rock)
        {
            return enWinner::Computer;
        }
        break;
    }

    return enWinner::Player1;

}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner" };
    return arrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
    string arrChoiceName[3] = { "Rock","Paper","Scissors" };
    return arrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
        case enWinner::Computer:
            cout << "\a";
            system("color 4F");
        break;

        case enWinner::Player1:
            system("color 2F");
        break;

        case enWinner::Draw:
            system("color 6F");
        break;
    }
    
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    SetWinnerScreenColor(RoundInfo.Winner);
    cout << "\n____________Round [" << RoundInfo.RoundNumber << "]____________\n\n";
    cout << "Player1 Choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "__________________________________\n" << endl;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults FillGameResults(short HowManyRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = HowManyRounds;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.Player1WinTimes = PlayerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;

}

stGameResults PlayGame(short HowManyRounds)
{

    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {

        RoundInfo.RoundNumber    = GameRound;
        RoundInfo.Player1Choice  = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner         = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName     = WinnerName(RoundInfo.Winner);

        //Increase win/Draw counters
        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;
        
        PrintRoundResult(RoundInfo);
        
    }

    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);

}

void ResetScreen()
{
    system("color 0F");
    system("cls");
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(4) << "+++ G a m e O v e r +++ \n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "_____________________ [Game Results] _____________________\n\n";
    cout << Tabs(2) << "Game Rounds        :         " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________\n";

    SetWinnerScreenColor(GameResults.GameWinner);

}

void StartGame()
{
    char PlayAgain = 'y';
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do You Want To Play Again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;

}