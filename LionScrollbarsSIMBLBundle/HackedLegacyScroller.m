//
//  HackedScroller.m
//  ScrollbarInject
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import "HackedLegacyScroller.h"

@interface NSScroller (Apple_Private_API)
- (void) setOverlayScrollerKnobAlpha:(CGFloat)alpha;
- (void) setOverlayScrollerTrackAlpha:(CGFloat)alpha;
@end

@implementation HackedLegacyScroller

static BOOL __useGradient = YES;
static BOOL __drawBackground = YES;
static BOOL __roundedCorners = YES;

+ (BOOL) overlaysScrollView 
{
	return NO;
}

+ (void) setRoundedCorners:(BOOL)enable
{
	__roundedCorners = enable;
}

+ (BOOL) useGradient 
{
    return __useGradient;
}

+ (void) setUseGradient:(BOOL)enable
{
	__useGradient = enable;
}

+ (BOOL) roundedCorners
{
    return __roundedCorners;
}

+ (BOOL) isCompatibleWithOverlayScrollers 
{
	return NO;
}

+ (BOOL) drawsKnobTrack 
{
    return __drawBackground;
}

+ (void) setDrawBackground:(BOOL)enable
{
	__drawBackground = enable;
}

+ (CGFloat) scrollerWidth
{
    return [super scrollerWidth] - 2;
}

+ (CGFloat) scrollerWidthForControlSize:(NSControlSize)controlSize
{
	switch (controlSize) {
		case NSRegularControlSize:
			return [super scrollerWidthForControlSize:controlSize] - 2;
			break;
		case NSSmallControlSize:
			return [super scrollerWidthForControlSize:controlSize] - 2;
			break;
		case NSMiniControlSize:
			return [super scrollerWidthForControlSize:controlSize] - 2;
			break;
	}
    return [[self class] scrollerWidth];
}

- (CGFloat)_scrollerWidth
{
	return [[self class] scrollerWidthForControlSize:[self controlSize]];
}

- (BOOL) isVertical
{
	BOOL isVertical;
    if ([self bounds].size.width < [self bounds].size.height) {
		isVertical = YES;
    } else {
		isVertical = NO;
    }
	return isVertical;
}

- (void) drawBackground:(NSRect) rect
{
	[[NSColor colorWithCalibratedRed:0.3 green:0.3 blue:0.3 alpha:1.0] set];
	CGFloat curve = [[self class] roundedCorners] ? [self _scrollerWidth]/2 : 0;
	NSBezierPath *path = [NSBezierPath bezierPathWithRoundedRect:
						  ([self isVertical] ? CGRectInset(rect, 1, 2) : CGRectInset(rect, 2, 1))
						  xRadius:curve
						  yRadius:curve];
	NSColor *color = [NSColor colorWithCalibratedRed:1 green:1 blue:1 alpha:1.0];
	NSColor *color3 = [NSColor colorWithCalibratedRed:0.8 green:0.8 blue:0.8 alpha:1.0];
	NSGradient *gradient = [[NSGradient alloc] initWithColors:[NSArray arrayWithObjects: color3, color, nil]];
	[gradient drawInBezierPath:path angle:[self isVertical] ? 0 : 90];
	[gradient release];
	[[NSColor colorWithCalibratedRed:0.8 green:0.8 blue:0.8 alpha:1.0] set];
	[path setLineWidth:1];
	[path stroke];
}

- (void)setOverlayScrollerKnobAlpha:(CGFloat)alpha 
{
	[super setOverlayScrollerKnobAlpha: 1];
}


- (void)setOverlayScrollerTrackAlpha:(CGFloat)alpha 
{
	[super setOverlayScrollerTrackAlpha: 1];
}

- (void) drawRect:(NSRect)rect
{	
	// XXX(dkaplan): Drawing the background here doesn't result in the desired behavior. Sometimes drawKnob is called on window resize (without calling drawRect) which doesn't do what we want.
	//if ([[self class] drawsKnobTrack]) {
	//	[self drawBackground:[self bounds]];
	//}
	[self drawKnob];
}

- (void) drawKnob
{
	BOOL isVertical = [self isVertical];
	if ([[self class] drawsKnobTrack]) {
		NSRect trackRect1 = [self bounds];
		NSRect trackRect2 = [self frame];
		if (isVertical) {
			if (trackRect2.size.height > trackRect1.size.height)
				trackRect1 = trackRect2;
		} else {
			if (trackRect2.size.width > trackRect1.size.width)
				trackRect1 = trackRect2;
		}
		[self drawBackground:trackRect1];
	}
    NSRect rect = [self rectForPart:NSScrollerKnob];
    if (isVertical) {
        rect.size.width = [self _scrollerWidth];
		rect.origin.x = 1;
    } else {
        rect.size.height = [self _scrollerWidth];
        rect.origin.y = 1;
    }

	CGFloat cornerRadius = [[self class] roundedCorners] ? [self _scrollerWidth]/2 : 0;
	NSBezierPath *path = [NSBezierPath bezierPathWithRoundedRect: 
			(isVertical ? CGRectInset(rect, 0, 1) : CGRectInset(rect, 1, 0))
			xRadius: cornerRadius
			yRadius: cornerRadius];
	if ([[self class] useGradient]) {
		NSColor *color = [NSColor colorWithCalibratedRed:0.8 green:0.8 blue:0.8 alpha:1.0];
		NSColor *color2 = [NSColor colorWithCalibratedRed:0.6 green:0.6 blue:0.6 alpha:1.0];
		NSGradient *gradient = [[NSGradient alloc] initWithColors: [NSArray arrayWithObjects: color, color2, nil]];
		[gradient drawInBezierPath:path angle:isVertical ? 0 : 90];
		[gradient release];
	} else {
		[[NSColor lightGrayColor] setFill];
		[path fill];
	}
	[[NSColor colorWithCalibratedRed:0.5 green:0.5 blue:0.5 alpha:1.0] set];
	[path setLineWidth:1];
	[path stroke];
}

- (void)setHackedScrollerSettings:(HackedScrollerSettings)settings
{
	// TODO
}

@end
