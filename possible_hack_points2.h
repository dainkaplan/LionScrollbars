@interface _NSBrowserScrollView : NSScrollView
{
}

- (id)initWithFrame:(struct CGRect)arg1;
- (id)_enclosingBrowserView;
- (void)_handleBoundsChangeForSubview:(id)arg1;
- (BOOL)preservesContentDuringLiveResize;
- (void)drawRect:(struct CGRect)arg1;
- (void)tile;
- (void)_doScroller:(id)arg1 hitPart:(long long)arg2 multiplier:(double)arg3;
- (id)_focusRingBleedRegion;
- (void)scrollWheel:(id)arg1;
/*POINT*/- (void)_overlayScroller:(id)arg1 didBecomeShown:(BOOL)arg2;

@end


@interface _NSBrowserColumnsContainerView : NSView
{
    struct __BrccvFlags {
        unsigned int ignoreScrolling:1;
        unsigned int reserved:31;
    } _brccvFlags;	// 12725256 = 0xc22c08
}

- (id)hitTest:(struct CGPoint)arg1;
- (id)_enclosingBrowserView;
- (BOOL)preservesContentDuringLiveResize;
- (void)setFrameSize:(struct CGSize)arg1;
- (BOOL)isOpaque;
- (void)drawRect:(struct CGRect)arg1;
- (BOOL)_showingFocusRingAroundEnclosingScrollView:(id)arg1;
- (void)_drawScrollViewFocusRing:(id)arg1 clipRect:(struct CGRect)arg2 needsFullDisplay:(BOOL)arg3;
- (void)_setIgnoringScrolling:(BOOL)arg1;
- (BOOL)_ignoringScrolling;
- (void)scrollPoint:(struct CGPoint)arg1;
- (BOOL)scrollRectToVisible:(struct CGRect)arg1;
- (void)scrollRect:(struct CGRect)arg1 by:(struct CGSize)arg2;
- (id)menuForEvent:(id)arg1;
- (void)viewDidMoveToWindow;
/*POINT*/- (void)_scrollerStyleRecommendationChanged:(id)arg1;

@end


@interface _NSBrowserColumnScrollHelper : NSObject
{
    _NSBrowserScrollView *_scrollView;	// 12726152 = 0xc22f88
    _NSBrowserColumnView *_optimizableColumn;	// 12726176 = 0xc22fa0
    struct CGPoint _initialOrigin;	// 12728080 = 0xc23710
    struct CGRect _destinationRect;	// 12726168 = 0xc22f98
    double _totalDistance;	// 12728088 = 0xc23718
    double _totalDuration;	// 12728096 = 0xc23720
    struct __BrcshFlags {
        unsigned int done:1;
        unsigned int animate:1;
        unsigned int shouldPostScrollNotifications:1;
        unsigned int needsEndColumnAnimationOptimization:1;
        unsigned int reserved:28;
    } _brcshFlags;	// 12726160 = 0xc22f90
    double _startTime;	// 12728104 = 0xc23728
    struct __CFRunLoopTimer *_timer;	// 12727224 = 0xc233b8
    struct __CFRunLoop *_runLoop;	// 12728112 = 0xc23730
    struct __CFRunLoopObserver *_displayWindowForBrowserObserver;	// 12728120 = 0xc23738
}

- (void)_setupRunLoopTimer;
- (void)_invalidateRunLoopTimer;
- (void)dealloc;
- (void)finalize;
- (void)_scrollToPosition:(long long)arg1;
- (void)_scrollToFinalPosition;
- (void)_doAnimationStep;
- (void)_stopAnimation;
- (id)_enclosingBrowserView;
/*POINT*/- (void)_suppressScrollerSurfaceBackingForAnimationForBannedApps:(BOOL)arg1;
- (void)_doAnimation;
- (void)setOptimizableColumn:(id)arg1;
- (void)scrollRectToVisible:(struct CGRect)arg1 inScrollView:(id)arg2 animate:(BOOL)arg3;
- (void)changeDestinationToRect:(struct CGRect)arg1;

@end


@interface NSClipView : NSView
{
    NSColor *_backgroundColor;	// 12768416 = 0xc2d4a0
    NSView *_docView;	// 12768392 = 0xc2d488
    struct CGRect _docRect;	// 12768400 = 0xc2d490
    struct CGRect _oldDocFrame;	// 12771304 = 0xc2dfe8
    NSCursor *_cursor;	// 12768424 = 0xc2d4a8
    id _scrollAnimationHelper;	// 12771312 = 0xc2dff0
    struct __cvFlags {
        unsigned int isFlipped:1;
        unsigned int onlyUncovered:1;
        unsigned int reflectScroll:1;
        unsigned int usedByCell:1;
        unsigned int scrollClipTo:1;
        unsigned int noCopyOnScroll:1;
        unsigned int drawsBackground:1;
        unsigned int scrollInProgress:1;
        unsigned int skipRemoveSuperviewCheck:1;
        unsigned int animateCurrentScroll:1;
        unsigned int canAnimateScrolls:1;
        unsigned int nextScrollRelativeToCurrentPosition:1;
        unsigned int viewBoundsChangedOverridden:1;
        unsigned int viewFrameChangedOverridden:1;
        unsigned int documentViewAlignment:4;
        unsigned int redrawnWhileScrolling:1;
        unsigned int dontConstrainScroll:1;
        unsigned int lastAtEdgesState:4;
        unsigned int showOverlayScrollersForScrollStep:1;
        unsigned int scrollerKnobFlashSpecifier:2;
        unsigned int drawsContentShadow:1;
        unsigned int RESERVED:4;
    } _cvFlags;	// 12768408 = 0xc2d498
}

/*POINT*/+ (void)_animatedScrollingPreferencesChanged:(id)arg1;
+ (void)initialize;
+ (void)_setAutoscrollResponseMultiplier:(double)arg1;
+ (double)_autoscrollResponseMultiplier;
+ (id)_contentShadow;
- (BOOL)_desiredLayerSizeMeritsTiledBackingLayer:(struct CGSize)arg1;
- (void)setLayer:(id)arg1;
- (BOOL)_drawsNothing;
- (id)initWithFrame:(struct CGRect)arg1;
- (BOOL)isOpaque;
- (BOOL)_clipViewShouldClipFocusRing;
- (id)_setSuperview:(id)arg1;
- (void)_registerForDocViewFrameAndBoundsChangeNotifications;
- (void)_unregisterForDocViewFrameAndBoundsChangeNotifications;
- (void)setDocumentView:(id)arg1;
- (void)willRemoveSubview:(id)arg1;
- (id)documentView;
- (void)_setDocViewFromRead:(id)arg1;
- (struct CGRect)documentRect;
- (struct CGSize)_minimumFrameSize;
- (struct CGRect)documentVisibleRect;
- (id)_markUsedByCell;
- (BOOL)_isUsedByCell;
- (void)setBackgroundColor:(id)arg1;
- (id)backgroundColor;
- (void)setDrawsBackground:(BOOL)arg1;
- (BOOL)drawsBackground;
- (BOOL)_canUseTiledBackingLayer;
- (id)makeBackingLayer;
- (unsigned long long)_backgroundFillOperation;
- (BOOL)drawsContentShadow;
- (void)setDrawsContentShadow:(BOOL)arg1;
- (id)_newShadowOfSize:(struct CGSize)arg1 fromOffset:(struct CGPoint)arg2 inImage:(id)arg3;
- (void)_drawShadowAroundRect:(struct CGRect)arg1 clipRect:(struct CGRect)arg2;
- (void)_drawOverhangShadowsInRect:(struct CGRect)arg1;
- (void)drawRect:(struct CGRect)arg1;
- (void)_pinDocRect;
- (BOOL)_forcePixelAlignedClipViewFrame;
- (void)setFrameOrigin:(struct CGPoint)arg1;
- (void)setFrameSize:(struct CGSize)arg1;
- (void)setFrameRotation:(double)arg1;
- (void)setBoundsOrigin:(struct CGPoint)arg1;
- (void)setBoundsSize:(struct CGSize)arg1;
- (void)setBoundsRotation:(double)arg1;
- (void)translateOriginToPoint:(struct CGPoint)arg1;
- (void)scaleUnitSquareToSize:(struct CGSize)arg1;
- (void)rotateByAngle:(double)arg1;
- (id)_computeBounds;
- (BOOL)preservesContentDuringLiveResize;
- (void)_selfBoundsChanged;
- (struct CGRect)_dirtyRectUncoveredFromOldDocFrame:(struct CGRect)arg1 byNewDocFrame:(struct CGRect)arg2;
- (void)_reflectDocumentViewFrameChange;
- (void)viewFrameChanged:(id)arg1;
- (void)_handleFrameChangeForSubview:(id)arg1;
- (void)_reflectDocumentViewBoundsChange;
- (void)viewBoundsChanged:(id)arg1;
- (void)_handleBoundsChangeForSubview:(id)arg1;
- (BOOL)isFlipped;
- (void)_alignCoords;
- (struct CGPoint)_pixelAlignProposedScrollPosition:(struct CGPoint)arg1;
- (BOOL)_proposedScrollPositionIsPixelAligned:(struct CGPoint)arg1;
- (void)_extendNextScrollRelativeToCurrentPosition;
- (BOOL)autoscroll:(id)arg1;
- (BOOL)_shouldAutoscrollForDraggingInfo:(id)arg1;
- (double)_scrollAmountForLineScroll:(double)arg1 percentageTowardsMax:(double)arg2 limitingSize:(double)arg3 multiplier:(double)arg4;
- (void)_autoscrollForDraggingInfo:(id)arg1 timeDelta:(double)arg2;
- (void)_scrollPoint:(const struct CGPoint *)arg1 fromView:(id)arg2;
- (BOOL)_scrollRectToVisible:(const struct CGRect *)arg1 fromView:(id)arg2;
- (BOOL)_scrollTo:(const struct CGPoint *)arg1;
- (BOOL)_scrollTo:(const struct CGPoint *)arg1 animate:(BOOL)arg2;
- (BOOL)_scrollTo:(const struct CGPoint *)arg1 animateScroll:(long long)arg2 flashScrollerKnobs:(unsigned long long)arg3;
- (struct CGPoint)constrainScrollPoint:(struct CGPoint)arg1;
- (BOOL)_canAnimateScrolls;
- (void)_setCanAnimateScrolls:(BOOL)arg1;
- (void)_setDontConstrainScroll:(BOOL)arg1;
- (void)_setAnimateCurrentScroll:(BOOL)arg1;
- (BOOL)_animateCurrentScroll;
- (void)setCopiesOnScroll:(BOOL)arg1;
- (BOOL)copiesOnScroll;
- (BOOL)_canCopyOnScrollForDeltaX:(double)arg1 deltaY:(double)arg2;
/*POINT*/- (BOOL)_shouldShowOverlayScrollersForScrollToPoint:(struct CGPoint)arg1;
- (void)_animatedScrollToPoint:(struct CGPoint)arg1;
- (void)_drawRect:(struct CGRect)arg1 clip:(BOOL)arg2;
- (void)_invalidateIntersectionsWithSiblingViews;
- (void)_immediateScrollToPoint:(struct CGPoint)arg1;
- (void)scrollToPoint:(struct CGPoint)arg1;
- (BOOL)_scrollInProgress;
- (BOOL)_shouldAdjustPatternPhase;
- (void)setUpGState;
- (BOOL)needsPanelToBecomeKey;
- (BOOL)acceptsFirstResponder;
- (BOOL)becomeFirstResponder;
- (void)setNextKeyView:(id)arg1;
- (void)setDocumentCursor:(id)arg1;
- (id)documentCursor;
- (void)resetCursorRects;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (void)dealloc;
- (BOOL)_isAnimatingScroll;
- (struct CGPoint)_animatingScrollTargetOrigin;
- (unsigned long long)_documentViewAlignment;
- (void)_setDocumentViewAlignment:(unsigned long long)arg1;

