function deviceInfo() {
  return {

    init() {
      showLoading();
      fetch(url + "/command", {
        method: "POST",
        body: JSON.stringify({ cmd: CommandType.REQUEST_DEVICE_SETTINGS })
      })
      .then(response => response.json())
      .then(data => {
        console.log(data);
        hideLoading();
      });
    }

  }
}
