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
        body: JSON.stringify({ cmd: CommandType.REQUEST_PROTOCOLS_SETTINGS })
      })
      .then(response => response.json())
      .then(data => {
        this.model = data;
        console.log(data);
        hideLoading();
      });
    },
    onSubmitWifi(event) {
      event.preventDefault();
      event.stopPropagation();
      event.stopImmediatePropagation();

      console.log(event);
    }
  }
}
