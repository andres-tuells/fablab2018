import * as SerialPort from 'serialport';
import * as Rx from 'rxjs';

let _messageObserver = null;
const _messageObservable = Rx.Observable.create((observer) => {
  _messageObserver = observer;
});

const parsers = SerialPort.parsers;
const parser = new parsers.Readline('\r\n');
let serialPort = null;

const state = {
  maxMessages: 10,
  baudRate: 9600,
  baudRateOptions: [2400, 4800, 9600],
  portAddress: '/dev/ttyACM0',
  messages: [],
  list: [],
};

const mutations = {
  updateBaudRate(state, value) {
    state.baudRate = value;
  },
  updatePort(state, value) {
    state.portAddress = value;
  },
  updateSerialPort(state, value) {
    state.serialPort = value;
  },
  addMessage(state, { type, content }) {
    const message = { type, content };
    if (_messageObserver) _messageObserver.next(message);
    console.log(`Serial: ${JSON.stringify(message)}`);
    state.messages.push(message);
    if (state.messages.length > state.maxMessages) {
      const [_, ...messages] = state.messages;
      state.messages = messages;
    }
  },
  clearMessages(state) {
    state.messages = [];
  },
  setList(state, list) {
    state.list = list;
  },
};

function connect(state, commit) {
  if (!state.portAddress || !state.baudRate) throw new Error('Serial port conf missing');
  serialPort = new SerialPort(
    state.portAddress,
    { baudRate: state.baudRate },
  );
  serialPort.pipe(parser);
  parser.on('data', (content) => {
    commit('addMessage', { type: 'received', content });
  });
  commit('updateSerialPort', serialPort);
  return new Promise((resolve) => {
    serialPort.on('open', () => {
      resolve();
      console.log(`Connected to ${state.portAddress}, baud: ${state.baudRate}`);
    });
  });
}

const actions = {
  listen({ commit, getters, state, rootGetters }) { // eslint-disable-line no-unused-vars
    console.log('startListening...', state.portAddress, state.baudRate);
    if (serialPort) serialPort.close();
    return connect(state, commit);
  },
  async send({ commit, getters, state, rootGetters }, content) { // eslint-disable-line no-unused-vars
    if (!serialPort) {
      await connect(state, commit);
    }
    serialPort.write(content);
    commit('addMessage', { type: 'sended', content });
  },
  close({ commit, getters, state, rootGetters }) { // eslint-disable-line no-unused-vars
    if (serialPort) serialPort.close();
    state.serialPort = null;
    console.log(`Connection to ${state.portAddress} closed.`);
  },
  async list({ commit, getters, state, rootGetters }) { // eslint-disable-line no-unused-vars
    let ports = await SerialPort.list();
    if (ports) ports = ports.filter(port => port.vendorId);
    else ports = [];
    commit('setList', ports);
    return ports;
  },
  updatePort({ commit, getters, state, rootGetters }, port) { // eslint-disable-line no-unused-vars
    commit('updatePort', port);
  },
  updateBaudRate({ commit, getters, state, rootGetters }, value) { // eslint-disable-line no-unused-vars
    commit('updateBaudRate', value);
  },
  clearMessages({ commit, getters, state, rootGetters }) { // eslint-disable-line no-unused-vars
    commit('clearMessages');
  },
};

const getters = {
  list: state => () => state.list,
  messages: state => () => state.messages,
  reverseMessages: state => () => {
    const [...messages] = state.messages;
    messages.reverse();
    return messages;
  },
  messageObservable: state => () => _messageObservable,
  source: state => key => _messageObservable.filter(x => x.type === 'received')
    .map(x => x.content)
    .filter(x => x.startsWith(key))
    .map(x => x.substring(key.length, x.length))
  ,
};


export default {
  namespaced: true,
  state,
  mutations,
  actions,
  getters,
};
