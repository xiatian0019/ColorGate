//
//  GameTools.cpp
//  MagicSnake
//
//  Created by xiaoming on 15/12/9.
//
//

#include "GameTools.hpp"


int GameTools::getRandomNum(int min,int max)
{
    if (min>=max) {
        return min;
    }
    unsigned long num=arc4random()%10000;
    int randomPoint=((int)num)%(max-min+1)+min;
    return randomPoint;
}

std::string GameTools::enCodeData(int value)
{
    std::string strData = Value(value*7).asString();
    return strData;
}
int GameTools::deCodeData(std::string value)
{
    int intData = atoi(value.c_str())/7;
    return intData;
}

void GameTools::changeToScene(Scene *scene,SceneAnime anime)
{
    TransitionScene * reScene=NULL;
    float animeTime=1;
    switch (anime) {
        case TRAN_FADE:
            reScene = TransitionFade::create(animeTime, scene);
            break;
        case TRAN_SHRINK:
            reScene = TransitionShrinkGrow::create(animeTime, scene);
            break;
        case TRAN_WHITE:
            reScene = TransitionCrossFade::create(animeTime, scene);
            break;
        default:
            reScene = TransitionRotoZoom::create(animeTime, scene);
            break;
    }
    Director::getInstance()->replaceScene(reScene);
}

int GameTools::getCurrentTime()
{
    struct timeval nowTimeval;
    gettimeofday(&nowTimeval, NULL);
    struct tm * tm;
    time_t time_sec ;
    time_sec = nowTimeval.tv_sec;
    tm = localtime(&time_sec);
    int currentTime=(tm->tm_year-116)*365+tm->tm_yday;
    return currentTime;
}

std::string GameTools::getFinalName(std::string nameData,int length)
{
    std::string lines;
    std::string textStr=nameData;
    int wordNum=0;
    int len =(int)textStr.length();
    for (;wordNum<length; wordNum++) {
        for(int cur = (int)lines.size(); cur < len;){
            char t = textStr[cur];
            if((t&0xE0) == 0xE0){    //3byte
                lines = lines + t + textStr[cur+1] + textStr[cur+2];
                cur += 3;
            }else if((t & 0xC0) == 0xC0){//2byte
                lines = lines + t + textStr[cur+1];
                cur += 2;
            }else { //1byte
                lines = lines + t;
                cur += 1;
            }
            break;
        }
    }
    if (lines.length()<len) {
        lines=lines + "..";
    }
    return lines.c_str();
}

std::string GameTools::getStringByLength(std::string stringData,int length)
{
    std::string lines;
    std::string textStr=stringData;
    int len =(int)textStr.length();
    for (int cur=(int)lines.size();(cur<len&&cur<length);) {
        char t = textStr[cur];
        if((t&0xE0) == 0xE0){    //3byte
            lines = lines + t + textStr[cur+1] + textStr[cur+2];
            cur += 3;
        }else if((t & 0xC0) == 0xC0){//2byte
            lines = lines + t + textStr[cur+1];
            cur += 2;
        }else { //1byte
            lines = lines + t;
            cur += 1;
        }
    }
    if (lines.length()<len) {
        lines=lines + "..";
    }
    return lines;
}


int GameTools::getUserAge()
{
    int currentTime=GameTools::getCurrentTime();
    int birthDay=UserDefault::getInstance()->getIntegerForKey("BirthDay", -1);
    if (birthDay==-1||birthDay>currentTime) {
        birthDay=currentTime;
        UserDefault::getInstance()->setIntegerForKey("BirthDay", birthDay);
    }
    UserDefault::getInstance()->flush();
    return currentTime-birthDay;
}

bool GameTools::checkIsBirthDay()
{
    struct timeval nowTimeval;
    gettimeofday(&nowTimeval, NULL);
    struct tm * tm;
    time_t time_sec ;
    time_sec = nowTimeval.tv_sec;
    tm = localtime(&time_sec);
    return (tm->tm_mon==4&&tm->tm_mday==29);
}