@end

@interface _NSScrollViewContentAreaLayout : NSObject
{
    NSScrollView *scrollView;	// 13672520 = 0xd0a048
    struct CGSize contentAreaSize;	// 13671648 = 0xd09ce0
    struct CGSize documentFrameSize;	// 13671632 = 0xd09cd0
    BOOL hScrollerShown;	// 13671656 = 0xd09ce8
    BOOL vScrollerShown;	// 13671664 = 0xd09cf0
    BOOL didTrimContentAreaForHScroller;	// 13671672 = 0xd09cf8
    BOOL didTrimContentAreaForVScroller;	// 13671680 = 0xd09d00
    struct CGSize trimmedContentAreaSize;	// 13671640 = 0xd09cd8
}

- (id)_initWithScrollView:(id)arg1;
- (id)copy;
- (id)description;
- (struct CGSize)_documentFrameSize;
- (struct CGSize)_clipBoundsSize;
- (void)_resetLayoutWithContentAreaSize:(struct CGSize)arg1;
/*POINT*/- (void)_addHorizontalScroller;
/*POINT*/- (void)_addVerticalScroller;
- (void)_updateLayoutWithDocumentFrameSize:(struct CGSize)arg1;
/*POINT*/- (BOOL)_hScrollerShown;
/*POINT*/- (BOOL)_vScrollerShown;
- (BOOL)_didTrimContentAreaForHScroller;
- (BOOL)_didTrimContentAreaForVScroller;
- (struct CGSize)_trimmedContentAreaSize;

@end


@interface WebDynamicScrollBarsView : NSScrollView <WebCoreFrameScrollView>
{
    struct WebDynamicScrollBarsViewPrivate *_private;	// 1651264 = 0x193240
}

- (id)initWithFrame:(struct CGRect)arg1;
- (id)initWithCoder:(id)arg1;
- (void)dealloc;
- (void)finalize;
- (void)setAllowsHorizontalScrolling:(BOOL)arg1;
/*POINT*/- (void)setAllowsScrollersToOverlapContent:(BOOL)arg1;
/*POINT*/- (void)setAlwaysHideHorizontalScroller:(BOOL)arg1;
/*POINT*/- (void)setAlwaysHideVerticalScroller:(BOOL)arg1;
- (BOOL)horizontalScrollingAllowed;
- (BOOL)verticalScrollingAllowed;
- (struct CGRect)contentViewFrame;
- (void)tile;
- (void)setSuppressLayout:(BOOL)arg1;
- (void)setScrollBarsSuppressed:(BOOL)arg1 repaintOnUnsuppress:(BOOL)arg2;
- (void)adjustForScrollOriginChange;
/*POINT*/- (void)updateScrollers;
- (void)reflectScrolledClipView:(id)arg1;
- (BOOL)allowsHorizontalScrolling;
- (BOOL)allowsVerticalScrolling;
- (void)scrollingModes:(int *)arg1 vertical:(int *)arg2;
- (int)horizontalScrollingMode;
- (int)verticalScrollingMode;
- (void)setHorizontalScrollingMode:(int)arg1 andLock:(BOOL)arg2;
- (void)setVerticalScrollingMode:(int)arg1 andLock:(BOOL)arg2;
- (void)setVerticalScrollingMode:(int)arg1;
- (void)setScrollingModes:(int)arg1 vertical:(int)arg2 andLock:(BOOL)arg3;
- (void)setHorizontalScrollingModeLocked:(BOOL)arg1;
- (void)setVerticalScrollingModeLocked:(BOOL)arg1;
- (void)setScrollingModesLocked:(BOOL)arg1;
- (BOOL)horizontalScrollingModeLocked;
- (BOOL)verticalScrollingModeLocked;
- (BOOL)autoforwardsScrollWheelEvents;
- (void)scrollWheel:(id)arg1;
- (BOOL)accessibilityIsIgnored;
- (void)setScrollOrigin:(struct CGPoint)arg1 updatePositionAtAll:(BOOL)arg2 immediately:(BOOL)arg3;
- (struct CGPoint)scrollOrigin;
- (BOOL)inProgrammaticScroll;

@end


@protocol WebCoreFrameScrollView
- (void)setScrollingModes:(int)arg1 vertical:(int)arg2 andLock:(BOOL)arg3;
- (void)scrollingModes:(int *)arg1 vertical:(int *)arg2;
- (void)setScrollBarsSuppressed:(BOOL)arg1 repaintOnUnsuppress:(BOOL)arg2;
- (void)setScrollOrigin:(struct CGPoint)arg1 updatePositionAtAll:(BOOL)arg2 immediately:(BOOL)arg3;
- (struct CGPoint)scrollOrigin;
@end



@interface WebFrame : NSObject
{
    WebFramePrivate *_private;	// 1657784 = 0x194bb8
}

+ (PassRefPtr_4af616b4)_createFrameWithPage:(struct Page *)arg1 frameName:(const struct String *)arg2 frameView:(id)arg3 ownerElement:(struct HTMLFrameOwnerElement *)arg4;
+ (void)_createMainFrameWithPage:(struct Page *)arg1 frameName:(const struct String *)arg2 frameView:(id)arg3;
+ (PassRefPtr_4af616b4)_createSubframeWithOwnerElement:(struct HTMLFrameOwnerElement *)arg1 frameName:(const struct String *)arg2 frameView:(id)arg3;
- (id)init;
- (id)initWithName:(id)arg1 webFrameView:(id)arg2 webView:(id)arg3;
- (void)dealloc;
- (void)finalize;
- (id)name;
- (id)frameView;
- (id)webView;
- (id)DOMDocument;
- (id)frameElement;
- (id)provisionalDataSource;
- (id)dataSource;
- (void)loadRequest:(id)arg1;
- (void)_loadData:(id)arg1 MIMEType:(id)arg2 textEncodingName:(id)arg3 baseURL:(id)arg4 unreachableURL:(id)arg5;
- (void)loadData:(id)arg1 MIMEType:(id)arg2 textEncodingName:(id)arg3 baseURL:(id)arg4;
- (void)_loadHTMLString:(id)arg1 baseURL:(id)arg2 unreachableURL:(id)arg3;
- (void)loadHTMLString:(id)arg1 baseURL:(id)arg2;
- (void)loadAlternateHTMLString:(id)arg1 baseURL:(id)arg2 forUnreachableURL:(id)arg3;
- (void)loadArchive:(id)arg1;
- (void)stopLoading;
- (void)reload;
- (void)reloadFromOrigin;
- (id)findFrameNamed:(id)arg1;
- (id)parentFrame;
- (id)childFrames;
- (id)windowObject;
- (struct OpaqueJSContext *)globalContext;
- (id)renderTreeAsExternalRepresentationForPrinting:(BOOL)arg1;
- (id)counterValueForElement:(id)arg1;
- (int)pageNumberForElement:(id)arg1:(float)arg2:(float)arg3;
- (int)numberOfPages:(float)arg1:(float)arg2;
- (id)pageProperty:(const char *)arg1:(int)arg2;
- (_Bool)isPageBoxVisible:(int)arg1;
- (id)pageSizeAndMarginsInPixels:(int)arg1:(int)arg2:(int)arg3:(int)arg4:(int)arg5:(int)arg6:(int)arg7;
- (void)printToCGContext:(struct CGContext *)arg1:(float)arg2:(float)arg3;
- (BOOL)_isDescendantOfFrame:(id)arg1;
- (void)_setShouldCreateRenderers:(BOOL)arg1;
- (id)_bodyBackgroundColor;
- (BOOL)_isFrameSet;
- (BOOL)_firstLayoutDone;
- (int)_loadType;
- (struct _NSRange)_selectedNSRange;
- (void)_selectNSRange:(struct _NSRange)arg1;
- (BOOL)_isDisplayingStandaloneImage;
- (unsigned int)_pendingFrameUnloadEventCount;
- (void)_setIsDisconnected:(_Bool)arg1;
- (void)_setExcludeFromTextSearch:(_Bool)arg1;
- (void)_recursive_resumeNullEventsForAllNetscapePlugins;
- (void)_recursive_pauseNullEventsForAllNetscapePlugins;
- (BOOL)_pauseAnimation:(id)arg1 onNode:(id)arg2 atTime:(double)arg3;
- (BOOL)_pauseTransitionOfProperty:(id)arg1 onNode:(id)arg2 atTime:(double)arg3;
- (BOOL)_pauseSVGAnimation:(id)arg1 onSMILNode:(id)arg2 atTime:(double)arg3;
- (unsigned int)_numberOfActiveAnimations;
- (void)_suspendAnimations;
- (void)_resumeAnimations;
- (void)_replaceSelectionWithFragment:(id)arg1 selectReplacement:(BOOL)arg2 smartReplace:(BOOL)arg3 matchStyle:(BOOL)arg4;
- (void)_replaceSelectionWithText:(id)arg1 selectReplacement:(BOOL)arg2 smartReplace:(BOOL)arg3;
- (void)_replaceSelectionWithMarkupString:(id)arg1 baseURLString:(id)arg2 selectReplacement:(BOOL)arg3 smartReplace:(BOOL)arg4;
- (void)_smartInsertForString:(id)arg1 replacingRange:(id)arg2 beforeString:(id *)arg3 afterString:(id *)arg4;
- (id)_cacheabilityDictionary;
- (BOOL)_allowsFollowingLink:(id)arg1;
- (id)_stringByEvaluatingJavaScriptFromString:(id)arg1 withGlobalObject:(struct OpaqueJSValue *)arg2 inScriptWorld:(id)arg3;
- (struct OpaqueJSContext *)_globalContextForScriptWorld:(id)arg1;
/*POINT*/- (void)setAllowsScrollersToOverlapContent:(BOOL)arg1;
/*POINT*/- (void)setAlwaysHideHorizontalScroller:(BOOL)arg1;
/*POINT*/- (void)setAlwaysHideVerticalScroller:(BOOL)arg1;
- (void)setAccessibleName:(id)arg1;
- (id)_layerTreeAsText;
- (BOOL)hasSpellingMarker:(int)arg1 length:(int)arg2;
- (BOOL)hasGrammarMarker:(int)arg1 length:(int)arg2;
- (id)accessibilityRoot;
- (void)_clearOpener;
- (id)_computePageRectsWithPrintScaleFactor:(float)arg1 pageSize:(struct CGSize)arg2;
- (BOOL)_isIncludedInWebKitStatistics;
- (void)_attachScriptDebugger;
- (void)_detachScriptDebugger;
- (id)_initWithWebFrameView:(id)arg1 webView:(id)arg2;
- (void)_clearCoreFrame;
- (void)_updateBackgroundAndUpdatesWhileOffscreen;
- (void)_setInternalLoadDelegate:(id)arg1;
- (id)_internalLoadDelegate;
- (void)_unmarkAllBadGrammar;
- (void)_unmarkAllMisspellings;
- (BOOL)_hasSelection;
- (void)_clearSelection;
- (id)_findFrameWithSelection;
- (void)_clearSelectionInOtherFrames;
- (id)_dataSource;
- (id)_stringWithDocumentTypeStringAndMarkupString:(id)arg1;
- (id)_nodesFromList:(Vector_37bbce44 *)arg1;
- (id)_markupStringFromRange:(id)arg1 nodes:(id *)arg2;
- (id)_selectedString;
- (id)_stringForRange:(id)arg1;
- (BOOL)_shouldFlattenCompositingLayers:(struct CGContext *)arg1;
- (void)_drawRect:(struct CGRect)arg1 contentsOnly:(BOOL)arg2;
- (BOOL)_getVisibleRect:(struct CGRect *)arg1;
- (id)_stringByEvaluatingJavaScriptFromString:(id)arg1;
- (id)_stringByEvaluatingJavaScriptFromString:(id)arg1 forceUserGesture:(BOOL)arg2;
- (struct CGRect)_caretRectAtPosition:(const struct Position *)arg1 affinity:(unsigned long long)arg2;
- (struct CGRect)_firstRectForDOMRange:(id)arg1;
- (void)_scrollDOMRangeToVisible:(id)arg1;
- (BOOL)_needsLayout;
- (id)_rangeByAlteringCurrentSelection:(int)arg1 direction:(int)arg2 granularity:(int)arg3;
- (int)_selectionGranularity;
- (struct _NSRange)_convertToNSRange:(struct Range *)arg1;
- (PassRefPtr_d7fc6f43)_convertToDOMRange:(struct _NSRange)arg1;
- (id)convertNSRangeToDOMRange:(struct _NSRange)arg1;
- (id)_convertNSRangeToDOMRange:(struct _NSRange)arg1;
- (struct _NSRange)convertDOMRangeToNSRange:(id)arg1;
- (struct _NSRange)_convertDOMRangeToNSRange:(id)arg1;
- (id)_markDOMRange;
- (id)_smartDeleteRangeForProposedRange:(id)arg1;
- (id)_documentFragmentWithMarkupString:(id)arg1 baseURLString:(id)arg2;
- (id)_documentFragmentWithNodesAsParagraphs:(id)arg1;
- (void)_replaceSelectionWithNode:(id)arg1 selectReplacement:(BOOL)arg2 smartReplace:(BOOL)arg3 matchStyle:(BOOL)arg4;
- (void)_insertParagraphSeparatorInQuotedContent;
- (struct VisiblePosition)_visiblePositionForPoint:(struct CGPoint)arg1;
- (id)_characterRangeAtPoint:(struct CGPoint)arg1;
- (id)_typingStyle;
- (void)_setTypingStyle:(id)arg1 withUndoAction:(int)arg2;
- (void)_dragSourceEndedAt:(struct CGPoint)arg1 operation:(unsigned long long)arg2;
- (BOOL)_canProvideDocumentSource;
- (BOOL)_canSaveAsWebArchive;
- (void)_commitData:(id)arg1;

