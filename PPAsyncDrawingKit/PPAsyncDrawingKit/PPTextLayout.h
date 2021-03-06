//
//  PPTextLayout.h
//  PPAsyncDrawingKit
//
//  Created by DSKcpp on 2016/10/14.
//  Copyright © 2016年 DSKcpp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <PPAsyncDrawingKit/PPTextLayoutFrame.h>
#import <PPAsyncDrawingKit/PPTextRenderer.h>

NS_ASSUME_NONNULL_BEGIN

/**
 有关 Text 的属性都有这个类负责
 */
@interface PPTextLayout : NSObject
@property (nonatomic, assign) NSUInteger numberOfLines;
@property (nullable, nonatomic, strong) NSArray<UIBezierPath *> *exclusionPaths;

@property (nonatomic, assign) CGSize maxSize;
@property (nonatomic, assign) CGPoint origin;
@property (nonatomic, assign) CGRect frame;

@property (nullable, nonatomic, copy, readonly) NSString *plainText;
@property (nullable, nonatomic, copy) NSAttributedString *attributedString;
@property (nullable, nonatomic, strong) NSAttributedString *truncationString;

@property (nonatomic, strong, readonly) PPTextLayoutFrame *layoutFrame;
@property (nonatomic, strong, readonly) PPTextRenderer *textRenderer;

- (instancetype)initWithAttributedString:(NSAttributedString *)attributedString;
- (void)setNeedsLayout;
@end

@interface PPTextLayout (PPTextLayoutCoordinates)
- (CGRect)convertRectToCoreText:(CGRect)rect;
- (CGRect)convertRectFromCoreText:(CGRect)rect;
- (CGPoint)convertPointToCoreText:(CGPoint)point;
- (CGPoint)convertPointFromCoreText:(CGPoint)point;
@end

@interface PPTextLayout (PPTextLayoutResult)
@property (nonatomic, assign, readonly) CGFloat layoutHeight;
@property (nonatomic, assign, readonly) CGSize layoutSize;
@property (nonatomic, assign, readonly) NSUInteger containingLineCount;

- (void)enumerateEnclosingRectsForCharacterRange:(NSRange)range usingBlock:(void (^)(CGRect rect, BOOL *stop))block;
- (void)enumerateLineFragmentsForCharacterRange:(NSRange)range usingBlock:(void(^)(CGRect rect, NSRange range, BOOL *stop))block;
@end

NS_ASSUME_NONNULL_END
