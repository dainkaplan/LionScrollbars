@protocol NSScrollerImpDelegate
- (struct CGRect)convertRectToBacking:(struct CGRect)arg1;
- (struct CGRect)convertRectFromBacking:(struct CGRect)arg1;
- (id)layer;
- (void)scrollerImp:(id)arg1 animateKnobAlphaTo:(double)arg2 duration:(double)arg3;
- (void)scrollerImp:(id)arg1 animateTrackAlphaTo:(double)arg2 duration:(double)arg3;
- (void)scrollerImp:(id)arg1 overlayScrollerStateChangedTo:(unsigned long long)arg2;

@optional
- (struct CGRect)convertRectToLayer:(struct CGRect)arg1;
@end

@protocol NSScrollerImpPairDelegate
- (struct CGRect)contentAreaRectForScrollerImpPair:(id)arg1;
- (BOOL)inLiveResizeForScrollerImpPair:(id)arg1;
- (struct CGPoint)mouseLocationInContentAreaForScrollerImpPair:(id)arg1;
- (struct CGPoint)scrollerImpPair:(id)arg1 convertContentPoint:(struct CGPoint)arg2 toScrollerImp:(id)arg3;
- (void)scrollerImpPair:(id)arg1 setContentAreaNeedsDisplayInRect:(struct CGRect)arg2;
- (void)scrollerImpPair:(id)arg1 updateScrollerStyleForNewRecommendedScrollerStyle:(long long)arg2;
@end


@interface NSScroller : NSControl <NSScrollerImpDelegate>
{
    double _curValue;	// 13191520 = 0xc94960
    double _percent;	// 13191528 = 0xc94968
    double _knobSize;	// 13191912 = 0xc94ae8
    struct __sFlags2 {
        unsigned int hitPart:4;
        unsigned int controlSize:2;
        unsigned int inMaxEnd:1;
        unsigned int setFloatValueOverridden:1;
        unsigned int setFloatValueKnobProportionOverridden:1;
        unsigned int style:1;
        unsigned int styleCompatibility:1;
        unsigned int overlayScrollerState:2;
        unsigned int knobStyle:2;
        unsigned int sbPaused:1;
        unsigned int reserved:16;
    } _sFlags2;	// 13191496 = 0xc94948
    id _target;	// 13191504 = 0xc94950
    SEL _action;	// 13191512 = 0xc94958
    struct _sFlags {
        unsigned int isHoriz:1;
        unsigned int arrowsLoc:2;
        unsigned int partsUsable:2;
        unsigned int fine:1;
        unsigned int needsEnableFlush:1;
        unsigned int thumbing:1;
        unsigned int slotDrawn:1;
        unsigned int knobDrawn:1;
        unsigned int lit:1;
        unsigned int knobLit:1;
        unsigned int reserved:1;
        unsigned int controlTint:3;
        unsigned int repeatCount:16;
    } sFlags;	// 13191488 = 0xc94940
}

