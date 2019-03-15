const fs = require('fs');
const FILE_PATH = 'data/20170301-rdns-test.json';
const ext = require('bindings')('tld');
// const stream = fs.createReadStream(FILE_PATH, 'utf-8');

async function main(inputFilePath) {
  const readStream = fs.createReadStream(inputFilePath,
    { encoding: 'utf8', highWaterMark: 1024, objectMode: true });

  for await (const chunk of readStream) {
    console.log(chunk);
    await ext.extractTld(chunk, () => {});
  }
  console.log('### DONE ###');
}

main(FILE_PATH).catch(console.error)