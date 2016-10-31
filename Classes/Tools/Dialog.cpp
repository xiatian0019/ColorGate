//
//  Dialog.cpp
//  MiniGameHor
//
//  Created by xiaoming on 16/6/28.
//
//

#include "Dialog.hpp"
#include "GameSetting.h"

static Dialog * dialog = NULL;

Dialog* Dialog::getInstance()
{
    if(dialog==NULL){
        dialog = new Dialog();
    }
    return dialog;
}
Dialog::Dialog()
{
    auto language = Application::getInstance()->getCurrentLanguage();
    isChinese = language == LanguageType::CHINESE;
    dataListCH.push_back("Memory Challenge");
    dataListCH.push_back("开始游戏");
    dataListCH.push_back("游戏帮助");
    dataListCH.push_back("关于我们");
    dataListCH.push_back("得分");
    dataListCH.push_back("游戏结束");
    dataListCH.push_back("点击屏幕开始游戏！");
    dataListCH.push_back("根据提示点击正确的圆！");
    dataListCH.push_back("每次选择正确，都会有时间奖励！");
    dataListCH.push_back("选择错误或时间到，游戏结束！");
    dataListCH.push_back("请点击任意一个圆。");
    dataListCH.push_back("请点击与上一关点击颜色相同的圆。");
    dataListCH.push_back("请点击与上一关");
    dataListCH.push_back("颜色相同的圆");
    dataListCH.push_back("最左侧");
    dataListCH.push_back("中间");
    dataListCH.push_back("最右侧");
    dataListCH.push_back("我们的其他游戏：");
    dataListCH.push_back("一款结合了数学、音乐、道具等多种元素的贪食蛇小游戏，在Apple Store中搜索看看吧~");

    dataListEN.push_back("Memory Challenge");
    dataListEN.push_back("START");
    dataListEN.push_back("HELP");
    dataListEN.push_back("HOME");
    dataListEN.push_back("SCORE");
    dataListEN.push_back("GAME OVER");
    dataListEN.push_back("Press Screen To Start!");
    dataListEN.push_back("According to the prompt,please choose the right one.");
    dataListEN.push_back("Every time you click right, there will be an extra time bonus!");
    dataListEN.push_back("Click the wrong one or times up,then game over!");
    dataListEN.push_back("Please click one of the circles.");
    dataListEN.push_back("Please click which color is same as the one you chose in last stage.");
    dataListEN.push_back("Please click which color is same as");
    dataListEN.push_back("one in last stage.");
    dataListEN.push_back("left");
    dataListEN.push_back("middle");
    dataListEN.push_back("right");
    dataListEN.push_back("Our other game:");
    dataListEN.push_back("A game with math,music and snake,you can get it in Apple Store.");

}
Dialog::~Dialog()
{
    
}



std::string Dialog::getStringByID(int txtId)
{
    std::vector<std::string>dataList=dataListEN;
    if (isChinese) {
        dataList=dataListCH;
    }
    if (txtId>=dataList.size()) {
        return "";
    }
    return dataList.at(txtId);
}

bool Dialog::getIsChinese()
{
    return isChinese;
}