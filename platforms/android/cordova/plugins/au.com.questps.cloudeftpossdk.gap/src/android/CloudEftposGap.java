package au.com.questps.cloudeftpossdk;

import android.app.Activity;

import org.apache.cordova.CordovaWebView;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.questps.cloudeftpossdk.CloudEftposSDK;
import com.questps.cloudeftpossdk.callbacks.OnAdvancedMenuClosed;
import com.questps.cloudeftpossdk.callbacks.OnAuthCompleted;
import com.questps.cloudeftpossdk.callbacks.OnDisplayUpdate;
import com.questps.cloudeftpossdk.callbacks.OnPairingCompleted;
import com.questps.cloudeftpossdk.callbacks.OnPrint;
import com.questps.cloudeftpossdk.callbacks.OnPromptUpdate;
import com.questps.cloudeftpossdk.callbacks.OnSDKLoaded;
import com.questps.cloudeftpossdk.callbacks.OnSignaturePrompt;
import com.questps.cloudeftpossdk.callbacks.OnStatus;
import com.questps.cloudeftpossdk.callbacks.OnTransactionCompleted;
import com.questps.cloudeftpossdk.callbacks.OnUpdateCompleted;
import com.questps.cloudeftpossdk.messages.AuthCompleted;
import com.questps.cloudeftpossdk.messages.DisplayData;
import com.questps.cloudeftpossdk.messages.ErrorResult;
import com.questps.cloudeftpossdk.messages.PairingCompleted;
import com.questps.cloudeftpossdk.messages.PrintData;
import com.questps.cloudeftpossdk.messages.PromptData;
import com.questps.cloudeftpossdk.messages.SignaturePromptData;
import com.questps.cloudeftpossdk.messages.StatusChange;
import com.questps.cloudeftpossdk.messages.TransactionCompleted;
import com.questps.cloudeftpossdk.messages.TransactionRequest;
import com.questps.cloudeftpossdk.messages.UpdateCompleted;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class CloudEftposGap extends CordovaPlugin {
    public static final String TAG = "CloudEftposGap";

    private static CloudEftposSDK cloudEftpos;

    /**
     * Constructor.
     */
    public CloudEftposGap() {
    }

    /**
     * Sets the context of the Command. This can then be used to do things like
     * get file paths associated with the Activity.
     *
     * @param cordova The context of the main Activity.
     * @param webView The CordovaWebView Cordova is running in.
     */
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
    }

    @Override
    public boolean execute(String action, JSONArray args, final CallbackContext callbackContext) throws JSONException {
        if (action.equals("init")) {
            this.init(args.getBoolean(0), callbackContext);
            return true;
        }
        if (cloudEftpos == null)
            return false;
        if (action.equals("setHostRegion")) {
            this.setHostRegion(args.getString(0), callbackContext);
            return true;
        }

        if (action.equals("connectDevice")) {
            this.connectDevice(callbackContext);
            return true;
        }

        if (action.equals("disconnectDevice")) {
            this.disconnectDevice(callbackContext);
            return true;
        }

        if (action.equals("setSupportedPaymentTerminals")) {
            this.setSupportedPaymentTerminals(args, callbackContext);
            return true;
        }

        if (action.equals("addSupportedPaymentTerminal")) {
            this.addSupportedPaymentTerminal(args.getString(0), callbackContext);
            return true;
        }

        if (action.equals("isAuthorised")) {
            this.isAuthorised(callbackContext);
            return true;
        }

        if (action.equals("deauthorise")) {
            this.deauthorise(callbackContext);
            return true;
        }

        if (action.equals("setAndroidTheme")) {
            this.setAndroidTheme(args.getString(0), callbackContext);
            return true;
        }
        if (action.equals("verifyCredentials")) {
            this.verifyCredentials(args.getString(0), args.getString(1), callbackContext);
            return true;
        }
        if (action.equals("authorisePOS")) {
            this.authorisePOS(args.getString(0), callbackContext);
            return true;
        }
        if (action.equals("verifyCredentials")) {
            this.verifyCredentials(args.getString(0), args.getString(1), callbackContext);
            return true;
        }
        if (action.equals("pairDevice")) {
            this.pairDevice(args.getBoolean(0), callbackContext);
            return true;
        }
        if (action.equals("unpairDevice")) {
            this.unpairDevice(callbackContext);
            return true;
        }
        if (action.equals("registerForStatusChanges")) {
            this.registerForStatusChanges(callbackContext);
            return true;
        }
        if (action.equals("startTransaction")) {
            this.startTransaction(args.getJSONObject(0), args.getBoolean(1), args.getBoolean(2), args.getBoolean(3), args.getBoolean(4), callbackContext);
            return true;
        }
        if (action.equals("promptResponse")) {
            this.promptResponse(args.getString(0), args.getString(1), callbackContext);
            return true;
        }
        if (action.equals("cancelTransaction")) {
            this.cancelTransaction(callbackContext);
            return true;
        }
        if (action.equals("recoverTransaction")) {
            this.recoverTransaction(args.getString(0), args.getInt(1), args.getInt(2), args.getBoolean(3), callbackContext);
            return true;
        }
        if (action.equals("sleepDevice")) {
            this.sleepDevice(callbackContext);
            return true;
        }
        if (action.equals("wakeDevice")) {
            this.wakeDevice(callbackContext);
            return true;
        }
        if (action.equals("advancedMenu")) {
            this.advancedMenu(args.getBoolean(0), callbackContext);
            return true;
        }
        if (action.equals("updatePINpad")) {
            this.updatePINpad(args.getBoolean(0), callbackContext);
            return true;
        }
        if (action.equals("emailReceipt")) {
            this.emailReceipt(args.getString(0), args.getString(1), args.getString(2), callbackContext);
            return true;
        }
        return false;
    }

    private void init(final Boolean productionMode, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos = new CloudEftposSDK(cordova.getActivity().getApplicationContext(), productionMode, new OnSDKLoaded() {
                    @Override
                    public void OnSDKLoaded() {
                        callbackContext.success();
                    }
                });
            }
        });
    }

    private void setHostRegion(final String regionCode, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.SetHostRegion(regionCode);
                callbackContext.success();
            }
        });
    }

    private void connectDevice(final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.ConnectDevice();
                callbackContext.success();
            }
        });
    }

    private void disconnectDevice(final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Boolean success = cloudEftpos.DisconnectDevice();
                PluginResult.Status status = success ? PluginResult.Status.OK : PluginResult.Status.ERROR;
                PluginResult pluginResult = new PluginResult(status);
                callbackContext.sendPluginResult(pluginResult);
            }
        });
    }

    private void setSupportedPaymentTerminals(final JSONArray terminalCodes, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ArrayList<String> list = new ArrayList<String>();
                if (terminalCodes != null) {
                    int len = terminalCodes.length();
                    for (int i = 0; i < len; i++) {
                        try {
                            list.add(terminalCodes.getString(i));
                        } catch (JSONException e) {
                        }
                    }
                }
                cloudEftpos.SetSupportedPaymentTerminals(list);
                callbackContext.success();
            }
        });
    }

    private void addSupportedPaymentTerminal(final String terminalCode, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.AddSupportedPaymentTerminal(terminalCode);
                callbackContext.success();
            }
        });
    }

    private void isAuthorised(final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Boolean isAuthorised = cloudEftpos.IsAuthenticated();
                PluginResult.Status status = isAuthorised ? PluginResult.Status.OK : PluginResult.Status.ERROR;
                PluginResult pluginResult = new PluginResult(status);
                callbackContext.sendPluginResult(pluginResult);
            }
        });
    }

    private void deauthorise(final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.Deauthorise();
                callbackContext.success();
            }
        });
    }

    private void setAndroidTheme(final String themeName, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Activity activity = cordova.getActivity();
                final int themeId = activity.getResources().getIdentifier(themeName, "style", activity.getPackageName());
                cloudEftpos.SetThemeResource(themeId);
                callbackContext.success();
            }
        });
    }

    private void verifyCredentials(final String email, final String password, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.VerifyCredentials(email, password, new OnAuthCompleted() {
                    @Override
                    public void OnAuthComplete(AuthCompleted authCompleted) {
                        PluginResult.Status status = (authCompleted.authorised) ? PluginResult.Status.OK : PluginResult.Status.ERROR;
                        PluginResult pluginResult = new PluginResult(status, authCompleted.error.description);
                        callbackContext.sendPluginResult(pluginResult);
                    }
                });
            }
        });
    }

    private void authorisePOS(final String posName, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.AuthorisePOS(posName, new OnAuthCompleted() {
                    @Override
                    public void OnAuthComplete(AuthCompleted authCompleted) {
                        PluginResult.Status status = (authCompleted.authorised) ? PluginResult.Status.OK : PluginResult.Status.ERROR;
                        PluginResult pluginResult = new PluginResult(status, authCompleted.error.description);
                        callbackContext.sendPluginResult(pluginResult);
                    }
                });
            }
        });
    }

    private void pairDevice(final Boolean animated, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.PairDevice(animated, new OnPairingCompleted() {
                    @Override
                    public void OnComplete(PairingCompleted pairingCompleted) {
                        PluginResult.Status status = (pairingCompleted.errorCode == null) ? PluginResult.Status.OK: PluginResult.Status.ERROR;
                        String errorString = (pairingCompleted.errorCode == null) ? null : pairingCompleted.errorCode.description;
                        PluginResult pluginResult = new PluginResult(status, errorString);
                        callbackContext.sendPluginResult(pluginResult);
                    }
                });
            }
        });
    }

    private void unpairDevice(final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.UnpairDevice();
                callbackContext.success();
            }
        });
    }

    private void registerForStatusChanges(final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.RegisterForStatusChanges(new OnStatus() {
                    private JSONObject getBanks(StatusChange statusChange) throws JSONException {
                        JSONObject banks = new JSONObject();
                        if (statusChange.pinpadBanks == null)
                            return banks;
                        JSONObject bank;
                        for (Map.Entry<String, StatusChange.BankApp> entry : statusChange.pinpadBanks.entrySet()) {
                            bank = new JSONObject();
                            StatusChange.BankApp bankApp = entry.getValue();
                            bank.put("aiic", bankApp.aiic);
                            bank.put("catid", bankApp.catid);
                            bank.put("caid", bankApp.caid);
                            bank.put("ppid", bankApp.ppid);
                            banks.put(entry.getKey(), bank);
                        }
                        return banks;
                    }

                    @Override
                    public void OnStatusChanged(StatusChange statusChange) {
                        JSONObject json = new JSONObject();
                        try {
                            json.put("batteryLevel", statusChange.batteryLevel);
                            json.put("ready", statusChange.ready);
                            json.put("connected", statusChange.connected);
                            json.put("paired", statusChange.paired);
                            json.put("awake", statusChange.awake);
                            json.put("updateAvailable", statusChange.updateAvailable);
                            json.put("pinpadName", statusChange.pinpadName);
                            json.put("pinpadBanks", this.getBanks(statusChange));
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, json);
                        pluginResult.setKeepCallback(true);
                        callbackContext.sendPluginResult(pluginResult);
                    }
                });
            }
        });
    }

    private static JSONObject getTransactionResult(TransactionCompleted transactionCompleted) {
        JSONObject json = new JSONObject();
        if (transactionCompleted != null) {
            try {
                json.put("approved", transactionCompleted.approved);
                json.put("receipt", transactionCompleted.receipt);
                json.put("signatureReceipt", transactionCompleted.signatureReceipt);
                json.put("responseCode", transactionCompleted.responseCode);
                json.put("responseText", transactionCompleted.responseText);
                json.put("amount", transactionCompleted.amount);
                json.put("cashOut", transactionCompleted.cashOut);
                json.put("tipAmount", transactionCompleted.tipAmount);
                json.put("surcharge", transactionCompleted.surcharge);
                json.put("account", transactionCompleted.account);
                json.put("CAID", transactionCompleted.CAID);
                json.put("CATID", transactionCompleted.CATID);
                json.put("posReference", transactionCompleted.posReference);
                json.put("dateTime", transactionCompleted.dateTime);
                json.put("authID", transactionCompleted.authID);
                json.put("STAN", transactionCompleted.STAN);
                json.put("settlementDate", transactionCompleted.settlementDate);
                json.put("truncatedPAN", transactionCompleted.approved);
                json.put("guid", transactionCompleted.guid);
                json.put("receiptURL", transactionCompleted.receiptURL);
                json.put("cardName", transactionCompleted.cardName);
                json.put("businessName", transactionCompleted.businessName);
                json.put("businessABN", transactionCompleted.businessABN);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
        return json;
    }

    private void startTransaction(JSONObject transactionRequest, final Boolean hasDisplayCallback, final Boolean hasPromptCallback,
                                  final Boolean hasSignatureCallback, final Boolean animated, final CallbackContext callbackContext) throws JSONException {
        final TransactionRequest request = new TransactionRequest();
        if (transactionRequest.has("amount"))           request.amount = transactionRequest.getInt("amount");
        if (transactionRequest.has("cashOut"))          request.cashOut = transactionRequest.getInt("cashOut");
        if (transactionRequest.has("tipAmount"))        request.tipAmount = transactionRequest.getInt("tipAmount");
        if (transactionRequest.has("transactionType")) {
            switch(transactionRequest.getInt("transactionType")) {
                case 1: request.transactionType = CloudEftposSDK.TransactionType.Purchase;  break;
                case 2: request.transactionType = CloudEftposSDK.TransactionType.Refund;    break;
                default: request.transactionType = CloudEftposSDK.TransactionType.Any;      break;
            }
        }
        if (transactionRequest.has("posReference"))     request.posReference = transactionRequest.getString("posReference");
        if (transactionRequest.has("posNotes"))         request.posNotes = transactionRequest.getString("posNotes");
        if (transactionRequest.has("gpsLocation"))      request.gpsLocation = transactionRequest.getString("gpsLocation");
        if (transactionRequest.has("posData1"))         request.posData1 = transactionRequest.getString("posData1");
        if (transactionRequest.has("posData2"))         request.posData2 = transactionRequest.getString("posData2");
        if (transactionRequest.has("verifyRefund"))     request.verifyRefund = transactionRequest.getBoolean("verifyRefund");
        if (transactionRequest.has("autoGpsLocation"))  request.autoGpsLocation = transactionRequest.getBoolean("autoGpsLocation");

        final OnDisplayUpdate onDisplayUpdate = (!hasDisplayCallback) ? null : new OnDisplayUpdate() {
            @Override
            public void OnDisplay(DisplayData displayData) {
                JSONObject json = new JSONObject();
                try {
                    json.put("type", "display");
                    json.put("msg", displayData.displayData);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, json);
                pluginResult.setKeepCallback(true);
                callbackContext.sendPluginResult(pluginResult);
            }
        };

        final OnPromptUpdate onPromptUpdate = (!hasPromptCallback) ? null : new OnPromptUpdate() {
            @Override
            public void OnPromptData(PromptData promptData) {
                JSONObject json = new JSONObject();
                try {
                    json.put("type", "prompt");
                    json.put("text", promptData.promptData);
                    json.put("inputRequired", promptData.inputRequired);
                    json.put("keys", promptData.keys);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, json);
                pluginResult.setKeepCallback(true);
                callbackContext.sendPluginResult(pluginResult);
            }
        };

        final OnSignaturePrompt onSignaturePrompt = (!hasSignatureCallback) ? null : new OnSignaturePrompt() {
            @Override
            public void OnCustomSignaturePrompt(SignaturePromptData signaturePromptData) {
                JSONObject json = new JSONObject();
                try {
                    json.put("type", "signature");
                    json.put("receipt", signaturePromptData.signaturePromptData);
                    json.put("keys", signaturePromptData.keys);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, json);
                pluginResult.setKeepCallback(true);
                callbackContext.sendPluginResult(pluginResult);
            }
        };

        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.StartTransaction(animated, request, onDisplayUpdate,
                onPromptUpdate, onSignaturePrompt, new OnTransactionCompleted() {
                    @Override
                    public void OnComplete(TransactionCompleted transactionCompleted, ErrorResult errorResult) {
                        JSONObject transResult = CloudEftposGap.getTransactionResult(transactionCompleted);
                        PluginResult.Status status = (errorResult == null) ? PluginResult.Status.OK : PluginResult.Status.ERROR;
                        PluginResult pluginResult = null;
                        if (errorResult == null){
                            pluginResult = new PluginResult(status, transResult);
                        }
                        else{
                            pluginResult = new PluginResult(status, errorResult.description);
                        }
                        callbackContext.sendPluginResult(pluginResult);
                    }
                }, cordova.getActivity().getApplicationContext());
            }
        });
    }

    private void cancelTransaction(final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.CancelTransaction();
                callbackContext.success();
            }
        });
    }

    private void promptResponse(final String key, final String text, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.PromptResponse(key, text);
                callbackContext.success();
            }
        });
    }

    private void recoverTransaction(final String posReference, final int transactionType, final int amount, final Boolean animated, final CallbackContext callbackContext) {
        final CloudEftposSDK.TransactionType type;
        switch(transactionType) {
            case 1: type = CloudEftposSDK.TransactionType.Purchase;  break;
            case 2: type = CloudEftposSDK.TransactionType.Refund;    break;
            default: type = CloudEftposSDK.TransactionType.Any;      break;
        }
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.RecoverTransaction(type, amount, posReference, new OnTransactionCompleted() {
                    @Override
                    public void OnComplete(TransactionCompleted transactionCompleted, ErrorResult errorResult) {
                        JSONObject transResult = CloudEftposGap.getTransactionResult(transactionCompleted);
                        PluginResult.Status status = (errorResult == null) ? PluginResult.Status.OK : PluginResult.Status.ERROR;
                        PluginResult pluginResult = null;
                        if (errorResult == null){
                            pluginResult = new PluginResult(status, transResult);
                        }
                        else{
                            pluginResult = new PluginResult(status, errorResult.description);
                        }
                        callbackContext.sendPluginResult(pluginResult);
                    }
                });
            }
        });
    }

    private void sleepDevice(final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.SleepDevice();
                callbackContext.success();
            }
        });
    }

    private void wakeDevice(final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.WakeDevice();
                callbackContext.success();
            }
        });
    };

    private void advancedMenu(final Boolean animated, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.AdvancedMenu(animated, new OnPrint() {
                    @Override
                    public void OnPrintCallback(PrintData printData) {
                        JSONObject json = new JSONObject();
                        try {
                            json.put("type", printData.type);
                            json.put("receipt", printData.receipt);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        PluginResult pluginResult = new PluginResult(PluginResult.Status.OK, json);
                        pluginResult.setKeepCallback(true);
                        callbackContext.sendPluginResult(pluginResult);
                    }
                }, new OnAdvancedMenuClosed() {
                    @Override
                    public void OnClose() {
                        callbackContext.success();
                    }
                });
            }
        });
    }

    private void updatePINpad(final Boolean animated, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                cloudEftpos.UpdatePINpad(animated, new OnUpdateCompleted() {
                    @Override
                    public void OnUpdateComplete(UpdateCompleted updateCompleted) {
                        PluginResult.Status status = (updateCompleted.error != null) ? PluginResult.Status.OK : PluginResult.Status.ERROR;
                        PluginResult pluginResult = new PluginResult(status, updateCompleted.error);
                        callbackContext.sendPluginResult(pluginResult);
                    }
                });
            }
        });
    }

    private void emailReceipt(final String posReference, final String transactionGuid, final String emailAddress, final CallbackContext callbackContext) {
        cordova.getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Boolean result = cloudEftpos.EmailReceipt(posReference, transactionGuid, emailAddress);
                PluginResult.Status status = (result) ? PluginResult.Status.OK: PluginResult.Status.ERROR;
                PluginResult pluginResult = new PluginResult(status, "");
                callbackContext.sendPluginResult(pluginResult);
            }
        });
    }

}
