
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
        // console.log(data);
        this.model = Object.assign(this.model, data);
        // this.model = data;
        
        fetch(url + "/command", {
          method: "POST",
          body: JSON.stringify({ cmd: CommandType.REQUEST_SENSORS_TYPES })
        })
        .then(response => response.json())
        .then(types => {
          // console.log(types);
          this.model.types = Object.keys(types).map(k => Object.assign(types[k], { name: k }));
          fetch(url + "/command", {
            method: "POST",
            body: JSON.stringify({ cmd: CommandType.REQUEST_SENSORS_FUNCTIONS })
          })
          .then(response => response.json())
          .then(functions => {
            // console.log(functions);
            this.model.functions = functions;
            fetch(url + "/command", {
              method: "POST",
              body: JSON.stringify({ cmd: CommandType.REQUEST_CHANNELS })
            })
            .then(response => response.json())
            .then(data => {
              // console.log(data);
              this.model.deviceId = data.deviceId;
              this.model.channels = data.channels;
              const event = new Event('channels-changed');
              document.dispatchEvent(event)
              hideLoading();
            });
          });
        });
      });
    },
    getChannelType(ch) {      
      return this.model.types.find(x => x.id === ch.type);
    },
    drawSensor(ch, i, units) {
      return '' +
       
      '<div class="ml-16 pb-6 flex flex-wrap w-full items-baseline sm:pb-2">' +      
        '<p id="sensor-value-' + ch.id + "-"  + i + '" class="text-2xl font-semibold text-gray-900">' +
          '71,897' + 
        '</p>' +
        '<p class="ml-2 flex items-baseline text-sm font-semibold text-green-600">' +            
          // '<svg class="self-center flex-shrink-0 h-5 w-5 text-green-500" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20" fill="currentColor" aria-hidden="true">' +
          //   '<path fill-rule="evenodd" d="M5.293 9.707a1 1 0 010-1.414l4-4a1 1 0 011.414 0l4 4a1 1 0 01-1.414 1.414L11 7.414V15a1 1 0 11-2 0V7.414L6.707 9.707a1 1 0 01-1.414 0z" clip-rule="evenodd" />' +
          // '</svg>' +
          // '<span class="sr-only">' +
          //   'Increased by' +
          // '</span>' +
          (units[i]?.unit || '') +
        '</p>' + 
      '</div>';
    },
    drawSensors(ch, index) {
      let html = '';
      let type = this.getChannelType(ch);

      if(type === undefined || type === null || ch.id === undefined || ch.id === null) {
        return html;
      }

      let count = 1;
      let units = [];

      switch (type.name) {
        case "PZEM004": {
          count = 4;
          break;
        }
        case "PZEM004t": {
          count = 6;
          units = [
            { decimal: 2, title: 'VOLTAGE', unit: 'V'},
            { decimal: 2, title: 'CURRENT', unit: 'A'},
            { decimal: 2, title: 'POWER', unit: 'W'},
            { decimal: 3, title: 'ENERGY', unit: 'kW/h'},
            { decimal: 1, title: 'FREQUENCY', unit: 'Hz'},
            { decimal: 2, title: 'Pf', unit: ''}
          ]
          break;
        }      
        default:
          break;
      }

      for(var i = 0; i < count; i++) {
        html += '<div class="relative bg-white pt-5 px-4 pb-12 sm:pt-6 sm:px-6 shadow rounded-lg overflow-hidden">';
        html +=   '<dt>';
        html +=     '<div class="absolute bg-indigo-500 rounded-md p-3">';
        html +=       '<svg class="h-6 w-6 text-white" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke="currentColor" aria-hidden="true">';
        html +=         '<path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 4.354a4 4 0 110 5.292M15 21H3v-1a6 6 0 0112 0v1zm0 0h6v-1a6 6 0 00-9-5.197M13 7a4 4 0 11-8 0 4 4 0 018 0z" />';
        html +=       '</svg>';
        html +=     '</div>';
        html +=     '<p class="ml-16 text-sm font-medium text-gray-500 truncate"> Channel ' + this.channelTitle(ch, index, i, units) + '</p>';
        html +=   '</dt>';
        html +=   '<dd class="flex flex-col">';
        html +=     '<div class="w-full">';
        html +=       this.drawSensor(ch, i, units);
        html +=     '</div>';
        html +=     '<div class="absolute bottom-0 inset-x-0 bg-gray-50 px-4 py-4 sm:px-6">';
        html +=       '<div class="text-sm">';
        html +=         '<a href="#" class="font-medium text-indigo-600 hover:text-indigo-500"> View <span class="sr-only"> Total Subscribers stats</span></a>';
        html +=       '</div>';
        html +=     '</div>';
        html +=   '</dd>';
        html += '</div>';
      }

      return html;
    },
    channelTitle(ch, index, i, units) {
      let title = index.toString(16);
      if(title.length < 2) {
        title = '0x0' + title;
      } else {
        title = '0x' + title
      }
      return title + ((units[i]?.title) ? ' - ' + units[i]?.title : '');
    },
    drawChannels() {
      let html = '';
      
      if(this.model?.channels === undefined || this.model?.channels === null)
        return html;

      this.model.channels.forEach((ch, index) => {
        html += this.drawSensors(ch, index);        
      });
      return html;
    }
  }
}
