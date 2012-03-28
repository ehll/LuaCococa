//
//  ParseSupportStruct.h
//  LuaCocoa
//
//  Created by Eric Wing on 10/14/09.
//  Copyright 2009 PlayControl Software, LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ParseSupport.h"

@interface ParseSupportStruct : ParseSupport
{
	NSString* structName; // could be different than keyname as in the case of NSPoint->CGPoint
	NSMutableArray* fieldNameArray;
	NSMutableArray* fieldElementArray;

	// Note: I have two caches for size. One as a global function and one here. I should see about unifying.
	// I am worried that the function may be called before a valid ParseSupportStruct is available though.
	size_t sizeOfStruct;
}

@property(retain, readonly) NSString* structName;
@property(retain, readonly) NSMutableArray* fieldNameArray;
@property(retain, readonly) NSMutableArray* fieldElementArray;
@property(assign, readonly) size_t sizeOfStruct;

- (id) initWithKeyName:(NSString*)key_name;
/**
  For a struct like:
	struct foo {
		int a;
		int b;
		struct fee c;
	};
  a is at index 0.
  b is at index 1.
  c is at index 2.
 */
- (void*) pointerAtFieldIndex:(NSUInteger)field_index forStructPtr:(void*)struct_ptr;

- (size_t) sizeOfStruct;

+ (NSString*) keyNameFromStructName:(NSString*)struct_name;

@end


// Helper: These are elements in the array
@interface ParseSupportStructFieldElement : NSObject
{
	bool compositeType; // is it a struct or a primitive type
	NSString* compositeName; // e.g. CGRect is made of CGPoint and CGSize. Problem: BridgeSupport doesn't list the keyName in this context.
	NSString* lookupName; // To deal with the problem that BridgeSupport uses inconsistent keynames for structnames.
	NSMutableArray* objcEncodingTypeArray; // this might be recursive

	// If the nesting goes deeper, I will throw away information.
	// All I need is the list of encoding types.
	// I don't need the additional struct names or field names.
	
//	char objcEncodingType;
//	NSString* structName; // could be different than keyname as in the case of NSPoint->CGPoint
//	NSMutableArray* objcEncodingTypeArray;
//	NSMutableArray* fieldNameArray;
}

@property(assign, readwrite, getter=isCompositeType) bool compositeType;
// Note: Setting compositeName is will also compute the lookupName
@property(retain, readwrite) NSString* compositeName;
 // To deal with the problem that BridgeSupport uses inconsistent keynames for structnames.
@property(retain, readonly) NSString* lookupName; // readonly because it is generated by setting compositeName
@property(retain, readwrite) NSMutableArray* objcEncodingTypeArray;


@end