+ (BOOL)isCompatibleWithOverlayScrollers;
+ (void)_aquaScrollerBehaviorChanged:(id)arg1;
+ (void)_aquaScrollerVariantChanged:(id)arg1;
+ (double)scrollerWidthForControlSize:(unsigned long long)arg1 scrollerStyle:(long long)arg2;
+ (double)scrollerWidthForControlSize:(unsigned long long)arg1;
+ (double)scrollerWidth;
+ (void)initialize;
+ (long long)preferredScrollerStyle;
+ (int)_arrowsConfig;
+ (void)_setArrowsConfig:(int)arg1;
+ (void)_drawEndCapInRect:(struct CGRect)arg1;
+ (BOOL)scrollerSubclassIsCompatibleWithOverlayScrollers;
+ (void)_ensureAllOverlayScrollersInFrontOfSurface:(id)arg1;
+ (id)defaultAnimationForKey:(id)arg1;
+ (BOOL)accessibilityIsSingleCelled;
- (BOOL)_desiredLayerSizeMeritsTiledBackingLayer:(struct CGSize)arg1;
- (BOOL)_useTigerMetrics;
- (double)_repeatTime;
- (id)_setWindow:(id)arg1;
- (BOOL)_routeAroundScrollerStyleAccessors;
- (id)initWithFrame:(struct CGRect)arg1;
- (void)dealloc;
- (BOOL)isOpaque;
- (BOOL)isFlipped;
- (void)viewWillDraw;
- (long long)scrollerStyle;
- (void)_setSurfaceBacked:(BOOL)arg1;
- (void)_really_setLionScrollerStyle:(long long)arg1;
- (void)setScrollerStyle:(long long)arg1;
- (long long)knobStyle;
- (void)setKnobStyle:(long long)arg1;
- (void)drawParts;
- (struct CGRect)rectForPart:(unsigned long long)arg1;
- (void)checkSpaceForParts;
- (unsigned long long)usableParts;
- (id)target;
- (void)setTarget:(id)arg1;
- (SEL)action;
- (void)setAction:(SEL)arg1;
- (void)_adjustForGrowBox;
- (void)setFrameOrigin:(struct CGPoint)arg1;
- (void)setFrameSize:(struct CGSize)arg1;
- (void)setArrowsPosition:(unsigned long long)arg1;
- (unsigned long long)arrowsPosition;
- (void)setControlTint:(unsigned long long)arg1;
- (unsigned long long)controlTint;
- (void)setControlSize:(unsigned long long)arg1;
- (unsigned long long)controlSize;
- (unsigned long long)_realControlTint;
- (void)setEnabled:(BOOL)arg1;
- (struct __CFDictionary *)_copyCompositeCoreUIDrawOptions;
- (void)_old_drawArrow:(unsigned long long)arg1 highlightPart:(unsigned long long)arg2;
- (void)drawArrow:(unsigned long long)arg1 highlightPart:(unsigned long long)arg2;
- (void)drawArrow:(unsigned long long)arg1 highlight:(BOOL)arg2;
- (void)_old_drawKnob;
- (void)drawKnob;
- (void)_old_drawKnobSlotInRect:(struct CGRect)arg1 highlight:(BOOL)arg2;
- (void)drawKnobSlotInRect:(struct CGRect)arg1 highlight:(BOOL)arg2;
- (void)_compositeScrollerPart:(unsigned long long)arg1 inRect:(struct CGRect)arg2 withAlpha:(double)arg3 drawHandler:(id)arg4;
- (void)drawRect:(struct CGRect)arg1;
- (void)highlight:(BOOL)arg1;
- (unsigned long long)_testPartUsingDestinationFloatValue:(struct CGPoint)arg1;
- (unsigned long long)testPart:(struct CGPoint)arg1;
- (BOOL)sendAction:(SEL)arg1 to:(id)arg2;
- (void)_postScrollerDidEndTrackingNotification;
- (void)trackKnob:(id)arg1;
- (void)trackScrollButtons:(id)arg1;
- (void)trackPagingArea:(id)arg1;
- (BOOL)_windowResizeMouseLocationIsInVisibleScrollerThumb:(struct CGPoint)arg1;
- (id)hitTest:(struct CGPoint)arg1;
- (void)mouseDown:(id)arg1;
- (unsigned long long)hitPart;
- (float)floatValue;
- (double)doubleValue;
- (double)knobProportion;
- (void)setKnobProportion:(double)arg1;
- (void)setFloatValue:(float)arg1 knobProportion:(double)arg2;
- (void)setFloatValue:(float)arg1;
- (void)setDoubleValue:(double)arg1;
- (BOOL)acceptsFirstMouse:(id)arg1;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (void)setInterfaceStyle:(unsigned long long)arg1;
- (void)_windowChangedKeyState;
- (unsigned int)_CAViewFlags;
- (void)_automateLiveScroll;
- (id)scrollerImp;
- (unsigned long long)_overlayScrollerState;
- (double)overlayScrollerKnobAlpha;
- (double)overlayScrollerTrackAlpha;
- (void)_decrementLine:(id)arg1;
- (void)_incrementLine:(id)arg1;
- (void)_decrementPage:(id)arg1;
- (void)_incrementPage:(id)arg1;
- (void)_scrollByDelta:(double)arg1;
- (double)_thumbingDoubleValue;
- (void)_setThumbingDoubleValue:(double)arg1;
- (double)_thumbingKnobProportion;
- (void)_setThumbingKnobProportion:(double)arg1;
- (struct CGRect)_drawingRectForPart:(unsigned long long)arg1;
- (void)_setSuppressSurfaceBackingForAnimation:(BOOL)arg1;
- (long long)_lionScrollerStyle;
- (void)_setLionScrollerStyle:(long long)arg1;
- (void)_replaceScrollerImp;
- (BOOL)_fixScrollerImpForSwizzlers;
- (BOOL)_isTrackingInKnob;
- (void)_setTrackingInKnob:(BOOL)arg1;
- (void)setLayer:(id)arg1;
- (void)_updateScrollerSurfaceAlphaAndBackgroundBlurRadius;
- (void)_setSurface:(id)arg1;
- (void)setOverlayScrollerKnobAlpha:(double)arg1;
- (void)setOverlayScrollerTrackAlpha:(double)arg1;
- (void)resetCursorRects;
- (BOOL)_avoidingOtherScrollerThumb;
- (void)_setAvoidingOtherScrollerThumb:(BOOL)arg1;
- (BOOL)_shouldAvoidScrollerExclusionRect;
- (void)scrollerImp:(id)arg1 animateKnobAlphaTo:(double)arg2 duration:(double)arg3;
- (void)scrollerImp:(id)arg1 animateTrackAlphaTo:(double)arg2 duration:(double)arg3;
- (void)scrollerImp:(id)arg1 overlayScrollerStateChangedTo:(unsigned long long)arg2;
- (void)_setOverlayScrollerState:(unsigned long long)arg1 forceImmediately:(BOOL)arg2;
- (id)accessibilityAttributeNames;
- (id)accessibilityRoleAttribute;
- (id)accessibilityValueAttribute;
- (BOOL)accessibilityIsValueAttributeSettable;
- (void)accessibilitySetValueAttribute:(id)arg1;
- (id)accessibilityOrientationAttribute;
- (BOOL)accessibilityIsOrientationAttributeSettable;
- (id)_accessibilityScrollView;
- (id)accessibilityHiddenAttribute;
- (BOOL)accessibilityIsHiddenAttributeSettable;
- (void)accessibilitySetHiddenAttribute:(id)arg1;
- (unsigned long long *)_accessibilitySupportedPartCodes;
- (BOOL)_accessibilityIsSupportedPartCode:(unsigned long long)arg1;
- (id)_accessibilityUIElementForPartCode:(unsigned long long)arg1;
- (id)accessibilityChildrenAttribute;
- (BOOL)accessibilityIsChildrenAttributeSettable;
- (id)accessibilityHitTest:(struct CGPoint)arg1;
- (id)accessibilityHelpStringForChild:(id)arg1;
- (BOOL)accessibilityIsChildFocusable:(id)arg1;
- (id)accessibilityPositionOfChild:(id)arg1;
- (id)accessibilitySizeOfChild:(id)arg1;

