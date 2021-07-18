
var host = "192.168.0.103"
var url = "http://" + host;
var ws = "ws://admin:admin@" + host + ":8080/ws";

function setHtml(elm, html) {
  elm.innerHTML = html;
  Array.from(elm.querySelectorAll("script")).forEach(oldScript => {
    const newScript = document.createElement("script");
    Array.from(oldScript.attributes)
      .forEach(attr => newScript.setAttribute(attr.name, attr.value));
    newScript.appendChild(document.createTextNode(oldScript.innerHTML));
    oldScript.parentNode.replaceChild(newScript, oldScript);
  });
}

function showLoading() {
  document.getElementById("loading").classList.replace("hidden", "flex");
} 

function hideLoading() {
  document.getElementById("loading").classList.replace("flex", "hidden");
}

function body() {
  return {
    notification: {
      isVisible: false,
      show() {

      },
      hide() {

      }
    },
    navbar: {
      activeItem: 0,
      isOpen: false,
      toggle(index) {
        if(index !== this.activeItem) {
          this.activeItem = index;
          this.isOpen = true;
        } else {
          this.isOpen = !this.isOpen;
        }
      }
    },
    responsiveMenu: {
      isOpened: false,
      toggle() {            
        this.isOpened = !this.isOpened;
      }
    },
    userMenu: {
      isOpened: false
    },
    login() {
      this.closeAll();
      showLoading();
      fetch("/pages/login.html")
        .then(response => response.text())
        .then(html => {
          setHtml(document.getElementById("main-content"), html);
          hideLoading();
        })
    },
    logout() {      
      this.closeAll();
      sessionStorage.removeItem("DEVICE");      
      this.login();
    },
    dashboard() {
      showLoading();
      fetch("/pages/dashboard.html")
        .then(response => response.text())
        .then(html => {
          setHtml(document.getElementById("main-content"), html);
          hideLoading();
          this.closeAll();
        });
    },
    settings() {
      showLoading();
      fetch("/pages/settings.html")
        .then(response => response.text())
        .then(html => {
          setHtml(document.getElementById("main-content"), html);
          hideLoading();
          this.closeAll();
        });
    },
    closeAll() {
      this.navbar.toggle(0);
      this.responsiveMenu.isOpened = false;
    },
    closeUpdateTimeDialog() {
      document.getElementById("dlgUpdateDateTime").classList.remove("fixed");
      document.getElementById("dlgUpdateDateTime").classList.add("hidden");
    },
    syncronizeDevicesTime() {
      let date = new Date();
      fetch(url + "/command", {
        method: "POST",
        body: JSON.stringify({ 
          cmd: CommandType.REQUEST_SYNC_DATETIME,
          data: moment(date).add(-1 * date.getTimezoneOffset(), 'minutes').add(1, 'seconds').unix()
        })
      })
      .then(response => response.json())
      .then(data => {
        // console.log(data);
        this.closeUpdateTimeDialog();
      });
    },
    toggleUserMenu() {
      this.userMenu.isOpened = !this.userMenu.isOpened;
    },
    closeUserMenuAll() {
      this.userMenu.isOpened = false;
    },
    user() {
      let data = sessionStorage.getItem("DEVICE");
      if(data !== undefined && data !== null) {
        let user = JSON.parse(data);
        return user;
      }
      return null;
    },
    isAuthenticated() {
      let user = this.user();
      return (user !== undefined && user !== null && user.username !== undefined && user.username !== null);
    }
    
  }
}

function navbar() {
  return {
    activeItem: 0,
    isOpen: false,
    toggle(index) {
      if(index !== this.activeItem) {
        this.activeItem = index;
        this.isOpen = true;
      } else {
        this.isOpen = !this.isOpen;
      }
    }
  }
}

function responsiveMenu() {
  return {
    isOpened: false,
    toggle() {
      this.isOpened = !this.isOpened;
    }
  }
}

