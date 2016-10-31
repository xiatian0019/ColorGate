//
//  GameCenter.cpp
//  ColorGate
//
//  Created by xiaoming on 16/6/20.
//
//

#include "GameCenter.hpp"
#import "AppController.h"
static int lastScore=0;

void GameCenter::login()
{
    AppController *appController= (AppController *)[UIApplication sharedApplication].delegate;
    [appController authenticateLocalUser];
}
void GameCenter::showRank()
{
    AppController *appController= (AppController *)[UIApplication sharedApplication].delegate;
    [appController showGameCenter];
}
void GameCenter::uploadScore(int newScore)
{
    if (lastScore>=newScore) {
        return;
    }
    lastScore=newScore;
    AppController *appController= (AppController *)[UIApplication sharedApplication].delegate;
    [appController reportTopScore:lastScore];
}