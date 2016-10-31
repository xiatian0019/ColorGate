//
//  Dialog.hpp
//  MiniGameHor
//
//  Created by xiaoming on 16/6/28.
//
//

#ifndef Dialog_hpp
#define Dialog_hpp

//DialogId
#define TXT_MAIN_TITLE   0
#define TXT_MAIN_START   1
#define TXT_MAIN_HELP    2
#define TXT_MAIN_ABOUT   3
#define TXT_BATTLE_SCORE 4
#define TXT_BATTLE_GAMEOVER    5
#define TXT_BATTLE_START_TIPS  6

#define TXT_HELP_1   7
#define TXT_HELP_2   8
#define TXT_HELP_3   9


#define TXT_TIPS_ANY   10
#define TXT_TIPS_LAST  11

#define TXT_STAGE_TIPS_START   12
#define TXT_STAGE_TIPS_END     13
#define TXT_STAGE_TIPS_LEFT    14
#define TXT_STAGE_TIPS_MIDDLE  15
#define TXT_STAGE_TIPS_RIGHT   16
#define TXT_MORE_GAME          17
#define TXT_MORE_GAME_DESC     18









#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Dialog : public Ref
{
public:
    static Dialog* getInstance();
    Dialog();
    ~Dialog();
    std::string getStringByID(int txtId);
    bool getIsChinese();
private:
    bool isChinese;
    std::vector<std::string>dataListCH;
    std::vector<std::string>dataListEN;
};

#endif /* Dialog_hpp */
