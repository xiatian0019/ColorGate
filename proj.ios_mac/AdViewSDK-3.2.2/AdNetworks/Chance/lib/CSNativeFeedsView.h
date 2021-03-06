//
//  CSNativeFeedsView.h
//  ChanceAdSDK
//
//  Created by CocoaChina_yangjh on 16/4/7.
//  Copyright © 2016年 CocoaChina. All rights reserved.
//

#import <UIKit/UIKit.h>

@class CSNativeFeedsItem;

@interface CSNativeFeedsView : UIView

@property (nonatomic, readonly) CSNativeFeedsItem *nativeFeedsItem;

@property (nonatomic, readonly) UIImageView *imageViewIcon;
@property (nonatomic, readonly) UILabel *labelTitle;
@property (nonatomic, readonly) UILabel *labelContent;
@property (nonatomic, readonly) NSArray<UIImageView *> *imageViews;
// 二次确认
@property (nonatomic, readonly) UILabel *labelConfirm;
@property (nonatomic, readonly) UIButton *buttonConfirm;
@property (nonatomic, readonly) UIButton *buttonCancel;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithFrame:(CGRect)frame NS_UNAVAILABLE;
- (instancetype)initWithFrame:(CGRect)frame andNativeFeedsItem:(CSNativeFeedsItem *)item;

- (void)showAD;

@end
