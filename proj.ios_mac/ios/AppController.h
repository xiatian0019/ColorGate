#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>
@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,GKGameCenterControllerDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;


//gameCente
- (void)authenticateLocalUser;
- (void)showGameCenter;
-(void)reportTopScore :(int) score;




- (void) retrieveTopXScores:(int)number;
-(void)showGradePanel;


@end