@end


@interface WebView : NSView <NSUserInterfaceValidations>
{
    WebViewPrivate *_private;	// 1742384 = 0x1a9630
}

+ (void)initialize;
+ (void)_applicationWillTerminate;
+ (BOOL)_canShowMIMEType:(id)arg1 allowingPlugins:(BOOL)arg2;
+ (BOOL)canShowMIMEType:(id)arg1;
+ (BOOL)canShowMIMETypeAsHTML:(id)arg1;
+ (id)MIMETypesShownAsHTML;
+ (void)setMIMETypesShownAsHTML:(id)arg1;
+ (id)URLFromPasteboard:(id)arg1;
+ (id)URLTitleFromPasteboard:(id)arg1;
+ (void)registerURLSchemeAsLocal:(id)arg1;
+ (void)registerViewClass:(Class)arg1 representationClass:(Class)arg2 forMIMEType:(id)arg3;
+ (BOOL)shouldIncludeInWebKitStatistics;
+ (void)_setCacheModel:(unsigned long long)arg1;
+ (unsigned long long)_cacheModel;
+ (unsigned long long)_didSetCacheModel;
+ (unsigned long long)_maxCacheModelInAnyInstance;
+ (void)_preferencesChangedNotification:(id)arg1;
+ (void)_preferencesRemovedNotification:(id)arg1;
+ (void)_preflightSpellCheckerNow:(id)arg1;
+ (void)_preflightSpellChecker;
+ (id)_standardUserAgentWithApplicationName:(id)arg1;
+ (void)_reportException:(struct OpaqueJSValue *)arg1 inContext:(struct OpaqueJSContext *)arg2;
+ (id)_supportedMIMETypes;
+ (id)_supportedFileExtensions;
+ (void)_registerPluginMIMEType:(id)arg1;
+ (void)_unregisterPluginMIMEType:(id)arg1;
+ (BOOL)_viewClass:(Class *)arg1 andRepresentationClass:(Class *)arg2 forMIMEType:(id)arg3 allowingPlugins:(BOOL)arg4;
+ (void)_setAlwaysUseATSU:(BOOL)arg1;
+ (void)_setAlwaysUsesComplexTextCodePath:(BOOL)arg1;
+ (BOOL)canCloseAllWebViews;
+ (void)closeAllWebViews;
+ (BOOL)canShowFile:(id)arg1;
+ (id)suggestedFileExtensionForMIMEType:(id)arg1;
+ (id)_MIMETypeForFile:(id)arg1;
+ (void)_unregisterViewClassAndRepresentationClassForMIMEType:(id)arg1;
+ (void)_registerViewClass:(Class)arg1 representationClass:(Class)arg2 forURLScheme:(id)arg3;
+ (id)_generatedMIMETypeForURLScheme:(id)arg1;
+ (BOOL)_representationExistsForURLScheme:(id)arg1;
+ (BOOL)_canHandleRequest:(id)arg1 forMainFrame:(BOOL)arg2;
+ (BOOL)_canHandleRequest:(id)arg1;
+ (id)_decodeData:(id)arg1;
+ (BOOL)automaticallyNotifiesObserversForKey:(id)arg1;
+ (void)_setShouldUseFontSmoothing:(BOOL)arg1;
+ (BOOL)_shouldUseFontSmoothing;
+ (void)_setUsesTestModeFocusRingColor:(BOOL)arg1;
+ (BOOL)_usesTestModeFocusRingColor;
+ (id)_pointingHandCursor;
+ (BOOL)_isNodeHaltedPlugin:(id)arg1;
+ (BOOL)_hasPluginForNodeBeenHalted:(id)arg1;
+ (void)_restartHaltedPluginForNode:(id)arg1;
+ (void)_addOriginAccessWhitelistEntryWithSourceOrigin:(id)arg1 destinationProtocol:(id)arg2 destinationHost:(id)arg3 allowDestinationSubdomains:(BOOL)arg4;
+ (void)_removeOriginAccessWhitelistEntryWithSourceOrigin:(id)arg1 destinationProtocol:(id)arg2 destinationHost:(id)arg3 allowDestinationSubdomains:(BOOL)arg4;
+ (void)_resetOriginAccessWhitelists;
+ (void)_addUserScriptToGroup:(id)arg1 world:(id)arg2 source:(id)arg3 url:(id)arg4 whitelist:(id)arg5 blacklist:(id)arg6 injectionTime:(int)arg7;
+ (void)_addUserScriptToGroup:(id)arg1 world:(id)arg2 source:(id)arg3 url:(id)arg4 whitelist:(id)arg5 blacklist:(id)arg6 injectionTime:(int)arg7 injectedFrames:(int)arg8;
+ (void)_addUserStyleSheetToGroup:(id)arg1 world:(id)arg2 source:(id)arg3 url:(id)arg4 whitelist:(id)arg5 blacklist:(id)arg6;
+ (void)_addUserStyleSheetToGroup:(id)arg1 world:(id)arg2 source:(id)arg3 url:(id)arg4 whitelist:(id)arg5 blacklist:(id)arg6 injectedFrames:(int)arg7;
+ (void)_removeUserScriptFromGroup:(id)arg1 world:(id)arg2 url:(id)arg3;
+ (void)_removeUserStyleSheetFromGroup:(id)arg1 world:(id)arg2 url:(id)arg3;
+ (void)_removeUserScriptsFromGroup:(id)arg1 world:(id)arg2;
+ (void)_removeUserStyleSheetsFromGroup:(id)arg1 world:(id)arg2;
+ (void)_removeAllUserContentFromGroup:(id)arg1;
+ (void)_setDomainRelaxationForbidden:(BOOL)arg1 forURLScheme:(id)arg2;
+ (void)_registerURLSchemeAsSecure:(id)arg1;
+ (void)_setLoadResourcesSerially:(BOOL)arg1;
+ (double)_defaultMinimumTimerInterval;
+ (BOOL)_HTTPPipeliningEnabled;
+ (void)_setHTTPPipeliningEnabled:(BOOL)arg1;
+ (void)_makeAllWebViewsPerformSelector:(SEL)arg1;
+ (void)_updateMouseoverWithEvent:(id)arg1;
- (BOOL)_canShowMIMEType:(id)arg1;
- (id)_pluginForMIMEType:(id)arg1;
- (id)_pluginForExtension:(id)arg1;
- (void)addPluginInstanceView:(id)arg1;
- (void)removePluginInstanceView:(id)arg1;
- (void)removePluginInstanceViewsFor:(id)arg1;
- (BOOL)_isMIMETypeRegisteredAsPlugin:(id)arg1;
- (id)_initWithArguments:(id)arg1;
- (id)initWithFrame:(struct CGRect)arg1;
- (id)initWithFrame:(struct CGRect)arg1 frameName:(id)arg2 groupName:(id)arg3;
- (id)initWithCoder:(id)arg1;
- (void)encodeWithCoder:(id)arg1;
- (void)dealloc;
- (void)finalize;
- (void)close;
- (void)setShouldCloseWithWindow:(BOOL)arg1;
- (BOOL)shouldCloseWithWindow;
- (void)addWindowObserversForWindow:(id)arg1;
- (void)removeWindowObservers;
- (void)viewWillMoveToWindow:(id)arg1;
- (void)viewDidMoveToWindow;
- (void)_windowDidBecomeKey:(id)arg1;
- (void)_windowDidResignKey:(id)arg1;
- (void)_windowWillOrderOnScreen:(id)arg1;
- (void)_windowWillOrderOffScreen:(id)arg1;
- (void)_windowWillClose:(id)arg1;
- (void)_windowDidChangeBackingProperties:(id)arg1;
- (void)setPreferences:(id)arg1;
- (id)preferences;
- (void)setPreferencesIdentifier:(id)arg1;
- (id)preferencesIdentifier;
- (void)setUIDelegate:(id)arg1;
- (id)UIDelegate;
- (void)setResourceLoadDelegate:(id)arg1;
- (id)resourceLoadDelegate;
- (void)setDownloadDelegate:(id)arg1;
- (id)downloadDelegate;
- (void)setPolicyDelegate:(id)arg1;
- (id)policyDelegate;
- (void)setFrameLoadDelegate:(id)arg1;
- (id)frameLoadDelegate;
- (id)mainFrame;
- (id)selectedFrame;
- (id)backForwardList;
- (void)setMaintainsBackForwardList:(BOOL)arg1;
- (BOOL)goBack;
- (BOOL)goForward;
- (BOOL)goToBackForwardItem:(id)arg1;
- (void)setTextSizeMultiplier:(float)arg1;
- (float)textSizeMultiplier;
- (void)_setZoomMultiplier:(float)arg1 isTextOnly:(BOOL)arg2;
- (float)_zoomMultiplier:(BOOL)arg1;
- (float)_realZoomMultiplier;
- (BOOL)_realZoomMultiplierIsTextOnly;
- (BOOL)_canZoomOut:(BOOL)arg1;
- (BOOL)_canZoomIn:(BOOL)arg1;
- (void)_zoomOut:(id)arg1 isTextOnly:(BOOL)arg2;
- (void)_zoomIn:(id)arg1 isTextOnly:(BOOL)arg2;
- (BOOL)_canResetZoom:(BOOL)arg1;
- (void)_resetZoom:(id)arg1 isTextOnly:(BOOL)arg2;
- (void)setApplicationNameForUserAgent:(id)arg1;
- (id)applicationNameForUserAgent;
- (void)setCustomUserAgent:(id)arg1;
- (id)customUserAgent;
- (void)setMediaStyle:(id)arg1;
- (id)mediaStyle;
- (BOOL)supportsTextEncoding;
- (void)setCustomTextEncodingName:(id)arg1;
- (id)_mainFrameOverrideEncoding;
- (id)customTextEncodingName;
- (id)stringByEvaluatingJavaScriptFromString:(id)arg1;
- (id)windowScriptObject;
- (id)userAgentForURL:(id)arg1;
- (void)setHostWindow:(id)arg1;
- (id)hostWindow;
- (id)documentViewAtWindowPoint:(struct CGPoint)arg1;
- (id)_elementAtWindowPoint:(struct CGPoint)arg1;
- (id)elementAtPoint:(struct CGPoint)arg1;
- (void)_autoscrollForDraggingInfo:(id)arg1 timeDelta:(double)arg2;
- (BOOL)_shouldAutoscrollForDraggingInfo:(id)arg1;
- (int)applicationFlags:(id)arg1;
- (unsigned long long)draggingEntered:(id)arg1;
- (unsigned long long)draggingUpdated:(id)arg1;
- (void)draggingExited:(id)arg1;
- (BOOL)prepareForDragOperation:(id)arg1;
- (BOOL)performDragOperation:(id)arg1;
- (id)_hitTest:(struct CGPoint *)arg1 dragTypes:(id)arg2;
- (BOOL)acceptsFirstResponder;
- (BOOL)becomeFirstResponder;
- (id)_webcore_effectiveFirstResponder;
- (void)setNextKeyView:(id)arg1;
- (BOOL)searchFor:(id)arg1 direction:(BOOL)arg2 caseSensitive:(BOOL)arg3 wrap:(BOOL)arg4;
- (void)setGroupName:(id)arg1;
- (id)groupName;
- (double)estimatedProgress;
- (id)pasteboardTypesForSelection;
- (void)writeSelectionWithPasteboardTypes:(id)arg1 toPasteboard:(id)arg2;
- (id)pasteboardTypesForElement:(id)arg1;
- (void)writeElement:(id)arg1 withPasteboardTypes:(id)arg2 toPasteboard:(id)arg3;
- (void)moveDragCaretToPoint:(struct CGPoint)arg1;
- (void)removeDragCaret;
- (void)setMainFrameURL:(id)arg1;
- (id)mainFrameURL;
- (BOOL)isLoading;
- (id)mainFrameTitle;
- (id)mainFrameIcon;
- (id)mainFrameDocument;
- (void)setDrawsBackground:(BOOL)arg1;
- (BOOL)drawsBackground;
- (void)setShouldUpdateWhileOffscreen:(BOOL)arg1;
- (BOOL)shouldUpdateWhileOffscreen;
- (void)setCurrentNodeHighlight:(id)arg1;
- (id)currentNodeHighlight;
- (id)previousValidKeyView;
- (struct OpaqueJSValue *)_nodesFromRect:(struct OpaqueJSContext *)arg1 forDocument:(struct OpaqueJSValue *)arg2 x:(int)arg3 y:(int)arg4 top:(unsigned int)arg5 right:(unsigned int)arg6 bottom:(unsigned int)arg7 left:(unsigned int)arg8 ignoreClipping:(BOOL)arg9;
- (struct OpaqueJSValue *)_computedStyleIncludingVisitedInfo:(struct OpaqueJSContext *)arg1 forElement:(struct OpaqueJSValue *)arg2;
- (void)_setGeolocationProvider:(id)arg1;
- (id)_geolocationProvider;
- (void)_geolocationDidChangePosition:(id)arg1;
- (void)_geolocationDidFailWithError:(id)arg1;
- (void)_setDeviceOrientationProvider:(id)arg1;
- (id)_deviceOrientationProvider;
- (BOOL)_becomingFirstResponderFromOutside;
- (void)_receivedIconChangedNotification:(id)arg1;
- (void)_registerForIconNotification:(BOOL)arg1;
- (void)_dispatchDidReceiveIconFromWebFrame:(id)arg1;
- (void)_addObject:(id)arg1 forIdentifier:(unsigned long long)arg2;
- (id)_objectForIdentifier:(unsigned long long)arg1;
- (void)_removeObjectForIdentifier:(unsigned long long)arg1;
- (void)_retrieveKeyboardUIModeFromPreferences:(id)arg1;
- (int)_keyboardUIMode;
- (void)_setInsertionPasteboard:(id)arg1;
- (void)_selectionChanged;
- (struct Frame *)_mainCoreFrame;
- (id)_selectedOrMainFrame;
- (BOOL)_needsOneShotDrawingSynchronization;
- (void)_setNeedsOneShotDrawingSynchronization:(BOOL)arg1;
- (BOOL)_syncCompositingChanges;
- (void)_scheduleCompositingLayerSync;
- (void)_enterFullscreenForNode:(struct Node *)arg1;
- (void)_exitFullscreen;
- (BOOL)_supportsFullScreenForElement:(const struct Element *)arg1 withKeyboard:(BOOL)arg2;
- (void)_enterFullScreenForElement:(struct Element *)arg1;
- (void)_exitFullScreenForElement:(struct Element *)arg1;
- (void)_fullScreenRendererChanged:(struct RenderBox *)arg1;
- (float)_deviceScaleFactor;
- (id)_focusedFrame;
- (BOOL)_isLoading;
- (id)_frameViewAtWindowPoint:(struct CGPoint)arg1;
- (BOOL)_continuousCheckingAllowed;
- (id)_responderForResponderOperations;
- (void)_openFrameInNewWindowFromMenu:(id)arg1;
- (void)_searchWithGoogleFromMenu:(id)arg1;
- (void)_searchWithSpotlightFromMenu:(id)arg1;
- (void)_clearLayerSyncLoopObserver;
- (void)_insertNewlineInQuotedContent;
- (void)_replaceSelectionWithNode:(id)arg1 matchStyle:(BOOL)arg2;
- (BOOL)_selectionIsCaret;
- (BOOL)_selectionIsAll;
- (void)_performResponderOperation:(SEL)arg1 with:(id)arg2;
- (void)alignCenter:(id)arg1;
- (void)alignJustified:(id)arg1;
- (void)alignLeft:(id)arg1;
- (void)alignRight:(id)arg1;
- (void)capitalizeWord:(id)arg1;
- (void)centerSelectionInVisibleArea:(id)arg1;
- (void)changeAttributes:(id)arg1;
- (void)changeBaseWritingDirection:(id)arg1;
- (void)changeBaseWritingDirectionToLTR:(id)arg1;
- (void)changeBaseWritingDirectionToRTL:(id)arg1;
- (void)changeColor:(id)arg1;
- (void)changeDocumentBackgroundColor:(id)arg1;
- (void)changeFont:(id)arg1;
- (void)changeSpelling:(id)arg1;
- (void)checkSpelling:(id)arg1;
- (void)complete:(id)arg1;
- (void)copy:(id)arg1;
- (void)copyFont:(id)arg1;
- (void)cut:(id)arg1;
- (void)delete:(id)arg1;
- (void)deleteBackward:(id)arg1;
- (void)deleteBackwardByDecomposingPreviousCharacter:(id)arg1;
- (void)deleteForward:(id)arg1;
- (void)deleteToBeginningOfLine:(id)arg1;
- (void)deleteToBeginningOfParagraph:(id)arg1;
- (void)deleteToEndOfLine:(id)arg1;
- (void)deleteToEndOfParagraph:(id)arg1;
- (void)deleteToMark:(id)arg1;
- (void)deleteWordBackward:(id)arg1;
- (void)deleteWordForward:(id)arg1;
- (void)ignoreSpelling:(id)arg1;
- (void)indent:(id)arg1;
- (void)insertBacktab:(id)arg1;
- (void)insertLineBreak:(id)arg1;
- (void)insertNewline:(id)arg1;
- (void)insertNewlineIgnoringFieldEditor:(id)arg1;
- (void)insertParagraphSeparator:(id)arg1;
- (void)insertTab:(id)arg1;
- (void)insertTabIgnoringFieldEditor:(id)arg1;
- (void)lowercaseWord:(id)arg1;
- (void)makeBaseWritingDirectionLeftToRight:(id)arg1;
- (void)makeBaseWritingDirectionRightToLeft:(id)arg1;
- (void)makeTextWritingDirectionLeftToRight:(id)arg1;
- (void)makeTextWritingDirectionNatural:(id)arg1;
- (void)makeTextWritingDirectionRightToLeft:(id)arg1;
- (void)moveBackward:(id)arg1;
- (void)moveBackwardAndModifySelection:(id)arg1;
- (void)moveDown:(id)arg1;
- (void)moveDownAndModifySelection:(id)arg1;
- (void)moveForward:(id)arg1;
- (void)moveForwardAndModifySelection:(id)arg1;
- (void)moveLeft:(id)arg1;
- (void)moveLeftAndModifySelection:(id)arg1;
- (void)moveParagraphBackwardAndModifySelection:(id)arg1;
- (void)moveParagraphForwardAndModifySelection:(id)arg1;
- (void)moveRight:(id)arg1;
- (void)moveRightAndModifySelection:(id)arg1;
- (void)moveToBeginningOfDocument:(id)arg1;
- (void)moveToBeginningOfDocumentAndModifySelection:(id)arg1;
- (void)moveToBeginningOfLine:(id)arg1;
- (void)moveToBeginningOfLineAndModifySelection:(id)arg1;
- (void)moveToBeginningOfParagraph:(id)arg1;
- (void)moveToBeginningOfParagraphAndModifySelection:(id)arg1;
- (void)moveToBeginningOfSentence:(id)arg1;
- (void)moveToBeginningOfSentenceAndModifySelection:(id)arg1;
- (void)moveToEndOfDocument:(id)arg1;
- (void)moveToEndOfDocumentAndModifySelection:(id)arg1;
- (void)moveToEndOfLine:(id)arg1;
- (void)moveToEndOfLineAndModifySelection:(id)arg1;
- (void)moveToEndOfParagraph:(id)arg1;
- (void)moveToEndOfParagraphAndModifySelection:(id)arg1;
- (void)moveToEndOfSentence:(id)arg1;
- (void)moveToEndOfSentenceAndModifySelection:(id)arg1;
- (void)moveToLeftEndOfLine:(id)arg1;
- (void)moveToLeftEndOfLineAndModifySelection:(id)arg1;
- (void)moveToRightEndOfLine:(id)arg1;
- (void)moveToRightEndOfLineAndModifySelection:(id)arg1;
- (void)moveUp:(id)arg1;
- (void)moveUpAndModifySelection:(id)arg1;
- (void)moveWordBackward:(id)arg1;
- (void)moveWordBackwardAndModifySelection:(id)arg1;
- (void)moveWordForward:(id)arg1;
- (void)moveWordForwardAndModifySelection:(id)arg1;
- (void)moveWordLeft:(id)arg1;
- (void)moveWordLeftAndModifySelection:(id)arg1;
- (void)moveWordRight:(id)arg1;
- (void)moveWordRightAndModifySelection:(id)arg1;
- (void)outdent:(id)arg1;
- (void)orderFrontSubstitutionsPanel:(id)arg1;
- (void)pageDown:(id)arg1;
- (void)pageDownAndModifySelection:(id)arg1;
- (void)pageUp:(id)arg1;
- (void)pageUpAndModifySelection:(id)arg1;
- (void)paste:(id)arg1;
- (void)pasteAsPlainText:(id)arg1;
- (void)pasteAsRichText:(id)arg1;
- (void)pasteFont:(id)arg1;
- (void)performFindPanelAction:(id)arg1;
- (void)scrollLineDown:(id)arg1;
- (void)scrollLineUp:(id)arg1;
- (void)scrollPageDown:(id)arg1;
- (void)scrollPageUp:(id)arg1;
- (void)scrollToBeginningOfDocument:(id)arg1;
- (void)scrollToEndOfDocument:(id)arg1;
- (void)selectAll:(id)arg1;
- (void)selectLine:(id)arg1;
- (void)selectParagraph:(id)arg1;
- (void)selectSentence:(id)arg1;
- (void)selectToMark:(id)arg1;
- (void)selectWord:(id)arg1;
- (void)setMark:(id)arg1;
- (void)showGuessPanel:(id)arg1;
- (void)startSpeaking:(id)arg1;
- (void)stopSpeaking:(id)arg1;
- (void)subscript:(id)arg1;
- (void)superscript:(id)arg1;
- (void)swapWithMark:(id)arg1;
- (void)takeFindStringFromSelection:(id)arg1;
- (void)toggleBaseWritingDirection:(id)arg1;
- (void)transpose:(id)arg1;
- (void)underline:(id)arg1;
- (void)unscript:(id)arg1;
- (void)uppercaseWord:(id)arg1;
- (void)yank:(id)arg1;
- (void)yankAndSelect:(id)arg1;
- (void)insertText:(id)arg1;
- (void)replaceSelectionWithNode:(id)arg1;
- (void)replaceSelectionWithText:(id)arg1;
- (void)replaceSelectionWithMarkupString:(id)arg1;
- (void)replaceSelectionWithArchive:(id)arg1;
- (void)deleteSelection;
- (void)applyStyle:(id)arg1;
- (BOOL)isAutomaticQuoteSubstitutionEnabled;
- (BOOL)isAutomaticLinkDetectionEnabled;
- (BOOL)isAutomaticDashSubstitutionEnabled;
- (BOOL)isAutomaticTextReplacementEnabled;
- (BOOL)isAutomaticSpellingCorrectionEnabled;
- (void)setAutomaticQuoteSubstitutionEnabled:(BOOL)arg1;
- (void)toggleAutomaticQuoteSubstitution:(id)arg1;
- (void)setAutomaticLinkDetectionEnabled:(BOOL)arg1;
- (void)toggleAutomaticLinkDetection:(id)arg1;
- (void)setAutomaticDashSubstitutionEnabled:(BOOL)arg1;
- (void)toggleAutomaticDashSubstitution:(id)arg1;
- (void)setAutomaticTextReplacementEnabled:(BOOL)arg1;
- (void)toggleAutomaticTextReplacement:(id)arg1;
- (void)setAutomaticSpellingCorrectionEnabled:(BOOL)arg1;
- (void)toggleAutomaticSpellingCorrection:(id)arg1;
- (void)handleCorrectionPanelResult:(id)arg1;
- (BOOL)isGrammarCheckingEnabled;
- (void)setGrammarCheckingEnabled:(BOOL)arg1;
- (void)toggleGrammarChecking:(id)arg1;
- (id)editableDOMRangeForPoint:(struct CGPoint)arg1;
- (BOOL)_shouldChangeSelectedDOMRange:(id)arg1 toDOMRange:(id)arg2 affinity:(unsigned long long)arg3 stillSelecting:(BOOL)arg4;
- (BOOL)maintainsInactiveSelection;
- (void)setSelectedDOMRange:(id)arg1 affinity:(unsigned long long)arg2;
- (id)selectedDOMRange;
- (unsigned long long)selectionAffinity;
- (void)setEditable:(BOOL)arg1;
- (BOOL)isEditable;
- (void)setTypingStyle:(id)arg1;
- (id)typingStyle;
- (void)setSmartInsertDeleteEnabled:(BOOL)arg1;
- (BOOL)smartInsertDeleteEnabled;
- (void)setContinuousSpellCheckingEnabled:(BOOL)arg1;
- (BOOL)isContinuousSpellCheckingEnabled;
- (long long)spellCheckerDocumentTag;
- (id)undoManager;
- (void)registerForEditingDelegateNotification:(id)arg1 selector:(SEL)arg2;
- (void)setEditingDelegate:(id)arg1;
- (id)editingDelegate;
- (id)styleDeclarationWithText:(id)arg1;
- (id)computedStyleForElement:(id)arg1 pseudoElement:(id)arg2;
- (void)addObserver:(id)arg1 forKeyPath:(id)arg2 options:(unsigned long long)arg3 context:(void *)arg4;
- (void)removeObserver:(id)arg1 forKeyPath:(id)arg2;
- (float)_headerHeight;
- (float)_footerHeight;
- (void)_drawHeaderInRect:(struct CGRect)arg1;
- (void)_drawFooterInRect:(struct CGRect)arg1;
- (void)_adjustPrintingMarginsForHeaderAndFooter;
- (void)_drawHeaderAndFooter;
- (void)scheduleInRunLoop:(id)arg1 forMode:(id)arg2;
- (void)unscheduleFromRunLoop:(id)arg1 forMode:(id)arg2;
- (BOOL)findString:(id)arg1 options:(unsigned long long)arg2;
- (void)setHoverFeedbackSuspended:(BOOL)arg1;
- (BOOL)isHoverFeedbackSuspended;
- (void)setMainFrameDocumentReady:(BOOL)arg1;
- (id)_frameForCurrentSelection;
- (void)setTabKeyCyclesThroughElements:(BOOL)arg1;
- (BOOL)tabKeyCyclesThroughElements;
- (void)setScriptDebugDelegate:(id)arg1;
- (id)scriptDebugDelegate;
- (void)setHistoryDelegate:(id)arg1;
- (id)historyDelegate;
- (BOOL)shouldClose;
- (id)aeDescByEvaluatingJavaScriptFromString:(id)arg1;
- (BOOL)canMarkAllTextMatches;
- (unsigned long long)countMatchesForText:(id)arg1 options:(unsigned long long)arg2 highlight:(BOOL)arg3 limit:(unsigned long long)arg4 markMatches:(BOOL)arg5;
- (unsigned long long)countMatchesForText:(id)arg1 inDOMRange:(id)arg2 options:(unsigned long long)arg3 highlight:(BOOL)arg4 limit:(unsigned long long)arg5 markMatches:(BOOL)arg6;
- (void)unmarkAllTextMatches;
- (id)rectsForTextMatches;
- (void)scrollDOMRangeToVisible:(id)arg1;
- (BOOL)allowsUndo;
- (void)setAllowsUndo:(BOOL)arg1;
- (void)setPageSizeMultiplier:(float)arg1;
- (float)pageSizeMultiplier;
- (BOOL)canZoomPageIn;
- (void)zoomPageIn:(id)arg1;
- (BOOL)canZoomPageOut;
- (void)zoomPageOut:(id)arg1;
- (BOOL)canResetPageZoom;
- (void)resetPageZoom:(id)arg1;
- (void)setMediaVolume:(float)arg1;
- (float)mediaVolume;
- (void)addVisitedLinks:(id)arg1;
- (void)takeStringURLFrom:(id)arg1;
- (BOOL)canGoBack;
- (BOOL)canGoForward;
- (void)goBack:(id)arg1;
- (void)goForward:(id)arg1;
- (void)stopLoading:(id)arg1;
- (void)reload:(id)arg1;
- (void)reloadFromOrigin:(id)arg1;
- (BOOL)canMakeTextSmaller;
- (void)makeTextSmaller:(id)arg1;
- (BOOL)canMakeTextLarger;
- (void)makeTextLarger:(id)arg1;
- (BOOL)canMakeTextStandardSize;
- (void)makeTextStandardSize:(id)arg1;
- (void)toggleSmartInsertDelete:(id)arg1;
- (void)toggleContinuousSpellChecking:(id)arg1;
- (BOOL)_responderValidateUserInterfaceItem:(id)arg1;
- (BOOL)validateUserInterfaceItemWithoutDelegate:(id)arg1;
- (BOOL)validateUserInterfaceItem:(id)arg1;
- (void)_dispatchPendingLoadRequests;
- (void)_registerDraggedTypes;
- (BOOL)_usesDocumentViews;
- (void)_injectMailQuirksScript;
- (void)_injectOutlookQuirksScript;
- (void)_injectSolarWalkQuirksScript;
- (void)_commonInitializationWithFrameName:(id)arg1 groupName:(id)arg2 usesDocumentViews:(BOOL)arg3;
- (id)_initWithFrame:(struct CGRect)arg1 frameName:(id)arg2 groupName:(id)arg3 usesDocumentViews:(BOOL)arg4;
- (BOOL)_mustDrawUnionedRect:(struct CGRect)arg1 singleRects:(const struct CGRect *)arg2 count:(long long)arg3;
- (void)drawSingleRect:(struct CGRect)arg1;
- (BOOL)isFlipped;
- (void)setFrameSize:(struct CGSize)arg1;
- (void)_viewWillDrawInternal;
- (void)viewWillDraw;
- (void)drawRect:(struct CGRect)arg1;
- (BOOL)_viewClass:(Class *)arg1 andRepresentationClass:(Class *)arg2 forMIMEType:(id)arg3;
- (BOOL)_isClosed;
- (void)_closePluginDatabases;
- (void)_closeWithFastTeardown;
- (void)_close;
- (BOOL)_isProcessingUserGesture;
- (id)_downloadURL:(id)arg1;
- (id)_openNewWindowWithRequest:(id)arg1;
- (id)inspector;
- (struct Page *)page;
- (id)_menuForElement:(id)arg1 defaultItems:(id)arg2;
- (void)_mouseDidMoveOverElement:(id)arg1 modifierFlags:(unsigned long long)arg2;
- (void)_loadBackForwardListFromOtherView:(id)arg1;
- (void)_setFormDelegate:(id)arg1;
- (id)_formDelegate;
- (BOOL)_needsAdobeFrameReloadingQuirk;
- (BOOL)_needsLinkElementTextCSSQuirk;
- (BOOL)_needsKeyboardEventDisambiguationQuirks;
- (BOOL)_needsFrameLoadDelegateRetainQuirk;
- (BOOL)_needsPreHTML5ParserQuirks;
- (BOOL)_needsUnrestrictedGetMatchedCSSRules;
- (void)_preferencesChangedNotification:(id)arg1;
- (void)_preferencesChanged:(id)arg1;
- (void)_cacheResourceLoadDelegateImplementations;
- (void)_cacheFrameLoadDelegateImplementations;
- (void)_cacheScriptDebugDelegateImplementations;
- (void)_cacheHistoryDelegateImplementations;
- (id)_policyDelegateForwarder;
- (id)_UIDelegateForwarder;
- (id)_editingDelegateForwarder;
- (void)_closeWindow;
- (void)_pushPerformingProgrammaticFocus;
- (void)_popPerformingProgrammaticFocus;
- (BOOL)_isPerformingProgrammaticFocus;
- (void)_didChangeValueForKey:(id)arg1;
- (void)_willChangeValueForKey:(id)arg1;
- (id)_declaredKeys;
- (void)setObservationInfo:(void *)arg1;
- (void *)observationInfo;
- (void)_willChangeBackForwardKeys;
- (void)_didChangeBackForwardKeys;
- (void)_didStartProvisionalLoadForFrame:(id)arg1;
- (void)_didCommitLoadForFrame:(id)arg1;
- (void)_didFinishLoadForFrame:(id)arg1;
- (void)_didFailLoadWithError:(id)arg1 forFrame:(id)arg2;
- (void)_didFailProvisionalLoadWithError:(id)arg1 forFrame:(id)arg2;
- (id)_cachedResponseForURL:(id)arg1;
- (void)_writeImageForElement:(id)arg1 withPasteboardTypes:(id)arg2 toPasteboard:(id)arg3;
- (void)_writeLinkElement:(id)arg1 withPasteboardTypes:(id)arg2 toPasteboard:(id)arg3;
- (void)_setInitiatedDrag:(BOOL)arg1;
- (void)_addControlRect:(struct CGRect)arg1 clip:(struct CGRect)arg2 fromView:(id)arg3 toDashboardRegions:(id)arg4;
- (void)_addScrollerDashboardRegionsForFrameView:(struct FrameView *)arg1 dashboardRegions:(id)arg2;
- (void)_addScrollerDashboardRegions:(id)arg1 from:(id)arg2;
- (void)_addScrollerDashboardRegions:(id)arg1;
- (id)_dashboardRegions;
- (void)_setDashboardBehavior:(int)arg1 to:(BOOL)arg2;
- (BOOL)_dashboardBehavior:(int)arg1;
/*POINT*/- (void)setAlwaysShowVerticalScroller:(BOOL)arg1;
/*POINT*/- (BOOL)alwaysShowVerticalScroller;
/*POINT*/- (void)setAlwaysShowHorizontalScroller:(BOOL)arg1;
- (void)setProhibitsMainFrameScrolling:(BOOL)arg1;
/*POINT*/- (BOOL)alwaysShowHorizontalScroller;
- (void)_setInViewSourceMode:(BOOL)arg1;
- (BOOL)_inViewSourceMode;
- (void)_setUseFastImageScalingMode:(BOOL)arg1;
- (BOOL)_inFastImageScalingMode;
- (BOOL)_cookieEnabled;
- (void)_setCookieEnabled:(BOOL)arg1;
- (void)_setAdditionalWebPlugInPaths:(id)arg1;
- (void)_attachScriptDebuggerToAllFrames;
- (void)_detachScriptDebuggerFromAllFrames;
- (void)setBackgroundColor:(id)arg1;
- (id)backgroundColor;
- (BOOL)defersCallbacks;
- (void)setDefersCallbacks:(BOOL)arg1;
- (BOOL)usesPageCache;
- (void)setUsesPageCache:(BOOL)arg1;
- (id)_globalHistoryItem;
- (void)_setGlobalHistoryItem:(struct HistoryItem *)arg1;
- (id)textIteratorForRect:(struct CGRect)arg1;
- (void)handleAuthenticationForResource:(id)arg1 challenge:(id)arg2 fromDataSource:(id)arg3;
- (void)_clearUndoRedoOperations;
- (void)_setCatchesDelegateExceptions:(BOOL)arg1;
- (BOOL)_catchesDelegateExceptions;
- (void)_executeCoreCommandByName:(id)arg1 value:(id)arg2;
- (void)_setCustomHTMLTokenizerTimeDelay:(double)arg1;
- (void)_setCustomHTMLTokenizerChunkSize:(int)arg1;
- (void)_clearMainFrameName;
- (void)setSelectTrailingWhitespaceEnabled:(BOOL)arg1;
- (BOOL)isSelectTrailingWhitespaceEnabled;
- (void)setMemoryCacheDelegateCallsEnabled:(BOOL)arg1;
- (BOOL)areMemoryCacheDelegateCallsEnabled;
- (void)_setJavaScriptURLsAreAllowed:(BOOL)arg1;
- (BOOL)_postsAcceleratedCompositingNotifications;
- (void)_setPostsAcceleratedCompositingNotifications:(BOOL)arg1;
- (BOOL)_isUsingAcceleratedCompositing;
- (void)_setBaseCTM:(struct CGAffineTransform)arg1 forContext:(struct CGContext *)arg2;
- (BOOL)interactiveFormValidationEnabled;
- (void)setInteractiveFormValidationEnabled:(BOOL)arg1;
- (int)validationMessageTimerMagnification;
- (void)setValidationMessageTimerMagnification:(int)arg1;
- (BOOL)_isSoftwareRenderable;
- (void)_setIncludesFlattenedCompositingLayersWhenDrawingToBitmap:(BOOL)arg1;
- (BOOL)_includesFlattenedCompositingLayersWhenDrawingToBitmap;
- (id)_insertionPasteboard;
- (void)_updateActiveState;
- (BOOL)cssAnimationsSuspended;
- (void)setCSSAnimationsSuspended:(BOOL)arg1;
- (void)_scaleWebView:(float)arg1 atOrigin:(struct CGPoint)arg2;
- (float)_viewScaleFactor;
- (void)_setUseFixedLayout:(BOOL)arg1;
- (void)_setFixedLayoutSize:(struct CGSize)arg1;
- (BOOL)_useFixedLayout;
- (struct CGSize)_fixedLayoutSize;
- (double)_backingScaleFactor;
- (void)_setCustomBackingScaleFactor:(double)arg1;
- (unsigned long long)markAllMatchesForText:(id)arg1 caseSensitive:(BOOL)arg2 highlight:(BOOL)arg3 limit:(unsigned long long)arg4;
- (unsigned long long)countMatchesForText:(id)arg1 caseSensitive:(BOOL)arg2 highlight:(BOOL)arg3 limit:(unsigned long long)arg4 markMatches:(BOOL)arg5;
- (BOOL)searchFor:(id)arg1 direction:(BOOL)arg2 caseSensitive:(BOOL)arg3 wrap:(BOOL)arg4 startInSelection:(BOOL)arg5;
- (void)_setMinimumTimerInterval:(double)arg1;
- (void)_removeFromAllWebViewsSet;
- (void)_addToAllWebViewsSet;
- (void)_closingEventHandling;
- (void)_setMouseDownEvent:(id)arg1;
- (void)mouseDown:(id)arg1;
- (void)mouseUp:(id)arg1;
- (void)_updateMouseoverWithFakeEvent;
- (void)_cancelUpdateMouseoverTimer;
- (void)_stopAutoscrollTimer;
- (void)_setToolTip:(id)arg1;

