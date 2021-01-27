#include <iostream>
#include <chrono>
#include <bitset>
#include <list>
#include <iomanip>
#include <cstdlib>
#include <numeric>

#include "FileHandler.h"
#include "SW.h"

using namespace std;

//----------------------MAIN-------------------------
vector< vector<int> > matrix;

int main(int argc, char *argv[])
{
    Timer timer;
    auto *pFileHandler = new FileHandler();
    SW *pSW = nullptr;

    bool running = true;
    char choice;
    string filename;
    int stop=10;
    double cool_rate = 1.2;//musi byc wiekszy od 1, im blizej 1 tym dluzej trwa algorytm i tym dokladniejszy bedzie wynik
    double err, errs[3][10];
    int ans_correct[3] = {1776, 2755, 2465};
    int ans_curr;
    int best_answers[3], answers[3][10];
    double avg_answers[3];
    //turbo read
    while(running)
    {
        cout <<"\n--- MENU GLOWNE ---\n";
        cout <<"1.Wczytanie danych z pliku\n"
               "2.zmien maksymalny czas wykonywania[s]\n"
               "3.zmien wsp. zmiany temperatury(dla czasow 90s+ zalecany 1.2 (Cauchy))\n"
               "4.SW-all (2h)\n"
               "5.SW-single\n"
               "0.Wyjscie\n";
        cout <<"--- MENU GLOWNE ---\n";
        cout << "User choice:";
        cin >> choice;
        switch(choice)
        {
            case '1':
                cout << "Podaj nazwe pliku(uzupelnic pole X: X.atsp): ";
                cin >> filename;
                filename.insert(0, "tsp/");
                filename.append(".atsp");
                matrix = pFileHandler->read_from_file(filename.c_str());
                break;

            case '2':
                cout <<"obecnie: " << stop <<"[s], podaj nowe [s], (0,inf): " <<endl;
                if(stop>0)
                    cin >> stop;
                else
                    cout <<"podaj poprawna wartosc";
                break;

            case '3':
                cout << "obecnie: " << cool_rate << ", podaj nowy wspolczynnik zmiany temperatury (0,1): (s): " << endl;

                cin >> cool_rate;
                break;

            case '4':
                for (int i = 0; i < 3; ++i)
                {
                    if (i==0)
                    {
                        matrix = pFileHandler->read_from_file("tsp/ftv47.atsp");
                        cout << "||ftv47:";
                        stop = 120;
                    } else if (i==1)
                    {
                        matrix = pFileHandler->read_from_file("tsp/ftv170.atsp");
                        cout << "||ftv170:";
                        stop = 240;
                    } else if (i==2)
                    {
                        matrix = pFileHandler->read_from_file("tsp/rbg403.atsp");
                        cout << "||rbg403:";
                        stop = 360;
                    }
                    for (int j = 0; j < 10; j++)
                    {
                        pSW = new SW(matrix, stop, cool_rate);

                        timer.start();
                        pSW->find_best_path();
                        timer.stop();

                        ans_curr = pSW->cost(pSW->path_best);
                        answers[i][j] = ans_curr;
                        err = (double) abs(ans_curr - ans_correct[i]) *100/ ans_correct[i];
                        errs[i][j] = err;
                        if (best_answers[i] > ans_curr)
                            best_answers[i] = ans_curr;

                        cout << "\n------------" << i << ","<< j << "------------\n";
                        cout << "WYNIK ALGORYTMU: "
                             << ans_curr
                             << " WYNIK OCZEKIWANY: " << ans_correct[i] << "\t";
                        cout << "BLAD WZGL.: " << err <<"%"
                             << "\nCZAS WYKRYCIA: " << pSW->time_found / 1000000000.0 << "[s]\n";
                        cout <<"CZAS CALKOWIY: ";
                        timer.info();
                        cout << "SCIEZKA: \n";
                        pSW->print_best_path();
                        cout << "---------------------------\n";
//                        break;
                    }
                }
                //
                fill(avg_answers, avg_answers+10, 0);
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 10; ++j)
                        avg_answers[i] += answers[i][j];

                    avg_answers[i] /= 10.0;
                }
                cout << "\n------------POSUMOWANIE------------\n";
                cout << "ftv47 :: SREDNIA WYNIKOW: "<<avg_answers[0]<< ", OCZEKIWANO: "<<ans_correct[0]<< "\n";
                cout << "ftv170 :: SREDNIA WYNIKOW: "<<avg_answers[1]<<", OCZEKIWANO: "<<ans_correct[1]<< "\n";
                cout << "rbg403 :: SREDNIA WYNIKOW: "<<avg_answers[2]<< ", OCZEKIWANO: "<<ans_correct[2]<<"\n";
                cout << "------------POSUMOWANIE------------\n";
                break;

            case '5':
                pSW = new SW(matrix, stop, cool_rate);
                timer.start();
                pSW->find_best_path();
                timer.stop();

                ans_curr = pSW->cost(pSW->path_best);
                cout << "---------------------------\n";
                cout << "WYNIK ALGORYTMU: "
                     << ans_curr<< "\t"
            <<"\nCZAS WYKRYCIA: " << pSW->time_found / 1000000000.0 << "[s]\n";
                cout <<"CZAS CALKOWIY: ";
                timer.info();
                cout << "SCIEZKA: \n";
                pSW->print_best_path();
                cout << "---------------------------\n";
                break;

            case '0':
                running = false;
                break;

            default: break;
        }//switch choice
    }//while running

    //free memory
    delete pSW;
    delete pFileHandler;
    pSW = nullptr;
    pFileHandler = nullptr;

    system("pause");
    return 0;
}
