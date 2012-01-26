//
//  HackedScroller.h
//  ScrollbarInject
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface HackedLegacyScroller : NSScroller

+ (BOOL) overlaysScrollView;
+ (BOOL) roundedCorners;
+ (BOOL) drawsKnobTrack;
- (BOOL) isVertical;
+ (BOOL) useGradient;
+ (void) setUseGradient:(BOOL)enable;
+ (void) setDrawBackground:(BOOL)enable;

// Overriding

+ (CGFloat) scrollerWidth;
- (void) drawRect:(NSRect)rect;
- (void)drawKnob;

@end
