#ifndef _CMDS_H_
#define _CMDS_H_

enum CommandType {
  UNKNOW                                      =  0,
  
  REQUEST_DEVICE_SETTINGS                     =  1,
  REQUEST_NETWORK_SETTINGS                    =  2,
  REQUEST_SERIAL_SETTINGS                     =  3,
  REQUEST_SECURITY_SETTINGS                   =  4,
  REQUEST_PROTOCOLS_SETTINGS                  =  5,
  REQUEST_WEBSOCKET_CLIENT_SETTINGS           =  6,
  REQUEST_MQTT_CLIENT_SETTINGS                =  7,
  REQUEST_TCP_CLIENT_SETTINGS                 =  8,
  REQUEST_UDP_CLIENT_SETTINGS                 =  9,
  REQUEST_GSM_GPRS_SETTINGS                   = 10,
  REQUEST_AVIABLE_NETWORKS                    = 11,
  REQUEST_SENSORS_ADDRESSES                   = 12,
  REQUEST_SENSORS_VALUES                      = 13,
  REQUEST_DEVICE_CHANNELS                     = 14,
  REQUEST_DEVICE_RULES                        = 15,
  REQUEST_MODBUS_SETTINGS                     = 16,

  REQUEST_SAVE_DEVICE_SETTINGS                = 17,
  REQUEST_SAVE_NETWORK_SETTINGS               = 18,
  REQUEST_SAVE_SERIAL_SETTINGS                = 19,
  REQUEST_SAVE_SECURITY_SETTINGS              = 20,
  REQUEST_SAVE_PROTOCOLS_SETTINGS             = 21,
  REQUEST_SAVE_WEBSOCKET_CLIENT_SETTINGS      = 22,
  REQUEST_SAVE_MQTT_CLIENT_SETTINGS           = 23,
  REQUEST_SAVE_TCP_CLIENT_SETTINGS            = 24,
  REQUEST_SAVE_UDP_CLIENT_SETTINGS            = 25,
  REQUEST_SAVE_GSM_GPRS_SETTINGS              = 26,
  REQUEST_SAVE_DEVICE_CHANNELS                = 27,
  REQUEST_SAVE_DEVICE_RULES                   = 28,
  REQUEST_SAVE_MODBUS_SETTINGS                = 29,

  REQUEST_SIGNIN                              = 30,

  REQUEST_RESTART                             = 255,

  RESPONSE_DEVICE_SETTINGS                    = 101,
  RESPONSE_NETWORK_SETTINGS                   = 102,
  RESPONSE_SERIAL_SETTINGS                    = 103,
  RESPONSE_SECURITY_SETTINGS                  = 104,
  RESPONSE_PROTOCOLS_SETTINGS                 = 105,
  RESPONSE_WEBSOCKET_CLIENT_SETTINGS          = 106,
  RESPONSE_MQTT_CLIENT_SETTINGS               = 107,
  RESPONSE_TCP_CLIENT_SETTINGS                = 108,
  RESPONSE_UDP_CLIENT_SETTINGS                = 109,
  RESPONSE_GSM_GPRS_SETTINGS                  = 110,
  RESPONSE_AVIABLE_NETWORKS                   = 111,
  RESPONSE_SENSORS_ADDRESSES                  = 112,
  RESPONSE_SENSORS_VALUES                     = 113,
  RESPONSE_DEVICE_CHANNELS                    = 114,
  RESPONSE_DEVICE_RULES                       = 115,
  RESPONSE_MODBUS_SETTINGS                    = 116,

  RESPONSE_SAVE_DEVICE_SETTINGS               = 117,
  RESPONSE_SAVE_NETWORK_SETTINGS              = 118,
  RESPONSE_SAVE_SERIAL_SETTINGS               = 119,
  RESPONSE_SAVE_SECURITY_SETTINGS             = 120,
  RESPONSE_SAVE_PROTOCOLS_SETTINGS            = 121,
  RESPONSE_SAVE_WEBSOCKET_CLIENT_SETTINGS     = 122,
  RESPONSE_SAVE_MQTT_CLIENT_SETTINGS          = 123,
  RESPONSE_SAVE_TCP_CLIENT_SETTINGS           = 124,
  RESPONSE_SAVE_UDP_CLIENT_SETTINGS           = 125,
  RESPONSE_SAVE_GSM_GPRS_SETTINGS             = 126,
  RESPONSE_SAVE_DEVICE_CHANNELS               = 127,
  RESPONSE_SAVE_DEVICE_RULES                  = 128,
  RESPONSE_SAVE_MODBUS_SETTINGS               = 129,

  RESPONSE_SIGNIN                             = 130,
  RESPONSE_AUTHORIZED                         = 230
};

#endif
