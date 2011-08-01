//
//  DefaultsManager.m
//  LionScollbars
//
//  Created by Dain Kaplan on 8/1/11.
//  Copyright 2011 Dain's place. All rights reserved.
//

#import "DefaultsManager.h"

#define SETTINGS_VIA_NSUSERDEFAULTS 10
#define SETTINGS_VIA_NSTASK 20
#define SETTINGS_VIA_CF 30
#define SETTINGS_VIA_FILESYSTEM 40
#define SETTINGS_METHOD SETTINGS_VIA_FILESYSTEM


NSString *kAppleShowScrollBarsKey = @"AppleShowScrollBars";

@interface DefaultsManager(Internal)

- (NSString *)_filesystem_settingValueForIdentifier:(NSString *)identifier;
- (void)_filesystem_setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier;
- (NSString *)_filesystem_getPreferencesFilePathIdentifier:(NSString *)identifier;
- (NSMutableDictionary *)_filesystem_getSettingsForIdentifier:(NSString *)identifier;

- (NSString *)_NSUserDefaults_settingValueForIdentifier:(NSString *)identifier;
- (void)_NSUserDefaults_setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier;

- (NSString *)_CF_settingValueForIdentifier:(NSString *)identifier;
- (void)_CF_setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier;

- (NSString *)_NSTask_settingValueForIdentifier:(NSString *)identifier;
- (void)_NSTask_setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier;
- (NSString *)_NSTask_runDefaultsWithArguments:(NSArray *)arguments;

@end

@implementation DefaultsManager

static DefaultsManager *_sharedSingleton;

+ (void)initialize
{
    static BOOL initialized = NO;
    if(!initialized)
    {
        initialized = YES;
        _sharedSingleton = [[DefaultsManager alloc] init];
    }
}

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

+ (DefaultsManager *)sharedManager 
{
	return _sharedSingleton;
}

- (NSString *)settingValueForIdentifier:(NSString *)identifier 
{
	NSString *setting;
#if SETTINGS_METHOD == SETTINGS_VIA_FILESYSTEM	
	setting = [self _filesystem_settingValueForIdentifier:identifier];
#elif SETTINGS_METHOD == SETTINGS_VIA_NSTASK
	setting = [self _NSTask_settingValueForIdentifier:identifier];
#elif SETTINGS_METHOD == SETTINGS_VIA_CF
	setting = [self _CF_settingValueForIdentifier:identifier];
#else // SETTINGS_VIA_NSUSERDEFAULTS
	setting = [self _NSUserDefaults_settingValueForIdentifier:identifier];
#endif
	return setting;
}

- (void)setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier 
{
#if SETTINGS_METHOD == SETTINGS_VIA_FILESYSTEM	
	[self _filesystem_setSettingValue:value 
							forIdentifier:identifier];
#elif SETTINGS_METHOD == SETTINGS_VIA_NSTASK
	[self _NSTask_setSettingValue:value 
					forIdentifier:identifier];
#elif SETTINGS_METHOD == SETTINGS_VIA_CF
	[self _CF_setSettingValue:value 
				forIdentifier:identifier];
#else // SETTINGS_VIA_NSUSERDEFAULTS
	[self _NSUserDefaults_setSettingValue:value 
							forIdentifier:identifier];	
#endif
}

#pragma mark Access methods using the file system (manual)

// XXX(dkaplan): Basically, since 10.7 introduced application-sandboxing,
//     we need to check ~/Library/Containers/[identifier]/Data/Library/Preferences/ 
//     and then, if it doesn't exist, look in the normal place (~/Library/Preferences/).
- (NSString *)_filesystem_settingValueForIdentifier:(NSString *)identifier
{
	NSString *setting = nil;
	if (identifier == nil) {
		// XXX(dkaplan): Global settings work fine using the normal method.
		setting = [self _NSUserDefaults_settingValueForIdentifier:nil];
	} else {
		NSMutableDictionary *defaults = [self _filesystem_getSettingsForIdentifier:identifier];
		if (defaults != nil) {
			setting = [defaults objectForKey:kAppleShowScrollBarsKey];
		}
	}
	return setting;
}

- (void)_filesystem_setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier
{
	if (identifier == nil) {
		// XXX(dkaplan): Global settings work fine using the normal method.
		[self _NSUserDefaults_setSettingValue:value forIdentifier:nil];
	} else {
		NSMutableDictionary *defaults = [self _filesystem_getSettingsForIdentifier:identifier];
		if (defaults == nil) {
			defaults = [NSMutableDictionary dictionary];
		}
		[defaults setValue:value forKey:kAppleShowScrollBarsKey];
		NSString *filePath = [self _filesystem_getPreferencesFilePathIdentifier:identifier];
		[defaults writeToFile:filePath atomically:YES];
	}
}

