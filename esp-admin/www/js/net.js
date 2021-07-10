function networkSettings() {
  return {
    model: {
      ap: {
        ssid: "",
        password: "",
        ip: ""
      },
      wifi: {
        ssid: "",
        password: "",
        ip: ""
      }        
    },
    networks: [],
    isOpen: false,
    init() {
      document.getElementById("net").addEventListener("onNetworks", (event) => {
        this.networks = event.detail.networks.filter(n => n.ssid !== '');
      });
      
      showLoading();
      fetch(url + "/command", {
        method: "POST",
        body: JSON.stringify({ cmd: CommandType.REQUEST_NETWORK_SETTINGS })
      })
      .then(response => response.json())
      .then(data => {
        this.model = data;
        hideLoading();
      });
    },
    selectItem(event, item, index) {
      this.model.wifi.ssid = this.networks[index].ssid;
      this.model.wifi.rssi = this.networks[index].rssi;
    },
    modelSignal(refs) {
      
      for(var i = refs.signalStrench.classList.length - 1; i >= 0; i--) {
        if(refs.signalStrench.classList[i].match(/bg-*/i)) {
          refs.signalStrench.classList.remove(refs.signalStrench.classList[i]);
        }
      }

      var newClassObj = this.signal(this.model.wifi.rssi);
      var key = Object.keys(newClassObj)[0];
      
      refs.signalStrench.classList.add(key);

      return {};
    },
    signal(rssi) {
      if(rssi >= -50) {
        return {
          'bg-green-700': true
        }
      } else if (rssi >= -60) {
        return {
          'bg-green-500': true
        }
      } else if (rssi >= -67) {
        return {
          'bg-yellow-400': true
        }
      } else if (rssi >= -70) {
        return {
          'bg-yellow-500': true
        }
      } else if (rssi >= -80) {
        return {
          'bg-yellow-500': true
        }
      } else if (rssi >= -90) {
        return {
          'bg-red-600': true
        }
      } else if(rssi !== undefined) {
        return {
          'bg-red-900': true
        }
      }
      
      return {
        'bg-gray-200': true
      }
    },
    onSubmitWifi(event) {
      event.preventDefault();
      event.stopPropagation();
      event.stopImmediatePropagation();

      showLoading();
      fetch(url + "/command", {
        method: "POST",
        body: JSON.stringify({ 
          cmd: CommandType.REQUEST_SAVE_WIFI_SETTINGS, 
          data: {
            ssid: this.model.wifi.ssid,
            password: this.model.wifi.password?.toString() || ''
          } 
        })
      })
      .then(response => response.json())
      .then(data => {
        // console.log(data);
        hideLoading();
      });

      /*console.log({
        wifi: {
          ssid: this.model.wifi.ssid,
          password: this.model.wifi.password || ''
        }
      });*/
    },
    onSubmitAp(event) {
      event.preventDefault();
      event.stopPropagation();
      event.stopImmediatePropagation();
      
      showLoading();
      fetch(url + "/command", {
        method: "POST",
        body: JSON.stringify({ 
          cmd: CommandType.REQUEST_SAVE_AP_SETTINGS, 
          data: {
            password: this.model.ap.password?.toString() || ''
          } 
        })
      })
      .then(response => response.json())
      .then(data => {
        // console.log(data);
        hideLoading();
      });

      /*console.log({
        ap: {
          ssid: this.model.ap.ssid,
          password: this.model.ap.password || ''
        }
      });*/
    }
  }
}
