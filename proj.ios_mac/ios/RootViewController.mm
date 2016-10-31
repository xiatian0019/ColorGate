/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"
#include "GameSetting.h"

@implementation RootViewController
@synthesize adInstl;
@synthesize video;
@synthesize sourceArray;

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
    [AdViewController deleteController];
}









#pragma mark -加载插屏广告
- (void)loadAdInstl
{
    [self.adInstl loadAdInstlView:self];
}
#pragma mark -展现插屏广告
- (void)showAdInstl
{
    if (self.adInstl.isReady) {
        [self.adInstl showAdInstlView:self];
        int addTime=cocos2d::UserDefault::getInstance()->getIntegerForKey("AddTime", -1);
        cocos2d::UserDefault::getInstance()->setIntegerForKey("AddTime", addTime+1);
        cocos2d::UserDefault::getInstance()->flush();
    }
    else{
        [self loadAdInstl];
        CCLOG("没有加载好~~~~");
    }
    
}

#pragma mark - InstlDelegate

- (void)adInstlManager:(AdInstlManager*)manager didGetEvent:(InstlEventType)eType error:(NSError*)error
{
    switch (eType) {
        case InstlEventType_StartLoadAd:
            CCLOG("InstlEventType_StartLoadAd");
            break;
        case InstlEventType_DidLoadAd:
            CCLOG("InstlEventType_DidLoadAd");
            break;
        case InstlEventType_FailLoadAd:
            CCLOG("InstlEventType_FailLoadAd");
            break;
        case InstlEventType_WillPresentAd:
            CCLOG("InstlEventType_WillPresentAd");
            //开始播放
            break;
        case InstlEventType_DidDismissAd:
            CCLOG("InstlEventType_DidDismissAd");
            //广告回来~~~
            [self loadAdInstl];
            break;
        case InstlEventType_WillPresentModal:
            CCLOG("InstlEventType_WillPresentModal");
            break;
        case InstlEventType_DidDismissModal:
            CCLOG("InstlEventType_DidDismissModal");
            break;
        default:
            break;
    }
}

- (BOOL)adInstlTestMode {
    return NO;
}

- (BOOL)adInstlLogMode {
    return YES;
}

#pragma mark -创建视频广告
- (void)createVideo
{
    self.video = [AdViewVideo playVideoWithAppId:AD_KEY controller:self videoType:ADVideoTypeInstl delegate:self];
}
#pragma mark -VideoDelegate
//视频广告开始播放
- (void)AdViewVideoPlayStarted
{
    
}
//视频广告结束播放
- (void)AdViewVideoPlayEnded
{
    
}
//关闭正在播放的视频
- (void)AdViewVideoClosedWithState:(BOOL)isPlayEnded
{
    
}



#pragma mark -创建贴片广告
- (void)AdPreMovie
{
    self.video = [AdViewVideo playVideoWithAppId:AD_KEY controller:self videoType:ADVideoTypePreMovie delegate:self];
    
}

#pragma mark - ProMoiveDelegate    开发者可根据回调的视频数据将视频广告呈现在自己封装的视频中。
- (void)AdViewVideoDidReceiveData:(NSArray *)videoSource withClickUrl:(NSString *)cUrl reportClickArr:(NSArray *)clickReportArr reportShowArr:(NSArray *)showReportArr {
    [self playVideoWithSourceArr:videoSource];
    //    clickUrl = cUrl;
}

- (void)AdViewVideoFailReceiveDataWithError:(NSError *)error {
    NSString *errorInfo = @"请检查网络是否通畅";
    if (error.code == -1)
        errorInfo = @"没有可播放的广告";
    
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"失败信息" message:errorInfo delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
    [alertView show];
}


#pragma mark - notifation
- (void)removeView {
    if ([[NSDate date] timeIntervalSince1970] - beforPlay < mp.duration) {
        nowPlay = (int)[self.sourceArray count];
    }
    [mp.view removeFromSuperview];
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [self playVideoWithSourceArr:self.sourceArray];
}

- (void)playVideoWithSourceArr:(NSArray*)sourceArr {
    if ([sourceArr count] == nowPlay) {
        self.sourceArray = nil;
        nowPlay = 0;
        return;
    }
    if (nil == self.sourceArray) {
        self.sourceArray = sourceArr;
        nowPlay = 0;
    }
    
    mp = [[MPMoviePlayerController alloc] init];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(removeView) name:MPMoviePlayerPlaybackDidFinishNotification object:nil];
    [mp.view setFrame:self.view.bounds];
    mp.controlStyle = MPMovieControlStyleFullscreen;
    NSString *urlStr = [sourceArr objectAtIndex:nowPlay];
    mp.contentURL = [NSURL URLWithString:urlStr];
    mp.shouldAutoplay = YES;
    [mp prepareToPlay];
    [self.view addSubview:mp.view];
    [mp play];
    beforPlay = [[NSDate date] timeIntervalSince1970];
    nowPlay++;
}

#pragma mark -视频广告必须添加 否则在播放视频结束后，切换到游戏场景出现 OpenGL error 0x0506 in -[CCEAGLView swapBuffers] 324错误
-(void) viewDidAppear:(BOOL)animated{
    
    cocos2d::Director::getInstance()->resume();
    cocos2d::Director::getInstance()->startAnimation();
}

- (void)viewWillDisappear:(BOOL)animated{
    
    cocos2d::Director::getInstance()->pause();
    cocos2d::Director::getInstance()->stopAnimation();
}



#pragma  mark -Banner
- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.view.backgroundColor = [UIColor clearColor];
    [self setUpView:nil];
}

-(void)setUpView:(id)sender{
    return;
    
    AdViewController *controller = [AdViewController sharedController];
    //
    [controller setAdViewKey:AD_KEY];
    //是否为测试模式和日志是否开启
    [controller setModeTest:NO Log:YES];
    //设置广告展现方向
    [controller setOrientationUp:NO Down:NO Left:YES Right:YES];
    //设置广告尺寸
    [controller setAdBannerSize:AdviewBannerSize_Auto];
    [controller setAdRootController:self];
    //设置广告位置
    
    [controller setAdPosition:CGPointMake(568/2-240, 255)];
    controller.bSuperOrientFix = YES;
    [controller loadView];
    [self.view addSubview:controller.adView];
    
    
}

-(void)setBannerHide:(BOOL)hided
{
    return;
    [[AdViewController sharedController]setAdHidden:hided];
}

#pragma mark -BannerDelegate
-(void)didGotNotify:(NSString *)code Info:(NSString *)content{
}




@end