@end


@interface ScrollbarPainterDelegate : NSObject <NSAnimationDelegate>
{
    ScrollAnimatorMac_490dd4ed *_animator;	// 13869736 = 0xd3a2a8
    RetainPtr_9b334399 _verticalKnobAnimation;	// 13869744 = 0xd3a2b0
    RetainPtr_9b334399 _horizontalKnobAnimation;	// 13869752 = 0xd3a2b8
    RetainPtr_9b334399 _verticalTrackAnimation;	// 13869760 = 0xd3a2c0
    RetainPtr_9b334399 _horizontalTrackAnimation;	// 13869768 = 0xd3a2c8
    RetainPtr_9b334399 _verticalUIStateTransitionAnimation;	// 13869776 = 0xd3a2d0
    RetainPtr_9b334399 _horizontalUIStateTransitionAnimation;	// 13869784 = 0xd3a2d8
}

- (id)initWithScrollAnimator:(struct ScrollAnimatorMac *)arg1;
- (void)cancelAnimations;
- (struct CGRect)convertRectToBacking:(struct CGRect)arg1;
- (struct CGRect)convertRectFromBacking:(struct CGRect)arg1;
- (id)layer;
- (struct CGPoint)mouseLocationInScrollerForScrollerImp:(id)arg1;
/*POINT*/- (void)setUpAlphaAnimation:(RetainPtr_9b334399 *)arg1 scrollerPainter:(id)arg2 part:(int)arg3 animateAlphaTo:(double)arg4 duration:(double)arg5;
/*POINT*/- (void)scrollerImp:(id)arg1 animateKnobAlphaTo:(double)arg2 duration:(double)arg3;
/*POINT*/- (void)scrollerImp:(id)arg1 animateTrackAlphaTo:(double)arg2 duration:(double)arg3;
/*POINT*/- (void)scrollerImp:(id)arg1 animateUIStateTransitionWithDuration:(double)arg2;
/*POINT*/- (void)scrollerImp:(id)arg1 overlayScrollerStateChangedTo:(unsigned long long)arg2;
- (void)scrollAnimatorDestroyed;
- (id).cxx_construct;
- (void).cxx_destruct;

