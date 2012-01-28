//
//  HackedScroller.m
//  ScrollbarInject
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain Kaplan <DK@tempura.org>. All rights reserved.
//

#import "HackedOverlayScroller.h"
#import <objc/objc-class.h>

// To stop compiler warnings about the private API calls
@interface NSScroller (PrivateAPI)
- (void) setOverlayScrollerKnobAlpha:(CGFloat)alpha;
- (void) setOverlayScrollerTrackAlpha:(CGFloat)alpha;
@end

@implementation HackedOverlayScroller

static CGFloat __minKnobAlpha = 0.8;
static CGFloat __minTrackAlpha = 0.0;

+ (BOOL) overlaysScrollView
{
	return YES;
}

+ (BOOL) isCompatibleWithOverlayScrollers 
{
	return YES;
}

+ (void) takeoverInstance:(NSScroller *)scroller 
{
	Class cls = [HackedOverlayScroller class];
	if (![scroller isMemberOfClass: cls]) {
		NSLog(@"scrollbar: %@", [scroller className]);
		object_setClass(scroller, cls);
		[scroller setOverlayScrollerKnobAlpha:-1];
		[scroller setOverlayScrollerTrackAlpha:-1];
	}
}

- (void) setOverlayScrollerKnobAlpha:(CGFloat)alpha 
{
	const CGFloat min = [HackedOverlayScroller minKnobAlpha];
	[super setOverlayScrollerKnobAlpha: MAX(alpha, min)];
}


- (void) setOverlayScrollerTrackAlpha:(CGFloat)alpha 
{
	const CGFloat min = [HackedOverlayScroller minTrackAlpha];
	[super setOverlayScrollerTrackAlpha: MAX(alpha, min)];
}

#pragma mark Custom methods

+ (CGFloat) minKnobAlpha
{
	return __minKnobAlpha;
}

+ (CGFloat) minTrackAlpha 
{
	return __minTrackAlpha;
}

+ (void) setMinKnobAlpha:(CGFloat)alpha
{
	__minKnobAlpha = MAX(0, MIN(1, alpha));
}

+ (void) setMinTrackAlpha:(CGFloat)alpha
{
	__minTrackAlpha = MAX(0, MIN(1, alpha));
}

- (void)setHackedScrollerSettings:(HackedScrollerSettings)settings
{
	// TODO
}

@end