// XXX(dkaplan): It looks like the plist file could be other places too. 
//     iWork's Pages, for example, saves itself in the TextEdit container...
- (NSString *)_filesystem_getPreferencesFilePathIdentifier:(NSString *)identifier
{
	NSString *sandboxExistsPath = [[NSString stringWithFormat: @"~/Library/Containers/%@", identifier] stringByExpandingTildeInPath];
	NSString *sandboxedFilePath = [NSString stringWithFormat: @"~/Library/Containers/%@/Data/Library/Preferences/%@.plist", identifier, identifier];
	NSString *regularFilePath = [NSString stringWithFormat: @"~/Library/Preferences/%@.plist", identifier];
	NSFileManager *fm = [NSFileManager defaultManager];
	NSString *filePath = nil;
	BOOL isDirectory = NO;
	BOOL isSandboxed = [fm fileExistsAtPath:sandboxExistsPath isDirectory:&isDirectory];
	if (isSandboxed && isDirectory) {
		sandboxedFilePath = [sandboxedFilePath stringByExpandingTildeInPath];
		filePath = sandboxedFilePath;
	} else {
		regularFilePath = [regularFilePath stringByExpandingTildeInPath];
		BOOL hasDefaults = [fm fileExistsAtPath:regularFilePath];
		if (hasDefaults) {
			filePath = regularFilePath;
		}
	}
	NSLog(@"File path is: %@", filePath);
	return filePath;
}

- (NSMutableDictionary *)_filesystem_getSettingsForIdentifier:(NSString *)identifier
{
	NSMutableDictionary* defaults = nil;
	NSString *filePath = [self _filesystem_getPreferencesFilePathIdentifier:identifier];
	if (filePath != nil) {
		defaults = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
	}
	return defaults;
}

#pragma mark Access methods using NSUserDefaults

- (NSString *)_NSUserDefaults_settingValueForIdentifier:(NSString *)identifier
{
	NSString *setting = nil;
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	if (identifier == nil) {
		identifier = NSGlobalDomain;
	}
	NSDictionary *appDefaults = [defaults persistentDomainForName:identifier];
	if (appDefaults != nil) {
		setting = [appDefaults valueForKey:kAppleShowScrollBarsKey];
	}
	return setting;
}

- (void)_NSUserDefaults_setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier 
{
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	NSMutableDictionary *appDefaults = nil;
	if (identifier == nil) {
		identifier = NSGlobalDomain;
	}
	appDefaults = [[defaults persistentDomainForName:identifier] mutableCopy];
	if (appDefaults == nil) {
		appDefaults = [NSMutableDictionary dictionary];
	}
	[appDefaults setValue:value forKey:kAppleShowScrollBarsKey];
	[defaults setPersistentDomain:appDefaults forName:identifier];
	[defaults synchronize];	
}

#pragma mark Access methods using CoreFoundation

- (NSString *)_CF_settingValueForIdentifier:(NSString *)identifier
{
	return (NSString *)CFPreferencesCopyAppValue((CFStringRef)kAppleShowScrollBarsKey, (CFStringRef)identifier);
}

- (void)_CF_setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier
{
	CFPreferencesSetAppValue((CFStringRef)kAppleShowScrollBarsKey, 
							 (CFStringRef)value, 
							 (CFStringRef)identifier);
	CFPreferencesAppSynchronize((CFStringRef)identifier);
}

#pragma mark Access methods using NSTask and /usr/bin/defaults

// This stupid hack is necessary because now on 10.7 preferences are sandboxed, but 
// the "defaults" app knows where to look for them, and has access to them.
- (NSString *)_NSTask_settingValueForIdentifier:(NSString *)identifier
{
	if (identifier == nil) {
		identifier = @"-g";
	}
	NSArray *arguments;
	arguments = [NSArray arrayWithObjects:@"read", identifier, kAppleShowScrollBarsKey, nil];
	NSString *ret = [self _NSTask_runDefaultsWithArguments:arguments];
	if ([@"Automatic" isEqualToString:ret]) {
		ret = @"Automatically";
	} else	if ([@"Always" isEqualToString:ret]) {
		ret = @"Always";
	} else if ([@"WhenScrolling" isEqualToString:ret]) {
		ret = @"When scrolling";
	} else {
		ret = nil;
	}
	return ret;
}

- (void)_NSTask_setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier 
{
	if (identifier == nil) {
		identifier = @"-g";
	}
	NSArray *arguments;
	if (value == nil) {
		arguments = [NSArray arrayWithObjects:@"remove", identifier, kAppleShowScrollBarsKey, nil];
	} else {
		arguments = [NSArray arrayWithObjects:@"write", identifier, kAppleShowScrollBarsKey, value, nil];
	}
	[self _NSTask_runDefaultsWithArguments:arguments];	
}

// See: http://stackoverflow.com/questions/412562/execute-a-terminal-command-from-a-cocoa-app
- (NSString *)_NSTask_runDefaultsWithArguments:(NSArray *)arguments
{
	NSTask *task;
	task = [[NSTask alloc] init];
	[task setLaunchPath: @"/usr/bin/defaults"];
	[task setArguments: arguments];
	
	NSPipe *pipe;
	pipe = [NSPipe pipe];
	[task setStandardOutput: pipe];
	//The magic line that keeps your log where it belongs
	[task setStandardInput:[NSPipe pipe]];
	
	NSFileHandle *file;
	file = [pipe fileHandleForReading];
	
	[task launch];
	
	NSData *data;
	data = [file readDataToEndOfFile];
	
	NSString *string;
	string = [[NSString alloc] initWithData: data encoding: NSUTF8StringEncoding];
	string = [string stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
	NSLog (@"defaults reports: %@", string);
	return string;
}

@end
