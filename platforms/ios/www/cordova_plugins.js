cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
  {
    "id": "cordova-plugin-battery-status.battery",
    "file": "plugins/cordova-plugin-battery-status/www/battery.js",
    "pluginId": "cordova-plugin-battery-status",
    "clobbers": [
      "navigator.battery"
    ]
  },
  {
    "id": "cordova-plugin-device.device",
    "file": "plugins/cordova-plugin-device/www/device.js",
    "pluginId": "cordova-plugin-device",
    "clobbers": [
      "device"
    ]
  },
  {
    "id": "au.com.questps.cloudeftpossdk.gap.cloudeftpossdk",
    "file": "plugins/au.com.questps.cloudeftpossdk.gap/www/cloudeftpos.js",
    "pluginId": "au.com.questps.cloudeftpossdk.gap",
    "clobbers": [
      "cloudeftpos"
    ]
  }
];
module.exports.metadata = 
// TOP OF METADATA
{
  "cordova-plugin-whitelist": "1.3.3",
  "cordova-plugin-battery-status": "2.0.2",
  "cordova-plugin-device": "2.0.2",
  "au.com.questps.cloudeftpossdk.gap": "1.0.0"
};
// BOTTOM OF METADATA
});