@end


@interface _NSScrollerGaussianBlur : NSObject
{
    double radius;	// 13891776 = 0xd3f8c0
    NSBitmapImageRep *blurMaskBitmap;	// 13891784 = 0xd3f8c8
    CIFilter *clampFilter;	// 13895400 = 0xd406e8
    CIFilter *blurFilter;	// 13895408 = 0xd406f0
    CIFilter *blurMaskTileFilter;	// 13895416 = 0xd406f8
    CIFilter *blendWithMaskFilter;	// 13895424 = 0xd40700
    CIFilter *flipFilter;	// 13895432 = 0xd40708
}

- (id)init;
@property double radius;
@property(retain) NSBitmapImageRep *blurMaskBitmap;
- (void)blurRect:(struct CGRect)arg1 availableSourceRect:(struct CGRect)arg2 flippedDestination:(BOOL)arg3 intensity:(double)arg4;
- (void)dealloc;

@end


@interface _NSScrollerBlurMaskLayer : CALayer
{
}

- (id)init;
- (void)drawInContext:(struct CGContext *)arg1;

@end

@interface _NSScrollerPartLayer : CALayer
{
}

- (id)init;

@end

@interface NSSmallLegacyScrollerImp : NSLegacyScrollerImp
{
}

+ (double)scrollerWidth;
- (unsigned long long)controlSize;
- (double)trackWidth;
- (double)knobMinLength;
- (void)loadImages;

@end

@interface NSRegularLegacyScrollerImp : NSLegacyScrollerImp
{
}

+ (double)scrollerWidth;
- (unsigned long long)controlSize;
- (double)trackWidth;
- (double)knobMinLength;
- (void)loadImages;

@end

@interface NSLegacyScrollerImp : NSScrollerImp
{
}

- (long long)scrollerStyle;
- (void)setKnobAlpha:(double)arg1;
- (void)setTrackAlpha:(double)arg1;
- (double)trackSideInset;
- (double)knobEndInset;
- (struct __CFDictionary *)copyCoreUIOptions;
- (void)drawKnobSlotInRect:(struct CGRect)arg1 highlight:(BOOL)arg2 alpha:(double)arg3;
- (void)drawKnobWithAlpha:(double)arg1;

@end

@interface NSSmallOverlayScrollerImp : NSOverlayScrollerImp
{
}

+ (double)scrollerWidth;
- (unsigned long long)controlSize;
- (double)trackWidth;
- (double)trackEndInset;
- (double)trackSideInset;
- (double)knobMinLength;
- (double)knobOverlapEndInset;
- (double)trackOverlapEndInset;
- (void)loadImages;

@end

@interface NSRegularOverlayScrollerImp : NSOverlayScrollerImp
{
}

+ (double)scrollerWidth;
- (unsigned long long)controlSize;
- (double)trackWidth;
- (double)trackEndInset;
- (double)trackSideInset;
- (double)knobMinLength;
- (double)knobOverlapEndInset;
- (double)trackOverlapEndInset;
- (void)loadImages;

@end

@interface NSOverlayScrollerImp : NSScrollerImp
{
}

- (id)init;
- (long long)scrollerStyle;
- (struct __CFDictionary *)copyCoreUIOptions;
- (struct __CFDictionary *)copyCoreUIKnobOptions;
- (struct CGRect)rectForPart:(unsigned long long)arg1;
- (void)drawKnobSlotInRect:(struct CGRect)arg1 highlight:(BOOL)arg2 alpha:(double)arg3;
- (void)drawKnobWithAlpha:(double)arg1;

@end

