//
//  NSScrollView+HackedAdditions.h
//  ScrollbarInject
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSScrollView (HackedAdditions)

- (void) lsb_tile;
+ (void) lsb_setMinKnobAlpha:(CGFloat)alpha;
+ (void) lsb_setMinTrackAlpha:(CGFloat)alpha;
+ (void) lsb_initialize;
+ (void) lsb_takeoverScrollers:(NSScrollView *)view;
+ (Class) lsb__horizontalScrollerClass;
+ (Class) lsb__verticalScrollerClass;

@end
