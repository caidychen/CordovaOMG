//
//  CloudEftposSDK.h
//  CloudEftposSDK
//
//  Created by Tom Graham on 12/03/13.
//  Copyright (c) 2013 Quest Payment Systems. All rights reserved.
//

#define CloudEftposSDK_version 1.6.7

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>

/*!
 *  @interface TransactionRequest
 *
 *  @property amount The amount in cents of the purchase or refund excluding
 *            any cashout or tip amounts.
 *  @property cashOut An amount in cents indicating cashout amount.
 *            0 if none. -1 for the PINpad to prompt.
 *  @property tipAmount An amount in cents indicating a tip. 0 if none.
 *  @property transactionType The type of transaction.
 *  @property posReference A 12 character reference for this transaction.
 *  @property posNotes Optional notes for a transaction to be stored online.
 *  @property gpsLocation An optional GPS location formatted as a string
 *            "LAT,LON" where LAT and LON are doubles.
 *  @property posData1 An optional field for providing additional data to the
 *            PINpad for a transaction.
 *  @property posData2 An optional field for providing additional data to the
 *            PINpad for a transaction.
 *  @property verifyRefund A boolean indicating whether refunds should
 *            automatically prompt for a passcode. Defaults to True.
 *  @property autoGpsLocation If set the SDK will automatically determine the
 *            GPS location for this transaction. Defaults to false.
 *  @property cancelAsButton If set the SDK will display a cancel button
 *            instead of a swipe on the dark transaction screen.
 *            Defaults to false.
 *  @property bypassTerminalSurcharge If set then any PINpad surcharge will be
 *            bypassed.
 *            Defaults to false.
 *  @property theme Can be set to the new dark transaction theme. Defaults to
 *            Classic.
 *  @property transactionMode Should be set to either Card or Alipay. Defaults
 *            to Card.
 *
 *  @discussion The TransactionRequest object should be set with the relevant
 *              parameters before passing it to the startTransaction method.
 */
@interface TransactionRequest : NSObject

typedef enum {
    Purchase = 0x01,
    Refund = 0x02
} TransactionType;

typedef enum {
    Classic = 0x00,
    Dark = 0x01,
    Modern = 0x02,
    ModernDark = 0x03
} TransactionTheme;
typedef enum {
    Card = 0,
    Alipay = 16
} TransactionMode;

@property (nonatomic) UInt32 amount;
@property (nonatomic) UInt32 cashout;
@property (nonatomic) UInt32 tipamount;
@property (nonatomic) TransactionType transactionType;
@property (nonatomic, strong) NSString *posReference;
@property (nonatomic, strong) NSString *posNotes;
@property (nonatomic, strong) NSString *gpsLocation;
@property (nonatomic, strong) NSData *posData1;
@property (nonatomic, strong) NSData *posData2;
@property (nonatomic) bool verifyRefund;
@property (nonatomic) bool autoGpsLocation;
@property (nonatomic) bool bypassTerminalSurcharge;
@property (nonatomic) bool cancelAsButton;
@property (nonatomic) TransactionTheme theme;
@property (nonatomic) TransactionMode transactionMode;
@property (nonatomic) UIColor *themePrimaryColor;

@end

@interface CloudEftpos : NSObject

extern NSString *const ErrorDomain;
typedef enum {
    ErrorPinpadDisconnected = 1,
    ErrorBadArgs = 2,
    ErrorCannotFindPinpad = 3,
    ErrorBluetoothDisabled = 4,
    ErrorNoNetwork = 5,
    ErrorNoInternet = 6,
    ErrorNoTransaction = 7,
    ErrorUnsupportedDevice = 8,
    ErrorPINpadError = 9,
    ErrorPinpadNotReady = 10,
    ErrorInvalidRefundPasscode = 11,
    ErrorTransactionInProgress = 12
} ErrorCodes;