function process(payload) {      
  switch (payload.cmd) {
    case CommandType.RESPONSE_SYSTEM_EVENT_AP_STACONNECTED:
    case CommandType.RESPONSE_SYSTEM_EVENT_AP_STADISCONNECTED:
    case CommandType.RESPONSE_SYSTEM_EVENT_AP_STAIPASSIGNED: {
      let elem = document.getElementById("num");
      if(elem) {  
        elem.innerHTML = payload.data;
      }
      break;
    }
    case CommandType.RESPONSE_SYSTEM_EVENT_SCAN_DONE: {          
      let elem = document.getElementById("net");
      if(elem) {
        let customEvent = new CustomEvent('onNetworks', {detail: payload});
        elem.dispatchEvent(customEvent);
      }
      // $dispatch('updateNetworks', ) ;
      break;
    }
    case CommandType.RESPONSE_SENSORS_VALUES : {
      // console.log(payload); 
      try {
        /*console.log(new Intl.DateTimeFormat('default', {
          year: 'numeric', month: 'numeric', day: 'numeric',
          hour: 'numeric', minute: 'numeric', second: 'numeric',
          hour12: false,
          timeZone: Intl.DateTimeFormat().resolvedOptions().timeZone,          
        }).format(payload*1000), new Date(payload*1000).toTimeString().slice(9));*/

        let elem = document.getElementById("datetime");
        if(elem) {
          elem.innerHTML = moment.unix(payload.date).utc().format('DD/MM/YYYY HH:mm:ss');
        }

        payload.data?.forEach(ch => {          
          ch.values?.forEach((s, i) => {
            let id = "sensor-value-" + ch.id + "-" + i;
            elem = document.getElementById(id);
            if(elem) {
              elem.innerHTML = ch.values[i];
            }
          })
          
        });
        // console.log(moment.unix(payload).utc().format('DD/MM/YYYY HH:mm:ss'));
        // console.log(new Date(payload*1000).toString());
      } catch (error) {
        console.log(payload);  
      }
      break;
    }
    default: {
      // try {
      //   /*console.log(new Intl.DateTimeFormat('default', {
      //     year: 'numeric', month: 'numeric', day: 'numeric',
      //     hour: 'numeric', minute: 'numeric', second: 'numeric',
      //     hour12: false,
      //     timeZone: Intl.DateTimeFormat().resolvedOptions().timeZone,          
      //   }).format(payload*1000), new Date(payload*1000).toTimeString().slice(9));*/

      //   let elem = document.getElementById("datetime");
      //   if(elem) {
      //     elem.innerHTML = moment.unix(payload).utc().format('DD/MM/YYYY HH:mm:ss');
      //   }
      //   // console.log(moment.unix(payload).utc().format('DD/MM/YYYY HH:mm:ss'));
      //   // console.log(new Date(payload*1000).toString());
      // } catch (error) {
      //   console.log(payload);  
      // }           
      console.log(payload);  
      break;
    }          
  }
}

function connectWebSocket() {

  let websocket = new WebSocket(ws);

  websocket.onopen = function() {
    console.log("Websocket Connected");
  };

  websocket.onmessage = function(e) {
    let payload = JSON.parse(e.data);          
    process(payload);
  };

  websocket.onclose = function(e) {
    console.log('Websocket is closed. Reconnect will be attempted in 1 second.', e.reason);
    websocket = null;
    setTimeout(function() {
      connectWebSocket();
    }, 1000);
  };

  websocket.onerror = function(err) {
    console.error('Websocket encountered error: ', err.message, 'Closing socket');
    websocket.close();
  };
}

function onDocumentReady() {
  connectWebSocket();
  showLoading();
  setTimeout(() => {
    fetch("/pages/dashboard.html")
    .then(response => response.text())
    .then(html => {          
      setHtml(document.getElementById("main-content"), html);
      // hideLoading();
      document.getElementById("dlgUpdateDateTime").classList.remove("hidden");
      document.getElementById("dlgUpdateDateTime").classList.add("fixed");
    });
  }, 3000);
}