@interface NSScrollerImp : NSObject
{
    NSScroller *scroller;	// 13891752 = 0xd3f8a8
    double doubleValue;	// 13891680 = 0xd3f860
    double knobProportion;	// 13891688 = 0xd3f868
    double knobLength;	// 13891768 = 0xd3f8b8
    struct CGSize boundsSize;	// 13891672 = 0xd3f858
    id <NSScrollerImpDelegate> delegate;	// 13891744 = 0xd3f8a0
    id target;	// 13891736 = 0xd3f898
    SEL action;	// 13891728 = 0xd3f890
    double trackAlpha;	// 13891696 = 0xd3f870
    double knobAlpha;	// 13891704 = 0xd3f878
    double rangeIndicatorAlpha;	// 13891760 = 0xd3f8b0
    _NSScrollerGaussianBlur *blur;	// 13894264 = 0xd40278
    struct _sImpFlags {
        unsigned int isHoriz:1;
        unsigned int arrowsLoc:2;
        unsigned int partsUsable:2;
        unsigned int fine:1;
        unsigned int needsEnableFlush:1;
        unsigned int thumbing:1;
        unsigned int slotDrawn:1;
        unsigned int knobDrawn:1;
        unsigned int lit:1;
        unsigned int knobLit:1;
        unsigned int reserved:1;
        unsigned int controlTint:3;
        unsigned int repeatCount:16;
    } sFlags;	// 13891720 = 0xd3f888
    struct __sImpFlags2 {
        unsigned int hitPart:4;
        unsigned int controlSize:2;
        unsigned int inMaxEnd:1;
        unsigned int setFloatValueOverridden:1;
        unsigned int setFloatValueKnobProportionOverridden:1;
        unsigned int style:1;
        unsigned int overlayScrollerState:2;
        unsigned int enabled:1;
        unsigned int avoidingOtherScrollerThumb:1;
        unsigned int tracking:1;
        unsigned int rangeIndicatorsShown:1;
        unsigned int knobStyle:2;
        unsigned int reserved:14;
    } _sFlags2;	// 13891712 = 0xd3f880
    CALayer *layer;	// 13891648 = 0xd3f840
    CALayer *trackLayer;	// 13891656 = 0xd3f848
    CALayer *knobLayer;	// 13891664 = 0xd3f850
    CAFilter *blurFilter;	// 13894272 = 0xd40280
}

+ (Class)scrollerImpClassForStyle:(long long)arg1 controlSize:(unsigned long long)arg2;
+ (id)scrollerImpWithStyle:(long long)arg1 controlSize:(unsigned long long)arg2 horizontal:(BOOL)arg3 replacingScrollerImp:(id)arg4;
+ (double)scrollerWidthForControlSize:(unsigned long long)arg1 scrollerStyle:(long long)arg2;
+ (double)scrollerWidth;
- (id)init;
- (void)dealloc;
- (void)_updateLayerGeometry;
- (void)_updateLayerBlur;
- (void)drawLayer:(id)arg1 inContext:(struct CGContext *)arg2;
@property(retain) CALayer *layer;
@property(retain) CALayer *trackLayer;
@property(retain) CALayer *knobLayer;
@property struct CGSize boundsSize;
@property double doubleValue;
@property double knobProportion;
@property double trackAlpha;
@property double knobAlpha;
@property(getter=isEnabled) BOOL enabled;
@property(getter=isHorizontal) BOOL horizontal;
@property BOOL avoidingOtherScrollerThumb;
@property(readonly) unsigned long long controlSize;
@property(readonly) long long scrollerStyle;
@property long long knobStyle;
- (BOOL)isTracking;
- (void)setTracking:(BOOL)arg1;
- (unsigned long long)overlayScrollerState;
- (void)setOverlayScrollerState:(unsigned long long)arg1 forceImmediately:(BOOL)arg2;
@property(readonly) double trackBoxWidth;
@property(readonly) double trackWidth;
@property(readonly) double trackSideInset;
@property(readonly) double trackEndInset;
@property(readonly) double knobEndInset;
@property(readonly) double knobMinLength;
@property(readonly) double knobOverlapEndInset;
@property(readonly) double trackOverlapEndInset;
- (void)checkSpaceForParts;
- (unsigned long long)usableParts;
- (struct CGRect)rectForPart:(unsigned long long)arg1;
- (BOOL)hitTestForLocalPoint:(struct CGPoint)arg1;
- (void)loadImages;
- (struct __CFDictionary *)copyCoreUIOptions;
- (struct __CFDictionary *)copyCoreUIKnobOptions;
- (struct __CFDictionary *)copyCoreUITrackOptions;
- (void)_blurBackgroundBehindScrollerBeforeDrawingInRect:(struct CGRect)arg1 intensity:(double)arg2;
- (void)_compositeScrollerPart:(unsigned long long)arg1 inRect:(struct CGRect)arg2 withAlpha:(double)arg3 drawHandler:(id)arg4;
- (void)drawKnobSlotInRect:(struct CGRect)arg1 highlight:(BOOL)arg2;
- (void)drawKnobSlotInRect:(struct CGRect)arg1 highlight:(BOOL)arg2 alpha:(double)arg3;
- (void)drawKnob;
- (void)drawKnobWithAlpha:(double)arg1;
@property SEL action; // @synthesize action;
@property id target; // @synthesize target;
@property id <NSScrollerImpDelegate> delegate; // @synthesize delegate;
@property NSScroller *scroller; // @synthesize scroller;
@property double rangeIndicatorAlpha; // @synthesize rangeIndicatorAlpha;
@property(readonly) double knobLength; // @synthesize knobLength;

@end


@interface _NSScrollerStyleRecommender : NSObject <NSMachPortDelegate>
{
    long long lastRecommendedScrollerStyle;	// 13903520 = 0xd426a0
    NSTimer *scrollerStyleRecommendationUpdateTimer;	// 13903536 = 0xd426b0
    struct IONotificationPort *iokitNotificationPort;	// 13903528 = 0xd426a8
    unsigned int iokitNotificationMachPort;	// 13903544 = 0xd426b8
    NSMachPort *iokitMachPort;	// 13903552 = 0xd426c0
    unsigned int servicePublishNotification;	// 13903560 = 0xd426c8
    unsigned int serviceTerminationNotification;	// 13903568 = 0xd426d0
}

