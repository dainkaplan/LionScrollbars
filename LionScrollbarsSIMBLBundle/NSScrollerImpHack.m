//
//  NSScrollerImp+HackingAdditions.m
//  LionScrollbarsSIMBLBundle
//
//  Created by Dain Kaplan on 1/24/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import "NSScrollerImpHack.h"
#import "Hacking.h"
#import "LSBPlugin.h"
#import "HackedOverlayScroller.h"
#import "HackedLegacyScroller.h"
#import <objc/objc-class.h>

@interface NSObject (Apple_Private_API)
+ (Class)scrollerImpClassForStyle:(long long)arg1 controlSize:(unsigned long long)arg2;
- (id) scroller;
- (void)setOverlayScrollerKnobAlpha:(CGFloat)alpha;
- (void)setOverlayScrollerTrackAlpha:(CGFloat)alpha;
@end

@implementation NSScrollerImpHack 

+ (void) lsb_initialize
{
	static BOOL __inited = NO;
	if (__inited) {
		return;
	}
	__inited = YES;
	LSBPlugin *plugin = [LSBPlugin sharedInstance];
	Hacking_ShouldLogStatus(plugin.logLevel > 0);
	Hacking_SwapClassMethods([self class], objc_getMetaClass("NSScrollerImp"), 
					 @selector(__scrollerImpClassForStyle:controlSize:), @selector(scrollerImpClassForStyle:controlSize:));
}

+ (void) lsb_initializeOverylayHack
{
	static BOOL __inited = NO;
	if (__inited) {
		return;
	}
	__inited = YES;
	LSBPlugin *plugin = [LSBPlugin sharedInstance];
	Hacking_ShouldLogStatus(plugin.logLevel > 0);
	Hacking_SwapMethods(self, NSClassFromString(@"NSOverlayScrollerImp"), 
				@selector(_overlay_drawKnobWithAlpha:), @selector(drawKnobWithAlpha:));
}

+ (void) lsb_initializeLegacyHack 
{
	static BOOL __inited = NO;
	if (__inited) {
		return;
	}
	__inited = YES;	
	LSBPlugin *plugin = [LSBPlugin sharedInstance];
	Hacking_ShouldLogStatus(plugin.logLevel > 0);
	Hacking_SwapMethods(self, NSClassFromString(@"NSLegacyScrollerImp"), 
				@selector(_legacy_drawKnobSlotInRect:highlight:alpha:), @selector(drawKnobSlotInRect:highlight:alpha:));
}

// drawKnobSlotInRect:highlight:alpha:
- (void)_legacy_drawKnobSlotInRect:(struct CGRect)arg1 highlight:(BOOL)arg2 alpha:(double)arg3
{
	NSScroller *scroller = [self scroller];
	Class cls = [HackedLegacyScroller class];
	if (![scroller isMemberOfClass: cls]) {
		LSBPlugin *plugin = [LSBPlugin sharedInstance];
		if (plugin.aggressiveScrollerHacking || [scroller isMemberOfClass:[NSScroller class]]) {
			if (plugin.logLevel > 0) NSLog(@"LSB: scrollbar: %@", [scroller className]);
			object_setClass(scroller, cls);
		}
	}
	[self _legacy_drawKnobSlotInRect:arg1 highlight:arg2 alpha:arg3];
}

- (void)_overlay_drawKnobWithAlpha:(double)arg1
{
	NSScroller *scroller = [self scroller];
	Class cls = [HackedOverlayScroller class];
	if (![scroller isMemberOfClass: cls]) {
		LSBPlugin *plugin = [LSBPlugin sharedInstance];
		if (plugin.aggressiveScrollerHacking || [scroller isMemberOfClass:[NSScroller class]]) {
			if (plugin.logLevel > 0) NSLog(@"LSB: scrollbar: %@", [scroller className]);
			object_setClass(scroller, cls);
			[scroller setOverlayScrollerKnobAlpha:-1];
			[scroller setOverlayScrollerTrackAlpha:-1];
		}
	}
	[self _overlay_drawKnobWithAlpha:arg1];
}

// XXX(dkaplan): This was where I wanted to hook into the scrollbar 
//     system, but plugins loaded with SIMBL aren't loaded fast enough 
//     for this hook to work (scrollbars exist before the plugin loads).
// __scrollerImpClassForStyle:controlSize:
+ (Class)__scrollerImpClassForStyle:(long long)arg1 controlSize:(unsigned long long)arg2
{
	NSScroller *scroller = [self scroller];
	LSBPlugin *plugin = [LSBPlugin sharedInstance];
	if (plugin.logLevel > 2) NSLog(@"LSB: __scrollerImpClassForStyle:controlSize: %@", [scroller className]);
	return [self __scrollerImpClassForStyle:arg1 controlSize:arg2];
}



//Hacking_SwapMethods(self, NSClassFromString(@"NSLegacyScrollerImp"), @selector(_legacy_drawKnob), @selector(drawKnob));
- (void)_legacy_drawKnob{
	NSScroller *scroller = [self scroller];
	LSBPlugin *plugin = [LSBPlugin sharedInstance];
	if (plugin.logLevel > 2) NSLog(@"LSB: _legacy_drawKnob: %@", [scroller className]);
	[self _legacy_drawKnob];
}


// Hacking_SwapMethods(self, NSClassFromString(@"NSLegacyScrollerImp"), @selector(_legacy_drawKnobWithAlpha:), @selector(drawKnobWithAlpha:));
- (void)_legacy_drawKnobWithAlpha:(double)arg1
{
	NSScroller *scroller = [self scroller];
	LSBPlugin *plugin = [LSBPlugin sharedInstance];
	if (plugin.logLevel > 2) NSLog(@"LSB: _legacy_drawKnobWithAlpha: %@", [scroller className]);
	[self _legacy_drawKnobWithAlpha:arg1];
}

@end