@end


@interface WebFrameView : NSView <WebCoreFrameView>
{
    WebFrameViewPrivate *_private;	// 1660800 = 0x195780
}

+ (id)_viewTypesAllowImageTypeOmission:(BOOL)arg1;
+ (BOOL)_canShowMIMETypeAsHTML:(id)arg1;
+ (Class)_viewClassForMIMEType:(id)arg1 allowingPlugins:(BOOL)arg2;
- (id)initWithFrame:(struct CGRect)arg1;
- (void)dealloc;
- (void)finalize;
- (id)webFrame;
- (void)setAllowsScrolling:(BOOL)arg1;
- (BOOL)allowsScrolling;
- (id)documentView;
- (BOOL)acceptsFirstResponder;
- (BOOL)becomeFirstResponder;
- (void)setNextKeyView:(id)arg1;
- (BOOL)isOpaque;
- (void)drawRect:(struct CGRect)arg1;
- (struct CGRect)visibleRect;
- (void)setFrameSize:(struct CGSize)arg1;
- (void)setBoundsSize:(struct CGSize)arg1;
- (void)viewDidMoveToWindow;
- (BOOL)_scrollOverflowInDirection:(int)arg1 granularity:(int)arg2;
- (BOOL)_isVerticalDocument;
- (BOOL)_isFlippedDocument;
- (BOOL)_scrollToBeginningOfDocument;
- (BOOL)_scrollToEndOfDocument;
- (void)scrollToBeginningOfDocument:(id)arg1;
- (void)scrollToEndOfDocument:(id)arg1;
- (void)_goBack;
- (void)_goForward;
- (BOOL)_scrollVerticallyBy:(float)arg1;
- (BOOL)_scrollHorizontallyBy:(float)arg1;
- (float)_horizontalKeyboardScrollDistance;
- (float)_horizontalPageScrollDistance;
- (BOOL)_pageVertically:(BOOL)arg1;
- (BOOL)_pageHorizontally:(BOOL)arg1;
- (BOOL)_pageInBlockProgressionDirection:(BOOL)arg1;
- (BOOL)_scrollLineVertically:(BOOL)arg1;
- (BOOL)_scrollLineHorizontally:(BOOL)arg1;
- (void)scrollPageUp:(id)arg1;
- (void)scrollPageDown:(id)arg1;
- (void)scrollLineUp:(id)arg1;
- (void)scrollLineDown:(id)arg1;
- (BOOL)_firstResponderIsFormControl;
- (void)keyDown:(id)arg1;
- (id)_webcore_effectiveFirstResponder;
- (BOOL)canPrintHeadersAndFooters;
- (id)printOperationWithPrintInfo:(id)arg1;
- (BOOL)documentViewShouldHandlePrint;
- (void)printDocumentView;
- (float)_area;
- (BOOL)_isScrollable;
- (id)_largestScrollableChild;
- (BOOL)_hasScrollBars;
- (id)_largestChildWithScrollBars;
- (id)_contentView;
- (Class)_customScrollViewClass;
- (void)_setCustomScrollViewClass:(Class)arg1;
- (id)_webView;
- (void)_setDocumentView:(id)arg1;
- (id)_makeDocumentViewForDataSource:(id)arg1;
- (void)_setWebFrame:(id)arg1;
- (id)_scrollView;
- (float)_verticalPageScrollDistance;
- (Class)_viewClassForMIMEType:(id)arg1;
- (void)_install;
- (float)_verticalKeyboardScrollDistance;
- (struct Frame *)_web_frame;

