const ext = require('bindings')('tld');

const fs = require('fs');
const FILE_PATH = 'data/20170301-rdns-test.json';
const LIST_SIZE = 10000;
const es = require('event-stream');
const stream = fs.createReadStream(FILE_PATH, 'utf-8');
let jsonString = '';
let count = 0;

console.time("TLD");
const extractTld = (param) => {
  const buffer = Buffer.from(param);
  ext
    .extractTld(buffer, () => {})
    .then(console.log)
}

stream
  .pipe(es.split())
  .pipe(es.map((string, cb) => {
    if (count == LIST_SIZE) {
      extractTld(jsonString + string + '\n' + null);
      jsonString = '';
      count = 0;
    }
    jsonString += `${string}\n`;
    count ++;
    cb();
  }))

stream.on('end', () => {
  console.log('finish');
  console.timeEnd('TLD');
})