typedef NS_ENUM(NSUInteger, AutoAllocationMode) {
    Allow = 1,      // Automatically allocate the PINpad to a company
    Deny = 2,       // Automatically reject unallocated PINpads
    Prompt = 3      // Ask the user if they wish to assign the PINpad to a company
};

// Detect changes to these properties by implementing registerForStatusChanges
@property (nonatomic) bool connected; // Is device currently connected
@property (nonatomic) bool paired; // Is device currently paired
@property (nonatomic) bool ready; // Is the PINpad ready to transact
@property (nonatomic) bool awake; // Is the device awake
@property (nonatomic) bool updateAvailable; // Is there a pending update available for the connected device
@property (nonatomic) AutoAllocationMode autoAllocationMode; // Multiple pairing modes support
@property (nonatomic) int batteryLevel; // Battery percentage between 0 and 100
@property (nonatomic, strong) NSString *pinpadName; // Name of the connected PINpad
@property (nonatomic, strong) NSDictionary *pinpadBanks; // Dictionary of bank details on the connected PINpad
@property (nonatomic, strong) NSString *instanceIdentifier; // Identifier of this particular instance of the SDK

// Theming for iOS 7
// Use to override the navigation bar font for screens in the SDK
@property (nonatomic, strong) UIFont *navigationBarFont;
// Use to override the navigation bar and status bar colour for screens in the SDK
@property (nonatomic, strong) UIColor *navigationBarColor;
// Use to override the navigation bar title colour for screens in the SDK
@property (nonatomic, strong) UIColor *navigationBarTitleColor;
@property (nonatomic, strong) UIColor *navigationBarTitleShadowColor;
// Use to override the navigation bar tint (back button) colour for screens in the SDK
@property (nonatomic, strong) UIColor *navigationBarTintColor;
// Use to override the status bar style in the SDK (useful if you change the navigation bar colour)
@property (nonatomic) UIStatusBarStyle statusBarStyle;

+(BOOL) isJailBroken;

/*!
 *  @method sharedInstance
 *
 *  @discussion Static method to get the CloudEftpos singleton.
 *              Preferred over using init.
 *              Any reference to the singleton stored should be stored
 *              as weak to ensure close functions correctly.
 */
+(CloudEftpos *) sharedInstance;

/*!
 *  @method close;
 *
 *  @discussion Static method to delete the CloudEftpos singleton.
 *              Must be used in conjunction with sharedInstance to
 *              Close the SDK.
 */
+(void) close;

/*!
 *  @method init:
 *
 *  @discussion Initialises the CloudEftpos object.
 */
-(CloudEftpos *) init;
-(CloudEftpos *) initWithInstanceIdentifier:(NSString *)identifier;

/*!
 *  @method setHostRegion:
 *
 *  @param regionCode The 2 character region code for the preferred region.
 *  See the full list of available regions in the SDK documentation.
 *  Defaults to "au" (Australia)
 *  This value is persistent, so once it is set it only needs to be called
 *  again to change the value (which should generally not happen!)
 *
 *  @discussion Set the host of the SDK to use the specified region code.
 */
-(void) setHostRegion:(NSString *)regionCode;

/*!
 *  @method registerForStatusChangesWithBlock
 *
 *  @param statusChanged A block to call when there is a status change for the
 *  PINpad. Status changes include: connection status, battery state,
 *  update for PINpad ready.
 *
 *  @discussion A block should be registered immediately after initiating the
 *  PINpad library. After registering a block it will be called immediately
 *  with the current state of the library. The block will be called infrequently
 *  to notify about changes to the PINpad such as battery level.
 */

-(void) registerForStatusChangesWithBlock:(void (^)(NSDictionary *status))statusChanged;