+ (id)sharedScrollerStyleRecommender;
- (void)handleMachMessage:(void *)arg1;
- (BOOL)startListeningForPointingDeviceConnectAndDisconnect;
- (void)stopListeningForPointingDeviceConnectAndDisconnect;
- (void)startListeningForUserPreferenceNotifications;
- (void)stopListeningForUserPreferenceNotifications;
- (long long)recommendedScrollerStyle;
- (void)setRecommendedScrollerStyleAndNotify:(long long)arg1;
- (void)scrollerStyleRecommendationUpdateTimerFired:(id)arg1;
- (void)cancelScrollerStyleRecommendationUpdate;
- (void)scheduleScrollerStyleRecommendationUpdate:(double)arg1;
- (void)notePointingDeviceConnected;
- (void)notePointingDeviceDisconnected;
- (void)showScrollBarsSettingChanged:(id)arg1;
- (void)pointingDeviceGestureScrollSettingChanged:(id)arg1;
- (id)init;
- (void)dealloc;
- (void)finalize;

@end

@interface NSScrollerImpPair : NSObject
{
    NSScrollView *scrollView;	// 13904984 = 0xd42c58
    id <NSScrollerImpPairDelegate> delegate;	// 13905016 = 0xd42c78
    NSScrollerImp *verticalScrollerImp;	// 13905000 = 0xd42c68
    NSScrollerImp *horizontalScrollerImp;	// 13905008 = 0xd42c70
    long long scrollerStyle;	// 13904992 = 0xd42c60
    NSTimer *overlayScrollerHideTimer;	// 13906832 = 0xd43390
    double overlayScrollerHideStartTime;	// 13905024 = 0xd42c80
    struct {
        unsigned int isFlipped:1;
        unsigned int wantsToFlashOverlayScrollers:1;
        unsigned int windowIsVisible:1;
        unsigned int inScrollGesture:1;
        unsigned int scrollerKnobStyle:2;
        unsigned int scrollerFlashPending:1;
        unsigned int overlayScrollerStateLocked:1;
        unsigned int reserved:24;
    } flags;	// 13904976 = 0xd42c50
    CDStruct_9fab449c flags2;	// 13906840 = 0xd43398
    NSTrackingArea *contentViewTrackingArea;	// 13906848 = 0xd433a0
    id reserved2;	// 13906856 = 0xd433a8
    id reserved3;	// 13906864 = 0xd433b0
}

+ (void)initialize;
+ (void)_updateAllScrollerImpPairsForNewRecommendedScrollerStyle:(long long)arg1;
+ (void)_scrollerStyleRecommendationChanged:(id)arg1;
- (id)init;
@property(getter=isFlipped) BOOL flipped;
@property NSScrollView *scrollView;
@property long long scrollerStyle;
@property(retain) NSScrollerImp *verticalScrollerImp;
@property(retain) NSScrollerImp *horizontalScrollerImp;
@property long long scrollerKnobStyle;
- (void)_setOverlayScrollerState:(unsigned long long)arg1 forScrollerImp:(id)arg2 forceImmediately:(BOOL)arg3;
@property(readonly) BOOL overlayScrollersShown;
- (void)_beginHideOverlayScrollers;
- (void)_overlayScrollerHideTimerFired:(id)arg1;
- (void)_cancelOverlayScrollerHideTimer;
- (void)_rescheduleOverlayScrollerHideTimerWithDelay:(double)arg1;
- (void)_updateOverlayScrollersStateWithReason:(id)arg1 forceAtLeastKnobsVisible:(BOOL)arg2;
- (void)flashScrollers;
- (void)hideOverlayScrollers;
- (void)lockOverlayScrollerState:(unsigned long long)arg1;
- (void)unlockOverlayScrollerState;
- (BOOL)overlayScrollerStateIsLocked;
- (void)contentAreaScrolled;
- (void)contentAreaWillDraw;
- (void)contentAreaDidHide;
- (void)removedFromSuperview;
- (void)movedToNewWindow;
- (void)windowOrderedOut;
- (void)windowOrderedIn;
- (void)mouseEnteredContentArea;
- (void)mouseMovedInContentArea;
- (void)mouseExitedContentArea;
- (void)startLiveResize;
- (void)contentAreaDidResize;
- (void)endLiveResize;
- (void)endTrackingInScrollerImp:(id)arg1;
- (void)beginScrollGesture;
- (void)endScrollGesture;
@property(readonly) BOOL inScrollGesture; // @dynamic inScrollGesture;
- (void)mouseEntered:(id)arg1;
- (void)mouseMoved:(id)arg1;
- (void)mouseExited:(id)arg1;
- (void)updateTrackingAreas;
- (void)dealloc;
@property id <NSScrollerImpPairDelegate> delegate; // @synthesize delegate;

@end


