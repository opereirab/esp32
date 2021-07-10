function deviceInfo() {
  return {
    model: {
      device: {
        name: "",
        serial: "",
        type: "",
        version: "1.0.0"
      }
    },
    isDeviceNameEditingMode: false,
    init() {
      showLoading();
      fetch(url + "/command", {
        method: "POST",
        body: JSON.stringify({ cmd: CommandType.REQUEST_DEVICE_SETTINGS })
      })
      .then(response => response.json())
      .then(data => {
        this.model = data;
        hideLoading();
      });
    },
    updateDeviceName(event) {
      event.preventDefault();
      event.stopPropagation();
      event.stopImmediatePropagation();

      showLoading();
      fetch(url + "/command", {
        method: "POST",
        body: JSON.stringify({ 
          cmd: CommandType.REQUEST_SAVE_DEVICE_SETTINGS, 
          data: {
            name: this.model.device.name
          } 
        })
      })
      .then(response => response.json())
      .then(data => {
        this.isDeviceNameEditingMode = false;
        hideLoading();
      });

      
    }
  }
}
