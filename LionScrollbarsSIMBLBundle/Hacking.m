//
//  Hacking.h
//  ScrollbarInject
//

#import "Hacking.h"
#import <Cocoa/Cocoa.h>
#import <objc/objc-class.h>

// Referenced:
// - http://www.culater.net/wiki/moin.cgi/CocoaReverseEngineering#head-eb6f8cbd6c9df740a64c6c8290e0ddc462d4dd20
// - http://theocacao.com/document.page/327
// - http://cocoadev.com/index.pl?AddClassAspects

// We define the struct here so we can mess with it, despite it being an opaque type in objc-class.h.
struct objc_method {
	SEL method_name;
	char *method_types;
	IMP method_imp;
};

#pragma mark method and variable declarations

BOOL __logStatus(BOOL res, SEL _sel, NSString* msg);
static BOOL __should_log_status = NO;

#pragma mark public method implementations

/**
 * Swaps the implementations for two methods (not the names of them).
 */
void Hacking_SwapClassMethods(Class _srcClass, Class _destClass, SEL _newSel, SEL _oldSel) {
	if (__should_log_status) {
		NSLog(@"_srcClass (%s) is %@", class_getName(_srcClass), _srcClass != nil ? @"not null" : @"null");
		NSLog(@"_destClass (%s) is %@", class_getName(_destClass), _destClass != nil ? @"not null" : @"null");
	}
	Method originalMethod = class_getClassMethod(_destClass, _oldSel);
	Method replacedMethod = class_getClassMethod(_srcClass, _newSel);
	if (__should_log_status) {
		NSLog(@"originalMethod (%s) is %@", sel_getName(_oldSel), originalMethod != nil ? @"not null" : @"null");
		NSLog(@"replacedMethod (%s) is %@", sel_getName(_newSel), replacedMethod != nil ? @"not null" : @"null");	
	}
	IMP imp1 = method_getImplementation(originalMethod);
	IMP imp2 = method_getImplementation(replacedMethod);
	const char *encoding = method_getTypeEncoding(originalMethod);
	method_setImplementation(originalMethod, imp2);
	class_addMethod(_destClass, _newSel, imp1, encoding);
}

/**
 * Swaps the implementations for two methods (not the names of them).
 */
void Hacking_SwapMethods(Class _srcClass, Class _destClass, SEL _newSel, SEL _oldSel) {
	if (__should_log_status) {
		NSLog(@"_srcClass (%s) is %@", class_getName(_srcClass), _srcClass != nil ? @"not null" : @"null");
		NSLog(@"_destClass (%s) is %@", class_getName(_destClass), _destClass != nil ? @"not null" : @"null");
	}
	Method originalMethod = class_getInstanceMethod(_destClass, _oldSel);
	Method replacedMethod = class_getInstanceMethod(_srcClass, _newSel);
	if (__should_log_status) {
		NSLog(@"originalMethod (%s) is %@", sel_getName(_oldSel), originalMethod != nil ? @"not null" : @"null");
		NSLog(@"replacedMethod (%s) is %@", sel_getName(_newSel), replacedMethod != nil ? @"not null" : @"null");	
	}
	IMP imp1 = method_getImplementation(originalMethod);
	IMP imp2 = method_getImplementation(replacedMethod);
	const char *encoding = method_getTypeEncoding(originalMethod);
	method_setImplementation(originalMethod, imp2);
	class_addMethod(_destClass, _newSel, imp1, encoding);
}

/**
 * _toSelector steals (copies) the IMP from _fromSelector. 
 * If successful, both _toSelector and _fromSelector will point 
 * to the same IMP, namely, that of _fromSelector.
 * 
 * Usage: Hacking_CopyMethod([self class], @selector(from), @selector(to));
 * 
 * @return if the entire process was successful.
 */ 
BOOL Hacking_CopyMethod(Class _class, SEL _fromSelector, SEL _toSelector, BOOL create_if_needed)
{
	BOOL success;
	
	Method to_method = nil;
	to_method = class_getInstanceMethod(_class, _toSelector);	
	success = (to_method != nil);
	__logStatus(success, _toSelector, @"Method lookup");
	if (!success) {
		if (!create_if_needed) {
			__logStatus(NO, _fromSelector, @"Method copied");
			return NO;
		}
		const char* _encoding = method_getTypeEncoding(to_method);
		success = class_addMethod(_class, _toSelector, nil, _encoding);
		__logStatus(success, _toSelector, @"Method add");
		if (!success) return NO;	
		to_method = class_getInstanceMethod(_class, _toSelector);	
		__logStatus(success, _toSelector, @"Method lookup");
		if (!success) return NO;
	}
	
	Method from_method = nil;
	from_method = class_getInstanceMethod(_class, _fromSelector);
	success = (from_method != nil);
	__logStatus(success, _fromSelector, @"Method lookup");
	if (!success) return NO;
	
	// Copy the IMP from _fromSelector to _toSelector
	to_method->method_imp = from_method->method_imp;
	
	__logStatus(YES, _fromSelector, @"Method copied");
	return YES;
}

void Hacking_ShouldLogStatus(BOOL shouldLog) 
{
	__should_log_status = shouldLog;
}

#pragma mark internal method implementations

BOOL __logStatus(BOOL res, SEL _sel, NSString* msg)
{
	if (__should_log_status == YES) {
		const char *name = sel_getName(_sel);
		NSLog(@"%@: SEL (%s) = %@", msg, name, res ? @"yes" : @"no");
	}
	return res;
}
