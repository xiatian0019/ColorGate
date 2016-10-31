//
//  BattleScene.hpp
//  ColorGate
//
//  Created by xiaoming on 16/4/28.
//
//

#ifndef BattleScene_hpp
#define BattleScene_hpp

#include <stdio.h>
#include "GateGroup.hpp"
#include "StageTip.hpp"
#include "GameOverPanel.hpp"

class BattleScene : public Layer , public GateGroupDelegate
{
public:
    static Scene* createScene();
    bool init();
    CREATE_FUNC(BattleScene);
private:
    void gateCorrect(GATE_COLOR newColor,int lastPos);
    void gateWrong();
    void gatePress(GATE_COLOR gateColor,Vec2 point);
    GateGroup *myGateGroup;
    GATE_COLOR currentColor;
    GATE_POS currentPos;
    void updateGateGroup();
    Label *labelScore;
    int myScore;
    void resetGame();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    bool gameRunning;
    StageTip *gameRunningTips;
    Label *gameOverTips;
    Label *gameTimeLabel;
    void updateLabels();
    void removeGateGroup();
    int gameTime;
    void secondFrame(float dt);
    void gameOver();
    void aniTimeAddAnime();
    void addSnow();
    
    void backClick(Ref *ref);
    
    
    Sprite *hourglass;
    void hourGlassAnimeRun();
    void hourGlassAnimeStop();
    void resetHourglass();
    
    GameOverPanel *gameOverPanel;
    void addGameOverPanel(int score);
    ParticleSystem* particleSystem;
    void onExit();
    void addAd(float dt);
};


#endif /* BattleScene_hpp */