@interface NSScrollView : NSView <NSScrollerImpPairDelegate, NSTextFinderBarContainer>
{
    NSScroller *_vScroller;	// 13658464 = 0xd06960
    NSScroller *_hScroller;	// 13658472 = 0xd06968
    NSClipView *_contentView;	// 13658480 = 0xd06970
    NSClipView *_headerClipView;	// 13658488 = 0xd06978
    NSView *_cornerView;	// 13658496 = 0xd06980
    id _ruler;	// 13658504 = 0xd06988
    struct __SFlags {
        unsigned int RESERVED:5;
        unsigned int findBarPosition:2;
        unsigned int predominantAxisScrolling:1;
        unsigned int hContentElasticity:2;
        unsigned int vContentElasticity:2;
        unsigned int unused:1;
        unsigned int findBarVisible:1;
        unsigned int autoforwardsScrollWheelEvents:1;
        unsigned int autohidesScrollers:1;
        unsigned int hasCustomLineBorderColor:1;
        unsigned int focusRingNeedsRedisplay:1;
        unsigned int skipRemoveSuperviewCheck:1;
        unsigned int doesNotDrawBackground:1;
        unsigned int needsTile:1;
        unsigned int hasVerticalRuler:1;
        unsigned int hasHorizontalRuler:1;
        unsigned int showRulers:1;
        unsigned int oldRulerInstalled:1;
        unsigned int borderType:2;
        unsigned int noDynamicScrolling:1;
        unsigned int hScrollerStatus:1;
        unsigned int vScrollerStatus:1;
        unsigned int hScrollerRequired:1;
        unsigned int vScrollerRequired:1;
    } _sFlags;	// 13658536 = 0xd069a8
    void *_extraIvars;	// 13658528 = 0xd069a0
    NSRulerView *_horizontalRuler;	// 13658512 = 0xd06990
    NSRulerView *_verticalRuler;	// 13658520 = 0xd06998
}

