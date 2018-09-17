//
//  CloudEftposGap.m
//  Snapweb
//
//  Created by Geoff Speirs on 28/04/2015.
//
//

#import "CloudEftposGap.h"
#import "CloudEftposSDK.h"

@implementation CloudEftposGap

-(void)init:(CDVInvokedUrlCommand *)command{
    BOOL productionMode = [[command.arguments objectAtIndex:0] boolValue];

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundeclared-selector"
    if (productionMode) {
        [[CloudEftpos sharedInstance] performSelector:@selector(forceProductionMode)];
    } else {
        [[CloudEftpos sharedInstance] performSelector:@selector(forceDeveloperMode)];
    }
#pragma clang diagnostic pop

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                  messageAsDictionary: nil];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)isJailBroken:(CDVInvokedUrlCommand *)command{
    BOOL isJailBroken = [CloudEftpos isJailBroken];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:isJailBroken ? CDVCommandStatus_OK : CDVCommandStatus_ERROR];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)setHostRegion:(CDVInvokedUrlCommand *)command{
    NSString *regionCode = [self unwrapNSNull:[command.arguments objectAtIndex:0]];
    [[CloudEftpos sharedInstance] setHostRegion:regionCode];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)connectDevice:(CDVInvokedUrlCommand *)command{
    [[CloudEftpos sharedInstance] connectDevice];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)disconnectDevice:(CDVInvokedUrlCommand *)command{
    BOOL success = [[CloudEftpos sharedInstance] disconnectDevice];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:success ? CDVCommandStatus_OK : CDVCommandStatus_ERROR];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)setSupportedPaymentTerminals:(CDVInvokedUrlCommand *)command{
    NSArray *terminalCodes = [self unwrapNSNull:command.arguments];
    [[CloudEftpos sharedInstance] setSupportedPaymentTerminals:terminalCodes];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)addSupportedPaymentTerminals:(CDVInvokedUrlCommand *)command{
    NSString *terminalCode = [self unwrapNSNull:[command.arguments objectAtIndex:0]];
    [[CloudEftpos sharedInstance] addSupportedPaymentTerminal:terminalCode];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)isDeveloperMode:(CDVInvokedUrlCommand *)command{
    BOOL developerMode = [[CloudEftpos sharedInstance] isDeveloperMode];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:developerMode ? CDVCommandStatus_OK : CDVCommandStatus_ERROR];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)isAuthorised:(CDVInvokedUrlCommand *)command{
    BOOL authorised = [[CloudEftpos sharedInstance] isAuthorised];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: authorised ? CDVCommandStatus_OK : CDVCommandStatus_ERROR];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)deauthorise:(CDVInvokedUrlCommand *)command{
    [[CloudEftpos sharedInstance] deauthorise];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)verifyCredentials:(CDVInvokedUrlCommand *)command{
    NSString * email = [self unwrapNSNull:[command.arguments objectAtIndex:0]];
    NSString * password = [self unwrapNSNull:[command.arguments objectAtIndex:1]];

    [[CloudEftpos sharedInstance] verifyCredentials:email password:password onCompletion:^(bool verified, NSError *error) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: (verified) ? CDVCommandStatus_OK : CDVCommandStatus_ERROR
                                                      messageAsString: (error) ? error.userInfo[NSLocalizedDescriptionKey] : nil];

        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

-(void)authorisePOS:(CDVInvokedUrlCommand *)command{
    NSString * posName = [self unwrapNSNull:[command.arguments objectAtIndex:0]];
    [[CloudEftpos sharedInstance] authorisePOS:posName onCompletion:^(bool authorised, NSError *error) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: (authorised) ? CDVCommandStatus_OK : CDVCommandStatus_ERROR
                                                      messageAsString: (error) ? error.userInfo[NSLocalizedDescriptionKey] : nil];

        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

-(void)pairDevice:(CDVInvokedUrlCommand *)command{
    BOOL animated = [[command.arguments objectAtIndex:0] boolValue];

    [[CloudEftpos sharedInstance] pairDeviceWithPresentingViewController:self.viewController animated:animated onCompletion:^(NSError *error) {
         CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: (error) ? CDVCommandStatus_ERROR : CDVCommandStatus_OK
                                                       messageAsString: (error) ? error.userInfo[NSLocalizedDescriptionKey] : nil];

        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

-(void)unpairDevice:(CDVInvokedUrlCommand *)command{
    [[CloudEftpos sharedInstance] unpairDevice];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                  messageAsDictionary: nil];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)registerForStatusChanges:(CDVInvokedUrlCommand *)command{
    [[CloudEftpos sharedInstance] registerForStatusChangesWithBlock:^(NSDictionary *status) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                      messageAsDictionary: status];
        pluginResult.keepCallback = [NSNumber numberWithBool:YES];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

-(void)startTransaction:(CDVInvokedUrlCommand *)command{
    NSDictionary * pluginRequest = [command.arguments objectAtIndex:0];
    TransactionRequest * transRequest = [[TransactionRequest alloc] init];
    transRequest.amount = [pluginRequest[@"amount"] intValue];
    transRequest.cashout = [pluginRequest[@"cashout"] intValue];
    transRequest.tipamount = [pluginRequest[@"tipamount"] intValue];
    transRequest.transactionType = [pluginRequest[@"transactionType"] intValue];
    transRequest.posReference = [self unwrapNSNull:pluginRequest[@"posReference"]];
    transRequest.posNotes = [self unwrapNSNull:pluginRequest[@"posNotes"]];
    transRequest.gpsLocation = [self unwrapNSNull:pluginRequest[@"gpsLocation"]];
    transRequest.posData1 = [self unwrapNSNull:pluginRequest[@"posData1"]];
    transRequest.posData2 = [self unwrapNSNull:pluginRequest[@"posData2"]];
    transRequest.verifyRefund = pluginRequest[@"verifyRefund"];
    transRequest.autoGpsLocation = pluginRequest[@"autoGpsLocation"];

    void (^displayBlock)(NSString *msg) = nil;
    void (^promptBlock)(NSString *text, bool inputRequired, NSArray *keys) = nil;
    void (^signaturePromptBlock)(NSString *receipt, NSArray *keys, signatureCaptureFallback fallbackBlock) = nil;
    if ([(NSNumber *)[command.arguments objectAtIndex:1] boolValue]) {
        displayBlock = ^(NSString *msg) {
            NSDictionary * result = @{@"type":@"display", @"msg":msg};
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                          messageAsDictionary: result];
            pluginResult.keepCallback = [NSNumber numberWithBool:YES];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        };
    }
    if ([(NSNumber *)[command.arguments objectAtIndex:2] boolValue]) {
        promptBlock = ^(NSString *text, bool inputRequired, NSArray *keys) {
            NSDictionary * result = @{@"type":@"prompt", @"text":text,
                                      @"inputRequired": [NSNumber numberWithBool:inputRequired],
                                      @"keys": keys};
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                          messageAsDictionary: result];
            pluginResult.keepCallback = [NSNumber numberWithBool:YES];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        };
    }
    if ([(NSNumber *)[command.arguments objectAtIndex:3] boolValue]) {
        signaturePromptBlock = ^(NSString *receipt, NSArray *keys, signatureCaptureFallback fallbackBlock) {
            NSDictionary * result = @{@"type":@"signature", @"receipt":receipt, @"keys": keys};
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                          messageAsDictionary: result];
            pluginResult.keepCallback = [NSNumber numberWithBool:YES];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        };
    }


    [[CloudEftpos sharedInstance] startTransaction:transRequest
                displayBlock:displayBlock
                 promptBlock:promptBlock
        signaturePromptBlock:signaturePromptBlock
    withPresentingViewController:self.viewController
                    animated:[(NSNumber *)[command.arguments objectAtIndex:4] boolValue]
                onCompletion:^(NSDictionary *result, NSError *error) {
        CDVPluginResult *pluginResult;
        if (error){
            pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_ERROR
                                             messageAsString: error.userInfo[NSLocalizedDescriptionKey]];
        }
        else{
            pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                         messageAsDictionary: [self fixedDateTimeDictionary:result]];
        }
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

-(void)promptResponse:(CDVInvokedUrlCommand *)command{
    [[CloudEftpos sharedInstance] promptResponse:[command.arguments objectAtIndex:0]
              withText:[command.arguments objectAtIndex:1]];
}

-(void)cancelTransaction:(CDVInvokedUrlCommand *)command{
    [[CloudEftpos sharedInstance] cancelTransaction];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                  messageAsDictionary: nil];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)recoverTransaction:(CDVInvokedUrlCommand *)command{
    NSString * posReference = [self unwrapNSNull:[command.arguments objectAtIndex:0]];
    TransactionType transactionType = [[command.arguments objectAtIndex:1] intValue];
    UInt32 amount = [[command.arguments objectAtIndex:2] intValue];
    BOOL animated = [[command.arguments objectAtIndex:3] boolValue];


    [[CloudEftpos sharedInstance] recoverTransactionWithPosReference:posReference transactionType:transactionType amount:amount withPresentingViewController:self.viewController animated:animated onCompletion:^(NSDictionary *result, NSError *error) {
        CDVPluginResult *pluginResult;
        if (error){
            pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_ERROR
                                             messageAsString: error.userInfo[NSLocalizedDescriptionKey]];
        }
        else{
            pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                         messageAsDictionary: [self fixedDateTimeDictionary:result]];
        }
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

-(void)sleepDevice:(CDVInvokedUrlCommand *)command{
    [[CloudEftpos sharedInstance] sleepDevice];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                  messageAsDictionary: nil];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)wakeDevice:(CDVInvokedUrlCommand *)command{
    [[CloudEftpos sharedInstance] wakeDevice];
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                  messageAsDictionary: nil];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)advancedMenu:(CDVInvokedUrlCommand *)command{
    BOOL animated = [[command.arguments objectAtIndex:0] boolValue];
    [[CloudEftpos sharedInstance] advancedMenuWithPresentingViewController:self.viewController animated:animated onClose:^{
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                      messageAsDictionary: nil];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    } onPrint:^(NSString *type, NSString *receipt) {
        NSDictionary * result = @{@"type":type, @"receipt":receipt};
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                      messageAsDictionary: result];
        pluginResult.keepCallback = [NSNumber numberWithBool:YES];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

-(void)updatePINpad:(CDVInvokedUrlCommand *)command{
    BOOL animated = [[command.arguments objectAtIndex:0] boolValue];
    [[CloudEftpos sharedInstance] updatePINpadWithPresentingViewController:self.viewController animated:animated onCompletion:^(NSError *error) {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: (error) ? CDVCommandStatus_ERROR : CDVCommandStatus_OK
                                                          messageAsString: (error) ? error.userInfo[NSLocalizedDescriptionKey] : nil];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

-(void)setiOSTheme:(CDVInvokedUrlCommand *)command{
    NSString * navBarColor = [self unwrapNSNull:[command.arguments objectAtIndex:0]];
    NSString * navBarTitleColor = [self unwrapNSNull:[command.arguments objectAtIndex:1]];
    NSString * navBarTitleShadowColor = [self unwrapNSNull:[command.arguments objectAtIndex:2]];
    NSString * navBarTintColor = [self unwrapNSNull:[command.arguments objectAtIndex:3]];
    NSString * statusBarStyle = [self unwrapNSNull:[command.arguments objectAtIndex:4]];

    [CloudEftpos sharedInstance].navigationBarColor = [self colorFromHexString:navBarColor];
    [CloudEftpos sharedInstance].navigationBarTitleColor = [self colorFromHexString:navBarTitleColor];
    [CloudEftpos sharedInstance].navigationBarTitleShadowColor = [self colorFromHexString:navBarTitleShadowColor];
    [CloudEftpos sharedInstance].navigationBarTintColor = [self colorFromHexString:navBarTintColor];

    if ([statusBarStyle isEqualToString:@"UIStatusBarStyleLightContent"]){
        [CloudEftpos sharedInstance].statusBarStyle = UIStatusBarStyleLightContent;
    }
    else if ([statusBarStyle isEqualToString:@"UIStatusBarStyleDefault"]){
        [CloudEftpos sharedInstance].statusBarStyle = UIStatusBarStyleDefault;
    }
    else if ([statusBarStyle isEqualToString:@"UIStatusBarStyleBlackTranslucent"]){
        [CloudEftpos sharedInstance].statusBarStyle = UIStatusBarStyleBlackTranslucent;
    }
    else if ([statusBarStyle isEqualToString:@"UIStatusBarStyleBlackOpaque"]){
        [CloudEftpos sharedInstance].statusBarStyle = UIStatusBarStyleBlackOpaque;
    }

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                  messageAsDictionary: nil];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

-(void)emailReceipt:(CDVInvokedUrlCommand *)command{
    NSString * posReference     = [self unwrapNSNull:[command.arguments objectAtIndex:0]];
    NSString * transactionGuid  = [self unwrapNSNull:[command.arguments objectAtIndex:1]];
    NSString * emailAddress     = [self unwrapNSNull:[command.arguments objectAtIndex:2]];

    BOOL sent = [[CloudEftpos sharedInstance] emailReceipt:posReference transactionGuid:transactionGuid emailAddress:emailAddress];
    CDVPluginResult * pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK messageAsBool:sent];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark Private Methods:

-(UIColor *)colorFromHexString:(NSString *)hexString {
    unsigned rgbValue = 0;
    NSString *colorString = [[hexString stringByReplacingOccurrencesOfString: @"#" withString: @""] uppercaseString];
    NSScanner *scanner = [NSScanner scannerWithString:colorString];
    [scanner scanHexInt:&rgbValue];
    return [UIColor colorWithRed:((rgbValue & 0xFF0000) >> 16)/255.0 green:((rgbValue & 0xFF00) >> 8)/255.0 blue:(rgbValue & 0xFF)/255.0 alpha:1.0];
}

//Required because JSON encoding doesn't handle NSDates. Also needs to match the output from the Android SDK.
-(NSDictionary *)fixedDateTimeDictionary:(NSDictionary *)dictionary{
    NSDateFormatter * formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"yyyyMMddHHmmss"];
    NSMutableDictionary * fixedDictionary = [NSMutableDictionary dictionaryWithDictionary:dictionary];
    fixedDictionary[@"dateTime"] = [formatter stringFromDate:[NSDate date]];
    [fixedDictionary removeObjectForKey:@"signatureImage"];
    [fixedDictionary removeObjectForKey:@"signaturePath"];
    return fixedDictionary;
}

-(id)unwrapNSNull:(id)obj{
    return ([obj isEqual:[NSNull null]]) ? nil : obj;
}
@end
