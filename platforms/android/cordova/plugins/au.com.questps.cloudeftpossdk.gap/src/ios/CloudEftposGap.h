//
//  CloudEftposGap.h
//  Snapweb
//
//  Created by Geoff Speirs on 28/04/2015.
//
//

#import <Cordova/CDVPlugin.h>

/*Cordova Plugin for interfacing with the CloudEftpos SDK.
 */
@interface CloudEftposGap : CDVPlugin

-(void)init:(CDVInvokedUrlCommand *)command;
-(void)isJailBroken:(CDVInvokedUrlCommand *)command;
-(void)setHostRegion:(CDVInvokedUrlCommand *)command;
-(void)connectDevice:(CDVInvokedUrlCommand *)command;
-(void)disconnectDevice:(CDVInvokedUrlCommand *)command;
-(void)setSupportedPaymentTerminals:(CDVInvokedUrlCommand *)command;
-(void)addSupportedPaymentTerminals:(CDVInvokedUrlCommand *)command;
-(void)isDeveloperMode:(CDVInvokedUrlCommand *)command;
-(void)isAuthorised:(CDVInvokedUrlCommand *)command;
-(void)deauthorise:(CDVInvokedUrlCommand *)command;
-(void)verifyCredentials:(CDVInvokedUrlCommand *)command;
-(void)authorisePOS:(CDVInvokedUrlCommand *)command;
-(void)pairDevice:(CDVInvokedUrlCommand *)command;
-(void)unpairDevice:(CDVInvokedUrlCommand *)command;
-(void)registerForStatusChanges:(CDVInvokedUrlCommand *)command;
-(void)startTransaction:(CDVInvokedUrlCommand *)command;
-(void)cancelTransaction:(CDVInvokedUrlCommand *)command;
-(void)recoverTransaction:(CDVInvokedUrlCommand *)command;
-(void)sleepDevice:(CDVInvokedUrlCommand *)command;
-(void)wakeDevice:(CDVInvokedUrlCommand *)command;
-(void)advancedMenu:(CDVInvokedUrlCommand *)command;
-(void)updatePINpad:(CDVInvokedUrlCommand *)command;
-(void)setiOSTheme:(CDVInvokedUrlCommand *)command;
-(void)emailReceipt:(CDVInvokedUrlCommand *)command;
@end