/*!
 *  @block statusChanged
 *
 *  @param status A dictionary containing key/value pairs of:
 *   - (NSNumber *) batteryLevel - The percentage of battery remaining (0-100)
 *                  Will be 0 if no device is connected
 *   - (NSNumber *) ready - Is the PINpad ready to transact? 0 for not ready,
 *                  1 for ready
 *   - (NSNumber *) connected - Is the PINpad connected? 0 for disconnected,
 *                  1 for connected
 *   - (NSNumber *) paired - 0 if no PINpad has been paired before, 1 if a
 *                  PINpad has previously been paired
 *   - (NSNumber *) awake - 0 if the PINpad is asleep, 1 if the PINpad is awake
 *                  Will be 0 if no device is connected
 *   - (NSNumber *) updateAvailable - Is an update available for the PINpad?
 *                  0 for no update, 1 for update for PINpad
 *   - (NSString *) pinpadName - The PINpads serial number.
 *   - (NSDictionary *) pinpadBanks - A dictionary of banks on the connected
 *                      PINpad. The key is the name of the bank. Each key
 *                      points to a Dictionary containing the aiic, caid,
 *                      catid and ppid.
 *
 *  @discussion Called whenever there is a change to the PINpad status.
 *  Implementations should check each key/value pair of the dictionary for
 *  changes.
 *
 *  @warning Please note: batteryLevel and updateAvailable are not
 *  yet implemented in this version of the SDK.
 */

/*!
 *  @method connectDevice
 *
 *  @discussion Begins the discovery process for connecting to the last
 *  connected device. If the device hasn't been previously paired nothing
 *  will happen.
 */
-(void) connectDevice;

/*!
 *  @method disconnectDevice
 *
 *  @return False if there was no device connected, otherwise true
 *
 *  @discussion Disconnects the device without unpairing it. Automatic
 *  device discovery will be disabled until connectDevice is called.
 */
-(bool) disconnectDevice;

/*!
 *  @method setSupportedPaymentTerminals
 *
 *  @param terminalCodes The available terminals by code.
 *
 *  @discussion Overrides the available payment termanal types based on
 *  the supplied codes.
 */
-(void) setSupportedPaymentTerminals:(NSArray *)terminalCodes;

/*!
 *  @method addSupportedPaymentTerminal
 *
 *  @param terminalCode The terminal code.
 *
 *  @discussion Adds the provided terminal type to the list of available
 *  terminals.
 */
-(void) addSupportedPaymentTerminal:(NSString *)terminalCode;

/*!
 *  @method pairDeviceWithPresentingViewController:
 *
 *  @param presentingViewController The currently displayed view controller.
 *  @param animated A bool indicating whether or not to animate the transition.
 *  @param onCompletion A block to call on completion of the pairing process
 *
 *  @discussion Initiations an attempt to pair the library with a new PINpad.
 */
-(void) pairDeviceWithPresentingViewController
:(UIViewController *)presentingViewController
animated:(BOOL)animated
onCompletion:(void (^)(NSError *error))onCompletion;

/*!
 *  @block onCompletion
 *
 *  @param error An error object containing the error that occurred or nil if
 *  there was no error.
 *
 *  @discussion Called when pairing has finished. Any implementation should
 *  check if there was an error returned.
 */

/*!
 *  @method unpairDevice
 *
 *  @discussion Unpairs the last PINpad device.
 */
-(void) unpairDevice;

/*!
 *  @method startTransaction:
 *
 *  @param transactionRequest A transaction request object as defined above.
 *  @param presentingViewController The currently displayed view controller.
 *  @param animated A bool indicating whether or not to animate the transition.
 *  @param onCompletion A block to call on completion of the transaction.
 *
 *  @discussion Initiates a transaction with the given details. Displays a
 *  transaction screen to the operator.
 */
-(void) startTransaction:(TransactionRequest *)transactionRequest
withPresentingViewController:(UIViewController *)presentingViewController
                animated:(BOOL)animated
            onCompletion:(void (^)(NSDictionary *result, NSError *error))onCompletion;

