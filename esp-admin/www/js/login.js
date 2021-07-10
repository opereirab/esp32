function securitySettings() {
  return {
    data: {
      username: "",
      password: ""
    },
    isDialogVisible: false,
    toggle() {
      console.log("toogle");
      this.isDialogVisible = !this.isDialogVisible;
    },
    init() {
      // showLoading();
      // fetch(url + "/command", {
      //   method: "POST",
      //   body: JSON.stringify({ cmd: CommandType.REQUEST_RESET_SECURITY_SETTINGS })
      // })
      // .then(response => response.json())
      // .then(data => {
      //   this.data = data;
      //   hideLoading();
      // });
    },
    signin(event) {
      event.preventDefault();
      event.stopPropagation();
      event.stopImmediatePropagation();
      
      showLoading();
      fetch(url + "/command", {
        method: "POST",
        body: JSON.stringify({ 
          cmd: CommandType.REQUEST_SIGNIN, 
          data: this.data
        })
      })
      .then(response => response.json())
      .then(data => {
        if(data === true) {
          sessionStorage.setItem("DEVICE", JSON.stringify(this.data));
          window.location.href = "/";
        }
        hideLoading();
      });
    }
  }
}
