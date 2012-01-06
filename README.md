# Welcome to LionScrollbars v0.2!

## What does it do?

LionScrollbars is a program that enables fine-grained control over how scrollbars are displayed on OS X Lion (10.7). 

## Why do we need it?

The default behavior for scrollbars in Lion only allows for three settings in System Preferences (always show, always hide, mouse-device specific); these settings apply to ALL applications. However, for some application you might find yourself wishing you could see a scrollbar (such as if you're editing text or code, etc.); with this program you can do that!

## How does it work?

Application preferences are stored in `.plist`  files for each application. These preference files allow for overriding system defaults, so we write to these files for any  application for which you wish to override the system default. Unfortunately in OS X Lion a sandboxing mechanism was introduced, which drastically complicates where and how preferences are handled. 

# The nitty-gritty

The information below is intended to be for informational purposes only (not fine examples of excellently written code).

## How to change scrollbar behavior on a per-app basis:

(Examples for toggling scrollbars for TextMate)

    defaults write com.macromates.TextMate AppleShowScrollBars Always
    defaults delete com.macromates.TextMate AppleShowScrollBars
    defaults read com.macromates.TextMate AppleShowScrollBars

## Or Globally:

    defaults write -g AppleShowScrollBars Always

The three possible values are:
"Automatic"     (== "Automatically based on input device", the default)
"WhenScrolling" (== "When scrolling")
"Always"        (== "Always")


## OS X Lion (10.7) 
Lion has sandboxing of certain apps, which we need to account for.
To check if an app will be sandboxed, look for a Contents/_CodeSignature directory.
This is not foolproof, but maybe good enough. If the app is sandboxed, then instead
of writing to: `~/Library/Preferences/com.company.AppName.plist` (which would be where)
`[NSUerDefaults persistentDomainForName:]` would read from, you must look in:
`~/Library/Containers/Data/Library/Preferences/com.company.AppName.plist`. This has to
be done manually by reading in and writing out the file, using `[NSDictionary readFile:]`.

The older way using CoreFoundation to read/write settings also does not work:

    CFPreferencesSetAppValue((CFStringRef)kAppleShowScrollBarsKey, (CFStringRef)value, (CFStringRef)identifier);
    CFPreferencesAppSynchronize((CFStringRef)identifier);

This also only looks in the first, default place, and not within sandboxes.

the terminal command `defaults` seems to know about the sandboxed location for some apps, but not all.
Preferences it find properly in the sandbox, but TextEdit it does not. The workaround to simply run
`/usr/bin/defaults` for reading/writing will also therefore not work in all cases.


## Reading/Writing preferences via NSUserDefaults

	- (NSString *)settingForIdentifier:(NSString *)identifier 
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
	- (void)setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier 
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
	
## Reading/Writing preferences via CoreFoundation

	CFPreferencesSetAppValue((CFStringRef)kAppleShowScrollBarsKey, (CFStringRef)value, (CFStringRef)identifier);
	CFPreferencesAppSynchronize((CFStringRef)identifier);

## Reading/Writing via NSTask and /usr/bin/defaults

	- (NSString *)askSystemGetSettingWithIdentifier:(NSString*)identifier
	{
		if (identifier == nil) {
			identifier = @"-g";
		}
		NSArray *arguments;
		arguments = [NSArray arrayWithObjects:@"read", identifier, kAppleShowScrollBarsKey, nil];
		NSString *ret = [self runSystemDefaultsWithArguments:arguments];
		ret = [self settingFromDisplayString:[self displayStringFromSetting:ret]];
		return ret;
	}
    
	- (NSString *)askSystemSetSettingForIdentifier:(NSString*)identifier withValue:(NSString *)value 
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
		return [self runSystemDefaultsWithArguments:arguments];	
	}
    
	// See: http://stackoverflow.com/questions/412562/execute-a-terminal-command-from-a-cocoa-app
	-(NSString *)runSystemDefaultsWithArguments:(NSArray *)arguments
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


## Reading/Writing plist files directly:

*From: [http://www.ifans.com/forums/showthread.php?t=64679]*

    - (void)readPlist
    {
        NSString *filePath = @"/System/Library/CoreServices/SystemVersion.plist";
	        NSMutableDictionary* plistDict = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
        
	        NSString *value;
	        value = [plistDict objectForKey:@"ProductVersion"];
      
	        /* You could now call the string "value" from somewhere to return the 
			   value of the string in the .plist specified, for the specified key. */
	}
    
	- (void)writeToPlist
	{
	    NSString *filePath = @"/System/Library/CoreServices/SystemVersion.plist";
	        NSMutableDictionary* plistDict = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
        
	        [plistDict setValue:@"1.1.1" forKey:@"ProductVersion"];
	        [plistDict writeToFile:filePath atomically: YES];
    
	/* This would change the firmware version in the plist to 1.1.1 by initing the 
	   NSDictionary with the plist, then changing the value of the string in the key 
	   "ProductVersion" to what you specified */
	}


