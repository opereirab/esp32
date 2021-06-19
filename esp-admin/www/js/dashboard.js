
function dashboard() {
  return {
    model: {
      channels: []
    },
    init() {
      showLoading();
      fetch(url + "/command?dummy=" + Date.now(), {
        method: "POST",
        body: JSON.stringify({ cmd: CommandType.REQUEST_DEVICE_SETTINGS })
      })
      .then(response => response.json())
      .then(data => {
        console.log(data);
        this.model = Object.assign(this.model, data);
        // this.model = data;
        
        fetch(url + "/command", {
          method: "POST",
          body: JSON.stringify({ cmd: CommandType.REQUEST_SENSORS_TYPES })
        })
        .then(response => response.json())
        .then(types => {
          console.log(types);
          this.model.types = types;
          fetch(url + "/command", {
            method: "POST",
            body: JSON.stringify({ cmd: CommandType.REQUEST_SENSORS_FUNCTIONS })
          })
          .then(response => response.json())
          .then(functions => {
            console.log(functions);
            this.model.functions = functions;
            fetch(url + "/command", {
              method: "POST",
              body: JSON.stringify({ cmd: CommandType.REQUEST_CHANNELS })
            })
            .then(response => response.json())
            .then(data => {
              console.log(data);
              this.model.deviceId = data.deviceId;
              this.model.channels = data.channels;
              hideLoading();
            });
          });
        });
      });
    }
  }
}
