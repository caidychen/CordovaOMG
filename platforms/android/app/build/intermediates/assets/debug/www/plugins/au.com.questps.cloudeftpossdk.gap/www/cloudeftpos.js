cordova.define("au.com.questps.cloudeftpossdk.gap.cloudeftpossdk", function(require, exports, module) {

var exec = require('cordova/exec');
var cordova = require('cordova');

function TransactionRequest(transactionType, posReference, amount) {
    this.transactionType   = typeof transactionType !== 'undefined' ? transactionType : 1;
    this.posReference      = typeof posReference !== 'undefined' ? posReference : null;
    this.amount            = typeof amount !== 'undefined' ? amount : 0;
    this.cashout = 0;
    this.tipAmount = 0;
    this.verifyRefund = false;
    this.autoGpsLocation = false;
}
TransactionRequest.PURCHASE = 1;
TransactionRequest.REFUND = 2;

/**
 * Initialises the Cloud EFTPOS SDK
 * @param {boolean} productionMode - Set the SDK to production mode
 * @param {function()} onSDKLoaded - Callback for when the SDK finishes initialising
 * @return {CloudEftposSDK} The CloudEftposSDK object
 */
function CloudEftposSDK(productionMode, onSDKLoaded) {
    productionMode      = typeof productionMode !== 'undefined' ? productionMode : true;
    onSDKLoaded         = typeof onSDKLoaded !== 'undefined' ? onSDKLoaded : function() {};

    exec(onSDKLoaded,
         null,
         "CloudEftposGap",
         "init",
         [productionMode]);
}

/**
 *  Verifies that user's iOS Device is JailBroken
 *  @param {function({boolean} isJailBroken)} onCompletion
 *  - False if user's deivce has not been jailbroken, otherwise true
 */
// CloudEftposSDK.prototype.isJailBroken = function(onCompletion){
//   onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
//   exec(function() { onCompletion(true); },
//        function() { onCompletion(false); },
//        "CloudEftposGap",
//        "isJailBroken",
//        []);
// }

/**
 *  Sets the host of the SDK to use the specified region code.
 *  @param regionCode The 2 character region code for the preferred region.
 *  See the full list of available regions in the SDK documentation.
 *  Defaults to "au" (Australia)
 *  This value is persistent, so once it is set it only needs to be called
 *  again to change the value (which should generally not happen!)
 */
CloudEftposSDK.prototype.setHostRegion = function(regionCode) {
  exec(null,
       null,
       "CloudEftposGap",
       "setHostRegion",
       [regionCode]);
}

/**
 *  Begins the discovery process for connecting to the last
 *  connected device. If the device hasn't been previously paired nothing
 *  will happen.
 */
CloudEftposSDK.prototype.connectDevice = function() {
  exec(null,
       null,
       "CloudEftposGap",
       "connectDevice",
       []);
}

/*!
 *  Disconnects the device without unpairing it. Automatic
 *  device discovery will be disabled until connectDevice is called.
 *  @param {function({boolean} success)} onCompletion
 *  - False if there was no device connected, otherwise true
 */
CloudEftposSDK.prototype.disconnectDevice = function(onCompletion) {
  onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
  exec(function() { onCompletion(true); },
       function() { onCompletion(false); },
       "CloudEftposGap",
       "disconnectDevice",
       []);
}

/*!
 *  Overrides the available payment termanal types based on
 *  the supplied codes.
 *  @param terminalCodes The available terminals by code.
 */
CloudEftposSDK.prototype.setSupportedPaymentTerminals = function(terminalCodes) {
  terminalCodes = Array.isArray(terminalCodes) ? terminalCodes : []
  exec(null,
       null,
       "CloudEftposGap",
       "setSupportedPaymentTerminals",
       terminalCodes);
}

/*!
 *  Adds the provided terminal type to the list of available
 *  terminals.
 *  @param terminalCode The terminal code.
 */
CloudEftposSDK.prototype.addSupportedPaymentTerminal = function(terminalCode) {
  exec(null,
       null,
       "CloudEftposGap",
       "addSupportedPaymentTerminal",
       [terminalCode]);
}

/*!
 *  Verifies that SDK is running in Developer Mode
 *  @param {function({boolean} isDeveloperMode} onCompletion
 */
// CloudEftposSDK.prototype.isDeveloperMode = function(onCompletion) {
//   onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
//   exec(function() { onCompletion(true); },
//        function() { onCompletion(false); },
//        "CloudEftposGap",
//        "isDeveloperMode",
//        []);
// }

/*!
 *  Verifies that the current user is authorised
 *  @param {function({boolean} isAuthorised} onCompletion
 */
CloudEftposSDK.prototype.isAuthorised = function(onCompletion) {
  onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
  exec(function() { onCompletion(true); },
       function() { onCompletion(false); },
       "CloudEftposGap",
       "isAuthorised",
       []);
}

/*!
 *  Deauthorise the current user
 */
CloudEftposSDK.prototype.deauthorise = function() {
  exec(null,
       null,
       "CloudEftposGap",
       "deauthorise",
       []);
}

/**
 * Verifies that a user (for the given email and password) is authorised to
 * interact with the CloudEFTPOS system.
 * @param {string} email - The email address of the authenticating user
 * @param {string} password - The password of the authenticating user
 * @param {function({boolean} authorised, {string} error)} onCompletion
 *  - Called on completion with an authorised flag and an error string if there
 *    was an error.
 */
CloudEftposSDK.prototype.verifyCredentials = function(email, password, onCompletion) {
    onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
    exec(function(result) { onCompletion(true, null); },
         function(error) { onCompletion(false, error); },
         "CloudEftposGap",
         "verifyCredentials",
         [email, password]);
}

/**
 * Adds this POS device as an authorised POS
 * @param {string} posName - The name for this POS device (eg. the device name)
 * @param {function({boolean} authorised, {string} error)} onCompletion
 *  - Called on completion with an authorised flag and an error string if there
 *    was an error.
 */
CloudEftposSDK.prototype.authorisePOS = function(posName, onCompletion) {
    onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
    exec(function(result) { onCompletion(true, null); },
         function(error) { onCompletion(false, error); },
         "CloudEftposGap",
         "authorisePOS",
         [posName]);
}

/**
 * Verifies the user and authorises the POS in one call.
 * @param {string} email - The email address of the authenticating user
 * @param {string} password - The password of the authenticating user
 * @param {string} posName - The name for this POS device (eg. the device name)
 * @param {function({boolean} authorised, {string} error)} onCompletion
 *  - Called on completion with an authorised flag and an error string if there
 *    was an error.
 */
CloudEftposSDK.prototype.fullAuth = function(email, password, posName, onCompletion) {
    onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
    _this = this;
    this.verifyCredentials(email, password, function(success, error) {
       if (!success) {
           onCompletion(success, error);
           return;
       }
       _this.authorisePOS(posName, onCompletion);
   });
}

/**
 * Displays the pairing screen in order to pair to a new PINpad
 * @param {boolean} animated - Whether to animate the screen transition
 * @param {function({string} error)} onCompletion
 *  - Called on completion with an optional error string.
 */
CloudEftposSDK.prototype.pairDevice = function(animated, onCompletion) {
    animated        = typeof animated !== 'undefined' ? animated : true;
    onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
    exec(onCompletion,
         function(error) { onCompletion(error); },
         "CloudEftposGap",
         "pairDevice",
         [animated]);
}

/**
 * Unpairs from any currently paired PINpad.
 */
CloudEftposSDK.prototype.unpairDevice = function() {
    exec(null,
         null,
         "CloudEftposGap",
         "unpairDevice",
         []);
}

/**
 * Registers a callback to be called when the SDK status changes. This should
 * be called immediately after initialising the SDK.
 * @param {function({object} status)} statusChanged
 *  - Called whenever the status of the SDK changes.
 */
CloudEftposSDK.prototype.registerForStatusChanges = function(statusChanged) {
    statusChanged    = typeof statusChanged !== 'undefined' ? statusChanged : function() {};
    exec(function(response) { statusChanged(response); },
         null,
         "CloudEftposGap",
         "registerForStatusChanges",
         []);
}
/**
 * status = {
 *  batteryLevel:   {number}  - The percentage of battery remaining (0-100).
 *  ready:          {boolean} - Is the PINpad ready to transact?
 *  connected:      {boolean} - Is the PINpad connected?
 *  paired:         {boolean} - Has a PINpad previously been connected?
 *  awake:          {boolean} - Is the PINpad awake?
 *  updateAvailable:{boolean} - Is there an update available for the PINpad?
 *  pinpadName:     {string}  - The serial of the currently paired PINpad.
 *  pinpadBanks:    {object}  - A disctionary of bank on the connected PINpad.
 *                              The key is the name of the bank. Each key points
 *                              to an object contaning the aiic, caid, catid,
 *                              and ppid.
 * }
 */

/**
 * Initialises the TransactionRequest object
 * @param {enum} transactionType - Either TransactionRequest.PURCHASE or
 *                                 TransactionRequest.REFUND
 * @param {string} posReference - The pos reference for the transaction
 * @param {number} amount - The amount of the transaction in cents
 * @return {TransactionRequest} The TransactionRequest object
 *
 * @properties
 *  amount:         {number}  - The amount in cents of the purchase or refund
 *                              excluding any cashout or tip amounts.
 *  cashOut:        {number}  - An amount in cents indicating cashout amount.
 *                              0 if none. -1 for the PINpad to prompt.
 *                              Defaults to 0.
 *  tipAmount:      {number}  - An amount in cents indicating a tip. 0 if none.
 *                              Defaults to 0.
 *  transactionType:{number}  - TransactionRequest.PURCHASE or .REFUND
 *                              Defaults to PURCHASE.
 *  posReference:   {string}  - A 12 character reference for this transaction.
 *  posNotes:       {string}  - Optional notes for a transaction to be stored
 *                              online.
 *  gpsLocation:    {string}  - An optional GPS location formatted as a string
 *                              "LAT,LON" where LAT and LON are doubles.
 *  autoGpsLocation {boolean} - If set the SDK will automatically determine the
 *                              GPS location for this transaction. Defaults to
 *                              false.
 *  verifyRefund:   {boolean} - Whether refunds should automatically prompt for
 *                              a passwcode. Defaults to True.
 */

/**
 * Initiates a transaction with the given details. Displays a transaction screen
 * to the operator.
 * @param {object} transactionRequest - A transaction request object.
 * @param {boolean} animated - Whether to animate the screen transition
 * @param {function({object} results, {string} error)} onCompletion
 *  - Called with a results object and an optional error string.
 */
CloudEftposSDK.prototype.startTransaction = function(transactionRequest, animated, onCompletion) {
    this.startTransactionExtended(transactionRequest, null, null, null, animated, onCompletion);
}

/**
 * result = {
 *  approved:        {boolean} - Approved (True) or declined (False)
 *  receipt:         {string}  - The EFTPOS receipt
 *  signatureReceipt:{string}  - The EFTPOS signature receipt (optional)
 *  responseCode:    {string}  - See response codes section of SDK
 *  responseText:    {string}  - Description of response
 *  amount:          {number}  - The amount processed for the transaction
 *                               excluding surcharge, cashout or tip.
 *  cashOut:         {number}  - The amount added for cashout.
 *  tipAmount:       {number}  - The amount added for tip.
 *  surcharge:       {number}  - The amount added for surcharge.
 *  account:         {string}  - The account selected by the customer
 *                               (lowercase).
 *  CAID:            {string}  - Merchant ID
 *  CATID:           {string}  - Terminal ID
 *  posReference:    {string}  - The POS reference used
 *  dateTime:        {string}  - The date and time of the transaction (YYYYMMDDHHmmss)
 *  authID:          {string}  - Unique auth ID from the bank
 *  STAN:            {string}  - Unique System Trace Audit Number from PINpad
 *  settlementDate:  {string}  - Settlement date formatted as MMDD
 *  truncatedPAN:    {string}  - A truncated copy of the card PAN
 *  cardName:        {string}  - The type of card used (eg: DEBIT, VISA, etc)
 *  businessName:    {string}  - The name configured for this business
 *  businessABN:     {string}  - The ABN configured for this business
 *  guid:            {string}  - A GUID that can be used for receipt lookups
 *  receiptURL:      {string}  - The URL of the receipt
 * }
 */

 /**
  * Initiates a transaction with the given details. Displays a transaction screen
  * to the operator.
  * @param {object} transactionRequest - A transaction request object.
  * @param {function({string} text)} displayCallback
  *  - Called by the SDK when it has text to display (should generally be null)
  * @param {function({string} text, {boolean} input_required, {[string]} keys)} promptCallback
  *  - Called by the SDK when it has requires that the user provide input
  * @param {function({string} receipt, {[string]} keys)} signatureCallback
  *  - Called by the SDK when it requires that the customer sign a receipt
  * @param {boolean} animated - Whether to animate the screen transition
  * @param {function({object} results, {object} error)} onCompletion
  *  - Called with a results object and an optional error string.
  */
 CloudEftposSDK.prototype.startTransactionExtended = function(transactionRequest, displayCallback, promptCallback, signatureCallback, animated, onCompletion) {
     animated        = typeof animated !== 'undefined' ? animated : true;
     onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
     var hasDC = displayCallback !== null && displayCallback !== undefined;
     var hasPC = promptCallback !== null && promptCallback !== undefined;
     var hasSC = signatureCallback !== null && signatureCallback !== undefined;
     exec(function(response) {
            if (response.type === "display") {
              displayCallback(response.msg);
            } else if (response.type === "prompt") {
              promptCallback(response.text, response.inputRequired, response.keys);
            } else if (response.type === "signature") {
              signatureCallback(response.receipt, response.keys);
            } else {
              onCompletion(response, null);
            }
          },
          function(error) { onCompletion(null, error); },
          "CloudEftposGap",
          "startTransaction",
          [transactionRequest, hasDC, hasPC, hasSC, animated]);
 }

 /**
  * This method should be called to respond to a promptCallback or a
  * signatureCallback.
  * @param {string} key - The key that was pressed.
  * @param {string} text - Any optional input that was entered.
  */
 CloudEftposSDK.prototype.promptResponse = function(key, text) {
    key   = typeof key !== 'undefined' ? key : null;
    text  = typeof text !== 'undefined' ? text : null;
    exec(null,
         null,
         "CloudEftposGap",
         "promptResponse",
         [key, text]);
 }

/**
 * Attempts to cancel a current transaction.
 */
CloudEftposSDK.prototype.cancelTransaction = function() {
    exec(null,
         null,
         "CloudEftposGap",
         "cancelTransaction",
         []);
}

/**
 * This method must be called to recover any transaction in the
 * case of the POS crashing or losing power. It will handle stepping the
 * user through reconnecting their microPay and recovering the last
 * transaction.
 * @param {string} posReference - The 12 character posReference used for the
 *                                transaction.
 * @param {number} transactionType - The type of transaction (1 for Purchase,
 *                                   2 for Refund)
 * @param {number} amount - An optional amount to compare against. 0 to match
 *                          any amount.
 * @param {boolean} animated - Whether to animate the screen transition
 * @param {function({object} result, {string} error)} onCompletion
 *  - Analogous to the startTransaction onCompletion callback.
 */
CloudEftposSDK.prototype.recoverTransaction = function(posReference, transactionType, amount, animated, onCompletion) {
    posReference    = typeof posReference !== 'undefined' ? posReference : "";
    transactionType = typeof transactionType !== 'undefined' ? transactionType : 0;
    amount          = typeof amount !== 'undefined' ? amount : 0;
    animated        = typeof animated !== 'undefined' ? animated : true;
    onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
    exec(function(response) { onCompletion(response, null); },
         function(error) { onCompletion(null, error); },
         "CloudEftposGap",
         "recoverTransaction",
         [posReference, transactionType, amount, animated]);
}

/**
 * Puts the PINpad into a sleep state that preserves battery power.
 */
CloudEftposSDK.prototype.sleepDevice = function() {
    exec(null,
         null,
         "CloudEftposGap",
         "sleepDevice",
         []);
}

/**
 * Wakes the PINpad up from its sleep state.
 */
CloudEftposSDK.prototype.wakeDevice = function() {
    exec(null,
         null,
         "CloudEftposGap",
         "wakeDevice",
         []);
}

/**
 * Displays a menu to perform advanced functions with the PINpad.
 * @param {boolean} animated - Whether to animate the screen transition
 * @param {function()} onClose
 *  - Called when the Tools menu closes.
 * @param {function({string} type, {string} receipt)} onPrint
 *  - Called if any prints are initiated from the Tools menu.
 */
CloudEftposSDK.prototype.advancedMenu = function(animated, onClose, onPrint) {
    animated        = typeof animated !== 'undefined' ? animated : true;
    onClose    = typeof onClose !== 'undefined' ? onClose : function() {};
    onPrint    = typeof onPrint !== 'undefined' ? onPrint : function() {};
    exec(function(response) {
        // the onClose response in OS will be null, in Adroid it will be 'OK'.
        if (typeof response === 'undefined' || response === null || response === 'OK')
                onClose();
            else
                onPrint(response['type'], response['receipt']);
        },
        null,
        "CloudEftposGap",
        "advancedMenu",
        [animated]);
}

/**
 * Checks if there is an update ready for the PINpad, downloads it and applies
 * it.
 * @param {boolean} animated - Whether to animate the screen transition
 * @param {function({string} error)} onCompletion
 *  - Called on completion of the update with an optional error message.
 */
CloudEftposSDK.prototype.updatePINpad = function(animated, onCompletion) {
    animated        = typeof animated !== 'undefined' ? animated : true;
    onCompletion    = typeof onCompletion !== 'undefined' ? onCompletion : function() {};
    exec(function(error) { onCompletion(null); },
         function(error) { onCompletion(error); },
         "CloudEftposGap",
         "updatePINpad",
         [animated]);
}

/**
 * Set the theme to use for any SDK screens.
 * @param {string} navigationBarColor - The NavBar colour
 * @param {string} navigationBarTitleColor - The NavBar text colour
 * @param {string} navigationBarTitleShadowColor - The NavBar text shadow colour
 * @param {string} navigationBarTintColor - The NavBar back icon colour
 * @param {string} statusBarStyle - Either UIStatusBarStyleLightContent or
 *                                  UIStatusBarStyleDarkContent
 */
CloudEftposSDK.prototype.setiOSTheme = function(navigationBarColor, navigationBarTitleColor, navigationBarTitleShadowColor, navigationBarTintColor, statusBarStyle) {
    // Colors in Hex
    // StatusBarStyle, string of:
    //  UIStatusBarStyleLightContent
    //  UIStatusBarStyleDarkContent
    exec(null,
         null,
         "CloudEftposGap",
         "setiOSTheme",
         [navigationBarColor, navigationBarTitleColor, navigationBarTitleShadowColor, navigationBarTintColor, statusBarStyle]);
}

/**
 * Set the theme to use for any SDK screens.
 * @param {string} posReference - The posReference used for the transaction
 * @param {string} transactionGuid - The guid provided by the transaction result
 * @param {string} emailAddress - An email address to send the receipt to.
 */
CloudEftposSDK.prototype.emailReceipt = function(posReference, transactionGuid, emailAddress, onCompletion) {
    exec(function(error) { onCompletion(true); },
         function(error) { onCompletion(false); },
         "CloudEftposGap",
         "emailReceipt",
         [posReference, transactionGuid, emailAddress]);
}

/**
 * Set the theme to use for any SDK screens.
 * @param {string} themeIdentifier - The resource name for the theme.
 */
CloudEftposSDK.prototype.setAndroidTheme = function(themeIdentifier) {
    // The theme Identifier (name) as a string
    exec(null,
         null,
         "CloudEftposGap",
         "setAndroidTheme",
         [themeIdentifier]);
};

module.exports = {
    TransactionRequest: TransactionRequest,
    CloudEftposSDK: CloudEftposSDK
};


});
