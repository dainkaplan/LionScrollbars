//
//  HackedScroller.h
//  ScrollbarInject
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface HackedOverlayScroller : NSScroller

+ (CGFloat) minKnobAlpha;
+ (CGFloat) minTrackAlpha;
+ (BOOL) overlaysScrollView;
+ (void) setMinKnobAlpha:(CGFloat)alpha;
+ (void) setMinTrackAlpha:(CGFloat)alpha;
+ (void) takeoverInstance:(NSScroller *)scroller;

@end