/*!
 *  @block onCompletion
 *
 *  @param result A result dictionary containing the following key/value pairs
 *   - (NSNumber *) approved - Approved (1) or declined (0)
 *   - (NSString *) receipt - The EFTPOS receipt
 *   - (NSString *) signatureReceipt - The EFTPOS signature receipt (optional)
 *   - (UIImage *) signatureImage - Signature as a UIImage (optional)
 *   - (UIBezierPath *) signaturePath - Signature as a UIBezierPath (optional)
 *   - (NSString *) responseCode - See response codes section of SDK
 *   - (NSString *) responseText - Description of response
 *   - (NSNumber *) amount - The amount processed for the transaction excluding
 *                  any surcharge, cashout or tip.
 *   - (NSNumber *) cashOut - The amount added for cashout.
 *   - (NSNumber *) tipAmount - The amount added for tip.
 *   - (NSNumber *) surcharge - The amount added for surcharge.
 *   - (NSString *) account - The account selected by the customer (lowercase).
 *   - (NSString *) CAID - Merchant ID
 *   - (NSString *) CATID - Terminal ID
 *   - (NSString *) posReference - The POS reference used
 *   - (NSDate *) dateTime - The date and time of the transaction
 *   - (NSString *) authID - Unique auth ID from the bank
 *   - (NSString *) STAN - Unique System Trace Audit Number from PINpad
 *   - (NSString *) settlementDate - Settlement date formatted as MMDD
 *   - (NSString *) truncatedPAN - A truncated copy of the card PAN
 *   - (NSString *) cardName - The type of card used (eg: DEBIT, VISA, etc)
 *   - (NSString *) businessName - The name configured for this business
 *   - (NSString *) businessABN - The ABN configured for this business
 *   - (NSString *) guid - A GUID that can be used for receipt lookups
 *   - (NSString *) receiptURL - The URL of the receipt
 *  @param error An error object containing the error that occurred or nil if
 *  there was no error.
 *
 *  @discussion Called when the transaction is finished or when an error occurs.
 *  Any implementation should check for an error and retrieve any required
 *  results from the result dictionary.
 */


/* Custom Start Transaction allows for overriding some functionality */

/*!
 *  @block customDisplayBlock
 *
 *  @param msg The display message.
 *
 *  @discussion This block is called every time the PINpad sends a display
 *  message to the POS.
 */
typedef void (^customDisplayBlock)(NSString *msg);

/*!
 *  @block customPromptBlock
 *
 *  @param text The text to display for the prompt.
 *  @param inputRequired Whether input is required or not. If input is
 *  required the prompt should allow the user to input a string.
 *  @param keys An array of NSString objects. Each string is a key that the
 *  user can press. These keys are usually "ok" or "cancel" and lower case.
 *
 *  @discussion This block is called when the POS must display a prompt to
 *  the user. The prompt allows the user to optionally enter text and to
 *  select a key.
 *  See promptResponse below for how to respond to this prompt.
 */
typedef void (^customPromptBlock)(NSString *text, bool inputRequired, NSArray *keys);

/*!
 *  @block customSignaturePromptBlock
 *
 *  @param receipt The signature receipt that may be optionally displayed
 *  to the user.
 *  @param keys An array of NSString objects. Each string is a key that the
 *  user can press. Regardless of these strings, you should respond with
 *  "yes", "no", or "cancel".
 *  @param fallbackBlock Call this block if you want to fallback to
 *  capturing the customers signature on the device screen. Make sure to
 *  pass the receipt and keys back into it.
 *  If you use the fallback you should NOT respond with promptResponse.
 *
 *  @discussion The block is called when the customer must sign for the
 *  transaction. The operator should then be prompted if the signature
 *  matches and respond with either "yes", "no" or "cancel".
 *  See promptResponse below for how to respond to this prompt.
 */
typedef void (^signatureCaptureFallback)(NSString *receipt, NSArray *keys);
typedef void (^customSignaturePromptBlock)(NSString *receipt, NSArray *keys, signatureCaptureFallback fallbackBlock);