@end


@interface WebCoreScrollView : NSScrollView
{
}

@end


// Not exported
@interface ScrollbarPartAnimation : NSAnimation
{
    struct RetainPtr<objc_object*> _scrollerPainter;	// 13870304 = 0xd3a4e0
    int _featureToAnimate;	// 13870312 = 0xd3a4e8
    ScrollAnimatorMac_490dd4ed *_animator;	// 13870320 = 0xd3a4f0
    double _startValue;	// 13867952 = 0xd39bb0
    double _endValue;	// 13867960 = 0xd39bb8
}

- (id)initWithScrollbarPainter:(id)arg1 animate:(int)arg2 scrollAnimator:(struct ScrollAnimatorMac *)arg3 animateFrom:(double)arg4 animateTo:(double)arg5 duration:(double)arg6;
- (void)setScrollbarPainter:(id)arg1;
- (void)setStartValue:(double)arg1;
- (void)setEndValue:(double)arg1;
- (void)setCurrentProgress:(float)arg1;
- (void)scrollAnimatorDestroyed;
- (id).cxx_construct;
- (void).cxx_destruct;

@end


// Not exported
@interface ScrollbarPainterControllerDelegate : NSObject
{
    ScrollAnimatorMac_490dd4ed *_animator;	// 13867944 = 0xd39ba8
}

