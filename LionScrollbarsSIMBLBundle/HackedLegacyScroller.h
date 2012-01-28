//
//  HackedScroller.h
//  ScrollbarInject
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import <AppKit/AppKit.h>
#import "HackedScrollersUserDefaults.h"

@interface HackedLegacyScroller : NSScroller <HackedScrollerUserDefaults>

+ (BOOL) overlaysScrollView;
+ (BOOL) roundedCorners;
+ (BOOL) drawsKnobTrack;
- (BOOL) isVertical;
+ (BOOL) useGradient;
+ (void) setUseGradient:(BOOL)enable;
+ (void) setDrawBackground:(BOOL)enable;
+ (void) setRoundedCorners:(BOOL)enable;

// Overriding

+ (CGFloat) scrollerWidth;
- (void) drawRect:(NSRect)rect;
- (void)drawKnob;

- (void)setHackedScrollerSettings:(HackedScrollerSettings)settings;

@end