/*!
 *  @method startTrasaction:
 *
 *  @param transactionRequest A transaction request object.
 *  @param displayBlock The customDisplayBlock to use for display messages.
 *  @param promptBlock The customPromptBlock to use for prompts. If nil,
 *  the SDK will use UIAlerts for this.
 *  @param signaturePromptBlock The customSignaturePromptBlock to use if a
 *  signature is required. If nil then the SDK will display its own
 *  signature capture screen.
 *  @param presentingViewController This is required if the
 *  signaturePromptBlock is nil.
 *  @param animated A bool indicating whether or not to animate the
 *  transition to the signature screen (if the signature block is nil).
 *  @param onCompletion A block to call on completion of the transaction.
 *
 *  @discussion The custom start transaction can be used if you require
 *  customisation of the prompt and signature callbacks.
 */
-(void) startTransaction:(TransactionRequest *)transactionRequest
            displayBlock:(customDisplayBlock)displayBlock
             promptBlock:(customPromptBlock)promptBlock
    signaturePromptBlock:(customSignaturePromptBlock)signaturePromptBlock
withPresentingViewController:(UIViewController *)presentingViewController
                animated:(BOOL)animated
            onCompletion:(void (^)(NSDictionary *result, NSError *error))onCompletion;

/*!
 *  @method startTransaction:
 *
 *  @param disableTransactionScreen Setting this to True will disable the
 *  transaction screen.
 *
 *  @discussion This method should not be used by any third parties
 *  outside of Quest Payment Systems!
 */
-(void) startTransaction:(TransactionRequest *)transactionRequest
            displayBlock:(customDisplayBlock)displayBlock
             promptBlock:(customPromptBlock)promptBlock
    signaturePromptBlock:(customSignaturePromptBlock)signaturePromptBlock
withPresentingViewController:(UIViewController *)presentingViewController
                animated:(BOOL)animated
            onCompletion:(void (^)(NSDictionary *result, NSError *error))onCompletion
disableTransactionScreen:(BOOL)disableTransactionScreen;

/*!
 *  @method promptResponse
 *
 *  @param key The key pressed such as "ok", "cancel", "yes", "no". Must be
 *  lower case.
 *  @param text The user input if provided, otherwise nil.
 *
 *  @discussion Must be called from promptBlock or signaturePromptBlock to
 *  respond with the key pressed and any text input.
 */
-(void) promptResponse:(NSString *)key
              withText:(NSString *)text;

/*!
 *  @method cancelTransaction
 *
 *  @discussion Cancels any pending transaction. The pending transaction
 *  will finish with an appropriate error code (to indicate cancellation).
 *  If there is no pending transaction then nothing will happen. May fail
 *  if the transaction cannot be cancelled.
 *  Note that generally this method should not be needed as the transaction
 *  interface provides its own cancellation button.
 */
-(void) cancelTransaction;

/*!
 *  @method sleepDevice
 *
 *  @discussion Puts the PINpad into a sleep state that preserves battery
 *  power.
 */
-(void) sleepDevice;

/*!
 *  @method wakeDevice
 *
 *  @discussion Wakes the PINpad up from its sleep state.
 */
-(void) wakeDevice;

/*!
 *  @method advancedMenuWithPresentingViewController:
 *
 *  @param presentingViewController The currently displayed view controller.
 *  @param animated A bool indicating whether or not to animate the transition.
 *  @param onClose A block to call when the advanced menu is closed.
 *  @param onPrint A block to call when an admin command results in a receipt.
 *
 *  @discussion Displays a menu to perform advanced functions with the PINpad.
 */
-(void) advancedMenuWithPresentingViewController
:(UIViewController *)presentingViewController
animated:(BOOL)animated
onClose:(void (^)(void))onClose
onPrint:(void (^)(NSString *type, NSString *receipt))onPrint;

/*!
 *  @block onPrint
 *
 *  @param type The type of print. Possible types are: logon, settlement
 *              cutover, current totals, previous totals
 *  @param receipt The pre-formatted receipt text.
 *
 *  @discussion This block is called whenever an admin command is performed
 *              that results with in a receipt. The receipt is
 *              automatically displayed to the user, but this block can be
 *              used to additionally store or print these receipts.
 */

