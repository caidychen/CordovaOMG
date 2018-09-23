//
//  CloudEftposSDK-private.h
//  CloudEftposSDK
//
//  Created by Tom Graham on 4/08/2015.
//  Copyright (c) 2015 Quest Payment Systems. All rights reserved.
//

#ifndef CloudEftposSDK_CloudEftposSDK_private_h
#define CloudEftposSDK_CloudEftposSDK_private_h

@interface CloudEftpos (Private)

-(void) startRecurring:(int)amount
               options:(NSDictionary *)options
             onDisplay:(nullable void (^)(NSString *msg))onDisplay
               onPrint:(nullable void (^)(NSString *type, NSNumber *print, NSString *text))onPrint
onTransactionCompleted:(nonnull void (^)(NSDictionary *result, NSError *error))onTransactionCompleted
             onStopped:(nonnull void (^)(bool success, NSString *message))onStopped;
                        
-(void) stopRecurring;

/*!
 *  @method registerTransactionCallbacks:
 *
 *  @param displayBlock The customDisplayBlock to use for display messages.
 *  @param onPrint A block to call when unsolicited prints arrive.
 *  @param onCompletion A block to call on completion of the transaction.
 *
 *  @discussion The custom start transaction can be used if you require
 *  customisation of the prompt and signature callbacks.
 */
-(void) registerTransactionCallbacks:(customDisplayBlock)displayBlock
                             printBlock:(void (^)(NSString *type, NSNumber *print, NSString *text))printBlock
                        onCompletion:(void (^)(NSDictionary *result, NSError *error))onCompletion;


/*!
 * @method destroy
 * 
 * @discussion destroys a CloudEftpos instance by removing all traces of it from persistant storage
 * the CloudEftpos instance should be nilled directly after this method is executed.
 */
-(void) destroy;

-(void) forceProductionMode;

-(void) forceDeveloperMode;

@end

#endif
