function cloudSettings() {
  return {
    model: {
      type: 0,
      host: "",
      port: null,
      username: "",
      password: "",
      topic: ""
    },
    init() {
      showLoading();
      fetch(url + "/command", {
        method: "POST",
        body: JSON.stringify({ cmd: CommandType.REQUEST_CLOUD_SETTINGS })
      })
      .then(response => response.json())
      .then(data => {
        this.model = data;
        hideLoading();
      });
    },
    onSubmitWifi(event) {
      event.preventDefault();
      event.stopPropagation();
      event.stopImmediatePropagation();

      showLoading();
      fetch(url + "/command", {
        method: "POST",
        body: JSON.stringify({ 
          cmd: CommandType.REQUEST_SAVE_CLOUD_SETTINGS, 
          data: {
            type: parseInt(this.model.type),
            host: this.model.host?.toString() || '',
            port: this.model.port || 0,
            username: this.model.username?.toString() || '',
            password: this.model.password?.toString() || '',
            topic: (parseInt(this.model.type) === 1) ? this.model.topic?.toString() || '' : ''
          } 
        })
      })
      .then(response => response.json())
      .then(data => {
        hideLoading();
      });
    }
  }
}