/*!
 *  @method recoverTransactionWithPosReference
 *
 *  @param posReference The 12 character posReference used for the transaction.
 *  @param transactionType The type of transaction (Purchase or Refund)
 *  @param amount An optional amout to compare against. 0 to match any amount.
 *  @param presentingViewController This is required if the
 *  signaturePromptBlock is nil.
 *  @param animated A bool indicating whether or not to animate the
 *  transition to the signature screen (if the signature block is nil).
 *  @param onCompletion Analogous to the startTransaction onCompletion block.
 *
 *  @discussion This method must be called to recover any transaction in the
 *  case of the POS crashing or losing power. It will handle stepping the
 *  user through reconnecting their PINpad and recovering the last
 *  transaction.
 */
// Get the last transaction result
-(void) recoverTransactionWithPosReference
:(NSString *)posReference
transactionType:(TransactionType)transactionType
amount:(UInt32)amount
withPresentingViewController:(UIViewController *)presentingViewController
animated:(bool)animated
onCompletion:(void (^)(NSDictionary *result, NSError *error))onCompletion;

/*!
 *  @block onCompletion
 *
 *  @discussion Exactly the same as the onCompletion block for startTransaction.
 *
 *  @see startTransaction
 */

/*!
 *  @method getLastTransactionWithPosReference
 *
 *  @param posReference The 12 character posReference used for the transaction.
 *  @param transactionType The type of transaction (Purchase or Refund)
 *  @param amount An optional amout to compare against. 0 to match any amount.
 *  @param onCompletion Analogous to the startTransaction onCompletion block.
 *
 *  @warning This function is deprecated. You should instead use the
 *           recoverTransaction method above.
 *
 *  @discussion Attempts to find a completed (or failed) transaction for the
 *  given POS reference. Calls the onCompletion block with the same response
 *  values as for startTransaction.
 */
// Get the last transaction result
-(void) getLastTransactionWithPosReference
:(NSString *)posReference
transactionType:(TransactionType)transactionType
amount:(UInt32)amount
onCompletion:(void (^)(NSDictionary *result, NSError *error))onCompletion;

/*!
 *  @block onCompletion
 *
 *  @discussion Exactly the same as the onCompletion block for startTransaction.
 *
 *  @see startTransaction
 */

/*!
 *  @method updatePINpad
 *
 *  @param presentingViewController The currently displayed view controller.
 *  @param animated A bool indicating whether or not to animate the transition.
 *  @param onCompletion A block to call on completion of the update.
 *
 *  @discussion Checks if there is an update ready for the PINpad,
 *  downloads it and applies it.
 */
-(void) updatePINpadWithPresentingViewController
:(UIViewController *)presentingViewController
animated:(BOOL)animated
onCompletion:(void (^)(NSError *error))onCompletion;

/*!
 *  @block onCompletion
 *
 *  @param version The version after applying the update (or current version if
 *  the update was not applied).
 *  @param error An error object containing the error that occurred or nil if
 *  there was no error.
 *
 *  @discussion Called once the update has been applied to the PINpad or if
 *  there is an error finding or applying the update.
 */

/*!
 *  @method emailReceipt
 *
 *  @param posReference The posReference used for the transaction.
 *  @param transactionGuid The guid provided by the transaction result.
 *  @param emailAddress An email address to send the receipt to.
 *
 *  @return True if the email was successfully queued. False if the email
 *  address provided is invalid.
 *
 *  @discussion Emails a digital receipt to a customers email address.
 */
-(bool) emailReceipt:(NSString *)posReference
     transactionGuid:(NSString *)transactionGuid
        emailAddress:(NSString *)emailAddress;

/* Cloud Commissioning Methods */