- (id)initWithScrollAnimator:(struct ScrollAnimatorMac *)arg1;
- (void)scrollAnimatorDestroyed;
- (struct CGRect)contentAreaRectForScrollerImpPair:(id)arg1;
- (BOOL)inLiveResizeForScrollerImpPair:(id)arg1;
- (struct CGPoint)mouseLocationInContentAreaForScrollerImpPair:(id)arg1;
- (struct CGPoint)scrollerImpPair:(id)arg1 convertContentPoint:(struct CGPoint)arg2 toScrollerImp:(id)arg3;
- (void)scrollerImpPair:(id)arg1 setContentAreaNeedsDisplayInRect:(struct CGRect)arg2;
- (void)scrollerImpPair:(id)arg1 updateScrollerStyleForNewRecommendedScrollerStyle:(long long)arg2;

@end


@interface WKView : NSView <NSTextInputClient>
{
    WKViewData *_data;	// 1810352 = 0x1b9fb0
    unsigned int _frameSizeUpdatesDisabledCount;	// 1810336 = 0x1b9fa0
}

- (id)initWithFrame:(struct CGRect)arg1;
- (id)initWithFrame:(struct CGRect)arg1 contextRef:(struct OpaqueWKContext *)arg2;
- (void)_registerDraggedTypes;
- (void)_updateRemoteAccessibilityRegistration:(BOOL)arg1;
- (id)initWithFrame:(struct CGRect)arg1 contextRef:(struct OpaqueWKContext *)arg2 pageGroupRef:(struct OpaqueWKPageGroup *)arg3;
- (void)dealloc;
@property(readonly) struct OpaqueWKPage *pageRef;
@property BOOL drawsBackground;
@property BOOL drawsTransparentBackground;
- (BOOL)acceptsFirstResponder;
- (BOOL)becomeFirstResponder;
- (BOOL)resignFirstResponder;
- (void)viewWillStartLiveResize;
- (void)viewDidEndLiveResize;
- (BOOL)isFlipped;
- (void)setFrame:(struct CGRect)arg1 andScrollBy:(struct CGSize)arg2;
- (void)setFrameSize:(struct CGSize)arg1;
- (void)_updateWindowAndViewFrames;
- (void)renewGState;
- (void)alignCenter:(id)arg1;
- (void)alignJustified:(id)arg1;
- (void)alignLeft:(id)arg1;
- (void)alignRight:(id)arg1;
- (void)copy:(id)arg1;
- (void)cut:(id)arg1;
- (void)delete:(id)arg1;
- (void)deleteBackward:(id)arg1;
- (void)deleteBackwardByDecomposingPreviousCharacter:(id)arg1;
- (void)deleteForward:(id)arg1;
- (void)deleteToBeginningOfLine:(id)arg1;
- (void)deleteToBeginningOfParagraph:(id)arg1;
- (void)deleteToEndOfLine:(id)arg1;
- (void)deleteToEndOfParagraph:(id)arg1;
- (void)deleteToMark:(id)arg1;
- (void)deleteWordBackward:(id)arg1;
- (void)deleteWordForward:(id)arg1;
- (void)ignoreSpelling:(id)arg1;
- (void)indent:(id)arg1;
- (void)insertBacktab:(id)arg1;
- (void)insertLineBreak:(id)arg1;
- (void)insertNewline:(id)arg1;
- (void)insertNewlineIgnoringFieldEditor:(id)arg1;
- (void)insertParagraphSeparator:(id)arg1;
- (void)insertTab:(id)arg1;
- (void)insertTabIgnoringFieldEditor:(id)arg1;
- (void)makeTextWritingDirectionLeftToRight:(id)arg1;
- (void)makeTextWritingDirectionNatural:(id)arg1;
- (void)makeTextWritingDirectionRightToLeft:(id)arg1;
- (void)moveBackward:(id)arg1;
- (void)moveBackwardAndModifySelection:(id)arg1;
- (void)moveDown:(id)arg1;
- (void)moveDownAndModifySelection:(id)arg1;
- (void)moveForward:(id)arg1;
- (void)moveForwardAndModifySelection:(id)arg1;
- (void)moveLeft:(id)arg1;
- (void)moveLeftAndModifySelection:(id)arg1;
- (void)moveParagraphBackwardAndModifySelection:(id)arg1;
- (void)moveParagraphForwardAndModifySelection:(id)arg1;
- (void)moveRight:(id)arg1;
- (void)moveRightAndModifySelection:(id)arg1;
- (void)moveToBeginningOfDocument:(id)arg1;
- (void)moveToBeginningOfDocumentAndModifySelection:(id)arg1;
- (void)moveToBeginningOfLine:(id)arg1;
- (void)moveToBeginningOfLineAndModifySelection:(id)arg1;
- (void)moveToBeginningOfParagraph:(id)arg1;
- (void)moveToBeginningOfParagraphAndModifySelection:(id)arg1;
- (void)moveToBeginningOfSentence:(id)arg1;
- (void)moveToBeginningOfSentenceAndModifySelection:(id)arg1;
- (void)moveToEndOfDocument:(id)arg1;
- (void)moveToEndOfDocumentAndModifySelection:(id)arg1;
- (void)moveToEndOfLine:(id)arg1;
- (void)moveToEndOfLineAndModifySelection:(id)arg1;
- (void)moveToEndOfParagraph:(id)arg1;
- (void)moveToEndOfParagraphAndModifySelection:(id)arg1;
- (void)moveToEndOfSentence:(id)arg1;
- (void)moveToEndOfSentenceAndModifySelection:(id)arg1;
- (void)moveToLeftEndOfLine:(id)arg1;
- (void)moveToLeftEndOfLineAndModifySelection:(id)arg1;
- (void)moveToRightEndOfLine:(id)arg1;
- (void)moveToRightEndOfLineAndModifySelection:(id)arg1;
- (void)moveUp:(id)arg1;
- (void)moveUpAndModifySelection:(id)arg1;
- (void)moveWordBackward:(id)arg1;
- (void)moveWordBackwardAndModifySelection:(id)arg1;
- (void)moveWordForward:(id)arg1;
- (void)moveWordForwardAndModifySelection:(id)arg1;
- (void)moveWordLeft:(id)arg1;
- (void)moveWordLeftAndModifySelection:(id)arg1;
- (void)moveWordRight:(id)arg1;
- (void)moveWordRightAndModifySelection:(id)arg1;
- (void)outdent:(id)arg1;
- (void)pageDown:(id)arg1;
- (void)pageDownAndModifySelection:(id)arg1;
- (void)pageUp:(id)arg1;
- (void)pageUpAndModifySelection:(id)arg1;
- (void)paste:(id)arg1;
- (void)pasteAsPlainText:(id)arg1;
- (void)scrollPageDown:(id)arg1;
- (void)scrollPageUp:(id)arg1;
- (void)scrollToBeginningOfDocument:(id)arg1;
- (void)scrollToEndOfDocument:(id)arg1;
- (void)selectAll:(id)arg1;
- (void)selectLine:(id)arg1;
- (void)selectParagraph:(id)arg1;
- (void)selectSentence:(id)arg1;
- (void)selectToMark:(id)arg1;
- (void)selectWord:(id)arg1;
- (void)setMark:(id)arg1;
- (void)subscript:(id)arg1;
- (void)superscript:(id)arg1;
- (void)swapWithMark:(id)arg1;
- (void)takeFindStringFromSelection:(id)arg1;
- (void)transpose:(id)arg1;
- (void)underline:(id)arg1;
- (void)unscript:(id)arg1;
- (void)yank:(id)arg1;
- (void)yankAndSelect:(id)arg1;
- (BOOL)writeSelectionToPasteboard:(id)arg1 types:(id)arg2;
- (id)validRequestorForSendType:(id)arg1 returnType:(id)arg2;
- (BOOL)readSelectionFromPasteboard:(id)arg1;
- (BOOL)validateUserInterfaceItem:(id)arg1;
- (void)startSpeaking:(id)arg1;
- (void)stopSpeaking:(id)arg1;
- (void)showGuessPanel:(id)arg1;
- (void)checkSpelling:(id)arg1;
- (void)changeSpelling:(id)arg1;
- (void)toggleContinuousSpellChecking:(id)arg1;
- (BOOL)isGrammarCheckingEnabled;
- (void)setGrammarCheckingEnabled:(BOOL)arg1;
- (void)toggleGrammarChecking:(id)arg1;
- (void)toggleAutomaticSpellingCorrection:(id)arg1;
- (void)orderFrontSubstitutionsPanel:(id)arg1;
- (void)toggleSmartInsertDelete:(id)arg1;
- (BOOL)isAutomaticQuoteSubstitutionEnabled;
- (void)setAutomaticQuoteSubstitutionEnabled:(BOOL)arg1;
- (void)toggleAutomaticQuoteSubstitution:(id)arg1;
- (BOOL)isAutomaticDashSubstitutionEnabled;
- (void)setAutomaticDashSubstitutionEnabled:(BOOL)arg1;
- (void)toggleAutomaticDashSubstitution:(id)arg1;
- (BOOL)isAutomaticLinkDetectionEnabled;
- (void)setAutomaticLinkDetectionEnabled:(BOOL)arg1;
- (void)toggleAutomaticLinkDetection:(id)arg1;
- (BOOL)isAutomaticTextReplacementEnabled;
- (void)setAutomaticTextReplacementEnabled:(BOOL)arg1;
- (void)toggleAutomaticTextReplacement:(id)arg1;
- (void)uppercaseWord:(id)arg1;
- (void)lowercaseWord:(id)arg1;
- (void)capitalizeWord:(id)arg1;
- (void)displayIfNeeded;
- (BOOL)_wantsKeyDownForEvent:(id)arg1;
- (void)_setMouseDownEvent:(id)arg1;
- (void)mouseEntered:(id)arg1;
- (void)mouseExited:(id)arg1;
- (void)mouseMovedInternal:(id)arg1;
- (void)mouseDownInternal:(id)arg1;
- (void)mouseUpInternal:(id)arg1;
- (void)mouseDraggedInternal:(id)arg1;
- (void)otherMouseDown:(id)arg1;
- (void)otherMouseDragged:(id)arg1;
- (void)otherMouseMoved:(id)arg1;
- (void)otherMouseUp:(id)arg1;
- (void)rightMouseDown:(id)arg1;
- (void)rightMouseDragged:(id)arg1;
- (void)rightMouseUp:(id)arg1;
- (void)scrollWheel:(id)arg1;
- (void)mouseMoved:(id)arg1;
- (void)mouseDown:(id)arg1;
- (void)mouseUp:(id)arg1;
- (void)mouseDragged:(id)arg1;
- (BOOL)acceptsFirstMouse:(id)arg1;
- (BOOL)shouldDelayWindowOrderingForEvent:(id)arg1;
- (void)shortCircuitedEndGestureWithEvent:(id)arg1;
- (void)beginGestureWithEvent:(id)arg1;
- (void)doCommandBySelector:(SEL)arg1;
- (void)insertText:(id)arg1;
- (void)insertText:(id)arg1 replacementRange:(struct _NSRange)arg2;
- (BOOL)_handleStyleKeyEquivalent:(id)arg1;
- (BOOL)performKeyEquivalent:(id)arg1;
- (void)keyUp:(id)arg1;
- (void)keyDown:(id)arg1;
- (void)flagsChanged:(id)arg1;
- (void)_executeSavedKeypressCommands;
- (void)_notifyInputContextAboutDiscardedComposition;
- (id)inputContext;
- (struct _NSRange)selectedRange;
- (BOOL)hasMarkedText;
- (void)unmarkText;
- (id)validAttributesForMarkedText;
- (void)setMarkedText:(id)arg1 selectedRange:(struct _NSRange)arg2 replacementRange:(struct _NSRange)arg3;
- (struct _NSRange)markedRange;
- (id)attributedSubstringForProposedRange:(struct _NSRange)arg1 actualRange:(struct _NSRange *)arg2;
- (unsigned long long)characterIndexForPoint:(struct CGPoint)arg1;
- (struct CGRect)firstRectForCharacterRange:(struct _NSRange)arg1 actualRange:(struct _NSRange *)arg2;
- (void)draggedImage:(id)arg1 endedAt:(struct CGPoint)arg2 operation:(unsigned long long)arg3;
- (int)applicationFlags:(id)arg1;
- (unsigned long long)draggingEntered:(id)arg1;
- (unsigned long long)draggingUpdated:(id)arg1;
- (void)draggingExited:(id)arg1;
- (BOOL)prepareForDragOperation:(id)arg1;
- (BOOL)performDragOperation:(id)arg1;
- (id)_hitTest:(struct CGPoint *)arg1 dragTypes:(id)arg2;
- (BOOL)_windowResizeMouseLocationIsInVisibleScrollerThumb:(struct CGPoint)arg1;
- (void)_updateWindowVisibility;
- (BOOL)_ownsWindowGrowBox;
- (BOOL)_updateGrowBoxForWindowFrameChange;
- (void)addWindowObserversForWindow:(id)arg1;
- (void)removeWindowObservers;
- (void)viewWillMoveToWindow:(id)arg1;
- (void)viewDidMoveToWindow;
- (void)_windowDidBecomeKey:(id)arg1;
- (void)_windowDidResignKey:(id)arg1;
- (void)_windowDidMiniaturize:(id)arg1;
- (void)_windowDidDeminiaturize:(id)arg1;
- (void)_windowFrameDidChange:(id)arg1;
- (void)_windowDidOrderOffScreen:(id)arg1;
- (void)_windowDidOrderOnScreen:(id)arg1;
- (void)_windowDidChangeBackingProperties:(id)arg1;
- (void)drawRect:(struct CGRect)arg1;
- (BOOL)isOpaque;
- (BOOL)mouseDownCanMoveWindow;
- (void)viewDidHide;
- (void)viewDidUnhide;
- (id)accessibilityFocusedUIElement;
- (BOOL)accessibilityIsIgnored;
- (id)accessibilityHitTest:(struct CGPoint)arg1;
- (id)accessibilityAttributeValue:(id)arg1;
- (id)hitTest:(struct CGPoint)arg1;
- (long long)conversationIdentifier;
- (BOOL)canChangeFrameLayout:(struct OpaqueWKFrame *)arg1;
- (id)printOperationWithPrintInfo:(id)arg1 forFrame:(struct OpaqueWKFrame *)arg2;
- (float)_intrinsicDeviceScaleFactor;
- (void)disableFrameSizeUpdates;
- (void)enableFrameSizeUpdates;
- (BOOL)frameSizeUpdatesDisabled;
- (void)performDictionaryLookupAtCurrentMouseLocation;
- (long long)spellCheckerDocumentTag;
- (void)handleCorrectionPanelResult:(id)arg1;
- (PassOwnPtr_4d2f5da3)_createDrawingAreaProxy;
- (BOOL)_isFocused;
- (void)_processDidCrash;
- (void)_pageClosed;
- (void)_didRelaunchProcess;
- (void)_setCursor:(id)arg1;
- (void)_setUserInterfaceItemState:(id)arg1 enabled:(BOOL)arg2 state:(int)arg3;
- (void)_resendKeyDownEvent:(id)arg1;
- (BOOL)_interpretKeyEvent:(id)arg1 savingCommandsTo:(Vector_81bcae4e *)arg2;
- (struct CGRect)_convertToDeviceSpace:(struct CGRect)arg1;
- (struct CGRect)_convertToUserSpace:(struct CGRect)arg1;
- (long long)addTrackingRect:(struct CGRect)arg1 owner:(id)arg2 userData:(void *)arg3 assumeInside:(BOOL)arg4;
- (long long)_addTrackingRect:(struct CGRect)arg1 owner:(id)arg2 userData:(void *)arg3 assumeInside:(BOOL)arg4 useTrackingNum:(int)arg5;
- (void)_addTrackingRects:(struct CGRect *)arg1 owner:(id)arg2 userDataList:(void **)arg3 assumeInsideList:(char *)arg4 trackingNums:(long long *)arg5 count:(int)arg6;
- (void)removeTrackingRect:(long long)arg1;
- (void)_removeTrackingRects:(long long *)arg1 count:(int)arg2;
- (void)_sendToolTipMouseExited;
- (void)_sendToolTipMouseEntered;
- (id)view:(id)arg1 stringForToolTip:(long long)arg2 point:(struct CGPoint)arg3 userData:(void *)arg4;
- (void)_toolTipChangedFrom:(id)arg1 to:(id)arg2;
- (void)_setFindIndicator:(PassRefPtr_c0ab1a11)arg1 fadeOut:(BOOL)arg2 animate:(BOOL)arg3;
- (void)_enterAcceleratedCompositingMode:(const struct LayerTreeContext *)arg1;
- (void)_exitAcceleratedCompositingMode;
- (void)_setAccessibilityWebProcessToken:(id)arg1;
- (void)_setComplexTextInputEnabled:(BOOL)arg1 pluginComplexTextInputIdentifier:(unsigned long long)arg2;
- (void)_setPageHasCustomRepresentation:(BOOL)arg1;
- (void)_didFinishLoadingDataForCustomRepresentationWithSuggestedFilename:(const struct String *)arg1 dataReference:(const struct DataReference *)arg2;
- (double)_customRepresentationZoomFactor;
- (void)_setCustomRepresentationZoomFactor:(double)arg1;
- (void)_findStringInCustomRepresentation:(id)arg1 withFindOptions:(int)arg2 maxMatchCount:(unsigned long long)arg3;
- (void)_countStringMatchesInCustomRepresentation:(id)arg1 withFindOptions:(int)arg2 maxMatchCount:(unsigned long long)arg3;
- (void)_setDragImage:(id)arg1 at:(struct CGPoint)arg2 linkDrag:(BOOL)arg3;
- (void)_updateSecureInputState;
- (void)_updateTextInputStateIncludingSecureInputState:(BOOL)arg1;
- (void)_resetTextInputState;
- (void)_setDrawingAreaSize:(struct CGSize)arg1;
- (void)_didChangeScrollbarsForMainFrame;
- (id)fullScreenWindowController;
- (void)closeFullScreenWindowController;
- (_Bool)_executeSavedCommandBySelector:(SEL)arg1;
- (void)_cacheWindowBottomCornerRect;

