const ext = require('bindings')('tld');
// const buffer = Buffer.from(`{"name":"73.39.12.63","value":"c-73-39-12-63.hsd1.md.comcast.net"}
// {"name":"73.39.12.63","value":"c-73-39-12-63.hsd1.md.comcast.net"}`);

const fs = require('fs');
const FILE_PATH = 'data/20170301-rdns-test.json';
const LIST_SIZE = 4000;
const es = require('event-stream');
const stream = fs.createReadStream(FILE_PATH, 'utf-8');
let list = [];

console.time("TLD");
const extractTld = (list) => {
  const buffer = Buffer.from("["+list.toString()+"]");
  ext
    .extractTld(buffer, () => {})
    .then(console.log)
}

stream
  .pipe(es.split())
  .pipe(es.map((string, cb) => {
    if (list.length == LIST_SIZE) {
      extractTld(list);
      list = [];
    }
    list.push(string);
    cb();
  }))

stream.on('end', () => {
  console.log('finish');
  console.timeEnd('TLD');
})
