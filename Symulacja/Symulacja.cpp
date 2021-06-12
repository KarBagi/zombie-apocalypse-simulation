﻿#include <iostream>
#include <time.h>
#include <fstream>
#include <chrono>
#include <thread>
#include "Map.h"
#include "MainClass.h"

using namespace std;

int main()
{
    srand((unsigned int)time(NULL));

    int AmmountCivilians = 0, AmmountSoldiers = 0;
    int AmmountWeakZombies = 0, AmmountStrongZombie = 0;
    int z = 1;

    fstream plik;
    plik.open("dane.txt", ios::out);

    cout << "Enter the number of civilians (1 - 200): ";
    while (!(cin >> AmmountCivilians && AmmountCivilians <= 200 && AmmountCivilians >= 0)) {
        cin.clear();
        cin.ignore(50, '\n');
        cout << "Incorrect number of Civilians. ";
    }

    cout << "Enter the number of soldiers (1 - 200): ";
    while (!(cin >> AmmountSoldiers && AmmountSoldiers <= 200 && AmmountSoldiers >= 0)) {
        cin.clear();
        cin.ignore(50, '\n');
        cout << "Incorrect number of soldiers. ";
    }

    cout << "Enter the number of weak zombies (1 - 200): ";
    while (!(cin >> AmmountWeakZombies && AmmountWeakZombies <= 200 && AmmountWeakZombies >= 0)) {
        cin.clear();
        cin.ignore(50, '\n');
        cout << "Incorrect number of weak zombies. ";
    }

    cout << "Enter the number of strong zombies (1 - 200): ";
    while (!(cin >> AmmountStrongZombie && AmmountStrongZombie <= 200 && AmmountStrongZombie >= 0)) {
        cin.clear();
        cin.ignore(50, '\n');
        cout << "Incorrect number of strong zombies. ";
    }

    int AmmountFood = 0;
    if (AmmountCivilians + AmmountSoldiers >= 30) { AmmountFood = 20; }
    else { AmmountFood = 10; }
    int AmmmountWeapons = 10;

    plik << "Initial value for each class" << endl;
    plik << "Civilians: " << AmmountCivilians << endl;
    plik << "Soldiers: " << AmmountSoldiers << endl;
    plik << "Weak Zombies: " << AmmountWeakZombies << endl;
    plik << "Strong Zombies: " << AmmountStrongZombie << endl;
    plik << "Food: " << AmmountFood << endl << endl;
    plik.close();

    int EndCivilians = 0;
    int EndSoldier = 0;
    int EndWeakZombie = 0;
    int EndStrongZombie = 0;
    int CurrentlyFood = 0;

    Map m1;
    int** AdditivesMap = m1.getArrayAdditivesMap();
    int** board = m1.getBoard();

    Civilians* Civil = new Civilians[AmmountCivilians];
    for (int i = 0; i < AmmountCivilians; i++)
    {
        Civil[i] = Civilians(1, 1, AmmountCivilians);
    }

    Soldiers* Soldier = new Soldiers[AmmountSoldiers];
    for (int o = 0; o < AmmountSoldiers; o++)
    {
        Soldier[o] = Soldiers(1, 1, AmmountSoldiers);
    }

    WeakZombies* WeakZombie = new WeakZombies[AmmountWeakZombies];
    for (int p = 0; p < AmmountWeakZombies; p++)
    {
        WeakZombie[p] = WeakZombies(1, 1, AmmountWeakZombies);
    }

    StrongZombies* StrongZombie = new StrongZombies[AmmountStrongZombie];
    for (int k = 0; k < AmmountStrongZombie; k++)
    {
        StrongZombie[k] = StrongZombies(1, 1, AmmountStrongZombie);
    }

    Food* food = new Food[AmmountFood];
    for (int q = 0; q < AmmountFood; q++)
    {
        food[q] = Food(1, AmmountFood);
    }

    Weapons* Weapon = new Weapons[AmmmountWeapons];
    for (int v = 0; v < AmmmountWeapons; v++)
    {
        Weapon[v] = Weapons(1, AmmmountWeapons);
    }

    for (int pks = 0; pks < AmmountCivilians; pks++) { Civil[pks].ArrangeSpecimens(board); }
    for (int pks = 0; pks < AmmountSoldiers; pks++) { Soldier[pks].ArrangeSpecimens(board); }
    for (int pks = 0; pks < AmmountWeakZombies; pks++) { WeakZombie[pks].ArrangeSpecimens(board); }
    for (int pks = 0; pks < AmmountStrongZombie; pks++) { StrongZombie[pks].ArrangeSpecimens(board); }
    for (int i = 0; i < AmmountFood; i++) { food[i].ArrangeAdditives(board, AdditivesMap); }
    for (int i = 0; i < AmmmountWeapons; i++) { Weapon[i].ArrangeAdditives(board, AdditivesMap); }

    system("cls");

    while (true) {
        m1.Reducing(EndCivilians, EndSoldier, EndWeakZombie, EndStrongZombie, CurrentlyFood);
        for (int dnf = 0; dnf < AmmountCivilians; dnf++) {
            Civil[dnf].Dying(board, AdditivesMap);
            Civil[dnf].Movement(board);
            Civil[dnf].Fight(board);
            Civil[dnf].CollectingFood(AdditivesMap);
            Civil[dnf].CollectingWepons(AdditivesMap);
            Civil[dnf].Starving();
            Civil[dnf].Multiplication(Civil, board, AmmountCivilians, EndCivilians);
        }

        for (int pks = 0; pks < AmmountSoldiers; pks++) {
            Soldier[pks].Dying(board, AdditivesMap);
            Soldier[pks].Movement(board);
            Soldier[pks].Fight(board);
            Soldier[pks].CollectingFood(AdditivesMap);
            Soldier[pks].CollectingWepons(AdditivesMap);
            Soldier[pks].Starving();
            Soldier[pks].Multiplication(Soldier, board, AmmountSoldiers, EndSoldier);
        }

        for (int rks = 0; rks < AmmountWeakZombies; rks++) {
            WeakZombie[rks].Dying(board);
            WeakZombie[rks].Movement(board);
            WeakZombie[rks].Fight(Soldier, Civil, board, AmmountCivilians, AmmountSoldiers);
        }

        for (int dns = 0; dns < AmmountStrongZombie; dns++) {
            StrongZombie[dns].Dying(board);
            StrongZombie[dns].Movement(board);
            StrongZombie[dns].Fight(Soldier, Civil, board, AmmountCivilians, AmmountSoldiers);
        }

        m1.count(EndCivilians, EndSoldier, EndWeakZombie, EndStrongZombie, CurrentlyFood);
        food->ArrangeAdditives(board, AdditivesMap);
        m1.CreateMap(EndCivilians, EndSoldier, EndWeakZombie, EndStrongZombie);

        this_thread::sleep_for(500ms);
        system("cls");

        plik.open("dane.txt", ios::out | ios::app);
        plik << "Ammount of specimens in " << z++ << " round" << endl;
        plik << "Civilians: " << EndCivilians << endl;
        plik << "Soldiers: " << EndSoldier << endl;
        plik << "Weak Zombies: " << EndWeakZombie << endl;
        plik << "Strong Zombies: " << EndStrongZombie << endl;
        plik << "Ammount of food on the map: " << CurrentlyFood << endl << endl;

        if ((EndSoldier + EndCivilians) <= 0) { cout << "Zombies won."; break; }
        if ((EndWeakZombie + EndStrongZombie) <= 0) { cout << "People won."; break; }

        plik.close();
    }
    return 0;
}