@end



// Not exported
@interface WKViewData : NSObject
{
    struct OwnPtr<WebKit::PageClientImpl> _pageClient;	// 1810368 = 0x1b9fc0
    struct RefPtr<WebKit::WebPageProxy> _page;	// 1810360 = 0x1b9fb8
    long long _lastToolTipTag;	// 1810496 = 0x1ba040
    id _trackingRectOwner;	// 1810488 = 0x1ba038
    void *_trackingRectUserData;	// 1810480 = 0x1ba030
    struct RetainPtr<NSView> _layerHostingView;	// 1810376 = 0x1b9fc8
    struct RetainPtr<objc_object*> _remoteAccessibilityChild;	// 1810384 = 0x1b9fd0
    struct HashMap<WTF::String, WTF::Vector<WTF::RetainPtr<objc_object*>, 0ul>, WTF::StringHash, WTF::HashTraits<WTF::String>, WTF::HashTraits<WTF::Vector<WTF::RetainPtr<objc_object*>, 0ul>>> _validationMap;	// 1810392 = 0x1b9fd8
    struct OwnPtr<WebKit::PDFViewController> _pdfViewController;	// 1810400 = 0x1b9fe0
    struct OwnPtr<WebKit::FindIndicatorWindow> _findIndicatorWindow;	// 1810408 = 0x1b9fe8
    struct RetainPtr<NSEvent> _keyDownEventBeingResent;	// 1810416 = 0x1b9ff0
    struct WKViewInterpretKeyEventsParameters *_interpretKeyEventsParameters;	// 1810472 = 0x1ba028
    struct CGSize _resizeScrollOffset;	// 1810432 = 0x1ba000
    unsigned long long _pluginComplexTextInputIdentifier;	// 1810504 = 0x1ba048
    _Bool _inBecomeFirstResponder;	// 1810456 = 0x1ba018
    _Bool _inResignFirstResponder;	// 1810464 = 0x1ba020
    NSEvent *_mouseDownEvent;	// 1811216 = 0x1ba310
    BOOL _ignoringMouseDraggedEvents;	// 1810440 = 0x1ba008
    BOOL _dragHasStarted;	// 1810448 = 0x1ba010
    id _endGestureMonitor;	// 1812608 = 0x1ba880
    struct RetainPtr<WKFullScreenWindowController> _fullScreenWindowController;	// 1810424 = 0x1b9ff8
    BOOL _hasSpellCheckerDocumentTag;	// 1810512 = 0x1ba050
    long long _spellCheckerDocumentTag;	// 1810520 = 0x1ba058
    BOOL _inSecureInputState;	// 1812616 = 0x1ba888
    struct CGRect _windowBottomCornerIntersectionRect;	// 1812624 = 0x1ba890
}

- (id).cxx_construct;
- (void).cxx_destruct;

@end