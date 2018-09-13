//
//  CloudEftposSDK-extended.h
//  CloudEftposSDK
//
//  Created by Tom Graham on 10/09/2014.
//  Copyright (c) 2014 Quest Payment Systems. All rights reserved.
//

#ifndef CloudEftposSDK_CloudEftposSDK_extended_h
#define CloudEftposSDK_CloudEftposSDK_extended_h

@interface CloudEftpos (Extended)

/*!
 *  @method logon:
 *
 *  @param onCompletion A block to call on completion of the logon.
 *
 *  @discussion Attempts to perform a logon to the bank.
 */
-(void) logon:(void (^)(NSDictionary *result, NSError *error))onCompletion;

/*!
 *  @method settlementCutover:
 *
 *  @param onCompletion A block to call on completion of the settlement.
 *
 *  @discussion Attempts to perform a settlement to the bank.
 */
-(void) settlementCutover:(void (^)(NSDictionary *result, NSError *error))onCompletion;

/*!
 *  @method currentTotals:
 *
 *  @param onCompletion A block to call on completion of the totals.
 *
 *  @discussion Attempts to perform a current totals to the bank.
 */
-(void) currentTotals:(void (^)(NSDictionary *result, NSError *error))onCompletion;

/*!
 *  @method lastTotals:
 *
 *  @param onCompletion A block to call on completion of the totals.
 *
 *  @discussion Attempts to perform a last totals to the bank.
 */
-(void) lastTotals:(void (^)(NSDictionary *result, NSError *error))onCompletion;

/*!
 *  @block onCompletion
 *
 *  @param result A result dictionary containing the following key/value pairs
 *   - (NSNumber *) success - Whether the message succesfully contacted the bank
 *   - (NSString *) receipt - The logon or settlement receipt
 *   - (NSString *) message - A message if something went wrong
 *   - (NSString *) code - The error code for the message if appropriate
 *   Any of these values may be nil if something went wrong
 *  @param error An error object containing the error that occurred or nil if
 *  there was no error.
 *
 *  @discussion Called when the operation is finished or when an error occurs.
 */


@end

#endif