+ (void)initialize;
+ (struct CGSize)frameSizeForContentSize:(struct CGSize)arg1 horizontalScrollerClass:(Class)arg2 verticalScrollerClass:(Class)arg3 borderType:(unsigned long long)arg4 controlSize:(unsigned long long)arg5 scrollerStyle:(long long)arg6;
+ (struct CGSize)contentSizeForFrameSize:(struct CGSize)arg1 horizontalScrollerClass:(Class)arg2 verticalScrollerClass:(Class)arg3 borderType:(unsigned long long)arg4 controlSize:(unsigned long long)arg5 scrollerStyle:(long long)arg6;
+ (struct CGSize)frameSizeForContentSize:(struct CGSize)arg1 hasHorizontalScroller:(BOOL)arg2 hasVerticalScroller:(BOOL)arg3 borderType:(unsigned long long)arg4;
+ (struct CGSize)contentSizeForFrameSize:(struct CGSize)arg1 hasHorizontalScroller:(BOOL)arg2 hasVerticalScroller:(BOOL)arg3 borderType:(unsigned long long)arg4;
+ (Class)_horizontalScrollerClass;
+ (Class)_verticalScrollerClass;
+ (void)setRulerViewClass:(Class)arg1;
+ (Class)rulerViewClass;
- (BOOL)_usesOverlayScrollers;
- (void)_updateTrackingAreas;
- (void)viewWillMoveToSuperview:(id)arg1;
- (BOOL)_overlayScrollersShown;
- (void)_overlayScroller:(id)arg1 didBecomeShown:(BOOL)arg2;
- (void)_pulseOverlayScrollers;
- (void)flashScrollers;
- (void)_scrollerDidEndTracking:(id)arg1;
- (struct CGRect)_contentFrameMinusScrollers;
- (void)_invalidateOverlayScrollerDebrisForScrollCopyOfClipView:(id)arg1 byDeltas:(struct CGPoint)arg2;
- (void)updateTrackingAreas;
- (id)_pointInVisibleScroller:(struct CGPoint)arg1;
- (void)viewWillStartLiveResize;
- (void)viewDidEndLiveResize;
- (void)viewDidHide;
- (void)_resetOveralyScrollerFlashForWindowOrderOut:(id)arg1;
- (void)_ensureOveralyScrollerFlashForWindowOrderIn:(id)arg1;
- (void)viewDidMoveToWindow;
- (void)viewWillDraw;
- (BOOL)_desiredLayerSizeMeritsTiledBackingLayer:(struct CGSize)arg1;
- (BOOL)scrollRectToVisible:(const struct CGRect *)arg1 fromView:(id)arg2;
- (id)initWithFrame:(struct CGRect)arg1;
- (void)dealloc;
- (double)_horizontalScrollerHeight;
- (double)_verticalScrollerWidth;
- (double)_horizontalScrollerHeightWithBorder;
- (double)_verticalScrollerWidthWithBorder;
- (BOOL)_accessoryViewMightInterfereWithOverlayScrollers:(id)arg1;
- (void)_checkForAccessoryViewsInScrollerAreas;
- (id)_allocContentAreaLayout;
- (void)_applyContentAreaLayout:(id)arg1;
- (struct CGRect)_cornerViewFrame;
- (struct CGSRegionObject *)_regionForOpaqueDescendants:(struct CGRect)arg1 forMove:(BOOL)arg2;
- (BOOL)isOpaque;
- (BOOL)isFlipped;
- (long long)scrollerStyle;
- (void)setScrollerStyle:(long long)arg1;
- (long long)scrollerKnobStyle;
- (void)setScrollerKnobStyle:(long long)arg1;
- (BOOL)_ownsWindowGrowBox;
- (void)_fixGrowBox;
- (BOOL)_updateGrowBoxForWindowFrameChange;
- (BOOL)_documentViewWantsHeaderView;
- (BOOL)_fixHeaderAndCornerViews;
- (void)setDocumentView:(id)arg1;
- (id)documentView;
- (void)setContentView:(id)arg1;
- (id)contentView;
- (struct CGRect)documentVisibleRect;
- (void)setDocumentCursor:(id)arg1;
- (id)documentCursor;
- (struct CGSize)contentSize;
- (void)resizeSubviewsWithOldSize:(struct CGSize)arg1;
- (void)setCopiesOnScroll:(BOOL)arg1;
- (void)setScrollsDynamically:(BOOL)arg1;
- (BOOL)scrollsDynamically;
- (void)setDrawsBackground:(BOOL)arg1;
- (BOOL)drawsBackground;
- (BOOL)_drawRectIfEmpty;
- (void)drawRect:(struct CGRect)arg1;
- (void)showActiveFirstResponderIndication;
- (void)_setKeyboardFocusRingNeedsDisplayDuringLiveResize;
- (void)_drawRect:(struct CGRect)arg1 clip:(BOOL)arg2;
- (void)setFrameSize:(struct CGSize)arg1;
- (void)setFrameOrigin:(struct CGPoint)arg1;
- (BOOL)_hasRectangularFocusRingAroundFrame;
- (unsigned long long)borderType;
- (void)setBorderType:(unsigned long long)arg1;
- (void)setBackgroundColor:(id)arg1;
- (id)backgroundColor;
- (void)setHasVerticalScroller:(BOOL)arg1;
- (BOOL)hasVerticalScroller;
- (void)setHasHorizontalScroller:(BOOL)arg1;
- (BOOL)hasHorizontalScroller;
- (id)verticalScroller;
- (id)horizontalScroller;
- (void)setVerticalScroller:(id)arg1;
- (void)setHorizontalScroller:(id)arg1;
- (BOOL)autohidesScrollers;
- (void)setAutohidesScrollers:(BOOL)arg1;
- (id)_newScroll:(BOOL)arg1;
- (void)_updateRulerlineForRuler:(id)arg1 oldPosition:(double)arg2 newPosition:(double)arg3 vertical:(BOOL)arg4;
- (id)_rulerline:(double)arg1:(double)arg2 last:(BOOL)arg3;
- (void)_setScrollerNeedsDisplay:(id)arg1;
- (id)_commonNewScroll:(id)arg1;
- (double)_repeatMultiplier:(double)arg1;
- (void)setHorizontalLineScroll:(double)arg1;
- (void)setVerticalLineScroll:(double)arg1;
- (void)setLineScroll:(double)arg1;
- (double)horizontalLineScroll;
- (double)verticalLineScroll;
- (double)lineScroll;
- (void)setHorizontalPageScroll:(double)arg1;
- (void)setVerticalPageScroll:(double)arg1;
- (void)setPageScroll:(double)arg1;
- (double)horizontalPageScroll;
- (double)verticalPageScroll;
- (double)pageScroll;
- (void)_doScroller:(id)arg1 hitPart:(long long)arg2 multiplier:(double)arg3;
- (BOOL)_pinnedInDirectionX:(double)arg1 y:(double)arg2;
- (BOOL)_pinnedInDirectionOfScroll:(id)arg1;
- (struct CGSize)_stretchAmount;
- (void)_snapRubberBand;
- (void)_snapRubberBandDueToNotification:(id)arg1;
- (void)_snapRubberBandWhenMouseReleasedFromTrackingLoop;
- (BOOL)_allowsVerticalStretching;
- (BOOL)_allowsHorizontalStretching;
- (void)_smoothScrollWithEvent:(id)arg1;
- (void)_discreetScrollWithEvent:(id)arg1;
- (void)scrollWheel:(id)arg1;
- (long long)horizontalScrollElasticity;
- (void)setHorizontalScrollElasticity:(long long)arg1;
- (long long)verticalScrollElasticity;
- (void)setVerticalScrollElasticity:(long long)arg1;
- (BOOL)usesPredominantAxisScrolling;
- (void)setUsesPredominantAxisScrolling:(BOOL)arg1;
- (void)_doScroller:(id)arg1;
- (void)_scrollPageInDirection:(int)arg1;
- (void)pageUp:(id)arg1;
- (void)pageDown:(id)arg1;
- (BOOL)needsPanelToBecomeKey;
- (BOOL)acceptsFirstResponder;
- (BOOL)becomeFirstResponder;
- (void)setNextKeyView:(id)arg1;
- (void)setInterfaceStyle:(unsigned long long)arg1;
- (void)_dynamicColorsChanged:(id)arg1;
- (id)_update;
- (BOOL)preservesContentDuringLiveResize;
- (void)_updateForLiveResizeWithOldSize:(struct CGSize)arg1;
- (id)_setWindow:(id)arg1;
- (BOOL)_cornerViewHidesWithVerticalScroller;
- (void)_setHorizontalScrollerHidden:(BOOL)arg1;
- (void)_setVerticalScrollerHidden:(BOOL)arg1;
- (void)_tileWithoutRecursing;
- (void)tile;
- (void)scrollClipView:(id)arg1 toPoint:(struct CGPoint)arg2;
- (id)_copySubviewsInOrderOfDisplay;
- (void)reflectScrolledClipView:(id)arg1;
- (void)encodeRestorableStateWithCoder:(id)arg1;
- (void)restoreStateWithCoder:(id)arg1;
- (void)_conditionallyReflectScrolledClipView;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (id)_setAutoResizeDocView:(BOOL)arg1;
- (id)_contentView;
- (void)removeFromSuperview;
- (void)willRemoveSubview:(id)arg1;
- (double)_destinationFloatValueForScroller:(id)arg1;
@property(retain) NSView *findBarView;
@property(getter=isFindBarVisible) BOOL findBarVisible;
- (void)findBarViewDidChangeHeight;
- (void)setFindBarPosition:(long long)arg1;
- (long long)findBarPosition;
- (id)accessibilityAttributeNames;
- (id)accessibilityRoleAttribute;
- (id)accessibilityHorizontalScrollBarAttribute;
- (BOOL)accessibilityIsHorizontalScrollBarAttributeSettable;
- (id)accessibilityVerticalScrollBarAttribute;
- (BOOL)accessibilityIsVerticalScrollBarAttributeSettable;
- (id)accessibilityContentsAttribute;
- (BOOL)accessibilityIsContentsAttributeSettable;
- (id)_accessibilityAdditionalChildren;
- (id)accessibilityChildrenAttribute;
- (BOOL)accessibilityIsIgnored;
- (BOOL)drawsContentShadow;
- (void)setDrawsContentShadow:(BOOL)arg1;
- (id)scrollerImpPair;
- (struct CGRect)contentAreaRectForScrollerImpPair:(id)arg1;
- (BOOL)inLiveResizeForScrollerImpPair:(id)arg1;
- (struct CGPoint)mouseLocationInContentAreaForScrollerImpPair:(id)arg1;
- (struct CGPoint)scrollerImpPair:(id)arg1 convertContentPoint:(struct CGPoint)arg2 toScrollerImp:(id)arg3;
- (void)scrollerImpPair:(id)arg1 setContentAreaNeedsDisplayInRect:(struct CGRect)arg2;
- (void)scrollerImpPair:(id)arg1 updateScrollerStyleForNewRecommendedScrollerStyle:(long long)arg2;
- (void)_setLineBorderColor:(id)arg1;
- (id)_lineBorderColor;
- (BOOL)autoforwardsScrollWheelEvents;
- (void)setAutoforwardsScrollWheelEvents:(BOOL)arg1;
- (struct CGRect)_boundsInsetForBorder;
- (void)_hideOverlayScrollers;
- (void)_lockOverlayScrollerState:(unsigned long long)arg1;
- (void)_unlockOverlayScrollerState;
- (BOOL)_overlayScrollerStateIsLocked;
- (void)setRulersVisible:(BOOL)arg1;
- (BOOL)rulersVisible;
- (void)setHasHorizontalRuler:(BOOL)arg1;
- (BOOL)hasHorizontalRuler;
- (void)setHasVerticalRuler:(BOOL)arg1;
- (BOOL)hasVerticalRuler;
- (void)setHorizontalRulerView:(id)arg1;
- (id)horizontalRulerView;
- (void)setVerticalRulerView:(id)arg1;
- (id)verticalRulerView;
- (void)_reflectDocumentViewBoundsChange;
- (void)_handleBoundsChangeForSubview:(id)arg1;
- (id)rulerStateDescription;
- (id)ns_widgetType;

