
var url = "http://192.168.0.103";
// var url = "";

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
    login() {
      showLoading();
      fetch("/pages/login.html")
        .then(response => response.text())
        .then(html => {
          setHtml(document.getElementById("main-content"), html);
          hideLoading();
        })
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
    default: {          
      console.log(payload);
      break;
    }          
  }
}

function initializeEvents() {
  if(window.EventSource) {
    var source = new EventSource(url + '/events');

    source.onopen = (ev) => {
      console.log("Events Connected");
    }

    source.onerror = (ev) => {
      if (e.target.readyState != EventSource.OPEN) {
        console.log("Events Disconnected");
      }
    }

    source.onmessage = (ev) => {
      let payload = JSON.parse(ev.data);          
      process(payload);
    }
  }
}

function onDocumentReady() {
  initializeEvents();
  showLoading();
  setTimeout(() => {
    fetch("/pages/dashboard.html")
    .then(response => response.text())
    .then(html => {          
      setHtml(document.getElementById("main-content"), html);
      hideLoading();
    });
  }, 3000);
}
