//
//  GameSetting.h
//  MiniGameHor
//
//  Created by xiaoming on 16/6/23.
//
//

#ifndef GameSetting_h
#define GameSetting_h


#define WIDTH    Director::getInstance()->getWinSize().width
#define HEIGHT   Director::getInstance()->getWinSize().height

#define AD_KEY                     @"SDK2016112011062985rewxfifnclgxc"
#define GAME_CENTER_KEY            @"xiaohuiPJ.Remember.rank"

#define EVALUATE_DAY         3
#define EVALUATE_OPEN        10
#define GRADE_REFUSE_NUM        5


#define GATE_WIDTH              (WIDTH/2)/3.5
#define GATE_HEIGHT             GATE_WIDTH/0.618

#define GATE_CIRCLE_SIZE        200

#define PRESS_MAX_DIF       10
#define STATE_TIME          200
#define ERROR_TIME          500


#define AD_MAX_PERDAY          7

enum GATE_COLOR
{
    RED,
    YELLOW,
    BLUE,
    ANY,
};

enum GATE_POS
{
    LEFT,
    CENTER,
    RIGHT,
    NONE,
};


#define FONT_VERDANA              "Verdana-Bold"
#define FONT_HELVETICA_BOLD       "Helvetica-Bold"
#define FONT_GEORGIA              "Georgia-Bold"
#define FONT_HELVETICA            "Helvetica"


#define BATTLE_BGM            "Higher-7obu.mp3"
#define MAIN_BGM               "none.mp3"

#define GAME_TIME   3000



#endif /* GameSetting_h */