@end

@interface _NSScrollViewContentAreaLayout : NSObject
{
    NSScrollView *scrollView;	// 13659296 = 0xd06ca0
    struct CGSize contentAreaSize;	// 13658424 = 0xd06938
    struct CGSize documentFrameSize;	// 13658408 = 0xd06928
    BOOL hScrollerShown;	// 13658432 = 0xd06940
    BOOL vScrollerShown;	// 13658440 = 0xd06948
    BOOL didTrimContentAreaForHScroller;	// 13658448 = 0xd06950
    BOOL didTrimContentAreaForVScroller;	// 13658456 = 0xd06958
    struct CGSize trimmedContentAreaSize;	// 13658416 = 0xd06930
}

- (id)_initWithScrollView:(id)arg1;
- (id)copy;
- (id)description;
- (struct CGSize)_documentFrameSize;
- (struct CGSize)_clipBoundsSize;
- (void)_resetLayoutWithContentAreaSize:(struct CGSize)arg1;
- (void)_addHorizontalScroller;
- (void)_addVerticalScroller;
- (void)_updateLayoutWithDocumentFrameSize:(struct CGSize)arg1;
- (BOOL)_hScrollerShown;
- (BOOL)_vScrollerShown;
- (BOOL)_didTrimContentAreaForHScroller;
- (BOOL)_didTrimContentAreaForVScroller;
- (struct CGSize)_trimmedContentAreaSize;

@end