/*!
 *  @method verifyCredentials:
 *
 *  @param email The email address of the authenticating user
 *  @param password The password of the authenticating user
 *  @param onCompletion A block to call on completion of the user
 *  authorisation
 *
 *  @discussion Verifies that a user (for the given email and password) is
 *  authorised to interact with the CloudEftpos system.
 */
-(void) verifyCredentials:(NSString *)email
                 password:(NSString *)password
             onCompletion:(void (^)(bool verified, NSError *error))onCompletion;
/*!
 *  @block onCompletion
 *
 *  @param verified True if the user is authorised to interact with CloudEftpos
 *  @param error An error object containing the error that occurred or nil if
 *  there was no error.
 *
 *  @discussion Called once the user has been authenticated.
 */

/*!
 *  @method verifyPasscode:
 *
 *  @param passcode The passcode to verify
 *
 *  @discussion Verifies a passcode. Will only work if the user has
 *  previously (and successfully) authorised against the system.
 */
-(void) verifyPasscode:(NSString *)passcode
          onCompletion:(void (^)(bool verified, NSError *error))onCompletion;
/*!
 *  @block onCompletion
 *
 *  @param verified True if the passcode is valid
 *  @param error An error object containing the error that occurred or nil if
 *  there was no error.
 *
 *  @discussion Called with the result of the passcode verification
 */

/*!
 *  @method authorisePOS:
 *
 *  @param posName The name for this POS device (eg: the phone's name)
 *  @param onCompletion A block to call on completion of the POS
 *  authorisation
 *
 *  @discussion Adds this POS device as an authorised POS.
 */
-(void) authorisePOS:(NSString *)posName
        onCompletion:(void (^)(bool authorised, NSError *error))onCompletion;
/*!
 *  @block onCompletion
 *
 *  @param authorised True if this POS device has been authorised.
 *  @param error An error object containing the error that occurred or nil if
 *  there was no error.
 *
 *  @discussion Called once POS device has been authorised.
 */


/*!
 *  @method registerForCommissionPINpadWithBlock:
 *
 *  @param commissionPINpad A block that will be called if the connected
 *  PINpad needs to be commissioned. This block should respond by calling
 *  the responseBlock that is passed to it.
 *
 *  @discussion Allows the POS to provide a CATID/CAID and terminal name
 *  when a new PINpad is connected.
 */
typedef void (^commissionPINpadResponseBlock)(NSString *terminalName, NSString *caid, NSString *catid);
typedef void (^commissionPINpadBlock)(UIViewController *presentingViewController, NSString *serialNumber, commissionPINpadResponseBlock responseBlock);
-(void) registerForCommissionPINpadWithBlock:(commissionPINpadBlock) commissionPINpad;
/*!
 *  @block commissionPINpad:
 *
 *  @param presentingViewController The current view controller. You can use
 *  this to display your own view for collecting user input.
 *  @param serialNumber The serial number of the connected PINpad.
 *  @param commissionPINpadResponseBlock The block to be used for responding.
 *
 *  @discussion Called if there is a PINpad to be commissioned.
 */
/*!
 *  @block responseBlock:
 *
 *  @param terminalName A friendly name for the terminal.
 *  @param caid The CAID (merchant ID).
 *  @param catid The CATID (terminal ID).
 *
 *  @discussion Used to respond with the PINpad details for commissioning.
 */


/*!
 *  @method isDeveloperMode
 *
 *  @return boolean Is the library in dev host mode?
 */
-(bool)isDeveloperMode;
/*!
 *  @method isAuthorised
 *
 *  @return boolean Is there an authorised user?
 */
-(bool)isAuthorised;
/*!
 *  @method deauthorise
 *
 *  @discussion Deauthorise the current user
 */
-(void) deauthorise;

/*!
 *  @method getUserName
 *
 *  @return NSString The name of the user
 */
-(NSString *)getUserName;

/*!
 *  @method getHostRegion
 *
 *  @return NSString The host region the SDK is connected to
 */
-(NSString *)getHostRegion;

@end

